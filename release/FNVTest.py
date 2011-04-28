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
    Current.addMod("FalloutNV.esm")
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
    newMod.save()

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
    assert record.modt_p == [238, 236, 12, 98, 148, 160, 189, 156, 110, 108, 12, 98, 153, 160, 189, 156, 114, 105, 24, 116, 155, 242, 124, 224, 238, 223, 14, 98, 22, 68, 125, 197, 110, 95, 14, 98, 27, 68, 125, 197, 114, 105, 24, 116, 155, 242, 124, 224, 243, 223, 14, 98, 22, 68, 125, 197, 115, 95, 14, 98, 27, 68, 125, 197, 114, 105, 24, 116, 155, 242, 124, 224, 236, 232, 15, 98, 19, 164, 241, 216, 108, 104, 15, 98, 24, 164, 241, 216, 114, 105, 24, 116, 155, 242, 124, 224]
    assert record.altTextures_list == [('BeardMustacheCurly:0', ('FalloutNV.esm', 653607), -1), ('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)]
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
    nrecord.altTextures_list = [('BeardMustacheCurly:1', ('FalloutNV.esm', 653606), -2), ('BeardMustacheCuRly:0', ('FalloutNV.esm', 653607), -1), ('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)]
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
    assert nrecord.altTextures_list == [('BeardMustacheCurly:1', ('FalloutNV.esm', 653606), -2), ('BeardMustacheCuRly:0', ('FalloutNV.esm', 653607), -1), ('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)]
    assert nrecord.modelFlags == 0x01
    assert nrecord.flags == 0x2
    assert nrecord.parts == [('FalloutNV.esm', 653606)]

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
    assert newrecord.modt_p == [238, 236, 12, 98, 148, 160, 189, 156, 110, 108, 12, 98, 153, 160, 189, 156, 114, 105, 24, 116, 155, 242, 124, 224, 238, 223, 14, 98, 22, 68, 125, 197, 110, 95, 14, 98, 27, 68, 125, 197, 114, 105, 24, 116, 155, 242, 124, 224, 243, 223, 14, 98, 22, 68, 125, 197, 115, 95, 14, 98, 27, 68, 125, 197, 114, 105, 24, 116, 155, 242, 124, 224, 236, 232, 15, 98, 19, 164, 241, 216, 108, 104, 15, 98, 24, 164, 241, 216, 114, 105, 24, 116, 155, 242, 124, 224]
    assert newrecord.altTextures_list == [('BeardMustacheCurly:0', ('FalloutNV.esm', 653607), -1), ('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)]
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
    newrecord.altTextures_list = [('BeardMustacheCurly:1', ('FalloutNV.esm', 653606), -2), ('BeardMustacheCuRly:0', ('FalloutNV.esm', 653607), -1), ('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)]
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
    assert newrecord.altTextures_list == [('BeardMustacheCurly:1', ('FalloutNV.esm', 653606), -2), ('BeardMustacheCuRly:0', ('FalloutNV.esm', 653607), -1), ('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)]
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
    assert record.modt_p == [238, 236, 12, 98, 148, 160, 189, 156, 110, 108, 12, 98, 153, 160, 189, 156, 114, 105, 24, 116, 155, 242, 124, 224, 238, 223, 14, 98, 22, 68, 125, 197, 110, 95, 14, 98, 27, 68, 125, 197, 114, 105, 24, 116, 155, 242, 124, 224, 243, 223, 14, 98, 22, 68, 125, 197, 115, 95, 14, 98, 27, 68, 125, 197, 114, 105, 24, 116, 155, 242, 124, 224, 236, 232, 15, 98, 19, 164, 241, 216, 108, 104, 15, 98, 24, 164, 241, 216, 114, 105, 24, 116, 155, 242, 124, 224]
    assert record.altTextures_list == [('BeardMustacheCurly:0', ('FalloutNV.esm', 653607), -1), ('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)]
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
    assert record.modt_p == [249, 236, 15, 104, 106, 177, 7, 48, 121, 108, 15, 104, 111, 177, 7, 48, 114, 105, 24, 116, 155, 242, 124, 224, 238, 223, 17, 104, 247, 73, 32, 158, 110, 95, 17, 104, 252, 73, 32, 158, 114, 105, 24, 116, 155, 242, 124, 224, 243, 223, 17, 104, 247, 73, 32, 158, 115, 95, 17, 104, 252, 73, 32, 158, 114, 105, 24, 116, 155, 242, 124, 224, 236, 232, 18, 104, 114, 22, 241, 46, 108, 104, 18, 104, 119, 22, 241, 46, 114, 105, 24, 116, 155, 242, 124, 224]
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
    nrecord.altTextures_list = [('BeardMustacheCurly:1', ('FalloutNV.esm', 653606), -2), ('BeardMustacheCuRly:0', ('FalloutNV.esm', 653607), -1), ('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)]
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
    assert nrecord.altTextures_list == [('BeardMustacheCurly:1', ('FalloutNV.esm', 653606), -2), ('BeardMustacheCuRly:0', ('FalloutNV.esm', 653607), -1), ('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)]
    assert nrecord.modelFlags == 0x3
    assert nrecord.iconPath == r'War\Hair\HairChildMCurly.dds'
    assert nrecord.iconPath == r'WAr\Hair\HairChildMCurly.dds'
    assert nrecord.flags == 0x4

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
    assert newrecord.modt_p == [249, 236, 15, 104, 106, 177, 7, 48, 121, 108, 15, 104, 111, 177, 7, 48, 114, 105, 24, 116, 155, 242, 124, 224, 238, 223, 17, 104, 247, 73, 32, 158, 110, 95, 17, 104, 252, 73, 32, 158, 114, 105, 24, 116, 155, 242, 124, 224, 243, 223, 17, 104, 247, 73, 32, 158, 115, 95, 17, 104, 252, 73, 32, 158, 114, 105, 24, 116, 155, 242, 124, 224, 236, 232, 18, 104, 114, 22, 241, 46, 108, 104, 18, 104, 119, 22, 241, 46, 114, 105, 24, 116, 155, 242, 124, 224]
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
    newrecord.altTextures_list = [('BeardMustacheCurly:1', ('FalloutNV.esm', 653606), -2), ('BeardMustacheCuRly:0', ('FalloutNV.esm', 653607), -1), ('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)]
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
    assert newrecord.altTextures_list == [('BeardMustacheCurly:1', ('FalloutNV.esm', 653606), -2), ('BeardMustacheCuRly:0', ('FalloutNV.esm', 653607), -1), ('BeardMustacheCurly:0', ('FalloutNV.esm',653605), 0)]
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
    assert record.modt_p == [249, 236, 15, 104, 106, 177, 7, 48, 121, 108, 15, 104, 111, 177, 7, 48, 114, 105, 24, 116, 155, 242, 124, 224, 238, 223, 17, 104, 247, 73, 32, 158, 110, 95, 17, 104, 252, 73, 32, 158, 114, 105, 24, 116, 155, 242, 124, 224, 243, 223, 17, 104, 247, 73, 32, 158, 115, 95, 17, 104, 252, 73, 32, 158, 114, 105, 24, 116, 155, 242, 124, 224, 236, 232, 18, 104, 114, 22, 241, 46, 108, 104, 18, 104, 119, 22, 241, 46, 114, 105, 24, 116, 155, 242, 124, 224]
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