from ctypes import *
import struct
import math
from os.path import exists
try:
    from bolt import GPath
    import bush
    import bosh
except:
    def GPath(obj):
        return obj

_CBashRequiredVersion = (0,5,0)

CBash = None
if(exists(".\\CBash.dll")):
    CBash = CDLL("CBash.dll")
    try:
        try:
            _CGetVersionMajor = CBash.GetVersionMajor
            _CGetVersionMinor = CBash.GetVersionMinor
            _CGetVersionRevision = CBash.GetVersionRevision
        except AttributeError: #Functions were renamed in v0.5.0
            _CGetVersionMajor = CBash.GetMajor
            _CGetVersionMinor = CBash.GetMinor
            _CGetVersionRevision = CBash.GetRevision
        _CGetVersionMajor.restype = c_ulong
        _CGetVersionMinor.restype = c_ulong
        _CGetVersionRevision.restype = c_ulong
        if (_CGetVersionMajor(),_CGetVersionMinor(),_CGetVersionRevision()) < _CBashRequiredVersion:
            raise ImportError("cint.py requires CBash v%d.%d.%d or higher! (found v%d.%d.%d)" % (_CBashRequiredVersion + (_CGetVersionMajor(),_CGetVersionMinor(),_CGetVersionRevision())))
        _CCreateCollection = CBash.CreateCollection
        _CDeleteCollection = CBash.DeleteCollection
        _CLoadCollection = CBash.LoadCollection
        _CUnloadCollection = CBash.UnloadCollection
        _CDeleteAllCollections = CBash.DeleteAllCollections
        _CAddMod = CBash.AddMod
        _CLoadMod = CBash.LoadMod
        _CUnloadMod = CBash.UnloadMod
        _CCleanModMasters = CBash.CleanModMasters
        _CSaveMod = CBash.SaveMod
        _CGetAllNumMods = CBash.GetAllNumMods
        _CGetAllModIDs = CBash.GetAllModIDs
        _CGetLoadOrderNumMods = CBash.GetLoadOrderNumMods
        _CGetLoadOrderModIDs = CBash.GetLoadOrderModIDs
        _CGetFileNameByID = CBash.GetFileNameByID
        _CGetFileNameByLoadOrder = CBash.GetFileNameByLoadOrder
        _CGetModNameByID = CBash.GetModNameByID
        _CGetModNameByLoadOrder = CBash.GetModNameByLoadOrder
        _CGetModIDByName = CBash.GetModIDByName
        _CGetModIDByLoadOrder = CBash.GetModIDByLoadOrder
        _CGetModLoadOrderByName = CBash.GetModLoadOrderByName
        _CGetModLoadOrderByID = CBash.GetModLoadOrderByID
        _CGetLongIDName = CBash.GetLongIDName
        _CIsModEmpty = CBash.IsModEmpty
        _CGetModNumTypes = CBash.GetModNumTypes
        _CGetModTypes = CBash.GetModTypes
        _CCreateRecord = CBash.CreateRecord
        _CDeleteRecord = CBash.DeleteRecord
        _CCopyRecord = CBash.CopyRecord
        _CUnloadRecord = CBash.UnloadRecord
        _CSetRecordIdentifiers = CBash.SetRecordIdentifiers
        _CGetRecordID = CBash.GetRecordID
        _CGetNumRecords = CBash.GetNumRecords
        _CGetRecordIDs = CBash.GetRecordIDs
        _CIsRecordWinning = CBash.IsRecordWinning
        _CGetNumRecordConflicts = CBash.GetNumRecordConflicts
        _CGetRecordConflicts = CBash.GetRecordConflicts
        _CGetRecordHistory = CBash.GetRecordHistory
        _CUpdateReferences = CBash.UpdateReferences
        _CGetNumReferences = CBash.GetNumReferences
        _CSetField = CBash.SetField
        _CDeleteField = CBash.DeleteField
        _CGetFieldAttribute = CBash.GetFieldAttribute
        _CGetField = CBash.GetField
        _CCreateCollection.restype = c_ulong
        _CDeleteCollection.restype = c_long
        _CLoadCollection.restype = c_long
        _CUnloadCollection.restype = c_long
        _CDeleteAllCollections.restype = c_long
        _CAddMod.restype = c_long
        _CLoadMod.restype = c_long
        _CUnloadMod.restype = c_long
        _CCleanModMasters.restype = c_long
        _CGetAllNumMods.restype = c_long
        _CGetAllModIDs.restype = c_long
        _CGetLoadOrderNumMods.restype = c_long
        _CGetLoadOrderModIDs.restype = c_long
        _CGetFileNameByID.restype = c_char_p
        _CGetFileNameByLoadOrder.restype = c_char_p
        _CGetModNameByID.restype = c_char_p
        _CGetModNameByLoadOrder.restype = c_char_p
        _CGetModIDByName.restype = c_ulong
        _CGetModIDByLoadOrder.restype = c_ulong
        _CGetModLoadOrderByName.restype = c_long
        _CGetModLoadOrderByID.restype = c_long
        _CGetLongIDName.restype = c_char_p
        _CIsModEmpty.restype = c_ulong
        _CGetModNumTypes.restype = c_long
        _CCreateRecord.restype = c_ulong
        _CDeleteRecord.restype = c_long
        _CCopyRecord.restype = c_ulong
        _CUnloadRecord.restype = c_long
        _CSetRecordIdentifiers.restype = c_long
        _CGetRecordID.restype = c_ulong
        _CGetNumRecords.restype = c_long
        _CIsRecordWinning.restype = c_long
        _CGetNumRecordConflicts.restype = c_long
        _CGetRecordConflicts.restype = c_long
        _CGetRecordHistory.restype = c_long
        _CUpdateReferences.restype = c_long
        _CGetNumReferences.restype = c_long
        _CGetFieldAttribute.restype = c_ulong
    except AttributeError, error:
        CBash = None
        print error
    except ImportError, error:
        CBash = None
        print error
    except:
        CBash = None
        raise

def LoggingCB(logString):
    print logString
    return 0

LoggingCallback = CFUNCTYPE(c_long, c_char_p)(LoggingCB)

#Helper functions
class API_FIELDS(object):
    """These fields MUST be defined in the same order as in CBash's Common.h"""
    __slots__ = ['UNKNOWN', 'MISSING', 'JUNK', 'BOOL',
                  'SINT8', 'UINT8', 'SINT16', 'UINT16',
                  'SINT32', 'UINT32', 'FLOAT32',
                  'RADIAN', 'FORMID', 'MGEFCODE',
                  'ACTORVALUE', 'FORMID_OR_UINT32',
                  'FORMID_OR_FLOAT32', 'UINT8_OR_UINT32',
                  'UNKNOWN_OR_FORMID_OR_UINT32',
                  'UNKNOWN_OR_SINT32', 'MGEFCODE_OR_UINT32',
                  'FORMID_OR_MGEFCODE_OR_ACTORVALUE_OR_UINT32',
                  'RESOLVED_MGEFCODE', 'STATIC_MGEFCODE',
                  'RESOLVED_ACTORVALUE', 'STATIC_ACTORVALUE',
                  'CHAR', 'CHAR4', 'STRING', 'ISTRING',
                  'STRING_OR_FLOAT32_OR_SINT32', 'LIST',
                  'PARENTRECORD', 'SUBRECORD', 'SINT8_FLAG',
                  'SINT8_TYPE', 'SINT8_FLAG_TYPE', 'SINT8_ARRAY',
                  'UINT8_FLAG', 'UINT8_TYPE', 'UINT8_FLAG_TYPE',
                  'UINT8_ARRAY', 'SINT16_FLAG', 'SINT16_TYPE',
                  'SINT16_FLAG_TYPE', 'SINT16_ARRAY',
                  'UINT16_FLAG', 'UINT16_TYPE', 'UINT16_FLAG_TYPE',
                  'UINT16_ARRAY', 'SINT32_FLAG', 'SINT32_TYPE',
                  'SINT32_FLAG_TYPE', 'SINT32_ARRAY', 'UINT32_FLAG',
                  'UINT32_TYPE', 'UINT32_FLAG_TYPE', 'UINT32_ARRAY',
                  'FLOAT32_ARRAY', 'RADIAN_ARRAY', 'FORMID_ARRAY',
                  'FORMID_OR_UINT32_ARRAY', 'MGEFCODE_OR_UINT32_ARRAY',
                  'STRING_ARRAY', 'ISTRING_ARRAY', 'SUBRECORD_ARRAY',
                  'UNDEFINED']

for value, attr in enumerate(API_FIELDS.__slots__):
    setattr(API_FIELDS, attr, value)

class ISTRING(str):
    """Case insensitive strings class. Performs like str except comparisons are case insensitive."""

    def __eq__(self, other):
        try:
            return self.lower() == other.lower()
        except AttributeError:
            return False

    def __lt__(self, other):
        try:
            return self.lower() < other.lower()
        except AttributeError:
            return False

    def __le__(self, other):
        try:
            return self.lower() <= other.lower()
        except AttributeError:
            return False

    def __gt__(self, other):
        try:
            return self.lower() > other.lower()
        except AttributeError:
            return False

    def __ne__(self, other):
        try:
            return self.lower() != other.lower()
        except AttributeError:
            return False

    def __ge__(self, other):
        try:
            return self.lower() >= other.lower()
        except AttributeError:
            return False

    def __cmp__(self, other):
        try:
            return cmp(self.lower(), other.lower())
        except AttributeError:
            return False

    def __hash__(self):
        return hash(self.lower())

    def __contains__(self, other):
        try:
            return other.lower() in self.lower()
        except AttributeError:
            return False

    def count(self, other, *args):
        try:
            return str.count(self.lower(), other.lower(), *args)
        except AttributeError:
            return 0

    def endswith(self, other, *args):
        try:
            if isinstance(other, tuple):
                for value in other:
                    if str.endswith(self.lower(), value.lower(), *args):
                        return True
                return False
            return str.endswith(self.lower(), other.lower(), *args)
        except AttributeError:
            return False

    def find(self, other, *args):
        try:
            return str.find(self.lower(), other.lower(), *args)
        except AttributeError:
            return -1

    def index(self, other, *args):
        try:
            return str.index(self.lower(), other.lower(), *args)
        except AttributeError:
            return ValueError

    def rfind(self, other, *args):
        try:
            return str.rfind(self.lower(), other.lower(), *args)
        except AttributeError:
            return -1

    def rindex(self, other, *args):
        try:
            return str.rindex(self.lower(), other.lower(), *args)
        except AttributeError:
            return ValueError

    def startswith(self, other, *args):
        try:
            if isinstance(other, tuple):
                for value in other:
                    if str.startswith(self.lower(), value.lower(), *args):
                        return True
                return False
            return str.startswith(self.lower(), other.lower(), *args)
        except AttributeError:
            return False

class PrintFormID(object):
    def __init__(self, formID):
        self._FormID = formID

    def __repr__(self):
        if(self._FormID):
            if isinstance(self._FormID, tuple):
                return '(%s, 0x%06X)' % (str(self._FormID[0]),self._FormID[1])
            return "%08X" % self._FormID
        return "None"

    def __str__(self):
        if(self._FormID):
            if isinstance(self._FormID, tuple):
                return '(%s, 0x%06X)' % (str(self._FormID[0]),self._FormID[1])
            return "%08X" % self._FormID
        return "None"

def getattr_deep(obj, attr):
    return reduce(getattr, attr.split('.'), obj)

def setattr_deep(obj, attr, value):
    attrs = attr.split('.')
    setattr(reduce(getattr, attrs[:-1], obj), attrs[-1], value)

def MakeLongFid(CollectionID, ModID, fid):
    if fid is None or fid == 0: return 0
    if isinstance(fid,tuple): return fid
    master = _CGetLongIDName(CollectionID, ModID, int(fid >> 24))
    if not master: return (None,int(fid & 0x00FFFFFFL))
    return (GPath(master),int(fid & 0x00FFFFFFL))

def MakeShortFid(CollectionID, fid):
    if fid is None or fid == 0: return 0
    if not isinstance(fid,tuple): return fid
    master, object = fid
    if master is None:
        raise AttributeError("Unable to convert long fid (None, %06X) into a short formID" % object)
    masterIndex = _CGetModLoadOrderByName(CollectionID, str(master))
    if(masterIndex == -1): return None
    return int(masterIndex << 24) | int(object & 0x00FFFFFFL)

def MakeLongMGEFCode(CollectionID, ModID, MGEFCode):
    if MGEFCode is None or MGEFCode == 0: return 0
    if isinstance(MGEFCode,tuple): return MGEFCode
    master = _CGetLongIDName(CollectionID, ModID, int(MGEFCode & 0x000000FFL))
    if not master: return (None,int(MGEFCode & 0xFFFFFF00L))
    return (GPath(master),int(MGEFCode & 0xFFFFFF00L))

def MakeShortMGEFCode(CollectionID, ModID, MGEFCode):
    if isinstance(MGEFCode, basestring): MGEFCode = cast(MGEFCode, POINTER(c_ulong)).contents.value
    if MGEFCode is None or MGEFCode == 0: return 0
    if not isinstance(MGEFCode,tuple): return MGEFCode
    master, object = MGEFCode
    if master is None:
        raise AttributeError("Unable to convert long MGEFCode (None, %06X) into a short MGEFCode" % object)
    masterIndex = _CGetModLoadOrderByName(CollectionID, str(master))
    if(masterIndex == -1): return None
    return int(masterIndex & 0x000000FFL) | int(object & 0xFFFFFF00L)

def ExtractCopyList(Elements):
    return [tuple(getattr(listElement, attr) for attr in listElement.copyattrs) for listElement in Elements]

def SetCopyList(oElements, nValues):
    for oElement, nValueTuple in zip(oElements, nValues):
        for nValue, attr in zip(nValueTuple, oElement.copyattrs):
            setattr(oElement, attr, nValue)

def ExtractExportList(Element):
    try:
        return [tuple(ExtractExportList(listElement) if hasattr(listElement, 'exportattrs') else getattr(listElement, attr) for attr in listElement.exportattrs) for listElement in Element]
    except TypeError:
        return [tuple(ExtractExportList(getattr(Element, attr)) if hasattr(getattr(Element, attr), 'exportattrs') else getattr(Element, attr) for attr in Element.exportattrs)]

# Classes
# Any level Descriptors
class CBashAlias(object):
    def __init__(self, AttrName):
        self._AttrName = AttrName
    def __get__(self, instance, owner):
        return getattr(instance, self._AttrName, None)
    def __set__(self, instance, nValue):
        setattr(instance, self._AttrName, nValue)

class CBashGrouped(object):
    def __init__(self, FieldID, Type, AsList=False):
        self._FieldID = FieldID
        self._Type = Type
        self._AsList = AsList
    def __get__(self, instance, owner):
        oElement = self._Type(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID)
        if(self._AsList): return tuple([getattr(oElement, attr) for attr in oElement.copyattrs])
        return oElement
    def __set__(self, instance, nElement):
        oElement = self._Type(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID)
        if nElement is None: nValueList = tuple([None for attr in oElement.copyattrs])
        elif isinstance(nElement, tuple): nValueTuple = nElement
        else: nValueTuple = tuple([getattr(nElement, attr) for attr in nElement.copyattrs])
        for nValue, attr in zip(nValueTuple, oElement.copyattrs):
            setattr(oElement, attr, nValue)

class CBashJunk(object):
    def __init__(self, FieldID):
        pass
    def __get__(self, instance, owner):
        return None
    def __set__(self, instance, nValue):
        pass

class CBashBasicFlag(object):
    def __init__(self, AttrName, Value):
        self._AttrName = AttrName
        self._Value = Value
    def __get__(self, instance, owner):
        field = getattr(instance, self._AttrName, None)
        if field is None: return None
        return (field & self._Value) != 0
    def __set__(self, instance, nValue):
        field = getattr(instance, self._AttrName, None)
        if nValue:
            if field: field |= self._Value
            else: field = self._Value
            setattr(instance, self._AttrName, field)
        elif field:
            field &= ~self._Value
            setattr(instance, self._AttrName, field)

class CBashInvertedFlag(object):
    def __init__(self, AttrName):
        self._AttrName = AttrName
    def __get__(self, instance, owner):
        field = getattr(instance, self._AttrName, None)
        if field is None: return None
        return not field
    def __set__(self, instance, nValue):
        setattr(instance, self._AttrName, not nValue)

class CBashBasicType(object):
    def __init__(self, AttrName, value, default):
        self._AttrName = AttrName
        self._Value = value
        self._DefaultFieldName = default
    def __get__(self, instance, owner):
        field = getattr(instance, self._AttrName, None)
        if field is None: return None
        return field == self._Value
    def __set__(self, instance, nValue):
        if nValue: setattr(instance, self._AttrName, self._Value)
        else: setattr(instance, self._DefaultFieldName, True)

class CBashMaskedType(object):
    def __init__(self, AttrName, typeMask, value, default):
        self._AttrName = AttrName
        self._TypeMask = typeMask
        self._Value = value
        self._DefaultFieldName = default
    def __get__(self, instance, owner):
        field = getattr(instance, self._AttrName, None)
        if field is None: return None
        return (field & self._TypeMask) == self._Value
    def __set__(self, instance, nValue):
        if nValue:
            field = getattr(instance, self._AttrName, 0)
            field &= ~self._TypeMask
            field |= (self._Value & self._TypeMask)
            setattr(instance, self._AttrName, field)
        elif getattr(instance, self._AttrName, None): setattr(instance, self._DefaultFieldName, True)

# Grouped Top Descriptors
class CBashGeneric_GROUP(object):
    def __init__(self, FieldID, Type):
        self._FieldID = FieldID
        self._Type = Type
        self._ResType = POINTER(Type)
    def __get__(self, instance, owner):
        FieldID = self._FieldID + instance._FieldID
        _CGetField.restype = self._ResType
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, FieldID, 0, 0, 0, 0, 0, 0, 0)
        if(retValue): return retValue.contents.value
        return None
    def __set__(self, instance, nValue):
        FieldID = self._FieldID + instance._FieldID
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, FieldID, 0, 0, 0, 0, 0, 0)
        else: _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, FieldID, 0, 0, 0, 0, 0, 0, byref(self._Type(nValue)), 0)

class CBashUINT8ARRAY_GROUP(object):
    def __init__(self, FieldID, Size=None):
        self._FieldID = FieldID
        self._Size = Size
    def __get__(self, instance, owner):
        FieldID = self._FieldID + instance._FieldID
        numRecords = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, FieldID, 0, 0, 0, 0, 0, 0, 1)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, FieldID, 0, 0, 0, 0, 0, 0, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        return []
    def __set__(self, instance, nValue):
        FieldID = self._FieldID + instance._FieldID
        if nValue is None or not len(nValue): _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, FieldID, 0, 0, 0, 0, 0, 0)
        else:
            length = len(nValue)
            if self._Size and length != self._Size: return
            cRecords = (c_ubyte * length)(*nValue)
            _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, FieldID, 0, 0, 0, 0, 0, 0, byref(cRecords), length)

class CBashFLOAT32_GROUP(object):
    def __init__(self, FieldID):
        self._FieldID = FieldID
    def __get__(self, instance, owner):
        FieldID = self._FieldID + instance._FieldID
        _CGetField.restype = POINTER(c_float)
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, FieldID, 0, 0, 0, 0, 0, 0, 0)
        if(retValue): return round(retValue.contents.value,6)
        return None
    def __set__(self, instance, nValue):
        FieldID = self._FieldID + instance._FieldID
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, FieldID, 0, 0, 0, 0, 0, 0)
        else: _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, FieldID, 0, 0, 0, 0, 0, 0, byref(c_float(round(nValue,6))), 0)

class CBashSTRING_GROUP(object):
    def __init__(self, FieldID):
        self._FieldID = FieldID
    def __get__(self, instance, owner):
        FieldID = self._FieldID + instance._FieldID
        _CGetField.restype = c_char_p
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, FieldID, 0, 0, 0, 0, 0, 0, 0)
        if(retValue): return retValue
        return None
    def __set__(self, instance, nValue):
        FieldID = self._FieldID + instance._FieldID
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, FieldID, 0, 0, 0, 0, 0, 0)
        else: _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, FieldID, 0, 0, 0, 0, 0, 0, str(nValue), 0)

class CBashISTRING_GROUP(object):
    def __init__(self, FieldID):
        self._FieldID = FieldID
    def __get__(self, instance, owner):
        FieldID = self._FieldID + instance._FieldID
        _CGetField.restype = c_char_p
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, FieldID, 0, 0, 0, 0, 0, 0, 0)
        if(retValue): return ISTRING(retValue)
        return None
    def __set__(self, instance, nValue):
        FieldID = self._FieldID + instance._FieldID
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, FieldID, 0, 0, 0, 0, 0, 0)
        else: _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, FieldID, 0, 0, 0, 0, 0, 0, str(nValue), 0)

class CBashLIST_GROUP(object):
    def __init__(self, FieldID, Type, AsList=False):
        self._FieldID = FieldID
        self._Type = Type
        self._AsList = AsList
    def __get__(self, instance, owner):
        FieldID = self._FieldID + instance._FieldID
        numElements = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, FieldID, 0, 0, 0, 0, 0, 0, 1)
        oElements = [self._Type(instance._CollectionID, instance._ModID, instance._RecordID, FieldID, x) for x in range(0, numElements)]
        if(self._AsList): return ExtractCopyList(oElements)
        return oElements
    def __set__(self, instance, nElements):
        FieldID = self._FieldID + instance._FieldID
        if nElements is None or not len(nElements):
            _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, FieldID, 0, 0, 0, 0, 0, 0)
        else:
            length = len(nElements)
            if isinstance(nElements[0], tuple): nValues = nElements
            else: nValues = ExtractCopyList(nElements)
            ##Resizes the list
            _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, FieldID, 0, 0, 0, 0, 0, 0, 0, c_long(length))
            numElements = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, FieldID, 0, 0, 0, 0, 0, 0, 1)
            oElements = [self._Type(instance._CollectionID, instance._ModID, instance._RecordID, FieldID, x) for x in range(0, numElements)]
            SetCopyList(oElements, nValues)

# Top level Descriptors
class CBashLIST(object):
    def __init__(self, FieldID, Type, AsList=False):
        self._FieldID = FieldID
        self._Type = Type
        self._AsList = AsList
    def __get__(self, instance, owner):
        numElements = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 1)
        oElements = [self._Type(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, x) for x in range(0, numElements)]
        if(self._AsList): return ExtractCopyList(oElements)
        return oElements
    def __set__(self, instance, nElements):
        if nElements is None or not len(nElements):
            _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0)
        else:
            length = len(nElements)
            if isinstance(nElements[0], tuple): nValues = nElements
            else: nValues = ExtractCopyList(nElements)
            ##Resizes the list
            _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 0, c_long(length))
            numElements = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 1)
            oElements = [self._Type(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, x) for x in range(0, numElements)]
            SetCopyList(oElements, nValues)

class CBashSINT32_OR_UNKNOWN(object):
    def __init__(self, FieldID):
        self._FieldID = FieldID
    def __get__(self, instance, owner):
        type = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 2)
        if type == API_FIELDS.SINT32:
            _CGetField.restype = POINTER(c_long)
            retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 0)
            if(retValue): return retValue.contents.value
        return None
    def __set__(self, instance, nValue):
        type = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 2)
        if type == API_FIELDS.SINT32:
            if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0)
            else: _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, byref(c_long(nValue)), 0)


class CBashXSED(object):
    """To delete the field, you have to set the current accessor to None."""
    def __init__(self, FieldID, AsOffset=False):
        self._FieldID = FieldID
        self._AsOffset = AsOffset
    def __get__(self, instance, owner):
        type = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 2)
        if self._AsOffset:
            if type == API_FIELDS.UINT32: return None #Mismatched variables
            _CGetField.restype = POINTER(c_ubyte)
        else:
            if type == API_FIELDS.UINT8: return None #Mismatched variables
            _CGetField.restype = POINTER(c_ulong)
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 0)
        if(retValue): return retValue.contents.value
        return None
    def __set__(self, instance, nValue):
        type = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 2)
        if nValue is None:
            if self._AsOffset:
                if type == API_FIELDS.UINT32: return #Mismatched variables
            else:
                if type == API_FIELDS.UINT8: return #Mismatched variables
            _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0)
        else:
            if self._AsOffset: nValue = c_ubyte(nValue)
            else: nValue = c_ulong(nValue)
            #Borrowing ArraySize to flag if the new value is an offset
            _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, byref(nValue), c_bool(self._AsOffset))


class CBashISTRINGARRAY(object):
    def __init__(self, FieldID):
        self._FieldID = FieldID
    def __get__(self, instance, owner):
        numRecords = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 1)
        if(numRecords > 0):
            cRecords = (POINTER(c_char_p) * numRecords)()
            _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, byref(cRecords))
            return [ISTRING(string_at(cRecords[x])) for x in range(0, numRecords)]
        return []
    def __set__(self, instance, nValue):
        if nValue is None or not len(nValue): _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0)
        else:
            length = len(nValue)
            cRecords = (c_char_p * length)(*nValue)
            _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, byref(cRecords), length)

class CBashGeneric(object):
    def __init__(self, FieldID, Type):
        self._FieldID = FieldID
        self._Type = Type
        self._ResType = POINTER(Type)
    def __get__(self, instance, owner):
        _CGetField.restype = self._ResType
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 0)
        if(retValue): return retValue.contents.value
        return None
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0)
        else: _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, byref(self._Type(nValue)), 0)

class CBashFORMID(object):
    def __init__(self, FieldID):
        self._FieldID = FieldID
    def __get__(self, instance, owner):
        _CGetField.restype = POINTER(c_ulong)
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 0)
        if(retValue): return MakeLongFid(instance._CollectionID, instance._ModID, retValue.contents.value)
        return None
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0)
        else: _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, byref(c_ulong(MakeShortFid(instance._CollectionID, nValue))), 0)

class CBashMGEFCODE(object):
    def __init__(self, FieldID):
        self._FieldID = FieldID
    def __get__(self, instance, owner):
        _CGetField.restype = POINTER(c_ulong)
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 0)
        if(retValue):
            type = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 2)
            if type == API_FIELDS.STATIC_MGEFCODE:
                return retValue.contents.value
            elif type == API_FIELDS.RESOLVED_MGEFCODE:
                return MakeLongMGEFCode(instance._CollectionID, instance._ModID, retValue.contents.value)
        return None
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0)
        else:
            _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, byref(c_ulong(MakeShortMGEFCode(instance._CollectionID, instance._ModID, nValue))), 0)

class CBashFORMIDARRAY(object):
    def __init__(self, FieldID):
        self._FieldID = FieldID
    def __get__(self, instance, owner):
        numRecords = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 1)
        if(numRecords > 0):
            cRecords = POINTER(c_ulong * numRecords)()
            _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, byref(cRecords))
            return [MakeLongFid(instance._CollectionID, instance._ModID, cRecords.contents[x]) for x in range(0, numRecords)]
        return []
    def __set__(self, instance, nValue):
        if nValue is None or not len(nValue): _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0)
        else:
            length = len(nValue)
            nValue = [MakeShortFid(instance._CollectionID, x) for x in nValue]
            cRecords = (c_ulong * length)(*nValue)
            _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, byref(cRecords), length)

class CBashFORMID_OR_UINT32(object):
    def __init__(self, FieldID):
        self._FieldID = FieldID
    def __get__(self, instance, owner):
        _CGetField.restype = POINTER(c_ulong)
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 0)
        if(retValue):
            type = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 2)
            if type == API_FIELDS.UINT32:
                return retValue.contents.value
            elif type == API_FIELDS.FORMID:
                return MakeLongFid(instance._CollectionID, instance._ModID, retValue.contents.value)
        return None
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0)
        else:
            _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, byref(c_ulong(MakeShortFid(instance._CollectionID, nValue))), 0)

class CBashFORMID_OR_UINT32_ARRAY(object):
    def __init__(self, FieldID, Size=None):
        self._FieldID = FieldID
        self._Size = Size
    def __get__(self, instance, owner):
        values = []
        numRecords = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 1)
        if(numRecords > 0):
            cRecords = (c_ulong * numRecords)()
            _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, byref(cRecords))
            for x in range(numRecords):
                type = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, x, 1, 0, 0, 0, 0, 2)
                if type == API_FIELDS.UINT32:
                    values.append(cRecords[x])
                elif type == API_FIELDS.FORMID:
                    values.append(MakeLongFid(instance._CollectionID, instance._ModID, cRecords[x]))
        return values
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0)
        else:
            length = len(nValue)
            if self._Size and length != self._Size: return
            #Each element can be either a formID or UINT32, so they have to be set separately
            #Resize the list
            _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 0, c_long(length))
            for x, value in enumerate(nValue):
                #Borrowing ArraySize to flag if the new value is a formID
                IsFormID = isinstance(value, tuple)
                _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, x, 1, 0, 0, 0, 0, byref(c_ulong(MakeShortFid(instance._CollectionID, value))), IsFormID)

class CBashMGEFCODE_OR_UINT32_ARRAY(object):
    def __init__(self, FieldID, Size=None):
        self._FieldID = FieldID
        self._Size = Size
    def __get__(self, instance, owner):
        values = []
        numRecords = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 1)
        if(numRecords > 0):
            cRecords = POINTER(c_ulong * numRecords)()
            _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, byref(cRecords))
            for x in range(numRecords):
                type = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, x, 1, 0, 0, 0, 0, 2)
                if type in (API_FIELDS.UINT32, API_FIELDS.STATIC_MGEFCODE):
                    values.append(cRecords.contents[x])
                elif type == API_FIELDS.RESOLVED_MGEFCODE:
                    values.append(MakeLongMGEFCode(instance._CollectionID, instance._ModID, cRecords.contents[x]))
        return values
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0)
        else:
            length = len(nValue)
            if self._Size and length != self._Size: return
            #They are either all MGEFCodes or all UINT32's, so it can be set in one operation
            nValue = [MakeShortMGEFCode(instance._CollectionID, instance._ModID, x) for x in nValue]
            cRecords = (c_ulong * length)(*nValue)
            _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, byref(cRecords), length)

class CBashUINT8ARRAY(object):
    def __init__(self, FieldID, Size=None):
        self._FieldID = FieldID
        self._Size = Size
    def __get__(self, instance, owner):
        numRecords = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 1)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        return []
    def __set__(self, instance, nValue):
        if nValue is None or not len(nValue): _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0)
        else:
            length = len(nValue)
            if self._Size and length != self._Size: return
            cRecords = (c_ubyte * length)(*nValue)
            _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, byref(cRecords), length)

class CBashUINT32ARRAY(object):
    def __init__(self, FieldID, Size=None):
        self._FieldID = FieldID
        self._Size = Size
    def __get__(self, instance, owner):
        numRecords = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 1)
        if(numRecords > 0):
            cRecords = POINTER(c_ulong * numRecords)()
            _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        return []
    def __set__(self, instance, nValue):
        if nValue is None or not len(nValue): _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0)
        else:
            length = len(nValue)
            if self._Size and length != self._Size: return
            cRecords = (c_ulong * length)(*nValue)
            _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, byref(cRecords), length)

class CBashSINT16ARRAY(object):
    def __init__(self, FieldID, Size=None):
        self._FieldID = FieldID
        self._Size = Size
    def __get__(self, instance, owner):
        numRecords = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 1)
        if(numRecords > 0):
            cRecords = POINTER(c_short * numRecords)()
            _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        return []
    def __set__(self, instance, nValue):
        if nValue is None or not len(nValue): _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0)
        else:
            length = len(nValue)
            if self._Size and length != self._Size: return
            cRecords = (c_short * length)(*nValue)
            _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, byref(cRecords), length)

class CBashFLOAT32(object):
    def __init__(self, FieldID):
        self._FieldID = FieldID
    def __get__(self, instance, owner):
        _CGetField.restype = POINTER(c_float)
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 0)
        if(retValue): return round(retValue.contents.value,6)
        return None
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0)
        else: _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, byref(c_float(round(nValue,6))), 0)

class CBashDEGREES(object):
    def __init__(self, FieldID):
        self._FieldID = FieldID
    def __get__(self, instance, owner):
        _CGetField.restype = POINTER(c_float)
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 0)
        if(retValue):
            try:
                return round(math.degrees(retValue.contents.value),6)
            except TypeError:
                return None
        return None
    def __set__(self, instance, nValue):
        try:
            nValue = math.radians(nValue)
        except TypeError:
            nValue = None
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0)
        else: _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, byref(c_float(round(nValue,6))), 0)

class CBashSTRING(object):
    def __init__(self, FieldID):
        self._FieldID = FieldID
    def __get__(self, instance, owner):
        _CGetField.restype = c_char_p
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 0)
        if(retValue): return retValue
        return None
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0)
        else: _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, str(nValue), 0)

class CBashISTRING(object):
    def __init__(self, FieldID):
        self._FieldID = FieldID
    def __get__(self, instance, owner):
        _CGetField.restype = c_char_p
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 0)
        if(retValue): return ISTRING(retValue)
        return None
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0)
        else: _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, str(nValue), 0)


class CBashRECORDARRAY(object):
    def __init__(self, Type, TypeName, CopyFlags=0):
        self._Type = Type
        self._TypeName = cast(TypeName, POINTER(c_ulong)).contents.value
        self._CopyFlags = CopyFlags
    def __get__(self, instance, owner):
        numRecords = _CGetNumRecords(instance._CollectionID, instance._ModID, self._TypeName)
        if(numRecords > 0):
            cRecords = (c_ulong * numRecords)()
            _CGetRecordIDs(instance._CollectionID, instance._ModID, self._TypeName, byref(cRecords))
            return [self._Type(instance._CollectionID, instance._ModID, x, 0, self._CopyFlags) for x in cRecords]
        return []
    def __set__(self, instance, nValue):
        return

class CBashSUBRECORD(object):
    def __init__(self, FieldID, Type, TypeName, CopyFlags=0):
        self._FieldID = FieldID
        self._Type = Type
        self._TypeName = TypeName
        self._CopyFlags = CopyFlags
        self._ResType = c_ulong
    def __get__(self, instance, owner):
        _CGetField.restype = self._ResType
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 0)
        if(retValue): return self._Type(instance._CollectionID, instance._ModID, retValue, instance._RecordID, self._CopyFlags)
        return None
    def __set__(self, instance, nValue):
        _CGetField.restype = self._ResType
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 0)
        if(retValue): oSubRecord = self._Type(instance._CollectionID, instance._ModID, retValue, instance._RecordID, self._CopyFlags)
        else: oSubRecord = None
        if nSubRecord is None and oSubRecord is not None: oSubRecord.DeleteRecord()
        else:
            if oSubRecord is None:
                RecordID = _CCreateRecord(instance._CollectionID, instance._ModID, self._TypeName, 0, 0, instance._RecordID, c_ulong(self._CopyFlags))
                if(RecordID): oSubRecord = self._Type(instance._CollectionID, instance._ModID, RecordID, instance._RecordID, self._CopyFlags)
            if oSubRecord is None:
                return
            SetCopyList(oSubRecord, ExtractCopyList(nSubRecord))

class CBashSUBRECORDARRAY(object):
    def __init__(self, FieldID, Type, TypeName, CopyFlags=0):
        self._FieldID = FieldID
        self._Type = Type
        self._TypeName = TypeName
        self._CopyFlags = CopyFlags
    def __get__(self, instance, owner):
        numRecords = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 1)
        if(numRecords > 0):
            cRecords = (c_ulong * numRecords)()
            _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, byref(cRecords))
            return [self._Type(instance._CollectionID, instance._ModID, x, instance._RecordID, self._CopyFlags) for x in cRecords]
        return []
    def __set__(self, instance, nValue):
        return

# ListX1 Descriptors
class CBashLIST_LIST(object):
    def __init__(self, ListFieldID, Type, AsList=False):
        self._ListFieldID = ListFieldID
        self._Type = Type
        self._AsList = AsList
    def __get__(self, instance, owner):
        numElements = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 1)
        oElements = [self._Type(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, x) for x in range(0, numElements)]
        if(self._AsList): return ExtractCopyList(oElements)
        return oElements
    def __set__(self, instance, nElements):
        if nElements is None or not len(nElements):
            _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0)
        else:
            length = len(nElements)
            if isinstance(nElements[0], tuple): nValues = nElements
            else: nValues = ExtractCopyList(nElements)
            ##Resizes the list
            _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 0, c_long(length))
            numElements = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 1)
            oElements = [self._Type(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, x) for x in range(0, numElements)]
            SetCopyList(oElements, nValues)

class CBashGeneric_LIST(object):
    def __init__(self, ListFieldID, Type):
        self._ListFieldID = ListFieldID
        self._Type = Type
        self._ResType = POINTER(Type)
    def __get__(self, instance, owner):
        _CGetField.restype = self._ResType
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 0)
        if(retValue): return retValue.contents.value
        return None
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0)
        else: _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, byref(self._Type(nValue)), 0)

class CBashFORMID_LIST(object):
    def __init__(self, ListFieldID):
        self._ListFieldID = ListFieldID
    def __get__(self, instance, owner):
        _CGetField.restype = POINTER(c_ulong)
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 0)
        if(retValue): return MakeLongFid(instance._CollectionID, instance._ModID, retValue.contents.value)
        return None
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0)
        else: _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, byref(c_ulong(MakeShortFid(instance._CollectionID, nValue))), 0)

class CBashACTORVALUE_LIST(object):
    def __init__(self, ListFieldID):
        self._ListFieldID = ListFieldID
    def __get__(self, instance, owner):
        _CGetField.restype = POINTER(c_ulong)
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 0)
        if(retValue):
            type = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 2)
            if type == API_FIELDS.STATIC_ACTORVALUE:
                return retValue.contents.value
            elif type == API_FIELDS.RESOLVED_ACTORVALUE:
                #Resolved Actor Value's are not formIDs, but can be treated as such for resolution
                return MakeLongFid(instance._CollectionID, instance._ModID, retValue.contents.value)
        return None
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0)
        else:
            _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, byref(c_ulong(MakeShortFid(instance._CollectionID, nValue))), 0)

class CBashFORMIDARRAY_LIST(object):
    def __init__(self, ListFieldID):
        self._ListFieldID = ListFieldID
    def __get__(self, instance, owner):
        numRecords = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 1)
        if(numRecords > 0):
            cRecords = POINTER(c_ulong * numRecords)()
            _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, byref(cRecords))
            return [MakeLongFid(instance._CollectionID, instance._ModID, cRecords.contents[x]) for x in range(0, numRecords)]
        return []
    def __set__(self, instance, nValue):
        if nValue is None or not len(nValue): _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0)
        else:
            length = len(nValue)
            nValue = [MakeShortFid(instance._CollectionID, x) for x in nValue]
            cRecords = (c_ulong * length)(*nValue)
            _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, byref(cRecords), length)

class CBashUNKNOWN_OR_FORMID_OR_UINT32_LIST(object):
    def __init__(self, ListFieldID):
        self._ListFieldID = ListFieldID
    def __get__(self, instance, owner):
        type = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 2)
        if type != API_FIELDS.UNKNOWN:
            _CGetField.restype = POINTER(c_long)
            retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 0)
            if(retValue):
                if type == API_FIELDS.UINT32:
                    return retValue.contents.value
                elif type == API_FIELDS.FORMID:
                    return MakeLongFid(instance._CollectionID, instance._ModID, retValue.contents.value)
        return None
    def __set__(self, instance, nValue):
        type = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 2)
        if type != API_FIELDS.UNKNOWN:
            if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0)
            else:
                _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, byref(c_ulong(MakeShortFid(instance._CollectionID, nValue))), 0)

class CBashMGEFCODE_OR_UINT32_LIST(object):
    def __init__(self, ListFieldID):
        self._ListFieldID = ListFieldID
    def __get__(self, instance, owner):
        _CGetField.restype = POINTER(c_long)
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 0)
        if(retValue):
            type = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 2)
            if type in (API_FIELDS.UINT32, API_FIELDS.STATIC_MGEFCODE):
                return retValue.contents.value
            elif type == API_FIELDS.RESOLVED_MGEFCODE:
                return MakeLongMGEFCode(instance._CollectionID, instance._ModID, retValue.contents.value)
        return None
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0)
        else:
            _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, byref(c_ulong(MakeShortMGEFCode(instance._CollectionID, instance._ModID, nValue))), 0)

class CBashFORMID_OR_MGEFCODE_OR_ACTORVALUE_OR_UINT32_LIST(object):
    def __init__(self, ListFieldID):
        self._ListFieldID = ListFieldID
    def __get__(self, instance, owner):
        _CGetField.restype = POINTER(c_long)
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 0)
        if(retValue):
            type = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 2)
            if type in (API_FIELDS.UINT32, API_FIELDS.STATIC_MGEFCODE, API_FIELDS.STATIC_ACTORVALUE):
                return retValue.contents.value
            elif type == API_FIELDS.RESOLVED_MGEFCODE:
                return MakeLongMGEFCode(instance._CollectionID, instance._ModID, retValue.contents.value)
            elif type in (API_FIELDS.FORMID, API_FIELDS.RESOLVED_ACTORVALUE):
                #Resolved Actor Value's are not formIDs, but can be treated as such for resolution
                return MakeLongFid(instance._CollectionID, instance._ModID, retValue.contents.value)
        return None
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0)
        else:
            type = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 2)
            if type in (API_FIELDS.STATIC_MGEFCODE, API_FIELDS.RESOLVED_MGEFCODE): nValue = MakeShortMGEFCode(instance._CollectionID, instance._ModID, nValue)
            elif type in (API_FIELDS.FORMID, API_FIELDS.STATIC_ACTORVALUE, API_FIELDS.RESOLVED_ACTORVALUE): nValue = MakeShortFid(instance._CollectionID, nValue)
            elif type == API_FIELDS.UINT32 and isinstance(nValue, tuple): return
            _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, byref(c_ulong(nValue)), 0)

class CBashUINT8ARRAY_LIST(object):
    def __init__(self, ListFieldID, Size=None):
        self._ListFieldID = ListFieldID
        self._Size = Size
    def __get__(self, instance, owner):
        numRecords = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 1)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        return []
    def __set__(self, instance, nValue):
        if nValue is None or not len(nValue): _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0)
        else:
            length = len(nValue)
            if self._Size and length != self._Size: return
            cRecords = (c_ubyte * length)(*nValue)
            _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, byref(cRecords), length)

class CBashUINT32ARRAY_LIST(object):
    def __init__(self, ListFieldID, Size=None):
        self._ListFieldID = ListFieldID
        self._Size = Size
    def __get__(self, instance, owner):
        numRecords = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 1)
        if(numRecords > 0):
            cRecords = POINTER(c_ulong * numRecords)()
            _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        return []
    def __set__(self, instance, nValue):
        if nValue is None or not len(nValue): _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0)
        else:
            length = len(nValue)
            if self._Size and length != self._Size: return
            cRecords = (c_ulong * length)(*nValue)
            _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, byref(cRecords), length)

class CBashFORMID_OR_UINT32_ARRAY_LIST(object):
    def __init__(self, ListFieldID, Size=None):
        self._ListFieldID = ListFieldID
        self._Size = Size
    def __get__(self, instance, owner):
        values = []
        numRecords = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 1)
        if(numRecords > 0):
            cRecords = (c_ulong * numRecords)()
            _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, byref(cRecords))
            for x in range(numRecords):
                type = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, instance._ListIndex, self._ListFieldID, x, 1, 0, 0, 2)
                if type == API_FIELDS.UINT32:
                    values.append(cRecords[x])
                elif type == API_FIELDS.FORMID:
                    values.append(MakeLongFid(instance._CollectionID, instance._ModID, cRecords[x]))
        return values
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0)
        else:
            length = len(nValue)
            if self._Size and length != self._Size: return
            #Each element can be either a formID or UINT32, so they have to be set separately
            #Resize the list
            _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 0, c_long(length))
            for x, value in enumerate(nValue):
                #Borrowing ArraySize to flag if the new value is a formID
                IsFormID = isinstance(value, tuple)
                _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, instance._ListIndex, self._ListFieldID, x, 1, 0, 0, byref(c_ulong(MakeShortFid(instance._CollectionID, value))), IsFormID)

class CBashFLOAT32_LIST(object):
    def __init__(self, ListFieldID):
        self._ListFieldID = ListFieldID
    def __get__(self, instance, owner):
        _CGetField.restype = POINTER(c_float)
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 0)
        if(retValue): return round(retValue.contents.value,6)
        return None
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0)
        else: _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, byref(c_float(round(nValue,6))), 0)

class CBashSTRING_LIST(object):
    def __init__(self, ListFieldID):
        self._ListFieldID = ListFieldID
    def __get__(self, instance, owner):
        _CGetField.restype = c_char_p
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 0)
        if(retValue): return retValue
        return None
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0)
        else: _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, str(nValue), 0)

class CBashISTRING_LIST(object):
    def __init__(self, ListFieldID):
        self._ListFieldID = ListFieldID
    def __get__(self, instance, owner):
        _CGetField.restype = c_char_p
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 0)
        if(retValue): return ISTRING(retValue)
        return None
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0)
        else: _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, str(nValue), 0)

# ListX2 Descriptors
class CBashLIST_LISTX2(object):
    def __init__(self, ListX2FieldID, Type, AsList=False):
        self._ListX2FieldID = ListX2FieldID
        self._Type = Type
        self._AsList = AsList
    def __get__(self, instance, owner):
        numElements = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, 1)
        oElements = [self._Type(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, x) for x in range(0, numElements)]
        if(self._AsList): return ExtractCopyList(oElements)
        return oElements
    def __set__(self, instance, nElements):
        if nElements is None or not len(nElements):
            _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0)
        else:
            length = len(nElements)
            if isinstance(nElements[0], tuple): nValues = nElements
            else: nValues = ExtractCopyList(nElements)
            ##Resizes the list
            _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, 0, c_long(length))
            numElements = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, 1)
            oElements = [self._Type(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, x) for x in range(0, numElements)]
            SetCopyList(oElements, nValues)

class CBashGeneric_LISTX2(object):
    def __init__(self, ListX2FieldID, Type):
        self._ListX2FieldID = ListX2FieldID
        self._Type = Type
        self._ResType = POINTER(Type)
    def __get__(self, instance, owner):
        _CGetField.restype = self._ResType
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, 0)
        if(retValue): return retValue.contents.value
        return None
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0)
        else: _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, byref(self._Type(nValue)), 0)

class CBashFLOAT32_LISTX2(object):
    def __init__(self, ListX2FieldID):
        self._ListX2FieldID = ListX2FieldID
    def __get__(self, instance, owner):
        _CGetField.restype = POINTER(c_float)
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, 0)
        if(retValue): return round(retValue.contents.value,6)
        return None
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0)
        else: _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, byref(c_float(round(nValue,6))), 0)

class CBashUINT8ARRAY_LISTX2(object):
    def __init__(self, ListX2FieldID, Size=None):
        self._ListX2FieldID = ListX2FieldID
        self._Size = Size
    def __get__(self, instance, owner):
        numRecords = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, 1)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        return []
    def __set__(self, instance, nValue):
        if nValue is None or not len(nValue): _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0)
        else:
            length = len(nValue)
            if self._Size and length != self._Size: return
            cRecords = (c_ubyte * length)(*nValue)
            _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, byref(cRecords), length)

class CBashFORMID_OR_UINT32_ARRAY_LISTX2(object):
    def __init__(self, ListX2FieldID, Size=None):
        self._ListX2FieldID = ListX2FieldID
        self._Size = Size
    def __get__(self, instance, owner):
        values = []
        numRecords = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, 1)
        if(numRecords > 0):
            cRecords = (c_ulong * numRecords)()
            _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, byref(cRecords))
            for x in range(numRecords):
                type = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, x, 1, 2)
                if type == API_FIELDS.UINT32:
                    values.append(cRecords[x])
                elif type == API_FIELDS.FORMID:
                    values.append(MakeLongFid(instance._CollectionID, instance._ModID, cRecords[x]))
        return values
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0)
        else:
            length = len(nValue)
            if self._Size and length != self._Size: return
            #Each element can be either a formID or UINT32, so they have to be set separately
            #Resize the list
            _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, 0, c_long(length))
            for x, value in enumerate(nValue):
                #Borrowing ArraySize to flag if the new value is a formID
                IsFormID = isinstance(value, tuple)
                _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, x, 1, byref(c_ulong(MakeShortFid(instance._CollectionID, value))), IsFormID)

class CBashFORMID_LISTX2(object):
    def __init__(self, ListX2FieldID):
        self._ListX2FieldID = ListX2FieldID
    def __get__(self, instance, owner):
        _CGetField.restype = POINTER(c_ulong)
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, 0)
        if(retValue): return MakeLongFid(instance._CollectionID, instance._ModID, retValue.contents.value)
        return None
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0)
        else: _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, byref(c_ulong(MakeShortFid(instance._CollectionID, nValue))), 0)

class CBashFORMID_OR_FLOAT32_LISTX2(object):
    def __init__(self, ListX2FieldID):
        self._ListX2FieldID = ListX2FieldID
    def __get__(self, instance, owner):
        type = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, 2)
        if type == API_FIELDS.FLOAT32:
            _CGetField.restype = POINTER(c_float)
            retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, 0)
            if(retValue): return round(retValue.contents.value,6)
        else:
            _CGetField.restype = POINTER(c_ulong)
            retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, 0)
            if(retValue): return MakeLongFid(instance._CollectionID, instance._ModID, retValue.contents.value)
        return None
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0)
        else:
            type = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, 2)
            if type == API_FIELDS.FLOAT32:
                try:
                    value = float(nValue)
                except TypeError:
                    return
                _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, byref(c_float(round(value,6))), 0)
            else:
                try:
                    value = MakeShortFid(instance._CollectionID, nValue)
                except TypeError:
                    return
                _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, byref(c_ulong(value)), 0)

class CBashSTRING_LISTX2(object):
    def __init__(self, ListX2FieldID):
        self._ListX2FieldID = ListX2FieldID
    def __get__(self, instance, owner):
        _CGetField.restype = c_char_p
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, 0)
        if(retValue): return retValue
        return None
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0)
        else: _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, str(nValue), 0)

class CBashISTRING_LISTX2(object):
    def __init__(self, ListX2FieldID):
        self._ListX2FieldID = ListX2FieldID
    def __get__(self, instance, owner):
        _CGetField.restype = c_char_p
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, 0)
        if(retValue): return ISTRING(retValue)
        return None
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0)
        else: _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, str(nValue), 0)

class CBashUNKNOWN_OR_FORMID_OR_UINT32_LISTX2(object):
    def __init__(self, ListX2FieldID):
        self._ListX2FieldID = ListX2FieldID
    def __get__(self, instance, owner):
        type = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, 2)
        if type != API_FIELDS.UNKNOWN:
            _CGetField.restype = POINTER(c_long)
            retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, 0)
            if(retValue):
                if type == API_FIELDS.UINT32:
                    return retValue.contents.value
                elif type == API_FIELDS.FORMID:
                    return MakeLongFid(instance._CollectionID, instance._ModID, retValue.contents.value)
        return None
    def __set__(self, instance, nValue):
        type = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, 2)
        if type != API_FIELDS.UNKNOWN:
            if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0)
            else:
                _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, byref(c_ulong(MakeShortFid(instance._CollectionID, nValue))), 0)

# ListX3 Descriptors
class CBashGeneric_LISTX3(object):
    def __init__(self, ListX3FieldID, Type):
        self._ListX3FieldID = ListX3FieldID
        self._Type = Type
        self._ResType = POINTER(Type)
    def __get__(self, instance, owner):
        _CGetField.restype = self._ResType
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, instance._ListX2FieldID, instance._ListX3Index, self._ListX3FieldID, 0)
        if(retValue): return retValue.contents.value
        return None
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, instance._ListX2FieldID, instance._ListX3Index, self._ListX3FieldID)
        else: _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, instance._ListX2FieldID, instance._ListX3Index, self._ListX3FieldID, byref(self._Type(nValue)), 0)

class CBashUINT8ARRAY_LISTX3(object):
    def __init__(self, ListX3FieldID, Size=None):
        self._ListX3FieldID = ListX3FieldID
        self._Size = Size
    def __get__(self, instance, owner):
        numRecords = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, instance._ListX2FieldID, instance._ListX3Index, self._ListX3FieldID, 1)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, instance._ListX2FieldID, instance._ListX3Index, self._ListX3FieldID, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        return []
    def __set__(self, instance, nValue):
        if nValue is None or not len(nValue): _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, instance._ListX2FieldID, instance._ListX3Index, self._ListX3FieldID)
        else:
            length = len(nValue)
            if self._Size and length != self._Size: return
            cRecords = (c_ubyte * length)(*nValue)
            _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, instance._ListX2FieldID, instance._ListX3Index, self._ListX3FieldID, byref(cRecords), length)

class CBashFLOAT32_LISTX3(object):
    def __init__(self, ListX3FieldID):
        self._ListX3FieldID = ListX3FieldID
    def __get__(self, instance, owner):
        _CGetField.restype = POINTER(c_float)
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, instance._ListX2FieldID, instance._ListX3Index, self._ListX3FieldID, 0)
        if(retValue): return round(retValue.contents.value,6)
        return None
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, instance._ListX2FieldID, instance._ListX3Index, self._ListX3FieldID)
        else: _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, instance._ListX2FieldID, instance._ListX3Index, self._ListX3FieldID, byref(c_float(round(nValue,6))), 0)

class CBashUNKNOWN_OR_FORMID_OR_UINT32_LISTX3(object):
    def __init__(self, ListX3FieldID):
        self._ListX3FieldID = ListX3FieldID
    def __get__(self, instance, owner):
        type = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, instance._ListX2FieldID, instance._ListX3Index, self._ListX3FieldID, 2)
        if type != API_FIELDS.UNKNOWN:
            _CGetField.restype = POINTER(c_long)
            retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, instance._ListX2FieldID, instance._ListX3Index, self._ListX3FieldID, 0)
            if(retValue):
                if type == API_FIELDS.UINT32:
                    return retValue.contents.value
                elif type == API_FIELDS.FORMID:
                    return MakeLongFid(instance._CollectionID, instance._ModID, retValue.contents.value)
        return None
    def __set__(self, instance, nValue):
        type = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, instance._ListX2FieldID, instance._ListX3Index, self._ListX3FieldID, 2)
        if type != API_FIELDS.UNKNOWN:
            if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, instance._ListX2FieldID, instance._ListX3Index, self._ListX3FieldID)
            else:
                _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, instance._ListX2FieldID, instance._ListX3Index, self._ListX3FieldID, byref(c_ulong(MakeShortFid(instance._CollectionID, nValue))), 0)

#Record accessors
#--Accessor Components
class BaseComponent(object):
    def __init__(self, CollectionIndex, ModID, RecordID, FieldID):
        self._CollectionID = CollectionIndex
        self._ModID = ModID
        self._RecordID = RecordID
        self._FieldID = FieldID

class ListComponent(object):
    def __init__(self, CollectionIndex, ModID, RecordID, FieldID, ListIndex):
        self._CollectionID = CollectionIndex
        self._ModID = ModID
        self._RecordID = RecordID
        self._FieldID = FieldID
        self._ListIndex = ListIndex

class ListX2Component(object):
    def __init__(self, CollectionIndex, ModID, RecordID, FieldID, ListIndex, ListFieldID, ListX2Index):
        self._CollectionID = CollectionIndex
        self._ModID = ModID
        self._RecordID = RecordID
        self._FieldID = FieldID
        self._ListIndex = ListIndex
        self._ListFieldID = ListFieldID
        self._ListX2Index = ListX2Index

class ListX3Component(object):
    def __init__(self, CollectionIndex, ModID, RecordID, FieldID, ListIndex, ListFieldID, ListX2Index, ListX2FieldID, ListX3Index):
        self._CollectionID = CollectionIndex
        self._ModID = ModID
        self._RecordID = RecordID
        self._FieldID = FieldID
        self._ListIndex = ListIndex
        self._ListFieldID = ListFieldID
        self._ListX2Index = ListX2Index
        self._ListX2FieldID = ListX2FieldID
        self._ListX3Index = ListX3Index

class Model(BaseComponent):
    modPath = CBashISTRING_GROUP(0)
    modb = CBashFLOAT32_GROUP(1)
    modt_p = CBashUINT8ARRAY_GROUP(2)
    copyattrs = ['modPath', 'modb', 'modt_p']
    exportattrs = ['modPath', 'modb']#, 'modt_p']

class Item(ListComponent):
    item = CBashFORMID_LIST(1)
    count = CBashGeneric_LIST(2, c_long)
    exportattrs = copyattrs = ['item', 'count']

class FNVItem(ListComponent):
    item = CBashFORMID_LIST(1)
    count = CBashGeneric_LIST(2, c_long)
    owner = CBashFORMID_LIST(3)
    globalOrRank = CBashUNKNOWN_OR_FORMID_OR_UINT32_LIST(4)
    condition = CBashFLOAT32_LIST(5)
    exportattrs = copyattrs = ['item', 'count', 'owner',
                               'globalOrRank', 'condition']

class Condition(ListComponent):
    operType = CBashGeneric_LIST(1, c_ubyte)
    unused1 = CBashUINT8ARRAY_LIST(2, 3)
    compValue = CBashFLOAT32_LIST(3)
    ifunc = CBashGeneric_LIST(4, c_ulong)
    param1 = CBashUNKNOWN_OR_FORMID_OR_UINT32_LIST(5)
    param2 = CBashUNKNOWN_OR_FORMID_OR_UINT32_LIST(6)
    unused2 = CBashUINT8ARRAY_LIST(7, 4)
    IsEqual = CBashMaskedType('operType', 0xF0, 0x00, 'IsNotEqual')
    IsNotEqual = CBashMaskedType('operType', 0xF0, 0x20, 'IsEqual')
    IsGreater = CBashMaskedType('operType', 0xF0, 0x40, 'IsEqual')
    IsGreaterOrEqual = CBashMaskedType('operType', 0xF0, 0x60, 'IsEqual')
    IsLess = CBashMaskedType('operType', 0xF0, 0x80, 'IsEqual')
    IsLessOrEqual = CBashMaskedType('operType', 0xF0, 0xA0, 'IsEqual')
    IsOr = CBashBasicFlag('operType', 0x01)
    IsRunOnTarget = CBashBasicFlag('operType', 0x02)
    IsUseGlobal = CBashBasicFlag('operType', 0x04)
    exportattrs = copyattrs = ['operType', 'compValue', 'ifunc', 'param1', 'param2']

class FNVCondition(ListComponent):
    operType = CBashGeneric_LIST(1, c_ubyte)
    unused1 = CBashUINT8ARRAY_LIST(2, 3)
    compValue = CBashFLOAT32_LIST(3)
    ifunc = CBashGeneric_LIST(4, c_ulong)
    param1 = CBashUNKNOWN_OR_FORMID_OR_UINT32_LIST(5)
    param2 = CBashUNKNOWN_OR_FORMID_OR_UINT32_LIST(6)
    runOn = CBashGeneric_LIST(7, c_ulong)
    reference = CBashUNKNOWN_OR_FORMID_OR_UINT32_LIST(8)
    IsEqual = CBashMaskedType('operType', 0xF0, 0x00, 'IsNotEqual')
    IsNotEqual = CBashMaskedType('operType', 0xF0, 0x20, 'IsEqual')
    IsGreater = CBashMaskedType('operType', 0xF0, 0x40, 'IsEqual')
    IsGreaterOrEqual = CBashMaskedType('operType', 0xF0, 0x60, 'IsEqual')
    IsLess = CBashMaskedType('operType', 0xF0, 0x80, 'IsEqual')
    IsLessOrEqual = CBashMaskedType('operType', 0xF0, 0xA0, 'IsEqual')
    IsOr = CBashBasicFlag('operType', 0x01)
    IsRunOnTarget = CBashBasicFlag('operType', 0x02)
    IsUseGlobal = CBashBasicFlag('operType', 0x04)
    IsResultOnSubject = CBashBasicType('runOn', 0, 'IsResultOnTarget')
    IsResultOnTarget = CBashBasicType('runOn', 1, 'IsResultOnSubject')
    IsResultOnReference = CBashBasicType('runOn', 2, 'IsResultOnSubject')
    IsResultOnCombatTarget = CBashBasicType('runOn', 3, 'IsResultOnSubject')
    IsResultOnLinkedReference = CBashBasicType('runOn', 4, 'IsResultOnSubject')
    exportattrs = copyattrs = ['operType', 'compValue', 'ifunc', 'param1',
                               'param2', 'runOn', 'reference']

class FNVConditionX2(ListX2Component):
    operType = CBashGeneric_LISTX2(1, c_ubyte)
    unused1 = CBashUINT8ARRAY_LISTX2(2, 3)
    compValue = CBashFORMID_OR_FLOAT32_LISTX2(3)
    ifunc = CBashGeneric_LISTX2(4, c_ulong)
    param1 = CBashUNKNOWN_OR_FORMID_OR_UINT32_LISTX2(5)
    param2 = CBashUNKNOWN_OR_FORMID_OR_UINT32_LISTX2(6)
    runOn = CBashGeneric_LISTX2(7, c_ulong)
    reference = CBashUNKNOWN_OR_FORMID_OR_UINT32_LISTX2(8)
    IsEqual = CBashMaskedType('operType', 0xF0, 0x00, 'IsNotEqual')
    IsNotEqual = CBashMaskedType('operType', 0xF0, 0x20, 'IsEqual')
    IsGreater = CBashMaskedType('operType', 0xF0, 0x40, 'IsEqual')
    IsGreaterOrEqual = CBashMaskedType('operType', 0xF0, 0x60, 'IsEqual')
    IsLess = CBashMaskedType('operType', 0xF0, 0x80, 'IsEqual')
    IsLessOrEqual = CBashMaskedType('operType', 0xF0, 0xA0, 'IsEqual')
    IsOr = CBashBasicFlag('operType', 0x01)
    IsRunOnTarget = CBashBasicFlag('operType', 0x02)
    IsUseGlobal = CBashBasicFlag('operType', 0x04)
    IsResultOnSubject = CBashBasicType('runOn', 0, 'IsResultOnTarget')
    IsResultOnTarget = CBashBasicType('runOn', 1, 'IsResultOnSubject')
    IsResultOnReference = CBashBasicType('runOn', 2, 'IsResultOnSubject')
    IsResultOnCombatTarget = CBashBasicType('runOn', 3, 'IsResultOnSubject')
    IsResultOnLinkedReference = CBashBasicType('runOn', 4, 'IsResultOnSubject')
    exportattrs = copyattrs = ['operType', 'compValue', 'ifunc', 'param1',
                               'param2', 'runOn', 'reference']

class Effect(ListComponent):
    ##name0 and name are both are always the same value, so setting one will set both. They're basically aliases
    name0 = CBashMGEFCODE_OR_UINT32_LIST(1)
    name = CBashMGEFCODE_OR_UINT32_LIST(2)
    magnitude = CBashGeneric_LIST(3, c_ulong)
    area = CBashGeneric_LIST(4, c_ulong)
    duration = CBashGeneric_LIST(5, c_ulong)
    rangeType = CBashGeneric_LIST(6, c_ulong)
    actorValue = CBashFORMID_OR_MGEFCODE_OR_ACTORVALUE_OR_UINT32_LIST(7) #OBME
    script = CBashFORMID_OR_MGEFCODE_OR_ACTORVALUE_OR_UINT32_LIST(8) #OBME
    school = CBashGeneric_LIST(9, c_ulong)
    visual = CBashMGEFCODE_OR_UINT32_LIST(10) #OBME
    flags = CBashGeneric_LIST(11, c_ubyte)
    unused1 = CBashUINT8ARRAY_LIST(12, 3)
    full = CBashSTRING_LIST(13) #OBME
    ##OBME Fields. Setting any of the below fields will make the mod require JRoush's OBME plugin for OBSE
    ##To see if OBME is in use, check the recordVersion field for a non-None value
    recordVersion = CBashGeneric_LIST(14, c_ubyte) #OBME
    betaVersion = CBashGeneric_LIST(15, c_ubyte) #OBME
    minorVersion = CBashGeneric_LIST(16, c_ubyte) #OBME
    majorVersion = CBashGeneric_LIST(17, c_ubyte) #OBME
    efitParamInfo = CBashGeneric_LIST(18, c_ubyte) #OBME
    efixParamInfo = CBashGeneric_LIST(19, c_ubyte) #OBME
    reserved1 = CBashUINT8ARRAY_LIST(20, 0xA) #OBME
    iconPath = CBashISTRING_LIST(21) #OBME
    ##If efixOverrides ever equals 0, the EFIX chunk will become unloaded
    ##This includes the fields: efixOverrides,  efixFlags, baseCost, resistAV, reserved2
    efixOverrides = CBashGeneric_LIST(22, c_ulong) #OBME
    efixFlags = CBashGeneric_LIST(23, c_ulong) #OBME
    baseCost = CBashFLOAT32_LIST(24) #OBME
    resistAV = CBashACTORVALUE_LIST(25) #OBME
    reserved2 = CBashUINT8ARRAY_LIST(26, 0x10) #OBME
    IsHostile = CBashBasicFlag('flags', 0x01)
    IsSelf = CBashBasicType('rangeType', 0, 'IsTouch')
    IsTouch = CBashBasicType('rangeType', 1, 'IsSelf')
    IsTarget = CBashBasicType('rangeType', 2, 'IsSelf')
    ##OBME Fields. Setting any of the below fields will make the mod require JRoush's OBME plugin for OBSE
    ##To see if OBME is in use, check the recordVersion field for a non-None value
    IsUsingHostileOverride = CBashBasicFlag('efixOverrides', 0x00000001) #OBME
    IsUsingRecoversOverride = CBashBasicFlag('efixOverrides', 0x00000002) #OBME
    IsUsingParamFlagAOverride = CBashBasicFlag('efixOverrides', 0x00000004) #OBME
    IsUsingBeneficialOverride = CBashBasicFlag('efixOverrides', 0x00000008) #OBME
    IsUsingEFIXParamOverride = CBashBasicFlag('efixOverrides', 0x00000010) #OBME
    IsUsingSchoolOverride = CBashBasicFlag('efixOverrides', 0x00000020) #OBME
    IsUsingNameOverride = CBashBasicFlag('efixOverrides', 0x00000040) #OBME
    IsUsingVFXCodeOverride = CBashBasicFlag('efixOverrides', 0x00000080) #OBME
    IsUsingBaseCostOverride = CBashBasicFlag('efixOverrides', 0x00000100) #OBME
    IsUsingResistAVOverride = CBashBasicFlag('efixOverrides', 0x00000200) #OBME
    IsUsingFXPersistsOverride = CBashBasicFlag('efixOverrides', 0x00000400) #OBME
    IsUsingIconOverride = CBashBasicFlag('efixOverrides', 0x00000800) #OBME
    IsUsingDoesntTeachOverride = CBashBasicFlag('efixOverrides', 0x00001000) #OBME
    IsUsingUnknownFOverride = CBashBasicFlag('efixOverrides', 0x00004000) #OBME
    IsUsingNoRecastOverride = CBashBasicFlag('efixOverrides', 0x00008000) #OBME
    IsUsingParamFlagBOverride = CBashBasicFlag('efixOverrides', 0x00010000) #OBME
    IsUsingMagnitudeIsRangeOverride = CBashBasicFlag('efixOverrides', 0x00020000) #OBME
    IsUsingAtomicResistanceOverride = CBashBasicFlag('efixOverrides', 0x00040000) #OBME
    IsUsingParamFlagCOverride = CBashBasicFlag('efixOverrides', 0x00080000) #OBME
    IsUsingParamFlagDOverride = CBashBasicFlag('efixOverrides', 0x00100000) #OBME
    IsUsingDisabledOverride = CBashBasicFlag('efixOverrides', 0x00400000) #OBME
    IsUsingUnknownOOverride = CBashBasicFlag('efixOverrides', 0x00800000) #OBME
    IsUsingNoHitEffectOverride = CBashBasicFlag('efixOverrides', 0x08000000) #OBME
    IsUsingPersistOnDeathOverride = CBashBasicFlag('efixOverrides', 0x10000000) #OBME
    IsUsingExplodesWithForceOverride = CBashBasicFlag('efixOverrides', 0x20000000) #OBME
    IsUsingHiddenOverride = CBashBasicFlag('efixOverrides', 0x40000000) #OBME
    ##The related efixOverrides flag must be set for the following to be used
    IsHostileOverride = CBashBasicFlag('efixFlags', 0x00000001) #OBME
    IsRecoversOverride = CBashBasicFlag('efixFlags', 0x00000002) #OBME
    IsParamFlagAOverride = CBashBasicFlag('efixFlags', 0x00000004) #OBME
    IsBeneficialOverride = CBashBasicFlag('efixFlags', 0x00000008) #OBME
    IsFXPersistsOverride = CBashBasicFlag('efixFlags', 0x00000400) #OBME
    IsUnknownFOverride = CBashBasicFlag('efixFlags', 0x00004000) #OBME
    IsNoRecastOverride = CBashBasicFlag('efixFlags', 0x00008000) #OBME
    IsParamFlagBOverride = CBashBasicFlag('efixFlags', 0x00010000) #OBME
    IsMagnitudeIsRangeOverride = CBashBasicFlag('efixFlags', 0x00020000) #OBME
    IsAtomicResistanceOverride = CBashBasicFlag('efixFlags', 0x00040000) #OBME
    IsParamFlagCOverride = CBashBasicFlag('efixFlags', 0x00080000) #OBME
    IsParamFlagDOverride = CBashBasicFlag('efixFlags', 0x00100000) #OBME
    IsDisabledOverride = CBashBasicFlag('efixFlags', 0x00400000) #OBME
    IsUnknownOOverride = CBashBasicFlag('efixFlags', 0x00800000) #OBME
    IsNoHitEffectOverride = CBashBasicFlag('efixFlags', 0x08000000) #OBME
    IsPersistOnDeathOverride = CBashBasicFlag('efixFlags', 0x10000000) #OBME
    IsExplodesWithForceOverride = CBashBasicFlag('efixFlags', 0x20000000) #OBME
    IsHiddenOverride = CBashBasicFlag('efixFlags', 0x40000000) #OBME
    exportattrs = copyattrs = ['name', 'magnitude', 'area', 'duration', 'rangeType',
                 'actorValue', 'script', 'school', 'visual', 'IsHostile',
                 'full']
    copyattrsOBME = copyattrs + ['recordVersion', 'betaVersion',
                                 'minorVersion', 'majorVersion',
                                 'efitParamInfo', 'efixParamInfo',
                                 'reserved1', 'iconPath', 'efixOverrides',
                                 'efixFlags', 'baseCost', 'resistAV',
                                 'reserved2']
    
class FNVEffect(ListComponent):
    effect = CBashFORMID_LIST(1)
    magnitude = CBashGeneric_LIST(2, c_ulong)
    area = CBashGeneric_LIST(3, c_ulong)
    duration = CBashGeneric_LIST(4, c_ulong)
    rangeType = CBashGeneric_LIST(5, c_ulong)
    actorValue = CBashGeneric_LIST(6, c_long)
    
    def create_condition(self):
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, self._FieldID, self._ListIndex, 7, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, self._FieldID, self._ListIndex, 7, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return FNVConditionX2(self._CollectionID, self._ModID, self._RecordID, self._FieldID, self._ListIndex, 7, length)
    conditions = CBashLIST_LIST(7, FNVConditionX2)
    conditions_list = CBashLIST_LIST(7, FNVConditionX2, True)

    
    IsSelf = CBashBasicType('rangeType', 0, 'IsTouch')
    IsTouch = CBashBasicType('rangeType', 1, 'IsSelf')
    IsTarget = CBashBasicType('rangeType', 2, 'IsSelf')
    exportattrs = copyattrs = ['effect', 'magnitude', 'area', 'duration',
                               'rangeType', 'actorValue', 'conditions_list']

class Faction(ListComponent):
    faction = CBashFORMID_LIST(1)
    rank = CBashGeneric_LIST(2, c_ubyte)
    unused1 = CBashUINT8ARRAY_LIST(3, 3)
    exportattrs = copyattrs = ['faction', 'rank']

class Relation(ListComponent):
    faction = CBashFORMID_LIST(1)
    mod = CBashGeneric_LIST(2, c_long)
    exportattrs = copyattrs = ['faction', 'mod']
    
class FNVRelation(ListComponent):
    faction = CBashFORMID_LIST(1)
    mod = CBashGeneric_LIST(2, c_long)
    groupReactionType = CBashGeneric_LIST(3, c_ulong)
    
    IsNeutral = CBashBasicType('groupReactionType', 0, 'IsEnemy')
    IsEnemy = CBashBasicType('groupReactionType', 1, 'IsNeutral')
    IsAlly = CBashBasicType('groupReactionType', 2, 'IsNeutral')
    IsFriend = CBashBasicType('groupReactionType', 3, 'IsNeutral')
    exportattrs = copyattrs = ['faction', 'mod', 'groupReactionType']

class FNVAltTexture(ListComponent):
    name = CBashSTRING_LIST(1)
    texture = CBashFORMID_LIST(2)
    index = CBashGeneric_LIST(3, c_long)
    exportattrs = copyattrs = ['name', 'texture', 'index']

class FNVDestructable(BaseComponent):
    class Stage(ListComponent):
        health = CBashGeneric_LIST(1, c_ubyte)
        index = CBashGeneric_LIST(2, c_ubyte)
        stage = CBashGeneric_LIST(3, c_ubyte)
        flags = CBashGeneric_LIST(4, c_ubyte)
        dps = CBashGeneric_LIST(5, c_long)
        explosion = CBashFORMID_LIST(6)
        debris = CBashFORMID_LIST(7)
        debrisCount = CBashGeneric_LIST(8, c_long)
        modPath = CBashISTRING_LIST(9)
        modt_p = CBashUINT8ARRAY_LIST(10)
        
        IsCapDamage = CBashBasicFlag('flags', 0x01)
        IsDisable = CBashBasicFlag('flags', 0x02)
        IsDestroy = CBashBasicFlag('flags', 0x04)
        exportattrs = copyattrs = ['health', 'index', 'stage',
                                   'flags', 'dps', 'explosion',
                                   'debris', 'debrisCount',
                                   'modPath', 'modt_p']

    health = CBashGeneric_GROUP(0, c_long)
    count = CBashGeneric_GROUP(1, c_ubyte)
    flags = CBashGeneric_GROUP(2, c_ubyte)
    unused1 = CBashUINT8ARRAY_GROUP(3, 2)

    def create_stage(self):
        FieldID = self._FieldID + 4
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, FieldID, 0, 0, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, FieldID, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return Stage(self._CollectionID, self._ModID, self._RecordID, FieldID, length)
    stages = CBashLIST_GROUP(4, Stage)
    stages_list = CBashLIST_GROUP(4, Stage, True)
    IsVATSTargetable = CBashBasicFlag('flags', 0x01)
    exportattrs = copyattrs = ['health', 'count', 'flags', 'stages_list']


class PGRP(ListComponent):
    x = CBashFLOAT32_LIST(1)
    y = CBashFLOAT32_LIST(2)
    z = CBashFLOAT32_LIST(3)
    connections = CBashGeneric_LIST(4, c_ubyte)
    unused1 = CBashUINT8ARRAY_LIST(5, 3)
    exportattrs = copyattrs = ['x', 'y', 'z', 'connections']

#--Accessors
#--Fallout New Vegas
class FnvBaseRecord(object):
    _Type = 'BASE'
    def __init__(self, CollectionIndex, ModID, RecordID, ParentID=0, CopyFlags=0):
        self._CollectionID = CollectionIndex
        self._ModID = ModID
        self._RecordID = RecordID
        self._CopyFlags = CopyFlags
        #ParentID isn't kept for most records

    def __eq__(self, other):
        if type(other) is type(self):
            return self._RecordID == other._RecordID
        return False

    def __ne__(self, other):
        return not self.__eq__(other)

    @property
    def FileName(self):
        return _CGetFileNameByID(self._CollectionID, self._ModID) or 'Missing'

    @property
    def ModName(self):
        return _CGetModNameByID(self._CollectionID, self._ModID) or 'Missing'

    @property
    def GName(self):
        return GPath(self.ModName)

    def UnloadRecord(self):
        _CUnloadRecord(self._CollectionID, self._ModID, self._RecordID)

    def DeleteRecord(self):
        _CDeleteRecord(self._CollectionID, self._ModID, self._RecordID, getattr(self, '_ParentID', 0))

    def GetNumReferences(self, FormIDToMatch):
        FormIDToMatch = MakeShortFid(self._CollectionID, FormIDToMatch)
        if FormIDToMatch is None: return 0
        return _CGetNumReferences(self._CollectionID, self._ModID, self._RecordID, FormIDToMatch)

    def UpdateReferences(self, FormIDToReplace, ReplacementFormID):
        FormIDToReplace = MakeShortFid(self._CollectionID, FormIDToReplace)
        ReplacementFormID = MakeShortFid(self._CollectionID, ReplacementFormID)
        if not (FormIDToReplace or ReplacementFormID): return 0
        return _CUpdateReferences(self._CollectionID, self._ModID, self._RecordID, FormIDToReplace, ReplacementFormID)

    def History(self):
        cModIDs = (c_ulong * 257)() #just allocate enough for the max number + size
        cRecordIDs = (c_ulong * 257)() #just allocate enough for the max number + size
        numRecords = _CGetRecordHistory(self._CollectionID, self._ModID, self._RecordID, byref(cModIDs), byref(cRecordIDs))
        parent = getattr(self, '_ParentID', 0)
        return [self.__class__(self._CollectionID, cModIDs[x], cRecordIDs[x], parent, self._CopyFlags) for x in range(0, numRecords)]

    def IsWinning(self, GetExtendedConflicts=False):
        """Returns true if the record is the last to load.
           If GetExtendedConflicts is True, scanned records will be considered.
           More efficient than running Conflicts() and checking the first value."""
        return _CIsRecordWinning(self._CollectionID, self._ModID, self._RecordID, c_ulong(GetExtendedConflicts))

    def Conflicts(self, GetExtendedConflicts=False):
        numRecords = _CGetNumRecordConflicts(self._CollectionID, self._RecordID, c_ulong(GetExtendedConflicts)) #gives upper bound
        if(numRecords > 1):
            cModIDs = (c_ulong * numRecords)()
            cRecordIDs = (c_ulong * numRecords)()
            numRecords = _CGetRecordConflicts(self._CollectionID, self._RecordID, byref(cModIDs), byref(cRecordIDs), c_ulong(GetExtendedConflicts))
            parent = getattr(self, '_ParentID', 0)
            return [self.__class__(self._CollectionID, cModIDs[x], cRecordIDs[x], parent, self._CopyFlags) for x in range(0, numRecords)]
        return []

    def ConflictDetails(self, attrs=None, GetExtendedConflicts=False):
        conflicting = {}
        if attrs is None:
            attrs = self.copyattrs
        if not attrs:
            return conflicting
        #recordMasters = set(ObModFile(self._CollectionID, self._ModID).TES4.masters)
        #sort oldest to newest rather than newest to oldest
        #conflicts = self.Conflicts(GetExtendedConflicts)
        #Less pythonic, but optimized for better speed.
        #Equivalent to commented out code.
        #parentRecords = [parent for parent in conflicts if parent.ModName in recordMasters]
        #parentRecords.reverse()
        parentRecords = self.History()
        if parentRecords:
            conflicting.update([(attr,reduce(getattr, attr.split('.'), self)) for parentRecord in parentRecords for attr in attrs if reduce(getattr, attr.split('.'), self) != reduce(getattr, attr.split('.'), parentRecord)])
        else: #is the first instance of the record
            conflicting.update([(attr,reduce(getattr, attr.split('.'), self)) for attr in attrs])
##        if parentRecords:
##            for parentRecord in parentRecords:
##                for attr in attrs:
##                    if getattr_deep(self,attr) != getattr_deep(parentRecord,attr):
##                        conflicting[attr] = getattr_deep(self,attr)
##        else:
##            for attr in attrs:
##                conflicting[attr] = getattr_deep(self,attr)
        return conflicting

    def mergeFilter(self,modSet):
        """This method is called by the bashed patch mod merger. The intention is
        to allow a record to be filtered according to the specified modSet. E.g.
        for a list record, items coming from mods not in the modSet could be
        removed from the list."""
        pass

    def CopyAsOverride(self, target, CopyFlags=None):
        if CopyFlags is None: CopyFlags = self._CopyFlags
        targetID = 0
        if hasattr(self, '_ParentID'):
            if isinstance(target, ObModFile): targetID = self._ParentID
            else: targetID = target._RecordID
        ##Record Creation Flags
        ##SetAsOverride       = 0x00000001,
        ##SetAsWorldCell      = 0x00000002,
        ##CopyWorldCellStatus = 0x00000004
        #Set SetAsOverride
        CopyFlags |= 0x00000001
        RecordID = _CCopyRecord(self._CollectionID, self._ModID, self._RecordID, target._ModID, targetID, 0, 0, c_ulong(CopyFlags))
        #Clear SetAsOverride
        CopyFlags &= ~0x00000001
        if(RecordID): return self.__class__(self._CollectionID, target._ModID, RecordID, getattr(self, '_ParentID', 0), CopyFlags)
        return None

    def CopyAsNew(self, target, RecordFormID=0, CopyFlags=None):
        if CopyFlags is None: CopyFlags = self._CopyFlags
        targetID = 0
        if hasattr(self, '_ParentID'):
            if isinstance(target, ObModFile): targetID = self._ParentID
            else: targetID = target._RecordID
        ##Record Creation Flags
        ##SetAsOverride       = 0x00000001,
        ##SetAsWorldCell      = 0x00000002,
        ##CopyWorldCellStatus = 0x00000004
        #Clear SetAsOverride in case it was set
        CopyFlags &= ~0x00000001
        RecordID = _CCopyRecord(self._CollectionID, self._ModID, self._RecordID, target._ModID, targetID, RecordFormID, 0, c_ulong(CopyFlags))
        if(RecordID): return self.__class__(self._CollectionID, target._ModID, RecordID, getattr(self, '_ParentID', 0), CopyFlags)
        return None

    @property
    def Parent(self):
        ParentID = getattr(self, '_ParentID', 0)
        if ParentID:
            testRecord = ObBaseRecord(self._CollectionID, self._ModID, ParentID, 0, 0)
            RecordType = type_record[testRecord.recType]
            if RecordType:
                return RecordType(self._CollectionID, self._ModID, ParentID, 0, 0)
        return None

    @property
    def recType(self):
        _CGetFieldAttribute.restype = (c_char * 4)
        retValue = _CGetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 0, 0, 0, 0, 0, 0, 0, 0)
        _CGetFieldAttribute.restype = c_ulong
        if(retValue and retValue.value != ''): return retValue.value
        return None

    flags1 = CBashGeneric(1, c_ulong)

    def get_fid(self):
        _CGetField.restype = POINTER(c_ulong)
        retValue = _CGetField(self._CollectionID, self._ModID, self._RecordID, 2, 0, 0, 0, 0, 0, 0, 0)
        if(retValue): return MakeLongFid(self._CollectionID, self._ModID, retValue.contents.value)
        return None
    def set_fid(self, nValue):
        if nValue is None: nValue = 0
        else: nValue = MakeShortFid(self._CollectionID, nValue)
        _CSetRecordIdentifiers(self._CollectionID, self._ModID, self._RecordID, nValue, self.eid or 0)
    fid = property(get_fid, set_fid)

    versionControl1 = CBashUINT8ARRAY(3, 4)
    formVersion = CBashGeneric(5, c_ushort)
    versionControl2 = CBashUINT8ARRAY(6, 2)

    def get_eid(self):
        _CGetField.restype = c_char_p
        retValue = _CGetField(self._CollectionID, self._ModID, self._RecordID, 4, 0, 0, 0, 0, 0, 0, 0)
        if(retValue): return ISTRING(retValue)
        return None
    def set_eid(self, nValue):
        if nValue is None or not len(nValue): nValue = 0
        else: nValue = str(nValue)
        _CSetRecordIdentifiers(self._CollectionID, self._ModID, self._RecordID, MakeShortFid(self._CollectionID, self.fid or 0), nValue)
    eid = property(get_eid, set_eid)

    IsDeleted = CBashBasicFlag('flags1', 0x00000020)
    IsHasTreeLOD = CBashBasicFlag('flags1', 0x00000040)
    IsConstant = CBashAlias('IsHasTreeLOD')
    IsHiddenFromLocalMap = CBashAlias('IsHasTreeLOD')
    IsTurnOffFire = CBashBasicFlag('flags1', 0x00000080)
    IsInaccessible = CBashBasicFlag('flags1', 0x00000100)
    IsOnLocalMap = CBashBasicFlag('flags1', 0x00000200)
    IsMotionBlur = CBashAlias('IsOnLocalMap')
    IsPersistent = CBashBasicFlag('flags1', 0x00000400)
    IsQuest = CBashAlias('IsPersistent')
    IsQuestOrPersistent = CBashAlias('IsPersistent')
    IsInitiallyDisabled = CBashBasicFlag('flags1', 0x00000800)
    IsIgnored = CBashBasicFlag('flags1', 0x00001000)
    IsNoVoiceFilter = CBashBasicFlag('flags1', 0x00002000)
    IsVoiceFilter = CBashInvertedFlag('IsNoVoiceFilter')
    IsVisibleWhenDistant = CBashBasicFlag('flags1', 0x00008000)
    IsVWD = CBashAlias('IsVisibleWhenDistant')
    IsRandomAnimStartOrHighPriorityLOD = CBashBasicFlag('flags1', 0x00010000)
    IsRandomAnimStart = CBashAlias('IsRandomAnimStartOrHighPriorityLOD')
    IsHighPriorityLOD = CBashAlias('IsRandomAnimStartOrHighPriorityLOD')
    IsTalkingActivator = CBashBasicFlag('flags1', 0x00020000)
    IsCompressed = CBashBasicFlag('flags1', 0x00040000)
    IsPlatformSpecificTexture = CBashBasicFlag('flags1', 0x00080000)
    IsObstacleOrNoAIAcquire = CBashBasicFlag('flags1', 0x02000000)
    IsObstacle = CBashAlias('IsObstacleOrNoAIAcquire')
    IsNoAIAcquire = CBashAlias('IsObstacleOrNoAIAcquire')
    IsNavMeshFilter = CBashBasicFlag('flags1', 0x04000000)
    IsNavMeshBoundBox = CBashBasicFlag('flags1', 0x08000000)
    IsNonPipboyOrAutoReflected = CBashBasicFlag('flags1', 0x10000000)
    IsNonPipboy = CBashAlias('IsNonPipboyOrAutoReflected')
    IsAutoReflected = CBashAlias('IsNonPipboyOrAutoReflected')
    IsPipboy = CBashInvertedFlag('IsNonPipboyOrAutoReflected')
    IsChildUsableOrAutoRefracted = CBashBasicFlag('flags1', 0x20000000)
    IsChildUsable = CBashAlias('IsChildUsableOrAutoRefracted')
    IsAutoRefracted = CBashAlias('IsChildUsableOrAutoRefracted')
    IsNavMeshGround = CBashBasicFlag('flags1', 0x40000000)
    baseattrs = ['flags1', 'versionControl1', 'formVersion', 'versionControl2', 'eid']

class FnvTES4Record(object):
    _Type = 'TES4'
    def __init__(self, CollectionIndex, ModID, RecordID, ParentID=0, CopyFlags=0):
        self._CollectionID = CollectionIndex
        self._ModID = ModID
        self._RecordID = RecordID

    def UnloadRecord(self):
        pass

    @property
    def recType(self):
        return self._Type

    flags1 = CBashGeneric(1, c_ulong)
    versionControl1 = CBashUINT8ARRAY(3, 4)
    formVersion = CBashGeneric(14, c_ushort)
    versionControl2 = CBashUINT8ARRAY(15, 2)
    version = CBashFLOAT32(5)
    numRecords = CBashGeneric(6, c_ulong)
    nextObject = CBashGeneric(7, c_ulong)
    ofst_p = CBashUINT8ARRAY(8)
    dele_p = CBashUINT8ARRAY(9)
    author = CBashSTRING(10)
    description = CBashSTRING(11)
    masters = CBashISTRINGARRAY(12)
    DATA = CBashJunk(13)
    overrides = CBashFORMIDARRAY(16)
    screenshot_p = CBashUINT8ARRAY(17)
    
    IsESM = CBashBasicFlag('flags1', 0x00000001)
    exportattrs = copyattrs = ['flags1', 'versionControl1', 'formVersion', 'versionControl2', 'version', 'numRecords', 'nextObject',
                 'author', 'description', 'masters', 'overrides', 'screenshot_p']
    
class FnvGMSTRecord(FnvBaseRecord):
    _Type = 'GMST'
    def get_value(self):
        rFormat = _CGetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 7, 0, 0, 0, 0, 0, 0, 2)
        if(rFormat == API_FIELDS.UNKNOWN):
            return None
        elif(rFormat == API_FIELDS.SINT32):
            _CGetField.restype = POINTER(c_long)
            retValue = _CGetField(self._CollectionID, self._ModID, self._RecordID, 7, 0, 0, 0, 0, 0, 0, 0)
            if(retValue): return retValue.contents.value
        elif(rFormat == API_FIELDS.FLOAT32):
            _CGetField.restype = POINTER(c_float)
            retValue = _CGetField(self._CollectionID, self._ModID, self._RecordID, 7, 0, 0, 0, 0, 0, 0, 0)
            if(retValue): return round(retValue.contents.value,6)
        elif(rFormat == API_FIELDS.STRING):
            _CGetField.restype = c_char_p
            return _CGetField(self._CollectionID, self._ModID, self._RecordID, 7, 0, 0, 0, 0, 0, 0, 0)
        return None
    def set_value(self, nValue):
        if nValue is None: _CDeleteField(self._CollectionID, self._ModID, self._RecordID, 7, 0, 0, 0, 0, 0, 0)
        else:
            rFormat = _CGetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 7, 0, 0, 0, 0, 0, 0, 2)
            if(rFormat == API_FIELDS.SINT32 and type(nValue) is int):
                _CSetField(self._CollectionID, self._ModID, self._RecordID, 7, 0, 0, 0, 0, 0, 0, byref(c_long(nValue)), 0)
            elif(rFormat == API_FIELDS.FLOAT32 == 10 and type(nValue) is float):
                _CSetField(self._CollectionID, self._ModID, self._RecordID, 7, 0, 0, 0, 0, 0, 0, byref(c_float(round(nValue,6))), 0)
            elif(rFormat == API_FIELDS.STRING and type(nValue) is str):
                _CSetField(self._CollectionID, self._ModID, self._RecordID, 7, 0, 0, 0, 0, 0, 0, nValue, 0)
    value = property(get_value, set_value)
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + ['value']
    
class FnvTXSTRecord(FnvBaseRecord):
    _Type = 'TXST'
    boundX1 = CBashGeneric(7, c_short)
    boundY1 = CBashGeneric(8, c_short)
    boundZ1 = CBashGeneric(9, c_short)
    boundX2 = CBashGeneric(10, c_short)
    boundY2 = CBashGeneric(11, c_short)
    boundZ2 = CBashGeneric(12, c_short)
    baseImageOrTransparencyPath = CBashISTRING(13)
    normalMapOrSpecularPath = CBashISTRING(14)
    envMapMaskOrUnkPath = CBashISTRING(15)
    glowMapOrUnusedPath = CBashISTRING(16)
    parallaxMapOrUnusedPath = CBashISTRING(17)
    envMapOrUnusedPath = CBashISTRING(18)
    decalMinWidth = CBashFLOAT32(19)
    decalMaxWidth = CBashFLOAT32(20)
    decalMinHeight = CBashFLOAT32(21)
    decalMaxHeight = CBashFLOAT32(22)
    decalDepth = CBashFLOAT32(23)
    decalShininess = CBashFLOAT32(24)
    decalScale = CBashFLOAT32(25)
    decalPasses = CBashGeneric(26, c_ubyte)
    decalFlags = CBashGeneric(27, c_ubyte)
    decalUnused1 = CBashUINT8ARRAY(28, 2)
    decalRed = CBashGeneric(29, c_ubyte)
    decalGreen = CBashGeneric(30, c_ubyte)
    decalBlue = CBashGeneric(31, c_ubyte)
    decalUnused2 = CBashUINT8ARRAY(32, 1)
    flags = CBashGeneric(33, c_ushort)

    IsNoSpecularMap = CBashBasicFlag('flags', 0x00000001)
    IsSpecularMap = CBashInvertedFlag('IsNoSpecularMap')

    IsObjectParallax = CBashBasicFlag('decalFlags', 0x00000001)
    IsObjectAlphaBlending = CBashBasicFlag('decalFlags', 0x00000002)
    IsObjectAlphaTesting = CBashBasicFlag('decalFlags', 0x00000004)
    copyattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                           'boundX2', 'boundY2', 'boundZ2', 'baseImageOrTransparencyPath',
                                           'normalMapOrSpecularPath', 'envMapMaskOrUnkPath', 'glowMapOrUnusedPath',
                                           'parallaxMapOrUnusedPath', 'envMapOrUnusedPath', 'decalMinWidth',
                                           'decalMaxWidth', 'decalMinHeight', 'decalMaxHeight',
                                           'decalDepth', 'decalShininess', 'decalScale',
                                           'decalPasses', 'decalFlags', 'decalUnused1',
                                           'decalRed', 'decalGreen', 'decalBlue',
                                           'decalUnused2', 'flags']
    
    exportattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                             'boundX2', 'boundY2', 'boundZ2', 'baseImageOrTransparencyPath',
                                             'normalMapOrSpecularPath', 'envMapMaskOrUnkPath', 'glowMapOrUnusedPath',
                                             'parallaxMapOrUnusedPath', 'envMapOrUnusedPath', 'decalMinWidth',
                                             'decalMaxWidth', 'decalMinHeight', 'decalMaxHeight',
                                             'decalDepth', 'decalShininess', 'decalScale',
                                             'decalPasses', 'decalFlags',
                                             'decalRed', 'decalGreen', 'decalBlue',
                                             'flags'] # 'decalUnused1','decalUnused2', 
class FnvMICNRecord(FnvBaseRecord):
    _Type = 'MICN'
    iconPath = CBashISTRING(7)
    smallIconPath = CBashISTRING(8)
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + ['iconPath', 'smallIconPath']

class FnvGLOBRecord(FnvBaseRecord):
    _Type = 'GLOB'
    format = CBashGeneric(7, c_char)
    value = CBashFLOAT32(8)
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + ['format', 'value']

class FnvCLASRecord(FnvBaseRecord):
    _Type = 'CLAS'
    full = CBashSTRING(7)
    description = CBashSTRING(8)
    iconPath = CBashISTRING(9)
    smallIconPath = CBashISTRING(10)
    tagSkills1 = CBashGeneric(11, c_long)
    tagSkills2 = CBashGeneric(12, c_long)
    tagSkills3 = CBashGeneric(13, c_long)
    tagSkills4 = CBashGeneric(14, c_long)
    flags = CBashGeneric(15, c_ulong)
    services = CBashGeneric(16, c_ulong)
    trainSkill = CBashGeneric(17, c_byte)
    trainLevel = CBashGeneric(18, c_ubyte)
    unused1 = CBashUINT8ARRAY(19, 2)
    strength = CBashGeneric(20, c_ubyte)
    perception = CBashGeneric(21, c_ubyte)
    endurance = CBashGeneric(22, c_ubyte)
    charisma = CBashGeneric(23, c_ubyte)
    intelligence = CBashGeneric(24, c_ubyte)
    agility = CBashGeneric(25, c_ubyte)
    luck = CBashGeneric(26, c_ubyte)
    
    IsPlayable = CBashBasicFlag('flags', 0x00000001)
    IsGuard = CBashBasicFlag('flags', 0x00000002)
    
    IsServicesWeapons = CBashBasicFlag('services', 0x00000001)
    IsServicesArmor = CBashBasicFlag('services', 0x00000002)
    IsServicesClothing = CBashBasicFlag('services', 0x00000004)
    IsServicesBooks = CBashBasicFlag('services', 0x00000008)
    IsServicesFood = CBashBasicFlag('services', 0x00000010)
    IsServicesChems = CBashBasicFlag('services', 0x00000020)
    IsServicesStimpacks = CBashBasicFlag('services', 0x00000040)
    IsServicesLights = CBashBasicFlag('services', 0x00000080)
    IsServicesMiscItems = CBashBasicFlag('services', 0x00000400)
    IsServicesPotions = CBashBasicFlag('services', 0x00002000)
    IsServicesTraining = CBashBasicFlag('services', 0x00004000)
    IsServicesRecharge = CBashBasicFlag('services', 0x00010000)
    IsServicesRepair = CBashBasicFlag('services', 0x00020000)    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + ['full', 'description', 'iconPath', 'smallIconPath',
                                                         'tagSkills1', 'tagSkills2', 'tagSkills3',
                                                         'tagSkills4', 'flags', 'services',
                                                         'trainSkill', 'trainLevel', 'strength',
                                                         'perception', 'endurance', 'charisma',
                                                         'intelligence', 'agility', 'luck']

class FnvFACTRecord(FnvBaseRecord):
    _Type = 'FACT'
    class Rank(ListComponent):
        rank = CBashGeneric_LIST(1, c_long)
        male = CBashSTRING_LIST(2)
        female = CBashSTRING_LIST(3)
        insigniaPath = CBashISTRING_LIST(4)
        exportattrs = copyattrs = ['rank', 'male', 'female', 'insigniaPath']

    full = CBashSTRING(7)

    def create_relation(self):
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 8, 0, 0, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, 8, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return FNVRelation(self._CollectionID, self._ModID, self._RecordID, 8, length)
    relations = CBashLIST(8, FNVRelation)
    relations_list = CBashLIST(8, FNVRelation, True)

    flags = CBashGeneric(9, c_ushort)
    unused1 = CBashUINT8ARRAY(10, 2)
    crimeGoldMultiplier = CBashFLOAT32(11)

    def create_rank(self):
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 12, 0, 0, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, 12, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return self.Rank(self._CollectionID, self._ModID, self._RecordID, 12, length)
    ranks = CBashLIST(12, Rank)
    ranks_list = CBashLIST(12, Rank, True)

    reputation = CBashFORMID(13)
    
    IsHiddenFromPC = CBashBasicFlag('flags', 0x0001)
    IsEvil = CBashBasicFlag('flags', 0x0002)
    IsSpecialCombat = CBashBasicFlag('flags', 0x0004)
    IsTrackCrime = CBashBasicFlag('flags', 0x0100)
    IsAllowSell = CBashBasicFlag('flags', 0x0200)
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + ['full', 'relations_list', 'flags',
                                        'crimeGoldMultiplier', 'ranks_list', 'reputation']

class FnvHDPTRecord(FnvBaseRecord):
    _Type = 'HDPT'
    full = CBashSTRING(7)
    modPath = CBashISTRING(8)
    modb = CBashFLOAT32(9)
    modt_p = CBashUINT8ARRAY(10)
    
    def create_altTexture(self):
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 11, 0, 0, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, 11, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return FNVAltTexture(self._CollectionID, self._ModID, self._RecordID, 11, length)
    altTextures = CBashLIST(11, FNVAltTexture)
    altTextures_list = CBashLIST(11, FNVAltTexture, True)

    modelFlags = CBashGeneric(12, c_ubyte)
    flags = CBashGeneric(13, c_ubyte)
    parts = CBashFORMIDARRAY(14)
    
    IsPlayable = CBashBasicFlag('flags', 0x01)
    
    IsHead = CBashBasicFlag('modelFlags', 0x01)
    IsTorso = CBashBasicFlag('modelFlags', 0x02)
    IsRightHand = CBashBasicFlag('modelFlags', 0x04)
    IsLeftHand = CBashBasicFlag('modelFlags', 0x08)
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + ['full', 'modPath', 'modb',
                                                         'modt_p', 'altTextures_list',
                                                         'modelFlags', 'flags', 'parts']

class FnvHAIRRecord(FnvBaseRecord):
    _Type = 'HAIR'
    full = CBashSTRING(7)
    modPath = CBashISTRING(8)
    modb = CBashFLOAT32(9)
    modt_p = CBashUINT8ARRAY(10)
    
    def create_altTexture(self):
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 11, 0, 0, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, 11, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return FNVAltTexture(self._CollectionID, self._ModID, self._RecordID, 11, length)
    altTextures = CBashLIST(11, FNVAltTexture)
    altTextures_list = CBashLIST(11, FNVAltTexture, True)

    modelFlags = CBashGeneric(12, c_ubyte)
    iconPath = CBashISTRING(13)
    flags = CBashGeneric(14, c_ubyte)
    
    IsPlayable = CBashBasicFlag('flags', 0x01)
    IsNotMale = CBashBasicFlag('flags', 0x02)
    IsMale = CBashInvertedFlag('IsNotMale')
    IsNotFemale = CBashBasicFlag('flags', 0x04)
    IsFemale = CBashInvertedFlag('IsNotFemale')
    IsFixedColor = CBashBasicFlag('flags', 0x08)
    
    IsHead = CBashBasicFlag('modelFlags', 0x01)
    IsTorso = CBashBasicFlag('modelFlags', 0x02)
    IsRightHand = CBashBasicFlag('modelFlags', 0x04)
    IsLeftHand = CBashBasicFlag('modelFlags', 0x08)
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + ['full', 'modPath', 'modb',
                                                         'modt_p', 'altTextures_list',
                                                         'modelFlags', 'iconPath', 'flags']
    
class FnvEYESRecord(FnvBaseRecord):
    _Type = 'EYES'
    full = CBashSTRING(7)
    iconPath = CBashISTRING(8)
    flags = CBashGeneric(9, c_ubyte)
    
    IsPlayable = CBashBasicFlag('flags', 0x01)
    IsNotMale = CBashBasicFlag('flags', 0x02)
    IsMale = CBashInvertedFlag('IsNotMale')
    IsNotFemale = CBashBasicFlag('flags', 0x04)
    IsFemale = CBashInvertedFlag('IsNotFemale')
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + ['full', 'iconPath', 'flags']
    
class FnvRACERecord(FnvBaseRecord):
    _Type = 'RACE'
    class RaceModel(BaseComponent):
        modPath = CBashISTRING_GROUP(0)
        modb = CBashFLOAT32_GROUP(1)
        modt_p = CBashUINT8ARRAY_GROUP(2)
        
        def create_altTexture(self):
            FieldID = self._FieldID + 3
            length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, FieldID, 0, 0, 0, 0, 0, 0, 1)
            CBash.SetField(self._CollectionID, self._ModID, self._RecordID, FieldID, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
            return FNVAltTexture(self._CollectionID, self._ModID, self._RecordID, FieldID, length)
        altTextures = CBashLIST_GROUP(3, FNVAltTexture)
        altTextures_list = CBashLIST_GROUP(3, FNVAltTexture, True)
        flags = CBashGeneric_GROUP(4, c_ubyte)
        iconPath = CBashISTRING_GROUP(5)
        smallIconPath = CBashISTRING_GROUP(6)
        
        IsHead = CBashBasicFlag('flags', 0x01)
        IsTorso = CBashBasicFlag('flags', 0x02)
        IsRightHand = CBashBasicFlag('flags', 0x04)
        IsLeftHand = CBashBasicFlag('flags', 0x08)
        copyattrs = ['modPath', 'modb', 'modt_p', 'altTextures_list',
                     'flags', 'iconPath', 'smallIconPath']
        exportattrs = ['modPath', 'modb', 'altTextures_list',
                     'flags', 'iconPath', 'smallIconPath']#, 'modt_p']

    full = CBashSTRING(7)
    description = CBashSTRING(8)
    
    def create_relation(self):
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 9, 0, 0, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, 9, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return FNVRelation(self._CollectionID, self._ModID, self._RecordID, 9, length)
    relations = CBashLIST(9, FNVRelation)
    relations_list = CBashLIST(9, FNVRelation, True)

    skill1 = CBashGeneric(10, c_byte)
    skill1Boost = CBashGeneric(11, c_byte)
    skill2 = CBashGeneric(12, c_byte)
    skill2Boost = CBashGeneric(13, c_byte)
    skill3 = CBashGeneric(14, c_byte)
    skill3Boost = CBashGeneric(15, c_byte)
    skill4 = CBashGeneric(16, c_byte)
    skill4Boost = CBashGeneric(17, c_byte)
    skill5 = CBashGeneric(18, c_byte)
    skill5Boost = CBashGeneric(19, c_byte)
    skill6 = CBashGeneric(20, c_byte)
    skill6Boost = CBashGeneric(21, c_byte)
    skill7 = CBashGeneric(22, c_byte)
    skill7Boost = CBashGeneric(23, c_byte)
    unused1 = CBashUINT8ARRAY(24, 2)
    maleHeight = CBashFLOAT32(25)
    femaleHeight = CBashFLOAT32(26)
    maleWeight = CBashFLOAT32(27)
    femaleWeight = CBashFLOAT32(28)
    flags = CBashGeneric(29, c_ulong)
    older = CBashFORMID(30)
    younger = CBashFORMID(31)
    maleVoice = CBashFORMID(32)
    femaleVoice = CBashFORMID(33)
    defaultHairMale = CBashFORMID(34)
    defaultHairFemale = CBashFORMID(35)
    defaultHairMaleColor = CBashGeneric(36, c_ubyte)
    defaultHairFemaleColor = CBashGeneric(37, c_ubyte)
    mainClamp = CBashFLOAT32(38)
    faceClamp = CBashFLOAT32(39)
    attr_p = CBashUINT8ARRAY(40)
    maleHead = CBashGrouped(41, RaceModel)
    maleHead_list = CBashGrouped(41, RaceModel, True)

    maleEars = CBashGrouped(48, RaceModel)
    maleEars_list = CBashGrouped(48, RaceModel, True)

    maleMouth = CBashGrouped(55, RaceModel)
    maleMouth_list = CBashGrouped(55, RaceModel, True)

    maleTeethLower = CBashGrouped(62, RaceModel)
    maleTeethLower_list = CBashGrouped(62, RaceModel, True)

    maleTeethUpper = CBashGrouped(69, RaceModel)
    maleTeethUpper_list = CBashGrouped(69, RaceModel, True)

    maleTongue = CBashGrouped(76, RaceModel)
    maleTongue_list = CBashGrouped(76, RaceModel, True)

    maleLeftEye = CBashGrouped(83, RaceModel)
    maleLeftEye_list = CBashGrouped(83, RaceModel, True)

    maleRightEye = CBashGrouped(90, RaceModel)
    maleRightEye_list = CBashGrouped(90, RaceModel, True)

    femaleHead = CBashGrouped(97, RaceModel)
    femaleHead_list = CBashGrouped(97, RaceModel, True)

    femaleEars = CBashGrouped(104, RaceModel)
    femaleEars_list = CBashGrouped(104, RaceModel, True)

    femaleMouth = CBashGrouped(111, RaceModel)
    femaleMouth_list = CBashGrouped(111, RaceModel, True)

    femaleTeethLower = CBashGrouped(118, RaceModel)
    femaleTeethLower_list = CBashGrouped(118, RaceModel, True)

    femaleTeethUpper = CBashGrouped(125, RaceModel)
    femaleTeethUpper_list = CBashGrouped(125, RaceModel, True)

    femaleTongue = CBashGrouped(132, RaceModel)
    femaleTongue_list = CBashGrouped(132, RaceModel, True)

    femaleLeftEye = CBashGrouped(139, RaceModel)
    femaleLeftEye_list = CBashGrouped(139, RaceModel, True)

    femaleRightEye = CBashGrouped(146, RaceModel)
    femaleRightEye_list = CBashGrouped(146, RaceModel, True)
    
    maleUpperBody = CBashGrouped(153, RaceModel)
    maleUpperBody_list = CBashGrouped(153, RaceModel, True)

    maleLeftHand = CBashGrouped(160, RaceModel)
    maleLeftHand_list = CBashGrouped(160, RaceModel, True)

    maleRightHand = CBashGrouped(167, RaceModel)
    maleRightHand_list = CBashGrouped(167, RaceModel, True)

    maleUpperBodyTexture = CBashGrouped(174, RaceModel)
    maleUpperBodyTexture_list = CBashGrouped(174, RaceModel, True)
    
    femaleUpperBody = CBashGrouped(181, RaceModel)
    femaleUpperBody_list = CBashGrouped(181, RaceModel, True)

    femaleLeftHand = CBashGrouped(188, RaceModel)
    femaleLeftHand_list = CBashGrouped(188, RaceModel, True)

    femaleRightHand = CBashGrouped(195, RaceModel)
    femaleRightHand_list = CBashGrouped(195, RaceModel, True)

    femaleUpperBodyTexture = CBashGrouped(202, RaceModel)
    femaleUpperBodyTexture_list = CBashGrouped(202, RaceModel, True)

    hairs = CBashFORMIDARRAY(209)
    eyes = CBashFORMIDARRAY(210)
    maleFggs_p = CBashUINT8ARRAY(211, 200)
    maleFgga_p = CBashUINT8ARRAY(212, 120)
    maleFgts_p = CBashUINT8ARRAY(213, 200)
    maleSnam_p = CBashUINT8ARRAY(214, 2)
    femaleFggs_p = CBashUINT8ARRAY(215, 200)
    femaleFgga_p = CBashUINT8ARRAY(216, 120)
    femaleFgts_p = CBashUINT8ARRAY(217, 200)
    femaleSnam_p = CBashUINT8ARRAY(218, 2)
    
    IsPlayable = CBashBasicFlag('flags', 0x00000001)
    IsChild = CBashBasicFlag('flags', 0x00000004)
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + ['full', 'description',
                                        'relations_list', 'skill1', 'skill1Boost',
                                        'skill2', 'skill2Boost', 'skill3',
                                        'skill3Boost', 'skill4', 'skill4Boost',
                                        'skill5', 'skill5Boost', 'skill6',
                                        'skill6Boost', 'skill7', 'skill7Boost',
                                        'maleHeight', 'femaleHeight',
                                        'maleWeight', 'femaleWeight', 'flags',
                                        'older', 'younger',
                                        'maleVoice', 'femaleVoice',
                                        'defaultHairMale', 'defaultHairFemale',
                                        'defaultHairMaleColor', 'defaultHairFemaleColor',
                                        'mainClamp', 'faceClamp', 'attr_p',
                                        'maleHead_list', 'maleEars_list',
                                        'maleMouth_list', 'maleTeethLower_list',
                                        'maleTeethUpper_list', 'maleTongue_list',
                                        'maleLeftEye_list', 'maleRightEye_list',                                           
                                        'femaleHead_list', 'femaleEars_list',
                                        'femaleMouth_list', 'femaleTeethLower_list',
                                        'femaleTeethUpper_list', 'femaleTongue_list',
                                        'femaleLeftEye_list', 'femaleRightEye_list',
                                        'maleUpperBody_list', 'maleLeftHand_list',
                                        'maleRightHand_list', 'maleUpperBodyTexture_list',
                                        'femaleUpperBody_list', 'femaleLeftHand_list',
                                        'femaleRightHand_list',
                                        'femaleUpperBodyTexture_list',
                                        'hairs', 'eyes',
                                        'maleFggs_p', 'maleFgga_p', 'maleFgts_p',
                                        'maleSnam_p',
                                        'femaleFggs_p', 'femaleFgga_p', 'femaleFgts_p',
                                        'femaleSnam_p']

class FnvSOUNRecord(FnvBaseRecord):
    _Type = 'SOUN'
    boundX1 = CBashGeneric(7, c_short)
    boundY1 = CBashGeneric(8, c_short)
    boundZ1 = CBashGeneric(9, c_short)
    boundX2 = CBashGeneric(10, c_short)
    boundY2 = CBashGeneric(11, c_short)
    boundZ2 = CBashGeneric(12, c_short)
    soundPath = CBashISTRING(13)
    chance = CBashGeneric(14, c_ubyte)
    minDistance = CBashGeneric(15, c_ubyte)
    maxDistance = CBashGeneric(16, c_ubyte)
    freqAdjustment = CBashGeneric(17, c_byte)
    unused1 = CBashUINT8ARRAY(18, 1)
    flags = CBashGeneric(19, c_ulong)
    staticAtten = CBashGeneric(20, c_short)
    stopTime = CBashGeneric(21, c_ubyte)
    startTime = CBashGeneric(22, c_ubyte)
    attenCurve = CBashSINT16ARRAY(23, 5)
    reverb = CBashGeneric(24, c_short)
    priority = CBashGeneric(25, c_long)
    x = CBashGeneric(26, c_long)
    y = CBashGeneric(27, c_long)
    
    IsRandomFrequencyShift = CBashBasicFlag('flags', 0x00000001)
    IsPlayAtRandom = CBashBasicFlag('flags', 0x00000002)
    IsEnvironmentIgnored = CBashBasicFlag('flags', 0x00000004)
    IsRandomLocation = CBashBasicFlag('flags', 0x00000008)
    IsLoop = CBashBasicFlag('flags', 0x00000010)
    IsMenuSound = CBashBasicFlag('flags', 0x00000020)
    Is2D = CBashBasicFlag('flags', 0x00000040)
    Is360LFE = CBashBasicFlag('flags', 0x00000080)
    IsDialogueSound = CBashBasicFlag('flags', 0x00000100)
    IsEnvelopeFast = CBashBasicFlag('flags', 0x00000200)
    IsEnvelopeSlow = CBashBasicFlag('flags', 0x00000400)
    Is2DRadius = CBashBasicFlag('flags', 0x00000800)
    IsMuteWhenSubmerged = CBashBasicFlag('flags', 0x00001000)    
    copyattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                           'boundX2', 'boundY2', 'boundZ2', 'soundPath',
                                           'chance', 'minDistance', 'maxDistance',
                                           'freqAdjustment', 'unused1', 'flags',
                                           'staticAtten', 'stopTime', 'startTime',
                                           'attenCurve', 'reverb', 'priority',
                                           'x', 'y']
    
    exportattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                           'boundX2', 'boundY2', 'boundZ2', 'soundPath',
                                           'chance', 'minDistance', 'maxDistance',
                                           'freqAdjustment', 'flags',
                                           'staticAtten', 'stopTime', 'startTime',
                                           'attenCurve', 'reverb', 'priority',
                                           'x', 'y'] # 'unused1', 

class FnvASPCRecord(FnvBaseRecord):
    _Type = 'ASPC'
    boundX1 = CBashGeneric(7, c_short)
    boundY1 = CBashGeneric(8, c_short)
    boundZ1 = CBashGeneric(9, c_short)
    boundX2 = CBashGeneric(10, c_short)
    boundY2 = CBashGeneric(11, c_short)
    boundZ2 = CBashGeneric(12, c_short)
    dawnOrDefaultLoop = CBashFORMID(13)
    afternoon = CBashFORMID(14)
    dusk = CBashFORMID(15)
    night = CBashFORMID(16)
    walla = CBashFORMID(17)
    wallaTriggerCount = CBashGeneric(18, c_ulong)
    regionSound = CBashFORMID(19)
    environmentType = CBashGeneric(20, c_ulong)
    spaceType = CBashGeneric(21, c_ulong)
    
    IsEnvironmentNone = CBashBasicType('environmentType', 0, 'IsEnvironmentDefault')
    IsEnvironmentDefault = CBashBasicType('environmentType', 1, 'IsEnvironmentNone')
    IsEnvironmentGeneric = CBashBasicType('environmentType', 2, 'IsEnvironmentNone')
    IsEnvironmentPaddedCell = CBashBasicType('environmentType', 3, 'IsEnvironmentNone')
    IsEnvironmentRoom = CBashBasicType('environmentType', 4, 'IsEnvironmentNone')
    IsEnvironmentBathroom = CBashBasicType('environmentType', 5, 'IsEnvironmentNone')
    IsEnvironmentLivingroom = CBashBasicType('environmentType', 6, 'IsEnvironmentNone')
    IsEnvironmentStoneRoom = CBashBasicType('environmentType', 7, 'IsEnvironmentNone')
    IsEnvironmentAuditorium = CBashBasicType('environmentType', 8, 'IsEnvironmentNone')
    IsEnvironmentConcerthall = CBashBasicType('environmentType', 9, 'IsEnvironmentNone')
    IsEnvironmentCave = CBashBasicType('environmentType', 10, 'IsEnvironmentNone')
    IsEnvironmentArena = CBashBasicType('environmentType', 11, 'IsEnvironmentNone')
    IsEnvironmentHangar = CBashBasicType('environmentType', 12, 'IsEnvironmentNone')
    IsEnvironmentCarpetedHallway = CBashBasicType('environmentType', 13, 'IsEnvironmentNone')
    IsEnvironmentHallway = CBashBasicType('environmentType', 14, 'IsEnvironmentNone')
    IsEnvironmentStoneCorridor = CBashBasicType('environmentType', 15, 'IsEnvironmentNone')
    IsEnvironmentAlley = CBashBasicType('environmentType', 16, 'IsEnvironmentNone')
    IsEnvironmentForest = CBashBasicType('environmentType', 17, 'IsEnvironmentNone')
    IsEnvironmentCity = CBashBasicType('environmentType', 18, 'IsEnvironmentNone')
    IsEnvironmentMountains = CBashBasicType('environmentType', 19, 'IsEnvironmentNone')
    IsEnvironmentQuarry = CBashBasicType('environmentType', 20, 'IsEnvironmentNone')
    IsEnvironmentPlain = CBashBasicType('environmentType', 21, 'IsEnvironmentNone')
    IsEnvironmentParkinglot = CBashBasicType('environmentType', 22, 'IsEnvironmentNone')
    IsEnvironmentSewerpipe = CBashBasicType('environmentType', 23, 'IsEnvironmentNone')
    IsEnvironmentUnderwater = CBashBasicType('environmentType', 24, 'IsEnvironmentNone')
    IsEnvironmentSmallRoom = CBashBasicType('environmentType', 25, 'IsEnvironmentNone')
    IsEnvironmentMediumRoom = CBashBasicType('environmentType', 26, 'IsEnvironmentNone')
    IsEnvironmentLargeRoom = CBashBasicType('environmentType', 27, 'IsEnvironmentNone')
    IsEnvironmentMediumHall = CBashBasicType('environmentType', 28, 'IsEnvironmentNone')
    IsEnvironmentLargeHall = CBashBasicType('environmentType', 29, 'IsEnvironmentNone')
    IsEnvironmentPlate = CBashBasicType('environmentType', 30, 'IsEnvironmentNone')
    
    IsSpaceExterior = CBashBasicType('spaceType', 0, 'IsSpaceInterior')
    IsSpaceInterior = CBashBasicType('spaceType', 1, 'IsSpaceExterior')
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                                         'boundX2', 'boundY2', 'boundZ2',
                                                         'dawnOrDefaultLoop', 'afternoon',
                                                         'dusk', 'night', 'walla',
                                                         'wallaTriggerCount', 'regionSound',
                                                         'environmentType', 'spaceType']

class FnvMGEFRecord(FnvBaseRecord):
    _Type = 'MGEF'
    full = CBashSTRING(7)
    description = CBashSTRING(8)
    iconPath = CBashISTRING(9)
    smallIconPath = CBashISTRING(10)
    modPath = CBashISTRING(11)
    modb = CBashFLOAT32(12)
    modt_p = CBashUINT8ARRAY(13)
    
    def create_altTexture(self):
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 14, 0, 0, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, 14, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return FNVAltTexture(self._CollectionID, self._ModID, self._RecordID, 14, length)
    altTextures = CBashLIST(14, FNVAltTexture)
    altTextures_list = CBashLIST(14, FNVAltTexture, True)

    modelFlags = CBashGeneric(15, c_ubyte)
    flags = CBashGeneric(16, c_ulong)
    baseCostUnused = CBashFLOAT32(17)
    associated = CBashFORMID(18)
    schoolUnused = CBashGeneric(19, c_long)
    resistType = CBashGeneric(20, c_long)
    numCounters = CBashGeneric(21, c_ushort)
    unused1 = CBashUINT8ARRAY(22, 2)
    light = CBashFORMID(23)
    projectileSpeed = CBashFLOAT32(24)
    effectShader = CBashFORMID(25)
    displayShader = CBashFORMID(26)
    effectSound = CBashFORMID(27)
    boltSound = CBashFORMID(28)
    hitSound = CBashFORMID(29)
    areaSound = CBashFORMID(30)
    cefEnchantmentUnused = CBashFLOAT32(31)
    cefBarterUnused = CBashFLOAT32(32)
    archType = CBashGeneric(33, c_ulong)
    actorValue = CBashGeneric(34, c_long)
    
    IsHostile = CBashBasicFlag('flags', 0x00000001)
    IsRecover = CBashBasicFlag('flags', 0x00000002)
    IsDetrimental = CBashBasicFlag('flags', 0x00000004)
    IsSelf = CBashBasicFlag('flags', 0x00000010)
    IsTouch = CBashBasicFlag('flags', 0x00000020)
    IsTarget = CBashBasicFlag('flags', 0x00000040)
    IsNoDuration = CBashBasicFlag('flags', 0x00000080)
    IsNoMagnitude = CBashBasicFlag('flags', 0x00000100)
    IsNoArea = CBashBasicFlag('flags', 0x00000200)
    IsFXPersist = CBashBasicFlag('flags', 0x00000400)
    IsGoryVisuals = CBashBasicFlag('flags', 0x00001000)
    IsDisplayNameOnly = CBashBasicFlag('flags', 0x00002000)
    IsRadioBroadcast = CBashBasicFlag('flags', 0x00008000)
    IsUseSkill = CBashBasicFlag('flags', 0x00080000)
    IsUseAttr = CBashBasicFlag('flags', 0x00100000)
    IsPainless = CBashBasicFlag('flags', 0x01000000)
    IsSprayType = CBashBasicFlag('flags', 0x02000000)
    IsBoltType = CBashBasicFlag('flags', 0x04000000)
    IsFogType = CBashBasicFlag('flags', 0x06000000)
    IsNoHitEffect = CBashBasicFlag('flags', 0x08000000)
    IsPersistOnDeath = CBashBasicFlag('flags', 0x10000000)
    IsUnknown1 = CBashBasicFlag('flags', 0x20000000)
    
    IsValueModifier = CBashBasicType('archType', 0, 'IsScript')
    IsScript = CBashBasicType('archType', 1, 'IsValueModifier')
    IsDispel = CBashBasicType('archType', 2, 'IsValueModifier')
    IsCureDisease = CBashBasicType('archType', 3, 'IsValueModifier')
    IsInvisibility = CBashBasicType('archType', 11, 'IsValueModifier')
    IsChameleon = CBashBasicType('archType', 12, 'IsValueModifier')
    IsLight = CBashBasicType('archType', 13, 'IsValueModifier')
    IsLock = CBashBasicType('archType', 16, 'IsValueModifier')
    IsOpen = CBashBasicType('archType', 17, 'IsValueModifier')
    IsBoundItem = CBashBasicType('archType', 18, 'IsValueModifier')
    IsSummonCreature = CBashBasicType('archType', 19, 'IsValueModifier')
    IsParalysis = CBashBasicType('archType', 24, 'IsValueModifier')
    IsCureParalysis = CBashBasicType('archType', 30, 'IsValueModifier')
    IsCureAddiction = CBashBasicType('archType', 31, 'IsValueModifier')
    IsCurePoison = CBashBasicType('archType', 32, 'IsValueModifier')
    IsConcussion = CBashBasicType('archType', 33, 'IsValueModifier')
    IsValueAndParts = CBashBasicType('archType', 34, 'IsValueModifier')
    IsLimbCondition = CBashBasicType('archType', 35, 'IsValueModifier')
    IsTurbo = CBashBasicType('archType', 36, 'IsValueModifier')
    copyattrs = FnvBaseRecord.baseattrs + ['full', 'description', 'iconPath', 'smallIconPath',
                                                         'modPath', 'modb', 'modt_p', 'altTextures_list',
                                                         'modelFlags', 'flags', 'baseCostUnused', 'associated',
                                                         'schoolUnused', 'resistType', 'numCounters', 'unused1',
                                                         'light', 'projectileSpeed', 'effectShader', 'displayShader',
                                                         'effectSound', 'boltSound', 'hitSound', 'areaSound',
                                                         'cefEnchantmentUnused', 'cefBarterUnused', 'archType', 'actorValue']
    exportattrs = FnvBaseRecord.baseattrs + ['full', 'description', 'iconPath', 'smallIconPath',
                                             'modPath', 'modb', 'altTextures_list',
                                             'modelFlags', 'flags', 'associated',
                                             'resistType', 'numCounters', 
                                             'light', 'projectileSpeed', 'effectShader', 'displayShader',
                                             'effectSound', 'boltSound', 'hitSound', 'areaSound',
                                             'archType', 'actorValue'] #'modt_p', 'baseCostUnused', 'schoolUnused', 'unused1', 'cefEnchantmentUnused', 'cefBarterUnused', 

class FnvSCPTRecord(FnvBaseRecord):
    _Type = 'SCPT'
    class Var(ListComponent):
        index = CBashGeneric_LIST(1, c_ulong)
        unused1 = CBashUINT8ARRAY_LIST(2, 12)
        flags = CBashGeneric_LIST(3, c_ubyte)
        unused2 = CBashUINT8ARRAY_LIST(4, 7)
        name = CBashISTRING_LIST(5)
        
        IsLongOrShort = CBashBasicFlag('flags', 0x00000001)
        exportattrs = copyattrs = ['index', 'flags', 'name']
        
    unused1 = CBashUINT8ARRAY(7, 4)
    numRefs = CBashGeneric(8, c_ulong)
    compiledSize = CBashGeneric(9, c_ulong)
    lastIndex = CBashGeneric(10, c_ulong)
    scriptType = CBashGeneric(11, c_ushort)
    scriptFlags = CBashGeneric(12, c_ushort)
    compiled_p = CBashUINT8ARRAY(13)
    scriptText = CBashISTRING(14)
    
    def create_var(self):
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 15, 0, 0, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, 15, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return self.Var(self._CollectionID, self._ModID, self._RecordID, 15, length)
    vars = CBashLIST(15, Var)
    vars_list = CBashLIST(15, Var, True)

    references = CBashFORMID_OR_UINT32_ARRAY(16)

    IsEnabled = CBashBasicFlag('scriptFlags', 0x0001)
    
    IsObject = CBashBasicType('scriptType', 0x0000, 'IsQuest')
    IsQuest = CBashBasicType('scriptType', 0x0001, 'IsObject')
    IsEffect = CBashBasicType('scriptType', 0x0100, 'IsObject')
    copyattrs = FnvBaseRecord.baseattrs + ['unused1', 'numRefs', 'compiledSize',
                                           'lastIndex', 'scriptType', 'flags',
                                           'compiled_p', 'scriptText',
                                           'vars_list', 'references']
    exportattrs = FnvBaseRecord.baseattrs + ['numRefs', 'compiledSize',
                                             'lastIndex', 'scriptType', 'flags',
                                             'scriptText',
                                             'vars_list', 'references'] #'unused1', 'compiled_p',

class FnvLTEXRecord(FnvBaseRecord):
    _Type = 'LTEX'
    iconPath = CBashISTRING(7)
    smallIconPath = CBashISTRING(8)
    texture = CBashFORMID(9)
    types = CBashGeneric(10, c_ubyte)
    friction = CBashGeneric(11, c_ubyte)
    restitution = CBashGeneric(12, c_ubyte)
    specularExponent = CBashGeneric(13, c_ubyte)
    grasses = CBashFORMIDARRAY(14)
    
    IsStone = CBashBasicType('types', 0, 'IsCloth')
    IsCloth = CBashBasicType('types', 1, 'IsStone')
    IsDirt = CBashBasicType('types', 2, 'IsStone')
    IsGlass = CBashBasicType('types', 3, 'IsStone')
    IsGrass = CBashBasicType('types', 4, 'IsStone')
    IsMetal = CBashBasicType('types', 5, 'IsStone')
    IsOrganic = CBashBasicType('types', 6, 'IsStone')
    IsSkin = CBashBasicType('types', 7, 'IsStone')
    IsWater = CBashBasicType('types', 8, 'IsStone')
    IsWood = CBashBasicType('types', 9, 'IsStone')
    IsHeavyStone = CBashBasicType('types', 10, 'IsStone')
    IsHeavyMetal = CBashBasicType('types', 11, 'IsStone')
    IsHeavyWood = CBashBasicType('types', 12, 'IsStone')
    IsChain = CBashBasicType('types', 13, 'IsStone')
    IsSnow = CBashBasicType('types', 14, 'IsStone')
    IsElevator = CBashBasicType('types', 15, 'IsStone')
    IsHollowMetal = CBashBasicType('types', 16, 'IsStone')
    IsSheetMetal = CBashBasicType('types', 17, 'IsStone')
    IsSand = CBashBasicType('types', 18, 'IsStone')
    IsBrokenConcrete = CBashBasicType('types', 19, 'IsStone')
    IsVehicleBody = CBashBasicType('types', 20, 'IsStone')
    IsVehiclePartSolid = CBashBasicType('types', 21, 'IsStone')
    IsVehiclePartHollow = CBashBasicType('types', 22, 'IsStone')
    IsBarrel = CBashBasicType('types', 23, 'IsStone')
    IsBottle = CBashBasicType('types', 24, 'IsStone')
    IsSodaCan = CBashBasicType('types', 25, 'IsStone')
    IsPistol = CBashBasicType('types', 26, 'IsStone')
    IsRifle = CBashBasicType('types', 27, 'IsStone')
    IsShoppingCart = CBashBasicType('types', 28, 'IsStone')
    IsLunchBox = CBashBasicType('types', 29, 'IsStone')
    IsBabyRattle = CBashBasicType('types', 30, 'IsStone')
    IsRubberBall = CBashBasicType('types', 31, 'IsStone')
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + ['iconPath', 'smallIconPath', 'texture',
                                                         'types', 'friction', 'restitution',
                                                         'specularExponent', 'grasses']

class FnvENCHRecord(FnvBaseRecord):
    _Type = 'ENCH'
    full = CBashSTRING(7)
    itemType = CBashGeneric(8, c_ulong)
    chargeAmountUnused = CBashGeneric(9, c_ulong)
    enchantCostUnused = CBashGeneric(10, c_ulong)
    flags = CBashGeneric(11, c_ubyte)
    unused1 = CBashUINT8ARRAY(12, 3)
    
    def create_effect(self):
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 13, 0, 0, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, 13, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return FNVEffect(self._CollectionID, self._ModID, self._RecordID, 13, length)
    effects = CBashLIST(13, FNVEffect)
    effects_list = CBashLIST(13, FNVEffect, True)

    
    IsNoAutoCalc = CBashBasicFlag('flags', 0x01)
    IsHideEffect = CBashBasicFlag('flags', 0x04)
    IsWeapon = CBashBasicType('itemType', 2, 'IsApparel')
    IsApparel = CBashBasicType('itemType', 3, 'IsWeapon')
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + ['full', 'itemType', 'chargeAmountUnused',
                                                         'enchantCostUnused', 'flags', 'effects_list']

class FnvSPELRecord(FnvBaseRecord):
    _Type = 'SPEL'
    full = CBashSTRING(7)
    spellType = CBashGeneric(8, c_ulong)
    costUnused = CBashGeneric(9, c_ulong)
    levelTypeUnused = CBashGeneric(10, c_ulong)
    flags = CBashGeneric(11, c_ubyte)
    unused1 = CBashUINT8ARRAY(12, 3)
    
    def create_effect(self):
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 13, 0, 0, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, 13, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return FNVEffect(self._CollectionID, self._ModID, self._RecordID, 13, length)
    effects = CBashLIST(13, FNVEffect)
    effects_list = CBashLIST(13, FNVEffect, True)

    
    IsManualCost = CBashBasicFlag('flags', 0x01)
    IsStartSpell = CBashBasicFlag('flags', 0x04)
    IsSilenceImmune = CBashBasicFlag('flags', 0x0A)
    IsAreaEffectIgnoresLOS = CBashBasicFlag('flags', 0x10)
    IsAEIgnoresLOS = CBashAlias('IsAreaEffectIgnoresLOS')
    IsScriptAlwaysApplies = CBashBasicFlag('flags', 0x20)
    IsDisallowAbsorbReflect = CBashBasicFlag('flags', 0x40)
    IsDisallowAbsorb = CBashAlias('IsDisallowAbsorbReflect')
    IsDisallowReflect = CBashAlias('IsDisallowAbsorbReflect')
    IsTouchExplodesWOTarget = CBashBasicFlag('flags', 0x80)
    IsTouchExplodes = CBashAlias('IsTouchExplodesWOTarget')

    IsActorEffect = CBashBasicType('spellType', 0, 'IsDisease')
    IsDisease = CBashBasicType('spellType', 1, 'IsActorEffect')
    IsPower = CBashBasicType('spellType', 2, 'IsActorEffect')
    IsLesserPower = CBashBasicType('spellType', 3, 'IsActorEffect')
    IsAbility = CBashBasicType('spellType', 4, 'IsActorEffect')
    IsPoison = CBashBasicType('spellType', 5, 'IsActorEffect')
    IsAddiction = CBashBasicType('spellType', 10, 'IsActorEffect')
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + ['full', 'spellType', 'costUnused',
                                                         'levelTypeUnused', 'flags', 'effects_list']

class FnvACTIRecord(FnvBaseRecord):
    _Type = 'ACTI'
    boundX1 = CBashGeneric(7, c_short)
    boundY1 = CBashGeneric(8, c_short)
    boundZ1 = CBashGeneric(9, c_short)
    boundX2 = CBashGeneric(10, c_short)
    boundY2 = CBashGeneric(11, c_short)
    boundZ2 = CBashGeneric(12, c_short)
    full = CBashSTRING(13)
    modPath = CBashISTRING(14)
    modb = CBashFLOAT32(15)
    modt_p = CBashUINT8ARRAY(16)
    
    def create_altTexture(self):
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 17, 0, 0, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, 17, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return FNVAltTexture(self._CollectionID, self._ModID, self._RecordID, 17, length)
    altTextures = CBashLIST(17, FNVAltTexture)
    altTextures_list = CBashLIST(17, FNVAltTexture, True)

    modelFlags = CBashGeneric(18, c_ubyte)
    script = CBashFORMID(19)
    destructable = CBashGrouped(20, FNVDestructable)
    destructable_list = CBashGrouped(20, FNVDestructable, True)

    loopSound = CBashFORMID(25)
    actSound = CBashFORMID(26)
    radioTemplate = CBashFORMID(27)
    radioStation = CBashFORMID(28)
    water = CBashFORMID(29)
    prompt = CBashSTRING(30)

    IsHead = CBashBasicFlag('modelFlags', 0x01)
    IsTorso = CBashBasicFlag('modelFlags', 0x02)
    IsRightHand = CBashBasicFlag('modelFlags', 0x04)
    IsLeftHand = CBashBasicFlag('modelFlags', 0x08)
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                                         'boundX2', 'boundY2', 'boundZ2',
                                                         'full', 'modPath', 'modb', 'modt_p',
                                                         'altTextures_list', 'modelFlags',
                                                         'script', 'destructable_list',
                                                         'loopSound', 'actSound',
                                                         'radioTemplate', 'radioStation',
                                                         'water', 'prompt']

class FnvTACTRecord(FnvBaseRecord):
    _Type = 'TACT'
    boundX1 = CBashGeneric(7, c_short)
    boundY1 = CBashGeneric(8, c_short)
    boundZ1 = CBashGeneric(9, c_short)
    boundX2 = CBashGeneric(10, c_short)
    boundY2 = CBashGeneric(11, c_short)
    boundZ2 = CBashGeneric(12, c_short)
    full = CBashSTRING(13)
    modPath = CBashISTRING(14)
    modb = CBashFLOAT32(15)
    modt_p = CBashUINT8ARRAY(16)
    
    def create_altTexture(self):
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 17, 0, 0, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, 17, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return FNVAltTexture(self._CollectionID, self._ModID, self._RecordID, 17, length)
    altTextures = CBashLIST(17, FNVAltTexture)
    altTextures_list = CBashLIST(17, FNVAltTexture, True)

    modelFlags = CBashGeneric(18, c_ubyte)
    script = CBashFORMID(19)
    destructable = CBashGrouped(20, FNVDestructable)
    destructable_list = CBashGrouped(20, FNVDestructable, True)

    loopSound = CBashFORMID(25)
    voice = CBashFORMID(26)
    radioTemplate = CBashFORMID(27)

    IsHead = CBashBasicFlag('modelFlags', 0x01)
    IsTorso = CBashBasicFlag('modelFlags', 0x02)
    IsRightHand = CBashBasicFlag('modelFlags', 0x04)
    IsLeftHand = CBashBasicFlag('modelFlags', 0x08)
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                                         'boundX2', 'boundY2', 'boundZ2',
                                                         'full', 'modPath', 'modb', 'modt_p',
                                                         'altTextures_list', 'modelFlags',
                                                         'script', 'destructable_list',
                                                         'loopSound', 'voice', 'radioTemplate']

class FnvTERMRecord(FnvBaseRecord):
    _Type = 'TERM'
    class Menu(ListComponent):
        class Var(ListX2Component):
            index = CBashGeneric_LISTX2(1, c_ulong)
            unused1 = CBashUINT8ARRAY_LISTX2(2, 12)
            flags = CBashGeneric_LISTX2(3, c_ubyte)
            unused2 = CBashUINT8ARRAY_LISTX2(4, 7)
            name = CBashISTRING_LISTX2(5)

            IsLongOrShort = CBashBasicFlag('flags', 0x00000001)
            exportattrs = copyattrs = ['index', 'flags', 'name']

        text = CBashSTRING_LIST(1)
        resultText = CBashSTRING_LIST(2)
        flags = CBashGeneric_LIST(3, c_ubyte)
        displayNote = CBashFORMID_LIST(4)
        subMenu = CBashFORMID_LIST(5)
        unused1 = CBashUINT8ARRAY_LIST(6, 4)
        numRefs = CBashGeneric_LIST(7, c_ulong)
        compiledSize = CBashGeneric_LIST(8, c_ulong)
        lastIndex = CBashGeneric_LIST(9, c_ulong)
        scriptType = CBashGeneric_LIST(10, c_ushort)
        scriptFlags = CBashGeneric_LIST(11, c_ushort)
        compiled_p = CBashUINT8ARRAY_LIST(12)
        scriptText = CBashISTRING_LIST(13)
        
        def create_var(self):
            length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, self._FieldID, self._ListIndex, 14, 0, 0, 0, 0, 1)
            CBash.SetField(self._CollectionID, self._ModID, self._RecordID, self._FieldID, self._ListIndex, 14, 0, 0, 0, 0, 0, c_ulong(length + 1))
            return self.Var(self._CollectionID, self._ModID, self._RecordID, self._FieldID, self._ListIndex, 14, length)
        vars = CBashLIST_LIST(14, Var)
        vars_list = CBashLIST_LIST(14, Var, True)

        
        references = CBashFORMID_OR_UINT32_ARRAY_LIST(15)
        def create_condition(self):
            length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, self._FieldID, self._ListIndex, 16, 0, 0, 0, 0, 1)
            CBash.SetField(self._CollectionID, self._ModID, self._RecordID, self._FieldID, self._ListIndex, 16, 0, 0, 0, 0, 0, c_ulong(length + 1))
            return FNVConditionX2(self._CollectionID, self._ModID, self._RecordID, self._FieldID, self._ListIndex, 16, length)
        conditions = CBashLIST_LIST(16, FNVConditionX2)
        conditions_list = CBashLIST_LIST(16, FNVConditionX2, True)

        
        IsAddNote = CBashBasicFlag('flags', 0x01)
        IsForceRedraw = CBashBasicFlag('flags', 0x02)

        IsEnabled = CBashBasicFlag('scriptFlags', 0x0001)

        IsObject = CBashBasicType('scriptType', 0x0000, 'IsQuest')
        IsQuest = CBashBasicType('scriptType', 0x0001, 'IsObject')
        IsEffect = CBashBasicType('scriptType', 0x0100, 'IsObject')
        copyattrs = ['text', 'resultText', 'flags',
                     'displayNote', 'subMenu', 'numRefs',
                     'compiledSize', 'lastIndex',
                     'scriptType', 'flags', 'compiled_p',
                     'scriptText', 'vars_list',
                     'references', 'conditions_list',]
        exportattrs = ['text', 'resultText', 'flags',
                       'displayNote', 'subMenu', 'numRefs',
                       'compiledSize', 'lastIndex',
                       'scriptType', 'flags',
                       'scriptText', 'vars_list',
                       'references', 'conditions_list',] # 'compiled_p',
        
    boundX1 = CBashGeneric(7, c_short)
    boundY1 = CBashGeneric(8, c_short)
    boundZ1 = CBashGeneric(9, c_short)
    boundX2 = CBashGeneric(10, c_short)
    boundY2 = CBashGeneric(11, c_short)
    boundZ2 = CBashGeneric(12, c_short)
    full = CBashSTRING(13)
    modPath = CBashISTRING(14)
    modb = CBashFLOAT32(15)
    modt_p = CBashUINT8ARRAY(16)
    
    def create_altTexture(self):
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 17, 0, 0, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, 17, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return FNVAltTexture(self._CollectionID, self._ModID, self._RecordID, 17, length)
    altTextures = CBashLIST(17, FNVAltTexture)
    altTextures_list = CBashLIST(17, FNVAltTexture, True)

    modelFlags = CBashGeneric(18, c_ubyte)
    script = CBashFORMID(19)
    destructable = CBashGrouped(20, FNVDestructable)
    destructable_list = CBashGrouped(20, FNVDestructable, True)

    description = CBashSTRING(25)
    loopSound = CBashFORMID(26)
    passNote = CBashFORMID(27)
    difficultyType = CBashGeneric(28, c_ubyte)
    flags = CBashGeneric(29, c_ubyte)
    serverType = CBashGeneric(30, c_ubyte)
    unused1 = CBashUINT8ARRAY(31, 1)
    
    def create_menu(self):
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 32, 0, 0, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, 32, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return self.Menu(self._CollectionID, self._ModID, self._RecordID, 32, length)
    menus = CBashLIST(32, Menu)
    menus_list = CBashLIST(32, Menu, True)

    
    IsVeryEasy = CBashBasicType('difficultyType', 0, 'IsEasy')
    IsEasy = CBashBasicType('difficultyType', 1, 'IsVeryEasy')
    IsAverage = CBashBasicType('difficultyType', 2, 'IsVeryEasy')
    IsHard = CBashBasicType('difficultyType', 3, 'IsVeryEasy')
    IsVeryHard = CBashBasicType('difficultyType', 4, 'IsVeryEasy')
    IsRequiresKey = CBashBasicType('difficultyType', 5, 'IsVeryEasy')
    
    IsLeveled = CBashBasicFlag('flags', 0x01)
    IsUnlocked = CBashBasicFlag('flags', 0x02)
    IsAlternateColors = CBashBasicFlag('flags', 0x04)
    IsHideWelcomeTextWhenDisplayingImage = CBashBasicFlag('flags', 0x08)
    
    IsServer1 = CBashBasicType('serverType', 0, 'IsServer2')
    IsServer2 = CBashBasicType('serverType', 1, 'IsServer1')
    IsServer3 = CBashBasicType('serverType', 2, 'IsServer1')
    IsServer4 = CBashBasicType('serverType', 3, 'IsServer1')
    IsServer5 = CBashBasicType('serverType', 4, 'IsServer1')
    IsServer6 = CBashBasicType('serverType', 5, 'IsServer1')
    IsServer7 = CBashBasicType('serverType', 6, 'IsServer1')
    IsServer8 = CBashBasicType('serverType', 7, 'IsServer1')
    IsServer9 = CBashBasicType('serverType', 8, 'IsServer1')
    IsServer10 = CBashBasicType('serverType', 9, 'IsServer1')
    copyattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                           'boundX2', 'boundY2', 'boundZ2',
                                           'full', 'modPath', 'modb', 'modt_p',
                                           'altTextures_list', 'modelFlags',
                                           'script', 'destructable_list',
                                           'description', 'loopSound',
                                           'passNote', 'difficultyType',
                                           'flags', 'serverType', 'menus_list']
    exportattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                             'boundX2', 'boundY2', 'boundZ2',
                                             'full', 'modPath', 'modb',
                                             'altTextures_list', 'modelFlags',
                                             'script', 'destructable_list',
                                             'description', 'loopSound',
                                             'passNote', 'difficultyType',
                                             'flags', 'serverType', 'menus_list'] # 'modt_p',

class FnvARMORecord(FnvBaseRecord):
    _Type = 'ARMO'
    class BipedModel(BaseComponent):
        modPath = CBashISTRING_GROUP(0)
        modt_p = CBashUINT8ARRAY_GROUP(1)

        def create_altTexture(self):
            FieldID = self._FieldID + 2
            length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, FieldID, 0, 0, 0, 0, 0, 0, 1)
            CBash.SetField(self._CollectionID, self._ModID, self._RecordID, FieldID, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
            return FNVAltTexture(self._CollectionID, self._ModID, self._RecordID, FieldID, length)
        altTextures = CBashLIST_GROUP(2, FNVAltTexture)
        altTextures_list = CBashLIST_GROUP(2, FNVAltTexture, True)
        flags = CBashGeneric_GROUP(3, c_ubyte)

        IsHead = CBashBasicFlag('flags', 0x01)
        IsTorso = CBashBasicFlag('flags', 0x02)
        IsRightHand = CBashBasicFlag('flags', 0x04)
        IsLeftHand = CBashBasicFlag('flags', 0x08)
        copyattrs = ['modPath', 'modt_p', 'altTextures_list',
                     'flags']
        exportattrs = ['modPath', 'altTextures_list', 'flags']#, 'modt_p']

    class WorldModel(BaseComponent):
        modPath = CBashISTRING_GROUP(0)
        modt_p = CBashUINT8ARRAY_GROUP(1)

        def create_altTexture(self):
            FieldID = self._FieldID + 2
            length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, FieldID, 0, 0, 0, 0, 0, 0, 1)
            CBash.SetField(self._CollectionID, self._ModID, self._RecordID, FieldID, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
            return FNVAltTexture(self._CollectionID, self._ModID, self._RecordID, FieldID, length)
        altTextures = CBashLIST_GROUP(2, FNVAltTexture)
        altTextures_list = CBashLIST_GROUP(2, FNVAltTexture, True)
        copyattrs = ['modPath', 'modt_p', 'altTextures_list']
        exportattrs = ['modPath', 'altTextures_list']#, 'modt_p']

    class Sound(ListComponent):
        sound = CBashFORMID_LIST(1)
        chance = CBashGeneric_LIST(2, c_ubyte)
        unused1 = CBashUINT8ARRAY_LIST(3, 3)
        type = CBashGeneric_LIST(4, c_ulong)
        IsWalk = CBashBasicType('type', 17, 'IsSneak')
        IsSneak = CBashBasicType('type', 18, 'IsWalk')
        IsRun = CBashBasicType('type', 19, 'IsWalk')
        IsSneakArmor = CBashBasicType('type', 20, 'IsWalk')
        IsRunArmor = CBashBasicType('type', 21, 'IsWalk')
        IsWalkArmor = CBashBasicType('type', 22, 'IsWalk')
        exportattrs = copyattrs = ['sound', 'chance', 'type']

    boundX1 = CBashGeneric(7, c_short)
    boundY1 = CBashGeneric(8, c_short)
    boundZ1 = CBashGeneric(9, c_short)
    boundX2 = CBashGeneric(10, c_short)
    boundY2 = CBashGeneric(11, c_short)
    boundZ2 = CBashGeneric(12, c_short)
    full = CBashSTRING(13)
    script = CBashFORMID(14)
    effect = CBashFORMID(15)
    flags = CBashGeneric(16, c_ulong)
    extraFlags = CBashGeneric(17, c_ubyte)
    unused1 = CBashUINT8ARRAY(18, 3)
    male = CBashGrouped(19, BipedModel)
    male_list = CBashGrouped(19, BipedModel, True)

    maleWorld = CBashGrouped(23, WorldModel)
    maleWorld_list = CBashGrouped(23, WorldModel, True)

    maleIconPath = CBashISTRING(26)
    maleSmallIconPath = CBashISTRING(27)
    female = CBashGrouped(28, BipedModel)
    female_list = CBashGrouped(28, BipedModel, True)

    femaleWorld = CBashGrouped(32, WorldModel)
    femaleWorld_list = CBashGrouped(32, WorldModel, True)

    femaleIconPath = CBashISTRING(35)
    femaleSmallIconPath = CBashISTRING(36)
    ragdollTemplate = CBashISTRING(37)
    repairList = CBashFORMID(38)
    modelList = CBashFORMID(39)
    equipmentType = CBashGeneric(40, c_long)
    pickupSound = CBashFORMID(41)
    dropSound = CBashFORMID(42)
    value = CBashGeneric(43, c_long)
    health = CBashGeneric(44, c_long)
    weight = CBashFLOAT32(45)
    AR = CBashGeneric(46, c_short)
    voiceFlags = CBashGeneric(47, c_ushort)
    DT = CBashFLOAT32(48)
    unknown1 = CBashUINT8ARRAY(49, 4)
    overrideSounds = CBashGeneric(50, c_ulong)
    def create_sound(self):
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 51, 0, 0, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, 51, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return self.Sound(self._CollectionID, self._ModID, self._RecordID, 51, length)
    sounds = CBashLIST(51, Sound)
    sounds_list = CBashLIST(51, Sound, True)

    soundsTemplate = CBashFORMID(52)
    
    IsHead = CBashBasicFlag('flags', 0x00000001)
    IsHair = CBashBasicFlag('flags', 0x00000002)
    IsUpperBody = CBashBasicFlag('flags', 0x00000004)
    IsLeftHand = CBashBasicFlag('flags', 0x00000008)
    IsRightHand = CBashBasicFlag('flags', 0x00000010)
    IsWeapon = CBashBasicFlag('flags', 0x00000020)
    IsPipBoy = CBashBasicFlag('flags', 0x00000040)
    IsBackpack = CBashBasicFlag('flags', 0x00000080)
    IsNecklace = CBashBasicFlag('flags', 0x00000100)
    IsHeadband = CBashBasicFlag('flags', 0x00000200)
    IsHat = CBashBasicFlag('flags', 0x00000400)
    IsEyeGlasses = CBashBasicFlag('flags', 0x00000800)
    IsNoseRing = CBashBasicFlag('flags', 0x00001000)
    IsEarrings = CBashBasicFlag('flags', 0x00002000)
    IsMask = CBashBasicFlag('flags', 0x00004000)
    IsChoker = CBashBasicFlag('flags', 0x00008000)
    IsMouthObject = CBashBasicFlag('flags', 0x00010000)
    IsBodyAddon1 = CBashBasicFlag('flags', 0x00020000)
    IsBodyAddon2 = CBashBasicFlag('flags', 0x00040000)
    IsBodyAddon3 = CBashBasicFlag('flags', 0x00080000)

    IsUnknown1 = CBashBasicFlag('extraFlags', 0x0001)
    IsUnknown2 = CBashBasicFlag('extraFlags', 0x0002)
    IsHasBackpack = CBashBasicFlag('extraFlags', 0x0004)
    IsMedium = CBashBasicFlag('extraFlags', 0x0008)
    IsUnknown3 = CBashBasicFlag('extraFlags', 0x0010)
    IsPowerArmor = CBashBasicFlag('extraFlags', 0x0020)
    IsNonPlayable = CBashBasicFlag('extraFlags', 0x0040)
    IsHeavy = CBashBasicFlag('extraFlags', 0x0080)

    IsNone = CBashBasicType('equipmentType', -1, 'IsBigGuns')
    IsBigGuns = CBashBasicType('equipmentType', 0, 'IsNone')
    IsEnergyWeapons = CBashBasicType('equipmentType', 1, 'IsNone')
    IsSmallGuns = CBashBasicType('equipmentType', 2, 'IsNone')
    IsMeleeWeapons = CBashBasicType('equipmentType', 3, 'IsNone')
    IsUnarmedWeapon = CBashBasicType('equipmentType', 4, 'IsNone')
    IsThrownWeapons = CBashBasicType('equipmentType', 5, 'IsNone')
    IsMine = CBashBasicType('equipmentType', 6, 'IsNone')
    IsBodyWear = CBashBasicType('equipmentType', 7, 'IsNone')
    IsHeadWear = CBashBasicType('equipmentType', 8, 'IsNone')
    IsHandWear = CBashBasicType('equipmentType', 9, 'IsNone')
    IsChems = CBashBasicType('equipmentType', 10, 'IsNone')
    IsStimpack = CBashBasicType('equipmentType', 11, 'IsNone')
    IsEdible = CBashBasicType('equipmentType', 12, 'IsNone')
    IsAlcohol = CBashBasicType('equipmentType', 13, 'IsNone')
    
    IsNotOverridingSounds = CBashBasicType('overrideSounds', 0, 'IsOverridingSounds')
    IsOverridingSounds = CBashBasicType('overrideSounds', 1, 'IsNotOverridingSounds')
    
    IsModulatesVoice = CBashBasicFlag('voiceFlags', 0x0001)
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                                         'boundX2', 'boundY2', 'boundZ2',
                                                         'full', 'script', 'effect',
                                                         'flags', 'extraFlags',
                                                         'male_list', 'maleWorld_list',
                                                         'maleIconPath', 'maleSmallIconPath',
                                                         'female_list', 'femaleWorld_list',
                                                         'femaleIconPath', 'femaleSmallIconPath',
                                                         'ragdollTemplate', 'repairList',
                                                         'modelList', 'equipmentType',
                                                         'pickupSound', 'dropSound', 'value',
                                                         'health', 'weight', 'AR', 'voiceFlags',
                                                         'DT', 'unknown1', 'overrideSounds',
                                                         'sounds_list', 'soundsTemplate']

class FnvBOOKRecord(FnvBaseRecord):
    _Type = 'BOOK'
    boundX1 = CBashGeneric(7, c_short)
    boundY1 = CBashGeneric(8, c_short)
    boundZ1 = CBashGeneric(9, c_short)
    boundX2 = CBashGeneric(10, c_short)
    boundY2 = CBashGeneric(11, c_short)
    boundZ2 = CBashGeneric(12, c_short)
    full = CBashSTRING(13)
    modPath = CBashISTRING(14)
    modb = CBashFLOAT32(15)
    modt_p = CBashUINT8ARRAY(16)
    
    def create_altTexture(self):
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 17, 0, 0, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, 17, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return FNVAltTexture(self._CollectionID, self._ModID, self._RecordID, 17, length)
    altTextures = CBashLIST(17, FNVAltTexture)
    altTextures_list = CBashLIST(17, FNVAltTexture, True)

    modelFlags = CBashGeneric(18, c_ubyte)
    iconPath = CBashISTRING(19)
    smallIconPath = CBashISTRING(20)
    script = CBashFORMID(21)
    description = CBashSTRING(22)
    destructable = CBashGrouped(23, FNVDestructable)
    destructable_list = CBashGrouped(23, FNVDestructable, True)

    flags = CBashGeneric(28, c_ubyte)
    teaches = CBashGeneric(29, c_byte)
    value = CBashGeneric(30, c_long)
    weight = CBashFLOAT32(31)
    
    IsHead = CBashBasicFlag('modelFlags', 0x01)
    IsTorso = CBashBasicFlag('modelFlags', 0x02)
    IsRightHand = CBashBasicFlag('modelFlags', 0x04)
    IsLeftHand = CBashBasicFlag('modelFlags', 0x08)
    
    IsFixed = CBashBasicFlag('flags', 0x00000002)
    IsCantBeTaken = CBashAlias('IsFixed')
    copyattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                           'boundX2', 'boundY2', 'boundZ2',
                                           'full', 'modPath', 'modb', 'modt_p',
                                           'altTextures_list', 'modelFlags',
                                           'iconPath', 'smallIconPath',
                                           'script', 'description',
                                           'destructable_list', 'flags',
                                           'teaches', 'value', 'weight']
    exportattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                             'boundX2', 'boundY2', 'boundZ2',
                                             'full', 'modPath', 'modb',
                                             'altTextures_list', 'modelFlags',
                                             'iconPath', 'smallIconPath',
                                             'script', 'description',
                                             'destructable_list', 'flags',
                                             'teaches', 'value', 'weight'] # 'modt_p',

class FnvCONTRecord(FnvBaseRecord):
    _Type = 'CONT'
    def mergeFilter(self,modSet):
        """Filter out items that don't come from specified modSet.
        Filters items."""
        self.items = [x for x in self.items if x.item[0] in modSet]
        
    boundX1 = CBashGeneric(7, c_short)
    boundY1 = CBashGeneric(8, c_short)
    boundZ1 = CBashGeneric(9, c_short)
    boundX2 = CBashGeneric(10, c_short)
    boundY2 = CBashGeneric(11, c_short)
    boundZ2 = CBashGeneric(12, c_short)
    full = CBashSTRING(13)
    modPath = CBashISTRING(14)
    modb = CBashFLOAT32(15)
    modt_p = CBashUINT8ARRAY(16)
    
    def create_altTexture(self):
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 17, 0, 0, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, 17, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return FNVAltTexture(self._CollectionID, self._ModID, self._RecordID, 17, length)
    altTextures = CBashLIST(17, FNVAltTexture)
    altTextures_list = CBashLIST(17, FNVAltTexture, True)

    modelFlags = CBashGeneric(18, c_ubyte)
    script = CBashFORMID(19)

    def create_item(self):
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 20, 0, 0, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, 20, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return FNVItem(self._CollectionID, self._ModID, self._RecordID, 20, length)
    items = CBashLIST(20, FNVItem)
    items_list = CBashLIST(20, FNVItem, True)

    destructable = CBashGrouped(21, FNVDestructable)
    destructable_list = CBashGrouped(21, FNVDestructable, True)

    flags = CBashGeneric(26, c_ubyte)
    weight = CBashFLOAT32(27)
    openSound = CBashFORMID(28)
    closeSound = CBashFORMID(29)
    loopSound = CBashFORMID(30)
    
    IsHead = CBashBasicFlag('modelFlags', 0x01)
    IsTorso = CBashBasicFlag('modelFlags', 0x02)
    IsRightHand = CBashBasicFlag('modelFlags', 0x04)
    IsLeftHand = CBashBasicFlag('modelFlags', 0x08)

    IsRespawn = CBashBasicFlag('flags', 0x00000001)
    copyattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                           'boundX2', 'boundY2', 'boundZ2',
                                           'full', 'modPath', 'modb', 'modt_p',
                                           'altTextures_list', 'modelFlags',
                                           'script', 'items_list',
                                           'destructable_list', 'flags',
                                           'weight', 'openSound',
                                           'closeSound', 'loopSound', ]
    exportattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                             'boundX2', 'boundY2', 'boundZ2',
                                             'full', 'modPath', 'modb',
                                             'altTextures_list', 'modelFlags',
                                             'script', 'items_list',
                                             'destructable_list', 'flags',
                                             'weight', 'openSound',
                                             'closeSound', 'loopSound', ] #'modt_p', 


class FnvDOORRecord(FnvBaseRecord):
    _Type = 'DOOR'
    boundX1 = CBashGeneric(7, c_short)
    boundY1 = CBashGeneric(8, c_short)
    boundZ1 = CBashGeneric(9, c_short)
    boundX2 = CBashGeneric(10, c_short)
    boundY2 = CBashGeneric(11, c_short)
    boundZ2 = CBashGeneric(12, c_short)
    full = CBashSTRING(13)
    modPath = CBashISTRING(14)
    modb = CBashFLOAT32(15)
    modt_p = CBashUINT8ARRAY(16)
    
    def create_altTexture(self):
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 17, 0, 0, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, 17, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return FNVAltTexture(self._CollectionID, self._ModID, self._RecordID, 17, length)
    altTextures = CBashLIST(17, FNVAltTexture)
    altTextures_list = CBashLIST(17, FNVAltTexture, True)

    modelFlags = CBashGeneric(18, c_ubyte)
    script = CBashFORMID(19)
    destructable = CBashGrouped(20, FNVDestructable)
    destructable_list = CBashGrouped(20, FNVDestructable, True)

    openSound = CBashFORMID(25)
    closeSound = CBashFORMID(26)
    loopSound = CBashFORMID(27)
    flags = CBashGeneric(28, c_ubyte)
    
    IsHead = CBashBasicFlag('modelFlags', 0x01)
    IsTorso = CBashBasicFlag('modelFlags', 0x02)
    IsRightHand = CBashBasicFlag('modelFlags', 0x04)
    IsLeftHand = CBashBasicFlag('modelFlags', 0x08)
    
    IsAutomatic = CBashBasicFlag('flags', 0x02)
    IsHidden = CBashBasicFlag('flags', 0x04)
    IsMinimalUse = CBashBasicFlag('flags', 0x08)
    IsSlidingDoor = CBashBasicFlag('flags', 0x10)
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                                         'boundX2', 'boundY2', 'boundZ2',
                                                         'full', 'modPath', 'modb', 'modt_p',
                                                         'altTextures_list', 'modelFlags',
                                                         'script', 'destructable_list',
                                                         'openSound', 'closeSound',
                                                         'loopSound', 'flags']
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                                         'boundX2', 'boundY2', 'boundZ2',
                                                         'full', 'modPath', 'modb',
                                                         'altTextures_list', 'modelFlags',
                                                         'script', 'destructable_list',
                                                         'openSound', 'closeSound',
                                                         'loopSound', 'flags'] #'modt_p', 

class FnvINGRRecord(FnvBaseRecord):
    _Type = 'INGR'
    boundX1 = CBashGeneric(7, c_short)
    boundY1 = CBashGeneric(8, c_short)
    boundZ1 = CBashGeneric(9, c_short)
    boundX2 = CBashGeneric(10, c_short)
    boundY2 = CBashGeneric(11, c_short)
    boundZ2 = CBashGeneric(12, c_short)
    full = CBashSTRING(13)
    modPath = CBashISTRING(14)
    modb = CBashFLOAT32(15)
    modt_p = CBashUINT8ARRAY(16)
    
    def create_altTexture(self):
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 17, 0, 0, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, 17, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return FNVAltTexture(self._CollectionID, self._ModID, self._RecordID, 17, length)
    altTextures = CBashLIST(17, FNVAltTexture)
    altTextures_list = CBashLIST(17, FNVAltTexture, True)

    modelFlags = CBashGeneric(18, c_ubyte)
    iconPath = CBashISTRING(19)
    smallIconPath = CBashISTRING(20)
    script = CBashFORMID(21)
    equipmentType = CBashGeneric(22, c_long)
    weight = CBashFLOAT32(23)
    value = CBashGeneric(24, c_long)
    flags = CBashGeneric(25, c_ubyte)
    unused1 = CBashUINT8ARRAY(26, 3)
                   
    def create_effect(self):
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 27, 0, 0, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, 27, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return FNVEffect(self._CollectionID, self._ModID, self._RecordID, 27, length)
    effects = CBashLIST(27, FNVEffect)
    effects_list = CBashLIST(27, FNVEffect, True)

    
    copyattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                           'boundX2', 'boundY2', 'boundZ2',
                                           'full', 'modPath', 'modb', 'modt_p',
                                           'altTextures_list', 'modelFlags',
                                           'iconPath', 'smallIconPath',
                                           'script', 'equipmentType',
                                           'weight', 'value', 'flags',
                                           'effects_list']
    exportattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                             'boundX2', 'boundY2', 'boundZ2',
                                             'full', 'modPath', 'modb',
                                             'altTextures_list', 'modelFlags',
                                             'iconPath', 'smallIconPath',
                                             'script', 'equipmentType',
                                             'weight', 'value', 'flags',
                                             'effects_list'] # 'modt_p',

class FnvLIGHRecord(FnvBaseRecord):
    _Type = 'LIGH'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvMISCRecord(FnvBaseRecord):
    _Type = 'MISC'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvSTATRecord(FnvBaseRecord):
    _Type = 'STAT'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvSCOLRecord(FnvBaseRecord):
    _Type = 'SCOL'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvMSTTRecord(FnvBaseRecord):
    _Type = 'MSTT'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvPWATRecord(FnvBaseRecord):
    _Type = 'PWAT'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvGRASRecord(FnvBaseRecord):
    _Type = 'GRAS'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvTREERecord(FnvBaseRecord):
    _Type = 'TREE'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvFURNRecord(FnvBaseRecord):
    _Type = 'FURN'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvWEAPRecord(FnvBaseRecord):
    _Type = 'WEAP'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvAMMORecord(FnvBaseRecord):
    _Type = 'AMMO'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvNPC_Record(FnvBaseRecord):
    _Type = 'NPC_'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvCREARecord(FnvBaseRecord):
    _Type = 'CREA'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvLVLCRecord(FnvBaseRecord):
    _Type = 'LVLC'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvLVLNRecord(FnvBaseRecord):
    _Type = 'LVLN'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvKEYMRecord(FnvBaseRecord):
    _Type = 'KEYM'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvALCHRecord(FnvBaseRecord):
    _Type = 'ALCH'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvIDLMRecord(FnvBaseRecord):
    _Type = 'IDLM'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvNOTERecord(FnvBaseRecord):
    _Type = 'NOTE'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvCOBJRecord(FnvBaseRecord):
    _Type = 'COBJ'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvPROJRecord(FnvBaseRecord):
    _Type = 'PROJ'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvLVLIRecord(FnvBaseRecord):
    _Type = 'LVLI'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvWTHRRecord(FnvBaseRecord):
    _Type = 'WTHR'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvCLMTRecord(FnvBaseRecord):
    _Type = 'CLMT'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvREGNRecord(FnvBaseRecord):
    _Type = 'REGN'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvNAVIRecord(FnvBaseRecord):
    _Type = 'NAVI'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvCELLRecord(FnvBaseRecord):
    _Type = 'CELL'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvWRLDRecord(FnvBaseRecord):
    _Type = 'WRLD'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvDIALRecord(FnvBaseRecord):
    _Type = 'DIAL'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvQUSTRecord(FnvBaseRecord):
    _Type = 'QUST'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvIDLERecord(FnvBaseRecord):
    _Type = 'IDLE'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvPACKRecord(FnvBaseRecord):
    _Type = 'PACK'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvCSTYRecord(FnvBaseRecord):
    _Type = 'CSTY'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvLSCRRecord(FnvBaseRecord):
    _Type = 'LSCR'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvANIORecord(FnvBaseRecord):
    _Type = 'ANIO'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvWATRRecord(FnvBaseRecord):
    _Type = 'WATR'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvEFSHRecord(FnvBaseRecord):
    _Type = 'EFSH'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvEXPLRecord(FnvBaseRecord):
    _Type = 'EXPL'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvDEBRRecord(FnvBaseRecord):
    _Type = 'DEBR'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvIMGSRecord(FnvBaseRecord):
    _Type = 'IMGS'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvIMADRecord(FnvBaseRecord):
    _Type = 'IMAD'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvFLSTRecord(FnvBaseRecord):
    _Type = 'FLST'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvPERKRecord(FnvBaseRecord):
    _Type = 'PERK'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvBPTDRecord(FnvBaseRecord):
    _Type = 'BPTD'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvADDNRecord(FnvBaseRecord):
    _Type = 'ADDN'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvAVIFRecord(FnvBaseRecord):
    _Type = 'AVIF'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvRADSRecord(FnvBaseRecord):
    _Type = 'RADS'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvCAMSRecord(FnvBaseRecord):
    _Type = 'CAMS'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvCPTHRecord(FnvBaseRecord):
    _Type = 'CPTH'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvVTYPRecord(FnvBaseRecord):
    _Type = 'VTYP'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvIPCTRecord(FnvBaseRecord):
    _Type = 'IPCT'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvIPDSRecord(FnvBaseRecord):
    _Type = 'IPDS'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvARMARecord(FnvBaseRecord):
    _Type = 'ARMA'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvECZNRecord(FnvBaseRecord):
    _Type = 'ECZN'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvMESGRecord(FnvBaseRecord):
    _Type = 'MESG'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvRGDLRecord(FnvBaseRecord):
    _Type = 'RGDL'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvDOBJRecord(FnvBaseRecord):
    _Type = 'DOBJ'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvLGTMRecord(FnvBaseRecord):
    _Type = 'LGTM'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvMUSCRecord(FnvBaseRecord):
    _Type = 'MUSC'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvIMODRecord(FnvBaseRecord):
    _Type = 'IMOD'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvREPURecord(FnvBaseRecord):
    _Type = 'REPU'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvRCPERecord(FnvBaseRecord):
    _Type = 'RCPE'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvRCCTRecord(FnvBaseRecord):
    _Type = 'RCCT'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvCHIPRecord(FnvBaseRecord):
    _Type = 'CHIP'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvCSNORecord(FnvBaseRecord):
    _Type = 'CSNO'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvLSCTRecord(FnvBaseRecord):
    _Type = 'LSCT'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvMSETRecord(FnvBaseRecord):
    _Type = 'MSET'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvALOCRecord(FnvBaseRecord):
    _Type = 'ALOC'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvCHALRecord(FnvBaseRecord):
    _Type = 'CHAL'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvAMEFRecord(FnvBaseRecord):
    _Type = 'AMEF'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvCCRDRecord(FnvBaseRecord):
    _Type = 'CCRD'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvCMNYRecord(FnvBaseRecord):
    _Type = 'CMNY'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvCDCKRecord(FnvBaseRecord):
    _Type = 'CDCK'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvDEHYRecord(FnvBaseRecord):
    _Type = 'DEHY'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvHUNGRecord(FnvBaseRecord):
    _Type = 'HUNG'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

class FnvSLPDRecord(FnvBaseRecord):
    _Type = 'SLPD'
    
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + []

#--Oblivion
class ObBaseRecord(object):
    _Type = 'BASE'
    def __init__(self, CollectionIndex, ModID, RecordID, ParentID=0, CopyFlags=0):
        self._CollectionID = CollectionIndex
        self._ModID = ModID
        self._RecordID = RecordID
        self._CopyFlags = CopyFlags
        #ParentID isn't kept for most records

    def __eq__(self, other):
        if type(other) is type(self):
            return self._RecordID == other._RecordID
        return False

    def __ne__(self, other):
        return not self.__eq__(other)

    @property
    def FileName(self):
        return _CGetFileNameByID(self._CollectionID, self._ModID) or 'Missing'

    @property
    def ModName(self):
        return _CGetModNameByID(self._CollectionID, self._ModID) or 'Missing'

    @property
    def GName(self):
        return GPath(self.ModName)

    def UnloadRecord(self):
        _CUnloadRecord(self._CollectionID, self._ModID, self._RecordID)

    def DeleteRecord(self):
        _CDeleteRecord(self._CollectionID, self._ModID, self._RecordID, getattr(self, '_ParentID', 0))

    def GetNumReferences(self, FormIDToMatch):
        FormIDToMatch = MakeShortFid(self._CollectionID, FormIDToMatch)
        if FormIDToMatch is None: return 0
        return _CGetNumReferences(self._CollectionID, self._ModID, self._RecordID, FormIDToMatch)

    def UpdateReferences(self, FormIDToReplace, ReplacementFormID):
        FormIDToReplace = MakeShortFid(self._CollectionID, FormIDToReplace)
        ReplacementFormID = MakeShortFid(self._CollectionID, ReplacementFormID)
        if not (FormIDToReplace or ReplacementFormID): return 0
        return _CUpdateReferences(self._CollectionID, self._ModID, self._RecordID, FormIDToReplace, ReplacementFormID)

    def History(self):
        cModIDs = (c_ulong * 257)() #just allocate enough for the max number + size
        cRecordIDs = (c_ulong * 257)() #just allocate enough for the max number + size
        numRecords = _CGetRecordHistory(self._CollectionID, self._ModID, self._RecordID, byref(cModIDs), byref(cRecordIDs))
        parent = getattr(self, '_ParentID', 0)
        return [self.__class__(self._CollectionID, cModIDs[x], cRecordIDs[x], parent, self._CopyFlags) for x in range(0, numRecords)]

    def IsWinning(self, GetExtendedConflicts=False):
        """Returns true if the record is the last to load.
           If GetExtendedConflicts is True, scanned records will be considered.
           More efficient than running Conflicts() and checking the first value."""
        return _CIsRecordWinning(self._CollectionID, self._ModID, self._RecordID, c_ulong(GetExtendedConflicts))

    def Conflicts(self, GetExtendedConflicts=False):
        numRecords = _CGetNumRecordConflicts(self._CollectionID, self._RecordID, c_ulong(GetExtendedConflicts)) #gives upper bound
        if(numRecords > 1):
            cModIDs = (c_ulong * numRecords)()
            cRecordIDs = (c_ulong * numRecords)()
            numRecords = _CGetRecordConflicts(self._CollectionID, self._RecordID, byref(cModIDs), byref(cRecordIDs), c_ulong(GetExtendedConflicts))
            parent = getattr(self, '_ParentID', 0)
            return [self.__class__(self._CollectionID, cModIDs[x], cRecordIDs[x], parent, self._CopyFlags) for x in range(0, numRecords)]
        return []

    def ConflictDetails(self, attrs=None, GetExtendedConflicts=False):
        conflicting = {}
        if attrs is None:
            attrs = self.copyattrs
        if not attrs:
            return conflicting
        #recordMasters = set(ObModFile(self._CollectionID, self._ModID).TES4.masters)
        #sort oldest to newest rather than newest to oldest
        #conflicts = self.Conflicts(GetExtendedConflicts)
        #Less pythonic, but optimized for better speed.
        #Equivalent to commented out code.
        #parentRecords = [parent for parent in conflicts if parent.ModName in recordMasters]
        #parentRecords.reverse()
        parentRecords = self.History()
        if parentRecords:
            conflicting.update([(attr,reduce(getattr, attr.split('.'), self)) for parentRecord in parentRecords for attr in attrs if reduce(getattr, attr.split('.'), self) != reduce(getattr, attr.split('.'), parentRecord)])
        else: #is the first instance of the record
            conflicting.update([(attr,reduce(getattr, attr.split('.'), self)) for attr in attrs])
##        if parentRecords:
##            for parentRecord in parentRecords:
##                for attr in attrs:
##                    if getattr_deep(self,attr) != getattr_deep(parentRecord,attr):
##                        conflicting[attr] = getattr_deep(self,attr)
##        else:
##            for attr in attrs:
##                conflicting[attr] = getattr_deep(self,attr)
        return conflicting

    def mergeFilter(self,modSet):
        """This method is called by the bashed patch mod merger. The intention is
        to allow a record to be filtered according to the specified modSet. E.g.
        for a list record, items coming from mods not in the modSet could be
        removed from the list."""
        pass

    def CopyAsOverride(self, target, CopyFlags=None):
        if CopyFlags is None: CopyFlags = self._CopyFlags
        targetID = 0
        if hasattr(self, '_ParentID'):
            if isinstance(target, ObModFile): targetID = self._ParentID
            else: targetID = target._RecordID
        ##Record Creation Flags
        ##SetAsOverride       = 0x00000001,
        ##SetAsWorldCell      = 0x00000002,
        ##CopyWorldCellStatus = 0x00000004
        #Set SetAsOverride
        CopyFlags |= 0x00000001
        RecordID = _CCopyRecord(self._CollectionID, self._ModID, self._RecordID, target._ModID, targetID, 0, 0, c_ulong(CopyFlags))
        #Clear SetAsOverride
        CopyFlags &= ~0x00000001
        if(RecordID): return self.__class__(self._CollectionID, target._ModID, RecordID, getattr(self, '_ParentID', 0), CopyFlags)
        return None

    def CopyAsNew(self, target, RecordFormID=0, CopyFlags=None):
        if CopyFlags is None: CopyFlags = self._CopyFlags
        targetID = 0
        if hasattr(self, '_ParentID'):
            if isinstance(target, ObModFile): targetID = self._ParentID
            else: targetID = target._RecordID
        ##Record Creation Flags
        ##SetAsOverride       = 0x00000001,
        ##SetAsWorldCell      = 0x00000002,
        ##CopyWorldCellStatus = 0x00000004
        #Clear SetAsOverride in case it was set
        CopyFlags &= ~0x00000001
        RecordID = _CCopyRecord(self._CollectionID, self._ModID, self._RecordID, target._ModID, targetID, RecordFormID, 0, c_ulong(CopyFlags))
        if(RecordID): return self.__class__(self._CollectionID, target._ModID, RecordID, getattr(self, '_ParentID', 0), CopyFlags)
        return None

    @property
    def Parent(self):
        ParentID = getattr(self, '_ParentID', 0)
        if ParentID:
            testRecord = ObBaseRecord(self._CollectionID, self._ModID, ParentID, 0, 0)
            RecordType = type_record[testRecord.recType]
            if RecordType:
                return RecordType(self._CollectionID, self._ModID, ParentID, 0, 0)
        return None

    @property
    def recType(self):
        _CGetFieldAttribute.restype = (c_char * 4)
        retValue = _CGetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 0, 0, 0, 0, 0, 0, 0, 0)
        _CGetFieldAttribute.restype = c_ulong
        if(retValue and retValue.value != ''): return retValue.value
        return None

    flags1 = CBashGeneric(1, c_ulong)

    def get_fid(self):
        _CGetField.restype = POINTER(c_ulong)
        retValue = _CGetField(self._CollectionID, self._ModID, self._RecordID, 2, 0, 0, 0, 0, 0, 0, 0)
        if(retValue): return MakeLongFid(self._CollectionID, self._ModID, retValue.contents.value)
        return None
    def set_fid(self, nValue):
        if nValue is None: nValue = 0
        else: nValue = MakeShortFid(self._CollectionID, nValue)
        _CSetRecordIdentifiers(self._CollectionID, self._ModID, self._RecordID, nValue, self.eid or 0)
    fid = property(get_fid, set_fid)

    flags2 = CBashGeneric(3, c_ulong)

    def get_eid(self):
        _CGetField.restype = c_char_p
        retValue = _CGetField(self._CollectionID, self._ModID, self._RecordID, 4, 0, 0, 0, 0, 0, 0, 0)
        if(retValue): return ISTRING(retValue)
        return None
    def set_eid(self, nValue):
        if nValue is None or not len(nValue): nValue = 0
        else: nValue = str(nValue)
        _CSetRecordIdentifiers(self._CollectionID, self._ModID, self._RecordID, MakeShortFid(self._CollectionID, self.fid or 0), nValue)
    eid = property(get_eid, set_eid)

    IsDeleted = CBashBasicFlag('flags1', 0x00000020)
    IsBorderRegion = CBashBasicFlag('flags1', 0x00000040)
    IsTurnOffFire = CBashBasicFlag('flags1', 0x00000080)
    IsCastsShadows = CBashBasicFlag('flags1', 0x00000200)
    IsPersistent = CBashBasicFlag('flags1', 0x00000400)
    IsQuest = CBashAlias('IsPersistent')
    IsQuestOrPersistent = CBashAlias('IsPersistent')
    IsInitiallyDisabled = CBashBasicFlag('flags1', 0x00000800)
    IsIgnored = CBashBasicFlag('flags1', 0x00001000)
    IsVisibleWhenDistant = CBashBasicFlag('flags1', 0x00008000)
    IsVWD = CBashAlias('IsVisibleWhenDistant')
    IsDangerousOrOffLimits = CBashBasicFlag('flags1', 0x00020000)
    IsCompressed = CBashBasicFlag('flags1', 0x00040000)
    IsCantWait = CBashBasicFlag('flags1', 0x00080000)
    baseattrs = ['flags1', 'flags2', 'eid']

class ObTES4Record(object):
    _Type = 'TES4'
    def __init__(self, CollectionIndex, ModID, RecordID, ParentID=0, CopyFlags=0):
        self._CollectionID = CollectionIndex
        self._ModID = ModID
        self._RecordID = RecordID

    def UnloadRecord(self):
        pass

    @property
    def recType(self):
        return self._Type

    flags1 = CBashGeneric(1, c_ulong)
    flags2 = CBashGeneric(3, c_ulong)
    version = CBashFLOAT32(5)
    numRecords = CBashGeneric(6, c_ulong)
    nextObject = CBashGeneric(7, c_ulong)
    ofst_p = CBashUINT8ARRAY(8)
    dele_p = CBashUINT8ARRAY(9)
    author = CBashSTRING(10)
    description = CBashSTRING(11)
    masters = CBashISTRINGARRAY(12)
    DATA = CBashJunk(13)
    IsESM = CBashBasicFlag('flags1', 0x00000001)
    exportattrs = copyattrs = ['flags1', 'flags2', 'version', 'numRecords', 'nextObject',
                 'author', 'description', 'masters']

class ObGMSTRecord(ObBaseRecord):
    _Type = 'GMST'
    def get_value(self):
        rFormat = _CGetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 5, 0, 0, 0, 0, 0, 0, 2)
        if(rFormat == API_FIELDS.UNKNOWN):
            return None
        elif(rFormat == API_FIELDS.SINT32):
            _CGetField.restype = POINTER(c_long)
            retValue = _CGetField(self._CollectionID, self._ModID, self._RecordID, 5, 0, 0, 0, 0, 0, 0, 0)
            if(retValue): return retValue.contents.value
        elif(rFormat == API_FIELDS.FLOAT32):
            _CGetField.restype = POINTER(c_float)
            retValue = _CGetField(self._CollectionID, self._ModID, self._RecordID, 5, 0, 0, 0, 0, 0, 0, 0)
            if(retValue): return round(retValue.contents.value,6)
        elif(rFormat == API_FIELDS.STRING):
            _CGetField.restype = c_char_p
            return _CGetField(self._CollectionID, self._ModID, self._RecordID, 5, 0, 0, 0, 0, 0, 0, 0)
        return None
    def set_value(self, nValue):
        if nValue is None: _CDeleteField(self._CollectionID, self._ModID, self._RecordID, 5, 0, 0, 0, 0, 0, 0)
        else:
            rFormat = _CGetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 5, 0, 0, 0, 0, 0, 0, 2)
            if(rFormat == API_FIELDS.SINT32 and type(nValue) is int):
                _CSetField(self._CollectionID, self._ModID, self._RecordID, 5, 0, 0, 0, 0, 0, 0, byref(c_long(nValue)), 0)
            elif(rFormat == API_FIELDS.FLOAT32 == 10 and type(nValue) is float):
                _CSetField(self._CollectionID, self._ModID, self._RecordID, 5, 0, 0, 0, 0, 0, 0, byref(c_float(round(nValue,6))), 0)
            elif(rFormat == API_FIELDS.STRING and type(nValue) is str):
                _CSetField(self._CollectionID, self._ModID, self._RecordID, 5, 0, 0, 0, 0, 0, 0, nValue, 0)
    value = property(get_value, set_value)
    exportattrs = copyattrs = ObBaseRecord.baseattrs + ['value']

class ObACHRRecord(ObBaseRecord):
    def __init__(self, CollectionIndex, ModID, RecordID, ParentID=0, CopyFlags=0):
        ObBaseRecord.__init__(self, CollectionIndex, ModID, RecordID, ParentID, CopyFlags)
        self._ParentID = ParentID

    _Type = 'ACHR'
    base = CBashFORMID(5)
    unknownXPCIFormID = CBashFORMID(6)
    unknownXPCIString = CBashISTRING(7)
    lod1 = CBashFLOAT32(8)
    lod2 = CBashFLOAT32(9)
    lod3 = CBashFLOAT32(10)
    parent = CBashFORMID(11)
    parentFlags = CBashGeneric(12, c_ubyte)
    unused1 = CBashUINT8ARRAY(13, 3)
    merchantContainer = CBashFORMID(14)
    horse = CBashFORMID(15)
    xrgd_p = CBashUINT8ARRAY(16)
    scale = CBashFLOAT32(17)
    posX = CBashFLOAT32(18)
    posY = CBashFLOAT32(19)
    posZ = CBashFLOAT32(20)
    rotX = CBashFLOAT32(21)
    rotX_degrees = CBashDEGREES(21)
    rotY = CBashFLOAT32(22)
    rotY_degrees = CBashDEGREES(22)
    rotZ = CBashFLOAT32(23)
    rotZ_degrees = CBashDEGREES(23)
    IsOppositeParent = CBashBasicFlag('parentFlags', 0x00000001)
    copyattrs = ObBaseRecord.baseattrs + ['base', 'unknownXPCIFormID', 'unknownXPCIString',
                                        'lod1', 'lod2', 'lod3', 'parent', 'parentFlags',
                                        'merchantContainer', 'horse', 'xrgd_p', 'scale',
                                        'posX', 'posY', 'posZ', 'rotX', 'rotY', 'rotZ']
    exportattrs = ObBaseRecord.baseattrs + ['base', 'unknownXPCIFormID', 'unknownXPCIString',
                                        'lod1', 'lod2', 'lod3', 'parent', 'parentFlags',
                                        'merchantContainer', 'horse', 'scale',
                                        'posX', 'posY', 'posZ', 'rotX', 'rotY', 'rotZ'] #'xrgd_p',

class ObACRERecord(ObBaseRecord):
    def __init__(self, CollectionIndex, ModID, RecordID, ParentID=0, CopyFlags=0):
        ObBaseRecord.__init__(self, CollectionIndex, ModID, RecordID, ParentID, CopyFlags=0)
        self._ParentID = ParentID

    _Type = 'ACRE'
    base = CBashFORMID(5)
    owner = CBashFORMID(6)
    rank = CBashGeneric(7, c_long)
    globalVariable = CBashFORMID(8)
    lod1 = CBashFLOAT32(9)
    lod2 = CBashFLOAT32(10)
    lod3 = CBashFLOAT32(11)
    parent = CBashFORMID(12)
    parentFlags = CBashGeneric(13, c_ubyte)
    unused1 = CBashUINT8ARRAY(14, 3)
    xrgd_p = CBashUINT8ARRAY(15)
    scale = CBashFLOAT32(16)
    posX = CBashFLOAT32(17)
    posY = CBashFLOAT32(18)
    posZ = CBashFLOAT32(19)
    rotX = CBashFLOAT32(20)
    rotX_degrees = CBashDEGREES(20)
    rotY = CBashFLOAT32(21)
    rotY_degrees = CBashDEGREES(21)
    rotZ = CBashFLOAT32(22)
    rotZ_degrees = CBashDEGREES(22)
    IsOppositeParent = CBashBasicFlag('parentFlags', 0x00000001)
    copyattrs = ObBaseRecord.baseattrs + ['base', 'owner', 'rank', 'globalVariable',
                                        'lod1', 'lod2', 'lod3', 'parent', 'parentFlags',
                                        'xrgd_p', 'scale', 'posX', 'posY', 'posZ', 'rotX',
                                        'rotY', 'rotZ']
    exportattrs = ObBaseRecord.baseattrs + ['base', 'owner', 'rank', 'globalVariable',
                                        'lod1', 'lod2', 'lod3', 'parent', 'parentFlags',
                                        'scale', 'posX', 'posY', 'posZ', 'rotX',
                                        'rotY', 'rotZ'] #'xrgd_p',

class ObREFRRecord(ObBaseRecord):
    def __init__(self, CollectionIndex, ModID, RecordID, ParentID=0, CopyFlags=0):
        ObBaseRecord.__init__(self, CollectionIndex, ModID, RecordID, ParentID, CopyFlags)
        self._ParentID = ParentID

    _Type = 'REFR'
    base = CBashFORMID(5)
    destination = CBashFORMID(6)
    destinationPosX = CBashFLOAT32(7)
    destinationPosY = CBashFLOAT32(8)
    destinationPosZ = CBashFLOAT32(9)
    destinationRotX = CBashFLOAT32(10)
    destinationRotX_degrees = CBashDEGREES(10)
    destinationRotY = CBashFLOAT32(11)
    destinationRotY_degrees = CBashDEGREES(11)
    destinationRotZ = CBashFLOAT32(12)
    destinationRotZ_degrees = CBashDEGREES(12)
    lockLevel = CBashGeneric(13, c_ubyte)
    unused1 = CBashUINT8ARRAY(14, 3)
    lockKey = CBashFORMID(15)
    unused2 = CBashUINT8ARRAY(16, 4)
    lockFlags = CBashGeneric(17, c_ubyte)
    unused3 = CBashUINT8ARRAY(18, 3)
    owner = CBashFORMID(19)
    rank = CBashGeneric(20, c_long)
    globalVariable = CBashFORMID(21)
    parent = CBashFORMID(22)
    parentFlags = CBashGeneric(23, c_ubyte)
    unused4 = CBashUINT8ARRAY(24, 3)
    target = CBashFORMID(25)
    seed = CBashXSED(26)
    seed_as_offset = CBashXSED(26, True)
    lod1 = CBashFLOAT32(27)
    lod2 = CBashFLOAT32(28)
    lod3 = CBashFLOAT32(29)
    charge = CBashFLOAT32(30)
    health = CBashGeneric(31, c_long)
    unknownXPCIFormID = CBashFORMID(32)
    unknownXPCIString = CBashISTRING(33)
    levelMod = CBashGeneric(34, c_long)
    unknownXRTMFormID = CBashFORMID(35)
    actionFlags = CBashGeneric(36, c_ulong)
    count = CBashGeneric(37, c_long)
    markerFlags = CBashGeneric(38, c_ubyte)
    markerName = CBashSTRING(39)
    markerType = CBashGeneric(40, c_ubyte)
    markerUnused = CBashUINT8ARRAY(41, 1)
    scale = CBashFLOAT32(42)
    soulType = CBashGeneric(43, c_ubyte)
    posX = CBashFLOAT32(44)
    posY = CBashFLOAT32(45)
    posZ = CBashFLOAT32(46)
    rotX = CBashFLOAT32(47)
    rotX_degrees = CBashDEGREES(47)
    rotY = CBashFLOAT32(48)
    rotY_degrees = CBashDEGREES(48)
    rotZ = CBashFLOAT32(49)
    rotZ_degrees = CBashDEGREES(49)
    IsLeveledLock = CBashBasicFlag('lockFlags', 0x00000004)
    IsOppositeParent = CBashBasicFlag('parentFlags', 0x00000001)
    IsUseDefault = CBashBasicFlag('actionFlags', 0x00000001)
    IsActivate = CBashBasicFlag('actionFlags', 0x00000002)
    IsOpen = CBashBasicFlag('actionFlags', 0x00000004)
    IsOpenByDefault = CBashBasicFlag('actionFlags', 0x00000008)
    IsVisible = CBashBasicFlag('markerFlags', 0x00000001)
    IsCanTravelTo = CBashBasicFlag('markerFlags', 0x00000002)
    IsMarkerNone = CBashBasicType('markerType', 0, 'IsCamp')
    IsCamp = CBashBasicType('markerType', 1, 'IsMarkerNone')
    IsCave = CBashBasicType('markerType', 2, 'IsMarkerNone')
    IsCity = CBashBasicType('markerType', 3, 'IsMarkerNone')
    IsElvenRuin = CBashBasicType('markerType', 4, 'IsMarkerNone')
    IsFortRuin = CBashBasicType('markerType', 5, 'IsMarkerNone')
    IsMine = CBashBasicType('markerType', 6, 'IsMarkerNone')
    IsLandmark = CBashBasicType('markerType', 7, 'IsMarkerNone')
    IsTavern = CBashBasicType('markerType', 8, 'IsMarkerNone')
    IsSettlement = CBashBasicType('markerType', 9, 'IsMarkerNone')
    IsDaedricShrine = CBashBasicType('markerType', 10, 'IsMarkerNone')
    IsOblivionGate = CBashBasicType('markerType', 11, 'IsMarkerNone')
    IsUnknownDoorIcon = CBashBasicType('markerType', 12, 'IsMarkerNone')
    IsNoSoul = CBashBasicType('soulType', 0, 'IsPettySoul')
    IsPettySoul = CBashBasicType('soulType', 1, 'IsNoSoul')
    IsLesserSoul = CBashBasicType('soulType', 2, 'IsNoSoul')
    IsCommonSoul = CBashBasicType('soulType', 3, 'IsNoSoul')
    IsGreaterSoul = CBashBasicType('soulType', 4, 'IsNoSoul')
    IsGrandSoul = CBashBasicType('soulType', 5, 'IsNoSoul')
    exportattrs = copyattrs = ObBaseRecord.baseattrs + ['base', 'destination',
                                        'destinationPosX', 'destinationPosY',
                                        'destinationPosZ', 'destinationRotX',
                                        'destinationRotY', 'destinationRotZ',
                                        'lockLevel', 'lockKey', 'lockFlags',
                                        'owner', 'rank',
                                        'globalVariable', 'parent',
                                        'parentFlags', 'target', 'seed',
                                        'seed_as_offset', 'lod1', 'lod2', 'lod3',
                                        'charge', 'health','levelMod','actionFlags',
                                        'count', 'markerFlags', 'markerName',
                                        'markerType', 'scale','soulType',
                                        'posX', 'posY', 'posZ', 'rotX',
                                        'rotY', 'rotZ']

class ObINFORecord(ObBaseRecord):
    def __init__(self, CollectionIndex, ModID, RecordID, ParentID=0, CopyFlags=0):
        ObBaseRecord.__init__(self, CollectionIndex, ModID, RecordID, ParentID, CopyFlags)
        self._ParentID = ParentID

    _Type = 'INFO'
    class Response(ListComponent):
        emotionType = CBashGeneric_LIST(1, c_ulong)
        emotionValue = CBashGeneric_LIST(2, c_long)
        unused1 = CBashUINT8ARRAY_LIST(3, 4)
        responseNum = CBashGeneric_LIST(4, c_ubyte)
        unused2 = CBashUINT8ARRAY_LIST(5, 3)
        responseText = CBashSTRING_LIST(6)
        actorNotes = CBashISTRING_LIST(7)
        IsNeutral = CBashBasicType('emotionType', 0, 'IsAnger')
        IsAnger = CBashBasicType('emotionType', 1, 'IsNeutral')
        IsDisgust = CBashBasicType('emotionType', 2, 'IsNeutral')
        IsFear = CBashBasicType('emotionType', 3, 'IsNeutral')
        IsSad = CBashBasicType('emotionType', 4, 'IsNeutral')
        IsHappy = CBashBasicType('emotionType', 5, 'IsNeutral')
        IsSurprise = CBashBasicType('emotionType', 6, 'IsNeutral')
        exportattrs = copyattrs = ['emotionType', 'emotionValue', 'responseNum',
                                   'responseText', 'actorNotes']

    dialType = CBashGeneric(5, c_ushort)
    flags = CBashGeneric(6, c_ubyte)
    quest = CBashFORMID(7)
    topic = CBashFORMID(8)
    prevInfo = CBashFORMID(9)
    addTopics = CBashFORMIDARRAY(10)

    def create_response(self):
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 11, 0, 0, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, 11, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return self.Response(self._CollectionID, self._ModID, self._RecordID, 11, length)
    responses = CBashLIST(11, Response)
    responses_list = CBashLIST(11, Response, True)

    def create_condition(self):
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 12, 0, 0, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, 12, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return Condition(self._CollectionID, self._ModID, self._RecordID, 12, length)
    conditions = CBashLIST(12, Condition)
    conditions_list = CBashLIST(12, Condition, True)

    choices = CBashFORMIDARRAY(13)
    linksFrom = CBashFORMIDARRAY(14)
    unused1 = CBashUINT8ARRAY(15, 4)
    numRefs = CBashGeneric(16, c_ulong)
    compiledSize = CBashGeneric(17, c_ulong)
    lastIndex = CBashGeneric(18, c_ulong)
    scriptType = CBashGeneric(19, c_ulong)
    compiled_p = CBashUINT8ARRAY(20)
    scriptText = CBashISTRING(21)
    references = CBashFORMID_OR_UINT32_ARRAY(22)
    IsTopic = CBashBasicType('dialType', 0, 'IsConversation')
    IsConversation = CBashBasicType('dialType', 1, 'IsTopic')
    IsCombat = CBashBasicType('dialType', 2, 'IsTopic')
    IsPersuasion = CBashBasicType('dialType', 3, 'IsTopic')
    IsDetection = CBashBasicType('dialType', 4, 'IsTopic')
    IsService = CBashBasicType('dialType', 5, 'IsTopic')
    IsMisc = CBashBasicType('dialType', 6, 'IsTopic')
    IsGoodbye = CBashBasicFlag('flags', 0x00000001)
    IsRandom = CBashBasicFlag('flags', 0x00000002)
    IsSayOnce = CBashBasicFlag('flags', 0x00000004)
    IsRunImmediately = CBashBasicFlag('flags', 0x00000008)
    IsInfoRefusal = CBashBasicFlag('flags', 0x00000010)
    IsRandomEnd = CBashBasicFlag('flags', 0x00000020)
    IsRunForRumors = CBashBasicFlag('flags', 0x00000040)
    copyattrs = ObBaseRecord.baseattrs + ['dialType', 'flags', 'quest', 'topic',
                                        'prevInfo', 'addTopics', 'responses_list',
                                        'conditions_list', 'choices', 'linksFrom',
                                        'numRefs', 'compiledSize', 'lastIndex',
                                        'scriptType', 'compiled_p', 'scriptText',
                                        'references']
    exportattrs = ObBaseRecord.baseattrs + ['dialType', 'flags', 'quest', 'topic',
                                        'prevInfo', 'addTopics', 'responses_list',
                                        'conditions_list', 'choices', 'linksFrom',
                                        'numRefs', 'compiledSize', 'lastIndex',
                                        'scriptType', 'scriptText',
                                        'references'] #'compiled_p',

class ObLANDRecord(ObBaseRecord):
    def __init__(self, CollectionIndex, ModID, RecordID, ParentID=0, CopyFlags=0):
        ObBaseRecord.__init__(self, CollectionIndex, ModID, RecordID, ParentID, CopyFlags)
        self._ParentID = ParentID

    _Type = 'LAND'
    class Normal(ListX2Component):
        x = CBashGeneric_LISTX2(1, c_ubyte)
        y = CBashGeneric_LISTX2(2, c_ubyte)
        z = CBashGeneric_LISTX2(3, c_ubyte)
        exportattrs = copyattrs = ['x', 'y', 'z']

    class Height(ListX2Component):
        height = CBashGeneric_LISTX2(1, c_byte)
        exportattrs = copyattrs = ['height']

    class Color(ListX2Component):
        red = CBashGeneric_LISTX2(1, c_ubyte)
        green = CBashGeneric_LISTX2(2, c_ubyte)
        blue = CBashGeneric_LISTX2(3, c_ubyte)
        exportattrs = copyattrs = ['red', 'green', 'blue']

    class BaseTexture(ListComponent):
        texture = CBashFORMID_LIST(1)
        quadrant = CBashGeneric_LIST(2, c_byte)
        unused1 = CBashUINT8ARRAY_LIST(3, 1)
        layer = CBashGeneric_LIST(4, c_short)
        exportattrs = copyattrs = ['texture', 'quadrant', 'layer']

    class AlphaLayer(ListComponent):
        class Opacity(ListX2Component):
            position = CBashGeneric_LISTX2(1, c_ushort)
            unused1 = CBashUINT8ARRAY_LISTX2(2, 2)
            opacity = CBashFLOAT32_LISTX2(3)
            exportattrs = copyattrs = ['position', 'opacity']
        texture = CBashFORMID_LIST(1)
        quadrant = CBashGeneric_LIST(2, c_byte)
        unused1 = CBashUINT8ARRAY_LIST(3, 1)
        layer = CBashGeneric_LIST(4, c_short)

        def create_opacity(self):
            length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, self._FieldID, self._ListIndex, 5, 0, 0, 0, 0, 1)
            CBash.SetField(self._CollectionID, self._ModID, self._RecordID, self._FieldID, self._ListIndex, 5, 0, 0, 0, 0, 0, c_ulong(length + 1))
            return self.Opacity(self._CollectionID, self._ModID, self._RecordID, self._FieldID, self._ListIndex, 5, length)
        opacities = CBashLIST_LIST(5, Opacity)
        opacities_list = CBashLIST_LIST(5, Opacity, True)

        exportattrs = copyattrs = ['texture', 'quadrant', 'layer', 'opacities_list']

    class VertexTexture(ListComponent):
        texture = CBashFORMID_LIST(1)
        exportattrs = copyattrs = ['texture']

    class Position(ListX2Component):
        height = CBashFLOAT32_LISTX2(1)
        normalX = CBashGeneric_LISTX2(2, c_ubyte)
        normalY = CBashGeneric_LISTX2(3, c_ubyte)
        normalZ = CBashGeneric_LISTX2(4, c_ubyte)
        red = CBashGeneric_LISTX2(5, c_ubyte)
        green = CBashGeneric_LISTX2(6, c_ubyte)
        blue = CBashGeneric_LISTX2(7, c_ubyte)
        baseTexture = CBashFORMID_LISTX2(8)
        alphaLayer1Texture = CBashFORMID_LISTX2(9)
        alphaLayer1Opacity = CBashFLOAT32_LISTX2(10)
        alphaLayer2Texture = CBashFORMID_LISTX2(11)
        alphaLayer2Opacity = CBashFLOAT32_LISTX2(12)
        alphaLayer3Texture = CBashFORMID_LISTX2(13)
        alphaLayer3Opacity = CBashFLOAT32_LISTX2(14)
        alphaLayer4Texture = CBashFORMID_LISTX2(15)
        alphaLayer4Opacity = CBashFLOAT32_LISTX2(16)
        alphaLayer5Texture = CBashFORMID_LISTX2(17)
        alphaLayer5Opacity = CBashFLOAT32_LISTX2(18)
        alphaLayer6Texture = CBashFORMID_LISTX2(19)
        alphaLayer6Opacity = CBashFLOAT32_LISTX2(20)
        alphaLayer7Texture = CBashFORMID_LISTX2(21)
        alphaLayer7Opacity = CBashFLOAT32_LISTX2(22)
        alphaLayer8Texture = CBashFORMID_LISTX2(23)
        alphaLayer8Opacity = CBashFLOAT32_LISTX2(24)
        exportattrs = copyattrs = ['height', 'normalX', 'normalY', 'normalZ',
                     'red', 'green', 'blue', 'baseTexture',
                     'alphaLayer1Texture', 'alphaLayer1Opacity',
                     'alphaLayer2Texture', 'alphaLayer2Opacity',
                     'alphaLayer3Texture', 'alphaLayer3Opacity',
                     'alphaLayer4Texture', 'alphaLayer4Opacity',
                     'alphaLayer5Texture', 'alphaLayer5Opacity',
                     'alphaLayer6Texture', 'alphaLayer6Opacity',
                     'alphaLayer7Texture', 'alphaLayer7Opacity',
                     'alphaLayer8Texture', 'alphaLayer8Opacity']

    data = CBashUINT8ARRAY(5)

    def get_normals(self):
        return [[self.Normal(self._CollectionID, self._ModID, self._RecordID, 6, x, 0, y) for y in range(0,33)] for x in range(0,33)]
    def set_normals(self, nElements):
        if nElements is None or len(nElements) != 33: return
        if isinstance(nElements[0], tuple): nValues = nElements
        else: nValues = ExtractCopyList(nElements)
        SetCopyList(self.normals, nValues)
    normals = property(get_normals, set_normals)
    def get_normals_list(self):
        return ExtractCopyList(self.normals)
    normals_list = property(get_normals_list, set_normals)

    heightOffset = CBashFLOAT32(7)

    def get_heights(self):
        return [[self.Height(self._CollectionID, self._ModID, self._RecordID, 8, x, 0, y) for y in range(0,33)] for x in range(0,33)]
    def set_heights(self, nElements):
        if nElements is None or len(nElements) != 33: return
        if isinstance(nElements[0], tuple): nValues = nElements
        else: nValues = ExtractCopyList(nElements)
        SetCopyList(self.heights, nValues)
    heights = property(get_heights, set_heights)
    def get_heights_list(self):
        return ExtractCopyList(self.heights)
    heights_list = property(get_heights_list, set_heights)

    unused1 = CBashUINT8ARRAY(9, 3)

    def get_colors(self):
        return [[self.Color(self._CollectionID, self._ModID, self._RecordID, 10, x, 0, y) for y in range(0,33)] for x in range(0,33)]
    def set_colors(self, nElements):
        if nElements is None or len(nElements) != 33: return
        if isinstance(nElements[0], tuple): nValues = nElements
        else: nValues = ExtractCopyList(nElements)
        SetCopyList(self.colors, nValues)
    colors = property(get_colors, set_colors)
    def get_colors_list(self):
        return ExtractCopyList(self.colors)
    colors_list = property(get_colors_list, set_colors)

    def create_baseTexture(self):
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 11, 0, 0, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, 11, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return self.BaseTexture(self._CollectionID, self._ModID, self._RecordID, 11, length)
    baseTextures = CBashLIST(11, BaseTexture)
    baseTextures_list = CBashLIST(11, BaseTexture, True)

    def create_alphaLayer(self):
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 12, 0, 0, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, 12, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return self.AlphaLayer(self._CollectionID, self._ModID, self._RecordID, 12, length)
    alphaLayers = CBashLIST(12, AlphaLayer)
    alphaLayers_list = CBashLIST(12, AlphaLayer, True)

    def create_vertexTexture(self):
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 13, 0, 0, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, 13, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return self.VertexTexture(self._CollectionID, self._ModID, self._RecordID, 13, length)
    vertexTextures = CBashLIST(13, VertexTexture)
    vertexTextures_list = CBashLIST(13, VertexTexture, True)

    ##The Positions accessor is unique in that it duplicates the above accessors. It just presents the data in a more friendly format.
    def get_Positions(self):
        return [[self.Position(self._CollectionID, self._ModID, self._RecordID, 14, row, 0, column) for column in range(0,33)] for row in range(0,33)]
    def set_Positions(self, nElements):
        if nElements is None or len(nElements) != 33: return
        if isinstance(nElements[0], tuple): nValues = nElements
        else: nValues = ExtractCopyList(nElements)
        SetCopyList(self.Positions, nValues)
    Positions = property(get_Positions, set_Positions)
    def get_Positions_list(self):
        return ExtractCopyList(self.Positions)
    Positions_list = property(get_Positions_list, set_Positions)
    copyattrs = ObBaseRecord.baseattrs + ['data_p', 'normals_list', 'heights_list', 'heightOffset',
                                        'colors_list', 'baseTextures_list', 'alphaLayers_list',
                                        'vertexTextures_list']
    exportattrs = ObBaseRecord.baseattrs + ['normals_list', 'heights_list', 'heightOffset',
                                        'colors_list', 'baseTextures_list', 'alphaLayers_list',
                                        'vertexTextures_list'] #'data_p',

class ObPGRDRecord(ObBaseRecord):
    def __init__(self, CollectionIndex, ModID, RecordID, ParentID=0, CopyFlags=0):
        ObBaseRecord.__init__(self, CollectionIndex, ModID, RecordID, ParentID, CopyFlags)
        self._ParentID = ParentID

    _Type = 'PGRD'
    class PGRI(ListComponent):
        point = CBashGeneric_LIST(1, c_ushort)
        unused1 = CBashUINT8ARRAY_LIST(2, 2)
        x = CBashFLOAT32_LIST(3)
        y = CBashFLOAT32_LIST(4)
        z = CBashFLOAT32_LIST(5)
        exportattrs = copyattrs = ['point', 'x', 'y', 'z']

    class PGRL(ListComponent):
        reference = CBashFORMID_LIST(1)
        points = CBashUINT32ARRAY_LIST(2)
        exportattrs = copyattrs = ['reference', 'points']

    count = CBashGeneric(5, c_ushort)

    def create_pgrp(self):
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 6, 0, 0, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, 6, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return PGRP(self._CollectionID, self._ModID, self._RecordID, 6, length)
    pgrp = CBashLIST(6, PGRP)
    pgrp_list = CBashLIST(6, PGRP, True)

    pgag_p = CBashUINT8ARRAY(7)
    pgrr_p = CBashUINT8ARRAY(8)

    def create_pgri(self):
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 9, 0, 0, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, 9, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return self.PGRI(self._CollectionID, self._ModID, self._RecordID, 9, length)
    pgri = CBashLIST(9, PGRI)
    pgri_list = CBashLIST(9, PGRI, True)

    def create_pgrl(self):
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 10, 0, 0, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, 10, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return self.PGRL(self._CollectionID, self._ModID, self._RecordID, 10, length)
    pgrl = CBashLIST(10, PGRL)
    pgrl_list = CBashLIST(10, PGRL, True)

    copyattrs = ObBaseRecord.baseattrs + ['count', 'pgrp_list', 'pgag_p', 'pgrr_p',
                                        'pgri_list', 'pgrl_list']
    exportattrs = ObBaseRecord.baseattrs + ['count', 'pgrp_list',
                                        'pgri_list', 'pgrl_list'] # 'pgag_p', 'pgrr_p',

class ObROADRecord(ObBaseRecord):
    def __init__(self, CollectionIndex, ModID, RecordID, ParentID=0, CopyFlags=0):
        ObBaseRecord.__init__(self, CollectionIndex, ModID, RecordID, ParentID, CopyFlags)
        self._ParentID = ParentID

    _Type = 'ROAD'
    class PGRR(ListComponent):
        x = CBashFLOAT32_LIST(1)
        y = CBashFLOAT32_LIST(2)
        z = CBashFLOAT32_LIST(3)
        exportattrs = copyattrs = ['x', 'y', 'z']

    def create_pgrp(self):
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 5, 0, 0, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, 5, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return PGRP(self._CollectionID, self._ModID, self._RecordID, 5, length)
    pgrp = CBashLIST(5, PGRP)
    pgrp_list = CBashLIST(5, PGRP, True)

    def create_pgrr(self):
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 6, 0, 0, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, 6, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return self.PGRR(self._CollectionID, self._ModID, self._RecordID, 6, length)
    pgrr = CBashLIST(6, PGRR)
    pgrr_list = CBashLIST(6, PGRR, True)

    exportattrs = copyattrs = ObBaseRecord.baseattrs + ['pgrp_list', 'pgrr_list']

class ObACTIRecord(ObBaseRecord):
    _Type = 'ACTI'
    full = CBashSTRING(5)
    modPath = CBashISTRING(6)
    modb = CBashFLOAT32(7)
    modt_p = CBashUINT8ARRAY(8)
    script = CBashFORMID(9)
    sound = CBashFORMID(10)
    copyattrs = ObBaseRecord.baseattrs + ['full', 'modPath', 'modb', 'modt_p', 'script',
                                        'sound']
    exportattrs = ObBaseRecord.baseattrs + ['full', 'modPath', 'modb', 'script', 'sound'] #'modt_p',

class ObALCHRecord(ObBaseRecord):
    _Type = 'ALCH'
    full = CBashSTRING(5)
    modPath = CBashISTRING(6)
    modb = CBashFLOAT32(7)
    modt_p = CBashUINT8ARRAY(8)
    iconPath = CBashISTRING(9)
    script = CBashFORMID(10)
    weight = CBashFLOAT32(11)
    value = CBashGeneric(12, c_long)
    flags = CBashGeneric(13, c_ubyte)
    unused1 = CBashUINT8ARRAY(14, 3)

    def create_effect(self):
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 15, 0, 0, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, 15, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return Effect(self._CollectionID, self._ModID, self._RecordID, 15, length)
    effects = CBashLIST(15, Effect)
    effects_list = CBashLIST(15, Effect, True)

    IsNoAutoCalc = CBashBasicFlag('flags', 0x00000001)
    IsFood = CBashBasicFlag('flags', 0x00000002)
    ##OBME Fields. Setting any of the below fields will make the mod require JRoush's OBME plugin for OBSE
    ##To see if OBME is in use, check the recordVersion field for a non-None value
    recordVersion = CBashGeneric(16, c_ubyte) #OBME
    betaVersion = CBashGeneric(17, c_ubyte) #OBME
    minorVersion = CBashGeneric(18, c_ubyte) #OBME
    majorVersion = CBashGeneric(19, c_ubyte) #OBME
    reserved = CBashUINT8ARRAY(20, 0x1C) #OBME
    datx_p = CBashUINT8ARRAY(21, 0x20) #OBME
    copyattrs = ObBaseRecord.baseattrs + ['full', 'modPath', 'modb', 'modt_p',
                                        'iconPath', 'script', 'weight',
                                        'value', 'flags', 'effects_list']
    exportattrs = ObBaseRecord.baseattrs + ['full', 'modPath', 'modb',
                                        'iconPath', 'script', 'weight',
                                        'value', 'flags', 'effects_list'] # 'modt_p',
    copyattrsOBME = copyattrs + ['recordVersion', 'betaVersion',
                                 'minorVersion', 'majorVersion',
                                 'reserved'] #, 'datx_p'

class ObAMMORecord(ObBaseRecord):
    _Type = 'AMMO'
    full = CBashSTRING(5)
    modPath = CBashISTRING(6)
    modb = CBashFLOAT32(7)
    modt_p = CBashUINT8ARRAY(8)
    iconPath = CBashISTRING(9)
    enchantment = CBashFORMID(10)
    enchantPoints = CBashGeneric(11, c_ushort)
    speed = CBashFLOAT32(12)
    flags = CBashGeneric(13, c_ubyte)
    unused1 = CBashUINT8ARRAY(14, 3)
    value = CBashGeneric(15, c_ulong)
    weight = CBashFLOAT32(16)
    damage = CBashGeneric(17, c_ushort)
    IsNotNormal = CBashBasicFlag('flags', 0x00000001)
    IsNotNormalWeapon = CBashAlias('IsNotNormal')
    IsNormal = CBashInvertedFlag('IsNotNormal')
    IsNormalWeapon = CBashAlias('IsNormal')
    copyattrs = ObBaseRecord.baseattrs + ['full', 'modPath', 'modb', 'modt_p',
                                        'iconPath', 'enchantment',
                                        'enchantPoints', 'speed', 'flags',
                                        'value', 'weight', 'damage']

    exportattrs = ObBaseRecord.baseattrs + ['full', 'modPath', 'modb',
                                        'iconPath', 'enchantment',
                                        'enchantPoints', 'speed', 'flags',
                                        'value', 'weight', 'damage'] # 'modt_p',

class ObANIORecord(ObBaseRecord):
    _Type = 'ANIO'
    modPath = CBashISTRING(5)
    modb = CBashFLOAT32(6)
    modt_p = CBashUINT8ARRAY(7)
    animationId = CBashFORMID(8)
    copyattrs = ObBaseRecord.baseattrs + ['modPath', 'modb', 'modt_p', 'animationId']
    exportattrs = ObBaseRecord.baseattrs + ['modPath', 'modb', 'animationId'] #'modt_p',

class ObAPPARecord(ObBaseRecord):
    _Type = 'APPA'
    full = CBashSTRING(5)
    modPath = CBashISTRING(6)
    modb = CBashFLOAT32(7)
    modt_p = CBashUINT8ARRAY(8)
    iconPath = CBashISTRING(9)
    script = CBashFORMID(10)
    apparatusType = CBashGeneric(11, c_ubyte)
    value = CBashGeneric(12, c_ulong)
    weight = CBashFLOAT32(13)
    quality = CBashFLOAT32(14)
    IsMortarPestle = CBashBasicType('apparatus', 0, 'IsAlembic')
    IsAlembic = CBashBasicType('apparatus', 1, 'IsMortarPestle')
    IsCalcinator = CBashBasicType('apparatus', 2, 'IsMortarPestle')
    IsRetort = CBashBasicType('apparatus', 3, 'IsMortarPestle')
    copyattrs = ObBaseRecord.baseattrs + ['full', 'modPath', 'modb', 'modt_p',
                                        'iconPath', 'script', 'apparatusType',
                                        'value', 'weight', 'quality']
    exportattrs = ObBaseRecord.baseattrs + ['full', 'modPath', 'modb',
                                        'iconPath', 'script', 'apparatusType',
                                        'value', 'weight', 'quality'] # 'modt_p',

class ObARMORecord(ObBaseRecord):
    _Type = 'ARMO'
    full = CBashSTRING(5)
    script = CBashFORMID(6)
    enchantment = CBashFORMID(7)
    enchantPoints = CBashGeneric(8, c_ushort)
    flags = CBashGeneric(9, c_ulong)
    maleBody = CBashGrouped(10, Model)
    maleBody_list = CBashGrouped(10, Model, True)

    maleWorld = CBashGrouped(13, Model)
    maleWorld_list = CBashGrouped(13, Model, True)

    maleIconPath = CBashISTRING(16)
    femaleBody = CBashGrouped(17, Model)
    femaleBody_list = CBashGrouped(17, Model, True)

    femaleWorld = CBashGrouped(20, Model)
    femaleWorld_list = CBashGrouped(20, Model, True)

    femaleIconPath = CBashISTRING(23)
    strength = CBashGeneric(24, c_ushort)
    value = CBashGeneric(25, c_ulong)
    health = CBashGeneric(26, c_ulong)
    weight = CBashFLOAT32(27)
    IsHead = CBashBasicFlag('flags', 0x00000001)
    IsHair = CBashBasicFlag('flags', 0x00000002)
    IsUpperBody = CBashBasicFlag('flags', 0x00000004)
    IsLowerBody = CBashBasicFlag('flags', 0x00000008)
    IsHand = CBashBasicFlag('flags', 0x00000010)
    IsFoot = CBashBasicFlag('flags', 0x00000020)
    IsRightRing = CBashBasicFlag('flags', 0x00000040)
    IsLeftRing = CBashBasicFlag('flags', 0x00000080)
    IsAmulet = CBashBasicFlag('flags', 0x00000100)
    IsWeapon = CBashBasicFlag('flags', 0x00000200)
    IsBackWeapon = CBashBasicFlag('flags', 0x00000400)
    IsSideWeapon = CBashBasicFlag('flags', 0x00000800)
    IsQuiver = CBashBasicFlag('flags', 0x00001000)
    IsShield = CBashBasicFlag('flags', 0x00002000)
    IsTorch = CBashBasicFlag('flags', 0x00004000)
    IsTail = CBashBasicFlag('flags', 0x00008000)
    IsHideRings = CBashBasicFlag('flags', 0x00010000)
    IsHideAmulets = CBashBasicFlag('flags', 0x00020000)
    IsNonPlayable = CBashBasicFlag('flags', 0x00400000)
    IsPlayable = CBashInvertedFlag('IsNonPlayable')
    IsHeavyArmor = CBashBasicFlag('flags', 0x00800000)
    exportattrs = copyattrs = ObBaseRecord.baseattrs + ['full', 'script', 'enchantment', 'enchantPoints',
                                        'flags', 'maleBody_list', 'maleWorld_list', 'maleIconPath',
                                        'femaleBody_list', 'femaleWorld_list', 'femaleIconPath',
                                        'strength', 'value', 'health', 'weight']

class ObBOOKRecord(ObBaseRecord):
    _Type = 'BOOK'
    full = CBashSTRING(5)
    modPath = CBashISTRING(6)
    modb = CBashFLOAT32(7)
    modt_p = CBashUINT8ARRAY(8)
    iconPath = CBashISTRING(9)
    text = CBashSTRING(10)
    script = CBashFORMID(11)
    enchantment = CBashFORMID(12)
    enchantPoints = CBashGeneric(13, c_ushort)
    flags = CBashGeneric(14, c_ubyte)
    teaches = CBashGeneric(15, c_byte)
    value = CBashGeneric(16, c_ulong)
    weight = CBashFLOAT32(17)
    IsScroll = CBashBasicFlag('flags', 0x00000001)
    IsFixed = CBashBasicFlag('flags', 0x00000002)
    IsCantBeTaken = CBashAlias('IsFixed')
    copyattrs = ObBaseRecord.baseattrs + ['full', 'modPath', 'modb', 'modt_p',
                                        'iconPath', 'text', 'script',
                                        'enchantment', 'enchantPoints',
                                        'flags', 'teaches', 'value', 'weight']
    exportattrs = ObBaseRecord.baseattrs + ['full', 'modPath', 'modb',
                                        'iconPath', 'text', 'script',
                                        'enchantment', 'enchantPoints',
                                        'flags', 'teaches', 'value', 'weight'] # 'modt_p',

class ObBSGNRecord(ObBaseRecord):
    _Type = 'BSGN'
    full = CBashSTRING(5)
    iconPath = CBashISTRING(6)
    text = CBashSTRING(7)
    spells = CBashFORMIDARRAY(8)
    exportattrs = copyattrs = ObBaseRecord.baseattrs + ['full', 'iconPath', 'text', 'spells']

class ObCELLRecord(ObBaseRecord):
    _Type = 'CELL'
    def __init__(self, CollectionIndex, ModID, RecordID, ParentID=0, CopyFlags=4):
        ##Record Creation Flags
        ##SetAsOverride       = 0x00000001,
        ##SetAsWorldCell      = 0x00000002,
        ##CopyWorldCellStatus = 0x00000004
        ObBaseRecord.__init__(self, CollectionIndex, ModID, RecordID, ParentID, CopyFlags)

    @property
    def _ParentID(self):
        _CGetField.restype = c_ulong
        retValue = _CGetField(self._CollectionID, self._ModID, self._RecordID, 40, 0, 0, 0, 0, 0, 0, 0)
        if(retValue): return retValue
        return 0

    full = CBashSTRING(5)
    flags = CBashGeneric(6, c_ubyte)
    ambientRed = CBashGeneric(7, c_ubyte)
    ambientGreen = CBashGeneric(8, c_ubyte)
    ambientBlue = CBashGeneric(9, c_ubyte)
    unused1 = CBashUINT8ARRAY(10, 1)
    directionalRed = CBashGeneric(11, c_ubyte)
    directionalGreen = CBashGeneric(12, c_ubyte)
    directionalBlue = CBashGeneric(13, c_ubyte)
    unused2 = CBashUINT8ARRAY(14, 1)
    fogRed = CBashGeneric(15, c_ubyte)
    fogGreen = CBashGeneric(16, c_ubyte)
    fogBlue = CBashGeneric(17, c_ubyte)
    unused3 = CBashUINT8ARRAY(18, 1)
    fogNear = CBashFLOAT32(19)
    fogFar = CBashFLOAT32(20)
    directionalXY = CBashGeneric(21, c_long)
    directionalZ = CBashGeneric(22, c_long)
    directionalFade = CBashFLOAT32(23)
    fogClip = CBashFLOAT32(24)
    musicType = CBashGeneric(25, c_ubyte)
    owner = CBashFORMID(26)
    rank = CBashGeneric(27, c_long)
    globalVariable = CBashFORMID(28)
    climate = CBashFORMID(29)
    waterHeight = CBashFLOAT32(30)
    regions = CBashFORMIDARRAY(31)
    posX = CBashSINT32_OR_UNKNOWN(32)
    posY = CBashSINT32_OR_UNKNOWN(33)
    water = CBashFORMID(34)
    def create_ACHR(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("ACHR", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, self._RecordID, 0)
        if(RecordID): return ObACHRRecord(self._CollectionID, self._ModID, RecordID, self._RecordID, 0)
        return None
    ACHR = CBashSUBRECORDARRAY(35, ObACHRRecord, "ACHR", 0)

    def create_ACRE(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("ACRE", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, self._RecordID, 0)
        if(RecordID): return ObACRERecord(self._CollectionID, self._ModID, RecordID, self._RecordID, 0)
        return None
    ACRE = CBashSUBRECORDARRAY(36, ObACRERecord, "ACRE", 0)

    def create_REFR(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("REFR", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, self._RecordID, 0)
        if(RecordID): return ObREFRRecord(self._CollectionID, self._ModID, RecordID, self._RecordID, 0)
        return None
    REFR = CBashSUBRECORDARRAY(37, ObREFRRecord, "REFR", 0)

    def create_PGRD(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("PGRD", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, self._RecordID, 0)
        if(RecordID): return ObPGRDRecord(self._CollectionID, self._ModID, RecordID, self._RecordID, 0)
        return None
    PGRD = CBashSUBRECORD(38, ObPGRDRecord, "PGRD", 0)

    def create_LAND(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("LAND", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, self._RecordID, 0)
        if(RecordID): return ObLANDRecord(self._CollectionID, self._ModID, RecordID, self._RecordID, 0)
        return None
    LAND = CBashSUBRECORD(39, ObLANDRecord, "LAND", 0)

    IsInterior = CBashBasicFlag('flags', 0x00000001)
    IsHasWater = CBashBasicFlag('flags', 0x00000002)
    IsInvertFastTravel = CBashBasicFlag('flags', 0x00000004)
    IsForceHideLand = CBashBasicFlag('flags', 0x00000008)
    IsPublicPlace = CBashBasicFlag('flags', 0x00000020)
    IsHandChanged = CBashBasicFlag('flags', 0x00000040)
    IsBehaveLikeExterior = CBashBasicFlag('flags', 0x00000080)
    IsDefault = CBashBasicType('music', 0, 'IsPublic')
    IsPublic = CBashBasicType('music', 1, 'IsDefault')
    IsDungeon = CBashBasicType('music', 2, 'IsDefault')
    exportattrs = copyattrs = ObBaseRecord.baseattrs + ['full', 'flags', 'ambientRed', 'ambientGreen', 'ambientBlue',
                                        'directionalRed', 'directionalGreen', 'directionalBlue',
                                        'fogRed', 'fogGreen', 'fogBlue', 'fogNear', 'fogFar',
                                        'directionalXY', 'directionalZ', 'directionalFade', 'fogClip',
                                        'musicType', 'owner', 'rank', 'globalVariable',
                                        'climate', 'waterHeight', 'regions', 'posX', 'posY',
                                        'water']

class ObCLASRecord(ObBaseRecord):
    _Type = 'CLAS'
    full = CBashSTRING(5)
    description = CBashSTRING(6)
    iconPath = CBashISTRING(7)
    primary1 = CBashGeneric(8, c_long)
    primary2 = CBashGeneric(9, c_long)
    specialization = CBashGeneric(10, c_ulong)
    major1 = CBashGeneric(11, c_long)
    major2 = CBashGeneric(12, c_long)
    major3 = CBashGeneric(13, c_long)
    major4 = CBashGeneric(14, c_long)
    major5 = CBashGeneric(15, c_long)
    major6 = CBashGeneric(16, c_long)
    major7 = CBashGeneric(17, c_long)
    flags = CBashGeneric(18, c_ulong)
    services = CBashGeneric(19, c_ulong)
    trainSkill = CBashGeneric(20, c_byte)
    trainLevel = CBashGeneric(21, c_ubyte)
    unused1 = CBashUINT8ARRAY(22, 2)
    IsPlayable = CBashBasicFlag('flags', 0x00000001)
    IsGuard = CBashBasicFlag('flags', 0x00000002)
    IsServicesWeapons = CBashBasicFlag('services', 0x00000001)
    IsServicesArmor = CBashBasicFlag('services', 0x00000002)
    IsServicesClothing = CBashBasicFlag('services', 0x00000004)
    IsServicesBooks = CBashBasicFlag('services', 0x00000008)
    IsServicesIngredients = CBashBasicFlag('services', 0x00000010)
    IsServicesLights = CBashBasicFlag('services', 0x00000080)
    IsServicesApparatus = CBashBasicFlag('services', 0x00000100)
    IsServicesMiscItems = CBashBasicFlag('services', 0x00000400)
    IsServicesSpells = CBashBasicFlag('services', 0x00000800)
    IsServicesMagicItems = CBashBasicFlag('services', 0x00001000)
    IsServicesPotions = CBashBasicFlag('services', 0x00002000)
    IsServicesTraining = CBashBasicFlag('services', 0x00004000)
    IsServicesRecharge = CBashBasicFlag('services', 0x00010000)
    IsServicesRepair = CBashBasicFlag('services', 0x00020000)
    exportattrs = copyattrs = ObBaseRecord.baseattrs + ['full', 'description', 'iconPath', 'primary1',
                                        'primary2', 'specialization', 'major1',
                                        'major2', 'major3', 'major4', 'major5',
                                        'major6', 'major7', 'flags', 'services',
                                        'trainSkill', 'trainLevel']

class ObCLMTRecord(ObBaseRecord):
    _Type = 'CLMT'
    class Weather(ListComponent):
        weather = CBashFORMID_LIST(1)
        chance = CBashGeneric_LIST(2, c_long)
        copyattrs = ['weather', 'chance']

    def create_weather(self):
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 5, 0, 0, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, 5, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return self.Weather(self._CollectionID, self._ModID, self._RecordID, 5, length)
    weathers = CBashLIST(5, Weather)
    weathers_list = CBashLIST(5, Weather, True)

    sunPath = CBashISTRING(6)
    glarePath = CBashISTRING(7)
    modPath = CBashISTRING(8)
    modb = CBashFLOAT32(9)
    modt_p = CBashUINT8ARRAY(10)
    riseBegin = CBashGeneric(11, c_ubyte)
    riseEnd = CBashGeneric(12, c_ubyte)
    setBegin = CBashGeneric(13, c_ubyte)
    setEnd = CBashGeneric(14, c_ubyte)
    volatility = CBashGeneric(15, c_ubyte)
    phaseLength = CBashGeneric(16, c_ubyte)
    copyattrs = ObBaseRecord.baseattrs + ['weathers_list', 'sunPath', 'glarePath', 'modPath',
                                        'modb', 'modt_p', 'riseBegin', 'riseEnd',
                                        'setBegin', 'setEnd', 'volatility', 'phaseLength']
    exportattrs = ObBaseRecord.baseattrs + ['weathers_list', 'sunPath', 'glarePath', 'modPath',
                                        'modb', 'riseBegin', 'riseEnd',
                                        'setBegin', 'setEnd', 'volatility', 'phaseLength'] #'modt_p',

class ObCLOTRecord(ObBaseRecord):
    _Type = 'CLOT'
    full = CBashSTRING(5)
    script = CBashFORMID(6)
    enchantment = CBashFORMID(7)
    enchantPoints = CBashGeneric(8, c_ushort)
    flags = CBashGeneric(9, c_ulong)
    maleBody = CBashGrouped(10, Model)
    maleBody_list = CBashGrouped(10, Model, True)

    maleWorld = CBashGrouped(13, Model)
    maleWorld_list = CBashGrouped(13, Model, True)

    maleIconPath = CBashISTRING(16)
    femaleBody = CBashGrouped(17, Model)
    femaleBody_list = CBashGrouped(17, Model, True)

    femaleWorld = CBashGrouped(20, Model)
    femaleWorld_list = CBashGrouped(20, Model, True)

    femaleIconPath = CBashISTRING(23)
    value = CBashGeneric(24, c_ulong)
    weight = CBashFLOAT32(25)
    IsHead = CBashBasicFlag('flags', 0x00000001)
    IsHair = CBashBasicFlag('flags', 0x00000002)
    IsUpperBody = CBashBasicFlag('flags', 0x00000004)
    IsLowerBody = CBashBasicFlag('flags', 0x00000008)
    IsHand = CBashBasicFlag('flags', 0x00000010)
    IsFoot = CBashBasicFlag('flags', 0x00000020)
    IsRightRing = CBashBasicFlag('flags', 0x00000040)
    IsLeftRing = CBashBasicFlag('flags', 0x00000080)
    IsAmulet = CBashBasicFlag('flags', 0x00000100)
    IsWeapon = CBashBasicFlag('flags', 0x00000200)
    IsBackWeapon = CBashBasicFlag('flags', 0x00000400)
    IsSideWeapon = CBashBasicFlag('flags', 0x00000800)
    IsQuiver = CBashBasicFlag('flags', 0x00001000)
    IsShield = CBashBasicFlag('flags', 0x00002000)
    IsTorch = CBashBasicFlag('flags', 0x00004000)
    IsTail = CBashBasicFlag('flags', 0x00008000)
    IsHideRings = CBashBasicFlag('flags', 0x00010000)
    IsHideAmulets = CBashBasicFlag('flags', 0x00020000)
    IsNonPlayable = CBashBasicFlag('flags', 0x00400000)
    IsPlayable = CBashInvertedFlag('IsNonPlayable')
    copyattrs = ObBaseRecord.baseattrs + ['full', 'script', 'enchantment',
                                        'enchantPoints', 'flags', 'maleBody_list', 'maleWorld_list',
                                        'maleIconPath', 'femaleBody_list', 'femaleWorld_list',
                                        'femaleIconPath', 'value', 'weight']
    exportattrs = ObBaseRecord.baseattrs + ['full', 'script', 'enchantment',
                                        'enchantPoints', 'flags', 'maleBody', 'maleWorld',
                                        'maleIconPath', 'femaleBody', 'femaleWorld',
                                        'femaleIconPath', 'value', 'weight']

class ObCONTRecord(ObBaseRecord):
    _Type = 'CONT'
    def mergeFilter(self,modSet):
        """Filter out items that don't come from specified modSet.
        Filters items."""
        self.items = [x for x in self.items if x.item[0] in modSet]

    full = CBashSTRING(5)
    modPath = CBashISTRING(6)
    modb = CBashFLOAT32(7)
    modt_p = CBashUINT8ARRAY(8)
    script = CBashFORMID(9)

    def create_item(self):
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 10, 0, 0, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, 10, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return Item(self._CollectionID, self._ModID, self._RecordID, 10, length)
    items = CBashLIST(10, Item)
    items_list = CBashLIST(10, Item, True)

    flags = CBashGeneric(11, c_ubyte)
    weight = CBashFLOAT32(12)
    soundOpen = CBashFORMID(13)
    soundClose = CBashFORMID(14)
    IsRespawn = CBashBasicFlag('flags', 0x00000001)
    copyattrs = ObBaseRecord.baseattrs + ['full', 'modPath', 'modb', 'modt_p',
                                        'script', 'items_list', 'flags', 'weight',
                                        'soundOpen', 'soundClose']

    exportattrs = ObBaseRecord.baseattrs + ['full', 'modPath', 'modb',
                                        'script', 'items_list', 'flags', 'weight',
                                        'soundOpen', 'soundClose'] # 'modt_p',

class ObCREARecord(ObBaseRecord):
    _Type = 'CREA'
    def mergeFilter(self,modSet):
        """Filter out items that don't come from specified modSet.
        Filters spells, factions and items."""
        self.spells = [x for x in self.spells if x[0] in modSet]
        self.factions = [x for x in self.factions if x.faction[0] in modSet]
        self.items = [x for x in self.items if x.item[0] in modSet]

    class Sound(ListComponent):
        soundType = CBashGeneric_LIST(1, c_ulong)
        sound = CBashFORMID_LIST(2)
        chance = CBashGeneric_LIST(3, c_ubyte)
        IsLeftFoot = CBashBasicType('soundType', 0, 'IsRightFoot')
        IsRightFoot = CBashBasicType('soundType', 1, 'IsLeftFoot')
        IsLeftBackFoot = CBashBasicType('soundType', 2, 'IsLeftFoot')
        IsRightBackFoot = CBashBasicType('soundType', 3, 'IsLeftFoot')
        IsIdle = CBashBasicType('soundType', 4, 'IsLeftFoot')
        IsAware = CBashBasicType('soundType', 5, 'IsLeftFoot')
        IsAttack = CBashBasicType('soundType', 6, 'IsLeftFoot')
        IsHit = CBashBasicType('soundType', 7, 'IsLeftFoot')
        IsDeath = CBashBasicType('soundType', 8, 'IsLeftFoot')
        IsWeapon = CBashBasicType('soundType', 9, 'IsLeftFoot')
        exportattrs = copyattrs = ['soundType', 'sound', 'chance']

    full = CBashSTRING(5)
    modPath = CBashISTRING(6)
    modb = CBashFLOAT32(7)
    modt_p = CBashUINT8ARRAY(8)
    spells = CBashFORMIDARRAY(9)
    bodyParts = CBashISTRINGARRAY(10)
    nift_p = CBashUINT8ARRAY(11)
    flags = CBashGeneric(12, c_ulong)
    baseSpell = CBashGeneric(13, c_ushort)
    fatigue = CBashGeneric(14, c_ushort)
    barterGold = CBashGeneric(15, c_ushort)
    level = CBashGeneric(16, c_short)
    calcMin = CBashGeneric(17, c_ushort)
    calcMax = CBashGeneric(18, c_ushort)

    def create_faction(self):
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 19, 0, 0, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, 19, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return Faction(self._CollectionID, self._ModID, self._RecordID, 19, length)
    factions = CBashLIST(19, Faction)
    factions_list = CBashLIST(19, Faction, True)

    deathItem = CBashFORMID(20)
    script = CBashFORMID(21)

    def create_item(self):
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 22, 0, 0, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, 22, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return Item(self._CollectionID, self._ModID, self._RecordID, 22, length)
    items = CBashLIST(22, Item)
    items_list = CBashLIST(22, Item, True)

    aggression = CBashGeneric(23, c_ubyte)
    confidence = CBashGeneric(24, c_ubyte)
    energyLevel = CBashGeneric(25, c_ubyte)
    responsibility = CBashGeneric(26, c_ubyte)
    services = CBashGeneric(27, c_ulong)
    trainSkill = CBashGeneric(28, c_byte)
    trainLevel = CBashGeneric(29, c_ubyte)
    unused1 = CBashUINT8ARRAY(30, 2)
    aiPackages = CBashFORMIDARRAY(31)
    animations = CBashISTRINGARRAY(32)
    creatureType = CBashGeneric(33, c_ubyte)
    combat = CBashGeneric(34, c_ubyte)
    magic = CBashGeneric(35, c_ubyte)
    stealth = CBashGeneric(36, c_ubyte)
    soulType = CBashGeneric(37, c_ubyte)
    unused2 = CBashUINT8ARRAY(38, 1)
    health = CBashGeneric(39, c_ushort)
    unused3 = CBashUINT8ARRAY(40, 2)
    attackDamage = CBashGeneric(41, c_ushort)
    strength = CBashGeneric(42, c_ubyte)
    intelligence = CBashGeneric(43, c_ubyte)
    willpower = CBashGeneric(44, c_ubyte)
    agility = CBashGeneric(45, c_ubyte)
    speed = CBashGeneric(46, c_ubyte)
    endurance = CBashGeneric(47, c_ubyte)
    personality = CBashGeneric(48, c_ubyte)
    luck = CBashGeneric(49, c_ubyte)
    attackReach = CBashGeneric(50, c_ubyte)
    combatStyle = CBashFORMID(51)
    turningSpeed = CBashFLOAT32(52)
    baseScale = CBashFLOAT32(53)
    footWeight = CBashFLOAT32(54)
    inheritsSoundsFrom = CBashFORMID(55)
    bloodSprayPath = CBashISTRING(56)
    bloodDecalPath = CBashISTRING(57)

    def create_sound(self):
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 58, 0, 0, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, 58, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return self.Sound(self._CollectionID, self._ModID, self._RecordID, 58, length)
    sounds = CBashLIST(58, Sound)
    sounds_list = CBashLIST(58, Sound, True)

    IsBiped = CBashBasicFlag('flags', 0x00000001)
    IsEssential = CBashBasicFlag('flags', 0x00000002)
    IsWeaponAndShield = CBashBasicFlag('flags', 0x00000004)
    IsRespawn = CBashBasicFlag('flags', 0x00000008)
    IsSwims = CBashBasicFlag('flags', 0x00000010)
    IsFlies = CBashBasicFlag('flags', 0x00000020)
    IsWalks = CBashBasicFlag('flags', 0x00000040)
    IsPCLevelOffset = CBashBasicFlag('flags', 0x00000080)
    IsNoLowLevel = CBashBasicFlag('flags', 0x00000200)
    IsLowLevel = CBashInvertedFlag('IsNoLowLevel')
    IsNoBloodSpray = CBashBasicFlag('flags', 0x00000800)
    IsBloodSpray = CBashInvertedFlag('IsNoBloodSpray')
    IsNoBloodDecal = CBashBasicFlag('flags', 0x00001000)
    IsBloodDecal = CBashInvertedFlag('IsNoBloodDecal')
    IsSummonable = CBashBasicFlag('flags', 0x00004000)
    IsNoHead = CBashBasicFlag('flags', 0x00008000)
    IsHead = CBashInvertedFlag('IsNoHead')
    IsNoRightArm = CBashBasicFlag('flags', 0x00010000)
    IsRightArm = CBashInvertedFlag('IsNoRightArm')
    IsNoLeftArm = CBashBasicFlag('flags', 0x00020000)
    IsLeftArm = CBashInvertedFlag('IsNoLeftArm')
    IsNoCombatInWater = CBashBasicFlag('flags', 0x00040000)
    IsCombatInWater = CBashInvertedFlag('IsNoCombatInWater')
    IsNoShadow = CBashBasicFlag('flags', 0x00080000)
    IsShadow = CBashInvertedFlag('IsNoShadow')
    IsNoCorpseCheck = CBashBasicFlag('flags', 0x00100000)
    IsCorpseCheck = CBashInvertedFlag('IsNoCorpseCheck')
    IsServicesWeapons = CBashBasicFlag('services', 0x00000001)
    IsServicesArmor = CBashBasicFlag('services', 0x00000002)
    IsServicesClothing = CBashBasicFlag('services', 0x00000004)
    IsServicesBooks = CBashBasicFlag('services', 0x00000008)
    IsServicesIngredients = CBashBasicFlag('services', 0x00000010)
    IsServicesLights = CBashBasicFlag('services', 0x00000080)
    IsServicesApparatus = CBashBasicFlag('services', 0x00000100)
    IsServicesMiscItems = CBashBasicFlag('services', 0x00000400)
    IsServicesSpells = CBashBasicFlag('services', 0x00000800)
    IsServicesMagicItems = CBashBasicFlag('services', 0x00001000)
    IsServicesPotions = CBashBasicFlag('services', 0x00002000)
    IsServicesTraining = CBashBasicFlag('services', 0x00004000)
    IsServicesRecharge = CBashBasicFlag('services', 0x00010000)
    IsServicesRepair = CBashBasicFlag('services', 0x00020000)
    IsCreature = CBashBasicType('creatureType', 0, 'IsDaedra')
    IsDaedra = CBashBasicType('creatureType', 1, 'IsCreature')
    IsUndead = CBashBasicType('creatureType', 2, 'IsCreature')
    IsHumanoid = CBashBasicType('creatureType', 3, 'IsCreature')
    IsHorse = CBashBasicType('creatureType', 4, 'IsCreature')
    IsGiant = CBashBasicType('creatureType', 5, 'IsCreature')
    IsNoSoul = CBashBasicType('soulType', 0, 'IsPettySoul')
    IsPettySoul = CBashBasicType('soulType', 1, 'IsNoSoul')
    IsLesserSoul = CBashBasicType('soulType', 2, 'IsNoSoul')
    IsCommonSoul = CBashBasicType('soulType', 3, 'IsNoSoul')
    IsGreaterSoul = CBashBasicType('soulType', 4, 'IsNoSoul')
    IsGrandSoul = CBashBasicType('soulType', 5, 'IsNoSoul')
    copyattrs = ObBaseRecord.baseattrs + ['full', 'modPath', 'modb', 'modt_p', 'spells',
                                        'bodyParts', 'nift_p', 'flags', 'baseSpell',
                                        'fatigue', 'barterGold', 'level', 'calcMin',
                                        'calcMax', 'factions_list', 'deathItem',
                                        'script', 'items_list', 'aggression', 'confidence',
                                        'energyLevel', 'responsibility', 'services',
                                        'trainSkill', 'trainLevel', 'aiPackages',
                                        'animations', 'creatureType', 'combat', 'magic',
                                        'stealth', 'soulType', 'health', 'attackDamage',
                                        'strength', 'intelligence', 'willpower', 'agility',
                                        'speed', 'endurance', 'personality', 'luck',
                                        'attackReach', 'combatStyle', 'turningSpeed',
                                        'baseScale', 'footWeight',
                                        'inheritsSoundsFrom', 'bloodSprayPath',
                                        'bloodDecalPath', 'sounds_list']
    exportattrs = ObBaseRecord.baseattrs + ['full', 'modPath', 'modb', 'spells',
                                        'bodyParts', 'flags', 'baseSpell',
                                        'fatigue', 'barterGold', 'level', 'calcMin',
                                        'calcMax', 'factions_list', 'deathItem',
                                        'script', 'items_list', 'aggression', 'confidence',
                                        'energyLevel', 'responsibility', 'services',
                                        'trainSkill', 'trainLevel', 'aiPackages',
                                        'animations', 'creatureType', 'combat', 'magic',
                                        'stealth', 'soulType', 'health', 'attackDamage',
                                        'strength', 'intelligence', 'willpower', 'agility',
                                        'speed', 'endurance', 'personality', 'luck',
                                        'attackReach', 'combatStyle', 'turningSpeed',
                                        'baseScale', 'footWeight',
                                        'inheritsSoundsFrom', 'bloodSprayPath',
                                        'bloodDecalPath', 'sounds_list'] #'modt_p', 'nift_p',

class ObCSTYRecord(ObBaseRecord):
    _Type = 'CSTY'
    dodgeChance = CBashGeneric(5, c_ubyte)
    lrChance = CBashGeneric(6, c_ubyte)
    unused1 = CBashUINT8ARRAY(7, 2)
    lrTimerMin = CBashFLOAT32(8)
    lrTimerMax = CBashFLOAT32(9)
    forTimerMin = CBashFLOAT32(10)
    forTimerMax = CBashFLOAT32(11)
    backTimerMin = CBashFLOAT32(12)
    backTimerMax = CBashFLOAT32(13)
    idleTimerMin = CBashFLOAT32(14)
    idleTimerMax = CBashFLOAT32(15)
    blkChance = CBashGeneric(16, c_ubyte)
    atkChance = CBashGeneric(17, c_ubyte)
    unused2 = CBashUINT8ARRAY(18, 2)
    atkBRecoil = CBashFLOAT32(19)
    atkBUnc = CBashFLOAT32(20)
    atkBh2h = CBashFLOAT32(21)
    pAtkChance = CBashGeneric(22, c_ubyte)
    unused3 = CBashUINT8ARRAY(23, 3)
    pAtkBRecoil = CBashFLOAT32(24)
    pAtkBUnc = CBashFLOAT32(25)
    pAtkNormal = CBashGeneric(26, c_ubyte)
    pAtkFor = CBashGeneric(27, c_ubyte)
    pAtkBack = CBashGeneric(28, c_ubyte)
    pAtkL = CBashGeneric(29, c_ubyte)
    pAtkR = CBashGeneric(30, c_ubyte)
    unused4 = CBashUINT8ARRAY(31, 3)
    holdTimerMin = CBashFLOAT32(32)
    holdTimerMax = CBashFLOAT32(33)
    flagsA = CBashGeneric(34, c_ubyte)
    acroDodge = CBashGeneric(35, c_ubyte)
    unused5 = CBashUINT8ARRAY(36, 2)
    rMultOpt = CBashFLOAT32(37)
    rMultMax = CBashFLOAT32(38)
    mDistance = CBashFLOAT32(39)
    rDistance = CBashFLOAT32(40)
    buffStand = CBashFLOAT32(41)
    rStand = CBashFLOAT32(42)
    groupStand = CBashFLOAT32(43)
    rushChance = CBashGeneric(44, c_ubyte)
    unused6 = CBashUINT8ARRAY(45, 3)
    rushMult = CBashFLOAT32(46)
    flagsB = CBashGeneric(47, c_ulong)
    dodgeFMult = CBashFLOAT32(48)
    dodgeFBase = CBashFLOAT32(49)
    encSBase = CBashFLOAT32(50)
    encSMult = CBashFLOAT32(51)
    dodgeAtkMult = CBashFLOAT32(52)
    dodgeNAtkMult = CBashFLOAT32(53)
    dodgeBAtkMult = CBashFLOAT32(54)
    dodgeBNAtkMult = CBashFLOAT32(55)
    dodgeFAtkMult = CBashFLOAT32(56)
    dodgeFNAtkMult = CBashFLOAT32(57)
    blockMult = CBashFLOAT32(58)
    blockBase = CBashFLOAT32(59)
    blockAtkMult = CBashFLOAT32(60)
    blockNAtkMult = CBashFLOAT32(61)
    atkMult = CBashFLOAT32(62)
    atkBase = CBashFLOAT32(63)
    atkAtkMult = CBashFLOAT32(64)
    atkNAtkMult = CBashFLOAT32(65)
    atkBlockMult = CBashFLOAT32(66)
    pAtkFBase = CBashFLOAT32(67)
    pAtkFMult = CBashFLOAT32(68)
    IsUseAdvanced = CBashBasicFlag('flagsA', 0x00000001)
    IsUseChanceForAttack = CBashBasicFlag('flagsA', 0x00000002)
    IsIgnoreAllies = CBashBasicFlag('flagsA', 0x00000004)
    IsWillYield = CBashBasicFlag('flagsA', 0x00000008)
    IsRejectsYields = CBashBasicFlag('flagsA', 0x00000010)
    IsFleeingDisabled = CBashBasicFlag('flagsA', 0x00000020)
    IsPrefersRanged = CBashBasicFlag('flagsA', 0x00000040)
    IsMeleeAlertOK = CBashBasicFlag('flagsA', 0x00000080)
    IsDoNotAcquire = CBashBasicFlag('flagsB', 0x00000001)
    exportattrs = copyattrs = ObBaseRecord.baseattrs + ['dodgeChance', 'lrChance', 'lrTimerMin', 'lrTimerMax',
                                        'forTimerMin', 'forTimerMax', 'backTimerMin',
                                        'backTimerMax', 'idleTimerMin', 'idleTimerMax',
                                        'blkChance', 'atkChance', 'atkBRecoil', 'atkBUnc',
                                        'atkBh2h', 'pAtkChance', 'pAtkBRecoil', 'pAtkBUnc',
                                        'pAtkNormal', 'pAtkFor', 'pAtkBack', 'pAtkL', 'pAtkR',
                                        'holdTimerMin', 'holdTimerMax', 'flagsA', 'acroDodge',
                                        'rMultOpt', 'rMultMax', 'mDistance', 'rDistance',
                                        'buffStand', 'rStand', 'groupStand', 'rushChance',
                                        'rushMult', 'flagsB', 'dodgeFMult', 'dodgeFBase',
                                        'encSBase', 'encSMult', 'dodgeAtkMult', 'dodgeNAtkMult',
                                        'dodgeBAtkMult', 'dodgeBNAtkMult', 'dodgeFAtkMult',
                                        'dodgeFNAtkMult', 'blockMult', 'blockBase', 'blockAtkMult',
                                        'blockNAtkMult', 'atkMult', 'atkBase', 'atkAtkMult',
                                        'atkNAtkMult', 'atkBlockMult', 'pAtkFBase', 'pAtkFMult']

class ObDIALRecord(ObBaseRecord):
    _Type = 'DIAL'
    quests = CBashFORMIDARRAY(5)
    removedQuests = CBashFORMIDARRAY(6)
    full = CBashSTRING(7)
    dialType = CBashGeneric(8, c_ubyte)
    def create_INFO(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("INFO", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, self._RecordID, 0)
        if(RecordID): return ObINFORecord(self._CollectionID, self._ModID, RecordID, self._RecordID, 0)
        return None
    INFO = CBashSUBRECORDARRAY(9, ObINFORecord, "INFO", 0)

    IsTopic = CBashBasicType('dialType', 0, 'IsConversation')
    IsConversation = CBashBasicType('dialType', 1, 'IsTopic')
    IsCombat = CBashBasicType('dialType', 2, 'IsTopic')
    IsPersuasion = CBashBasicType('dialType', 3, 'IsTopic')
    IsDetection = CBashBasicType('dialType', 4, 'IsTopic')
    IsService = CBashBasicType('dialType', 5, 'IsTopic')
    IsMisc = CBashBasicType('dialType', 6, 'IsTopic')
    exportattrs = copyattrs = ObBaseRecord.baseattrs + ['quests', 'removedQuests',
                                        'full', 'dialType']

class ObDOORRecord(ObBaseRecord):
    _Type = 'DOOR'
    full = CBashSTRING(5)
    modPath = CBashISTRING(6)
    modb = CBashFLOAT32(7)
    modt_p = CBashUINT8ARRAY(8)
    script = CBashFORMID(9)
    soundOpen = CBashFORMID(10)
    soundClose = CBashFORMID(11)
    soundLoop = CBashFORMID(12)
    flags = CBashGeneric(13, c_ubyte)
    destinations = CBashFORMIDARRAY(14)
    IsOblivionGate = CBashBasicFlag('flags', 0x00000001)
    IsAutomatic = CBashBasicFlag('flags', 0x00000002)
    IsHidden = CBashBasicFlag('flags', 0x00000004)
    IsMinimalUse = CBashBasicFlag('flags', 0x00000008)
    copyattrs = ObBaseRecord.baseattrs + ['full', 'modPath', 'modb', 'modt_p',
                                        'script', 'soundOpen',
                                        'soundClose', 'soundLoop',
                                        'flags', 'destinations']
    exportattrs = ObBaseRecord.baseattrs + ['full', 'modPath', 'modb',
                                        'script', 'soundOpen',
                                        'soundClose', 'soundLoop',
                                        'flags', 'destinations'] # 'modt_p',

class ObEFSHRecord(ObBaseRecord):
    _Type = 'EFSH'
    fillTexturePath = CBashISTRING(5)
    particleTexturePath = CBashISTRING(6)
    flags = CBashGeneric(7, c_ubyte)
    unused1 = CBashUINT8ARRAY(8, 3)
    memSBlend = CBashGeneric(9, c_ulong)
    memBlendOp = CBashGeneric(10, c_ulong)
    memZFunc = CBashGeneric(11, c_ulong)
    fillRed = CBashGeneric(12, c_ubyte)
    fillGreen = CBashGeneric(13, c_ubyte)
    fillBlue = CBashGeneric(14, c_ubyte)
    unused2 = CBashUINT8ARRAY(15, 1)
    fillAIn = CBashFLOAT32(16)
    fillAFull = CBashFLOAT32(17)
    fillAOut = CBashFLOAT32(18)
    fillAPRatio = CBashFLOAT32(19)
    fillAAmp = CBashFLOAT32(20)
    fillAFreq = CBashFLOAT32(21)
    fillAnimSpdU = CBashFLOAT32(22)
    fillAnimSpdV = CBashFLOAT32(23)
    edgeOff = CBashFLOAT32(24)
    edgeRed = CBashGeneric(25, c_ubyte)
    edgeGreen = CBashGeneric(26, c_ubyte)
    edgeBlue = CBashGeneric(27, c_ubyte)
    unused3 = CBashUINT8ARRAY(28, 1)
    edgeAIn = CBashFLOAT32(29)
    edgeAFull = CBashFLOAT32(30)
    edgeAOut = CBashFLOAT32(31)
    edgeAPRatio = CBashFLOAT32(32)
    edgeAAmp = CBashFLOAT32(33)
    edgeAFreq = CBashFLOAT32(34)
    fillAFRatio = CBashFLOAT32(35)
    edgeAFRatio = CBashFLOAT32(36)
    memDBlend = CBashGeneric(37, c_ubyte)
    partSBlend = CBashGeneric(38, c_ubyte)
    partBlendOp = CBashGeneric(39, c_ubyte)
    partZFunc = CBashGeneric(40, c_ubyte)
    partDBlend = CBashGeneric(41, c_ubyte)
    partBUp = CBashFLOAT32(42)
    partBFull = CBashFLOAT32(43)
    partBDown = CBashFLOAT32(44)
    partBFRatio = CBashFLOAT32(45)
    partBPRatio = CBashFLOAT32(46)
    partLTime = CBashFLOAT32(47)
    partLDelta = CBashFLOAT32(48)
    partNSpd = CBashFLOAT32(49)
    partNAcc = CBashFLOAT32(50)
    partVel1 = CBashFLOAT32(51)
    partVel2 = CBashFLOAT32(52)
    partVel3 = CBashFLOAT32(53)
    partAcc1 = CBashFLOAT32(54)
    partAcc2 = CBashFLOAT32(55)
    partAcc3 = CBashFLOAT32(56)
    partKey1 = CBashFLOAT32(57)
    partKey2 = CBashFLOAT32(58)
    partKey1Time = CBashFLOAT32(59)
    partKey2Time = CBashFLOAT32(60)
    key1Red = CBashGeneric(61, c_ubyte)
    key1Green = CBashGeneric(62, c_ubyte)
    key1Blue = CBashGeneric(63, c_ubyte)
    unused4 = CBashUINT8ARRAY(64, 1)
    key2Red = CBashGeneric(65, c_ubyte)
    key2Green = CBashGeneric(66, c_ubyte)
    key2Blue = CBashGeneric(67, c_ubyte)
    unused5 = CBashUINT8ARRAY(68, 1)
    key3Red = CBashGeneric(69, c_ubyte)
    key3Green = CBashGeneric(70, c_ubyte)
    key3Blue = CBashGeneric(71, c_ubyte)
    unused6 = CBashUINT8ARRAY(72, 1)
    key1A = CBashFLOAT32(73)
    key2A = CBashFLOAT32(74)
    key3A = CBashFLOAT32(75)
    key1Time = CBashFLOAT32(76)
    key2Time = CBashFLOAT32(77)
    key3Time = CBashFLOAT32(78)
    IsNoMemShader = CBashBasicFlag('flags', 0x00000001)
    IsNoMembraneShader = CBashAlias('IsNoMemShader')
    IsNoPartShader = CBashBasicFlag('flags', 0x00000008)
    IsNoParticleShader = CBashAlias('IsNoPartShader')
    IsEdgeInverse = CBashBasicFlag('flags', 0x00000010)
    IsEdgeEffectInverse = CBashAlias('IsEdgeInverse')
    IsMemSkinOnly = CBashBasicFlag('flags', 0x00000020)
    IsMembraneShaderSkinOnly = CBashAlias('IsMemSkinOnly')
    exportattrs = copyattrs = ObBaseRecord.baseattrs + ['fillTexturePath', 'particleTexturePath', 'flags', 'memSBlend', 'memBlendOp',
                                        'memZFunc', 'fillRed', 'fillGreen', 'fillBlue', 'fillAIn', 'fillAFull',
                                        'fillAOut', 'fillAPRatio', 'fillAAmp', 'fillAFreq', 'fillAnimSpdU',
                                        'fillAnimSpdV', 'edgeOff', 'edgeRed', 'edgeGreen', 'edgeBlue', 'edgeAIn',
                                        'edgeAFull', 'edgeAOut', 'edgeAPRatio', 'edgeAAmp', 'edgeAFreq',
                                        'fillAFRatio', 'edgeAFRatio', 'memDBlend', 'partSBlend', 'partBlendOp',
                                        'partZFunc', 'partDBlend', 'partBUp', 'partBFull', 'partBDown',
                                        'partBFRatio', 'partBPRatio', 'partLTime', 'partLDelta', 'partNSpd',
                                        'partNAcc', 'partVel1', 'partVel2', 'partVel3', 'partAcc1', 'partAcc2',
                                        'partAcc3', 'partKey1', 'partKey2', 'partKey1Time', 'partKey2Time',
                                        'key1Red', 'key1Green', 'key1Blue', 'key2Red', 'key2Green', 'key2Blue',
                                        'key3Red', 'key3Green', 'key3Blue', 'key1A', 'key2A', 'key3A',
                                        'key1Time', 'key2Time', 'key3Time']

class ObENCHRecord(ObBaseRecord):
    _Type = 'ENCH'
    full = CBashSTRING(5)
    itemType = CBashGeneric(6, c_ulong)
    chargeAmount = CBashGeneric(7, c_ulong)
    enchantCost = CBashGeneric(8, c_ulong)
    flags = CBashGeneric(9, c_ubyte)
    unused1 = CBashUINT8ARRAY(10, 3)

    def create_effect(self):
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 11, 0, 0, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, 11, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return Effect(self._CollectionID, self._ModID, self._RecordID, 11, length)
    effects = CBashLIST(11, Effect)
    effects_list = CBashLIST(11, Effect, True)

    IsNoAutoCalc = CBashBasicFlag('flags', 0x00000001)
    IsScroll = CBashBasicType('itemType', 0, 'IsStaff')
    IsStaff = CBashBasicType('itemType', 1, 'IsScroll')
    IsWeapon = CBashBasicType('itemType', 2, 'IsScroll')
    IsApparel = CBashBasicType('itemType', 3, 'IsScroll')
    ##OBME Fields. Setting any of the below fields will make the mod require JRoush's OBME plugin for OBSE
    ##To see if OBME is in use, check the recordVersion field for a non-None value
    recordVersion = CBashGeneric(12, c_ubyte)
    betaVersion = CBashGeneric(13, c_ubyte)
    minorVersion = CBashGeneric(14, c_ubyte)
    majorVersion = CBashGeneric(15, c_ubyte)
    reserved = CBashUINT8ARRAY(16, 0x1C)
    datx_p = CBashUINT8ARRAY(17, 0x20)
    exportattrs = copyattrs = ObBaseRecord.baseattrs + ['full', 'itemType', 'chargeAmount',
                                        'enchantCost', 'flags', 'effects_list']
    copyattrsOBME = copyattrs + ['recordVersion', 'betaVersion',
                                 'minorVersion', 'majorVersion',
                                 'reserved'] #, 'datx_p'

class ObEYESRecord(ObBaseRecord):
    _Type = 'EYES'
    full = CBashSTRING(5)
    iconPath = CBashISTRING(6)
    flags = CBashGeneric(7, c_ubyte)
    IsPlayable = CBashBasicFlag('flags', 0x00000001)
    exportattrs = copyattrs = ObBaseRecord.baseattrs + ['full', 'iconPath', 'flags']

class ObFACTRecord(ObBaseRecord):
    _Type = 'FACT'
    class Rank(ListComponent):
        rank = CBashGeneric_LIST(1, c_long)
        male = CBashSTRING_LIST(2)
        female = CBashSTRING_LIST(3)
        insigniaPath = CBashISTRING_LIST(4)
        exportattrs = copyattrs = ['rank', 'male', 'female', 'insigniaPath']

    full = CBashSTRING(5)

    def create_relation(self):
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 6, 0, 0, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, 6, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return Relation(self._CollectionID, self._ModID, self._RecordID, 6, length)
    relations = CBashLIST(6, Relation)
    relations_list = CBashLIST(6, Relation, True)

    flags = CBashGeneric(7, c_ubyte)
    crimeGoldMultiplier = CBashFLOAT32(8)

    def create_rank(self):
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 9, 0, 0, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, 9, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return self.Rank(self._CollectionID, self._ModID, self._RecordID, 9, length)
    ranks = CBashLIST(9, Rank)
    ranks_list = CBashLIST(9, Rank, True)

    IsHiddenFromPC = CBashBasicFlag('flags', 0x00000001)
    IsEvil = CBashBasicFlag('flags', 0x00000002)
    IsSpecialCombat = CBashBasicFlag('flags', 0x00000004)
    exportattrs = copyattrs = ObBaseRecord.baseattrs + ['full', 'relations_list', 'flags',
                                        'crimeGoldMultiplier', 'ranks_list']

class ObFLORRecord(ObBaseRecord):
    _Type = 'FLOR'
    full = CBashSTRING(5)
    modPath = CBashISTRING(6)
    modb = CBashFLOAT32(7)
    modt_p = CBashUINT8ARRAY(8)
    script = CBashFORMID(9)
    ingredient = CBashFORMID(10)
    spring = CBashGeneric(11, c_ubyte)
    summer = CBashGeneric(12, c_ubyte)
    fall = CBashGeneric(13, c_ubyte)
    winter = CBashGeneric(14, c_ubyte)
    copyattrs = ObBaseRecord.baseattrs + ['full', 'modPath', 'modb', 'modt_p',
                                        'script', 'ingredient', 'spring',
                                        'summer', 'fall', 'winter']
    exportattrs = ObBaseRecord.baseattrs + ['full', 'modPath', 'modb',
                                        'script', 'ingredient', 'spring',
                                        'summer', 'fall', 'winter'] # 'modt_p',

class ObFURNRecord(ObBaseRecord):
    _Type = 'FURN'
    full = CBashSTRING(5)
    modPath = CBashISTRING(6)
    modb = CBashFLOAT32(7)
    modt_p = CBashUINT8ARRAY(8)
    script = CBashFORMID(9)
    flags = CBashGeneric(10, c_ulong)
    IsAnim01 = CBashBasicFlag('flags', 0x00000001)
    IsAnim02 = CBashBasicFlag('flags', 0x00000002)
    IsAnim03 = CBashBasicFlag('flags', 0x00000004)
    IsAnim04 = CBashBasicFlag('flags', 0x00000008)
    IsAnim05 = CBashBasicFlag('flags', 0x00000010)
    IsAnim06 = CBashBasicFlag('flags', 0x00000020)
    IsAnim07 = CBashBasicFlag('flags', 0x00000040)
    IsAnim08 = CBashBasicFlag('flags', 0x00000080)
    IsAnim09 = CBashBasicFlag('flags', 0x00000100)
    IsAnim10 = CBashBasicFlag('flags', 0x00000200)
    IsAnim11 = CBashBasicFlag('flags', 0x00000400)
    IsAnim12 = CBashBasicFlag('flags', 0x00000800)
    IsAnim13 = CBashBasicFlag('flags', 0x00001000)
    IsAnim14 = CBashBasicFlag('flags', 0x00002000)
    IsAnim15 = CBashBasicFlag('flags', 0x00004000)
    IsAnim16 = CBashBasicFlag('flags', 0x00008000)
    IsAnim17 = CBashBasicFlag('flags', 0x00010000)
    IsAnim18 = CBashBasicFlag('flags', 0x00020000)
    IsAnim19 = CBashBasicFlag('flags', 0x00040000)
    IsAnim20 = CBashBasicFlag('flags', 0x00080000)
    IsAnim21 = CBashBasicFlag('flags', 0x00100000)
    IsAnim22 = CBashBasicFlag('flags', 0x00200000)
    IsAnim23 = CBashBasicFlag('flags', 0x00400000)
    IsAnim24 = CBashBasicFlag('flags', 0x00800000)
    IsAnim25 = CBashBasicFlag('flags', 0x01000000)
    IsAnim26 = CBashBasicFlag('flags', 0x02000000)
    IsAnim27 = CBashBasicFlag('flags', 0x04000000)
    IsAnim28 = CBashBasicFlag('flags', 0x08000000)
    IsAnim29 = CBashBasicFlag('flags', 0x10000000)
    IsAnim30 = CBashBasicFlag('flags', 0x20000000)
    IsSitAnim = CBashMaskedType('flags', 0xC0000000, 0x40000000, 'IsSleepAnim')
    IsSleepAnim = CBashMaskedType('flags', 0xC0000000, 0x80000000, 'IsSitAnim')
    copyattrs = ObBaseRecord.baseattrs + ['full', 'modPath', 'modb',
                                        'modt_p', 'script', 'flags']
    exportattrs = ObBaseRecord.baseattrs + ['full', 'modPath', 'modb',
                                        'script', 'flags'] #'modt_p',

class ObGLOBRecord(ObBaseRecord):
    _Type = 'GLOB'
    format = CBashGeneric(5, c_char)
    value = CBashFLOAT32(6)
    exportattrs = copyattrs = ObBaseRecord.baseattrs + ['format', 'value']

class ObGRASRecord(ObBaseRecord):
    _Type = 'GRAS'
    modPath = CBashISTRING(5)
    modb = CBashFLOAT32(6)
    modt_p = CBashUINT8ARRAY(7)
    density = CBashGeneric(8, c_ubyte)
    minSlope = CBashGeneric(9, c_ubyte)
    maxSlope = CBashGeneric(10, c_ubyte)
    unused1 = CBashUINT8ARRAY(11, 1)
    waterDistance = CBashGeneric(12, c_ushort)
    unused2 = CBashUINT8ARRAY(13, 2)
    waterOp = CBashGeneric(14, c_ulong)
    posRange = CBashFLOAT32(15)
    heightRange = CBashFLOAT32(16)
    colorRange = CBashFLOAT32(17)
    wavePeriod = CBashFLOAT32(18)
    flags = CBashGeneric(19, c_ubyte)
    unused3 = CBashUINT8ARRAY(20, 3)
    IsVLighting = CBashBasicFlag('flags', 0x00000001)
    IsVertexLighting = CBashAlias('IsVLighting')
    IsUScaling = CBashBasicFlag('flags', 0x00000002)
    IsUniformScaling = CBashAlias('IsUScaling')
    IsFitSlope = CBashBasicFlag('flags', 0x00000004)
    IsFitToSlope = CBashAlias('IsFitSlope')
    copyattrs = ObBaseRecord.baseattrs + ['modPath', 'modb', 'modt_p', 'density',
                                        'minSlope', 'maxSlope', 'waterDistance',
                                        'waterOp', 'posRange', 'heightRange',
                                        'colorRange', 'wavePeriod', 'flags']
    exportattrs = ObBaseRecord.baseattrs + ['modPath', 'modb', 'density',
                                        'minSlope', 'maxSlope', 'waterDistance',
                                        'waterOp', 'posRange', 'heightRange',
                                        'colorRange', 'wavePeriod', 'flags'] #'modt_p',

class ObHAIRRecord(ObBaseRecord):
    _Type = 'HAIR'
    full = CBashSTRING(5)
    modPath = CBashISTRING(6)
    modb = CBashFLOAT32(7)
    modt_p = CBashUINT8ARRAY(8)
    iconPath = CBashISTRING(9)
    flags = CBashGeneric(10, c_ubyte)
    IsPlayable = CBashBasicFlag('flags', 0x00000001)
    IsNotMale = CBashBasicFlag('flags', 0x00000002)
    IsMale = CBashInvertedFlag('IsNotMale')
    IsNotFemale = CBashBasicFlag('flags', 0x00000004)
    IsFemale = CBashInvertedFlag('IsNotFemale')
    IsFixedColor = CBashBasicFlag('flags', 0x00000008)
    copyattrs = ObBaseRecord.baseattrs + ['full', 'modPath', 'modb',
                                        'modt_p', 'iconPath', 'flags']
    exportattrs = ObBaseRecord.baseattrs + ['full', 'modPath', 'modb',
                                        'iconPath', 'flags'] #'modt_p',

class ObIDLERecord(ObBaseRecord):
    _Type = 'IDLE'
    modPath = CBashISTRING(5)
    modb = CBashFLOAT32(6)
    modt_p = CBashUINT8ARRAY(7)

    def create_condition(self):
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 8, 0, 0, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, 8, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return Condition(self._CollectionID, self._ModID, self._RecordID, 8, length)
    conditions = CBashLIST(8, Condition)
    conditions_list = CBashLIST(8, Condition, True)

    group = CBashGeneric(9, c_ubyte)
    parent = CBashFORMID(10)
    prevId = CBashFORMID(11)
    IsLowerBody = CBashMaskedType('group', 0x0F, 0x00, 'IsLeftArm')
    IsLeftArm = CBashMaskedType('group', 0x0F, 0x01, 'IsLowerBody')
    IsLeftHand = CBashMaskedType('group', 0x0F, 0x02, 'IsLowerBody')
    IsRightArm = CBashMaskedType('group', 0x0F, 0x03, 'IsLowerBody')
    IsSpecialIdle = CBashMaskedType('group', 0x0F, 0x04, 'IsLowerBody')
    IsWholeBody = CBashMaskedType('group', 0x0F, 0x05, 'IsLowerBody')
    IsUpperBody = CBashMaskedType('group', 0x0F, 0x06, 'IsLowerBody')
    IsNotReturnFile = CBashBasicFlag('group', 0x80)
    IsReturnFile = CBashInvertedFlag('IsNotReturnFile')
    copyattrs = ObBaseRecord.baseattrs + ['modPath', 'modb', 'modt_p',
                                        'conditions_list', 'group', 'parent', 'prevId']
    exportattrs = ObBaseRecord.baseattrs + ['modPath', 'modb', 'conditions_list',
                                            'group', 'parent', 'prevId'] # 'modt_p',

class ObINGRRecord(ObBaseRecord):
    _Type = 'INGR'
    full = CBashSTRING(5)
    modPath = CBashISTRING(6)
    modb = CBashFLOAT32(7)
    modt_p = CBashUINT8ARRAY(8)
    iconPath = CBashISTRING(9)
    script = CBashFORMID(10)
    weight = CBashFLOAT32(11)
    value = CBashGeneric(12, c_long)
    flags = CBashGeneric(13, c_ubyte)
    unused1 = CBashUINT8ARRAY(14, 3)

    def create_effect(self):
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 15, 0, 0, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, 15, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return Effect(self._CollectionID, self._ModID, self._RecordID, 15, length)
    effects = CBashLIST(15, Effect)
    effects_list = CBashLIST(15, Effect, True)

    IsNoAutoCalc = CBashBasicFlag('flags', 0x00000001)
    IsFood = CBashBasicFlag('flags', 0x00000002)
    ##OBME Fields. Setting any of the below fields will make the mod require JRoush's OBME plugin for OBSE
    ##To see if OBME is in use, check the recordVersion field for a non-None value
    recordVersion = CBashGeneric(16, c_ubyte)
    betaVersion = CBashGeneric(17, c_ubyte)
    minorVersion = CBashGeneric(18, c_ubyte)
    majorVersion = CBashGeneric(19, c_ubyte)
    reserved = CBashUINT8ARRAY(20, 0x1C)
    datx_p = CBashUINT8ARRAY(21, 0x20)
    copyattrs = ObBaseRecord.baseattrs + ['full', 'modPath', 'modb', 'modt_p', 'iconPath',
                                        'script', 'weight', 'value', 'flags',
                                        'effects_list']
    exportattrs = ObBaseRecord.baseattrs + ['full', 'modPath', 'modb', 'iconPath',
                                        'script', 'weight', 'value', 'flags',
                                        'effects_list'] #'modt_p',
    copyattrsOBME = copyattrs + ['recordVersion', 'betaVersion',
                                 'minorVersion', 'majorVersion',
                                 'reserved'] #, 'datx_p'

class ObKEYMRecord(ObBaseRecord):
    _Type = 'KEYM'
    full = CBashSTRING(5)
    modPath = CBashISTRING(6)
    modb = CBashFLOAT32(7)
    modt_p = CBashUINT8ARRAY(8)
    iconPath = CBashISTRING(9)
    script = CBashFORMID(10)
    value = CBashGeneric(11, c_long)
    weight = CBashFLOAT32(12)
    copyattrs = ObBaseRecord.baseattrs + ['full', 'modPath', 'modb', 'modt_p', 'iconPath',
                                        'script', 'value', 'weight']
    exportattrs = ObBaseRecord.baseattrs + ['full', 'modPath', 'modb', 'iconPath',
                                        'script', 'value', 'weight'] #'modt_p',

class ObLIGHRecord(ObBaseRecord):
    _Type = 'LIGH'
    modPath = CBashISTRING(5)
    modb = CBashFLOAT32(6)
    modt_p = CBashUINT8ARRAY(7)
    script = CBashFORMID(8)
    full = CBashSTRING(9)
    iconPath = CBashISTRING(10)
    duration = CBashGeneric(11, c_long)
    radius = CBashGeneric(12, c_ulong)
    red = CBashGeneric(13, c_ubyte)
    green = CBashGeneric(14, c_ubyte)
    blue = CBashGeneric(15, c_ubyte)
    unused1 = CBashUINT8ARRAY(16, 1)
    flags = CBashGeneric(17, c_ulong)
    falloff = CBashFLOAT32(18)
    fov = CBashFLOAT32(19)
    value = CBashGeneric(20, c_ulong)
    weight = CBashFLOAT32(21)
    fade = CBashFLOAT32(22)
    sound = CBashFORMID(23)
    IsDynamic = CBashBasicFlag('flags', 0x00000001)
    IsCanTake = CBashBasicFlag('flags', 0x00000002)
    IsNegative = CBashBasicFlag('flags', 0x00000004)
    IsFlickers = CBashBasicFlag('flags', 0x00000008)
    IsOffByDefault = CBashBasicFlag('flags', 0x00000020)
    IsFlickerSlow = CBashBasicFlag('flags', 0x00000040)
    IsPulse = CBashBasicFlag('flags', 0x00000080)
    IsPulseSlow = CBashBasicFlag('flags', 0x00000100)
    IsSpotLight = CBashBasicFlag('flags', 0x00000200)
    IsSpotShadow = CBashBasicFlag('flags', 0x00000400)
    copyattrs = ObBaseRecord.baseattrs + ['modPath', 'modb', 'modt_p', 'script', 'full',
                                        'iconPath', 'duration', 'radius', 'red',
                                        'green', 'blue', 'flags', 'falloff', 'fov',
                                        'value', 'weight', 'fade', 'sound']
    exportattrs = ObBaseRecord.baseattrs + ['modPath', 'modb', 'script', 'full',
                                        'iconPath', 'duration', 'radius', 'red',
                                        'green', 'blue', 'flags', 'falloff', 'fov',
                                        'value', 'weight', 'fade', 'sound'] #'modt_p',

class ObLSCRRecord(ObBaseRecord):
    _Type = 'LSCR'
    class Location(ListComponent):
        direct = CBashFORMID_LIST(1)
        indirect = CBashFORMID_LIST(2)
        gridY = CBashGeneric_LIST(3, c_short)
        gridX = CBashGeneric_LIST(4, c_short)
        exportattrs = copyattrs = ['direct', 'indirect', 'gridY', 'gridX']

    iconPath = CBashISTRING(5)
    text = CBashSTRING(6)

    def create_location(self):
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 7, 0, 0, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, 7, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return self.Location(self._CollectionID, self._ModID, self._RecordID, 7, length)
    locations = CBashLIST(7, Location)
    locations_list = CBashLIST(7, Location, True)

    exportattrs = copyattrs = ObBaseRecord.baseattrs + ['iconPath', 'text', 'locations_list']

class ObLTEXRecord(ObBaseRecord):
    _Type = 'LTEX'
    iconPath = CBashISTRING(5)
    types = CBashGeneric(6, c_ubyte)
    friction = CBashGeneric(7, c_ubyte)
    restitution = CBashGeneric(8, c_ubyte)
    specular = CBashGeneric(9, c_ubyte)
    grass = CBashFORMIDARRAY(10)
    IsStone = CBashBasicType('types', 0, 'IsCloth')
    IsCloth = CBashBasicType('types', 1, 'IsStone')
    IsDirt = CBashBasicType('types', 2, 'IsStone')
    IsGlass = CBashBasicType('types', 3, 'IsStone')
    IsGrass = CBashBasicType('types', 4, 'IsStone')
    IsMetal = CBashBasicType('types', 5, 'IsStone')
    IsOrganic = CBashBasicType('types', 6, 'IsStone')
    IsSkin = CBashBasicType('types', 7, 'IsStone')
    IsWater = CBashBasicType('types', 8, 'IsStone')
    IsWood = CBashBasicType('types', 9, 'IsStone')
    IsHeavyStone = CBashBasicType('types', 10, 'IsStone')
    IsHeavyMetal = CBashBasicType('types', 11, 'IsStone')
    IsHeavyWood = CBashBasicType('types', 12, 'IsStone')
    IsChain = CBashBasicType('types', 13, 'IsStone')
    IsSnow = CBashBasicType('types', 14, 'IsStone')
    exportattrs = copyattrs = ObBaseRecord.baseattrs + ['iconPath', 'types', 'friction', 'restitution',
                                        'specular', 'grass']

class ObLVLCRecord(ObBaseRecord):
    _Type = 'LVLC'
    class Entry(ListComponent):
        level = CBashGeneric_LIST(1, c_short)
        unused1 = CBashUINT8ARRAY_LIST(2, 2)
        listId = CBashFORMID_LIST(3)
        count = CBashGeneric_LIST(4, c_short)
        unused2 = CBashUINT8ARRAY_LIST(5, 2)
        exportattrs = copyattrs = ['level', 'listId', 'count']

    def mergeFilter(self,modSet):
        """Filter out items that don't come from specified modSet."""
        self.entries = [entry for entry in self.entries if entry.listId[0] in modSet]

    chanceNone = CBashGeneric(5, c_ubyte)
    flags = CBashGeneric(6, c_ubyte)
    script = CBashFORMID(7)
    template = CBashFORMID(8)

    def create_entry(self):
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 9, 0, 0, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, 9, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return self.Entry(self._CollectionID, self._ModID, self._RecordID, 9, length)
    entries = CBashLIST(9, Entry)
    entries_list = CBashLIST(9, Entry, True)

    IsCalcFromAllLevels = CBashBasicFlag('flags', 0x00000001)
    IsCalcForEachItem = CBashBasicFlag('flags', 0x00000002)
    IsUseAllSpells = CBashBasicFlag('flags', 0x00000004)
    exportattrs = copyattrs = ObBaseRecord.baseattrs + ['chanceNone', 'flags', 'script',
                                        'template', 'entries_list']

class ObLVLIRecord(ObBaseRecord):
    _Type = 'LVLI'
    class Entry(ListComponent):
        level = CBashGeneric_LIST(1, c_short)
        unused1 = CBashUINT8ARRAY_LIST(2, 2)
        listId = CBashFORMID_LIST(3)
        count = CBashGeneric_LIST(4, c_short)
        unused2 = CBashUINT8ARRAY_LIST(5, 2)
        exportattrs = copyattrs = ['level', 'listId', 'count']

    def mergeFilter(self,modSet):
        """Filter out items that don't come from specified modSet."""
        self.entries = [entry for entry in self.entries if entry.listId[0] in modSet]

    chanceNone = CBashGeneric(5, c_ubyte)
    flags = CBashGeneric(6, c_ubyte)
    script = CBashJunk(7) #Doesn't actually exist, but is here so that LVLC,LVLI,LVSP can be processed similarly
    template = CBashJunk(8) #ditto

    def create_entry(self):
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 9, 0, 0, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, 9, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return self.Entry(self._CollectionID, self._ModID, self._RecordID, 9, length)
    entries = CBashLIST(9, Entry)
    entries_list = CBashLIST(9, Entry, True)

    IsCalcFromAllLevels = CBashBasicFlag('flags', 0x00000001)
    IsCalcForEachItem = CBashBasicFlag('flags', 0x00000002)
    IsUseAllSpells = CBashBasicFlag('flags', 0x00000004)
    exportattrs = copyattrs = ObBaseRecord.baseattrs + ['chanceNone', 'flags', 'entries_list']

class ObLVSPRecord(ObBaseRecord):
    _Type = 'LVSP'
    class Entry(ListComponent):
        level = CBashGeneric_LIST(1, c_short)
        unused1 = CBashUINT8ARRAY_LIST(2, 2)
        listId = CBashFORMID_LIST(3)
        count = CBashGeneric_LIST(4, c_short)
        unused2 = CBashUINT8ARRAY_LIST(5, 2)
        exportattrs = copyattrs = ['level', 'listId', 'count']

    def mergeFilter(self,modSet):
        """Filter out items that don't come from specified modSet."""
        self.entries = [entry for entry in self.entries if entry.listId[0] in modSet]

    chanceNone = CBashGeneric(5, c_ubyte)
    flags = CBashGeneric(6, c_ubyte)
    script = CBashJunk(7) #Doesn't actually exist, but is here so that LVLC,LVLI,LVSP can be processed similarly
    template = CBashJunk(8) #ditto

    def create_entry(self):
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 9, 0, 0, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, 9, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return self.Entry(self._CollectionID, self._ModID, self._RecordID, 9, length)
    entries = CBashLIST(9, Entry)
    entries_list = CBashLIST(9, Entry, True)

    IsCalcFromAllLevels = CBashBasicFlag('flags', 0x00000001)
    IsCalcForEachItem = CBashBasicFlag('flags', 0x00000002)
    IsUseAllSpells = CBashBasicFlag('flags', 0x00000004)
    exportattrs = copyattrs = ObBaseRecord.baseattrs + ['chanceNone', 'flags', 'entries_list']

class ObMGEFRecord(ObBaseRecord):
    _Type = 'MGEF'
    full = CBashSTRING(5)
    text = CBashSTRING(6)
    iconPath = CBashISTRING(7)
    modPath = CBashISTRING(8)
    modb = CBashFLOAT32(9)
    modt_p = CBashUINT8ARRAY(10)
    flags = CBashGeneric(11, c_ulong)
    baseCost = CBashFLOAT32(12)
    associated = CBashFORMID(13)
    school = CBashGeneric(14, c_long)
    ##0xFFFFFFFF is None for resistValue
    resistValue = CBashGeneric(15, c_ulong)
    numCounters = CBashGeneric(16, c_ushort)
    unused1 = CBashUINT8ARRAY(17)
    light = CBashFORMID(18)
    projectileSpeed = CBashFLOAT32(19)
    effectShader = CBashFORMID(20)
    enchantEffect = CBashFORMID(21)
    castingSound = CBashFORMID(22)
    boltSound = CBashFORMID(23)
    hitSound = CBashFORMID(24)
    areaSound = CBashFORMID(25)
    cefEnchantment = CBashFLOAT32(26)
    cefBarter = CBashFLOAT32(27)
    counterEffects = CBashMGEFCODE_OR_UINT32_ARRAY(28)
    #Note: the vanilla code discards mod changes to most flag bits
    #  only those listed as changeable below may be edited by non-obme mods
    # comments garnered from JRoush's OBME
    IsHostile = CBashBasicFlag('flags', 0x00000001)
    IsRecover = CBashBasicFlag('flags', 0x00000002)
    IsDetrimental = CBashBasicFlag('flags', 0x00000004) #OBME Deprecated, used for ValueModifier effects AV is decreased rather than increased
    IsMagnitudeIsPercent = CBashBasicFlag('flags', 0x00000008) #OBME Deprecated
    IsSelf = CBashBasicFlag('flags', 0x00000010)
    IsTouch = CBashBasicFlag('flags', 0x00000020)
    IsTarget = CBashBasicFlag('flags', 0x00000040)
    IsNoDuration = CBashBasicFlag('flags', 0x00000080)
    IsNoMagnitude = CBashBasicFlag('flags', 0x00000100)
    IsNoArea = CBashBasicFlag('flags', 0x00000200)
    IsFXPersist = CBashBasicFlag('flags', 0x00000400) #Changeable
    IsSpellmaking = CBashBasicFlag('flags', 0x00000800) #Changeable
    IsEnchanting = CBashBasicFlag('flags', 0x00001000) #Changeable
    IsNoIngredient = CBashBasicFlag('flags', 0x00002000) #Changeable
    IsUnknownF = CBashBasicFlag('flags', 0x00004000) #no effects have this flag set
    IsNoRecast = CBashBasicFlag('flags', 0x00008000) #no effects have this flag set
    IsUseWeapon = CBashBasicFlag('flags', 0x00010000) #OBME Deprecated
    IsUseArmor = CBashBasicFlag('flags', 0x00020000) #OBME Deprecated
    IsUseCreature = CBashBasicFlag('flags', 0x00040000) #OBME Deprecated
    IsUseSkill = CBashBasicFlag('flags', 0x00080000) #OBME Deprecated
    IsUseAttr = CBashBasicFlag('flags', 0x00100000) #OBME Deprecated
    IsPCHasEffect = CBashBasicFlag('flags', 0x00200000) #whether or not PC has effect, forced to zero during loading
    IsDisabled = CBashBasicFlag('flags', 0x00400000) #Changeable, many if not all methods that loop over effects ignore those with this flag.
                                                    #  Spells with an effect with this flag are apparently uncastable.
    IsUnknownO = CBashBasicFlag('flags', 0x00800000) #Changeable, POSN,DISE - these effects have *only* this bit set,
                                                    #  perhaps a flag for meta effects
    IsUseAV = CBashBasicFlag('flags', 0x01000000) #OBME Deprecated, Changeable, but once set by default or by a previously loaded mod file
                                                    #  it cannot be unset by another mod, nor can the mgefParam be overriden

    IsBallType = CBashMaskedType('flags', 0x06000000, 0, 'IsBoltType')  #Changeable
    IsFogType = CBashMaskedType('flags', 0x06000000, 0x06000000, 'IsBallType')  #Changeable

    def get_IsSprayType(self):
        return self.flags != None and not self.IsFogType and (self.flags & 0x02000000) != 0
    def set_IsSprayType(self, nValue):
        if nValue:
            self.flags &= ~0x06000000
            self.flags |= 0x02000000
        elif self.IsSprayType: self.IsBallType = True
    IsSprayType = property(get_IsSprayType, set_IsSprayType)  #Changeable

    def get_IsBoltType(self):
        return self.flags != None and not self.IsFogType and (self.flags & 0x04000000) != 0
    def set_IsBoltType(self, nValue):
        if nValue:
            self.flags &= ~0x06000000
            self.flags |= 0x04000000
        elif self.IsBoltType: self.IsBallType = True
    IsBoltType = property(get_IsBoltType, set_IsBoltType)  #Changeable

    IsFogType = CBashBasicFlag('flags', 0x06000000) #Changeable
    IsNoHitEffect = CBashBasicFlag('flags', 0x08000000) #Changeable, no hit shader on target
    IsPersistOnDeath = CBashBasicFlag('flags', 0x10000000) #Effect is not automatically removed when its target dies
    IsExplodesWithForce = CBashBasicFlag('flags', 0x20000000) #causes explosion that can move loose objects (e.g. ragdolls)
    IsMagnitudeIsLevel = CBashBasicFlag('flags', 0x40000000) #OBME Deprecated
    IsMagnitudeIsFeet = CBashBasicFlag('flags', 0x80000000)  #OBME Deprecated
    ##OBME Fields. Setting any of the below fields will make the mod require JRoush's OBME plugin for OBSE
    ##To see if OBME is in use, check the recordVersion field for a non-None value
    recordVersion = CBashGeneric(29, c_ubyte) #OBME
    betaVersion = CBashGeneric(30, c_ubyte) #OBME
    minorVersion = CBashGeneric(31, c_ubyte) #OBME
    majorVersion = CBashGeneric(32, c_ubyte) #OBME
    mgefParamAInfo = CBashGeneric(33, c_ubyte) #OBME
    mgefParamBInfo = CBashGeneric(34, c_ubyte) #OBME
    reserved1 = CBashUINT8ARRAY(35, 0x2) #OBME
    handlerCode = CBashGeneric(36, c_ulong) #OBME
    OBMEFlags = CBashGeneric(37, c_ulong) #OBME
    mgefParamB = CBashGeneric(38, c_ulong) #OBME
    reserved2 = CBashUINT8ARRAY(39, 0x1C) #OBME
    mgefCode = CBashMGEFCODE(40) #OBME
    datx_p = CBashUINT8ARRAY(41, 0x20) #OBME
    IsBeneficial = CBashBasicFlag('OBMEFlags', 0x00000008) #OBME
    IsMagnitudeIsRange = CBashBasicFlag('OBMEFlags', 0x00020000) #OBME
    IsAtomicResistance = CBashBasicFlag('OBMEFlags', 0x00040000) #OBME
    IsParamFlagA = CBashBasicFlag('OBMEFlags', 0x00000004) #OBME //Meaning varies with effect handler
    IsParamFlagB = CBashBasicFlag('OBMEFlags', 0x00010000) #OBME //Meaning varies with effect handler
    IsParamFlagC = CBashBasicFlag('OBMEFlags', 0x00080000) #OBME //Meaning varies with effect handler
    IsParamFlagD = CBashBasicFlag('OBMEFlags', 0x00100000) #OBME //Meaning varies with effect handler
    IsHidden = CBashBasicFlag('OBMEFlags', 0x40000000) #OBME
    copyattrs = ObBaseRecord.baseattrs + ['full', 'text', 'iconPath', 'modPath',
                                          'modb', 'modt_p', 'flags', 'baseCost',
                                          'associated', 'school', 'resistValue',
                                          'numCounters', 'light', 'projectileSpeed',
                                          'effectShader', 'enchantEffect',
                                          'castingSound', 'boltSound', 'hitSound',
                                          'areaSound', 'cefEnchantment', 'cefBarter',
                                          'counterEffects']
    exportattrs = ObBaseRecord.baseattrs + ['full', 'text', 'iconPath', 'modPath',
                                          'modb', 'flags', 'baseCost',
                                          'associated', 'school', 'resistValue',
                                          'numCounters', 'light', 'projectileSpeed',
                                          'effectShader', 'enchantEffect',
                                          'castingSound', 'boltSound', 'hitSound',
                                          'areaSound', 'cefEnchantment', 'cefBarter',
                                          'counterEffects'] #'modt_p',
    copyattrsOBME = copyattrs + ['recordVersion', 'betaVersion',
                                 'minorVersion', 'majorVersion',
                                 'mgefParamAInfo', 'mgefParamBInfo',
                                 'reserved1', 'handlerCode', 'OBMEFlags',
                                 'mgefParamB', 'reserved2', 'mgefCode'] #, 'datx_p'

class ObMISCRecord(ObBaseRecord):
    _Type = 'MISC'
    full = CBashSTRING(5)
    modPath = CBashISTRING(6)
    modb = CBashFLOAT32(7)
    modt_p = CBashUINT8ARRAY(8)
    iconPath = CBashISTRING(9)
    script = CBashFORMID(10)
    value = CBashGeneric(11, c_long)
    weight = CBashFLOAT32(12)
    copyattrs = ObBaseRecord.baseattrs + ['full', 'modPath', 'modb', 'modt_p', 'iconPath',
                                        'script', 'value', 'weight']
    exportattrs = ObBaseRecord.baseattrs + ['full', 'modPath', 'modb', 'iconPath',
                                        'script', 'value', 'weight'] #'modt_p',

class ObNPC_Record(ObBaseRecord):
    _Type = 'NPC_'
    def mergeFilter(self,modSet):
        """Filter out items that don't come from specified modSet.
        Filters spells, factions and items."""
        self.spells = [x for x in self.spells if x[0] in modSet]
        self.factions = [x for x in self.factions if x.faction[0] in modSet]
        self.items = [x for x in self.items if x.item[0] in modSet]

    full = CBashSTRING(5)
    modPath = CBashISTRING(6)
    modb = CBashFLOAT32(7)
    modt_p = CBashUINT8ARRAY(8)
    flags = CBashGeneric(9, c_ulong)
    baseSpell = CBashGeneric(10, c_ushort)
    fatigue = CBashGeneric(11, c_ushort)
    barterGold = CBashGeneric(12, c_ushort)
    level = CBashGeneric(13, c_short)
    calcMin = CBashGeneric(14, c_ushort)
    calcMax = CBashGeneric(15, c_ushort)

    def create_faction(self):
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 16, 0, 0, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, 16, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return Faction(self._CollectionID, self._ModID, self._RecordID, 16, length)
    factions = CBashLIST(16, Faction)
    factions_list = CBashLIST(16, Faction, True)

    deathItem = CBashFORMID(17)
    race = CBashFORMID(18)
    spells = CBashFORMIDARRAY(19)
    script = CBashFORMID(20)

    def create_item(self):
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 21, 0, 0, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, 21, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return Item(self._CollectionID, self._ModID, self._RecordID, 21, length)
    items = CBashLIST(21, Item)
    items_list = CBashLIST(21, Item, True)

    aggression = CBashGeneric(22, c_ubyte)
    confidence = CBashGeneric(23, c_ubyte)
    energyLevel = CBashGeneric(24, c_ubyte)
    responsibility = CBashGeneric(25, c_ubyte)
    services = CBashGeneric(26, c_ulong)
    trainSkill = CBashGeneric(27, c_byte)
    trainLevel = CBashGeneric(28, c_ubyte)
    unused1 = CBashUINT8ARRAY(29, 2)
    aiPackages = CBashFORMIDARRAY(30)
    animations = CBashISTRINGARRAY(31)
    iclass = CBashFORMID(32)
    armorer = CBashGeneric(33, c_ubyte)
    athletics = CBashGeneric(34, c_ubyte)
    blade = CBashGeneric(35, c_ubyte)
    block = CBashGeneric(36, c_ubyte)
    blunt = CBashGeneric(37, c_ubyte)
    h2h = CBashGeneric(38, c_ubyte)
    heavyArmor = CBashGeneric(39, c_ubyte)
    alchemy = CBashGeneric(40, c_ubyte)
    alteration = CBashGeneric(41, c_ubyte)
    conjuration = CBashGeneric(42, c_ubyte)
    destruction = CBashGeneric(43, c_ubyte)
    illusion = CBashGeneric(44, c_ubyte)
    mysticism = CBashGeneric(45, c_ubyte)
    restoration = CBashGeneric(46, c_ubyte)
    acrobatics = CBashGeneric(47, c_ubyte)
    lightArmor = CBashGeneric(48, c_ubyte)
    marksman = CBashGeneric(49, c_ubyte)
    mercantile = CBashGeneric(50, c_ubyte)
    security = CBashGeneric(51, c_ubyte)
    sneak = CBashGeneric(52, c_ubyte)
    speechcraft = CBashGeneric(53, c_ubyte)
    health = CBashGeneric(54, c_ushort)
    unused2 = CBashUINT8ARRAY(55, 2)
    strength = CBashGeneric(56, c_ubyte)
    intelligence = CBashGeneric(57, c_ubyte)
    willpower = CBashGeneric(58, c_ubyte)
    agility = CBashGeneric(59, c_ubyte)
    speed = CBashGeneric(60, c_ubyte)
    endurance = CBashGeneric(61, c_ubyte)
    personality = CBashGeneric(62, c_ubyte)
    luck = CBashGeneric(63, c_ubyte)
    hair = CBashFORMID(64)
    hairLength = CBashFLOAT32(65)
    eye = CBashFORMID(66)
    hairRed = CBashGeneric(67, c_ubyte)
    hairGreen = CBashGeneric(68, c_ubyte)
    hairBlue = CBashGeneric(69, c_ubyte)
    unused3 = CBashUINT8ARRAY(70, 1)
    combatStyle = CBashFORMID(71)
    fggs_p = CBashUINT8ARRAY(72, 200)
    fgga_p = CBashUINT8ARRAY(73, 120)
    fgts_p = CBashUINT8ARRAY(74, 200)
    fnam = CBashGeneric(75, c_ushort)
    IsFemale = CBashBasicFlag('flags', 0x00000001)
    IsMale = CBashInvertedFlag('IsFemale')
    IsEssential = CBashBasicFlag('flags', 0x00000002)
    IsRespawn = CBashBasicFlag('flags', 0x00000008)
    IsAutoCalc = CBashBasicFlag('flags', 0x00000010)
    IsPCLevelOffset = CBashBasicFlag('flags', 0x00000080)
    IsNoLowLevel = CBashBasicFlag('flags', 0x00000200)
    IsLowLevel = CBashInvertedFlag('IsNoLowLevel')
    IsNoRumors = CBashBasicFlag('flags', 0x00002000)
    IsRumors = CBashInvertedFlag('IsNoRumors')
    IsSummonable = CBashBasicFlag('flags', 0x00004000)
    IsNoPersuasion = CBashBasicFlag('flags', 0x00008000)
    IsPersuasion = CBashInvertedFlag('IsNoPersuasion')
    IsCanCorpseCheck = CBashBasicFlag('flags', 0x00100000)
    IsServicesWeapons = CBashBasicFlag('services', 0x00000001)
    IsServicesArmor = CBashBasicFlag('services', 0x00000002)
    IsServicesClothing = CBashBasicFlag('services', 0x00000004)
    IsServicesBooks = CBashBasicFlag('services', 0x00000008)
    IsServicesIngredients = CBashBasicFlag('services', 0x00000010)
    IsServicesLights = CBashBasicFlag('services', 0x00000080)
    IsServicesApparatus = CBashBasicFlag('services', 0x00000100)
    IsServicesMiscItems = CBashBasicFlag('services', 0x00000400)
    IsServicesSpells = CBashBasicFlag('services', 0x00000800)
    IsServicesMagicItems = CBashBasicFlag('services', 0x00001000)
    IsServicesPotions = CBashBasicFlag('services', 0x00002000)
    IsServicesTraining = CBashBasicFlag('services', 0x00004000)
    IsServicesRecharge = CBashBasicFlag('services', 0x00010000)
    IsServicesRepair = CBashBasicFlag('services', 0x00020000)
    copyattrs = ObBaseRecord.baseattrs + ['full', 'modPath', 'modb', 'modt_p',
                                        'flags', 'baseSpell', 'fatigue',
                                        'barterGold', 'level', 'calcMin',
                                        'calcMax', 'factions_list', 'deathItem',
                                        'race', 'spells', 'script',
                                        'items_list', 'aggression', 'confidence',
                                        'energyLevel', 'responsibility',
                                        'services', 'trainSkill', 'trainLevel',
                                        'aiPackages', 'animations', 'iclass',
                                        'armorer', 'athletics', 'blade',
                                        'block', 'blunt', 'h2h', 'heavyArmor',
                                        'alchemy', 'alteration', 'conjuration',
                                        'destruction', 'illusion', 'mysticism',
                                        'restoration', 'acrobatics', 'lightArmor',
                                        'marksman', 'mercantile', 'security',
                                        'sneak', 'speechcraft', 'health',
                                        'strength', 'intelligence', 'willpower',
                                        'agility', 'speed', 'endurance',
                                        'personality', 'luck', 'hair',
                                        'hairLength', 'eye', 'hairRed',
                                        'hairGreen', 'hairBlue', 'combatStyle',
                                        'fggs_p', 'fgga_p', 'fgts_p', 'fnam']
    exportattrs = ObBaseRecord.baseattrs + ['full', 'modPath', 'modb',
                                        'flags', 'baseSpell', 'fatigue',
                                        'barterGold', 'level', 'calcMin',
                                        'calcMax', 'factions_list', 'deathItem',
                                        'race', 'spells', 'script',
                                        'items_list', 'aggression', 'confidence',
                                        'energyLevel', 'responsibility',
                                        'services', 'trainSkill', 'trainLevel',
                                        'aiPackages', 'animations', 'iclass',
                                        'armorer', 'athletics', 'blade',
                                        'block', 'blunt', 'h2h', 'heavyArmor',
                                        'alchemy', 'alteration', 'conjuration',
                                        'destruction', 'illusion', 'mysticism',
                                        'restoration', 'acrobatics', 'lightArmor',
                                        'marksman', 'mercantile', 'security',
                                        'sneak', 'speechcraft', 'health',
                                        'strength', 'intelligence', 'willpower',
                                        'agility', 'speed', 'endurance',
                                        'personality', 'luck', 'hair',
                                        'hairLength', 'eye', 'hairRed',
                                        'hairGreen', 'hairBlue', 'combatStyle',
                                        'fnam'] # 'modt_p', 'fggs_p', 'fgga_p', 'fgts_p',

class ObPACKRecord(ObBaseRecord):
    _Type = 'PACK'
    flags = CBashGeneric(5, c_ulong)
    aiType = CBashGeneric(6, c_ubyte)
    unused1 = CBashUINT8ARRAY(7, 3)
    locType = CBashGeneric(8, c_long)
    locId = CBashFORMID_OR_UINT32(9)
    locRadius = CBashGeneric(10, c_long)
    month = CBashGeneric(11, c_byte)
    day = CBashGeneric(12, c_byte)
    date = CBashGeneric(13, c_ubyte)
    time = CBashGeneric(14, c_byte)
    duration = CBashGeneric(15, c_long)
    targetType = CBashGeneric(16, c_long)
    targetId = CBashFORMID_OR_UINT32(17)
    targetCount = CBashGeneric(18, c_long)

    def create_condition(self):
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 19, 0, 0, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, 19, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return Condition(self._CollectionID, self._ModID, self._RecordID, 19, length)
    conditions = CBashLIST(19, Condition)
    conditions_list = CBashLIST(19, Condition, True)

    IsOffersServices = CBashBasicFlag('flags', 0x00000001)
    IsMustReachLocation = CBashBasicFlag('flags', 0x00000002)
    IsMustComplete = CBashBasicFlag('flags', 0x00000004)
    IsLockAtStart = CBashBasicFlag('flags', 0x00000008)
    IsLockAtEnd = CBashBasicFlag('flags', 0x00000010)
    IsLockAtLocation = CBashBasicFlag('flags', 0x00000020)
    IsUnlockAtStart = CBashBasicFlag('flags', 0x00000040)
    IsUnlockAtEnd = CBashBasicFlag('flags', 0x00000080)
    IsUnlockAtLocation = CBashBasicFlag('flags', 0x00000100)
    IsContinueIfPcNear = CBashBasicFlag('flags', 0x00000200)
    IsOncePerDay = CBashBasicFlag('flags', 0x00000400)
    IsSkipFallout = CBashBasicFlag('flags', 0x00001000)
    IsAlwaysRun = CBashBasicFlag('flags', 0x00002000)
    IsAlwaysSneak = CBashBasicFlag('flags', 0x00020000)
    IsAllowSwimming = CBashBasicFlag('flags', 0x00040000)
    IsAllowFalls = CBashBasicFlag('flags', 0x00080000)
    IsUnequipArmor = CBashBasicFlag('flags', 0x00100000)
    IsUnequipWeapons = CBashBasicFlag('flags', 0x00200000)
    IsDefensiveCombat = CBashBasicFlag('flags', 0x00400000)
    IsUseHorse = CBashBasicFlag('flags', 0x00800000)
    IsNoIdleAnims = CBashBasicFlag('flags', 0x01000000)
    IsAIFind = CBashBasicType('aiType', 0, 'IsAIFollow')
    IsAIFollow = CBashBasicType('aiType', 1, 'IsAIFind')
    IsAIEscort = CBashBasicType('aiType', 2, 'IsAIFind')
    IsAIEat = CBashBasicType('aiType', 3, 'IsAIFind')
    IsAISleep = CBashBasicType('aiType', 4, 'IsAIFind')
    IsAIWander = CBashBasicType('aiType', 5, 'IsAIFind')
    IsAITravel = CBashBasicType('aiType', 6, 'IsAIFind')
    IsAIAccompany = CBashBasicType('aiType', 7, 'IsAIFind')
    IsAIUseItemAt = CBashBasicType('aiType', 8, 'IsAIFind')
    IsAIAmbush = CBashBasicType('aiType', 9, 'IsAIFind')
    IsAIFleeNotCombat = CBashBasicType('aiType', 10, 'IsAIFind')
    IsAICastMagic = CBashBasicType('aiType', 11, 'IsAIFind')
    IsLocNearReference = CBashBasicType('locType', 0, 'IsLocInCell')
    IsLocInCell = CBashBasicType('locType', 1, 'IsLocNearReference')
    IsLocNearCurrentLocation = CBashBasicType('locType', 2, 'IsLocNearReference')
    IsLocNearEditorLocation = CBashBasicType('locType', 3, 'IsLocNearReference')
    IsLocObjectID = CBashBasicType('locType', 4, 'IsLocNearReference')
    IsLocObjectType = CBashBasicType('locType', 5, 'IsLocNearReference')
    IsTargetReference = CBashBasicType('locType', 0, 'IsTargetObjectID')
    IsTargetObjectID = CBashBasicType('locType', 1, 'IsTargetReference')
    IsTargetObjectType = CBashBasicType('locType', 2, 'IsTargetReference')
    exportattrs = copyattrs = ObBaseRecord.baseattrs + ['flags', 'aiType', 'locType', 'locId',
                                        'locRadius', 'month', 'day', 'date', 'time',
                                        'duration', 'targetType', 'targetId',
                                        'targetCount', 'conditions_list']

class ObQUSTRecord(ObBaseRecord):
    _Type = 'QUST'
    class Stage(ListComponent):
        class Entry(ListX2Component):
            class ConditionX3(ListX3Component):
                operType = CBashGeneric_LISTX3(1, c_ubyte)
                unused1 = CBashUINT8ARRAY_LISTX3(2, 3)
                compValue = CBashFLOAT32_LISTX3(3)
                ifunc = CBashGeneric_LISTX3(4, c_ulong)
                param1 = CBashUNKNOWN_OR_FORMID_OR_UINT32_LISTX3(5)
                param2 = CBashUNKNOWN_OR_FORMID_OR_UINT32_LISTX3(6)
                unused2 = CBashUINT8ARRAY_LISTX3(7, 4)
                IsEqual = CBashMaskedType('operType', 0xF0, 0x00, 'IsNotEqual')
                IsNotEqual = CBashMaskedType('operType', 0xF0, 0x20, 'IsEqual')
                IsGreater = CBashMaskedType('operType', 0xF0, 0x40, 'IsEqual')
                IsGreaterOrEqual = CBashMaskedType('operType', 0xF0, 0x60, 'IsEqual')
                IsLess = CBashMaskedType('operType', 0xF0, 0x80, 'IsEqual')
                IsLessOrEqual = CBashMaskedType('operType', 0xF0, 0xA0, 'IsEqual')
                IsOr = CBashBasicFlag('operType', 0x01)
                IsRunOnTarget = CBashBasicFlag('operType', 0x02)
                IsUseGlobal = CBashBasicFlag('operType', 0x04)
                exportattrs = copyattrs = ['operType', 'compValue', 'ifunc', 'param1',
                             'param2']

            flags = CBashGeneric_LISTX2(1, c_ubyte)

            def create_condition(self):
                length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, self._FieldID, self._ListIndex, self._ListFieldID, self._ListX2Index, 2, 0, 0, 1)
                CBash.SetField(self._CollectionID, self._ModID, self._RecordID, self._FieldID, self._ListIndex, self._ListFieldID, self._ListX2Index, 2, 0, 0, 0, c_ulong(length + 1))
                return self.ConditionX3(self._CollectionID, self._ModID, self._RecordID, self._FieldID, self._ListIndex, self._ListFieldID, self._ListX2Index, 2, length)
            conditions = CBashLIST_LISTX2(2, ConditionX3)
            conditions_list = CBashLIST_LISTX2(2, ConditionX3, True)

            text = CBashSTRING_LISTX2(3)
            unused1 = CBashUINT8ARRAY_LISTX2(4, 4)
            numRefs = CBashGeneric_LISTX2(5, c_ulong)
            compiledSize = CBashGeneric_LISTX2(6, c_ulong)
            lastIndex = CBashGeneric_LISTX2(7, c_ulong)
            scriptType = CBashGeneric_LISTX2(8, c_ulong)
            compiled_p = CBashUINT8ARRAY_LISTX2(9)
            scriptText = CBashISTRING_LISTX2(10)
            references = CBashFORMID_OR_UINT32_ARRAY_LISTX2(11)
            IsCompletes = CBashBasicFlag('flags', 0x00000001)
            copyattrs = ['flags', 'conditions_list', 'text', 'numRefs', 'compiledSize',
                         'lastIndex', 'scriptType', 'compiled_p', 'scriptText',
                         'references']
            exportattrs = ['flags', 'conditions_list', 'text', 'numRefs', 'compiledSize',
                         'lastIndex', 'scriptType', 'scriptText',
                         'references'] #'compiled_p',

        stage = CBashGeneric_LIST(1, c_ushort)

        def create_entry(self):
            length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, self._FieldID, self._ListIndex, 2, 0, 0, 0, 0, 1)
            CBash.SetField(self._CollectionID, self._ModID, self._RecordID, self._FieldID, self._ListIndex, 2, 0, 0, 0, 0, 0, c_ulong(length + 1))
            return self.Entry(self._CollectionID, self._ModID, self._RecordID, self._FieldID, self._ListIndex, 2, length)
        entries = CBashLIST_LIST(2, Entry)
        entries_list = CBashLIST_LIST(2, Entry, True)

        exportattrs = copyattrs = ['stage', 'entries_list']

    class Target(ListComponent):
        class ConditionX2(ListX2Component):
            operType = CBashGeneric_LISTX2(1, c_ubyte)
            unused1 = CBashUINT8ARRAY_LISTX2(2, 3)
            compValue = CBashFLOAT32_LISTX2(3)
            ifunc = CBashGeneric_LISTX2(4, c_ulong)
            param1 = CBashUNKNOWN_OR_FORMID_OR_UINT32_LISTX2(5)
            param2 = CBashUNKNOWN_OR_FORMID_OR_UINT32_LISTX2(6)
            unused2 = CBashUINT8ARRAY_LISTX2(7, 4)
            IsEqual = CBashMaskedType('operType', 0xF0, 0x00, 'IsNotEqual')
            IsNotEqual = CBashMaskedType('operType', 0xF0, 0x20, 'IsEqual')
            IsGreater = CBashMaskedType('operType', 0xF0, 0x40, 'IsEqual')
            IsGreaterOrEqual = CBashMaskedType('operType', 0xF0, 0x60, 'IsEqual')
            IsLess = CBashMaskedType('operType', 0xF0, 0x80, 'IsEqual')
            IsLessOrEqual = CBashMaskedType('operType', 0xF0, 0xA0, 'IsEqual')
            IsOr = CBashBasicFlag('operType', 0x01)
            IsRunOnTarget = CBashBasicFlag('operType', 0x02)
            IsUseGlobal = CBashBasicFlag('operType', 0x04)
            exportattrs = copyattrs = ['operType', 'compValue', 'ifunc', 'param1',
                         'param2']

        targetId = CBashFORMID_LIST(1)
        flags = CBashGeneric_LIST(2, c_ubyte)
        unused1 = CBashUINT8ARRAY_LIST(3, 3)

        def create_condition(self):
            length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, self._FieldID, self._ListIndex, 4, 0, 0, 0, 0, 1)
            CBash.SetField(self._CollectionID, self._ModID, self._RecordID, self._FieldID, self._ListIndex, 4, 0, 0, 0, 0, 0, c_ulong(length + 1))
            return self.ConditionX2(self._CollectionID, self._ModID, self._RecordID, self._FieldID, self._ListIndex, 4, length)
        conditions = CBashLIST_LIST(4, ConditionX2)
        conditions_list = CBashLIST_LIST(4, ConditionX2, True)

        IsIgnoresLocks = CBashBasicFlag('flags', 0x00000001)
        exportattrs = copyattrs = ['targetId', 'flags', 'conditions_list']

    script = CBashFORMID(5)
    full = CBashSTRING(6)
    iconPath = CBashISTRING(7)
    flags = CBashGeneric(8, c_ubyte)
    priority = CBashGeneric(9, c_ubyte)

    def create_condition(self):
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 10, 0, 0, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, 10, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return Condition(self._CollectionID, self._ModID, self._RecordID, 10, length)
    conditions = CBashLIST(10, Condition)
    conditions_list = CBashLIST(10, Condition, True)

    def create_stage(self):
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 11, 0, 0, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, 11, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return self.Stage(self._CollectionID, self._ModID, self._RecordID, 11, length)
    stages = CBashLIST(11, Stage)
    stages_list = CBashLIST(11, Stage, True)

    def create_target(self):
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 12, 0, 0, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, 12, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return self.Target(self._CollectionID, self._ModID, self._RecordID, 12, length)
    targets = CBashLIST(12, Target)
    targets_list = CBashLIST(12, Target, True)

    IsStartEnabled = CBashBasicFlag('flags', 0x00000001)
    IsRepeatedTopics = CBashBasicFlag('flags', 0x00000004)
    IsRepeatedStages = CBashBasicFlag('flags', 0x00000008)
    exportattrs = copyattrs = ObBaseRecord.baseattrs + ['script', 'full', 'iconPath',
                                        'flags', 'priority', 'conditions_list',
                                        'stages_list', 'targets_list']

class ObRACERecord(ObBaseRecord):
    _Type = 'RACE'
    class RaceModel(BaseComponent):
        modPath = CBashISTRING_GROUP(0)
        modb = CBashFLOAT32_GROUP(1)
        iconPath = CBashISTRING_GROUP(2)
        modt_p = CBashUINT8ARRAY_GROUP(3)
        copyattrs = ['modPath', 'modb', 'iconPath', 'modt_p']
        exportattrs = ['modPath', 'modb', 'iconPath']#, 'modt_p']

    full = CBashSTRING(5)
    text = CBashSTRING(6)
    spells = CBashFORMIDARRAY(7)

    def create_relation(self):
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 8, 0, 0, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, 8, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return Relation(self._CollectionID, self._ModID, self._RecordID, 8, length)
    relations = CBashLIST(8, Relation)
    relations_list = CBashLIST(8, Relation, True)

    skill1 = CBashGeneric(9, c_byte)
    skill1Boost = CBashGeneric(10, c_byte)
    skill2 = CBashGeneric(11, c_byte)
    skill2Boost = CBashGeneric(12, c_byte)
    skill3 = CBashGeneric(13, c_byte)
    skill3Boost = CBashGeneric(14, c_byte)
    skill4 = CBashGeneric(15, c_byte)
    skill4Boost = CBashGeneric(16, c_byte)
    skill5 = CBashGeneric(17, c_byte)
    skill5Boost = CBashGeneric(18, c_byte)
    skill6 = CBashGeneric(19, c_byte)
    skill6Boost = CBashGeneric(20, c_byte)
    skill7 = CBashGeneric(21, c_byte)
    skill7Boost = CBashGeneric(22, c_byte)
    unused1 = CBashUINT8ARRAY(23, 2)
    maleHeight = CBashFLOAT32(24)
    femaleHeight = CBashFLOAT32(25)
    maleWeight = CBashFLOAT32(26)
    femaleWeight = CBashFLOAT32(27)
    flags = CBashGeneric(28, c_ulong)
    maleVoice = CBashFORMID(29)
    femaleVoice = CBashFORMID(30)
    defaultHairMale = CBashFORMID(31)
    defaultHairFemale = CBashFORMID(32)
    defaultHairColor = CBashGeneric(33, c_ubyte)
    mainClamp = CBashFLOAT32(34)
    faceClamp = CBashFLOAT32(35)
    maleStrength = CBashGeneric(36, c_ubyte)
    maleIntelligence = CBashGeneric(37, c_ubyte)
    maleWillpower = CBashGeneric(38, c_ubyte)
    maleAgility = CBashGeneric(39, c_ubyte)
    maleSpeed = CBashGeneric(40, c_ubyte)
    maleEndurance = CBashGeneric(41, c_ubyte)
    malePersonality = CBashGeneric(42, c_ubyte)
    maleLuck = CBashGeneric(43, c_ubyte)
    femaleStrength = CBashGeneric(44, c_ubyte)
    femaleIntelligence = CBashGeneric(45, c_ubyte)
    femaleWillpower = CBashGeneric(46, c_ubyte)
    femaleAgility = CBashGeneric(47, c_ubyte)
    femaleSpeed = CBashGeneric(48, c_ubyte)
    femaleEndurance = CBashGeneric(49, c_ubyte)
    femalePersonality = CBashGeneric(50, c_ubyte)
    femaleLuck = CBashGeneric(51, c_ubyte)
    head = CBashGrouped(52, RaceModel)
    head_list = CBashGrouped(52, RaceModel, True)

    maleEars = CBashGrouped(56, RaceModel)
    maleEars_list = CBashGrouped(56, RaceModel, True)

    femaleEars = CBashGrouped(60, RaceModel)
    femaleEars_list = CBashGrouped(60, RaceModel, True)

    mouth = CBashGrouped(64, RaceModel)
    mouth_list = CBashGrouped(64, RaceModel, True)

    teethLower = CBashGrouped(68, RaceModel)
    teethLower_list = CBashGrouped(68, RaceModel, True)

    teethUpper = CBashGrouped(72, RaceModel)
    teethUpper_list = CBashGrouped(72, RaceModel, True)

    tongue = CBashGrouped(76, RaceModel)
    tongue_list = CBashGrouped(76, RaceModel, True)

    leftEye = CBashGrouped(80, RaceModel)
    leftEye_list = CBashGrouped(80, RaceModel, True)

    rightEye = CBashGrouped(84, RaceModel)
    rightEye_list = CBashGrouped(84, RaceModel, True)

    maleTail = CBashGrouped(88, Model)
    maleTail_list = CBashGrouped(88, Model, True)

    maleUpperBodyPath = CBashISTRING(91)
    maleLowerBodyPath = CBashISTRING(92)
    maleHandPath = CBashISTRING(93)
    maleFootPath = CBashISTRING(94)
    maleTailPath = CBashISTRING(95)
    femaleTail = CBashGrouped(96, Model)
    femaleTail_list = CBashGrouped(96, Model, True)

    femaleUpperBodyPath = CBashISTRING(99)
    femaleLowerBodyPath = CBashISTRING(100)
    femaleHandPath = CBashISTRING(101)
    femaleFootPath = CBashISTRING(102)
    femaleTailPath = CBashISTRING(103)
    hairs = CBashFORMIDARRAY(104)
    eyes = CBashFORMIDARRAY(105)
    fggs_p = CBashUINT8ARRAY(106, 200)
    fgga_p = CBashUINT8ARRAY(107, 120)
    fgts_p = CBashUINT8ARRAY(108, 200)
    snam_p = CBashUINT8ARRAY(109, 2)
    IsPlayable = CBashBasicFlag('flags', 0x00000001)
    copyattrs = ObBaseRecord.baseattrs + ['full', 'text', 'spells',
                                        'relations_list', 'skill1', 'skill1Boost',
                                        'skill2', 'skill2Boost', 'skill3',
                                        'skill3Boost', 'skill4', 'skill4Boost',
                                        'skill5', 'skill5Boost', 'skill6',
                                        'skill6Boost', 'skill7', 'skill7Boost',
                                        'maleHeight', 'femaleHeight',
                                        'maleWeight', 'femaleWeight', 'flags',
                                        'maleVoice', 'femaleVoice',
                                        'defaultHairMale',
                                        'defaultHairFemale',
                                        'defaultHairColor', 'mainClamp',
                                        'faceClamp', 'maleStrength',
                                        'maleIntelligence', 'maleAgility',
                                        'maleSpeed', 'maleEndurance',
                                        'malePersonality', 'maleLuck',
                                        'femaleStrength', 'femaleIntelligence',
                                        'femaleWillpower', 'femaleAgility',
                                        'femaleSpeed', 'femaleEndurance',
                                        'femalePersonality', 'femaleLuck',
                                        'head_list', 'maleEars_list', 'femaleEars_list',
                                        'mouth_list', 'teethLower_list', 'teethUpper_list',
                                        'tongue_list', 'leftEye_list', 'rightEye_list',
                                        'maleTail_list', 'maleUpperBodyPath',
                                        'maleLowerBodyPath', 'maleHandPath',
                                        'maleFootPath', 'maleTailPath',
                                        'femaleTail_list', 'femaleUpperBodyPath',
                                        'femaleLowerBodyPath', 'femaleHandPath',
                                        'femaleFootPath', 'femaleTailPath',
                                        'hairs', 'eyes', 'fggs_p',
                                        'fgga_p', 'fgts_p', 'snam_p']
    exportattrs = ObBaseRecord.baseattrs + ['full', 'text', 'spells',
                                        'relations_list', 'skill1', 'skill1Boost',
                                        'skill2', 'skill2Boost', 'skill3',
                                        'skill3Boost', 'skill4', 'skill4Boost',
                                        'skill5', 'skill5Boost', 'skill6',
                                        'skill6Boost', 'skill7', 'skill7Boost',
                                        'maleHeight', 'femaleHeight',
                                        'maleWeight', 'femaleWeight', 'flags',
                                        'maleVoice', 'femaleVoice',
                                        'defaultHairMale',
                                        'defaultHairFemale',
                                        'defaultHairColor', 'mainClamp',
                                        'faceClamp', 'maleStrength',
                                        'maleIntelligence', 'maleAgility',
                                        'maleSpeed', 'maleEndurance',
                                        'malePersonality', 'maleLuck',
                                        'femaleStrength', 'femaleIntelligence',
                                        'femaleWillpower', 'femaleAgility',
                                        'femaleSpeed', 'femaleEndurance',
                                        'femalePersonality', 'femaleLuck',
                                        'head_list', 'maleEars_list', 'femaleEars_list',
                                        'mouth_list', 'teethLower_list', 'teethUpper_list',
                                        'tongue_list', 'leftEye_list', 'rightEye_list',
                                        'maleTail_list', 'maleUpperBodyPath',
                                        'maleLowerBodyPath', 'maleHandPath',
                                        'maleFootPath', 'maleTailPath',
                                        'femaleTail_list', 'femaleUpperBodyPath',
                                        'femaleLowerBodyPath', 'femaleHandPath',
                                        'femaleFootPath', 'femaleTailPath',
                                        'hairs', 'eyes'] # 'fggs_p','fgga_p', 'fgts_p', 'snam_p'

class ObREGNRecord(ObBaseRecord):
    _Type = 'REGN'
    class Area(ListComponent):
        class Point(ListX2Component):
            posX = CBashFLOAT32_LISTX2(1)
            posY = CBashFLOAT32_LISTX2(2)
            exportattrs = copyattrs = ['posX', 'posY']

        edgeFalloff = CBashFORMID_LIST(1)

        def create_point(self):
            length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, self._FieldID, self._ListIndex, 2, 0, 0, 0, 0, 1)
            CBash.SetField(self._CollectionID, self._ModID, self._RecordID, self._FieldID, self._ListIndex, 2, 0, 0, 0, 0, 0, c_ulong(length + 1))
            return self.Point(self._CollectionID, self._ModID, self._RecordID, self._FieldID, self._ListIndex, 2, length)
        points = CBashLIST_LIST(2, Point)
        points_list = CBashLIST_LIST(2, Point, True)

        exportattrs = copyattrs = ['edgeFalloff', 'points_list']

    class Entry(ListComponent):
        class Object(ListX2Component):
            objectId = CBashFORMID_LISTX2(1)
            parentIndex = CBashGeneric_LISTX2(2, c_ushort)
            unused1 = CBashUINT8ARRAY_LISTX2(3, 2)
            density = CBashFLOAT32_LISTX2(4)
            clustering = CBashGeneric_LISTX2(5, c_ubyte)
            minSlope = CBashGeneric_LISTX2(6, c_ubyte)
            maxSlope = CBashGeneric_LISTX2(7, c_ubyte)
            flags = CBashGeneric_LISTX2(8, c_ubyte)
            radiusWRTParent = CBashGeneric_LISTX2(9, c_ushort)
            radius = CBashGeneric_LISTX2(10, c_ushort)
            unk1 = CBashUINT8ARRAY_LISTX2(11, 4)
            maxHeight = CBashFLOAT32_LISTX2(12)
            sink = CBashFLOAT32_LISTX2(13)
            sinkVar = CBashFLOAT32_LISTX2(14)
            sizeVar = CBashFLOAT32_LISTX2(15)
            angleVarX = CBashGeneric_LISTX2(16, c_ushort)
            angleVarY = CBashGeneric_LISTX2(17, c_ushort)
            angleVarZ = CBashGeneric_LISTX2(18, c_ushort)
            unused2 = CBashUINT8ARRAY_LISTX2(19, 1)
            unk2 = CBashUINT8ARRAY_LISTX2(20, 4)
            IsConformToSlope = CBashBasicFlag('flags', 0x00000001)
            IsPaintVertices = CBashBasicFlag('flags', 0x00000002)
            IsSizeVariance = CBashBasicFlag('flags', 0x00000004)
            IsXVariance = CBashBasicFlag('flags', 0x00000008)
            IsYVariance = CBashBasicFlag('flags', 0x00000010)
            IsZVariance = CBashBasicFlag('flags', 0x00000020)
            IsTree = CBashBasicFlag('flags', 0x00000040)
            IsHugeRock = CBashBasicFlag('flags', 0x00000080)
            exportattrs = copyattrs = ['objectId', 'parentIndex', 'density', 'clustering',
                         'minSlope', 'maxSlope', 'flags', 'radiusWRTParent',
                         'radius', 'unk1', 'maxHeight', 'sink', 'sinkVar',
                         'sizeVar', 'angleVarX', 'angleVarY', 'angleVarZ',
                         'unk2']

        class Grass(ListX2Component):
            grass = CBashFORMID_LISTX2(1)
            unk1 = CBashUINT8ARRAY_LISTX2(2, 4)
            exportattrs = copyattrs = ['grass', 'unk1']

        class Sound(ListX2Component):
            sound = CBashFORMID_LISTX2(1)
            flags = CBashGeneric_LISTX2(2, c_ulong)
            chance = CBashGeneric_LISTX2(3, c_ulong)
            IsPleasant = CBashBasicFlag('flags', 0x00000001)
            IsCloudy = CBashBasicFlag('flags', 0x00000002)
            IsRainy = CBashBasicFlag('flags', 0x00000004)
            IsSnowy = CBashBasicFlag('flags', 0x00000008)
            exportattrs = copyattrs = ['sound', 'flags', 'chance']

        class Weather(ListX2Component):
            weather = CBashFORMID_LISTX2(1)
            chance = CBashGeneric_LISTX2(2, c_ulong)
            exportattrs = copyattrs = ['weather', 'chance']

        entryType = CBashGeneric_LIST(1, c_ulong)
        flags = CBashGeneric_LIST(2, c_ubyte)
        priority = CBashGeneric_LIST(3, c_ubyte)
        unused1 = CBashUINT8ARRAY_LIST(4, 4)

        def create_object(self):
            length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, self._FieldID, self._ListIndex, 5, 0, 0, 0, 0, 1)
            CBash.SetField(self._CollectionID, self._ModID, self._RecordID, self._FieldID, self._ListIndex, 5, 0, 0, 0, 0, 0, c_ulong(length + 1))
            return self.Object(self._CollectionID, self._ModID, self._RecordID, self._FieldID, self._ListIndex, 5, length)
        objects = CBashLIST_LIST(5, Object)
        objects_list = CBashLIST_LIST(5, Object, True)

        mapName = CBashSTRING_LIST(6)
        iconPath = CBashISTRING_LIST(7)

        def create_grass(self):
            length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, self._FieldID, self._ListIndex, 8, 0, 0, 0, 0, 1)
            CBash.SetField(self._CollectionID, self._ModID, self._RecordID, self._FieldID, self._ListIndex, 8, 0, 0, 0, 0, 0, c_ulong(length + 1))
            return self.Grass(self._CollectionID, self._ModID, self._RecordID, self._FieldID, self._ListIndex, 8, length)
        grasses = CBashLIST_LIST(8, Grass)
        grasses_list = CBashLIST_LIST(8, Grass, True)

        musicType = CBashGeneric_LIST(9, c_ulong)

        def create_sound(self):
            length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, self._FieldID, self._ListIndex, 10, 0, 0, 0, 0, 1)
            CBash.SetField(self._CollectionID, self._ModID, self._RecordID, self._FieldID, self._ListIndex, 10, 0, 0, 0, 0, 0, c_ulong(length + 1))
            return self.Sound(self._CollectionID, self._ModID, self._RecordID, self._FieldID, self._ListIndex, 10, length)
        sounds = CBashLIST_LIST(10, Sound)
        sounds_list = CBashLIST_LIST(10, Sound, True)

        def create_weather(self):
            length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, self._FieldID, self._ListIndex, 11, 0, 0, 0, 0, 1)
            CBash.SetField(self._CollectionID, self._ModID, self._RecordID, self._FieldID, self._ListIndex, 11, 0, 0, 0, 0, 0, c_ulong(length + 1))
            return self.Weather(self._CollectionID, self._ModID, self._RecordID, self._FieldID, self._ListIndex, 11, length)
        weathers = CBashLIST_LIST(11, Weather)
        weathers_list = CBashLIST_LIST(11, Weather, True)

        IsObject = CBashBasicType('entryType', 2, 'IsWeather')
        IsWeather = CBashBasicType('entryType', 3, 'IsObject')
        IsMap = CBashBasicType('entryType', 4, 'IsObject')
        IsIcon = CBashBasicType('entryType', 5, 'IsObject')
        IsGrass = CBashBasicType('entryType', 6, 'IsObject')
        IsSound = CBashBasicType('entryType', 7, 'IsObject')
        IsDefault = CBashBasicType('musicType', 0, 'IsPublic')
        IsPublic = CBashBasicType('musicType', 1, 'IsDefault')
        IsDungeon = CBashBasicType('musicType', 2, 'IsDefault')
        IsOverride = CBashBasicFlag('flags', 0x00000001)
        exportattrs = copyattrs = ['entryType', 'flags', 'priority', 'objects_list', 'mapName',
                     'iconPath', 'grasses_list', 'musicType', 'sounds_list', 'weathers_list']

    iconPath = CBashISTRING(5)
    mapRed = CBashGeneric(6, c_ubyte)
    mapGreen = CBashGeneric(7, c_ubyte)
    mapBlue = CBashGeneric(8, c_ubyte)
    unused1 = CBashUINT8ARRAY(9, 1)
    worldspace = CBashFORMID(10)

    def create_area(self):
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 11, 0, 0, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, 11, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return self.Area(self._CollectionID, self._ModID, self._RecordID, 11, length)
    areas = CBashLIST(11, Area)
    areas_list = CBashLIST(11, Area, True)

    def create_entry(self):
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 12, 0, 0, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, 12, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return self.Entry(self._CollectionID, self._ModID, self._RecordID, 12, length)
    entries = CBashLIST(12, Entry)
    entries_list = CBashLIST(12, Entry, True)

    exportattrs = copyattrs = ObBaseRecord.baseattrs + ['iconPath', 'mapRed', 'mapGreen',
                                        'mapBlue', 'worldspace', 'areas_list',
                                        'entries_list']

class ObSBSPRecord(ObBaseRecord):
    _Type = 'SBSP'
    sizeX = CBashFLOAT32(5)
    sizeY = CBashFLOAT32(6)
    sizeZ = CBashFLOAT32(7)
    exportattrs = copyattrs = ObBaseRecord.baseattrs + ['sizeX', 'sizeY', 'sizeZ']

class ObSCPTRecord(ObBaseRecord):
    _Type = 'SCPT'
    class Var(ListComponent):
        index = CBashGeneric_LIST(1, c_ulong)
        unused1 = CBashUINT8ARRAY_LIST(2, 12)
        flags = CBashGeneric_LIST(3, c_ubyte)
        unused2 = CBashUINT8ARRAY_LIST(4, 7)
        name = CBashISTRING_LIST(5)
        IsLongOrShort = CBashBasicFlag('flags', 0x00000001)
        exportattrs = copyattrs = ['index', 'flags', 'name']

    unused1 = CBashUINT8ARRAY(5, 2)
    numRefs = CBashGeneric(6, c_ulong)
    compiledSize = CBashGeneric(7, c_ulong)
    lastIndex = CBashGeneric(8, c_ulong)
    scriptType = CBashGeneric(9, c_ulong)
    compiled_p = CBashUINT8ARRAY(10)
    scriptText = CBashISTRING(11)

    def create_var(self):
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 12, 0, 0, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, 12, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return self.Var(self._CollectionID, self._ModID, self._RecordID, 12, length)
    vars = CBashLIST(12, Var)
    vars_list = CBashLIST(12, Var, True)

    references = CBashFORMID_OR_UINT32_ARRAY(13)

    IsObject = CBashBasicType('scriptType', 0x00000000, 'IsQuest')
    IsQuest = CBashBasicType('scriptType', 0x00000001, 'IsObject')
    IsMagicEffect = CBashBasicType('scriptType', 0x00000100, 'IsObject')
    copyattrs = ObBaseRecord.baseattrs + ['numRefs', 'compiledSize', 'lastIndex',
                                        'scriptType', 'compiled_p', 'scriptText',
                                        'vars_list', 'references']
    exportattrs = ObBaseRecord.baseattrs + ['numRefs', 'compiledSize', 'lastIndex',
                                        'scriptType', 'scriptText',
                                        'vars_list', 'references'] #'compiled_p',

class ObSGSTRecord(ObBaseRecord):
    _Type = 'SGST'
    full = CBashSTRING(5)
    modPath = CBashISTRING(6)
    modb = CBashFLOAT32(7)
    modt_p = CBashUINT8ARRAY(8)
    iconPath = CBashISTRING(9)
    script = CBashFORMID(10)

    def create_effect(self):
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 11, 0, 0, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, 11, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return Effect(self._CollectionID, self._ModID, self._RecordID, 11, length)
    effects = CBashLIST(11, Effect)
    effects_list = CBashLIST(11, Effect, True)

    uses = CBashGeneric(12, c_ubyte)
    value = CBashGeneric(13, c_long)
    weight = CBashFLOAT32(14)
    ##OBME Fields. Setting any of the below fields will make the mod require JRoush's OBME plugin for OBSE
    ##To see if OBME is in use, check the recordVersion field for a non-None value
    recordVersion = CBashGeneric(15, c_ubyte)
    betaVersion = CBashGeneric(16, c_ubyte)
    minorVersion = CBashGeneric(17, c_ubyte)
    majorVersion = CBashGeneric(18, c_ubyte)
    reserved = CBashUINT8ARRAY(19, 0x1C)
    datx_p = CBashUINT8ARRAY(20, 0x20)
    copyattrs = ObBaseRecord.baseattrs + ['full', 'modPath', 'modb', 'modt_p',
                                        'iconPath', 'script', 'effects_list',
                                        'uses', 'value', 'weight']
    exportattrs = ObBaseRecord.baseattrs + ['full', 'modPath', 'modb',
                                        'iconPath', 'script', 'effects_list',
                                        'uses', 'value', 'weight'] # 'modt_p',
    copyattrsOBME = copyattrs + ['recordVersion', 'betaVersion',
                                 'minorVersion', 'majorVersion',
                                 'reserved'] #, 'datx_p'

class ObSKILRecord(ObBaseRecord):
    _Type = 'SKIL'
    skill = CBashGeneric(5, c_long)
    description = CBashSTRING(6)
    iconPath = CBashISTRING(7)
    action = CBashGeneric(8, c_long)
    attribute = CBashGeneric(9, c_long)
    specialization = CBashGeneric(10, c_ulong)
    use0 = CBashFLOAT32(11)
    use1 = CBashFLOAT32(12)
    apprentice = CBashSTRING(13)
    journeyman = CBashSTRING(14)
    expert = CBashSTRING(15)
    master = CBashSTRING(16)
    exportattrs = copyattrs = ObBaseRecord.baseattrs + ['skill', 'description', 'iconPath',
                                        'action', 'attribute', 'specialization',
                                        'use0', 'use1', 'apprentice',
                                        'journeyman', 'expert', 'master']

class ObSLGMRecord(ObBaseRecord):
    _Type = 'SLGM'
    full = CBashSTRING(5)
    modPath = CBashISTRING(6)
    modb = CBashFLOAT32(7)
    modt_p = CBashUINT8ARRAY(8)
    iconPath = CBashISTRING(9)
    script = CBashFORMID(10)
    value = CBashGeneric(11, c_long)
    weight = CBashFLOAT32(12)
    soulType = CBashGeneric(13, c_ubyte)
    capacityType = CBashGeneric(14, c_ubyte)
    IsNoSoul = CBashBasicType('soulType', 0, 'IsPettySoul')
    IsPettySoul = CBashBasicType('soulType', 1, 'IsNoSoul')
    IsLesserSoul = CBashBasicType('soulType', 2, 'IsNoSoul')
    IsCommonSoul = CBashBasicType('soulType', 3, 'IsNoSoul')
    IsGreaterSoul = CBashBasicType('soulType', 4, 'IsNoSoul')
    IsGrandSoul = CBashBasicType('soulType', 5, 'IsNoSoul')
    IsNoCapacity = CBashBasicType('capacityType', 0, 'IsPettyCapacity')
    IsPettyCapacity = CBashBasicType('capacityType', 1, 'IsNoCapacity')
    IsLesserCapacity = CBashBasicType('capacityType', 2, 'IsNoCapacity')
    IsCommonCapacity = CBashBasicType('capacityType', 3, 'IsNoCapacity')
    IsGreaterCapacity = CBashBasicType('capacityType', 4, 'IsNoCapacity')
    IsGrandCapacity = CBashBasicType('capacityType', 5, 'IsNoCapacity')
    copyattrs = ObBaseRecord.baseattrs + ['full', 'modPath', 'modb', 'modt_p',
                                        'iconPath', 'script', 'value',
                                        'weight', 'soulType', 'capacityType']
    exportattrs = ObBaseRecord.baseattrs + ['full', 'modPath', 'modb',
                                        'iconPath', 'script', 'value',
                                        'weight', 'soulType', 'capacityType'] # 'modt_p',

class ObSOUNRecord(ObBaseRecord):
    _Type = 'SOUN'
    soundPath = CBashISTRING(5)
    minDistance = CBashGeneric(6, c_ubyte)
    maxDistance = CBashGeneric(7, c_ubyte)
    freqAdjustment = CBashGeneric(8, c_byte)
    unused1 = CBashUINT8ARRAY(9, 1)
    flags = CBashGeneric(10, c_ushort)
    unused2 = CBashUINT8ARRAY(11, 2)
    staticAtten = CBashGeneric(12, c_short)
    stopTime = CBashGeneric(13, c_ubyte)
    startTime = CBashGeneric(14, c_ubyte)
    IsRandomFrequencyShift = CBashBasicFlag('flags', 0x00000001)
    IsPlayAtRandom = CBashBasicFlag('flags', 0x00000002)
    IsEnvironmentIgnored = CBashBasicFlag('flags', 0x00000004)
    IsRandomLocation = CBashBasicFlag('flags', 0x00000008)
    IsLoop = CBashBasicFlag('flags', 0x00000010)
    IsMenuSound = CBashBasicFlag('flags', 0x00000020)
    Is2D = CBashBasicFlag('flags', 0x00000040)
    Is360LFE = CBashBasicFlag('flags', 0x00000080)
    exportattrs = copyattrs = ObBaseRecord.baseattrs + ['soundPath', 'minDistance', 'maxDistance',
                                        'freqAdjustment', 'flags', 'staticAtten',
                                        'stopTime', 'startTime']

class ObSPELRecord(ObBaseRecord):
    _Type = 'SPEL'
    full = CBashSTRING(5)
    spellType = CBashGeneric(6, c_ulong)
    cost = CBashGeneric(7, c_ulong)
    levelType = CBashGeneric(8, c_ulong)
    flags = CBashGeneric(9, c_ubyte)
    unused1 = CBashUINT8ARRAY(10, 3)

    def create_effect(self):
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 11, 0, 0, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, 11, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return Effect(self._CollectionID, self._ModID, self._RecordID, 11, length)
    effects = CBashLIST(11, Effect)
    effects_list = CBashLIST(11, Effect, True)

    IsManualCost = CBashBasicFlag('flags', 0x00000001)
    IsStartSpell = CBashBasicFlag('flags', 0x00000004)
    IsSilenceImmune = CBashBasicFlag('flags', 0x0000000A)
    IsAreaEffectIgnoresLOS = CBashBasicFlag('flags', 0x00000010)
    IsAEIgnoresLOS = CBashAlias('IsAreaEffectIgnoresLOS')
    IsScriptAlwaysApplies = CBashBasicFlag('flags', 0x00000020)
    IsDisallowAbsorbReflect = CBashBasicFlag('flags', 0x00000040)
    IsDisallowAbsorb = CBashAlias('IsDisallowAbsorbReflect')
    IsDisallowReflect = CBashAlias('IsDisallowAbsorbReflect')
    IsTouchExplodesWOTarget = CBashBasicFlag('flags', 0x00000080)
    IsTouchExplodes = CBashAlias('IsTouchExplodesWOTarget')
    IsSpell = CBashBasicType('spellType', 0, 'IsDisease')
    IsDisease = CBashBasicType('spellType', 1, 'IsSpell')
    IsPower = CBashBasicType('spellType', 2, 'IsSpell')
    IsLesserPower = CBashBasicType('spellType', 3, 'IsSpell')
    IsAbility = CBashBasicType('spellType', 4, 'IsSpell')
    IsPoison = CBashBasicType('spellType', 5, 'IsSpell')
    IsNovice = CBashBasicType('levelType', 0, 'IsApprentice')
    IsApprentice = CBashBasicType('levelType', 1, 'IsNovice')
    IsJourneyman = CBashBasicType('levelType', 2, 'IsNovice')
    IsExpert = CBashBasicType('levelType', 3, 'IsNovice')
    IsMaster = CBashBasicType('levelType', 4, 'IsNovice')
    ##OBME Fields. Setting any of the below fields will make the mod require JRoush's OBME plugin for OBSE
    ##To see if OBME is in use, check the recordVersion field for a non-None value
    recordVersion = CBashGeneric(12, c_ubyte)
    betaVersion = CBashGeneric(13, c_ubyte)
    minorVersion = CBashGeneric(14, c_ubyte)
    majorVersion = CBashGeneric(15, c_ubyte)
    reserved = CBashUINT8ARRAY(16, 0x1C)
    datx_p = CBashUINT8ARRAY(17, 0x20)
    exportattrs = copyattrs = ObBaseRecord.baseattrs + ['full', 'spellType', 'cost',
                                        'levelType', 'flags', 'effects_list']
    copyattrsOBME = copyattrs + ['recordVersion', 'betaVersion',
                                 'minorVersion', 'majorVersion',
                                 'reserved'] #, 'datx_p'

class ObSTATRecord(ObBaseRecord):
    _Type = 'STAT'
    modPath = CBashISTRING(5)
    modb = CBashFLOAT32(6)
    modt_p = CBashUINT8ARRAY(7)
    copyattrs = ObBaseRecord.baseattrs + ['modPath', 'modb', 'modt_p']
    exportattrs = ObBaseRecord.baseattrs + ['modPath', 'modb']#, 'modt_p']

class ObTREERecord(ObBaseRecord):
    _Type = 'TREE'
    modPath = CBashISTRING(5)
    modb = CBashFLOAT32(6)
    modt_p = CBashUINT8ARRAY(7)
    iconPath = CBashISTRING(8)
    speedTree = CBashUINT32ARRAY(9)
    curvature = CBashFLOAT32(10)
    minAngle = CBashFLOAT32(11)
    maxAngle = CBashFLOAT32(12)
    branchDim = CBashFLOAT32(13)
    leafDim = CBashFLOAT32(14)
    shadowRadius = CBashGeneric(15, c_long)
    rockSpeed = CBashFLOAT32(16)
    rustleSpeed = CBashFLOAT32(17)
    widthBill = CBashFLOAT32(18)
    heightBill = CBashFLOAT32(19)
    copyattrs = ObBaseRecord.baseattrs + ['modPath', 'modb', 'modt_p', 'iconPath',
                                        'speedTree', 'curvature', 'minAngle',
                                        'maxAngle', 'branchDim', 'leafDim',
                                        'shadowRadius', 'rockSpeed',
                                        'rustleSpeed', 'widthBill', 'heightBill']
    exportattrs = ObBaseRecord.baseattrs + ['modPath', 'modb', 'iconPath',
                                        'speedTree', 'curvature', 'minAngle',
                                        'maxAngle', 'branchDim', 'leafDim',
                                        'shadowRadius', 'rockSpeed',
                                        'rustleSpeed', 'widthBill', 'heightBill'] #'modt_p',

class ObWATRRecord(ObBaseRecord):
    _Type = 'WATR'
    texturePath = CBashISTRING(5)
    opacity = CBashGeneric(6, c_ubyte)
    flags = CBashGeneric(7, c_ubyte)
    materialPath = CBashISTRING(8)
    sound = CBashFORMID(9)
    windVelocity = CBashFLOAT32(10)
    windDirection = CBashFLOAT32(11)
    waveAmp = CBashFLOAT32(12)
    waveFreq = CBashFLOAT32(13)
    sunPower = CBashFLOAT32(14)
    reflectAmt = CBashFLOAT32(15)
    fresnelAmt = CBashFLOAT32(16)
    xSpeed = CBashFLOAT32(17)
    ySpeed = CBashFLOAT32(18)
    fogNear = CBashFLOAT32(19)
    fogFar = CBashFLOAT32(20)
    shallowRed = CBashGeneric(21, c_ubyte)
    shallowGreen = CBashGeneric(22, c_ubyte)
    shallowBlue = CBashGeneric(23, c_ubyte)
    unused1 = CBashUINT8ARRAY(24, 1)
    deepRed = CBashGeneric(25, c_ubyte)
    deepGreen = CBashGeneric(26, c_ubyte)
    deepBlue = CBashGeneric(27, c_ubyte)
    unused2 = CBashUINT8ARRAY(28, 1)
    reflRed = CBashGeneric(29, c_ubyte)
    reflGreen = CBashGeneric(30, c_ubyte)
    reflBlue = CBashGeneric(31, c_ubyte)
    unused3 = CBashUINT8ARRAY(32, 1)
    blend = CBashGeneric(33, c_ubyte)
    unused4 = CBashUINT8ARRAY(34, 3)
    rainForce = CBashFLOAT32(35)
    rainVelocity = CBashFLOAT32(36)
    rainFalloff = CBashFLOAT32(37)
    rainDampner = CBashFLOAT32(38)
    rainSize = CBashFLOAT32(39)
    dispForce = CBashFLOAT32(40)
    dispVelocity = CBashFLOAT32(41)
    dispFalloff = CBashFLOAT32(42)
    dispDampner = CBashFLOAT32(43)
    dispSize = CBashFLOAT32(44)
    damage = CBashGeneric(45, c_ushort)
    dayWater = CBashFORMID(46)
    nightWater = CBashFORMID(47)
    underWater = CBashFORMID(48)
    IsCausesDamage = CBashBasicFlag('flags', 0x00000001)
    IsCausesDmg = CBashAlias('IsCausesDamage')
    IsReflective = CBashBasicFlag('flags', 0x00000002)
    exportattrs = copyattrs = ObBaseRecord.baseattrs + ['texturePath', 'opacity', 'flags', 'materialPath',
                                        'sound', 'windVelocity', 'windDirection',
                                        'waveAmp', 'waveFreq', 'sunPower',
                                        'reflectAmt', 'fresnelAmt', 'xSpeed',
                                        'ySpeed', 'fogNear', 'fogFar',
                                        'shallowRed', 'shallowGreen', 'shallowBlue',
                                        'deepRed', 'deepGreen', 'deepBlue',
                                        'reflRed', 'reflGreen', 'reflBlue',
                                        'blend', 'rainForce', 'rainVelocity',
                                        'rainFalloff', 'rainDampner', 'rainSize',
                                        'dispForce', 'dispVelocity', 'dispFalloff',
                                        'dispDampner', 'dispSize', 'damage',
                                        'dayWater', 'nightWater', 'underWater']

class ObWEAPRecord(ObBaseRecord):
    _Type = 'WEAP'
    full = CBashSTRING(5)
    modPath = CBashISTRING(6)
    modb = CBashFLOAT32(7)
    modt_p = CBashUINT8ARRAY(8)
    iconPath = CBashISTRING(9)
    script = CBashFORMID(10)
    enchantment = CBashFORMID(11)
    enchantPoints = CBashGeneric(12, c_ushort)
    weaponType = CBashGeneric(13, c_ulong)
    speed = CBashFLOAT32(14)
    reach = CBashFLOAT32(15)
    flags = CBashGeneric(16, c_ulong)
    value = CBashGeneric(17, c_ulong)
    health = CBashGeneric(18, c_ulong)
    weight = CBashFLOAT32(19)
    damage = CBashGeneric(20, c_ushort)
    IsBlade1Hand = CBashBasicType('weaponType', 0, 'IsBlade2Hand')
    IsBlade2Hand = CBashBasicType('weaponType', 1, 'IsBlade1Hand')
    IsBlunt1Hand = CBashBasicType('weaponType', 2, 'IsBlade1Hand')
    IsBlunt2Hand = CBashBasicType('weaponType', 3, 'IsBlade1Hand')
    IsStaff = CBashBasicType('weaponType', 4, 'IsBlade1Hand')
    IsBow = CBashBasicType('weaponType', 5, 'IsBlade1Hand')
    IsNotNormalWeapon = CBashBasicFlag('flags', 0x00000001)
    IsNotNormal = CBashAlias('IsNotNormalWeapon')
    IsNormalWeapon = CBashInvertedFlag('IsNotNormalWeapon')
    IsNormal = CBashAlias('IsNormalWeapon')
    copyattrs = ObBaseRecord.baseattrs + ['full', 'modPath', 'modb', 'modt_p',
                                        'iconPath', 'script', 'enchantment',
                                        'enchantPoints', 'weaponType',
                                        'speed', 'reach', 'flags', 'value',
                                        'health', 'weight', 'damage']
    exportattrs = ObBaseRecord.baseattrs + ['full', 'modPath', 'modb',
                                        'iconPath', 'script', 'enchantment',
                                        'enchantPoints', 'weaponType',
                                        'speed', 'reach', 'flags', 'value',
                                        'health', 'weight', 'damage'] # 'modt_p',

class ObWRLDRecord(ObBaseRecord):
    _Type = 'WRLD'
    full = CBashSTRING(5)
    parent = CBashFORMID(6)
    climate = CBashFORMID(7)
    water = CBashFORMID(8)
    mapPath = CBashISTRING(9)
    dimX = CBashGeneric(10, c_long)
    dimY = CBashGeneric(11, c_long)
    NWCellX = CBashGeneric(12, c_short)
    NWCellY = CBashGeneric(13, c_short)
    SECellX = CBashGeneric(14, c_short)
    SECellY = CBashGeneric(15, c_short)
    flags = CBashGeneric(16, c_ubyte)
    xMinObjBounds = CBashFLOAT32(17)
    yMinObjBounds = CBashFLOAT32(18)
    xMaxObjBounds = CBashFLOAT32(19)
    yMaxObjBounds = CBashFLOAT32(20)
    musicType = CBashGeneric(21, c_ulong)
    ofst_p = CBashUINT8ARRAY(22)
    def create_ROAD(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("ROAD", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, self._RecordID, 0)
        if(RecordID): return ObROADRecord(self._CollectionID, self._ModID, RecordID, self._RecordID, 0)
        return None
    ROAD = CBashSUBRECORD(23, ObROADRecord, "ROAD", 0)

    def create_WorldCELL(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("CELL", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, self._RecordID, 2)
        if(RecordID): return ObCELLRecord(self._CollectionID, self._ModID, RecordID, self._RecordID, 2)
        return None
    WorldCELL = CBashSUBRECORD(24, ObCELLRecord, "CELL", 2)

    def create_CELLS(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("CELL", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, self._RecordID, 0)
        if(RecordID): return ObCELLRecord(self._CollectionID, self._ModID, RecordID, self._RecordID, 0)
        return None
    CELLS = CBashSUBRECORDARRAY(25, ObCELLRecord, "CELL", 0)

    IsSmallWorld = CBashBasicFlag('flags', 0x00000001)
    IsNoFastTravel = CBashBasicFlag('flags', 0x00000002)
    IsFastTravel = CBashInvertedFlag('IsNoFastTravel')
    IsOblivionWorldspace = CBashBasicFlag('flags', 0x00000004)
    IsNoLODWater = CBashBasicFlag('flags', 0x00000010)
    IsLODWater = CBashInvertedFlag('IsNoLODWater')
    IsDefault = CBashBasicType('musicType', 0, 'IsPublic')
    IsPublic = CBashBasicType('musicType', 1, 'IsDefault')
    IsDungeon = CBashBasicType('musicType', 2, 'IsDefault')
    exportattrs = copyattrs = ObBaseRecord.baseattrs + ['full', 'parent', 'climate', 'water', 'mapPath',
                                        'dimX', 'dimY', 'NWCellX', 'NWCellY', 'SECellX',
                                        'SECellY', 'flags', 'xMinObjBounds', 'yMinObjBounds',
                                        'xMaxObjBounds', 'yMaxObjBounds', 'musicType', 'ROAD', 'WorldCELL'] #'ofst_p',

class ObWTHRRecord(ObBaseRecord):
    _Type = 'WTHR'
    class WTHRColor(BaseComponent):
        riseRed = CBashGeneric_GROUP(0, c_ubyte)
        riseGreen = CBashGeneric_GROUP(1, c_ubyte)
        riseBlue = CBashGeneric_GROUP(2, c_ubyte)
        unused1 = CBashUINT8ARRAY_GROUP(3, 1)
        dayRed = CBashGeneric_GROUP(4, c_ubyte)
        dayGreen = CBashGeneric_GROUP(5, c_ubyte)
        dayBlue = CBashGeneric_GROUP(6, c_ubyte)
        unused2 = CBashUINT8ARRAY_GROUP(7, 1)
        setRed = CBashGeneric_GROUP(8, c_ubyte)
        setGreen = CBashGeneric_GROUP(9, c_ubyte)
        setBlue = CBashGeneric_GROUP(10, c_ubyte)
        unused3 = CBashUINT8ARRAY_GROUP(11, 1)
        nightRed = CBashGeneric_GROUP(12, c_ubyte)
        nightGreen = CBashGeneric_GROUP(13, c_ubyte)
        nightBlue = CBashGeneric_GROUP(14, c_ubyte)
        unused4 = CBashUINT8ARRAY_GROUP(15, 1)
        exportattrs = copyattrs = ['riseRed', 'riseGreen', 'riseBlue',
                     'dayRed', 'dayGreen', 'dayBlue',
                     'setRed', 'setGreen', 'setBlue',
                     'nightRed', 'nightGreen', 'nightBlue']

    class Sound(ListComponent):
        sound = CBashFORMID_LIST(1)
        type = CBashGeneric_LIST(2, c_ulong)
        IsDefault = CBashBasicType('type', 0, 'IsPrecip')
        IsPrecipitation = CBashBasicType('type', 1, 'IsDefault')
        IsPrecip = CBashAlias('IsPrecipitation')
        IsWind = CBashBasicType('type', 2, 'IsDefault')
        IsThunder = CBashBasicType('type', 3, 'IsDefault')
        exportattrs = copyattrs = ['sound', 'type']

    lowerLayerPath = CBashISTRING(5)
    upperLayerPath = CBashISTRING(6)
    modPath = CBashISTRING(7)
    modb = CBashFLOAT32(8)
    modt_p = CBashUINT8ARRAY(9)
    upperSky = CBashGrouped(10, WTHRColor)
    upperSky_list = CBashGrouped(10, WTHRColor, True)

    fog = CBashGrouped(26, WTHRColor)
    fog_list = CBashGrouped(26, WTHRColor, True)

    lowerClouds = CBashGrouped(42, WTHRColor)
    lowerClouds_list = CBashGrouped(42, WTHRColor, True)

    ambient = CBashGrouped(58, WTHRColor)
    ambient_list = CBashGrouped(58, WTHRColor, True)

    sunlight = CBashGrouped(74, WTHRColor)
    sunlight_list = CBashGrouped(74, WTHRColor, True)

    sun = CBashGrouped(90, WTHRColor)
    sun_list = CBashGrouped(90, WTHRColor, True)

    stars = CBashGrouped(106, WTHRColor)
    stars_list = CBashGrouped(106, WTHRColor, True)

    lowerSky = CBashGrouped(122, WTHRColor)
    lowerSky_list = CBashGrouped(122, WTHRColor, True)

    horizon = CBashGrouped(138, WTHRColor)
    horizon_list = CBashGrouped(138, WTHRColor, True)

    upperClouds = CBashGrouped(154, WTHRColor)
    upperClouds_list = CBashGrouped(154, WTHRColor, True)

    fogDayNear = CBashFLOAT32(170)
    fogDayFar = CBashFLOAT32(171)
    fogNightNear = CBashFLOAT32(172)
    fogNightFar = CBashFLOAT32(173)
    eyeAdaptSpeed = CBashFLOAT32(174)
    blurRadius = CBashFLOAT32(175)
    blurPasses = CBashFLOAT32(176)
    emissiveMult = CBashFLOAT32(177)
    targetLum = CBashFLOAT32(178)
    upperLumClamp = CBashFLOAT32(179)
    brightScale = CBashFLOAT32(180)
    brightClamp = CBashFLOAT32(181)
    lumRampNoTex = CBashFLOAT32(182)
    lumRampMin = CBashFLOAT32(183)
    lumRampMax = CBashFLOAT32(184)
    sunlightDimmer = CBashFLOAT32(185)
    grassDimmer = CBashFLOAT32(186)
    treeDimmer = CBashFLOAT32(187)
    windSpeed = CBashGeneric(188, c_ubyte)
    lowerCloudSpeed = CBashGeneric(189, c_ubyte)
    upperCloudSpeed = CBashGeneric(190, c_ubyte)
    transDelta = CBashGeneric(191, c_ubyte)
    sunGlare = CBashGeneric(192, c_ubyte)
    sunDamage = CBashGeneric(193, c_ubyte)
    rainFadeIn = CBashGeneric(194, c_ubyte)
    rainFadeOut = CBashGeneric(195, c_ubyte)
    boltFadeIn = CBashGeneric(196, c_ubyte)
    boltFadeOut = CBashGeneric(197, c_ubyte)
    boltFrequency = CBashGeneric(198, c_ubyte)
    weatherType = CBashGeneric(199, c_ubyte)
    boltRed = CBashGeneric(200, c_ubyte)
    boltGreen = CBashGeneric(201, c_ubyte)
    boltBlue = CBashGeneric(202, c_ubyte)

    def create_sound(self):
        length = CBash.GetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 203, 0, 0, 0, 0, 0, 0, 1)
        CBash.SetField(self._CollectionID, self._ModID, self._RecordID, 203, 0, 0, 0, 0, 0, 0, 0, c_ulong(length + 1))
        return self.Sound(self._CollectionID, self._ModID, self._RecordID, 203, length)
    sounds = CBashLIST(203, Sound)
    sounds_list = CBashLIST(203, Sound, True)

    ##actually flags, but all are exclusive(except unknowns)...so like a Type
    ##Manual hackery will make the CS think it is multiple types. It isn't known how the game would react.
    IsNone = CBashMaskedType('weatherType', 0x0F, 0x00, 'IsPleasant')
    IsPleasant = CBashMaskedType('weatherType', 0x0F, 0x01, 'IsNone')
    IsCloudy = CBashMaskedType('weatherType', 0x0F, 0x02, 'IsNone')
    IsRainy = CBashMaskedType('weatherType', 0x0F, 0x04, 'IsNone')
    IsSnow = CBashMaskedType('weatherType', 0x0F, 0x08, 'IsNone')
    IsUnk1 = CBashBasicFlag('weatherType', 0x40)
    IsUnk2 = CBashBasicFlag('weatherType', 0x80)
    copyattrs = ObBaseRecord.baseattrs + ['lowerLayerPath', 'upperLayerPath', 'modPath',
                                        'modb', 'modt_p', 'upperSky_list', 'fog_list',
                                        'lowerClouds_list', 'ambient_list', 'sunlight_list',
                                        'sun_list', 'stars_list', 'lowerSky_list', 'horizon_list',
                                        'upperClouds_list', 'fogDayNear', 'fogDayFar',
                                        'fogNightNear', 'fogNightFar', 'eyeAdaptSpeed',
                                        'blurRadius', 'blurPasses', 'emissiveMult',
                                        'targetLum', 'upperLumClamp', 'brightScale',
                                        'brightClamp', 'lumRampNoTex', 'lumRampMin',
                                        'lumRampMax', 'sunlightDimmer', 'grassDimmer',
                                        'treeDimmer', 'windSpeed', 'lowerCloudSpeed',
                                        'upperCloudSpeed', 'transDelta', 'sunGlare',
                                        'sunDamage', 'rainFadeIn', 'rainFadeOut',
                                        'boltFadeIn', 'boltFadeOut', 'boltFrequency',
                                        'weatherType', 'boltRed', 'boltGreen', 'boltBlue', 'sounds_list']
    exportattrs = ObBaseRecord.baseattrs + ['lowerLayerPath', 'upperLayerPath', 'modPath',
                                        'modb', 'upperSky_list', 'fog_list',
                                        'lowerClouds_list', 'ambient_list', 'sunlight_list',
                                        'sun_list', 'stars_list', 'lowerSky_list', 'horizon_list',
                                        'upperClouds_list', 'fogDayNear', 'fogDayFar',
                                        'fogNightNear', 'fogNightFar', 'eyeAdaptSpeed',
                                        'blurRadius', 'blurPasses', 'emissiveMult',
                                        'targetLum', 'upperLumClamp', 'brightScale',
                                        'brightClamp', 'lumRampNoTex', 'lumRampMin',
                                        'lumRampMax', 'sunlightDimmer', 'grassDimmer',
                                        'treeDimmer', 'windSpeed', 'lowerCloudSpeed',
                                        'upperCloudSpeed', 'transDelta', 'sunGlare',
                                        'sunDamage', 'rainFadeIn', 'rainFadeOut',
                                        'boltFadeIn', 'boltFadeOut', 'boltFrequency',
                                        'weatherType', 'boltRed', 'boltGreen', 'boltBlue', 'sounds_list'] #'modt_p',

#Helper functions
validTypes = set(['GMST','GLOB','CLAS','FACT','HAIR','EYES','RACE',
                  'SOUN','SKIL','MGEF','SCPT','LTEX','ENCH','SPEL',
                  'BSGN','ACTI','APPA','ARMO','BOOK','CLOT','CONT',
                  'DOOR','INGR','LIGH','MISC','STAT','GRAS','TREE',
                  'FLOR','FURN','WEAP','AMMO','NPC_','CREA','LVLC',
                  'SLGM','KEYM','ALCH','SBSP','SGST','LVLI','WTHR',
                  'CLMT','REGN','WRLD','CELL','ACHR','ACRE','REFR',
                  'PGRD','LAND','ROAD','DIAL','INFO','QUST','IDLE',
                  'PACK','CSTY','LSCR','LVSP','ANIO','WATR','EFSH'])

aggregateTypes = set(['GMST','GLOB','CLAS','FACT','HAIR','EYES','RACE',
                  'SOUN','SKIL','MGEF','SCPT','LTEX','ENCH','SPEL',
                  'BSGN','ACTI','APPA','ARMO','BOOK','CLOT','CONT',
                  'DOOR','INGR','LIGH','MISC','STAT','GRAS','TREE',
                  'FLOR','FURN','WEAP','AMMO','NPC_','CREA','LVLC',
                  'SLGM','KEYM','ALCH','SBSP','SGST','LVLI','WTHR',
                  'CLMT','REGN','WRLD','CELLS','ACHRS','ACRES','REFRS',
                  'PGRDS','LANDS','ROADS','DIAL','INFOS','QUST','IDLE',
                  'PACK','CSTY','LSCR','LVSP','ANIO','WATR','EFSH'])

pickupables = set(['APPA','ARMO','BOOK','CLOT','INGR','LIGH','MISC',
                   'WEAP','AMMO','SLGM','KEYM','ALCH','SGST'])

type_record = dict([('BASE',ObBaseRecord),(None,None),('',None),
                    ('GMST',ObGMSTRecord),('GLOB',ObGLOBRecord),('CLAS',ObCLASRecord),
                    ('FACT',ObFACTRecord),('HAIR',ObHAIRRecord),('EYES',ObEYESRecord),
                    ('RACE',ObRACERecord),('SOUN',ObSOUNRecord),('SKIL',ObSKILRecord),
                    ('MGEF',ObMGEFRecord),('SCPT',ObSCPTRecord),('LTEX',ObLTEXRecord),
                    ('ENCH',ObENCHRecord),('SPEL',ObSPELRecord),('BSGN',ObBSGNRecord),
                    ('ACTI',ObACTIRecord),('APPA',ObAPPARecord),('ARMO',ObARMORecord),
                    ('BOOK',ObBOOKRecord),('CLOT',ObCLOTRecord),('CONT',ObCONTRecord),
                    ('DOOR',ObDOORRecord),('INGR',ObINGRRecord),('LIGH',ObLIGHRecord),
                    ('MISC',ObMISCRecord),('STAT',ObSTATRecord),('GRAS',ObGRASRecord),
                    ('TREE',ObTREERecord),('FLOR',ObFLORRecord),('FURN',ObFURNRecord),
                    ('WEAP',ObWEAPRecord),('AMMO',ObAMMORecord),('NPC_',ObNPC_Record),
                    ('CREA',ObCREARecord),('LVLC',ObLVLCRecord),('SLGM',ObSLGMRecord),
                    ('KEYM',ObKEYMRecord),('ALCH',ObALCHRecord),('SBSP',ObSBSPRecord),
                    ('SGST',ObSGSTRecord),('LVLI',ObLVLIRecord),('WTHR',ObWTHRRecord),
                    ('CLMT',ObCLMTRecord),('REGN',ObREGNRecord),('WRLD',ObWRLDRecord),
                    ('CELL',ObCELLRecord),('ACHR',ObACHRRecord),('ACRE',ObACRERecord),
                    ('REFR',ObREFRRecord),('PGRD',ObPGRDRecord),('LAND',ObLANDRecord),
                    ('ROAD',ObROADRecord),('DIAL',ObDIALRecord),('INFO',ObINFORecord),
                    ('QUST',ObQUSTRecord),('IDLE',ObIDLERecord),('PACK',ObPACKRecord),
                    ('CSTY',ObCSTYRecord),('LSCR',ObLSCRRecord),('LVSP',ObLVSPRecord),
                    ('ANIO',ObANIORecord),('WATR',ObWATRRecord),('EFSH',ObEFSHRecord)])
fnv_type_record = dict([('BASE',FnvBaseRecord),(None,None),('',None),
                        ('GMST',FnvGMSTRecord),('TXST',FnvTXSTRecord),('MICN',FnvMICNRecord),
                        ('GLOB',FnvGLOBRecord),('CLAS',FnvCLASRecord),('FACT',FnvFACTRecord),
                        ('HDPT',FnvHDPTRecord),('HAIR',FnvHAIRRecord),('EYES',FnvEYESRecord),
                        ('RACE',FnvRACERecord),('SOUN',FnvSOUNRecord),('ASPC',FnvASPCRecord),
                        ('MGEF',FnvMGEFRecord),('SCPT',FnvSCPTRecord),('LTEX',FnvLTEXRecord),
                        ('ENCH',FnvENCHRecord),('SPEL',FnvSPELRecord),('ACTI',FnvACTIRecord),
                        ('TACT',FnvTACTRecord),('TERM',FnvTERMRecord),('ARMO',FnvARMORecord),
                        ('BOOK',FnvBOOKRecord),('CONT',FnvCONTRecord),('DOOR',FnvDOORRecord),
                        ('INGR',FnvINGRRecord),('LIGH',FnvLIGHRecord),('MISC',FnvMISCRecord),
                        ('STAT',FnvSTATRecord),('SCOL',FnvSCOLRecord),('MSTT',FnvMSTTRecord),
                        ('PWAT',FnvPWATRecord),('GRAS',FnvGRASRecord),('TREE',FnvTREERecord),
                        ('FURN',FnvFURNRecord),('WEAP',FnvWEAPRecord),('AMMO',FnvAMMORecord),
                        ('NPC_',FnvNPC_Record),('CREA',FnvCREARecord),('LVLC',FnvLVLCRecord),
                        ('LVLN',FnvLVLNRecord),('KEYM',FnvKEYMRecord),('ALCH',FnvALCHRecord),
                        ('IDLM',FnvIDLMRecord),('NOTE',FnvNOTERecord),('COBJ',FnvCOBJRecord),
                        ('PROJ',FnvPROJRecord),('LVLI',FnvLVLIRecord),('WTHR',FnvWTHRRecord),
                        ('CLMT',FnvCLMTRecord),('REGN',FnvREGNRecord),('NAVI',FnvNAVIRecord),
                        ('CELL',FnvCELLRecord),('WRLD',FnvWRLDRecord),('DIAL',FnvDIALRecord),
                        ('QUST',FnvQUSTRecord),('IDLE',FnvIDLERecord),('PACK',FnvPACKRecord),
                        ('CSTY',FnvCSTYRecord),('LSCR',FnvLSCRRecord),('ANIO',FnvANIORecord),
                        ('WATR',FnvWATRRecord),('EFSH',FnvEFSHRecord),('EXPL',FnvEXPLRecord),
                        ('DEBR',FnvDEBRRecord),('IMGS',FnvIMGSRecord),('IMAD',FnvIMADRecord),
                        ('FLST',FnvFLSTRecord),('PERK',FnvPERKRecord),('BPTD',FnvBPTDRecord),
                        ('ADDN',FnvADDNRecord),('AVIF',FnvAVIFRecord),('RADS',FnvRADSRecord),
                        ('CAMS',FnvCAMSRecord),('CPTH',FnvCPTHRecord),('VTYP',FnvVTYPRecord),
                        ('IPCT',FnvIPCTRecord),('IPDS',FnvIPDSRecord),('ARMA',FnvARMARecord),
                        ('ECZN',FnvECZNRecord),('MESG',FnvMESGRecord),('RGDL',FnvRGDLRecord),
                        ('DOBJ',FnvDOBJRecord),('LGTM',FnvLGTMRecord),('MUSC',FnvMUSCRecord),
                        ('IMOD',FnvIMODRecord),('REPU',FnvREPURecord),('RCPE',FnvRCPERecord),
                        ('RCCT',FnvRCCTRecord),('CHIP',FnvCHIPRecord),('CSNO',FnvCSNORecord),
                        ('LSCT',FnvLSCTRecord),('MSET',FnvMSETRecord),('ALOC',FnvALOCRecord),
                        ('CHAL',FnvCHALRecord),('AMEF',FnvAMEFRecord),('CCRD',FnvCCRDRecord),
                        ('CMNY',FnvCMNYRecord),('CDCK',FnvCDCKRecord),('DEHY',FnvDEHYRecord),
                        ('HUNG',FnvHUNGRecord),('SLPD',FnvSLPDRecord),])

class ObModFile(object):
    def __init__(self, CollectionIndex, ModID):
        self._CollectionID = CollectionIndex
        self._ModID = ModID

    def __eq__(self, other):
        if type(other) is type(self):
            return self._CollectionID == other._CollectionID and self._ModID == other._ModID
        return False

    def __ne__(self, other):
        return not self.__eq__(other)

    @property
    def FileName(self):
        return _CGetFileNameByID(self._CollectionID, self._ModID) or 'Missing'

    @property
    def ModName(self):
        return _CGetModNameByID(self._CollectionID, self._ModID) or 'Missing'

    @property
    def GName(self):
        return GPath(self.ModName)

    def HasRecord(self, RecordIdentifier):
        return self.LookupRecord(RecordIdentifier) is not None

    def LookupRecord(self, RecordIdentifier):
        if not RecordIdentifier: return None
        if isinstance(RecordIdentifier, basestring):
            _FormID = 0
            _EditorID = RecordIdentifier
        else:
            _FormID = MakeShortFid(self._CollectionID, RecordIdentifier)
            _EditorID = 0
        if not (_EditorID or _FormID): return None
        RecordID = _CGetRecordID(self._CollectionID, self._ModID, _FormID, _EditorID)
        if RecordID:
            testRecord = ObBaseRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
            RecordType = type_record[testRecord.recType]
            if RecordType:
                return RecordType(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None

    def IsEmpty(self):
        return _CIsModEmpty(self._CollectionID, self._ModID)

    def GetNewRecordTypes(self):
        numRecords = _CGetModNumTypes(self._CollectionID, self._ModID)
        if(numRecords > 0):
            cRecords = ((c_char * 4) * numRecords)()
            _CGetModTypes(self._CollectionID, self._ModID, byref(cRecords))
            return [cRecord.value for cRecord in cRecords if cRecord]
        return []

    def UpdateReferences(self, FormIDToReplace, ReplacementFormID):
        FormIDToReplace = MakeShortFid(self._CollectionID, FormIDToReplace)
        ReplacementFormID = MakeShortFid(self._CollectionID, ReplacementFormID)
        if not (FormIDToReplace or ReplacementFormID): return 0
        return _CUpdateReferences(self._CollectionID, self._ModID, 0, FormIDToReplace, ReplacementFormID)

    def CleanMasters(self):
        return _CCleanModMasters(self._CollectionID, self._ModID)

    def Unload(self):
        _CUnloadMod(self._CollectionID, self._ModID)

    def save(self, CloseCollection=True):
        return _CSaveMod(self._CollectionID, self._ModID, c_ulong(CloseCollection))

    @property
    def TES4(self):
        RecordID = _CGetRecordID(self._CollectionID, self._ModID, 0, 0)
        return ObTES4Record(self._CollectionID, self._ModID, RecordID, 0, 0)

    def create_GMST(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("GMST", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return ObGMSTRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    GMST = CBashRECORDARRAY(ObGMSTRecord, 'GMST', 0)

    def create_GLOB(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("GLOB", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return ObGLOBRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    GLOB = CBashRECORDARRAY(ObGLOBRecord, 'GLOB', 0)

    def create_CLAS(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("CLAS", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return ObCLASRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    CLAS = CBashRECORDARRAY(ObCLASRecord, 'CLAS', 0)

    def create_FACT(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("FACT", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return ObFACTRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    FACT = CBashRECORDARRAY(ObFACTRecord, 'FACT', 0)

    def create_HAIR(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("HAIR", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return ObHAIRRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    HAIR = CBashRECORDARRAY(ObHAIRRecord, 'HAIR', 0)

    def create_EYES(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("EYES", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return ObEYESRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    EYES = CBashRECORDARRAY(ObEYESRecord, 'EYES', 0)

    def create_RACE(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("RACE", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return ObRACERecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    RACE = CBashRECORDARRAY(ObRACERecord, 'RACE', 0)

    def create_SOUN(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("SOUN", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return ObSOUNRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    SOUN = CBashRECORDARRAY(ObSOUNRecord, 'SOUN', 0)

    def create_SKIL(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("SKIL", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return ObSKILRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    SKIL = CBashRECORDARRAY(ObSKILRecord, 'SKIL', 0)

    def create_MGEF(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("MGEF", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return ObMGEFRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    MGEF = CBashRECORDARRAY(ObMGEFRecord, 'MGEF', 0)

    def create_SCPT(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("SCPT", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return ObSCPTRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    SCPT = CBashRECORDARRAY(ObSCPTRecord, 'SCPT', 0)

    def create_LTEX(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("LTEX", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return ObLTEXRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    LTEX = CBashRECORDARRAY(ObLTEXRecord, 'LTEX', 0)

    def create_ENCH(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("ENCH", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return ObENCHRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    ENCH = CBashRECORDARRAY(ObENCHRecord, 'ENCH', 0)

    def create_SPEL(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("SPEL", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return ObSPELRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    SPEL = CBashRECORDARRAY(ObSPELRecord, 'SPEL', 0)

    def create_BSGN(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("BSGN", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return ObBSGNRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    BSGN = CBashRECORDARRAY(ObBSGNRecord, 'BSGN', 0)

    def create_ACTI(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("ACTI", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return ObACTIRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    ACTI = CBashRECORDARRAY(ObACTIRecord, 'ACTI', 0)

    def create_APPA(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("APPA", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return ObAPPARecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    APPA = CBashRECORDARRAY(ObAPPARecord, 'APPA', 0)

    def create_ARMO(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("ARMO", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return ObARMORecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    ARMO = CBashRECORDARRAY(ObARMORecord, 'ARMO', 0)

    def create_BOOK(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("BOOK", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return ObBOOKRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    BOOK = CBashRECORDARRAY(ObBOOKRecord, 'BOOK', 0)

    def create_CLOT(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("CLOT", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return ObCLOTRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    CLOT = CBashRECORDARRAY(ObCLOTRecord, 'CLOT', 0)

    def create_CONT(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("CONT", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return ObCONTRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    CONT = CBashRECORDARRAY(ObCONTRecord, 'CONT', 0)

    def create_DOOR(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("DOOR", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return ObDOORRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    DOOR = CBashRECORDARRAY(ObDOORRecord, 'DOOR', 0)

    def create_INGR(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("INGR", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return ObINGRRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    INGR = CBashRECORDARRAY(ObINGRRecord, 'INGR', 0)

    def create_LIGH(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("LIGH", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return ObLIGHRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    LIGH = CBashRECORDARRAY(ObLIGHRecord, 'LIGH', 0)

    def create_MISC(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("MISC", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return ObMISCRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    MISC = CBashRECORDARRAY(ObMISCRecord, 'MISC', 0)

    def create_STAT(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("STAT", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return ObSTATRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    STAT = CBashRECORDARRAY(ObSTATRecord, 'STAT', 0)

    def create_GRAS(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("GRAS", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return ObGRASRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    GRAS = CBashRECORDARRAY(ObGRASRecord, 'GRAS', 0)

    def create_TREE(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("TREE", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return ObTREERecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    TREE = CBashRECORDARRAY(ObTREERecord, 'TREE', 0)

    def create_FLOR(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("FLOR", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return ObFLORRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    FLOR = CBashRECORDARRAY(ObFLORRecord, 'FLOR', 0)

    def create_FURN(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("FURN", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return ObFURNRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    FURN = CBashRECORDARRAY(ObFURNRecord, 'FURN', 0)

    def create_WEAP(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("WEAP", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return ObWEAPRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    WEAP = CBashRECORDARRAY(ObWEAPRecord, 'WEAP', 0)

    def create_AMMO(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("AMMO", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return ObAMMORecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    AMMO = CBashRECORDARRAY(ObAMMORecord, 'AMMO', 0)

    def create_NPC_(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("NPC_", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return ObNPC_Record(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    NPC_ = CBashRECORDARRAY(ObNPC_Record, 'NPC_', 0)

    def create_CREA(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("CREA", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return ObCREARecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    CREA = CBashRECORDARRAY(ObCREARecord, 'CREA', 0)

    def create_LVLC(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("LVLC", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return ObLVLCRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    LVLC = CBashRECORDARRAY(ObLVLCRecord, 'LVLC', 0)

    def create_SLGM(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("SLGM", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return ObSLGMRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    SLGM = CBashRECORDARRAY(ObSLGMRecord, 'SLGM', 0)

    def create_KEYM(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("KEYM", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return ObKEYMRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    KEYM = CBashRECORDARRAY(ObKEYMRecord, 'KEYM', 0)

    def create_ALCH(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("ALCH", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return ObALCHRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    ALCH = CBashRECORDARRAY(ObALCHRecord, 'ALCH', 0)

    def create_SBSP(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("SBSP", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return ObSBSPRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    SBSP = CBashRECORDARRAY(ObSBSPRecord, 'SBSP', 0)

    def create_SGST(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("SGST", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return ObSGSTRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    SGST = CBashRECORDARRAY(ObSGSTRecord, 'SGST', 0)

    def create_LVLI(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("LVLI", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return ObLVLIRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    LVLI = CBashRECORDARRAY(ObLVLIRecord, 'LVLI', 0)

    def create_WTHR(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("WTHR", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return ObWTHRRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    WTHR = CBashRECORDARRAY(ObWTHRRecord, 'WTHR', 0)

    def create_CLMT(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("CLMT", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return ObCLMTRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    CLMT = CBashRECORDARRAY(ObCLMTRecord, 'CLMT', 0)

    def create_REGN(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("REGN", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return ObREGNRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    REGN = CBashRECORDARRAY(ObREGNRecord, 'REGN', 0)

    def create_WRLD(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("WRLD", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return ObWRLDRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    WRLD = CBashRECORDARRAY(ObWRLDRecord, 'WRLD', 0)

    def create_CELL(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("CELL", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return ObCELLRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    CELL = CBashRECORDARRAY(ObCELLRecord, 'CELL', 0)

    def create_DIAL(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("DIAL", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return ObDIALRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    DIAL = CBashRECORDARRAY(ObDIALRecord, 'DIAL', 0)

    def create_QUST(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("QUST", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return ObQUSTRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    QUST = CBashRECORDARRAY(ObQUSTRecord, 'QUST', 0)

    def create_IDLE(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("IDLE", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return ObIDLERecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    IDLE = CBashRECORDARRAY(ObIDLERecord, 'IDLE', 0)

    def create_PACK(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("PACK", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return ObPACKRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    PACK = CBashRECORDARRAY(ObPACKRecord, 'PACK', 0)

    def create_CSTY(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("CSTY", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return ObCSTYRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    CSTY = CBashRECORDARRAY(ObCSTYRecord, 'CSTY', 0)

    def create_LSCR(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("LSCR", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return ObLSCRRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    LSCR = CBashRECORDARRAY(ObLSCRRecord, 'LSCR', 0)

    def create_LVSP(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("LVSP", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return ObLVSPRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    LVSP = CBashRECORDARRAY(ObLVSPRecord, 'LVSP', 0)

    def create_ANIO(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("ANIO", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return ObANIORecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    ANIO = CBashRECORDARRAY(ObANIORecord, 'ANIO', 0)

    def create_WATR(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("WATR", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return ObWATRRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    WATR = CBashRECORDARRAY(ObWATRRecord, 'WATR', 0)

    def create_EFSH(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("EFSH", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return ObEFSHRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    EFSH = CBashRECORDARRAY(ObEFSHRecord, 'EFSH', 0)


    ##Aggregate properties. Useful for iterating through all records without going through the parent records.
    @property
    def CELLS(self):
        cells = self.CELL
        for world in self.WRLD:
            cell = world.WorldCELL
            if(cell): cells += [cell]
            cells += world.CELLS
        return cells

    @property
    def INFOS(self):
        infos = []
        for dial in self.DIAL:
            infos += dial.INFO
        return infos

    @property
    def ACHRS(self):
        achrs = []
        for cell in self.CELL:
            achrs += cell.ACHR
        for world in self.WRLD:
            cell = world.WorldCELL
            if(cell): achrs += cell.ACHR
            for cell in world.CELLS:
                achrs += cell.ACHR
        return achrs

    @property
    def ACRES(self):
        acres = []
        for cell in self.CELL:
            acres += cell.ACRE
        for world in self.WRLD:
            cell = world.WorldCELL
            if(cell): acres += cell.ACRE
            for cell in world.CELLS:
                acres += cell.ACRE
        return acres

    @property
    def REFRS(self):
        refrs = []
        for cell in self.CELL:
            refrs += cell.REFR
        for world in self.WRLD:
            cell = world.WorldCELL
            if(cell): refrs += cell.REFR
            for cell in world.CELLS:
                refrs += cell.REFR
        return refrs

    @property
    def PGRDS(self):
        pgrds = []
        for cell in self.CELL:
            pgrd = cell.PGRD
            if(pgrd): pgrds += [pgrd]
        for world in self.WRLD:
            cell = world.WorldCELL
            if(cell):
                pgrd = cell.PGRD
                if(pgrd): pgrds += [pgrd]
            for cell in world.CELLS:
                pgrd = cell.PGRD
                if(pgrd): pgrds += [pgrd]
        return pgrds

    @property
    def LANDS(self):
        lands = []
        for cell in self.CELL:
            land = cell.LAND
            if(land): lands += [land]
        for world in self.WRLD:
            cell = world.WorldCELL
            if(cell):
                land = cell.LAND
                if(land): lands += [land]
            for cell in world.CELLS:
                land = cell.LAND
                if(land): lands += [land]
        return lands

    @property
    def ROADS(self):
        roads = []
        for world in self.WRLD:
            road = world.ROAD
            if(road): roads.append(road)
        return roads

    @property
    def tops(self):
        return dict((("GMST", self.GMST),("GLOB", self.GLOB),("CLAS", self.CLAS),("FACT", self.FACT),
                     ("HAIR", self.HAIR),("EYES", self.EYES),("RACE", self.RACE),("SOUN", self.SOUN),
                     ("SKIL", self.SKIL),("MGEF", self.MGEF),("SCPT", self.SCPT),("LTEX", self.LTEX),
                     ("ENCH", self.ENCH),("SPEL", self.SPEL),("BSGN", self.BSGN),("ACTI", self.ACTI),
                     ("APPA", self.APPA),("ARMO", self.ARMO),("BOOK", self.BOOK),("CLOT", self.CLOT),
                     ("CONT", self.CONT),("DOOR", self.DOOR),("INGR", self.INGR),("LIGH", self.LIGH),
                     ("MISC", self.MISC),("STAT", self.STAT),("GRAS", self.GRAS),("TREE", self.TREE),
                     ("FLOR", self.FLOR),("FURN", self.FURN),("WEAP", self.WEAP),("AMMO", self.AMMO),
                     ("NPC_", self.NPC_),("CREA", self.CREA),("LVLC", self.LVLC),("SLGM", self.SLGM),
                     ("KEYM", self.KEYM),("ALCH", self.ALCH),("SBSP", self.SBSP),("SGST", self.SGST),
                     ("LVLI", self.LVLI),("WTHR", self.WTHR),("CLMT", self.CLMT),("REGN", self.REGN),
                     ("CELL", self.CELL),("WRLD", self.WRLD),("DIAL", self.DIAL),("QUST", self.QUST),
                     ("IDLE", self.IDLE),("PACK", self.PACK),("CSTY", self.CSTY),("LSCR", self.LSCR),
                     ("LVSP", self.LVSP),("ANIO", self.ANIO),("WATR", self.WATR),("EFSH", self.EFSH)))

    @property
    def aggregates(self):
        return dict((("GMST", self.GMST),("GLOB", self.GLOB),("CLAS", self.CLAS),("FACT", self.FACT),
                     ("HAIR", self.HAIR),("EYES", self.EYES),("RACE", self.RACE),("SOUN", self.SOUN),
                     ("SKIL", self.SKIL),("MGEF", self.MGEF),("SCPT", self.SCPT),("LTEX", self.LTEX),
                     ("ENCH", self.ENCH),("SPEL", self.SPEL),("BSGN", self.BSGN),("ACTI", self.ACTI),
                     ("APPA", self.APPA),("ARMO", self.ARMO),("BOOK", self.BOOK),("CLOT", self.CLOT),
                     ("CONT", self.CONT),("DOOR", self.DOOR),("INGR", self.INGR),("LIGH", self.LIGH),
                     ("MISC", self.MISC),("STAT", self.STAT),("GRAS", self.GRAS),("TREE", self.TREE),
                     ("FLOR", self.FLOR),("FURN", self.FURN),("WEAP", self.WEAP),("AMMO", self.AMMO),
                     ("NPC_", self.NPC_),("CREA", self.CREA),("LVLC", self.LVLC),("SLGM", self.SLGM),
                     ("KEYM", self.KEYM),("ALCH", self.ALCH),("SBSP", self.SBSP),("SGST", self.SGST),
                     ("LVLI", self.LVLI),("WTHR", self.WTHR),("CLMT", self.CLMT),("REGN", self.REGN),
                     ("WRLD", self.WRLD),("CELL", self.CELLS),("ACHR", self.ACHRS),("ACRE", self.ACRES),
                     ("REFR", self.REFRS),("PGRD", self.PGRDS),("LAND", self.LANDS),("ROAD", self.ROADS),
                     ("DIAL", self.DIAL),("INFO", self.INFOS),("QUST", self.QUST),("IDLE", self.IDLE),
                     ("PACK", self.PACK),("CSTY", self.CSTY),("LSCR", self.LSCR),("LVSP", self.LVSP),
                     ("ANIO", self.ANIO),("WATR", self.WATR),("EFSH", self.EFSH)))

class FnvModFile(object):
    def __init__(self, CollectionIndex, ModID):
        self._CollectionID = CollectionIndex
        self._ModID = ModID

    def __eq__(self, other):
        if type(other) is type(self):
            return self._CollectionID == other._CollectionID and self._ModID == other._ModID
        return False

    def __ne__(self, other):
        return not self.__eq__(other)

    @property
    def FileName(self):
        return _CGetFileNameByID(self._CollectionID, self._ModID) or 'Missing'

    @property
    def ModName(self):
        return _CGetModNameByID(self._CollectionID, self._ModID) or 'Missing'

    @property
    def GName(self):
        return GPath(self.ModName)

    def HasRecord(self, RecordIdentifier):
        return self.LookupRecord(RecordIdentifier) is not None

    def LookupRecord(self, RecordIdentifier):
        if not RecordIdentifier: return None
        if isinstance(RecordIdentifier, basestring):
            _FormID = 0
            _EditorID = RecordIdentifier
        else:
            _FormID = MakeShortFid(self._CollectionID, RecordIdentifier)
            _EditorID = 0
        if not (_EditorID or _FormID): return None
        RecordID = _CGetRecordID(self._CollectionID, self._ModID, _FormID, _EditorID)
        if RecordID:
            testRecord = FnvBaseRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
            RecordType = fnv_type_record[testRecord.recType]
            if RecordType:
                return RecordType(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None

    def IsEmpty(self):
        return _CIsModEmpty(self._CollectionID, self._ModID)

    def GetNewRecordTypes(self):
        numRecords = _CGetModNumTypes(self._CollectionID, self._ModID)
        if(numRecords > 0):
            cRecords = ((c_char * 4) * numRecords)()
            _CGetModTypes(self._CollectionID, self._ModID, byref(cRecords))
            return [cRecord.value for cRecord in cRecords if cRecord]
        return []

    def UpdateReferences(self, FormIDToReplace, ReplacementFormID):
        FormIDToReplace = MakeShortFid(self._CollectionID, FormIDToReplace)
        ReplacementFormID = MakeShortFid(self._CollectionID, ReplacementFormID)
        if not (FormIDToReplace or ReplacementFormID): return 0
        return _CUpdateReferences(self._CollectionID, self._ModID, 0, FormIDToReplace, ReplacementFormID)

    def CleanMasters(self):
        return _CCleanModMasters(self._CollectionID, self._ModID)

    def Unload(self):
        _CUnloadMod(self._CollectionID, self._ModID)

    def save(self, CloseCollection=True):
        return _CSaveMod(self._CollectionID, self._ModID, c_ulong(CloseCollection))

    @property
    def TES4(self):
        RecordID = _CGetRecordID(self._CollectionID, self._ModID, 0, 0)
        return FnvTES4Record(self._CollectionID, self._ModID, RecordID, 0, 0)

    def create_GMST(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("GMST", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvGMSTRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    GMST = CBashRECORDARRAY(FnvGMSTRecord, 'GMST', 0)

    def create_TXST(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("TXST", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvTXSTRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    TXST = CBashRECORDARRAY(FnvTXSTRecord, 'TXST', 0)

    def create_MICN(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("MICN", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvMICNRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    MICN = CBashRECORDARRAY(FnvMICNRecord, 'MICN', 0)

    def create_GLOB(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("GLOB", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvGLOBRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    GLOB = CBashRECORDARRAY(FnvGLOBRecord, 'GLOB', 0)

    def create_CLAS(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("CLAS", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvCLASRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    CLAS = CBashRECORDARRAY(FnvCLASRecord, 'CLAS', 0)

    def create_FACT(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("FACT", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvFACTRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    FACT = CBashRECORDARRAY(FnvFACTRecord, 'FACT', 0)

    def create_HDPT(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("HDPT", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvHDPTRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    HDPT = CBashRECORDARRAY(FnvHDPTRecord, 'HDPT', 0)

    def create_HAIR(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("HAIR", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvHAIRRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    HAIR = CBashRECORDARRAY(FnvHAIRRecord, 'HAIR', 0)

    def create_EYES(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("EYES", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvEYESRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    EYES = CBashRECORDARRAY(FnvEYESRecord, 'EYES', 0)

    def create_RACE(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("RACE", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvRACERecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    RACE = CBashRECORDARRAY(FnvRACERecord, 'RACE', 0)

    def create_SOUN(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("SOUN", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvSOUNRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    SOUN = CBashRECORDARRAY(FnvSOUNRecord, 'SOUN', 0)

    def create_ASPC(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("ASPC", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvASPCRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    ASPC = CBashRECORDARRAY(FnvASPCRecord, 'ASPC', 0)

    def create_MGEF(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("MGEF", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvMGEFRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    MGEF = CBashRECORDARRAY(FnvMGEFRecord, 'MGEF', 0)

    def create_SCPT(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("SCPT", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvSCPTRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    SCPT = CBashRECORDARRAY(FnvSCPTRecord, 'SCPT', 0)

    def create_LTEX(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("LTEX", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvLTEXRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    LTEX = CBashRECORDARRAY(FnvLTEXRecord, 'LTEX', 0)

    def create_ENCH(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("ENCH", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvENCHRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    ENCH = CBashRECORDARRAY(FnvENCHRecord, 'ENCH', 0)

    def create_SPEL(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("SPEL", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvSPELRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    SPEL = CBashRECORDARRAY(FnvSPELRecord, 'SPEL', 0)

    def create_ACTI(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("ACTI", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvACTIRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    ACTI = CBashRECORDARRAY(FnvACTIRecord, 'ACTI', 0)

    def create_TACT(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("TACT", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvTACTRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    TACT = CBashRECORDARRAY(FnvTACTRecord, 'TACT', 0)

    def create_TERM(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("TERM", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvTERMRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    TERM = CBashRECORDARRAY(FnvTERMRecord, 'TERM', 0)

    def create_ARMO(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("ARMO", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvARMORecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    ARMO = CBashRECORDARRAY(FnvARMORecord, 'ARMO', 0)

    def create_BOOK(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("BOOK", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvBOOKRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    BOOK = CBashRECORDARRAY(FnvBOOKRecord, 'BOOK', 0)

    def create_CONT(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("CONT", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvCONTRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    CONT = CBashRECORDARRAY(FnvCONTRecord, 'CONT', 0)

    def create_DOOR(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("DOOR", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvDOORRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    DOOR = CBashRECORDARRAY(FnvDOORRecord, 'DOOR', 0)

    def create_INGR(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("INGR", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvINGRRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    INGR = CBashRECORDARRAY(FnvINGRRecord, 'INGR', 0)

    def create_LIGH(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("LIGH", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvLIGHRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    LIGH = CBashRECORDARRAY(FnvLIGHRecord, 'LIGH', 0)

    def create_MISC(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("MISC", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvMISCRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    MISC = CBashRECORDARRAY(FnvMISCRecord, 'MISC', 0)

    def create_STAT(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("STAT", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvSTATRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    STAT = CBashRECORDARRAY(FnvSTATRecord, 'STAT', 0)

    def create_SCOL(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("SCOL", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvSCOLRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    SCOL = CBashRECORDARRAY(FnvSCOLRecord, 'SCOL', 0)

    def create_MSTT(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("MSTT", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvMSTTRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    MSTT = CBashRECORDARRAY(FnvMSTTRecord, 'MSTT', 0)

    def create_PWAT(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("PWAT", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvPWATRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    PWAT = CBashRECORDARRAY(FnvPWATRecord, 'PWAT', 0)

    def create_GRAS(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("GRAS", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvGRASRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    GRAS = CBashRECORDARRAY(FnvGRASRecord, 'GRAS', 0)

    def create_TREE(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("TREE", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvTREERecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    TREE = CBashRECORDARRAY(FnvTREERecord, 'TREE', 0)

    def create_FURN(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("FURN", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvFURNRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    FURN = CBashRECORDARRAY(FnvFURNRecord, 'FURN', 0)

    def create_WEAP(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("WEAP", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvWEAPRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    WEAP = CBashRECORDARRAY(FnvWEAPRecord, 'WEAP', 0)

    def create_AMMO(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("AMMO", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvAMMORecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    AMMO = CBashRECORDARRAY(FnvAMMORecord, 'AMMO', 0)

    def create_NPC_(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("NPC_", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvNPC_Record(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    NPC_ = CBashRECORDARRAY(FnvNPC_Record, 'NPC_', 0)

    def create_CREA(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("CREA", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvCREARecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    CREA = CBashRECORDARRAY(FnvCREARecord, 'CREA', 0)

    def create_LVLC(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("LVLC", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvLVLCRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    LVLC = CBashRECORDARRAY(FnvLVLCRecord, 'LVLC', 0)

    def create_LVLN(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("LVLN", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvLVLNRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    LVLN = CBashRECORDARRAY(FnvLVLNRecord, 'LVLN', 0)

    def create_KEYM(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("KEYM", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvKEYMRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    KEYM = CBashRECORDARRAY(FnvKEYMRecord, 'KEYM', 0)

    def create_ALCH(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("ALCH", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvALCHRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    ALCH = CBashRECORDARRAY(FnvALCHRecord, 'ALCH', 0)

    def create_IDLM(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("IDLM", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvIDLMRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    IDLM = CBashRECORDARRAY(FnvIDLMRecord, 'IDLM', 0)

    def create_NOTE(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("NOTE", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvNOTERecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    NOTE = CBashRECORDARRAY(FnvNOTERecord, 'NOTE', 0)

    def create_COBJ(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("COBJ", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvCOBJRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    COBJ = CBashRECORDARRAY(FnvCOBJRecord, 'COBJ', 0)

    def create_PROJ(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("PROJ", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvPROJRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    PROJ = CBashRECORDARRAY(FnvPROJRecord, 'PROJ', 0)

    def create_LVLI(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("LVLI", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvLVLIRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    LVLI = CBashRECORDARRAY(FnvLVLIRecord, 'LVLI', 0)

    def create_WTHR(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("WTHR", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvWTHRRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    WTHR = CBashRECORDARRAY(FnvWTHRRecord, 'WTHR', 0)

    def create_CLMT(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("CLMT", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvCLMTRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    CLMT = CBashRECORDARRAY(FnvCLMTRecord, 'CLMT', 0)

    def create_REGN(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("REGN", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvREGNRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    REGN = CBashRECORDARRAY(FnvREGNRecord, 'REGN', 0)

    def create_NAVI(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("NAVI", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvNAVIRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    NAVI = CBashRECORDARRAY(FnvNAVIRecord, 'NAVI', 0)

    def create_CELL(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("CELL", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvCELLRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    CELL = CBashRECORDARRAY(FnvCELLRecord, 'CELL', 0)

    def create_WRLD(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("WRLD", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvWRLDRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    WRLD = CBashRECORDARRAY(FnvWRLDRecord, 'WRLD', 0)

    def create_DIAL(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("DIAL", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvDIALRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    DIAL = CBashRECORDARRAY(FnvDIALRecord, 'DIAL', 0)

    def create_QUST(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("QUST", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvQUSTRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    QUST = CBashRECORDARRAY(FnvQUSTRecord, 'QUST', 0)

    def create_IDLE(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("IDLE", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvIDLERecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    IDLE = CBashRECORDARRAY(FnvIDLERecord, 'IDLE', 0)

    def create_PACK(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("PACK", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvPACKRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    PACK = CBashRECORDARRAY(FnvPACKRecord, 'PACK', 0)

    def create_CSTY(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("CSTY", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvCSTYRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    CSTY = CBashRECORDARRAY(FnvCSTYRecord, 'CSTY', 0)

    def create_LSCR(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("LSCR", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvLSCRRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    LSCR = CBashRECORDARRAY(FnvLSCRRecord, 'LSCR', 0)

    def create_ANIO(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("ANIO", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvANIORecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    ANIO = CBashRECORDARRAY(FnvANIORecord, 'ANIO', 0)

    def create_WATR(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("WATR", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvWATRRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    WATR = CBashRECORDARRAY(FnvWATRRecord, 'WATR', 0)

    def create_EFSH(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("EFSH", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvEFSHRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    EFSH = CBashRECORDARRAY(FnvEFSHRecord, 'EFSH', 0)

    def create_EXPL(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("EXPL", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvEXPLRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    EXPL = CBashRECORDARRAY(FnvEXPLRecord, 'EXPL', 0)

    def create_DEBR(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("DEBR", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvDEBRRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    DEBR = CBashRECORDARRAY(FnvDEBRRecord, 'DEBR', 0)

    def create_IMGS(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("IMGS", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvIMGSRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    IMGS = CBashRECORDARRAY(FnvIMGSRecord, 'IMGS', 0)

    def create_IMAD(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("IMAD", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvIMADRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    IMAD = CBashRECORDARRAY(FnvIMADRecord, 'IMAD', 0)

    def create_FLST(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("FLST", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvFLSTRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    FLST = CBashRECORDARRAY(FnvFLSTRecord, 'FLST', 0)

    def create_PERK(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("PERK", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvPERKRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    PERK = CBashRECORDARRAY(FnvPERKRecord, 'PERK', 0)

    def create_BPTD(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("BPTD", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvBPTDRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    BPTD = CBashRECORDARRAY(FnvBPTDRecord, 'BPTD', 0)

    def create_ADDN(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("ADDN", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvADDNRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    ADDN = CBashRECORDARRAY(FnvADDNRecord, 'ADDN', 0)

    def create_AVIF(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("AVIF", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvAVIFRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    AVIF = CBashRECORDARRAY(FnvAVIFRecord, 'AVIF', 0)

    def create_RADS(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("RADS", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvRADSRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    RADS = CBashRECORDARRAY(FnvRADSRecord, 'RADS', 0)

    def create_CAMS(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("CAMS", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvCAMSRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    CAMS = CBashRECORDARRAY(FnvCAMSRecord, 'CAMS', 0)

    def create_CPTH(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("CPTH", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvCPTHRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    CPTH = CBashRECORDARRAY(FnvCPTHRecord, 'CPTH', 0)

    def create_VTYP(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("VTYP", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvVTYPRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    VTYP = CBashRECORDARRAY(FnvVTYPRecord, 'VTYP', 0)

    def create_IPCT(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("IPCT", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvIPCTRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    IPCT = CBashRECORDARRAY(FnvIPCTRecord, 'IPCT', 0)

    def create_IPDS(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("IPDS", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvIPDSRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    IPDS = CBashRECORDARRAY(FnvIPDSRecord, 'IPDS', 0)

    def create_ARMA(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("ARMA", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvARMARecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    ARMA = CBashRECORDARRAY(FnvARMARecord, 'ARMA', 0)

    def create_ECZN(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("ECZN", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvECZNRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    ECZN = CBashRECORDARRAY(FnvECZNRecord, 'ECZN', 0)

    def create_MESG(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("MESG", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvMESGRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    MESG = CBashRECORDARRAY(FnvMESGRecord, 'MESG', 0)

    def create_RGDL(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("RGDL", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvRGDLRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    RGDL = CBashRECORDARRAY(FnvRGDLRecord, 'RGDL', 0)

    def create_DOBJ(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("DOBJ", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvDOBJRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    DOBJ = CBashRECORDARRAY(FnvDOBJRecord, 'DOBJ', 0)

    def create_LGTM(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("LGTM", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvLGTMRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    LGTM = CBashRECORDARRAY(FnvLGTMRecord, 'LGTM', 0)

    def create_MUSC(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("MUSC", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvMUSCRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    MUSC = CBashRECORDARRAY(FnvMUSCRecord, 'MUSC', 0)

    def create_IMOD(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("IMOD", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvIMODRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    IMOD = CBashRECORDARRAY(FnvIMODRecord, 'IMOD', 0)

    def create_REPU(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("REPU", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvREPURecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    REPU = CBashRECORDARRAY(FnvREPURecord, 'REPU', 0)

    def create_RCPE(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("RCPE", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvRCPERecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    RCPE = CBashRECORDARRAY(FnvRCPERecord, 'RCPE', 0)

    def create_RCCT(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("RCCT", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvRCCTRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    RCCT = CBashRECORDARRAY(FnvRCCTRecord, 'RCCT', 0)

    def create_CHIP(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("CHIP", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvCHIPRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    CHIP = CBashRECORDARRAY(FnvCHIPRecord, 'CHIP', 0)

    def create_CSNO(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("CSNO", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvCSNORecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    CSNO = CBashRECORDARRAY(FnvCSNORecord, 'CSNO', 0)

    def create_LSCT(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("LSCT", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvLSCTRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    LSCT = CBashRECORDARRAY(FnvLSCTRecord, 'LSCT', 0)

    def create_MSET(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("MSET", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvMSETRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    MSET = CBashRECORDARRAY(FnvMSETRecord, 'MSET', 0)

    def create_ALOC(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("ALOC", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvALOCRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    ALOC = CBashRECORDARRAY(FnvALOCRecord, 'ALOC', 0)

    def create_CHAL(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("CHAL", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvCHALRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    CHAL = CBashRECORDARRAY(FnvCHALRecord, 'CHAL', 0)

    def create_AMEF(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("AMEF", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvAMEFRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    AMEF = CBashRECORDARRAY(FnvAMEFRecord, 'AMEF', 0)

    def create_CCRD(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("CCRD", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvCCRDRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    CCRD = CBashRECORDARRAY(FnvCCRDRecord, 'CCRD', 0)

    def create_CMNY(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("CMNY", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvCMNYRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    CMNY = CBashRECORDARRAY(FnvCMNYRecord, 'CMNY', 0)

    def create_CDCK(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("CDCK", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvCDCKRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    CDCK = CBashRECORDARRAY(FnvCDCKRecord, 'CDCK', 0)

    def create_DEHY(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("DEHY", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvDEHYRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    DEHY = CBashRECORDARRAY(FnvDEHYRecord, 'DEHY', 0)

    def create_HUNG(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("HUNG", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvHUNGRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    HUNG = CBashRECORDARRAY(FnvHUNGRecord, 'HUNG', 0)

    def create_SLPD(self, EditorID=0, FormID=0):
        RecordID = CBash.CreateRecord(self._CollectionID, self._ModID, cast("SLPD", POINTER(c_ulong)).contents.value, MakeShortFid(self._CollectionID, FormID), EditorID, 0, 0)
        if(RecordID): return FnvSLPDRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None
    SLPD = CBashRECORDARRAY(FnvSLPDRecord, 'SLPD', 0)

  
    @property
    def tops(self):
        return dict((("GMST", self.GMST),("TXST", self.TXST),("MICN", self.MICN),
                     ("GLOB", self.GLOB),("CLAS", self.CLAS),("FACT", self.FACT),
                     ("HDPT", self.HDPT),("HAIR", self.HAIR),("EYES", self.EYES),
                     ("RACE", self.RACE),("SOUN", self.SOUN),("ASPC", self.ASPC),
                     ("MGEF", self.MGEF),("SCPT", self.SCPT),("LTEX", self.LTEX),
                     ("ENCH", self.ENCH),("SPEL", self.SPEL),("ACTI", self.ACTI),
                     ("TACT", self.TACT),("TERM", self.TERM),("ARMO", self.ARMO),
                     ("BOOK", self.BOOK),("CONT", self.CONT),("DOOR", self.DOOR),
                     ("INGR", self.INGR),("LIGH", self.LIGH),("MISC", self.MISC),
                     ("STAT", self.STAT),("SCOL", self.SCOL),("MSTT", self.MSTT),
                     ("PWAT", self.PWAT),("GRAS", self.GRAS),("TREE", self.TREE),
                     ("FURN", self.FURN),("WEAP", self.WEAP),("AMMO", self.AMMO),
                     ("NPC_", self.NPC_),("CREA", self.CREA),("LVLC", self.LVLC),
                     ("LVLN", self.LVLN),("KEYM", self.KEYM),("ALCH", self.ALCH),
                     ("IDLM", self.IDLM),("NOTE", self.NOTE),("COBJ", self.COBJ),
                     ("PROJ", self.PROJ),("LVLI", self.LVLI),("WTHR", self.WTHR),
                     ("CLMT", self.CLMT),("REGN", self.REGN),("NAVI", self.NAVI),
                     ("CELL", self.CELL),("WRLD", self.WRLD),("DIAL", self.DIAL),
                     ("QUST", self.QUST),("IDLE", self.IDLE),("PACK", self.PACK),
                     ("CSTY", self.CSTY),("LSCR", self.LSCR),("ANIO", self.ANIO),
                     ("WATR", self.WATR),("EFSH", self.EFSH),("EXPL", self.EXPL),
                     ("DEBR", self.DEBR),("IMGS", self.IMGS),("IMAD", self.IMAD),
                     ("FLST", self.FLST),("PERK", self.PERK),("BPTD", self.BPTD),
                     ("ADDN", self.ADDN),("AVIF", self.AVIF),("RADS", self.RADS),
                     ("CAMS", self.CAMS),("CPTH", self.CPTH),("VTYP", self.VTYP),
                     ("IPCT", self.IPCT),("IPDS", self.IPDS),("ARMA", self.ARMA),
                     ("ECZN", self.ECZN),("MESG", self.MESG),("RGDL", self.RGDL),
                     ("DOBJ", self.DOBJ),("LGTM", self.LGTM),("MUSC", self.MUSC),
                     ("IMOD", self.IMOD),("REPU", self.REPU),("RCPE", self.RCPE),
                     ("RCCT", self.RCCT),("CHIP", self.CHIP),("CSNO", self.CSNO),
                     ("LSCT", self.LSCT),("MSET", self.MSET),("ALOC", self.ALOC),
                     ("CHAL", self.CHAL),("AMEF", self.AMEF),("CCRD", self.CCRD),
                     ("CMNY", self.CMNY),("CDCK", self.CDCK),("DEHY", self.DEHY),
                     ("HUNG", self.HUNG),("SLPD", self.SLPD),))

    @property
    def aggregates(self):
        return dict((("GMST", self.GMST),("TXST", self.TXST),("MICN", self.MICN),
                     ("GLOB", self.GLOB),("CLAS", self.CLAS),("FACT", self.FACT),
                     ("HDPT", self.HDPT),("HAIR", self.HAIR),("EYES", self.EYES),
                     ("RACE", self.RACE),("SOUN", self.SOUN),("ASPC", self.ASPC),
                     ("MGEF", self.MGEF),("SCPT", self.SCPT),("LTEX", self.LTEX),
                     ("ENCH", self.ENCH),("SPEL", self.SPEL),("ACTI", self.ACTI),
                     ("TACT", self.TACT),("TERM", self.TERM),("ARMO", self.ARMO),
                     ("BOOK", self.BOOK),("CONT", self.CONT),("DOOR", self.DOOR),
                     ("INGR", self.INGR),("LIGH", self.LIGH),("MISC", self.MISC),
                     ("STAT", self.STAT),("SCOL", self.SCOL),("MSTT", self.MSTT),
                     ("PWAT", self.PWAT),("GRAS", self.GRAS),("TREE", self.TREE),
                     ("FURN", self.FURN),("WEAP", self.WEAP),("AMMO", self.AMMO),
                     ("NPC_", self.NPC_),("CREA", self.CREA),("LVLC", self.LVLC),
                     ("LVLN", self.LVLN),("KEYM", self.KEYM),("ALCH", self.ALCH),
                     ("IDLM", self.IDLM),("NOTE", self.NOTE),("COBJ", self.COBJ),
                     ("PROJ", self.PROJ),("LVLI", self.LVLI),("WTHR", self.WTHR),
                     ("CLMT", self.CLMT),("REGN", self.REGN),("NAVI", self.NAVI),
                     ("CELL", self.CELL),("WRLD", self.WRLD),("DIAL", self.DIAL),
                     ("QUST", self.QUST),("IDLE", self.IDLE),("PACK", self.PACK),
                     ("CSTY", self.CSTY),("LSCR", self.LSCR),("ANIO", self.ANIO),
                     ("WATR", self.WATR),("EFSH", self.EFSH),("EXPL", self.EXPL),
                     ("DEBR", self.DEBR),("IMGS", self.IMGS),("IMAD", self.IMAD),
                     ("FLST", self.FLST),("PERK", self.PERK),("BPTD", self.BPTD),
                     ("ADDN", self.ADDN),("AVIF", self.AVIF),("RADS", self.RADS),
                     ("CAMS", self.CAMS),("CPTH", self.CPTH),("VTYP", self.VTYP),
                     ("IPCT", self.IPCT),("IPDS", self.IPDS),("ARMA", self.ARMA),
                     ("ECZN", self.ECZN),("MESG", self.MESG),("RGDL", self.RGDL),
                     ("DOBJ", self.DOBJ),("LGTM", self.LGTM),("MUSC", self.MUSC),
                     ("IMOD", self.IMOD),("REPU", self.REPU),("RCPE", self.RCPE),
                     ("RCCT", self.RCCT),("CHIP", self.CHIP),("CSNO", self.CSNO),
                     ("LSCT", self.LSCT),("MSET", self.MSET),("ALOC", self.ALOC),
                     ("CHAL", self.CHAL),("AMEF", self.AMEF),("CCRD", self.CCRD),
                     ("CMNY", self.CMNY),("CDCK", self.CDCK),("DEHY", self.DEHY),
                     ("HUNG", self.HUNG),("SLPD", self.SLPD),))

class ObCollection:
    """Collection of esm/esp's."""
    def __init__(self, CollectionID=None, ModsPath=".", CollectionType=0):
        #CollectionType == 0, Oblivion
        #CollectionType == 1, Fallout 3
        #CollectionType == 2, Fallout New Vegas
        self._CollectionID = CollectionID or _CCreateCollection(str(ModsPath), CollectionType) #Oblivion collection type hardcoded for now
        self._ModIndex = -1
        self._WhichGame = CollectionType
        self.LoadOrderMods = []
        self.AllMods = []

    def __eq__(self, other):
        if type(other) is type(self):
            return self._CollectionID == other._CollectionID
        return False

    def __ne__(self, other):
        return not self.__eq__(other)

    def addMod(self, FileName, MinLoad=True, NoLoad=False, IgnoreExisting=False, Flags=0x00000078):
##        //MinLoad and FullLoad are exclusive
##        // If both are set, FullLoad takes priority
##        // If neither is set, the mod isn't loaded
##
##        //SkipNewRecords causes any new record to be ignored when the mod is loaded
##        // This may leave broken records behind (such as a quest override pointing to a new script that was ignored)
##        // So it shouldn't be used if planning on copying records unless you either check that there are no new records being referenced
##
##        //InLoadOrder makes the mod count towards the 255 limit and enables record creation and copying as new.
##        // If it is false, it forces Saveable to be false.
##        // Any mod with new records should have this set unless you're ignoring the new records.
##        // It causes the mod to be reported by GetNumModIDs, GetModIDs
##
##        //Saveable allows the mod to be saved.
##
##        //AddMasters causes the mod's masters to be added
##        // This is essential for most mod editing functions.
##
##        //LoadMasters causes the mod's masters to be added to the load order and loaded into memory
##        // This has no effect if AddMasters is false
##        // This is required if you want to lookup overridden records
##
##        //ExtendedConflicts causes any conflicting records to be ignored by most functions
##        // IsRecordWinning, GetNumRecordConflicts, GetRecordConflicts will report the extended conflicts only if asked
##
##        //TrackNewTypes causes the loader to track which record types in a mod are new and not overrides
##        // Increases load time per mod.
##        // It enables GetModNumTypes and GetModTypes for that mod.
##
##        //IndexLANDs causes LAND records to have extra indexing.
##        // Increases load time per mod.
##        // It allows the safe editing of land records heights.
##        // Modifying one LAND may require changes in an adjacent LAND to prevent seams
##
##        //FixupPlaceables moves any REFR,ACHR,ACRE records in a world cell to the actual cell they belong to.
##        // Increases load time per mod.
##        // Use if you're planning on iterating through every placeable in a specific cell
##        //   so that you don't have to check the world cell as well.
##
##        //IgnoreAbsentMasters causes any records that override masters not in the load order to be dropped
##        // If it is true, it forces IsAddMasters to be false.
##        // Allows mods not in load order to copy records
##
##        //Only the following combinations are tested:
##        // Normal:  (fIsMinLoad or fIsFullLoad) + fIsInLoadOrder + fIsSaveable + fIsAddMasters + fIsLoadMasters
##        // Merged:  (fIsMinLoad or fIsFullLoad) + fIsSkipNewRecords + fIgnoreAbsentMasters
##        // Scanned: (fIsMinLoad or fIsFullLoad) + fIsSkipNewRecords + fIsExtendedConflicts

        fIsMinLoad             = 0x00000001
        fIsFullLoad            = 0x00000002
        fIsSkipNewRecords      = 0x00000004
        fIsInLoadOrder         = 0x00000008
        fIsSaveable            = 0x00000010
        fIsAddMasters          = 0x00000020
        fIsLoadMasters         = 0x00000040
        fIsExtendedConflicts   = 0x00000080
        fIsTrackNewTypes       = 0x00000100
        fIsIndexLANDs          = 0x00000200
        fIsFixupPlaceables     = 0x00000400
        fIsIgnoreExisting      = 0x00000800
        fIsIgnoreAbsentMasters = 0x00001000

        if IgnoreExisting:
            Flags |= fIsIgnoreExisting
        else:
            Flags &= ~fIsIgnoreExisting
        if NoLoad:
            Flags &= ~fIsFullLoad
            Flags &= ~fIsMinLoad
        elif MinLoad:
            Flags |= fIsMinLoad
            Flags &= ~fIsFullLoad
        else:
            Flags |= fIsFullLoad
            Flags &= ~fIsMinLoad
        _CAddMod(self._CollectionID, str(FileName), Flags)
        return None

    def addMergeMod(self, FileName):
        return self.addMod(FileName, Flags=0x00001004)

    def addScanMod(self, FileName):
        return self.addMod(FileName, Flags=0x00001084)

    def load(self):
        _CLoadCollection(self._CollectionID)

        _NumModsIDs = _CGetLoadOrderNumMods(self._CollectionID)
        if _NumModsIDs > 0:
            cModIDs = (c_ulong * _NumModsIDs)()
            _CGetLoadOrderModIDs(self._CollectionID, byref(cModIDs))
            if self._WhichGame == 0:
                self.LoadOrderMods = [ObModFile(self._CollectionID, ModID) for ModID in cModIDs]
            elif self._WhichGame == 2:
                self.LoadOrderMods = [FnvModFile(self._CollectionID, ModID) for ModID in cModIDs]

        _NumModsIDs = _CGetAllNumMods(self._CollectionID)
        if _NumModsIDs > 0:
            cModIDs = (c_ulong * _NumModsIDs)()
            _CGetAllModIDs(self._CollectionID, byref(cModIDs))
            if self._WhichGame == 0:
                self.AllMods = [ObModFile(self._CollectionID, ModID) for ModID in cModIDs]
            elif self._WhichGame == 2:
                self.AllMods = [FnvModFile(self._CollectionID, ModID) for ModID in cModIDs]

    def LookupRecord(self, RecordIdentifier):
        if not RecordIdentifier: return None
        if isinstance(RecordIdentifier, basestring):
            _FormID = 0
            _EditorID = RecordIdentifier
        else:
            _FormID = MakeShortFid(self._CollectionID, RecordIdentifier)
            _EditorID = 0
        if not (_FormID or _EditorID): return None
        RecordID = _CGetRecordID(self._CollectionID, self._ModID, _FormID, _EditorID)
        if RecordID:
            if self._WhichGame == 0:
                testRecord = ObBaseRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
                RecordType = type_record[testRecord.recType]
            elif self._WhichGame == 2:
                testRecord = FnvBaseRecord(self._CollectionID, self._ModID, RecordID, 0, 0)
                RecordType = fnv_type_record[testRecord.recType]
            if RecordType:
                return RecordType(self._CollectionID, self._ModID, RecordID, 0, 0)
        return None

    def LookupRecords(self, RecordIdentifier, GetExtendedConflicts=False):
        if not RecordIdentifier: return None
        if not isinstance(RecordIdentifier, basestring):
            RecordIdentifier = MakeShortFid(self._CollectionID, RecordIdentifier)
        if GetExtendedConflicts:
            records = [mod.LookupRecord(RecordIdentifier) for mod in reversed(self.AllMods)]
        else:
            records = [mod.LookupRecord(RecordIdentifier) for mod in reversed(self.LoadOrderMods)]
        return [record for record in records if record is not None]

    def LookupModFile(self, ModName):
        ModID = _CGetModIDByName(self._CollectionID, str(ModName))
        if(ModID == -1):
            raise KeyError("ModName(%s) not found in collection (%08X)\n" % (ModName, self._CollectionID) + self.Debug_DumpModFiles())
        if self._WhichGame == 0:
            return ObModFile(self._CollectionID, ModID)
        elif self._WhichGame == 2:
            return FnvModFile(self._CollectionID, ModID)

    def UpdateReferences(self, FormIDToReplace, ReplacementFormID):
        return sum([mod.UpdateReferences(FormIDToReplace, ReplacementFormID) for mod in self.LoadOrderMods])

    def Unload(self):
        _CUnloadCollection(self._CollectionID)

    def __del__(self):
        _CDeleteCollection(self._CollectionID)
    
    def Debug_DumpModFiles(self):
        value = "Collection (%08X) contains the following modfiles:\n" % (self._CollectionID,)
        for mod in self.AllMods:
            LoadOrder = _CGetModLoadOrderByID(self._CollectionID, mod._ModID)
            if LoadOrder == -1: LoadOrder = '--'
            else: LoadOrder = '%02X' % (LoadOrder,)
            ModName, FileName = mod.ModName, mod.FileName
            if ModName == FileName:
                value += "Load Order (%s), Name(%s)\n" % (LoadOrder, ModName)
            else:
                value += "Load Order (%s), ModName(%s) FileName(%s)\n" % (LoadOrder, ModName, FileName)
        return value