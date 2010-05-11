from ctypes import *
CBash = CDLL("CBash.dll")

class Collection:
    """Collection of esm/esp's."""

    def __init__(self, selfID=None):
        if selfID:
            self.ID = selfID
        else:
            self.ID = CBash.NewCollection()

    def addMod(self, ModName):
        CBash.AddMod(self.ID, ModName)

    def load(self, RecordTypes, LoadMasters=False, FullLoad=False):
        for recordType in RecordTypes:
            if recordType is string:
                CBash.PrepLoad(self.ID, recordType)
        CBash.LoadPreppedRecordTypes(self.ID, LoadMasters, FullLoad)

    def close(self):
        CBash.Close(self.ID)

    def __del__(self):
        self.close()
        CBash.DeleteCollection(self.ID)

    def getGMSTRecords(self):
        return CBash.GetGMSTRecords(self.ID)        

    def getChangedMods(self):
        return CBash.GetChangedMods(self.ID)

    def safeSaveMod(self, ModName):
        return CBash.SafeSaveMod(self.ID, ModName)

    def safeSaveAllChangedMods(self):
        return CBash.SafeSaveAllChangedMods(self.ID)    

    def readRecordField(self, recordFID, FieldName):
        return CBash.ReadRecordField(self.ID, recordFID, FieldName)

    def setRecordField(self, recordFID, FieldName, FieldValue):
        return CBash.SetRecordField(self.ID, recordFID, FieldName, FieldValue)

    def newRecord(self, ModName, RecordType):
        return CBash.NewRecord(self.ID, ModName, RecordType)    
    
Current = Collection()

Current.addMod("Test.esm")
Current.load(["GMST"], LoadMasters=True, FullLoad=True)

GMSTRecords = Current.getGMSTRecords()
for record in GMSTRecords:
    EDID = Current.readRecordField(record, "EDID")
    DATA = Current.readRecordField(record, "DATA")
    print EDID
    print DATA
    Current.setRecordField(record, "EDID", EDID + "1")
    print Current.readRecordField(record, "EDID")
    print Current.readRecordField(record, "DATA")
print "Done\n"

NewGMST = Current.newRecord("Test.esm", "GMST")
Current.setRecordField(NewGMST, "EDID", "sTestING")
Current.setRecordField(NewGMST, "DATA", "This was a test")

GMSTRecords = Current.getGMSTRecords()
for record in GMSTRecords:
    if record == NewGMST:
        EDID = Current.readRecordField(record, "EDID")
        DATA = Current.readRecordField(record, "DATA")
        print EDID
        print DATA

TouchedMods = Current.getChangedMods()
for ModName in TouchedMods:
    if ModName == "Test.esm":
        Current.safeSaveMod("Test.esm")

##Current.safeSaveAllChangedMods()


##FilteredRecords = Current.FilterRecords(GMSTRecords, "EDID", Equals, "*")

del Current
