from cint import *

def fflags(y):
    for x in range(32):
        z = pow(2, x)
        if y & z == z:
            print hex(z)
            
RecIndent = -2
def printRecord(record):
    global RecIndent
    RecIndent += 2
    if hasattr(record, 'copyattrs'):
        msize = max([len(attr) for attr in record.copyattrs])
        for attr in record.copyattrs:
            rec = getattr(record, attr)
            if RecIndent: print " " * (RecIndent - 1),
            print attr + " " * (msize - len(attr)), ":",
            if rec is None:
                print rec
            elif 'flag' in attr.lower() or 'service' in attr.lower():
                print hex(rec)
                for x in range(32):
                    z = pow(2, x)
                    if rec & z == z:
                        print "  Active" + " " * (msize - len("  Active")), "  :", hex(z)

            elif isinstance(rec, tuple) and len(rec) == 2 and isinstance(rec[0], basestring) and isinstance(rec[1], int):
                print PrintFormID(rec)
            elif isinstance(rec, list):
                if len(rec) > 0:
                    IsFidList = True
                    for obj in rec:
                        if not (isinstance(obj, tuple) and len(obj) == 2 and isinstance(obj[0], basestring) and isinstance(obj[1], int)):
                            IsFidList = False
                            break
                    if IsFidList:
                        print [PrintFormID(x) for x in rec]
                    else:
                        print rec
                else:
                    print rec
            else:
                print rec
            printRecord(rec)
    elif isinstance(record, list):
        if len(record) > 0:
            if hasattr(record[0], 'copyattrs'):
                for rec in record:
                    printRecord(rec)
                    
    RecIndent -= 2

def d(record):
    try:
        fid = record.fid
        msize = max([len(attr) for attr in record.copyattrs])
        print "fid" + " " * (msize - len("fid")), ":", PrintFormID(fid)
    except AttributeError:
        pass
    printRecord(record)
    
def regressionTests():
    Current = ObCollection(CollectionType=2)
    Current.addMod("FalloutNV.esm")#, MinLoad=False)
    Current.addMod("RegressionTests.esp")
    Current.load()
    newMod = Current.LookupModFile("RegressionTests.esp")

    assertTES4(Current, newMod)
    assertGMST(Current, newMod)
    assertTXST(Current, newMod)
    assertMICN(Current, newMod)
    assertGLOB(Current, newMod)
    assertCLAS(Current, newMod)
    assertFACT(Current, newMod)
    assertHDPT(Current, newMod)
    assertHAIR(Current, newMod)
    assertEYES(Current, newMod)
    assertRACE(Current, newMod)
    assertSOUN(Current, newMod)
##    newMod.save()

def assertTES4(Current, newMod):
    record = Current.LoadOrderMods[0].TES4

    assert record.IsESM
    assert record.flags1 == 0x80000001
    assert record.versionControl1 == [0, 0, 0, 0]
    assert record.formVersion == 2
    assert record.versionControl2 == [0, 0]
    
    assert record.version == 1.32
    assert record.numRecords == 543989
    assert record.nextObject == 0xFF17B7C6
    assert record.ofst_p == []
    assert record.dele_p == []
    assert record.author == "ipely"
    assert record.author != "Ipely"
    assert record.description == None
    assert record.masters == []
    assert record.DATA == None
    assert record.overrides == []
    assert record.screenshot_p == []

    record = newMod.TES4
    record.flags1 = 5
    record.versionControl1 = [1, 2, 3, 4]
    record.formVersion = 6
    record.versionControl2 = [7, 8]
    
    record.version = 1.2
    record.numRecords = 10
    record.nextObject = 0x00001000
    record.ofst_p = [0, 1, 2, 3]
    record.dele_p = [10, 11, 12, 13]
    record.author = "Waruddar"
    record.description = "This is a test string\nand only a test string."
##    record.masters = ["Oblivion.esm"] #For now, masters shouldn't be set directly. More coding needs to be done to make it safe
##    record.masters = []
    record.DATA = 1
    record.overrides = [0x00001001, 0x00001002, 0x00001003]
    record.screenshot_p = [10, 11, 12, 13, 11, 12, 13]

    assert record.flags1 ==  5 | 0x80000000 #CBash sets 0x80000000 for internal use
    assert record.versionControl1 == [1, 2, 3, 4]
    assert record.formVersion == 6
    assert record.versionControl2 == [7, 8]
    
    assert record.version == 1.2
    assert record.numRecords == 10
    assert record.nextObject == 0x00001000
    assert record.ofst_p == [0, 1, 2, 3]
    assert record.dele_p == [10, 11, 12, 13]
    assert record.author == "Waruddar"
    assert record.author != "WAruddar"
    assert record.description == "This is a test string\nand only a test string."
    assert record.description != "This is A test string\nand only a test string."
##    assert record.masters == ["Oblivion.esm"]
##    assert record.masters == ["oblivion.esm"] #Masters are case-insensitive
    assert record.DATA == None
    assert record.overrides == [('FalloutNV.esm', 0x001001), ('FalloutNV.esm', 0x001002), ('FalloutNV.esm', 0x001003)]
    assert record.screenshot_p == [10, 11, 12, 13, 11, 12, 13]

    print "TES4:Finished testing"

def assertGMST(Current, newMod):
    record = Current.LoadOrderMods[0].GMST[0]

    assert record.fid == ('FalloutNV.esm', 0x17B37C)
    assert record.flags1 == 0x80000000 #CBash sets 0x80000000 for internal use
    assert record.versionControl1 == [12, 92, 22, 0]
    assert record.formVersion == 15
    assert record.versionControl2 == [0, 0]
    
    assert record.eid == "sPoisonNoWeaponMessage"
    assert record.eid == "sPoisonNoweaponMessage"
    assert record.value == "You must first equip a weapon that can be poisoned."
    assert record.value != "You Must first equip a weapon that can be poisoned."

    srecord = newMod.create_GMST("sWarString")
    irecord = newMod.create_GMST("iWarString")
    frecord = newMod.create_GMST("fWarString")

    srecord.flags1 = 10
    srecord.versionControl1 = [1, 3, 2, 6]
    srecord.formVersion = 1
    srecord.versionControl2 = [2, 3]
    srecord.value = "It works!"
    srecord.value = 1 #Shouldn't work
    srecord.value = 1.0 #Shouldn't work

    assert srecord.fid == ('RegressionTests.esp', 0x001001)
    assert srecord.flags1 == 10 | 0x80000000
    assert srecord.versionControl1 == [1, 3, 2, 6]
    assert srecord.formVersion == 1
    assert srecord.versionControl2 == [2, 3]
    assert srecord.eid == "sWarString"
    assert srecord.eid == "sWaRString"
    assert srecord.value == "It works!"
    assert srecord.value != "IT works!"

    irecord.flags1 = 11
    irecord.versionControl1 = [11, 13, 12, 16]
    irecord.formVersion = 13
    irecord.versionControl2 = [12, 13]
    irecord.value = 2
    irecord.value = "It works!"  #Shouldn't work
    irecord.value = 2.0 #Shouldn't work

    assert irecord.fid == ('RegressionTests.esp', 0x001002)
    assert irecord.flags1 == 11 | 0x80000000
    assert irecord.versionControl1 == [11, 13, 12, 16]
    assert irecord.formVersion == 13
    assert irecord.versionControl2 == [12, 13]
    assert irecord.eid == "iWarString"
    assert irecord.eid == "IWarString"
    assert irecord.value == 2

    frecord.flags1 = 12
    frecord.versionControl1 = [12, 32, 22, 62]
    frecord.formVersion = 21
    frecord.versionControl2 = [22, 23]
    frecord.value = 3.0
    frecord.value = "It works!"  #Shouldn't work
    frecord.value = 3 #Shouldn't work

    assert frecord.fid == ('RegressionTests.esp', 0x001003)
    assert frecord.flags1 == 12 | 0x80000000
    assert frecord.versionControl1 == [12, 32, 22, 62]
    assert frecord.formVersion == 21
    assert frecord.versionControl2 == [22, 23]
    assert frecord.eid == "fWarString"
    assert frecord.eid == "fWarSTRing"
    assert frecord.value == 3.0

    record = Current.LoadOrderMods[0].GMST[0]
    newrecord = record.CopyAsOverride(newMod)

    assert newrecord.fid == ('RegressionTests.esp', 0x001004) #GMSTs are keyed by editorID, so the formID will change on CopyAsOverride
    assert newrecord.flags1 == 0x80000000
    assert newrecord.versionControl1 == [12, 92, 22, 0]
    assert newrecord.formVersion == 15
    assert newrecord.versionControl2 == [0, 0]
    assert newrecord.eid == "sPoisonNoWeaponMessage"
    assert newrecord.eid == "sPoisonNoweaponMessage"
    assert newrecord.value == "You must first equip a weapon that can be poisoned."
    assert newrecord.value != "You Must first equip a weapon that can be poisoned."

    newrecord.flags1 = 0
    newrecord.versionControl1 = [122, 232, 222, 6]
    newrecord.formVersion = 24
    newrecord.versionControl2 = [222, 223]
    newrecord.eid = "sTestWar"
    newrecord.eid = "" #Shouldn't work
    newrecord.value = "Test:"

    assert newrecord.fid == ('RegressionTests.esp', 0x001004)
    assert newrecord.flags1 == 0x80000000
    assert newrecord.versionControl1 == [122, 232, 222, 6]
    assert newrecord.formVersion == 24
    assert newrecord.versionControl2 == [222, 223]
    assert newrecord.eid == "sTestWar"
    assert newrecord.eid == "sTEstWar"
    assert newrecord.value == "Test:"
    assert newrecord.value != "TeSt:"

    assert record.fid == ('FalloutNV.esm', 0x17B37C)
    assert record.flags1 == 0x80000000 #CBash sets 0x80000000 for internal use
    assert record.versionControl1 == [12, 92, 22, 0]
    assert record.formVersion == 15
    assert record.versionControl2 == [0, 0]
    assert record.eid == "sPoisonNoWeaponMessage"
    assert record.eid == "sPoisonNoweaponMessage"
    assert record.value == "You must first equip a weapon that can be poisoned."
    assert record.value != "You Must first equip a weapon that can be poisoned."

    print "GMST:Finished testing"

def assertTXST(Current, newMod):
    record = Current.LoadOrderMods[0].TXST[0]

    assert record.fid == ('FalloutNV.esm', 0x177DB0)
    assert record.flags1 == 0x80000000 #CBash sets 0x80000000 for internal use
    assert record.versionControl1 == [30, 91, 19, 0]
    assert record.formVersion == 15
    assert record.versionControl2 == [1, 0]
    assert record.eid == 'NVNCRMPhelmet'
    assert record.eid == 'NVNCRMPHelmet'
    
    assert record.boundX1 == 0
    assert record.boundY1 == 0
    assert record.boundZ1 == 0
    assert record.boundX2 == 0
    assert record.boundY2 == 0
    assert record.boundZ2 == 0
    assert record.baseImageOrTransparencyPath == r'armor\headgear\trooperHelmMP.dds'
    assert record.baseImageOrTransparencyPath == r'Armor\headgear\trooperHelmMP.dds'
    assert record.normalMapOrSpecularPath == r'armor\headgear\trooperHelm_n.dds'
    assert record.normalMapOrSpecularPath == r'Armor\headgear\trooperHelm_n.dds'
    assert record.envMapMaskOrUnkPath == None
    assert record.glowMapOrUnusedPath == None
    assert record.parallaxMapOrUnusedPath == None
    assert record.envMapOrUnusedPath == None
    assert record.decalMinWidth == None
    assert record.decalMaxWidth == None
    assert record.decalMinHeight == None
    assert record.decalMaxHeight == None
    assert record.decalDepth == None
    assert record.decalShininess == None
    assert record.decalScale == None
    assert record.decalPasses == None
    assert record.decalFlags == None
    assert record.decalUnused1 == []
    assert record.decalRed == None
    assert record.decalGreen == None
    assert record.decalBlue == None
    assert record.decalUnused2 == []
    assert record.flags == 0
    
    nrecord = newMod.create_TXST()

    nrecord.flags1 = 10
    nrecord.versionControl1 = [1, 3, 2, 6]
    nrecord.formVersion = 1
    nrecord.versionControl2 = [2, 3]
    nrecord.eid = 'WarTest'
    
    nrecord.boundX1 = 11
    nrecord.boundY1 = 12
    nrecord.boundZ1 = 13
    nrecord.boundX2 = 14
    nrecord.boundY2 = 15
    nrecord.boundZ2 = 16
    nrecord.baseImageOrTransparencyPath = r'armor\1\trooperHelmMP.dds'
    nrecord.normalMapOrSpecularPath = r'Armor\2\trooperHelm_n.dds'
    nrecord.envMapMaskOrUnkPath = r'Armor\3\trooperHelm_n.dds'
    nrecord.glowMapOrUnusedPath = r'Armor\4\trooperHelm_n.dds'
    nrecord.parallaxMapOrUnusedPath = r'Armor\5\trooperHelm_n.dds'
    nrecord.envMapOrUnusedPath = r'Armor\6\trooperHelm_n.dds'
    nrecord.decalMinWidth = 17
    nrecord.decalMaxWidth = 18
    nrecord.decalMinHeight = 19
    nrecord.decalMaxHeight = 20
    nrecord.decalDepth = 21
    nrecord.decalShininess = 22
    nrecord.decalScale = 23
    nrecord.decalPasses = 24
    nrecord.decalFlags = 25
    nrecord.decalUnused1 = [1,2]
    nrecord.decalRed = 26
    nrecord.decalGreen = 27
    nrecord.decalBlue = 28
    nrecord.decalUnused2 = [3]
    nrecord.flags = 29
    
    assert nrecord.fid == ('RegressionTests.esp', 0x001005)
    assert nrecord.flags1 == 0x80000000 | 10
    assert nrecord.versionControl1 == [1, 3, 2, 6]
    assert nrecord.formVersion == 1
    assert nrecord.versionControl2 == [2, 3]
    assert nrecord.eid == 'WarTest'
    assert nrecord.eid == 'WArTest'

    assert nrecord.boundX1 == 11
    assert nrecord.boundY1 == 12
    assert nrecord.boundZ1 == 13
    assert nrecord.boundX2 == 14
    assert nrecord.boundY2 == 15
    assert nrecord.boundZ2 == 16
    assert nrecord.baseImageOrTransparencyPath == r'armor\1\trooperHelmMP.dds'
    assert nrecord.normalMapOrSpecularPath == r'Armor\2\trooperHelm_n.dds'
    assert nrecord.envMapMaskOrUnkPath == r'Armor\3\trooperHelm_n.dds'
    assert nrecord.glowMapOrUnusedPath == r'Armor\4\trooperHelm_n.dds'
    assert nrecord.parallaxMapOrUnusedPath == r'Armor\5\trooperHelm_n.dds'
    assert nrecord.envMapOrUnusedPath == r'Armor\6\trooperHelm_n.dds'
    assert nrecord.decalMinWidth == 17
    assert nrecord.decalMaxWidth == 18
    assert nrecord.decalMinHeight == 19
    assert nrecord.decalMaxHeight == 20
    assert nrecord.decalDepth == 21
    assert nrecord.decalShininess == 22
    assert nrecord.decalScale == 23
    assert nrecord.decalPasses == 24
    assert nrecord.decalFlags == 25
    assert nrecord.decalUnused1 == [1,2]
    assert nrecord.decalRed == 26
    assert nrecord.decalGreen == 27
    assert nrecord.decalBlue == 28
    assert nrecord.decalUnused2 == [3]
    assert nrecord.flags == 29

    record = Current.LoadOrderMods[0].TXST[0]
    newrecord = record.CopyAsOverride(newMod)

    assert newrecord.fid == ('FalloutNV.esm', 0x177DB0)
    assert newrecord.flags1 == 0x80000000 #CBash sets 0x80000000 for internal use
    assert newrecord.versionControl1 == [30, 91, 19, 0]
    assert newrecord.formVersion == 15
    assert newrecord.versionControl2 == [1, 0]
    assert newrecord.eid == 'NVNCRMPhelmet'
    assert newrecord.eid == 'NVNCRMPHelmet'
    
    assert newrecord.boundX1 == 0
    assert newrecord.boundY1 == 0
    assert newrecord.boundZ1 == 0
    assert newrecord.boundX2 == 0
    assert newrecord.boundY2 == 0
    assert newrecord.boundZ2 == 0
    assert newrecord.baseImageOrTransparencyPath == r'armor\headgear\trooperHelmMP.dds'
    assert newrecord.baseImageOrTransparencyPath == r'Armor\headgear\trooperHelmMP.dds'
    assert newrecord.normalMapOrSpecularPath == r'armor\headgear\trooperHelm_n.dds'
    assert newrecord.normalMapOrSpecularPath == r'Armor\headgear\trooperHelm_n.dds'
    assert newrecord.envMapMaskOrUnkPath == None
    assert newrecord.glowMapOrUnusedPath == None
    assert newrecord.parallaxMapOrUnusedPath == None
    assert newrecord.envMapOrUnusedPath == None
    assert newrecord.decalMinWidth == None
    assert newrecord.decalMaxWidth == None
    assert newrecord.decalMinHeight == None
    assert newrecord.decalMaxHeight == None
    assert newrecord.decalDepth == None
    assert newrecord.decalShininess == None
    assert newrecord.decalScale == None
    assert newrecord.decalPasses == None
    assert newrecord.decalFlags == None
    assert newrecord.decalUnused1 == []
    assert newrecord.decalRed == None
    assert newrecord.decalGreen == None
    assert newrecord.decalBlue == None
    assert newrecord.decalUnused2 == []
    assert newrecord.flags == 0

    newrecord.flags1 = 10
    newrecord.versionControl1 = [1, 3, 2, 6]
    newrecord.formVersion = 1
    newrecord.versionControl2 = [2, 3]
    newrecord.eid = 'WarTest'
    
    newrecord.boundX1 = 11
    newrecord.boundY1 = 12
    newrecord.boundZ1 = 13
    newrecord.boundX2 = 14
    newrecord.boundY2 = 15
    newrecord.boundZ2 = 16
    newrecord.baseImageOrTransparencyPath = r'armor\1\trooperHelmMP.dds'
    newrecord.normalMapOrSpecularPath = r'Armor\2\trooperHelm_n.dds'
    newrecord.envMapMaskOrUnkPath = r'Armor\3\trooperHelm_n.dds'
    newrecord.glowMapOrUnusedPath = r'Armor\4\trooperHelm_n.dds'
    newrecord.parallaxMapOrUnusedPath = r'Armor\5\trooperHelm_n.dds'
    newrecord.envMapOrUnusedPath = r'Armor\6\trooperHelm_n.dds'
    newrecord.decalMinWidth = 17
    newrecord.decalMaxWidth = 18
    newrecord.decalMinHeight = 19
    newrecord.decalMaxHeight = 20
    newrecord.decalDepth = 21
    newrecord.decalShininess = 22
    newrecord.decalScale = 23
    newrecord.decalPasses = 24
    newrecord.decalFlags = 25
    newrecord.decalUnused1 = [1,2]
    newrecord.decalRed = 26
    newrecord.decalGreen = 27
    newrecord.decalBlue = 28
    newrecord.decalUnused2 = [3]
    newrecord.flags = 29
    
    assert newrecord.fid == ('FalloutNV.esm', 0x177DB0)
    assert newrecord.flags1 == 0x80000000 | 10
    assert newrecord.versionControl1 == [1, 3, 2, 6]
    assert newrecord.formVersion == 1
    assert newrecord.versionControl2 == [2, 3]
    assert newrecord.eid == 'WarTest'
    assert newrecord.eid == 'WArTest'
    
    assert newrecord.boundX1 == 11
    assert newrecord.boundY1 == 12
    assert newrecord.boundZ1 == 13
    assert newrecord.boundX2 == 14
    assert newrecord.boundY2 == 15
    assert newrecord.boundZ2 == 16
    assert newrecord.baseImageOrTransparencyPath == r'armor\1\trooperHelmMP.dds'
    assert newrecord.normalMapOrSpecularPath == r'Armor\2\trooperHelm_n.dds'
    assert newrecord.envMapMaskOrUnkPath == r'Armor\3\trooperHelm_n.dds'
    assert newrecord.glowMapOrUnusedPath == r'Armor\4\trooperHelm_n.dds'
    assert newrecord.parallaxMapOrUnusedPath == r'Armor\5\trooperHelm_n.dds'
    assert newrecord.envMapOrUnusedPath == r'Armor\6\trooperHelm_n.dds'
    assert newrecord.decalMinWidth == 17
    assert newrecord.decalMaxWidth == 18
    assert newrecord.decalMinHeight == 19
    assert newrecord.decalMaxHeight == 20
    assert newrecord.decalDepth == 21
    assert newrecord.decalShininess == 22
    assert newrecord.decalScale == 23
    assert newrecord.decalPasses == 24
    assert newrecord.decalFlags == 25
    assert newrecord.decalUnused1 == [1,2]
    assert newrecord.decalRed == 26
    assert newrecord.decalGreen == 27
    assert newrecord.decalBlue == 28
    assert newrecord.decalUnused2 == [3]
    assert newrecord.flags == 29

    assert record.fid == ('FalloutNV.esm', 0x177DB0)
    assert record.flags1 == 0x80000000 #CBash sets 0x80000000 for internal use
    assert record.versionControl1 == [30, 91, 19, 0]
    assert record.formVersion == 15
    assert record.versionControl2 == [1, 0]
    assert record.eid == 'NVNCRMPhelmet'
    assert record.eid == 'NVNCRMPHelmet'
    
    assert record.boundX1 == 0
    assert record.boundY1 == 0
    assert record.boundZ1 == 0
    assert record.boundX2 == 0
    assert record.boundY2 == 0
    assert record.boundZ2 == 0
    assert record.baseImageOrTransparencyPath == r'armor\headgear\trooperHelmMP.dds'
    assert record.baseImageOrTransparencyPath == r'Armor\headgear\trooperHelmMP.dds'
    assert record.normalMapOrSpecularPath == r'armor\headgear\trooperHelm_n.dds'
    assert record.normalMapOrSpecularPath == r'Armor\headgear\trooperHelm_n.dds'
    assert record.envMapMaskOrUnkPath == None
    assert record.glowMapOrUnusedPath == None
    assert record.parallaxMapOrUnusedPath == None
    assert record.envMapOrUnusedPath == None
    assert record.decalMinWidth == None
    assert record.decalMaxWidth == None
    assert record.decalMinHeight == None
    assert record.decalMaxHeight == None
    assert record.decalDepth == None
    assert record.decalShininess == None
    assert record.decalScale == None
    assert record.decalPasses == None
    assert record.decalFlags == None
    assert record.decalUnused1 == []
    assert record.decalRed == None
    assert record.decalGreen == None
    assert record.decalBlue == None
    assert record.decalUnused2 == []
    assert record.flags == 0

    print "TXST:Finished testing"

def assertMICN(Current, newMod):
    record = Current.LoadOrderMods[0].MICN[0]
    
    assert record.fid == ('FalloutNV.esm', 0x174090)
    assert record.flags1 == 0x80000000 #CBash sets 0x80000000 for internal use
    assert record.versionControl1 == [16, 91, 22, 0]
    assert record.formVersion == 15
    assert record.versionControl2 == [1, 0]
    assert record.eid == 'MenuIconFactionBrotherhood'
    assert record.eid == 'MenuIconFActionBrotherhood'
    
    assert record.iconPath == r'interface\icons\message icons\glow_message_vaultboy_brotherhood.dds'
    assert record.iconPath == r'interface\icons\messAge icons\glow_message_vaultboy_brotherhood.dds'
    assert record.smallIconPath == None
    
    nrecord = newMod.create_MICN()

    nrecord.flags1 = 10
    nrecord.versionControl1 = [1, 3, 2, 6]
    nrecord.formVersion = 1
    nrecord.versionControl2 = [2, 3]
    nrecord.eid = 'WarTest'
    
    nrecord.iconPath = r'armor\1\trooperHelmMP.dds'
    nrecord.smallIconPath = r'Armor\2\trooperHelm_n.dds'
    
    assert nrecord.fid == ('RegressionTests.esp', 0x001006)
    assert nrecord.flags1 == 0x80000000 | 10
    assert nrecord.versionControl1 == [1, 3, 2, 6]
    assert nrecord.formVersion == 1
    assert nrecord.versionControl2 == [2, 3]
    assert nrecord.eid == 'WarTest'
    assert nrecord.eid == 'WArTest'
    
    assert nrecord.iconPath == r'armor\1\trooperHelmMP.dds'
    assert nrecord.iconPath == r'Armor\1\trooperHelmMP.dds'
    assert nrecord.smallIconPath == r'armor\2\trooperHelm_n.dds'
    assert nrecord.smallIconPath == r'Armor\2\trooperHelm_n.dds'

    record = Current.LoadOrderMods[0].MICN[0]
    newrecord = record.CopyAsOverride(newMod)

    assert newrecord.fid == ('FalloutNV.esm', 0x174090)
    assert newrecord.flags1 == 0x80000000 #CBash sets 0x80000000 for internal use
    assert newrecord.versionControl1 == [16, 91, 22, 0]
    assert newrecord.formVersion == 15
    assert newrecord.versionControl2 == [1, 0]
    assert newrecord.eid == 'MenuIconFactionBrotherhood'
    assert newrecord.eid == 'MenuIconFActionBrotherhood'
    
    assert record.iconPath == r'interface\icons\message icons\glow_message_vaultboy_brotherhood.dds'
    assert record.iconPath == r'interface\icons\messAge icons\glow_message_vaultboy_brotherhood.dds'
    assert record.smallIconPath == None

    newrecord.flags1 = 10
    newrecord.versionControl1 = [1, 3, 2, 6]
    newrecord.formVersion = 1
    newrecord.versionControl2 = [2, 3]
    newrecord.eid = 'WarTest'
    
    newrecord.iconPath = r'armor\1\trooperHelmMP.dds'
    newrecord.smallIconPath = r'Armor\2\trooperHelm_n.dds'
    
    assert newrecord.fid == ('FalloutNV.esm', 0x174090)
    assert newrecord.flags1 == 0x80000000 | 10
    assert newrecord.versionControl1 == [1, 3, 2, 6]
    assert newrecord.formVersion == 1
    assert newrecord.versionControl2 == [2, 3]
    assert newrecord.eid == 'WarTest'
    assert newrecord.eid == 'WArTest'
    
    assert newrecord.iconPath == r'armor\1\trooperHelmMP.dds'
    assert newrecord.iconPath == r'Armor\1\trooperHelmMP.dds'
    assert newrecord.smallIconPath == r'armor\2\trooperHelm_n.dds'
    assert newrecord.smallIconPath == r'Armor\2\trooperHelm_n.dds'

    assert record.fid == ('FalloutNV.esm', 0x174090)
    assert record.flags1 == 0x80000000 #CBash sets 0x80000000 for internal use
    assert record.versionControl1 == [16, 91, 22, 0]
    assert record.formVersion == 15
    assert record.versionControl2 == [1, 0]
    assert record.eid == 'MenuIconFactionBrotherhood'
    assert record.eid == 'MenuIconFActionBrotherhood'
    
    assert record.iconPath == r'interface\icons\message icons\glow_message_vaultboy_brotherhood.dds'
    assert record.iconPath == r'interface\icons\messAge icons\glow_message_vaultboy_brotherhood.dds'
    assert record.smallIconPath == None

    print "MICN:Finished testing"

def assertGLOB(Current, newMod):
    record = Current.LoadOrderMods[0].GLOB[0]
    
    assert record.fid == ('FalloutNV.esm', 0x179B16)
    assert record.flags1 == 0x80000040 #CBash sets 0x80000000 for internal use
    assert record.versionControl1 == [5, 92, 71, 0]
    assert record.formVersion == 15
    assert record.versionControl2 == [0, 0]
    assert record.eid == 'EuclidPointerRange'
    assert record.eid == 'EuclidPointerRAnge'
    
    assert record.format == r'l'
    assert record.value == 12000.0
    
    nrecord = newMod.create_GLOB()

    nrecord.flags1 = 10
    nrecord.versionControl1 = [1, 3, 2, 6]
    nrecord.formVersion = 1
    nrecord.versionControl2 = [2, 3]
    nrecord.eid = 'WarTest'
    
    nrecord.format = r'l'
    nrecord.value = 10000
    
    assert nrecord.fid == ('RegressionTests.esp', 0x001007)
    assert nrecord.flags1 == 0x80000000 | 10
    assert nrecord.versionControl1 == [1, 3, 2, 6]
    assert nrecord.formVersion == 1
    assert nrecord.versionControl2 == [2, 3]
    assert nrecord.eid == 'WarTest'
    assert nrecord.eid == 'WArTest'
    
    assert nrecord.format == r'l'
    assert nrecord.value == 10000

    record = Current.LoadOrderMods[0].GLOB[0]
    newrecord = record.CopyAsOverride(newMod)
    
    assert newrecord.fid == ('FalloutNV.esm', 0x179B16)
    assert newrecord.flags1 == 0x80000040 #CBash sets 0x80000000 for internal use
    assert newrecord.versionControl1 == [5, 92, 71, 0]
    assert newrecord.formVersion == 15
    assert newrecord.versionControl2 == [0, 0]
    assert newrecord.eid == 'EuclidPointerRange'
    assert newrecord.eid == 'EuclidPointerRAnge'
    
    assert newrecord.format == r'l'
    assert newrecord.value == 12000.0

    newrecord.flags1 = 10
    newrecord.versionControl1 = [1, 3, 2, 6]
    newrecord.formVersion = 1
    newrecord.versionControl2 = [2, 3]
    newrecord.eid = 'WarTest'
    
    newrecord.format = r'l'
    newrecord.value = 11000
    
    assert newrecord.fid == ('FalloutNV.esm', 0x179B16)
    assert newrecord.flags1 == 0x80000000 | 10
    assert newrecord.versionControl1 == [1, 3, 2, 6]
    assert newrecord.formVersion == 1
    assert newrecord.versionControl2 == [2, 3]
    assert newrecord.eid == 'WarTest'
    assert newrecord.eid == 'WArTest'
    
    assert newrecord.format == r'l'
    assert newrecord.value == 11000

    assert record.fid == ('FalloutNV.esm', 0x179B16)
    assert record.flags1 == 0x80000040 #CBash sets 0x80000000 for internal use
    assert record.versionControl1 == [5, 92, 71, 0]
    assert record.formVersion == 15
    assert record.versionControl2 == [0, 0]
    assert record.eid == 'EuclidPointerRange'
    assert record.eid == 'EuclidPointerRAnge'
    
    assert record.format == r'l'
    assert record.value == 12000.0

    print "GLOB:Finished testing"

def assertCLAS(Current, newMod):
    record = Current.LoadOrderMods[0].CLAS[0]

    assert record.fid == ('FalloutNV.esm', 0x17A636)
    assert record.flags1 == 0x80000000 #CBash sets 0x80000000 for internal use
    assert record.versionControl1 == [8, 92, 57, 0]
    assert record.formVersion == 15
    assert record.versionControl2 == [1, 0]
    assert record.eid == 'LegionaryBadAss'
    assert record.eid == 'LegionaryBAdAss'
    
    assert record.full == 'Legate'
    assert record.full != 'LegAte'
    assert record.description == None
    assert record.iconPath == None
    assert record.smallIconPath == None
    assert record.tagSkills1 == 38
    assert record.tagSkills2 == 41
    assert record.tagSkills3 == 45
    assert record.tagSkills4 == -1
    assert record.flags == 0x0L
    assert record.services == 0x0L
    assert record.trainSkill == 0
    assert record.trainLevel == 0
    assert record.strength == 9
    assert record.perception == 8
    assert record.endurance == 8
    assert record.charisma == 7
    assert record.intelligence == 6
    assert record.agility == 7
    assert record.luck == 7
    
    nrecord = newMod.create_CLAS()

    nrecord.flags1 = 10
    nrecord.versionControl1 = [1, 3, 2, 6]
    nrecord.formVersion = 1
    nrecord.versionControl2 = [2, 3]
    nrecord.eid = 'WarTest'
    
    nrecord.full = 'WarLegate'
    nrecord.description = 'WarDesc'
    nrecord.iconPath = 'WarPath'
    nrecord.smallIconPath = 'WarSPath'
    nrecord.tagSkills1 = 1
    nrecord.tagSkills2 = 2
    nrecord.tagSkills3 = 3
    nrecord.tagSkills4 = 4
    nrecord.flags = 5
    nrecord.services = 6
    nrecord.trainSkill = 7
    nrecord.trainLevel = 8
    nrecord.strength = 9
    nrecord.perception = 10
    nrecord.endurance = 11
    nrecord.charisma = 12
    nrecord.intelligence = 13
    nrecord.agility = 14
    nrecord.luck = 15
    
    assert nrecord.fid == ('RegressionTests.esp', 0x001008)
    assert nrecord.flags1 == 0x80000000 | 10
    assert nrecord.versionControl1 == [1, 3, 2, 6]
    assert nrecord.formVersion == 1
    assert nrecord.versionControl2 == [2, 3]
    assert nrecord.eid == 'WarTest'
    assert nrecord.eid == 'WArTest'
    
    assert nrecord.full == 'WarLegate'
    assert nrecord.full != 'WArLegate'
    assert nrecord.description == 'WarDesc'
    assert nrecord.description != 'WArDesc'
    assert nrecord.iconPath == 'WarPath'
    assert nrecord.iconPath == 'WArPath'
    assert nrecord.smallIconPath == 'WarSPath'
    assert nrecord.smallIconPath == 'WArSPath'
    assert nrecord.tagSkills1 == 1
    assert nrecord.tagSkills2 == 2
    assert nrecord.tagSkills3 == 3
    assert nrecord.tagSkills4 == 4
    assert nrecord.flags == 5
    assert nrecord.services == 6
    assert nrecord.trainSkill == 7
    assert nrecord.trainLevel == 8
    assert nrecord.strength == 9
    assert nrecord.perception == 10
    assert nrecord.endurance == 11
    assert nrecord.charisma == 12
    assert nrecord.intelligence == 13
    assert nrecord.agility == 14
    assert nrecord.luck == 15

    record = Current.LoadOrderMods[0].CLAS[0]
    newrecord = record.CopyAsOverride(newMod)
    
    assert newrecord.fid == ('FalloutNV.esm', 0x17A636)
    assert newrecord.flags1 == 0x80000000 #CBash sets 0x80000000 for internal use
    assert newrecord.versionControl1 == [8, 92, 57, 0]
    assert newrecord.formVersion == 15
    assert newrecord.versionControl2 == [1, 0]
    assert newrecord.eid == 'LegionaryBadAss'
    assert newrecord.eid == 'LegionaryBAdAss'
    
    assert newrecord.full == 'Legate'
    assert newrecord.full != 'LegAte'
    assert newrecord.description == None
    assert newrecord.iconPath == None
    assert newrecord.smallIconPath == None
    assert newrecord.tagSkills1 == 38
    assert newrecord.tagSkills2 == 41
    assert newrecord.tagSkills3 == 45
    assert newrecord.tagSkills4 == -1
    assert newrecord.flags == 0x0L
    assert newrecord.services == 0x0L
    assert newrecord.trainSkill == 0
    assert newrecord.trainLevel == 0
    assert newrecord.strength == 9
    assert newrecord.perception == 8
    assert newrecord.endurance == 8
    assert newrecord.charisma == 7
    assert newrecord.intelligence == 6
    assert newrecord.agility == 7
    assert newrecord.luck == 7

    newrecord.flags1 = 10
    newrecord.versionControl1 = [1, 3, 2, 6]
    newrecord.formVersion = 1
    newrecord.versionControl2 = [2, 3]
    newrecord.eid = 'WarTest'
    
    newrecord.full = 'WarLegate'
    newrecord.description = 'WarDesc'
    newrecord.iconPath = 'WarPath'
    newrecord.smallIconPath = 'WarSPath'
    newrecord.tagSkills1 = 1
    newrecord.tagSkills2 = 2
    newrecord.tagSkills3 = 3
    newrecord.tagSkills4 = 4
    newrecord.flags = 5
    newrecord.services = 6
    newrecord.trainSkill = 7
    newrecord.trainLevel = 8
    newrecord.strength = 9
    newrecord.perception = 10
    newrecord.endurance = 11
    newrecord.charisma = 12
    newrecord.intelligence = 13
    newrecord.agility = 14
    newrecord.luck = 15
    
    assert newrecord.fid == ('FalloutNV.esm', 0x17A636)
    assert newrecord.flags1 == 0x80000000 | 10
    assert newrecord.versionControl1 == [1, 3, 2, 6]
    assert newrecord.formVersion == 1
    assert newrecord.versionControl2 == [2, 3]
    assert newrecord.eid == 'WarTest'
    assert newrecord.eid == 'WArTest'
    
    assert newrecord.full == 'WarLegate'
    assert newrecord.full != 'WArLegate'
    assert newrecord.description == 'WarDesc'
    assert newrecord.description != 'WArDesc'
    assert newrecord.iconPath == 'WarPath'
    assert newrecord.iconPath == 'WArPath'
    assert newrecord.smallIconPath == 'WarSPath'
    assert newrecord.smallIconPath == 'WArSPath'
    assert newrecord.tagSkills1 == 1
    assert newrecord.tagSkills2 == 2
    assert newrecord.tagSkills3 == 3
    assert newrecord.tagSkills4 == 4
    assert newrecord.flags == 5
    assert newrecord.services == 6
    assert newrecord.trainSkill == 7
    assert newrecord.trainLevel == 8
    assert newrecord.strength == 9
    assert newrecord.perception == 10
    assert newrecord.endurance == 11
    assert newrecord.charisma == 12
    assert newrecord.intelligence == 13
    assert newrecord.agility == 14
    assert newrecord.luck == 15

    assert record.fid == ('FalloutNV.esm', 0x17A636)
    assert record.flags1 == 0x80000000 #CBash sets 0x80000000 for internal use
    assert record.versionControl1 == [8, 92, 57, 0]
    assert record.formVersion == 15
    assert record.versionControl2 == [1, 0]
    assert record.eid == 'LegionaryBadAss'
    assert record.eid == 'LegionaryBAdAss'
    
    assert record.full == 'Legate'
    assert record.full != 'LegAte'
    assert record.description == None
    assert record.iconPath == None
    assert record.smallIconPath == None
    assert record.tagSkills1 == 38
    assert record.tagSkills2 == 41
    assert record.tagSkills3 == 45
    assert record.tagSkills4 == -1
    assert record.flags == 0x0L
    assert record.services == 0x0L
    assert record.trainSkill == 0
    assert record.trainLevel == 0
    assert record.strength == 9
    assert record.perception == 8
    assert record.endurance == 8
    assert record.charisma == 7
    assert record.intelligence == 6
    assert record.agility == 7
    assert record.luck == 7

    print "CLAS:Finished testing"

def assertFACT(Current, newMod):
    record = Current.LoadOrderMods[0].LookupRecord(0x1D3FE)

    assert record.fid == ('FalloutNV.esm', 0x01D3FE)
    assert record.flags1 == 0x80000000L
    assert record.versionControl1 == [10, 92, 2, 0]
    assert record.formVersion == 15
    assert record.versionControl2 == [7, 0]
    assert record.eid == 'BrotherhoodSteelFaction'
    assert record.eid == 'BrOtherhoodSteelFaction'
    
    assert record.full == 'Brotherhood of Steel'
    assert record.full != 'Brotherhood Of Steel'
    assert record.relations_list == [(('FalloutNV.esm', 1264455), -100, 1L), (('FalloutNV.esm', 1530450), 0, 1L),
                                     (('FalloutNV.esm', 111268), 0, 1L), (('FalloutNV.esm', 266421), 0, 2L),
                                     (('FalloutNV.esm', 1469262), 0, 2L), (('FalloutNV.esm', 103314), 0,2L),
                                     (('FalloutNV.esm', 591630), 0, 3L), (('FalloutNV.esm', 559885), 0, 2L),
                                     (('FalloutNV.esm', 96729), 0, 3L), (('FalloutNV.esm', 96747), 0, 3L),
                                     (('FalloutNV.esm', 1317537), 0, 2L), (('FalloutNV.esm', 1355838), 0, 2L),
                                     (('FalloutNV.esm',197906), 0, 2L), (('FalloutNV.esm', 673511), 0, 0L),
                                     (('FalloutNV.esm', 119275), -100, 0L), (('FalloutNV.esm', 119806),100, 2L)]
    assert record.flags == 0x100
    assert record.crimeGoldMultiplier == None
    assert record.ranks_list == [(0, 'Squire', None, None), (1, 'Knight', None, None), (2, 'Knight Sergeant', None, None),
                                 (3, 'Knight Captain', None, None), (4, 'Paladin', None, None),
                                 (5, 'Star Paladin', None, None), (6, 'Sentinel', None, None), (7, 'Elder', None, None)]
    assert record.reputation == ('FalloutNV.esm', 0x11E662)

    nrecord = newMod.create_FACT()

    nrecord.flags1 = 10
    nrecord.versionControl1 = [1, 3, 2, 6]
    nrecord.formVersion = 1
    nrecord.versionControl2 = [2, 3]
    nrecord.eid = 'WarTest'
    
    nrecord.full = 'WarBrotherhood of Steel'
    nrecord.relations_list = [(('FalloutNV.esm', 1), -2, 0L), (('FalloutNV.esm', 3), 4, 1L), (('FalloutNV.esm', 5), 6, 2L), (('FalloutNV.esm', 7), 8, 3L), (('FalloutNV.esm', 9), 10, 4L), (('FalloutNV.esm', 11), 12,0L), (('FalloutNV.esm', 13), 0, 1L)]
    nrecord.flags = 4
    nrecord.crimeGoldMultiplier = 5.0
    nrecord.ranks_list = [(1, 'WarSquire', None, 'Wart'), (0, 'WarKnight', None, None), (2, 'WarKnight Sergeant', None, None), (3, 'WarKnight Captain', None, None), (4, 'WarPaladin', None, None)]
    nrecord.reputation = ('FalloutNV.esm', 6)

    assert nrecord.fid == ('RegressionTests.esp', 0x001009)
    assert nrecord.flags1 == 0x80000000 | 10
    assert nrecord.versionControl1 == [1, 3, 2, 6]
    assert nrecord.formVersion == 1
    assert nrecord.versionControl2 == [2, 3]
    assert nrecord.eid == 'WarTest'
    assert nrecord.eid == 'WArTest'
    
    assert nrecord.full == 'WarBrotherhood of Steel'
    assert nrecord.relations_list == [(('FalloutNV.esm', 1), -2, 0L), (('FalloutNV.esm', 3), 4, 1L), (('FalloutNV.esm', 5), 6, 2L), (('FalloutNV.esm', 7), 8, 3L), (('FalloutNV.esm', 9), 10, 4L), (('FalloutNV.esm', 11), 12,0L), (('FalloutNV.esm', 13), 0, 1L)]
    assert nrecord.flags == 4
    assert nrecord.crimeGoldMultiplier == 5.0
    assert nrecord.ranks_list == [(1, 'WarSquire', None, 'Wart'), (0, 'WarKnight', None, None), (2, 'WarKnight Sergeant', None, None), (3, 'WarKnight Captain', None, None), (4, 'WarPaladin', None, None)]
    assert nrecord.reputation == ('FalloutNV.esm', 6)

    relation = nrecord.create_relation()
    relation.faction = ('RegressionTests.esp', 0x001009)
    relation.mod = 3
    relation.groupReactionType = 2
    
    assert nrecord.relations_list == [(('FalloutNV.esm', 1), -2, 0L), (('FalloutNV.esm', 3), 4, 1L), (('FalloutNV.esm', 5), 6, 2L), (('FalloutNV.esm', 7), 8, 3L), (('FalloutNV.esm', 9), 10, 4L), (('FalloutNV.esm', 11), 12,0L), (('FalloutNV.esm', 13), 0, 1L), (('RegressionTests.esp', 0x001009), 3, 2)]

    relation = nrecord.create_rank()
    relation.rank = 12
    relation.male = r'WarMALE'
    relation.female = r'WarFEMALE'
    relation.insigniaPath = r'War\path\Test'

    assert nrecord.ranks_list == [(1, 'WarSquire', None, 'Wart'), (0, 'WarKnight', None, None), (2, 'WarKnight Sergeant', None, None), (3, 'WarKnight Captain', None, None), (4, 'WarPaladin', None, None), (12, 'WarMALE', 'WarFEMALE', r'War\path\Test')]

    record = Current.LoadOrderMods[0].LookupRecord(0x1D3FE)
    newrecord = record.CopyAsOverride(newMod)
    
    assert newrecord.fid == ('FalloutNV.esm', 0x01D3FE)
    assert newrecord.flags1 == 0x80000000L
    assert newrecord.versionControl1 == [10, 92, 2, 0]
    assert newrecord.formVersion == 15
    assert newrecord.versionControl2 == [7, 0]
    assert newrecord.eid == 'BrotherhoodSteelFaction'
    assert newrecord.eid == 'BrOtherhoodSteelFaction'
    
    assert newrecord.full == 'Brotherhood of Steel'
    assert newrecord.full != 'Brotherhood Of Steel'
    assert newrecord.relations_list == [(('FalloutNV.esm', 1264455), -100, 1L), (('FalloutNV.esm', 1530450), 0, 1L),
                                     (('FalloutNV.esm', 111268), 0, 1L), (('FalloutNV.esm', 266421), 0, 2L),
                                     (('FalloutNV.esm', 1469262), 0, 2L), (('FalloutNV.esm', 103314), 0,2L),
                                     (('FalloutNV.esm', 591630), 0, 3L), (('FalloutNV.esm', 559885), 0, 2L),
                                     (('FalloutNV.esm', 96729), 0, 3L), (('FalloutNV.esm', 96747), 0, 3L),
                                     (('FalloutNV.esm', 1317537), 0, 2L), (('FalloutNV.esm', 1355838), 0, 2L),
                                     (('FalloutNV.esm',197906), 0, 2L), (('FalloutNV.esm', 673511), 0, 0L),
                                     (('FalloutNV.esm', 119275), -100, 0L), (('FalloutNV.esm', 119806),100, 2L)]
    assert newrecord.flags == 0x100
    assert newrecord.crimeGoldMultiplier == None
    assert newrecord.ranks_list == [(0, 'Squire', None, None), (1, 'Knight', None, None), (2, 'Knight Sergeant', None, None),
                                 (3, 'Knight Captain', None, None), (4, 'Paladin', None, None),
                                 (5, 'Star Paladin', None, None), (6, 'Sentinel', None, None), (7, 'Elder', None, None)]
    assert newrecord.reputation == ('FalloutNV.esm', 0x11E662)

    newrecord.flags1 = 10
    newrecord.versionControl1 = [1, 3, 2, 6]
    newrecord.formVersion = 1
    newrecord.versionControl2 = [2, 3]
    newrecord.eid = 'WarTest'
    
    newrecord.full = 'WarBrotherhood of Steel'
    newrecord.relations_list = [(('FalloutNV.esm', 1), -2, 0L), (('FalloutNV.esm', 3), 4, 1L), (('FalloutNV.esm', 5), 6, 2L), (('FalloutNV.esm', 7), 8, 3L), (('FalloutNV.esm', 9), 10, 4L), (('FalloutNV.esm', 11), 12,0L), (('FalloutNV.esm', 13), 0, 1L)]
    newrecord.flags = 4
    newrecord.crimeGoldMultiplier = 5.0
    newrecord.ranks_list = [(1, 'WarSquire', None, 'Wart'), (0, 'WarKnight', None, None), (2, 'WarKnight Sergeant', None, None), (3, 'WarKnight Captain', None, None), (4, 'WarPaladin', None, None)]
    newrecord.reputation = ('FalloutNV.esm', 6)
    
    assert newrecord.fid == ('FalloutNV.esm', 0x01D3FE)
    assert newrecord.flags1 == 0x80000000 | 10
    assert newrecord.versionControl1 == [1, 3, 2, 6]
    assert newrecord.formVersion == 1
    assert newrecord.versionControl2 == [2, 3]
    assert newrecord.eid == 'WarTest'
    assert newrecord.eid == 'WArTest'
    
    assert newrecord.flags1 == 0x80000000 | 10
    assert newrecord.versionControl1 == [1, 3, 2, 6]
    assert newrecord.formVersion == 1
    assert newrecord.versionControl2 == [2, 3]
    assert newrecord.eid == 'WarTest'
    assert newrecord.eid == 'WArTest'
    
    assert newrecord.full == 'WarBrotherhood of Steel'
    assert newrecord.relations_list == [(('FalloutNV.esm', 1), -2, 0L), (('FalloutNV.esm', 3), 4, 1L), (('FalloutNV.esm', 5), 6, 2L), (('FalloutNV.esm', 7), 8, 3L), (('FalloutNV.esm', 9), 10, 4L), (('FalloutNV.esm', 11), 12,0L), (('FalloutNV.esm', 13), 0, 1L)]
    assert newrecord.flags == 4
    assert newrecord.crimeGoldMultiplier == 5.0
    assert newrecord.ranks_list == [(1, 'WarSquire', None, 'Wart'), (0, 'WarKnight', None, None), (2, 'WarKnight Sergeant', None, None), (3, 'WarKnight Captain', None, None), (4, 'WarPaladin', None, None)]
    assert newrecord.reputation == ('FalloutNV.esm', 6)

    assert record.fid == ('FalloutNV.esm', 0x01D3FE)
    assert record.flags1 == 0x80000000L
    assert record.versionControl1 == [10, 92, 2, 0]
    assert record.formVersion == 15
    assert record.versionControl2 == [7, 0]
    assert record.eid == 'BrotherhoodSteelFaction'
    assert record.eid == 'BrOtherhoodSteelFaction'
    
    assert record.full == 'Brotherhood of Steel'
    assert record.full != 'Brotherhood Of Steel'
    assert record.relations_list == [(('FalloutNV.esm', 1264455), -100, 1L), (('FalloutNV.esm', 1530450), 0, 1L),
                                     (('FalloutNV.esm', 111268), 0, 1L), (('FalloutNV.esm', 266421), 0, 2L),
                                     (('FalloutNV.esm', 1469262), 0, 2L), (('FalloutNV.esm', 103314), 0,2L),
                                     (('FalloutNV.esm', 591630), 0, 3L), (('FalloutNV.esm', 559885), 0, 2L),
                                     (('FalloutNV.esm', 96729), 0, 3L), (('FalloutNV.esm', 96747), 0, 3L),
                                     (('FalloutNV.esm', 1317537), 0, 2L), (('FalloutNV.esm', 1355838), 0, 2L),
                                     (('FalloutNV.esm',197906), 0, 2L), (('FalloutNV.esm', 673511), 0, 0L),
                                     (('FalloutNV.esm', 119275), -100, 0L), (('FalloutNV.esm', 119806),100, 2L)]
    assert record.flags == 0x100
    assert record.crimeGoldMultiplier == None
    assert record.ranks_list == [(0, 'Squire', None, None), (1, 'Knight', None, None), (2, 'Knight Sergeant', None, None),
                                 (3, 'Knight Captain', None, None), (4, 'Paladin', None, None),
                                 (5, 'Star Paladin', None, None), (6, 'Sentinel', None, None), (7, 'Elder', None, None)]
    assert record.reputation == ('FalloutNV.esm', 0x11E662)

    print "FACT:Finished testing"

def assertHDPT(Current, newMod):
    record = Current.LoadOrderMods[0].LookupRecord(0x0BCBEF)

    assert record.fid == ('FalloutNV.esm', 0x0BCBEF)
    assert record.flags1 == 0x80000000
    assert record.versionControl1 == [5, 66, 39, 0]
    assert record.formVersion == 15
    assert record.versionControl2 == [3, 0]
    assert record.eid == r'BeardMustacheCurlyFull'
    assert record.eid == r'BeArdMustacheCurlyFull'
    
    assert record.full == r'The Comrade'
    assert record.full != r'ThE Comrade'
    assert record.modPath == r'Characters\Hair\BeardMustacheCurly.nif'
    assert record.modPath == r'ChAracters\Hair\BeardMustacheCurly.nif'
    assert record.modb == 0.0
    assert record.modt_p == [238, 236, 12, 98, 148, 160, 189, 156, 110, 108, 12, 98, 153, 160,
                             189, 156, 114, 105, 24, 116, 155, 242, 124, 224, 238, 223, 14, 98,
                             22, 68, 125, 197, 110, 95, 14, 98, 27, 68, 125, 197, 114, 105, 24,
                             116, 155, 242, 124, 224, 243, 223, 14, 98, 22, 68, 125, 197, 115,
                             95, 14, 98, 27, 68, 125, 197, 114, 105, 24, 116, 155, 242, 124, 224,
                             236, 232, 15, 98, 19, 164, 241, 216, 108, 104, 15, 98, 24, 164, 241,
                             216, 114, 105, 24, 116, 155, 242, 124, 224]
    assert record.altTextures_list == [('BeardMustacheCurly:0', ('FalloutNV.esm', 653607), -1),
                                       ('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)]
    assert record.modelFlags == 0x0
    assert record.flags == 0x1
    assert record.parts == []
    
    nrecord = newMod.create_HDPT()

    nrecord.flags1 = 10
    nrecord.versionControl1 = [1, 3, 2, 6]
    nrecord.formVersion = 1
    nrecord.versionControl2 = [2, 3]
    nrecord.eid = r'WarTest'
    
    nrecord.full = r'WarThe Comrade'
    nrecord.modPath = r'War\Hair\BeardMustacheCurly.nif'
    nrecord.modb = 1.2
    nrecord.modt_p = None
    nrecord.altTextures_list = [('BeardMustacheCurly:1', ('FalloutNV.esm', 653606), -2),
                                ('BeardMustacheCuRly:0', ('FalloutNV.esm', 653607), -1),
                                ('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)]
    nrecord.modelFlags = 0x01
    nrecord.flags = 0x2
    nrecord.parts = [('FalloutNV.esm', 653606)]
    
    assert nrecord.fid == ('RegressionTests.esp', 0x00100A)
    assert nrecord.flags1 == 0x80000000 | 10
    assert nrecord.versionControl1 == [1, 3, 2, 6]
    assert nrecord.formVersion == 1
    assert nrecord.versionControl2 == [2, 3]
    assert nrecord.eid == 'WarTest'
    assert nrecord.eid == 'WArTest'
    
    assert nrecord.full == r'WarThe Comrade'
    assert nrecord.full != r'WArThe Comrade'
    assert nrecord.modPath == r'War\Hair\BeardMustacheCurly.nif'
    assert nrecord.modPath == r'WAr\Hair\BeardMustacheCurly.nif'
    assert nrecord.modb == 1.2
    assert nrecord.modt_p == []
    assert nrecord.altTextures_list == [('BeardMustacheCurly:1', ('FalloutNV.esm', 653606), -2),
                                        ('BeardMustacheCuRly:0', ('FalloutNV.esm', 653607), -1),
                                        ('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)]
    assert nrecord.modelFlags == 0x01
    assert nrecord.flags == 0x2
    assert nrecord.parts == [('FalloutNV.esm', 653606)]

    altTexture = nrecord.create_altTexture()
    altTexture.name = r'WarTESTNAME'
    altTexture.texture = ('FalloutNV.esm', 653616)
    altTexture.index = 6

    assert nrecord.altTextures_list == [('BeardMustacheCurly:1', ('FalloutNV.esm', 653606), -2),
                                        ('BeardMustacheCuRly:0', ('FalloutNV.esm', 653607), -1),
                                        ('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0),
                                        ('WarTESTNAME', ('FalloutNV.esm', 653616), 6)]

    record = Current.LoadOrderMods[0].LookupRecord(0x0BCBEF)
    newrecord = record.CopyAsOverride(newMod)
    
    assert newrecord.fid == ('FalloutNV.esm', 0x0BCBEF)
    assert newrecord.flags1 == 0x80000000
    assert newrecord.versionControl1 == [5, 66, 39, 0]
    assert newrecord.formVersion == 15
    assert newrecord.versionControl2 == [3, 0]
    assert newrecord.eid == r'BeardMustacheCurlyFull'
    assert newrecord.eid == r'BeArdMustacheCurlyFull'
    
    assert newrecord.full == r'The Comrade'
    assert newrecord.full != r'ThE Comrade'
    assert newrecord.modPath == r'Characters\Hair\BeardMustacheCurly.nif'
    assert newrecord.modPath == r'ChAracters\Hair\BeardMustacheCurly.nif'
    assert newrecord.modb == 0.0
    assert newrecord.modt_p == [238, 236, 12, 98, 148, 160, 189, 156, 110, 108, 12, 98, 153,
                                160, 189, 156, 114, 105, 24, 116, 155, 242, 124, 224, 238,
                                223, 14, 98, 22, 68, 125, 197, 110, 95, 14, 98, 27, 68, 125,
                                197, 114, 105, 24, 116, 155, 242, 124, 224, 243, 223, 14, 98,
                                22, 68, 125, 197, 115, 95, 14, 98, 27, 68, 125, 197, 114,
                                105, 24, 116, 155, 242, 124, 224, 236, 232, 15, 98, 19, 164,
                                241, 216, 108, 104, 15, 98, 24, 164, 241, 216, 114, 105, 24,
                                116, 155, 242, 124, 224]
    assert newrecord.altTextures_list == [('BeardMustacheCurly:0', ('FalloutNV.esm', 653607), -1),
                                          ('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)]
    assert newrecord.modelFlags == 0x0
    assert newrecord.flags == 0x1
    assert newrecord.parts == []

    newrecord.flags1 = 10
    newrecord.versionControl1 = [1, 3, 2, 6]
    newrecord.formVersion = 1
    newrecord.versionControl2 = [2, 3]
    newrecord.eid = 'WarTest'
    
    newrecord.full = r'WarThe Comrade'
    newrecord.modPath = r'War\Hair\BeardMustacheCurly.nif'
    newrecord.modb = 1.2
    newrecord.modt_p = None
    newrecord.altTextures_list = [('BeardMustacheCurly:1', ('FalloutNV.esm', 653606), -2),
                                  ('BeardMustacheCuRly:0', ('FalloutNV.esm', 653607), -1),
                                  ('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)]
    newrecord.modelFlags = 0x01
    newrecord.flags = 0x2
    newrecord.parts = [('FalloutNV.esm', 653606)]
    
    assert newrecord.fid == ('FalloutNV.esm', 0x0BCBEF)
    assert newrecord.flags1 == 0x80000000 | 10
    assert newrecord.versionControl1 == [1, 3, 2, 6]
    assert newrecord.formVersion == 1
    assert newrecord.versionControl2 == [2, 3]
    assert newrecord.eid == 'WarTest'
    assert newrecord.eid == 'WArTest'
    
    assert newrecord.full == r'WarThe Comrade'
    assert newrecord.full != r'WArThe Comrade'
    assert newrecord.modPath == r'War\Hair\BeardMustacheCurly.nif'
    assert newrecord.modPath == r'WAr\Hair\BeardMustacheCurly.nif'
    assert newrecord.modb == 1.2
    assert newrecord.modt_p == []
    assert newrecord.altTextures_list == [('BeardMustacheCurly:1', ('FalloutNV.esm', 653606), -2),
                                          ('BeardMustacheCuRly:0', ('FalloutNV.esm', 653607), -1),
                                          ('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)]
    assert newrecord.modelFlags == 0x01
    assert newrecord.flags == 0x2
    assert newrecord.parts == [('FalloutNV.esm', 653606)]

    assert record.fid == ('FalloutNV.esm', 0x0BCBEF)
    assert record.flags1 == 0x80000000
    assert record.versionControl1 == [5, 66, 39, 0]
    assert record.formVersion == 15
    assert record.versionControl2 == [3, 0]
    assert record.eid == r'BeardMustacheCurlyFull'
    assert record.eid == r'BeArdMustacheCurlyFull'
    
    assert record.full == r'The Comrade'
    assert record.full != r'ThE Comrade'
    assert record.modPath == r'Characters\Hair\BeardMustacheCurly.nif'
    assert record.modPath == r'ChAracters\Hair\BeardMustacheCurly.nif'
    assert record.modb == 0.0
    assert record.modt_p == [238, 236, 12, 98, 148, 160, 189, 156, 110, 108, 12, 98, 153,
                             160, 189, 156, 114, 105, 24, 116, 155, 242, 124, 224, 238, 223,
                             14, 98, 22, 68, 125, 197, 110, 95, 14, 98, 27, 68, 125, 197,
                             114, 105, 24, 116, 155, 242, 124, 224, 243, 223, 14, 98, 22,
                             68, 125, 197, 115, 95, 14, 98, 27, 68, 125, 197, 114, 105, 24,
                             116, 155, 242, 124, 224, 236, 232, 15, 98, 19, 164, 241, 216,
                             108, 104, 15, 98, 24, 164, 241, 216, 114, 105, 24, 116, 155,
                             242, 124, 224]
    assert record.altTextures_list == [('BeardMustacheCurly:0', ('FalloutNV.esm', 653607), -1),
                                       ('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)]
    assert record.modelFlags == 0x0
    assert record.flags == 0x1
    assert record.parts == []

    print "HDPT:Finished testing"

def assertHAIR(Current, newMod):
    record = Current.LoadOrderMods[0].HAIR[0]

    assert record.fid == ('FalloutNV.esm', 0x05239D)
    assert record.flags1 == 0x80000000L
    assert record.versionControl1 == [5, 66, 39, 0]
    assert record.formVersion == 15
    assert record.versionControl2 == [2, 0]
    assert record.eid == r'HairFemaleCherry'
    assert record.eid == r'HAirFemaleCherry'
    
    assert record.full == r'Pretty Puff'
    assert record.full != r'PrEtty Puff'
    assert record.modPath == r'Characters\Hair\HairFemaleCherry.NIF'
    assert record.modPath == r'ChAracters\Hair\HairFemaleCherry.NIF'
    assert record.modb == 0.0
    assert record.modt_p == [249, 236, 15, 104, 106, 177, 7, 48, 121, 108, 15, 104, 111,
                             177, 7, 48, 114, 105, 24, 116, 155, 242, 124, 224, 238, 223,
                             17, 104, 247, 73, 32, 158, 110, 95, 17, 104, 252, 73, 32,
                             158, 114, 105, 24, 116, 155, 242, 124, 224, 243, 223, 17,
                             104, 247, 73, 32, 158, 115, 95, 17, 104, 252, 73, 32, 158,
                             114, 105, 24, 116, 155, 242, 124, 224, 236, 232, 18, 104,
                             114, 22, 241, 46, 108, 104, 18, 104, 119, 22, 241, 46, 114,
                             105, 24, 116, 155, 242, 124, 224]
    assert record.altTextures_list == []
    assert record.modelFlags == 0x0
    assert record.iconPath == r'Characters\Hair\HairChildMCurly.dds'
    assert record.iconPath == r'ChAracters\Hair\HairChildMCurly.dds'
    assert record.flags == 0x2
    
    nrecord = newMod.create_HAIR()

    nrecord.flags1 = 10
    nrecord.versionControl1 = [1, 3, 2, 6]
    nrecord.formVersion = 1
    nrecord.versionControl2 = [2, 3]
    nrecord.eid = r'WarTest'
    
    nrecord.full = r'WarPretty Puff'
    nrecord.modPath = r'War\Hair\HairFemaleCherry.NIF'
    nrecord.modb = 3.1
    nrecord.modt_p = [1, 236, 15]
    nrecord.altTextures_list = [('BeardMustacheCurly:1', ('FalloutNV.esm', 653606), -2),
                                ('BeardMustacheCuRly:0', ('FalloutNV.esm', 653607), -1),
                                ('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)]
    nrecord.modelFlags = 0x3
    nrecord.iconPath = r'War\Hair\HairChildMCurly.dds'
    nrecord.flags = 0x4
    
    assert nrecord.fid == ('RegressionTests.esp', 0x00100B)
    assert nrecord.flags1 == 0x80000000 | 10
    assert nrecord.versionControl1 == [1, 3, 2, 6]
    assert nrecord.formVersion == 1
    assert nrecord.versionControl2 == [2, 3]
    assert nrecord.eid == 'WarTest'
    assert nrecord.eid == 'WArTest'
    
    assert nrecord.full == r'WarPretty Puff'
    assert nrecord.full != r'WArPretty Puff'
    assert nrecord.modPath == r'War\Hair\HairFemaleCherry.NIF'
    assert nrecord.modPath == r'WAr\Hair\HairFemaleCherry.NIF'
    assert nrecord.modb == 3.1
    assert nrecord.modt_p == [1, 236, 15]
    assert nrecord.altTextures_list == [('BeardMustacheCurly:1', ('FalloutNV.esm', 653606), -2),
                                        ('BeardMustacheCuRly:0', ('FalloutNV.esm', 653607), -1),
                                        ('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)]
    assert nrecord.modelFlags == 0x3
    assert nrecord.iconPath == r'War\Hair\HairChildMCurly.dds'
    assert nrecord.iconPath == r'WAr\Hair\HairChildMCurly.dds'
    assert nrecord.flags == 0x4

    altTexture = nrecord.create_altTexture()
    altTexture.name = r'WarTESTNAME'
    altTexture.texture = ('FalloutNV.esm', 653616)
    altTexture.index = 6

    assert nrecord.altTextures_list == [('BeardMustacheCurly:1', ('FalloutNV.esm', 653606), -2),
                                        ('BeardMustacheCuRly:0', ('FalloutNV.esm', 653607), -1),
                                        ('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0),
                                        ('WarTESTNAME', ('FalloutNV.esm', 653616), 6)]

    record = Current.LoadOrderMods[0].HAIR[0]
    newrecord = record.CopyAsOverride(newMod)
    
    assert newrecord.fid == ('FalloutNV.esm', 0x05239D)
    assert newrecord.flags1 == 0x80000000L
    assert newrecord.versionControl1 == [5, 66, 39, 0]
    assert newrecord.formVersion == 15
    assert newrecord.versionControl2 == [2, 0]
    assert newrecord.eid == r'HairFemaleCherry'
    assert newrecord.eid == r'HAirFemaleCherry'
    
    assert newrecord.full == r'Pretty Puff'
    assert newrecord.full != r'PrEtty Puff'
    assert newrecord.modPath == r'Characters\Hair\HairFemaleCherry.NIF'
    assert newrecord.modPath == r'ChAracters\Hair\HairFemaleCherry.NIF'
    assert newrecord.modb == 0.0
    assert newrecord.modt_p == [249, 236, 15, 104, 106, 177, 7, 48, 121, 108, 15, 104, 111,
                                177, 7, 48, 114, 105, 24, 116, 155, 242, 124, 224, 238, 223,
                                17, 104, 247, 73, 32, 158, 110, 95, 17, 104, 252, 73, 32,
                                158, 114, 105, 24, 116, 155, 242, 124, 224, 243, 223, 17,
                                104, 247, 73, 32, 158, 115, 95, 17, 104, 252, 73, 32, 158,
                                114, 105, 24, 116, 155, 242, 124, 224, 236, 232, 18, 104,
                                114, 22, 241, 46, 108, 104, 18, 104, 119, 22, 241, 46, 114,
                                105, 24, 116, 155, 242, 124, 224]
    assert newrecord.altTextures_list == []
    assert newrecord.modelFlags == 0x0
    assert newrecord.iconPath == r'Characters\Hair\HairChildMCurly.dds'
    assert newrecord.iconPath == r'ChAracters\Hair\HairChildMCurly.dds'
    assert newrecord.flags == 0x2

    newrecord.flags1 = 10
    newrecord.versionControl1 = [1, 3, 2, 6]
    newrecord.formVersion = 1
    newrecord.versionControl2 = [2, 3]
    newrecord.eid = 'WarTest'
    
    newrecord.full = r'WarPretty Puff'
    newrecord.modPath = r'War\Hair\HairFemaleCherry.NIF'
    newrecord.modb = 3.1
    newrecord.modt_p = [1, 236, 15]
    newrecord.altTextures_list = [('BeardMustacheCurly:1', ('FalloutNV.esm', 653606), -2),
                                  ('BeardMustacheCuRly:0', ('FalloutNV.esm', 653607), -1),
                                  ('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)]
    newrecord.modelFlags = 0x3
    newrecord.iconPath = r'War\Hair\HairChildMCurly.dds'
    newrecord.flags = 0x4
    
    assert newrecord.fid == ('FalloutNV.esm', 0x05239D)
    assert newrecord.flags1 == 0x80000000 | 10
    assert newrecord.versionControl1 == [1, 3, 2, 6]
    assert newrecord.formVersion == 1
    assert newrecord.versionControl2 == [2, 3]
    assert newrecord.eid == 'WarTest'
    assert newrecord.eid == 'WArTest'
    
    assert newrecord.full == r'WarPretty Puff'
    assert newrecord.full != r'WArPretty Puff'
    assert newrecord.modPath == r'War\Hair\HairFemaleCherry.NIF'
    assert newrecord.modPath == r'WAr\Hair\HairFemaleCherry.NIF'
    assert newrecord.modb == 3.1
    assert newrecord.modt_p == [1, 236, 15]
    assert newrecord.altTextures_list == [('BeardMustacheCurly:1', ('FalloutNV.esm', 653606), -2),
                                          ('BeardMustacheCuRly:0', ('FalloutNV.esm', 653607), -1),
                                          ('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)]
    assert newrecord.modelFlags == 0x3
    assert newrecord.iconPath == r'War\Hair\HairChildMCurly.dds'
    assert newrecord.iconPath == r'WAr\Hair\HairChildMCurly.dds'
    assert newrecord.flags == 0x4

    assert record.fid == ('FalloutNV.esm', 0x05239D)
    assert record.flags1 == 0x80000000L
    assert record.versionControl1 == [5, 66, 39, 0]
    assert record.formVersion == 15
    assert record.versionControl2 == [2, 0]
    assert record.eid == r'HairFemaleCherry'
    assert record.eid == r'HAirFemaleCherry'
    
    assert record.full == r'Pretty Puff'
    assert record.full != r'PrEtty Puff'
    assert record.modPath == r'Characters\Hair\HairFemaleCherry.NIF'
    assert record.modPath == r'ChAracters\Hair\HairFemaleCherry.NIF'
    assert record.modb == 0.0
    assert record.modt_p == [249, 236, 15, 104, 106, 177, 7, 48, 121, 108, 15, 104, 111, 177, 7,
                             48, 114, 105, 24, 116, 155, 242, 124, 224, 238, 223, 17, 104, 247,
                             73, 32, 158, 110, 95, 17, 104, 252, 73, 32, 158, 114, 105, 24, 116,
                             155, 242, 124, 224, 243, 223, 17, 104, 247, 73, 32, 158, 115, 95,
                             17, 104, 252, 73, 32, 158, 114, 105, 24, 116, 155, 242, 124, 224,
                             236, 232, 18, 104, 114, 22, 241, 46, 108, 104, 18, 104, 119, 22,
                             241, 46, 114, 105, 24, 116, 155, 242, 124, 224]
    assert record.altTextures_list == []
    assert record.modelFlags == 0x0
    assert record.iconPath == r'Characters\Hair\HairChildMCurly.dds'
    assert record.iconPath == r'ChAracters\Hair\HairChildMCurly.dds'
    assert record.flags == 0x2

    print "HAIR:Finished testing"

def assertEYES(Current, newMod):
    record = Current.LoadOrderMods[0].EYES[0]

    assert record.fid == ('FalloutNV.esm', 0x0945BA)
    assert record.flags1 == 0x80000000L
    assert record.versionControl1 == [9, 76, 1, 0]
    assert record.formVersion == 15
    assert record.versionControl2 == [0, 0]
    assert record.eid == 'DLCPittEyeGreenMut'
    assert record.eid == 'DLCPittEyEGreenMut'
    
    assert record.full == 'Green'
    assert record.full != 'GreEn'
    assert record.iconPath == r'Characters\Eyes\EyeGreenMutantHuman.dds'
    assert record.iconPath == r'ChAracters\Eyes\EyeGreenMutantHuman.dds'
    assert record.flags == 0x0
    
    nrecord = newMod.create_EYES()

    nrecord.flags1 = 10
    nrecord.versionControl1 = [1, 3, 2, 6]
    nrecord.formVersion = 1
    nrecord.versionControl2 = [2, 3]
    nrecord.eid = r'WarTest'
    
    nrecord.full = 'Green'
    nrecord.iconPath = r'Characters\Eyes\EyeGreenMutantHuman.dds'
    nrecord.flags = 0x0
    
    assert nrecord.fid == ('RegressionTests.esp', 0x00100C)
    assert nrecord.flags1 == 0x80000000 | 10
    assert nrecord.versionControl1 == [1, 3, 2, 6]
    assert nrecord.formVersion == 1
    assert nrecord.versionControl2 == [2, 3]
    assert nrecord.eid == 'WarTest'
    assert nrecord.eid == 'WArTest'
    
    assert nrecord.full == 'Green'
    assert nrecord.full != 'GrEen'
    assert nrecord.iconPath == r'Characters\Eyes\EyeGreenMutantHuman.dds'
    assert nrecord.iconPath == r'ChAracters\Eyes\EyeGreenMutantHuman.dds'
    assert nrecord.flags == 0x0

    record = Current.LoadOrderMods[0].EYES[0]
    newrecord = record.CopyAsOverride(newMod)

    assert newrecord.fid == ('FalloutNV.esm', 0x0945BA)
    assert newrecord.flags1 == 0x80000000L
    assert newrecord.versionControl1 == [9, 76, 1, 0]
    assert newrecord.formVersion == 15
    assert newrecord.versionControl2 == [0, 0]
    assert newrecord.eid == 'DLCPittEyeGreenMut'
    assert newrecord.eid == 'DLCPittEyEGreenMut'
    
    assert newrecord.full == 'Green'
    assert newrecord.full != 'GreEn'
    assert newrecord.iconPath == r'Characters\Eyes\EyeGreenMutantHuman.dds'
    assert newrecord.iconPath == r'ChAracters\Eyes\EyeGreenMutantHuman.dds'
    assert newrecord.flags == 0x0

    newrecord.flags1 = 10
    newrecord.versionControl1 = [1, 3, 2, 6]
    newrecord.formVersion = 1
    newrecord.versionControl2 = [2, 3]
    newrecord.eid = 'WarTest'
    
    newrecord.full = 'Green'
    newrecord.iconPath = r'Characters\Eyes\EyeGreenMutantHuman.dds'
    newrecord.flags = 0x0
    
    assert newrecord.fid == ('FalloutNV.esm', 0x0945BA)
    assert newrecord.flags1 == 0x80000000 | 10
    assert newrecord.versionControl1 == [1, 3, 2, 6]
    assert newrecord.formVersion == 1
    assert newrecord.versionControl2 == [2, 3]
    assert newrecord.eid == 'WarTest'
    assert newrecord.eid == 'WArTest'
    
    assert newrecord.full == 'Green'
    assert newrecord.full != 'GrEen'
    assert newrecord.iconPath == r'Characters\Eyes\EyeGreenMutantHuman.dds'
    assert newrecord.iconPath == r'ChAracters\Eyes\EyeGreenMutantHuman.dds'
    assert newrecord.flags == 0x0

    assert record.fid == ('FalloutNV.esm', 0x0945BA)
    assert record.flags1 == 0x80000000L
    assert record.versionControl1 == [9, 76, 1, 0]
    assert record.formVersion == 15
    assert record.versionControl2 == [0, 0]
    assert record.eid == 'DLCPittEyeGreenMut'
    assert record.eid == 'DLCPittEyEGreenMut'
    
    assert record.full == 'Green'
    assert record.full != 'GreEn'
    assert record.iconPath == r'Characters\Eyes\EyeGreenMutantHuman.dds'
    assert record.iconPath == r'ChAracters\Eyes\EyeGreenMutantHuman.dds'
    assert record.flags == 0x0

    print "EYES:Finished testing"

def assertRACE(Current, newMod):
    record = Current.LoadOrderMods[0].RACE[0]

    assert record.fid == ('FalloutNV.esm', 0x0987DF)
    assert record.flags1 == 0x80000000L
    assert record.versionControl1 == [16, 66, 39, 0]
    assert record.formVersion == 15
    assert record.versionControl2 == [5, 0]
    assert record.eid == 'CaucasianOldAged'
    assert record.eid == 'CAucasianOldAged'
    
    assert record.full == 'Caucasian Old'
    assert record.full != 'CAucasian Old'
    assert record.description == None
    assert record.relations_list == []
    assert record.skill1 == -1
    assert record.skill1Boost == 0
    assert record.skill2 == -1
    assert record.skill2Boost == 0
    assert record.skill3 == -1
    assert record.skill3Boost == 0
    assert record.skill4 == -1
    assert record.skill4Boost == 0
    assert record.skill5 == -1
    assert record.skill5Boost == 0
    assert record.skill6 == -1
    assert record.skill6Boost == 0
    assert record.skill7 == -1
    assert record.skill7Boost == 0
    assert record.maleHeight == 1.0
    assert record.femaleHeight == 1.0
    assert record.maleWeight == 1.0
    assert record.femaleWeight == 1.0
    assert record.flags == 0x0L
    assert record.older == None
    assert record.younger == ('FalloutNV.esm', 0x000019)
    assert record.maleVoice == ('FalloutNV.esm', 0x019FD2)
    assert record.femaleVoice == ('FalloutNV.esm', 0x00002E)
    assert record.defaultHairMale == ('FalloutNV.esm', 0x0987DA)
    assert record.defaultHairFemale == ('FalloutNV.esm', 0x044529)
    assert record.defaultHairMaleColor == 1
    assert record.defaultHairFemaleColor == 1
    assert record.mainClamp == 5.0
    assert record.faceClamp == 3.0
    assert record.attr_p == [5, 5]
    assert record.maleHead_list == ('Characters\\Head\\HeadOld.NIF', None,
                                    [238, 225, 9, 104, 61, 251, 66, 106, 110, 97, 9,
                                     104, 66, 251, 66, 106, 101, 108, 24, 116, 214,
                                     243, 129, 224, 238, 223, 11, 104, 138, 215, 34,
                                     197, 110, 95, 11, 104, 143, 215, 34, 197, 101,
                                     108, 24, 116, 214, 243, 129, 224, 243, 223, 11,
                                     104, 138, 215, 34, 197, 115, 95, 11, 104, 143,
                                     215, 34, 197, 101, 108, 24, 116, 214, 243, 129,
                                     224, 235, 243, 12, 104, 159, 237, 36, 86, 107,
                                     115, 12, 104, 164, 237, 36, 86, 101, 108, 24,
                                     116, 214, 243, 129, 224],
                                    [], 2, 'Characters\\Old\\HeadHuman.dds', None)
    assert record.maleEars_list == (None, None, [], [], None, 'Characters\\Head\\EarsHuman.dds', None)
    assert record.maleMouth_list == ('Characters\\Head\\MouthHuman.NIF', None,
                                     [238, 225, 10, 109, 43, 201, 76, 110, 110, 97,
                                      10, 109, 48, 201, 76, 110, 104, 116, 25, 116,
                                      145, 5, 223, 51, 238, 223, 6, 102, 132, 76, 107,
                                      195, 110, 95, 6, 102, 137, 76, 107, 195, 100, 101,
                                      15, 116, 246, 82, 111, 175, 243, 223, 6, 102, 132,
                                      76, 107, 195, 115, 95, 6, 102, 137, 76, 107, 195,
                                      100, 101, 15, 116, 246, 82, 111, 175],
                                     [], None, 'Characters\\Mouth\\MouthHuman.dds', None)
    assert record.maleTeethLower_list == ('Characters\\Head\\TeethLowerHuman.NIF', None,
                                          [238, 225, 15, 116, 216, 76, 118, 0, 110,97, 15,
                                           116, 221, 76, 118, 0, 104, 116, 25, 116, 145, 5,
                                           223, 51, 238, 223, 6, 102, 132, 76, 107, 195, 110,
                                           95, 6, 102,137, 76, 107, 195, 100, 101, 15, 116,
                                           246, 82, 111, 175, 243, 223, 6, 102, 132, 76, 107,
                                           195, 115, 95, 6, 102, 137, 76,107, 195, 100, 101,
                                           15, 116, 246, 82, 111, 175],
                                          [], None, 'Characters\\Mouth\\TeethLowerRaider.dds', None)
    assert record.maleTeethUpper_list == ('Characters\\Head\\TeethUpperHuman.NIF', None,
                                          [238, 225, 15, 116, 87, 210, 9, 247, 110,97, 15,
                                           116, 92, 210, 9, 247, 104, 116, 25, 116, 145, 5,
                                           223, 51, 238, 223, 6, 102, 132, 76, 107, 195, 110,
                                           95, 6, 102,137, 76, 107, 195, 100, 101, 15, 116,
                                           246, 82, 111, 175, 243, 223, 6, 102, 132, 76, 107,
                                           195, 115, 95, 6, 102, 137, 76,107, 195, 100, 101,
                                           15, 116, 246, 82, 111, 175],
                                          [], None, 'Characters\\Mouth\\TeethUpperRaider.dds', None)
    assert record.maleTongue_list == ('Characters\\Head\\TongueHuman.NIF', None,
                                      [238, 225, 11, 116, 205, 135, 184, 206, 110, 97, 11, 116,
                                       210, 135, 184, 206, 104, 116, 25, 116, 145, 5, 223, 51,
                                       238, 223, 6, 102, 132, 76, 107, 195, 110, 95, 6, 102,
                                       137, 76, 107, 195, 100, 101, 15, 116, 246, 82, 111, 175,
                                       243, 223, 6, 102, 132, 76, 107, 195, 115, 95, 6, 102,
                                       137, 76, 107, 195, 100, 101, 15, 116, 246, 82, 111, 175],
                                      [], None, 'Characters\\Mouth\\TongueRaider.dds', None)
    assert record.maleLeftEye_list == ('Characters\\Head\\EyeLeftHuman.NIF', None,
                                       [244, 236, 10, 101, 18, 128, 201, 157, 116, 108, 10,
                                        101, 23, 128, 201, 157, 115, 101, 24, 116, 246, 241,
                                        121, 224, 238, 223, 6, 102, 132, 76, 107, 195, 110,
                                        95, 6,102, 137, 76, 107, 195, 100, 101, 15, 116, 246,
                                        82, 111, 175, 243, 223, 6, 102, 132, 76, 107, 195,
                                        115, 95, 6, 102, 137, 76, 107, 195, 100, 101, 15, 116,
                                        246, 82, 111, 175],
                                       [], None, None, None)
    assert record.maleRightEye_list == ('Characters\\Head\\EyeRightHuman.NIF', None,
                                        [244, 236, 10, 101, 18, 128, 201, 157, 116,108, 10,
                                         101, 23, 128, 201, 157, 115, 101, 24, 116, 246, 241,
                                         121, 224, 238, 223, 6, 102, 132, 76, 107, 195, 110,
                                         95, 6, 102, 137, 76, 107, 195, 100, 101, 15, 116, 246,
                                         82, 111, 175, 243, 223, 6, 102, 132, 76, 107, 195, 115,
                                         95, 6, 102, 137, 76, 107, 195, 100, 101, 15, 116, 246,
                                         82, 111, 175],
                                        [], None, None, None)
    assert record.femaleHead_list == ('Characters\\Head\\HeadOldFemale.NIF', None,
                                      [238, 225, 9, 104, 61, 251, 66, 106, 110, 97, 9, 104, 66,
                                       251, 66, 106, 101, 108, 24, 116, 214, 243, 129, 224, 238,
                                       223, 11, 104, 138, 215, 34, 197, 110, 95, 11, 104, 143,
                                       215, 34, 197, 101, 108, 24, 116, 214, 243, 129, 224, 243,
                                       223, 11, 104, 138, 215, 34, 197, 115, 95, 11, 104, 143,
                                       215, 34, 197, 101, 108, 24, 116, 214, 243, 129, 224, 235,
                                       243, 12, 104, 159, 237, 36, 86, 107, 115, 12, 104, 164,
                                       237, 36, 86, 101, 108, 26, 116, 213, 12, 207, 126],
                                      [], 2, 'Characters\\OldFemale\\HeadHuman.dds', None)
    assert record.femaleEars_list == (None, None, [], [], None, 'Characters\\Head\\EarsHuman.dds', None)
    assert record.femaleMouth_list == ('Characters\\Head\\MouthHuman.NIF', None,
                                       [238, 225, 10, 109, 43, 201, 76, 110, 110, 97,10, 109, 48,
                                        201, 76, 110, 104, 116, 25, 116, 145, 5, 223, 51, 238,
                                        223, 6, 102, 132, 76, 107, 195, 110, 95, 6, 102, 137, 76,
                                        107, 195, 100, 101, 15, 116, 246, 82, 111, 175, 243, 223,
                                        6, 102, 132, 76, 107, 195, 115, 95, 6, 102, 137, 76, 107,
                                        195, 100, 101, 15, 116, 246, 82, 111, 175],
                                       [], None, 'Characters\\Mouth\\MouthHuman.dds', None)
    assert record.femaleTeethLower_list == ('Characters\\Head\\TeethLowerHuman.NIF', None,
                                            [238, 225, 15, 116, 216, 76, 118, 0, 110,97, 15, 116,
                                             221, 76, 118, 0, 104, 116, 25, 116, 145, 5, 223, 51,
                                             238, 223, 6, 102, 132, 76, 107, 195, 110, 95, 6, 102,
                                             137, 76, 107, 195, 100, 101, 15, 116, 246, 82, 111,
                                             175, 243, 223, 6, 102, 132, 76, 107, 195, 115, 95, 6,
                                             102, 137, 76,107, 195, 100, 101, 15, 116, 246, 82, 111,
                                             175],
                                            [], None, 'Characters\\Mouth\\TeethLowerHuman.dds', None)
    assert record.femaleTeethUpper_list == ('Characters\\Head\\TeethUpperHuman.NIF', None,
                                            [238, 225, 15, 116, 87, 210, 9, 247, 110,97, 15, 116,
                                             92, 210, 9, 247, 104, 116, 25, 116, 145, 5, 223, 51,
                                             238, 223, 6, 102, 132, 76, 107, 195, 110, 95, 6, 102,
                                             137, 76, 107, 195, 100, 101, 15, 116, 246, 82, 111,
                                             175, 243, 223, 6, 102, 132, 76, 107, 195, 115, 95, 6,
                                             102, 137, 76,107, 195, 100, 101, 15, 116, 246, 82, 111,
                                             175],
                                            [], None, 'Characters\\Mouth\\TeethUpperHuman.dds', None)
    assert record.femaleTongue_list == ('Characters\\Head\\TongueHuman.NIF', None,
                                        [238, 225, 11, 116, 205, 135, 184, 206, 110, 97, 11, 116, 210,
                                         135, 184, 206, 104, 116, 25, 116, 145, 5, 223, 51, 238, 223,
                                         6, 102, 132, 76, 107, 195, 110, 95, 6, 102, 137, 76, 107, 195,
                                         100, 101, 15, 116, 246, 82, 111, 175, 243, 223, 6, 102, 132,
                                         76, 107, 195, 115, 95, 6, 102, 137, 76, 107, 195, 100, 101, 15,
                                         116, 246, 82, 111, 175],
                                        [], None, 'Characters\\Mouth\\TongueHuman.dds', None)
    assert record.femaleLeftEye_list == ('Characters\\Head\\EyeLeftHumanFemale.NIF', None,
                                         [244, 236, 10, 101, 18, 128, 201, 157,116, 108, 10, 101, 23,
                                          128, 201, 157, 115, 101, 24, 116, 246, 241, 121, 224, 238,
                                          223, 6, 102, 132, 76, 107, 195, 110, 95, 6, 102, 137, 76, 107,
                                          195, 100, 101, 15, 116, 246, 82, 111, 175, 243, 223, 6, 102,
                                          132, 76, 107, 195, 115, 95, 6, 102, 137, 76, 107, 195, 100, 101,
                                          15, 116, 246, 82, 111, 175],
                                         [], None, None, None)
    assert record.femaleRightEye_list == ('Characters\\Head\\EyeRightHumanFemale.NIF', None,
                                          [244, 236, 10, 101, 18, 128, 201, 157, 116, 108, 10, 101, 23,
                                           128, 201, 157, 115, 101, 24, 116, 246, 241, 121, 224, 238,
                                           223, 6, 102, 132, 76, 107, 195, 110, 95, 6, 102, 137, 76, 107,
                                           195, 100, 101, 15, 116, 246, 82, 111, 175, 243, 223, 6, 102,
                                           132, 76, 107, 195, 115, 95, 6, 102, 137, 76, 107, 195, 100, 101,
                                           15, 116, 246, 82, 111, 175],
                                          [], None, None, None)
    assert record.maleUpperBody_list == ('characters\\_Male\\UpperBody.nif', None,
                                         [237, 242, 10, 117, 117, 224, 236, 252, 109, 114, 10, 117, 122,
                                          224, 236, 252, 114, 97, 24, 116, 57, 167, 49, 123, 238, 223,
                                          12, 117, 240, 164, 206, 114, 110, 95, 12, 117, 245, 164, 206, 114,
                                          114, 97, 24, 116, 57, 167, 49, 123, 229, 236, 13, 117, 232, 128,
                                          83, 141, 101, 108, 13, 117, 237, 128, 83, 141, 101, 108, 24, 116, 214,
                                          243, 129, 224, 238, 223, 15, 117, 97, 58, 128, 50, 110, 95, 15,
                                          117, 102, 58, 128, 50, 101, 108, 24, 116, 214, 243, 129, 224, 243,
                                          223, 15, 117, 97, 58, 128, 50, 115, 95, 15, 117, 102, 58, 128,
                                          50, 101, 108, 24, 116, 214, 243, 129, 224, 177, 176, 13, 109, 250,
                                          76, 9, 70, 49, 48, 13, 109, 255, 76, 9, 70, 101, 114, 13, 116,
                                          56, 122, 56, 113, 238, 223, 15, 109, 123, 14, 177, 93, 110, 95, 15,
                                          109, 128, 14, 177, 93, 101, 114, 13, 116, 56, 122, 56, 113, 243,
                                          223, 15, 109, 123, 14, 177, 93, 115, 95, 15, 109, 128, 14, 177, 93,
                                          101, 114, 13, 116, 56, 122, 56, 113],
                                         [], 2, 'Characters\\Male\\UpperBodyMale.dds', None)
    assert record.maleLeftHand_list == ('characters\\_Male\\LeftHand.nif', None,
                                        [229, 236, 8, 104, 208, 132, 4, 122, 101, 108, 8, 104, 213, 132, 4,
                                         122, 101, 108, 24, 116, 214, 243, 129, 224, 238, 223, 10, 104, 73,
                                         202, 29, 195, 110, 95, 10, 104, 78, 202, 29, 195, 101, 108, 24, 116,
                                         214, 243, 129, 224, 235, 243, 11, 104, 160, 170, 165, 201, 107, 115,
                                         11, 104, 165, 170, 165, 201, 101, 108, 24, 116, 214, 243, 129, 224],
                                        [], 8, 'Characters\\Male\\HandMale.dds', None)
    assert record.maleRightHand_list == ('characters\\_Male\\RightHand.nif', None,
                                         [229, 236, 8, 104, 208, 132, 4, 122, 101, 108, 8, 104, 213, 132, 4,
                                          122, 101, 108, 24, 116, 214, 243, 129, 224, 238, 223, 10, 104, 73,
                                          202, 29, 195, 110, 95, 10, 104, 78, 202, 29, 195, 101, 108, 24, 116,
                                          214, 243, 129, 224, 235, 243, 11, 104, 160, 170, 165, 201, 107, 115,
                                          11, 104, 165, 170, 165, 201, 101, 108, 24, 116, 214, 243, 129, 224],
                                         [], 4, 'Characters\\Male\\HandMale.dds', None)
    assert record.maleUpperBodyTexture_list == ('Characters\\_Male\\UpperBodyHumanMale.egt', None, [], [], None, None, None)
    assert record.femaleUpperBody_list == ('Characters\\_Male\\FemaleUpperBody.NIF', None,
                                           [177, 176, 13, 109, 250, 76, 9, 70, 49,
                                            48, 13, 109, 255, 76, 9, 70, 101, 114,
                                            13, 116, 56, 122, 56, 113, 238, 223,
                                            15, 109, 123, 14, 177, 93, 110, 95, 15,
                                            109, 128, 14, 177, 93, 101, 114, 13,
                                            116, 56, 122, 56, 113, 243, 223, 15,
                                            109, 123, 14, 177, 93, 115, 95, 15, 109,
                                            128, 14, 177, 93, 101, 114, 13, 116, 56,
                                            122, 56, 113, 230, 242, 10, 117, 117, 224,
                                            236, 252, 102, 114, 10, 117, 122, 224,
                                            236, 252, 114, 97, 24, 116, 57, 167, 49,
                                            123, 238, 223, 12, 117, 233, 164, 206, 114,
                                            110, 95, 12, 117, 238, 164, 206, 114, 114,
                                            97, 24, 116, 57, 167, 49, 123, 229, 236, 15,
                                            117, 103, 195, 201, 238, 101, 108, 15, 117,
                                            108, 195, 201, 238, 101, 108, 26, 116, 213,
                                            12, 207, 126, 238, 223, 17, 117, 96, 45, 127,
                                            247, 110, 95, 17, 117, 101, 45, 127, 247, 101,
                                            108, 26, 116, 213, 12, 207, 126, 243, 223, 17,
                                            117, 96, 45, 127, 247, 115, 95, 17, 117, 101,
                                            45, 127, 247, 101, 108, 26, 116, 213, 12, 207,
                                            126, 235, 243, 18, 117, 73, 13, 180, 16, 107,
                                            115, 18, 117, 78, 13, 180, 16, 101, 108, 26,
                                            116, 213, 12, 207, 126],
                                           [], 2, 'Characters\\Female\\UpperBodyFemale.dds', None)
    assert record.femaleLeftHand_list == ('Characters\\_Male\\FemaleLeftHand.NIF', None,
                                          [229, 236, 10, 104, 79, 83, 103, 127, 101,
                                           108, 10, 104, 84, 83, 103, 127, 101, 108,
                                           26, 116, 213, 12, 207, 126, 238, 223, 12,
                                           104, 72, 73, 131, 230, 110, 95, 12, 104,
                                           77, 73, 131, 230, 101, 108, 26, 116, 213,
                                           12, 207, 126, 235, 243, 13, 104, 97, 235,
                                           158, 254, 107, 115, 13, 104, 102, 235, 158,
                                           254, 101, 108, 26, 116, 213, 12, 207, 126],
                                          [], 8, 'Characters\\Female\\HandFemale.dds', None)
    assert record.femaleRightHand_list == ('Characters\\_Male\\FemaleRightHand.NIF', None,
                                           [229, 236, 10, 104, 79, 83, 103, 127, 101,
                                            108, 10, 104, 84, 83, 103, 127, 101, 108,
                                            26, 116, 213, 12, 207, 126, 238, 223, 12,
                                            104, 72, 73, 131, 230, 110, 95, 12, 104,
                                            77, 73, 131, 230, 101, 108, 26, 116, 213,
                                            12, 207, 126, 235, 243, 13, 104, 97, 235,
                                            158, 254, 107, 115, 13, 104, 102, 235, 158,
                                            254, 101, 108, 26, 116, 213, 12, 207, 126],
                                           [], 4, 'Characters\\Female\\HandFemale.dds', None)
    assert record.femaleUpperBodyTexture_list == ('Characters\\_Male\\UpperBodyHumanFemale.egt', None, [], [], None, None, None)
    assert record.hairs == [('FalloutNV.esm', 0x0987DA),
                            ('FalloutNV.esm', 0x0987D8),
                            ('FalloutNV.esm', 0x044529),
                            ('FalloutNV.esm', 0x044528),
                            ('FalloutNV.esm', 0x044527),
                            ('FalloutNV.esm', 0x0987D9)]
    assert record.eyes == [('FalloutNV.esm', 0x004253),
                           ('FalloutNV.esm', 0x004256),
                           ('FalloutNV.esm', 0x004255),
                           ('FalloutNV.esm', 0x004252)]
    assert record.maleFggs_p == [162, 167, 106, 61, 117, 33, 170, 61, 44,
                                 80, 61, 189, 42, 95, 42, 62, 244, 137, 48,
                                 189, 210, 104, 4, 59, 198, 14, 207, 189,
                                 187, 83, 34, 61, 127, 198, 25, 190, 144,
                                 52, 225, 189, 178, 36, 134, 190, 214, 144,
                                 108, 190, 142, 78, 228, 190, 59, 168, 178,
                                 61, 113, 171, 59, 61, 33, 242, 49, 62, 94,
                                 90, 42, 191, 196, 140, 7, 61, 96, 62, 200,
                                 189, 78, 45, 55, 63, 20, 216, 133, 63, 246,
                                 181, 198, 62, 216, 142, 132, 191, 190, 117,
                                 113, 191, 149, 216, 62, 191, 130, 148, 33,
                                 63, 187, 44, 158, 190, 75, 145, 143, 191, 45,
                                 15, 183, 189, 39, 213, 46, 62, 21, 39, 93,
                                 63, 0, 7, 5, 60, 24, 87, 36, 189, 4, 45, 101,
                                 63, 96, 46, 106, 190, 97, 216, 40, 63, 130,
                                 139, 106, 62, 184, 78, 49, 63, 105, 179, 114,
                                 191, 76, 191, 19, 62, 130, 64, 218, 190, 196,
                                 230, 102, 189, 141, 188, 35, 191, 198, 62,
                                 71, 62, 244, 182, 67, 62, 48, 35, 140, 191,
                                 66, 39, 18, 63, 182, 224, 155, 62, 40, 250,
                                 153, 188, 146, 156, 140, 63]
    assert record.maleFgga_p == [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    assert record.maleFgts_p == [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0]
    assert record.maleSnam_p == [149, 130]
    assert record.femaleFggs_p == [122, 3, 147, 63, 29, 75, 137, 63, 160, 52,
                                   64, 191, 249, 100, 69, 63, 223, 130, 233,
                                   190, 33, 179, 159, 190, 159, 45, 159, 190,
                                   160, 203, 64, 63, 185, 125, 3, 191, 109,
                                   76, 39, 191, 36, 224, 37, 190, 64, 87, 109,
                                   188, 113, 124, 220, 63, 59, 137, 103, 64,
                                   54, 230, 89, 63, 120, 165, 100, 191, 132,
                                   126, 140, 63, 240, 20, 79, 192, 27, 5, 87,
                                   191, 108, 65, 167, 190, 220, 4, 250, 63,
                                   191, 113, 29, 190, 244, 159, 86, 192, 65,
                                   63, 202, 192, 10, 9, 71, 64, 14, 1, 28, 64,
                                   206, 72, 133, 191, 80, 8, 131, 192, 234, 133,
                                   176, 63, 147, 130, 204, 63, 202, 16, 178, 62,
                                   127, 42, 11, 192, 0, 120, 214, 59, 64, 85,
                                   97, 63, 14, 72, 182, 192, 44, 102, 236, 62,
                                   239, 187, 175, 63, 61, 108, 165, 63, 174, 58,
                                   132, 63, 130, 21, 86, 63, 135, 243, 12, 192,
                                   126, 13, 67, 192, 249, 237, 192, 192, 131,
                                   140, 28, 193, 197, 199, 134, 191, 208, 92,
                                   154, 190, 208, 25, 76, 190, 98, 70, 166, 64,
                                   173, 147, 165, 192, 120, 126, 78, 193]
    assert record.femaleFgga_p == [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    assert record.femaleFgts_p == [165, 144, 167, 190, 166, 9, 42, 190, 153,
                                   126, 193, 61, 136, 106, 149, 190, 62, 45,
                                   164, 188, 151, 117, 154, 190, 207, 220, 223,
                                   189, 233, 215, 14, 192, 233, 123, 133, 191,
                                   209, 186, 163, 62, 190, 103, 142, 62, 184,
                                   111, 192, 62, 216, 218, 48, 190, 122, 66, 124,
                                   63, 145, 197, 184, 188, 198, 171, 65, 191, 40,
                                   172, 137, 62, 217, 253, 48, 63, 5, 243, 170,
                                   61, 44, 186, 178, 62, 29, 9, 161, 63, 163, 206,
                                   119, 191, 240, 110, 143, 190, 37, 159, 30, 63,
                                   86, 230, 200, 62, 245, 118, 221, 190, 180, 74,
                                   1, 191, 75, 105, 84, 63, 189, 102, 81, 63, 254,
                                   53, 150, 62, 139, 165, 199, 62, 255, 172, 78,
                                   62, 26, 217, 8, 63, 73, 42, 239, 189, 192, 24,
                                   46, 64, 158, 40, 116, 62, 52, 142, 107, 190,
                                   152, 110, 37, 59, 167, 207, 28, 63, 43, 74, 82,
                                   63, 240, 214, 57, 64, 13, 206, 248, 191, 94,
                                   192, 75, 63, 162, 50, 13, 191, 232, 69, 57, 61,
                                   250, 185, 12, 192, 136, 103, 60, 190, 73, 32,
                                   1, 192, 209, 164, 13, 191, 107, 181, 11, 190]
    assert record.femaleSnam_p == [149, 130]
    
    nrecord = newMod.create_RACE()

    nrecord.flags1 = 10
    nrecord.versionControl1 = [1, 3, 2, 6]
    nrecord.formVersion = 1
    nrecord.versionControl2 = [2, 3]
    nrecord.eid = r'WarTest'
    
    nrecord.full = 'WarCaucasian Old'
    nrecord.description = 'This is a very boring regression test of a rather annoying record to read/write.'
    nrecord.relations_list = [(('FalloutNV.esm', 1264455), -100, 1L), (('FalloutNV.esm', 1530450), 0, 1L),
                              (('FalloutNV.esm', 111268), 0, 1L), (('FalloutNV.esm', 266421), 0, 2L),
                              (('FalloutNV.esm', 1469262), 0, 2L), (('FalloutNV.esm', 103314), 0,2L),
                              (('FalloutNV.esm', 591630), 0, 3L), (('FalloutNV.esm', 559885), 0, 2L),
                              (('FalloutNV.esm', 96729), 0, 3L), (('FalloutNV.esm', 96747), 0, 3L),
                              (('FalloutNV.esm', 1317537), 0, 2L), (('FalloutNV.esm', 1355838), 0, 2L),
                              (('FalloutNV.esm',197906), 0, 2L), (('FalloutNV.esm', 673511), 0, 0L),
                              (('FalloutNV.esm', 119275), -100, 0L), (('FalloutNV.esm', 119806),100, 2L)]
    nrecord.skill1 = 1
    nrecord.skill1Boost = 2
    nrecord.skill2 = 3
    nrecord.skill2Boost = 4
    nrecord.skill3 = 5
    nrecord.skill3Boost = 6
    nrecord.skill4 = 7
    nrecord.skill4Boost = 8
    nrecord.skill5 = 9
    nrecord.skill5Boost = 10
    nrecord.skill6 = 11
    nrecord.skill6Boost = 12
    nrecord.skill7 = 13
    nrecord.skill7Boost = 14
    nrecord.maleHeight = 1.5
    nrecord.femaleHeight = 1.6
    nrecord.maleWeight = 1.7
    nrecord.femaleWeight = 1.8
    nrecord.flags = 19
    nrecord.older = ('FalloutNV.esm', 0x00001A)
    nrecord.younger = ('FalloutNV.esm', 0x00001B)
    nrecord.maleVoice = ('FalloutNV.esm', 0x00001C)
    nrecord.femaleVoice = ('FalloutNV.esm', 0x00001D)
    nrecord.defaultHairMale = ('FalloutNV.esm', 0x00001E)
    nrecord.defaultHairFemale = ('FalloutNV.esm', 0x00001F)
    nrecord.defaultHairMaleColor = 1
    nrecord.defaultHairFemaleColor = 2
    nrecord.mainClamp = 3.0
    nrecord.faceClamp = 4.0
    nrecord.attr_p = [55, 55]
    nrecord.maleHead_list = ('War\\Head\\HeadOld.NIF', 1.0, [a for a in range(5)], [('BeardMustacheCurly:1', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 1, 'War\\Old\\HeadHuman.dds', 'War2\\Old\\HeadHuman.dds')
    nrecord.maleEars_list = ('War1\\Head', 1.1, [a for a in range(6)], [('BeardMustacheCurly:2', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 2, 'War\\Head\\EarsHuman.dds', 'War3\\Old\\HeadHuman.dds')
    nrecord.maleMouth_list = ('War\\Head\\MouthHuman.NIF', 1.2,[a for a in range(4)],[('BeardMustacheCurly:3', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 1, 'War\\Mouth\\MouthHuman.dds', 'War4\\Old\\HeadHuman.dds')
    nrecord.maleTeethLower_list = ('War\\Head\\TeethLowerHuman.NIF', 1.3,[a for a in range(16)],[('BeardMustacheCurly:4', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 2, 'War\\Mouth\\TeethLowerRaider.dds', 'War5\\Old\\HeadHuman.dds')
    nrecord.maleTeethUpper_list = ('War\\Head\\TeethUpperHuman.NIF', 1.4,[a for a in range(15)],[('BeardMustacheCurly:5', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 1, 'War\\Mouth\\TeethUpperRaider.dds', 'War6\\Old\\HeadHuman.dds')
    nrecord.maleTongue_list = ('War\\Head\\TongueHuman.NIF', 1.5,[a for a in range(14)],[('BeardMustacheCurly:6', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 2, 'War\\Mouth\\TongueRaider.dds', 'War7\\Old\\HeadHuman.dds')
    nrecord.maleLeftEye_list = ('War\\Head\\EyeLeftHuman.NIF', 1.6,[a for a in range(13)],[('BeardMustacheCurly:7', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 1, 'War1\\H3ad', 'War8\\Old\\HeadHuman.dds')
    nrecord.maleRightEye_list = ('War\\Head\\EyeRightHuman.NIF', 1.7,[a for a in range(12)],[('BeardMustacheCurly:8', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 2, 'War1\\H3ad', 'War9\\Old\\HeadHuman.dds')
    nrecord.femaleHead_list = ('War\\Head\\HeadOldFemale.NIF', 1.8,[a for a in range(1)],[('BeardMustacheCurly:9', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 2, 'War\\OldFemale\\HeadHuman.dds', 'War10\\Old\\HeadHuman.dds')
    nrecord.femaleEars_list = ('War2\\Head', 1.9, [a for a in range(4)], [], 1, 'War\\Head\\EarsHuman.dds', 'War11\\Old\\HeadHuman.dds')
    nrecord.femaleMouth_list = ('War\\Head\\MouthHuman.NIF', 2.0,[a for a in range(5)],[('BeardMustacheCurly:10', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 2, 'Characters\\Mouth\\MouthHuman.dds', 'War12\\Old\\HeadHuman.dds')
    nrecord.femaleTeethLower_list = ('War\\Head\\TeethLowerHuman.NIF', 2.1,[a for a in range(4)],[('BeardMustacheCurly:110', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 1, 'War\\Mouth\\TeethLowerHuman.dds', 'War13\\Old\\HeadHuman.dds')
    nrecord.femaleTeethUpper_list = ('War\\Head\\TeethUpperHuman.NIF', 2.2,[a for a in range(3)],[('BeardMustacheCurly:1110', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 2, 'War\\Mouth\\TeethUpperHuman.dds', 'War14\\Old\\HeadHuman.dds')
    nrecord.femaleTongue_list = ('War\\Head\\TongueHuman.NIF', 2.3,[a for a in range(9)],[('BeardMustacheCurly:11110', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 1, 'War\\Mouth\\TongueHuman.dds', 'War15\\Old\\HeadHuman.dds')
    nrecord.femaleLeftEye_list = ('War\\Head\\EyeLeftHumanFemale.NIF', 2.4,[a for a in range(8)],[('BeardMustacheCurly:111110', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 2, 'War1\\H3ad', 'War16\\Old\\HeadHuman.dds')
    nrecord.femaleRightEye_list = ('War\\Head\\EyeRightHumanFemale.NIF', 2.5,[a for a in range(7)],[('BeardMustacheCurly:a0', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 1, 'War1\\H3ad', 'War17\\Old\\HeadHuman.dds')
    nrecord.maleUpperBody_list = ('War\\_Male\\UpperBody.nif', 2.6,[a for a in range(6)],[('BeardMustacheCurly:aa0', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 2, 'War\\Male\\UpperBodyMale.dds', 'War18\\Old\\HeadHuman.dds')
    nrecord.maleLeftHand_list = ('War\\_Male\\LeftHand.nif', 2.7,[a for a in range(5)],[('BeardMustacheCurly:aaa0', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 8, 'War\\Male\\HandMale.dds', 'War19\\Old\\HeadHuman.dds')
    nrecord.maleRightHand_list = ('War\\_Male\\RightHand.nif', 2.8,[a for a in range(13)],[('BeardMustacheCurly:aaaa0', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 4, 'War\\Male\\HandMale.dds', 'War20\\Old\\HeadHuman.dds')
    nrecord.maleUpperBodyTexture_list = ('War\\_Male\\UpperBodyHumanMale.egt', 2.9, [a for a in range(3)], [('BeardMustacheCurly:aaaaa0', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 1, 'War1\\H3ad', 'War21\\Old\\HeadHuman.dds')
    nrecord.femaleUpperBody_list = ('War\\_Male\\FemaleUpperBody.NIF', 3.0,[a for a in range(12)],[('BeardMustacheCurly:0a', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 2, 'War\\Female\\UpperBodyFemale.dds', 'War22\\Old\\HeadHuman.dds')
    nrecord.femaleLeftHand_list = ('War\\_Male\\FemaleLeftHand.NIF', 3.1,[a for a in range(11)],[('BeardMustacheCurly:0aa', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 8, 'War\\Female\\HandFemale.dds', 'War23\\Old\\HeadHuman.dds')
    nrecord.femaleRightHand_list = ('War\\_Male\\FemaleRightHand.NIF', 3.2,[a for a in range(10)],[('BeardMustacheCurly:0aaa', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 4, 'War\\Female\\HandFemale.dds', 'War24\\Old\\HeadHuman.dds')
    nrecord.femaleUpperBodyTexture_list = ('War\\_Male\\UpperBodyHumanFemale.egt', 3.3, [a for a in range(2)], [('BeardMustacheCurly:0aaaa', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 2, 'War1\\H3ad', 'War25\\Old\\HeadHuman.dds')
    nrecord.hairs = [('FalloutNV.esm', 0x000001),
                            ('FalloutNV.esm', 0x000002),
                            ('FalloutNV.esm', 0x000003),
                            ('FalloutNV.esm', 0x000004),
                            ('FalloutNV.esm', 0x000005),
                            ('FalloutNV.esm', 0x000006)]
    nrecord.eyes = [('FalloutNV.esm', 0x000007),
                           ('FalloutNV.esm', 0x000008),
                           ('FalloutNV.esm', 0x000009),
                           ('FalloutNV.esm', 0x00000A)]
    nrecord.maleFggs_p = [a for a in range(200)]
    nrecord.maleFgga_p = [a for a in range(120)]
    nrecord.maleFgts_p = [a for a in range(200)]
    nrecord.maleSnam_p = [1, 2]
    nrecord.femaleFggs_p = [a for a in range(200)]
    nrecord.femaleFgga_p = [a for a in range(120)]
    nrecord.femaleFgts_p = [a for a in range(200)]
    nrecord.femaleSnam_p = [3, 4]
    
    assert nrecord.fid == ('RegressionTests.esp', 0x00100D)
    assert nrecord.flags1 == 0x80000000 | 10
    assert nrecord.versionControl1 == [1, 3, 2, 6]
    assert nrecord.formVersion == 1
    assert nrecord.versionControl2 == [2, 3]
    assert nrecord.eid == 'WarTest'
    assert nrecord.eid == 'WArTest'
    
    assert nrecord.full == 'WarCaucasian Old'
    assert nrecord.full != 'WArCaucasian Old'
    assert nrecord.description == 'This is a very boring regression test of a rather annoying record to read/write.'
    assert nrecord.description != 'This is A very boring regression test of a rather annoying record to read/write.'
    assert nrecord.relations_list == [(('FalloutNV.esm', 1264455), -100, 1L), (('FalloutNV.esm', 1530450), 0, 1L),
                              (('FalloutNV.esm', 111268), 0, 1L), (('FalloutNV.esm', 266421), 0, 2L),
                              (('FalloutNV.esm', 1469262), 0, 2L), (('FalloutNV.esm', 103314), 0,2L),
                              (('FalloutNV.esm', 591630), 0, 3L), (('FalloutNV.esm', 559885), 0, 2L),
                              (('FalloutNV.esm', 96729), 0, 3L), (('FalloutNV.esm', 96747), 0, 3L),
                              (('FalloutNV.esm', 1317537), 0, 2L), (('FalloutNV.esm', 1355838), 0, 2L),
                              (('FalloutNV.esm',197906), 0, 2L), (('FalloutNV.esm', 673511), 0, 0L),
                              (('FalloutNV.esm', 119275), -100, 0L), (('FalloutNV.esm', 119806),100, 2L)]
    assert nrecord.skill1 == 1
    assert nrecord.skill1Boost == 2
    assert nrecord.skill2 == 3
    assert nrecord.skill2Boost == 4
    assert nrecord.skill3 == 5
    assert nrecord.skill3Boost == 6
    assert nrecord.skill4 == 7
    assert nrecord.skill4Boost == 8
    assert nrecord.skill5 == 9
    assert nrecord.skill5Boost == 10
    assert nrecord.skill6 == 11
    assert nrecord.skill6Boost == 12
    assert nrecord.skill7 == 13
    assert nrecord.skill7Boost == 14
    assert nrecord.maleHeight == 1.5
    assert nrecord.femaleHeight == 1.6
    assert nrecord.maleWeight == 1.7
    assert nrecord.femaleWeight == 1.8
    assert nrecord.flags == 19
    assert nrecord.older == ('FalloutNV.esm', 0x00001A)
    assert nrecord.younger == ('FalloutNV.esm', 0x00001B)
    assert nrecord.maleVoice == ('FalloutNV.esm', 0x00001C)
    assert nrecord.femaleVoice == ('FalloutNV.esm', 0x00001D)
    assert nrecord.defaultHairMale == ('FalloutNV.esm', 0x00001E)
    assert nrecord.defaultHairFemale == ('FalloutNV.esm', 0x00001F)
    assert nrecord.defaultHairMaleColor == 1
    assert nrecord.defaultHairFemaleColor == 2
    assert nrecord.mainClamp == 3.0
    assert nrecord.faceClamp == 4.0
    assert nrecord.attr_p == [55, 55]

    assert nrecord.maleHead_list == ('War\\Head\\HeadOld.NIF', 1.0, [a for a in range(5)], [('BeardMustacheCurly:1', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 1, 'War\\Old\\HeadHuman.dds', 'War2\\Old\\HeadHuman.dds')
    assert nrecord.maleEars_list == ('War1\\Head', 1.1, [a for a in range(6)], [('BeardMustacheCurly:2', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 2, 'War\\Head\\EarsHuman.dds', 'War3\\Old\\HeadHuman.dds')
    assert nrecord.maleMouth_list == ('War\\Head\\MouthHuman.NIF', 1.2,[a for a in range(4)],[('BeardMustacheCurly:3', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 1, 'War\\Mouth\\MouthHuman.dds', 'War4\\Old\\HeadHuman.dds')
    assert nrecord.maleTeethLower_list == ('War\\Head\\TeethLowerHuman.NIF', 1.3,[a for a in range(16)],[('BeardMustacheCurly:4', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 2, 'War\\Mouth\\TeethLowerRaider.dds', 'War5\\Old\\HeadHuman.dds')
    assert nrecord.maleTeethUpper_list == ('War\\Head\\TeethUpperHuman.NIF', 1.4,[a for a in range(15)],[('BeardMustacheCurly:5', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 1, 'War\\Mouth\\TeethUpperRaider.dds', 'War6\\Old\\HeadHuman.dds')
    assert nrecord.maleTongue_list == ('War\\Head\\TongueHuman.NIF', 1.5,[a for a in range(14)],[('BeardMustacheCurly:6', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 2, 'War\\Mouth\\TongueRaider.dds', 'War7\\Old\\HeadHuman.dds')
    assert nrecord.maleLeftEye_list == ('War\\Head\\EyeLeftHuman.NIF', 1.6,[a for a in range(13)],[('BeardMustacheCurly:7', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 1, 'War1\\H3ad', 'War8\\Old\\HeadHuman.dds')
    assert nrecord.maleRightEye_list == ('War\\Head\\EyeRightHuman.NIF', 1.7,[a for a in range(12)],[('BeardMustacheCurly:8', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 2, 'War1\\H3ad', 'War9\\Old\\HeadHuman.dds')
    assert nrecord.femaleHead_list == ('War\\Head\\HeadOldFemale.NIF', 1.8,[a for a in range(1)],[('BeardMustacheCurly:9', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 2, 'War\\OldFemale\\HeadHuman.dds', 'War10\\Old\\HeadHuman.dds')
    assert nrecord.femaleEars_list == ('War2\\Head', 1.9, [a for a in range(4)], [], 1, 'War\\Head\\EarsHuman.dds', 'War11\\Old\\HeadHuman.dds')
    assert nrecord.femaleMouth_list == ('War\\Head\\MouthHuman.NIF', 2.0,[a for a in range(5)],[('BeardMustacheCurly:10', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 2, 'Characters\\Mouth\\MouthHuman.dds', 'War12\\Old\\HeadHuman.dds')
    assert nrecord.femaleTeethLower_list == ('War\\Head\\TeethLowerHuman.NIF', 2.1,[a for a in range(4)],[('BeardMustacheCurly:110', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 1, 'War\\Mouth\\TeethLowerHuman.dds', 'War13\\Old\\HeadHuman.dds')
    assert nrecord.femaleTeethUpper_list == ('War\\Head\\TeethUpperHuman.NIF', 2.2,[a for a in range(3)],[('BeardMustacheCurly:1110', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 2, 'War\\Mouth\\TeethUpperHuman.dds', 'War14\\Old\\HeadHuman.dds')
    assert nrecord.femaleTongue_list == ('War\\Head\\TongueHuman.NIF', 2.3,[a for a in range(9)],[('BeardMustacheCurly:11110', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 1, 'War\\Mouth\\TongueHuman.dds', 'War15\\Old\\HeadHuman.dds')
    assert nrecord.femaleLeftEye_list == ('War\\Head\\EyeLeftHumanFemale.NIF', 2.4,[a for a in range(8)],[('BeardMustacheCurly:111110', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 2, 'War1\\H3ad', 'War16\\Old\\HeadHuman.dds')
    assert nrecord.femaleRightEye_list == ('War\\Head\\EyeRightHumanFemale.NIF', 2.5,[a for a in range(7)],[('BeardMustacheCurly:a0', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 1, 'War1\\H3ad', 'War17\\Old\\HeadHuman.dds')
    assert nrecord.maleUpperBody_list == ('War\\_Male\\UpperBody.nif', 2.6,[a for a in range(6)],[('BeardMustacheCurly:aa0', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 2, 'War\\Male\\UpperBodyMale.dds', 'War18\\Old\\HeadHuman.dds')
    assert nrecord.maleLeftHand_list == ('War\\_Male\\LeftHand.nif', 2.7,[a for a in range(5)],[('BeardMustacheCurly:aaa0', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 8, 'War\\Male\\HandMale.dds', 'War19\\Old\\HeadHuman.dds')
    assert nrecord.maleRightHand_list == ('War\\_Male\\RightHand.nif', 2.8,[a for a in range(13)],[('BeardMustacheCurly:aaaa0', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 4, 'War\\Male\\HandMale.dds', 'War20\\Old\\HeadHuman.dds')
    assert nrecord.maleUpperBodyTexture_list == ('War\\_Male\\UpperBodyHumanMale.egt', 2.9, [a for a in range(3)], [('BeardMustacheCurly:aaaaa0', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 1, 'War1\\H3ad', 'War21\\Old\\HeadHuman.dds')
    assert nrecord.femaleUpperBody_list == ('War\\_Male\\FemaleUpperBody.NIF', 3.0,[a for a in range(12)],[('BeardMustacheCurly:0a', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 2, 'War\\Female\\UpperBodyFemale.dds', 'War22\\Old\\HeadHuman.dds')
    assert nrecord.femaleLeftHand_list == ('War\\_Male\\FemaleLeftHand.NIF', 3.1,[a for a in range(11)],[('BeardMustacheCurly:0aa', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 8, 'War\\Female\\HandFemale.dds', 'War23\\Old\\HeadHuman.dds')
    assert nrecord.femaleRightHand_list == ('War\\_Male\\FemaleRightHand.NIF', 3.2,[a for a in range(10)],[('BeardMustacheCurly:0aaa', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 4, 'War\\Female\\HandFemale.dds', 'War24\\Old\\HeadHuman.dds')
    assert nrecord.femaleUpperBodyTexture_list == ('War\\_Male\\UpperBodyHumanFemale.egt', 3.3, [a for a in range(2)], [('BeardMustacheCurly:0aaaa', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 2, 'War1\\H3ad', 'War25\\Old\\HeadHuman.dds')
    assert nrecord.hairs == [('FalloutNV.esm', 0x000001),
                            ('FalloutNV.esm', 0x000002),
                            ('FalloutNV.esm', 0x000003),
                            ('FalloutNV.esm', 0x000004),
                            ('FalloutNV.esm', 0x000005),
                            ('FalloutNV.esm', 0x000006)]
    assert nrecord.eyes == [('FalloutNV.esm', 0x000007),
                           ('FalloutNV.esm', 0x000008),
                           ('FalloutNV.esm', 0x000009),
                           ('FalloutNV.esm', 0x00000A)]
    assert nrecord.maleFggs_p == [a for a in range(200)]
    assert nrecord.maleFgga_p == [a for a in range(120)]
    assert nrecord.maleFgts_p == [a for a in range(200)]
    assert nrecord.maleSnam_p == [1, 2]
    assert nrecord.femaleFggs_p == [a for a in range(200)]
    assert nrecord.femaleFgga_p == [a for a in range(120)]
    assert nrecord.femaleFgts_p == [a for a in range(200)]
    assert nrecord.femaleSnam_p == [3, 4]

    relation = nrecord.create_relation()
    relation.faction = ('RegressionTests.esp', 0x001009)
    relation.mod = 3
    relation.groupReactionType = 2
    
    assert nrecord.relations_list == [(('FalloutNV.esm', 1264455), -100, 1L), (('FalloutNV.esm', 1530450), 0, 1L),
                              (('FalloutNV.esm', 111268), 0, 1L), (('FalloutNV.esm', 266421), 0, 2L),
                              (('FalloutNV.esm', 1469262), 0, 2L), (('FalloutNV.esm', 103314), 0,2L),
                              (('FalloutNV.esm', 591630), 0, 3L), (('FalloutNV.esm', 559885), 0, 2L),
                              (('FalloutNV.esm', 96729), 0, 3L), (('FalloutNV.esm', 96747), 0, 3L),
                              (('FalloutNV.esm', 1317537), 0, 2L), (('FalloutNV.esm', 1355838), 0, 2L),
                              (('FalloutNV.esm',197906), 0, 2L), (('FalloutNV.esm', 673511), 0, 0L),
                              (('FalloutNV.esm', 119275), -100, 0L), (('FalloutNV.esm', 119806),100, 2L),
                              (('RegressionTests.esp', 0x001009), 3, 2)]

    altTexture = nrecord.maleHead.create_altTexture()
    altTexture.name = r'WarTESTNAME'
    altTexture.texture = ('FalloutNV.esm', 653616)
    altTexture.index = 6
    
    altTexture = nrecord.femaleHead.create_altTexture()
    altTexture.name = r'FeWarTESTNAME'
    altTexture.texture = ('FalloutNV.esm', 653617)
    altTexture.index = 3

    assert nrecord.maleHead.altTextures_list == [('BeardMustacheCurly:1', ('FalloutNV.esm', 653607), -1),
                                                 ('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0),
                                                 ('WarTESTNAME', ('FalloutNV.esm', 653616), 6)]
    assert nrecord.femaleHead.altTextures_list == [('BeardMustacheCurly:9', ('FalloutNV.esm', 653607), -1),
                                                   ('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0),
                                                   ('FeWarTESTNAME', ('FalloutNV.esm', 653617), 3)]

    record = Current.LoadOrderMods[0].RACE[0]
    newrecord = record.CopyAsOverride(newMod)

    assert newrecord.fid == ('FalloutNV.esm', 0x0987DF)
    assert newrecord.flags1 == 0x80000000L
    assert newrecord.versionControl1 == [16, 66, 39, 0]
    assert newrecord.formVersion == 15
    assert newrecord.versionControl2 == [5, 0]
    assert newrecord.eid == 'CaucasianOldAged'
    assert newrecord.eid == 'CAucasianOldAged'
    
    assert newrecord.full == 'Caucasian Old'
    assert newrecord.full != 'CAucasian Old'
    assert newrecord.description == None
    assert newrecord.relations_list == []
    assert newrecord.skill1 == -1
    assert newrecord.skill1Boost == 0
    assert newrecord.skill2 == -1
    assert newrecord.skill2Boost == 0
    assert newrecord.skill3 == -1
    assert newrecord.skill3Boost == 0
    assert newrecord.skill4 == -1
    assert newrecord.skill4Boost == 0
    assert newrecord.skill5 == -1
    assert newrecord.skill5Boost == 0
    assert newrecord.skill6 == -1
    assert newrecord.skill6Boost == 0
    assert newrecord.skill7 == -1
    assert newrecord.skill7Boost == 0
    assert newrecord.maleHeight == 1.0
    assert newrecord.femaleHeight == 1.0
    assert newrecord.maleWeight == 1.0
    assert newrecord.femaleWeight == 1.0
    assert newrecord.flags == 0x0L
    assert newrecord.older == None
    assert newrecord.younger == ('FalloutNV.esm', 0x000019)
    assert newrecord.maleVoice == ('FalloutNV.esm', 0x019FD2)
    assert newrecord.femaleVoice == ('FalloutNV.esm', 0x00002E)
    assert newrecord.defaultHairMale == ('FalloutNV.esm', 0x0987DA)
    assert newrecord.defaultHairFemale == ('FalloutNV.esm', 0x044529)
    assert newrecord.defaultHairMaleColor == 1
    assert newrecord.defaultHairFemaleColor == 1
    assert newrecord.mainClamp == 5.0
    assert newrecord.faceClamp == 3.0
    assert newrecord.attr_p == [5, 5]
    assert newrecord.maleHead_list == ('Characters\\Head\\HeadOld.NIF', None,
                                    [238, 225, 9, 104, 61, 251, 66, 106, 110, 97, 9,
                                     104, 66, 251, 66, 106, 101, 108, 24, 116, 214,
                                     243, 129, 224, 238, 223, 11, 104, 138, 215, 34,
                                     197, 110, 95, 11, 104, 143, 215, 34, 197, 101,
                                     108, 24, 116, 214, 243, 129, 224, 243, 223, 11,
                                     104, 138, 215, 34, 197, 115, 95, 11, 104, 143,
                                     215, 34, 197, 101, 108, 24, 116, 214, 243, 129,
                                     224, 235, 243, 12, 104, 159, 237, 36, 86, 107,
                                     115, 12, 104, 164, 237, 36, 86, 101, 108, 24,
                                     116, 214, 243, 129, 224],
                                    [], 2, 'Characters\\Old\\HeadHuman.dds', None)
    assert newrecord.maleEars_list == (None, None, [], [], None, 'Characters\\Head\\EarsHuman.dds', None)
    assert newrecord.maleMouth_list == ('Characters\\Head\\MouthHuman.NIF', None,
                                     [238, 225, 10, 109, 43, 201, 76, 110, 110, 97,
                                      10, 109, 48, 201, 76, 110, 104, 116, 25, 116,
                                      145, 5, 223, 51, 238, 223, 6, 102, 132, 76, 107,
                                      195, 110, 95, 6, 102, 137, 76, 107, 195, 100, 101,
                                      15, 116, 246, 82, 111, 175, 243, 223, 6, 102, 132,
                                      76, 107, 195, 115, 95, 6, 102, 137, 76, 107, 195,
                                      100, 101, 15, 116, 246, 82, 111, 175],
                                     [], None, 'Characters\\Mouth\\MouthHuman.dds', None)
    assert newrecord.maleTeethLower_list == ('Characters\\Head\\TeethLowerHuman.NIF', None,
                                          [238, 225, 15, 116, 216, 76, 118, 0, 110,97, 15,
                                           116, 221, 76, 118, 0, 104, 116, 25, 116, 145, 5,
                                           223, 51, 238, 223, 6, 102, 132, 76, 107, 195, 110,
                                           95, 6, 102,137, 76, 107, 195, 100, 101, 15, 116,
                                           246, 82, 111, 175, 243, 223, 6, 102, 132, 76, 107,
                                           195, 115, 95, 6, 102, 137, 76,107, 195, 100, 101,
                                           15, 116, 246, 82, 111, 175],
                                          [], None, 'Characters\\Mouth\\TeethLowerRaider.dds', None)
    assert newrecord.maleTeethUpper_list == ('Characters\\Head\\TeethUpperHuman.NIF', None,
                                          [238, 225, 15, 116, 87, 210, 9, 247, 110,97, 15,
                                           116, 92, 210, 9, 247, 104, 116, 25, 116, 145, 5,
                                           223, 51, 238, 223, 6, 102, 132, 76, 107, 195, 110,
                                           95, 6, 102,137, 76, 107, 195, 100, 101, 15, 116,
                                           246, 82, 111, 175, 243, 223, 6, 102, 132, 76, 107,
                                           195, 115, 95, 6, 102, 137, 76,107, 195, 100, 101,
                                           15, 116, 246, 82, 111, 175],
                                          [], None, 'Characters\\Mouth\\TeethUpperRaider.dds', None)
    assert newrecord.maleTongue_list == ('Characters\\Head\\TongueHuman.NIF', None,
                                      [238, 225, 11, 116, 205, 135, 184, 206, 110, 97, 11, 116,
                                       210, 135, 184, 206, 104, 116, 25, 116, 145, 5, 223, 51,
                                       238, 223, 6, 102, 132, 76, 107, 195, 110, 95, 6, 102,
                                       137, 76, 107, 195, 100, 101, 15, 116, 246, 82, 111, 175,
                                       243, 223, 6, 102, 132, 76, 107, 195, 115, 95, 6, 102,
                                       137, 76, 107, 195, 100, 101, 15, 116, 246, 82, 111, 175],
                                      [], None, 'Characters\\Mouth\\TongueRaider.dds', None)
    assert newrecord.maleLeftEye_list == ('Characters\\Head\\EyeLeftHuman.NIF', None,
                                       [244, 236, 10, 101, 18, 128, 201, 157, 116, 108, 10,
                                        101, 23, 128, 201, 157, 115, 101, 24, 116, 246, 241,
                                        121, 224, 238, 223, 6, 102, 132, 76, 107, 195, 110,
                                        95, 6,102, 137, 76, 107, 195, 100, 101, 15, 116, 246,
                                        82, 111, 175, 243, 223, 6, 102, 132, 76, 107, 195,
                                        115, 95, 6, 102, 137, 76, 107, 195, 100, 101, 15, 116,
                                        246, 82, 111, 175],
                                       [], None, None, None)
    assert newrecord.maleRightEye_list == ('Characters\\Head\\EyeRightHuman.NIF', None,
                                        [244, 236, 10, 101, 18, 128, 201, 157, 116,108, 10,
                                         101, 23, 128, 201, 157, 115, 101, 24, 116, 246, 241,
                                         121, 224, 238, 223, 6, 102, 132, 76, 107, 195, 110,
                                         95, 6, 102, 137, 76, 107, 195, 100, 101, 15, 116, 246,
                                         82, 111, 175, 243, 223, 6, 102, 132, 76, 107, 195, 115,
                                         95, 6, 102, 137, 76, 107, 195, 100, 101, 15, 116, 246,
                                         82, 111, 175],
                                        [], None, None, None)
    assert newrecord.femaleHead_list == ('Characters\\Head\\HeadOldFemale.NIF', None,
                                      [238, 225, 9, 104, 61, 251, 66, 106, 110, 97, 9, 104, 66,
                                       251, 66, 106, 101, 108, 24, 116, 214, 243, 129, 224, 238,
                                       223, 11, 104, 138, 215, 34, 197, 110, 95, 11, 104, 143,
                                       215, 34, 197, 101, 108, 24, 116, 214, 243, 129, 224, 243,
                                       223, 11, 104, 138, 215, 34, 197, 115, 95, 11, 104, 143,
                                       215, 34, 197, 101, 108, 24, 116, 214, 243, 129, 224, 235,
                                       243, 12, 104, 159, 237, 36, 86, 107, 115, 12, 104, 164,
                                       237, 36, 86, 101, 108, 26, 116, 213, 12, 207, 126],
                                      [], 2, 'Characters\\OldFemale\\HeadHuman.dds', None)
    assert newrecord.femaleEars_list == (None, None, [], [], None, 'Characters\\Head\\EarsHuman.dds', None)
    assert newrecord.femaleMouth_list == ('Characters\\Head\\MouthHuman.NIF', None,
                                       [238, 225, 10, 109, 43, 201, 76, 110, 110, 97,10, 109, 48,
                                        201, 76, 110, 104, 116, 25, 116, 145, 5, 223, 51, 238,
                                        223, 6, 102, 132, 76, 107, 195, 110, 95, 6, 102, 137, 76,
                                        107, 195, 100, 101, 15, 116, 246, 82, 111, 175, 243, 223,
                                        6, 102, 132, 76, 107, 195, 115, 95, 6, 102, 137, 76, 107,
                                        195, 100, 101, 15, 116, 246, 82, 111, 175],
                                       [], None, 'Characters\\Mouth\\MouthHuman.dds', None)
    assert newrecord.femaleTeethLower_list == ('Characters\\Head\\TeethLowerHuman.NIF', None,
                                            [238, 225, 15, 116, 216, 76, 118, 0, 110,97, 15, 116,
                                             221, 76, 118, 0, 104, 116, 25, 116, 145, 5, 223, 51,
                                             238, 223, 6, 102, 132, 76, 107, 195, 110, 95, 6, 102,
                                             137, 76, 107, 195, 100, 101, 15, 116, 246, 82, 111,
                                             175, 243, 223, 6, 102, 132, 76, 107, 195, 115, 95, 6,
                                             102, 137, 76,107, 195, 100, 101, 15, 116, 246, 82, 111,
                                             175],
                                            [], None, 'Characters\\Mouth\\TeethLowerHuman.dds', None)
    assert newrecord.femaleTeethUpper_list == ('Characters\\Head\\TeethUpperHuman.NIF', None,
                                            [238, 225, 15, 116, 87, 210, 9, 247, 110,97, 15, 116,
                                             92, 210, 9, 247, 104, 116, 25, 116, 145, 5, 223, 51,
                                             238, 223, 6, 102, 132, 76, 107, 195, 110, 95, 6, 102,
                                             137, 76, 107, 195, 100, 101, 15, 116, 246, 82, 111,
                                             175, 243, 223, 6, 102, 132, 76, 107, 195, 115, 95, 6,
                                             102, 137, 76,107, 195, 100, 101, 15, 116, 246, 82, 111,
                                             175],
                                            [], None, 'Characters\\Mouth\\TeethUpperHuman.dds', None)
    assert newrecord.femaleTongue_list == ('Characters\\Head\\TongueHuman.NIF', None,
                                        [238, 225, 11, 116, 205, 135, 184, 206, 110, 97, 11, 116, 210,
                                         135, 184, 206, 104, 116, 25, 116, 145, 5, 223, 51, 238, 223,
                                         6, 102, 132, 76, 107, 195, 110, 95, 6, 102, 137, 76, 107, 195,
                                         100, 101, 15, 116, 246, 82, 111, 175, 243, 223, 6, 102, 132,
                                         76, 107, 195, 115, 95, 6, 102, 137, 76, 107, 195, 100, 101, 15,
                                         116, 246, 82, 111, 175],
                                        [], None, 'Characters\\Mouth\\TongueHuman.dds', None)
    assert newrecord.femaleLeftEye_list == ('Characters\\Head\\EyeLeftHumanFemale.NIF', None,
                                         [244, 236, 10, 101, 18, 128, 201, 157,116, 108, 10, 101, 23,
                                          128, 201, 157, 115, 101, 24, 116, 246, 241, 121, 224, 238,
                                          223, 6, 102, 132, 76, 107, 195, 110, 95, 6, 102, 137, 76, 107,
                                          195, 100, 101, 15, 116, 246, 82, 111, 175, 243, 223, 6, 102,
                                          132, 76, 107, 195, 115, 95, 6, 102, 137, 76, 107, 195, 100, 101,
                                          15, 116, 246, 82, 111, 175],
                                         [], None, None, None)
    assert newrecord.femaleRightEye_list == ('Characters\\Head\\EyeRightHumanFemale.NIF', None,
                                          [244, 236, 10, 101, 18, 128, 201, 157, 116, 108, 10, 101, 23,
                                           128, 201, 157, 115, 101, 24, 116, 246, 241, 121, 224, 238,
                                           223, 6, 102, 132, 76, 107, 195, 110, 95, 6, 102, 137, 76, 107,
                                           195, 100, 101, 15, 116, 246, 82, 111, 175, 243, 223, 6, 102,
                                           132, 76, 107, 195, 115, 95, 6, 102, 137, 76, 107, 195, 100, 101,
                                           15, 116, 246, 82, 111, 175],
                                          [], None, None, None)
    assert newrecord.maleUpperBody_list == ('characters\\_Male\\UpperBody.nif', None,
                                         [237, 242, 10, 117, 117, 224, 236, 252, 109, 114, 10, 117, 122,
                                          224, 236, 252, 114, 97, 24, 116, 57, 167, 49, 123, 238, 223,
                                          12, 117, 240, 164, 206, 114, 110, 95, 12, 117, 245, 164, 206, 114,
                                          114, 97, 24, 116, 57, 167, 49, 123, 229, 236, 13, 117, 232, 128,
                                          83, 141, 101, 108, 13, 117, 237, 128, 83, 141, 101, 108, 24, 116, 214,
                                          243, 129, 224, 238, 223, 15, 117, 97, 58, 128, 50, 110, 95, 15,
                                          117, 102, 58, 128, 50, 101, 108, 24, 116, 214, 243, 129, 224, 243,
                                          223, 15, 117, 97, 58, 128, 50, 115, 95, 15, 117, 102, 58, 128,
                                          50, 101, 108, 24, 116, 214, 243, 129, 224, 177, 176, 13, 109, 250,
                                          76, 9, 70, 49, 48, 13, 109, 255, 76, 9, 70, 101, 114, 13, 116,
                                          56, 122, 56, 113, 238, 223, 15, 109, 123, 14, 177, 93, 110, 95, 15,
                                          109, 128, 14, 177, 93, 101, 114, 13, 116, 56, 122, 56, 113, 243,
                                          223, 15, 109, 123, 14, 177, 93, 115, 95, 15, 109, 128, 14, 177, 93,
                                          101, 114, 13, 116, 56, 122, 56, 113],
                                         [], 2, 'Characters\\Male\\UpperBodyMale.dds', None)
    assert newrecord.maleLeftHand_list == ('characters\\_Male\\LeftHand.nif', None,
                                        [229, 236, 8, 104, 208, 132, 4, 122, 101, 108, 8, 104, 213, 132, 4,
                                         122, 101, 108, 24, 116, 214, 243, 129, 224, 238, 223, 10, 104, 73,
                                         202, 29, 195, 110, 95, 10, 104, 78, 202, 29, 195, 101, 108, 24, 116,
                                         214, 243, 129, 224, 235, 243, 11, 104, 160, 170, 165, 201, 107, 115,
                                         11, 104, 165, 170, 165, 201, 101, 108, 24, 116, 214, 243, 129, 224],
                                        [], 8, 'Characters\\Male\\HandMale.dds', None)
    assert newrecord.maleRightHand_list == ('characters\\_Male\\RightHand.nif', None,
                                         [229, 236, 8, 104, 208, 132, 4, 122, 101, 108, 8, 104, 213, 132, 4,
                                          122, 101, 108, 24, 116, 214, 243, 129, 224, 238, 223, 10, 104, 73,
                                          202, 29, 195, 110, 95, 10, 104, 78, 202, 29, 195, 101, 108, 24, 116,
                                          214, 243, 129, 224, 235, 243, 11, 104, 160, 170, 165, 201, 107, 115,
                                          11, 104, 165, 170, 165, 201, 101, 108, 24, 116, 214, 243, 129, 224],
                                         [], 4, 'Characters\\Male\\HandMale.dds', None)
    assert newrecord.maleUpperBodyTexture_list == ('Characters\\_Male\\UpperBodyHumanMale.egt', None, [], [], None, None, None)
    assert newrecord.femaleUpperBody_list == ('Characters\\_Male\\FemaleUpperBody.NIF', None,
                                           [177, 176, 13, 109, 250, 76, 9, 70, 49,
                                            48, 13, 109, 255, 76, 9, 70, 101, 114,
                                            13, 116, 56, 122, 56, 113, 238, 223,
                                            15, 109, 123, 14, 177, 93, 110, 95, 15,
                                            109, 128, 14, 177, 93, 101, 114, 13,
                                            116, 56, 122, 56, 113, 243, 223, 15,
                                            109, 123, 14, 177, 93, 115, 95, 15, 109,
                                            128, 14, 177, 93, 101, 114, 13, 116, 56,
                                            122, 56, 113, 230, 242, 10, 117, 117, 224,
                                            236, 252, 102, 114, 10, 117, 122, 224,
                                            236, 252, 114, 97, 24, 116, 57, 167, 49,
                                            123, 238, 223, 12, 117, 233, 164, 206, 114,
                                            110, 95, 12, 117, 238, 164, 206, 114, 114,
                                            97, 24, 116, 57, 167, 49, 123, 229, 236, 15,
                                            117, 103, 195, 201, 238, 101, 108, 15, 117,
                                            108, 195, 201, 238, 101, 108, 26, 116, 213,
                                            12, 207, 126, 238, 223, 17, 117, 96, 45, 127,
                                            247, 110, 95, 17, 117, 101, 45, 127, 247, 101,
                                            108, 26, 116, 213, 12, 207, 126, 243, 223, 17,
                                            117, 96, 45, 127, 247, 115, 95, 17, 117, 101,
                                            45, 127, 247, 101, 108, 26, 116, 213, 12, 207,
                                            126, 235, 243, 18, 117, 73, 13, 180, 16, 107,
                                            115, 18, 117, 78, 13, 180, 16, 101, 108, 26,
                                            116, 213, 12, 207, 126],
                                           [], 2, 'Characters\\Female\\UpperBodyFemale.dds', None)
    assert newrecord.femaleLeftHand_list == ('Characters\\_Male\\FemaleLeftHand.NIF', None,
                                          [229, 236, 10, 104, 79, 83, 103, 127, 101,
                                           108, 10, 104, 84, 83, 103, 127, 101, 108,
                                           26, 116, 213, 12, 207, 126, 238, 223, 12,
                                           104, 72, 73, 131, 230, 110, 95, 12, 104,
                                           77, 73, 131, 230, 101, 108, 26, 116, 213,
                                           12, 207, 126, 235, 243, 13, 104, 97, 235,
                                           158, 254, 107, 115, 13, 104, 102, 235, 158,
                                           254, 101, 108, 26, 116, 213, 12, 207, 126],
                                          [], 8, 'Characters\\Female\\HandFemale.dds', None)
    assert newrecord.femaleRightHand_list == ('Characters\\_Male\\FemaleRightHand.NIF', None,
                                           [229, 236, 10, 104, 79, 83, 103, 127, 101,
                                            108, 10, 104, 84, 83, 103, 127, 101, 108,
                                            26, 116, 213, 12, 207, 126, 238, 223, 12,
                                            104, 72, 73, 131, 230, 110, 95, 12, 104,
                                            77, 73, 131, 230, 101, 108, 26, 116, 213,
                                            12, 207, 126, 235, 243, 13, 104, 97, 235,
                                            158, 254, 107, 115, 13, 104, 102, 235, 158,
                                            254, 101, 108, 26, 116, 213, 12, 207, 126],
                                           [], 4, 'Characters\\Female\\HandFemale.dds', None)
    assert newrecord.femaleUpperBodyTexture_list == ('Characters\\_Male\\UpperBodyHumanFemale.egt', None, [], [], None, None, None)
    assert newrecord.hairs == [('FalloutNV.esm', 0x0987DA),
                            ('FalloutNV.esm', 0x0987D8),
                            ('FalloutNV.esm', 0x044529),
                            ('FalloutNV.esm', 0x044528),
                            ('FalloutNV.esm', 0x044527),
                            ('FalloutNV.esm', 0x0987D9)]
    assert newrecord.eyes == [('FalloutNV.esm', 0x004253),
                           ('FalloutNV.esm', 0x004256),
                           ('FalloutNV.esm', 0x004255),
                           ('FalloutNV.esm', 0x004252)]
    assert newrecord.maleFggs_p == [162, 167, 106, 61, 117, 33, 170, 61, 44,
                                 80, 61, 189, 42, 95, 42, 62, 244, 137, 48,
                                 189, 210, 104, 4, 59, 198, 14, 207, 189,
                                 187, 83, 34, 61, 127, 198, 25, 190, 144,
                                 52, 225, 189, 178, 36, 134, 190, 214, 144,
                                 108, 190, 142, 78, 228, 190, 59, 168, 178,
                                 61, 113, 171, 59, 61, 33, 242, 49, 62, 94,
                                 90, 42, 191, 196, 140, 7, 61, 96, 62, 200,
                                 189, 78, 45, 55, 63, 20, 216, 133, 63, 246,
                                 181, 198, 62, 216, 142, 132, 191, 190, 117,
                                 113, 191, 149, 216, 62, 191, 130, 148, 33,
                                 63, 187, 44, 158, 190, 75, 145, 143, 191, 45,
                                 15, 183, 189, 39, 213, 46, 62, 21, 39, 93,
                                 63, 0, 7, 5, 60, 24, 87, 36, 189, 4, 45, 101,
                                 63, 96, 46, 106, 190, 97, 216, 40, 63, 130,
                                 139, 106, 62, 184, 78, 49, 63, 105, 179, 114,
                                 191, 76, 191, 19, 62, 130, 64, 218, 190, 196,
                                 230, 102, 189, 141, 188, 35, 191, 198, 62,
                                 71, 62, 244, 182, 67, 62, 48, 35, 140, 191,
                                 66, 39, 18, 63, 182, 224, 155, 62, 40, 250,
                                 153, 188, 146, 156, 140, 63]
    assert newrecord.maleFgga_p == [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    assert newrecord.maleFgts_p == [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0]
    assert newrecord.maleSnam_p == [149, 130]
    assert newrecord.femaleFggs_p == [122, 3, 147, 63, 29, 75, 137, 63, 160, 52,
                                   64, 191, 249, 100, 69, 63, 223, 130, 233,
                                   190, 33, 179, 159, 190, 159, 45, 159, 190,
                                   160, 203, 64, 63, 185, 125, 3, 191, 109,
                                   76, 39, 191, 36, 224, 37, 190, 64, 87, 109,
                                   188, 113, 124, 220, 63, 59, 137, 103, 64,
                                   54, 230, 89, 63, 120, 165, 100, 191, 132,
                                   126, 140, 63, 240, 20, 79, 192, 27, 5, 87,
                                   191, 108, 65, 167, 190, 220, 4, 250, 63,
                                   191, 113, 29, 190, 244, 159, 86, 192, 65,
                                   63, 202, 192, 10, 9, 71, 64, 14, 1, 28, 64,
                                   206, 72, 133, 191, 80, 8, 131, 192, 234, 133,
                                   176, 63, 147, 130, 204, 63, 202, 16, 178, 62,
                                   127, 42, 11, 192, 0, 120, 214, 59, 64, 85,
                                   97, 63, 14, 72, 182, 192, 44, 102, 236, 62,
                                   239, 187, 175, 63, 61, 108, 165, 63, 174, 58,
                                   132, 63, 130, 21, 86, 63, 135, 243, 12, 192,
                                   126, 13, 67, 192, 249, 237, 192, 192, 131,
                                   140, 28, 193, 197, 199, 134, 191, 208, 92,
                                   154, 190, 208, 25, 76, 190, 98, 70, 166, 64,
                                   173, 147, 165, 192, 120, 126, 78, 193]
    assert newrecord.femaleFgga_p == [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    assert newrecord.femaleFgts_p == [165, 144, 167, 190, 166, 9, 42, 190, 153,
                                   126, 193, 61, 136, 106, 149, 190, 62, 45,
                                   164, 188, 151, 117, 154, 190, 207, 220, 223,
                                   189, 233, 215, 14, 192, 233, 123, 133, 191,
                                   209, 186, 163, 62, 190, 103, 142, 62, 184,
                                   111, 192, 62, 216, 218, 48, 190, 122, 66, 124,
                                   63, 145, 197, 184, 188, 198, 171, 65, 191, 40,
                                   172, 137, 62, 217, 253, 48, 63, 5, 243, 170,
                                   61, 44, 186, 178, 62, 29, 9, 161, 63, 163, 206,
                                   119, 191, 240, 110, 143, 190, 37, 159, 30, 63,
                                   86, 230, 200, 62, 245, 118, 221, 190, 180, 74,
                                   1, 191, 75, 105, 84, 63, 189, 102, 81, 63, 254,
                                   53, 150, 62, 139, 165, 199, 62, 255, 172, 78,
                                   62, 26, 217, 8, 63, 73, 42, 239, 189, 192, 24,
                                   46, 64, 158, 40, 116, 62, 52, 142, 107, 190,
                                   152, 110, 37, 59, 167, 207, 28, 63, 43, 74, 82,
                                   63, 240, 214, 57, 64, 13, 206, 248, 191, 94,
                                   192, 75, 63, 162, 50, 13, 191, 232, 69, 57, 61,
                                   250, 185, 12, 192, 136, 103, 60, 190, 73, 32,
                                   1, 192, 209, 164, 13, 191, 107, 181, 11, 190]
    assert newrecord.femaleSnam_p == [149, 130]

    newrecord.flags1 = 10
    newrecord.versionControl1 = [1, 3, 2, 6]
    newrecord.formVersion = 1
    newrecord.versionControl2 = [2, 3]
    newrecord.eid = r'WarTest'
    
    newrecord.full = 'WarCaucasian Old'
    newrecord.description = 'This is a very boring regression test of a rather annoying record to read/write.'
    newrecord.relations_list = [(('FalloutNV.esm', 1264455), -100, 1L), (('FalloutNV.esm', 1530450), 0, 1L),
                              (('FalloutNV.esm', 111268), 0, 1L), (('FalloutNV.esm', 266421), 0, 2L),
                              (('FalloutNV.esm', 1469262), 0, 2L), (('FalloutNV.esm', 103314), 0,2L),
                              (('FalloutNV.esm', 591630), 0, 3L), (('FalloutNV.esm', 559885), 0, 2L),
                              (('FalloutNV.esm', 96729), 0, 3L), (('FalloutNV.esm', 96747), 0, 3L),
                              (('FalloutNV.esm', 1317537), 0, 2L), (('FalloutNV.esm', 1355838), 0, 2L),
                              (('FalloutNV.esm',197906), 0, 2L), (('FalloutNV.esm', 673511), 0, 0L),
                              (('FalloutNV.esm', 119275), -100, 0L), (('FalloutNV.esm', 119806),100, 2L)]
    newrecord.skill1 = 1
    newrecord.skill1Boost = 2
    newrecord.skill2 = 3
    newrecord.skill2Boost = 4
    newrecord.skill3 = 5
    newrecord.skill3Boost = 6
    newrecord.skill4 = 7
    newrecord.skill4Boost = 8
    newrecord.skill5 = 9
    newrecord.skill5Boost = 10
    newrecord.skill6 = 11
    newrecord.skill6Boost = 12
    newrecord.skill7 = 13
    newrecord.skill7Boost = 14
    newrecord.maleHeight = 1.5
    newrecord.femaleHeight = 1.6
    newrecord.maleWeight = 1.7
    newrecord.femaleWeight = 1.8
    newrecord.flags = 19
    newrecord.older = ('FalloutNV.esm', 0x00001A)
    newrecord.younger = ('FalloutNV.esm', 0x00001B)
    newrecord.maleVoice = ('FalloutNV.esm', 0x00001C)
    newrecord.femaleVoice = ('FalloutNV.esm', 0x00001D)
    newrecord.defaultHairMale = ('FalloutNV.esm', 0x00001E)
    newrecord.defaultHairFemale = ('FalloutNV.esm', 0x00001F)
    newrecord.defaultHairMaleColor = 1
    newrecord.defaultHairFemaleColor = 2
    newrecord.mainClamp = 3.0
    newrecord.faceClamp = 4.0
    newrecord.attr_p = [55, 55]
    newrecord.maleHead_list = ('War\\Head\\HeadOld.NIF', 1.0, [a for a in range(5)], [('BeardMustacheCurly:1', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 1, 'War\\Old\\HeadHuman.dds', 'War2\\Old\\HeadHuman.dds')
    newrecord.maleEars_list = ('War1\\Head', 1.1, [a for a in range(6)], [('BeardMustacheCurly:2', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 2, 'War\\Head\\EarsHuman.dds', 'War3\\Old\\HeadHuman.dds')
    newrecord.maleMouth_list = ('War\\Head\\MouthHuman.NIF', 1.2,[a for a in range(4)],[('BeardMustacheCurly:3', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 1, 'War\\Mouth\\MouthHuman.dds', 'War4\\Old\\HeadHuman.dds')
    newrecord.maleTeethLower_list = ('War\\Head\\TeethLowerHuman.NIF', 1.3,[a for a in range(16)],[('BeardMustacheCurly:4', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 2, 'War\\Mouth\\TeethLowerRaider.dds', 'War5\\Old\\HeadHuman.dds')
    newrecord.maleTeethUpper_list = ('War\\Head\\TeethUpperHuman.NIF', 1.4,[a for a in range(15)],[('BeardMustacheCurly:5', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 1, 'War\\Mouth\\TeethUpperRaider.dds', 'War6\\Old\\HeadHuman.dds')
    newrecord.maleTongue_list = ('War\\Head\\TongueHuman.NIF', 1.5,[a for a in range(14)],[('BeardMustacheCurly:6', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 2, 'War\\Mouth\\TongueRaider.dds', 'War7\\Old\\HeadHuman.dds')
    newrecord.maleLeftEye_list = ('War\\Head\\EyeLeftHuman.NIF', 1.6,[a for a in range(13)],[('BeardMustacheCurly:7', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 1, 'War1\\H3ad', 'War8\\Old\\HeadHuman.dds')
    newrecord.maleRightEye_list = ('War\\Head\\EyeRightHuman.NIF', 1.7,[a for a in range(12)],[('BeardMustacheCurly:8', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 2, 'War1\\H3ad', 'War9\\Old\\HeadHuman.dds')
    newrecord.femaleHead_list = ('War\\Head\\HeadOldFemale.NIF', 1.8,[a for a in range(1)],[('BeardMustacheCurly:9', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 2, 'War\\OldFemale\\HeadHuman.dds', 'War10\\Old\\HeadHuman.dds')
    newrecord.femaleEars_list = ('War2\\Head', 1.9, [a for a in range(4)], [], 1, 'War\\Head\\EarsHuman.dds', 'War11\\Old\\HeadHuman.dds')
    newrecord.femaleMouth_list = ('War\\Head\\MouthHuman.NIF', 2.0,[a for a in range(5)],[('BeardMustacheCurly:10', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 2, 'Characters\\Mouth\\MouthHuman.dds', 'War12\\Old\\HeadHuman.dds')
    newrecord.femaleTeethLower_list = ('War\\Head\\TeethLowerHuman.NIF', 2.1,[a for a in range(4)],[('BeardMustacheCurly:110', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 1, 'War\\Mouth\\TeethLowerHuman.dds', 'War13\\Old\\HeadHuman.dds')
    newrecord.femaleTeethUpper_list = ('War\\Head\\TeethUpperHuman.NIF', 2.2,[a for a in range(3)],[('BeardMustacheCurly:1110', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 2, 'War\\Mouth\\TeethUpperHuman.dds', 'War14\\Old\\HeadHuman.dds')
    newrecord.femaleTongue_list = ('War\\Head\\TongueHuman.NIF', 2.3,[a for a in range(9)],[('BeardMustacheCurly:11110', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 1, 'War\\Mouth\\TongueHuman.dds', 'War15\\Old\\HeadHuman.dds')
    newrecord.femaleLeftEye_list = ('War\\Head\\EyeLeftHumanFemale.NIF', 2.4,[a for a in range(8)],[('BeardMustacheCurly:111110', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 2, 'War1\\H3ad', 'War16\\Old\\HeadHuman.dds')
    newrecord.femaleRightEye_list = ('War\\Head\\EyeRightHumanFemale.NIF', 2.5,[a for a in range(7)],[('BeardMustacheCurly:a0', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 1, 'War1\\H3ad', 'War17\\Old\\HeadHuman.dds')
    newrecord.maleUpperBody_list = ('War\\_Male\\UpperBody.nif', 2.6,[a for a in range(6)],[('BeardMustacheCurly:aa0', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 2, 'War\\Male\\UpperBodyMale.dds', 'War18\\Old\\HeadHuman.dds')
    newrecord.maleLeftHand_list = ('War\\_Male\\LeftHand.nif', 2.7,[a for a in range(5)],[('BeardMustacheCurly:aaa0', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 8, 'War\\Male\\HandMale.dds', 'War19\\Old\\HeadHuman.dds')
    newrecord.maleRightHand_list = ('War\\_Male\\RightHand.nif', 2.8,[a for a in range(13)],[('BeardMustacheCurly:aaaa0', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 4, 'War\\Male\\HandMale.dds', 'War20\\Old\\HeadHuman.dds')
    newrecord.maleUpperBodyTexture_list = ('War\\_Male\\UpperBodyHumanMale.egt', 2.9, [a for a in range(3)], [('BeardMustacheCurly:aaaaa0', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 1, 'War1\\H3ad', 'War21\\Old\\HeadHuman.dds')
    newrecord.femaleUpperBody_list = ('War\\_Male\\FemaleUpperBody.NIF', 3.0,[a for a in range(12)],[('BeardMustacheCurly:0a', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 2, 'War\\Female\\UpperBodyFemale.dds', 'War22\\Old\\HeadHuman.dds')
    newrecord.femaleLeftHand_list = ('War\\_Male\\FemaleLeftHand.NIF', 3.1,[a for a in range(11)],[('BeardMustacheCurly:0aa', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 8, 'War\\Female\\HandFemale.dds', 'War23\\Old\\HeadHuman.dds')
    newrecord.femaleRightHand_list = ('War\\_Male\\FemaleRightHand.NIF', 3.2,[a for a in range(10)],[('BeardMustacheCurly:0aaa', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 4, 'War\\Female\\HandFemale.dds', 'War24\\Old\\HeadHuman.dds')
    newrecord.femaleUpperBodyTexture_list = ('War\\_Male\\UpperBodyHumanFemale.egt', 3.3, [a for a in range(2)], [('BeardMustacheCurly:0aaaa', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 2, 'War1\\H3ad', 'War25\\Old\\HeadHuman.dds')
    newrecord.hairs = [('FalloutNV.esm', 0x000001),
                            ('FalloutNV.esm', 0x000002),
                            ('FalloutNV.esm', 0x000003),
                            ('FalloutNV.esm', 0x000004),
                            ('FalloutNV.esm', 0x000005),
                            ('FalloutNV.esm', 0x000006)]
    newrecord.eyes = [('FalloutNV.esm', 0x000007),
                           ('FalloutNV.esm', 0x000008),
                           ('FalloutNV.esm', 0x000009),
                           ('FalloutNV.esm', 0x00000A)]
    newrecord.maleFggs_p = [a for a in range(200)]
    newrecord.maleFgga_p = [a for a in range(120)]
    newrecord.maleFgts_p = [a for a in range(200)]
    newrecord.maleSnam_p = [1, 2]
    newrecord.femaleFggs_p = [a for a in range(200)]
    newrecord.femaleFgga_p = [a for a in range(120)]
    newrecord.femaleFgts_p = [a for a in range(200)]
    newrecord.femaleSnam_p = [3, 4]
    
    assert newrecord.fid == ('FalloutNV.esm', 0x0987DF)
    assert newrecord.flags1 == 0x80000000 | 10
    assert newrecord.versionControl1 == [1, 3, 2, 6]
    assert newrecord.formVersion == 1
    assert newrecord.versionControl2 == [2, 3]
    assert newrecord.eid == 'WarTest'
    assert newrecord.eid == 'WArTest'
    
    assert newrecord.full == 'WarCaucasian Old'
    assert newrecord.full != 'WArCaucasian Old'
    assert newrecord.description == 'This is a very boring regression test of a rather annoying record to read/write.'
    assert newrecord.description != 'This is A very boring regression test of a rather annoying record to read/write.'
    assert newrecord.relations_list == [(('FalloutNV.esm', 1264455), -100, 1L), (('FalloutNV.esm', 1530450), 0, 1L),
                              (('FalloutNV.esm', 111268), 0, 1L), (('FalloutNV.esm', 266421), 0, 2L),
                              (('FalloutNV.esm', 1469262), 0, 2L), (('FalloutNV.esm', 103314), 0,2L),
                              (('FalloutNV.esm', 591630), 0, 3L), (('FalloutNV.esm', 559885), 0, 2L),
                              (('FalloutNV.esm', 96729), 0, 3L), (('FalloutNV.esm', 96747), 0, 3L),
                              (('FalloutNV.esm', 1317537), 0, 2L), (('FalloutNV.esm', 1355838), 0, 2L),
                              (('FalloutNV.esm',197906), 0, 2L), (('FalloutNV.esm', 673511), 0, 0L),
                              (('FalloutNV.esm', 119275), -100, 0L), (('FalloutNV.esm', 119806),100, 2L)]
    assert newrecord.skill1 == 1
    assert newrecord.skill1Boost == 2
    assert newrecord.skill2 == 3
    assert newrecord.skill2Boost == 4
    assert newrecord.skill3 == 5
    assert newrecord.skill3Boost == 6
    assert newrecord.skill4 == 7
    assert newrecord.skill4Boost == 8
    assert newrecord.skill5 == 9
    assert newrecord.skill5Boost == 10
    assert newrecord.skill6 == 11
    assert newrecord.skill6Boost == 12
    assert newrecord.skill7 == 13
    assert newrecord.skill7Boost == 14
    assert newrecord.maleHeight == 1.5
    assert newrecord.femaleHeight == 1.6
    assert newrecord.maleWeight == 1.7
    assert newrecord.femaleWeight == 1.8
    assert newrecord.flags == 19
    assert newrecord.older == ('FalloutNV.esm', 0x00001A)
    assert newrecord.younger == ('FalloutNV.esm', 0x00001B)
    assert newrecord.maleVoice == ('FalloutNV.esm', 0x00001C)
    assert newrecord.femaleVoice == ('FalloutNV.esm', 0x00001D)
    assert newrecord.defaultHairMale == ('FalloutNV.esm', 0x00001E)
    assert newrecord.defaultHairFemale == ('FalloutNV.esm', 0x00001F)
    assert newrecord.defaultHairMaleColor == 1
    assert newrecord.defaultHairFemaleColor == 2
    assert newrecord.mainClamp == 3.0
    assert newrecord.faceClamp == 4.0
    assert newrecord.attr_p == [55, 55]

    assert newrecord.maleHead_list == ('War\\Head\\HeadOld.NIF', 1.0, [a for a in range(5)], [('BeardMustacheCurly:1', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 1, 'War\\Old\\HeadHuman.dds', 'War2\\Old\\HeadHuman.dds')
    assert newrecord.maleEars_list == ('War1\\Head', 1.1, [a for a in range(6)], [('BeardMustacheCurly:2', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 2, 'War\\Head\\EarsHuman.dds', 'War3\\Old\\HeadHuman.dds')
    assert newrecord.maleMouth_list == ('War\\Head\\MouthHuman.NIF', 1.2,[a for a in range(4)],[('BeardMustacheCurly:3', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 1, 'War\\Mouth\\MouthHuman.dds', 'War4\\Old\\HeadHuman.dds')
    assert newrecord.maleTeethLower_list == ('War\\Head\\TeethLowerHuman.NIF', 1.3,[a for a in range(16)],[('BeardMustacheCurly:4', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 2, 'War\\Mouth\\TeethLowerRaider.dds', 'War5\\Old\\HeadHuman.dds')
    assert newrecord.maleTeethUpper_list == ('War\\Head\\TeethUpperHuman.NIF', 1.4,[a for a in range(15)],[('BeardMustacheCurly:5', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 1, 'War\\Mouth\\TeethUpperRaider.dds', 'War6\\Old\\HeadHuman.dds')
    assert newrecord.maleTongue_list == ('War\\Head\\TongueHuman.NIF', 1.5,[a for a in range(14)],[('BeardMustacheCurly:6', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 2, 'War\\Mouth\\TongueRaider.dds', 'War7\\Old\\HeadHuman.dds')
    assert newrecord.maleLeftEye_list == ('War\\Head\\EyeLeftHuman.NIF', 1.6,[a for a in range(13)],[('BeardMustacheCurly:7', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 1, 'War1\\H3ad', 'War8\\Old\\HeadHuman.dds')
    assert newrecord.maleRightEye_list == ('War\\Head\\EyeRightHuman.NIF', 1.7,[a for a in range(12)],[('BeardMustacheCurly:8', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 2, 'War1\\H3ad', 'War9\\Old\\HeadHuman.dds')
    assert newrecord.femaleHead_list == ('War\\Head\\HeadOldFemale.NIF', 1.8,[a for a in range(1)],[('BeardMustacheCurly:9', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 2, 'War\\OldFemale\\HeadHuman.dds', 'War10\\Old\\HeadHuman.dds')
    assert newrecord.femaleEars_list == ('War2\\Head', 1.9, [a for a in range(4)], [], 1, 'War\\Head\\EarsHuman.dds', 'War11\\Old\\HeadHuman.dds')
    assert newrecord.femaleMouth_list == ('War\\Head\\MouthHuman.NIF', 2.0,[a for a in range(5)],[('BeardMustacheCurly:10', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 2, 'Characters\\Mouth\\MouthHuman.dds', 'War12\\Old\\HeadHuman.dds')
    assert newrecord.femaleTeethLower_list == ('War\\Head\\TeethLowerHuman.NIF', 2.1,[a for a in range(4)],[('BeardMustacheCurly:110', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 1, 'War\\Mouth\\TeethLowerHuman.dds', 'War13\\Old\\HeadHuman.dds')
    assert newrecord.femaleTeethUpper_list == ('War\\Head\\TeethUpperHuman.NIF', 2.2,[a for a in range(3)],[('BeardMustacheCurly:1110', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 2, 'War\\Mouth\\TeethUpperHuman.dds', 'War14\\Old\\HeadHuman.dds')
    assert newrecord.femaleTongue_list == ('War\\Head\\TongueHuman.NIF', 2.3,[a for a in range(9)],[('BeardMustacheCurly:11110', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 1, 'War\\Mouth\\TongueHuman.dds', 'War15\\Old\\HeadHuman.dds')
    assert newrecord.femaleLeftEye_list == ('War\\Head\\EyeLeftHumanFemale.NIF', 2.4,[a for a in range(8)],[('BeardMustacheCurly:111110', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 2, 'War1\\H3ad', 'War16\\Old\\HeadHuman.dds')
    assert newrecord.femaleRightEye_list == ('War\\Head\\EyeRightHumanFemale.NIF', 2.5,[a for a in range(7)],[('BeardMustacheCurly:a0', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 1, 'War1\\H3ad', 'War17\\Old\\HeadHuman.dds')
    assert newrecord.maleUpperBody_list == ('War\\_Male\\UpperBody.nif', 2.6,[a for a in range(6)],[('BeardMustacheCurly:aa0', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 2, 'War\\Male\\UpperBodyMale.dds', 'War18\\Old\\HeadHuman.dds')
    assert newrecord.maleLeftHand_list == ('War\\_Male\\LeftHand.nif', 2.7,[a for a in range(5)],[('BeardMustacheCurly:aaa0', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 8, 'War\\Male\\HandMale.dds', 'War19\\Old\\HeadHuman.dds')
    assert newrecord.maleRightHand_list == ('War\\_Male\\RightHand.nif', 2.8,[a for a in range(13)],[('BeardMustacheCurly:aaaa0', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 4, 'War\\Male\\HandMale.dds', 'War20\\Old\\HeadHuman.dds')
    assert newrecord.maleUpperBodyTexture_list == ('War\\_Male\\UpperBodyHumanMale.egt', 2.9, [a for a in range(3)], [('BeardMustacheCurly:aaaaa0', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 1, 'War1\\H3ad', 'War21\\Old\\HeadHuman.dds')
    assert newrecord.femaleUpperBody_list == ('War\\_Male\\FemaleUpperBody.NIF', 3.0,[a for a in range(12)],[('BeardMustacheCurly:0a', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 2, 'War\\Female\\UpperBodyFemale.dds', 'War22\\Old\\HeadHuman.dds')
    assert newrecord.femaleLeftHand_list == ('War\\_Male\\FemaleLeftHand.NIF', 3.1,[a for a in range(11)],[('BeardMustacheCurly:0aa', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 8, 'War\\Female\\HandFemale.dds', 'War23\\Old\\HeadHuman.dds')
    assert newrecord.femaleRightHand_list == ('War\\_Male\\FemaleRightHand.NIF', 3.2,[a for a in range(10)],[('BeardMustacheCurly:0aaa', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 4, 'War\\Female\\HandFemale.dds', 'War24\\Old\\HeadHuman.dds')
    assert newrecord.femaleUpperBodyTexture_list == ('War\\_Male\\UpperBodyHumanFemale.egt', 3.3, [a for a in range(2)], [('BeardMustacheCurly:0aaaa', ('FalloutNV.esm', 653607), -1),('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)], 2, 'War1\\H3ad', 'War25\\Old\\HeadHuman.dds')
    assert newrecord.hairs == [('FalloutNV.esm', 0x000001),
                            ('FalloutNV.esm', 0x000002),
                            ('FalloutNV.esm', 0x000003),
                            ('FalloutNV.esm', 0x000004),
                            ('FalloutNV.esm', 0x000005),
                            ('FalloutNV.esm', 0x000006)]
    assert newrecord.eyes == [('FalloutNV.esm', 0x000007),
                           ('FalloutNV.esm', 0x000008),
                           ('FalloutNV.esm', 0x000009),
                           ('FalloutNV.esm', 0x00000A)]
    assert newrecord.maleFggs_p == [a for a in range(200)]
    assert newrecord.maleFgga_p == [a for a in range(120)]
    assert newrecord.maleFgts_p == [a for a in range(200)]
    assert newrecord.maleSnam_p == [1, 2]
    assert newrecord.femaleFggs_p == [a for a in range(200)]
    assert newrecord.femaleFgga_p == [a for a in range(120)]
    assert newrecord.femaleFgts_p == [a for a in range(200)]
    assert newrecord.femaleSnam_p == [3, 4]

    assert record.fid == ('FalloutNV.esm', 0x0987DF)
    assert record.flags1 == 0x80000000L
    assert record.versionControl1 == [16, 66, 39, 0]
    assert record.formVersion == 15
    assert record.versionControl2 == [5, 0]
    assert record.eid == 'CaucasianOldAged'
    assert record.eid == 'CAucasianOldAged'
    
    assert record.full == 'Caucasian Old'
    assert record.full != 'CAucasian Old'
    assert record.description == None
    assert record.relations_list == []
    assert record.skill1 == -1
    assert record.skill1Boost == 0
    assert record.skill2 == -1
    assert record.skill2Boost == 0
    assert record.skill3 == -1
    assert record.skill3Boost == 0
    assert record.skill4 == -1
    assert record.skill4Boost == 0
    assert record.skill5 == -1
    assert record.skill5Boost == 0
    assert record.skill6 == -1
    assert record.skill6Boost == 0
    assert record.skill7 == -1
    assert record.skill7Boost == 0
    assert record.maleHeight == 1.0
    assert record.femaleHeight == 1.0
    assert record.maleWeight == 1.0
    assert record.femaleWeight == 1.0
    assert record.flags == 0x0L
    assert record.older == None
    assert record.younger == ('FalloutNV.esm', 0x000019)
    assert record.maleVoice == ('FalloutNV.esm', 0x019FD2)
    assert record.femaleVoice == ('FalloutNV.esm', 0x00002E)
    assert record.defaultHairMale == ('FalloutNV.esm', 0x0987DA)
    assert record.defaultHairFemale == ('FalloutNV.esm', 0x044529)
    assert record.defaultHairMaleColor == 1
    assert record.defaultHairFemaleColor == 1
    assert record.mainClamp == 5.0
    assert record.faceClamp == 3.0
    assert record.attr_p == [5, 5]
    assert record.maleHead_list == ('Characters\\Head\\HeadOld.NIF', None,
                                    [238, 225, 9, 104, 61, 251, 66, 106, 110, 97, 9,
                                     104, 66, 251, 66, 106, 101, 108, 24, 116, 214,
                                     243, 129, 224, 238, 223, 11, 104, 138, 215, 34,
                                     197, 110, 95, 11, 104, 143, 215, 34, 197, 101,
                                     108, 24, 116, 214, 243, 129, 224, 243, 223, 11,
                                     104, 138, 215, 34, 197, 115, 95, 11, 104, 143,
                                     215, 34, 197, 101, 108, 24, 116, 214, 243, 129,
                                     224, 235, 243, 12, 104, 159, 237, 36, 86, 107,
                                     115, 12, 104, 164, 237, 36, 86, 101, 108, 24,
                                     116, 214, 243, 129, 224],
                                    [], 2, 'Characters\\Old\\HeadHuman.dds', None)
    assert record.maleEars_list == (None, None, [], [], None, 'Characters\\Head\\EarsHuman.dds', None)
    assert record.maleMouth_list == ('Characters\\Head\\MouthHuman.NIF', None,
                                     [238, 225, 10, 109, 43, 201, 76, 110, 110, 97,
                                      10, 109, 48, 201, 76, 110, 104, 116, 25, 116,
                                      145, 5, 223, 51, 238, 223, 6, 102, 132, 76, 107,
                                      195, 110, 95, 6, 102, 137, 76, 107, 195, 100, 101,
                                      15, 116, 246, 82, 111, 175, 243, 223, 6, 102, 132,
                                      76, 107, 195, 115, 95, 6, 102, 137, 76, 107, 195,
                                      100, 101, 15, 116, 246, 82, 111, 175],
                                     [], None, 'Characters\\Mouth\\MouthHuman.dds', None)
    assert record.maleTeethLower_list == ('Characters\\Head\\TeethLowerHuman.NIF', None,
                                          [238, 225, 15, 116, 216, 76, 118, 0, 110,97, 15,
                                           116, 221, 76, 118, 0, 104, 116, 25, 116, 145, 5,
                                           223, 51, 238, 223, 6, 102, 132, 76, 107, 195, 110,
                                           95, 6, 102,137, 76, 107, 195, 100, 101, 15, 116,
                                           246, 82, 111, 175, 243, 223, 6, 102, 132, 76, 107,
                                           195, 115, 95, 6, 102, 137, 76,107, 195, 100, 101,
                                           15, 116, 246, 82, 111, 175],
                                          [], None, 'Characters\\Mouth\\TeethLowerRaider.dds', None)
    assert record.maleTeethUpper_list == ('Characters\\Head\\TeethUpperHuman.NIF', None,
                                          [238, 225, 15, 116, 87, 210, 9, 247, 110,97, 15,
                                           116, 92, 210, 9, 247, 104, 116, 25, 116, 145, 5,
                                           223, 51, 238, 223, 6, 102, 132, 76, 107, 195, 110,
                                           95, 6, 102,137, 76, 107, 195, 100, 101, 15, 116,
                                           246, 82, 111, 175, 243, 223, 6, 102, 132, 76, 107,
                                           195, 115, 95, 6, 102, 137, 76,107, 195, 100, 101,
                                           15, 116, 246, 82, 111, 175],
                                          [], None, 'Characters\\Mouth\\TeethUpperRaider.dds', None)
    assert record.maleTongue_list == ('Characters\\Head\\TongueHuman.NIF', None,
                                      [238, 225, 11, 116, 205, 135, 184, 206, 110, 97, 11, 116,
                                       210, 135, 184, 206, 104, 116, 25, 116, 145, 5, 223, 51,
                                       238, 223, 6, 102, 132, 76, 107, 195, 110, 95, 6, 102,
                                       137, 76, 107, 195, 100, 101, 15, 116, 246, 82, 111, 175,
                                       243, 223, 6, 102, 132, 76, 107, 195, 115, 95, 6, 102,
                                       137, 76, 107, 195, 100, 101, 15, 116, 246, 82, 111, 175],
                                      [], None, 'Characters\\Mouth\\TongueRaider.dds', None)
    assert record.maleLeftEye_list == ('Characters\\Head\\EyeLeftHuman.NIF', None,
                                       [244, 236, 10, 101, 18, 128, 201, 157, 116, 108, 10,
                                        101, 23, 128, 201, 157, 115, 101, 24, 116, 246, 241,
                                        121, 224, 238, 223, 6, 102, 132, 76, 107, 195, 110,
                                        95, 6,102, 137, 76, 107, 195, 100, 101, 15, 116, 246,
                                        82, 111, 175, 243, 223, 6, 102, 132, 76, 107, 195,
                                        115, 95, 6, 102, 137, 76, 107, 195, 100, 101, 15, 116,
                                        246, 82, 111, 175],
                                       [], None, None, None)
    assert record.maleRightEye_list == ('Characters\\Head\\EyeRightHuman.NIF', None,
                                        [244, 236, 10, 101, 18, 128, 201, 157, 116,108, 10,
                                         101, 23, 128, 201, 157, 115, 101, 24, 116, 246, 241,
                                         121, 224, 238, 223, 6, 102, 132, 76, 107, 195, 110,
                                         95, 6, 102, 137, 76, 107, 195, 100, 101, 15, 116, 246,
                                         82, 111, 175, 243, 223, 6, 102, 132, 76, 107, 195, 115,
                                         95, 6, 102, 137, 76, 107, 195, 100, 101, 15, 116, 246,
                                         82, 111, 175],
                                        [], None, None, None)
    assert record.femaleHead_list == ('Characters\\Head\\HeadOldFemale.NIF', None,
                                      [238, 225, 9, 104, 61, 251, 66, 106, 110, 97, 9, 104, 66,
                                       251, 66, 106, 101, 108, 24, 116, 214, 243, 129, 224, 238,
                                       223, 11, 104, 138, 215, 34, 197, 110, 95, 11, 104, 143,
                                       215, 34, 197, 101, 108, 24, 116, 214, 243, 129, 224, 243,
                                       223, 11, 104, 138, 215, 34, 197, 115, 95, 11, 104, 143,
                                       215, 34, 197, 101, 108, 24, 116, 214, 243, 129, 224, 235,
                                       243, 12, 104, 159, 237, 36, 86, 107, 115, 12, 104, 164,
                                       237, 36, 86, 101, 108, 26, 116, 213, 12, 207, 126],
                                      [], 2, 'Characters\\OldFemale\\HeadHuman.dds', None)
    assert record.femaleEars_list == (None, None, [], [], None, 'Characters\\Head\\EarsHuman.dds', None)
    assert record.femaleMouth_list == ('Characters\\Head\\MouthHuman.NIF', None,
                                       [238, 225, 10, 109, 43, 201, 76, 110, 110, 97,10, 109, 48,
                                        201, 76, 110, 104, 116, 25, 116, 145, 5, 223, 51, 238,
                                        223, 6, 102, 132, 76, 107, 195, 110, 95, 6, 102, 137, 76,
                                        107, 195, 100, 101, 15, 116, 246, 82, 111, 175, 243, 223,
                                        6, 102, 132, 76, 107, 195, 115, 95, 6, 102, 137, 76, 107,
                                        195, 100, 101, 15, 116, 246, 82, 111, 175],
                                       [], None, 'Characters\\Mouth\\MouthHuman.dds', None)
    assert record.femaleTeethLower_list == ('Characters\\Head\\TeethLowerHuman.NIF', None,
                                            [238, 225, 15, 116, 216, 76, 118, 0, 110,97, 15, 116,
                                             221, 76, 118, 0, 104, 116, 25, 116, 145, 5, 223, 51,
                                             238, 223, 6, 102, 132, 76, 107, 195, 110, 95, 6, 102,
                                             137, 76, 107, 195, 100, 101, 15, 116, 246, 82, 111,
                                             175, 243, 223, 6, 102, 132, 76, 107, 195, 115, 95, 6,
                                             102, 137, 76,107, 195, 100, 101, 15, 116, 246, 82, 111,
                                             175],
                                            [], None, 'Characters\\Mouth\\TeethLowerHuman.dds', None)
    assert record.femaleTeethUpper_list == ('Characters\\Head\\TeethUpperHuman.NIF', None,
                                            [238, 225, 15, 116, 87, 210, 9, 247, 110,97, 15, 116,
                                             92, 210, 9, 247, 104, 116, 25, 116, 145, 5, 223, 51,
                                             238, 223, 6, 102, 132, 76, 107, 195, 110, 95, 6, 102,
                                             137, 76, 107, 195, 100, 101, 15, 116, 246, 82, 111,
                                             175, 243, 223, 6, 102, 132, 76, 107, 195, 115, 95, 6,
                                             102, 137, 76,107, 195, 100, 101, 15, 116, 246, 82, 111,
                                             175],
                                            [], None, 'Characters\\Mouth\\TeethUpperHuman.dds', None)
    assert record.femaleTongue_list == ('Characters\\Head\\TongueHuman.NIF', None,
                                        [238, 225, 11, 116, 205, 135, 184, 206, 110, 97, 11, 116, 210,
                                         135, 184, 206, 104, 116, 25, 116, 145, 5, 223, 51, 238, 223,
                                         6, 102, 132, 76, 107, 195, 110, 95, 6, 102, 137, 76, 107, 195,
                                         100, 101, 15, 116, 246, 82, 111, 175, 243, 223, 6, 102, 132,
                                         76, 107, 195, 115, 95, 6, 102, 137, 76, 107, 195, 100, 101, 15,
                                         116, 246, 82, 111, 175],
                                        [], None, 'Characters\\Mouth\\TongueHuman.dds', None)
    assert record.femaleLeftEye_list == ('Characters\\Head\\EyeLeftHumanFemale.NIF', None,
                                         [244, 236, 10, 101, 18, 128, 201, 157,116, 108, 10, 101, 23,
                                          128, 201, 157, 115, 101, 24, 116, 246, 241, 121, 224, 238,
                                          223, 6, 102, 132, 76, 107, 195, 110, 95, 6, 102, 137, 76, 107,
                                          195, 100, 101, 15, 116, 246, 82, 111, 175, 243, 223, 6, 102,
                                          132, 76, 107, 195, 115, 95, 6, 102, 137, 76, 107, 195, 100, 101,
                                          15, 116, 246, 82, 111, 175],
                                         [], None, None, None)
    assert record.femaleRightEye_list == ('Characters\\Head\\EyeRightHumanFemale.NIF', None,
                                          [244, 236, 10, 101, 18, 128, 201, 157, 116, 108, 10, 101, 23,
                                           128, 201, 157, 115, 101, 24, 116, 246, 241, 121, 224, 238,
                                           223, 6, 102, 132, 76, 107, 195, 110, 95, 6, 102, 137, 76, 107,
                                           195, 100, 101, 15, 116, 246, 82, 111, 175, 243, 223, 6, 102,
                                           132, 76, 107, 195, 115, 95, 6, 102, 137, 76, 107, 195, 100, 101,
                                           15, 116, 246, 82, 111, 175],
                                          [], None, None, None)
    assert record.maleUpperBody_list == ('characters\\_Male\\UpperBody.nif', None,
                                         [237, 242, 10, 117, 117, 224, 236, 252, 109, 114, 10, 117, 122,
                                          224, 236, 252, 114, 97, 24, 116, 57, 167, 49, 123, 238, 223,
                                          12, 117, 240, 164, 206, 114, 110, 95, 12, 117, 245, 164, 206, 114,
                                          114, 97, 24, 116, 57, 167, 49, 123, 229, 236, 13, 117, 232, 128,
                                          83, 141, 101, 108, 13, 117, 237, 128, 83, 141, 101, 108, 24, 116, 214,
                                          243, 129, 224, 238, 223, 15, 117, 97, 58, 128, 50, 110, 95, 15,
                                          117, 102, 58, 128, 50, 101, 108, 24, 116, 214, 243, 129, 224, 243,
                                          223, 15, 117, 97, 58, 128, 50, 115, 95, 15, 117, 102, 58, 128,
                                          50, 101, 108, 24, 116, 214, 243, 129, 224, 177, 176, 13, 109, 250,
                                          76, 9, 70, 49, 48, 13, 109, 255, 76, 9, 70, 101, 114, 13, 116,
                                          56, 122, 56, 113, 238, 223, 15, 109, 123, 14, 177, 93, 110, 95, 15,
                                          109, 128, 14, 177, 93, 101, 114, 13, 116, 56, 122, 56, 113, 243,
                                          223, 15, 109, 123, 14, 177, 93, 115, 95, 15, 109, 128, 14, 177, 93,
                                          101, 114, 13, 116, 56, 122, 56, 113],
                                         [], 2, 'Characters\\Male\\UpperBodyMale.dds', None)
    assert record.maleLeftHand_list == ('characters\\_Male\\LeftHand.nif', None,
                                        [229, 236, 8, 104, 208, 132, 4, 122, 101, 108, 8, 104, 213, 132, 4,
                                         122, 101, 108, 24, 116, 214, 243, 129, 224, 238, 223, 10, 104, 73,
                                         202, 29, 195, 110, 95, 10, 104, 78, 202, 29, 195, 101, 108, 24, 116,
                                         214, 243, 129, 224, 235, 243, 11, 104, 160, 170, 165, 201, 107, 115,
                                         11, 104, 165, 170, 165, 201, 101, 108, 24, 116, 214, 243, 129, 224],
                                        [], 8, 'Characters\\Male\\HandMale.dds', None)
    assert record.maleRightHand_list == ('characters\\_Male\\RightHand.nif', None,
                                         [229, 236, 8, 104, 208, 132, 4, 122, 101, 108, 8, 104, 213, 132, 4,
                                          122, 101, 108, 24, 116, 214, 243, 129, 224, 238, 223, 10, 104, 73,
                                          202, 29, 195, 110, 95, 10, 104, 78, 202, 29, 195, 101, 108, 24, 116,
                                          214, 243, 129, 224, 235, 243, 11, 104, 160, 170, 165, 201, 107, 115,
                                          11, 104, 165, 170, 165, 201, 101, 108, 24, 116, 214, 243, 129, 224],
                                         [], 4, 'Characters\\Male\\HandMale.dds', None)
    assert record.maleUpperBodyTexture_list == ('Characters\\_Male\\UpperBodyHumanMale.egt', None, [], [], None, None, None)
    assert record.femaleUpperBody_list == ('Characters\\_Male\\FemaleUpperBody.NIF', None,
                                           [177, 176, 13, 109, 250, 76, 9, 70, 49,
                                            48, 13, 109, 255, 76, 9, 70, 101, 114,
                                            13, 116, 56, 122, 56, 113, 238, 223,
                                            15, 109, 123, 14, 177, 93, 110, 95, 15,
                                            109, 128, 14, 177, 93, 101, 114, 13,
                                            116, 56, 122, 56, 113, 243, 223, 15,
                                            109, 123, 14, 177, 93, 115, 95, 15, 109,
                                            128, 14, 177, 93, 101, 114, 13, 116, 56,
                                            122, 56, 113, 230, 242, 10, 117, 117, 224,
                                            236, 252, 102, 114, 10, 117, 122, 224,
                                            236, 252, 114, 97, 24, 116, 57, 167, 49,
                                            123, 238, 223, 12, 117, 233, 164, 206, 114,
                                            110, 95, 12, 117, 238, 164, 206, 114, 114,
                                            97, 24, 116, 57, 167, 49, 123, 229, 236, 15,
                                            117, 103, 195, 201, 238, 101, 108, 15, 117,
                                            108, 195, 201, 238, 101, 108, 26, 116, 213,
                                            12, 207, 126, 238, 223, 17, 117, 96, 45, 127,
                                            247, 110, 95, 17, 117, 101, 45, 127, 247, 101,
                                            108, 26, 116, 213, 12, 207, 126, 243, 223, 17,
                                            117, 96, 45, 127, 247, 115, 95, 17, 117, 101,
                                            45, 127, 247, 101, 108, 26, 116, 213, 12, 207,
                                            126, 235, 243, 18, 117, 73, 13, 180, 16, 107,
                                            115, 18, 117, 78, 13, 180, 16, 101, 108, 26,
                                            116, 213, 12, 207, 126],
                                           [], 2, 'Characters\\Female\\UpperBodyFemale.dds', None)
    assert record.femaleLeftHand_list == ('Characters\\_Male\\FemaleLeftHand.NIF', None,
                                          [229, 236, 10, 104, 79, 83, 103, 127, 101,
                                           108, 10, 104, 84, 83, 103, 127, 101, 108,
                                           26, 116, 213, 12, 207, 126, 238, 223, 12,
                                           104, 72, 73, 131, 230, 110, 95, 12, 104,
                                           77, 73, 131, 230, 101, 108, 26, 116, 213,
                                           12, 207, 126, 235, 243, 13, 104, 97, 235,
                                           158, 254, 107, 115, 13, 104, 102, 235, 158,
                                           254, 101, 108, 26, 116, 213, 12, 207, 126],
                                          [], 8, 'Characters\\Female\\HandFemale.dds', None)
    assert record.femaleRightHand_list == ('Characters\\_Male\\FemaleRightHand.NIF', None,
                                           [229, 236, 10, 104, 79, 83, 103, 127, 101,
                                            108, 10, 104, 84, 83, 103, 127, 101, 108,
                                            26, 116, 213, 12, 207, 126, 238, 223, 12,
                                            104, 72, 73, 131, 230, 110, 95, 12, 104,
                                            77, 73, 131, 230, 101, 108, 26, 116, 213,
                                            12, 207, 126, 235, 243, 13, 104, 97, 235,
                                            158, 254, 107, 115, 13, 104, 102, 235, 158,
                                            254, 101, 108, 26, 116, 213, 12, 207, 126],
                                           [], 4, 'Characters\\Female\\HandFemale.dds', None)
    assert record.femaleUpperBodyTexture_list == ('Characters\\_Male\\UpperBodyHumanFemale.egt', None, [], [], None, None, None)
    assert record.hairs == [('FalloutNV.esm', 0x0987DA),
                            ('FalloutNV.esm', 0x0987D8),
                            ('FalloutNV.esm', 0x044529),
                            ('FalloutNV.esm', 0x044528),
                            ('FalloutNV.esm', 0x044527),
                            ('FalloutNV.esm', 0x0987D9)]
    assert record.eyes == [('FalloutNV.esm', 0x004253),
                           ('FalloutNV.esm', 0x004256),
                           ('FalloutNV.esm', 0x004255),
                           ('FalloutNV.esm', 0x004252)]
    assert record.maleFggs_p == [162, 167, 106, 61, 117, 33, 170, 61, 44,
                                 80, 61, 189, 42, 95, 42, 62, 244, 137, 48,
                                 189, 210, 104, 4, 59, 198, 14, 207, 189,
                                 187, 83, 34, 61, 127, 198, 25, 190, 144,
                                 52, 225, 189, 178, 36, 134, 190, 214, 144,
                                 108, 190, 142, 78, 228, 190, 59, 168, 178,
                                 61, 113, 171, 59, 61, 33, 242, 49, 62, 94,
                                 90, 42, 191, 196, 140, 7, 61, 96, 62, 200,
                                 189, 78, 45, 55, 63, 20, 216, 133, 63, 246,
                                 181, 198, 62, 216, 142, 132, 191, 190, 117,
                                 113, 191, 149, 216, 62, 191, 130, 148, 33,
                                 63, 187, 44, 158, 190, 75, 145, 143, 191, 45,
                                 15, 183, 189, 39, 213, 46, 62, 21, 39, 93,
                                 63, 0, 7, 5, 60, 24, 87, 36, 189, 4, 45, 101,
                                 63, 96, 46, 106, 190, 97, 216, 40, 63, 130,
                                 139, 106, 62, 184, 78, 49, 63, 105, 179, 114,
                                 191, 76, 191, 19, 62, 130, 64, 218, 190, 196,
                                 230, 102, 189, 141, 188, 35, 191, 198, 62,
                                 71, 62, 244, 182, 67, 62, 48, 35, 140, 191,
                                 66, 39, 18, 63, 182, 224, 155, 62, 40, 250,
                                 153, 188, 146, 156, 140, 63]
    assert record.maleFgga_p == [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    assert record.maleFgts_p == [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0]
    assert record.maleSnam_p == [149, 130]
    assert record.femaleFggs_p == [122, 3, 147, 63, 29, 75, 137, 63, 160, 52,
                                   64, 191, 249, 100, 69, 63, 223, 130, 233,
                                   190, 33, 179, 159, 190, 159, 45, 159, 190,
                                   160, 203, 64, 63, 185, 125, 3, 191, 109,
                                   76, 39, 191, 36, 224, 37, 190, 64, 87, 109,
                                   188, 113, 124, 220, 63, 59, 137, 103, 64,
                                   54, 230, 89, 63, 120, 165, 100, 191, 132,
                                   126, 140, 63, 240, 20, 79, 192, 27, 5, 87,
                                   191, 108, 65, 167, 190, 220, 4, 250, 63,
                                   191, 113, 29, 190, 244, 159, 86, 192, 65,
                                   63, 202, 192, 10, 9, 71, 64, 14, 1, 28, 64,
                                   206, 72, 133, 191, 80, 8, 131, 192, 234, 133,
                                   176, 63, 147, 130, 204, 63, 202, 16, 178, 62,
                                   127, 42, 11, 192, 0, 120, 214, 59, 64, 85,
                                   97, 63, 14, 72, 182, 192, 44, 102, 236, 62,
                                   239, 187, 175, 63, 61, 108, 165, 63, 174, 58,
                                   132, 63, 130, 21, 86, 63, 135, 243, 12, 192,
                                   126, 13, 67, 192, 249, 237, 192, 192, 131,
                                   140, 28, 193, 197, 199, 134, 191, 208, 92,
                                   154, 190, 208, 25, 76, 190, 98, 70, 166, 64,
                                   173, 147, 165, 192, 120, 126, 78, 193]
    assert record.femaleFgga_p == [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    assert record.femaleFgts_p == [165, 144, 167, 190, 166, 9, 42, 190, 153,
                                   126, 193, 61, 136, 106, 149, 190, 62, 45,
                                   164, 188, 151, 117, 154, 190, 207, 220, 223,
                                   189, 233, 215, 14, 192, 233, 123, 133, 191,
                                   209, 186, 163, 62, 190, 103, 142, 62, 184,
                                   111, 192, 62, 216, 218, 48, 190, 122, 66, 124,
                                   63, 145, 197, 184, 188, 198, 171, 65, 191, 40,
                                   172, 137, 62, 217, 253, 48, 63, 5, 243, 170,
                                   61, 44, 186, 178, 62, 29, 9, 161, 63, 163, 206,
                                   119, 191, 240, 110, 143, 190, 37, 159, 30, 63,
                                   86, 230, 200, 62, 245, 118, 221, 190, 180, 74,
                                   1, 191, 75, 105, 84, 63, 189, 102, 81, 63, 254,
                                   53, 150, 62, 139, 165, 199, 62, 255, 172, 78,
                                   62, 26, 217, 8, 63, 73, 42, 239, 189, 192, 24,
                                   46, 64, 158, 40, 116, 62, 52, 142, 107, 190,
                                   152, 110, 37, 59, 167, 207, 28, 63, 43, 74, 82,
                                   63, 240, 214, 57, 64, 13, 206, 248, 191, 94,
                                   192, 75, 63, 162, 50, 13, 191, 232, 69, 57, 61,
                                   250, 185, 12, 192, 136, 103, 60, 190, 73, 32,
                                   1, 192, 209, 164, 13, 191, 107, 181, 11, 190]
    assert record.femaleSnam_p == [149, 130]

    print "RACE:Finished testing"

def assertSOUN(Current, newMod):
    record = Current.LoadOrderMods[0].SOUN[0]
    d(record)
    return
    assert record.fid == ('FalloutNV.esm', 0x0945BA)
    assert record.flags1 == 0x80000000L
    assert record.versionControl1 == [9, 76, 1, 0]
    assert record.formVersion == 15
    assert record.versionControl2 == [0, 0]
    assert record.eid == 'DLCPittEyeGreenMut'
    assert record.eid == 'DLCPittEyEGreenMut'
    
    assert record.full == 'Green'
    assert record.full != 'GreEn'
    assert record.iconPath == r'Characters\SOUN\EyeGreenMutantHuman.dds'
    assert record.iconPath == r'ChAracters\SOUN\EyeGreenMutantHuman.dds'
    assert record.flags == 0x0
    
    nrecord = newMod.create_SOUN()

    nrecord.flags1 = 10
    nrecord.versionControl1 = [1, 3, 2, 6]
    nrecord.formVersion = 1
    nrecord.versionControl2 = [2, 3]
    nrecord.eid = r'WarTest'
    
    nrecord.full = 'Green'
    nrecord.iconPath = r'Characters\SOUN\EyeGreenMutantHuman.dds'
    nrecord.flags = 0x0
    
    assert nrecord.fid == ('RegressionTests.esp', 0x00100C)
    assert nrecord.flags1 == 0x80000000 | 10
    assert nrecord.versionControl1 == [1, 3, 2, 6]
    assert nrecord.formVersion == 1
    assert nrecord.versionControl2 == [2, 3]
    assert nrecord.eid == 'WarTest'
    assert nrecord.eid == 'WArTest'
    
    assert nrecord.full == 'Green'
    assert nrecord.full != 'GrEen'
    assert nrecord.iconPath == r'Characters\SOUN\EyeGreenMutantHuman.dds'
    assert nrecord.iconPath == r'ChAracters\SOUN\EyeGreenMutantHuman.dds'
    assert nrecord.flags == 0x0

    record = Current.LoadOrderMods[0].SOUN[0]
    newrecord = record.CopyAsOverride(newMod)

    assert newrecord.fid == ('FalloutNV.esm', 0x0945BA)
    assert newrecord.flags1 == 0x80000000L
    assert newrecord.versionControl1 == [9, 76, 1, 0]
    assert newrecord.formVersion == 15
    assert newrecord.versionControl2 == [0, 0]
    assert newrecord.eid == 'DLCPittEyeGreenMut'
    assert newrecord.eid == 'DLCPittEyEGreenMut'
    
    assert newrecord.full == 'Green'
    assert newrecord.full != 'GreEn'
    assert newrecord.iconPath == r'Characters\SOUN\EyeGreenMutantHuman.dds'
    assert newrecord.iconPath == r'ChAracters\SOUN\EyeGreenMutantHuman.dds'
    assert newrecord.flags == 0x0

    newrecord.flags1 = 10
    newrecord.versionControl1 = [1, 3, 2, 6]
    newrecord.formVersion = 1
    newrecord.versionControl2 = [2, 3]
    newrecord.eid = 'WarTest'
    
    newrecord.full = 'Green'
    newrecord.iconPath = r'Characters\SOUN\EyeGreenMutantHuman.dds'
    newrecord.flags = 0x0
    
    assert newrecord.fid == ('FalloutNV.esm', 0x0945BA)
    assert newrecord.flags1 == 0x80000000 | 10
    assert newrecord.versionControl1 == [1, 3, 2, 6]
    assert newrecord.formVersion == 1
    assert newrecord.versionControl2 == [2, 3]
    assert newrecord.eid == 'WarTest'
    assert newrecord.eid == 'WArTest'
    
    assert newrecord.full == 'Green'
    assert newrecord.full != 'GrEen'
    assert newrecord.iconPath == r'Characters\SOUN\EyeGreenMutantHuman.dds'
    assert newrecord.iconPath == r'ChAracters\SOUN\EyeGreenMutantHuman.dds'
    assert newrecord.flags == 0x0

    assert record.fid == ('FalloutNV.esm', 0x0945BA)
    assert record.flags1 == 0x80000000L
    assert record.versionControl1 == [9, 76, 1, 0]
    assert record.formVersion == 15
    assert record.versionControl2 == [0, 0]
    assert record.eid == 'DLCPittEyeGreenMut'
    assert record.eid == 'DLCPittEyEGreenMut'
    
    assert record.full == 'Green'
    assert record.full != 'GreEn'
    assert record.iconPath == r'Characters\SOUN\EyeGreenMutantHuman.dds'
    assert record.iconPath == r'ChAracters\SOUN\EyeGreenMutantHuman.dds'
    assert record.flags == 0x0

    print "SOUN:Finished testing"

from timeit import Timer

##print "1TestMinimalLoad"
##test = [Timer('TestMinimalLoad()', 'from __main__ import TestMinimalLoad').timeit(1) for x in range(0, 1)]
##mini = min(test)
##avgi = sum(test) / len(test)
##maxi = max(test)
##print "Min:%.15f, Avg:%.15f, Max:%.15f" % (mini, avgi, maxi)

##print "10TestMinimalLoad"
##test = [Timer('TestMinimalLoad()', 'from __main__ import TestMinimalLoad').timeit(1) for x in range(0, 10)]
##mini = min(test)
##avgi = sum(test) / len(test)
##maxi = max(test)
##print "Min:%.15f, Avg:%.15f, Max:%.15f" % (mini, avgi, maxi)

##print "1TestFullLoad"
##test = [Timer('TestFullLoad()', 'from __main__ import TestFullLoad').timeit(1) for x in range(0, 1)]
##mini = min(test)
##avgi = sum(test) / len(test)
##maxi = max(test)
##print "Min:%.15f, Avg:%.15f, Max:%.15f" % (mini, avgi, maxi)

##print "10TestFullLoad"
##test = [Timer('TestFullLoad()', 'from __main__ import TestFullLoad').timeit(1) for x in range(0, 10)]
##mini = min(test)
##avgi = sum(test) / len(test)
##maxi = max(test)
##print "Min:%.15f, Avg:%.15f, Max:%.15f" % (mini, avgi, maxi)

##phonenumber = raw_input(">")

##print "1TestReadWriteAll"
##test = [Timer('TestReadWriteAll()', 'from __main__ import TestReadWriteAll').timeit(1) for x in range(0, 1)]
##mini = min(test)
##avgi = sum(test) / len(test)
##maxi = max(test)
##print "Min:%.15f, Avg:%.15f, Max:%.15f" % (mini, avgi, maxi)

##phonenumber = raw_input(">")
##Current = ObCollection()
####Current.addMod("Oblivion.esm")
####print "MinLoad"
##Current.addMod("Oblivion.esm", MinLoad=False)
##print "FullLoad"
####Current.addMod("Oscuro's_Oblivion_Overhaul.esp")
####Current.fullLoad(LoadMasters=True)
##Current.load()
##phonenumber = raw_input(">")
##del Current
##phonenumber = raw_input("!")

regressionTests()