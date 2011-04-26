from cint import *

RecIndent = -2
def printRecord(record):
    global RecIndent
    RecIndent += 2
    if hasattr(record, 'copyattrs'):
        for attr in record.copyattrs:
            rec = getattr(record, attr)
            if RecIndent: print " " * (RecIndent - 1),
            print attr, ":", rec
            printRecord(rec)
    elif isinstance(record, list):
        if len(record) > 0 and hasattr(record[0], 'copyattrs'):
            for rec in record:
                printRecord(rec)
    RecIndent -= 2

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