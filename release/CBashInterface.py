from ctypes import *
import struct

CBash = CDLL("CBash.dll")

class BaseRecord(object):
    def __init__(self, CollectionIndex, ModName, recordID, parentID = None):
        self._CollectionIndex = CollectionIndex
        self._ModName = ModName
        self._recordID = recordID
        self._parentID = parentID
    def CopyAsOverride(self, targetMod):
        CBash.CopyFIDRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(True))
        return
    def CopyAsNew(self, targetMod):
        CBash.CopyFIDRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(False))
        return
    def get_flags1(self):
        CBash.ReadFIDField.restype = POINTER(c_int)
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 2).contents.value
    def set_flags1(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 2, nValue)
    flags1 = property(get_flags1, set_flags1)
    def get_fid(self):
        CBash.ReadFIDField.restype = POINTER(c_int)
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 3).contents.value
    def set_fid(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 3, nValue)
    fid = property(get_fid, set_fid)
    def get_flags2(self):
        CBash.ReadFIDField.restype = POINTER(c_int)
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 4).contents.value
    def set_flags2(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 4, nValue)
    flags2 = property(get_flags2, set_flags2)
    def get_eid(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 5)
    def set_eid(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 5, nValue)
    eid = property(get_eid, set_eid)

class TES4Record(object):
    def __init__(self, CollectionIndex, ModName):
        self._CollectionIndex = CollectionIndex
        self._ModName = ModName
    def get_recType(self):
        CBash.ReadTES4Field.restype = POINTER(c_uint)
        return CBash.ReadTES4Field(self._CollectionIndex, self._ModName, 0).contents.value
    def set_recType(self, nValue):
        CBash.SetTES4FieldUI(self._CollectionIndex, self._ModName, 0, nValue)
    recType = property(get_recType, set_recType)
    @property
    def size(self):
        CBash.ReadTES4Field.restype = POINTER(c_ulong)
        return CBash.ReadTES4Field(self._CollectionIndex, self._ModName, 1).contents.value
    def get_flags1(self):
        CBash.ReadTES4Field.restype = POINTER(c_uint)
        return CBash.ReadTES4Field(self._CollectionIndex, self._ModName, 2).contents.value
    def set_flags1(self, nValue):
        CBash.SetTES4FieldUI(self._CollectionIndex, self._ModName, 2, nValue)
    flags1 = property(get_flags1, set_flags1)
    def get_flags2(self):
        CBash.ReadTES4Field.restype = POINTER(c_uint)
        return CBash.ReadTES4Field(self._CollectionIndex, self._ModName, 4).contents.value
    def set_flags2(self, nValue):
        CBash.SetTES4FieldUI(self._CollectionIndex, self._ModName, 4, nValue)
    flags2 = property(get_flags2, set_flags2)
    def get_version(self):
        CBash.ReadTES4Field.restype = POINTER(c_float)
        return CBash.ReadTES4Field(self._CollectionIndex, self._ModName, 6).contents.value
    def set_version(self, nValue):
        CBash.SetTES4FieldF(self._CollectionIndex, self._ModName, 6, c_float(nValue))
    version = property(get_version, set_version)
    def get_numRecords(self):
        CBash.ReadTES4Field.restype = POINTER(c_uint)
        return CBash.ReadTES4Field(self._CollectionIndex, self._ModName, 7).contents.value
    def set_numRecords(self, nValue):
        CBash.SetTES4FieldUI(self._CollectionIndex, self._ModName, 7, nValue)
    numRecords = property(get_numRecords, set_numRecords)
    def get_nextObject(self):
        CBash.ReadTES4Field.restype = POINTER(c_uint)
        return CBash.ReadTES4Field(self._CollectionIndex, self._ModName, 8).contents.value
    def set_nextObject(self, nValue):
        CBash.SetTES4FieldUI(self._CollectionIndex, self._ModName, 8, nValue)
    nextObject = property(get_nextObject, set_nextObject)
    def get_ofst_p(self):
        numRecords = CBash.GetTES4FieldArraySize(self._CollectionIndex, self._ModName, 9)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetTES4FieldArray(self._CollectionIndex, self._ModName, 9, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_ofst_p(self, nValue):
        length = len(nValue)
        CBash.SetTES4FieldR(self._CollectionIndex, self._ModName, 9, struct.pack('B' * length, *nValue), length)
    ofst_p = property(get_ofst_p, set_ofst_p)
    def get_dele_p(self):
        numRecords = CBash.GetTES4FieldArraySize(self._CollectionIndex, self._ModName, 10)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetTES4FieldArray(self._CollectionIndex, self._ModName, 10, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_dele_p(self, nValue):
        length = len(nValue)
        CBash.SetTES4FieldR(self._CollectionIndex, self._ModName, 10, struct.pack('B' * length, *nValue), length)
    dele_p = property(get_dele_p, set_dele_p)
    def get_author(self):
        CBash.ReadTES4Field.restype = c_char_p
        return CBash.ReadTES4Field(self._CollectionIndex, self._ModName, 11)
    def set_author(self, nValue):
        CBash.SetTES4FieldStr(self._CollectionIndex, self._ModName, 11, nValue)
    author = property(get_author, set_author)
    def get_description(self):
        CBash.ReadTES4Field.restype = c_char_p
        return CBash.ReadTES4Field(self._CollectionIndex, self._ModName, 12)
    def set_description(self, nValue):
        CBash.SetTES4FieldStr(self._CollectionIndex, self._ModName, 12, nValue)
    description = property(get_description, set_description)
    def get_masters(self):
        numRecords = CBash.GetTES4FieldArraySize(self._CollectionIndex, self._ModName, 13)
        if(numRecords > 0):
            cRecords = (POINTER(c_char_p) * numRecords)()
            CBash.GetTES4FieldArray(self._CollectionIndex, self._ModName, 13, cRecords)
            return [string_at(cRecords[x]) for x in range(0, numRecords)]
        else: return []
    def set_masters(self, nValue):
        length = len(nValue)
        cRecords = (c_char_p * length)(*nValue)
        CBash.SetTES4FieldStrA(self._CollectionIndex, self._ModName, 13, byref(cRecords), length)
    masters = property(get_masters, set_masters)
    @property
    def DATA(self):
        return 0

class GMSTRecord(object):
    def __init__(self, CollectionIndex, ModName, recordID):
        self._CollectionIndex = CollectionIndex
        self._ModName = ModName
        self._recordID = recordID
    def CopyAsOverride(self, targetMod):
        recID = CBash.CopyGMSTRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName)
        if(recID): return GLOBRecord(self._CollectionIndex, targetMod._ModName, self._recordID)
        return None

    def get_recType(self):
        CBash.ReadGMSTField.restype = POINTER(c_int)
        return CBash.ReadGMSTField(self._CollectionIndex, self._ModName, self._recordID, 0).contents.value
    def set_recType(self, nValue):
        CBash.SetGMSTFieldUI(self._CollectionIndex, self._ModName, self._recordID, 0, nValue)
    recType = property(get_recType, set_recType)
    @property
    def size(self):
        CBash.ReadGMSTField.restype = POINTER(c_ulong)
        return CBash.ReadGMSTField(self._CollectionIndex, self._ModName, self._recordID, 1).contents.value
    def get_flags1(self):
        CBash.ReadGMSTField.restype = POINTER(c_int)
        return CBash.ReadGMSTField(self._CollectionIndex, self._ModName, self._recordID, 2).contents.value
    def set_flags1(self, nValue):
        CBash.SetGMSTFieldUI(self._CollectionIndex, self._ModName, self._recordID, 2, nValue)
    flags1 = property(get_flags1, set_flags1)
    def get_fid(self):
        CBash.ReadGMSTField.restype = POINTER(c_int)
        return CBash.ReadGMSTField(self._CollectionIndex, self._ModName, self._recordID, 3).contents.value
    def set_fid(self, nValue):
        CBash.SetGMSTFieldUI(self._CollectionIndex, self._ModName, self._recordID, 3, nValue)
    fid = property(get_fid, set_fid)
    def get_flags2(self):
        CBash.ReadGMSTField.restype = POINTER(c_int)
        return CBash.ReadGMSTField(self._CollectionIndex, self._ModName, self._recordID, 4).contents.value
    def set_flags2(self, nValue):
        CBash.SetGMSTFieldUI(self._CollectionIndex, self._ModName, self._recordID, 4, nValue)
    flags2 = property(get_flags2, set_flags2)
    @property
    def eid(self):
        #eid, unsettable due to conflicts with GMST_ModFile_Record
        CBash.ReadGMSTField.restype = c_char_p
        return CBash.ReadGMSTField(self._CollectionIndex, self._ModName, self._recordID, 5)
    def get_value(self):
        rFormat = CBash.GetGMSTFieldType(self._CollectionIndex, self._ModName, self._recordID, 6)
        if(rFormat == -1):
            return None
        elif(rFormat == 1):
            CBash.ReadGMSTField.restype = POINTER(c_int)
        elif(rFormat == 2):
            CBash.ReadGMSTField.restype = POINTER(c_float)
        elif(rFormat == 3):
            CBash.ReadGMSTField.restype = c_char_p
            return CBash.ReadGMSTField(self._CollectionIndex, self._ModName, self._recordID, 6)
        return CBash.ReadGMSTField(self._CollectionIndex, self._ModName, self._recordID, 6).contents.value
    def set_value(self, nValue):
        rFormat = CBash.GetGMSTFieldType(self._CollectionIndex, self._ModName, self._recordID, 6)
        if(rFormat == 1 and type(nValue) is int):
            CBash.SetGMSTFieldI(self._CollectionIndex, self._ModName, self._recordID, 6, nValue)
        elif(rFormat == 2 and type(nValue) is float):
            CBash.SetGMSTFieldF(self._CollectionIndex, self._ModName, self._recordID, 6, c_float(nValue))
        elif(rFormat == 3 and type(nValue) is str):
            CBash.SetGMSTFieldStr(self._CollectionIndex, self._ModName, self._recordID, 6, nValue)
    value = property(get_value, set_value)

class GLOBRecord(BaseRecord):
    def CopyAsOverride(self, targetMod):
        FID = CBash.CopyGLOBRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(True))
        if(FID): return GLOBRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def CopyAsNew(self, targetMod):
        FID = CBash.CopyGLOBRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(False))
        if(FID): return GLOBRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def get_format(self):
        CBash.ReadFIDField.restype = POINTER(c_char)
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 6).contents.value
    def set_format(self, nValue):
        CBash.SetFIDFieldC(self._CollectionIndex, self._ModName, self._recordID, 6, c_char(nValue))
    format = property(get_format, set_format)
    def get_value(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 7).contents.value
    def set_value(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 7, c_float(nValue))
    value = property(get_value, set_value)
    
class CLASRecord(BaseRecord):
    def CopyAsOverride(self, targetMod):
        FID = CBash.CopyCLASRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(True))
        if(FID): return CLASRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def CopyAsNew(self, targetMod):
        FID = CBash.CopyCLASRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(False))
        if(FID): return CLASRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def get_full(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 6)
    def set_full(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 6, nValue)
    full = property(get_full, set_full)
    def get_description(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 7)
    def set_description(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 7, nValue)
    description = property(get_description, set_description)
    def get_iconPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 8)
    def set_iconPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 8, nValue)
    iconPath = property(get_iconPath, set_iconPath)
    def get_primary1(self):
        CBash.ReadFIDField.restype = POINTER(c_int)
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 9).contents.value
    def set_primary1(self, nValue):
        CBash.SetFIDFieldI(self._CollectionIndex, self._ModName, self._recordID, 9, nValue)
    primary1 = property(get_primary1, set_primary1)
    def get_primary2(self):
        CBash.ReadFIDField.restype = POINTER(c_int)
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 10).contents.value
    def set_primary2(self, nValue):
        CBash.SetFIDFieldI(self._CollectionIndex, self._ModName, self._recordID, 10, nValue)
        
    primary2 = property(get_primary2, set_primary2)
    def get_specialization(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 11).contents.value
    def set_specialization(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 11, nValue)
        
    specialization = property(get_specialization, set_specialization)
    def get_major1(self):
        CBash.ReadFIDField.restype = POINTER(c_int)
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 12).contents.value
    def set_major1(self, nValue):
        CBash.SetFIDFieldI(self._CollectionIndex, self._ModName, self._recordID, 12, nValue)
        
    major1 = property(get_major1, set_major1)
    def get_major2(self):
        CBash.ReadFIDField.restype = POINTER(c_int)
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 13).contents.value
    def set_major2(self, nValue):
        CBash.SetFIDFieldI(self._CollectionIndex, self._ModName, self._recordID, 13, nValue)
        
    major2 = property(get_major2, set_major2)
    def get_major3(self):
        CBash.ReadFIDField.restype = POINTER(c_int)
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 14).contents.value
    def set_major3(self, nValue):
        CBash.SetFIDFieldI(self._CollectionIndex, self._ModName, self._recordID, 14, nValue)
        
    major3 = property(get_major3, set_major3)
    def get_major4(self):
        CBash.ReadFIDField.restype = POINTER(c_int)
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 15).contents.value
    def set_major4(self, nValue):
        CBash.SetFIDFieldI(self._CollectionIndex, self._ModName, self._recordID, 15, nValue)
        
    major4 = property(get_major4, set_major4)
    def get_major5(self):
        CBash.ReadFIDField.restype = POINTER(c_int)
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 16).contents.value
    def set_major5(self, nValue):
        CBash.SetFIDFieldI(self._CollectionIndex, self._ModName, self._recordID, 16, nValue)
        
    major5 = property(get_major5, set_major5)
    def get_major6(self):
        CBash.ReadFIDField.restype = POINTER(c_int)
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 17).contents.value
    def set_major6(self, nValue):
        CBash.SetFIDFieldI(self._CollectionIndex, self._ModName, self._recordID, 17, nValue)
        
    major6 = property(get_major6, set_major6)
    def get_major7(self):
        CBash.ReadFIDField.restype = POINTER(c_int)
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 18).contents.value
    def set_major7(self, nValue):
        CBash.SetFIDFieldI(self._CollectionIndex, self._ModName, self._recordID, 18, nValue)
        
    major7 = property(get_major7, set_major7)
    def get_flags(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 19).contents.value
    def set_flags(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 19, nValue)
        
    flags = property(get_flags, set_flags)
    def get_services(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 20).contents.value
    def set_services(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 20, nValue)
    services = property(get_services, set_services)
    def get_trainSkill(self):
        CBash.ReadFIDField.restype = POINTER(c_byte)
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 21).contents.value
    def set_trainSkill(self, nValue):
        CBash.SetFIDFieldC(self._CollectionIndex, self._ModName, self._recordID, 21, c_byte(nValue))
    trainSkill = property(get_trainSkill, set_trainSkill)
    def get_trainLevel(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 22).contents.value
    def set_trainLevel(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 22, c_ubyte(nValue))
    trainLevel = property(get_trainLevel, set_trainLevel)
    def get_unused1(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 23)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 23, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_unused1(self, nValue):
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 23, struct.pack('2B', *nValue), 2)
    unused1 = property(get_unused1, set_unused1)

class FACTRecord(BaseRecord):
    def CopyAsOverride(self, targetMod):
        FID = CBash.CopyFACTRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(True))
        if(FID): return FACTRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def CopyAsNew(self, targetMod):
        FID = CBash.CopyFACTRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(False))
        if(FID): return FACTRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    class Relation(object):
        def __init__(self, CollectionIndex, ModName, recordID, listIndex):
            self._CollectionIndex = CollectionIndex
            self._ModName = ModName
            self._recordID = recordID
            self._listIndex = listIndex
        def get_faction(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, 7, self._listIndex, 1).contents.value
        def set_faction(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, 7, self._listIndex, 1, nValue)
        faction = property(get_faction, set_faction)
        def get_mod(self):
            CBash.ReadFIDListField.restype = POINTER(c_int)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, 7, self._listIndex, 2).contents.value
        def set_mod(self, nValue):
            CBash.SetFIDListFieldI(self._CollectionIndex, self._ModName, self._recordID, 7, self._listIndex, 2, nValue)
        mod = property(get_mod, set_mod)

    class Rank(object):
        def __init__(self, CollectionIndex, ModName, recordID, listIndex):
            self._CollectionIndex = CollectionIndex
            self._ModName = ModName
            self._recordID = recordID
            self._listIndex = listIndex
        def get_rank(self):
            CBash.ReadFIDListField.restype = POINTER(c_int)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, 10, self._listIndex, 1).contents.value
        def set_rank(self, nValue):
            CBash.SetFIDListFieldI(self._CollectionIndex, self._ModName, self._recordID, 10, self._listIndex, 1, nValue)
        rank = property(get_rank, set_rank)
        def get_male(self):
            CBash.ReadFIDListField.restype = c_char_p
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, 10, self._listIndex, 2)
        def set_male(self, nValue):
            CBash.SetFIDListFieldStr(self._CollectionIndex, self._ModName, self._recordID, 10, self._listIndex, 2, nValue)
        male = property(get_male, set_male)
        def get_female(self):
            CBash.ReadFIDListField.restype = c_char_p
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, 10, self._listIndex, 3)
        def set_female(self, nValue):
            CBash.SetFIDListFieldStr(self._CollectionIndex, self._ModName, self._recordID, 10, self._listIndex, 3, nValue)
        female = property(get_female, set_female)
        def get_insigniaPath(self):
            CBash.ReadFIDListField.restype = c_char_p
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, 10, self._listIndex, 4)
        def set_insigniaPath(self, nValue):
            CBash.SetFIDListFieldStr(self._CollectionIndex, self._ModName, self._recordID, 10, self._listIndex, 4, nValue)
        insigniaPath = property(get_insigniaPath, set_insigniaPath)

    def newRelationsElement(self):
        listIndex = CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 7)
        if(listIndex == -1): return None
        return self.Relation(self._CollectionIndex, self._ModName, self._recordID, listIndex)

    def newRanksElement(self):
        listIndex = CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 10)
        if(listIndex == -1): return None
        return self.Rank(self._CollectionIndex, self._ModName, self._recordID, listIndex)
    
    def get_full(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 6)
    def set_full(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 6, nValue)

    full = property(get_full, set_full)
    def get_relations(self):
        numRecords = CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 7)
        if(numRecords > 0): return [self.Relation(self._CollectionIndex, self._ModName, self._recordID, x) for x in range(0, numRecords)]
        else: return []
    def set_relations(self, nRelations):
        diffLength = len(nRelations) - CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 7)
        nValues = [(relation.faction,relation.mod) for relation in nRelations]
        while(diffLength < 0):
            CBash.DeleteFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 7)
            diffLength += 1
        while(diffLength > 0):
            CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 7)
            diffLength -= 1
        for oRelation, nValue in zip(self.relations, nValues):
            oRelation.faction, oRelation.mod = nValue
    relations = property(get_relations, set_relations)
    def get_flags(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 8)
        if(retValue): return retValue.contents.value
        else: return None
    def set_flags(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 8, c_ubyte(nValue))
    flags = property(get_flags, set_flags)
    def get_crimeGoldMultiplier(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 9)
        if(retValue): return retValue.contents.value
        else: return None
    def set_crimeGoldMultiplier(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 9, c_float(nValue))       
    crimeGoldMultiplier = property(get_crimeGoldMultiplier, set_crimeGoldMultiplier)
    def get_ranks(self):
        numRecords = CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 10)
        if(numRecords > 0): return [self.Rank(self._CollectionIndex, self._ModName, self._recordID, x) for x in range(0, numRecords)]
        else: return []
    def set_ranks(self, nRanks):
        diffLength = len(nRanks) - CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 10)
        nValues = [(nRank.rank, nRank.male, nRank.female, nRank.insigniaPath) for nRank in nRanks]
        while(diffLength < 0):
            CBash.DeleteFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 10)
            diffLength += 1
        while(diffLength > 0):
            CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 10)
            diffLength -= 1
        for oRank, nValue in zip(self.ranks, nValues):
            oRank.rank, oRank.male, oRank.female, oRank.insigniaPath = nValue
    ranks = property(get_ranks, set_ranks)

class HAIRRecord(BaseRecord):
    def CopyAsOverride(self, targetMod):
        FID = CBash.CopyHAIRRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(True))
        if(FID): return HAIRRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def CopyAsNew(self, targetMod):
        FID = CBash.CopyHAIRRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(False))
        if(FID): return HAIRRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def get_full(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 6)
    def set_full(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 6, nValue)
    full = property(get_full, set_full)
    def get_modPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 7)
    def set_modPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 7, nValue)
    modPath = property(get_modPath, set_modPath)
    def get_modb(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 8)
        if(retValue): return retValue.contents.value
        else: return None
    def set_modb(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 8, c_float(nValue))
    modb = property(get_modb, set_modb)
    def get_modt_p(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 9)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 9, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_modt_p(self, nValue):
        length = len(nValue)
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 9, struct.pack('B' * length, *nValue), length)
    modt_p = property(get_modt_p, set_modt_p)
    def get_iconPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 10)
    def set_iconPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 10, nValue)
    iconPath = property(get_iconPath, set_iconPath)
    def get_flags(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 11)
        if(retValue): return retValue.contents.value
        else: return None
    def set_flags(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 11, c_ubyte(nValue))
    flags = property(get_flags, set_flags)
    
class EYESRecord(BaseRecord):
    def CopyAsOverride(self, targetMod):
        FID = CBash.CopyEYESRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(True))
        if(FID): return EYESRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def CopyAsNew(self, targetMod):
        FID = CBash.CopyEYESRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(False))
        if(FID): return EYESRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def get_full(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 6)
    def set_full(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 6, nValue)
    full = property(get_full, set_full)
    def get_iconPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 7)
    def set_iconPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 7, nValue)
    iconPath = property(get_iconPath, set_iconPath)
    def get_flags(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 8)
        if(retValue): return retValue.contents.value
        else: return None
    def set_flags(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 8, c_ubyte(nValue))
    flags = property(get_flags, set_flags)
    
class RACERecord(BaseRecord):
    def CopyAsOverride(self, targetMod):
        FID = CBash.CopyRACERecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(True))
        if(FID): return RACERecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def CopyAsNew(self, targetMod):
        FID = CBash.CopyRACERecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(False))
        if(FID): return RACERecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    class Relation(object):
        def __init__(self, CollectionIndex, ModName, recordID, listIndex):
            self._CollectionIndex = CollectionIndex
            self._ModName = ModName
            self._recordID = recordID
            self._listIndex = listIndex
        def get_faction(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, 9, self._listIndex, 1).contents.value
        def set_faction(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, 9, self._listIndex, 1, nValue)
        faction = property(get_faction, set_faction)
        def get_mod(self):
            CBash.ReadFIDListField.restype = POINTER(c_int)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, 9, self._listIndex, 2).contents.value
        def set_mod(self, nValue):
            CBash.SetFIDListFieldI(self._CollectionIndex, self._ModName, self._recordID, 9, self._listIndex, 2, nValue)
        mod = property(get_mod, set_mod)

    class RaceModel(object):
        def __init__(self, CollectionIndex, ModName, recordID, listIndex):
            self._CollectionIndex = CollectionIndex
            self._ModName = ModName
            self._recordID = recordID
            self._listIndex = listIndex
        def get_modPath(self):
            CBash.ReadFIDField.restype = c_char_p
            return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, self._listIndex)
        def set_modPath(self, nValue):
            CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, self._listIndex, nValue)
        modPath = property(get_modPath, set_modPath)
        def get_modb(self):
            CBash.ReadFIDField.restype = POINTER(c_float)
            retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, self._listIndex + 1)
            if(retValue): return retValue.contents.value
            else: return None
        def set_modb(self, nValue):
            CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, self._listIndex + 1, c_float(nValue))
        modb = property(get_modb, set_modb)
        def get_iconPath(self):
            CBash.ReadFIDField.restype = c_char_p
            return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, self._listIndex + 2)
        def set_iconPath(self, nValue):
            CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, self._listIndex + 2, nValue)
        iconPath = property(get_iconPath, set_iconPath)
        def get_modt_p(self):
            numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, self._listIndex + 3)
            if(numRecords > 0):
                cRecords = POINTER(c_ubyte * numRecords)()
                CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, self._listIndex + 3, byref(cRecords))
                return [cRecords.contents[x] for x in range(0, numRecords)]
            else: return []
        def set_modt_p(self, nValue):
            length = len(nValue)
            CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, self._listIndex + 3, struct.pack('B' * length, *nValue), length)
        modt_p = property(get_modt_p, set_modt_p)
       
    class Model(object):
        def __init__(self, CollectionIndex, ModName, recordID, listIndex):
            self._CollectionIndex = CollectionIndex
            self._ModName = ModName
            self._recordID = recordID
            self._listIndex = listIndex
        def get_modPath(self):
            CBash.ReadFIDField.restype = c_char_p
            return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, self._listIndex)
        def set_modPath(self, nValue):
            CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, self._listIndex, nValue)
        modPath = property(get_modPath, set_modPath)
        def get_modb(self):
            CBash.ReadFIDField.restype = POINTER(c_float)
            retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, self._listIndex + 1)
            if(retValue): return retValue.contents.value
            else: return None
        def set_modb(self, nValue):
            CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, self._listIndex + 1, c_float(nValue))
        modb = property(get_modb, set_modb)
        def get_modt_p(self):
            numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, self._listIndex + 2)
            if(numRecords > 0):
                cRecords = POINTER(c_ubyte * numRecords)()
                CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, self._listIndex + 2, byref(cRecords))
                return [cRecords.contents[x] for x in range(0, numRecords)]
            else: return []
        def set_modt_p(self, nValue):
            length = len(nValue)
            CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, self._listIndex + 2, struct.pack('B' * length, *nValue), length)
        modt_p = property(get_modt_p, set_modt_p)    
    def newRelationsElement(self):
        listIndex = CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 9)
        if(listIndex == -1): return None
        return self.Relation(self._CollectionIndex, self._ModName, self._recordID, listIndex)
    def get_full(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 6)
    def set_full(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 6, nValue)
    full = property(get_full, set_full)
    def get_text(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 7)
    def set_text(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 7, nValue)
    text = property(get_text, set_text)
    def get_spells(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 8)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 8, byref(cRecords))
            return [cRecords[x].contents.value for x in range(0, numRecords)]
        else: return []
    def set_spells(self, nValue):
        length = len(nValue)
        cRecords = (c_uint * length)(*nValue)
        CBash.SetFIDFieldUIA(self._CollectionIndex, self._ModName, self._recordID, 8, cRecords, length)
    spells = property(get_spells, set_spells)
    def get_relations(self):
        numRecords = CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 9)
        if(numRecords > 0): return [self.Relation(self._CollectionIndex, self._ModName, self._recordID, x) for x in range(0, numRecords)]
        else: return []
    def set_relations(self, nRelations):
        diffLength = len(nRelations) - len(self.relations)
        nValues = [(relation.faction,relation.mod) for relation in nRelations]
        while(diffLength < 0):
            CBash.DeleteFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 9)
            diffLength += 1
        while(diffLength > 0):
            CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 9)
            diffLength -= 1
        for oRelation, nValue in zip(self.relations, nValues):
            oRelation.faction, oRelation.mod = nValue
    relations = property(get_relations, set_relations)
    def get_skill1(self):
        CBash.ReadFIDField.restype = POINTER(c_byte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 10)
        if(retValue): return retValue.contents.value
        else: return None
    def set_skill1(self, nValue):
        CBash.SetFIDFieldC(self._CollectionIndex, self._ModName, self._recordID, 10, c_byte(nValue))
    skill1 = property(get_skill1, set_skill1)
    def get_skill1Boost(self):
        CBash.ReadFIDField.restype = POINTER(c_byte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 11)
        if(retValue): return retValue.contents.value
        else: return None
    def set_skill1Boost(self, nValue):
        CBash.SetFIDFieldC(self._CollectionIndex, self._ModName, self._recordID, 11, c_byte(nValue))
    skill1Boost = property(get_skill1Boost, set_skill1Boost)
    def get_skill2(self):
        CBash.ReadFIDField.restype = POINTER(c_byte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 12)
        if(retValue): return retValue.contents.value
        else: return None
    def set_skill2(self, nValue):
        CBash.SetFIDFieldC(self._CollectionIndex, self._ModName, self._recordID, 12, c_byte(nValue))
    skill2 = property(get_skill2, set_skill2)
    def get_skill2Boost(self):
        CBash.ReadFIDField.restype = POINTER(c_byte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 13)
        if(retValue): return retValue.contents.value
        else: return None
    def set_skill2Boost(self, nValue):
        CBash.SetFIDFieldC(self._CollectionIndex, self._ModName, self._recordID, 13, c_byte(nValue))
    skill2Boost = property(get_skill2Boost, set_skill2Boost)
    def get_skill3(self):
        CBash.ReadFIDField.restype = POINTER(c_byte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 14)
        if(retValue): return retValue.contents.value
        else: return None
    def set_skill3(self, nValue):
        CBash.SetFIDFieldC(self._CollectionIndex, self._ModName, self._recordID, 14, c_byte(nValue))
    skill3 = property(get_skill3, set_skill3)
    def get_skill3Boost(self):
        CBash.ReadFIDField.restype = POINTER(c_byte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 15)
        if(retValue): return retValue.contents.value
        else: return None
    def set_skill3Boost(self, nValue):
        CBash.SetFIDFieldC(self._CollectionIndex, self._ModName, self._recordID, 15, c_byte(nValue))
    skill3Boost = property(get_skill3Boost, set_skill3Boost)
    def get_skill4(self):
        CBash.ReadFIDField.restype = POINTER(c_byte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 16)
        if(retValue): return retValue.contents.value
        else: return None
    def set_skill4(self, nValue):
        CBash.SetFIDFieldC(self._CollectionIndex, self._ModName, self._recordID, 16, c_byte(nValue))
    skill4 = property(get_skill4, set_skill4)
    def get_skill4Boost(self):
        CBash.ReadFIDField.restype = POINTER(c_byte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 17)
        if(retValue): return retValue.contents.value
        else: return None
    def set_skill4Boost(self, nValue):
        CBash.SetFIDFieldC(self._CollectionIndex, self._ModName, self._recordID, 17, c_byte(nValue))
    skill4Boost = property(get_skill4Boost, set_skill4Boost)
    def get_skill5(self):
        CBash.ReadFIDField.restype = POINTER(c_byte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 18)
        if(retValue): return retValue.contents.value
        else: return None
    def set_skill5(self, nValue):
        CBash.SetFIDFieldC(self._CollectionIndex, self._ModName, self._recordID, 18, c_byte(nValue))
    skill5 = property(get_skill5, set_skill5)
    def get_skill5Boost(self):
        CBash.ReadFIDField.restype = POINTER(c_byte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 19)
        if(retValue): return retValue.contents.value
        else: return None
    def set_skill5Boost(self, nValue):
        CBash.SetFIDFieldC(self._CollectionIndex, self._ModName, self._recordID, 19, c_byte(nValue))
    skill5Boost = property(get_skill5Boost, set_skill5Boost)
    def get_skill6(self):
        CBash.ReadFIDField.restype = POINTER(c_byte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 20)
        if(retValue): return retValue.contents.value
        else: return None
    def set_skill6(self, nValue):
        CBash.SetFIDFieldC(self._CollectionIndex, self._ModName, self._recordID, 20, c_byte(nValue))
    skill6 = property(get_skill6, set_skill6)
    def get_skill6Boost(self):
        CBash.ReadFIDField.restype = POINTER(c_byte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 21)
        if(retValue): return retValue.contents.value
        else: return None
    def set_skill6Boost(self, nValue):
        CBash.SetFIDFieldC(self._CollectionIndex, self._ModName, self._recordID, 21, c_byte(nValue))
    skill6Boost = property(get_skill6Boost, set_skill6Boost)
    def get_skill7(self):
        CBash.ReadFIDField.restype = POINTER(c_byte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 22)
        if(retValue): return retValue.contents.value
        else: return None
    def set_skill7(self, nValue):
        CBash.SetFIDFieldC(self._CollectionIndex, self._ModName, self._recordID, 22, c_byte(nValue))
    skill7 = property(get_skill7, set_skill7)
    def get_skill7Boost(self):
        CBash.ReadFIDField.restype = POINTER(c_byte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 23)
        if(retValue): return retValue.contents.value
        else: return None
    def set_skill7Boost(self, nValue):
        CBash.SetFIDFieldC(self._CollectionIndex, self._ModName, self._recordID, 23, c_byte(nValue))
    skill7Boost = property(get_skill7Boost, set_skill7Boost)
    def get_unused1(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 24)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 24, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_unused1(self, nValue):
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 24, struct.pack('2B', *nValue), 2)
    unused1 = property(get_unused1, set_unused1)
    def get_maleHeight(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 25)
        if(retValue): return retValue.contents.value
        else: return None
    def set_maleHeight(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 25, c_float(nValue))
    maleHeight = property(get_maleHeight, set_maleHeight)
    def get_femaleHeight(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 26)
        if(retValue): return retValue.contents.value
        else: return None
    def set_femaleHeight(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 26, c_float(nValue))   
    femaleHeight = property(get_femaleHeight, set_femaleHeight)
    def get_maleWeight(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 27)
        if(retValue): return retValue.contents.value
        else: return None
    def set_maleWeight(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 27, c_float(nValue))   
    maleWeight = property(get_maleWeight, set_maleWeight)
    def get_femaleWeight(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 28)
        if(retValue): return retValue.contents.value
        else: return None
    def set_femaleWeight(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 28, c_float(nValue))          
    femaleWeight = property(get_femaleWeight, set_femaleWeight)
    def get_flags(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 29)
        if(retValue): return retValue.contents.value
        else: return None
    def set_flags(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 29, c_uint(nValue))
    flags = property(get_flags, set_flags)
    def get_maleVoice(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 30)
        if(retValue): return retValue.contents.value
        else: return None
    def set_maleVoice(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 30, c_uint(nValue))
    maleVoice = property(get_maleVoice, set_maleVoice)
    def get_femaleVoice(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 31)
        if(retValue): return retValue.contents.value
        else: return None
    def set_femaleVoice(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 31, c_uint(nValue))
    femaleVoice = property(get_femaleVoice, set_femaleVoice)
    def get_defaultHairMale(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 32)
        if(retValue): return retValue.contents.value
        else: return None
    def set_defaultHairMale(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 32, c_uint(nValue))
    defaultHairMale = property(get_defaultHairMale, set_defaultHairMale)
    def get_defaultHairFemale(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 33)
        if(retValue): return retValue.contents.value
        else: return None
    def set_defaultHairFemale(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 33, c_uint(nValue))
    defaultHairFemale = property(get_defaultHairFemale, set_defaultHairFemale)
    def get_defaultHairColor(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 34)
        if(retValue): return retValue.contents.value
        else: return None
    def set_defaultHairColor(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 34, c_ubyte(nValue))
    defaultHairColor = property(get_defaultHairColor, set_defaultHairColor)
    def get_mainClamp(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 35)
        if(retValue): return retValue.contents.value
        else: return None
    def set_mainClamp(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 35, c_float(nValue))
    mainClamp = property(get_mainClamp, set_mainClamp)
    def get_faceClamp(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 36)
        if(retValue): return retValue.contents.value
        else: return None
    def set_faceClamp(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 36, c_float(nValue))
    faceClamp = property(get_faceClamp, set_faceClamp)
    def get_maleStrength(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 37)
        if(retValue): return retValue.contents.value
        else: return None
    def set_maleStrength(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 37, c_ubyte(nValue))
    maleStrength = property(get_maleStrength, set_maleStrength)
    def get_maleIntelligence(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 38)
        if(retValue): return retValue.contents.value
        else: return None
    def set_maleIntelligence(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 38, c_ubyte(nValue))
    maleIntelligence = property(get_maleIntelligence, set_maleIntelligence)
    def get_maleWillpower(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 39)
        if(retValue): return retValue.contents.value
        else: return None
    def set_maleWillpower(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 39, c_ubyte(nValue))
    maleWillpower = property(get_maleWillpower, set_maleWillpower)
    def get_maleAgility(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 40)
        if(retValue): return retValue.contents.value
        else: return None
    def set_maleAgility(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 40, c_ubyte(nValue))
    maleAgility = property(get_maleAgility, set_maleAgility)
    def get_maleSpeed(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 41)
        if(retValue): return retValue.contents.value
        else: return None
    def set_maleSpeed(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 41, c_ubyte(nValue))
    maleSpeed = property(get_maleSpeed, set_maleSpeed)
    def get_maleEndurance(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 42)
        if(retValue): return retValue.contents.value
        else: return None
    def set_maleEndurance(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 42, c_ubyte(nValue))
    maleEndurance = property(get_maleEndurance, set_maleEndurance)
    def get_malePersonality(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 43)
        if(retValue): return retValue.contents.value
        else: return None
    def set_malePersonality(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 43, c_ubyte(nValue))
    malePersonality = property(get_malePersonality, set_malePersonality)
    def get_maleLuck(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 44)
        if(retValue): return retValue.contents.value
        else: return None
    def set_maleLuck(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 44, c_ubyte(nValue))
    maleLuck = property(get_maleLuck, set_maleLuck)
    def get_femaleStrength(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 45)
        if(retValue): return retValue.contents.value
        else: return None
    def set_femaleStrength(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 45, c_ubyte(nValue))
    femaleStrength = property(get_femaleStrength, set_femaleStrength)
    def get_femaleIntelligence(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 46)
        if(retValue): return retValue.contents.value
        else: return None
    def set_femaleIntelligence(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 46, c_ubyte(nValue))
    femaleIntelligence = property(get_femaleIntelligence, set_femaleIntelligence)
    def get_femaleWillpower(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 47)
        if(retValue): return retValue.contents.value
        else: return None
    def set_femaleWillpower(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 47, c_ubyte(nValue))
    femaleWillpower = property(get_femaleWillpower, set_femaleWillpower)
    def get_femaleAgility(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 48)
        if(retValue): return retValue.contents.value
        else: return None
    def set_femaleAgility(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 48, c_ubyte(nValue))
    femaleAgility = property(get_femaleAgility, set_femaleAgility)
    def get_femaleSpeed(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 49)
        if(retValue): return retValue.contents.value
        else: return None
    def set_femaleSpeed(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 49, c_ubyte(nValue))
    femaleSpeed = property(get_femaleSpeed, set_femaleSpeed)
    def get_femaleEndurance(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 50)
        if(retValue): return retValue.contents.value
        else: return None
    def set_femaleEndurance(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 50, c_ubyte(nValue))
    femaleEndurance = property(get_femaleEndurance, set_femaleEndurance)
    def get_femalePersonality(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 51)
        if(retValue): return retValue.contents.value
        else: return None
    def set_femalePersonality(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 51, c_ubyte(nValue))
    femalePersonality = property(get_femalePersonality, set_femalePersonality)
    def get_femaleLuck(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 52)
        if(retValue): return retValue.contents.value
        else: return None
    def set_femaleLuck(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 52, c_ubyte(nValue))
    femaleLuck = property(get_femaleLuck, set_femaleLuck)
    @property
    def head(self):
        return self.RaceModel(self._CollectionIndex, self._ModName, self._recordID, 53)
    @property
    def maleEars(self):
        return self.RaceModel(self._CollectionIndex, self._ModName, self._recordID, 57)
    @property
    def femaleEars(self):
        return self.RaceModel(self._CollectionIndex, self._ModName, self._recordID, 61)
    @property
    def mouth(self):
        return self.RaceModel(self._CollectionIndex, self._ModName, self._recordID, 65)
    @property
    def teethLower(self):
        return self.RaceModel(self._CollectionIndex, self._ModName, self._recordID, 69)
    @property
    def teethUpper(self):
        return self.RaceModel(self._CollectionIndex, self._ModName, self._recordID, 73)
    @property
    def tongue(self):
        return self.RaceModel(self._CollectionIndex, self._ModName, self._recordID, 77)
    @property
    def leftEye(self):
        return self.RaceModel(self._CollectionIndex, self._ModName, self._recordID, 81)
    @property
    def rightEye(self):
        return self.RaceModel(self._CollectionIndex, self._ModName, self._recordID, 85)
    @property
    def maleTailModel(self):
        return self.Model(self._CollectionIndex, self._ModName, self._recordID, 89)
    def get_maleUpperBodyPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 92)
    def set_maleUpperBodyPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 92, nValue)
    maleUpperBodyPath = property(get_maleUpperBodyPath, set_maleUpperBodyPath)
    def get_maleLowerBodyPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 93)
    def set_maleLowerBodyPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 93, nValue)
    maleLowerBodyPath = property(get_maleLowerBodyPath, set_maleLowerBodyPath)
    def get_maleHandPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 94)
    def set_maleHandPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 94, nValue)
    maleHandPath = property(get_maleHandPath, set_maleHandPath)
    def get_maleFootPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 95)
    def set_maleFootPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 95, nValue)
    maleFootPath = property(get_maleFootPath, set_maleFootPath)
    def get_maleTailPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 96)
    def set_maleTailPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 96, nValue)
    maleTailPath = property(get_maleTailPath, set_maleTailPath)
    @property
    def femaleTailModel(self):
        return self.Model(self._CollectionIndex, self._ModName, self._recordID, 97)
    def get_femaleUpperBodyPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 100)
    def set_femaleUpperBodyPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 100, nValue)
    femaleUpperBodyPath = property(get_femaleUpperBodyPath, set_femaleUpperBodyPath)
    def get_femaleLowerBodyPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 101)
    def set_femaleLowerBodyPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 101, nValue)
    femaleLowerBodyPath = property(get_femaleLowerBodyPath, set_femaleLowerBodyPath)
    def get_femaleHandPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 102)
    def set_femaleHandPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 102, nValue)
    femaleHandPath = property(get_femaleHandPath, set_femaleHandPath)
    def get_femaleFootPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 103)
    def set_femaleFootPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 103, nValue)
    femaleFootPath = property(get_femaleFootPath, set_femaleFootPath)
    def get_femaleTailPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 104)
    def set_femaleTailPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 104, nValue)
    femaleTailPath = property(get_femaleTailPath, set_femaleTailPath)
    def get_hairs(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 105)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 105, byref(cRecords))
            return [cRecords[x].contents.value for x in range(0, numRecords)]
        else: return []
    def set_hairs(self, nValue):
        length = len(nValue)
        cRecords = (c_uint * length)(*nValue)
        CBash.SetFIDFieldUIA(self._CollectionIndex, self._ModName, self._recordID, 105, cRecords, length)
    hairs = property(get_hairs, set_hairs)
    def get_eyes(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 106)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 106, byref(cRecords))
            return [cRecords[x].contents.value for x in range(0, numRecords)]
        else: return []
    def set_eyes(self, nValue):
        length = len(nValue)
        cRecords = (c_uint * length)(*nValue)
        CBash.SetFIDFieldUIA(self._CollectionIndex, self._ModName, self._recordID, 106, cRecords, length)
    eyes = property(get_eyes, set_eyes)
    def get_fggs_p(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 107)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 107, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_fggs_p(self, nValue):
        length = len(nValue)
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 107, struct.pack('B' * length, *nValue), length)
    fggs_p = property(get_fggs_p, set_fggs_p)
    def get_fgga_p(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 108)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 108, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_fgga_p(self, nValue):
        length = len(nValue)
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 108, struct.pack('B' * length, *nValue), length)
    fgga_p = property(get_fgga_p, set_fgga_p)
    def get_fgts_p(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 109)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 109, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_fgts_p(self, nValue):
        length = len(nValue)
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 109, struct.pack('B' * length, *nValue), length)
    fgts_p = property(get_fgts_p, set_fgts_p)
    def get_snam(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 110)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 110, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_snam(self, nValue):
        length = len(nValue)
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 110, struct.pack('B' * length, *nValue), length)
    snam = property(get_snam, set_snam)
    
class SOUNRecord(BaseRecord):
    def CopyAsOverride(self, targetMod):
        FID = CBash.CopySOUNRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(True))
        if(FID): return SOUNRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def CopyAsNew(self, targetMod):
        FID = CBash.CopySOUNRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(False))
        if(FID): return SOUNRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def get_soundFile(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 6)
    def set_soundFile(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 6, nValue)
    soundFile = property(get_soundFile, set_soundFile)
    def get_minDistance(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 7)
        if(retValue): return retValue.contents.value
        else: return None
    def set_minDistance(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 7, c_ubyte(nValue))
    minDistance = property(get_minDistance, set_minDistance)
    def get_maxDistance(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 8)
        if(retValue): return retValue.contents.value
        else: return None
    def set_maxDistance(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 8, c_ubyte(nValue))        
    maxDistance = property(get_maxDistance, set_maxDistance)
    def get_freqAdjustment(self):
        CBash.ReadFIDField.restype = POINTER(c_byte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 9)
        if(retValue): return retValue.contents.value
        else: return None
    def set_freqAdjustment(self, nValue):
        CBash.SetFIDFieldC(self._CollectionIndex, self._ModName, self._recordID, 9, c_byte(nValue))        
    freqAdjustment = property(get_freqAdjustment, set_freqAdjustment)
    def get_unused1(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 10)
        if(retValue): return retValue.contents.value
        else: return None
    def set_unused1(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 10, c_ubyte(nValue))        
    unused1 = property(get_unused1, set_unused1)
    def get_flags(self):
        CBash.ReadFIDField.restype = POINTER(c_ushort)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 11)
        if(retValue): return retValue.contents.value
        else: return None
    def set_flags(self, nValue):
        CBash.SetFIDFieldUS(self._CollectionIndex, self._ModName, self._recordID, 11, c_ushort(nValue))
    flags = property(get_flags, set_flags)
    def get_unused2(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 12)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 12, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_unused2(self, nValue):
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 12, struct.pack('2B', *nValue), 2)
    unused2 = property(get_unused2, set_unused2)
    def get_staticAtten(self):
        CBash.ReadFIDField.restype = POINTER(c_short)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 13)
        if(retValue): return retValue.contents.value
        else: return None
    def set_staticAtten(self, nValue):
        CBash.SetFIDFieldS(self._CollectionIndex, self._ModName, self._recordID, 13, c_short(nValue))
    staticAtten = property(get_staticAtten, set_staticAtten)
    def get_stopTime(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 14)
        if(retValue): return retValue.contents.value
        else: return None
    def set_stopTime(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 14, c_ubyte(nValue))
    stopTime = property(get_stopTime, set_stopTime)
    def get_startTime(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 15)
        if(retValue): return retValue.contents.value
        else: return None
    def set_startTime(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 15, c_ubyte(nValue))
    startTime = property(get_startTime, set_startTime)
class SKILRecord(BaseRecord):
    def CopyAsOverride(self, targetMod):
        FID = CBash.CopySKILRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(True))
        if(FID): return SKILRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def CopyAsNew(self, targetMod):
        FID = CBash.CopySKILRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(False))
        if(FID): return SKILRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def get_skill(self):
        CBash.ReadFIDField.restype = POINTER(c_int)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 6)
        if(retValue): return retValue.contents.value
        else: return None
    def set_skill(self, nValue):
        CBash.SetFIDFieldI(self._CollectionIndex, self._ModName, self._recordID, 6, nValue)
    skill = property(get_skill, set_skill)
    def get_description(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 7)
    def set_description(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 7, nValue)
    description = property(get_description, set_description)
    def get_iconPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 8)
    def set_iconPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 8, nValue)
    iconPath = property(get_iconPath, set_iconPath)
    def get_action(self):
        CBash.ReadFIDField.restype = POINTER(c_int)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 9)
        if(retValue): return retValue.contents.value
        else: return None
    def set_action(self, nValue):
        CBash.SetFIDFieldI(self._CollectionIndex, self._ModName, self._recordID, 9, nValue)
    action = property(get_action, set_action)
    def get_attribute(self):
        CBash.ReadFIDField.restype = POINTER(c_int)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 10)
        if(retValue): return retValue.contents.value
        else: return None
    def set_attribute(self, nValue):
        CBash.SetFIDFieldI(self._CollectionIndex, self._ModName, self._recordID, 10, nValue)
    attribute = property(get_attribute, set_attribute)
    def get_specialization(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 11)
        if(retValue): return retValue.contents.value
        else: return None
    def set_specialization(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 11, c_uint(nValue))
    specialization = property(get_specialization, set_specialization)
    def get_use0(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 12)
        if(retValue): return retValue.contents.value
        else: return None
    def set_use0(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 12, c_float(nValue))
    use0 = property(get_use0, set_use0)
    def get_use1(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 13)
        if(retValue): return retValue.contents.value
        else: return None
    def set_use1(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 13, c_float(nValue))
    use1 = property(get_use1, set_use1)
    def get_apprentice(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 14)
    def set_apprentice(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 14, nValue)
    apprentice = property(get_apprentice, set_apprentice)
    def get_journeyman(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 15)
    def set_journeyman(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 15, nValue)
    journeyman = property(get_journeyman, set_journeyman)
    def get_expert(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 16)
    def set_expert(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 16, nValue)
    expert = property(get_expert, set_expert)
    def get_master(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 17)
    def set_master(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 17, nValue)
    master = property(get_master, set_master)
class MGEFRecord(BaseRecord):
    def CopyAsOverride(self, targetMod):
        FID = CBash.CopyMGEFRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(True))
        if(FID): return MGEFRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def CopyAsNew(self, targetMod):
        FID = CBash.CopyMGEFRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(False))
        if(FID): return MGEFRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def get_full(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 6)
    def set_full(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 6, nValue)
    full = property(get_full, set_full)
    def get_text(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 7)
    def set_text(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 7, nValue)
    text = property(get_text, set_text)
    def get_iconPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 8)
    def set_iconPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 8, nValue)
    iconPath = property(get_iconPath, set_iconPath)
    def get_modPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 9)
    def set_modPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 9, nValue)
    modPath = property(get_modPath, set_modPath)
    def get_modb(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 10)
        if(retValue): return retValue.contents.value
        else: return None
    def set_modb(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 10, c_float(nValue))
    modb = property(get_modb, set_modb)
    def get_modt_p(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 11)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 11, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_modt_p(self, nValue):
        length = len(nValue)
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 11, struct.pack('B' * length, *nValue), length)
    modt_p = property(get_modt_p, set_modt_p)
    def get_flags(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 12)
        if(retValue): return retValue.contents.value
        else: return None
    def set_flags(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 12, c_uint(nValue))
    flags = property(get_flags, set_flags)
    def get_baseCost(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 13)
        if(retValue): return retValue.contents.value
        else: return None
    def set_baseCost(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 13, c_float(nValue))
    baseCost = property(get_baseCost, set_baseCost)
    def get_associated(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 14)
        if(retValue): return retValue.contents.value
        else: return None
    def set_associated(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 14, c_uint(nValue))
    associated = property(get_associated, set_associated)
    def get_school(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 15)
        if(retValue): return retValue.contents.value
        else: return None
    def set_school(self, nValue):
        CBash.SetFIDFieldI(self._CollectionIndex, self._ModName, self._recordID, 15, nValue)
    school = property(get_school, set_school)
    def get_resistValue(self):
        CBash.ReadFIDField.restype = POINTER(c_int)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 16)
        if(retValue): return retValue.contents.value
        else: return None
    def set_resistValue(self, nValue):
        CBash.SetFIDFieldI(self._CollectionIndex, self._ModName, self._recordID, 16, nValue)
    resistValue = property(get_resistValue, set_resistValue)
    def get_unk1(self):
        CBash.ReadFIDField.restype = POINTER(c_ushort)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 17)
        if(retValue): return retValue.contents.value
        else: return None
    def set_unk1(self, nValue):
        CBash.SetFIDFieldUS(self._CollectionIndex, self._ModName, self._recordID, 17, c_ushort(nValue))
    unk1 = property(get_unk1, set_unk1)
    def get_unused1(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 18)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 18, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_unused1(self, nValue):
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 18, struct.pack('2B', *nValue), 2)
    unused1 = property(get_unused1, set_unused1)
    def get_light(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 19)
        if(retValue): return retValue.contents.value
        else: return None
    def set_light(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 19, c_uint(nValue))
    light = property(get_light, set_light)
    def get_projectileSpeed(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 20)
        if(retValue): return retValue.contents.value
        else: return None
    def set_projectileSpeed(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 20, c_float(nValue))
    projectileSpeed = property(get_projectileSpeed, set_projectileSpeed)
    def get_effectShader(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 21)
        if(retValue): return retValue.contents.value
        else: return None
    def set_effectShader(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 21, c_uint(nValue))
    effectShader = property(get_effectShader, set_effectShader)
    def get_enchantEffect(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 22)
        if(retValue): return retValue.contents.value
        else: return None
    def set_enchantEffect(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 22, c_uint(nValue))
    enchantEffect = property(get_enchantEffect, set_enchantEffect)
    def get_castingSound(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 23)
        if(retValue): return retValue.contents.value
        else: return None
    def set_castingSound(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 23, c_uint(nValue))
    castingSound = property(get_castingSound, set_castingSound)
    def get_boltSound(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 24)
        if(retValue): return retValue.contents.value
        else: return None
    def set_boltSound(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 24, c_uint(nValue))
    boltSound = property(get_boltSound, set_boltSound)
    def get_hitSound(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 25)
        if(retValue): return retValue.contents.value
        else: return None
    def set_hitSound(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 25, c_uint(nValue))
    hitSound = property(get_hitSound, set_hitSound)
    def get_areaSound(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 26)
        if(retValue): return retValue.contents.value
        else: return None
    def set_areaSound(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 26, c_uint(nValue))
    areaSound = property(get_areaSound, set_areaSound)
    def get_cefEnchantment(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 27)
        if(retValue): return retValue.contents.value
        else: return None
    def set_cefEnchantment(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 27, c_float(nValue))
    cefEnchantment = property(get_cefEnchantment, set_cefEnchantment)
    def get_cefBarter(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 28)
        if(retValue): return retValue.contents.value
        else: return None
    def set_cefBarter(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 28, c_float(nValue))
    cefBarter = property(get_cefBarter, set_cefBarter)
    def get_counterEffects(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 29)
        if(numRecords > 0):
            cRecords = POINTER(c_uint * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 29, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_counterEffects(self, nValue):
        CBash.SetFIDFieldUIA(self._CollectionIndex, self._ModName, self._recordID, 29, struct.pack('I' * len(nValue), *nValue), len(nValue))
    counterEffects = property(get_counterEffects, set_counterEffects)

class SCPTRecord(BaseRecord):
    def CopyAsOverride(self, targetMod):
        FID = CBash.CopySCPTRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(True))
        if(FID): return SCPTRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def CopyAsNew(self, targetMod):
        FID = CBash.CopySCPTRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(False))
        if(FID): return SCPTRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    class Var(object):
        def __init__(self, CollectionIndex, ModName, recordID, listIndex):
            self._CollectionIndex = CollectionIndex
            self._ModName = ModName
            self._recordID = recordID
            self._listIndex = listIndex
        def get_listIndex(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 1).contents.value
        def set_listIndex(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 1, nValue)
        index = property(get_listIndex, set_listIndex)
        def get_unused1(self):
            numRecords = CBash.GetFIDListArraySize(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 2)
            if(numRecords > 0):
                cRecords = POINTER(c_ubyte * numRecords)()
                CBash.GetFIDListArray(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 2, byref(cRecords))
                return [cRecords.contents[x] for x in range(0, numRecords)]
            else: return []
        def set_unused1(self, nValue):
            CBash.SetFIDListFieldR(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 2, struct.pack('12B', *nValue), 12)
        unused1 = property(get_unused1, set_unused1)
        def get_flags(self):
            CBash.ReadFIDListField.restype = POINTER(c_ubyte)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 3).contents.value
        def set_flags(self, nValue):
            CBash.SetFIDListFieldUC(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 3, c_ubyte(nValue))
        flags = property(get_flags, set_flags)
        def get_unused2(self):
            numRecords = CBash.GetFIDListArraySize(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 4)
            if(numRecords > 0):
                cRecords = POINTER(c_ubyte * numRecords)()
                CBash.GetFIDListArray(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 4, byref(cRecords))
                return [cRecords.contents[x] for x in range(0, numRecords)]
            else: return []
        def set_unused2(self, nValue):
            CBash.SetFIDListFieldR(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 4, struct.pack('7B', *nValue), 7)
        unused2 = property(get_unused2, set_unused2)
        def get_name(self):
            CBash.ReadFIDListField.restype = c_char_p
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5)
        def set_name(self, nValue):
            CBash.SetFIDListFieldStr(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5, nValue)
        name = property(get_name, set_name)
    class Reference(object):
        def __init__(self, CollectionIndex, ModName, recordID, listIndex):
            self._CollectionIndex = CollectionIndex
            self._ModName = ModName
            self._recordID = recordID
            self._listIndex = listIndex
        def get_reference(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, 14, self._listIndex, 1).contents.value
        def set_reference(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, 14, self._listIndex, 1, nValue)
        reference = property(get_reference, set_reference)
        def get_isSCRO(self):
            CBash.ReadFIDListField.restype = POINTER(c_bool)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, 14, self._listIndex, 2).contents.value
        def set_isSCRO(self, nValue):
            if isinstance(nValue, bool):
                if(nValue): CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, 14, self._listIndex, 2, 1)
                else: CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, 14, self._listIndex, 2, 0)
            else: CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, 14, self._listIndex, 2, nValue)
        isSCRO = property(get_isSCRO, set_isSCRO)
    def newVarsElement(self):
        listIndex = CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 13)
        if(listIndex == -1): return None
        return self.Var(self._CollectionIndex, self._ModName, self._recordID, listIndex)    
    def newReferencesElement(self):
        listIndex = CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 14)
        if(listIndex == -1): return None
        return self.Reference(self._CollectionIndex, self._ModName, self._recordID, listIndex)    
    def get_unused1(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 6)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 6, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_unused1(self, nValue):
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 6, struct.pack('2B', *nValue), 2)
    unused1 = property(get_unused1, set_unused1)
    def get_numRefs(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 7)
        if(retValue): return retValue.contents.value
        else: return None
    def set_numRefs(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 7, c_uint(nValue))
    numRefs = property(get_numRefs, set_numRefs)
    def get_compiledSize(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 8)
        if(retValue): return retValue.contents.value
        else: return None
    def set_compiledSize(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 8, c_uint(nValue))
    compiledSize = property(get_compiledSize, set_compiledSize)
    def get_lastIndex(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 9)
        if(retValue): return retValue.contents.value
        else: return None
    def set_lastIndex(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 9, c_uint(nValue))
    lastIndex = property(get_lastIndex, set_lastIndex)
    def get_scriptType(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 10)
        if(retValue): return retValue.contents.value
        else: return None
    def set_scriptType(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 10, c_uint(nValue))
    scriptType = property(get_scriptType, set_scriptType)
    def get_compiled_p(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 11)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 11, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_compiled_p(self, nValue):
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 11, struct.pack('B' * len(nValue), *nValue), len(nValue))
    compiled_p = property(get_compiled_p, set_compiled_p)
    def get_scriptText(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 12)
    def set_scriptText(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 12, nValue)
    scriptText = property(get_scriptText, set_scriptText)
    def get_vars(self):
        numRecords = CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 13)
        if(numRecords > 0): return [self.Var(self._CollectionIndex, self._ModName, self._recordID, x) for x in range(0, numRecords)]
        else: return []
    def set_vars(self, nVars):
        diffLength = len(nVars) - CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 13)
        nValues = [(nVar.index, nVar.unused1, nVar.flags, nVar.unused2, nVar.name) for nVar in nVars]
        while(diffLength < 0):
            CBash.DeleteFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 13)
            diffLength += 1
        while(diffLength > 0):
            CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 13)
            diffLength -= 1
        for oVar, nValue in zip(self.vars, nValues):
            oVar.index, oVar.unused1, oVar.flags, oVar.unused2, oVar.name = nValue
    vars = property(get_vars, set_vars)
    def get_references(self):
        numRecords = CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 14)
        if(numRecords > 0): return [self.Reference(self._CollectionIndex, self._ModName, self._recordID, x) for x in range(0, numRecords)]
        else: return []
    def set_references(self, nReferences):
        diffLength = len(nReferences) - CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 14)
        nValues = [(nReference.reference,nReference.isSCRO) for nReference in nReferences]
        while(diffLength < 0):
            CBash.DeleteFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 14)
            diffLength += 1
        while(diffLength > 0):
            CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 14)
            diffLength -= 1
        for oReference, nValue in zip(self.references, nValues):
            oReference.reference, oReference.isSCRO = nValue  
    references = property(get_references, set_references)
class LTEXRecord(BaseRecord):
    def CopyAsOverride(self, targetMod):
        FID = CBash.CopyLTEXRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(True))
        if(FID): return LTEXRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def CopyAsNew(self, targetMod):
        FID = CBash.CopyLTEXRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(False))
        if(FID): return LTEXRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def get_iconPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 6)
    def set_iconPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 6, nValue)
    iconPath = property(get_iconPath, set_iconPath)
    def get_flags(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 7)
        if(retValue): return retValue.contents.value
        else: return None
    def set_flags(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 7, c_ubyte(nValue))
    flags = property(get_flags, set_flags)
    def get_friction(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 8)
        if(retValue): return retValue.contents.value
        else: return None
    def set_friction(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 8, c_ubyte(nValue))
    friction = property(get_friction, set_friction)
    def get_restitution(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 9)
        if(retValue): return retValue.contents.value
        else: return None
    def set_restitution(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 9, c_ubyte(nValue))
    restitution = property(get_restitution, set_restitution)
    def get_specular(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 10)
        if(retValue): return retValue.contents.value
        else: return None
    def set_specular(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 10, c_ubyte(nValue))
    specular = property(get_specular, set_specular)
    def get_grass(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 11)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 11, byref(cRecords))
            return [cRecords[x].contents.value for x in range(0, numRecords)]
        else: return []
    def set_grass(self, nValue):
        length = len(nValue)
        cRecords = (c_uint * length)(*nValue)
        CBash.SetFIDFieldUIA(self._CollectionIndex, self._ModName, self._recordID, 11, cRecords, length)
    grass = property(get_grass, set_grass)

class ENCHRecord(BaseRecord):
    def CopyAsOverride(self, targetMod):
        FID = CBash.CopyENCHRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(True))
        if(FID): return ENCHRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def CopyAsNew(self, targetMod):
        FID = CBash.CopyENCHRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(False))
        if(FID): return ENCHRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    class Effect(object):
        def __init__(self, CollectionIndex, ModName, recordID, subField, listIndex):
            self._CollectionIndex = CollectionIndex
            self._ModName = ModName
            self._recordID = recordID
            self._subField = subField
            self._listIndex = listIndex
        ##name0 and name are both are always the same value, so setting one will set both. They're basically aliases
        def get_name0(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 1).contents.value
        def set_name0(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 1, nValue)
        name0 = property(get_name0, set_name0)
        def get_name(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 2).contents.value
        def set_name(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 2, nValue)
        name = property(get_name, set_name)
        def get_magnitude(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 3).contents.value
        def set_magnitude(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 3, nValue)
        magnitude = property(get_magnitude, set_magnitude)
        def get_area(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 4).contents.value
        def set_area(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 4, nValue)
        area = property(get_area, set_area)
        def get_duration(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 5).contents.value
        def set_duration(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 5, nValue)
        duration = property(get_duration, set_duration)
        def get_recipient(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 6).contents.value
        def set_recipient(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 6, nValue)
        recipient = property(get_recipient, set_recipient)
        def get_actorValue(self):
            CBash.ReadFIDListField.restype = POINTER(c_int)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 7).contents.value
        def set_actorValue(self, nValue):
            CBash.SetFIDListFieldI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 7, nValue)
        actorValue = property(get_actorValue, set_actorValue)
        def get_script(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 8).contents.value
        def set_script(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 8, nValue)
        script = property(get_script, set_script)
        def get_school(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 9).contents.value
        def set_school(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 9, nValue)
        school = property(get_school, set_school)
        def get_visual(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 10).contents.value
        def set_visual(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 10, nValue)
        visual = property(get_visual, set_visual)
        def get_flags(self):
            CBash.ReadFIDListField.restype = POINTER(c_ubyte)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 11).contents.value
        def set_flags(self, nValue):
            CBash.SetFIDListFieldUC(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 11, c_ubyte(nValue))
        flags = property(get_flags, set_flags)
        def get_unused1(self):
            numRecords = CBash.GetFIDListArraySize(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 12)
            if(numRecords > 0):
                cRecords = POINTER(c_ubyte * numRecords)()
                CBash.GetFIDListArray(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 12, byref(cRecords))
                return [cRecords.contents[x] for x in range(0, numRecords)]
            else: return []
        def set_unused1(self, nValue):
            CBash.SetFIDListFieldR(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 12, struct.pack('3B', *nValue), 3)
        unused1 = property(get_unused1, set_unused1)
        def get_full(self):
            CBash.ReadFIDListField.restype = c_char_p
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 13)
        def set_full(self, nValue):
            CBash.SetFIDListFieldStr(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 13, nValue)
        full = property(get_full, set_full)
    def newEffectsElement(self):
        listIndex = CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 12)
        if(listIndex == -1): return None
        return self.Effect(self._CollectionIndex, self._ModName, self._recordID, 12, listIndex)
    
    def get_full(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 6)
    def set_full(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 6, nValue)
    full = property(get_full, set_full)
    def get_itemType(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 7)
        if(retValue): return retValue.contents.value
        else: return None
    def set_itemType(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 7, c_uint(nValue))
    itemType = property(get_itemType, set_itemType)
    def get_chargeAmount(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 8)
        if(retValue): return retValue.contents.value
        else: return None
    def set_chargeAmount(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 8, c_uint(nValue))
    chargeAmount = property(get_chargeAmount, set_chargeAmount)
    def get_enchantCost(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 9)
        if(retValue): return retValue.contents.value
        else: return None
    def set_enchantCost(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 9, c_uint(nValue))
    enchantCost = property(get_enchantCost, set_enchantCost)
    def get_flags(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 10)
        if(retValue): return retValue.contents.value
        else: return None
    def set_flags(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 10, c_ubyte(nValue))
    flags = property(get_flags, set_flags)
    def get_unused1(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 11)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 11, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_unused1(self, nValue):
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 11, struct.pack('3B', *nValue), 3)
    unused1 = property(get_unused1, set_unused1)
    def get_effects(self):
        numRecords = CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 12)
        if(numRecords > 0): return [self.Effect(self._CollectionIndex, self._ModName, self._recordID, 12, x) for x in range(0, numRecords)]
        else: return []
    def set_effects(self, nEffects):
        diffLength = len(nEffects) - CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 12)
        nValues = [(nVar.name0, nVar.name, nVar.magnitude, nVar.area, nVar.duration, nVar.recipient, nVar.actorValue, nVar.script, nVar.school, nVar.visual, nVar.flags, nVar.unused1, nVar.full) for nVar in nVars]
        while(diffLength < 0):
            CBash.DeleteFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 12)
            diffLength += 1
        while(diffLength > 0):
            CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 12)
            diffLength -= 1
        for oEffect, nValue in zip(self.effects, nValues):
            oEffect.index, oEffect.unused1, oEffect.flags, oEffect.unused2, oEffect.name = nValue
    effects = property(get_effects, set_effects)
class SPELRecord(BaseRecord):
    def CopyAsOverride(self, targetMod):
        FID = CBash.CopySPELRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(True))
        if(FID): return SPELRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def CopyAsNew(self, targetMod):
        FID = CBash.CopySPELRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(False))
        if(FID): return SPELRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    class Effect(object):
        def __init__(self, CollectionIndex, ModName, recordID, subField, listIndex):
            self._CollectionIndex = CollectionIndex
            self._ModName = ModName
            self._recordID = recordID
            self._subField = subField
            self._listIndex = listIndex
        ##name0 and name are both are always the same value, so setting one will set both. They're basically aliases
        def get_name0(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 1).contents.value
        def set_name0(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 1, nValue)
        name0 = property(get_name0, set_name0)
        def get_name(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 2).contents.value
        def set_name(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 2, nValue)
        name = property(get_name, set_name)
        def get_magnitude(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 3).contents.value
        def set_magnitude(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 3, nValue)
        magnitude = property(get_magnitude, set_magnitude)
        def get_area(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 4).contents.value
        def set_area(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 4, nValue)
        area = property(get_area, set_area)
        def get_duration(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 5).contents.value
        def set_duration(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 5, nValue)
        duration = property(get_duration, set_duration)
        def get_recipient(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 6).contents.value
        def set_recipient(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 6, nValue)
        recipient = property(get_recipient, set_recipient)
        def get_actorValue(self):
            CBash.ReadFIDListField.restype = POINTER(c_int)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 7).contents.value
        def set_actorValue(self, nValue):
            CBash.SetFIDListFieldI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 7, nValue)
        actorValue = property(get_actorValue, set_actorValue)
        def get_script(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 8).contents.value
        def set_script(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 8, nValue)
        script = property(get_script, set_script)
        def get_school(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 9).contents.value
        def set_school(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 9, nValue)
        school = property(get_school, set_school)
        def get_visual(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 10).contents.value
        def set_visual(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 10, nValue)
        visual = property(get_visual, set_visual)
        def get_flags(self):
            CBash.ReadFIDListField.restype = POINTER(c_ubyte)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 11).contents.value
        def set_flags(self, nValue):
            CBash.SetFIDListFieldUC(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 11, c_ubyte(nValue))
        flags = property(get_flags, set_flags)
        def get_unused1(self):
            numRecords = CBash.GetFIDListArraySize(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 12)
            if(numRecords > 0):
                cRecords = POINTER(c_ubyte * numRecords)()
                CBash.GetFIDListArray(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 12, byref(cRecords))
                return [cRecords.contents[x] for x in range(0, numRecords)]
            else: return []
        def set_unused1(self, nValue):
            CBash.SetFIDListFieldR(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 12, struct.pack('3B', *nValue), 3)
        unused1 = property(get_unused1, set_unused1)
        def get_full(self):
            CBash.ReadFIDListField.restype = c_char_p
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 13)
        def set_full(self, nValue):
            CBash.SetFIDListFieldStr(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 13, nValue)
        full = property(get_full, set_full)
    def newEffectsElement(self):
        listIndex = CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 12)
        if(listIndex == -1): return None
        return self.Effect(self._CollectionIndex, self._ModName, self._recordID, 12, listIndex)
    
    def get_full(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 6)
    def set_full(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 6, nValue)
    full = property(get_full, set_full)
    def get_spellType(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 7)
        if(retValue): return retValue.contents.value
        else: return None
    def set_spellType(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 7, c_uint(nValue))
    spellType = property(get_spellType, set_spellType)
    def get_cost(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 8)
        if(retValue): return retValue.contents.value
        else: return None
    def set_cost(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 8, c_uint(nValue))
    cost = property(get_cost, set_cost)
    def get_level(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 9)
        if(retValue): return retValue.contents.value
        else: return None
    def set_level(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 9, c_uint(nValue))
    level = property(get_level, set_level)
    def get_flags(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 10)
        if(retValue): return retValue.contents.value
        else: return None
    def set_flags(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 10, c_ubyte(nValue))
    flags = property(get_flags, set_flags)
    def get_unused1(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 11)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 11, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_unused1(self, nValue):
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 11, struct.pack('3B', *nValue), 3)
    unused1 = property(get_unused1, set_unused1)
    def get_effects(self):
        numRecords = CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 12)
        if(numRecords > 0): return [self.Effect(self._CollectionIndex, self._ModName, self._recordID, 12, x) for x in range(0, numRecords)]
        else: return []
    def set_effects(self, nEffects):
        diffLength = len(nEffects) - CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 12)
        nValues = [(nVar.name0, nVar.name, nVar.magnitude, nVar.area, nVar.duration, nVar.recipient, nVar.actorValue, nVar.script, nVar.school, nVar.visual, nVar.flags, nVar.unused1, nVar.full) for nVar in nVars]
        while(diffLength < 0):
            CBash.DeleteFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 12)
            diffLength += 1
        while(diffLength > 0):
            CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 12)
            diffLength -= 1
        for oEffect, nValue in zip(self.effects, nValues):
            oEffect.index, oEffect.unused1, oEffect.flags, oEffect.unused2, oEffect.name = nValue
    effects = property(get_effects, set_effects)
    
class BSGNRecord(BaseRecord):
    def CopyAsOverride(self, targetMod):
        FID = CBash.CopyBSGNRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(True))
        if(FID): return BSGNRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def CopyAsNew(self, targetMod):
        FID = CBash.CopyBSGNRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(False))
        if(FID): return BSGNRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def get_full(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 6)
    def set_full(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 6, nValue)
    full = property(get_full, set_full)
    def get_iconPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 7)
    def set_iconPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 7, nValue)
    iconPath = property(get_iconPath, set_iconPath)
    def get_text(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 8)
    def set_text(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 8, nValue)
    text = property(get_text, set_text)
    def get_spells(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 9)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 9, byref(cRecords))
            return [cRecords[x].contents.value for x in range(0, numRecords)]
        else: return []
    def set_spells(self, nValue):
        length = len(nValue)
        cRecords = (c_uint * length)(*nValue)
        CBash.SetFIDFieldUIA(self._CollectionIndex, self._ModName, self._recordID, 9, cRecords, length)
    spells = property(get_spells, set_spells)

class ACTIRecord(BaseRecord):
    def CopyAsOverride(self, targetMod):
        FID = CBash.CopyACTIRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(True))
        if(FID): return ACTIRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def CopyAsNew(self, targetMod):
        FID = CBash.CopyACTIRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(False))
        if(FID): return ACTIRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def get_full(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 6)
    def set_full(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 6, nValue)
    full = property(get_full, set_full)
    def get_modPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 7)
    def set_modPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 7, nValue)
    modPath = property(get_modPath, set_modPath)
    def get_modb(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 8)
        if(retValue): return retValue.contents.value
        else: return None
    def set_modb(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 8, c_float(nValue))
    modb = property(get_modb, set_modb)
    def get_modt_p(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 9)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 9, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_modt_p(self, nValue):
        length = len(nValue)
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 9, struct.pack('B' * length, *nValue), length)
    modt_p = property(get_modt_p, set_modt_p)
    def get_script(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 10)
        if(retValue): return retValue.contents.value
        else: return None
    def set_script(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 10, c_uint(nValue))
    script = property(get_script, set_script)
    def get_sound(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 11)
        if(retValue): return retValue.contents.value
        else: return None
    def set_sound(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 11, c_uint(nValue))
    sound = property(get_sound, set_sound)

class APPARecord(BaseRecord):
    def CopyAsOverride(self, targetMod):
        FID = CBash.CopyAPPARecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(True))
        if(FID): return APPARecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def CopyAsNew(self, targetMod):
        FID = CBash.CopyAPPARecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(False))
        if(FID): return APPARecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def get_full(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 6)
    def set_full(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 6, nValue)
    full = property(get_full, set_full)
    def get_modPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 7)
    def set_modPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 7, nValue)
    modPath = property(get_modPath, set_modPath)
    def get_modb(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 8)
        if(retValue): return retValue.contents.value
        else: return None
    def set_modb(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 8, c_float(nValue))
    modb = property(get_modb, set_modb)
    def get_modt_p(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 9)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 9, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_modt_p(self, nValue):
        length = len(nValue)
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 9, struct.pack('B' * length, *nValue), length)
    modt_p = property(get_modt_p, set_modt_p)
    def get_iconPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 10)
    def set_iconPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 10, nValue)
    iconPath = property(get_iconPath, set_iconPath)
    def get_script(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 11)
        if(retValue): return retValue.contents.value
        else: return None
    def set_script(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 11, c_uint(nValue))
    script = property(get_script, set_script)
    def get_apparatus(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 12)
        if(retValue): return retValue.contents.value
        else: return None
    def set_apparatus(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 12, c_ubyte(nValue))
    apparatus = property(get_apparatus, set_apparatus)
    def get_value(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 13)
        if(retValue): return retValue.contents.value
        else: return None
    def set_value(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 13, c_uint(nValue))
    value = property(get_value, set_value)
    def get_weight(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 14)
        if(retValue): return retValue.contents.value
        else: return None
    def set_weight(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 14, c_float(nValue))
    weight = property(get_weight, set_weight)
    def get_quality(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 15)
        if(retValue): return retValue.contents.value
        else: return None
    def set_quality(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 15, c_float(nValue))
    quality = property(get_quality, set_quality)

class ARMORecord(BaseRecord):
    def CopyAsOverride(self, targetMod):
        FID = CBash.CopyARMORecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(True))
        if(FID): return ARMORecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def CopyAsNew(self, targetMod):
        FID = CBash.CopyARMORecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(False))
        if(FID): return ARMORecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    class Model(object):
        def __init__(self, CollectionIndex, ModName, recordID, listIndex):
            self._CollectionIndex = CollectionIndex
            self._ModName = ModName
            self._recordID = recordID
            self._listIndex = listIndex
        def get_modPath(self):
            CBash.ReadFIDField.restype = c_char_p
            return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, self._listIndex)
        def set_modPath(self, nValue):
            CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, self._listIndex, nValue)
        modPath = property(get_modPath, set_modPath)
        def get_modb(self):
            CBash.ReadFIDField.restype = POINTER(c_float)
            retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, self._listIndex + 1)
            if(retValue): return retValue.contents.value
            else: return None
        def set_modb(self, nValue):
            CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, self._listIndex + 1, c_float(nValue))
        modb = property(get_modb, set_modb)
        def get_modt_p(self):
            numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, self._listIndex + 2)
            if(numRecords > 0):
                cRecords = POINTER(c_ubyte * numRecords)()
                CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, self._listIndex + 2, byref(cRecords))
                return [cRecords.contents[x] for x in range(0, numRecords)]
            else: return []
        def set_modt_p(self, nValue):
            length = len(nValue)
            CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, self._listIndex + 2, struct.pack('B' * length, *nValue), length)
        modt_p = property(get_modt_p, set_modt_p)   
    def get_full(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 6)
    def set_full(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 6, nValue)
    full = property(get_full, set_full)
    def get_script(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 7)
        if(retValue): return retValue.contents.value
        else: return None
    def set_script(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 7, c_uint(nValue))
    script = property(get_script, set_script)
    def get_enchantment(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 8)
        if(retValue): return retValue.contents.value
        else: return None
    def set_enchantment(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 8, c_uint(nValue))
    enchantment = property(get_enchantment, set_enchantment)
    def get_enchantPoints(self):
        CBash.ReadFIDField.restype = POINTER(c_ushort)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 9)
        if(retValue): return retValue.contents.value
        else: return None
    def set_enchantPoints(self, nValue):
        CBash.SetFIDFieldUS(self._CollectionIndex, self._ModName, self._recordID, 9, c_ushort(nValue))
    enchantPoints = property(get_enchantPoints, set_enchantPoints)
    def get_flags(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 10)
        if(retValue): return retValue.contents.value
        else: return None
    def set_flags(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 10, c_uint(nValue))
    flags = property(get_flags, set_flags)
    @property
    def maleBody(self):
        return self.Model(self._CollectionIndex, self._ModName, self._recordID, 11)
    @property
    def maleWorld(self):
        return self.Model(self._CollectionIndex, self._ModName, self._recordID, 14)
    def get_maleIconPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 17)
    def set_maleIconPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 17, nValue)
    maleIconPath = property(get_maleIconPath, set_maleIconPath)
    @property
    def femaleBody(self):
        return self.Model(self._CollectionIndex, self._ModName, self._recordID, 18)
    @property
    def femaleWorld(self):
        return self.Model(self._CollectionIndex, self._ModName, self._recordID, 21)
    def get_femaleIconPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 24)
    def set_femaleIconPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 24, nValue)
    femaleIconPath = property(get_femaleIconPath, set_femaleIconPath)
    def get_strength(self):
        CBash.ReadFIDField.restype = POINTER(c_ushort)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 25)
        if(retValue): return retValue.contents.value
        else: return None
    def set_strength(self, nValue):
        CBash.SetFIDFieldUS(self._CollectionIndex, self._ModName, self._recordID, 25, c_ushort(nValue))
    strength = property(get_strength, set_strength)
    def get_value(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 26)
        if(retValue): return retValue.contents.value
        else: return None
    def set_value(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 26, c_uint(nValue))
    value = property(get_value, set_value)
    def get_health(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 27)
        if(retValue): return retValue.contents.value
        else: return None
    def set_health(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 27, c_uint(nValue))
    health = property(get_health, set_health)
    def get_weight(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 28)
        if(retValue): return retValue.contents.value
        else: return None
    def set_weight(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 28, c_float(nValue))
    weight = property(get_weight, set_weight)

class BOOKRecord(BaseRecord):
    def CopyAsOverride(self, targetMod):
        FID = CBash.CopyBOOKRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(True))
        if(FID): return BOOKRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def CopyAsNew(self, targetMod):
        FID = CBash.CopyBOOKRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(False))
        if(FID): return BOOKRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def get_full(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 6)
    def set_full(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 6, nValue)
    full = property(get_full, set_full)
    def get_modPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 7)
    def set_modPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 7, nValue)
    modPath = property(get_modPath, set_modPath)
    def get_modb(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 8)
        if(retValue): return retValue.contents.value
        else: return None
    def set_modb(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 8, c_float(nValue))
    modb = property(get_modb, set_modb)
    def get_modt_p(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 9)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 9, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_modt_p(self, nValue):
        length = len(nValue)
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 9, struct.pack('B' * length, *nValue), length)
    modt_p = property(get_modt_p, set_modt_p)
    def get_iconPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 10)
    def set_iconPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 10, nValue)
    iconPath = property(get_iconPath, set_iconPath)
    def get_text(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 11)
    def set_text(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 11, nValue)
    text = property(get_text, set_text)
    def get_script(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 12)
        if(retValue): return retValue.contents.value
        else: return None
    def set_script(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 12, c_uint(nValue))
    script = property(get_script, set_script)
    def get_enchantment(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 13)
        if(retValue): return retValue.contents.value
        else: return None
    def set_enchantment(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 13, c_uint(nValue))
    enchantment = property(get_enchantment, set_enchantment)
    def get_enchantPoints(self):
        CBash.ReadFIDField.restype = POINTER(c_ushort)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 14)
        if(retValue): return retValue.contents.value
        else: return None
    def set_enchantPoints(self, nValue):
        CBash.SetFIDFieldUS(self._CollectionIndex, self._ModName, self._recordID, 14, c_ushort(nValue))
    enchantPoints = property(get_enchantPoints, set_enchantPoints)
    def get_flags(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 15)
        if(retValue): return retValue.contents.value
        else: return None
    def set_flags(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 15, c_ubyte(nValue))
    flags = property(get_flags, set_flags)
    def get_teaches(self):
        CBash.ReadFIDField.restype = POINTER(c_byte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 16)
        if(retValue): return retValue.contents.value
        else: return None
    def set_teaches(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 16, c_byte(nValue))
    teaches = property(get_teaches, set_teaches)
    def get_value(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 17)
        if(retValue): return retValue.contents.value
        else: return None
    def set_value(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 17, c_uint(nValue))
    value = property(get_value, set_value)
    def get_weight(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 18)
        if(retValue): return retValue.contents.value
        else: return None
    def set_weight(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 18, c_float(nValue))
    weight = property(get_weight, set_weight)
class CLOTRecord(BaseRecord):
    def CopyAsOverride(self, targetMod):
        FID = CBash.CopyCLOTRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(True))
        if(FID): return CLOTRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def CopyAsNew(self, targetMod):
        FID = CBash.CopyCLOTRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(False))
        if(FID): return CLOTRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    class Model(object):
        def __init__(self, CollectionIndex, ModName, recordID, listIndex):
            self._CollectionIndex = CollectionIndex
            self._ModName = ModName
            self._recordID = recordID
            self._listIndex = listIndex
        def get_modPath(self):
            CBash.ReadFIDField.restype = c_char_p
            return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, self._listIndex)
        def set_modPath(self, nValue):
            CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, self._listIndex, nValue)
        modPath = property(get_modPath, set_modPath)
        def get_modb(self):
            CBash.ReadFIDField.restype = POINTER(c_float)
            retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, self._listIndex + 1)
            if(retValue): return retValue.contents.value
            else: return None
        def set_modb(self, nValue):
            CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, self._listIndex + 1, c_float(nValue))
        modb = property(get_modb, set_modb)
        def get_modt_p(self):
            numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, self._listIndex + 2)
            if(numRecords > 0):
                cRecords = POINTER(c_ubyte * numRecords)()
                CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, self._listIndex + 2, byref(cRecords))
                return [cRecords.contents[x] for x in range(0, numRecords)]
            else: return []
        def set_modt_p(self, nValue):
            length = len(nValue)
            CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, self._listIndex + 2, struct.pack('B' * length, *nValue), length)
        modt_p = property(get_modt_p, set_modt_p)   
    def get_full(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 6)
    def set_full(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 6, nValue)
    full = property(get_full, set_full)
    def get_script(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 7)
        if(retValue): return retValue.contents.value
        else: return None
    def set_script(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 7, c_uint(nValue))
    script = property(get_script, set_script)
    def get_enchantment(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 8)
        if(retValue): return retValue.contents.value
        else: return None
    def set_enchantment(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 8, c_uint(nValue))
    enchantment = property(get_enchantment, set_enchantment)
    def get_enchantPoints(self):
        CBash.ReadFIDField.restype = POINTER(c_ushort)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 9)
        if(retValue): return retValue.contents.value
        else: return None
    def set_enchantPoints(self, nValue):
        CBash.SetFIDFieldUS(self._CollectionIndex, self._ModName, self._recordID, 9, c_ushort(nValue))
    enchantPoints = property(get_enchantPoints, set_enchantPoints)
    def get_flags(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 10)
        if(retValue): return retValue.contents.value
        else: return None
    def set_flags(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 10, c_uint(nValue))
    flags = property(get_flags, set_flags)
    @property
    def maleBody(self):
        return self.Model(self._CollectionIndex, self._ModName, self._recordID, 11)
    @property
    def maleWorld(self):
        return self.Model(self._CollectionIndex, self._ModName, self._recordID, 14)
    def get_maleIconPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 17)
    def set_maleIconPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 17, nValue)
    maleIconPath = property(get_maleIconPath, set_maleIconPath)
    @property
    def femaleBody(self):
        return self.Model(self._CollectionIndex, self._ModName, self._recordID, 18)
    @property
    def femaleWorld(self):
        return self.Model(self._CollectionIndex, self._ModName, self._recordID, 21)
    def get_femaleIconPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 24)
    def set_femaleIconPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 24, nValue)
    femaleIconPath = property(get_femaleIconPath, set_femaleIconPath)
    def get_value(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 25)
        if(retValue): return retValue.contents.value
        else: return None
    def set_value(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 25, c_uint(nValue))
    value = property(get_value, set_value)
    def get_weight(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 26)
        if(retValue): return retValue.contents.value
        else: return None
    def set_weight(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 26, c_float(nValue))
    weight = property(get_weight, set_weight)
class CONTRecord(BaseRecord):
    def CopyAsOverride(self, targetMod):
        FID = CBash.CopyCONTRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(True))
        if(FID): return CONTRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def CopyAsNew(self, targetMod):
        FID = CBash.CopyCONTRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(False))
        if(FID): return CONTRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    class Item(object):
        def __init__(self, CollectionIndex, ModName, recordID, subField, listIndex):
            self._CollectionIndex = CollectionIndex
            self._ModName = ModName
            self._recordID = recordID
            self._subField = subField
            self._listIndex = listIndex
        def get_item(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 1).contents.value
        def set_item(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 1, nValue)
        item = property(get_item, set_item)
        def get_count(self):
            CBash.ReadFIDListField.restype = POINTER(c_int)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 2).contents.value
        def set_count(self, nValue):
            CBash.SetFIDListFieldI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 2, nValue)
        count = property(get_count, set_count)
    def newItemsElement(self):
        listIndex = CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 11)
        if(listIndex == -1): return None
        return self.Item(self._CollectionIndex, self._ModName, self._recordID, 11, listIndex)
    def get_full(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 6)
    def set_full(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 6, nValue)
    full = property(get_full, set_full)
    def get_modPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 7)
    def set_modPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 7, nValue)
    modPath = property(get_modPath, set_modPath)
    def get_modb(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 8)
        if(retValue): return retValue.contents.value
        else: return None
    def set_modb(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 8, c_float(nValue))
    modb = property(get_modb, set_modb)
    def get_modt_p(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 9)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 9, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_modt_p(self, nValue):
        length = len(nValue)
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 9, struct.pack('B' * length, *nValue), length)
    modt_p = property(get_modt_p, set_modt_p)
    def get_script(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 10)
        if(retValue): return retValue.contents.value
        else: return None
    def set_script(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 10, c_uint(nValue))
    script = property(get_script, set_script)
    def get_items(self):
        numRecords = CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 11)
        if(numRecords > 0): return [self.Item(self._CollectionIndex, self._ModName, self._recordID, 11, x) for x in range(0, numRecords)]
        else: return []
    def set_items(self, nItems):
        diffLength = len(nItems) - CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 11)
        nValues = [(item.item, item.count) for item in nItems]
        while(diffLength < 0):
            CBash.DeleteFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 11)
            diffLength += 1
        while(diffLength > 0):
            CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 11)
            diffLength -= 1
        for oItem, nValue in zip(self.items, nValues):
            oItem.item, oItem.count = nValue
    items = property(get_items, set_items)
    def get_flags(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 12)
        if(retValue): return retValue.contents.value
        else: return None
    def set_flags(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 12, c_ubyte(nValue))
    flags = property(get_flags, set_flags)
    def get_weight(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 13)
        if(retValue): return retValue.contents.value
        else: return None
    def set_weight(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 13, c_float(nValue))
    weight = property(get_weight, set_weight)
    def get_soundOpen(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 14)
        if(retValue): return retValue.contents.value
        else: return None
    def set_soundOpen(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 14, c_uint(nValue))
    soundOpen = property(get_soundOpen, set_soundOpen)
    def get_soundClose(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 15)
        if(retValue): return retValue.contents.value
        else: return None
    def set_soundClose(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 15, c_uint(nValue))
    soundClose = property(get_soundClose, set_soundClose)
    
class DOORRecord(BaseRecord):
    def CopyAsOverride(self, targetMod):
        FID = CBash.CopyDOORRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(True))
        if(FID): return DOORRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def CopyAsNew(self, targetMod):
        FID = CBash.CopyDOORRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(False))
        if(FID): return DOORRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def get_full(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 6)
    def set_full(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 6, nValue)
    full = property(get_full, set_full)
    def get_modPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 7)
    def set_modPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 7, nValue)
    modPath = property(get_modPath, set_modPath)
    def get_modb(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 8)
        if(retValue): return retValue.contents.value
        else: return None
    def set_modb(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 8, c_float(nValue))
    modb = property(get_modb, set_modb)
    def get_modt_p(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 9)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 9, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_modt_p(self, nValue):
        length = len(nValue)
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 9, struct.pack('B' * length, *nValue), length)
    modt_p = property(get_modt_p, set_modt_p)
    def get_script(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 10)
        if(retValue): return retValue.contents.value
        else: return None
    def set_script(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 10, c_uint(nValue))
    script = property(get_script, set_script)
    def get_soundOpen(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 11)
        if(retValue): return retValue.contents.value
        else: return None
    def set_soundOpen(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 11, c_uint(nValue))
    soundOpen = property(get_soundOpen, set_soundOpen)
    def get_soundClose(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 12)
        if(retValue): return retValue.contents.value
        else: return None
    def set_soundClose(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 12, c_uint(nValue))
    soundClose = property(get_soundClose, set_soundClose)
    def get_soundLoop(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 13)
        if(retValue): return retValue.contents.value
        else: return None
    def set_soundLoop(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 13, c_uint(nValue))
    soundLoop = property(get_soundLoop, set_soundLoop)
    def get_flags(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 14)
        if(retValue): return retValue.contents.value
        else: return None
    def set_flags(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 14, c_ubyte(nValue))
    flags = property(get_flags, set_flags)
    def get_destinations(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 15)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 15, byref(cRecords))
            return [cRecords[x].contents.value for x in range(0, numRecords)]
        else: return []
    def set_destinations(self, nValue):
        length = len(nValue)
        cRecords = (c_uint * length)(*nValue)
        CBash.SetFIDFieldUIA(self._CollectionIndex, self._ModName, self._recordID, 15, cRecords, length)
    destinations = property(get_destinations, set_destinations)
class INGRRecord(BaseRecord):
    def CopyAsOverride(self, targetMod):
        FID = CBash.CopyINGRRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(True))
        if(FID): return INGRRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def CopyAsNew(self, targetMod):
        FID = CBash.CopyINGRRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(False))
        if(FID): return INGRRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    class Effect(object):
        def __init__(self, CollectionIndex, ModName, recordID, subField, listIndex):
            self._CollectionIndex = CollectionIndex
            self._ModName = ModName
            self._recordID = recordID
            self._subField = subField
            self._listIndex = listIndex
        ##name0 and name are both are always the same value, so setting one will set both. They're basically aliases
        def get_name0(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 1).contents.value
        def set_name0(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 1, nValue)
        name0 = property(get_name0, set_name0)
        def get_name(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 2).contents.value
        def set_name(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 2, nValue)
        name = property(get_name, set_name)
        def get_magnitude(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 3).contents.value
        def set_magnitude(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 3, nValue)
        magnitude = property(get_magnitude, set_magnitude)
        def get_area(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 4).contents.value
        def set_area(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 4, nValue)
        area = property(get_area, set_area)
        def get_duration(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 5).contents.value
        def set_duration(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 5, nValue)
        duration = property(get_duration, set_duration)
        def get_recipient(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 6).contents.value
        def set_recipient(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 6, nValue)
        recipient = property(get_recipient, set_recipient)
        def get_actorValue(self):
            CBash.ReadFIDListField.restype = POINTER(c_int)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 7).contents.value
        def set_actorValue(self, nValue):
            CBash.SetFIDListFieldI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 7, nValue)
        actorValue = property(get_actorValue, set_actorValue)
        def get_script(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 8).contents.value
        def set_script(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 8, nValue)
        script = property(get_script, set_script)
        def get_school(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 9).contents.value
        def set_school(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 9, nValue)
        school = property(get_school, set_school)
        def get_visual(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 10).contents.value
        def set_visual(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 10, nValue)
        visual = property(get_visual, set_visual)
        def get_flags(self):
            CBash.ReadFIDListField.restype = POINTER(c_ubyte)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 11).contents.value
        def set_flags(self, nValue):
            CBash.SetFIDListFieldUC(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 11, c_ubyte(nValue))
        flags = property(get_flags, set_flags)
        def get_unused1(self):
            numRecords = CBash.GetFIDListArraySize(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 12)
            if(numRecords > 0):
                cRecords = POINTER(c_ubyte * numRecords)()
                CBash.GetFIDListArray(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 12, byref(cRecords))
                return [cRecords.contents[x] for x in range(0, numRecords)]
            else: return []
        def set_unused1(self, nValue):
            CBash.SetFIDListFieldR(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 12, struct.pack('3B', *nValue), 3)
        unused1 = property(get_unused1, set_unused1)
        def get_full(self):
            CBash.ReadFIDListField.restype = c_char_p
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 13)
        def set_full(self, nValue):
            CBash.SetFIDListFieldStr(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 13, nValue)
        full = property(get_full, set_full)
    def newEffectsElement(self):
        listIndex = CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 16)
        if(listIndex == -1): return None
        return self.Effect(self._CollectionIndex, self._ModName, self._recordID, 16, listIndex)
    def get_full(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 6)
    def set_full(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 6, nValue)
    full = property(get_full, set_full)
    def get_modPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 7)
    def set_modPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 7, nValue)
    modPath = property(get_modPath, set_modPath)
    def get_modb(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 8)
        if(retValue): return retValue.contents.value
        else: return None
    def set_modb(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 8, c_float(nValue))
    modb = property(get_modb, set_modb)
    def get_modt_p(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 9)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 9, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_modt_p(self, nValue):
        length = len(nValue)
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 9, struct.pack('B' * length, *nValue), length)
    modt_p = property(get_modt_p, set_modt_p)
    def get_iconPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 10)
    def set_iconPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 10, nValue)
    iconPath = property(get_iconPath, set_iconPath)
    def get_script(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 11)
        if(retValue): return retValue.contents.value
        else: return None
    def set_script(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 11, c_uint(nValue))
    script = property(get_script, set_script)
    def get_weight(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 12)
        if(retValue): return retValue.contents.value
        else: return None
    def set_weight(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 12, c_float(nValue))
    weight = property(get_weight, set_weight)
    def get_value(self):
        CBash.ReadFIDField.restype = POINTER(c_int)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 13)
        if(retValue): return retValue.contents.value
        else: return None
    def set_value(self, nValue):
        CBash.SetFIDFieldI(self._CollectionIndex, self._ModName, self._recordID, 13, c_int(nValue))
    value = property(get_value, set_value)
    def get_flags(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 14)
        if(retValue): return retValue.contents.value
        else: return None
    def set_flags(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 14, c_ubyte(nValue))
    flags = property(get_flags, set_flags)
    def get_unused1(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 15)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 15, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_unused1(self, nValue):
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 15, struct.pack('3B', *nValue), 3)
    unused1 = property(get_unused1, set_unused1)
    def get_effects(self):
        numRecords = CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 16)
        if(numRecords > 0): return [self.Effect(self._CollectionIndex, self._ModName, self._recordID, 16, x) for x in range(0, numRecords)]
        else: return []
    def set_effects(self, nEffects):
        diffLength = len(nEffects) - CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 16)
        nValues = [(nEffect.name0, nEffect.name, nEffect.magnitude, nEffect.area, nEffect.duration, nEffect.recipient, nEffect.actorValue, nEffect.script, nEffect.school, nEffect.visual, nEffect.flags, nEffect.unused1, nEffect.full) for nEffect in nEffects]
        while(diffLength < 0):
            CBash.DeleteFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 16)
            diffLength += 1
        while(diffLength > 0):
            CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 16)
            diffLength -= 1
        for oEffect, nValue in zip(self.effects, nValues):
            oEffect.name0, oEffect.name, oEffect.magnitude, oEffect.area, oEffect.duration, oEffect.recipient, oEffect.actorValue, oEffect.script, oEffect.school, oEffect.visual, oEffect.flags, oEffect.unused1, oEffect.full = nValue
    effects = property(get_effects, set_effects)

class LIGHRecord(BaseRecord):
    def CopyAsOverride(self, targetMod):
        FID = CBash.CopyLIGHRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(True))
        if(FID): return LIGHRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def CopyAsNew(self, targetMod):
        FID = CBash.CopyLIGHRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(False))
        if(FID): return LIGHRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def get_modPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 6)
    def set_modPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 6, nValue)
    modPath = property(get_modPath, set_modPath)
    def get_modb(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 7)
        if(retValue): return retValue.contents.value
        else: return None
    def set_modb(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 7, c_float(nValue))
    modb = property(get_modb, set_modb)
    def get_modt_p(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 8)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 8, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_modt_p(self, nValue):
        length = len(nValue)
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 8, struct.pack('B' * length, *nValue), length)
    modt_p = property(get_modt_p, set_modt_p)
    def get_script(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 9)
        if(retValue): return retValue.contents.value
        else: return None
    def set_script(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 9, c_uint(nValue))
    script = property(get_script, set_script)
    def get_full(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 10)
    def set_full(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 10, nValue)
    full = property(get_full, set_full)
    def get_iconPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 11)
    def set_iconPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 11, nValue)
    iconPath = property(get_iconPath, set_iconPath)
    def get_duration(self):
        CBash.ReadFIDField.restype = POINTER(c_int)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 12)
        if(retValue): return retValue.contents.value
        else: return None
    def set_duration(self, nValue):
        CBash.SetFIDFieldI(self._CollectionIndex, self._ModName, self._recordID, 12, c_int(nValue))
    duration = property(get_duration, set_duration)
    def get_radius(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 13)
        if(retValue): return retValue.contents.value
        else: return None
    def set_radius(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 13, c_uint(nValue))
    radius = property(get_radius, set_radius)
    def get_red(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 14)
        if(retValue): return retValue.contents.value
        else: return None
    def set_red(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 14, c_ubyte(nValue))
    red = property(get_red, set_red)
    def get_green(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 15)
        if(retValue): return retValue.contents.value
        else: return None
    def set_green(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 15, c_ubyte(nValue))
    green = property(get_green, set_green)
    def get_blue(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 16)
        if(retValue): return retValue.contents.value
        else: return None
    def set_blue(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 16, c_ubyte(nValue))
    blue = property(get_blue, set_blue)
    def get_unused1(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 17)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 17, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_unused1(self, nValue):
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 17, struct.pack('B', *nValue), 1)
    unused1 = property(get_unused1, set_unused1)
    def get_flags(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 18)
        if(retValue): return retValue.contents.value
        else: return None
    def set_flags(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 18, c_uint(nValue))
    flags = property(get_flags, set_flags)
    def get_falloff(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 19)
        if(retValue): return retValue.contents.value
        else: return None
    def set_falloff(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 19, c_float(nValue))
    falloff = property(get_falloff, set_falloff)
    def get_fov(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 20)
        if(retValue): return retValue.contents.value
        else: return None
    def set_fov(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 20, c_float(nValue))
    fov = property(get_fov, set_fov)
    def get_value(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 21)
        if(retValue): return retValue.contents.value
        else: return None
    def set_value(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 21, c_uint(nValue))
    value = property(get_value, set_value)
    def get_weight(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 22)
        if(retValue): return retValue.contents.value
        else: return None
    def set_weight(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 22, c_float(nValue))
    weight = property(get_weight, set_weight)
    def get_fade(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 23)
        if(retValue): return retValue.contents.value
        else: return None
    def set_fade(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 23, c_float(nValue))
    fade = property(get_fade, set_fade)
    def get_sound(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 24)
        if(retValue): return retValue.contents.value
        else: return None
    def set_sound(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 24, c_uint(nValue))
    sound = property(get_sound, set_sound)

class MISCRecord(BaseRecord):
    def CopyAsOverride(self, targetMod):
        FID = CBash.CopyMISCRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(True))
        if(FID): return MISCRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def CopyAsNew(self, targetMod):
        FID = CBash.CopyMISCRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(False))
        if(FID): return MISCRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def get_full(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 6)
    def set_full(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 6, nValue)
    full = property(get_full, set_full)
    def get_modPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 7)
    def set_modPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 7, nValue)
    modPath = property(get_modPath, set_modPath)
    def get_modb(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 8)
        if(retValue): return retValue.contents.value
        else: return None
    def set_modb(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 8, c_float(nValue))
    modb = property(get_modb, set_modb)
    def get_modt_p(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 9)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 9, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_modt_p(self, nValue):
        length = len(nValue)
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 9, struct.pack('B' * length, *nValue), length)
    modt_p = property(get_modt_p, set_modt_p)
    def get_iconPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 10)
    def set_iconPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 10, nValue)
    iconPath = property(get_iconPath, set_iconPath)
    def get_script(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 11)
        if(retValue): return retValue.contents.value
        else: return None
    def set_script(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 11, c_uint(nValue))
    script = property(get_script, set_script)
    def get_value(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 12)
        if(retValue): return retValue.contents.value
        else: return None
    def set_value(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 12, c_uint(nValue))
    value = property(get_value, set_value)
    def get_weight(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 13)
        if(retValue): return retValue.contents.value
        else: return None
    def set_weight(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 13, c_float(nValue))
    weight = property(get_weight, set_weight)

class STATRecord(BaseRecord):
    def CopyAsOverride(self, targetMod):
        FID = CBash.CopySTATRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(True))
        if(FID): return STATRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def CopyAsNew(self, targetMod):
        FID = CBash.CopySTATRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(False))
        if(FID): return STATRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def get_modPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 6)
    def set_modPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 6, nValue)
    modPath = property(get_modPath, set_modPath)
    def get_modb(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 7)
        if(retValue): return retValue.contents.value
        else: return None
    def set_modb(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 7, c_float(nValue))
    modb = property(get_modb, set_modb)
    def get_modt_p(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 8)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 8, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_modt_p(self, nValue):
        length = len(nValue)
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 8, struct.pack('B' * length, *nValue), length)
    modt_p = property(get_modt_p, set_modt_p)
class GRASRecord(BaseRecord):
    def CopyAsOverride(self, targetMod):
        FID = CBash.CopyGRASRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(True))
        if(FID): return GRASRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def CopyAsNew(self, targetMod):
        FID = CBash.CopyGRASRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(False))
        if(FID): return GRASRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def get_modPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 6)
    def set_modPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 6, nValue)
    modPath = property(get_modPath, set_modPath)
    def get_modb(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 7)
        if(retValue): return retValue.contents.value
        else: return None
    def set_modb(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 7, c_float(nValue))
    modb = property(get_modb, set_modb)
    def get_modt_p(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 8)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 8, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_modt_p(self, nValue):
        length = len(nValue)
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 8, struct.pack('B' * length, *nValue), length)
    modt_p = property(get_modt_p, set_modt_p)
    def get_density(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 9)
        if(retValue): return retValue.contents.value
        else: return None
    def set_density(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 9, c_ubyte(nValue))
    density = property(get_density, set_density)
    def get_minSlope(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 10)
        if(retValue): return retValue.contents.value
        else: return None
    def set_minSlope(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 10, c_ubyte(nValue))
    minSlope = property(get_minSlope, set_minSlope)
    def get_maxSlope(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 11)
        if(retValue): return retValue.contents.value
        else: return None
    def set_maxSlope(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 11, c_ubyte(nValue))
    maxSlope = property(get_maxSlope, set_maxSlope)
    def get_unused1(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 12)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 12, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_unused1(self, nValue):
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 12, struct.pack('B', *nValue), 1)
    unused1 = property(get_unused1, set_unused1)
    def get_waterDistance(self):
        CBash.ReadFIDField.restype = POINTER(c_ushort)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 13)
        if(retValue): return retValue.contents.value
        else: return None
    def set_waterDistance(self, nValue):
        CBash.SetFIDFieldUS(self._CollectionIndex, self._ModName, self._recordID, 13, c_ushort(nValue))
    waterDistance = property(get_waterDistance, set_waterDistance)
    def get_unused2(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 14)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 14, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_unused2(self, nValue):
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 14, struct.pack('2B', *nValue), 2)
    unused2 = property(get_unused2, set_unused2)
    def get_waterOp(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 15)
        if(retValue): return retValue.contents.value
        else: return None
    def set_waterOp(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 15, nValue)
    waterOp = property(get_waterOp, set_waterOp)
    def get_posRange(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 16)
        if(retValue): return retValue.contents.value
        else: return None
    def set_posRange(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 16, c_float(nValue))
    posRange = property(get_posRange, set_posRange)
    def get_heightRange(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 17)
        if(retValue): return retValue.contents.value
        else: return None
    def set_heightRange(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 17, c_float(nValue))
    heightRange = property(get_heightRange, set_heightRange)
    def get_colorRange(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 18)
        if(retValue): return retValue.contents.value
        else: return None
    def set_colorRange(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 18, c_float(nValue))
    colorRange = property(get_colorRange, set_colorRange)
    def get_wavePeriod(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 19)
        if(retValue): return retValue.contents.value
        else: return None
    def set_wavePeriod(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 19, c_float(nValue))
    wavePeriod = property(get_wavePeriod, set_wavePeriod)
    def get_flags(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 20)
        if(retValue): return retValue.contents.value
        else: return None
    def set_flags(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 20, c_ubyte(nValue))
    flags = property(get_flags, set_flags)
    def get_unused3(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 21)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 21, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_unused3(self, nValue):
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 21, struct.pack('3B', *nValue), 3)
    unused3 = property(get_unused3, set_unused3)
class TREERecord(BaseRecord):
    def CopyAsOverride(self, targetMod):
        FID = CBash.CopyTREERecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(True))
        if(FID): return TREERecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def CopyAsNew(self, targetMod):
        FID = CBash.CopyTREERecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(False))
        if(FID): return TREERecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def get_modPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 6)
    def set_modPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 6, nValue)
    modPath = property(get_modPath, set_modPath)
    def get_modb(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 7)
        if(retValue): return retValue.contents.value
        else: return None
    def set_modb(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 7, c_float(nValue))
    modb = property(get_modb, set_modb)
    def get_modt_p(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 8)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 8, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_modt_p(self, nValue):
        length = len(nValue)
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 8, struct.pack('B' * length, *nValue), length)
    modt_p = property(get_modt_p, set_modt_p)
    def get_iconPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 9)
    def set_iconPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 9, nValue)
    iconPath = property(get_iconPath, set_iconPath)
    def get_speedTree(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 10)
        if(numRecords > 0):
            cRecords = POINTER(c_uint * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 10, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_speedTree(self, nValue):
        CBash.SetFIDFieldUIA(self._CollectionIndex, self._ModName, self._recordID, 10, struct.pack('I' * len(nValue), *nValue), len(nValue))
    speedTree = property(get_speedTree, set_speedTree)
    def get_curvature(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 11)
        if(retValue): return retValue.contents.value
        else: return None
    def set_curvature(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 11, c_float(nValue))
    curvature = property(get_curvature, set_curvature)
    def get_minAngle(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 12)
        if(retValue): return retValue.contents.value
        else: return None
    def set_minAngle(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 12, c_float(nValue))
    minAngle = property(get_minAngle, set_minAngle)
    def get_maxAngle(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 13)
        if(retValue): return retValue.contents.value
        else: return None
    def set_maxAngle(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 13, c_float(nValue))
    maxAngle = property(get_maxAngle, set_maxAngle)
    def get_branchDim(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 14)
        if(retValue): return retValue.contents.value
        else: return None
    def set_branchDim(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 14, c_float(nValue))
    branchDim = property(get_branchDim, set_branchDim)
    def get_leafDim(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 15)
        if(retValue): return retValue.contents.value
        else: return None
    def set_leafDim(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 15, c_float(nValue))
    leafDim = property(get_leafDim, set_leafDim)
    def get_shadowRadius(self):
        CBash.ReadFIDField.restype = POINTER(c_int)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 16)
        if(retValue): return retValue.contents.value
        else: return None
    def set_shadowRadius(self, nValue):
        CBash.SetFIDFieldI(self._CollectionIndex, self._ModName, self._recordID, 16, nValue)
    shadowRadius = property(get_shadowRadius, set_shadowRadius)
    def get_rockSpeed         (self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 17)
        if(retValue): return retValue.contents.value
        else: return None
    def set_rockSpeed         (self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 17, c_float(nValue))
    rockSpeed          = property(get_rockSpeed         , set_rockSpeed         )
    def get_rustleSpeed  (self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 18)
        if(retValue): return retValue.contents.value
        else: return None
    def set_rustleSpeed  (self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 18, c_float(nValue))
    rustleSpeed   = property(get_rustleSpeed  , set_rustleSpeed  )
    def get_widthBill(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 19)
        if(retValue): return retValue.contents.value
        else: return None
    def set_widthBill(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 19, c_float(nValue))
    widthBill = property(get_widthBill, set_widthBill)
    def get_heightBill(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 20)
        if(retValue): return retValue.contents.value
        else: return None
    def set_heightBill(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 20, c_float(nValue))
    heightBill = property(get_heightBill, set_heightBill)
class FLORRecord(BaseRecord):
    def CopyAsOverride(self, targetMod):
        FID = CBash.CopyFLORRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(True))
        if(FID): return FLORRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def CopyAsNew(self, targetMod):
        FID = CBash.CopyFLORRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(False))
        if(FID): return FLORRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def get_full(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 6)
    def set_full(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 6, nValue)
    full = property(get_full, set_full)
    def get_modPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 7)
    def set_modPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 7, nValue)
    modPath = property(get_modPath, set_modPath)
    def get_modb(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 8)
        if(retValue): return retValue.contents.value
        else: return None
    def set_modb(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 8, c_float(nValue))
    modb = property(get_modb, set_modb)
    def get_modt_p(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 9)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 9, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_modt_p(self, nValue):
        length = len(nValue)
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 9, struct.pack('B' * length, *nValue), length)
    modt_p = property(get_modt_p, set_modt_p)
    def get_script(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 10)
        if(retValue): return retValue.contents.value
        else: return None
    def set_script(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 10, nValue)
    script = property(get_script, set_script)
    def get_ingredient(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 11)
        if(retValue): return retValue.contents.value
        else: return None
    def set_ingredient(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 11, nValue)
    ingredient = property(get_ingredient, set_ingredient)
    def get_spring(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 12)
        if(retValue): return retValue.contents.value
        else: return None
    def set_spring(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 12, c_ubyte(nValue))
    spring = property(get_spring, set_spring)
    def get_summer(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 13)
        if(retValue): return retValue.contents.value
        else: return None
    def set_summer(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 13, c_ubyte(nValue))
    summer = property(get_summer, set_summer)
    def get_fall(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 14)
        if(retValue): return retValue.contents.value
        else: return None
    def set_fall(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 14, c_ubyte(nValue))
    fall = property(get_fall, set_fall)
    def get_winter(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 15)
        if(retValue): return retValue.contents.value
        else: return None
    def set_winter(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 15, c_ubyte(nValue))
    winter = property(get_winter, set_winter)
class FURNRecord(BaseRecord):
    def CopyAsOverride(self, targetMod):
        FID = CBash.CopyFURNRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(True))
        if(FID): return FURNRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def CopyAsNew(self, targetMod):
        FID = CBash.CopyFURNRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(False))
        if(FID): return FURNRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def get_full(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 6)
    def set_full(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 6, nValue)
    full = property(get_full, set_full)
    def get_modPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 7)
    def set_modPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 7, nValue)
    modPath = property(get_modPath, set_modPath)
    def get_modb(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 8)
        if(retValue): return retValue.contents.value
        else: return None
    def set_modb(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 8, c_float(nValue))
    modb = property(get_modb, set_modb)
    def get_modt_p(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 9)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 9, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_modt_p(self, nValue):
        length = len(nValue)
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 9, struct.pack('B' * length, *nValue), length)
    modt_p = property(get_modt_p, set_modt_p)
    def get_script(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 10)
        if(retValue): return retValue.contents.value
        else: return None
    def set_script(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 10, c_uint(nValue))
    script = property(get_script, set_script)
    def get_flags(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 11)
        if(retValue): return retValue.contents.value
        else: return None
    def set_flags(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 11, nValue)
    flags = property(get_flags, set_flags)
class WEAPRecord(BaseRecord):
    def CopyAsOverride(self, targetMod):
        FID = CBash.CopyWEAPRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(True))
        if(FID): return WEAPRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def CopyAsNew(self, targetMod):
        FID = CBash.CopyWEAPRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(False))
        if(FID): return WEAPRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def get_full(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 6)
    def set_full(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 6, nValue)
    full = property(get_full, set_full)
    def get_modPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 7)
    def set_modPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 7, nValue)
    modPath = property(get_modPath, set_modPath)
    def get_modb(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 8)
        if(retValue): return retValue.contents.value
        else: return None
    def set_modb(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 8, c_float(nValue))
    modb = property(get_modb, set_modb)
    def get_modt_p(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 9)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 9, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_modt_p(self, nValue):
        length = len(nValue)
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 9, struct.pack('B' * length, *nValue), length)
    modt_p = property(get_modt_p, set_modt_p)
    def get_iconPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 10)
    def set_iconPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 10, nValue)
    iconPath = property(get_iconPath, set_iconPath)
    def get_script(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 11)
        if(retValue): return retValue.contents.value
        else: return None
    def set_script(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 11, c_uint(nValue))
    script = property(get_script, set_script)
    def get_enchantment(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 12)
        if(retValue): return retValue.contents.value
        else: return None
    def set_enchantment(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 12, nValue)
    enchantment = property(get_enchantment, set_enchantment)
    def get_enchantPoints(self):
        CBash.ReadFIDField.restype = POINTER(c_ushort)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 13)
        if(retValue): return retValue.contents.value
        else: return None
    def set_enchantPoints(self, nValue):
        CBash.SetFIDFieldUS(self._CollectionIndex, self._ModName, self._recordID, 13, c_ushort(nValue))
    enchantPoints = property(get_enchantPoints, set_enchantPoints)                    
    def get_weaponType(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 14)
        if(retValue): return retValue.contents.value
        else: return None
    def set_weaponType(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 14, nValue)
    weaponType = property(get_weaponType, set_weaponType)
    def get_speed(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 15)
        if(retValue): return retValue.contents.value
        else: return None
    def set_speed(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 15, c_float(nValue))
    speed = property(get_speed, set_speed)
    def get_reach(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 16)
        if(retValue): return retValue.contents.value
        else: return None
    def set_reach(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 16, c_float(nValue))
    reach = property(get_reach, set_reach)
    def get_flags(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 17)
        if(retValue): return retValue.contents.value
        else: return None
    def set_flags(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 17, nValue)
    flags = property(get_flags, set_flags)
    def get_value(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 18)
        if(retValue): return retValue.contents.value
        else: return None
    def set_value(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 18, nValue)
    value = property(get_value, set_value)
    def get_health(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 19)
        if(retValue): return retValue.contents.value
        else: return None
    def set_health(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 19, nValue)
    health = property(get_health, set_health)
    def get_weight(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 20)
        if(retValue): return retValue.contents.value
        else: return None
    def set_weight(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 20, c_float(nValue))
    weight = property(get_weight, set_weight)
    def get_damage(self):
        CBash.ReadFIDField.restype = POINTER(c_ushort)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 21)
        if(retValue): return retValue.contents.value
        else: return None
    def set_damage(self, nValue):
        CBash.SetFIDFieldUS(self._CollectionIndex, self._ModName, self._recordID, 21, c_ushort(nValue))
    damage = property(get_damage, set_damage)
    
class AMMORecord(BaseRecord):
    def CopyAsOverride(self, targetMod):
        FID = CBash.CopyAMMORecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(True))
        if(FID): return AMMORecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def CopyAsNew(self, targetMod):
        FID = CBash.CopyAMMORecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(False))
        if(FID): return AMMORecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def get_full(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 6)
    def set_full(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 6, nValue)
    full = property(get_full, set_full)
    def get_modPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 7)
    def set_modPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 7, nValue)
    modPath = property(get_modPath, set_modPath)
    def get_modb(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 8)
        if(retValue): return retValue.contents.value
        else: return None
    def set_modb(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 8, c_float(nValue))
    modb = property(get_modb, set_modb)
    def get_modt_p(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 9)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 9, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_modt_p(self, nValue):
        length = len(nValue)
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 9, struct.pack('B' * length, *nValue), length)
    modt_p = property(get_modt_p, set_modt_p)
    def get_iconPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 10)
    def set_iconPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 10, nValue)
    iconPath = property(get_iconPath, set_iconPath)
    def get_enchantment(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 11)
        if(retValue): return retValue.contents.value
        else: return None
    def set_enchantment(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 11, nValue)
    enchantment = property(get_enchantment, set_enchantment)
    def get_enchantPoints(self):
        CBash.ReadFIDField.restype = POINTER(c_ushort)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 12)
        if(retValue): return retValue.contents.value
        else: return None
    def set_enchantPoints(self, nValue):
        CBash.SetFIDFieldUS(self._CollectionIndex, self._ModName, self._recordID, 12, c_ushort(nValue))
    enchantPoints = property(get_enchantPoints, set_enchantPoints)     
    def get_speed(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 13)
        if(retValue): return retValue.contents.value
        else: return None
    def set_speed(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 13, c_float(nValue))
    speed = property(get_speed, set_speed)  
    def get_flags(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 14)
        if(retValue): return retValue.contents.value
        else: return None
    def set_flags(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 14, nValue)
    flags = property(get_flags, set_flags)
    def get_unused1(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 15)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 15, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_unused1(self, nValue):
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 15, struct.pack('3B', *nValue), 3)
    unused1 = property(get_unused1, set_unused1)
    def get_value(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 16)
        if(retValue): return retValue.contents.value
        else: return None
    def set_value(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 16, nValue)
    value = property(get_value, set_value)
    def get_weight(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 17)
        if(retValue): return retValue.contents.value
        else: return None
    def set_weight(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 17, c_float(nValue))
    weight = property(get_weight, set_weight)
    def get_damage(self):
        CBash.ReadFIDField.restype = POINTER(c_ushort)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 18)
        if(retValue): return retValue.contents.value
        else: return None
    def set_damage(self, nValue):
        CBash.SetFIDFieldUS(self._CollectionIndex, self._ModName, self._recordID, 18, c_ushort(nValue))
    damage = property(get_damage, set_damage)
class NPC_Record(BaseRecord):
    def CopyAsOverride(self, targetMod):
        FID = CBash.CopyNPC_Record(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(True))
        if(FID): return NPC_Record(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def CopyAsNew(self, targetMod):
        FID = CBash.CopyNPC_Record(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(False))
        if(FID): return NPC_Record(self._CollectionIndex, targetMod._ModName, FID)
        return None
    class Faction(object):
        def __init__(self, CollectionIndex, ModName, recordID, subField, listIndex):
            self._CollectionIndex = CollectionIndex
            self._ModName = ModName
            self._recordID = recordID
            self._subField = subField
            self._listIndex = listIndex
        def get_faction(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 1).contents.value
        def set_faction(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 1, nValue)
        faction = property(get_faction, set_faction)
        def get_rank(self):
            CBash.ReadFIDListField.restype = POINTER(c_ubyte)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 2).contents.value
        def set_rank(self, nValue):
            CBash.SetFIDListFieldUC(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 2, c_ubyte(nValue))
        rank = property(get_rank, set_rank)
        def get_unused1(self):
            numRecords = CBash.GetFIDListArraySize(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 3)
            if(numRecords > 0):
                cRecords = POINTER(c_ubyte * numRecords)()
                CBash.GetFIDListArray(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 3, byref(cRecords))
                return [cRecords.contents[x] for x in range(0, numRecords)]
            else: return []
        def set_unused1(self, nValue):
            CBash.SetFIDListFieldR(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 3, struct.pack('3B', *nValue), 3)
        unused1 = property(get_unused1, set_unused1)
    class Item(object):
        def __init__(self, CollectionIndex, ModName, recordID, subField, listIndex):
            self._CollectionIndex = CollectionIndex
            self._ModName = ModName
            self._recordID = recordID
            self._subField = subField
            self._listIndex = listIndex
        def get_item(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 1).contents.value
        def set_item(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 1, nValue)
        item = property(get_item, set_item)
        def get_count(self):
            CBash.ReadFIDListField.restype = POINTER(c_int)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 2).contents.value
        def set_count(self, nValue):
            CBash.SetFIDListFieldI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 2, nValue)
        count = property(get_count, set_count)
        
    def newFactionsElement(self):
        listIndex = CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 17)
        if(listIndex == -1): return None
        return self.Faction(self._CollectionIndex, self._ModName, self._recordID, 17, listIndex)
    def newItemsElement(self):
        listIndex = CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 22)
        if(listIndex == -1): return None
        return self.Item(self._CollectionIndex, self._ModName, self._recordID, 22, listIndex)
    def get_full(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 6)
    def set_full(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 6, nValue)
    full = property(get_full, set_full)
    def get_modPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 7)
    def set_modPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 7, nValue)
    modPath = property(get_modPath, set_modPath)
    def get_modb(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 8)
        if(retValue): return retValue.contents.value
        else: return None
    def set_modb(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 8, c_float(nValue))
    modb = property(get_modb, set_modb)
    def get_modt_p(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 9)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 9, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_modt_p(self, nValue):
        length = len(nValue)
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 9, struct.pack('B' * length, *nValue), length)
    modt_p = property(get_modt_p, set_modt_p)
    def get_flags(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 10)
        if(retValue): return retValue.contents.value
        else: return None
    def set_flags(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 10, nValue)
    flags = property(get_flags, set_flags)
    def get_baseSpell(self):
        CBash.ReadFIDField.restype = POINTER(c_ushort)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 11)
        if(retValue): return retValue.contents.value
        else: return None
    def set_baseSpell(self, nValue):
        CBash.SetFIDFieldUS(self._CollectionIndex, self._ModName, self._recordID, 11, c_ushort(nValue))
    baseSpell = property(get_baseSpell, set_baseSpell)
    def get_fatigue(self):
        CBash.ReadFIDField.restype = POINTER(c_ushort)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 12)
        if(retValue): return retValue.contents.value
        else: return None
    def set_fatigue(self, nValue):
        CBash.SetFIDFieldUS(self._CollectionIndex, self._ModName, self._recordID, 12, c_ushort(nValue))
    fatigue = property(get_fatigue, set_fatigue)
    def get_barterGold(self):
        CBash.ReadFIDField.restype = POINTER(c_ushort)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 13)
        if(retValue): return retValue.contents.value
        else: return None
    def set_barterGold(self, nValue):
        CBash.SetFIDFieldUS(self._CollectionIndex, self._ModName, self._recordID, 13, c_ushort(nValue))
    barterGold = property(get_barterGold, set_barterGold)
    def get_level(self):
        CBash.ReadFIDField.restype = POINTER(c_short)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 14)
        if(retValue): return retValue.contents.value
        else: return None
    def set_level(self, nValue):
        CBash.SetFIDFieldS(self._CollectionIndex, self._ModName, self._recordID, 14, c_short(nValue))
    level = property(get_level, set_level)
    def get_calcMin(self):
        CBash.ReadFIDField.restype = POINTER(c_ushort)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 15)
        if(retValue): return retValue.contents.value
        else: return None
    def set_calcMin(self, nValue):
        CBash.SetFIDFieldUS(self._CollectionIndex, self._ModName, self._recordID, 15, c_ushort(nValue))
    calcMin = property(get_calcMin, set_calcMin)
    def get_calcMax(self):
        CBash.ReadFIDField.restype = POINTER(c_ushort)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 16)
        if(retValue): return retValue.contents.value
        else: return None
    def set_calcMax(self, nValue):
        CBash.SetFIDFieldUS(self._CollectionIndex, self._ModName, self._recordID, 16, c_ushort(nValue))
    calcMax = property(get_calcMax, set_calcMax)
    def get_factions(self):
        numRecords = CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 17)
        if(numRecords > 0): return [self.Faction(self._CollectionIndex, self._ModName, self._recordID, 17, x) for x in range(0, numRecords)]
        else: return []
    def set_factions(self, nFactions):
        diffLength = len(nFactions) - CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 17)
        nValues = [(faction.faction,faction.rank,faction.unused1) for faction in nFactions]
        while(diffLength < 0):
            CBash.DeleteFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 17)
            diffLength += 1
        while(diffLength > 0):
            CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 17)
            diffLength -= 1
        for oFaction, nValue in zip(self.factions, nValues):
            oFaction.faction, oFaction.rank, oFaction.unused1 = nValue
    factions = property(get_factions, set_factions)
    def get_deathItem(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 18)
        if(retValue): return retValue.contents.value
        else: return None
    def set_deathItem(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 18, nValue)
    deathItem = property(get_deathItem, set_deathItem)
    def get_race(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 19)
        if(retValue): return retValue.contents.value
        else: return None
    def set_race(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 19, nValue)
    race = property(get_race, set_race)
    def get_spells(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 20)
        if(numRecords > 0):
            cRecords = POINTER(c_uint * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 20, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_spells(self, nValue):
        CBash.SetFIDFieldUIA(self._CollectionIndex, self._ModName, self._recordID, 20, struct.pack('I' * len(nValue), *nValue), len(nValue))
    spells = property(get_spells, set_spells)
    def get_script(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 21)
        if(retValue): return retValue.contents.value
        else: return None
    def set_script(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 21, nValue)
    script = property(get_script, set_script)
    def get_items(self):
        numRecords = CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 22)
        if(numRecords > 0): return [self.Item(self._CollectionIndex, self._ModName, self._recordID, 22, x) for x in range(0, numRecords)]
        else: return []
    def set_items(self, nItems):
        diffLength = len(nItems) - CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 22)
        nValues = [(item.item, item.count) for item in nItems]
        while(diffLength < 0):
            CBash.DeleteFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 22)
            diffLength += 1
        while(diffLength > 0):
            CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 22)
            diffLength -= 1
        for oItem, nValue in zip(self.items, nValues):
            oItem.item, oItem.count = nValue
    items = property(get_items, set_items)
    def get_aggression(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 23)
        if(retValue): return retValue.contents.value
        else: return None
    def set_aggression(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 23, c_ubyte(nValue))
    aggression = property(get_aggression, set_aggression)
    def get_confidence(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 24)
        if(retValue): return retValue.contents.value
        else: return None
    def set_confidence(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 24, c_ubyte(nValue))
    confidence = property(get_confidence, set_confidence)
    def get_energyLevel(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 25)
        if(retValue): return retValue.contents.value
        else: return None
    def set_energyLevel(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 25, c_ubyte(nValue))
    energyLevel = property(get_energyLevel, set_energyLevel)
    def get_responsibility(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 26)
        if(retValue): return retValue.contents.value
        else: return None
    def set_responsibility(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 26, c_ubyte(nValue))
    responsibility = property(get_responsibility, set_responsibility)
    def get_services(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 27)
        if(retValue): return retValue.contents.value
        else: return None
    def set_services(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 27, nValue)
    services = property(get_services, set_services)
    def get_trainSkill(self):
        CBash.ReadFIDField.restype = POINTER(c_byte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 28)
        if(retValue): return retValue.contents.value
        else: return None
    def set_trainSkill(self, nValue):
        CBash.SetFIDFieldC(self._CollectionIndex, self._ModName, self._recordID, 28, c_byte(nValue))
    trainSkill = property(get_trainSkill, set_trainSkill)
    def get_trainLevel(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 29)
        if(retValue): return retValue.contents.value
        else: return None
    def set_trainLevel(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 29, c_ubyte(nValue))
    trainLevel = property(get_trainLevel, set_trainLevel)
    def get_unused1(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 30)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 30, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_unused1(self, nValue):
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 30, struct.pack('2B', *nValue), 2)
    unused1 = property(get_unused1, set_unused1)
    def get_aiPackages(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 31)
        if(numRecords > 0):
            cRecords = POINTER(c_uint * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 31, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_aiPackages(self, nValue):
        CBash.SetFIDFieldUIA(self._CollectionIndex, self._ModName, self._recordID, 31, struct.pack('I' * len(nValue), *nValue), len(nValue))
    aiPackages = property(get_aiPackages, set_aiPackages)
    def get_animations(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 32)
        if(numRecords > 0):
            cRecords = (POINTER(c_char_p) * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 32, byref(cRecords))
            return [string_at(cRecords[x]) for x in range(0, numRecords)]
        else: return []
    def set_animations(self, nValue):
        length = len(nValue)
        cRecords = (c_char_p * length)(*nValue)
        CBash.SetFIDFieldStrA(self._CollectionIndex, self._ModName, self._recordID, 32, byref(cRecords), length)
    animations = property(get_animations, set_animations)
    def get_iclass(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 33)
        if(retValue): return retValue.contents.value
        else: return None
    def set_iclass(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 33, nValue)
    iclass = property(get_iclass, set_iclass)
    def get_armorer(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 34)
        if(retValue): return retValue.contents.value
        else: return None
    def set_armorer(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 34, c_ubyte(nValue))
    armorer = property(get_armorer, set_armorer)
    def get_athletics(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 35)
        if(retValue): return retValue.contents.value
        else: return None
    def set_athletics(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 35, c_ubyte(nValue))
    athletics = property(get_athletics, set_athletics)
    def get_blade(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 36)
        if(retValue): return retValue.contents.value
        else: return None
    def set_blade(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 36, c_ubyte(nValue))
    blade = property(get_blade, set_blade)
    def get_block(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 37)
        if(retValue): return retValue.contents.value
        else: return None
    def set_block(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 37, c_ubyte(nValue))
    block = property(get_block, set_block)
    def get_blunt(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 38)
        if(retValue): return retValue.contents.value
        else: return None
    def set_blunt(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 38, c_ubyte(nValue))
    blunt = property(get_blunt, set_blunt)
    def get_h2h(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 39)
        if(retValue): return retValue.contents.value
        else: return None
    def set_h2h(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 39, c_ubyte(nValue))
    h2h = property(get_h2h, set_h2h)
    def get_heavyArmor(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 40)
        if(retValue): return retValue.contents.value
        else: return None
    def set_heavyArmor(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 40, c_ubyte(nValue))
    heavyArmor = property(get_heavyArmor, set_heavyArmor)
    def get_alchemy(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 41)
        if(retValue): return retValue.contents.value
        else: return None
    def set_alchemy(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 41, c_ubyte(nValue))
    alchemy = property(get_alchemy, set_alchemy)
    def get_alteration(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 42)
        if(retValue): return retValue.contents.value
        else: return None
    def set_alteration(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 42, c_ubyte(nValue))
    alteration = property(get_alteration, set_alteration)
    def get_conjuration(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 43)
        if(retValue): return retValue.contents.value
        else: return None
    def set_conjuration(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 43, c_ubyte(nValue))
    conjuration = property(get_conjuration, set_conjuration)
    def get_destruction(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 44)
        if(retValue): return retValue.contents.value
        else: return None
    def set_destruction(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 44, c_ubyte(nValue))
    destruction = property(get_destruction, set_destruction)
    def get_illusion(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 45)
        if(retValue): return retValue.contents.value
        else: return None
    def set_illusion(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 45, c_ubyte(nValue))
    illusion = property(get_illusion, set_illusion)
    def get_mysticism(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 46)
        if(retValue): return retValue.contents.value
        else: return None
    def set_mysticism(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 46, c_ubyte(nValue))
    mysticism = property(get_mysticism, set_mysticism)
    def get_restoration(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 47)
        if(retValue): return retValue.contents.value
        else: return None
    def set_restoration(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 47, c_ubyte(nValue))
    restoration = property(get_restoration, set_restoration)
    def get_acrobatics(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 48)
        if(retValue): return retValue.contents.value
        else: return None
    def set_acrobatics(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 48, c_ubyte(nValue))
    acrobatics = property(get_acrobatics, set_acrobatics)
    def get_lightArmor(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 49)
        if(retValue): return retValue.contents.value
        else: return None
    def set_lightArmor(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 49, c_ubyte(nValue))
    lightArmor = property(get_lightArmor, set_lightArmor)
    def get_marksman(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 50)
        if(retValue): return retValue.contents.value
        else: return None
    def set_marksman(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 50, c_ubyte(nValue))
    marksman = property(get_marksman, set_marksman)
    def get_mercantile(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 51)
        if(retValue): return retValue.contents.value
        else: return None
    def set_mercantile(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 51, c_ubyte(nValue))
    mercantile = property(get_mercantile, set_mercantile)
    def get_security(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 52)
        if(retValue): return retValue.contents.value
        else: return None
    def set_security(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 52, c_ubyte(nValue))
    security = property(get_security, set_security)
    def get_sneak(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 53)
        if(retValue): return retValue.contents.value
        else: return None
    def set_sneak(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 53, c_ubyte(nValue))
    sneak = property(get_sneak, set_sneak)
    def get_speechcraft(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 54)
        if(retValue): return retValue.contents.value
        else: return None
    def set_speechcraft(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 54, c_ubyte(nValue))
    speechcraft = property(get_speechcraft, set_speechcraft)
    def get_health(self):
        CBash.ReadFIDField.restype = POINTER(c_ushort)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 55)
        if(retValue): return retValue.contents.value
        else: return None
    def set_health(self, nValue):
        CBash.SetFIDFieldUS(self._CollectionIndex, self._ModName, self._recordID, 55, c_ushort(nValue))
    health = property(get_health, set_health)
    def get_unused2(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 56)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 56, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_unused2(self, nValue):
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 56, struct.pack('2B', *nValue), 2)
    unused2 = property(get_unused2, set_unused2)
    def get_strength(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 57)
        if(retValue): return retValue.contents.value
        else: return None
    def set_strength(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 57, c_ubyte(nValue))
    strength = property(get_strength, set_strength)
    def get_intelligence(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 58)
        if(retValue): return retValue.contents.value
        else: return None
    def set_intelligence(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 58, c_ubyte(nValue))
    intelligence = property(get_intelligence, set_intelligence)
    def get_willpower(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 59)
        if(retValue): return retValue.contents.value
        else: return None
    def set_willpower(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 59, c_ubyte(nValue))
    willpower = property(get_willpower, set_willpower)
    def get_agility(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 60)
        if(retValue): return retValue.contents.value
        else: return None
    def set_agility(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 60, c_ubyte(nValue))
    agility = property(get_agility, set_agility)
    def get_speed(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 61)
        if(retValue): return retValue.contents.value
        else: return None
    def set_speed(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 61, c_ubyte(nValue))
    speed = property(get_speed, set_speed)
    def get_endurance(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 62)
        if(retValue): return retValue.contents.value
        else: return None
    def set_endurance(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 62, c_ubyte(nValue))
    endurance = property(get_endurance, set_endurance)
    def get_personality(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 63)
        if(retValue): return retValue.contents.value
        else: return None
    def set_personality(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 63, c_ubyte(nValue))
    personality = property(get_personality, set_personality)
    def get_luck(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 64)
        if(retValue): return retValue.contents.value
        else: return None
    def set_luck(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 64, c_ubyte(nValue))
    luck = property(get_luck, set_luck)
    def get_hair(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 65)
        if(retValue): return retValue.contents.value
        else: return None
    def set_hair(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 65, nValue)
    hair = property(get_hair, set_hair)
    def get_hairLength(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 66)
        if(retValue): return retValue.contents.value
        else: return None
    def set_hairLength(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 66, c_float(nValue))
    hairLength = property(get_hairLength, set_hairLength)
    def get_eye(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 67)
        if(retValue): return retValue.contents.value
        else: return None
    def set_eye(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 67, nValue)
    eye = property(get_eye, set_eye)
    def get_hairRed(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 68)
        if(retValue): return retValue.contents.value
        else: return None
    def set_hairRed(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 68, c_ubyte(nValue))
    hairRed = property(get_hairRed, set_hairRed)
    def get_hairGreen(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 69)
        if(retValue): return retValue.contents.value
        else: return None
    def set_hairGreen(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 69, c_ubyte(nValue))
    hairGreen = property(get_hairGreen, set_hairGreen)
    def get_hairBlue(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 70)
        if(retValue): return retValue.contents.value
        else: return None
    def set_hairBlue(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 70, c_ubyte(nValue))
    hairBlue = property(get_hairBlue, set_hairBlue)
    def get_unused3(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 71)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 71, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_unused3(self, nValue):
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 71, struct.pack('B', *nValue), 1)
    unused3 = property(get_unused3, set_unused3)
    def get_combatStyle(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 72)
        if(retValue): return retValue.contents.value
        else: return None
    def set_combatStyle(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 72, nValue)
    combatStyle = property(get_combatStyle, set_combatStyle)
    def get_fggs_p(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 73)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 73, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_fggs_p(self, nValue):
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 73, struct.pack('200B', *nValue), 200)
    fggs_p = property(get_fggs_p, set_fggs_p)
    def get_fgga_p(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 74)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 74, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_fgga_p(self, nValue):
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 74, struct.pack('120B', *nValue), 120)
    fgga_p = property(get_fgga_p, set_fgga_p)
    def get_fgts_p(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 75)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 75, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_fgts_p(self, nValue):
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 75, struct.pack('200B', *nValue), 200)
    fgts_p = property(get_fgts_p, set_fgts_p)
    def get_fnam(self):
        CBash.ReadFIDField.restype = POINTER(c_ushort)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 76)
        if(retValue): return retValue.contents.value
        else: return None
    def set_fnam(self, nValue):
        CBash.SetFIDFieldUS(self._CollectionIndex, self._ModName, self._recordID, 76, c_ushort(nValue))
    fnam = property(get_fnam, set_fnam)
class CREARecord(BaseRecord):
    def CopyAsOverride(self, targetMod):
        FID = CBash.CopyCREARecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(True))
        if(FID): return CREARecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def CopyAsNew(self, targetMod):
        FID = CBash.CopyCREARecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(False))
        if(FID): return CREARecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    class Faction(object):
        def __init__(self, CollectionIndex, ModName, recordID, subField, listIndex):
            self._CollectionIndex = CollectionIndex
            self._ModName = ModName
            self._recordID = recordID
            self._subField = subField
            self._listIndex = listIndex
        def get_faction(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 1).contents.value
        def set_faction(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 1, nValue)
        faction = property(get_faction, set_faction)
        def get_rank(self):
            CBash.ReadFIDListField.restype = POINTER(c_ubyte)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 2).contents.value
        def set_rank(self, nValue):
            CBash.SetFIDListFieldUC(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 2, c_ubyte(nValue))
        rank = property(get_rank, set_rank)
        def get_unused1(self):
            numRecords = CBash.GetFIDListArraySize(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 3)
            if(numRecords > 0):
                cRecords = POINTER(c_ubyte * numRecords)()
                CBash.GetFIDListArray(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 3, byref(cRecords))
                return [cRecords.contents[x] for x in range(0, numRecords)]
            else: return []
        def set_unused1(self, nValue):
            CBash.SetFIDListFieldR(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 3, struct.pack('3B', *nValue), 3)
        unused1 = property(get_unused1, set_unused1)
    class Item(object):
        def __init__(self, CollectionIndex, ModName, recordID, subField, listIndex):
            self._CollectionIndex = CollectionIndex
            self._ModName = ModName
            self._recordID = recordID
            self._subField = subField
            self._listIndex = listIndex
        def get_item(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 1).contents.value
        def set_item(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 1, nValue)
        item = property(get_item, set_item)
        def get_count(self):
            CBash.ReadFIDListField.restype = POINTER(c_int)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 2).contents.value
        def set_count(self, nValue):
            CBash.SetFIDListFieldI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 2, nValue)
        count = property(get_count, set_count)
    class Sound(object):
        def __init__(self, CollectionIndex, ModName, recordID, subField, listIndex):
            self._CollectionIndex = CollectionIndex
            self._ModName = ModName
            self._recordID = recordID
            self._subField = subField
            self._listIndex = listIndex
        def get_type(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 1).contents.value
        def set_type(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 1, nValue)
        type = property(get_type, set_type)
        def get_sound(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 2).contents.value
        def set_sound(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 2, nValue)
        sound = property(get_sound, set_sound)
        def get_chance(self):
            CBash.ReadFIDListField.restype = POINTER(c_ubyte)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 3).contents.value
        def set_chance(self, nValue):
            CBash.SetFIDListFieldUC(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 3, c_ubyte(nValue))
        chance = property(get_chance, set_chance)
    def newFactionsElement(self):
        listIndex = CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 20)
        if(listIndex == -1): return None
        return self.Faction(self._CollectionIndex, self._ModName, self._recordID, 20, listIndex)
    def newItemsElement(self):
        listIndex = CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 23)
        if(listIndex == -1): return None
        return self.Item(self._CollectionIndex, self._ModName, self._recordID, 23, listIndex)
    def newSoundsElement(self):
        listIndex = CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 59)
        if(listIndex == -1): return None
        return self.Sound(self._CollectionIndex, self._ModName, self._recordID, 59, listIndex)
    def get_full(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 6)
    def set_full(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 6, nValue)
    full = property(get_full, set_full)
    def get_modPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 7)
    def set_modPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 7, nValue)
    modPath = property(get_modPath, set_modPath)
    def get_modb(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 8)
        if(retValue): return retValue.contents.value
        else: return None
    def set_modb(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 8, c_float(nValue))
    modb = property(get_modb, set_modb)
    def get_modt_p(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 9)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 9, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_modt_p(self, nValue):
        length = len(nValue)
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 9, struct.pack('B' * length, *nValue), length)
    modt_p = property(get_modt_p, set_modt_p)
    def get_spells(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 10)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 10, byref(cRecords))
            return [cRecords[x].contents.value for x in range(0, numRecords)]
        else: return []
    def set_spells(self, nValue):
        CBash.SetFIDFieldUIA(self._CollectionIndex, self._ModName, self._recordID, 10, struct.pack('I' * len(nValue), *nValue), len(nValue))
    spells = property(get_spells, set_spells)
    def get_bodyParts(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 11)
        if(numRecords > 0):
            cRecords = cRecords = (POINTER(c_char_p) * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 11, byref(cRecords))
            return [string_at(cRecords[x]) for x in range(0, numRecords)]
        else: return []
    def set_bodyParts(self, nValue):
        length = len(nValue)
        cRecords = (c_char_p * length)(*nValue)
        CBash.SetFIDFieldStrA(self._CollectionIndex, self._ModName, self._recordID, 11, byref(cRecords), length)
    bodyParts = property(get_bodyParts, set_bodyParts)
    def get_nift_p(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 12)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 12, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_nift_p(self, nValue):
        length = len(nValue)
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 12, struct.pack('B' * length, *nValue), length)
    nift_p = property(get_nift_p, set_nift_p)
    def get_flags(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 13)
        if(retValue): return retValue.contents.value
        else: return None
    def set_flags(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 13, nValue)
    flags = property(get_flags, set_flags)
    def get_baseSpell(self):
        CBash.ReadFIDField.restype = POINTER(c_ushort)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 14)
        if(retValue): return retValue.contents.value
        else: return None
    def set_baseSpell(self, nValue):
        CBash.SetFIDFieldUS(self._CollectionIndex, self._ModName, self._recordID, 14, c_ushort(nValue))
    baseSpell = property(get_baseSpell, set_baseSpell)
    def get_fatigue(self):
        CBash.ReadFIDField.restype = POINTER(c_ushort)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 15)
        if(retValue): return retValue.contents.value
        else: return None
    def set_fatigue(self, nValue):
        CBash.SetFIDFieldUS(self._CollectionIndex, self._ModName, self._recordID, 15, c_ushort(nValue))
    fatigue = property(get_fatigue, set_fatigue)
    def get_barterGold(self):
        CBash.ReadFIDField.restype = POINTER(c_ushort)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 16)
        if(retValue): return retValue.contents.value
        else: return None
    def set_barterGold(self, nValue):
        CBash.SetFIDFieldUS(self._CollectionIndex, self._ModName, self._recordID, 16, c_ushort(nValue))
    barterGold = property(get_barterGold, set_barterGold)
    def get_level(self):
        CBash.ReadFIDField.restype = POINTER(c_short)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 17)
        if(retValue): return retValue.contents.value
        else: return None
    def set_level(self, nValue):
        CBash.SetFIDFieldS(self._CollectionIndex, self._ModName, self._recordID, 17, c_short(nValue))
    level = property(get_level, set_level)
    def get_calcMin(self):
        CBash.ReadFIDField.restype = POINTER(c_ushort)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 18)
        if(retValue): return retValue.contents.value
        else: return None
    def set_calcMin(self, nValue):
        CBash.SetFIDFieldUS(self._CollectionIndex, self._ModName, self._recordID, 18, c_ushort(nValue))
    calcMin = property(get_calcMin, set_calcMin)
    def get_calcMax(self):
        CBash.ReadFIDField.restype = POINTER(c_ushort)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 19)
        if(retValue): return retValue.contents.value
        else: return None
    def set_calcMax(self, nValue):
        CBash.SetFIDFieldUS(self._CollectionIndex, self._ModName, self._recordID, 19, c_ushort(nValue))
    calcMax = property(get_calcMax, set_calcMax)
    def get_factions(self):
        numRecords = CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 20)
        if(numRecords > 0): return [self.Faction(self._CollectionIndex, self._ModName, self._recordID, 20, x) for x in range(0, numRecords)]
        else: return []
    def set_factions(self, nFactions):
        diffLength = len(nFactions) - CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 20)
        nValues = [(faction.faction,faction.rank,faction.unused1) for faction in nFactions]
        while(diffLength < 0):
            CBash.DeleteFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 20)
            diffLength += 1
        while(diffLength > 0):
            CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 20)
            diffLength -= 1
        for oFaction, nValue in zip(self.factions, nValues):
            oFaction.faction, oFaction.rank, oFaction.unused1 = nValue
    factions = property(get_factions, set_factions)
    def get_deathItem(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 21)
        if(retValue): return retValue.contents.value
        else: return None
    def set_deathItem(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 21, nValue)
    deathItem = property(get_deathItem, set_deathItem)
    def get_script(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 22)
        if(retValue): return retValue.contents.value
        else: return None
    def set_script(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 22, nValue)
    script = property(get_script, set_script)
    def get_items(self):
        numRecords = CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 23)
        if(numRecords > 0): return [self.Item(self._CollectionIndex, self._ModName, self._recordID, 23, x) for x in range(0, numRecords)]
        else: return []
    def set_items(self, nItems):
        diffLength = len(nItems) - CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 23)
        nValues = [(item.item, item.count) for item in nItems]
        while(diffLength < 0):
            CBash.DeleteFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 23)
            diffLength += 1
        while(diffLength > 0):
            CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 23)
            diffLength -= 1
        for oItem, nValue in zip(self.items, nValues):
            oItem.item, oItem.count = nValue
    items = property(get_items, set_items)
    def get_aggression(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 24)
        if(retValue): return retValue.contents.value
        else: return None
    def set_aggression(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 24, c_ubyte(nValue))
    aggression = property(get_aggression, set_aggression)
    def get_confidence(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 25)
        if(retValue): return retValue.contents.value
        else: return None
    def set_confidence(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 25, c_ubyte(nValue))
    confidence = property(get_confidence, set_confidence)
    def get_energyLevel(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 26)
        if(retValue): return retValue.contents.value
        else: return None
    def set_energyLevel(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 26, c_ubyte(nValue))
    energyLevel = property(get_energyLevel, set_energyLevel)
    def get_responsibility(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 27)
        if(retValue): return retValue.contents.value
        else: return None
    def set_responsibility(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 27, c_ubyte(nValue))
    responsibility = property(get_responsibility, set_responsibility)
    def get_services(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 28)
        if(retValue): return retValue.contents.value
        else: return None
    def set_services(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 28, nValue)
    services = property(get_services, set_services)
    def get_trainSkill(self):
        CBash.ReadFIDField.restype = POINTER(c_byte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 29)
        if(retValue): return retValue.contents.value
        else: return None
    def set_trainSkill(self, nValue):
        CBash.SetFIDFieldC(self._CollectionIndex, self._ModName, self._recordID, 29, c_byte(nValue))
    trainSkill = property(get_trainSkill, set_trainSkill)
    def get_trainLevel(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 30)
        if(retValue): return retValue.contents.value
        else: return None
    def set_trainLevel(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 30, c_ubyte(nValue))
    trainLevel = property(get_trainLevel, set_trainLevel)
    def get_unused1(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 31)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 31, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_unused1(self, nValue):
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 31, struct.pack('2B', *nValue), 2)
    unused1 = property(get_unused1, set_unused1)
    def get_aiPackages(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 32)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 32, byref(cRecords))
            return [cRecords[x].contents.value for x in range(0, numRecords)]
        else: return []
    def set_aiPackages(self, nValue):
        CBash.SetFIDFieldUIA(self._CollectionIndex, self._ModName, self._recordID, 32, struct.pack('I' * len(nValue), *nValue), len(nValue))
    aiPackages = property(get_aiPackages, set_aiPackages)
    def get_animations(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 33)
        if(numRecords > 0):
            cRecords = cRecords = (POINTER(c_char_p) * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 33, byref(cRecords))
            return [string_at(cRecords[x]) for x in range(0, numRecords)]
        else: return []
    def set_animations(self, nValue):
        length = len(nValue)
        cRecords = (c_char_p * length)(*nValue)
        CBash.SetFIDFieldStrA(self._CollectionIndex, self._ModName, self._recordID, 33, byref(cRecords), length)
    animations = property(get_animations, set_animations)
    def get_creatureType(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 34)
        if(retValue): return retValue.contents.value
        else: return None
    def set_creatureType(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 34, c_ubyte(nValue))
    creatureType = property(get_creatureType, set_creatureType)
    def get_combat(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 35)
        if(retValue): return retValue.contents.value
        else: return None
    def set_combat(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 35, c_ubyte(nValue))
    combat = property(get_combat, set_combat)
    def get_magic(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 36)
        if(retValue): return retValue.contents.value
        else: return None
    def set_magic(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 36, c_ubyte(nValue))
    magic = property(get_magic, set_magic)
    def get_stealth(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 37)
        if(retValue): return retValue.contents.value
        else: return None
    def set_stealth(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 37, c_ubyte(nValue))
    stealth = property(get_stealth, set_stealth)
    def get_soul(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 38)
        if(retValue): return retValue.contents.value
        else: return None
    def set_soul(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 38, c_ubyte(nValue))
    soul = property(get_soul, set_soul)
    def get_unused2(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 39)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 39, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_unused2(self, nValue):
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 39, struct.pack('B', *nValue), 1)
    unused2 = property(get_unused2, set_unused2)
    def get_health(self):
        CBash.ReadFIDField.restype = POINTER(c_ushort)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 40)
        if(retValue): return retValue.contents.value
        else: return None
    def set_health(self, nValue):
        CBash.SetFIDFieldUS(self._CollectionIndex, self._ModName, self._recordID, 40, c_ushort(nValue))
    health = property(get_health, set_health)
    def get_unused3(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 41)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 41, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_unused3(self, nValue):
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 41, struct.pack('2B', *nValue), 2)
    unused3 = property(get_unused3, set_unused3)
    def get_attackDamage(self):
        CBash.ReadFIDField.restype = POINTER(c_ushort)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 42)
        if(retValue): return retValue.contents.value
        else: return None
    def set_attackDamage(self, nValue):
        CBash.SetFIDFieldUS(self._CollectionIndex, self._ModName, self._recordID, 42, c_ushort(nValue))
    attackDamage = property(get_attackDamage, set_attackDamage)
    def get_strength(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 43)
        if(retValue): return retValue.contents.value
        else: return None
    def set_strength(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 43, c_ubyte(nValue))
    strength = property(get_strength, set_strength)
    def get_intelligence(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 44)
        if(retValue): return retValue.contents.value
        else: return None
    def set_intelligence(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 44, c_ubyte(nValue))
    intelligence = property(get_intelligence, set_intelligence)
    def get_willpower(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 45)
        if(retValue): return retValue.contents.value
        else: return None
    def set_willpower(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 45, c_ubyte(nValue))
    willpower = property(get_willpower, set_willpower)
    def get_agility(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 46)
        if(retValue): return retValue.contents.value
        else: return None
    def set_agility(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 46, c_ubyte(nValue))
    agility = property(get_agility, set_agility)
    def get_speed(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 47)
        if(retValue): return retValue.contents.value
        else: return None
    def set_speed(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 47, c_ubyte(nValue))
    speed = property(get_speed, set_speed)
    def get_endurance(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 48)
        if(retValue): return retValue.contents.value
        else: return None
    def set_endurance(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 48, c_ubyte(nValue))
    endurance = property(get_endurance, set_endurance)
    def get_personality(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 49)
        if(retValue): return retValue.contents.value
        else: return None
    def set_personality(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 49, c_ubyte(nValue))
    personality = property(get_personality, set_personality)
    def get_luck(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 50)
        if(retValue): return retValue.contents.value
        else: return None
    def set_luck(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 50, c_ubyte(nValue))
    luck = property(get_luck, set_luck)
    def get_attackReach(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 51)
        if(retValue): return retValue.contents.value
        else: return None
    def set_attackReach(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 51, c_ubyte(nValue))
    attackReach = property(get_attackReach, set_attackReach)
    def get_combatStyle(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 52)
        if(retValue): return retValue.contents.value
        else: return None
    def set_combatStyle(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 52, nValue)
    combatStyle = property(get_combatStyle, set_combatStyle)
    def get_turningSpeed(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 53)
        if(retValue): return retValue.contents.value
        else: return None
    def set_turningSpeed(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 53, c_float(nValue))
    turningSpeed = property(get_turningSpeed, set_turningSpeed)
    def get_baseScale(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 54)
        if(retValue): return retValue.contents.value
        else: return None
    def set_baseScale(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 54, c_float(nValue))
    baseScale = property(get_baseScale, set_baseScale)
    def get_footWeight(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 55)
        if(retValue): return retValue.contents.value
        else: return None
    def set_footWeight(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 55, c_float(nValue))
    footWeight = property(get_footWeight, set_footWeight)
    def get_inheritsSoundsFrom(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 56)
        if(retValue): return retValue.contents.value
        else: return None
    def set_inheritsSoundsFrom(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 56, nValue)
    inheritsSoundsFrom = property(get_inheritsSoundsFrom, set_inheritsSoundsFrom)
    def get_bloodSprayPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 57)
    def set_bloodSprayPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 57, nValue)
    bloodSprayPath = property(get_bloodSprayPath, set_bloodSprayPath)
    def get_bloodDecalPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 58)
    def set_bloodDecalPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 58, nValue)
    bloodDecalPath = property(get_bloodDecalPath, set_bloodDecalPath)
    def get_sounds(self):
        numRecords = CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 59)
        if(numRecords > 0): return [self.Sound(self._CollectionIndex, self._ModName, self._recordID, 59, x) for x in range(0, numRecords)]
        else: return []
    def set_sounds(self, nSounds):
        diffLength = len(nSounds) - CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 59)
        nValues = [(nSound.type, nSound.sound, nSound.chance) for nSound in nSounds]
        while(diffLength < 0):
            CBash.DeleteFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 59)
            diffLength += 1
        while(diffLength > 0):
            CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 59)
            diffLength -= 1
        for oSound, nValue in zip(self.sounds, nValues):
            oSound.type, oSound.sound, oSound.chance = nValue
    sounds = property(get_sounds, set_sounds)
class LVLRecord(BaseRecord):
    def CopyAsOverride(self, targetMod):
        FID = CBash.CopyLVLRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(True))
        if(FID): return LVLRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def CopyAsNew(self, targetMod):
        FID = CBash.CopyLVLRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(False))
        if(FID): return LVLRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    class Entry(object):
        def __init__(self, CollectionIndex, ModName, recordID, subField, listIndex):
            self._CollectionIndex = CollectionIndex
            self._ModName = ModName
            self._recordID = recordID
            self._subField = subField
            self._listIndex = listIndex
        def get_level(self):
            CBash.ReadFIDListField.restype = POINTER(c_short)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 1).contents.value
        def set_level(self, nValue):
            CBash.SetFIDListFieldS(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 1, c_short(nValue))
        level = property(get_level, set_level)
        def get_unused1(self):
            numRecords = CBash.GetFIDListArraySize(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 2)
            if(numRecords > 0):
                cRecords = POINTER(c_ubyte * numRecords)()
                CBash.GetFIDListArray(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 2, byref(cRecords))
                return [cRecords.contents[x] for x in range(0, numRecords)]
            else: return []
        def set_unused1(self, nValue):
            CBash.SetFIDListFieldR(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 2, struct.pack('2B', *nValue), 2)
        unused1 = property(get_unused1, set_unused1)
        def get_listId(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 3).contents.value
        def set_listId(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 3, nValue)
        listId = property(get_listId, set_listId)
        def get_count(self):
            CBash.ReadFIDListField.restype = POINTER(c_short)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 4).contents.value
        def set_count(self, nValue):
            CBash.SetFIDListFieldS(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 4, c_short(nValue))
        count = property(get_count, set_count)
        def get_unused2(self):
            numRecords = CBash.GetFIDListArraySize(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 5)
            if(numRecords > 0):
                cRecords = POINTER(c_ubyte * numRecords)()
                CBash.GetFIDListArray(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 5, byref(cRecords))
                return [cRecords.contents[x] for x in range(0, numRecords)]
            else: return []
        def set_unused2(self, nValue):
            CBash.SetFIDListFieldR(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 5, struct.pack('2B', *nValue), 2)
        unused2 = property(get_unused2, set_unused2)
    def newEntriesElement(self):
        listIndex = CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 10)
        if(listIndex == -1): return None
        return self.Entry(self._CollectionIndex, self._ModName, self._recordID, 10, listIndex)
    def get_chanceNone(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 6)
        if(retValue): return retValue.contents.value
        else: return None
    def set_chanceNone(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 6, c_ubyte(nValue))
    chanceNone = property(get_chanceNone, set_chanceNone)
    def get_flags(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 7)
        if(retValue): return retValue.contents.value
        else: return None
    def set_flags(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 7, c_ubyte(nValue))
    flags = property(get_flags, set_flags)
    def get_entries(self):
        numRecords = CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 10)
        if(numRecords > 0): return [self.Entry(self._CollectionIndex, self._ModName, self._recordID, 10, x) for x in range(0, numRecords)]
        else: return []
    def set_entries(self, nEntries):
        diffLength = len(nEntries) - CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 10)
        nValues = [(nEntry.level, nEntry.unused1, nEntry.listId, nEntry.count, nEntry.unused2) for nEntry in nEntries]
        while(diffLength < 0):
            CBash.DeleteFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 10)
            diffLength += 1
        while(diffLength > 0):
            CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 10)
            diffLength -= 1
        for oEntry, nValue in zip(self.entries, nValues):
            oEntry.level, oEntry.unused1, oEntry.listId, oEntry.count, oEntry.unused2 = nValue
    entries = property(get_entries, set_entries)
class LVLCRecord(LVLRecord):
    def CopyAsOverride(self, targetMod):
        FID = CBash.CopyLVLCRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(True))
        if(FID): return LVLCRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def CopyAsNew(self, targetMod):
        FID = CBash.CopyLVLCRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(False))
        if(FID): return LVLCRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def get_script(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 8)
        if(retValue): return retValue.contents.value
        else: return None
    def set_script(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 8, nValue)
    script = property(get_script, set_script)
    def get_template(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 9)
        if(retValue): return retValue.contents.value
        else: return None
    def set_template(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 9, nValue)
    template = property(get_template, set_template)
class SLGMRecord(BaseRecord):
    def CopyAsOverride(self, targetMod):
        FID = CBash.CopySLGMRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(True))
        if(FID): return SLGMRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def CopyAsNew(self, targetMod):
        FID = CBash.CopySLGMRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(False))
        if(FID): return SLGMRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def get_full(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 6)
    def set_full(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 6, nValue)
    full = property(get_full, set_full)
    def get_modPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 7)
    def set_modPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 7, nValue)
    modPath = property(get_modPath, set_modPath)
    def get_modb(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 8)
        if(retValue): return retValue.contents.value
        else: return None
    def set_modb(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 8, c_float(nValue))
    modb = property(get_modb, set_modb)
    def get_modt_p(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 9)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 9, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_modt_p(self, nValue):
        length = len(nValue)
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 9, struct.pack('B' * length, *nValue), length)
    modt_p = property(get_modt_p, set_modt_p)
    def get_iconPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 10)
    def set_iconPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 10, nValue)
    iconPath = property(get_iconPath, set_iconPath)
    def get_script(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 11)
        if(retValue): return retValue.contents.value
        else: return None
    def set_script(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 11, c_uint(nValue))
    script = property(get_script, set_script)
    def get_value(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 12)
        if(retValue): return retValue.contents.value
        else: return None
    def set_value(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 12, c_uint(nValue))
    value = property(get_value, set_value)
    def get_weight(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 13)
        if(retValue): return retValue.contents.value
        else: return None
    def set_weight(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 13, c_float(nValue))
    weight = property(get_weight, set_weight)
    def get_soul(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 14)
        if(retValue): return retValue.contents.value
        else: return None
    def set_soul(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 14, c_ubyte(nValue))
    soul = property(get_soul, set_soul)
    def get_capacity(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 15)
        if(retValue): return retValue.contents.value
        else: return None
    def set_capacity(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 15, c_ubyte(nValue))
    capacity = property(get_capacity, set_capacity)
class KEYMRecord(BaseRecord):
    def CopyAsOverride(self, targetMod):
        FID = CBash.CopyKEYMRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(True))
        if(FID): return KEYMRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def CopyAsNew(self, targetMod):
        FID = CBash.CopyKEYMRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(False))
        if(FID): return KEYMRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def get_full(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 6)
    def set_full(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 6, nValue)
    full = property(get_full, set_full)
    def get_modPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 7)
    def set_modPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 7, nValue)
    modPath = property(get_modPath, set_modPath)
    def get_modb(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 8)
        if(retValue): return retValue.contents.value
        else: return None
    def set_modb(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 8, c_float(nValue))
    modb = property(get_modb, set_modb)
    def get_modt_p(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 9)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 9, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_modt_p(self, nValue):
        length = len(nValue)
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 9, struct.pack('B' * length, *nValue), length)
    modt_p = property(get_modt_p, set_modt_p)
    def get_iconPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 10)
    def set_iconPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 10, nValue)
    iconPath = property(get_iconPath, set_iconPath)
    def get_script(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 11)
        if(retValue): return retValue.contents.value
        else: return None
    def set_script(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 11, c_uint(nValue))
    script = property(get_script, set_script)
    def get_value(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 12)
        if(retValue): return retValue.contents.value
        else: return None
    def set_value(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 12, c_uint(nValue))
    value = property(get_value, set_value)
    def get_weight(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 13)
        if(retValue): return retValue.contents.value
        else: return None
    def set_weight(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 13, c_float(nValue))
    weight = property(get_weight, set_weight)
class ALCHRecord(BaseRecord):
    def CopyAsOverride(self, targetMod):
        FID = CBash.CopyALCHRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(True))
        if(FID): return ALCHRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def CopyAsNew(self, targetMod):
        FID = CBash.CopyALCHRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(False))
        if(FID): return ALCHRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    class Effect(object):
        def __init__(self, CollectionIndex, ModName, recordID, subField, listIndex):
            self._CollectionIndex = CollectionIndex
            self._ModName = ModName
            self._recordID = recordID
            self._subField = subField
            self._listIndex = listIndex
        ##name0 and name are both are always the same value, so setting one will set both. They're basically aliases
        def get_name0(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 1).contents.value
        def set_name0(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 1, nValue)
        name0 = property(get_name0, set_name0)
        def get_name(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 2).contents.value
        def set_name(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 2, nValue)
        name = property(get_name, set_name)
        def get_magnitude(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 3).contents.value
        def set_magnitude(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 3, nValue)
        magnitude = property(get_magnitude, set_magnitude)
        def get_area(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 4).contents.value
        def set_area(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 4, nValue)
        area = property(get_area, set_area)
        def get_duration(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 5).contents.value
        def set_duration(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 5, nValue)
        duration = property(get_duration, set_duration)
        def get_recipient(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 6).contents.value
        def set_recipient(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 6, nValue)
        recipient = property(get_recipient, set_recipient)
        def get_actorValue(self):
            CBash.ReadFIDListField.restype = POINTER(c_int)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 7).contents.value
        def set_actorValue(self, nValue):
            CBash.SetFIDListFieldI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 7, nValue)
        actorValue = property(get_actorValue, set_actorValue)
        def get_script(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 8).contents.value
        def set_script(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 8, nValue)
        script = property(get_script, set_script)
        def get_school(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 9).contents.value
        def set_school(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 9, nValue)
        school = property(get_school, set_school)
        def get_visual(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 10).contents.value
        def set_visual(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 10, nValue)
        visual = property(get_visual, set_visual)
        def get_flags(self):
            CBash.ReadFIDListField.restype = POINTER(c_ubyte)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 11).contents.value
        def set_flags(self, nValue):
            CBash.SetFIDListFieldUC(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 11, c_ubyte(nValue))
        flags = property(get_flags, set_flags)
        def get_unused1(self):
            numRecords = CBash.GetFIDListArraySize(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 12)
            if(numRecords > 0):
                cRecords = POINTER(c_ubyte * numRecords)()
                CBash.GetFIDListArray(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 12, byref(cRecords))
                return [cRecords.contents[x] for x in range(0, numRecords)]
            else: return []
        def set_unused1(self, nValue):
            CBash.SetFIDListFieldR(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 12, struct.pack('3B', *nValue), 3)
        unused1 = property(get_unused1, set_unused1)
        def get_full(self):
            CBash.ReadFIDListField.restype = c_char_p
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 13)
        def set_full(self, nValue):
            CBash.SetFIDListFieldStr(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 13, nValue)
        full = property(get_full, set_full)
    def newEffectsElement(self):
        listIndex = CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 16)
        if(listIndex == -1): return None
        return self.Effect(self._CollectionIndex, self._ModName, self._recordID, 16, listIndex)
    def get_full(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 6)
    def set_full(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 6, nValue)
    full = property(get_full, set_full)
    def get_modPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 7)
    def set_modPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 7, nValue)
    modPath = property(get_modPath, set_modPath)
    def get_modb(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 8)
        if(retValue): return retValue.contents.value
        else: return None
    def set_modb(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 8, c_float(nValue))
    modb = property(get_modb, set_modb)
    def get_modt_p(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 9)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 9, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_modt_p(self, nValue):
        length = len(nValue)
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 9, struct.pack('B' * length, *nValue), length)
    modt_p = property(get_modt_p, set_modt_p)
    def get_iconPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 10)
    def set_iconPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 10, nValue)
    iconPath = property(get_iconPath, set_iconPath)
    def get_script(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 11)
        if(retValue): return retValue.contents.value
        else: return None
    def set_script(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 11, c_uint(nValue))
    script = property(get_script, set_script)
    def get_weight(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 12)
        if(retValue): return retValue.contents.value
        else: return None
    def set_weight(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 12, c_float(nValue))
    weight = property(get_weight, set_weight)
    def get_value(self):
        CBash.ReadFIDField.restype = POINTER(c_int)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 13)
        if(retValue): return retValue.contents.value
        else: return None
    def set_value(self, nValue):
        CBash.SetFIDFieldI(self._CollectionIndex, self._ModName, self._recordID, 13, c_int(nValue))
    value = property(get_value, set_value)
    def get_flags(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 14)
        if(retValue): return retValue.contents.value
        else: return None
    def set_flags(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 14, c_ubyte(nValue))
    flags = property(get_flags, set_flags)
    def get_unused1(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 15)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 15, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_unused1(self, nValue):
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 15, struct.pack('3B', *nValue), 3)
    unused1 = property(get_unused1, set_unused1)
    def get_effects(self):
        numRecords = CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 16)
        if(numRecords > 0): return [self.Effect(self._CollectionIndex, self._ModName, self._recordID, 16, x) for x in range(0, numRecords)]
        else: return []
    def set_effects(self, nEffects):
        diffLength = len(nEffects) - CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 16)
        nValues = [(nEffect.name0, nEffect.name, nEffect.magnitude, nEffect.area, nEffect.duration, nEffect.recipient, nEffect.actorValue, nEffect.script, nEffect.school, nEffect.visual, nEffect.flags, nEffect.unused1, nEffect.full) for nEffect in nEffects]
        while(diffLength < 0):
            CBash.DeleteFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 16)
            diffLength += 1
        while(diffLength > 0):
            CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 16)
            diffLength -= 1
        for oEffect, nValue in zip(self.effects, nValues):
            oEffect.name0, oEffect.name, oEffect.magnitude, oEffect.area, oEffect.duration, oEffect.recipient, oEffect.actorValue, oEffect.script, oEffect.school, oEffect.visual, oEffect.flags, oEffect.unused1, oEffect.full = nValue
    effects = property(get_effects, set_effects)
class SBSPRecord(BaseRecord):
    def CopyAsOverride(self, targetMod):
        FID = CBash.CopySBSPRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(True))
        if(FID): return SBSPRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def CopyAsNew(self, targetMod):
        FID = CBash.CopySBSPRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(False))
        if(FID): return SBSPRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def get_sizeX(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 6)
        if(retValue): return retValue.contents.value
        else: return None
    def set_sizeX(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 6, c_float(nValue))
    sizeX = property(get_sizeX, set_sizeX)
    def get_sizeY(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 7)
        if(retValue): return retValue.contents.value
        else: return None
    def set_sizeY(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 7, c_float(nValue))
    sizeY = property(get_sizeY, set_sizeY)
    def get_sizeZ(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 8)
        if(retValue): return retValue.contents.value
        else: return None
    def set_sizeZ(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 8, c_float(nValue))
    sizeZ = property(get_sizeZ, set_sizeZ)
class SGSTRecord(BaseRecord):
    def CopyAsOverride(self, targetMod):
        FID = CBash.CopySGSTRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(True))
        if(FID): return SGSTRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def CopyAsNew(self, targetMod):
        FID = CBash.CopySGSTRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(False))
        if(FID): return SGSTRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    class Effect(object):
        def __init__(self, CollectionIndex, ModName, recordID, subField, listIndex):
            self._CollectionIndex = CollectionIndex
            self._ModName = ModName
            self._recordID = recordID
            self._subField = subField
            self._listIndex = listIndex
        ##name0 and name are both are always the same value, so setting one will set both. They're basically aliases
        def get_name0(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 1).contents.value
        def set_name0(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 1, nValue)
        name0 = property(get_name0, set_name0)
        def get_name(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 2).contents.value
        def set_name(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 2, nValue)
        name = property(get_name, set_name)
        def get_magnitude(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 3).contents.value
        def set_magnitude(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 3, nValue)
        magnitude = property(get_magnitude, set_magnitude)
        def get_area(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 4).contents.value
        def set_area(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 4, nValue)
        area = property(get_area, set_area)
        def get_duration(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 5).contents.value
        def set_duration(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 5, nValue)
        duration = property(get_duration, set_duration)
        def get_recipient(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 6).contents.value
        def set_recipient(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 6, nValue)
        recipient = property(get_recipient, set_recipient)
        def get_actorValue(self):
            CBash.ReadFIDListField.restype = POINTER(c_int)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 7).contents.value
        def set_actorValue(self, nValue):
            CBash.SetFIDListFieldI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 7, nValue)
        actorValue = property(get_actorValue, set_actorValue)
        def get_script(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 8).contents.value
        def set_script(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 8, nValue)
        script = property(get_script, set_script)
        def get_school(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 9).contents.value
        def set_school(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 9, nValue)
        school = property(get_school, set_school)
        def get_visual(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 10).contents.value
        def set_visual(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 10, nValue)
        visual = property(get_visual, set_visual)
        def get_flags(self):
            CBash.ReadFIDListField.restype = POINTER(c_ubyte)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 11).contents.value
        def set_flags(self, nValue):
            CBash.SetFIDListFieldUC(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 11, c_ubyte(nValue))
        flags = property(get_flags, set_flags)
        def get_unused1(self):
            numRecords = CBash.GetFIDListArraySize(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 12)
            if(numRecords > 0):
                cRecords = POINTER(c_ubyte * numRecords)()
                CBash.GetFIDListArray(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 12, byref(cRecords))
                return [cRecords.contents[x] for x in range(0, numRecords)]
            else: return []
        def set_unused1(self, nValue):
            CBash.SetFIDListFieldR(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 12, struct.pack('3B', *nValue), 3)
        unused1 = property(get_unused1, set_unused1)
        def get_full(self):
            CBash.ReadFIDListField.restype = c_char_p
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 13)
        def set_full(self, nValue):
            CBash.SetFIDListFieldStr(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 13, nValue)
        full = property(get_full, set_full)
    def newEffectsElement(self):
        listIndex = CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 12)
        if(listIndex == -1): return None
        return self.Effect(self._CollectionIndex, self._ModName, self._recordID, 12, listIndex)
    def get_full(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 6)
    def set_full(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 6, nValue)
    full = property(get_full, set_full)
    def get_modPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 7)
    def set_modPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 7, nValue)
    modPath = property(get_modPath, set_modPath)
    def get_modb(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 8)
        if(retValue): return retValue.contents.value
        else: return None
    def set_modb(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 8, c_float(nValue))
    modb = property(get_modb, set_modb)
    def get_modt_p(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 9)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 9, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_modt_p(self, nValue):
        length = len(nValue)
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 9, struct.pack('B' * length, *nValue), length)
    modt_p = property(get_modt_p, set_modt_p)
    def get_iconPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 10)
    def set_iconPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 10, nValue)
    iconPath = property(get_iconPath, set_iconPath)
    def get_script(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 11)
        if(retValue): return retValue.contents.value
        else: return None
    def set_script(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 11, c_uint(nValue))
    script = property(get_script, set_script)
    def get_effects(self):
        numRecords = CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 12)
        if(numRecords > 0): return [self.Effect(self._CollectionIndex, self._ModName, self._recordID, 12, x) for x in range(0, numRecords)]
        else: return []
    def set_effects(self, nEffects):
        diffLength = len(nEffects) - CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 12)
        nValues = [(nEffect.name0, nEffect.name, nEffect.magnitude, nEffect.area, nEffect.duration, nEffect.recipient, nEffect.actorValue, nEffect.script, nEffect.school, nEffect.visual, nEffect.flags, nEffect.unused1, nEffect.full) for nEffect in nEffects]
        while(diffLength < 0):
            CBash.DeleteFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 12)
            diffLength += 1
        while(diffLength > 0):
            CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 12)
            diffLength -= 1
        for oEffect, nValue in zip(self.effects, nValues):
            oEffect.name0, oEffect.name, oEffect.magnitude, oEffect.area, oEffect.duration, oEffect.recipient, oEffect.actorValue, oEffect.script, oEffect.school, oEffect.visual, oEffect.flags, oEffect.unused1, oEffect.full = nValue
    effects = property(get_effects, set_effects)
    def get_uses(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 13)
        if(retValue): return retValue.contents.value
        else: return None
    def set_uses(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 13, c_ubyte(nValue))
    uses = property(get_uses, set_uses)
    def get_value(self):
        CBash.ReadFIDField.restype = POINTER(c_int)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 14)
        if(retValue): return retValue.contents.value
        else: return None
    def set_value(self, nValue):
        CBash.SetFIDFieldI(self._CollectionIndex, self._ModName, self._recordID, 14, nValue)
    value = property(get_value, set_value)
    def get_weight(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 15)
        if(retValue): return retValue.contents.value
        else: return None
    def set_weight(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 15, c_float(nValue))
    weight = property(get_weight, set_weight)
class LVLIRecord(LVLRecord):
    def CopyAsOverride(self, targetMod):
        FID = CBash.CopyLVLIRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(True))
        if(FID): return LVLIRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def CopyAsNew(self, targetMod):
        FID = CBash.CopyLVLIRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(False))
        if(FID): return LVLIRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def get_data_p(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 11)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 11, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_data_p(self, nValue):
        length = len(nValue)
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 11, struct.pack('B' * length, *nValue), length)
    data_p = property(get_data_p, set_data_p)
class WTHRRecord(BaseRecord):
    def CopyAsOverride(self, targetMod):
        FID = CBash.CopyWTHRRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(True))
        if(FID): return WTHRRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def CopyAsNew(self, targetMod):
        FID = CBash.CopyWTHRRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(False))
        if(FID): return WTHRRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    class WTHRColor(object):
        def __init__(self, CollectionIndex, ModName, recordID, listIndex):
            self._CollectionIndex = CollectionIndex
            self._ModName = ModName
            self._recordID = recordID
            self._listIndex = listIndex
        def get_riseRed(self):
            CBash.ReadFIDField.restype = POINTER(c_ubyte)
            retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, self._listIndex)
            if(retValue): return retValue.contents.value
            else: return None
        def set_riseRed(self, nValue):
            CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, self._listIndex, c_ubyte(nValue))
        riseRed = property(get_riseRed, set_riseRed)
        def get_riseGreen(self):
            CBash.ReadFIDField.restype = POINTER(c_ubyte)
            retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, self._listIndex + 1)
            if(retValue): return retValue.contents.value
            else: return None
        def set_riseGreen(self, nValue):
            CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, self._listIndex + 1, c_ubyte(nValue))
        riseGreen = property(get_riseGreen, set_riseGreen)
        def get_riseBlue(self):
            CBash.ReadFIDField.restype = POINTER(c_ubyte)
            retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, self._listIndex + 2)
            if(retValue): return retValue.contents.value
            else: return None
        def set_riseBlue(self, nValue):
            CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, self._listIndex + 2, c_ubyte(nValue))
        riseBlue = property(get_riseBlue, set_riseBlue)
        def get_unused1(self):
            numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, self._listIndex + 3)
            if(numRecords > 0):
                cRecords = POINTER(c_ubyte * numRecords)()
                CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, self._listIndex + 3, byref(cRecords))
                return [cRecords.contents[x] for x in range(0, numRecords)]
            else: return []
        def set_unused1(self, nValue):
            CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, self._listIndex + 3, struct.pack('B', *nValue), 1)
        unused1 = property(get_unused1, set_unused1)
        def get_dayRed(self):
            CBash.ReadFIDField.restype = POINTER(c_ubyte)
            retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, self._listIndex + 4)
            if(retValue): return retValue.contents.value
            else: return None
        def set_dayRed(self, nValue):
            CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, self._listIndex + 4, c_ubyte(nValue))
        dayRed = property(get_dayRed, set_dayRed)
        def get_dayGreen(self):
            CBash.ReadFIDField.restype = POINTER(c_ubyte)
            retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, self._listIndex + 5)
            if(retValue): return retValue.contents.value
            else: return None
        def set_dayGreen(self, nValue):
            CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, self._listIndex + 5, c_ubyte(nValue))
        dayGreen = property(get_dayGreen, set_dayGreen)
        def get_dayBlue(self):
            CBash.ReadFIDField.restype = POINTER(c_ubyte)
            retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, self._listIndex + 6)
            if(retValue): return retValue.contents.value
            else: return None
        def set_dayBlue(self, nValue):
            CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, self._listIndex + 6, c_ubyte(nValue))
        dayBlue = property(get_dayBlue, set_dayBlue)
        def get_unused2(self):
            numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, self._listIndex + 7)
            if(numRecords > 0):
                cRecords = POINTER(c_ubyte * numRecords)()
                CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, self._listIndex + 7, byref(cRecords))
                return [cRecords.contents[x] for x in range(0, numRecords)]
            else: return []
        def set_unused2(self, nValue):
            CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, self._listIndex + 7, struct.pack('B', *nValue), 1)
        unused2 = property(get_unused2, set_unused2)
        def get_setRed(self):
            CBash.ReadFIDField.restype = POINTER(c_ubyte)
            retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, self._listIndex + 8)
            if(retValue): return retValue.contents.value
            else: return None
        def set_setRed(self, nValue):
            CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, self._listIndex + 8, c_ubyte(nValue))
        setRed = property(get_setRed, set_setRed)
        def get_setGreen(self):
            CBash.ReadFIDField.restype = POINTER(c_ubyte)
            retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, self._listIndex + 9)
            if(retValue): return retValue.contents.value
            else: return None
        def set_setGreen(self, nValue):
            CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, self._listIndex + 9, c_ubyte(nValue))
        setGreen = property(get_setGreen, set_setGreen)
        def get_setBlue(self):
            CBash.ReadFIDField.restype = POINTER(c_ubyte)
            retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, self._listIndex + 10)
            if(retValue): return retValue.contents.value
            else: return None
        def set_setBlue(self, nValue):
            CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, self._listIndex + 10, c_ubyte(nValue))
        setBlue = property(get_setBlue, set_setBlue)
        def get_unused3(self):
            numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, self._listIndex + 11)
            if(numRecords > 0):
                cRecords = POINTER(c_ubyte * numRecords)()
                CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, self._listIndex + 11, byref(cRecords))
                return [cRecords.contents[x] for x in range(0, numRecords)]
            else: return []
        def set_unused3(self, nValue):
            CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, self._listIndex + 11, struct.pack('B', *nValue), 1)
        unused3 = property(get_unused3, set_unused3)
        def get_nightRed(self):
            CBash.ReadFIDField.restype = POINTER(c_ubyte)
            retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, self._listIndex + 12)
            if(retValue): return retValue.contents.value
            else: return None
        def set_nightRed(self, nValue):
            CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, self._listIndex + 12, c_ubyte(nValue))
        nightRed = property(get_nightRed, set_nightRed)
        def get_nightGreen(self):
            CBash.ReadFIDField.restype = POINTER(c_ubyte)
            retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, self._listIndex + 13)
            if(retValue): return retValue.contents.value
            else: return None
        def set_nightGreen(self, nValue):
            CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, self._listIndex + 13, c_ubyte(nValue))
        nightGreen = property(get_nightGreen, set_nightGreen)
        def get_nightBlue(self):
            CBash.ReadFIDField.restype = POINTER(c_ubyte)
            retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, self._listIndex + 14)
            if(retValue): return retValue.contents.value
            else: return None
        def set_nightBlue(self, nValue):
            CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, self._listIndex + 14, c_ubyte(nValue))
        nightBlue = property(get_nightBlue, set_nightBlue)
        def get_unused4(self):
            numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, self._listIndex + 15)
            if(numRecords > 0):
                cRecords = POINTER(c_ubyte * numRecords)()
                CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, self._listIndex + 15, byref(cRecords))
                return [cRecords.contents[x] for x in range(0, numRecords)]
            else: return []
        def set_unused4(self, nValue):
            CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, self._listIndex + 15, struct.pack('B', *nValue), 1)
        unused4 = property(get_unused4, set_unused4)  
    class Sound(object):
        def __init__(self, CollectionIndex, ModName, recordID, listIndex):
            self._CollectionIndex = CollectionIndex
            self._ModName = ModName
            self._recordID = recordID
            self._listIndex = listIndex
        def get_sound(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, 204, self._listIndex, 1).contents.value
        def set_sound(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, 204, self._listIndex, 1, nValue)
        sound = property(get_sound, set_sound)
        def get_type(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, 204, self._listIndex, 2).contents.value
        def set_type(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, 204, self._listIndex, 2, nValue)
        type = property(get_type, set_type)
    def newSoundsElement(self):
        listIndex = CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 204)
        if(listIndex == -1): return None
        return self.Sound(self._CollectionIndex, self._ModName, self._recordID, listIndex)
    def get_lowerLayer(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 6)
    def set_lowerLayer(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 6, nValue)
    lowerLayer = property(get_lowerLayer, set_lowerLayer)
    def get_upperLayer(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 7)
    def set_upperLayer(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 7, nValue)
    upperLayer = property(get_upperLayer, set_upperLayer)
    def get_modPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 8)
    def set_modPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 8, nValue)
    modPath = property(get_modPath, set_modPath)
    def get_modb(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 9)
        if(retValue): return retValue.contents.value
        else: return None
    def set_modb(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 9, c_float(nValue))
    modb = property(get_modb, set_modb)
    def get_modt_p(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 10)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 10, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_modt_p(self, nValue):
        length = len(nValue)
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 10, struct.pack('B' * length, *nValue), length)
    modt_p = property(get_modt_p, set_modt_p)
    @property
    def upperSky(self):
        return self.WTHRColor(self._CollectionIndex, self._ModName, self._recordID, 11)
    @property
    def fog(self):
        return self.WTHRColor(self._CollectionIndex, self._ModName, self._recordID, 27)
    @property
    def lowerClouds(self):
        return self.WTHRColor(self._CollectionIndex, self._ModName, self._recordID, 43)
    @property
    def ambient(self):
        return self.WTHRColor(self._CollectionIndex, self._ModName, self._recordID, 59)
    @property
    def sunlight(self):
        return self.WTHRColor(self._CollectionIndex, self._ModName, self._recordID, 75)
    @property
    def sun(self):
        return self.WTHRColor(self._CollectionIndex, self._ModName, self._recordID, 91)
    @property
    def stars(self):
        return self.WTHRColor(self._CollectionIndex, self._ModName, self._recordID, 107)
    @property
    def lowerSky(self):
        return self.WTHRColor(self._CollectionIndex, self._ModName, self._recordID, 123)
    @property
    def horizon(self):
        return self.WTHRColor(self._CollectionIndex, self._ModName, self._recordID, 139)
    @property
    def upperClouds(self):
        return self.WTHRColor(self._CollectionIndex, self._ModName, self._recordID, 155)
    def get_fogDayNear(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 171)
        if(retValue): return retValue.contents.value
        else: return None
    def set_fogDayNear(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 171, c_float(nValue))
    fogDayNear = property(get_fogDayNear, set_fogDayNear)
    def get_fogDayFar(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 172)
        if(retValue): return retValue.contents.value
        else: return None
    def set_fogDayFar(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 172, c_float(nValue))
    fogDayFar = property(get_fogDayFar, set_fogDayFar)
    def get_fogNightNear(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 173)
        if(retValue): return retValue.contents.value
        else: return None
    def set_fogNightNear(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 173, c_float(nValue))
    fogNightNear = property(get_fogNightNear, set_fogNightNear)
    def get_fogNightFar(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 174)
        if(retValue): return retValue.contents.value
        else: return None
    def set_fogNightFar(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 174, c_float(nValue))
    fogNightFar = property(get_fogNightFar, set_fogNightFar)
    def get_eyeAdaptSpeed(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 175)
        if(retValue): return retValue.contents.value
        else: return None
    def set_eyeAdaptSpeed(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 175, c_float(nValue))
    eyeAdaptSpeed = property(get_eyeAdaptSpeed, set_eyeAdaptSpeed)
    def get_blurRadius(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 176)
        if(retValue): return retValue.contents.value
        else: return None
    def set_blurRadius(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 176, c_float(nValue))
    blurRadius = property(get_blurRadius, set_blurRadius)
    def get_blurPasses(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 177)
        if(retValue): return retValue.contents.value
        else: return None
    def set_blurPasses(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 177, c_float(nValue))
    blurPasses = property(get_blurPasses, set_blurPasses)
    def get_emissiveMult(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 178)
        if(retValue): return retValue.contents.value
        else: return None
    def set_emissiveMult(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 178, c_float(nValue))
    emissiveMult = property(get_emissiveMult, set_emissiveMult)
    def get_targetLum(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 179)
        if(retValue): return retValue.contents.value
        else: return None
    def set_targetLum(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 179, c_float(nValue))
    targetLum = property(get_targetLum, set_targetLum)
    def get_upperLumClamp(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 180)
        if(retValue): return retValue.contents.value
        else: return None
    def set_upperLumClamp(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 180, c_float(nValue))
    upperLumClamp = property(get_upperLumClamp, set_upperLumClamp)
    def get_brightScale(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 181)
        if(retValue): return retValue.contents.value
        else: return None
    def set_brightScale(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 181, c_float(nValue))
    brightScale = property(get_brightScale, set_brightScale)
    def get_brightClamp(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 182)
        if(retValue): return retValue.contents.value
        else: return None
    def set_brightClamp(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 182, c_float(nValue))
    brightClamp = property(get_brightClamp, set_brightClamp)
    def get_lumRampNoTex(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 183)
        if(retValue): return retValue.contents.value
        else: return None
    def set_lumRampNoTex(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 183, c_float(nValue))
    lumRampNoTex = property(get_lumRampNoTex, set_lumRampNoTex)
    def get_lumRampMin(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 184)
        if(retValue): return retValue.contents.value
        else: return None
    def set_lumRampMin(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 184, c_float(nValue))
    lumRampMin = property(get_lumRampMin, set_lumRampMin)
    def get_lumRampMax(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 185)
        if(retValue): return retValue.contents.value
        else: return None
    def set_lumRampMax(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 185, c_float(nValue))
    lumRampMax = property(get_lumRampMax, set_lumRampMax)
    def get_sunlightDimmer(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 186)
        if(retValue): return retValue.contents.value
        else: return None
    def set_sunlightDimmer(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 186, c_float(nValue))
    sunlightDimmer = property(get_sunlightDimmer, set_sunlightDimmer)
    def get_grassDimmer(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 187)
        if(retValue): return retValue.contents.value
        else: return None
    def set_grassDimmer(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 187, c_float(nValue))
    grassDimmer = property(get_grassDimmer, set_grassDimmer)
    def get_treeDimmer(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 188)
        if(retValue): return retValue.contents.value
        else: return None
    def set_treeDimmer(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 188, c_float(nValue))
    treeDimmer = property(get_treeDimmer, set_treeDimmer)
    def get_windSpeed(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 189)
        if(retValue): return retValue.contents.value
        else: return None
    def set_windSpeed(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 189, c_ubyte(nValue))
    windSpeed = property(get_windSpeed, set_windSpeed)
    def get_lowerCloudSpeed(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 190)
        if(retValue): return retValue.contents.value
        else: return None
    def set_lowerCloudSpeed(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 190, c_ubyte(nValue))
    lowerCloudSpeed = property(get_lowerCloudSpeed, set_lowerCloudSpeed)
    def get_upperCloudSpeed(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 191)
        if(retValue): return retValue.contents.value
        else: return None
    def set_upperCloudSpeed(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 191, c_ubyte(nValue))
    upperCloudSpeed = property(get_upperCloudSpeed, set_upperCloudSpeed)
    def get_transDelta(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 192)
        if(retValue): return retValue.contents.value
        else: return None
    def set_transDelta(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 192, c_ubyte(nValue))
    transDelta = property(get_transDelta, set_transDelta)
    def get_sunGlare(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 193)
        if(retValue): return retValue.contents.value
        else: return None
    def set_sunGlare(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 193, c_ubyte(nValue))
    sunGlare = property(get_sunGlare, set_sunGlare)
    def get_sunDamage(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 194)
        if(retValue): return retValue.contents.value
        else: return None
    def set_sunDamage(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 194, c_ubyte(nValue))
    sunDamage = property(get_sunDamage, set_sunDamage)
    def get_rainFadeIn(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 195)
        if(retValue): return retValue.contents.value
        else: return None
    def set_rainFadeIn(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 195, c_ubyte(nValue))
    rainFadeIn = property(get_rainFadeIn, set_rainFadeIn)
    def get_rainFadeOut(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 196)
        if(retValue): return retValue.contents.value
        else: return None
    def set_rainFadeOut(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 196, c_ubyte(nValue))
    rainFadeOut = property(get_rainFadeOut, set_rainFadeOut)
    def get_boltFadeIn(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 197)
        if(retValue): return retValue.contents.value
        else: return None
    def set_boltFadeIn(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 197, c_ubyte(nValue))
    boltFadeIn = property(get_boltFadeIn, set_boltFadeIn)
    def get_boltFadeOut(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 198)
        if(retValue): return retValue.contents.value
        else: return None
    def set_boltFadeOut(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 198, c_ubyte(nValue))
    boltFadeOut = property(get_boltFadeOut, set_boltFadeOut)
    def get_boltFrequency(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 199)
        if(retValue): return retValue.contents.value
        else: return None
    def set_boltFrequency(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 199, c_ubyte(nValue))
    boltFrequency = property(get_boltFrequency, set_boltFrequency)
    def get_weatherType(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 200)
        if(retValue): return retValue.contents.value
        else: return None
    def set_weatherType(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 200, c_ubyte(nValue))
    weatherType = property(get_weatherType, set_weatherType)
    def get_boltRed(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 201)
        if(retValue): return retValue.contents.value
        else: return None
    def set_boltRed(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 201, c_ubyte(nValue))
    boltRed = property(get_boltRed, set_boltRed)
    def get_boltGreen(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 202)
        if(retValue): return retValue.contents.value
        else: return None
    def set_boltGreen(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 202, c_ubyte(nValue))
    boltGreen = property(get_boltGreen, set_boltGreen)
    def get_boltBlue(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 203)
        if(retValue): return retValue.contents.value
        else: return None
    def set_boltBlue(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 203, c_ubyte(nValue))
    boltBlue = property(get_boltBlue, set_boltBlue)
    def get_sounds(self):
        numRecords = CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 204)
        if(numRecords > 0): return [self.Sound(self._CollectionIndex, self._ModName, self._recordID, x) for x in range(0, numRecords)]
        else: return []
    def set_sounds(self, nSounds):
        diffLength = len(nSounds) - CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 204)
        nValues = [(nSound.sound, nSound.type) for nSound in nSounds]
        while(diffLength < 0):
            CBash.DeleteFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 204)
            diffLength += 1
        while(diffLength > 0):
            CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 204)
            diffLength -= 1
        for oSound, nValue in zip(self.sounds, nValues):
            oSound.sound, oSound.type = nValue
    sounds = property(get_sounds, set_sounds)
class CLMTRecord(BaseRecord):
    def CopyAsOverride(self, targetMod):
        FID = CBash.CopyCLMTRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(True))
        if(FID): return CLMTRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def CopyAsNew(self, targetMod):
        FID = CBash.CopyCLMTRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(False))
        if(FID): return CLMTRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    class Weather(object):
        def __init__(self, CollectionIndex, ModName, recordID, listIndex):
            self._CollectionIndex = CollectionIndex
            self._ModName = ModName
            self._recordID = recordID
            self._listIndex = listIndex
        def get_weather(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, 6, self._listIndex, 1).contents.value
        def set_weather(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, 6, self._listIndex, 1, nValue)
        weather = property(get_weather, set_weather)
        def get_chance(self):
            CBash.ReadFIDListField.restype = POINTER(c_int)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, 6, self._listIndex, 2).contents.value
        def set_chance(self, nValue):
            CBash.SetFIDListFieldI(self._CollectionIndex, self._ModName, self._recordID, 6, self._listIndex, 2, nValue)
        chance = property(get_chance, set_chance)
    def newWeathersElement(self):
        listIndex = CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 6)
        if(listIndex == -1): return None
        return self.Weather(self._CollectionIndex, self._ModName, self._recordID, listIndex)

    def get_weathers(self):
        numRecords = CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 6)
        if(numRecords > 0): return [self.Weather(self._CollectionIndex, self._ModName, self._recordID, x) for x in range(0, numRecords)]
        else: return []
    def set_weathers(self, nWeathers):
        diffLength = len(nWeathers) - CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 6)
        nValues = [(nWeather.weather, nWeather.chance) for nWeather in nWeathers]
        while(diffLength < 0):
            CBash.DeleteFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 6)
            diffLength += 1
        while(diffLength > 0):
            CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 6)
            diffLength -= 1
        for oWeather, nValue in zip(self.weathers, nValues):
            oWeather.weather, oWeather.chance = nValue
    weathers = property(get_weathers, set_weathers)
    def get_sunPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 7)
    def set_sunPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 7, nValue)
    sunPath = property(get_sunPath, set_sunPath)
    def get_glarePath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 8)
    def set_glarePath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 8, nValue)
    glarePath = property(get_glarePath, set_glarePath)
    def get_modPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 9)
    def set_modPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 9, nValue)
    modPath = property(get_modPath, set_modPath)
    def get_modb(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 10)
        if(retValue): return retValue.contents.value
        else: return None
    def set_modb(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 10, c_float(nValue))
    modb = property(get_modb, set_modb)
    def get_modt_p(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 11)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 11, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_modt_p(self, nValue):
        length = len(nValue)
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 11, struct.pack('B' * length, *nValue), length)
    modt_p = property(get_modt_p, set_modt_p)
    def get_riseBegin(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 12)
        if(retValue): return retValue.contents.value
        else: return None
    def set_riseBegin(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 12, c_ubyte(nValue))
    riseBegin = property(get_riseBegin, set_riseBegin)
    def get_riseEnd(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 13)
        if(retValue): return retValue.contents.value
        else: return None
    def set_riseEnd(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 13, c_ubyte(nValue))
    riseEnd = property(get_riseEnd, set_riseEnd)
    def get_setBegin(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 14)
        if(retValue): return retValue.contents.value
        else: return None
    def set_setBegin(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 14, c_ubyte(nValue))
    setBegin = property(get_setBegin, set_setBegin)
    def get_setEnd(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 15)
        if(retValue): return retValue.contents.value
        else: return None
    def set_setEnd(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 15, c_ubyte(nValue))
    setEnd = property(get_setEnd, set_setEnd)
    def get_volatility(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 16)
        if(retValue): return retValue.contents.value
        else: return None
    def set_volatility(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 16, c_ubyte(nValue))
    volatility = property(get_volatility, set_volatility)
    def get_phaseLength(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 17)
        if(retValue): return retValue.contents.value
        else: return None
    def set_phaseLength(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 17, c_ubyte(nValue))
    phaseLength = property(get_phaseLength, set_phaseLength)
class REGNRecord(BaseRecord):
    def CopyAsOverride(self, targetMod):
        FID = CBash.CopyREGNRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(True))
        if(FID): return REGNRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def CopyAsNew(self, targetMod):
        FID = CBash.CopyREGNRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(False))
        if(FID): return REGNRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    class Area(object):
        class Points(object):
            def __init__(self, CollectionIndex, ModName, recordID, listIndex, listX2Index):
                self._CollectionIndex = CollectionIndex
                self._ModName = ModName
                self._recordID = recordID
                self._listIndex = listIndex
                self._listX2Index = listX2Index
            def get_posX(self):
                CBash.ReadFIDListX2Field.restype = POINTER(c_float)
                return CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2, self._listX2Index, 1).contents.value
            def set_posX(self, nValue):
                CBash.SetFIDListX2FieldF(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2, self._listX2Index, 1, c_float(nValue))
            posX = property(get_posX, set_posX)
            def get_posY(self):
                CBash.ReadFIDListX2Field.restype = POINTER(c_float)
                return CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2, self._listX2Index, 2).contents.value
            def set_posY(self, nValue):
                CBash.SetFIDListX2FieldF(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2, self._listX2Index, 2, c_float(nValue))
            posY = property(get_posY, set_posY)
            
        def __init__(self, CollectionIndex, ModName, recordID, listIndex):
            self._CollectionIndex = CollectionIndex
            self._ModName = ModName
            self._recordID = recordID
            self._listIndex = listIndex
        def newPointsElement(self):
            listX2Index = CBash.CreateFIDListX2Element(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2)
            if(listX2Index == -1): return None
            return self.Points(self._CollectionIndex, self._ModName, self._recordID, self._listIndex, listX2Index)
        def get_edgeFalloff(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 1).contents.value
        def set_edgeFalloff(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 1, nValue)
        edgeFalloff = property(get_edgeFalloff, set_edgeFalloff)
        def get_points(self):
            numRecords = CBash.GetFIDListX2Size(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2)
            if(numRecords > 0): return [self.Points(self._CollectionIndex, self._ModName, self._recordID, self._listIndex, x) for x in range(0, numRecords)]
            else: return []
        def set_points(self, nPoints):
            diffLength = len(nPoints) - CBash.GetFIDListX2Size(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2)
            nValues = [(nPoint.posX, nPoint.posY) for nPoint in nPoints]
            while(diffLength < 0):
                CBash.DeleteFIDListX2Element(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2)
                diffLength += 1
            while(diffLength > 0):
                CBash.CreateFIDListX2Element(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2)
                diffLength -= 1
            for oPoint, nValue in zip(self.points, nValues):
                oPoint.posX, oPoint.posY = nValue
        points = property(get_points, set_points)
    class Entry(object):
        class Object(object):
            def __init__(self, CollectionIndex, ModName, recordID, listIndex, listX2Index):
                self._CollectionIndex = CollectionIndex
                self._ModName = ModName
                self._recordID = recordID
                self._listIndex = listIndex
                self._listX2Index = listX2Index
            def get_objectId(self):
                CBash.ReadFIDListX2Field.restype = POINTER(c_uint)
                retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5, self._listX2Index, 1)
                if(retValue): return retValue.contents.value
                else: return None
            def set_objectId(self, nValue):
                CBash.SetFIDListX2FieldUI(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5, self._listX2Index, 1, nValue)
            objectId = property(get_objectId, set_objectId)
            def get_parentIndex(self):
                CBash.ReadFIDListX2Field.restype = POINTER(c_ushort)
                retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5, self._listX2Index, 2)
                if(retValue): return retValue.contents.value
                else: return None
            def set_parentIndex(self, nValue):
                CBash.SetFIDListX2FieldUS(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5, self._listX2Index, 2, c_ushort(nValue))
            parentIndex = property(get_parentIndex, set_parentIndex)
            def get_unused1(self):
                numRecords = CBash.GetFIDListX2ArraySize(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5, self._listX2Index, 3)
                if(numRecords > 0):
                    cRecords = POINTER(c_ubyte * numRecords)()
                    CBash.GetFIDListX2Array(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5, self._listX2Index, 3, byref(cRecords))
                    return [cRecords.contents[x] for x in range(0, numRecords)]
                else: return []
            def set_unused1(self, nValue):
                CBash.SetFIDListX2FieldR(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5, self._listX2Index, 3, struct.pack('2B', *nValue), 2)
            unused1 = property(get_unused1, set_unused1)
            def get_density(self):
                CBash.ReadFIDListX2Field.restype = POINTER(c_float)
                retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5, self._listX2Index, 4)
                if(retValue): return retValue.contents.value
                else: return None
            def set_density(self, nValue):
                CBash.SetFIDListX2FieldF(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5, self._listX2Index, 4, c_float(nValue))
            density = property(get_density, set_density)
            def get_clustering(self):
                CBash.ReadFIDListX2Field.restype = POINTER(c_ubyte)
                retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5, self._listX2Index, 5)
                if(retValue): return retValue.contents.value
                else: return None
            def set_clustering(self, nValue):
                CBash.SetFIDListX2FieldUC(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5, self._listX2Index, 5, c_ubyte(nValue))
            clustering = property(get_clustering, set_clustering)
            def get_minSlope(self):
                CBash.ReadFIDListX2Field.restype = POINTER(c_ubyte)
                retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5, self._listX2Index, 6)
                if(retValue): return retValue.contents.value
                else: return None
            def set_minSlope(self, nValue):
                CBash.SetFIDListX2FieldUC(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5, self._listX2Index, 6, c_ubyte(nValue))
            minSlope = property(get_minSlope, set_minSlope)
            def get_maxSlope(self):
                CBash.ReadFIDListX2Field.restype = POINTER(c_ubyte)
                retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5, self._listX2Index, 7)
                if(retValue): return retValue.contents.value
                else: return None
            def set_maxSlope(self, nValue):
                CBash.SetFIDListX2FieldUC(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5, self._listX2Index, 7, c_ubyte(nValue))
            maxSlope = property(get_maxSlope, set_maxSlope)
            def get_flags(self):
                CBash.ReadFIDListX2Field.restype = POINTER(c_ubyte)
                retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5, self._listX2Index, 8)
                if(retValue): return retValue.contents.value
                else: return None
            def set_flags(self, nValue):
                CBash.SetFIDListX2FieldUC(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5, self._listX2Index, 8, c_ubyte(nValue))
            flags = property(get_flags, set_flags)
            def get_radiusWRTParent(self):
                CBash.ReadFIDListX2Field.restype = POINTER(c_ushort)
                retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5, self._listX2Index, 9)
                if(retValue): return retValue.contents.value
                else: return None
            def set_radiusWRTParent(self, nValue):
                CBash.SetFIDListX2FieldUS(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5, self._listX2Index, 9, c_ushort(nValue))
            radiusWRTParent = property(get_radiusWRTParent, set_radiusWRTParent)
            def get_radius(self):
                CBash.ReadFIDListX2Field.restype = POINTER(c_ushort)
                retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5, self._listX2Index, 10)
                if(retValue): return retValue.contents.value
                else: return None
            def set_radius(self, nValue):
                CBash.SetFIDListX2FieldUS(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5, self._listX2Index, 10, c_ushort(nValue))
            radius = property(get_radius, set_radius)
            def get_unk1(self):
                numRecords = CBash.GetFIDListX2ArraySize(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5, self._listX2Index, 11)
                if(numRecords > 0):
                    cRecords = POINTER(c_ubyte * numRecords)()
                    CBash.GetFIDListX2Array(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5, self._listX2Index, 11, byref(cRecords))
                    return [cRecords.contents[x] for x in range(0, numRecords)]
                else: return []
            def set_unk1(self, nValue):
                CBash.SetFIDListX2FieldR(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5, self._listX2Index, 11, struct.pack('4B', *nValue), 4)
            unk1 = property(get_unk1, set_unk1)
            def get_maxHeight(self):
                CBash.ReadFIDListX2Field.restype = POINTER(c_float)
                retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5, self._listX2Index, 12)
                if(retValue): return retValue.contents.value
                else: return None
            def set_maxHeight(self, nValue):
                CBash.SetFIDListX2FieldF(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5, self._listX2Index, 12, c_float(nValue))
            maxHeight = property(get_maxHeight, set_maxHeight)
            def get_sink(self):
                CBash.ReadFIDListX2Field.restype = POINTER(c_float)
                retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5, self._listX2Index, 13)
                if(retValue): return retValue.contents.value
                else: return None
            def set_sink(self, nValue):
                CBash.SetFIDListX2FieldF(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5, self._listX2Index, 13, c_float(nValue))
            sink = property(get_sink, set_sink)
            def get_sinkVar(self):
                CBash.ReadFIDListX2Field.restype = POINTER(c_float)
                retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5, self._listX2Index, 14)
                if(retValue): return retValue.contents.value
                else: return None
            def set_sinkVar(self, nValue):
                CBash.SetFIDListX2FieldF(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5, self._listX2Index, 14, c_float(nValue))
            sinkVar = property(get_sinkVar, set_sinkVar)
            def get_sizeVar(self):
                CBash.ReadFIDListX2Field.restype = POINTER(c_float)
                retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5, self._listX2Index, 15)
                if(retValue): return retValue.contents.value
                else: return None
            def set_sizeVar(self, nValue):
                CBash.SetFIDListX2FieldF(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5, self._listX2Index, 15, c_float(nValue))
            sizeVar = property(get_sizeVar, set_sizeVar)
            def get_angleVarX(self):
                CBash.ReadFIDListX2Field.restype = POINTER(c_ushort)
                retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5, self._listX2Index, 16)
                if(retValue): return retValue.contents.value
                else: return None
            def set_angleVarX(self, nValue):
                CBash.SetFIDListX2FieldUS(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5, self._listX2Index, 16, c_ushort(nValue))
            angleVarX = property(get_angleVarX, set_angleVarX)
            def get_angleVarY(self):
                CBash.ReadFIDListX2Field.restype = POINTER(c_ushort)
                retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5, self._listX2Index, 17)
                if(retValue): return retValue.contents.value
                else: return None
            def set_angleVarY(self, nValue):
                CBash.SetFIDListX2FieldUS(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5, self._listX2Index, 17, c_ushort(nValue))
            angleVarY = property(get_angleVarY, set_angleVarY)
            def get_angleVarZ(self):
                CBash.ReadFIDListX2Field.restype = POINTER(c_ushort)
                retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5, self._listX2Index, 18)
                if(retValue): return retValue.contents.value
                else: return None
            def set_angleVarZ(self, nValue):
                CBash.SetFIDListX2FieldUS(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5, self._listX2Index, 18, c_ushort(nValue))
            angleVarZ = property(get_angleVarZ, set_angleVarZ)
            def get_unused2(self):
                numRecords = CBash.GetFIDListX2ArraySize(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5, self._listX2Index, 19)
                if(numRecords > 0):
                    cRecords = POINTER(c_ubyte * numRecords)()
                    CBash.GetFIDListX2Array(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5, self._listX2Index, 19, byref(cRecords))
                    return [cRecords.contents[x] for x in range(0, numRecords)]
                else: return []
            def set_unused2(self, nValue):
                CBash.SetFIDListX2FieldR(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5, self._listX2Index, 19, struct.pack('2B', *nValue), 2)
            unused2 = property(get_unused2, set_unused2)
            def get_unk2(self):
                numRecords = CBash.GetFIDListX2ArraySize(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5, self._listX2Index, 20)
                if(numRecords > 0):
                    cRecords = POINTER(c_ubyte * numRecords)()
                    CBash.GetFIDListX2Array(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5, self._listX2Index, 20, byref(cRecords))
                    return [cRecords.contents[x] for x in range(0, numRecords)]
                else: return []
            def set_unk2(self, nValue):
                CBash.SetFIDListX2FieldR(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5, self._listX2Index, 20, struct.pack('4B', *nValue), 4)
            unk2 = property(get_unk2, set_unk2)
        class Grass(object):
            def __init__(self, CollectionIndex, ModName, recordID, listIndex, listX2Index):
                self._CollectionIndex = CollectionIndex
                self._ModName = ModName
                self._recordID = recordID
                self._listIndex = listIndex
                self._listX2Index = listX2Index
            def get_grass(self):
                CBash.ReadFIDListX2Field.restype = POINTER(c_uint)
                retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 8, self._listX2Index, 1)
                if(retValue): return retValue.contents.value
                else: return None
            def set_grass(self, nValue):
                CBash.SetFIDListX2FieldUI(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 8, self._listX2Index, 1, nValue)
            grass = property(get_grass, set_grass)
            def get_unk1(self):
                numRecords = CBash.GetFIDListX2ArraySize(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 8, self._listX2Index, 2)
                if(numRecords > 0):
                    cRecords = POINTER(c_ubyte * numRecords)()
                    CBash.GetFIDListX2Array(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 8, self._listX2Index, 2, byref(cRecords))
                    return [cRecords.contents[x] for x in range(0, numRecords)]
                else: return []
            def set_unk1(self, nValue):
                CBash.SetFIDListX2FieldR(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 8, self._listX2Index, 2, struct.pack('4B', *nValue), 4)
            unk1 = property(get_unk1, set_unk1)
        class Sound(object):
            def __init__(self, CollectionIndex, ModName, recordID, listIndex, listX2Index):
                self._CollectionIndex = CollectionIndex
                self._ModName = ModName
                self._recordID = recordID
                self._listIndex = listIndex
                self._listX2Index = listX2Index
            def get_sound(self):
                CBash.ReadFIDListX2Field.restype = POINTER(c_uint)
                retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 10, self._listX2Index, 1)
                if(retValue): return retValue.contents.value
                else: return None
            def set_sound(self, nValue):
                CBash.SetFIDListX2FieldUI(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 10, self._listX2Index, 1, nValue)
            sound = property(get_sound, set_sound)
            def get_flags(self):
                CBash.ReadFIDListX2Field.restype = POINTER(c_uint)
                retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 10, self._listX2Index, 2)
                if(retValue): return retValue.contents.value
                else: return None
            def set_flags(self, nValue):
                CBash.SetFIDListX2FieldUI(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 10, self._listX2Index, 2, nValue)
            flags = property(get_flags, set_flags)
            def get_chance(self):
                CBash.ReadFIDListX2Field.restype = POINTER(c_uint)
                retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 10, self._listX2Index, 3)
                if(retValue): return retValue.contents.value
                else: return None
            def set_chance(self, nValue):
                CBash.SetFIDListX2FieldUI(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 10, self._listX2Index, 3, nValue)
            chance = property(get_chance, set_chance)
        class Weather(object):
            def __init__(self, CollectionIndex, ModName, recordID, listIndex, listX2Index):
                self._CollectionIndex = CollectionIndex
                self._ModName = ModName
                self._recordID = recordID
                self._listIndex = listIndex
                self._listX2Index = listX2Index
            def get_weather(self):
                CBash.ReadFIDListX2Field.restype = POINTER(c_uint)
                retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 11, self._listX2Index, 1)
                if(retValue): return retValue.contents.value
                else: return None
            def set_weather(self, nValue):
                CBash.SetFIDListX2FieldUI(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 11, self._listX2Index, 1, nValue)
            weather = property(get_weather, set_weather)
            def get_chance(self):
                CBash.ReadFIDListX2Field.restype = POINTER(c_uint)
                retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 11, self._listX2Index, 2)
                if(retValue): return retValue.contents.value
                else: return None
            def set_chance(self, nValue):
                CBash.SetFIDListX2FieldUI(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 11, self._listX2Index, 2, nValue)
            chance = property(get_chance, set_chance)

        def __init__(self, CollectionIndex, ModName, recordID, listIndex):
            self._CollectionIndex = CollectionIndex
            self._ModName = ModName
            self._recordID = recordID
            self._listIndex = listIndex
        def newObjectsElement(self):
            listX2Index = CBash.CreateFIDListX2Element(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5)
            if(listX2Index == -1): return None
            return self.Object(self._CollectionIndex, self._ModName, self._recordID, self._listIndex, listX2Index)
        def newGrassesElement(self):
            listX2Index = CBash.CreateFIDListX2Element(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 8)
            if(listX2Index == -1): return None
            return self.Grass(self._CollectionIndex, self._ModName, self._recordID, self._listIndex, listX2Index)
        def newSoundsElement(self):
            listX2Index = CBash.CreateFIDListX2Element(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 10)
            if(listX2Index == -1): return None
            return self.Sound(self._CollectionIndex, self._ModName, self._recordID, self._listIndex, listX2Index)
        def newWeathersElement(self):
            listX2Index = CBash.CreateFIDListX2Element(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 11)
            if(listX2Index == -1): return None
            return self.Weather(self._CollectionIndex, self._ModName, self._recordID, self._listIndex, listX2Index)

        def get_entryType(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            retValue = CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 1)
            if(retValue): return retValue.contents.value
            else: return None
        def set_entryType(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 1, nValue)
        entryType = property(get_entryType, set_entryType)
        def get_flags(self):
            CBash.ReadFIDListField.restype = POINTER(c_ubyte)
            retValue = CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 2)
            if(retValue): return retValue.contents.value
            else: return None
        def set_flags(self, nValue):
            CBash.SetFIDListFieldUC(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 2, c_ubyte(nValue))
        flags = property(get_flags, set_flags)
        def get_priority(self):
            CBash.ReadFIDListField.restype = POINTER(c_ubyte)
            retValue = CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 3)
            if(retValue): return retValue.contents.value
            else: return None
        def set_priority(self, nValue):
            CBash.SetFIDListFieldUC(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 3, c_ubyte(nValue))
        priority = property(get_priority, set_priority)
        def get_unused1(self):
            numRecords = CBash.GetFIDListArraySize(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 4)
            if(numRecords > 0):
                cRecords = POINTER(c_ubyte * numRecords)()
                CBash.GetFIDListArray(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 4, byref(cRecords))
                return [cRecords.contents[x] for x in range(0, numRecords)]
            else: return []
        def set_unused1(self, nValue):
            CBash.SetFIDListFieldR(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 4, struct.pack('2B', *nValue), 2)
        unused1 = property(get_unused1, set_unused1)
        def get_objects(self):
            numRecords = CBash.GetFIDListX2Size(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5)
            if(numRecords > 0): return [self.Object(self._CollectionIndex, self._ModName, self._recordID, self._listIndex, x) for x in range(0, numRecords)]
            else: return []
        def set_objects(self, nObjects):
            diffLength = len(nObjects) - CBash.GetFIDListX2Size(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5)
            nValues = [(nObject.objectId, nObject.parentIndex, nObject.unused1, nObject.density, nObject.clustering, 
                        nObject.minSlope, nObject.maxSlope, nObject.flags, nObject.radiusWRTParent, nObject.radius, 
                        nObject.unk1, nObject.maxHeight, nObject.sink, nObject.sinkVar, nObject.sizeVar, 
                        nObject.angleVarX, nObject.angleVarY, nObject.angleVarZ, nObject.unused2, nObject.unk2) for nObject in nObjects]
            while(diffLength < 0):
                CBash.DeleteFIDListX2Element(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5)
                diffLength += 1
            while(diffLength > 0):
                CBash.CreateFIDListX2Element(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5)
                diffLength -= 1
            for oObject, nValue in zip(self.objects, nValues):
                oObject.objectId, oObject.parentIndex, oObject.unused1, oObject.density, oObject.clustering, oObject.minSlope, oObject.maxSlope, oObject.flags, oObject.radiusWRTParent, oObject.radius, oObject.unk1, oObject.maxHeight, oObject.sink, oObject.sinkVar, oObject.sizeVar,oObject.angleVarX, oObject.angleVarY, oObject.angleVarZ, oObject.unused2, oObject.unk2 = nValue
        objects = property(get_objects, set_objects)
        def get_mapName(self):
            CBash.ReadFIDListField.restype = c_char_p
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 6)
        def set_mapName(self, nValue):
            CBash.SetFIDListFieldStr(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 6, nValue)
        mapName = property(get_mapName, set_mapName)
        def get_iconPath(self):
            CBash.ReadFIDListField.restype = c_char_p
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 7)
        def set_iconPath(self, nValue):
            CBash.SetFIDListFieldStr(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 7, nValue)
        iconPath = property(get_iconPath, set_iconPath)
        def get_grasses(self):
            numRecords = CBash.GetFIDListX2Size(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 8)
            if(numRecords > 0): return [self.Grass(self._CollectionIndex, self._ModName, self._recordID, self._listIndex, x) for x in range(0, numRecords)]
            else: return []
        def set_grasses(self, nGrasses):
            diffLength = len(nGrasses) - CBash.GetFIDListX2Size(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 8)
            nValues = [(nGrass.grass, nGrass.unk1) for nGrass in nGrasses]
            while(diffLength < 0):
                CBash.DeleteFIDListX2Element(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 8)
                diffLength += 1
            while(diffLength > 0):
                CBash.CreateFIDListX2Element(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 8)
                diffLength -= 1
            for oGrass, nValue in zip(self.grasses, nValues):
                oGrass.grass, oGrass.unk1 = nValue
        grasses = property(get_grasses, set_grasses)
        def get_musicType(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            retValue = CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 9)
            if(retValue): return retValue.contents.value
            else: return None
        def set_musicType(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 9, nValue)
        musicType = property(get_musicType, set_musicType)
        def get_sounds(self):
            numRecords = CBash.GetFIDListX2Size(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 10)
            if(numRecords > 0): return [self.Sound(self._CollectionIndex, self._ModName, self._recordID, self._listIndex, x) for x in range(0, numRecords)]
            else: return []
        def set_sounds(self, nSounds):
            diffLength = len(nSounds) - CBash.GetFIDListX2Size(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 10)
            nValues = [(nSound.sound, nSound.flags, nSound.chance) for nSound in nSounds]
            while(diffLength < 0):
                CBash.DeleteFIDListX2Element(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 10)
                diffLength += 1
            while(diffLength > 0):
                CBash.CreateFIDListX2Element(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 10)
                diffLength -= 1
            for oSound, nValue in zip(self.sounds, nValues):
                oSound.sound, oSound.flags, oSound.chance = nValue
        sounds = property(get_sounds, set_sounds)
        def get_weathers(self):
            numRecords = CBash.GetFIDListX2Size(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 11)
            if(numRecords > 0): return [self.Weather(self._CollectionIndex, self._ModName, self._recordID, self._listIndex, x) for x in range(0, numRecords)]
            else: return []
        def set_weathers(self, nWeathers):
            diffLength = len(nWeathers) - CBash.GetFIDListX2Size(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 11)
            nValues = [(nWeather.weather, nWeather.chance) for nWeather in nWeathers]
            while(diffLength < 0):
                CBash.DeleteFIDListX2Element(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 11)
                diffLength += 1
            while(diffLength > 0):
                CBash.CreateFIDListX2Element(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 11)
                diffLength -= 1
            for oWeather, nValue in zip(self.weathers, nValues):
                oWeather.weather, oWeather.chance = nValue
        weathers = property(get_weathers, set_weathers)
    def newAreasElement(self):
        listIndex = CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 12)
        if(listIndex == -1): return None
        return self.Area(self._CollectionIndex, self._ModName, self._recordID, listIndex)
    def newEntriesElement(self):
        listIndex = CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 13)
        if(listIndex == -1): return None
        return self.Entry(self._CollectionIndex, self._ModName, self._recordID, listIndex)

    def get_iconPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 6)
    def set_iconPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 6, nValue)
    iconPath = property(get_iconPath, set_iconPath)
    def get_mapRed(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 7)
        if(retValue): return retValue.contents.value
        else: return None
    def set_mapRed(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 7, c_ubyte(nValue))
    mapRed = property(get_mapRed, set_mapRed)
    def get_mapGreen(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 8)
        if(retValue): return retValue.contents.value
        else: return None
    def set_mapGreen(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 8, c_ubyte(nValue))
    mapGreen = property(get_mapGreen, set_mapGreen)
    def get_mapBlue(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 9)
        if(retValue): return retValue.contents.value
        else: return None
    def set_mapBlue(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 9, c_ubyte(nValue))
    mapBlue = property(get_mapBlue, set_mapBlue)
    def get_unused1(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 10)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 10, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_unused1(self, nValue):
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 10, struct.pack('B', *nValue), 1)
    unused1 = property(get_unused1, set_unused1)
    def get_worldspace(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 11)
        if(retValue): return retValue.contents.value
        else: return None
    def set_worldspace(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 11, nValue)
    worldspace = property(get_worldspace, set_worldspace)
    def get_areas(self):
        numRecords = CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 12)
        if(numRecords > 0): return [self.Area(self._CollectionIndex, self._ModName, self._recordID, x) for x in range(0, numRecords)]
        else: return []
    def set_areas(self, nAreas):
        diffLength = len(nAreas) - CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 12)
        nValues = [(nArea.edgeFalloff, [(nPoint.posX, nPoint.posY) for nPoint in nArea.points]) for nArea in nAreas]
        while(diffLength < 0):
            CBash.DeleteFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 12)
            diffLength += 1
        while(diffLength > 0):
            CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 12)
            diffLength -= 1
        for oArea, nValue in zip(self.areas, nValues):
            oArea.edgeFalloff = nValue[0]
            diffLength = len(nValue[1]) - CBash.GetFIDListX2Size(self._CollectionIndex, self._ModName, self._recordID, 12, oArea._listIndex, 2)
            while(diffLength < 0):
                CBash.DeleteFIDListX2Element(self._CollectionIndex, self._ModName, self._recordID, 12, oArea._listIndex, 2)
                diffLength += 1
            while(diffLength > 0):
                CBash.CreateFIDListX2Element(self._CollectionIndex, self._ModName, self._recordID, 12, oArea._listIndex, 2)
                diffLength -= 1
            for oPoint, posValue in zip(oArea.points, nValue[1]):
                oPoint.posX, oPoint.posY = posValue
    areas = property(get_areas, set_areas)
    def get_entries(self):
        numRecords = CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 13)
        if(numRecords > 0): return [self.Entry(self._CollectionIndex, self._ModName, self._recordID, x) for x in range(0, numRecords)]
        else: return []
    def set_entries(self, nEntries):
        diffLength = len(nEntries) - CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 13)
        nValues = [(nEntry.entryType, nEntry.flags, nEntry.priority, nEntry.unused1,
                    [(nObject.objectId, nObject.subField, nObject.unused1, nObject.density, 
                      nObject.clustering, nObject.minSlope, nObject.maxSlope, nObject.flags, 
                      nObject.radiusWRTParent, nObject.radius, nObject.unk1, nObject.maxHeight,  
                      nObject.sink, nObject.sinkVar, nObject.sizeVar, nObject.angleVarX, 
                      nObject.angleVarY, nObject.angleVarZ, nObject.unused2, nObject.unk2) for nObject in nEntry.objects],
                    nEntry.mapName, nEntry.iconPath,
                    [(nGrass.grass, nGrass.unk1) for nGrass in nEntry.grasses],
                    nEntry.musicType,
                    [(nSound.sound, nSound.flags, nSound.chance) for nSound in nEntry.sounds],
                    [(nWeather.weather, nWeather.chance) for nWeather in nEntry.weathers]) for nEntry in nEntries]
        while(diffLength < 0):
            CBash.DeleteFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 13)
            diffLength += 1
        while(diffLength > 0):
            CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 13)
            diffLength -= 1
        for oEntry, nValue in zip(self.entries, nValues):
            nEntry.entryType = nValue[0]
            nEntry.flags = nValue[1]
            nEntry.priority = nValue[2]
            nEntry.unused1 = nValue[3]
            diffLength = len(nValue[4]) - CBash.GetFIDListX2Size(self._CollectionIndex, self._ModName, self._recordID, 13, oEntry._listIndex, 5)
            while(diffLength < 0):
                CBash.DeleteFIDListX2Element(self._CollectionIndex, self._ModName, self._recordID, 13, oEntry._listIndex, 5)
                diffLength += 1
            while(diffLength > 0):
                CBash.CreateFIDListX2Element(self._CollectionIndex, self._ModName, self._recordID, 13, oEntry._listIndex, 5)
                diffLength -= 1
            for oObject, objValue in zip(oEntry.objects, nValue[4]):
                oObject.objectId, oObject.subField, oObject.unused1, oObject.density, 
                oObject.clustering, oObject.minSlope, oObject.maxSlope, oObject.flags, 
                oObject.radiusWRTParent, oObject.radius, oObject.unk1, oObject.maxHeight,  
                oObject.sink, oObject.sinkVar, oObject.sizeVar, oObject.angleVarX, 
                oObject.angleVarY, oObject.angleVarZ, oObject.unused2, oObject.unk2 = objValue
            nEntry.mapName = nValue[5]
            nEntry.iconPath = nValue[6]
            diffLength = len(nValue[7]) - CBash.GetFIDListX2Size(self._CollectionIndex, self._ModName, self._recordID, 13, oEntry._listIndex, 8)
            while(diffLength < 0):
                CBash.DeleteFIDListX2Element(self._CollectionIndex, self._ModName, self._recordID, 13, oEntry._listIndex, 8)
                diffLength += 1
            while(diffLength > 0):
                CBash.CreateFIDListX2Element(self._CollectionIndex, self._ModName, self._recordID, 13, oEntry._listIndex, 8)
                diffLength -= 1
            for oGrass, grassValue in zip(oEntry.grasses, nValue[7]):
                oGrass.grass, oGrass.unk1 = grassValue
            nEntry.musicType = nValue[8]
            diffLength = len(nValue[9]) - CBash.GetFIDListX2Size(self._CollectionIndex, self._ModName, self._recordID, 13, oEntry._listIndex, 10)
            while(diffLength < 0):
                CBash.DeleteFIDListX2Element(self._CollectionIndex, self._ModName, self._recordID, 13, oEntry._listIndex, 10)
                diffLength += 1
            while(diffLength > 0):
                CBash.CreateFIDListX2Element(self._CollectionIndex, self._ModName, self._recordID, 13, oEntry._listIndex, 10)
                diffLength -= 1
            for oSound, soundValue in zip(oEntry.sounds, nValue[9]):
                oSound.sound, oSound.flags, oSound.chance = soundValue
            diffLength = len(nValue[10]) - CBash.GetFIDListX2Size(self._CollectionIndex, self._ModName, self._recordID, 13, oEntry._listIndex, 11)
            while(diffLength < 0):
                CBash.DeleteFIDListX2Element(self._CollectionIndex, self._ModName, self._recordID, 13, oEntry._listIndex, 11)
                diffLength += 1
            while(diffLength > 0):
                CBash.CreateFIDListX2Element(self._CollectionIndex, self._ModName, self._recordID, 13, oEntry._listIndex, 11)
                diffLength -= 1
            for oWeather, weatherValue in zip(oEntry.weathers, nValue[10]):
                oWeather.weather, oWeather.chance = weatherValue                  
    entries = property(get_entries, set_entries)
class CELLRecord(BaseRecord):
    def CopyAsOverride(self, targetMod):
        if(self._parentID == None):
            FID = CBash.CopyCELLRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, 0, c_bool(True))
            if(FID): return CELLRecord(self._CollectionIndex, targetMod._ModName, FID)
        else:
            FID = CBash.CopyCELLRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, targetMod._recordID, c_bool(True))
            if(FID): return CELLRecord(self._CollectionIndex, targetMod._ModName, FID, targetMod._recordID)
        return None
    def CopyAsNew(self, targetMod):
        if(self._parentID == None):
            FID = CBash.CopyCELLRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, 0, c_bool(False))
            if(FID): return CELLRecord(self._CollectionIndex, targetMod._ModName, FID)
        else:
            FID = CBash.CopyCELLRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, targetMod._recordID, c_bool(False))
            if(FID): return CELLRecord(self._CollectionIndex, targetMod._ModName, FID, targetMod._recordID)
        return None
    def createACHRRecord(self):
        FID = CBash.CreateACHRRecord(self._CollectionIndex, self._ModName, self._recordID)
        if(FID): return ACHRRecord(self._CollectionIndex, self._ModName, FID, self._recordID)
        return None
    def createACRERecord(self):
        FID = CBash.CreateACRERecord(self._CollectionIndex, self._ModName, self._recordID)
        if(FID): return ACRERecord(self._CollectionIndex, self._ModName, FID, self._recordID)
        return None
    def createREFRRecord(self):
        FID = CBash.CreateREFRRecord(self._CollectionIndex, self._ModName, self._recordID)
        if(FID): return REFRRecord(self._CollectionIndex, self._ModName, FID, self._recordID)
        return None
    def createPGRDRecord(self):
        FID = CBash.CreatePGRDRecord(self._CollectionIndex, self._ModName, self._recordID)
        if(FID): return PGRDRecord(self._CollectionIndex, self._ModName, FID, self._recordID)
        return None
    def createLANDRecord(self):
        FID = CBash.CreateLANDRecord(self._CollectionIndex, self._ModName, self._recordID)
        if(FID): return LANDRecord(self._CollectionIndex, self._ModName, FID, self._recordID)
        return None
    def get_full(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 6)
    def set_full(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 6, nValue)
    full = property(get_full, set_full)
    def get_flags(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 7)
        if(retValue): return retValue.contents.value
        else: return None
    def set_flags(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 7, c_ubyte(nValue))
    flags = property(get_flags, set_flags)
    def get_ambientRed(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 8)
        if(retValue): return retValue.contents.value
        else: return None
    def set_ambientRed(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 8, c_ubyte(nValue))
    ambientRed = property(get_ambientRed, set_ambientRed)
    def get_ambientGreen(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 9)
        if(retValue): return retValue.contents.value
        else: return None
    def set_ambientGreen(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 9, c_ubyte(nValue))
    ambientGreen = property(get_ambientGreen, set_ambientGreen)
    def get_ambientBlue(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 10)
        if(retValue): return retValue.contents.value
        else: return None
    def set_ambientBlue(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 10, c_ubyte(nValue))
    ambientBlue = property(get_ambientBlue, set_ambientBlue)
    def get_unused1(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 11)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 11, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_unused1(self, nValue):
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 11, struct.pack('B', *nValue), 1)
    unused1 = property(get_unused1, set_unused1)
    def get_directionalRed(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 12)
        if(retValue): return retValue.contents.value
        else: return None
    def set_directionalRed(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 12, c_ubyte(nValue))
    directionalRed = property(get_directionalRed, set_directionalRed)
    def get_directionalGreen(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 13)
        if(retValue): return retValue.contents.value
        else: return None
    def set_directionalGreen(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 13, c_ubyte(nValue))
    directionalGreen = property(get_directionalGreen, set_directionalGreen)
    def get_directionalBlue(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 14)
        if(retValue): return retValue.contents.value
        else: return None
    def set_directionalBlue(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 14, c_ubyte(nValue))
    directionalBlue = property(get_directionalBlue, set_directionalBlue)
    def get_unused2(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 15)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 15, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_unused2(self, nValue):
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 15, struct.pack('B', *nValue), 1)
    unused2 = property(get_unused2, set_unused2)
    def get_fogRed(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 16)
        if(retValue): return retValue.contents.value
        else: return None
    def set_fogRed(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 16, c_ubyte(nValue))
    fogRed = property(get_fogRed, set_fogRed)
    def get_fogGreen(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 17)
        if(retValue): return retValue.contents.value
        else: return None
    def set_fogGreen(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 17, c_ubyte(nValue))
    fogGreen = property(get_fogGreen, set_fogGreen)
    def get_fogBlue(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 18)
        if(retValue): return retValue.contents.value
        else: return None
    def set_fogBlue(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 18, c_ubyte(nValue))
    fogBlue = property(get_fogBlue, set_fogBlue)
    def get_unused3(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 19)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 19, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_unused3(self, nValue):
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 19, struct.pack('B', *nValue), 1)
    unused3 = property(get_unused3, set_unused3)
    def get_fogNear(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 20)
        if(retValue): return retValue.contents.value
        else: return None
    def set_fogNear(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 20, c_float(nValue))
    fogNear = property(get_fogNear, set_fogNear)
    def get_fogFar(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 21)
        if(retValue): return retValue.contents.value
        else: return None
    def set_fogFar(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 21, c_float(nValue))
    fogFar = property(get_fogFar, set_fogFar)
    def get_directionalXY(self):
        CBash.ReadFIDField.restype = POINTER(c_int)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 22)
        if(retValue): return retValue.contents.value
        else: return None
    def set_directionalXY(self, nValue):
        CBash.SetFIDFieldI(self._CollectionIndex, self._ModName, self._recordID, 22, nValue)
    directionalXY = property(get_directionalXY, set_directionalXY)
    def get_directionalZ(self):
        CBash.ReadFIDField.restype = POINTER(c_int)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 23)
        if(retValue): return retValue.contents.value
        else: return None
    def set_directionalZ(self, nValue):
        CBash.SetFIDFieldI(self._CollectionIndex, self._ModName, self._recordID, 23, nValue)
    directionalZ = property(get_directionalZ, set_directionalZ)
    def get_directionalFade(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 24)
        if(retValue): return retValue.contents.value
        else: return None
    def set_directionalFade(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 24, c_float(nValue))
    directionalFade = property(get_directionalFade, set_directionalFade)
    def get_fogClip(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 25)
        if(retValue): return retValue.contents.value
        else: return None
    def set_fogClip(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 25, c_float(nValue))
    fogClip = property(get_fogClip, set_fogClip)
    def get_music(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 26)
        if(retValue): return retValue.contents.value
        else: return None
    def set_music(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 26, c_ubyte(nValue))
    music = property(get_music, set_music)
    def get_owner(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 27)
        if(retValue): return retValue.contents.value
        else: return None
    def set_owner(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 27, nValue)
    owner = property(get_owner, set_owner)
    def get_rank(self):
        CBash.ReadFIDField.restype = POINTER(c_int)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 28)
        if(retValue): return retValue.contents.value
        else: return None
    def set_rank(self, nValue):
        CBash.SetFIDFieldI(self._CollectionIndex, self._ModName, self._recordID, 28, nValue)
    rank = property(get_rank, set_rank)
    def get_globalVariable(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 29)
        if(retValue): return retValue.contents.value
        else: return None
    def set_globalVariable(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 29, nValue)
    globalVariable = property(get_globalVariable, set_globalVariable)
    def get_climate(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 30)
        if(retValue): return retValue.contents.value
        else: return None
    def set_climate(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 30, nValue)
    climate = property(get_climate, set_climate)
    def get_waterHeight(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 31)
        if(retValue): return retValue.contents.value
        else: return None
    def set_waterHeight(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 31, c_float(nValue))
    waterHeight = property(get_waterHeight, set_waterHeight)
    def get_regions(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 32)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 32, byref(cRecords))
            return [cRecords[x].contents.value for x in range(0, numRecords)]
        else: return []
    def set_regions(self, nValue):
        CBash.SetFIDFieldUIA(self._CollectionIndex, self._ModName, self._recordID, 32, struct.pack('I' * len(nValue), *nValue), len(nValue))
    regions = property(get_regions, set_regions)
    def get_posX(self):
        CBash.ReadFIDField.restype = POINTER(c_int)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 33)
        if(retValue): return retValue.contents.value
        else: return None
    def set_posX(self, nValue):
        CBash.SetFIDFieldI(self._CollectionIndex, self._ModName, self._recordID, 33, nValue)
    posX = property(get_posX, set_posX)
    def get_posY(self):
        CBash.ReadFIDField.restype = POINTER(c_int)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 34)
        if(retValue): return retValue.contents.value
        else: return None
    def set_posY(self, nValue):
        CBash.SetFIDFieldI(self._CollectionIndex, self._ModName, self._recordID, 34, nValue)
    posY = property(get_posY, set_posY)
    def get_water(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 35)
        if(retValue): return retValue.contents.value
        else: return None
    def set_water(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 35, nValue)
    water = property(get_water, set_water)
    @property
    def ACHR(self):
        numSubRecords = CBash.GetNumACHRRecords(self._CollectionIndex, self._ModName, self._recordID)
        if(numSubRecords > 0):
            cRecords = (POINTER(c_uint) * numSubRecords)()
            CBash.GetACHRRecords(self._CollectionIndex, self._ModName, self._recordID, cRecords)
            return [ACHRRecord(self._CollectionIndex, self._ModName, x.contents.value, self._recordID) for x in cRecords]
        else: return []

    @property
    def ACRE(self):
        numSubRecords = CBash.GetNumACRERecords(self._CollectionIndex, self._ModName, self._recordID)
        if(numSubRecords > 0):
            cRecords = (POINTER(c_uint) * numSubRecords)()
            CBash.GetACRERecords(self._CollectionIndex, self._ModName, self._recordID, cRecords)
            return [ACRERecord(self._CollectionIndex, self._ModName, x.contents.value, self._recordID) for x in cRecords]
        else: return []
    @property
    def REFR(self):
        numSubRecords = CBash.GetNumREFRRecords(self._CollectionIndex, self._ModName, self._recordID)
        if(numSubRecords > 0):
            cRecords = (POINTER(c_uint) * numSubRecords)()
            CBash.GetREFRRecords(self._CollectionIndex, self._ModName, self._recordID, cRecords)
            return [REFRRecord(self._CollectionIndex, self._ModName, x.contents.value, self._recordID) for x in cRecords]
        else: return []
    def get_PGRD(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 39)
        if(retValue): return PGRDRecord(self._CollectionIndex, self._ModName, retValue.contents.value, self._recordID)
        else: return None
    def set_PGRD(self, nPGRD):
        curPGRD = self.PGRD
        if(curPGRD == None):
            curPGRD = self.createPGRDRecord()
        curPGRD.count = nPGRD.count
        curPGRD.PGRP = nPGRD.PGRP
        curPGRD.PGAG = nPGRD.PGAG
        curPGRD.PGRR = nPGRD.PGRR
        curPGRD.PGRI = nPGRD.PGRI
        curPGRD.PGRL = nPGRD.PGRL
    PGRD = property(get_PGRD, set_PGRD)
    def get_LAND(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 40)
        if(retValue): return LANDRecord(self._CollectionIndex, self._ModName, retValue.contents.value, self._recordID)
        else: return None
    def set_LAND(self, nLAND):
        curLAND = self.LAND
        if(curLAND == None):
            curLAND = self.createLANDRecord()
##        curLAND.count = nLAND.count
##        curLAND.PGRP = nLAND.PGRP
##        curLAND.PGAG = nLAND.PGAG
##        curLAND.PGRR = nLAND.PGRR
##        curLAND.PGRI = nLAND.PGRI
##        curLAND.PGRL = nLAND.PGRL
    LAND = property(get_LAND, set_LAND)
class ACHRRecord(BaseRecord):
    def CopyAsOverride(self, targetCELL):
        FID = CBash.CopyACHRRecord(self._CollectionIndex, self._ModName, self._recordID, targetCELL._ModName, targetCELL._recordID, c_bool(True))
        if(FID): return ACHRRecord(self._CollectionIndex, targetCELL._ModName, FID, targetCELL._recordID)
        return None
    def CopyAsNew(self, targetCELL):
        FID = CBash.CopyACHRRecord(self._CollectionIndex, self._ModName, self._recordID, targetCELL._ModName, targetCELL._recordID, c_bool(False))
        if(FID): return ACHRRecord(self._CollectionIndex, targetCELL._ModName, FID, targetCELL._recordID)
        return None
    def get_eid(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 5)
    def set_eid(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 5, nValue)
    eid = property(get_eid, set_eid)
    def get_base(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 6)
        if(retValue): return retValue.contents.value
        else: return None
    def set_base(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 6, nValue)
    base = property(get_base, set_base)
    def get_unknownXPCIFormID(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 7)
        if(retValue): return retValue.contents.value
        else: return None
    def set_unknownXPCIFormID(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 7, nValue)
    unknownXPCIFormID = property(get_unknownXPCIFormID, set_unknownXPCIFormID)
    def get_unknownXPCIString(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 8)
    def set_unknownXPCIString(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 8, nValue)
    unknownXPCIString = property(get_unknownXPCIString, set_unknownXPCIString)
    def get_lod1(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 9)
        if(retValue): return retValue.contents.value
        else: return None
    def set_lod1(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 9, c_float(nValue))
    lod1 = property(get_lod1, set_lod1)
    def get_lod2(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 10)
        if(retValue): return retValue.contents.value
        else: return None
    def set_lod2(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 10, c_float(nValue))
    lod2 = property(get_lod2, set_lod2)
    def get_lod3(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 11)
        if(retValue): return retValue.contents.value
        else: return None
    def set_lod3(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 11, c_float(nValue))
    lod3 = property(get_lod3, set_lod3)
    def get_parent(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 12)
        if(retValue): return retValue.contents.value
        else: return None
    def set_parent(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 12, nValue)
    parent = property(get_parent, set_parent)
    def get_parentFlags(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 13)
        if(retValue): return retValue.contents.value
        else: return None
    def set_parentFlags(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 13, c_ubyte(nValue))
    parentFlags = property(get_parentFlags, set_parentFlags)
    def get_unused1(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 14)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 14, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_unused1(self, nValue):
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 14, struct.pack('3B', *nValue), 3)
    unused1 = property(get_unused1, set_unused1)
    def get_merchantContainer(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 15)
        if(retValue): return retValue.contents.value
        else: return None
    def set_merchantContainer(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 15, nValue)
    merchantContainer = property(get_merchantContainer, set_merchantContainer)
    def get_horse(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 16)
        if(retValue): return retValue.contents.value
        else: return None
    def set_horse(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 16, nValue)
    horse = property(get_horse, set_horse)
    def get_xrgd_p(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 17)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 17, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_xrgd_p(self, nValue):
        length = len(nValue)
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 17, struct.pack('B' * length, *nValue), length)
    xrgd_p = property(get_xrgd_p, set_xrgd_p)
    def get_scale(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 18)
        if(retValue): return retValue.contents.value
        else: return None
    def set_scale(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 18, c_float(nValue))
    scale = property(get_scale, set_scale)
    def get_posX(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 19)
        if(retValue): return retValue.contents.value
        else: return None
    def set_posX(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 19, c_float(nValue))
    posX = property(get_posX, set_posX)
    def get_posY(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 20)
        if(retValue): return retValue.contents.value
        else: return None
    def set_posY(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 20, c_float(nValue))
    posY = property(get_posY, set_posY)
    def get_posZ(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 21)
        if(retValue): return retValue.contents.value
        else: return None
    def set_posZ(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 21, c_float(nValue))
    posZ = property(get_posZ, set_posZ)
    def get_rotX(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 22)
        if(retValue): return retValue.contents.value
        else: return None
    def set_rotX(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 22, c_float(nValue))
    rotX = property(get_rotX, set_rotX)
    def get_rotY(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 23)
        if(retValue): return retValue.contents.value
        else: return None
    def set_rotY(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 23, c_float(nValue))
    rotY = property(get_rotY, set_rotY)
    def get_rotZ(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 24)
        if(retValue): return retValue.contents.value
        else: return None
    def set_rotZ(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 24, c_float(nValue))
    rotZ = property(get_rotZ, set_rotZ)
class ACRERecord(BaseRecord):
    def CopyAsOverride(self, targetCELL):
        FID = CBash.CopyACRERecord(self._CollectionIndex, self._ModName, self._recordID, targetCELL._ModName, targetCELL._recordID, c_bool(True))
        if(FID): return ACRERecord(self._CollectionIndex, targetCELL._ModName, FID, targetCELL._recordID)
        return None
    def CopyAsNew(self, targetCELL):
        FID = CBash.CopyACRERecord(self._CollectionIndex, self._ModName, self._recordID, targetCELL._ModName, targetCELL._recordID, c_bool(False))
        if(FID): return ACRERecord(self._CollectionIndex, targetCELL._ModName, FID, targetCELL._recordID)
        return None
    def get_eid(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 5)
    def set_eid(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 5, nValue)
    eid = property(get_eid, set_eid)
    def get_base(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 6)
        if(retValue): return retValue.contents.value
        else: return None
    def set_base(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 6, nValue)
    base = property(get_base, set_base)
    def get_owner(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 7)
        if(retValue): return retValue.contents.value
        else: return None
    def set_owner(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 7, nValue)
    owner = property(get_owner, set_owner)
    def get_rank(self):
        CBash.ReadFIDField.restype = POINTER(c_int)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 8)
        if(retValue): return retValue.contents.value
        else: return None
    def set_rank(self, nValue):
        CBash.SetFIDFieldI(self._CollectionIndex, self._ModName, self._recordID, 8, nValue)
    rank = property(get_rank, set_rank)
    def get_globalVariable(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 9)
        if(retValue): return retValue.contents.value
        else: return None
    def set_globalVariable(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 9, nValue)
    globalVariable = property(get_globalVariable, set_globalVariable)
    def get_parent(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 10)
        if(retValue): return retValue.contents.value
        else: return None
    def set_parent(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 10, nValue)
    parent = property(get_parent, set_parent)
    def get_parentFlags(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 11)
        if(retValue): return retValue.contents.value
        else: return None
    def set_parentFlags(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 11, c_ubyte(nValue))
    parentFlags = property(get_parentFlags, set_parentFlags)
    def get_unused1(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 12)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 12, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_unused1(self, nValue):
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 12, struct.pack('3B', *nValue), 3)
    unused1 = property(get_unused1, set_unused1)
    def get_xrgd_p(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 13)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 13, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_xrgd_p(self, nValue):
        length = len(nValue)
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 13, struct.pack('B' * length, *nValue), length)
    xrgd_p = property(get_xrgd_p, set_xrgd_p)
    def get_scale(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 14)
        if(retValue): return retValue.contents.value
        else: return None
    def set_scale(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 14, c_float(nValue))
    scale = property(get_scale, set_scale)
    def get_posX(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 15)
        if(retValue): return retValue.contents.value
        else: return None
    def set_posX(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 15, c_float(nValue))
    posX = property(get_posX, set_posX)
    def get_posY(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 16)
        if(retValue): return retValue.contents.value
        else: return None
    def set_posY(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 16, c_float(nValue))
    posY = property(get_posY, set_posY)
    def get_posZ(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 17)
        if(retValue): return retValue.contents.value
        else: return None
    def set_posZ(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 17, c_float(nValue))
    posZ = property(get_posZ, set_posZ)
    def get_rotX(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 18)
        if(retValue): return retValue.contents.value
        else: return None
    def set_rotX(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 18, c_float(nValue))
    rotX = property(get_rotX, set_rotX)
    def get_rotY(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 19)
        if(retValue): return retValue.contents.value
        else: return None
    def set_rotY(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 19, c_float(nValue))
    rotY = property(get_rotY, set_rotY)
    def get_rotZ(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 20)
        if(retValue): return retValue.contents.value
        else: return None
    def set_rotZ(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 20, c_float(nValue))
    rotZ = property(get_rotZ, set_rotZ)
class REFRRecord(BaseRecord):
    def CopyAsOverride(self, targetCELL):
        FID = CBash.CopyREFRRecord(self._CollectionIndex, self._ModName, self._recordID, targetCELL._ModName, targetCELL._recordID, c_bool(True))
        if(FID): return REFRRecord(self._CollectionIndex, targetCELL._ModName, FID, targetCELL._recordID)
        return None
    def CopyAsNew(self, targetCELL):
        FID = CBash.CopyREFRRecord(self._CollectionIndex, self._ModName, self._recordID, targetCELL._ModName, targetCELL._recordID, c_bool(False))
        if(FID): return REFRRecord(self._CollectionIndex, targetCELL._ModName, FID, targetCELL._recordID)
        return None
    def get_eid(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 5)
    def set_eid(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 5, nValue)
    eid = property(get_eid, set_eid)
    def get_base(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 6)
        if(retValue): return retValue.contents.value
        else: return None
    def set_base(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 6, nValue)
    base = property(get_base, set_base)
    def get_destinationFormID(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 7)
        if(retValue): return retValue.contents.value
        else: return None
    def set_destinationFormID(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 7, nValue)
    destinationFormID = property(get_destinationFormID, set_destinationFormID)
    def get_destinationPosX(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 8)
        if(retValue): return retValue.contents.value
        else: return None
    def set_destinationPosX(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 8, c_float(nValue))
    destinationPosX = property(get_destinationPosX, set_destinationPosX)
    def get_destinationPosY(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 9)
        if(retValue): return retValue.contents.value
        else: return None
    def set_destinationPosY(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 9, c_float(nValue))
    destinationPosY = property(get_destinationPosY, set_destinationPosY)
    def get_destinationPosZ(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 10)
        if(retValue): return retValue.contents.value
        else: return None
    def set_destinationPosZ(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 10, c_float(nValue))
    destinationPosZ = property(get_destinationPosZ, set_destinationPosZ)
    def get_destinationRotX(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 11)
        if(retValue): return retValue.contents.value
        else: return None
    def set_destinationRotX(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 11, c_float(nValue))
    destinationRotX = property(get_destinationRotX, set_destinationRotX)
    def get_destinationRotY(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 12)
        if(retValue): return retValue.contents.value
        else: return None
    def set_destinationRotY(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 12, c_float(nValue))
    destinationRotY = property(get_destinationRotY, set_destinationRotY)
    def get_destinationRotZ(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 13)
        if(retValue): return retValue.contents.value
        else: return None
    def set_destinationRotZ(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 13, c_float(nValue))
    destinationRotZ = property(get_destinationRotZ, set_destinationRotZ)
    def get_lockLevel(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 14)
        if(retValue): return retValue.contents.value
        else: return None
    def set_lockLevel(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 14, c_ubyte(nValue))
    lockLevel = property(get_lockLevel, set_lockLevel)
    def get_unused1(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 15)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 15, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_unused1(self, nValue):
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 15, struct.pack('3B', *nValue), 3)
    unused1 = property(get_unused1, set_unused1)
    def get_lockKey(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 16)
        if(retValue): return retValue.contents.value
        else: return None
    def set_lockKey(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 16, nValue)
    lockKey = property(get_lockKey, set_lockKey)
    def get_unused2(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 17)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 17, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_unused2(self, nValue):
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 17, struct.pack('4B', *nValue), 4)
    unused2 = property(get_unused2, set_unused2)
    def get_lockFlags(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 18)
        if(retValue): return retValue.contents.value
        else: return None
    def set_lockFlags(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 18, c_ubyte(nValue))
    lockFlags = property(get_lockFlags, set_lockFlags)
    def get_unused3(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 19)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 19, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_unused3(self, nValue):
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 19, struct.pack('3B', *nValue), 3)
    unused3 = property(get_unused3, set_unused3)
    def get_owner(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 20)
        if(retValue): return retValue.contents.value
        else: return None
    def set_owner(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 20, nValue)
    owner = property(get_owner, set_owner)
    def get_rank(self):
        CBash.ReadFIDField.restype = POINTER(c_int)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 21)
        if(retValue): return retValue.contents.value
        else: return None
    def set_rank(self, nValue):
        CBash.SetFIDFieldI(self._CollectionIndex, self._ModName, self._recordID, 21, nValue)
    rank = property(get_rank, set_rank)
    def get_globalVariable(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 22)
        if(retValue): return retValue.contents.value
        else: return None
    def set_globalVariable(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 22, nValue)
    globalVariable = property(get_globalVariable, set_globalVariable)
    def get_parent(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 23)
        if(retValue): return retValue.contents.value
        else: return None
    def set_parent(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 23, nValue)
    parent = property(get_parent, set_parent)
    def get_parentFlags(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 24)
        if(retValue): return retValue.contents.value
        else: return None
    def set_parentFlags(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 24, c_ubyte(nValue))
    parentFlags = property(get_parentFlags, set_parentFlags)
    def get_unused4(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 25)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 25, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_unused4(self, nValue):
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 25, struct.pack('3B', *nValue), 3)
    unused4 = property(get_unused4, set_unused4)
    def get_targetFormID(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 26)
        if(retValue): return retValue.contents.value
        else: return None
    def set_targetFormID(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 26, nValue)
    targetFormID = property(get_targetFormID, set_targetFormID)
    def get_seed(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 27)
        if(retValue): return retValue.contents.value
        else: return None
    def set_seed(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 27, nValue)
    seed = property(get_seed, set_seed)
    def get_seedOffset(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 27)
        if(retValue): return retValue.contents.value
        else: return None
    def set_seedOffset(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 27, c_ubyte(nValue))
    seedOffset = property(get_seedOffset, set_seedOffset)
    def get_lod1(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 28)
        if(retValue): return retValue.contents.value
        else: return None
    def set_lod1(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 28, c_float(nValue))
    lod1 = property(get_lod1, set_lod1)
    def get_lod2(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 29)
        if(retValue): return retValue.contents.value
        else: return None
    def set_lod2(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 29, c_float(nValue))
    lod2 = property(get_lod2, set_lod2)
    def get_lod3(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 30)
        if(retValue): return retValue.contents.value
        else: return None
    def set_lod3(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 30, c_float(nValue))
    lod3 = property(get_lod3, set_lod3)
    def get_charge(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 31)
        if(retValue): return retValue.contents.value
        else: return None
    def set_charge(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 31, c_float(nValue))
    charge = property(get_charge, set_charge)
    def get_health(self):
        CBash.ReadFIDField.restype = POINTER(c_int)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 32)
        if(retValue): return retValue.contents.value
        else: return None
    def set_health(self, nValue):
        CBash.SetFIDFieldI(self._CollectionIndex, self._ModName, self._recordID, 32, nValue)
    health = property(get_health, set_health)
    def get_unknownXPCIFormID(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 33)
        if(retValue): return retValue.contents.value
        else: return None
    def set_unknownXPCIFormID(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 33, nValue)
    unknownXPCIFormID = property(get_unknownXPCIFormID, set_unknownXPCIFormID)
    def get_unknownXPCIString(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 34)
    def set_unknownXPCIString(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 34, nValue)
    unknownXPCIString = property(get_unknownXPCIString, set_unknownXPCIString)
    def get_levelMod(self):
        CBash.ReadFIDField.restype = POINTER(c_int)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 35)
        if(retValue): return retValue.contents.value
        else: return None
    def set_levelMod(self, nValue):
        CBash.SetFIDFieldI(self._CollectionIndex, self._ModName, self._recordID, 35, nValue)
    levelMod = property(get_levelMod, set_levelMod)
    def get_unknownXRTMFormID(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 36)
        if(retValue): return retValue.contents.value
        else: return None
    def set_unknownXRTMFormID(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 36, nValue)
    unknownXRTMFormID = property(get_unknownXRTMFormID, set_unknownXRTMFormID)
    def get_actionFlags(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 37)
        if(retValue): return retValue.contents.value
        else: return None
    def set_actionFlags(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 37, nValue)
    actionFlags = property(get_actionFlags, set_actionFlags)
    def get_count(self):
        CBash.ReadFIDField.restype = POINTER(c_int)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 38)
        if(retValue): return retValue.contents.value
        else: return None
    def set_count(self, nValue):
        CBash.SetFIDFieldI(self._CollectionIndex, self._ModName, self._recordID, 38, nValue)
    count = property(get_count, set_count)
    def get_markerFlags(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 39)
        if(retValue): return retValue.contents.value
        else: return None
    def set_markerFlags(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 39, c_ubyte(nValue))
    markerFlags = property(get_markerFlags, set_markerFlags)
    def get_markerName(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 40)
    def set_markerName(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 40, nValue)
    markerName = property(get_markerName, set_markerName)
    def get_markerType(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 41)
        if(retValue): return retValue.contents.value
        else: return None
    def set_markerType(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 41, c_ubyte(nValue))
    markerType = property(get_markerType, set_markerType)
    def get_markerUnused(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 42)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 42, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_markerUnused(self, nValue):
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 42, struct.pack('B', *nValue), 1)
    markerUnused = property(get_markerUnused, set_markerUnused)
    def get_scale(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 43)
        if(retValue): return retValue.contents.value
        else: return None
    def set_scale(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 43, c_float(nValue))
    scale = property(get_scale, set_scale)
    def get_soul(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 44)
        if(retValue): return retValue.contents.value
        else: return None
    def set_soul(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 44, c_ubyte(nValue))
    soul = property(get_soul, set_soul)
    def get_posX(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 45)
        if(retValue): return retValue.contents.value
        else: return None
    def set_posX(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 45, c_float(nValue))
    posX = property(get_posX, set_posX)
    def get_posY(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 46)
        if(retValue): return retValue.contents.value
        else: return None
    def set_posY(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 46, c_float(nValue))
    posY = property(get_posY, set_posY)
    def get_posZ(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 47)
        if(retValue): return retValue.contents.value
        else: return None
    def set_posZ(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 47, c_float(nValue))
    posZ = property(get_posZ, set_posZ)
    def get_rotX(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 48)
        if(retValue): return retValue.contents.value
        else: return None
    def set_rotX(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 48, c_float(nValue))
    rotX = property(get_rotX, set_rotX)
    def get_rotY(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 49)
        if(retValue): return retValue.contents.value
        else: return None
    def set_rotY(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 49, c_float(nValue))
    rotY = property(get_rotY, set_rotY)
    def get_rotZ(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 50)
        if(retValue): return retValue.contents.value
        else: return None
    def set_rotZ(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 50, c_float(nValue))
    rotZ = property(get_rotZ, set_rotZ)
class PGRDRecord(BaseRecord):
    def CopyAsOverride(self, targetCELL):
        FID = CBash.CopyPGRDRecord(self._CollectionIndex, self._ModName, self._recordID, targetCELL._ModName, targetCELL._recordID, c_bool(True))
        if(FID): return PGRDRecord(self._CollectionIndex, targetCELL._ModName, FID, targetCELL._recordID)
        return None
    def CopyAsNew(self, targetCELL):
        FID = CBash.CopyPGRDRecord(self._CollectionIndex, self._ModName, self._recordID, targetCELL._ModName, targetCELL._recordID, c_bool(False))
        if(FID): return PGRDRecord(self._CollectionIndex, targetCELL._ModName, FID, targetCELL._recordID)
        return None
    class PGRPRecord(object):
        def __init__(self, CollectionIndex, ModName, recordID, listIndex):
            self._CollectionIndex = CollectionIndex
            self._ModName = ModName
            self._recordID = recordID
            self._listIndex = listIndex
        def get_x(self):
            CBash.ReadFIDListField.restype = POINTER(c_float)
            retValue = CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, 7, self._listIndex, 1)
            if(retValue): return retValue.contents.value
            else: return None
        def set_x(self, nValue):
            CBash.SetFIDListFieldF(self._CollectionIndex, self._ModName, self._recordID, 7, self._listIndex, 1, c_float(nValue))
        x = property(get_x, set_x)
        def get_y(self):
            CBash.ReadFIDListField.restype = POINTER(c_float)
            retValue = CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, 7, self._listIndex, 2)
            if(retValue): return retValue.contents.value
            else: return None
        def set_y(self, nValue):
            CBash.SetFIDListFieldF(self._CollectionIndex, self._ModName, self._recordID, 7, self._listIndex, 2, c_float(nValue))
        y = property(get_y, set_y)
        def get_z(self):
            CBash.ReadFIDListField.restype = POINTER(c_float)
            retValue = CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, 7, self._listIndex, 3)
            if(retValue): return retValue.contents.value
            else: return None
        def set_z(self, nValue):
            CBash.SetFIDListFieldF(self._CollectionIndex, self._ModName, self._recordID, 7, self._listIndex, 3, c_float(nValue))
        z = property(get_z, set_z)
        def get_connections(self):
            CBash.ReadFIDListField.restype = POINTER(c_ubyte)
            retValue = CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, 7, self._listIndex, 4)
            if(retValue): return retValue.contents.value
            else: return None
        def set_connections(self, nValue):
            CBash.SetFIDListFieldUC(self._CollectionIndex, self._ModName, self._recordID, 7, self._listIndex, 4, c_ubyte(nValue))
        connections = property(get_connections, set_connections)
        def get_unused1(self):
            numRecords = CBash.GetFIDListArraySize(self._CollectionIndex, self._ModName, self._recordID, 7, self._listIndex, 5)
            if(numRecords > 0):
                cRecords = POINTER(c_ubyte * numRecords)()
                CBash.GetFIDListArray(self._CollectionIndex, self._ModName, self._recordID, 7, self._listIndex, 5, byref(cRecords))
                return [cRecords.contents[x] for x in range(0, numRecords)]
            else: return []
        def set_unused1(self, nValue):
            CBash.SetFIDListFieldR(self._CollectionIndex, self._ModName, self._recordID, 7, self._listIndex, 5, struct.pack('3B', *nValue), 3)
        unused1 = property(get_unused1, set_unused1)
    class PGRIRecord(object):
        def __init__(self, CollectionIndex, ModName, recordID, listIndex):
            self._CollectionIndex = CollectionIndex
            self._ModName = ModName
            self._recordID = recordID
            self._listIndex = listIndex
        def get_point(self):
            CBash.ReadFIDListField.restype = POINTER(c_ushort)
            retValue = CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, 10, self._listIndex, 1)
            if(retValue): return retValue.contents.value
            else: return None
        def set_point(self, nValue):
            CBash.SetFIDListFieldUS(self._CollectionIndex, self._ModName, self._recordID, 10, self._listIndex, 1, c_ushort(nValue))
        point = property(get_point, set_point)
        def get_unused1(self):
            numRecords = CBash.GetFIDListArraySize(self._CollectionIndex, self._ModName, self._recordID, 10, self._listIndex, 2)
            if(numRecords > 0):
                cRecords = POINTER(c_ubyte * numRecords)()
                CBash.GetFIDListArray(self._CollectionIndex, self._ModName, self._recordID, 10, self._listIndex, 2, byref(cRecords))
                return [cRecords.contents[x] for x in range(0, numRecords)]
            else: return []
        def set_unused1(self, nValue):
            CBash.SetFIDListFieldR(self._CollectionIndex, self._ModName, self._recordID, 10, self._listIndex, 2, struct.pack('2B', *nValue), 2)
        unused1 = property(get_unused1, set_unused1)
        def get_x(self):
            CBash.ReadFIDListField.restype = POINTER(c_float)
            retValue = CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, 10, self._listIndex, 3)
            if(retValue): return retValue.contents.value
            else: return None
        def set_x(self, nValue):
            CBash.SetFIDListFieldF(self._CollectionIndex, self._ModName, self._recordID, 10, self._listIndex, 3, c_float(nValue))
        x = property(get_x, set_x)
        def get_y(self):
            CBash.ReadFIDListField.restype = POINTER(c_float)
            retValue = CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, 10, self._listIndex, 4)
            if(retValue): return retValue.contents.value
            else: return None
        def set_y(self, nValue):
            CBash.SetFIDListFieldF(self._CollectionIndex, self._ModName, self._recordID, 10, self._listIndex, 4, c_float(nValue))
        y = property(get_y, set_y)
        def get_z(self):
            CBash.ReadFIDListField.restype = POINTER(c_float)
            retValue = CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, 10, self._listIndex, 5)
            if(retValue): return retValue.contents.value
            else: return None
        def set_z(self, nValue):
            CBash.SetFIDListFieldF(self._CollectionIndex, self._ModName, self._recordID, 10, self._listIndex, 5, c_float(nValue))
        z = property(get_z, set_z)
    class PGRLRecord(object):
        def __init__(self, CollectionIndex, ModName, recordID, listIndex):
            self._CollectionIndex = CollectionIndex
            self._ModName = ModName
            self._recordID = recordID
            self._listIndex = listIndex
        def get_reference(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            retValue = CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, 11, self._listIndex, 1)
            if(retValue): return retValue.contents.value
            else: return None
        def set_reference(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, 11, self._listIndex, 1, nValue)
        reference = property(get_reference, set_reference)
        def get_points(self):
            numRecords = CBash.GetFIDListArraySize(self._CollectionIndex, self._ModName, self._recordID, 11, self._listIndex, 2)
            if(numRecords > 0):                
                cRecords = POINTER(c_uint * numRecords)()
                CBash.GetFIDListArray(self._CollectionIndex, self._ModName, self._recordID, 11, self._listIndex, 2, byref(cRecords))
                return [cRecords.contents[x] for x in range(0, numRecords)]
            else: return []
        def set_points(self, nValues):
            CBash.SetFIDListFieldUIA(self._CollectionIndex, self._ModName, self._recordID, 11, self._listIndex, 2, struct.pack('I' * len(nValues), *nValues), len(nValues))
        points = property(get_points, set_points)
    def newPGRPElement(self):
        listIndex = CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 7)
        if(listIndex == -1): return None
        return self.PGRPRecord(self._CollectionIndex, self._ModName, self._recordID, listIndex)

    def newPGRIElement(self):
        listIndex = CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 10)
        if(listIndex == -1): return None
        return self.PGRIRecord(self._CollectionIndex, self._ModName, self._recordID, listIndex)

    def newPGRLElement(self):
        listIndex = CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 11)
        if(listIndex == -1): return None
        return self.PGRLRecord(self._CollectionIndex, self._ModName, self._recordID, listIndex)
    
    def get_count(self):
        CBash.ReadFIDField.restype = POINTER(c_ushort)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 6)
        if(retValue): return retValue.contents.value
        else: return None
    def set_count(self, nValue):
        CBash.SetFIDFieldUS(self._CollectionIndex, self._ModName, self._recordID, 6, c_ushort(nValue))
    count = property(get_count, set_count)    
    def get_PGRP(self):
        numRecords = CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 7)
        if(numRecords > 0): return [self.PGRPRecord(self._CollectionIndex, self._ModName, self._recordID, x) for x in range(0, numRecords)]
        else: return []
    def set_PGRP(self, nPGRP):
        diffLength = len(nPGRP) - CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 7)
        nValues = [(nPGRPRecord.x, nPGRPRecord.y, nPGRPRecord.z, nPGRPRecord.connections, nPGRPRecord.unused1) for nPGRPRecord in nPGRP]
        while(diffLength < 0):
            CBash.DeleteFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 7)
            diffLength += 1
        while(diffLength > 0):
            CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 7)
            diffLength -= 1
        for oPGRPRecord, nValue in zip(self.PGRP, nValues):
            oPGRPRecord.x, oPGRPRecord.y, oPGRPRecord.z, oPGRPRecord.connections, oPGRPRecord.unused1 = nValue
    PGRP = property(get_PGRP, set_PGRP)    
    def get_PGAG(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 8)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 8, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_PGAG(self, nValue):
        length = len(nValue)
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 8, struct.pack('B' * length, *nValue), length)
    PGAG = property(get_PGAG, set_PGAG)
    def get_PGRR(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 9)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 9, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_PGRR(self, nValue):
        length = len(nValue)
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 9, struct.pack('B' * length, *nValue), length)
    PGRR = property(get_PGRR, set_PGRR)
    def get_PGRI(self):
        numRecords = CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 10)
        if(numRecords > 0): return [self.PGRIRecord(self._CollectionIndex, self._ModName, self._recordID, x) for x in range(0, numRecords)]
        else: return []
    def set_PGRI(self, nPGRI):
        diffLength = len(nPGRI) - CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 10)
        nValues = [(nPGRIRecord.point, nPGRIRecord.unused1, nPGRIRecord.x, nPGRIRecord.y, nPGRIRecord.z) for nPGRIRecord in nPGRI]
        while(diffLength < 0):
            CBash.DeleteFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 10)
            diffLength += 1
        while(diffLength > 0):
            CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 10)
            diffLength -= 1
        for oPGRIRecord, nValue in zip(self.PGRI, nValues):
            oPGRIRecord.point, oPGRIRecord.unused1, oPGRIRecord.x, oPGRIRecord.y, oPGRIRecord.z = nValue
    PGRI = property(get_PGRI, set_PGRI) 
    def get_PGRL(self):
        numRecords = CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 11)
        if(numRecords > 0): return [self.PGRLRecord(self._CollectionIndex, self._ModName, self._recordID, x) for x in range(0, numRecords)]
        else: return []
    def set_PGRL(self, nPGRLs):
        diffLength = len(nPGRLs) - CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 11)
        nValues = [(nPGRL.reference, nPGRL.points) for nPGRL in nPGRLs]
        while(diffLength < 0):
            CBash.DeleteFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 11)
            diffLength += 1
        while(diffLength > 0):
            CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 11)
            diffLength -= 1
        for oPGRL, nValue in zip(self.PGRL, nValues):
            oPGRL.reference, oPGRL.points = nValue            
    PGRL = property(get_PGRL, set_PGRL) 
class WRLDRecord(BaseRecord):
    def CopyAsOverride(self, targetMod):
        FID = CBash.CopyWRLDRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(True))
        if(FID): return WRLDRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def CopyAsNew(self, targetMod):
        FID = CBash.CopyWRLDRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(False))
        if(FID): return WRLDRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def createWorldCELLRecord(self):
        FID = CBash.CreateWorldCELLRecord(self._CollectionIndex, self._ModName, self._recordID)
        if(FID): return CELLRecord(self._CollectionIndex, self._ModName, FID, self._recordID)
        return None
    def createCELLRecord(self):
        FID = CBash.CreateCELLRecord(self._CollectionIndex, self._ModName, self._recordID)
        if(FID): return CELLRecord(self._CollectionIndex, self._ModName, FID, self._recordID)
        return None
    def createROADRecord(self):
        FID = CBash.CreateROADRecord(self._CollectionIndex, self._ModName, self._recordID)
        if(FID): return ROADRecord(self._CollectionIndex, self._ModName, FID, self._recordID)
        return None

    def get_full(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 6)
    def set_full(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 6, nValue)
    full = property(get_full, set_full)
    def get_parent(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 7)
        if(retValue): return retValue.contents.value
        else: return None
    def set_parent(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 7, nValue)
    parent = property(get_parent, set_parent)
    def get_climate(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 8)
        if(retValue): return retValue.contents.value
        else: return None
    def set_climate(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 8, nValue)
    climate = property(get_climate, set_climate)
    def get_water(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 9)
        if(retValue): return retValue.contents.value
        else: return None
    def set_water(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 9, nValue)
    water = property(get_water, set_water)
    def get_mapPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 10)
    def set_mapPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 10, nValue)
    mapPath = property(get_mapPath, set_mapPath)
    def get_dimX(self):
        CBash.ReadFIDField.restype = POINTER(c_int)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 11)
        if(retValue): return retValue.contents.value
        else: return None
    def set_dimX(self, nValue):
        CBash.SetFIDFieldI(self._CollectionIndex, self._ModName, self._recordID, 11, nValue)
    dimX = property(get_dimX, set_dimX)
    def get_dimY(self):
        CBash.ReadFIDField.restype = POINTER(c_int)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 12)
        if(retValue): return retValue.contents.value
        else: return None
    def set_dimY(self, nValue):
        CBash.SetFIDFieldI(self._CollectionIndex, self._ModName, self._recordID, 12, nValue)
    dimY = property(get_dimY, set_dimY)
    def get_NWCellX(self):
        CBash.ReadFIDField.restype = POINTER(c_short)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 13)
        if(retValue): return retValue.contents.value
        else: return None
    def set_NWCellX(self, nValue):
        CBash.SetFIDFieldS(self._CollectionIndex, self._ModName, self._recordID, 13, c_short(nValue))
    NWCellX = property(get_NWCellX, set_NWCellX)
    def get_NWCellY(self):
        CBash.ReadFIDField.restype = POINTER(c_short)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 14)
        if(retValue): return retValue.contents.value
        else: return None
    def set_NWCellY(self, nValue):
        CBash.SetFIDFieldS(self._CollectionIndex, self._ModName, self._recordID, 14, c_short(nValue))
    NWCellY = property(get_NWCellY, set_NWCellY)
    def get_SECellX(self):
        CBash.ReadFIDField.restype = POINTER(c_short)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 15)
        if(retValue): return retValue.contents.value
        else: return None
    def set_SECellX(self, nValue):
        CBash.SetFIDFieldS(self._CollectionIndex, self._ModName, self._recordID, 15, c_short(nValue))
    SECellX = property(get_SECellX, set_SECellX)
    def get_SECellY(self):
        CBash.ReadFIDField.restype = POINTER(c_short)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 16)
        if(retValue): return retValue.contents.value
        else: return None
    def set_SECellY(self, nValue):
        CBash.SetFIDFieldS(self._CollectionIndex, self._ModName, self._recordID, 16, c_short(nValue))
    SECellY = property(get_SECellY, set_SECellY)
    def get_flags(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 17)
        if(retValue): return retValue.contents.value
        else: return None
    def set_flags(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 17, c_ubyte(nValue))
    flags = property(get_flags, set_flags)
    def get_unknown00(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 18)
        if(retValue): return retValue.contents.value
        else: return None
    def set_unknown00(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 18, c_float(nValue))
    unknown00 = property(get_unknown00, set_unknown00)
    def get_unknown01(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 19)
        if(retValue): return retValue.contents.value
        else: return None
    def set_unknown01(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 19, c_float(nValue))
    unknown01 = property(get_unknown01, set_unknown01)
    def get_unknown90(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 20)
        if(retValue): return retValue.contents.value
        else: return None
    def set_unknown90(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 20, c_float(nValue))
    unknown90 = property(get_unknown90, set_unknown90)
    def get_unknown91(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 21)
        if(retValue): return retValue.contents.value
        else: return None
    def set_unknown91(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 21, c_float(nValue))
    unknown91 = property(get_unknown91, set_unknown91)
    def get_sound(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 22)
        if(retValue): return retValue.contents.value
        else: return None
    def set_sound(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 22, nValue)
    sound = property(get_sound, set_sound)
    def get_ofst_p(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 23)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 23, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_ofst_p(self, nValue):
        length = len(nValue)
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 23, struct.pack('B' * length, *nValue), length)
    ofst_p = property(get_ofst_p, set_ofst_p)
    def get_ROAD(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 24)
        if(retValue): return ROADRecord(self._CollectionIndex, self._ModName, retValue.contents.value, self._recordID)
        else: return None
    def set_ROAD(self, nROAD):
        if(nROAD == None):
            return
        curROAD = self.ROAD
        if(curROAD == None):
            curROAD = self.createROADRecord()
        curROAD.PGRP = nROAD.PGRP
        curROAD.PGRR = nROAD.PGRR
    ROAD = property(get_ROAD, set_ROAD)
    def get_CELL(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 25)
        if(retValue): return CELLRecord(self._CollectionIndex, self._ModName, retValue.contents.value, self._recordID)
        else: return None
    def set_CELL(self, nCELL):
        curCELL = self.CELL
        if(curCELL == None):
            curCELL = self.createWorldCELLRecord()
        curCELL.count = nCELL.count
        curCELL.PGRP = nCELL.PGRP
        curCELL.PGAG = nCELL.PGAG
        curCELL.PGRR = nCELL.PGRR
        curCELL.PGRI = nCELL.PGRI
        curCELL.PGRL = nCELL.PGRL
    CELL = property(get_CELL, set_CELL)
    @property
    def CELLS(self):
        numSubRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 26)
        if(numSubRecords > 0):
            cRecords = (POINTER(c_uint) * numSubRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 26, byref(cRecords))
            return [CELLRecord(self._CollectionIndex, self._ModName, x.contents.value, self._recordID) for x in cRecords]
        else: return []
class ROADRecord(BaseRecord):
    def CopyAsOverride(self, targetWRLD):
        FID = CBash.CopyROADRecord(self._CollectionIndex, self._ModName, self._recordID, targetWRLD._ModName, targetWRLD._recordID, c_bool(True))
        if(FID): return ROADRecord(self._CollectionIndex, targetWRLD._ModName, FID, targetWRLD._recordID)
        return None
    def CopyAsNew(self, targetWRLD):
        FID = CBash.CopyROADRecord(self._CollectionIndex, self._ModName, self._recordID, targetWRLD._ModName, targetWRLD._recordID, c_bool(False))
        if(FID): return ROADRecord(self._CollectionIndex, targetWRLD._ModName, FID, targetWRLD._recordID)
        return None
    class PGRPRecord(object):
        def __init__(self, CollectionIndex, ModName, recordID, listIndex):
            self._CollectionIndex = CollectionIndex
            self._ModName = ModName
            self._recordID = recordID
            self._listIndex = listIndex
        def get_x(self):
            CBash.ReadFIDListField.restype = POINTER(c_float)
            retValue = CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, 6, self._listIndex, 1)
            if(retValue): return retValue.contents.value
            else: return None
        def set_x(self, nValue):
            CBash.SetFIDListFieldF(self._CollectionIndex, self._ModName, self._recordID, 6, self._listIndex, 1, c_float(nValue))
        x = property(get_x, set_x)
        def get_y(self):
            CBash.ReadFIDListField.restype = POINTER(c_float)
            retValue = CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, 6, self._listIndex, 2)
            if(retValue): return retValue.contents.value
            else: return None
        def set_y(self, nValue):
            CBash.SetFIDListFieldF(self._CollectionIndex, self._ModName, self._recordID, 6, self._listIndex, 2, c_float(nValue))
        y = property(get_y, set_y)
        def get_z(self):
            CBash.ReadFIDListField.restype = POINTER(c_float)
            retValue = CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, 6, self._listIndex, 3)
            if(retValue): return retValue.contents.value
            else: return None
        def set_z(self, nValue):
            CBash.SetFIDListFieldF(self._CollectionIndex, self._ModName, self._recordID, 6, self._listIndex, 3, c_float(nValue))
        z = property(get_z, set_z)
        def get_connections(self):
            CBash.ReadFIDListField.restype = POINTER(c_ubyte)
            retValue = CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, 6, self._listIndex, 4)
            if(retValue): return retValue.contents.value
            else: return None
        def set_connections(self, nValue):
            CBash.SetFIDListFieldUC(self._CollectionIndex, self._ModName, self._recordID, 6, self._listIndex, 4, c_ubyte(nValue))
        connections = property(get_connections, set_connections)
        def get_unused1(self):
            numRecords = CBash.GetFIDListArraySize(self._CollectionIndex, self._ModName, self._recordID, 6, self._listIndex, 5)
            if(numRecords > 0):
                cRecords = POINTER(c_ubyte * numRecords)()
                CBash.GetFIDListArray(self._CollectionIndex, self._ModName, self._recordID, 6, self._listIndex, 5, byref(cRecords))
                return [cRecords.contents[x] for x in range(0, numRecords)]
            else: return []
        def set_unused1(self, nValue):
            CBash.SetFIDListFieldR(self._CollectionIndex, self._ModName, self._recordID, 6, self._listIndex, 5, struct.pack('3B', *nValue), 3)
        unused1 = property(get_unused1, set_unused1)
    class PGRRRecord(object):
        def __init__(self, CollectionIndex, ModName, recordID, listIndex):
            self._CollectionIndex = CollectionIndex
            self._ModName = ModName
            self._recordID = recordID
            self._listIndex = listIndex
        def get_x(self):
            CBash.ReadFIDListField.restype = POINTER(c_float)
            retValue = CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, 7, self._listIndex, 1)
            if(retValue): return retValue.contents.value
            else: return None
        def set_x(self, nValue):
            CBash.SetFIDListFieldF(self._CollectionIndex, self._ModName, self._recordID, 7, self._listIndex, 1, c_float(nValue))
        x = property(get_x, set_x)
        def get_y(self):
            CBash.ReadFIDListField.restype = POINTER(c_float)
            retValue = CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, 7, self._listIndex, 2)
            if(retValue): return retValue.contents.value
            else: return None
        def set_y(self, nValue):
            CBash.SetFIDListFieldF(self._CollectionIndex, self._ModName, self._recordID, 7, self._listIndex, 2, c_float(nValue))
        y = property(get_y, set_y)
        def get_z(self):
            CBash.ReadFIDListField.restype = POINTER(c_float)
            retValue = CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, 7, self._listIndex, 3)
            if(retValue): return retValue.contents.value
            else: return None
        def set_z(self, nValue):
            CBash.SetFIDListFieldF(self._CollectionIndex, self._ModName, self._recordID, 7, self._listIndex, 3, c_float(nValue))
        z = property(get_z, set_z)

    def newPGRPElement(self):
        listIndex = CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 6)
        if(listIndex == -1): return None
        return self.PGRPRecord(self._CollectionIndex, self._ModName, self._recordID, listIndex)
    def newPGRRElement(self):
        listIndex = CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 7)
        if(listIndex == -1): return None
        return self.PGRRRecord(self._CollectionIndex, self._ModName, self._recordID, listIndex)

    def get_PGRP(self):
        numRecords = CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 6)
        if(numRecords > 0): return [self.PGRPRecord(self._CollectionIndex, self._ModName, self._recordID, x) for x in range(0, numRecords)]
        else: return []
    def set_PGRP(self, nPGRP):
        diffLength = len(nPGRP) - CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 6)
        nValues = [(nPGRPRecord.x, nPGRPRecord.y, nPGRPRecord.z, nPGRPRecord.connections, nPGRPRecord.unused1) for nPGRPRecord in nPGRP]
        while(diffLength < 0):
            CBash.DeleteFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 6)
            diffLength += 1
        while(diffLength > 0):
            CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 6)
            diffLength -= 1
        for oPGRPRecord, nValue in zip(self.PGRP, nValues):
            oPGRPRecord.x, oPGRPRecord.y, oPGRPRecord.z, oPGRPRecord.connections, oPGRPRecord.unused1 = nValue
    PGRP = property(get_PGRP, set_PGRP)
    def get_PGRR(self):
        numRecords = CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 7)
        if(numRecords > 0): return [self.PGRRRecord(self._CollectionIndex, self._ModName, self._recordID, x) for x in range(0, numRecords)]
        else: return []
    def set_PGRR(self, nPGRR):
        diffLength = len(nPGRR) - CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 7)
        nValues = [(nPGRRRecord.x, nPGRRRecord.y, nPGRRRecord.z) for nPGRRRecord in nPGRR]
        while(diffLength < 0):
            CBash.DeleteFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 7)
            diffLength += 1
        while(diffLength > 0):
            CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 7)
            diffLength -= 1
        for oPGRRRecord, nValue in zip(self.PGRR, nValues):
            oPGRRRecord.x, oPGRRRecord.y, oPGRRRecord.z = nValue
    PGRR = property(get_PGRR, set_PGRR)
class LANDRecord(BaseRecord):
    def CopyAsOverride(self, targetCELL):
        FID = CBash.CopyLANDRecord(self._CollectionIndex, self._ModName, self._recordID, targetCELL._ModName, targetCELL._recordID, c_bool(True))
        if(FID): return LANDRecord(self._CollectionIndex, targetCELL._ModName, FID, targetCELL._recordID)
        return None
    def CopyAsNew(self, targetCELL):
        FID = CBash.CopyLANDRecord(self._CollectionIndex, self._ModName, self._recordID, targetCELL._ModName, targetCELL._recordID, c_bool(False))
        if(FID): return LANDRecord(self._CollectionIndex, targetCELL._ModName, FID, targetCELL._recordID)
        return None
    class Normal(object):
        def __init__(self, CollectionIndex, ModName, recordID, listIndex, listX2Index):
            self._CollectionIndex = CollectionIndex
            self._ModName = ModName
            self._recordID = recordID
            self._listIndex = listIndex
            self._listX2Index = listX2Index
        def get_x(self):
            CBash.ReadFIDListX2Field.restype = POINTER(c_ubyte)
            retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 7, self._listIndex, 0, self._listX2Index, 1)
            if(retValue): return retValue.contents.value
            else: return None
        def set_x(self, nValue):
            CBash.SetFIDListX2FieldUC(self._CollectionIndex, self._ModName, self._recordID, 7, self._listIndex, 0, self._listX2Index, 1, c_ubyte(nValue))
        x = property(get_x, set_x)
        def get_y(self):
            CBash.ReadFIDListX2Field.restype = POINTER(c_ubyte)
            retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 7, self._listIndex, 0, self._listX2Index, 2)
            if(retValue): return retValue.contents.value
            else: return None
        def set_y(self, nValue):
            CBash.SetFIDListX2FieldUC(self._CollectionIndex, self._ModName, self._recordID, 7, self._listIndex, 0, self._listX2Index, 2, c_ubyte(nValue))
        y = property(get_y, set_y)
        def get_z(self):
            CBash.ReadFIDListX2Field.restype = POINTER(c_ubyte)
            retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 7, self._listIndex, 0, self._listX2Index, 3)
            if(retValue): return retValue.contents.value
            else: return None
        def set_z(self, nValue):
            CBash.SetFIDListX2FieldUC(self._CollectionIndex, self._ModName, self._recordID, 7, self._listIndex, 0, self._listX2Index, 3, c_ubyte(nValue))
        z = property(get_z, set_z)
    class Height(object):
        def __init__(self, CollectionIndex, ModName, recordID, listIndex, listX2Index):
            self._CollectionIndex = CollectionIndex
            self._ModName = ModName
            self._recordID = recordID
            self._listIndex = listIndex
            self._listX2Index = listX2Index
        def get_height(self):
            CBash.ReadFIDListX2Field.restype = POINTER(c_byte)
            retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 9, self._listIndex, 0, self._listX2Index, 1)
            if(retValue): return retValue.contents.value
            else: return None
        def set_height(self, nValue):
            CBash.SetFIDListX2FieldC(self._CollectionIndex, self._ModName, self._recordID, 9, self._listIndex, 0, self._listX2Index, 1, c_ubyte(nValue))
        height = property(get_height, set_height)
    class Color(object):
        def __init__(self, CollectionIndex, ModName, recordID, listIndex, listX2Index):
            self._CollectionIndex = CollectionIndex
            self._ModName = ModName
            self._recordID = recordID
            self._listIndex = listIndex
            self._listX2Index = listX2Index
        def get_red(self):
            CBash.ReadFIDListX2Field.restype = POINTER(c_ubyte)
            retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 11, self._listIndex, 0, self._listX2Index, 1)
            if(retValue): return retValue.contents.value
            else: return None
        def set_red(self, nValue):
            CBash.SetFIDListX2FieldUC(self._CollectionIndex, self._ModName, self._recordID, 11, self._listIndex, 0, self._listX2Index, 1, c_ubyte(nValue))
        red = property(get_red, set_red)
        def get_green(self):
            CBash.ReadFIDListX2Field.restype = POINTER(c_ubyte)
            retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 11, self._listIndex, 0, self._listX2Index, 2)
            if(retValue): return retValue.contents.value
            else: return None
        def set_green(self, nValue):
            CBash.SetFIDListX2FieldUC(self._CollectionIndex, self._ModName, self._recordID, 11, self._listIndex, 0, self._listX2Index, 2, c_ubyte(nValue))
        green = property(get_green, set_green)
        def get_blue(self):
            CBash.ReadFIDListX2Field.restype = POINTER(c_ubyte)
            retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 11, self._listIndex, 0, self._listX2Index, 3)
            if(retValue): return retValue.contents.value
            else: return None
        def set_blue(self, nValue):
            CBash.SetFIDListX2FieldUC(self._CollectionIndex, self._ModName, self._recordID, 11, self._listIndex, 0, self._listX2Index, 3, c_ubyte(nValue))
        blue = property(get_blue, set_blue)
    class BaseTexture(object):
        def __init__(self, CollectionIndex, ModName, recordID, subField, listIndex):
            self._CollectionIndex = CollectionIndex
            self._ModName = ModName
            self._recordID = recordID
            self._subField = subField
            self._listIndex = listIndex
        def get_texture(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            retValue = CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 1)
            if(retValue): return retValue.contents.value
            else: return None
        def set_texture(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 1, nValue)
        texture = property(get_texture, set_texture)
        def get_quadrant(self):
            CBash.ReadFIDListField.restype = POINTER(c_byte)
            retValue = CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 2)
            if(retValue): return retValue.contents.value
            else: return None
        def set_quadrant(self, nValue):
            CBash.SetFIDListFieldUC(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 2, c_byte(nValue))
        quadrant = property(get_quadrant, set_quadrant)
        def get_unused1(self):
            numRecords = CBash.GetFIDListArraySize(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 3)
            if(numRecords > 0):
                cRecords = POINTER(c_ubyte * numRecords)()
                CBash.GetFIDListArray(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 3, byref(cRecords))
                return [cRecords.contents[x] for x in range(0, numRecords)]
            else: return []
        def set_unused1(self, nValue):
            CBash.SetFIDListFieldR(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 3, struct.pack('B', *nValue), 1)
        unused1 = property(get_unused1, set_unused1)
        def get_layer(self):
            CBash.ReadFIDListField.restype = POINTER(c_short)
            retValue = CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 4)
            if(retValue): return retValue.contents.value
            else: return None
        def set_layer(self, nValue):
            CBash.SetFIDListFieldS(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 4, c_short(nValue))
        layer = property(get_layer, set_layer)
    class AlphaLayer(object):
        class Opacity(object):
            def __init__(self, CollectionIndex, ModName, recordID, listIndex, listX2Index):
                self._CollectionIndex = CollectionIndex
                self._ModName = ModName
                self._recordID = recordID
                self._listIndex = listIndex
                self._listX2Index = listX2Index
            def get_position(self):
                CBash.ReadFIDListX2Field.restype = POINTER(c_ushort)
                retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5, self._listX2Index, 1)
                if(retValue): return retValue.contents.value
                else: return None
            def set_position(self, nValue):
                CBash.SetFIDListX2FieldUS(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5, self._listX2Index, 1, c_ushort(nValue))
            position = property(get_position, set_position)
            def get_unused1(self):
                numRecords = CBash.GetFIDListX2ArraySize(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5, self._listX2Index, 2)
                if(numRecords > 0):
                    cRecords = POINTER(c_ubyte * numRecords)()
                    CBash.GetFIDListX2Array(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5, self._listX2Index, 2, byref(cRecords))
                    return [cRecords.contents[x] for x in range(0, numRecords)]
                else: return []
            def set_unused1(self, nValue):
                CBash.SetFIDListX2FieldR(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5, self._listX2Index, 2, struct.pack('2B', *nValue), 2)
            unused1 = property(get_unused1, set_unused1)
            def get_opacity(self):
                CBash.ReadFIDListX2Field.restype = POINTER(c_float)
                retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5, self._listX2Index, 3)
                if(retValue): return retValue.contents.value
                else: return None
            def set_opacity(self, nValue):
                CBash.SetFIDListX2FieldF(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5, self._listX2Index, 3, c_float(nValue))
            opacity = property(get_opacity, set_opacity)
        def __init__(self, CollectionIndex, ModName, recordID, subField, listIndex):
            self._CollectionIndex = CollectionIndex
            self._ModName = ModName
            self._recordID = recordID
            self._subField = subField
            self._listIndex = listIndex
        def newOpacitiesElement(self):
            listX2Index = CBash.CreateFIDListX2Element(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 5)
            if(listX2Index == -1): return None
            return self.Opacity(self._CollectionIndex, self._ModName, self._recordID, self._listIndex, listX2Index)
        def get_texture(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            retValue = CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 1)
            if(retValue): return retValue.contents.value
            else: return None
        def set_texture(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 1, nValue)
        texture = property(get_texture, set_texture)
        def get_quadrant(self):
            CBash.ReadFIDListField.restype = POINTER(c_byte)
            retValue = CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 2)
            if(retValue): return retValue.contents.value
            else: return None
        def set_quadrant(self, nValue):
            CBash.SetFIDListFieldUC(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 2, c_byte(nValue))
        quadrant = property(get_quadrant, set_quadrant)
        def get_unused1(self):
            numRecords = CBash.GetFIDListArraySize(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 3)
            if(numRecords > 0):
                cRecords = POINTER(c_ubyte * numRecords)()
                CBash.GetFIDListArray(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 3, byref(cRecords))
                return [cRecords.contents[x] for x in range(0, numRecords)]
            else: return []
        def set_unused1(self, nValue):
            CBash.SetFIDListFieldR(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 3, struct.pack('B', *nValue), 1)
        unused1 = property(get_unused1, set_unused1)
        def get_layer(self):
            CBash.ReadFIDListField.restype = POINTER(c_short)
            retValue = CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 4)
            if(retValue): return retValue.contents.value
            else: return None
        def set_layer(self, nValue):
            CBash.SetFIDListFieldS(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 4, c_short(nValue))
        layer = property(get_layer, set_layer)
        def get_opacities(self):
            numRecords = CBash.GetFIDListX2Size(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 5)
            if(numRecords > 0): return [self.Opacity(self._CollectionIndex, self._ModName, self._recordID, self._listIndex, x) for x in range(0, numRecords)]
            else: return []
        def set_opacities(self, nOpacities):
            diffLength = len(nOpacities) - CBash.GetFIDListX2Size(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 5)
            nValues = [(nOpacity.position, nOpacity.unused1, nOpacity.opacity) for nOpacity in nOpacities]
            while(diffLength < 0):
                CBash.DeleteFIDListX2Element(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 5)
                diffLength += 1
            while(diffLength > 0):
                CBash.CreateFIDListX2Element(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 5)
                diffLength -= 1
            for oOpacity, nValue in zip(self.opacities, nValues):
                oOpacity.position, oOpacity.unused1, oOpacity.opacity = nValue
        opacities = property(get_opacities, set_opacities)
    class VertexTexture(object):
        def __init__(self, CollectionIndex, ModName, recordID, subField, listIndex):
            self._CollectionIndex = CollectionIndex
            self._ModName = ModName
            self._recordID = recordID
            self._subField = subField
            self._listIndex = listIndex
        def get_texture(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            retValue = CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 1)
            if(retValue): return retValue.contents.value
            else: return None
        def set_texture(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 1, nValue)
        texture = property(get_texture, set_texture)
    class Positions(object):
        def __init__(self, CollectionIndex, ModName, recordID, listIndex, listX2Index):
            self._CollectionIndex = CollectionIndex
            self._ModName = ModName
            self._recordID = recordID
            self._listIndex = listIndex
            self._listX2Index = listX2Index
        def get_height(self):
            CBash.ReadFIDListX2Field.restype = POINTER(c_float)
            retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 15, self._listIndex, 0, self._listX2Index, 1)
            if(retValue): return retValue.contents.value
            else: return None
        def set_height(self, nValue):
            CBash.SetFIDListX2FieldF(self._CollectionIndex, self._ModName, self._recordID, 15, self._listIndex, 0, self._listX2Index, 1, c_float(nValue))
        height = property(get_height, set_height)
        def get_normalX(self):
            CBash.ReadFIDListX2Field.restype = POINTER(c_ubyte)
            retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 15, self._listIndex, 0, self._listX2Index, 2)
            if(retValue): return retValue.contents.value
            else: return None
        def set_normalX(self, nValue):
            CBash.SetFIDListX2FieldUC(self._CollectionIndex, self._ModName, self._recordID, 15, self._listIndex, 0, self._listX2Index, 2, c_ubyte(nValue))
        normalX = property(get_normalX, set_normalX)
        def get_normalY(self):
            CBash.ReadFIDListX2Field.restype = POINTER(c_ubyte)
            retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 15, self._listIndex, 0, self._listX2Index, 3)
            if(retValue): return retValue.contents.value
            else: return None
        def set_normalY(self, nValue):
            CBash.SetFIDListX2FieldUC(self._CollectionIndex, self._ModName, self._recordID, 15, self._listIndex, 0, self._listX2Index, 3, c_ubyte(nValue))
        normalY = property(get_normalY, set_normalY)
        def get_normalZ(self):
            CBash.ReadFIDListX2Field.restype = POINTER(c_ubyte)
            retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 15, self._listIndex, 0, self._listX2Index, 4)
            if(retValue): return retValue.contents.value
            else: return None
        def set_normalZ(self, nValue):
            CBash.SetFIDListX2FieldUC(self._CollectionIndex, self._ModName, self._recordID, 15, self._listIndex, 0, self._listX2Index, 4, c_ubyte(nValue))
        normalZ = property(get_normalZ, set_normalZ)
        def get_red(self):
            CBash.ReadFIDListX2Field.restype = POINTER(c_ubyte)
            retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 15, self._listIndex, 0, self._listX2Index, 5)
            if(retValue): return retValue.contents.value
            else: return None
        def set_red(self, nValue):
            CBash.SetFIDListX2FieldUC(self._CollectionIndex, self._ModName, self._recordID, 15, self._listIndex, 0, self._listX2Index, 5, c_ubyte(nValue))
        red = property(get_red, set_red)
        def get_green(self):
            CBash.ReadFIDListX2Field.restype = POINTER(c_ubyte)
            retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 15, self._listIndex, 0, self._listX2Index, 6)
            if(retValue): return retValue.contents.value
            else: return None
        def set_green(self, nValue):
            CBash.SetFIDListX2FieldUC(self._CollectionIndex, self._ModName, self._recordID, 15, self._listIndex, 0, self._listX2Index, 6, c_ubyte(nValue))
        green = property(get_green, set_green)
        def get_blue(self):
            CBash.ReadFIDListX2Field.restype = POINTER(c_ubyte)
            retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 15, self._listIndex, 0, self._listX2Index, 7)
            if(retValue): return retValue.contents.value
            else: return None
        def set_blue(self, nValue):
            CBash.SetFIDListX2FieldUC(self._CollectionIndex, self._ModName, self._recordID, 15, self._listIndex, 0, self._listX2Index, 7, c_ubyte(nValue))
        blue = property(get_blue, set_blue)
        def get_baseTexture(self):
            CBash.ReadFIDListX2Field.restype = POINTER(c_uint)
            retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 15, self._listIndex, 0, self._listX2Index, 8)
            if(retValue): return retValue.contents.value
            else: return None
        def set_baseTexture(self, nValue):
            CBash.SetFIDListX2FieldUI(self._CollectionIndex, self._ModName, self._recordID, 15, self._listIndex, 0, self._listX2Index, 8, nValue)
        baseTexture = property(get_baseTexture, set_baseTexture)
        def get_layer1Texture(self):
            CBash.ReadFIDListX2Field.restype = POINTER(c_uint)
            retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 15, self._listIndex, 0, self._listX2Index, 9)
            if(retValue): return retValue.contents.value
            else: return None
        def set_layer1Texture(self, nValue):
            CBash.SetFIDListX2FieldUI(self._CollectionIndex, self._ModName, self._recordID, 15, self._listIndex, 0, self._listX2Index, 9, nValue)
        layer1Texture = property(get_layer1Texture, set_layer1Texture)
        def get_layer1Opacity(self):
            CBash.ReadFIDListX2Field.restype = POINTER(c_float)
            retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 15, self._listIndex, 0, self._listX2Index, 10)
            if(retValue): return retValue.contents.value
            else: return None
        def set_layer1Opacity(self, nValue):
            CBash.SetFIDListX2FieldF(self._CollectionIndex, self._ModName, self._recordID, 15, self._listIndex, 0, self._listX2Index, 10, c_float(nValue))
        layer1Opacity = property(get_layer1Opacity, set_layer1Opacity)
        def get_layer2Texture(self):
            CBash.ReadFIDListX2Field.restype = POINTER(c_uint)
            retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 15, self._listIndex, 0, self._listX2Index, 11)
            if(retValue): return retValue.contents.value
            else: return None
        def set_layer2Texture(self, nValue):
            CBash.SetFIDListX2FieldUI(self._CollectionIndex, self._ModName, self._recordID, 15, self._listIndex, 0, self._listX2Index, 11, nValue)
        layer2Texture = property(get_layer2Texture, set_layer2Texture)
        def get_layer2Opacity(self):
            CBash.ReadFIDListX2Field.restype = POINTER(c_float)
            retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 15, self._listIndex, 0, self._listX2Index, 12)
            if(retValue): return retValue.contents.value
            else: return None
        def set_layer2Opacity(self, nValue):
            CBash.SetFIDListX2FieldF(self._CollectionIndex, self._ModName, self._recordID, 15, self._listIndex, 0, self._listX2Index, 12, c_float(nValue))
        layer2Opacity = property(get_layer2Opacity, set_layer2Opacity)
        def get_layer3Texture(self):
            CBash.ReadFIDListX2Field.restype = POINTER(c_uint)
            retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 15, self._listIndex, 0, self._listX2Index, 13)
            if(retValue): return retValue.contents.value
            else: return None
        def set_layer3Texture(self, nValue):
            CBash.SetFIDListX2FieldUI(self._CollectionIndex, self._ModName, self._recordID, 15, self._listIndex, 0, self._listX2Index, 13, nValue)
        layer3Texture = property(get_layer3Texture, set_layer3Texture)
        def get_layer3Opacity(self):
            CBash.ReadFIDListX2Field.restype = POINTER(c_float)
            retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 15, self._listIndex, 0, self._listX2Index, 14)
            if(retValue): return retValue.contents.value
            else: return None
        def set_layer3Opacity(self, nValue):
            CBash.SetFIDListX2FieldF(self._CollectionIndex, self._ModName, self._recordID, 15, self._listIndex, 0, self._listX2Index, 14, c_float(nValue))
        layer3Opacity = property(get_layer3Opacity, set_layer3Opacity)
        def get_layer4Texture(self):
            CBash.ReadFIDListX2Field.restype = POINTER(c_uint)
            retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 15, self._listIndex, 0, self._listX2Index, 15)
            if(retValue): return retValue.contents.value
            else: return None
        def set_layer4Texture(self, nValue):
            CBash.SetFIDListX2FieldUI(self._CollectionIndex, self._ModName, self._recordID, 15, self._listIndex, 0, self._listX2Index, 15, nValue)
        layer4Texture = property(get_layer4Texture, set_layer4Texture)
        def get_layer4Opacity(self):
            CBash.ReadFIDListX2Field.restype = POINTER(c_float)
            retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 15, self._listIndex, 0, self._listX2Index, 16)
            if(retValue): return retValue.contents.value
            else: return None
        def set_layer4Opacity(self, nValue):
            CBash.SetFIDListX2FieldF(self._CollectionIndex, self._ModName, self._recordID, 15, self._listIndex, 0, self._listX2Index, 16, c_float(nValue))
        layer4Opacity = property(get_layer4Opacity, set_layer4Opacity)
        def get_layer5Texture(self):
            CBash.ReadFIDListX2Field.restype = POINTER(c_uint)
            retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 15, self._listIndex, 0, self._listX2Index, 17)
            if(retValue): return retValue.contents.value
            else: return None
        def set_layer5Texture(self, nValue):
            CBash.SetFIDListX2FieldUI(self._CollectionIndex, self._ModName, self._recordID, 15, self._listIndex, 0, self._listX2Index, 17, nValue)
        layer5Texture = property(get_layer5Texture, set_layer5Texture)
        def get_layer5Opacity(self):
            CBash.ReadFIDListX2Field.restype = POINTER(c_float)
            retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 15, self._listIndex, 0, self._listX2Index, 18)
            if(retValue): return retValue.contents.value
            else: return None
        def set_layer5Opacity(self, nValue):
            CBash.SetFIDListX2FieldF(self._CollectionIndex, self._ModName, self._recordID, 15, self._listIndex, 0, self._listX2Index, 18, c_float(nValue))
        layer5Opacity = property(get_layer5Opacity, set_layer5Opacity)
        def get_layer6Texture(self):
            CBash.ReadFIDListX2Field.restype = POINTER(c_uint)
            retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 15, self._listIndex, 0, self._listX2Index, 19)
            if(retValue): return retValue.contents.value
            else: return None
        def set_layer6Texture(self, nValue):
            CBash.SetFIDListX2FieldUI(self._CollectionIndex, self._ModName, self._recordID, 15, self._listIndex, 0, self._listX2Index, 19, nValue)
        layer6Texture = property(get_layer6Texture, set_layer6Texture)
        def get_layer6Opacity(self):
            CBash.ReadFIDListX2Field.restype = POINTER(c_float)
            retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 15, self._listIndex, 0, self._listX2Index, 20)
            if(retValue): return retValue.contents.value
            else: return None
        def set_layer6Opacity(self, nValue):
            CBash.SetFIDListX2FieldF(self._CollectionIndex, self._ModName, self._recordID, 15, self._listIndex, 0, self._listX2Index, 20, c_float(nValue))
        layer6Opacity = property(get_layer6Opacity, set_layer6Opacity)
        def get_layer7Texture(self):
            CBash.ReadFIDListX2Field.restype = POINTER(c_uint)
            retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 15, self._listIndex, 0, self._listX2Index, 21)
            if(retValue): return retValue.contents.value
            else: return None
        def set_layer7Texture(self, nValue):
            CBash.SetFIDListX2FieldUI(self._CollectionIndex, self._ModName, self._recordID, 15, self._listIndex, 0, self._listX2Index, 21, nValue)
        layer7Texture = property(get_layer7Texture, set_layer7Texture)
        def get_layer7Opacity(self):
            CBash.ReadFIDListX2Field.restype = POINTER(c_float)
            retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 15, self._listIndex, 0, self._listX2Index, 22)
            if(retValue): return retValue.contents.value
            else: return None
        def set_layer7Opacity(self, nValue):
            CBash.SetFIDListX2FieldF(self._CollectionIndex, self._ModName, self._recordID, 15, self._listIndex, 0, self._listX2Index, 22, c_float(nValue))
        layer7Opacity = property(get_layer7Opacity, set_layer7Opacity)
        def get_layer8Texture(self):
            CBash.ReadFIDListX2Field.restype = POINTER(c_uint)
            retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 15, self._listIndex, 0, self._listX2Index, 23)
            if(retValue): return retValue.contents.value
            else: return None
        def set_layer8Texture(self, nValue):
            CBash.SetFIDListX2FieldUI(self._CollectionIndex, self._ModName, self._recordID, 15, self._listIndex, 0, self._listX2Index, 23, nValue)
        layer8Texture = property(get_layer8Texture, set_layer8Texture)
        def get_layer8Opacity(self):
            CBash.ReadFIDListX2Field.restype = POINTER(c_float)
            retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 15, self._listIndex, 0, self._listX2Index, 24)
            if(retValue): return retValue.contents.value
            else: return None
        def set_layer8Opacity(self, nValue):
            CBash.SetFIDListX2FieldF(self._CollectionIndex, self._ModName, self._recordID, 15, self._listIndex, 0, self._listX2Index, 24, c_float(nValue))
        layer8Opacity = property(get_layer8Opacity, set_layer8Opacity)


        
    def newBaseTexturesElement(self):
        listIndex = CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 12)
        if(listIndex == -1): return None
        return self.BaseTexture(self._CollectionIndex, self._ModName, self._recordID, 12, listIndex)
    def newAlphaLayersElement(self):
        listIndex = CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 13)
        if(listIndex == -1): return None
        return self.AlphaLayer(self._CollectionIndex, self._ModName, self._recordID, 13, listIndex)
    def newVertexTexturesElement(self):
        listIndex = CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 14)
        if(listIndex == -1): return None
        return self.VertexTexture(self._CollectionIndex, self._ModName, self._recordID, 14, listIndex)
    def get_data(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 6)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 6, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_data(self, nValue):
        length = len(nValue)
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 6, struct.pack('B' * length, *nValue), length)
    data = property(get_data, set_data)
    def get_normals(self):
        return [[self.Normal(self._CollectionIndex, self._ModName, self._recordID, x, y) for y in range(0,33)] for x in range(0,33)]
    def set_normals(self, nNormals):
        if(len(nNormals) != 33):
            return
        nValues = [(nNormal.x, nNormal.y, nNormal.z) for nNormal in nNormals]
        for oNormal, nValue in zip(self.normals, nValues):
            oNormal.x, oNormal.y, oNormal.z = nValue
    normals = property(get_normals, set_normals)
    def get_heights(self):
        return [[self.Height(self._CollectionIndex, self._ModName, self._recordID, x, y) for y in range(0,33)] for x in range(0,33)]
    def set_heights(self, nHeights):
        if(len(nNormals) != 33):
            return
        nValues = [nHeight.height for nHeight in nHeights]
        for oHeight, nValue in zip(self.heights, nValues):
            oHeight.height = nValue
    heights = property(get_heights, set_heights)
    def get_heightOffset(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 8)
        if(retValue): return retValue.contents.value
        else: return None
    def set_heightOffset(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 8, c_float(nValue))
    heightOffset = property(get_heightOffset, set_heightOffset)
    def get_unused1(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 10)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 10, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_unused1(self, nValue):
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 10, struct.pack('3B', *nValue), 3)
    unused1 = property(get_unused1, set_unused1)
    def get_colors(self):
        return [[self.Color(self._CollectionIndex, self._ModName, self._recordID, x, y)for y in range(0,33)]for x in range(0,33)]
    def set_colors(self, nColors):
        if(len(nColors) != 33):
            return
        nValues = [(nColor.red, nColor.green, nColor.blue) for nColor in nColors]
        for oColor, nValue in zip(self.colors, nValues):
            oColor.red, oColor.green, oColor.blue = nValue
    colors = property(get_colors, set_colors)
    def get_baseTextures(self):
        numRecords = CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 12)
        if(numRecords > 0): return [self.BaseTexture(self._CollectionIndex, self._ModName, self._recordID, 12, x) for x in range(0, numRecords)]
        else: return []
    def set_baseTextures(self, nBaseTextures):
        diffLength = len(nBaseTextures) - CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 12)
        nValues = [(nBaseTexture.texture, nBaseTexture.quadrant, nBaseTexture.unused1, nBaseTexture.layer) for nBaseTexture in nBaseTextures]
        while(diffLength < 0):
            CBash.DeleteFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 12)
            diffLength += 1
        while(diffLength > 0):
            CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 12)
            diffLength -= 1
        for oBaseTexture, nValue in zip(self.baseTextures, nValues):
            oBaseTexture.texture, oBaseTexture.quadrant, oBaseTexture.unused1, oBaseTexture.layer = nValue
    baseTextures = property(get_baseTextures, set_baseTextures)
    def get_alphaLayers(self):
        numRecords = CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 13)
        if(numRecords > 0): return [self.AlphaLayer(self._CollectionIndex, self._ModName, self._recordID, 13, x) for x in range(0, numRecords)]
        else: return []
    def set_alphaLayers(self, nAlphaLayers):
        diffLength = len(nAlphaLayers) - CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 13)
        nValues = [(nAlphaLayer.texture, nAlphaLayer.quadrant, nAlphaLayer.unused1, nAlphaLayer.layer,
                  [(nOpacity.position, nOpacity.unused1, nOpacity.opacity) for nOpacity in nAlphaLayer.opacities]) for nAlphaLayer in nAlphaLayers]
        while(diffLength < 0):
            CBash.DeleteFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 13)
            diffLength += 1
        while(diffLength > 0):
            CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 13)
            diffLength -= 1
        for oAlphaLayer, nValue in zip(self.alphaLayers, nValues):
            oAlphaLayer.texture = nValue[0]
            oAlphaLayer.quadrant = nValue[1]
            oAlphaLayer.unused1 = nValue[2]
            oAlphaLayer.layer = nValue[3]
            diffLength = len(nValue[4]) - CBash.GetFIDListX2Size(self._CollectionIndex, self._ModName, self._recordID, 13, oTarget._listIndex, 5)
            while(diffLength < 0):
                CBash.DeleteFIDListX2Element(self._CollectionIndex, self._ModName, self._recordID, 13, oTarget._listIndex, 5)
                diffLength += 1
            while(diffLength > 0):
                CBash.CreateFIDListX2Element(self._CollectionIndex, self._ModName, self._recordID, 13, oTarget._listIndex, 5)
                diffLength -= 1
            for oOpacity, eValue in zip(oAlphaLayer.opacities, nValue[4]):
                oOpacity.position, oOpacity.unused1, oOpacity.opacity = eValue
    alphaLayers = property(get_alphaLayers, set_alphaLayers)
    def get_vertexTextures(self):
        numRecords = CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 14)
        if(numRecords > 0): return [self.BaseTexture(self._CollectionIndex, self._ModName, self._recordID, 14, x) for x in range(0, numRecords)]
        else: return []
    def set_vertexTextures(self, nVertexTextures):
        diffLength = len(nVertexTextures) - CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 14)
        nValues = [nVertexTexture.texture for nVertexTexture in nVertexTextures]
        while(diffLength < 0):
            CBash.DeleteFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 14)
            diffLength += 1
        while(diffLength > 0):
            CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 14)
            diffLength -= 1
        for oVertexTexture, nValue in zip(self.vertexTextures, nValues):
            oVertexTexture.texture = nValue
    vertexTextures = property(get_vertexTextures, set_vertexTextures)
    def get_positions(self):
        return [[self.Positions(self._CollectionIndex, self._ModName, self._recordID, row, column) for column in range(0,33)] for row in range(0,33)]
    def set_positions(self, nPositions):
        if(len(nPositions) != 33):
            return
        nValues = [(nPosition.height, nPosition.normalX, nPosition.normalY, nPosition.normalZ, nPosition.red, nPosition.green,
                    nPosition.blue, nPosition.baseTexture, nPosition.layer1Texture, nPosition.layer1Opacity, nPosition.layer2Texture, nPosition.layer2Opacity,
                    nPosition.layer3Texture, nPosition.layer3Opacity, nPosition.layer4Texture, nPosition.layer4Opacity, nPosition.layer5Texture, nPosition.layer5Opacity,
                    nPosition.layer6Texture, nPosition.layer6Opacity, nPosition.layer7Texture, nPosition.layer7Opacity, nPosition.layer8Texture, nPosition.layer8Opacity) for nPosition in nPositions]
        for oPosition, nValue in zip(self.Position, nValues):
            oPosition.height, oPosition.normalX, oPosition.normalY, oPosition.normalZ, oPosition.red, oPosition.green,
            oPosition.blue, oPosition.baseTexture, oPosition.layer1Texture, oPosition.layer1Opacity, oPosition.layer2Texture, oPosition.layer2Opacity,
            oPosition.layer3Texture, oPosition.layer3Opacity, oPosition.layer4Texture, oPosition.layer4Opacity, oPosition.layer5Texture, oPosition.layer5Opacity,
            oPosition.layer6Texture, oPosition.layer6Opacity, oPosition.layer7Texture, oPosition.layer7Opacity, oPosition.layer8Texture, oPosition.layer8Opacity = nValue
    Position = property(get_positions, set_positions)

class DIALRecord(BaseRecord):
    def CopyAsOverride(self, targetMod):
        FID = CBash.CopyDIALRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(True))
        if(FID): return DIALRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def CopyAsNew(self, targetMod):
        FID = CBash.CopyDIALRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(False))
        if(FID): return DIALRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def createINFORecord(self):
        FID = CBash.CreateINFORecord(self._CollectionIndex, self._ModName, self._recordID)
        if(FID): return INFORecord(self._CollectionIndex, self._ModName, FID, self._recordID)
        return None
    def get_quests(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 6)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 6, byref(cRecords))
            return [cRecords[x].contents.value for x in range(0, numRecords)]
        else: return []
    def set_quests(self, nValue):
        CBash.SetFIDFieldUIA(self._CollectionIndex, self._ModName, self._recordID, 6, struct.pack('I' * len(nValue), *nValue), len(nValue))
    quests = property(get_quests, set_quests)
    def get_full(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 7)
    def set_full(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 7, nValue)
    full = property(get_full, set_full)
    def get_dialType(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 8)
        if(retValue): return retValue.contents.value
        else: return None
    def set_dialType(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 8, c_ubyte(nValue))
    dialType = property(get_dialType, set_dialType)
    @property
    def INFO(self):
        numSubRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 9)
        if(numSubRecords > 0):
            cRecords = (POINTER(c_uint) * numSubRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 9, byref(cRecords))
            return [INFORecord(self._CollectionIndex, self._ModName, x.contents.value, self._recordID) for x in cRecords]
        else: return []
class INFORecord(BaseRecord):
    def CopyAsOverride(self, targetDIAL):
        FID = CBash.CopyINFORecord(self._CollectionIndex, self._ModName, self._recordID, targetDIAL._ModName, targetDIAL._recordID, c_bool(True))
        if(FID): return INFORecord(self._CollectionIndex, targetDIAL._ModName, FID, targetDIAL._recordID)
        return None
    def CopyAsNew(self, targetDIAL):
        FID = CBash.CopyINFORecord(self._CollectionIndex, self._ModName, self._recordID, targetDIAL._ModName, targetDIAL._recordID, c_bool(False))
        if(FID): return INFORecord(self._CollectionIndex, targetDIAL._ModName, FID, targetDIAL._recordID)
        return None
    class Response(object):
        def __init__(self, CollectionIndex, ModName, recordID, listIndex):
            self._CollectionIndex = CollectionIndex
            self._ModName = ModName
            self._recordID = recordID
            self._listIndex = listIndex
        def get_emotionType(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            retValue = CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 1)
            if(retValue): return retValue.contents.value
            else: return None
        def set_emotionType(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 1, nValue)
        emotionType = property(get_emotionType, set_emotionType)
        def get_emotionValue(self):
            CBash.ReadFIDListField.restype = POINTER(c_int)
            retValue = CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 2)
            if(retValue): return retValue.contents.value
            else: return None
        def set_emotionValue(self, nValue):
            CBash.SetFIDListFieldI(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 2, nValue)
        emotionValue = property(get_emotionValue, set_emotionValue)
        def get_unused1(self):
            numRecords = CBash.GetFIDListArraySize(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 3)
            if(numRecords > 0):
                cRecords = POINTER(c_ubyte * numRecords)()
                CBash.GetFIDListArray(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 3, byref(cRecords))
                return [cRecords.contents[x] for x in range(0, numRecords)]
            else: return []
        def set_unused1(self, nValue):
            CBash.SetFIDListFieldR(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 3, struct.pack('4B', *nValue), 4)
        unused1 = property(get_unused1, set_unused1)
        def get_responseNum(self):
            CBash.ReadFIDListField.restype = POINTER(c_ubyte)
            retValue = CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 4)
            if(retValue): return retValue.contents.value
            else: return None
        def set_responseNum(self, nValue):
            CBash.SetFIDListFieldUC(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 4, c_ubyte(nValue))
        responseNum = property(get_responseNum, set_responseNum)
        def get_unused2(self):
            numRecords = CBash.GetFIDListArraySize(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5)
            if(numRecords > 0):
                cRecords = POINTER(c_ubyte * numRecords)()
                CBash.GetFIDListArray(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5, byref(cRecords))
                return [cRecords.contents[x] for x in range(0, numRecords)]
            else: return []
        def set_unused2(self, nValue):
            CBash.SetFIDListFieldR(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 5, struct.pack('3B', *nValue), 3)
        unused2 = property(get_unused2, set_unused2)
        def get_responseText(self):
            CBash.ReadFIDListField.restype = c_char_p
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 6)
        def set_responseText(self, nValue):
            CBash.SetFIDListFieldStr(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 6, nValue)
        responseText = property(get_responseText, set_responseText)
        def get_actorNotes(self):
            CBash.ReadFIDListField.restype = c_char_p
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 7)
        def set_actorNotes(self, nValue):
            CBash.SetFIDListFieldStr(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 7, nValue)
        actorNotes = property(get_actorNotes, set_actorNotes)
    class Condition(object):
        def __init__(self, CollectionIndex, ModName, recordID, subField, listIndex):
            self._CollectionIndex = CollectionIndex
            self._ModName = ModName
            self._recordID = recordID
            self._subField = subField
            self._listIndex = listIndex
        def get_operType(self):
            CBash.ReadFIDListField.restype = POINTER(c_ubyte)
            retValue = CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 1)
            if(retValue): return retValue.contents.value
            else: return None
        def set_operType(self, nValue):
            CBash.SetFIDListFieldUC(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 1, c_ubyte(nValue))
        operType = property(get_operType, set_operType)
        def get_unused1(self):
            numRecords = CBash.GetFIDListArraySize(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 2)
            if(numRecords > 0):
                cRecords = POINTER(c_ubyte * numRecords)()
                CBash.GetFIDListArray(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 2, byref(cRecords))
                return [cRecords.contents[x] for x in range(0, numRecords)]
            else: return []
        def set_unused1(self, nValue):
            CBash.SetFIDListFieldR(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 2, struct.pack('3B', *nValue), 3)
        unused1 = property(get_unused1, set_unused1)
        def get_compValue(self):
            CBash.ReadFIDListField.restype = POINTER(c_float)
            retValue = CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 3)
            if(retValue): return retValue.contents.value
            else: return None
        def set_compValue(self, nValue):
            CBash.SetFIDListFieldF(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 3, c_float(nValue))
        compValue = property(get_compValue, set_compValue)
        def get_ifunc(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            retValue = CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 4)
            if(retValue): return retValue.contents.value
            else: return None
        def set_ifunc(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 4, nValue)
        ifunc = property(get_ifunc, set_ifunc)
        def get_param1(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            retValue = CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 5)
            if(retValue): return retValue.contents.value
            else: return None
        def set_param1(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 5, nValue)
        param1 = property(get_param1, set_param1)
        def get_param2(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            retValue = CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 6)
            if(retValue): return retValue.contents.value
            else: return None
        def set_param2(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 6, nValue)
        param2 = property(get_param2, set_param2)
        def get_unused2(self):
            numRecords = CBash.GetFIDListArraySize(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 7)
            if(numRecords > 0):
                cRecords = POINTER(c_ubyte * numRecords)()
                CBash.GetFIDListArray(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 7, byref(cRecords))
                return [cRecords.contents[x] for x in range(0, numRecords)]
            else: return []
        def set_unused2(self, nValue):
            CBash.SetFIDListFieldR(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 7, struct.pack('4B', *nValue), 4)
        unused2 = property(get_unused2, set_unused2)
    class Reference(object):
        def __init__(self, CollectionIndex, ModName, recordID, listIndex):
            self._CollectionIndex = CollectionIndex
            self._ModName = ModName
            self._recordID = recordID
            self._listIndex = listIndex
        def get_reference(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, 24, self._listIndex, 1).contents.value
        def set_reference(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, 24, self._listIndex, 1, nValue)
        reference = property(get_reference, set_reference)
        def get_isSCRO(self):
            CBash.ReadFIDListField.restype = POINTER(c_bool)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, 24, self._listIndex, 2).contents.value
        def set_isSCRO(self, nValue):
            if isinstance(nValue, bool):
                if(nValue): CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, 25, self._listIndex, 2, 1)
                else: CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, 25, self._listIndex, 2, 0)
            else: CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, 24, self._listIndex, 2, nValue)
        isSCRO = property(get_isSCRO, set_isSCRO)
    def newResponsesElement(self):
        listIndex = CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 13)
        print listIndex
        if(listIndex == -1): return None
        return self.Response(self._CollectionIndex, self._ModName, self._recordID, listIndex)
    def newConditionsElement(self):
        listIndex = CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 14)
        if(listIndex == -1): return None
        return self.Condition(self._CollectionIndex, self._ModName, self._recordID, 14, listIndex)
    def newReferencesElement(self):
        listIndex = CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 24)
        if(listIndex == -1): return None
        return self.Reference(self._CollectionIndex, self._ModName, self._recordID, listIndex) 
    def get_dialType(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 6)
        if(retValue): return retValue.contents.value
        else: return None
    def set_dialType(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 6, c_ubyte(nValue))
    dialType = property(get_dialType, set_dialType)
    def get_flags(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 7)
        if(retValue): return retValue.contents.value
        else: return None
    def set_flags(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 7, c_ubyte(nValue))
    flags = property(get_flags, set_flags)
    def get_unused1(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 8)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 8, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_unused1(self, nValue):
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 8, struct.pack('B', *nValue), 1)
    unused1 = property(get_unused1, set_unused1)
    def get_quest(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 9)
        if(retValue): return retValue.contents.value
        else: return None
    def set_quest(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 9, nValue)
    quest = property(get_quest, set_quest)
    def get_topic(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 10)
        if(retValue): return retValue.contents.value
        else: return None
    def set_topic(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 10, nValue)
    topic = property(get_topic, set_topic)
    def get_prevInfo(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 11)
        if(retValue): return retValue.contents.value
        else: return None
    def set_prevInfo(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 11, nValue)
    prevInfo = property(get_prevInfo, set_prevInfo)
    def get_addTopics(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 12)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 12, byref(cRecords))
            return [cRecords[x].contents.value for x in range(0, numRecords)]
        else: return []
    def set_addTopics(self, nValue):
        CBash.SetFIDFieldUIA(self._CollectionIndex, self._ModName, self._recordID, 12, struct.pack('I' * len(nValue), *nValue), len(nValue))
    addTopics = property(get_addTopics, set_addTopics)
    def get_responses(self):
        numRecords = CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 13)
        if(numRecords > 0): return [self.Response(self._CollectionIndex, self._ModName, self._recordID, x) for x in range(0, numRecords)]
        else: return []
    def set_responses(self, nResponses):
        diffLength = len(nResponses) - CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 13)
        nValues = [(nResponse.emotionType, nResponse.emotionValue, nResponse.unused1, nResponse.responseNum, nResponse.unused2, nResponse.responseText, nResponse.actorNotes) for nResponse in nResponses]
        while(diffLength < 0):
            CBash.DeleteFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 13)
            diffLength += 1
        while(diffLength > 0):
            CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 13)
            diffLength -= 1
        for oResponse, nValue in zip(self.responses, nValues):
            oResponse.emotionType, oResponse.emotionValue, oResponse.unused1, oResponse.responseNum, oResponse.unused2, oResponse.responseText, oResponse.actorNotes = nValue
    responses = property(get_responses, set_responses)    
    def get_conditions(self):
        numRecords = CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 14)
        if(numRecords > 0): return [self.Condition(self._CollectionIndex, self._ModName, self._recordID, 14, x) for x in range(0, numRecords)]
        else: return []
    def set_conditions(self, nConditions):
        diffLength = len(nConditions) - CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 14)
        nValues = [(nCondition.operType, nCondition.unused1, nCondition.compValue, nCondition.ifunc, nCondition.param1, nCondition.param2, nCondition.unused2) for nCondition in nConditions]
        while(diffLength < 0):
            CBash.DeleteFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 14)
            diffLength += 1
        while(diffLength > 0):
            CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 14)
            diffLength -= 1
        for oCondition, nValue in zip(self.conditions, nValues):
            oCondition.operType, oCondition.unused1, oCondition.compValue, oCondition.ifunc, oCondition.param1, oCondition.param2, oCondition.unused2 = nValue
    conditions = property(get_conditions, set_conditions)
    def get_choices(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 15)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 15, byref(cRecords))
            return [cRecords[x].contents.value for x in range(0, numRecords)]
        else: return []
    def set_choices(self, nValue):
        CBash.SetFIDFieldUIA(self._CollectionIndex, self._ModName, self._recordID, 15, struct.pack('I' * len(nValue), *nValue), len(nValue))
    choices = property(get_choices, set_choices)
    def get_linksFrom(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 16)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 16, byref(cRecords))
            return [cRecords[x].contents.value for x in range(0, numRecords)]
        else: return []
    def set_linksFrom(self, nValue):
        CBash.SetFIDFieldUIA(self._CollectionIndex, self._ModName, self._recordID, 16, struct.pack('I' * len(nValue), *nValue), len(nValue))
    linksFrom = property(get_linksFrom, set_linksFrom)
    def get_unused2(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 17)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 17, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_unused2(self, nValue):
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 17, struct.pack('4B', *nValue), 4)
    unused2 = property(get_unused2, set_unused2)
    def get_numRefs(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 18)
        if(retValue): return retValue.contents.value
        else: return None
    def set_numRefs(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 18, nValue)
    numRefs = property(get_numRefs, set_numRefs)
    def get_compiledSize(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 19)
        if(retValue): return retValue.contents.value
        else: return None
    def set_compiledSize(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 19, nValue)
    compiledSize = property(get_compiledSize, set_compiledSize)
    def get_lastIndex(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 20)
        if(retValue): return retValue.contents.value
        else: return None
    def set_lastIndex(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 20, nValue)
    lastIndex = property(get_lastIndex, set_lastIndex)
    def get_scriptType(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 21)
        if(retValue): return retValue.contents.value
        else: return None
    def set_scriptType(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 21, nValue)
    scriptType = property(get_scriptType, set_scriptType)
    def get_compiled_p(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 22)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 22, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_compiled_p(self, nValue):
        length = len(nValue)
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 22, struct.pack('B' * length, *nValue), length)
    compiled_p = property(get_compiled_p, set_compiled_p)
    def get_scriptText(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 23)
    def set_scriptText(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 23, nValue)
    scriptText = property(get_scriptText, set_scriptText)
    def get_references(self):
        numRecords = CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 24)
        if(numRecords > 0): return [self.Reference(self._CollectionIndex, self._ModName, self._recordID, x) for x in range(0, numRecords)]
        else: return []
    def set_references(self, nReferences):
        diffLength = len(nReferences) - CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 24)
        nValues = [(nReference.reference,nReference.isSCRO) for nReference in nReferences]
        while(diffLength < 0):
            CBash.DeleteFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 24)
            diffLength += 1
        while(diffLength > 0):
            CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 24)
            diffLength -= 1
        for oReference, nValue in zip(self.references, nValues):
            oReference.reference, oReference.isSCRO = nValue  
    references = property(get_references, set_references)
class QUSTRecord(BaseRecord):
    def CopyAsOverride(self, targetMod):
        FID = CBash.CopyQUSTRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(True))
        if(FID): return QUSTRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def CopyAsNew(self, targetMod):
        FID = CBash.CopyQUSTRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(False))
        if(FID): return QUSTRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    class Condition(object):
        def __init__(self, CollectionIndex, ModName, recordID, subField, listIndex):
            self._CollectionIndex = CollectionIndex
            self._ModName = ModName
            self._recordID = recordID
            self._subField = subField
            self._listIndex = listIndex
        def get_operType(self):
            CBash.ReadFIDListField.restype = POINTER(c_ubyte)
            retValue = CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 1)
            if(retValue): return retValue.contents.value
            else: return None
        def set_operType(self, nValue):
            CBash.SetFIDListFieldUC(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 1, c_ubyte(nValue))
        operType = property(get_operType, set_operType)
        def get_unused1(self):
            numRecords = CBash.GetFIDListArraySize(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 2)
            if(numRecords > 0):
                cRecords = POINTER(c_ubyte * numRecords)()
                CBash.GetFIDListArray(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 2, byref(cRecords))
                return [cRecords.contents[x] for x in range(0, numRecords)]
            else: return []
        def set_unused1(self, nValue):
            CBash.SetFIDListFieldR(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 2, struct.pack('3B', *nValue), 3)
        unused1 = property(get_unused1, set_unused1)
        def get_compValue(self):
            CBash.ReadFIDListField.restype = POINTER(c_float)
            retValue = CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 3)
            if(retValue): return retValue.contents.value
            else: return None
        def set_compValue(self, nValue):
            CBash.SetFIDListFieldF(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 3, c_float(nValue))
        compValue = property(get_compValue, set_compValue)
        def get_ifunc(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            retValue = CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 4)
            if(retValue): return retValue.contents.value
            else: return None
        def set_ifunc(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 4, nValue)
        ifunc = property(get_ifunc, set_ifunc)
        def get_param1(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            retValue = CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 5)
            if(retValue): return retValue.contents.value
            else: return None
        def set_param1(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 5, nValue)
        param1 = property(get_param1, set_param1)
        def get_param2(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            retValue = CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 6)
            if(retValue): return retValue.contents.value
            else: return None
        def set_param2(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 6, nValue)
        param2 = property(get_param2, set_param2)
        def get_unused2(self):
            numRecords = CBash.GetFIDListArraySize(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 7)
            if(numRecords > 0):
                cRecords = POINTER(c_ubyte * numRecords)()
                CBash.GetFIDListArray(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 7, byref(cRecords))
                return [cRecords.contents[x] for x in range(0, numRecords)]
            else: return []
        def set_unused2(self, nValue):
            CBash.SetFIDListFieldR(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 7, struct.pack('4B', *nValue), 4)
        unused2 = property(get_unused2, set_unused2)
    class Stage(object):
        class Entry(object):
            class Condition(object):
                def __init__(self, CollectionIndex, ModName, recordID, listIndex, listX2Index, listX3Index):
                    self._CollectionIndex = CollectionIndex
                    self._ModName = ModName
                    self._recordID = recordID
                    self._listIndex = listIndex
                    self._listX2Index = listX2Index
                    self._listX3Index = listX3Index
                def get_operType(self):
                    CBash.ReadFIDListX3Field.restype = POINTER(c_ubyte)
                    retValue = CBash.ReadFIDListX3Field(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2, self._listX2Index, 2, self._listX3Index, 1)
                    if(retValue):
                        return retValue.contents.value
                    else:
                        return None
                def set_operType(self, nValue):
                    CBash.SetFIDListX3FieldUC(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2, self._listX2Index, 2, self._listX3Index, 1, c_ubyte(nValue))
                operType = property(get_operType, set_operType)
                def get_unused1(self):
                    numRecords = CBash.GetFIDListX3ArraySize(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2, self._listX2Index, 2, self._listX3Index, 2)
                    if(numRecords > 0):
                        cRecords = POINTER(c_ubyte * numRecords)()
                        CBash.GetFIDListX3Array(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2, self._listX2Index, 2, self._listX3Index, 2, byref(cRecords))
                        return [cRecords.contents[x] for x in range(0, numRecords)]
                    else:
                        return []
                def set_unused1(self, nValue):
                    CBash.SetFIDListX3FieldR(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2, self._listX2Index, 2, self._listX3Index, 2, struct.pack('3B', *nValue), 3)
                unused1 = property(get_unused1, set_unused1)
                def get_compValue(self):
                    CBash.ReadFIDListX3Field.restype = POINTER(c_float)
                    retValue = CBash.ReadFIDListX3Field(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2, self._listX2Index, 2, self._listX3Index, 3)
                    if(retValue):
                        return retValue.contents.value
                    else:
                        return None
                def set_compValue(self, nValue):
                    CBash.SetFIDListX3FieldF(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2, self._listX2Index, 2, self._listX3Index, 3, c_float(nValue))
                compValue = property(get_compValue, set_compValue)
                def get_ifunc(self):
                    CBash.ReadFIDListX3Field.restype = POINTER(c_uint)
                    retValue = CBash.ReadFIDListX3Field(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2, self._listX2Index, 2, self._listX3Index, 4)
                    if(retValue):
                        return retValue.contents.value
                    else:
                        return None
                def set_ifunc(self, nValue):
                    CBash.SetFIDListX3FieldUI(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2, self._listX2Index, 2, self._listX3Index, 4, nValue)
                ifunc = property(get_ifunc, set_ifunc)
                def get_param1(self):
                    CBash.ReadFIDListX3Field.restype = POINTER(c_uint)
                    retValue = CBash.ReadFIDListX3Field(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2, self._listX2Index, 2, self._listX3Index, 5)
                    if(retValue):
                        return retValue.contents.value
                    else:
                        return None
                def set_param1(self, nValue):
                    CBash.SetFIDListX3FieldUI(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2, self._listX2Index, 2, self._listX3Index, 5, nValue)
                param1 = property(get_param1, set_param1)
                def get_param2(self):
                    CBash.ReadFIDListX3Field.restype = POINTER(c_uint)
                    retValue = CBash.ReadFIDListX3Field(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2, self._listX2Index, 2, self._listX3Index, 6)
                    if(retValue):
                        return retValue.contents.value
                    else:
                        return None
                def set_param2(self, nValue):
                    CBash.SetFIDListX3FieldUI(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2, self._listX2Index, 2, self._listX3Index, 6, nValue)
                param2 = property(get_param2, set_param2)
                def get_unused2(self):
                    numRecords = CBash.GetFIDListX3ArraySize(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2, self._listX2Index, 2, self._listX3Index, 7)
                    if(numRecords > 0):
                        cRecords = POINTER(c_ubyte * numRecords)()
                        CBash.GetFIDListX3Array(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2, self._listX2Index, 2, self._listX3Index, 7, byref(cRecords))
                        return [cRecords.contents[x] for x in range(0, numRecords)]
                    else:
                        return []
                def set_unused2(self, nValue):
                    CBash.SetFIDListX3FieldR(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2, self._listX2Index, 2, self._listX3Index, 7, struct.pack('4B', *nValue), 4)
                unused2 = property(get_unused2, set_unused2)

            class Reference(object):
                def __init__(self, CollectionIndex, ModName, recordID, listIndex, listX2Index, listX3Index):
                    self._CollectionIndex = CollectionIndex
                    self._ModName = ModName
                    self._recordID = recordID
                    self._listIndex = listIndex
                    self._listX2Index = listX2Index
                    self._listX3Index = listX3Index
                def get_reference(self):
                    CBash.ReadFIDListX3Field.restype = POINTER(c_uint)
                    return CBash.ReadFIDListX3Field(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2, self._listX2Index, 11, self._listX3Index, 1).contents.value
                def set_reference(self, nValue):
                    CBash.SetFIDListX3FieldUI(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2, self._listX2Index, 11, self._listX3Index, 1, nValue)
                reference = property(get_reference, set_reference)
                def get_isSCRO(self):
                    CBash.ReadFIDListX3Field.restype = POINTER(c_bool)
                    return CBash.ReadFIDListX3Field(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2, self._listX2Index, 11, self._listX3Index, 2).contents.value
                def set_isSCRO(self, nValue):
                    if isinstance(nValue, bool):
                        if(nValue):
                            CBash.SetFIDListX3FieldUI(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2, self._listX2Index, 11, self._listX3Index, 2, 1)
                        else:
                            CBash.SetFIDListX3FieldUI(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2, self._listX2Index, 11, self._listX3Index, 2, 0)
                    else:
                        CBash.SetFIDListX3FieldUI(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2, self._listX2Index, 11, self._listX3Index, 2, nValue)
                isSCRO = property(get_isSCRO, set_isSCRO)
            def __init__(self, CollectionIndex, ModName, recordID, listIndex, listX2Index):
                self._CollectionIndex = CollectionIndex
                self._ModName = ModName
                self._recordID = recordID
                self._listIndex = listIndex
                self._listX2Index = listX2Index
            def newConditionsElement(self):
                listX3Index = CBash.CreateFIDListX3Element(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2, self._listX2Index, 2)
                if(listX3Index == -1):
                    return None
                return self.Condition(self._CollectionIndex, self._ModName, self._recordID, self._listIndex, self._listX2Index, listX3Index)
            def newReferencesElement(self):
                listX3Index = CBash.CreateFIDListX3Element(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2, self._listX2Index, 11)
                if(listX3Index == -1):
                    return None
                return self.Reference(self._CollectionIndex, self._ModName, self._recordID, self._listIndex, self._listX2Index, listX3Index)
                
            def get_flags(self):
                CBash.ReadFIDListX2Field.restype = POINTER(c_ubyte)
                retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2, self._listX2Index, 1)
                if(retValue): return retValue.contents.value
                else: return None
            def set_flags(self, nValue):
                CBash.SetFIDListX2FieldUC(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2, self._listX2Index, 1, c_ubyte(nValue))
            flags = property(get_flags, set_flags)
            def get_conditions(self):
                numRecords = CBash.GetFIDListX3Size(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2, self._listX2Index, 2)
                if(numRecords > 0):
                    return [self.Condition(self._CollectionIndex, self._ModName, self._recordID, self._listIndex, self._listX2Index, x) for x in range(0, numRecords)]
                else: return []
            def set_conditions(self, nConditions):
                diffLength = len(nConditions) - CBash.GetFIDListX3Size(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2, self._listX2Index, 2)
                nValues = [(nCondition.operType, nCondition.unused1, nCondition.compValue, nCondition.ifunc, nCondition.param1, nCondition.param2, nCondition.unused2) for nCondition in nConditions]
                while(diffLength < 0):
                    CBash.DeleteFIDListX3Element(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2, self._listX2Index, 2)
                    diffLength += 1
                while(diffLength > 0):
                    CBash.CreateFIDListX3Element(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2, self._listX2Index, 2)
                    diffLength -= 1
                for oCondition, nValue in zip(self.conditions, nValues):
                    oCondition.operType, oCondition.unused1, oCondition.compValue, oCondition.ifunc, oCondition.param1, oCondition.param2, oCondition.unused2 = nValue
            conditions = property(get_conditions, set_conditions)
            def get_text(self):
                CBash.ReadFIDListX2Field.restype = c_char_p
                return CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2, self._listX2Index, 3)
            def set_text(self, nValue):
                CBash.SetFIDListX2FieldStr(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2, self._listX2Index, 3, nValue)
            text = property(get_text, set_text)
            def get_unused1(self):
                numRecords = CBash.GetFIDListX2ArraySize(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2, self._listX2Index, 4)
                if(numRecords > 0):
                    cRecords = POINTER(c_ubyte * numRecords)()
                    CBash.GetFIDListX2Array(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2, self._listX2Index, 4, byref(cRecords))
                    return [cRecords.contents[x] for x in range(0, numRecords)]
                else: return []
            def set_unused1(self, nValue):
                CBash.SetFIDListX2FieldR(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2, self._listX2Index, 4, struct.pack('4B', *nValue), 4)
            unused1 = property(get_unused1, set_unused1)
            def get_numRefs(self):
                CBash.ReadFIDListX2Field.restype = POINTER(c_uint)
                retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2, self._listX2Index, 5)
                if(retValue): return retValue.contents.value
                else: return None
            def set_numRefs(self, nValue):
                CBash.SetFIDListX2FieldUI(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2, self._listX2Index, 5, nValue)
            numRefs = property(get_numRefs, set_numRefs)
            def get_compiledSize(self):
                CBash.ReadFIDListX2Field.restype = POINTER(c_uint)
                retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2, self._listX2Index, 6)
                if(retValue): return retValue.contents.value
                else: return None
            def set_compiledSize(self, nValue):
                CBash.SetFIDListX2FieldUI(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2, self._listX2Index, 6, nValue)
            compiledSize = property(get_compiledSize, set_compiledSize)
            def get_lastIndex(self):
                CBash.ReadFIDListX2Field.restype = POINTER(c_uint)
                retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2, self._listX2Index, 7)
                if(retValue): return retValue.contents.value
                else: return None
            def set_lastIndex(self, nValue):
                CBash.SetFIDListX2FieldUI(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2, self._listX2Index, 7, nValue)
            lastIndex = property(get_lastIndex, set_lastIndex)
            def get_scriptType(self):
                CBash.ReadFIDListX2Field.restype = POINTER(c_uint)
                retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2, self._listX2Index, 8)
                if(retValue): return retValue.contents.value
                else: return None
            def set_scriptType(self, nValue):
                CBash.SetFIDListX2FieldUI(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2, self._listX2Index, 8, nValue)
            scriptType = property(get_scriptType, set_scriptType)
            def get_compiled_p(self):
                numRecords = CBash.GetFIDListX2ArraySize(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2, self._listX2Index, 9)
                if(numRecords > 0):
                    cRecords = POINTER(c_ubyte * numRecords)()
                    CBash.GetFIDListX2Array(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2, self._listX2Index, 9, byref(cRecords))
                    return [cRecords.contents[x] for x in range(0, numRecords)]
                else: return []
            def set_compiled_p(self, nValue):
                length = len(nValue)
                CBash.SetFIDListX2FieldR(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2, self._listX2Index, 9, struct.pack('B' * length, *nValue), length)
            compiled_p = property(get_compiled_p, set_compiled_p)
            def get_scriptText(self):
                CBash.ReadFIDListX2Field.restype = c_char_p
                return CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2, self._listX2Index, 10)
            def set_scriptText(self, nValue):
                CBash.SetFIDListX2FieldStr(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2, self._listX2Index, 10, nValue)
            scriptText = property(get_scriptText, set_scriptText)
            def get_references(self):
                numRecords = CBash.GetFIDListX3Size(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2, self._listX2Index, 11)
                if(numRecords > 0):
                    return [self.Reference(self._CollectionIndex, self._ModName, self._recordID, self._listIndex, self._listX2Index, x) for x in range(0, numRecords)]
                else: return []
            def set_references(self, nReferences):
                diffLength = len(nReferences) - CBash.GetFIDListX3Size(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2, self._listX2Index, 11)
                nValues = [(nReference.reference,nReference.isSCRO) for nReference in nReferences]
                while(diffLength < 0):
                    CBash.DeleteFIDListX3Element(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2, self._listX2Index, 11)
                    diffLength += 1
                while(diffLength > 0):
                    CBash.CreateFIDListX3Element(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2, self._listX2Index, 11)
                    diffLength -= 1
                for oReference, nValue in zip(self.references, nValues):
                    oReference.reference, oReference.isSCRO = nValue  
            references = property(get_references, set_references)
        def __init__(self, CollectionIndex, ModName, recordID, listIndex):
            self._CollectionIndex = CollectionIndex
            self._ModName = ModName
            self._recordID = recordID
            self._listIndex = listIndex
        def newEntriesElement(self):
            listX2Index = CBash.CreateFIDListX2Element(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2)
            if(listX2Index == -1): return None
            return self.Entry(self._CollectionIndex, self._ModName, self._recordID, self._listIndex, listX2Index)
        def get_stage(self):
            CBash.ReadFIDListField.restype = POINTER(c_ushort)
            retValue = CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 1)
            if(retValue): return retValue.contents.value
            else: return None
        def set_stage(self, nValue):
            CBash.SetFIDListFieldUS(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 1, c_ushort(nValue))
        stage = property(get_stage, set_stage)
        def get_entries(self):
            numRecords = CBash.GetFIDListX2Size(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2)
            if(numRecords > 0): return [self.Entry(self._CollectionIndex, self._ModName, self._recordID, self._listIndex, x) for x in range(0, numRecords)]
            else: return []
        def set_entries(self, nEntries):
            diffLength = len(nEntries) - CBash.GetFIDListX2Size(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2)
            nValues = [(nEntry.flags,
                        [(nCondition.operType, nCondition.unused1, nCondition.compValue, nCondition.ifunc, 
                          nCondition.param1, nCondition.param2, nCondition.unused2) for nCondition in nEntry.conditions],
                        nEntry.text, nEntry.unused1, nEntry.numRefs, nEntry.compiledSize, nEntry.lastIndex, nEntry.scriptType, nEntry.compiled_p, nEntry.scriptText,
                        [(nReference.reference, nReference.isSCRO) for nReference in nEntry.references]) for nEntry in nEntries]
            while(diffLength < 0):
                CBash.DeleteFIDListX2Element(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2)
                diffLength += 1
            while(diffLength > 0):
                CBash.CreateFIDListX2Element(self._CollectionIndex, self._ModName, self._recordID, 12, self._listIndex, 2)
                diffLength -= 1
            for oEntry, nValue in zip(self.entries, nValues):
                nEntry.flags = nValue[0]
                diffLength = len(nValue[1]) - CBash.GetFIDListX3Size(self._CollectionIndex, self._ModName, self._recordID, 12, oEntry._listIndex, 2, oEntry._listX2Index, 2)
                while(diffLength < 0):
                    CBash.DeleteFIDListX3Element(self._CollectionIndex, self._ModName, self._recordID, 12, oEntry._listIndex, 2, oEntry.listX2Index, 2)
                    diffLength += 1
                while(diffLength > 0):
                    CBash.CreateFIDListX3Element(self._CollectionIndex, self._ModName, self._recordID, 12, oEntry._listIndex, 2, oEntry.listX2Index, 2)
                    diffLength -= 1
                for oCondition, condValue in zip(oEntry.conditions, nValue[1]):
                    oCondition.operType, oCondition.unused1, oCondition.compValue, oCondition.ifunc, oCondition.param1, oCondition.param2, oCondition.unused2 = condValue
                nEntry.text = nValue[2]
                nEntry.unused1 = nValue[3]
                nEntry.numRefs = nValue[4]
                nEntry.compiledSize = nValue[5]
                nEntry.lastIndex = nValue[6]
                nEntry.scriptType = nValue[7]
                nEntry.compiled_p = nValue[8]
                nEntry.scriptText = nValue[9]
                diffLength = len(nValue[10]) - CBash.GetFIDListX3Size(self._CollectionIndex, self._ModName, self._recordID, 12, oEntry._listIndex, 2, oEntry._listX2Index, 11)
                while(diffLength < 0):
                    CBash.DeleteFIDListX3Element(self._CollectionIndex, self._ModName, self._recordID, 12, oEntry._listIndex, 2, oEntry.listX2Index, 11)
                    diffLength += 1
                while(diffLength > 0):
                    CBash.CreateFIDListX3Element(self._CollectionIndex, self._ModName, self._recordID, 12, oEntry._listIndex, 2, oEntry.listX2Index, 11)
                    diffLength -= 1
                for oReference, refValue in zip(oEntry.references, nValue[10]):
                    oReference.reference, oReference.isSCRO = refValue   
        entries = property(get_entries, set_entries)
    class Target(object):
        class Condition(object):
            def __init__(self, CollectionIndex, ModName, recordID, listIndex, listX2Index):
                self._CollectionIndex = CollectionIndex
                self._ModName = ModName
                self._recordID = recordID
                self._listIndex = listIndex
                self._listX2Index = listX2Index
            def get_operType(self):
                CBash.ReadFIDListX2Field.restype = POINTER(c_ubyte)
                retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 4, self._listX2Index, 1)
                if(retValue): return retValue.contents.value
                else: return None
            def set_operType(self, nValue):
                CBash.SetFIDListX2FieldUC(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 4, self._listX2Index, 1, c_ubyte(nValue))
            operType = property(get_operType, set_operType)
            def get_unused1(self):
                numRecords = CBash.GetFIDListX2ArraySize(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 4, self._listX2Index, 2)
                if(numRecords > 0):
                    cRecords = POINTER(c_ubyte * numRecords)()
                    CBash.GetFIDListX2Array(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 4, self._listX2Index, 2, byref(cRecords))
                    return [cRecords.contents[x] for x in range(0, numRecords)]
                else: return []
            def set_unused1(self, nValue):
                CBash.SetFIDListX2FieldR(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 4, self._listX2Index, 2, struct.pack('3B', *nValue), 3)
            unused1 = property(get_unused1, set_unused1)
            def get_compValue(self):
                CBash.ReadFIDListX2Field.restype = POINTER(c_float)
                retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 4, self._listX2Index, 3)
                if(retValue): return retValue.contents.value
                else: return None
            def set_compValue(self, nValue):
                CBash.SetFIDListX2FieldF(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 4, self._listX2Index, 3, c_float(nValue))
            compValue = property(get_compValue, set_compValue)
            def get_ifunc(self):
                CBash.ReadFIDListX2Field.restype = POINTER(c_uint)
                retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 4, self._listX2Index, 4)
                if(retValue): return retValue.contents.value
                else: return None
            def set_ifunc(self, nValue):
                CBash.SetFIDListX2FieldUI(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 4, self._listX2Index, 4, nValue)
            ifunc = property(get_ifunc, set_ifunc)
            def get_param1(self):
                CBash.ReadFIDListX2Field.restype = POINTER(c_uint)
                retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 4, self._listX2Index, 5)
                if(retValue): return retValue.contents.value
                else: return None
            def set_param1(self, nValue):
                CBash.SetFIDListX2FieldUI(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 4, self._listX2Index, 5, nValue)
            param1 = property(get_param1, set_param1)
            def get_param2(self):
                CBash.ReadFIDListX2Field.restype = POINTER(c_uint)
                retValue = CBash.ReadFIDListX2Field(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 4, self._listX2Index, 6)
                if(retValue): return retValue.contents.value
                else: return None
            def set_param2(self, nValue):
                CBash.SetFIDListX2FieldUI(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 4, self._listX2Index, 6, nValue)
            param2 = property(get_param2, set_param2)
            def get_unused2(self):
                numRecords = CBash.GetFIDListX2ArraySize(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 4, self._listX2Index, 7)
                if(numRecords > 0):
                    cRecords = POINTER(c_ubyte * numRecords)()
                    CBash.GetFIDListX2Array(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 4, self._listX2Index, 7, byref(cRecords))
                    return [cRecords.contents[x] for x in range(0, numRecords)]
                else: return []
            def set_unused2(self, nValue):
                CBash.SetFIDListX2FieldR(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 4, self._listX2Index, 7, struct.pack('4B', *nValue), 4)
            unused2 = property(get_unused2, set_unused2)
        def __init__(self, CollectionIndex, ModName, recordID, listIndex):
            self._CollectionIndex = CollectionIndex
            self._ModName = ModName
            self._recordID = recordID
            self._listIndex = listIndex
        def newConditionsElement(self):
            listX2Index = CBash.CreateFIDListX2Element(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 4)
            if(listX2Index == -1): return None
            return self.Condition(self._CollectionIndex, self._ModName, self._recordID, self._listIndex, listX2Index)
        def get_targetId(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            retValue = CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 1)
            if(retValue): return retValue.contents.value
            else: return None
        def set_targetId(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 1, nValue)
        targetId = property(get_targetId, set_targetId)
        def get_flags(self):
            CBash.ReadFIDListField.restype = POINTER(c_ubyte)
            retValue = CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 2)
            if(retValue): return retValue.contents.value
            else: return None
        def set_flags(self, nValue):
            CBash.SetFIDListFieldUC(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 2, c_ubyte(nValue))
        flags = property(get_flags, set_flags)
        def get_unused1(self):
            numRecords = CBash.GetFIDListArraySize(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 3)
            if(numRecords > 0):
                cRecords = POINTER(c_ubyte * numRecords)()
                CBash.GetFIDListArray(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 3, byref(cRecords))
                return [cRecords.contents[x] for x in range(0, numRecords)]
            else: return []
        def set_unused1(self, nValue):
            CBash.SetFIDListFieldR(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 3, struct.pack('3B', *nValue), 3)
        unused1 = property(get_unused1, set_unused1)
        def get_conditions(self):
            numRecords = CBash.GetFIDListX2Size(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 4)
            if(numRecords > 0): return [self.Condition(self._CollectionIndex, self._ModName, self._recordID, self._listIndex, x) for x in range(0, numRecords)]
            else: return []
        def set_conditions(self, nConditions):
            diffLength = len(nConditions) - CBash.GetFIDListX2Size(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 4)
            nValues = [(nCondition.operType, nCondition.unused1, nCondition.compValue, nCondition.ifunc, nCondition.param1, nCondition.param2, nCondition.unused2) for nCondition in nConditions]
            while(diffLength < 0):
                CBash.DeleteFIDListX2Element(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 4)
                diffLength += 1
            while(diffLength > 0):
                CBash.CreateFIDListX2Element(self._CollectionIndex, self._ModName, self._recordID, 13, self._listIndex, 4)
                diffLength -= 1
            for oCondition, nValue in zip(self.conditions, nValues):
                oCondition.operType, oCondition.unused1, oCondition.compValue, oCondition.ifunc, oCondition.param1, oCondition.param2, oCondition.unused2 = nValue
        conditions = property(get_conditions, set_conditions)
    def newConditionsElement(self):
        listIndex = CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 11)
        if(listIndex == -1): return None
        return self.Condition(self._CollectionIndex, self._ModName, self._recordID, 11, listIndex)
    def newStagesElement(self):
        listIndex = CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 12)
        if(listIndex == -1): return None
        return self.Stage(self._CollectionIndex, self._ModName, self._recordID, listIndex)
    def newTargetsElement(self):
        listIndex = CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 13)
        if(listIndex == -1): return None
        return self.Target(self._CollectionIndex, self._ModName, self._recordID, listIndex)

    def get_script(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 6)
        if(retValue): return retValue.contents.value
        else: return None
    def set_script(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 6, nValue)
    script = property(get_script, set_script)
    def get_full(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 7)
    def set_full(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 7, nValue)
    full = property(get_full, set_full)
    def get_iconPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 8)
    def set_iconPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 8, nValue)
    iconPath = property(get_iconPath, set_iconPath)
    def get_questFlags(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 9)
        if(retValue): return retValue.contents.value
        else: return None
    def set_questFlags(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 9, c_ubyte(nValue))
    questFlags = property(get_questFlags, set_questFlags)
    def get_priority(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 10)
        if(retValue): return retValue.contents.value
        else: return None
    def set_priority(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 10, c_ubyte(nValue))
    priority = property(get_priority, set_priority)
    def get_conditions(self):
        numRecords = CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 11)
        if(numRecords > 0): return [self.Condition(self._CollectionIndex, self._ModName, self._recordID, 11, x) for x in range(0, numRecords)]
        else: return []
    def set_conditions(self, nConditions):
        diffLength = len(nConditions) - CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 11)
        nValues = [(nCondition.operType, nCondition.unused1, nCondition.compValue, nCondition.ifunc, nCondition.param1, nCondition.param2, nCondition.unused2) for nCondition in nConditions]
        while(diffLength < 0):
            CBash.DeleteFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 11)
            diffLength += 1
        while(diffLength > 0):
            CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 11)
            diffLength -= 1
        for oCondition, nValue in zip(self.conditions, nValues):
            oCondition.operType, oCondition.unused1, oCondition.compValue, oCondition.ifunc, oCondition.param1, oCondition.param2, oCondition.unused2 = nValue
    conditions = property(get_conditions, set_conditions)
    def get_stages(self):
        numRecords = CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 12)
        if(numRecords > 0): return [self.Stage(self._CollectionIndex, self._ModName, self._recordID, x) for x in range(0, numRecords)]
        else: return []
    def set_stages(self, nStages):
        diffLength = len(nStages) - CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 12)
        nValues = [(nStage.stage,
                  [(nEntry.flags,
                  [(nCondition.operType, nCondition.unused1, nCondition.compValue, nCondition.ifunc, 
                  nCondition.param1, nCondition.param2, nCondition.unused2) for nCondition in nEntry.conditions],
                  nEntry.text, nEntry.unused1, nEntry.numRefs, nEntry.compiledSize, nEntry.lastIndex, nEntry.scriptType, nEntry.compiled_p, nEntry.scriptText,
                  [(nReference.reference, nReference.isSCRO) for nReference in nEntry.references]) for nEntry in nStage.entries]) for nStage in nStages]
        while(diffLength < 0):
            CBash.DeleteFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 12)
            diffLength += 1
        while(diffLength > 0):
            CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 12)
            diffLength -= 1
        for oStage, nValue in zip(self.stages, nValues):
            oStage.stage = nValue[0]
            for oEntry, eValue in zip(oStage.entries, nValue[1]):
                nEntry.flags = eValue[0]
                diffLength = len(eValue[1]) - CBash.GetFIDListX3Size(self._CollectionIndex, self._ModName, self._recordID, 12, oEntry._listIndex, 2, oEntry._listX2Index, 2)
                while(diffLength < 0):
                    CBash.DeleteFIDListX3Element(self._CollectionIndex, self._ModName, self._recordID, 12, oEntry._listIndex, 2, oEntry._listX2Index, 2)
                    diffLength += 1
                while(diffLength > 0):
                    CBash.CreateFIDListX3Element(self._CollectionIndex, self._ModName, self._recordID, 12, oEntry._listIndex, 2, oEntry._listX2Index, 2)
                    diffLength -= 1
                for oCondition, condValue in zip(oEntry.conditions, eValue[1]):
                    oCondition.operType, oCondition.unused1, oCondition.compValue, oCondition.ifunc, oCondition.param1, oCondition.param2, oCondition.unused2 = condValue
                nEntry.text = eValue[2]
                nEntry.unused1 = eValue[3]
                nEntry.numRefs = eValue[4]
                nEntry.compiledSize = eValue[5]
                nEntry.lastIndex = eValue[6]
                nEntry.scriptType = eValue[7]
                nEntry.compiled_p = eValue[8]
                nEntry.scriptText = eValue[9]
                diffLength = len(eValue[10]) - CBash.GetFIDListX3Size(self._CollectionIndex, self._ModName, self._recordID, 12, oEntry._listIndex, 2, oEntry._listX2Index, 11)
                while(diffLength < 0):
                    CBash.DeleteFIDListX3Element(self._CollectionIndex, self._ModName, self._recordID, 12, oEntry._listIndex, 2, oEntry._listX2Index, 11)
                    diffLength += 1
                while(diffLength > 0):
                    CBash.CreateFIDListX3Element(self._CollectionIndex, self._ModName, self._recordID, 12, oEntry._listIndex, 2, oEntry._listX2Index, 11)
                    diffLength -= 1
                for oReference, refValue in zip(oEntry.references, eValue[10]):
                    oReference.reference, oReference.isSCRO = refValue  
    stages = property(get_stages, set_stages)
    def get_targets(self):
        numRecords = CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 13)
        if(numRecords > 0): return [self.Target(self._CollectionIndex, self._ModName, self._recordID, x) for x in range(0, numRecords)]
        else: return []
    def set_targets(self, nTargets):
        diffLength = len(nTargets) - CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 13)
        nValues = [(nTarget.targetId, nTarget.flags, nTarget.unused1,
                  [(nCondition.operType, nCondition.unused1, nCondition.compValue, nCondition.ifunc, nCondition.param1, nCondition.param2, nCondition.unused2) for nCondition in nTarget.conditions]) for nTarget in nTargets]
        while(diffLength < 0):
            CBash.DeleteFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 13)
            diffLength += 1
        while(diffLength > 0):
            CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 13)
            diffLength -= 1
        for oTarget, nValue in zip(self.targets, nValues):
            oTarget.targetId = nValue[0]
            oTarget.flags = nValue[1]
            oTarget.unused1 = nValue[2]
            diffLength = len(nValue[3]) - CBash.GetFIDListX2Size(self._CollectionIndex, self._ModName, self._recordID, 13, oTarget._listIndex, 4)
            while(diffLength < 0):
                CBash.DeleteFIDListX2Element(self._CollectionIndex, self._ModName, self._recordID, 13, oTarget._listIndex, 4)
                diffLength += 1
            while(diffLength > 0):
                CBash.CreateFIDListX2Element(self._CollectionIndex, self._ModName, self._recordID, 13, oTarget._listIndex, 4)
                diffLength -= 1
            for oCondition, eValue in zip(oTarget.conditions, nValue[3]):
                oCondition.operType, oCondition.unused1, oCondition.compValue, oCondition.ifunc, oCondition.param1, oCondition.param2, oCondition.unused2 = eValue
    targets = property(get_targets, set_targets)
class IDLERecord(BaseRecord):
    def CopyAsOverride(self, targetMod):
        FID = CBash.CopyIDLERecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(True))
        if(FID): return IDLERecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def CopyAsNew(self, targetMod):
        FID = CBash.CopyIDLERecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(False))
        if(FID): return IDLERecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    class Condition(object):
        def __init__(self, CollectionIndex, ModName, recordID, subField, listIndex):
            self._CollectionIndex = CollectionIndex
            self._ModName = ModName
            self._recordID = recordID
            self._subField = subField
            self._listIndex = listIndex
        def get_operType(self):
            CBash.ReadFIDListField.restype = POINTER(c_ubyte)
            retValue = CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 1)
            if(retValue): return retValue.contents.value
            else: return None
        def set_operType(self, nValue):
            CBash.SetFIDListFieldUC(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 1, c_ubyte(nValue))
        operType = property(get_operType, set_operType)
        def get_unused1(self):
            numRecords = CBash.GetFIDListArraySize(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 2)
            if(numRecords > 0):
                cRecords = POINTER(c_ubyte * numRecords)()
                CBash.GetFIDListArray(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 2, byref(cRecords))
                return [cRecords.contents[x] for x in range(0, numRecords)]
            else: return []
        def set_unused1(self, nValue):
            CBash.SetFIDListFieldR(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 2, struct.pack('3B', *nValue), 3)
        unused1 = property(get_unused1, set_unused1)
        def get_compValue(self):
            CBash.ReadFIDListField.restype = POINTER(c_float)
            retValue = CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 3)
            if(retValue): return retValue.contents.value
            else: return None
        def set_compValue(self, nValue):
            CBash.SetFIDListFieldF(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 3, c_float(nValue))
        compValue = property(get_compValue, set_compValue)
        def get_ifunc(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            retValue = CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 4)
            if(retValue): return retValue.contents.value
            else: return None
        def set_ifunc(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 4, nValue)
        ifunc = property(get_ifunc, set_ifunc)
        def get_param1(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            retValue = CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 5)
            if(retValue): return retValue.contents.value
            else: return None
        def set_param1(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 5, nValue)
        param1 = property(get_param1, set_param1)
        def get_param2(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            retValue = CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 6)
            if(retValue): return retValue.contents.value
            else: return None
        def set_param2(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 6, nValue)
        param2 = property(get_param2, set_param2)
        def get_unused2(self):
            numRecords = CBash.GetFIDListArraySize(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 7)
            if(numRecords > 0):
                cRecords = POINTER(c_ubyte * numRecords)()
                CBash.GetFIDListArray(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 7, byref(cRecords))
                return [cRecords.contents[x] for x in range(0, numRecords)]
            else: return []
        def set_unused2(self, nValue):
            CBash.SetFIDListFieldR(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 7, struct.pack('4B', *nValue), 4)
        unused2 = property(get_unused2, set_unused2)
    def newConditionsElement(self):
        listIndex = CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 9)
        if(listIndex == -1): return None
        return self.Condition(self._CollectionIndex, self._ModName, self._recordID, 9, listIndex)

    def get_modPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 6)
    def set_modPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 6, nValue)
    modPath = property(get_modPath, set_modPath)
    def get_modb(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 7)
        if(retValue): return retValue.contents.value
        else: return None
    def set_modb(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 7, c_float(nValue))
    modb = property(get_modb, set_modb)
    def get_modt_p(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 8)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 8, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_modt_p(self, nValue):
        length = len(nValue)
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 8, struct.pack('B' * length, *nValue), length)
    modt_p = property(get_modt_p, set_modt_p)
    def get_conditions(self):
        numRecords = CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 9)
        if(numRecords > 0): return [self.Condition(self._CollectionIndex, self._ModName, self._recordID, 9, x) for x in range(0, numRecords)]
        else: return []
    def set_conditions(self, nConditions):
        diffLength = len(nConditions) - CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 9)
        nValues = [(nCondition.operType, nCondition.unused1, nCondition.compValue, nCondition.ifunc, nCondition.param1, nCondition.param2, nCondition.unused2) for nCondition in nConditions]
        while(diffLength < 0):
            CBash.DeleteFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 9)
            diffLength += 1
        while(diffLength > 0):
            CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 9)
            diffLength -= 1
        for oCondition, nValue in zip(self.conditions, nValues):
            oCondition.operType, oCondition.unused1, oCondition.compValue, oCondition.ifunc, oCondition.param1, oCondition.param2, oCondition.unused2 = nValue
    conditions = property(get_conditions, set_conditions)
    def get_group(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 10)
        if(retValue): return retValue.contents.value
        else: return None
    def set_group(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 10, c_ubyte(nValue))
    group = property(get_group, set_group)
    def get_parent(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 11)
        if(retValue): return retValue.contents.value
        else: return None
    def set_parent(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 11, nValue)
    parent = property(get_parent, set_parent)
    def get_prevId(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 12)
        if(retValue): return retValue.contents.value
        else: return None
    def set_prevId(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 12, nValue)
    prevId = property(get_prevId, set_prevId)
class PACKRecord(BaseRecord):
    def CopyAsOverride(self, targetMod):
        FID = CBash.CopyPACKRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(True))
        if(FID): return PACKRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def CopyAsNew(self, targetMod):
        FID = CBash.CopyPACKRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(False))
        if(FID): return PACKRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    class Condition(object):
        def __init__(self, CollectionIndex, ModName, recordID, subField, listIndex):
            self._CollectionIndex = CollectionIndex
            self._ModName = ModName
            self._recordID = recordID
            self._subField = subField
            self._listIndex = listIndex
        def get_operType(self):
            CBash.ReadFIDListField.restype = POINTER(c_ubyte)
            retValue = CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 1)
            if(retValue): return retValue.contents.value
            else: return None
        def set_operType(self, nValue):
            CBash.SetFIDListFieldUC(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 1, c_ubyte(nValue))
        operType = property(get_operType, set_operType)
        def get_unused1(self):
            numRecords = CBash.GetFIDListArraySize(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 2)
            if(numRecords > 0):
                cRecords = POINTER(c_ubyte * numRecords)()
                CBash.GetFIDListArray(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 2, byref(cRecords))
                return [cRecords.contents[x] for x in range(0, numRecords)]
            else: return []
        def set_unused1(self, nValue):
            CBash.SetFIDListFieldR(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 2, struct.pack('3B', *nValue), 3)
        unused1 = property(get_unused1, set_unused1)
        def get_compValue(self):
            CBash.ReadFIDListField.restype = POINTER(c_float)
            retValue = CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 3)
            if(retValue): return retValue.contents.value
            else: return None
        def set_compValue(self, nValue):
            CBash.SetFIDListFieldF(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 3, c_float(nValue))
        compValue = property(get_compValue, set_compValue)
        def get_ifunc(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            retValue = CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 4)
            if(retValue): return retValue.contents.value
            else: return None
        def set_ifunc(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 4, nValue)
        ifunc = property(get_ifunc, set_ifunc)
        def get_param1(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            retValue = CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 5)
            if(retValue): return retValue.contents.value
            else: return None
        def set_param1(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 5, nValue)
        param1 = property(get_param1, set_param1)
        def get_param2(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            retValue = CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 6)
            if(retValue): return retValue.contents.value
            else: return None
        def set_param2(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 6, nValue)
        param2 = property(get_param2, set_param2)
        def get_unused2(self):
            numRecords = CBash.GetFIDListArraySize(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 7)
            if(numRecords > 0):
                cRecords = POINTER(c_ubyte * numRecords)()
                CBash.GetFIDListArray(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 7, byref(cRecords))
                return [cRecords.contents[x] for x in range(0, numRecords)]
            else: return []
        def set_unused2(self, nValue):
            CBash.SetFIDListFieldR(self._CollectionIndex, self._ModName, self._recordID, self._subField, self._listIndex, 7, struct.pack('4B', *nValue), 4)
        unused2 = property(get_unused2, set_unused2)
    def newConditionsElement(self):
        listIndex = CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 20)
        if(listIndex == -1): return None
        return self.Condition(self._CollectionIndex, self._ModName, self._recordID, 20, listIndex)
    def get_flags(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 6)
        if(retValue): return retValue.contents.value
        else: return None
    def set_flags(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 6, nValue)
    flags = property(get_flags, set_flags)
    def get_aiType(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 7)
        if(retValue): return retValue.contents.value
        else: return None
    def set_aiType(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 7, c_ubyte(nValue))
    aiType = property(get_aiType, set_aiType)
    def get_unused1(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 8)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 8, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_unused1(self, nValue):
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 8, struct.pack('3B', *nValue), 3)
    unused1 = property(get_unused1, set_unused1)
    def get_locType(self):
        CBash.ReadFIDField.restype = POINTER(c_int)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 9)
        if(retValue): return retValue.contents.value
        else: return None
    def set_locType(self, nValue):
        CBash.SetFIDFieldI(self._CollectionIndex, self._ModName, self._recordID, 9, nValue)
    locType = property(get_locType, set_locType)
    def get_locId(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 10)
        if(retValue): return retValue.contents.value
        else: return None
    def set_locId(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 10, nValue)
    locId = property(get_locId, set_locId)
    def get_locRadius(self):
        CBash.ReadFIDField.restype = POINTER(c_int)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 11)
        if(retValue): return retValue.contents.value
        else: return None
    def set_locRadius(self, nValue):
        CBash.SetFIDFieldI(self._CollectionIndex, self._ModName, self._recordID, 11, nValue)
    locRadius = property(get_locRadius, set_locRadius)
    def get_month(self):
        CBash.ReadFIDField.restype = POINTER(c_byte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 12)
        if(retValue): return retValue.contents.value
        else: return None
    def set_month(self, nValue):
        CBash.SetFIDFieldC(self._CollectionIndex, self._ModName, self._recordID, 12, c_byte(nValue))
    month = property(get_month, set_month)
    def get_day(self):
        CBash.ReadFIDField.restype = POINTER(c_byte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 13)
        if(retValue): return retValue.contents.value
        else: return None
    def set_day(self, nValue):
        CBash.SetFIDFieldC(self._CollectionIndex, self._ModName, self._recordID, 13, c_byte(nValue))
    day = property(get_day, set_day)
    def get_date(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 14)
        if(retValue): return retValue.contents.value
        else: return None
    def set_date(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 14, c_ubyte(nValue))
    date = property(get_date, set_date)
    def get_time(self):
        CBash.ReadFIDField.restype = POINTER(c_byte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 15)
        if(retValue): return retValue.contents.value
        else: return None
    def set_time(self, nValue):
        CBash.SetFIDFieldC(self._CollectionIndex, self._ModName, self._recordID, 15, c_byte(nValue))
    time = property(get_time, set_time)
    def get_duration(self):
        CBash.ReadFIDField.restype = POINTER(c_int)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 16)
        if(retValue): return retValue.contents.value
        else: return None
    def set_duration(self, nValue):
        CBash.SetFIDFieldI(self._CollectionIndex, self._ModName, self._recordID, 16, nValue)
    duration = property(get_duration, set_duration)
    def get_targetType(self):
        CBash.ReadFIDField.restype = POINTER(c_int)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 17)
        if(retValue): return retValue.contents.value
        else: return None
    def set_targetType(self, nValue):
        CBash.SetFIDFieldI(self._CollectionIndex, self._ModName, self._recordID, 17, nValue)
    targetType = property(get_targetType, set_targetType)
    def get_targetId(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 18)
        if(retValue): return retValue.contents.value
        else: return None
    def set_targetId(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 18, nValue)
    targetId = property(get_targetId, set_targetId)
    def get_targetCount(self):
        CBash.ReadFIDField.restype = POINTER(c_int)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 19)
        if(retValue): return retValue.contents.value
        else: return None
    def set_targetCount(self, nValue):
        CBash.SetFIDFieldI(self._CollectionIndex, self._ModName, self._recordID, 19, nValue)
    targetCount = property(get_targetCount, set_targetCount)
    def get_conditions(self):
        numRecords = CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 20)
        if(numRecords > 0): return [self.Condition(self._CollectionIndex, self._ModName, self._recordID, 20, x) for x in range(0, numRecords)]
        else: return []
    def set_conditions(self, nConditions):
        diffLength = len(nConditions) - CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 20)
        nValues = [(nCondition.operType, nCondition.unused1, nCondition.compValue, nCondition.ifunc, nCondition.param1, nCondition.param2, nCondition.unused2) for nCondition in nConditions]
        while(diffLength < 0):
            CBash.DeleteFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 20)
            diffLength += 1
        while(diffLength > 0):
            CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 20)
            diffLength -= 1
        for oCondition, nValue in zip(self.conditions, nValues):
            oCondition.operType, oCondition.unused1, oCondition.compValue, oCondition.ifunc, oCondition.param1, oCondition.param2, oCondition.unused2 = nValue
    conditions = property(get_conditions, set_conditions)
class CSTYRecord(BaseRecord):
    def CopyAsOverride(self, targetMod):
        FID = CBash.CopyCSTYRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(True))
        if(FID): return CSTYRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def CopyAsNew(self, targetMod):
        FID = CBash.CopyCSTYRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(False))
        if(FID): return CSTYRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def get_dodgeChance(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 6)
        if(retValue): return retValue.contents.value
        else: return None
    def set_dodgeChance(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 6, c_ubyte(nValue))
    dodgeChance = property(get_dodgeChance, set_dodgeChance)
    def get_lrChance(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 7)
        if(retValue): return retValue.contents.value
        else: return None
    def set_lrChance(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 7, c_ubyte(nValue))
    lrChance = property(get_lrChance, set_lrChance)
    def get_unused1(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 8)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 8, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_unused1(self, nValue):
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 8, struct.pack('2B', *nValue), 2)
    unused1 = property(get_unused1, set_unused1)
    def get_lrTimerMin(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 9)
        if(retValue): return retValue.contents.value
        else: return None
    def set_lrTimerMin(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 9, c_float(nValue))
    lrTimerMin = property(get_lrTimerMin, set_lrTimerMin)
    def get_lrTimerMax(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 10)
        if(retValue): return retValue.contents.value
        else: return None
    def set_lrTimerMax(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 10, c_float(nValue))
    lrTimerMax = property(get_lrTimerMax, set_lrTimerMax)
    def get_forTimerMin(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 11)
        if(retValue): return retValue.contents.value
        else: return None
    def set_forTimerMin(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 11, c_float(nValue))
    forTimerMin = property(get_forTimerMin, set_forTimerMin)
    def get_forTimerMax(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 12)
        if(retValue): return retValue.contents.value
        else: return None
    def set_forTimerMax(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 12, c_float(nValue))
    forTimerMax = property(get_forTimerMax, set_forTimerMax)
    def get_backTimerMin(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 13)
        if(retValue): return retValue.contents.value
        else: return None
    def set_backTimerMin(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 13, c_float(nValue))
    backTimerMin = property(get_backTimerMin, set_backTimerMin)
    def get_backTimerMax(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 14)
        if(retValue): return retValue.contents.value
        else: return None
    def set_backTimerMax(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 14, c_float(nValue))
    backTimerMax = property(get_backTimerMax, set_backTimerMax)
    def get_idleTimerMin(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 15)
        if(retValue): return retValue.contents.value
        else: return None
    def set_idleTimerMin(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 15, c_float(nValue))
    idleTimerMin = property(get_idleTimerMin, set_idleTimerMin)
    def get_idleTimerMax(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 16)
        if(retValue): return retValue.contents.value
        else: return None
    def set_idleTimerMax(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 16, c_float(nValue))
    idleTimerMax = property(get_idleTimerMax, set_idleTimerMax)
    def get_blkChance(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 17)
        if(retValue): return retValue.contents.value
        else: return None
    def set_blkChance(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 17, c_ubyte(nValue))
    blkChance = property(get_blkChance, set_blkChance)
    def get_atkChance(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 18)
        if(retValue): return retValue.contents.value
        else: return None
    def set_atkChance(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 18, c_ubyte(nValue))
    atkChance = property(get_atkChance, set_atkChance)
    def get_unused2(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 19)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 19, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_unused2(self, nValue):
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 19, struct.pack('2B', *nValue), 2)
    unused2 = property(get_unused2, set_unused2)
    def get_atkBRecoil(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 20)
        if(retValue): return retValue.contents.value
        else: return None
    def set_atkBRecoil(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 20, c_float(nValue))
    atkBRecoil = property(get_atkBRecoil, set_atkBRecoil)
    def get_atkBUnc(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 21)
        if(retValue): return retValue.contents.value
        else: return None
    def set_atkBUnc(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 21, c_float(nValue))
    atkBUnc = property(get_atkBUnc, set_atkBUnc)
    def get_atkBh2h(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 22)
        if(retValue): return retValue.contents.value
        else: return None
    def set_atkBh2h(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 22, c_float(nValue))
    atkBh2h = property(get_atkBh2h, set_atkBh2h)
    def get_pAtkChance(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 23)
        if(retValue): return retValue.contents.value
        else: return None
    def set_pAtkChance(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 23, c_ubyte(nValue))
    pAtkChance = property(get_pAtkChance, set_pAtkChance)
    def get_unused3(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 24)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 24, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_unused3(self, nValue):
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 24, struct.pack('3B', *nValue), 3)
    unused3 = property(get_unused3, set_unused3)
    def get_pAtkBRecoil(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 25)
        if(retValue): return retValue.contents.value
        else: return None
    def set_pAtkBRecoil(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 25, c_float(nValue))
    pAtkBRecoil = property(get_pAtkBRecoil, set_pAtkBRecoil)
    def get_pAtkBUnc(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 26)
        if(retValue): return retValue.contents.value
        else: return None
    def set_pAtkBUnc(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 26, c_float(nValue))
    pAtkBUnc = property(get_pAtkBUnc, set_pAtkBUnc)
    def get_pAtkNormal(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 27)
        if(retValue): return retValue.contents.value
        else: return None
    def set_pAtkNormal(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 27, c_ubyte(nValue))
    pAtkNormal = property(get_pAtkNormal, set_pAtkNormal)
    def get_pAtkFor(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 28)
        if(retValue): return retValue.contents.value
        else: return None
    def set_pAtkFor(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 28, c_ubyte(nValue))
    pAtkFor = property(get_pAtkFor, set_pAtkFor)
    def get_pAtkBack(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 29)
        if(retValue): return retValue.contents.value
        else: return None
    def set_pAtkBack(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 29, c_ubyte(nValue))
    pAtkBack = property(get_pAtkBack, set_pAtkBack)
    def get_pAtkL(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 30)
        if(retValue): return retValue.contents.value
        else: return None
    def set_pAtkL(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 30, c_ubyte(nValue))
    pAtkL = property(get_pAtkL, set_pAtkL)
    def get_pAtkR(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 31)
        if(retValue): return retValue.contents.value
        else: return None
    def set_pAtkR(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 31, c_ubyte(nValue))
    pAtkR = property(get_pAtkR, set_pAtkR)
    def get_unused4(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 32)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 32, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_unused4(self, nValue):
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 32, struct.pack('3B', *nValue), 3)
    unused4 = property(get_unused4, set_unused4)                    
    def get_holdTimerMin(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 33)
        if(retValue): return retValue.contents.value
        else: return None
    def set_holdTimerMin(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 33, c_float(nValue))
    holdTimerMin = property(get_holdTimerMin, set_holdTimerMin)
    def get_holdTimerMax(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 34)
        if(retValue): return retValue.contents.value
        else: return None
    def set_holdTimerMax(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 34, c_float(nValue))
    holdTimerMax = property(get_holdTimerMax, set_holdTimerMax)
    def get_flagsA(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 35)
        if(retValue): return retValue.contents.value
        else: return None
    def set_flagsA(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 35, c_ubyte(nValue))
    flagsA = property(get_flagsA, set_flagsA)
    def get_acroDodge(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 36)
        if(retValue): return retValue.contents.value
        else: return None
    def set_acroDodge(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 36, c_ubyte(nValue))
    acroDodge = property(get_acroDodge, set_acroDodge)
    def get_unused5(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 37)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 37, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_unused5(self, nValue):
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 37, struct.pack('2B', *nValue), 2)
    unused5 = property(get_unused5, set_unused5)
    def get_rMultOpt(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 38)
        if(retValue): return retValue.contents.value
        else: return None
    def set_rMultOpt(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 38, c_float(nValue))
    rMultOpt = property(get_rMultOpt, set_rMultOpt)
    def get_rMultMax(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 39)
        if(retValue): return retValue.contents.value
        else: return None
    def set_rMultMax(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 39, c_float(nValue))
    rMultMax = property(get_rMultMax, set_rMultMax)
    def get_mDistance(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 40)
        if(retValue): return retValue.contents.value
        else: return None
    def set_mDistance(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 40, c_float(nValue))
    mDistance = property(get_mDistance, set_mDistance)
    def get_rDistance(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 41)
        if(retValue): return retValue.contents.value
        else: return None
    def set_rDistance(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 41, c_float(nValue))
    rDistance = property(get_rDistance, set_rDistance)
    def get_buffStand(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 42)
        if(retValue): return retValue.contents.value
        else: return None
    def set_buffStand(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 42, c_float(nValue))
    buffStand = property(get_buffStand, set_buffStand)
    def get_rStand(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 43)
        if(retValue): return retValue.contents.value
        else: return None
    def set_rStand(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 43, c_float(nValue))
    rStand = property(get_rStand, set_rStand)
    def get_groupStand(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 44)
        if(retValue): return retValue.contents.value
        else: return None
    def set_groupStand(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 44, c_float(nValue))
    groupStand = property(get_groupStand, set_groupStand)
    def get_rushChance(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 45)
        if(retValue): return retValue.contents.value
        else: return None
    def set_rushChance(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 45, c_ubyte(nValue))
    rushChance = property(get_rushChance, set_rushChance)
    def get_unused6(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 46)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 46, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_unused6(self, nValue):
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 46, struct.pack('3B', *nValue), 3)
    unused6 = property(get_unused6, set_unused6)
    def get_rushMult(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 47)
        if(retValue): return retValue.contents.value
        else: return None
    def set_rushMult(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 47, c_float(nValue))
    rushMult = property(get_rushMult, set_rushMult)
    def get_flagsB(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 48)
        if(retValue): return retValue.contents.value
        else: return None
    def set_flagsB(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 48, nValue)
    flagsB = property(get_flagsB, set_flagsB)
    def get_dodgeFMult(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 49)
        if(retValue): return retValue.contents.value
        else: return None
    def set_dodgeFMult(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 49, c_float(nValue))
    dodgeFMult = property(get_dodgeFMult, set_dodgeFMult)
    def get_dodgeFBase(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 50)
        if(retValue): return retValue.contents.value
        else: return None
    def set_dodgeFBase(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 50, c_float(nValue))
    dodgeFBase = property(get_dodgeFBase, set_dodgeFBase)
    def get_encSBase(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 51)
        if(retValue): return retValue.contents.value
        else: return None
    def set_encSBase(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 51, c_float(nValue))
    encSBase = property(get_encSBase, set_encSBase)
    def get_encSMult(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 52)
        if(retValue): return retValue.contents.value
        else: return None
    def set_encSMult(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 52, c_float(nValue))
    encSMult = property(get_encSMult, set_encSMult)
    def get_dodgeAtkMult(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 53)
        if(retValue): return retValue.contents.value
        else: return None
    def set_dodgeAtkMult(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 53, c_float(nValue))
    dodgeAtkMult = property(get_dodgeAtkMult, set_dodgeAtkMult)
    def get_dodgeNAtkMult(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 54)
        if(retValue): return retValue.contents.value
        else: return None
    def set_dodgeNAtkMult(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 54, c_float(nValue))
    dodgeNAtkMult = property(get_dodgeNAtkMult, set_dodgeNAtkMult)
    def get_dodgeBAtkMult(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 55)
        if(retValue): return retValue.contents.value
        else: return None
    def set_dodgeBAtkMult(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 55, c_float(nValue))
    dodgeBAtkMult = property(get_dodgeBAtkMult, set_dodgeBAtkMult)
    def get_dodgeBNAtkMult(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 56)
        if(retValue): return retValue.contents.value
        else: return None
    def set_dodgeBNAtkMult(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 56, c_float(nValue))
    dodgeBNAtkMult = property(get_dodgeBNAtkMult, set_dodgeBNAtkMult)
    def get_dodgeFAtkMult(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 57)
        if(retValue): return retValue.contents.value
        else: return None
    def set_dodgeFAtkMult(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 57, c_float(nValue))
    dodgeFAtkMult = property(get_dodgeFAtkMult, set_dodgeFAtkMult)
    def get_dodgeFNAtkMult(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 58)
        if(retValue): return retValue.contents.value
        else: return None
    def set_dodgeFNAtkMult(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 58, c_float(nValue))
    dodgeFNAtkMult = property(get_dodgeFNAtkMult, set_dodgeFNAtkMult)
    def get_blockMult(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 59)
        if(retValue): return retValue.contents.value
        else: return None
    def set_blockMult(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 59, c_float(nValue))
    blockMult = property(get_blockMult, set_blockMult)
    def get_blockBase(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 60)
        if(retValue): return retValue.contents.value
        else: return None
    def set_blockBase(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 60, c_float(nValue))
    blockBase = property(get_blockBase, set_blockBase)
    def get_blockAtkMult(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 61)
        if(retValue): return retValue.contents.value
        else: return None
    def set_blockAtkMult(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 61, c_float(nValue))
    blockAtkMult = property(get_blockAtkMult, set_blockAtkMult)
    def get_blockNAtkMult(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 62)
        if(retValue): return retValue.contents.value
        else: return None
    def set_blockNAtkMult(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 62, c_float(nValue))
    blockNAtkMult = property(get_blockNAtkMult, set_blockNAtkMult)
    def get_atkMult(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 63)
        if(retValue): return retValue.contents.value
        else: return None
    def set_atkMult(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 63, c_float(nValue))
    atkMult = property(get_atkMult, set_atkMult)
    def get_atkBase(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 64)
        if(retValue): return retValue.contents.value
        else: return None
    def set_atkBase(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 64, c_float(nValue))
    atkBase = property(get_atkBase, set_atkBase)
    def get_atkAtkMult(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 65)
        if(retValue): return retValue.contents.value
        else: return None
    def set_atkAtkMult(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 65, c_float(nValue))
    atkAtkMult = property(get_atkAtkMult, set_atkAtkMult)
    def get_atkNAtkMult(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 66)
        if(retValue): return retValue.contents.value
        else: return None
    def set_atkNAtkMult(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 66, c_float(nValue))
    atkNAtkMult = property(get_atkNAtkMult, set_atkNAtkMult)
    def get_atkBlockMult(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 67)
        if(retValue): return retValue.contents.value
        else: return None
    def set_atkBlockMult(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 67, c_float(nValue))
    atkBlockMult = property(get_atkBlockMult, set_atkBlockMult)
    def get_pAtkFBase(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 68)
        if(retValue): return retValue.contents.value
        else: return None
    def set_pAtkFBase(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 68, c_float(nValue))
    pAtkFBase = property(get_pAtkFBase, set_pAtkFBase)
    def get_pAtkFMult(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 69)
        if(retValue): return retValue.contents.value
        else: return None
    def set_pAtkFMult(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 69, c_float(nValue))
    pAtkFMult = property(get_pAtkFMult, set_pAtkFMult)
class LSCRRecord(BaseRecord):
    def CopyAsOverride(self, targetMod):
        FID = CBash.CopyLSCRRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(True))
        if(FID): return LSCRRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def CopyAsNew(self, targetMod):
        FID = CBash.CopyLSCRRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(False))
        if(FID): return LSCRRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    class Location(object):
        def __init__(self, CollectionIndex, ModName, recordID, listIndex):
            self._CollectionIndex = CollectionIndex
            self._ModName = ModName
            self._recordID = recordID
            self._listIndex = listIndex
        def get_direct(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, 8, self._listIndex, 1).contents.value
        def set_direct(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, 8, self._listIndex, 1, nValue)
        direct = property(get_direct, set_direct)
        def get_indirect(self):
            CBash.ReadFIDListField.restype = POINTER(c_uint)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, 8, self._listIndex, 2).contents.value
        def set_indirect(self, nValue):
            CBash.SetFIDListFieldUI(self._CollectionIndex, self._ModName, self._recordID, 8, self._listIndex, 2, nValue)
        indirect = property(get_indirect, set_indirect)
        def get_gridY(self):
            CBash.ReadFIDListField.restype = POINTER(c_short)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, 8, self._listIndex, 3).contents.value
        def set_gridY(self, nValue):
            CBash.SetFIDListFieldS(self._CollectionIndex, self._ModName, self._recordID, 8, self._listIndex, 3, c_short(nValue))
        gridY = property(get_gridY, set_gridY)
        def get_gridX(self):
            CBash.ReadFIDListField.restype = POINTER(c_short)
            return CBash.ReadFIDListField(self._CollectionIndex, self._ModName, self._recordID, 8, self._listIndex, 4).contents.value
        def set_gridX(self, nValue):
            CBash.SetFIDListFieldS(self._CollectionIndex, self._ModName, self._recordID, 8, self._listIndex, 4, c_short(nValue))
        gridX = property(get_gridX, set_gridX)
    def newLocationsElement(self):
        listIndex = CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 8)
        if(listIndex == -1): return None
        return self.Location(self._CollectionIndex, self._ModName, self._recordID, listIndex)
    def get_iconPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 6)
    def set_iconPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 6, nValue)
    iconPath = property(get_iconPath, set_iconPath)
    def get_text(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 7)
    def set_text(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 7, nValue)
    text = property(get_text, set_text)
    def get_locations(self):
        numRecords = CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 8)
        if(numRecords > 0): return [self.Location(self._CollectionIndex, self._ModName, self._recordID, x) for x in range(0, numRecords)]
        else: return []
    def set_locations(self, nLocations):
        diffLength = len(nLocations) - CBash.GetFIDListSize(self._CollectionIndex, self._ModName, self._recordID, 8)
        nValues = [(nLocation.direct, nLocation.indirect, nLocation.gridY, nLocation.gridX) for nLocation in nLocations]
        while(diffLength < 0):
            CBash.DeleteFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 8)
            diffLength += 1
        while(diffLength > 0):
            CBash.CreateFIDListElement(self._CollectionIndex, self._ModName, self._recordID, 8)
            diffLength -= 1
        for oLocation, nValue in zip(self.locations, nValues):
            oLocation.direct, oLocation.indirect, oLocation.gridY, oLocation.gridX = nValue
    locations = property(get_locations, set_locations)

class LVSPRecord(LVLRecord):
    def CopyAsOverride(self, targetMod):
        FID = CBash.CopyLVSPRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(True))
        if(FID): return LVSPRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def CopyAsNew(self, targetMod):
        FID = CBash.CopyLVSPRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(False))
        if(FID): return LVSPRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
class ANIORecord(BaseRecord):
    def CopyAsOverride(self, targetMod):
        FID = CBash.CopyANIORecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(True))
        if(FID): return ANIORecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def CopyAsNew(self, targetMod):
        FID = CBash.CopyANIORecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(False))
        if(FID): return ANIORecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def get_modPath(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 6)
    def set_modPath(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 6, nValue)
    modPath = property(get_modPath, set_modPath)
    def get_modb(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 7)
        if(retValue): return retValue.contents.value
        else: return None
    def set_modb(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 7, c_float(nValue))
    modb = property(get_modb, set_modb)
    def get_modt_p(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 8)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 8, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_modt_p(self, nValue):
        length = len(nValue)
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 8, struct.pack('B' * length, *nValue), length)
    modt_p = property(get_modt_p, set_modt_p)
    def get_animationId(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 9)
        if(retValue): return retValue.contents.value
        else: return None
    def set_animationId(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 9, nValue)
    animationId = property(get_animationId, set_animationId)
class WATRRecord(BaseRecord):
    def CopyAsOverride(self, targetMod):
        FID = CBash.CopyWATRRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(True))
        if(FID): return WATRRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def CopyAsNew(self, targetMod):
        FID = CBash.CopyWATRRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(False))
        if(FID): return WATRRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def get_texture(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 6)
    def set_texture(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 6, nValue)
    texture = property(get_texture, set_texture)
    def get_opacity(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 7)
        if(retValue): return retValue.contents.value
        else: return None
    def set_opacity(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 7, c_ubyte(nValue))
    opacity = property(get_opacity, set_opacity)
    def get_flags(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 8)
        if(retValue): return retValue.contents.value
        else: return None
    def set_flags(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 8, c_ubyte(nValue))
    flags = property(get_flags, set_flags)                    
    def get_material(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 9)
    def set_material(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 9, nValue)
    material = property(get_material, set_material)                    
    def get_sound(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 10)
        if(retValue): return retValue.contents.value
        else: return None
    def set_sound(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 10, nValue)
    sound = property(get_sound, set_sound)                    
    def get_windVelocity(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 11)
        if(retValue): return retValue.contents.value
        else: return None
    def set_windVelocity(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 11, c_float(nValue))
    windVelocity = property(get_windVelocity, set_windVelocity)
    def get_windDirection(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 12)
        if(retValue): return retValue.contents.value
        else: return None
    def set_windDirection(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 12, c_float(nValue))
    windDirection = property(get_windDirection, set_windDirection)
    def get_waveAmp(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 13)
        if(retValue): return retValue.contents.value
        else: return None
    def set_waveAmp(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 13, c_float(nValue))
    waveAmp = property(get_waveAmp, set_waveAmp)
    def get_waveFreq(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 14)
        if(retValue): return retValue.contents.value
        else: return None
    def set_waveFreq(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 14, c_float(nValue))
    waveFreq = property(get_waveFreq, set_waveFreq)
    def get_sunPower(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 15)
        if(retValue): return retValue.contents.value
        else: return None
    def set_sunPower(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 15, c_float(nValue))
    sunPower = property(get_sunPower, set_sunPower)
    def get_reflectAmt(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 16)
        if(retValue): return retValue.contents.value
        else: return None
    def set_reflectAmt(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 16, c_float(nValue))
    reflectAmt = property(get_reflectAmt, set_reflectAmt)
    def get_fresnelAmt(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 17)
        if(retValue): return retValue.contents.value
        else: return None
    def set_fresnelAmt(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 17, c_float(nValue))
    fresnelAmt = property(get_fresnelAmt, set_fresnelAmt)
    def get_xSpeed(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 18)
        if(retValue): return retValue.contents.value
        else: return None
    def set_xSpeed(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 18, c_float(nValue))
    xSpeed = property(get_xSpeed, set_xSpeed)
    def get_ySpeed(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 19)
        if(retValue): return retValue.contents.value
        else: return None
    def set_ySpeed(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 19, c_float(nValue))
    ySpeed = property(get_ySpeed, set_ySpeed)
    def get_fogNear(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 20)
        if(retValue): return retValue.contents.value
        else: return None
    def set_fogNear(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 20, c_float(nValue))
    fogNear = property(get_fogNear, set_fogNear)
    def get_fogFar(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 21)
        if(retValue): return retValue.contents.value
        else: return None
    def set_fogFar(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 21, c_float(nValue))
    fogFar = property(get_fogFar, set_fogFar)
    def get_shallowRed(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 22)
        if(retValue): return retValue.contents.value
        else: return None
    def set_shallowRed(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 22, c_ubyte(nValue))
    shallowRed = property(get_shallowRed, set_shallowRed)
    def get_shallowGreen(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 23)
        if(retValue): return retValue.contents.value
        else: return None
    def set_shallowGreen(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 23, c_ubyte(nValue))
    shallowGreen = property(get_shallowGreen, set_shallowGreen)
    def get_shallowBlue(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 24)
        if(retValue): return retValue.contents.value
        else: return None
    def set_shallowBlue(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 24, c_ubyte(nValue))
    shallowBlue = property(get_shallowBlue, set_shallowBlue)
    def get_unused1(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 25)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 25, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_unused1(self, nValue):
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 25, struct.pack('B', *nValue), 1)
    unused1 = property(get_unused1, set_unused1)
    def get_deepRed(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 26)
        if(retValue): return retValue.contents.value
        else: return None
    def set_deepRed(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 26, c_ubyte(nValue))
    deepRed = property(get_deepRed, set_deepRed)
    def get_deepGreen(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 27)
        if(retValue): return retValue.contents.value
        else: return None
    def set_deepGreen(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 27, c_ubyte(nValue))
    deepGreen = property(get_deepGreen, set_deepGreen)
    def get_deepBlue(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 28)
        if(retValue): return retValue.contents.value
        else: return None
    def set_deepBlue(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 28, c_ubyte(nValue))
    deepBlue = property(get_deepBlue, set_deepBlue)
    def get_unused2(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 29)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 29, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_unused2(self, nValue):
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 29, struct.pack('B', *nValue), 1)
    unused2 = property(get_unused2, set_unused2)
    def get_reflRed(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 30)
        if(retValue): return retValue.contents.value
        else: return None
    def set_reflRed(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 30, c_ubyte(nValue))
    reflRed = property(get_reflRed, set_reflRed)
    def get_reflGreen(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 31)
        if(retValue): return retValue.contents.value
        else: return None
    def set_reflGreen(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 31, c_ubyte(nValue))
    reflGreen = property(get_reflGreen, set_reflGreen)
    def get_reflBlue(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 32)
        if(retValue): return retValue.contents.value
        else: return None
    def set_reflBlue(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 32, c_ubyte(nValue))
    reflBlue = property(get_reflBlue, set_reflBlue)                    
    def get_unused3(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 33)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 33, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_unused3(self, nValue):
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 33, struct.pack('B', *nValue), 1)
    unused3 = property(get_unused3, set_unused3)
    def get_blend(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 34)
        if(retValue): return retValue.contents.value
        else: return None
    def set_blend(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 34, c_ubyte(nValue))
    blend = property(get_blend, set_blend)
    def get_unused4(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 35)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 35, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_unused4(self, nValue):
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 35, struct.pack('3B', *nValue), 3)
    unused4 = property(get_unused4, set_unused4)
    def get_rainForce(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 36)
        if(retValue): return retValue.contents.value
        else: return None
    def set_rainForce(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 36, c_float(nValue))
    rainForce = property(get_rainForce, set_rainForce)
    def get_rainVelocity(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 37)
        if(retValue): return retValue.contents.value
        else: return None
    def set_rainVelocity(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 37, c_float(nValue))
    rainVelocity = property(get_rainVelocity, set_rainVelocity)
    def get_rainFalloff(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 38)
        if(retValue): return retValue.contents.value
        else: return None
    def set_rainFalloff(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 38, c_float(nValue))
    rainFalloff = property(get_rainFalloff, set_rainFalloff)
    def get_rainDampner(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 39)
        if(retValue): return retValue.contents.value
        else: return None
    def set_rainDampner(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 39, c_float(nValue))
    rainDampner = property(get_rainDampner, set_rainDampner)
    def get_rainSize(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 40)
        if(retValue): return retValue.contents.value
        else: return None
    def set_rainSize(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 40, c_float(nValue))
    rainSize = property(get_rainSize, set_rainSize)
    def get_dispForce(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 41)
        if(retValue): return retValue.contents.value
        else: return None
    def set_dispForce(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 41, c_float(nValue))
    dispForce = property(get_dispForce, set_dispForce)
    def get_dispVelocity(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 42)
        if(retValue): return retValue.contents.value
        else: return None
    def set_dispVelocity(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 42, c_float(nValue))
    dispVelocity = property(get_dispVelocity, set_dispVelocity)
    def get_dispFalloff(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 43)
        if(retValue): return retValue.contents.value
        else: return None
    def set_dispFalloff(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 43, c_float(nValue))
    dispFalloff = property(get_dispFalloff, set_dispFalloff)
    def get_dispDampner(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 44)
        if(retValue): return retValue.contents.value
        else: return None
    def set_dispDampner(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 44, c_float(nValue))
    dispDampner = property(get_dispDampner, set_dispDampner)
    def get_dispSize(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 45)
        if(retValue): return retValue.contents.value
        else: return None
    def set_dispSize(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 45, c_float(nValue))
    dispSize = property(get_dispSize, set_dispSize)
    def get_damage(self):
        CBash.ReadFIDField.restype = POINTER(c_ushort)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 46)
        if(retValue): return retValue.contents.value
        else: return None
    def set_damage(self, nValue):
        CBash.SetFIDFieldUS(self._CollectionIndex, self._ModName, self._recordID, 46, c_ushort(nValue))
    damage = property(get_damage, set_damage)                    
    def get_dayWater(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 47)
        if(retValue): return retValue.contents.value
        else: return None
    def set_dayWater(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 47, nValue)
    dayWater = property(get_dayWater, set_dayWater)
    def get_nightWater(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 48)
        if(retValue): return retValue.contents.value
        else: return None
    def set_nightWater(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 48, nValue)
    nightWater = property(get_nightWater, set_nightWater)
    def get_underWater(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 49)
        if(retValue): return retValue.contents.value
        else: return None
    def set_underWater(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 49, nValue)
    underWater = property(get_underWater, set_underWater)    
class EFSHRecord(BaseRecord):
    def CopyAsOverride(self, targetMod):
        FID = CBash.CopyEFSHRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(True))
        if(FID): return EFSHRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def CopyAsNew(self, targetMod):
        FID = CBash.CopyEFSHRecord(self._CollectionIndex, self._ModName, self._recordID, targetMod._ModName, c_bool(False))
        if(FID): return EFSHRecord(self._CollectionIndex, targetMod._ModName, FID)
        return None
    def get_fillTexture(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 6)
    def set_fillTexture(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 6, nValue)
    fillTexture = property(get_fillTexture, set_fillTexture)
    def get_particleTexture(self):
        CBash.ReadFIDField.restype = c_char_p
        return CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 7)
    def set_particleTexture(self, nValue):
        CBash.SetFIDFieldStr(self._CollectionIndex, self._ModName, self._recordID, 7, nValue)
    particleTexture = property(get_particleTexture, set_particleTexture)
    def get_flags(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 8)
        if(retValue): return retValue.contents.value
        else: return None
    def set_flags(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 8, c_ubyte(nValue))
    flags = property(get_flags, set_flags)
    def get_unused1(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 9)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 9, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_unused1(self, nValue):
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 9, struct.pack('3B', *nValue), 3)
    unused1 = property(get_unused1, set_unused1)
    def get_memSBlend(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 10)
        if(retValue): return retValue.contents.value
        else: return None
    def set_memSBlend(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 10, nValue)
    memSBlend = property(get_memSBlend, set_memSBlend)
    def get_memBlendOp(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 11)
        if(retValue): return retValue.contents.value
        else: return None
    def set_memBlendOp(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 11, nValue)
    memBlendOp = property(get_memBlendOp, set_memBlendOp)
    def get_memZFunc(self):
        CBash.ReadFIDField.restype = POINTER(c_uint)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 12)
        if(retValue): return retValue.contents.value
        else: return None
    def set_memZFunc(self, nValue):
        CBash.SetFIDFieldUI(self._CollectionIndex, self._ModName, self._recordID, 12, nValue)
    memZFunc = property(get_memZFunc, set_memZFunc)
    def get_fillRed(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 13)
        if(retValue): return retValue.contents.value
        else: return None
    def set_fillRed(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 13, c_ubyte(nValue))
    fillRed = property(get_fillRed, set_fillRed)
    def get_fillGreen(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 14)
        if(retValue): return retValue.contents.value
        else: return None
    def set_fillGreen(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 14, c_ubyte(nValue))
    fillGreen = property(get_fillGreen, set_fillGreen)
    def get_fillBlue(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 15)
        if(retValue): return retValue.contents.value
        else: return None
    def set_fillBlue(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 15, c_ubyte(nValue))
    fillBlue = property(get_fillBlue, set_fillBlue)
    def get_unused2(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 16)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 16, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_unused2(self, nValue):
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 16, struct.pack('B', *nValue), 1)
    unused2 = property(get_unused2, set_unused2)
    def get_fillAIn(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 17)
        if(retValue): return retValue.contents.value
        else: return None
    def set_fillAIn(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 17, c_float(nValue))
    fillAIn = property(get_fillAIn, set_fillAIn)
    def get_fillAFull(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 18)
        if(retValue): return retValue.contents.value
        else: return None
    def set_fillAFull(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 18, c_float(nValue))
    fillAFull = property(get_fillAFull, set_fillAFull)
    def get_fillAOut(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 19)
        if(retValue): return retValue.contents.value
        else: return None
    def set_fillAOut(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 19, c_float(nValue))
    fillAOut = property(get_fillAOut, set_fillAOut)
    def get_fillAPRatio(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 20)
        if(retValue): return retValue.contents.value
        else: return None
    def set_fillAPRatio(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 20, c_float(nValue))
    fillAPRatio = property(get_fillAPRatio, set_fillAPRatio)
    def get_fillAAmp(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 21)
        if(retValue): return retValue.contents.value
        else: return None
    def set_fillAAmp(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 21, c_float(nValue))
    fillAAmp = property(get_fillAAmp, set_fillAAmp)
    def get_fillAFreq(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 22)
        if(retValue): return retValue.contents.value
        else: return None
    def set_fillAFreq(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 22, c_float(nValue))
    fillAFreq = property(get_fillAFreq, set_fillAFreq)
    def get_fillAnimSpdU(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 23)
        if(retValue): return retValue.contents.value
        else: return None
    def set_fillAnimSpdU(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 23, c_float(nValue))
    fillAnimSpdU = property(get_fillAnimSpdU, set_fillAnimSpdU)
    def get_fillAnimSpdV(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 24)
        if(retValue): return retValue.contents.value
        else: return None
    def set_fillAnimSpdV(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 24, c_float(nValue))
    fillAnimSpdV = property(get_fillAnimSpdV, set_fillAnimSpdV)
    def get_edgeOff(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 25)
        if(retValue): return retValue.contents.value
        else: return None
    def set_edgeOff(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 25, c_float(nValue))
    edgeOff = property(get_edgeOff, set_edgeOff)
    def get_edgeRed(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 26)
        if(retValue): return retValue.contents.value
        else: return None
    def set_edgeRed(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 26, c_ubyte(nValue))
    edgeRed = property(get_edgeRed, set_edgeRed)
    def get_edgeGreen(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 27)
        if(retValue): return retValue.contents.value
        else: return None
    def set_edgeGreen(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 27, c_ubyte(nValue))
    edgeGreen = property(get_edgeGreen, set_edgeGreen)
    def get_edgeBlue(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 28)
        if(retValue): return retValue.contents.value
        else: return None
    def set_edgeBlue(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 28, c_ubyte(nValue))
    edgeBlue = property(get_edgeBlue, set_edgeBlue)
    def get_unused3(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 29)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 29, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_unused3(self, nValue):
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 29, struct.pack('B', *nValue), 1)
    unused3 = property(get_unused3, set_unused3)
    def get_edgeAIn(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 30)
        if(retValue): return retValue.contents.value
        else: return None
    def set_edgeAIn(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 30, c_float(nValue))
    edgeAIn = property(get_edgeAIn, set_edgeAIn)
    def get_edgeAFull(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 31)
        if(retValue): return retValue.contents.value
        else: return None
    def set_edgeAFull(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 31, c_float(nValue))
    edgeAFull = property(get_edgeAFull, set_edgeAFull)
    def get_edgeAOut(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 32)
        if(retValue): return retValue.contents.value
        else: return None
    def set_edgeAOut(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 32, c_float(nValue))
    edgeAOut = property(get_edgeAOut, set_edgeAOut)
    def get_edgeAPRatio(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 33)
        if(retValue): return retValue.contents.value
        else: return None
    def set_edgeAPRatio(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 33, c_float(nValue))
    edgeAPRatio = property(get_edgeAPRatio, set_edgeAPRatio)
    def get_edgeAAmp(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 34)
        if(retValue): return retValue.contents.value
        else: return None
    def set_edgeAAmp(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 34, c_float(nValue))
    edgeAAmp = property(get_edgeAAmp, set_edgeAAmp)
    def get_edgeAFreq(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 35)
        if(retValue): return retValue.contents.value
        else: return None
    def set_edgeAFreq(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 35, c_float(nValue))
    edgeAFreq = property(get_edgeAFreq, set_edgeAFreq)
    def get_fillAFRatio(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 36)
        if(retValue): return retValue.contents.value
        else: return None
    def set_fillAFRatio(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 36, c_float(nValue))
    fillAFRatio = property(get_fillAFRatio, set_fillAFRatio)
    def get_edgeAFRatio(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 37)
        if(retValue): return retValue.contents.value
        else: return None
    def set_edgeAFRatio(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 37, c_float(nValue))
    edgeAFRatio = property(get_edgeAFRatio, set_edgeAFRatio)
    def get_memDBlend(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 38)
        if(retValue): return retValue.contents.value
        else: return None
    def set_memDBlend(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 38, c_ubyte(nValue))
    memDBlend = property(get_memDBlend, set_memDBlend)
    def get_partSBlend(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 39)
        if(retValue): return retValue.contents.value
        else: return None
    def set_partSBlend(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 39, c_ubyte(nValue))
    partSBlend = property(get_partSBlend, set_partSBlend)
    def get_partBlendOp(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 40)
        if(retValue): return retValue.contents.value
        else: return None
    def set_partBlendOp(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 40, c_ubyte(nValue))
    partBlendOp = property(get_partBlendOp, set_partBlendOp)
    def get_partZFunc(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 41)
        if(retValue): return retValue.contents.value
        else: return None
    def set_partZFunc(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 41, c_ubyte(nValue))
    partZFunc = property(get_partZFunc, set_partZFunc)
    def get_partDBlend(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 42)
        if(retValue): return retValue.contents.value
        else: return None
    def set_partDBlend(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 42, c_ubyte(nValue))
    partDBlend = property(get_partDBlend, set_partDBlend)
    def get_partBUp(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 43)
        if(retValue): return retValue.contents.value
        else: return None
    def set_partBUp(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 43, c_float(nValue))
    partBUp = property(get_partBUp, set_partBUp)
    def get_partBFull(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 44)
        if(retValue): return retValue.contents.value
        else: return None
    def set_partBFull(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 44, c_float(nValue))
    partBFull = property(get_partBFull, set_partBFull)
    def get_partBDown(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 45)
        if(retValue): return retValue.contents.value
        else: return None
    def set_partBDown(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 45, c_float(nValue))
    partBDown = property(get_partBDown, set_partBDown)
    def get_partBFRatio(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 46)
        if(retValue): return retValue.contents.value
        else: return None
    def set_partBFRatio(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 46, c_float(nValue))
    partBFRatio = property(get_partBFRatio, set_partBFRatio)
    def get_partBPRatio(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 47)
        if(retValue): return retValue.contents.value
        else: return None
    def set_partBPRatio(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 47, c_float(nValue))
    partBPRatio = property(get_partBPRatio, set_partBPRatio)
    def get_partLTime(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 48)
        if(retValue): return retValue.contents.value
        else: return None
    def set_partLTime(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 48, c_float(nValue))
    partLTime = property(get_partLTime, set_partLTime)
    def get_partLDelta(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 49)
        if(retValue): return retValue.contents.value
        else: return None
    def set_partLDelta(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 49, c_float(nValue))
    partLDelta = property(get_partLDelta, set_partLDelta)
    def get_partNSpd(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 50)
        if(retValue): return retValue.contents.value
        else: return None
    def set_partNSpd(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 50, c_float(nValue))
    partNSpd = property(get_partNSpd, set_partNSpd)
    def get_partNAcc(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 51)
        if(retValue): return retValue.contents.value
        else: return None
    def set_partNAcc(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 51, c_float(nValue))
    partNAcc = property(get_partNAcc, set_partNAcc)
    def get_partVel1(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 52)
        if(retValue): return retValue.contents.value
        else: return None
    def set_partVel1(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 52, c_float(nValue))
    partVel1 = property(get_partVel1, set_partVel1)
    def get_partVel2(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 53)
        if(retValue): return retValue.contents.value
        else: return None
    def set_partVel2(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 53, c_float(nValue))
    partVel2 = property(get_partVel2, set_partVel2)
    def get_partVel3(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 54)
        if(retValue): return retValue.contents.value
        else: return None
    def set_partVel3(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 54, c_float(nValue))
    partVel3 = property(get_partVel3, set_partVel3)
    def get_partAcc1(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 55)
        if(retValue): return retValue.contents.value
        else: return None
    def set_partAcc1(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 55, c_float(nValue))
    partAcc1 = property(get_partAcc1, set_partAcc1)
    def get_partAcc2(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 56)
        if(retValue): return retValue.contents.value
        else: return None
    def set_partAcc2(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 56, c_float(nValue))
    partAcc2 = property(get_partAcc2, set_partAcc2)
    def get_partAcc3(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 57)
        if(retValue): return retValue.contents.value
        else: return None
    def set_partAcc3(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 57, c_float(nValue))
    partAcc3 = property(get_partAcc3, set_partAcc3)
    def get_partKey1(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 58)
        if(retValue): return retValue.contents.value
        else: return None
    def set_partKey1(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 58, c_float(nValue))
    partKey1 = property(get_partKey1, set_partKey1)
    def get_partKey2(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 59)
        if(retValue): return retValue.contents.value
        else: return None
    def set_partKey2(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 59, c_float(nValue))
    partKey2 = property(get_partKey2, set_partKey2)
    def get_partKey1Time(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 60)
        if(retValue): return retValue.contents.value
        else: return None
    def set_partKey1Time(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 60, c_float(nValue))
    partKey1Time = property(get_partKey1Time, set_partKey1Time)
    def get_partKey2Time(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 61)
        if(retValue): return retValue.contents.value
        else: return None
    def set_partKey2Time(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 61, c_float(nValue))
    partKey2Time = property(get_partKey2Time, set_partKey2Time)
    def get_key1Red(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 62)
        if(retValue): return retValue.contents.value
        else: return None
    def set_key1Red(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 62, c_ubyte(nValue))
    key1Red = property(get_key1Red, set_key1Red)
    def get_key1Green(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 63)
        if(retValue): return retValue.contents.value
        else: return None
    def set_key1Green(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 63, c_ubyte(nValue))
    key1Green = property(get_key1Green, set_key1Green)
    def get_key1Blue(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 64)
        if(retValue): return retValue.contents.value
        else: return None
    def set_key1Blue(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 64, c_ubyte(nValue))
    key1Blue = property(get_key1Blue, set_key1Blue)
    def get_unused4(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 65)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 65, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_unused4(self, nValue):
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 65, struct.pack('B', *nValue), 1)
    unused4 = property(get_unused4, set_unused4)
    def get_key2Red(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 66)
        if(retValue): return retValue.contents.value
        else: return None
    def set_key2Red(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 66, c_ubyte(nValue))
    key2Red = property(get_key2Red, set_key2Red)
    def get_key2Green(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 67)
        if(retValue): return retValue.contents.value
        else: return None
    def set_key2Green(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 67, c_ubyte(nValue))
    key2Green = property(get_key2Green, set_key2Green)
    def get_key2Blue(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 68)
        if(retValue): return retValue.contents.value
        else: return None
    def set_key2Blue(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 68, c_ubyte(nValue))
    key2Blue = property(get_key2Blue, set_key2Blue)
    def get_unused5(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 69)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 69, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_unused5(self, nValue):
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 69, struct.pack('B', *nValue), 1)
    unused5 = property(get_unused5, set_unused5)
    def get_key3Red(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 70)
        if(retValue): return retValue.contents.value
        else: return None
    def set_key3Red(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 70, c_ubyte(nValue))
    key3Red = property(get_key3Red, set_key3Red)
    def get_key3Green(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 71)
        if(retValue): return retValue.contents.value
        else: return None
    def set_key3Green(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 71, c_ubyte(nValue))
    key3Green = property(get_key3Green, set_key3Green)
    def get_key3Blue(self):
        CBash.ReadFIDField.restype = POINTER(c_ubyte)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 72)
        if(retValue): return retValue.contents.value
        else: return None
    def set_key3Blue(self, nValue):
        CBash.SetFIDFieldUC(self._CollectionIndex, self._ModName, self._recordID, 72, c_ubyte(nValue))
    key3Blue = property(get_key3Blue, set_key3Blue)
    def get_unused6(self):
        numRecords = CBash.GetFIDFieldArraySize(self._CollectionIndex, self._ModName, self._recordID, 73)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            CBash.GetFIDFieldArray(self._CollectionIndex, self._ModName, self._recordID, 73, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        else: return []
    def set_unused6(self, nValue):
        CBash.SetFIDFieldR(self._CollectionIndex, self._ModName, self._recordID, 73, struct.pack('B', *nValue), 1)
    unused6 = property(get_unused6, set_unused6)
    def get_key1A(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 74)
        if(retValue): return retValue.contents.value
        else: return None
    def set_key1A(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 74, c_float(nValue))
    key1A = property(get_key1A, set_key1A)
    def get_key2A(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 75)
        if(retValue): return retValue.contents.value
        else: return None
    def set_key2A(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 75, c_float(nValue))
    key2A = property(get_key2A, set_key2A)
    def get_key3A(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 76)
        if(retValue): return retValue.contents.value
        else: return None
    def set_key3A(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 76, c_float(nValue))
    key3A = property(get_key3A, set_key3A)
    def get_key1Time(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 77)
        if(retValue): return retValue.contents.value
        else: return None
    def set_key1Time(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 77, c_float(nValue))
    key1Time = property(get_key1Time, set_key1Time)
    def get_key2Time(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 78)
        if(retValue): return retValue.contents.value
        else: return None
    def set_key2Time(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 78, c_float(nValue))
    key2Time = property(get_key2Time, set_key2Time)
    def get_key3Time(self):
        CBash.ReadFIDField.restype = POINTER(c_float)
        retValue = CBash.ReadFIDField(self._CollectionIndex, self._ModName, self._recordID, 79)
        if(retValue): return retValue.contents.value
        else: return None
    def set_key3Time(self, nValue):
        CBash.SetFIDFieldF(self._CollectionIndex, self._ModName, self._recordID, 79, c_float(nValue))
    key3Time = property(get_key3Time, set_key3Time)

class ModFile(object):
    def __init__(self, CollectionIndex, ModName=None):
        self._CollectionIndex = CollectionIndex
        self._ModName = ModName

    def createGMSTRecord(self, recordID):
        if(CBash.CreateGMSTRecord(self._CollectionIndex, self._ModName, recordID)):
            return GMSTRecord(self._CollectionIndex, self._ModName, recordID)
        return None
    def createGLOBRecord(self):
        FID = CBash.CreateGLOBRecord(self._CollectionIndex, self._ModName)
        if(FID): return GLOBRecord(self._CollectionIndex, self._ModName, FID)
        return None
    def createCLASRecord(self):
        FID = CBash.CreateCLASRecord(self._CollectionIndex, self._ModName)
        if(FID): return CLASRecord(self._CollectionIndex, self._ModName, FID)
        return None
    def createFACTRecord(self):
        FID = CBash.CreateFACTRecord(self._CollectionIndex, self._ModName)
        if(FID): return FACTRecord(self._CollectionIndex, self._ModName, FID)
        return None
    def createHAIRRecord(self):
        FID = CBash.CreateHAIRRecord(self._CollectionIndex, self._ModName)
        if(FID): return HAIRRecord(self._CollectionIndex, self._ModName, FID)
        return None
    def createEYESRecord(self):
        FID = CBash.CreateEYESRecord(self._CollectionIndex, self._ModName)
        if(FID): return EYESRecord(self._CollectionIndex, self._ModName, FID)
        return None
    def createRACERecord(self):
        FID = CBash.CreateRACERecord(self._CollectionIndex, self._ModName)
        if(FID): return RACERecord(self._CollectionIndex, self._ModName, FID)
        return None
    def createSOUNRecord(self):
        FID = CBash.CreateSOUNRecord(self._CollectionIndex, self._ModName)
        if(FID): return SOUNRecord(self._CollectionIndex, self._ModName, FID)
        return None
    def createSKILRecord(self):
        FID = CBash.CreateSKILRecord(self._CollectionIndex, self._ModName)
        if(FID): return SKILRecord(self._CollectionIndex, self._ModName, FID)
        return None
    def createMGEFRecord(self):
        FID = CBash.CreateMGEFRecord(self._CollectionIndex, self._ModName)
        if(FID): return MGEFRecord(self._CollectionIndex, self._ModName, FID)
        return None
    def createSCPTRecord(self):
        FID = CBash.CreateSCPTRecord(self._CollectionIndex, self._ModName)
        if(FID): return SCPTRecord(self._CollectionIndex, self._ModName, FID)
        return None
    def createLTEXRecord(self):
        FID = CBash.CreateLTEXRecord(self._CollectionIndex, self._ModName)
        if(FID): return LTEXRecord(self._CollectionIndex, self._ModName, FID)
        return None
    def createENCHRecord(self):
        FID = CBash.CreateENCHRecord(self._CollectionIndex, self._ModName)
        if(FID): return ENCHRecord(self._CollectionIndex, self._ModName, FID)
        return None
    def createSPELRecord(self):
        FID = CBash.CreateSPELRecord(self._CollectionIndex, self._ModName)
        if(FID): return SPELRecord(self._CollectionIndex, self._ModName, FID)
        return None
    def createBSGNRecord(self):
        FID = CBash.CreateBSGNRecord(self._CollectionIndex, self._ModName)
        if(FID): return BSGNRecord(self._CollectionIndex, self._ModName, FID)
        return None
    def createACTIRecord(self):
        FID = CBash.CreateACTIRecord(self._CollectionIndex, self._ModName)
        if(FID): return ACTIRecord(self._CollectionIndex, self._ModName, FID)
        return None
    def createAPPARecord(self):
        FID = CBash.CreateAPPARecord(self._CollectionIndex, self._ModName)
        if(FID): return APPARecord(self._CollectionIndex, self._ModName, FID)
        return None
    def createARMORecord(self):
        FID = CBash.CreateARMORecord(self._CollectionIndex, self._ModName)
        if(FID): return ARMORecord(self._CollectionIndex, self._ModName, FID)
        return None
    def createBOOKRecord(self):
        FID = CBash.CreateBOOKRecord(self._CollectionIndex, self._ModName)
        if(FID): return BOOKRecord(self._CollectionIndex, self._ModName, FID)
        return None
    def createCLOTRecord(self):
        FID = CBash.CreateCLOTRecord(self._CollectionIndex, self._ModName)
        if(FID): return CLOTRecord(self._CollectionIndex, self._ModName, FID)
        return None
    def createCONTRecord(self):
        FID = CBash.CreateCONTRecord(self._CollectionIndex, self._ModName)
        if(FID): return CONTRecord(self._CollectionIndex, self._ModName, FID)
        return None
    def createDOORRecord(self):
        FID = CBash.CreateDOORRecord(self._CollectionIndex, self._ModName)
        if(FID): return DOORRecord(self._CollectionIndex, self._ModName, FID)
        return None
    def createINGRRecord(self):
        FID = CBash.CreateINGRRecord(self._CollectionIndex, self._ModName)
        if(FID): return INGRRecord(self._CollectionIndex, self._ModName, FID)
        return None
    def createLIGHRecord(self):
        FID = CBash.CreateLIGHRecord(self._CollectionIndex, self._ModName)
        if(FID): return LIGHRecord(self._CollectionIndex, self._ModName, FID)
        return None
    def createMISCRecord(self):
        FID = CBash.CreateMISCRecord(self._CollectionIndex, self._ModName)
        if(FID): return MISCRecord(self._CollectionIndex, self._ModName, FID)
        return None
    def createSTATRecord(self):
        FID = CBash.CreateSTATRecord(self._CollectionIndex, self._ModName)
        if(FID): return STATRecord(self._CollectionIndex, self._ModName, FID)
        return None
    def createGRASRecord(self):
        FID = CBash.CreateGRASRecord(self._CollectionIndex, self._ModName)
        if(FID): return GRASRecord(self._CollectionIndex, self._ModName, FID)
        return None
    def createTREERecord(self):
        FID = CBash.CreateTREERecord(self._CollectionIndex, self._ModName)
        if(FID): return TREERecord(self._CollectionIndex, self._ModName, FID)
        return None
    def createFLORRecord(self):
        FID = CBash.CreateFLORRecord(self._CollectionIndex, self._ModName)
        if(FID): return FLORRecord(self._CollectionIndex, self._ModName, FID)
        return None
    def createFURNRecord(self):
        FID = CBash.CreateFURNRecord(self._CollectionIndex, self._ModName)
        if(FID): return FURNRecord(self._CollectionIndex, self._ModName, FID)
        return None
    def createWEAPRecord(self):
        FID = CBash.CreateWEAPRecord(self._CollectionIndex, self._ModName)
        if(FID): return WEAPRecord(self._CollectionIndex, self._ModName, FID)
        return None
    def createAMMORecord(self):
        FID = CBash.CreateAMMORecord(self._CollectionIndex, self._ModName)
        if(FID): return AMMORecord(self._CollectionIndex, self._ModName, FID)
        return None
    def createNPC_Record(self):
        FID = CBash.CreateNPC_Record(self._CollectionIndex, self._ModName)
        if(FID): return NPC_Record(self._CollectionIndex, self._ModName, FID)
        return None
    def createCREARecord(self):
        FID = CBash.CreateCREARecord(self._CollectionIndex, self._ModName)
        if(FID): return CREARecord(self._CollectionIndex, self._ModName, FID)
        return None
    def createLVLCRecord(self):
        FID = CBash.CreateLVLCRecord(self._CollectionIndex, self._ModName)
        if(FID): return LVLCRecord(self._CollectionIndex, self._ModName, FID)
        return None
    def createSLGMRecord(self):
        FID = CBash.CreateSLGMRecord(self._CollectionIndex, self._ModName)
        if(FID): return SLGMRecord(self._CollectionIndex, self._ModName, FID)
        return None
    def createKEYMRecord(self):
        FID = CBash.CreateKEYMRecord(self._CollectionIndex, self._ModName)
        if(FID): return KEYMRecord(self._CollectionIndex, self._ModName, FID)
        return None
    def createALCHRecord(self):
        FID = CBash.CreateALCHRecord(self._CollectionIndex, self._ModName)
        if(FID): return ALCHRecord(self._CollectionIndex, self._ModName, FID)
        return None
    def createSBSPRecord(self):
        FID = CBash.CreateSBSPRecord(self._CollectionIndex, self._ModName)
        if(FID): return SBSPRecord(self._CollectionIndex, self._ModName, FID)
        return None
    def createSGSTRecord(self):
        FID = CBash.CreateSGSTRecord(self._CollectionIndex, self._ModName)
        if(FID): return SGSTRecord(self._CollectionIndex, self._ModName, FID)
        return None
    def createLVLIRecord(self):
        FID = CBash.CreateLVLIRecord(self._CollectionIndex, self._ModName)
        if(FID): return LVLIRecord(self._CollectionIndex, self._ModName, FID)
        return None
    def createWTHRRecord(self):
        FID = CBash.CreateWTHRRecord(self._CollectionIndex, self._ModName)
        if(FID): return WTHRRecord(self._CollectionIndex, self._ModName, FID)
        return None
    def createCLMTRecord(self):
        FID = CBash.CreateCLMTRecord(self._CollectionIndex, self._ModName)
        if(FID): return CLMTRecord(self._CollectionIndex, self._ModName, FID)
        return None
    def createREGNRecord(self):
        FID = CBash.CreateREGNRecord(self._CollectionIndex, self._ModName)
        if(FID): return REGNRecord(self._CollectionIndex, self._ModName, FID)
        return None
    def createCELLRecord(self):
        FID = CBash.CreateCELLRecord(self._CollectionIndex, self._ModName, 0)
        if(FID): return CELLRecord(self._CollectionIndex, self._ModName, FID)
        return None
    def createWRLDRecord(self):
        FID = CBash.CreateWRLDRecord(self._CollectionIndex, self._ModName)
        if(FID): return WRLDRecord(self._CollectionIndex, self._ModName, FID)
        return None
    def createDIALRecord(self):
        FID = CBash.CreateDIALRecord(self._CollectionIndex, self._ModName)
        if(FID): return DIALRecord(self._CollectionIndex, self._ModName, FID)
        return None
    def createQUSTRecord(self):
        FID = CBash.CreateQUSTRecord(self._CollectionIndex, self._ModName)
        if(FID): return QUSTRecord(self._CollectionIndex, self._ModName, FID)
        return None
    def createIDLERecord(self):
        FID = CBash.CreateIDLERecord(self._CollectionIndex, self._ModName)
        if(FID): return IDLERecord(self._CollectionIndex, self._ModName, FID)
        return None
    def createPACKRecord(self):
        FID = CBash.CreatePACKRecord(self._CollectionIndex, self._ModName)
        if(FID): return PACKRecord(self._CollectionIndex, self._ModName, FID)
        return None
    def createCSTYRecord(self):
        FID = CBash.CreateCSTYRecord(self._CollectionIndex, self._ModName)
        if(FID): return CSTYRecord(self._CollectionIndex, self._ModName, FID)
        return None
    def createLSCRRecord(self):
        FID = CBash.CreateLSCRRecord(self._CollectionIndex, self._ModName)
        if(FID): return LSCRRecord(self._CollectionIndex, self._ModName, FID)
        return None
    def createLVSPRecord(self):
        FID = CBash.CreateLVSPRecord(self._CollectionIndex, self._ModName)
        if(FID): return LVSPRecord(self._CollectionIndex, self._ModName, FID)
        return None
    def createANIORecord(self):
        FID = CBash.CreateANIORecord(self._CollectionIndex, self._ModName)
        if(FID): return ANIORecord(self._CollectionIndex, self._ModName, FID)
        return None
    def createWATRRecord(self):
        FID = CBash.CreateWATRRecord(self._CollectionIndex, self._ModName)
        if(FID): return WATRRecord(self._CollectionIndex, self._ModName, FID)
        return None
    def createEFSHRecord(self):
        FID = CBash.CreateEFSHRecord(self._CollectionIndex, self._ModName)
        if(FID): return EFSHRecord(self._CollectionIndex, self._ModName, FID)
        return None

    def safeSave(self):
        return CBash.SafeSaveMod(self._CollectionIndex, self._ModName)
    @property
    def TES4(self):
        return TES4Record(self._CollectionIndex, self._ModName)

    @property
    def GMST(self):
        numRecords = CBash.GetNumGMSTRecords(self._CollectionIndex, self._ModName)
        if(numRecords > 0):
            cRecords = (POINTER(c_char_p) * numRecords)()
            CBash.GetGMSTs(self._CollectionIndex, self._ModName, cRecords)
            return [GMSTRecord(self._CollectionIndex, self._ModName, string_at(cRecords[x])) for x in range(0, numRecords)]
        else: return []
    @property
    def GLOB(self):
        numRecords = CBash.GetNumGLOBRecords(self._CollectionIndex, self._ModName)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetGLOBRecords(self._CollectionIndex, self._ModName, cRecords)
            return [GLOBRecord(self._CollectionIndex, self._ModName, x.contents.value) for x in cRecords]
        else: return []
    @property
    def CLAS(self):
        numRecords = CBash.GetNumCLASRecords(self._CollectionIndex, self._ModName)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetCLASRecords(self._CollectionIndex, self._ModName, cRecords)
            return [CLASRecord(self._CollectionIndex, self._ModName, x.contents.value) for x in cRecords]
        else: return []
    @property
    def FACT(self):
        numRecords = CBash.GetNumFACTRecords(self._CollectionIndex, self._ModName)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetFACTRecords(self._CollectionIndex, self._ModName, cRecords)
            return [FACTRecord(self._CollectionIndex, self._ModName, x.contents.value) for x in cRecords]
        else: return []
    @property
    def HAIR(self):
        numRecords = CBash.GetNumHAIRRecords(self._CollectionIndex, self._ModName)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetHAIRRecords(self._CollectionIndex, self._ModName, cRecords)
            return [HAIRRecord(self._CollectionIndex, self._ModName, x.contents.value) for x in cRecords]
        else: return []
    @property
    def EYES(self):
        numRecords = CBash.GetNumEYESRecords(self._CollectionIndex, self._ModName)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetEYESRecords(self._CollectionIndex, self._ModName, cRecords)
            return [EYESRecord(self._CollectionIndex, self._ModName, x.contents.value) for x in cRecords]
        else: return []
    @property
    def RACE(self):
        numRecords = CBash.GetNumRACERecords(self._CollectionIndex, self._ModName)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetRACERecords(self._CollectionIndex, self._ModName, cRecords)
            return [RACERecord(self._CollectionIndex, self._ModName, x.contents.value) for x in cRecords]
        else: return []
    @property
    def SOUN(self):
        numRecords = CBash.GetNumSOUNRecords(self._CollectionIndex, self._ModName)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetSOUNRecords(self._CollectionIndex, self._ModName, cRecords)
            return [SOUNRecord(self._CollectionIndex, self._ModName, x.contents.value) for x in cRecords]
        else: return []
    @property
    def SKIL(self):
        numRecords = CBash.GetNumSKILRecords(self._CollectionIndex, self._ModName)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetSKILRecords(self._CollectionIndex, self._ModName, cRecords)
            return [SKILRecord(self._CollectionIndex, self._ModName, x.contents.value) for x in cRecords]
        else: return []
    @property
    def MGEF(self):
        numRecords = CBash.GetNumMGEFRecords(self._CollectionIndex, self._ModName)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetMGEFRecords(self._CollectionIndex, self._ModName, cRecords)
            return [MGEFRecord(self._CollectionIndex, self._ModName, x.contents.value) for x in cRecords]
        else: return []
    @property
    def SCPT(self):
        numRecords = CBash.GetNumSCPTRecords(self._CollectionIndex, self._ModName)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetSCPTRecords(self._CollectionIndex, self._ModName, cRecords)
            return [SCPTRecord(self._CollectionIndex, self._ModName, x.contents.value) for x in cRecords]
        else: return []
    @property
    def LTEX(self):
        numRecords = CBash.GetNumLTEXRecords(self._CollectionIndex, self._ModName)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetLTEXRecords(self._CollectionIndex, self._ModName, cRecords)
            return [LTEXRecord(self._CollectionIndex, self._ModName, x.contents.value) for x in cRecords]
        else: return []
    @property
    def ENCH(self):
        numRecords = CBash.GetNumENCHRecords(self._CollectionIndex, self._ModName)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetENCHRecords(self._CollectionIndex, self._ModName, cRecords)
            return [ENCHRecord(self._CollectionIndex, self._ModName, x.contents.value) for x in cRecords]
        else: return []
    @property
    def SPEL(self):
        numRecords = CBash.GetNumSPELRecords(self._CollectionIndex, self._ModName)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetSPELRecords(self._CollectionIndex, self._ModName, cRecords)
            return [SPELRecord(self._CollectionIndex, self._ModName, x.contents.value) for x in cRecords]
        else: return []
    @property
    def BSGN(self):
        numRecords = CBash.GetNumBSGNRecords(self._CollectionIndex, self._ModName)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetBSGNRecords(self._CollectionIndex, self._ModName, cRecords)
            return [BSGNRecord(self._CollectionIndex, self._ModName, x.contents.value) for x in cRecords]
        else: return []
    @property
    def ACTI(self):
        numRecords = CBash.GetNumACTIRecords(self._CollectionIndex, self._ModName)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetACTIRecords(self._CollectionIndex, self._ModName, cRecords)
            return [ACTIRecord(self._CollectionIndex, self._ModName, x.contents.value) for x in cRecords]
        else: return []
    @property
    def APPA(self):
        numRecords = CBash.GetNumAPPARecords(self._CollectionIndex, self._ModName)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetAPPARecords(self._CollectionIndex, self._ModName, cRecords)
            return [APPARecord(self._CollectionIndex, self._ModName, x.contents.value) for x in cRecords]
        else: return []
    @property
    def ARMO(self):
        numRecords = CBash.GetNumARMORecords(self._CollectionIndex, self._ModName)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetARMORecords(self._CollectionIndex, self._ModName, cRecords)
            return [ARMORecord(self._CollectionIndex, self._ModName, x.contents.value) for x in cRecords]
        else: return []
    @property
    def BOOK(self):
        numRecords = CBash.GetNumBOOKRecords(self._CollectionIndex, self._ModName)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetBOOKRecords(self._CollectionIndex, self._ModName, cRecords)
            return [BOOKRecord(self._CollectionIndex, self._ModName, x.contents.value) for x in cRecords]
        else: return []
    @property
    def CLOT(self):
        numRecords = CBash.GetNumCLOTRecords(self._CollectionIndex, self._ModName)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetCLOTRecords(self._CollectionIndex, self._ModName, cRecords)
            return [CLOTRecord(self._CollectionIndex, self._ModName, x.contents.value) for x in cRecords]
        else: return []
    @property
    def CONT(self):
        numRecords = CBash.GetNumCONTRecords(self._CollectionIndex, self._ModName)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetCONTRecords(self._CollectionIndex, self._ModName, cRecords)
            return [CONTRecord(self._CollectionIndex, self._ModName, x.contents.value) for x in cRecords]
        else: return []
    @property
    def DOOR(self):
        numRecords = CBash.GetNumDOORRecords(self._CollectionIndex, self._ModName)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetDOORRecords(self._CollectionIndex, self._ModName, cRecords)
            return [DOORRecord(self._CollectionIndex, self._ModName, x.contents.value) for x in cRecords]
        else: return []
    @property
    def INGR(self):
        numRecords = CBash.GetNumINGRRecords(self._CollectionIndex, self._ModName)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetINGRRecords(self._CollectionIndex, self._ModName, cRecords)
            return [INGRRecord(self._CollectionIndex, self._ModName, x.contents.value) for x in cRecords]
        else: return []
    @property
    def LIGH(self):
        numRecords = CBash.GetNumLIGHRecords(self._CollectionIndex, self._ModName)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetLIGHRecords(self._CollectionIndex, self._ModName, cRecords)
            return [LIGHRecord(self._CollectionIndex, self._ModName, x.contents.value) for x in cRecords]
        else: return []
    @property
    def MISC(self):
        numRecords = CBash.GetNumMISCRecords(self._CollectionIndex, self._ModName)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetMISCRecords(self._CollectionIndex, self._ModName, cRecords)
            return [MISCRecord(self._CollectionIndex, self._ModName, x.contents.value) for x in cRecords]
        else: return []
    @property
    def STAT(self):
        numRecords = CBash.GetNumSTATRecords(self._CollectionIndex, self._ModName)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetSTATRecords(self._CollectionIndex, self._ModName, cRecords)
            return [STATRecord(self._CollectionIndex, self._ModName, x.contents.value) for x in cRecords]
        else: return []
    @property
    def GRAS(self):
        numRecords = CBash.GetNumGRASRecords(self._CollectionIndex, self._ModName)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetGRASRecords(self._CollectionIndex, self._ModName, cRecords)
            return [GRASRecord(self._CollectionIndex, self._ModName, x.contents.value) for x in cRecords]
        else: return []
    @property
    def TREE(self):
        numRecords = CBash.GetNumTREERecords(self._CollectionIndex, self._ModName)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetTREERecords(self._CollectionIndex, self._ModName, cRecords)
            return [TREERecord(self._CollectionIndex, self._ModName, x.contents.value) for x in cRecords]
        else: return []
    @property
    def FLOR(self):
        numRecords = CBash.GetNumFLORRecords(self._CollectionIndex, self._ModName)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetFLORRecords(self._CollectionIndex, self._ModName, cRecords)
            return [FLORRecord(self._CollectionIndex, self._ModName, x.contents.value) for x in cRecords]
        else: return []
    @property
    def FURN(self):
        numRecords = CBash.GetNumFURNRecords(self._CollectionIndex, self._ModName)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetFURNRecords(self._CollectionIndex, self._ModName, cRecords)
            return [FURNRecord(self._CollectionIndex, self._ModName, x.contents.value) for x in cRecords]
        else: return []
    @property
    def WEAP(self):
        numRecords = CBash.GetNumWEAPRecords(self._CollectionIndex, self._ModName)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetWEAPRecords(self._CollectionIndex, self._ModName, cRecords)
            return [WEAPRecord(self._CollectionIndex, self._ModName, x.contents.value) for x in cRecords]
        else: return []
    @property
    def AMMO(self):
        numRecords = CBash.GetNumAMMORecords(self._CollectionIndex, self._ModName)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetAMMORecords(self._CollectionIndex, self._ModName, cRecords)
            return [AMMORecord(self._CollectionIndex, self._ModName, x.contents.value) for x in cRecords]
        else: return []
    @property
    def NPC_(self):
        numRecords = CBash.GetNumNPC_Records(self._CollectionIndex, self._ModName)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetNPC_Records(self._CollectionIndex, self._ModName, cRecords)
            return [NPC_Record(self._CollectionIndex, self._ModName, x.contents.value) for x in cRecords]
        else: return []
    @property
    def CREA(self):
        numRecords = CBash.GetNumCREARecords(self._CollectionIndex, self._ModName)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetCREARecords(self._CollectionIndex, self._ModName, cRecords)
            return [CREARecord(self._CollectionIndex, self._ModName, x.contents.value) for x in cRecords]
        else: return []
    @property
    def LVLC(self):
        numRecords = CBash.GetNumLVLCRecords(self._CollectionIndex, self._ModName)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetLVLCRecords(self._CollectionIndex, self._ModName, cRecords)
            return [LVLCRecord(self._CollectionIndex, self._ModName, x.contents.value) for x in cRecords]
        else: return []
    @property
    def SLGM(self):
        numRecords = CBash.GetNumSLGMRecords(self._CollectionIndex, self._ModName)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetSLGMRecords(self._CollectionIndex, self._ModName, cRecords)
            return [SLGMRecord(self._CollectionIndex, self._ModName, x.contents.value) for x in cRecords]
        else: return []
    @property
    def KEYM(self):
        numRecords = CBash.GetNumKEYMRecords(self._CollectionIndex, self._ModName)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetKEYMRecords(self._CollectionIndex, self._ModName, cRecords)
            return [KEYMRecord(self._CollectionIndex, self._ModName, x.contents.value) for x in cRecords]
        else: return []
    @property
    def ALCH(self):
        numRecords = CBash.GetNumALCHRecords(self._CollectionIndex, self._ModName)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetALCHRecords(self._CollectionIndex, self._ModName, cRecords)
            return [ALCHRecord(self._CollectionIndex, self._ModName, x.contents.value) for x in cRecords]
        else: return []
    @property
    def SBSP(self):
        numRecords = CBash.GetNumSBSPRecords(self._CollectionIndex, self._ModName)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetSBSPRecords(self._CollectionIndex, self._ModName, cRecords)
            return [SBSPRecord(self._CollectionIndex, self._ModName, x.contents.value) for x in cRecords]
        else: return []
    @property
    def SGST(self):
        numRecords = CBash.GetNumSGSTRecords(self._CollectionIndex, self._ModName)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetSGSTRecords(self._CollectionIndex, self._ModName, cRecords)
            return [SGSTRecord(self._CollectionIndex, self._ModName, x.contents.value) for x in cRecords]
        else: return []
    @property
    def LVLI(self):
        numRecords = CBash.GetNumLVLIRecords(self._CollectionIndex, self._ModName)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetLVLIRecords(self._CollectionIndex, self._ModName, cRecords)
            return [LVLIRecord(self._CollectionIndex, self._ModName, x.contents.value) for x in cRecords]
        else: return []
    @property
    def WTHR(self):
        numRecords = CBash.GetNumWTHRRecords(self._CollectionIndex, self._ModName)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetWTHRRecords(self._CollectionIndex, self._ModName, cRecords)
            return [WTHRRecord(self._CollectionIndex, self._ModName, x.contents.value) for x in cRecords]
        else: return []
    @property
    def CLMT(self):
        numRecords = CBash.GetNumCLMTRecords(self._CollectionIndex, self._ModName)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetCLMTRecords(self._CollectionIndex, self._ModName, cRecords)
            return [CLMTRecord(self._CollectionIndex, self._ModName, x.contents.value) for x in cRecords]
        else: return []
    @property
    def REGN(self):
        numRecords = CBash.GetNumREGNRecords(self._CollectionIndex, self._ModName)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetREGNRecords(self._CollectionIndex, self._ModName, cRecords)
            return [REGNRecord(self._CollectionIndex, self._ModName, x.contents.value) for x in cRecords]
        else: return []
    @property
    def CELL(self):
        numRecords = CBash.GetNumCELLRecords(self._CollectionIndex, self._ModName)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetCELLRecords(self._CollectionIndex, self._ModName, cRecords)
            return [CELLRecord(self._CollectionIndex, self._ModName, x.contents.value) for x in cRecords]
        else: return []
    @property
    def WRLD(self):
        numRecords = CBash.GetNumWRLDRecords(self._CollectionIndex, self._ModName)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetWRLDRecords(self._CollectionIndex, self._ModName, cRecords)
            return [WRLDRecord(self._CollectionIndex, self._ModName, x.contents.value) for x in cRecords]
        else: return []
    @property
    def DIAL(self):
        numRecords = CBash.GetNumDIALRecords(self._CollectionIndex, self._ModName)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetDIALRecords(self._CollectionIndex, self._ModName, cRecords)
            return [DIALRecord(self._CollectionIndex, self._ModName, x.contents.value) for x in cRecords]
        else: return []
    @property
    def QUST(self):
        numRecords = CBash.GetNumQUSTRecords(self._CollectionIndex, self._ModName)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetQUSTRecords(self._CollectionIndex, self._ModName, cRecords)
            return [QUSTRecord(self._CollectionIndex, self._ModName, x.contents.value) for x in cRecords]
        else: return []
    @property
    def IDLE(self):
        numRecords = CBash.GetNumIDLERecords(self._CollectionIndex, self._ModName)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetIDLERecords(self._CollectionIndex, self._ModName, cRecords)
            return [IDLERecord(self._CollectionIndex, self._ModName, x.contents.value) for x in cRecords]
        else: return []
    @property
    def PACK(self):
        numRecords = CBash.GetNumPACKRecords(self._CollectionIndex, self._ModName)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetPACKRecords(self._CollectionIndex, self._ModName, cRecords)
            return [PACKRecord(self._CollectionIndex, self._ModName, x.contents.value) for x in cRecords]
        else: return []
    @property
    def CSTY(self):
        numRecords = CBash.GetNumCSTYRecords(self._CollectionIndex, self._ModName)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetCSTYRecords(self._CollectionIndex, self._ModName, cRecords)
            return [CSTYRecord(self._CollectionIndex, self._ModName, x.contents.value) for x in cRecords]
        else: return []
    @property
    def LSCR(self):
        numRecords = CBash.GetNumLSCRRecords(self._CollectionIndex, self._ModName)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetLSCRRecords(self._CollectionIndex, self._ModName, cRecords)
            return [LSCRRecord(self._CollectionIndex, self._ModName, x.contents.value) for x in cRecords]
        else: return []
    @property
    def LVSP(self):
        numRecords = CBash.GetNumLVSPRecords(self._CollectionIndex, self._ModName)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetLVSPRecords(self._CollectionIndex, self._ModName, cRecords)
            return [LVSPRecord(self._CollectionIndex, self._ModName, x.contents.value) for x in cRecords]
        else: return []
    @property
    def ANIO(self):
        numRecords = CBash.GetNumANIORecords(self._CollectionIndex, self._ModName)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetANIORecords(self._CollectionIndex, self._ModName, cRecords)
            return [ANIORecord(self._CollectionIndex, self._ModName, x.contents.value) for x in cRecords]
        else: return []
    @property
    def WATR(self):
        numRecords = CBash.GetNumWATRRecords(self._CollectionIndex, self._ModName)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetWATRRecords(self._CollectionIndex, self._ModName, cRecords)
            return [WATRRecord(self._CollectionIndex, self._ModName, x.contents.value) for x in cRecords]
        else: return []
    @property
    def EFSH(self):
        numRecords = CBash.GetNumEFSHRecords(self._CollectionIndex, self._ModName)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetEFSHRecords(self._CollectionIndex, self._ModName, cRecords)
            return [EFSHRecord(self._CollectionIndex, self._ModName, x.contents.value) for x in cRecords]
        else: return []
    
class Collection:
    """Collection of esm/esp's."""

    def __init__(self, recordID=None):
        if recordID:
            self._CollectionIndex = recordID
        else:
            self._CollectionIndex = CBash.NewCollection()
        self._ModIndex = -1
        CBash.GetModName.restype = c_char_p

    def addMod(self, ModName, CreateIfNotExist=False):
        if(CBash.AddMod(self._CollectionIndex, ModName, CreateIfNotExist) != -1):
            return ModFile(self._CollectionIndex, ModName)
        else: return None

    def minimalLoad(self, LoadMasters=False):
        CBash.MinimalLoad(self._CollectionIndex, LoadMasters)
        
    def fullLoad(self, LoadMasters=False):
        CBash.FullLoad(self._CollectionIndex, LoadMasters)

    def debug(self, debugLevel = 0, AllRecords = False):
        CBash.Debug(self._CollectionIndex, debugLevel, AllRecords)

    def close(self):
        CBash.Close(self._CollectionIndex)

    def __del__(self):
        self.close()
        CBash.DeleteCollection(self._CollectionIndex)

    @property
    def TES4(self):
        numRecords = CBash.GetNumMods(self._CollectionIndex)
        if(numRecords > 0):
            cRecords = (POINTER(c_char_p) * numRecords)()
            CBash.GetMods(self._CollectionIndex, cRecords)
            return [TES4Record(self._CollectionIndex, string_at(cRecords[x])) for x in range(0, numRecords)]
        else: return []
    @property
    def GMST(self):
        numRecords = CBash.GetNumGMSTRecords(self._CollectionIndex, 0)
        if(numRecords > 0):
            cRecords = (POINTER(c_char_p) * numRecords)()
            CBash.GetGMSTs(self._CollectionIndex, 0, cRecords)
            return [GMSTRecord(self._CollectionIndex, 0, string_at(cRecords[x])) for x in range(0, numRecords)]
        else: return []
    @property
    def GLOB(self):
        numRecords = CBash.GetNumGLOBRecords(self._CollectionIndex, 0)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetGLOBRecords(self._CollectionIndex, 0, cRecords)
            return [GLOBRecord(self._CollectionIndex, 0,  x.contents.value) for x in cRecords]
        else: return []
    @property
    def CLAS(self):
        numRecords = CBash.GetNumCLASRecords(self._CollectionIndex, 0)
        if(numRecords > 0):
            cRecords = (POINTER(c_uint) * numRecords)()
            CBash.GetCLASRecords(self._CollectionIndex, 0, cRecords)
            return [CLASRecord(self._CollectionIndex, 0, x.contents.value) for x in cRecords]
        else: return []
    @property
    def FACT(self):
        ##Iterator is slightly faster if not iterating through entire sequence
        ##Might be even faster if it didn't search through ALL forms, and just all the forms of the type
        ##Should get progressively slower as more non-FACT records are added
        class FACTIterator():
            def __init__(self, recordID):
                CBash.IncrementIterator.restype = c_longlong
                self._CollectionIndex = recordID
            def __iter__(self):
                self._IteratorIndex = CBash.StartFACTIterator(self._CollectionIndex)
                return self
            def next(self):
                nextRecordID = CBash.IncrementIterator(self._IteratorIndex)
                if nextRecordID == -1:
                    CBash.StopIterator(self._IteratorIndex)
                    raise StopIteration
                return FACTRecord(self._CollectionIndex, 0, nextRecordID)
        return FACTIterator(self._CollectionIndex)
        ##Getting all the records at once is slower, but more of a constant time
        ##It shouldn't be affected if more non-FACT records are added.
##        numRecords = CBash.GetNumRecords(self._CollectionIndex, 0, eFACT)
##        if(numRecords > 0):
##            cRecords = (POINTER(c_uint) * numRecords)()
##            CBash.GetFIDs(self._CollectionIndex, 0, eFACT, cRecords)
##            return [FACTRecord(self._CollectionIndex, x.contents.value) for x in cRecords]
##        else:
##            return []
    @property
    def HAIR(self):
        class HAIRIterator():
            def __init__(self, recordID):
                CBash.IncrementIterator.restype = c_longlong
                self._CollectionIndex = recordID
            def __iter__(self):
                self._IteratorIndex = CBash.StartHAIRIterator(self._CollectionIndex)
                return self
            def next(self):
                nextRecordID = CBash.IncrementIterator(self._IteratorIndex)
                if nextRecordID == -1:
                    CBash.StopIterator(self._IteratorIndex)
                    raise StopIteration
                return HAIRRecord(self._CollectionIndex, 0, nextRecordID)
        return HAIRIterator(self._CollectionIndex)
    @property
    def EYES(self):
        class EYESIterator():
            def __init__(self, recordID):
                CBash.IncrementIterator.restype = c_longlong
                self._CollectionIndex = recordID
            def __iter__(self):
                self._IteratorIndex = CBash.StartEYESIterator(self._CollectionIndex)
                return self
            def next(self):
                nextRecordID = CBash.IncrementIterator(self._IteratorIndex)
                if nextRecordID == -1:
                    CBash.StopIterator(self._IteratorIndex)
                    raise StopIteration
                return EYESRecord(self._CollectionIndex, 0, nextRecordID)
        return EYESIterator(self._CollectionIndex)
    @property
    def RACE(self):
        class RACEIterator():
            def __init__(self, recordID):
                CBash.IncrementIterator.restype = c_longlong
                self._CollectionIndex = recordID
            def __iter__(self):
                self._IteratorIndex = CBash.StartRACEIterator(self._CollectionIndex)
                return self
            def next(self):
                nextRecordID = CBash.IncrementIterator(self._IteratorIndex)
                if nextRecordID == -1:
                    CBash.StopIterator(self._IteratorIndex)
                    raise StopIteration
                return RACERecord(self._CollectionIndex, 0, nextRecordID)
        return RACEIterator(self._CollectionIndex)
    
    @property
    def SOUN(self):
        class SOUNIterator():
            def __init__(self, recordID):
                CBash.IncrementIterator.restype = c_longlong
                self._CollectionIndex = recordID
            def __iter__(self):
                self._IteratorIndex = CBash.StartSOUNIterator(self._CollectionIndex)
                return self
            def next(self):
                nextRecordID = CBash.IncrementIterator(self._IteratorIndex)
                if nextRecordID == -1:
                    CBash.StopIterator(self._IteratorIndex)
                    raise StopIteration
                return SOUNRecord(self._CollectionIndex, 0, nextRecordID)
        return SOUNIterator(self._CollectionIndex)
    
    @property
    def SKIL(self):
        class SKILIterator():
            def __init__(self, recordID):
                CBash.IncrementIterator.restype = c_longlong
                self._CollectionIndex = recordID
            def __iter__(self):
                self._IteratorIndex = CBash.StartSKILIterator(self._CollectionIndex)
                return self
            def next(self):
                nextRecordID = CBash.IncrementIterator(self._IteratorIndex)
                if nextRecordID == -1:
                    CBash.StopIterator(self._IteratorIndex)
                    raise StopIteration
                return SKILRecord(self._CollectionIndex, 0, nextRecordID)
        return SKILIterator(self._CollectionIndex)
    
    @property
    def MGEF(self):
        class MGEFIterator():
            def __init__(self, CollectionIndex):
                CBash.IncrementIterator.restype = c_longlong
                self._CollectionIndex = CollectionIndex
            def __iter__(self):
                self._IteratorIndex = CBash.StartMGEFIterator(self._CollectionIndex)
                return self
            def next(self):
                nextRecordID = CBash.IncrementIterator(self._IteratorIndex)
                if nextRecordID == -1:
                    CBash.StopIterator(self._IteratorIndex)
                    raise StopIteration
                return MGEFRecord(self._CollectionIndex, 0, nextRecordID)
        return MGEFIterator(self._CollectionIndex)
    
    @property
    def SCPT(self):
        class SCPTIterator():
            def __init__(self, CollectionIndex):
                CBash.IncrementIterator.restype = c_longlong
                self._CollectionIndex = CollectionIndex
            def __iter__(self):
                self._IteratorIndex = CBash.StartSCPTIterator(self._CollectionIndex)
                return self
            def next(self):
                nextRecordID = CBash.IncrementIterator(self._IteratorIndex)
                if nextRecordID == -1:
                    CBash.StopIterator(self._IteratorIndex)
                    raise StopIteration
                return SCPTRecord(self._CollectionIndex, 0, nextRecordID)
        return SCPTIterator(self._CollectionIndex)

    @property
    def LTEX(self):
        class LTEXIterator():
            def __init__(self, CollectionIndex):
                CBash.IncrementIterator.restype = c_longlong
                self._CollectionIndex = CollectionIndex
            def __iter__(self):
                self._IteratorIndex = CBash.StartLTEXIterator(self._CollectionIndex)
                return self
            def next(self):
                nextRecordID = CBash.IncrementIterator(self._IteratorIndex)
                if nextRecordID == -1:
                    CBash.StopIterator(self._IteratorIndex)
                    raise StopIteration
                return LTEXRecord(self._CollectionIndex, 0, nextRecordID)
        return LTEXIterator(self._CollectionIndex)
    @property
    def ENCH(self):
        class ENCHIterator():
            def __init__(self, CollectionIndex):
                CBash.IncrementIterator.restype = c_longlong
                self._CollectionIndex = CollectionIndex
            def __iter__(self):
                self._IteratorIndex = CBash.StartENCHIterator(self._CollectionIndex)
                return self
            def next(self):
                nextRecordID = CBash.IncrementIterator(self._IteratorIndex)
                if nextRecordID == -1:
                    CBash.StopIterator(self._IteratorIndex)
                    raise StopIteration
                return ENCHRecord(self._CollectionIndex, 0, nextRecordID)
        return ENCHIterator(self._CollectionIndex)
    @property
    def SPEL(self):
        class SPELIterator():
            def __init__(self, CollectionIndex):
                CBash.IncrementIterator.restype = c_longlong
                self._CollectionIndex = CollectionIndex
            def __iter__(self):
                self._IteratorIndex = CBash.StartSPELIterator(self._CollectionIndex)
                return self
            def next(self):
                nextRecordID = CBash.IncrementIterator(self._IteratorIndex)
                if nextRecordID == -1:
                    CBash.StopIterator(self._IteratorIndex)
                    raise StopIteration
                return SPELRecord(self._CollectionIndex, 0, nextRecordID)
        return SPELIterator(self._CollectionIndex)
    @property
    def BSGN(self):
        class BSGNIterator():
            def __init__(self, CollectionIndex):
                CBash.IncrementIterator.restype = c_longlong
                self._CollectionIndex = CollectionIndex
            def __iter__(self):
                self._IteratorIndex = CBash.StartBSGNIterator(self._CollectionIndex)
                return self
            def next(self):
                nextRecordID = CBash.IncrementIterator(self._IteratorIndex)
                if nextRecordID == -1:
                    CBash.StopIterator(self._IteratorIndex)
                    raise StopIteration
                return BSGNRecord(self._CollectionIndex, 0, nextRecordID)
        return BSGNIterator(self._CollectionIndex)
    @property
    def ACTI(self):
        class ACTIIterator():
            def __init__(self, CollectionIndex):
                CBash.IncrementIterator.restype = c_longlong
                self._CollectionIndex = CollectionIndex
            def __iter__(self):
                self._IteratorIndex = CBash.StartACTIIterator(self._CollectionIndex)
                return self
            def next(self):
                nextRecordID = CBash.IncrementIterator(self._IteratorIndex)
                if nextRecordID == -1:
                    CBash.StopIterator(self._IteratorIndex)
                    raise StopIteration
                return ACTIRecord(self._CollectionIndex, 0, nextRecordID)
        return ACTIIterator(self._CollectionIndex)
    @property
    def APPA(self):
        class APPAIterator():
            def __init__(self, CollectionIndex):
                CBash.IncrementIterator.restype = c_longlong
                self._CollectionIndex = CollectionIndex
            def __iter__(self):
                self._IteratorIndex = CBash.StartAPPAIterator(self._CollectionIndex)
                return self
            def next(self):
                nextRecordID = CBash.IncrementIterator(self._IteratorIndex)
                if nextRecordID == -1:
                    CBash.StopIterator(self._IteratorIndex)
                    raise StopIteration
                return APPARecord(self._CollectionIndex, 0, nextRecordID)
        return APPAIterator(self._CollectionIndex)
    @property
    def ARMO(self):
        class ARMOIterator():
            def __init__(self, CollectionIndex):
                CBash.IncrementIterator.restype = c_longlong
                self._CollectionIndex = CollectionIndex
            def __iter__(self):
                self._IteratorIndex = CBash.StartARMOIterator(self._CollectionIndex)
                return self
            def next(self):
                nextRecordID = CBash.IncrementIterator(self._IteratorIndex)
                if nextRecordID == -1:
                    CBash.StopIterator(self._IteratorIndex)
                    raise StopIteration
                return ARMORecord(self._CollectionIndex, 0, nextRecordID)
        return ARMOIterator(self._CollectionIndex)
    @property
    def BOOK(self):
        class BOOKIterator():
            def __init__(self, CollectionIndex):
                CBash.IncrementIterator.restype = c_longlong
                self._CollectionIndex = CollectionIndex
            def __iter__(self):
                self._IteratorIndex = CBash.StartBOOKIterator(self._CollectionIndex)
                return self
            def next(self):
                nextRecordID = CBash.IncrementIterator(self._IteratorIndex)
                if nextRecordID == -1:
                    CBash.StopIterator(self._IteratorIndex)
                    raise StopIteration
                return BOOKRecord(self._CollectionIndex, 0, nextRecordID)
        return BOOKIterator(self._CollectionIndex)
    @property
    def CLOT(self):
        class CLOTIterator():
            def __init__(self, CollectionIndex):
                CBash.IncrementIterator.restype = c_longlong
                self._CollectionIndex = CollectionIndex
            def __iter__(self):
                self._IteratorIndex = CBash.StartCLOTIterator(self._CollectionIndex)
                return self
            def next(self):
                nextRecordID = CBash.IncrementIterator(self._IteratorIndex)
                if nextRecordID == -1:
                    CBash.StopIterator(self._IteratorIndex)
                    raise StopIteration
                return CLOTRecord(self._CollectionIndex, 0, nextRecordID)
        return CLOTIterator(self._CollectionIndex)
    @property
    def CONT(self):
        class CONTIterator():
            def __init__(self, CollectionIndex):
                CBash.IncrementIterator.restype = c_longlong
                self._CollectionIndex = CollectionIndex
            def __iter__(self):
                self._IteratorIndex = CBash.StartCONTIterator(self._CollectionIndex)
                return self
            def next(self):
                nextRecordID = CBash.IncrementIterator(self._IteratorIndex)
                if nextRecordID == -1:
                    CBash.StopIterator(self._IteratorIndex)
                    raise StopIteration
                return CONTRecord(self._CollectionIndex, 0, nextRecordID)
        return CONTIterator(self._CollectionIndex)
    @property
    def DOOR(self):
        class DOORIterator():
            def __init__(self, CollectionIndex):
                CBash.IncrementIterator.restype = c_longlong
                self._CollectionIndex = CollectionIndex
            def __iter__(self):
                self._IteratorIndex = CBash.StartDOORIterator(self._CollectionIndex)
                return self
            def next(self):
                nextRecordID = CBash.IncrementIterator(self._IteratorIndex)
                if nextRecordID == -1:
                    CBash.StopIterator(self._IteratorIndex)
                    raise StopIteration
                return DOORRecord(self._CollectionIndex, 0, nextRecordID)
        return DOORIterator(self._CollectionIndex)
    @property
    def INGR(self):
        class INGRIterator():
            def __init__(self, CollectionIndex):
                CBash.IncrementIterator.restype = c_longlong
                self._CollectionIndex = CollectionIndex
            def __iter__(self):
                self._IteratorIndex = CBash.StartINGRIterator(self._CollectionIndex)
                return self
            def next(self):
                nextRecordID = CBash.IncrementIterator(self._IteratorIndex)
                if nextRecordID == -1:
                    CBash.StopIterator(self._IteratorIndex)
                    raise StopIteration
                return INGRRecord(self._CollectionIndex, 0, nextRecordID)
        return INGRIterator(self._CollectionIndex)
    @property
    def LIGH(self):
        class LIGHIterator():
            def __init__(self, CollectionIndex):
                CBash.IncrementIterator.restype = c_longlong
                self._CollectionIndex = CollectionIndex
            def __iter__(self):
                self._IteratorIndex = CBash.StartLIGHIterator(self._CollectionIndex)
                return self
            def next(self):
                nextRecordID = CBash.IncrementIterator(self._IteratorIndex)
                if nextRecordID == -1:
                    CBash.StopIterator(self._IteratorIndex)
                    raise StopIteration
                return LIGHRecord(self._CollectionIndex, 0, nextRecordID)
        return LIGHIterator(self._CollectionIndex)
    @property
    def MISC(self):
        class MISCIterator():
            def __init__(self, CollectionIndex):
                CBash.IncrementIterator.restype = c_longlong
                self._CollectionIndex = CollectionIndex
            def __iter__(self):
                self._IteratorIndex = CBash.StartMISCIterator(self._CollectionIndex)
                return self
            def next(self):
                nextRecordID = CBash.IncrementIterator(self._IteratorIndex)
                if nextRecordID == -1:
                    CBash.StopIterator(self._IteratorIndex)
                    raise StopIteration
                return MISCRecord(self._CollectionIndex, 0, nextRecordID)
        return MISCIterator(self._CollectionIndex)
    @property
    def STAT(self):
        class STATIterator():
            def __init__(self, CollectionIndex):
                CBash.IncrementIterator.restype = c_longlong
                self._CollectionIndex = CollectionIndex
            def __iter__(self):
                self._IteratorIndex = CBash.StartSTATIterator(self._CollectionIndex)
                return self
            def next(self):
                nextRecordID = CBash.IncrementIterator(self._IteratorIndex)
                if nextRecordID == -1:
                    CBash.StopIterator(self._IteratorIndex)
                    raise StopIteration
                return STATRecord(self._CollectionIndex, 0, nextRecordID)
        return STATIterator(self._CollectionIndex)
    @property
    def GRAS(self):
        class GRASIterator():
            def __init__(self, CollectionIndex):
                CBash.IncrementIterator.restype = c_longlong
                self._CollectionIndex = CollectionIndex
            def __iter__(self):
                self._IteratorIndex = CBash.StartGRASIterator(self._CollectionIndex)
                return self
            def next(self):
                nextRecordID = CBash.IncrementIterator(self._IteratorIndex)
                if nextRecordID == -1:
                    CBash.StopIterator(self._IteratorIndex)
                    raise StopIteration
                return GRASRecord(self._CollectionIndex, 0, nextRecordID)
        return GRASIterator(self._CollectionIndex)
    @property
    def TREE(self):
        class TREEIterator():
            def __init__(self, CollectionIndex):
                CBash.IncrementIterator.restype = c_longlong
                self._CollectionIndex = CollectionIndex
            def __iter__(self):
                self._IteratorIndex = CBash.StartTREEIterator(self._CollectionIndex)
                return self
            def next(self):
                nextRecordID = CBash.IncrementIterator(self._IteratorIndex)
                if nextRecordID == -1:
                    CBash.StopIterator(self._IteratorIndex)
                    raise StopIteration
                return TREERecord(self._CollectionIndex, 0, nextRecordID)
        return TREEIterator(self._CollectionIndex)
    @property
    def FLOR(self):
        class FLORIterator():
            def __init__(self, CollectionIndex):
                CBash.IncrementIterator.restype = c_longlong
                self._CollectionIndex = CollectionIndex
            def __iter__(self):
                self._IteratorIndex = CBash.StartFLORIterator(self._CollectionIndex)
                return self
            def next(self):
                nextRecordID = CBash.IncrementIterator(self._IteratorIndex)
                if nextRecordID == -1:
                    CBash.StopIterator(self._IteratorIndex)
                    raise StopIteration
                return FLORRecord(self._CollectionIndex, 0, nextRecordID)
        return FLORIterator(self._CollectionIndex)
    @property
    def FURN(self):
        class FURNIterator():
            def __init__(self, CollectionIndex):
                CBash.IncrementIterator.restype = c_longlong
                self._CollectionIndex = CollectionIndex
            def __iter__(self):
                self._IteratorIndex = CBash.StartFURNIterator(self._CollectionIndex)
                return self
            def next(self):
                nextRecordID = CBash.IncrementIterator(self._IteratorIndex)
                if nextRecordID == -1:
                    CBash.StopIterator(self._IteratorIndex)
                    raise StopIteration
                return FURNRecord(self._CollectionIndex, 0, nextRecordID)
        return FURNIterator(self._CollectionIndex)
    @property
    def WEAP(self):
        class WEAPIterator():
            def __init__(self, CollectionIndex):
                CBash.IncrementIterator.restype = c_longlong
                self._CollectionIndex = CollectionIndex
            def __iter__(self):
                self._IteratorIndex = CBash.StartWEAPIterator(self._CollectionIndex)
                return self
            def next(self):
                nextRecordID = CBash.IncrementIterator(self._IteratorIndex)
                if nextRecordID == -1:
                    CBash.StopIterator(self._IteratorIndex)
                    raise StopIteration
                return WEAPRecord(self._CollectionIndex, 0, nextRecordID)
        return WEAPIterator(self._CollectionIndex)
    @property
    def AMMO(self):
        class AMMOIterator():
            def __init__(self, CollectionIndex):
                CBash.IncrementIterator.restype = c_longlong
                self._CollectionIndex = CollectionIndex
            def __iter__(self):
                self._IteratorIndex = CBash.StartAMMOIterator(self._CollectionIndex)
                return self
            def next(self):
                nextRecordID = CBash.IncrementIterator(self._IteratorIndex)
                if nextRecordID == -1:
                    CBash.StopIterator(self._IteratorIndex)
                    raise StopIteration
                return AMMORecord(self._CollectionIndex, 0, nextRecordID)
        return AMMOIterator(self._CollectionIndex)
    @property
    def NPC_(self):
        class NPC_Iterator():
            def __init__(self, CollectionIndex):
                CBash.IncrementIterator.restype = c_longlong
                self._CollectionIndex = CollectionIndex
            def __iter__(self):
                self._IteratorIndex = CBash.StartNPC_Iterator(self._CollectionIndex)
                return self
            def next(self):
                nextRecordID = CBash.IncrementIterator(self._IteratorIndex)
                if nextRecordID == -1:
                    CBash.StopIterator(self._IteratorIndex)
                    raise StopIteration
                return NPC_Record(self._CollectionIndex, 0, nextRecordID)
        return NPC_Iterator(self._CollectionIndex)
    @property
    def CREA(self):
        class CREAIterator():
            def __init__(self, CollectionIndex):
                CBash.IncrementIterator.restype = c_longlong
                self._CollectionIndex = CollectionIndex
            def __iter__(self):
                self._IteratorIndex = CBash.StartCREAIterator(self._CollectionIndex)
                return self
            def next(self):
                nextRecordID = CBash.IncrementIterator(self._IteratorIndex)
                if nextRecordID == -1:
                    CBash.StopIterator(self._IteratorIndex)
                    raise StopIteration
                return CREARecord(self._CollectionIndex, 0, nextRecordID)
        return CREAIterator(self._CollectionIndex)
    @property
    def LVLC(self):
        class LVLCIterator():
            def __init__(self, CollectionIndex):
                CBash.IncrementIterator.restype = c_longlong
                self._CollectionIndex = CollectionIndex
            def __iter__(self):
                self._IteratorIndex = CBash.StartLVLCIterator(self._CollectionIndex)
                return self
            def next(self):
                nextRecordID = CBash.IncrementIterator(self._IteratorIndex)
                if nextRecordID == -1:
                    CBash.StopIterator(self._IteratorIndex)
                    raise StopIteration
                return LVLCRecord(self._CollectionIndex, 0, nextRecordID)
        return LVLCIterator(self._CollectionIndex)
    @property
    def SLGM(self):
        class SLGMIterator():
            def __init__(self, CollectionIndex):
                CBash.IncrementIterator.restype = c_longlong
                self._CollectionIndex = CollectionIndex
            def __iter__(self):
                self._IteratorIndex = CBash.StartSLGMIterator(self._CollectionIndex)
                return self
            def next(self):
                nextRecordID = CBash.IncrementIterator(self._IteratorIndex)
                if nextRecordID == -1:
                    CBash.StopIterator(self._IteratorIndex)
                    raise StopIteration
                return SLGMRecord(self._CollectionIndex, 0, nextRecordID)
        return SLGMIterator(self._CollectionIndex)
    @property
    def KEYM(self):
        class KEYMIterator():
            def __init__(self, CollectionIndex):
                CBash.IncrementIterator.restype = c_longlong
                self._CollectionIndex = CollectionIndex
            def __iter__(self):
                self._IteratorIndex = CBash.StartKEYMIterator(self._CollectionIndex)
                return self
            def next(self):
                nextRecordID = CBash.IncrementIterator(self._IteratorIndex)
                if nextRecordID == -1:
                    CBash.StopIterator(self._IteratorIndex)
                    raise StopIteration
                return KEYMRecord(self._CollectionIndex, 0, nextRecordID)
        return KEYMIterator(self._CollectionIndex)
    @property
    def ALCH(self):
        class ALCHIterator():
            def __init__(self, CollectionIndex):
                CBash.IncrementIterator.restype = c_longlong
                self._CollectionIndex = CollectionIndex
            def __iter__(self):
                self._IteratorIndex = CBash.StartALCHIterator(self._CollectionIndex)
                return self
            def next(self):
                nextRecordID = CBash.IncrementIterator(self._IteratorIndex)
                if nextRecordID == -1:
                    CBash.StopIterator(self._IteratorIndex)
                    raise StopIteration
                return ALCHRecord(self._CollectionIndex, 0, nextRecordID)
        return ALCHIterator(self._CollectionIndex)
    @property
    def SBSP(self):
        class SBSPIterator():
            def __init__(self, CollectionIndex):
                CBash.IncrementIterator.restype = c_longlong
                self._CollectionIndex = CollectionIndex
            def __iter__(self):
                self._IteratorIndex = CBash.StartSBSPIterator(self._CollectionIndex)
                return self
            def next(self):
                nextRecordID = CBash.IncrementIterator(self._IteratorIndex)
                if nextRecordID == -1:
                    CBash.StopIterator(self._IteratorIndex)
                    raise StopIteration
                return SBSPRecord(self._CollectionIndex, 0, nextRecordID)
        return SBSPIterator(self._CollectionIndex)
    @property
    def SGST(self):
        class SGSTIterator():
            def __init__(self, CollectionIndex):
                CBash.IncrementIterator.restype = c_longlong
                self._CollectionIndex = CollectionIndex
            def __iter__(self):
                self._IteratorIndex = CBash.StartSGSTIterator(self._CollectionIndex)
                return self
            def next(self):
                nextRecordID = CBash.IncrementIterator(self._IteratorIndex)
                if nextRecordID == -1:
                    CBash.StopIterator(self._IteratorIndex)
                    raise StopIteration
                return SGSTRecord(self._CollectionIndex, 0, nextRecordID)
        return SGSTIterator(self._CollectionIndex)
    @property
    def LVLI(self):
        class LVLIIterator():
            def __init__(self, CollectionIndex):
                CBash.IncrementIterator.restype = c_longlong
                self._CollectionIndex = CollectionIndex
            def __iter__(self):
                self._IteratorIndex = CBash.StartLVLIIterator(self._CollectionIndex)
                return self
            def next(self):
                nextRecordID = CBash.IncrementIterator(self._IteratorIndex)
                if nextRecordID == -1:
                    CBash.StopIterator(self._IteratorIndex)
                    raise StopIteration
                return LVLIRecord(self._CollectionIndex, 0, nextRecordID)
        return LVLIIterator(self._CollectionIndex)
    @property
    def WTHR(self):
        class WTHRIterator():
            def __init__(self, CollectionIndex):
                CBash.IncrementIterator.restype = c_longlong
                self._CollectionIndex = CollectionIndex
            def __iter__(self):
                self._IteratorIndex = CBash.StartWTHRIterator(self._CollectionIndex)
                return self
            def next(self):
                nextRecordID = CBash.IncrementIterator(self._IteratorIndex)
                if nextRecordID == -1:
                    CBash.StopIterator(self._IteratorIndex)
                    raise StopIteration
                return WTHRRecord(self._CollectionIndex, 0, nextRecordID)
        return WTHRIterator(self._CollectionIndex)
    @property
    def CLMT(self):
        class CLMTIterator():
            def __init__(self, CollectionIndex):
                CBash.IncrementIterator.restype = c_longlong
                self._CollectionIndex = CollectionIndex
            def __iter__(self):
                self._IteratorIndex = CBash.StartCLMTIterator(self._CollectionIndex)
                return self
            def next(self):
                nextRecordID = CBash.IncrementIterator(self._IteratorIndex)
                if nextRecordID == -1:
                    CBash.StopIterator(self._IteratorIndex)
                    raise StopIteration
                return CLMTRecord(self._CollectionIndex, 0, nextRecordID)
        return CLMTIterator(self._CollectionIndex)
    @property
    def REGN(self):
        class REGNIterator():
            def __init__(self, CollectionIndex):
                CBash.IncrementIterator.restype = c_longlong
                self._CollectionIndex = CollectionIndex
            def __iter__(self):
                self._IteratorIndex = CBash.StartREGNIterator(self._CollectionIndex)
                return self
            def next(self):
                nextRecordID = CBash.IncrementIterator(self._IteratorIndex)
                if nextRecordID == -1:
                    CBash.StopIterator(self._IteratorIndex)
                    raise StopIteration
                return REGNRecord(self._CollectionIndex, 0, nextRecordID)
        return REGNIterator(self._CollectionIndex)
    @property
    def CELL(self):
        class CELLIterator():
            def __init__(self, CollectionIndex):
                CBash.IncrementIterator.restype = c_longlong
                self._CollectionIndex = CollectionIndex
            def __iter__(self):
                self._IteratorIndex = CBash.StartCELLIterator(self._CollectionIndex)
                return self
            def next(self):
                nextRecordID = CBash.IncrementIterator(self._IteratorIndex)
                if nextRecordID == -1:
                    CBash.StopIterator(self._IteratorIndex)
                    raise StopIteration
                return CELLRecord(self._CollectionIndex, 0, nextRecordID)
        return CELLIterator(self._CollectionIndex)
    @property
    def WRLD(self):
        class WRLDIterator():
            def __init__(self, CollectionIndex):
                CBash.IncrementIterator.restype = c_longlong
                self._CollectionIndex = CollectionIndex
            def __iter__(self):
                self._IteratorIndex = CBash.StartWRLDIterator(self._CollectionIndex)
                return self
            def next(self):
                nextRecordID = CBash.IncrementIterator(self._IteratorIndex)
                if nextRecordID == -1:
                    CBash.StopIterator(self._IteratorIndex)
                    raise StopIteration
                return WRLDRecord(self._CollectionIndex, 0, nextRecordID)
        return WRLDIterator(self._CollectionIndex)
    @property
    def DIAL(self):
        class DIALIterator():
            def __init__(self, CollectionIndex):
                CBash.IncrementIterator.restype = c_longlong
                self._CollectionIndex = CollectionIndex
            def __iter__(self):
                self._IteratorIndex = CBash.StartDIALIterator(self._CollectionIndex)
                return self
            def next(self):
                nextRecordID = CBash.IncrementIterator(self._IteratorIndex)
                if nextRecordID == -1:
                    CBash.StopIterator(self._IteratorIndex)
                    raise StopIteration
                return DIALRecord(self._CollectionIndex, 0, nextRecordID)
        return DIALIterator(self._CollectionIndex)
    @property
    def QUST(self):
        class QUSTIterator():
            def __init__(self, CollectionIndex):
                CBash.IncrementIterator.restype = c_longlong
                self._CollectionIndex = CollectionIndex
            def __iter__(self):
                self._IteratorIndex = CBash.StartQUSTIterator(self._CollectionIndex)
                return self
            def next(self):
                nextRecordID = CBash.IncrementIterator(self._IteratorIndex)
                if nextRecordID == -1:
                    CBash.StopIterator(self._IteratorIndex)
                    raise StopIteration
                return QUSTRecord(self._CollectionIndex, 0, nextRecordID)
        return QUSTIterator(self._CollectionIndex)
    @property
    def IDLE(self):
        class IDLEIterator():
            def __init__(self, CollectionIndex):
                CBash.IncrementIterator.restype = c_longlong
                self._CollectionIndex = CollectionIndex
            def __iter__(self):
                self._IteratorIndex = CBash.StartIDLEIterator(self._CollectionIndex)
                return self
            def next(self):
                nextRecordID = CBash.IncrementIterator(self._IteratorIndex)
                if nextRecordID == -1:
                    CBash.StopIterator(self._IteratorIndex)
                    raise StopIteration
                return IDLERecord(self._CollectionIndex, 0, nextRecordID)
        return IDLEIterator(self._CollectionIndex)
    @property
    def PACK(self):
        class PACKIterator():
            def __init__(self, CollectionIndex):
                CBash.IncrementIterator.restype = c_longlong
                self._CollectionIndex = CollectionIndex
            def __iter__(self):
                self._IteratorIndex = CBash.StartPACKIterator(self._CollectionIndex)
                return self
            def next(self):
                nextRecordID = CBash.IncrementIterator(self._IteratorIndex)
                if nextRecordID == -1:
                    CBash.StopIterator(self._IteratorIndex)
                    raise StopIteration
                return PACKRecord(self._CollectionIndex, 0, nextRecordID)
        return PACKIterator(self._CollectionIndex)
    @property
    def CSTY(self):
        class CSTYIterator():
            def __init__(self, CollectionIndex):
                CBash.IncrementIterator.restype = c_longlong
                self._CollectionIndex = CollectionIndex
            def __iter__(self):
                self._IteratorIndex = CBash.StartCSTYIterator(self._CollectionIndex)
                return self
            def next(self):
                nextRecordID = CBash.IncrementIterator(self._IteratorIndex)
                if nextRecordID == -1:
                    CBash.StopIterator(self._IteratorIndex)
                    raise StopIteration
                return CSTYRecord(self._CollectionIndex, 0, nextRecordID)
        return CSTYIterator(self._CollectionIndex)
    @property
    def LSCR(self):
        class LSCRIterator():
            def __init__(self, CollectionIndex):
                CBash.IncrementIterator.restype = c_longlong
                self._CollectionIndex = CollectionIndex
            def __iter__(self):
                self._IteratorIndex = CBash.StartLSCRIterator(self._CollectionIndex)
                return self
            def next(self):
                nextRecordID = CBash.IncrementIterator(self._IteratorIndex)
                if nextRecordID == -1:
                    CBash.StopIterator(self._IteratorIndex)
                    raise StopIteration
                return LSCRRecord(self._CollectionIndex, 0, nextRecordID)
        return LSCRIterator(self._CollectionIndex)
    @property
    def LVSP(self):
        class LVSPIterator():
            def __init__(self, CollectionIndex):
                CBash.IncrementIterator.restype = c_longlong
                self._CollectionIndex = CollectionIndex
            def __iter__(self):
                self._IteratorIndex = CBash.StartLVSPIterator(self._CollectionIndex)
                return self
            def next(self):
                nextRecordID = CBash.IncrementIterator(self._IteratorIndex)
                if nextRecordID == -1:
                    CBash.StopIterator(self._IteratorIndex)
                    raise StopIteration
                return LVSPRecord(self._CollectionIndex, 0, nextRecordID)
        return LVSPIterator(self._CollectionIndex)
    @property
    def ANIO(self):
        class ANIOIterator():
            def __init__(self, CollectionIndex):
                CBash.IncrementIterator.restype = c_longlong
                self._CollectionIndex = CollectionIndex
            def __iter__(self):
                self._IteratorIndex = CBash.StartANIOIterator(self._CollectionIndex)
                return self
            def next(self):
                nextRecordID = CBash.IncrementIterator(self._IteratorIndex)
                if nextRecordID == -1:
                    CBash.StopIterator(self._IteratorIndex)
                    raise StopIteration
                return ANIORecord(self._CollectionIndex, 0, nextRecordID)
        return ANIOIterator(self._CollectionIndex)
    @property
    def WATR(self):
        class WATRIterator():
            def __init__(self, CollectionIndex):
                CBash.IncrementIterator.restype = c_longlong
                self._CollectionIndex = CollectionIndex
            def __iter__(self):
                self._IteratorIndex = CBash.StartWATRIterator(self._CollectionIndex)
                return self
            def next(self):
                nextRecordID = CBash.IncrementIterator(self._IteratorIndex)
                if nextRecordID == -1:
                    CBash.StopIterator(self._IteratorIndex)
                    raise StopIteration
                return WATRRecord(self._CollectionIndex, 0, nextRecordID)
        return WATRIterator(self._CollectionIndex)
    @property
    def EFSH(self):
        class EFSHIterator():
            def __init__(self, CollectionIndex):
                CBash.IncrementIterator.restype = c_longlong
                self._CollectionIndex = CollectionIndex
            def __iter__(self):
                self._IteratorIndex = CBash.StartEFSHIterator(self._CollectionIndex)
                return self
            def next(self):
                nextRecordID = CBash.IncrementIterator(self._IteratorIndex)
                if nextRecordID == -1:
                    CBash.StopIterator(self._IteratorIndex)
                    raise StopIteration
                return EFSHRecord(self._CollectionIndex, 0, nextRecordID)
        return EFSHIterator(self._CollectionIndex)
    
    def __iter__(self):
        self._ModIndex = -1
        return self

    def __len__(self):
        return CBash.GetNumMods(self._CollectionIndex)

    def next(self):
        self._ModIndex = self._ModIndex + 1
        if self._ModIndex >= CBash.GetNumMods(self._CollectionIndex):
            raise StopIteration
        return ModFile(self._CollectionIndex, CBash.GetModName(self._CollectionIndex, self._ModIndex))

    def __getitem__(self, ModIndex):
        if(ModIndex < 0 or ModIndex >= CBash.GetNumMods(self._CollectionIndex)):
            raise IndexError
        else:
            return ModFile(self._CollectionIndex, CBash.GetModName(self._CollectionIndex, ModIndex))

    def getChangedMods(self):
        return CBash.GetChangedMods(self._CollectionIndex)

    def safeSaveMod(self, ModName):
        return CBash.SafeSaveMod(self._CollectionIndex, ModName)

    def safeSaveAllChangedMods(self):
        return CBash.SafeSaveAllChangedMods(self._recordID)    