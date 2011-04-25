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