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

def assertTES4(Current, newMod):
    record = Current.LoadOrderMods[0].TES4

    assert record.IsESM
    assert record.flags1 == 0x80000001
    assert record.flags2 == 0
    assert record.version == 1.0
    assert record.numRecords == 1252095
    assert record.nextObject == 0xFF09764D
    assert record.ofst_p == [0, 2, 0, 0, 78, 79, 78, 69, 0, 0, 0, 0, 1, 233, 142, 87,
                             84, 69, 83, 52, 0, 0, 0, 0, 2, 235, 195, 1, 71, 82, 85,
                             80, 0, 0, 0, 0, 3, 0, 0, 0, 71, 77, 83, 84, 0, 0, 0, 0,
                             4, 105, 111, 110, 71, 76, 79, 66, 0, 0, 0, 0, 5, 0, 0,
                             0, 67, 76, 65, 83, 0, 0, 0, 0, 6, 0, 0, 0, 70, 65, 67,
                             84, 0, 0, 0, 0, 7, 0, 0, 0, 72, 65, 73, 82, 0, 0, 0, 0,
                             8, 0, 0, 0, 69, 89, 69, 83, 0, 0, 0, 0, 9, 0, 0, 0, 82,
                             65, 67, 69, 0, 0, 0, 0, 10, 0, 0, 0, 83, 79, 85, 78, 0,
                             0, 0, 0, 11, 0, 0,0, 83, 75, 73, 76, 0, 0, 0, 0, 12, 0,
                             0, 0, 77, 71, 69, 70, 0, 0, 0, 0, 13, 0, 0, 0, 83, 67,
                             80, 84, 0, 0, 0, 0, 14, 0,0, 0, 76, 84, 69, 88, 0, 0,
                             0, 0, 15, 0, 0, 0, 69, 78, 67, 72, 0, 0, 0, 0, 16, 0,
                             0, 0, 83, 80, 69, 76, 0, 0, 0, 0, 17,0, 0, 0, 66, 83,
                             71, 78, 0, 0, 0, 0, 18, 0, 0, 0, 65, 67, 84, 73, 0, 0,
                             0, 0, 19, 0, 0, 0, 65, 80, 80, 65, 0, 0, 0, 0, 20, 0,
                             0, 0, 65, 82, 77, 79, 0, 0, 0, 0, 21, 0, 0, 0, 66, 79,
                             79, 75, 0, 0, 0, 0, 22, 0, 0, 0, 67, 76, 79, 84, 0, 0,
                             0, 0, 23, 0, 0, 0, 67, 79, 78, 84, 0, 0, 0, 0, 24, 68,
                             249, 119, 68, 79, 79, 82, 0, 0, 0, 0, 25, 19, 20, 0,
                             73, 78, 71, 82,0, 0, 0, 0, 26, 138, 245, 119, 76, 73,
                             71, 72, 0, 0, 0, 0, 27, 0, 0, 0, 76, 79, 67, 75, 0, 0,
                             0, 0, 28, 0, 0, 0, 77, 73, 83, 67, 0, 0, 0, 0, 29, 0,
                             0, 0, 82, 69, 80, 65, 0, 0, 0, 0, 30, 194, 245, 119,
                             83, 84, 65, 84, 0, 0, 0, 0, 31, 245, 18, 0, 84, 82,
                             69, 69, 0, 0, 0, 0, 32, 0, 0, 0, 70, 76, 79, 82, 0, 0,
                             0, 0, 33, 0, 0, 0, 70, 85, 82, 78, 0, 0, 0, 0, 34, 0,
                             0, 0, 87, 69, 65, 80, 0, 0, 0, 0, 35, 2, 0, 0, 65, 77,
                             77, 79, 0, 0, 0, 0, 36, 0, 0, 0, 78, 80, 67, 95, 0, 0,
                             0, 0, 37, 219, 111, 0, 67, 82, 69, 65, 0, 0, 0, 0, 38,
                             0, 0, 0, 76, 86, 76, 67, 0, 0, 0, 0, 39, 162, 112, 0,
                             83, 76, 71, 77, 0,0, 0, 0, 40, 0, 0, 0, 75, 69, 89, 77,
                             0, 0, 0, 0, 41, 107, 143, 0, 65, 76, 67, 72, 0, 0, 0,
                             0, 42, 245, 18, 0, 76, 86, 76, 73, 0, 0, 0, 0, 43, 167,
                             111, 0, 83, 78, 68, 71, 0, 0, 0, 0, 44, 220, 111, 0,
                             67, 76, 77, 84, 0, 0, 0, 0, 45, 222, 111, 0, 82, 69,
                             71, 78, 0, 0, 0, 0, 46, 217, 111, 0, 67, 69, 76, 76,
                             65, 254, 121, 17, 47, 107, 143, 0, 82, 69, 70, 82, 0,
                             0, 0, 0, 48, 29, 228, 1, 65, 67, 72, 82, 0, 0, 0, 0,
                             49, 0, 0, 0, 65, 67, 82, 69, 0, 0, 0, 0, 50, 0, 0, 0,
                             80, 71, 82,68, 0, 0, 0, 0, 51, 0, 0, 0, 87, 82, 76, 68,
                             0, 0, 0, 0, 52, 184, 218, 1, 76, 65, 78, 68, 0, 0, 0,
                             0, 53, 180, 218, 1, 84, 76, 79, 68, 0, 0, 0, 0, 54, 0,
                             0, 0, 68, 73, 65, 76, 0, 0, 0, 0, 55, 0, 218, 1, 73,
                             78, 70, 79, 0, 0, 0, 0, 56, 184, 218, 1, 81, 85, 83,
                             84, 0, 0, 0, 0]
    assert record.dele_p == [101, 84, 43, 226, 70, 177, 196, 1]
    assert record.author == "mlipari"
    assert record.description == " "
    assert record.masters == []

    record = newMod.TES4
    record.flags1 = 5
    record.flags2 = 12
    record.version = 1.2
    record.numRecords = 10
    record.nextObject = 0x00001000
    record.ofst_p = [0, 1, 2, 3]
    record.dele_p = [10, 11, 12, 13]
    record.author = "Waruddar"
    record.description = "This is a test string\nand only a test string."
##    record.masters = ["Oblivion.esm"] #For now, masters shouldn't be set directly. More coding needs to be done to make it safe
    assert record.flags1 ==  5 | 0x80000000 #CBash sets 0x80000000 for internal use
    assert record.flags2 == 12
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

    print "TES4:Finished testing"


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

##TestTemp()
##TestAttrReport()
##TestCopyAttrs()
##TestCleanMasters()
##TestFullLoad()
##TestMinimalLoad()
##TestLoadMasters()
##TestDeleteRecord()
##TestReadWriteAll()
##TestTES4()
##TestGMST()
##TestGLOB()
##TestCLAS()
##TestFACT()
##TestHAIR()
##TestEYES()
##TestRACE()
##TestSOUN()
##TestSKIL()
##TestMGEF()
##TestSCPT()
##TestLTEX()
##TestENCH()
##TestSPEL()
##TestBSGN()
##TestACTI()
##TestAPPA()
##TestARMO()
##TestBOOK()
##TestCLOT()
##TestCONT()
##TestDOOR()
##TestINGR()
##TestLIGH()
##TestMISC()
##TestSTAT()
##TestGRAS()
##TestTREE()
##TestFLOR()
##TestFURN()
##TestWEAP()
##TestAMMO()
##TestNPC_()
##TestCREA()
##TestLVLC()
##TestSLGM()
##TestKEYM()
##TestALCH()
##TestSBSP()
##TestSGST()
##TestLVLI()
##TestWTHR()
##TestCLMT()
##TestREGN()
##TestCELL()
##TestWRLD()
##TestDIAL()
##TestQUST()
##TestIDLE()
##TestPACK()
##TestCSTY()
##TestLSCR()
##TestLVSP()
##TestANIO()
##TestWATR()
##TestEFSH()
####Current.debug(6, True)
##print "Entirely Finished\n"

##del Current
