from ctypes import *
CBash = CDLL("CBash.dll")

Current = Collection()

Current.addMod("Test.esm")
Current.load(["GMST"], LoadMasters=True, FullLoad=True)

TouchedMods = Current.getChangedMods()
for ModName in TouchedMods:
    if ModName == "Test.esm":
        Current.safeSaveMod("Test.esm")

##Current.safeSaveAllChangedMods()


##FilteredRecords = Current.FilterRecords(GMSTRecords, "EDID", Equals, "*")

del Current
