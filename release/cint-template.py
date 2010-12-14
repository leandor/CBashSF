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
        _CGetNumMods = CBash.GetNumMods
        _CGetModIDs = CBash.GetModIDs
        _CGetModName = CBash.GetModName
        _CGetModID = CBash.GetModID
        _CIsModEmpty = CBash.IsModEmpty
        _CGetModNumTypes = CBash.GetModNumTypes
        _CGetModTypes = CBash.GetModTypes
        _CCreateRecord = CBash.CreateRecord
        _CDeleteRecord = CBash.DeleteRecord
        _CCopyRecord = CBash.CopyRecord
        _CLoadRecord = CBash.LoadRecord
        _CUnloadRecord = CBash.UnloadRecord
        _CSetRecordIDs = CBash.SetRecordIDs
        _CGetNumRecords = CBash.GetNumRecords
        _CGetRecordFormIDs = CBash.GetRecordFormIDs
        _CGetRecordEditorIDs = CBash.GetRecordEditorIDs
        _CIsRecordWinning = CBash.IsRecordWinning
        _CGetNumRecordConflicts = CBash.GetNumRecordConflicts
        _CGetRecordConflicts = CBash.GetRecordConflicts
        _CUpdateReferences = CBash.UpdateReferences
        _CGetNumReferences = CBash.GetNumReferences
        _CSetField = CBash.SetField
        _CDeleteField = CBash.DeleteField
        _CGetFieldAttribute = CBash.GetFieldAttribute
        _CGetField = CBash.GetField
        _CGetVersionMajor.restype = c_ulong
        _CGetVersionMinor.restype = c_ulong
        _CGetVersionRevision.restype = c_ulong
        _CCreateCollection.restype = c_long
        _CDeleteCollection.restype = c_long
        _CLoadCollection.restype = c_long
        _CUnloadCollection.restype = c_long
        _CDeleteAllCollections.restype = c_long
        _CAddMod.restype = c_long
        _CLoadMod.restype = c_long
        _CUnloadMod.restype = c_long
        _CCleanModMasters.restype = c_long
        _CGetNumMods.restype = c_long
        _CGetModIDs.restype = c_long
        _CGetModName.restype = c_char_p
        _CGetModID.restype = c_long
        _CIsModEmpty.restype = c_ulong
        _CGetModNumTypes.restype = c_long
        _CCreateRecord.restype = c_ulong
        _CDeleteRecord.restype = c_long
        _CCopyRecord.restype = c_ulong
        _CLoadRecord.restype = c_long
        _CUnloadRecord.restype = c_long
        _CSetRecordIDs.restype = c_long
        _CGetNumRecords.restype = c_long
        _CIsRecordWinning.restype = c_long
        _CGetNumRecordConflicts.restype = c_long
        _CUpdateReferences.restype = c_long
        _CGetNumReferences.restype = c_long
        _CGetFieldAttribute.restype = c_ulong
    except ImportError as error:
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
                 'UINT8_OR_UINT32',
                 'UNKNOWN_OR_FORMID_OR_UINT32',
                 'UNKNOWN_OR_SINT32', 'MGEFCODE_OR_UINT32',
                 'FORMID_OR_MGEFCODE_OR_ACTORVALUE_OR_UINT32',
                 'RESOLVED_MGEFCODE', 'STATIC_MGEFCODE',
                 'RESOLVED_ACTORVALUE', 'STATIC_ACTORVALUE',
                 'CHAR', 'CHAR4', 'STRING', 'ISTRING', 'LIST',
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

    UNKNOWN, MISSING, JUNK, BOOL, SINT8, UINT8, SINT16, UINT16, SINT32, UINT32, FLOAT32, RADIAN, FORMID, MGEFCODE, ACTORVALUE, FORMID_OR_UINT32, UINT8_OR_UINT32, UNKNOWN_OR_FORMID_OR_UINT32, UNKNOWN_OR_SINT32, MGEFCODE_OR_UINT32, FORMID_OR_MGEFCODE_OR_ACTORVALUE_OR_UINT32, RESOLVED_MGEFCODE, STATIC_MGEFCODE, RESOLVED_ACTORVALUE, STATIC_ACTORVALUE, CHAR, CHAR4, STRING, ISTRING, LIST, PARENTRECORD, SUBRECORD, SINT8_FLAG, SINT8_TYPE, SINT8_FLAG_TYPE, SINT8_ARRAY, UINT8_FLAG, UINT8_TYPE, UINT8_FLAG_TYPE, UINT8_ARRAY, SINT16_FLAG, SINT16_TYPE, SINT16_FLAG_TYPE, SINT16_ARRAY, UINT16_FLAG, UINT16_TYPE, UINT16_FLAG_TYPE, UINT16_ARRAY, SINT32_FLAG, SINT32_TYPE, SINT32_FLAG_TYPE, SINT32_ARRAY, UINT32_FLAG, UINT32_TYPE, UINT32_FLAG_TYPE, UINT32_ARRAY, FLOAT32_ARRAY, RADIAN_ARRAY, FORMID_ARRAY, FORMID_OR_UINT32_ARRAY, MGEFCODE_OR_UINT32_ARRAY, STRING_ARRAY, ISTRING_ARRAY, SUBRECORD_ARRAY, UNDEFINED = range(len(__slots__))

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

def MakeLongFid(CollectionID, fid):
    if fid is None or fid == 0: return 0
    masterIndex = int(fid >> 24)
    object = int(fid & 0x00FFFFFFL)
    master = _CGetModName(CollectionID, masterIndex)
    return (GPath(master),object)

def MakeShortFid(CollectionID, fid):
    if fid is None or fid == 0: return 0
    if not isinstance(fid,tuple): return fid
    master, object = fid
    masterIndex = _CGetModID(CollectionID, str(master))
    if(masterIndex == -1): return None
    masterIndex = int(masterIndex << 24)
    object = int(object & 0x00FFFFFFL)
    return masterIndex | object

def MakeLongMGEFCode(CollectionID, MGEFCode):
    if MGEFCode is None or MGEFCode == 0: return 0
    masterIndex = int(MGEFCode & 0x000000FFL)
    object = int(MGEFCode & 0xFFFFFF00L)
    master = _CGetModName(CollectionID, masterIndex)
    return (GPath(master),object)

def MakeShortMGEFCode(CollectionID, MGEFCode):
    if isinstance(MGEFCode, basestring): MGEFCode = cast(MGEFCode, POINTER(c_ulong)).contents.value
    if MGEFCode is None or MGEFCode == 0: return 0
    if not isinstance(MGEFCode,tuple): return MGEFCode
    masterIndex = _CGetModID(CollectionID, str(MGEFCode[0]))
    if(masterIndex == -1):
        return None
    masterIndex = int(masterIndex & 0x000000FFL)
    object = int(MGEFCode & 0xFFFFFF00L)
    return masterIndex | object

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
        return 0
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
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, FieldID, 0, 0, 0, 0, 0, 0, 0)
        if(retValue): return retValue.contents.value
        return None
    def __set__(self, instance, nValue):
        FieldID = self._FieldID + instance._FieldID
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, 0, FieldID, 0, 0, 0, 0, 0, 0)
        else: _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, FieldID, 0, 0, 0, 0, 0, 0, byref(self._Type(nValue)), 0)

class CBashUINT8ARRAY_GROUP(object):
    def __init__(self, FieldID, Size=None):
        self._FieldID = FieldID
        self._Size = Size
    def __get__(self, instance, owner):
        FieldID = self._FieldID + instance._FieldID
        numRecords = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, 0, FieldID, 0, 0, 0, 0, 0, 0, 1)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, FieldID, 0, 0, 0, 0, 0, 0, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        return []
    def __set__(self, instance, nValue):
        FieldID = self._FieldID + instance._FieldID
        if nValue is None or not len(nValue): _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, 0, FieldID, 0, 0, 0, 0, 0, 0)
        else:
            length = len(nValue)
            if self._Size and length != self._Size: return
            cRecords = (c_ubyte * length)(*nValue)
            _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, FieldID, 0, 0, 0, 0, 0, 0, byref(cRecords), length)

class CBashFLOAT32_GROUP(object):
    def __init__(self, FieldID):
        self._FieldID = FieldID
    def __get__(self, instance, owner):
        FieldID = self._FieldID + instance._FieldID
        _CGetField.restype = POINTER(c_float)
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, FieldID, 0, 0, 0, 0, 0, 0, 0)
        if(retValue): return round(retValue.contents.value,6)
        return None
    def __set__(self, instance, nValue):
        FieldID = self._FieldID + instance._FieldID
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, 0, FieldID, 0, 0, 0, 0, 0, 0)
        else: _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, FieldID, 0, 0, 0, 0, 0, 0, byref(c_float(round(nValue,6))), 0)

class CBashSTRING_GROUP(object):
    def __init__(self, FieldID):
        self._FieldID = FieldID
    def __get__(self, instance, owner):
        FieldID = self._FieldID + instance._FieldID
        _CGetField.restype = c_char_p
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, FieldID, 0, 0, 0, 0, 0, 0, 0)
        if(retValue): return retValue
        return None
    def __set__(self, instance, nValue):
        FieldID = self._FieldID + instance._FieldID
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, 0, FieldID, 0, 0, 0, 0, 0, 0)
        else: _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, FieldID, 0, 0, 0, 0, 0, 0, nValue, 0)

class CBashISTRING_GROUP(object):
    def __init__(self, FieldID):
        self._FieldID = FieldID
    def __get__(self, instance, owner):
        FieldID = self._FieldID + instance._FieldID
        _CGetField.restype = c_char_p
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, FieldID, 0, 0, 0, 0, 0, 0, 0)
        if(retValue): return ISTRING(retValue)
        return None
    def __set__(self, instance, nValue):
        FieldID = self._FieldID + instance._FieldID
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, 0, FieldID, 0, 0, 0, 0, 0, 0)
        else: _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, FieldID, 0, 0, 0, 0, 0, 0, nValue, 0)

# Top level Descriptors
#  EDID keyed
class CBashEDIDGeneric(object):
    def __init__(self, FieldID, Type):
        self._FieldID = FieldID
        self._Type = Type
        self._ResType = POINTER(Type)
    def __get__(self, instance, owner):
        _CGetField.restype = self._ResType
        retValue = _CGetField(instance._CollectionID, instance._ModID, 0, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 0)
        if(retValue): return retValue.contents.value
        return None
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, 0, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0)
        else: _CSetField(instance._CollectionID, instance._ModID, 0, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, byref(self._Type(nValue)), 0)

class CBashEDIDFORMID(object):
    def __init__(self, FieldID):
        self._FieldID = FieldID
    def __get__(self, instance, owner):
        _CGetField.restype = POINTER(c_ulong)
        retValue = _CGetField(instance._CollectionID, instance._ModID, 0, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 0)
        if(retValue): return MakeLongFid(instance._CollectionID, retValue.contents.value)
        return None
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, 0, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0)
        else: _CSetField(instance._CollectionID, instance._ModID, 0, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, byref(c_ulong(MakeShortFid(instance._CollectionID, nValue))), 0)

class CBashEDIDSTRING(object):
    def __init__(self, FieldID):
        self._FieldID = FieldID
    def __get__(self, instance, owner):
        _CGetField.restype = c_char_p
        retValue = _CGetField(instance._CollectionID, instance._ModID, 0, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 0)
        if(retValue): return retValue
        return None
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, 0, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0)
        else: _CSetField(instance._CollectionID, instance._ModID, 0, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, nValue, 0)

class CBashEDIDISTRING(object):
    def __init__(self, FieldID):
        self._FieldID = FieldID
    def __get__(self, instance, owner):
        _CGetField.restype = c_char_p
        retValue = _CGetField(instance._CollectionID, instance._ModID, 0, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 0)
        if(retValue): return ISTRING(retValue)
        return None
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, 0, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0)
        else: _CSetField(instance._CollectionID, instance._ModID, 0, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, nValue, 0)

class CBashEDIDFLOAT32(object):
    def __init__(self, FieldID):
        self._FieldID = FieldID
    def __get__(self, instance, owner):
        _CGetField.restype = POINTER(c_float)
        retValue = _CGetField(instance._CollectionID, instance._ModID, 0, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 0)
        if(retValue): return round(retValue.contents.value,6)
        return None
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, 0, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0)
        else: _CSetField(instance._CollectionID, instance._ModID, 0, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, byref(c_float(round(nValue,6))), 0)

class CBashEDIDUINT8ARRAY(object):
    def __init__(self, FieldID, Size=None):
        self._FieldID = FieldID
        self._Size = Size
    def __get__(self, instance, owner):
        numRecords = _CGetFieldAttribute(instance._CollectionID, instance._ModID, 0, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 1)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            _CGetField(instance._CollectionID, instance._ModID, 0, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        return []
    def __set__(self, instance, nValue):
        if nValue is None or not len(nValue): _CDeleteField(instance._CollectionID, instance._ModID, 0, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0)
        else:
            length = len(nValue)
            if self._Size and length != self._Size: return
            cRecords = (c_ubyte * length)(*nValue)
            _CSetField(instance._CollectionID, instance._ModID, 0, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, byref(cRecords), length)

class CBashEDIDMGEFCODE_OR_UINT32_ARRAY(object):
    def __init__(self, FieldID, Size=None):
        self._FieldID = FieldID
        self._Size = Size
    def __get__(self, instance, owner):
        values = []
        numRecords = _CGetFieldAttribute(instance._CollectionID, instance._ModID, 0, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 1)
        if(numRecords > 0):
            cRecords = POINTER(c_ulong * numRecords)()
            _CGetField(instance._CollectionID, instance._ModID, 0, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, byref(cRecords))
            for x in range(numRecords):
                type = _CGetFieldAttribute(instance._CollectionID, instance._ModID, 0, instance._RecordID, self._FieldID, x, 1, 0, 0, 0, 0, 2)
                if type in (API_FIELDS.UINT32, API_FIELDS.STATIC_MGEFCODE):
                    values.append(cRecords.contents[x])
                elif type == API_FIELDS.RESOLVED_MGEFCODE:
                    values.append(MakeLongMGEFCode(instance._CollectionID, cRecords.contents[x]))
        return values
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, 0, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0)
        else:
            length = len(nValue)
            if self._Size and length != self._Size: return
            #They are either all MGEFCodes or all UINT32's, so it can be set in one operation
            nValue = [MakeShortMGEFCode(instance._CollectionID, x) for x in nValue]
            cRecords = (c_ulong * length)(*nValue)
            _CSetField(instance._CollectionID, instance._ModID, 0, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, byref(cRecords), length)

class CBashEDIDMGEFCODE(object):
    def __init__(self, FieldID):
        self._FieldID = FieldID
    def __get__(self, instance, owner):
        _CGetField.restype = POINTER(c_ulong)
        retValue = _CGetField(instance._CollectionID, instance._ModID, 0, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 0)
        if(retValue):
            type = _CGetFieldAttribute(instance._CollectionID, instance._ModID, 0, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 2)
            if type == API_FIELDS.STATIC_MGEFCODE:
                return retValue.contents.value
            elif type == API_FIELDS.RESOLVED_MGEFCODE:
                return MakeLongMGEFCode(instance._CollectionID, retValue.contents.value)
        return None
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, 0, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0)
        else:
            _CSetField(instance._CollectionID, instance._ModID, 0, instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, byref(c_ulong(MakeShortMGEFCode(instance._CollectionID, nValue))), 0)

#  FormID keyed
class CBashLIST(object):
    def __init__(self, FieldID, Type, AsList=False):
        self._FieldID = FieldID
        self._Type = Type
        self._AsList = AsList
    def __get__(self, instance, owner):
        numElements = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0, 1)
        oElements = [self._Type(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, x) for x in range(0, numElements)]
        if(self._AsList): return ExtractCopyList(oElements)
        return oElements
    def __set__(self, instance, nElements):
        length = len(nElements)
        if nElements is None or not length:
            _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0)
        else:
            if isinstance(nElements[0], tuple): nValues = nElements
            else: nValues = ExtractCopyList(nElements)
            ##Resizes the list
            _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0, 0, c_long(length))
            numElements = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0, 1)
            oElements = [self._Type(instance._CollectionID, instance._ModID, instance._RecordID, self._FieldID, x) for x in range(0, numElements)]
            SetCopyList(oElements, nValues)

class CBashSINT32_OR_UNKNOWN(object):
    def __init__(self, FieldID):
        self._FieldID = FieldID
    def __get__(self, instance, owner):
        type = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0, 2)
        if type == API_FIELDS.SINT32:
            _CGetField.restype = POINTER(c_long)
            retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0, 0)
            if(retValue): return retValue.contents.value
        return None
    def __set__(self, instance, nValue):
        type = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0, 2)
        if type == API_FIELDS.SINT32:
            if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0)
            else: _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0, byref(c_long(nValue)), 0)


class CBashXSED(object):
    """To delete the field, you have to set the current accessor to None."""
    def __init__(self, FieldID, AsOffset=False):
        self._FieldID = FieldID
        self._AsOffset = AsOffset
    def __get__(self, instance, owner):
        type = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0, 2)
        if self._AsOffset:
            if type == API_FIELDS.UINT32: return None #Mismatched variables
            _CGetField.restype = POINTER(c_ubyte)
        else:
            if type == API_FIELDS.UINT8: return None #Mismatched variables
            _CGetField.restype = POINTER(c_ulong)
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0, 0)
        if(retValue): return retValue.contents.value
        return None
    def __set__(self, instance, nValue):
        type = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0, 2)
        if nValue is None:
            if self._AsOffset:
                if type == API_FIELDS.UINT32: return #Mismatched variables
            else:
                if type == API_FIELDS.UINT8: return #Mismatched variables
            _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0)
        else:
            if self._AsOffset: nValue = c_ubyte(nValue)
            else: nValue = c_ulong(nValue)
            #Borrowing ArraySize to flag if the new value is an offset
            _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0, byref(nValue), c_bool(self._AsOffset))


class CBashISTRINGARRAY(object):
    def __init__(self, FieldID):
        self._FieldID = FieldID
    def __get__(self, instance, owner):
        numRecords = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0, 1)
        if(numRecords > 0):
            cRecords = (POINTER(c_char_p) * numRecords)()
            _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0, byref(cRecords))
            return [ISTRING(string_at(cRecords[x])) for x in range(0, numRecords)]
        return []
    def __set__(self, instance, nValue):
        if nValue is None or not len(nValue): _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0)
        else:
            length = len(nValue)
            cRecords = (c_char_p * length)(*nValue)
            _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0, byref(cRecords), length)

class CBashGeneric(object):
    def __init__(self, FieldID, Type):
        self._FieldID = FieldID
        self._Type = Type
        self._ResType = POINTER(Type)
    def __get__(self, instance, owner):
        _CGetField.restype = self._ResType
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0, 0)
        if(retValue): return retValue.contents.value
        return None
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0)
        else: _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0, byref(self._Type(nValue)), 0)

class CBashFORMID(object):
    def __init__(self, FieldID):
        self._FieldID = FieldID
    def __get__(self, instance, owner):
        _CGetField.restype = POINTER(c_ulong)
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0, 0)
        if(retValue): return MakeLongFid(instance._CollectionID, retValue.contents.value)
        return None
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0)
        else: _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0, byref(c_ulong(MakeShortFid(instance._CollectionID, nValue))), 0)

class CBashMGEFCODE(object):
    def __init__(self, FieldID):
        self._FieldID = FieldID
    def __get__(self, instance, owner):
        _CGetField.restype = POINTER(c_ulong)
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0, 0)
        if(retValue):
            type = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0, 2)
            if type == API_FIELDS.STATIC_MGEFCODE:
                return retValue.contents.value
            elif type == API_FIELDS.RESOLVED_MGEFCODE:
                return MakeLongMGEFCode(instance._CollectionID, retValue.contents.value)
        return None
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0)
        else:
            _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0, byref(c_ulong(MakeShortMGEFCode(instance._CollectionID, nValue))), 0)

class CBashFORMIDARRAY(object):
    def __init__(self, FieldID):
        self._FieldID = FieldID
    def __get__(self, instance, owner):
        numRecords = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0, 1)
        if(numRecords > 0):
            cRecords = POINTER(c_ulong * numRecords)()
            _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0, byref(cRecords))
            return [MakeLongFid(instance._CollectionID, cRecords.contents[x]) for x in range(0, numRecords)]
        return []
    def __set__(self, instance, nValue):
        if nValue is None or not len(nValue): _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0)
        else:
            length = len(nValue)
            cRecords = (c_ulong * length)(*nValue)
            _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0, byref(cRecords), length)

class CBashFORMID_OR_UINT32(object):
    def __init__(self, FieldID):
        self._FieldID = FieldID
    def __get__(self, instance, owner):
        _CGetField.restype = POINTER(c_ulong)
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0, 0)
        if(retValue):
            type = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0, 2)
            if type == API_FIELDS.UINT32:
                return retValue.contents.value
            elif type == API_FIELDS.FORMID:
                return MakeLongFid(instance._CollectionID, retValue.contents.value)
        return None
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0)
        else:
            _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0, byref(c_ulong(MakeShortFid(instance._CollectionID, nValue))), 0)

class CBashFORMID_OR_UINT32_ARRAY(object):
    def __init__(self, FieldID, Size=None):
        self._FieldID = FieldID
        self._Size = Size
    def __get__(self, instance, owner):
        values = []
        numRecords = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0, 1)
        if(numRecords > 0):
            cRecords = (c_ulong * numRecords)()
            _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0, byref(cRecords))
            for x in range(numRecords):
                type = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, x, 1, 0, 0, 0, 0, 2)
                if type == API_FIELDS.UINT32:
                    values.append(cRecords[x])
                elif type == API_FIELDS.FORMID:
                    values.append(MakeLongFid(instance._CollectionID, cRecords[x]))
        return values
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0)
        else:
            length = len(nValue)
            if self._Size and length != self._Size: return
            #Each element can be either a formID or UINT32, so they have to be set separately
            #Resize the list
            _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0, 0, c_long(length))
            for x, value in enumerate(nValue):
                #Borrowing ArraySize to flag if the new value is a formID
                IsFormID = isinstance(value, tuple)
                _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, x, 1, 0, 0, 0, 0, byref(c_ulong(MakeShortFid(instance._CollectionID, value))), IsFormID)

class CBashMGEFCODE_OR_UINT32_ARRAY(object):
    def __init__(self, FieldID, Size=None):
        self._FieldID = FieldID
        self._Size = Size
    def __get__(self, instance, owner):
        values = []
        numRecords = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0, 1)
        if(numRecords > 0):
            cRecords = POINTER(c_ulong * numRecords)()
            _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0, byref(cRecords))
            for x in range(numRecords):
                type = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, x, 1, 0, 0, 0, 0, 2)
                if type in (API_FIELDS.UINT32, API_FIELDS.STATIC_MGEFCODE):
                    values.append(cRecords.contents[x])
                elif type == API_FIELDS.RESOLVED_MGEFCODE:
                    values.append(MakeLongMGEFCode(instance._CollectionID, cRecords.contents[x]))
        return values
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0)
        else:
            length = len(nValue)
            if self._Size and length != self._Size: return
            #They are either all MGEFCodes or all UINT32's, so it can be set in one operation
            nValue = [MakeShortMGEFCode(instance._CollectionID, x) for x in nValue]
            cRecords = (c_ulong * length)(*nValue)
            _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0, byref(cRecords), length)

class CBashUINT8ARRAY(object):
    def __init__(self, FieldID, Size=None):
        self._FieldID = FieldID
        self._Size = Size
    def __get__(self, instance, owner):
        numRecords = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0, 1)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        return []
    def __set__(self, instance, nValue):
        if nValue is None or not len(nValue): _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0)
        else:
            length = len(nValue)
            if self._Size and length != self._Size: return
            cRecords = (c_ubyte * length)(*nValue)
            _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0, byref(cRecords), length)

class CBashUINT32ARRAY(object):
    def __init__(self, FieldID, Size=None):
        self._FieldID = FieldID
        self._Size = Size
    def __get__(self, instance, owner):
        numRecords = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0, 1)
        if(numRecords > 0):
            cRecords = POINTER(c_ulong * numRecords)()
            _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        return []
    def __set__(self, instance, nValue):
        if nValue is None or not len(nValue): _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0)
        else:
            length = len(nValue)
            if self._Size and length != self._Size: return
            cRecords = (c_ulong * length)(*nValue)
            _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0, byref(cRecords), length)

class CBashFLOAT32(object):
    def __init__(self, FieldID):
        self._FieldID = FieldID
    def __get__(self, instance, owner):
        _CGetField.restype = POINTER(c_float)
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0, 0)
        if(retValue): return round(retValue.contents.value,6)
        return None
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0)
        else: _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0, byref(c_float(round(nValue,6))), 0)

class CBashDEGREES(object):
    def __init__(self, FieldID):
        self._FieldID = FieldID
    def __get__(self, instance, owner):
        _CGetField.restype = POINTER(c_float)
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0, 0)
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
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0)
        else: _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0, byref(c_float(round(nValue,6))), 0)

class CBashSTRING(object):
    def __init__(self, FieldID):
        self._FieldID = FieldID
    def __get__(self, instance, owner):
        _CGetField.restype = c_char_p
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0, 0)
        if(retValue): return retValue
        return None
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0)
        else: _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0, nValue, 0)

class CBashISTRING(object):
    def __init__(self, FieldID):
        self._FieldID = FieldID
    def __get__(self, instance, owner):
        _CGetField.restype = c_char_p
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0, 0)
        if(retValue): return ISTRING(retValue)
        return None
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0)
        else: _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0, nValue, 0)


class CBashRECORDARRAY(object):
    def __init__(self, Type, TypeName, CopyFlags=0):
        self._Type = Type
        self._TypeName = cast(TypeName, POINTER(c_ulong)).contents.value
        self._CopyFlags = CopyFlags
    def __get__(self, instance, owner):
        numRecords = _CGetNumRecords(instance._CollectionID, instance._ModID, self._TypeName)
        if(numRecords > 0):
            cRecords = (c_ulong * numRecords)()
            _CGetRecordFormIDs(instance._CollectionID, instance._ModID, self._TypeName, byref(cRecords))
            return [self._Type(instance._CollectionID, instance._ModID, x, 0, self._CopyFlags) for x in cRecords]
        return []
    def __set__(self, instance, nValue):
        return

class CBashEDIDRECORDARRAY(object):
    def __init__(self, Type, TypeName, CopyFlags=0):
        self._Type = Type
        self._TypeName = cast(TypeName, POINTER(c_ulong)).contents.value
        self._CopyFlags = CopyFlags
    def __get__(self, instance, owner):
        numRecords = _CGetNumRecords(instance._CollectionID, instance._ModID, self._TypeName)
        if(numRecords > 0):
            cRecords = (POINTER(c_char_p) * numRecords)()
            _CGetRecordEditorIDs(instance._CollectionID, instance._ModID, self._TypeName, cRecords)
            return [self._Type(instance._CollectionID, instance._ModID, string_at(cRecords[x]), 0, self._CopyFlags) for x in range(0, numRecords)]
        return []
    def __set__(self, instance, nValue):
        return

class CBashSUBRECORD(object):
    def __init__(self, FieldID, Type, TypeName, CopyFlags=0):
        self._FieldID = FieldID
        self._Type = Type
        self._TypeName = TypeName
        self._CopyFlags = CopyFlags
        self._ResType = POINTER(c_ulong)
    def __get__(self, instance, owner):
        _CGetField.restype = self._ResType
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0, 0)
        if(retValue): return self._Type(instance._CollectionID, instance._ModID, retValue.contents.value, instance._RecordID, self._CopyFlags)
        return None
    def __set__(self, instance, nValue):
        _CGetField.restype = self._ResType
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0, 0)
        if(retValue): oSubRecord = self._Type(instance._CollectionID, instance._ModID, retValue.contents.value, instance._RecordID, self._CopyFlags)
        else: oSubRecord = None
        if nSubRecord is None and oSubRecord is not None: oSubRecord.DeleteRecord()
        else:
            if oSubRecord is None:
                FID = _CCreateRecord(instance._CollectionID, instance._ModID, self._TypeName, 0, 0, instance._RecordID, c_ulong(self._CopyFlags))
                if(FID): oSubRecord = self._Type(instance._CollectionID, instance._ModID, FID, instance._RecordID, self._CopyFlags)
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
        numRecords = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0, 1)
        if(numRecords > 0):
            cRecords = (c_ulong * numRecords)()
            _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, 0, 0, 0, 0, 0, 0, byref(cRecords))
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
        numElements = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, 0, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 1)
        oElements = [self._Type(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, x) for x in range(0, numElements)]
        if(self._AsList): return ExtractCopyList(oElements)
        return oElements
    def __set__(self, instance, nElements):
        length = len(nElements)
        if nElements is None or not length:
            _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, 0, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0)
        else:
            if isinstance(nElements[0], tuple): nValues = nElements
            else: nValues = ExtractCopyList(nElements)
            ##Resizes the list
            _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 0, c_long(length))
            numElements = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, 0, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 1)
            oElements = [self._Type(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, x) for x in range(0, numElements)]
            SetCopyList(oElements, nValues)

class CBashGeneric_LIST(object):
    def __init__(self, ListFieldID, Type):
        self._ListFieldID = ListFieldID
        self._Type = Type
        self._ResType = POINTER(Type)
    def __get__(self, instance, owner):
        _CGetField.restype = self._ResType
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 0)
        if(retValue): return retValue.contents.value
        return None
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, 0, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0)
        else: _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, byref(self._Type(nValue)), 0)

class CBashFORMID_LIST(object):
    def __init__(self, ListFieldID):
        self._ListFieldID = ListFieldID
    def __get__(self, instance, owner):
        _CGetField.restype = POINTER(c_ulong)
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 0)
        if(retValue): return MakeLongFid(instance._CollectionID, retValue.contents.value)
        return None
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, 0, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0)
        else: _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, byref(c_ulong(MakeShortFid(instance._CollectionID, nValue))), 0)

class CBashACTORVALUE_LIST(object):
    def __init__(self, ListFieldID):
        self._ListFieldID = ListFieldID
    def __get__(self, instance, owner):
        _CGetField.restype = POINTER(c_ulong)
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 0)
        if(retValue):
            type = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, 0, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 2)
            if type == API_FIELDS.STATIC_ACTORVALUE:
                return retValue.contents.value
            elif type == API_FIELDS.RESOLVED_ACTORVALUE:
                #Resolved Actor Value's are not formIDs, but can be treated as such for resolution
                return MakeLongFid(instance._CollectionID, retValue.contents.value)
        return None
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, 0, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0)
        else:
            _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, byref(c_ulong(MakeShortFid(instance._CollectionID, nValue))), 0)

class CBashFORMIDARRAY_LIST(object):
    def __init__(self, ListFieldID):
        self._ListFieldID = ListFieldID
    def __get__(self, instance, owner):
        numRecords = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, 0, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 1)
        if(numRecords > 0):
            cRecords = POINTER(c_ulong * numRecords)()
            _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, byref(cRecords))
            return [MakeLongFid(instance._CollectionID, cRecords.contents[x]) for x in range(0, numRecords)]
        return []
    def __set__(self, instance, nValue):
        if nValue is None or not len(nValue): _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, 0, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0)
        else:
            length = len(nValue)
            cRecords = (c_ulong * length)(*nValue)
            _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, byref(cRecords), length)

class CBashUNKNOWN_OR_FORMID_OR_UINT32_LIST(object):
    def __init__(self, ListFieldID):
        self._ListFieldID = ListFieldID
    def __get__(self, instance, owner):
        type = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, 0, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 2)
        if type != API_FIELDS.UNKNOWN:
            _CGetField.restype = POINTER(c_long)
            retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 0)
            if(retValue):
                if type == API_FIELDS.UINT32:
                    return retValue.contents.value
                elif type == API_FIELDS.FORMID:
                    return MakeLongFid(instance._CollectionID, retValue.contents.value)
        return None
    def __set__(self, instance, nValue):
        type = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, 0, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 2)
        if type != API_FIELDS.UNKNOWN:
            if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, 0, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0)
            else:
                _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, byref(c_ulong(MakeShortFid(instance._CollectionID, nValue))), 0)

class CBashMGEFCODE_OR_UINT32_LIST(object):
    def __init__(self, ListFieldID):
        self._ListFieldID = ListFieldID
    def __get__(self, instance, owner):
        _CGetField.restype = POINTER(c_long)
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 0)
        if(retValue):
            type = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, 0, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 2)
            if type in (API_FIELDS.UINT32, API_FIELDS.STATIC_MGEFCODE):
                return retValue.contents.value
            elif type == API_FIELDS.RESOLVED_MGEFCODE:
                return MakeLongMGEFCode(instance._CollectionID, retValue.contents.value)
        return None
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, 0, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0)
        else:
            _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, byref(c_long(MakeShortMGEFCode(instance._CollectionID, nValue))), 0)

class CBashFORMID_OR_MGEFCODE_OR_ACTORVALUE_OR_UINT32_LIST(object):
    def __init__(self, ListFieldID):
        self._ListFieldID = ListFieldID
    def __get__(self, instance, owner):
        _CGetField.restype = POINTER(c_long)
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 0)
        if(retValue):
            type = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, 0, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 2)
            if type in (API_FIELDS.UINT32, API_FIELDS.STATIC_MGEFCODE, API_FIELDS.STATIC_ACTORVALUE):
                return retValue.contents.value
            elif type == API_FIELDS.RESOLVED_MGEFCODE:
                return MakeLongMGEFCode(instance._CollectionID, retValue.contents.value)
            elif type in (API_FIELDS.FORMID, API_FIELDS.RESOLVED_ACTORVALUE):
                #Resolved Actor Value's are not formIDs, but can be treated as such for resolution
                return MakeLongFid(instance._CollectionID, retValue.contents.value)
        return None
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, 0, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0)
        else:
            type = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, 0, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 2)
            if type in (API_FIELDS.STATIC_MGEFCODE, API_FIELDS.RESOLVED_MGEFCODE): nValue = MakeShortMGEFCode(instance._CollectionID, nValue)
            elif type in (API_FIELDS.FORMID, API_FIELDS.STATIC_ACTORVALUE, API_FIELDS.RESOLVED_ACTORVALUE): nValue = MakeShortFid(instance._CollectionID, nValue)
            elif type == API_FIELDS.UINT32 and isinstance(nValue, tuple): return
            _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, byref(c_ulong(nValue)), 0)

class CBashUINT8ARRAY_LIST(object):
    def __init__(self, ListFieldID, Size=None):
        self._ListFieldID = ListFieldID
        self._Size = Size
    def __get__(self, instance, owner):
        numRecords = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, 0, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 1)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        return []
    def __set__(self, instance, nValue):
        if nValue is None or not len(nValue): _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, 0, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0)
        else:
            length = len(nValue)
            if self._Size and length != self._Size: return
            cRecords = (c_ubyte * length)(*nValue)
            _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, byref(cRecords), length)

class CBashUINT32ARRAY_LIST(object):
    def __init__(self, ListFieldID, Size=None):
        self._ListFieldID = ListFieldID
        self._Size = Size
    def __get__(self, instance, owner):
        numRecords = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, 0, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 1)
        if(numRecords > 0):
            cRecords = POINTER(c_ulong * numRecords)()
            _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        return []
    def __set__(self, instance, nValue):
        if nValue is None or not len(nValue): _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, 0, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0)
        else:
            length = len(nValue)
            if self._Size and length != self._Size: return
            cRecords = (c_ulong * length)(*nValue)
            _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, byref(cRecords), length)

class CBashFLOAT32_LIST(object):
    def __init__(self, ListFieldID):
        self._ListFieldID = ListFieldID
    def __get__(self, instance, owner):
        _CGetField.restype = POINTER(c_float)
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 0)
        if(retValue): return round(retValue.contents.value,6)
        return None
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, 0, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0)
        else: _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, byref(c_float(round(nValue,6))), 0)

class CBashSTRING_LIST(object):
    def __init__(self, ListFieldID):
        self._ListFieldID = ListFieldID
    def __get__(self, instance, owner):
        _CGetField.restype = c_char_p
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 0)
        if(retValue): return retValue
        return None
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, 0, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0)
        else: _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, nValue, 0)

class CBashISTRING_LIST(object):
    def __init__(self, ListFieldID):
        self._ListFieldID = ListFieldID
    def __get__(self, instance, owner):
        _CGetField.restype = c_char_p
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 0)
        if(retValue): return ISTRING(retValue)
        return None
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, 0, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0)
        else: _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, nValue, 0)

# ListX2 Descriptors
class CBashLIST_LISTX2(object):
    def __init__(self, FieldID, ListFieldID, ListX2FieldID, Type, AsList=False):
        self._FieldID = FieldID
        self._ListFieldID = ListFieldID
        self._ListX2FieldID = ListX2FieldID
        self._Type = Type
        self._AsList = AsList
    def __get__(self, instance, owner):
        numElements = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, instance._ListIndex, self._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, 1)
        oElements = [self._Type(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, instance._ListX2Index, self._ListX2FieldID, x) for x in range(0, numElements)]
        if(self._AsList): return ExtractCopyList(oElements)
        return oElements
    def __set__(self, instance, nElements):
        length = len(nElements)
        if nElements is None or not length:
            _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, instance._ListIndex, self._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0)
        else:
            if isinstance(nElements[0], tuple): nValues = nElements
            else: nValues = ExtractCopyList(nElements)
            ##Resizes the list
            _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, instance._ListIndex, self._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, 0, c_long(length))
            numElements = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, instance._ListIndex, self._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, 1)
            oElements = [self._Type(instance._CollectionID, instance._ModID, instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, instance._ListX2Index, self._ListX2FieldID, x) for x in range(0, numElements)]
            SetCopyList(oElements, nValues)

class CBashGeneric_LISTX2(object):
    def __init__(self, FieldID, ListFieldID, ListX2FieldID, Type):
        self._FieldID = FieldID
        self._ListFieldID = ListFieldID
        self._ListX2FieldID = ListX2FieldID
        self._Type = Type
        self._ResType = POINTER(Type)
    def __get__(self, instance, owner):
        _CGetField.restype = self._ResType
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, instance._ListIndex, self._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, 0)
        if(retValue): return retValue.contents.value
        return None
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, instance._ListIndex, self._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0)
        else: _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, instance._ListIndex, self._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, byref(self._Type(nValue)), 0)

class CBashFLOAT32_LISTX2(object):
    def __init__(self, FieldID, ListFieldID, ListX2FieldID):
        self._FieldID = FieldID
        self._ListFieldID = ListFieldID
        self._ListX2FieldID = ListX2FieldID
    def __get__(self, instance, owner):
        _CGetField.restype = POINTER(c_float)
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, instance._ListIndex, self._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, 0)
        if(retValue): return round(retValue.contents.value,6)
        return None
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, instance._ListIndex, self._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0)
        else: _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, instance._ListIndex, self._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, byref(c_float(round(nValue,6))), 0)

class CBashUINT8ARRAY_LISTX2(object):
    def __init__(self, FieldID, ListFieldID, ListX2FieldID, Size=None):
        self._FieldID = FieldID
        self._ListFieldID = ListFieldID
        self._ListX2FieldID = ListX2FieldID
        self._Size = Size
    def __get__(self, instance, owner):
        numRecords = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, instance._ListIndex, self._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, 1)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, instance._ListIndex, self._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        return []
    def __set__(self, instance, nValue):
        if nValue is None or not len(nValue): _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, instance._ListIndex, self._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0)
        else:
            length = len(nValue)
            if self._Size and length != self._Size: return
            cRecords = (c_ubyte * length)(*nValue)
            _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, instance._ListIndex, self._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, byref(cRecords), length)

class CBashFORMID_OR_UINT32_ARRAY_LISTX2(object):
    def __init__(self, FieldID, ListFieldID, ListX2FieldID, Size=None):
        self._FieldID = FieldID
        self._ListFieldID = ListFieldID
        self._ListX2FieldID = ListX2FieldID
        self._Size = Size
    def __get__(self, instance, owner):
        values = []
        numRecords = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, instance._ListIndex, self._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, 1)
        if(numRecords > 0):
            cRecords = (c_ulong * numRecords)()
            _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, instance._ListIndex, self._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, byref(cRecords))
            for x in range(numRecords):
                type = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, instance._ListIndex, self._ListFieldID, instance._ListX2Index, self._ListX2FieldID, x, 1, 2)
                if type == API_FIELDS.UINT32:
                    values.append(cRecords[x])
                elif type == API_FIELDS.FORMID:
                    values.append(MakeLongFid(instance._CollectionID, cRecords[x]))
        return values
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, instance._ListIndex, self._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0)
        else:
            length = len(nValue)
            if self._Size and length != self._Size: return
            #Each element can be either a formID or UINT32, so they have to be set separately
            #Resize the list
            _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, instance._ListIndex, self._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, 0, c_long(length))
            for x, value in enumerate(nValue):
                #Borrowing ArraySize to flag if the new value is a formID
                IsFormID = isinstance(value, tuple)
                _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, instance._ListIndex, self._ListFieldID, instance._ListX2Index, self._ListX2FieldID, x, 1, byref(c_ulong(MakeShortFid(instance._CollectionID, value))), IsFormID)
                
class CBashFORMID_LISTX2(object):
    def __init__(self, FieldID, ListFieldID, ListX2FieldID):
        self._FieldID = FieldID
        self._ListFieldID = ListFieldID
        self._ListX2FieldID = ListX2FieldID
    def __get__(self, instance, owner):
        _CGetField.restype = POINTER(c_ulong)
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, instance._ListIndex, self._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, 0)
        if(retValue): return MakeLongFid(instance._CollectionID, retValue.contents.value)
        return None
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, instance._ListIndex, self._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0)
        else: _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, instance._ListIndex, self._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, byref(c_ulong(MakeShortFid(instance._CollectionID, nValue))), 0)

class CBashSTRING_LISTX2(object):
    def __init__(self, FieldID, ListFieldID, ListX2FieldID):
        self._FieldID = FieldID
        self._ListFieldID = ListFieldID
        self._ListX2FieldID = ListX2FieldID
    def __get__(self, instance, owner):
        _CGetField.restype = c_char_p
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, instance._ListIndex, self._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, 0)
        if(retValue): return retValue
        return None
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, instance._ListIndex, self._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0)
        else: _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, instance._ListIndex, self._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, nValue, 0)

class CBashISTRING_LISTX2(object):
    def __init__(self, FieldID, ListFieldID, ListX2FieldID):
        self._FieldID = FieldID
        self._ListFieldID = ListFieldID
        self._ListX2FieldID = ListX2FieldID
    def __get__(self, instance, owner):
        _CGetField.restype = c_char_p
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, instance._ListIndex, self._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, 0)
        if(retValue): return ISTRING(retValue)
        return None
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, instance._ListIndex, self._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0)
        else: _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, instance._ListIndex, self._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, nValue, 0)

class CBashUNKNOWN_OR_FORMID_OR_UINT32_LISTX2(object):
    def __init__(self, FieldID, ListFieldID, ListX2FieldID):
        self._FieldID = FieldID
        self._ListFieldID = ListFieldID
        self._ListX2FieldID = ListX2FieldID
    def __get__(self, instance, owner):
        type = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, instance._ListIndex, self._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, 2)
        if type != API_FIELDS.UNKNOWN:
            _CGetField.restype = POINTER(c_long)
            retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, instance._ListIndex, self._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, 0)
            if(retValue):
                if type == API_FIELDS.UINT32:
                    return retValue.contents.value
                elif type == API_FIELDS.FORMID:
                    return MakeLongFid(instance._CollectionID, retValue.contents.value)
        return None
    def __set__(self, instance, nValue):
        type = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, instance._ListIndex, self._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, 2)
        if type != API_FIELDS.UNKNOWN:
            if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, instance._ListIndex, self._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0)
            else:
                _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, instance._ListIndex, self._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, byref(c_ulong(MakeShortFid(instance._CollectionID, nValue))), 0)


# ListX3 Descriptors
class CBashGeneric_LISTX3(object):
    def __init__(self, FieldID, ListFieldID, ListX2FieldID, ListX3FieldID, Type):
        self._FieldID = FieldID
        self._ListFieldID = ListFieldID
        self._ListX2FieldID = ListX2FieldID
        self._ListX3FieldID = ListX3FieldID
        self._Type = Type
        self._ResType = POINTER(Type)
    def __get__(self, instance, owner):
        _CGetField.restype = self._ResType
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, instance._ListIndex, self._ListFieldID, instance._ListX2Index, self._ListX2FieldID, instance._ListX3Index, self._ListX3FieldID, 0)
        if(retValue): return retValue.contents.value
        return None
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, instance._ListIndex, self._ListFieldID, instance._ListX2Index, self._ListX2FieldID, instance._ListX3Index, self._ListX3FieldID)
        else: _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, instance._ListIndex, self._ListFieldID, instance._ListX2Index, self._ListX2FieldID, instance._ListX3Index, self._ListX3FieldID, byref(self._Type(nValue)), 0)

class CBashUINT8ARRAY_LISTX3(object):
    def __init__(self, FieldID, ListFieldID, ListX2FieldID, ListX3FieldID, Size=None):
        self._FieldID = FieldID
        self._ListFieldID = ListFieldID
        self._ListX2FieldID = ListX2FieldID
        self._ListX3FieldID = ListX3FieldID
        self._Size = Size
    def __get__(self, instance, owner):
        numRecords = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, instance._ListIndex, self._ListFieldID, instance._ListX2Index, self._ListX2FieldID, instance._ListX3Index, self._ListX3FieldID, 1)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, instance._ListIndex, self._ListFieldID, instance._ListX2Index, self._ListX2FieldID, instance._ListX3Index, self._ListX3FieldID, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        return []
    def __set__(self, instance, nValue):
        if nValue is None or not len(nValue): _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, instance._ListIndex, self._ListFieldID, instance._ListX2Index, self._ListX2FieldID, instance._ListX3Index, self._ListX3FieldID)
        else:
            length = len(nValue)
            if self._Size and length != self._Size: return
            cRecords = (c_ubyte * length)(*nValue)
            _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, instance._ListIndex, self._ListFieldID, instance._ListX2Index, self._ListX2FieldID, instance._ListX3Index, self._ListX3FieldID, byref(cRecords), length)

class CBashFLOAT32_LISTX3(object):
    def __init__(self, FieldID, ListFieldID, ListX2FieldID, ListX3FieldID):
        self._FieldID = FieldID
        self._ListFieldID = ListFieldID
        self._ListX2FieldID = ListX2FieldID
        self._ListX3FieldID = ListX3FieldID
    def __get__(self, instance, owner):
        _CGetField.restype = POINTER(c_float)
        retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, instance._ListIndex, self._ListFieldID, instance._ListX2Index, self._ListX2FieldID, instance._ListX3Index, self._ListX3FieldID, 0)
        if(retValue): return round(retValue.contents.value,6)
        return None
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, instance._ListIndex, self._ListFieldID, instance._ListX2Index, self._ListX2FieldID, instance._ListX3Index, self._ListX3FieldID)
        else: _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, instance._ListIndex, self._ListFieldID, instance._ListX2Index, self._ListX2FieldID, instance._ListX3Index, self._ListX3FieldID, byref(c_float(round(nValue,6))), 0)

class CBashUNKNOWN_OR_FORMID_OR_UINT32_LISTX3(object):
    def __init__(self, FieldID, ListFieldID, ListX2FieldID, ListX3FieldID):
        self._FieldID = FieldID
        self._ListFieldID = ListFieldID
        self._ListX2FieldID = ListX2FieldID
        self._ListX3FieldID = ListX3FieldID
    def __get__(self, instance, owner):
        type = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, instance._ListIndex, self._ListFieldID, instance._ListX2Index, self._ListX2FieldID, instance._ListX3Index, self._ListX3FieldID, 2)
        if type != API_FIELDS.UNKNOWN:
            _CGetField.restype = POINTER(c_long)
            retValue = _CGetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, instance._ListIndex, self._ListFieldID, instance._ListX2Index, self._ListX2FieldID, instance._ListX3Index, self._ListX3FieldID, 0)
            if(retValue):
                if type == API_FIELDS.UINT32:
                    return retValue.contents.value
                elif type == API_FIELDS.FORMID:
                    return MakeLongFid(instance._CollectionID, retValue.contents.value)
        return None
    def __set__(self, instance, nValue):
        type = _CGetFieldAttribute(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, instance._ListIndex, self._ListFieldID, instance._ListX2Index, self._ListX2FieldID, instance._ListX3Index, self._ListX3FieldID, 2)
        if type != API_FIELDS.UNKNOWN:
            if nValue is None: _CDeleteField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, instance._ListIndex, self._ListFieldID, instance._ListX2Index, self._ListX2FieldID, instance._ListX3Index, self._ListX3FieldID)
            else:
                _CSetField(instance._CollectionID, instance._ModID, instance._RecordID, 0, self._FieldID, instance._ListIndex, self._ListFieldID, instance._ListX2Index, self._ListX2FieldID, instance._ListX3Index, self._ListX3FieldID, byref(c_ulong(MakeShortFid(instance._CollectionID, nValue))), 0)


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
    ISTRING_GROUPEDMACRO(modPath, 0)
    FLOAT32_GROUPEDMACRO(modb, 1)
    UINT8_ARRAY_GROUPEDMACRO(modt_p, 2)
    copyattrs = ['modPath', 'modb', 'modt_p']
    exportattrs = ['modPath', 'modb']#, 'modt_p']

class Item(ListComponent):
    FORMID_LISTMACRO(item, self._FieldID, 1)
    SINT32_LISTMACRO(count, self._FieldID, 2)
    exportattrs = copyattrs = ['item', 'count']

class Condition(ListComponent):
    UINT8_FLAG_TYPE_LISTMACRO(operType, self._FieldID, 1)
    UINT8_ARRAY_LISTMACRO(unused1, self._FieldID, 2, 3)
    FLOAT32_LISTMACRO(compValue, self._FieldID, 3)
    UINT32_TYPE_LISTMACRO(ifunc, self._FieldID, 4)
    UNKNOWN_OR_FORMID_OR_UINT32_LISTMACRO(param1, self._FieldID, 5)
    UNKNOWN_OR_FORMID_OR_UINT32_LISTMACRO(param2, self._FieldID, 6)
    UINT8_ARRAY_LISTMACRO(unused2, self._FieldID, 7, 4)
    MaskedTypeMACRO(IsEqual, operType, 0xF0, 0x00, IsNotEqual)
    MaskedTypeMACRO(IsNotEqual, operType, 0xF0, 0x20, IsEqual)
    MaskedTypeMACRO(IsGreater, operType, 0xF0, 0x40, IsEqual)
    MaskedTypeMACRO(IsGreaterOrEqual, operType, 0xF0, 0x60, IsEqual)
    MaskedTypeMACRO(IsLess, operType, 0xF0, 0x80, IsEqual)
    MaskedTypeMACRO(IsLessOrEqual, operType, 0xF0, 0xA0, IsEqual)
    BasicFlagMACRO(IsOr, operType, 0x01)
    BasicFlagMACRO(IsRunOnTarget, operType, 0x02)
    BasicFlagMACRO(IsUseGlobal, operType, 0x04)
    exportattrs = copyattrs = ['operType', 'compValue', 'ifunc', 'param1', 'param2']

class Effect(ListComponent):
    ##name0 and name are both are always the same value, so setting one will set both. They're basically aliases
    MGEFCODE_OR_UINT32_LISTMACRO(name0, self._FieldID, 1)
    MGEFCODE_OR_UINT32_LISTMACRO(name, self._FieldID, 2)
    UINT32_LISTMACRO(magnitude, self._FieldID, 3)
    UINT32_LISTMACRO(area, self._FieldID, 4)
    UINT32_LISTMACRO(duration, self._FieldID, 5)
    UINT32_LISTMACRO(rangeType, self._FieldID, 6)
    OBMEFORMID_OR_MGEFCODE_OR_ACTORVALUE_OR_UINT32_LISTMACRO(actorValue, self._FieldID, 7)
    OBMEFORMID_OR_MGEFCODE_OR_ACTORVALUE_OR_UINT32_LISTMACRO(script, self._FieldID, 8)
    UINT32_LISTMACRO(school, self._FieldID, 9)
    OBMEMGEFCODE_OR_UINT32_LISTMACRO(visual, self._FieldID, 10)
    UINT8_FLAG_LISTMACRO(flags, self._FieldID, 11)
    UINT8_ARRAY_LISTMACRO(unused1, self._FieldID, 12, 3)
    OBMESTRING_LISTMACRO(full, self._FieldID, 13)
    ##OBME Fields. Setting any of the below fields will make the mod require JRoush's OBME plugin for OBSE
    ##To see if OBME is in use, check the recordVersion field for a non-None value
    OBMEUINT8_LISTMACRO(recordVersion, self._FieldID, 14)
    OBMEUINT8_LISTMACRO(betaVersion, self._FieldID, 15)
    OBMEUINT8_LISTMACRO(minorVersion, self._FieldID, 16)
    OBMEUINT8_LISTMACRO(majorVersion, self._FieldID, 17)
    OBMEUINT8_LISTMACRO(efitParamInfo, self._FieldID, 18)
    OBMEUINT8_LISTMACRO(efixParamInfo, self._FieldID, 19)
    OBMEUINT8_ARRAY_LISTMACRO(reserved1, self._FieldID, 20, 0xA)
    OBMEISTRING_LISTMACRO(iconPath, self._FieldID, 21)
    ##If efixOverrides ever equals 0, the EFIX chunk will become unloaded
    ##This includes the fields: efixOverrides,  efixFlags, baseCost, resistAV, reserved2
    OBMEUINT32_FLAG_LISTMACRO(efixOverrides, self._FieldID, 22)
    OBMEUINT32_FLAG_LISTMACRO(efixFlags, self._FieldID, 23)
    OBMEFLOAT32_LISTMACRO(baseCost, self._FieldID, 24)
    OBMEACTORVALUE_LISTMACRO(resistAV, self._FieldID, 25)
    OBMEUINT8_ARRAY_LISTMACRO(reserved2, self._FieldID, 26, 0x10)
    BasicFlagMACRO(IsHostile, flags, 0x01)
    BasicTypeMACRO(IsSelf, rangeType, 0, IsTouch)
    BasicTypeMACRO(IsTouch, rangeType, 1, IsSelf)
    BasicTypeMACRO(IsTarget, rangeType, 2, IsSelf)
    ##OBME Fields. Setting any of the below fields will make the mod require JRoush's OBME plugin for OBSE
    ##To see if OBME is in use, check the recordVersion field for a non-None value
    OBMEBasicFlagMACRO(IsUsingHostileOverride, efixOverrides, 0x00000001)
    OBMEBasicFlagMACRO(IsUsingRecoversOverride, efixOverrides, 0x00000002)
    OBMEBasicFlagMACRO(IsUsingParamFlagAOverride, efixOverrides, 0x00000004)
    OBMEBasicFlagMACRO(IsUsingBeneficialOverride, efixOverrides, 0x00000008)
    OBMEBasicFlagMACRO(IsUsingEFIXParamOverride, efixOverrides, 0x00000010)
    OBMEBasicFlagMACRO(IsUsingSchoolOverride, efixOverrides, 0x00000020)
    OBMEBasicFlagMACRO(IsUsingNameOverride, efixOverrides, 0x00000040)
    OBMEBasicFlagMACRO(IsUsingVFXCodeOverride, efixOverrides, 0x00000080)
    OBMEBasicFlagMACRO(IsUsingBaseCostOverride, efixOverrides, 0x00000100)
    OBMEBasicFlagMACRO(IsUsingResistAVOverride, efixOverrides, 0x00000200)
    OBMEBasicFlagMACRO(IsUsingFXPersistsOverride, efixOverrides, 0x00000400)
    OBMEBasicFlagMACRO(IsUsingIconOverride, efixOverrides, 0x00000800)
    OBMEBasicFlagMACRO(IsUsingDoesntTeachOverride, efixOverrides, 0x00001000)
    OBMEBasicFlagMACRO(IsUsingUnknownFOverride, efixOverrides, 0x00004000)
    OBMEBasicFlagMACRO(IsUsingNoRecastOverride, efixOverrides, 0x00008000)
    OBMEBasicFlagMACRO(IsUsingParamFlagBOverride, efixOverrides, 0x00010000)
    OBMEBasicFlagMACRO(IsUsingMagnitudeIsRangeOverride, efixOverrides, 0x00020000)
    OBMEBasicFlagMACRO(IsUsingAtomicResistanceOverride, efixOverrides, 0x00040000)
    OBMEBasicFlagMACRO(IsUsingParamFlagCOverride, efixOverrides, 0x00080000)
    OBMEBasicFlagMACRO(IsUsingParamFlagDOverride, efixOverrides, 0x00100000)
    OBMEBasicFlagMACRO(IsUsingDisabledOverride, efixOverrides, 0x00400000)
    OBMEBasicFlagMACRO(IsUsingUnknownOOverride, efixOverrides, 0x00800000)
    OBMEBasicFlagMACRO(IsUsingNoHitEffectOverride, efixOverrides, 0x08000000)
    OBMEBasicFlagMACRO(IsUsingPersistOnDeathOverride, efixOverrides, 0x10000000)
    OBMEBasicFlagMACRO(IsUsingExplodesWithForceOverride, efixOverrides, 0x20000000)
    OBMEBasicFlagMACRO(IsUsingHiddenOverride, efixOverrides, 0x40000000)
    ##The related efixOverrides flag must be set for the following to be used
    OBMEBasicFlagMACRO(IsHostileOverride, efixFlags, 0x00000001)
    OBMEBasicFlagMACRO(IsRecoversOverride, efixFlags, 0x00000002)
    OBMEBasicFlagMACRO(IsParamFlagAOverride, efixFlags, 0x00000004)
    OBMEBasicFlagMACRO(IsBeneficialOverride, efixFlags, 0x00000008)
    OBMEBasicFlagMACRO(IsFXPersistsOverride, efixFlags, 0x00000400)
    OBMEBasicFlagMACRO(IsUnknownFOverride, efixFlags, 0x00004000)
    OBMEBasicFlagMACRO(IsNoRecastOverride, efixFlags, 0x00008000)
    OBMEBasicFlagMACRO(IsParamFlagBOverride, efixFlags, 0x00010000)
    OBMEBasicFlagMACRO(IsMagnitudeIsRangeOverride, efixFlags, 0x00020000)
    OBMEBasicFlagMACRO(IsAtomicResistanceOverride, efixFlags, 0x00040000)
    OBMEBasicFlagMACRO(IsParamFlagCOverride, efixFlags, 0x00080000)
    OBMEBasicFlagMACRO(IsParamFlagDOverride, efixFlags, 0x00100000)
    OBMEBasicFlagMACRO(IsDisabledOverride, efixFlags, 0x00400000)
    OBMEBasicFlagMACRO(IsUnknownOOverride, efixFlags, 0x00800000)
    OBMEBasicFlagMACRO(IsNoHitEffectOverride, efixFlags, 0x08000000)
    OBMEBasicFlagMACRO(IsPersistOnDeathOverride, efixFlags, 0x10000000)
    OBMEBasicFlagMACRO(IsExplodesWithForceOverride, efixFlags, 0x20000000)
    OBMEBasicFlagMACRO(IsHiddenOverride, efixFlags, 0x40000000)
    exportattrs = copyattrs = ['name', 'magnitude', 'area', 'duration', 'rangeType',
                 'actorValue', 'script', 'school', 'visual', 'IsHostile',
                 'full']
    copyattrsOBME = copyattrs + ['recordVersion', 'betaVersion',
                                 'minorVersion', 'majorVersion',
                                 'efitParamInfo', 'efixParamInfo',
                                 'reserved1', 'iconPath', 'efixOverrides',
                                 'efixFlags', 'baseCost', 'resistAV',
                                 'reserved2']

class Faction(ListComponent):
    FORMID_LISTMACRO(faction, self._FieldID, 1)
    UINT8_LISTMACRO(rank, self._FieldID, 2)
    UINT8_ARRAY_LISTMACRO(unused1, self._FieldID, 3, 3)
    exportattrs = copyattrs = ['faction', 'rank']

class Relation(ListComponent):
    FORMID_LISTMACRO(faction, self._FieldID, 1)
    SINT32_LISTMACRO(mod, self._FieldID, 2)
    exportattrs = copyattrs = ['faction', 'mod']

class PGRP(ListComponent):
    FLOAT32_LISTMACRO(x, self._FieldID, 1)
    FLOAT32_LISTMACRO(y, self._FieldID, 2)
    FLOAT32_LISTMACRO(z, self._FieldID, 3)
    UINT8_LISTMACRO(connections, self._FieldID, 4)
    UINT8_ARRAY_LISTMACRO(unused1, self._FieldID, 5, 3)
    exportattrs = copyattrs = ['x', 'y', 'z', 'connections']

#--Accessors
class ObFormIDRecord(object):
    _Type = 'FID_'
    def __init__(self, CollectionIndex, ModID, RecordID, ParentID=0, CopyFlags=0):
        self._CollectionID = CollectionIndex
        self._ModID = ModID
        self._RecordID = RecordID
        self._CopyFlags = CopyFlags
        #ParentID isn't kept for most records
        
    @property
    def ModName(self):
        return _CGetModName(self._CollectionID, self._ModID) or 'Missing'

    @property
    def NormModName(self):
        ModName = _CGetModName(self._CollectionID, self._ModID) or 'Missing'
        if ModName[-6:] == '.ghost':
            return ModName[:-6]
        return ModName

    @property
    def GName(self):
        return GPath(self.NormModName)

    def LoadRecord(self):
        _CLoadRecord(self._CollectionID, self._ModID, self._RecordID, 0)

    def UnloadRecord(self):
        _CUnloadRecord(self._CollectionID, self._ModID, self._RecordID, 0)

    def DeleteRecord(self):
        _CDeleteRecord(self._CollectionID, self._ModID, self._RecordID, 0, getattr(self, '_ParentID', 0))

    def GetNumReferences(self, FormIDToMatch):
        FormIDToMatch = MakeShortFid(self._CollectionID, FormIDToMatch)
        if FormIDToMatch is None: return 0
        return _CGetNumReferences(self._CollectionID, self._ModID, self._RecordID, FormIDToMatch)

    def UpdateReferences(self, FormIDToReplace, ReplacementFormID):
        FormIDToReplace = MakeShortFid(self._CollectionID, FormIDToReplace)
        ReplacementFormID = MakeShortFid(self._CollectionID, ReplacementFormID)
        if not (FormIDToReplace or ReplacementFormID): return 0
        return _CUpdateReferences(self._CollectionID, self._ModID, self._RecordID, FormIDToReplace, ReplacementFormID)

    def IsWinning(self, GetExtendedConflicts=False):
        """Returns true if the record is the last to load.
           If ignoreScanned is True, scanned records will never be considered winning.
           More efficient than running Conflicts() and checking the first value."""
        return _CIsRecordWinning(self._CollectionID, self._ModID, self._RecordID, 0, c_ulong(GetExtendedConflicts))

    def Conflicts(self, GetExtendedConflicts=False):
        numRecords = _CGetNumRecordConflicts(self._CollectionID, self._RecordID, 0, c_ulong(GetExtendedConflicts))
        if(numRecords > 1):
            cModIDs = (c_ulong * numRecords)()
            _CGetRecordConflicts(self._CollectionID, self._RecordID, 0, byref(cModIDs), c_ulong(GetExtendedConflicts))
            parent = getattr(self, '_ParentID', 0)
            return [self.__class__(self._CollectionID, cModIDs[x], self._RecordID, parent, self._CopyFlags) for x in range(0, numRecords)]
        return []

    def ConflictDetails(self, attrs=None, GetExtendedConflicts=False):
        conflicting = {}
        if attrs is None:
            attrs = self.copyattrs
        if not attrs:
            return conflicting
        recordMasters = set(ObModFile(self._CollectionID, self._ModID).TES4.masters)
        #sort oldest to newest rather than newest to oldest
        conflicts = self.Conflicts(ignoreScanned)
        #Less pythonic, but optimized for better speed.
        #Equivalent to commented out code.
        parentRecords = [parent for parent in conflicts if parent._NormName in recordMasters]
        parentRecords.reverse()
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

    def ConflictDetailsDeux(self, tags, tag_attrs, srcMods, GetExtendedConflicts=False):
        conflicting = {}
        recordMasters = set(ObModFile(self._CollectionID, self._ModID).TES4.masters)
        conflicts = self.Conflicts(ignoreScanned)
        if conflicts:
            newest = conflicts[0]
            baseValues = {}
            baseValues.update([(attr,reduce(getattr, attr.split('.'), newest)) for attrs in tag_attrs.values() for attr in attrs])
            #sort oldest to newest rather than newest to oldest
            conflicts.reverse()
            #Less pythonic, but optimized for better speed.
            #Equivalent to commented out code.
            conflicting.update([(attr,reduce(getattr, attr.split('.'), parentRecord)) for parentRecord in conflicts if parentRecord.GName in srcMods for bashKey in tags if bashKey in bosh.modInfos[parentRecord.GName].getBashTags() for attr in tag_attrs[bashKey] if baseValues[attr] != reduce(getattr, attr.split('.'), parentRecord)])
##            for parentRecord in conflicts:
##                if parentRecord.GName in srcMods:
##                    modInfo = bosh.modInfos[parentRecord.GName]
##                    bashTags = modInfo.getBashTags()
##                    attrs = []
##                    for bashKey in tags:
##                        if bashKey in bashTags:
##                            attrs += tag_attrs[bashKey]
##                    for attr in attrs:
##                        value = getattr_deep(parentRecord,attr)
##                        if baseValues[attr] != value:
##                            conflicting[attr] = value
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
        FID = _CCopyRecord(self._CollectionID, self._ModID, self._RecordID, 0, target._ModID, targetID, 0, 0, c_ulong(CopyFlags))
        #Clear SetAsOverride
        CopyFlags &= ~0x00000001
        if(FID): return self.__class__(self._CollectionID, target._ModID, FID, getattr(self, '_ParentID', 0), CopyFlags)
        return None

    def CopyAsNew(self, target, RecordID=0, CopyFlags=None):
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
        FID = _CCopyRecord(self._CollectionID, self._ModID, self._RecordID, 0, target._ModID, targetID, RecordID, 0, c_ulong(CopyFlags))
        if(FID): return self.__class__(self._CollectionID, target._ModID, FID, getattr(self, '_ParentID', 0), CopyFlags)
        return None

    @property
    def recType(self):
        _CGetFieldAttribute.restype = (c_char * 4)
        retValue = _CGetFieldAttribute(self._CollectionID, self._ModID, self._RecordID, 0, 0, 0, 0, 0, 0, 0, 0, 0)
        _CGetFieldAttribute.restype = c_ulong
        if(retValue): return retValue.value
        return None

    UINT32_FLAG_MACRO(flags1, 1)

    def get_fid(self):
        _CGetField.restype = POINTER(c_ulong)
        retValue = _CGetField(self._CollectionID, self._ModID, self._RecordID, 0, 2, 0, 0, 0, 0, 0, 0, 0)
        if(retValue): return MakeLongFid(self._CollectionID, retValue.contents.value)
        return None
    def set_fid(self, nValue):
        if nValue is None: nValue = 0
        else: nValue = MakeShortFid(self._CollectionID, nValue)
        _FormID = self._RecordID
        _EditorID = self.eid or 0
        if(_CSetRecordIDs(self._CollectionID, self._ModID, _FormID, _EditorID, nValue, _EditorID) == 1):
            self._RecordID = nValue
    fid = property(get_fid, set_fid)

    UINT32_FLAG_MACRO(flags2, 3)

    def get_eid(self):
        _CGetField.restype = c_char_p
        retValue = _CGetField(self._CollectionID, self._ModID, self._RecordID, 0, 4, 0, 0, 0, 0, 0, 0, 0)
        if(retValue): return ISTRING(retValue)
        return None
    def set_eid(self, nValue):
        if nValue is None or not len(nValue): nValue = 0
        else: nValue = str(nValue)
        _FormID = self._RecordID
        _EditorID = self.eid or 0
        _CSetRecordIDs(self._CollectionID, self._ModID, _FormID, _EditorID, _FormID, nValue)
    eid = property(get_eid, set_eid)
    
    BasicFlagMACRO(IsDeleted, flags1, 0x00000020)
    BasicFlagMACRO(IsBorderRegion, flags1, 0x00000040)
    BasicFlagMACRO(IsTurnOffFire, flags1, 0x00000080)
    BasicFlagMACRO(IsCastsShadows, flags1, 0x00000200)
    BasicFlagMACRO(IsPersistent, flags1, 0x00000400)
    BasicAliasMACRO(IsQuest, IsPersistent)
    BasicAliasMACRO(IsQuestOrPersistent, IsPersistent)
    BasicFlagMACRO(IsInitiallyDisabled, flags1, 0x00000800)
    BasicFlagMACRO(IsIgnored, flags1, 0x00001000)
    BasicFlagMACRO(IsVisibleWhenDistant, flags1, 0x00008000)
    BasicAliasMACRO(IsVWD, IsVisibleWhenDistant)
    BasicFlagMACRO(IsDangerousOrOffLimits, flags1, 0x00020000)
    BasicFlagMACRO(IsCompressed, flags1, 0x00040000)
    BasicFlagMACRO(IsCantWait, flags1, 0x00080000)
    baseattrs = ['flags1', 'flags2', 'eid']

class ObEditorIDRecord(object):
    _Type = 'EDID'
    def __init__(self, CollectionIndex, ModID, RecordID, ParentID=0, CopyFlags=0):
        self._CollectionID = CollectionIndex
        self._ModID = ModID
        self._RecordID = RecordID
        self._CopyFlags = CopyFlags
        
    @property
    def ModName(self):
        return _CGetModName(self._CollectionID, self._ModID) or 'Missing'

    @property
    def NormModName(self):
        ModName = _CGetModName(self._CollectionID, self._ModID) or 'Missing'
        if ModName[-6:] == '.ghost':
            return ModName[:-6]
        return ModName

    @property
    def GName(self):
        return GPath(self.NormModName)

    def UnloadRecord(self):
        _CUnloadRecord(self._CollectionID, self._ModID, 0, self._RecordID)

    def DeleteRecord(self):
        _CDeleteRecord(self._CollectionID, self._ModID, 0, self._RecordID, 0)

    def GetNumReferences(self, referenceFid):
        return 0

    def UpdateReferences(self, origFid, newFid):
        return 0

    def IsWinning(self, GetExtendedConflicts=False):
        """Returns true if the record is the last to load.
           If ignoreScanned is True, scanned records will never be considered winning.
           More efficient than running Conflicts() and checking the first value."""
        return _CIsRecordWinning(self._CollectionID, self._ModID, 0, self._RecordID, c_ulong(GetExtendedConflicts))

    def Conflicts(self, GetExtendedConflicts=False):
        numRecords = _CGetNumRecordConflicts(self._CollectionID, 0, self._RecordID, c_ulong(GetExtendedConflicts))
        if(numRecords > 1):
            cModIDs = (c_ulong * numRecords)()
            _CGetRecordConflicts(self._CollectionID, 0, self._RecordID, byref(cModIDs), c_ulong(GetExtendedConflicts))
            parent = getattr(self, '_ParentID', 0)
            return [self.__class__(self._CollectionID, cModIDs[x], self._RecordID, parent, self._CopyFlags) for x in range(0, numRecords)]
        return []

    def ConflictDetails(self, attrs=None, GetExtendedConflicts=False):
        conflicting = {}
        if attrs is None:
            attrs = self.copyattrs
        if not attrs:
            return conflicting
        recordMasters = set(ObModFile(self._CollectionID, self._ModID).TES4.masters)
        #sort oldest to newest rather than newest to oldest
        conflicts = self.Conflicts(ignoreScanned)
        #Less pythonic, but optimized for better speed.
        #Equivalent to commented out code.
        parentRecords = [parent for parent in conflicts if parent._ModID in recordMasters].reverse()
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

    def ConflictDetailsDeux(self, tags, tag_attrs, srcMods, GetExtendedConflicts=False):
        conflicting = {}
        recordMasters = set(ObModFile(self._CollectionID, self._ModID).TES4.masters)
        conflicts = self.Conflicts(ignoreScanned)
        if conflicts:
            newest = conflicts[0]
            baseValues = {}
            baseValues.update([(attr,reduce(getattr, attr.split('.'), newest)) for attrs in tag_attrs.values() for attr in attrs])
            #sort oldest to newest rather than newest to oldest
            conflicts.reverse()
            #Less pythonic, but optimized for better speed.
            #Equivalent to commented out code.
            conflicting.update([(attr,reduce(getattr, attr.split('.'), parentRecord)) for parentRecord in conflicts if parentRecord.GName in srcMods for bashKey in tags if bashKey in bosh.modInfos[parentRecord.GName].getBashTags() for attr in tag_attrs[bashKey] if baseValues[attr] != reduce(getattr, attr.split('.'), parentRecord)])
##            for parentRecord in conflicts:
##                if parentRecord.GName in srcMods:
##                    modInfo = bosh.modInfos[parentRecord.GName]
##                    bashTags = modInfo.getBashTags()
##                    attrs = []
##                    for bashKey in tags:
##                        if bashKey in bashTags:
##                            attrs += tag_attrs[bashKey]
##                    for attr in attrs:
##                        value = getattr_deep(parentRecord,attr)
##                        if baseValues[attr] != value:
##                            conflicting[attr] = value
        return conflicting

    def CopyAsNew(self, target, RecordID, CopyFlags=None):
        if CopyFlags is None: CopyFlags = self._CopyFlags
        targetID = 0
        if hasattr(self, '_ParentID'):
            if isinstance(target, ObModFile): targetID = self._ParentID
            else: targetID = target._RecordID
        ##Record Creation Flags
        ##SetAsOverride       = 0x00000001,
        ##SetAsWorldCell      = 0x00000002,
        ##CopyWorldCellStatus = 0x00000004
        #Clear SetAsOverride
        CopyFlags &= ~0x00000001
        _EditorID = self._RecordID
        recID = _CCopyRecord(self._CollectionID, self._ModID, 0, _EditorID, target._ModID, targetID, 0, RecordID, c_ulong(CopyFlags))
        if(recID):
            return self.__class__(self._CollectionID, target._ModID, RecordID, getattr(self, '_ParentID', 0), CopyFlags)
        return None
    
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
        recID = _CCopyRecord(self._CollectionID, self._ModID, 0, self._RecordID, target._ModID, targetID, 0, 0, c_ulong(CopyFlags))
        #Clear SetAsOverride
        CopyFlags &= ~0x00000001
        if(recID): return self.__class__(self._CollectionID, target._ModID, self._RecordID, getattr(self, '_ParentID', 0), CopyFlags)
        return None

    @property
    def recType(self):
        return self._Type

    UINT32_FLAG_EDIDMACRO(flags1, 1)

    def get_fid(self):
        _CGetField.restype = POINTER(c_ulong)
        retValue = _CGetField(self._CollectionID, self._ModID, 0, self._RecordID, 2, 0, 0, 0, 0, 0, 0, 0)
        if(retValue): return MakeLongFid(self._CollectionID, retValue.contents.value)
        return None
    def set_fid(self, nValue):
        if nValue is None: nValue = 0
        else: nValue = MakeShortFid(self._CollectionID, nValue)
        _CGetField.restype = POINTER(c_ulong)
        _FormID = _CGetField(self._CollectionID, self._ModID, 0, self._RecordID, 2, 0, 0, 0, 0, 0, 0, 0)
        if(_FormID): _FormID = _FormID.contents.value
        else: raise AttributeError
        _EditorID = self._RecordID
        _CSetRecordIDs(self._CollectionID, self._ModID, _FormID, _EditorID, nValue, _EditorID)
    fid = property(get_fid, set_fid)

    UINT32_FLAG_EDIDMACRO(flags2, 3)

    def get_eid(self):
        _CGetField.restype = c_char_p
        retValue = _CGetField(self._CollectionID, self._ModID, 0, self._RecordID, 4, 0, 0, 0, 0, 0, 0, 0)
        if(retValue): return retValue
        return None
    def set_eid(self, nValue):
        if nValue is None or not len(nValue): nValue = 0
        else: nValue = str(nValue)
        _CGetField.restype = POINTER(c_ulong)
        _FormID = _CGetField(self._CollectionID, self._ModID, 0, self._RecordID, 2, 0, 0, 0, 0, 0, 0, 0)
        if(_FormID): _FormID = _FormID.contents.value
        else: raise AttributeError
        _EditorID = self._RecordID
        if(_CSetRecordIDs(self._CollectionID, self._ModID, _FormID, _EditorID, _FormID, nValue) == 1):
            self._RecordID = nValue
    eid = property(get_eid, set_eid)
    
    BasicFlagMACRO(IsDeleted, flags1, 0x00000020)
    BasicFlagMACRO(IsBorderRegion, flags1, 0x00000040)
    BasicFlagMACRO(IsTurnOffFire, flags1, 0x00000080)
    BasicFlagMACRO(IsCastsShadows, flags1, 0x00000200)
    BasicFlagMACRO(IsPersistent, flags1, 0x00000400)
    BasicAliasMACRO(IsQuest, IsPersistent)
    BasicAliasMACRO(IsQuestOrPersistent, IsPersistent)
    BasicFlagMACRO(IsInitiallyDisabled, flags1, 0x00000800)
    BasicFlagMACRO(IsIgnored, flags1, 0x00001000)
    BasicFlagMACRO(IsVisibleWhenDistant, flags1, 0x00008000)
    BasicAliasMACRO(IsVWD, IsVisibleWhenDistant)
    BasicFlagMACRO(IsDangerousOrOffLimits, flags1, 0x00020000)
    BasicFlagMACRO(IsCompressed, flags1, 0x00040000)
    BasicFlagMACRO(IsCantWait, flags1, 0x00080000)
    baseattrs = ['flags1', 'fid', 'flags2']

class ObTES4Record(object):
    _Type = 'TES4'
    def __init__(self, CollectionIndex, ModID, RecordID, ParentID=0, CopyFlags=0):
        self._CollectionID = CollectionIndex
        self._ModID = ModID
        self._RecordID = 0

    def UnloadRecord(self):
        pass

    @property
    def recType(self):
        return self._Type

    UINT32_FLAG_MACRO(flags1, 1)
    UINT32_FLAG_MACRO(flags2, 3)
    FLOAT32_MACRO(version, 5)
    UINT32_MACRO(numRecords, 6)
    UINT32_MACRO(nextObject, 7)
    UINT8_ARRAY_MACRO(ofst_p, 8)
    UINT8_ARRAY_MACRO(dele_p, 9)
    STRING_MACRO(author, 10)
    STRING_MACRO(description, 11)
    ISTRING_ARRAY_MACRO(masters, 12)
    JUNK_MACRO(DATA, 13)
    BasicFlagMACRO(IsESM, flags1, 0x00000001)
    exportattrs = copyattrs = ['flags1', 'flags2', 'version', 'numRecords', 'nextObject',
                 'author', 'description', 'masters']

class ObGMSTRecord(ObEditorIDRecord):
    _Type = 'GMST'
    def get_value(self):
        rFormat = _CGetFieldAttribute(self._CollectionID, self._ModID, 0, self._RecordID, 5, 0, 0, 0, 0, 0, 0, 0)
        if(rFormat == API_FIELDS.UNKNOWN):
            return None
        elif(rFormat == API_FIELDS.SINT32):
            _CGetField.restype = POINTER(c_long)
            retValue = _CGetField(self._CollectionID, self._ModID, 0, self._RecordID, 5, 0, 0, 0, 0, 0, 0, 0)
            if(retValue): return retValue.contents.value
        elif(rFormat == API_FIELDS.FLOAT32):
            _CGetField.restype = POINTER(c_float)
            retValue = _CGetField(self._CollectionID, self._ModID, 0, self._RecordID, 5, 0, 0, 0, 0, 0, 0, 0)
            if(retValue): return round(retValue.contents.value,6)
        elif(rFormat == API_FIELDS.STRING):
            _CGetField.restype = c_char_p
            return _CGetField(self._CollectionID, self._ModID, 0, self._RecordID, 5, 0, 0, 0, 0, 0, 0, 0)
        return None
    def set_value(self, nValue):
        if nValue is None: _CDeleteField(self._CollectionID, self._ModID, 0, self._RecordID, 5, 0, 0, 0, 0, 0, 0)
        else:
            rFormat = _CGetFieldAttribute(self._CollectionID, self._ModID, 0, self._RecordID, 5, 0, 0, 0, 0, 0, 0, 0)
            if(rFormat == API_FIELDS.SINT32 and type(nValue) is int):
                _CSetField(self._CollectionID, self._ModID, 0, self._RecordID, 5, 0, 0, 0, 0, 0, 0, byref(c_long(nValue)), 0)
            elif(rFormat == API_FIELDS.FLOAT32 == 10 and type(nValue) is float):
                _CSetField(self._CollectionID, self._ModID, 0, self._RecordID, 5, 0, 0, 0, 0, 0, 0, byref(c_float(round(nValue,6))), 0)
            elif(rFormat == API_FIELDS.STRING and type(nValue) is str):
                _CSetField(self._CollectionID, self._ModID, 0, self._RecordID, 5, 0, 0, 0, 0, 0, 0, nValue, 0)
    value = property(get_value, set_value)
    exportattrs = copyattrs = ObEditorIDRecord.baseattrs + ['value']

class ObACHRRecord(ObFormIDRecord):
    def __init__(self, CollectionIndex, ModID, RecordID, ParentID=0, CopyFlags=0):
        ObFormIDRecord.__init__(self, CollectionIndex, ModID, RecordID, ParentID, CopyFlags)
        self._ParentID = ParentID

    _Type = 'ACHR'
    FORMID_MACRO(base, 5)
    FORMID_MACRO(unknownXPCIFormID, 6)
    ISTRING_MACRO(unknownXPCIString, 7)
    FLOAT32_MACRO(lod1, 8)
    FLOAT32_MACRO(lod2, 9)
    FLOAT32_MACRO(lod3, 10)
    FORMID_MACRO(parent, 11)
    UINT8_FLAG_MACRO(parentFlags, 12)
    UINT8_ARRAY_MACRO(unused1, 13, 3)
    FORMID_MACRO(merchantContainer, 14)
    FORMID_MACRO(horse, 15)
    UINT8_ARRAY_MACRO(xrgd_p, 16)
    FLOAT32_MACRO(scale, 17)
    FLOAT32_MACRO(posX, 18)
    FLOAT32_MACRO(posY, 19)
    FLOAT32_MACRO(posZ, 20)
    RADIAN_MACRO(rotX, 21)
    RADIAN_MACRO(rotY, 22)
    RADIAN_MACRO(rotZ, 23)
    BasicFlagMACRO(IsOppositeParent, parentFlags, 0x00000001)
    copyattrs = ObFormIDRecord.baseattrs + ['base', 'unknownXPCIFormID', 'unknownXPCIString',
                                        'lod1', 'lod2', 'lod3', 'parent', 'parentFlags',
                                        'merchantContainer', 'horse', 'xrgd_p', 'scale',
                                        'posX', 'posY', 'posZ', 'rotX', 'rotY', 'rotZ']
    exportattrs = ObFormIDRecord.baseattrs + ['base', 'unknownXPCIFormID', 'unknownXPCIString',
                                        'lod1', 'lod2', 'lod3', 'parent', 'parentFlags',
                                        'merchantContainer', 'horse', 'scale',
                                        'posX', 'posY', 'posZ', 'rotX', 'rotY', 'rotZ'] #'xrgd_p', 

class ObACRERecord(ObFormIDRecord):
    def __init__(self, CollectionIndex, ModID, RecordID, ParentID=0, CopyFlags=0):
        ObFormIDRecord.__init__(self, CollectionIndex, ModID, RecordID, ParentID, CopyFlags=0)
        self._ParentID = ParentID

    _Type = 'ACRE'
    FORMID_MACRO(base, 5)
    FORMID_MACRO(owner, 6)
    SINT32_MACRO(rank, 7)
    FORMID_MACRO(globalVariable, 8)
    FLOAT32_MACRO(lod1, 9)
    FLOAT32_MACRO(lod2, 10)
    FLOAT32_MACRO(lod3, 11)
    FORMID_MACRO(parent, 12)
    UINT8_FLAG_MACRO(parentFlags, 13)
    UINT8_ARRAY_MACRO(unused1, 14, 3)
    UINT8_ARRAY_MACRO(xrgd_p, 15)
    FLOAT32_MACRO(scale, 16)
    FLOAT32_MACRO(posX, 17)
    FLOAT32_MACRO(posY, 18)
    FLOAT32_MACRO(posZ, 19)
    RADIAN_MACRO(rotX, 20)
    RADIAN_MACRO(rotY, 21)
    RADIAN_MACRO(rotZ, 22)
    BasicFlagMACRO(IsOppositeParent, parentFlags, 0x00000001)
    copyattrs = ObFormIDRecord.baseattrs + ['base', 'owner', 'rank', 'globalVariable',
                                        'lod1', 'lod2', 'lod3', 'parent', 'parentFlags',
                                        'xrgd_p', 'scale', 'posX', 'posY', 'posZ', 'rotX',
                                        'rotY', 'rotZ']
    exportattrs = ObFormIDRecord.baseattrs + ['base', 'owner', 'rank', 'globalVariable',
                                        'lod1', 'lod2', 'lod3', 'parent', 'parentFlags',
                                        'scale', 'posX', 'posY', 'posZ', 'rotX',
                                        'rotY', 'rotZ'] #'xrgd_p', 

class ObREFRRecord(ObFormIDRecord):
    def __init__(self, CollectionIndex, ModID, RecordID, ParentID=0, CopyFlags=0):
        ObFormIDRecord.__init__(self, CollectionIndex, ModID, RecordID, ParentID, CopyFlags)
        self._ParentID = ParentID

    _Type = 'REFR'
    FORMID_MACRO(base, 5)
    FORMID_MACRO(destination, 6)
    FLOAT32_MACRO(destinationPosX, 7)
    FLOAT32_MACRO(destinationPosY, 8)
    FLOAT32_MACRO(destinationPosZ, 9)
    RADIAN_MACRO(destinationRotX, 10)
    RADIAN_MACRO(destinationRotY, 11)
    RADIAN_MACRO(destinationRotZ, 12)
    UINT8_MACRO(lockLevel, 13)
    UINT8_ARRAY_MACRO(unused1, 14, 3)
    FORMID_MACRO(lockKey, 15)
    UINT8_ARRAY_MACRO(unused2, 16, 4)
    UINT8_FLAG_MACRO(lockFlags, 17)
    UINT8_ARRAY_MACRO(unused3, 18, 3)
    FORMID_MACRO(owner, 19)
    SINT32_MACRO(rank, 20)
    FORMID_MACRO(globalVariable, 21)
    FORMID_MACRO(parent, 22)
    UINT8_FLAG_MACRO(parentFlags, 23)
    UINT8_ARRAY_MACRO(unused4, 24, 3)
    FORMID_MACRO(target, 25)
    XSED_MACRO(seed, 26)
    FLOAT32_MACRO(lod1, 27)
    FLOAT32_MACRO(lod2, 28)
    FLOAT32_MACRO(lod3, 29)
    FLOAT32_MACRO(charge, 30)
    SINT32_MACRO(health, 31)
    FORMID_MACRO(unknownXPCIFormID, 32)
    ISTRING_MACRO(unknownXPCIString, 33)
    SINT32_MACRO(levelMod, 34)
    FORMID_MACRO(unknownXRTMFormID, 35)
    UINT32_FLAG_MACRO(actionFlags, 36)
    SINT32_MACRO(count, 37)
    UINT8_FLAG_MACRO(markerFlags, 38)
    STRING_MACRO(markerName, 39)
    UINT8_TYPE_MACRO(markerType, 40)
    UINT8_ARRAY_MACRO(markerUnused, 41, 1)
    FLOAT32_MACRO(scale, 42)
    UINT8_TYPE_MACRO(soulType, 43)
    FLOAT32_MACRO(posX, 44)
    FLOAT32_MACRO(posY, 45)
    FLOAT32_MACRO(posZ, 46)
    RADIAN_MACRO(rotX, 47)
    RADIAN_MACRO(rotY, 48)
    RADIAN_MACRO(rotZ, 49)
    BasicFlagMACRO(IsLeveledLock, lockFlags, 0x00000004)
    BasicFlagMACRO(IsOppositeParent, parentFlags, 0x00000001)
    BasicFlagMACRO(IsUseDefault, actionFlags, 0x00000001)
    BasicFlagMACRO(IsActivate, actionFlags, 0x00000002)
    BasicFlagMACRO(IsOpen, actionFlags, 0x00000004)
    BasicFlagMACRO(IsOpenByDefault, actionFlags, 0x00000008)
    BasicFlagMACRO(IsVisible, markerFlags, 0x00000001)
    BasicFlagMACRO(IsCanTravelTo, markerFlags, 0x00000002)
    BasicTypeMACRO(IsMarkerNone, markerType, 0, IsCamp)
    BasicTypeMACRO(IsCamp, markerType, 1, IsMarkerNone)
    BasicTypeMACRO(IsCave, markerType, 2, IsMarkerNone)
    BasicTypeMACRO(IsCity, markerType, 3, IsMarkerNone)
    BasicTypeMACRO(IsElvenRuin, markerType, 4, IsMarkerNone)
    BasicTypeMACRO(IsFortRuin, markerType, 5, IsMarkerNone)
    BasicTypeMACRO(IsMine, markerType, 6, IsMarkerNone)
    BasicTypeMACRO(IsLandmark, markerType, 7, IsMarkerNone)
    BasicTypeMACRO(IsTavern, markerType, 8, IsMarkerNone)
    BasicTypeMACRO(IsSettlement, markerType, 9, IsMarkerNone)
    BasicTypeMACRO(IsDaedricShrine, markerType, 10, IsMarkerNone)
    BasicTypeMACRO(IsOblivionGate, markerType, 11, IsMarkerNone)
    BasicTypeMACRO(IsUnknownDoorIcon, markerType, 12, IsMarkerNone)
    BasicTypeMACRO(IsNoSoul, soulType, 0, IsPettySoul)
    BasicTypeMACRO(IsPettySoul, soulType, 1, IsNoSoul)
    BasicTypeMACRO(IsLesserSoul, soulType, 2, IsNoSoul)
    BasicTypeMACRO(IsCommonSoul, soulType, 3, IsNoSoul)
    BasicTypeMACRO(IsGreaterSoul, soulType, 4, IsNoSoul)
    BasicTypeMACRO(IsGrandSoul, soulType, 5, IsNoSoul)
    exportattrs = copyattrs = ObFormIDRecord.baseattrs + ['base', 'destination',
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

class ObINFORecord(ObFormIDRecord):
    def __init__(self, CollectionIndex, ModID, RecordID, ParentID=0, CopyFlags=0):
        ObFormIDRecord.__init__(self, CollectionIndex, ModID, RecordID, ParentID, CopyFlags)
        self._ParentID = ParentID

    _Type = 'INFO'
    class Response(ListComponent):
        UINT32_LISTMACRO(emotionType, 11, 1)
        SINT32_LISTMACRO(emotionValue, 11, 2)
        UINT8_ARRAY_LISTMACRO(unused1, 11, 3)
        UINT8_LISTMACRO(responseNum, 11, 4)
        UINT8_ARRAY_LISTMACRO(unused2, 11, 5)
        STRING_LISTMACRO(responseText, 11, 6)
        ISTRING_LISTMACRO(actorNotes, 11, 7)
        BasicTypeMACRO(IsNeutral, emotionType, 0, IsAnger)
        BasicTypeMACRO(IsAnger, emotionType, 1, IsNeutral)
        BasicTypeMACRO(IsDisgust, emotionType, 2, IsNeutral)
        BasicTypeMACRO(IsFear, emotionType, 3, IsNeutral)
        BasicTypeMACRO(IsSad, emotionType, 4, IsNeutral)
        BasicTypeMACRO(IsHappy, emotionType, 5, IsNeutral)
        BasicTypeMACRO(IsSurprise, emotionType, 6, IsNeutral)
        exportattrs = copyattrs = ['emotionType', 'emotionValue', 'responseNum',
                                   'responseText', 'actorNotes']

    UINT16_TYPE_MACRO(dialType, 5)
    UINT8_FLAG_MACRO(flags, 6)
    FORMID_MACRO(quest, 7)
    FORMID_MACRO(topic, 8)
    FORMID_MACRO(prevInfo, 9)
    FORMID_ARRAY_MACRO(addTopics, 10)

    LIST_MACRO(responses, 11, self.Response)
    LIST_MACRO(conditions, 12, Condition)
    FORMID_ARRAY_MACRO(choices, 13)
    FORMID_ARRAY_MACRO(linksFrom, 14)
    UINT8_ARRAY_MACRO(unused1, 15, 4)
    UINT32_MACRO(numRefs, 16)
    UINT32_MACRO(compiledSize, 17)
    UINT32_MACRO(lastIndex, 18)
    UINT32_MACRO(scriptType, 19)
    UINT8_ARRAY_MACRO(compiled_p, 20)
    ISTRING_MACRO(scriptText, 21)
    FORMID_OR_UINT32_ARRAY_MACRO(references, 22)
    BasicTypeMACRO(IsTopic, dialType, 0, IsConversation)
    BasicTypeMACRO(IsConversation, dialType, 1, IsTopic)
    BasicTypeMACRO(IsCombat, dialType, 2, IsTopic)
    BasicTypeMACRO(IsPersuasion, dialType, 3, IsTopic)
    BasicTypeMACRO(IsDetection, dialType, 4, IsTopic)
    BasicTypeMACRO(IsService, dialType, 5, IsTopic)
    BasicTypeMACRO(IsMisc, dialType, 6, IsTopic)
    BasicFlagMACRO(IsGoodbye, flags, 0x00000001)
    BasicFlagMACRO(IsRandom, flags, 0x00000002)
    BasicFlagMACRO(IsSayOnce, flags, 0x00000004)
    BasicFlagMACRO(IsRunImmediately, flags, 0x00000008)
    BasicFlagMACRO(IsInfoRefusal, flags, 0x00000010)
    BasicFlagMACRO(IsRandomEnd, flags, 0x00000020)
    BasicFlagMACRO(IsRunForRumors, flags, 0x00000040)
    copyattrs = ObFormIDRecord.baseattrs + ['dialType', 'flags', 'quest', 'topic',
                                        'prevInfo', 'addTopics', 'responses_list',
                                        'conditions_list', 'choices', 'linksFrom',
                                        'numRefs', 'compiledSize', 'lastIndex',
                                        'scriptType', 'compiled_p', 'scriptText',
                                        'references']
    exportattrs = ObFormIDRecord.baseattrs + ['dialType', 'flags', 'quest', 'topic',
                                        'prevInfo', 'addTopics', 'responses_list',
                                        'conditions_list', 'choices', 'linksFrom',
                                        'numRefs', 'compiledSize', 'lastIndex',
                                        'scriptType', 'scriptText',
                                        'references'] #'compiled_p', 

class ObLANDRecord(ObFormIDRecord):
    def __init__(self, CollectionIndex, ModID, RecordID, ParentID=0, CopyFlags=0):
        ObFormIDRecord.__init__(self, CollectionIndex, ModID, RecordID, ParentID, CopyFlags)
        self._ParentID = ParentID

    _Type = 'LAND'
    class Normal(ListX2Component):
        UINT8_LISTX2MACRO(x, 6, 0, 1)
        UINT8_LISTX2MACRO(y, 6, 0, 2)
        UINT8_LISTX2MACRO(z, 6, 0, 3)
        exportattrs = copyattrs = ['x', 'y', 'z']

    class Height(ListX2Component):
        SINT8_LISTX2MACRO(height, 8, 0, 1)
        exportattrs = copyattrs = ['height']

    class Color(ListX2Component):
        UINT8_LISTX2MACRO(red, 11, 0, 1)
        UINT8_LISTX2MACRO(green, 11, 0, 2)
        UINT8_LISTX2MACRO(blue, 11, 0, 3)
        exportattrs = copyattrs = ['red', 'green', 'blue']

    class BaseTexture(ListComponent):
        FORMID_LISTMACRO(texture, self._FieldID, 1)
        SINT8_LISTMACRO(quadrant, self._FieldID, 2)
        UINT8_ARRAY_LISTMACRO(unused1, self._FieldID, 3, 1)
        SINT16_LISTMACRO(layer, self._FieldID, 4)
        exportattrs = copyattrs = ['texture', 'quadrant', 'layer']

    class AlphaLayer(ListComponent):
        class Opacity(ListX2Component):
            UINT16_LISTX2MACRO(position, 12, 5, 1)
            UINT8_ARRAY_LISTX2MACRO(unused1, 12, 5, 2, 2)
            FLOAT32_LISTX2MACRO(opacity, 12, 5, 3)
            exportattrs = copyattrs = ['position', 'opacity']
        FORMID_LISTMACRO(texture, 12, 1)
        SINT8_LISTMACRO(quadrant, 12, 2)
        UINT8_ARRAY_LISTMACRO(unused1, 12, 3, 1)
        SINT16_LISTMACRO(layer, 12, 4)

        LIST_LISTMACRO(opacities, 12, 5, self.Opacity)
        exportattrs = copyattrs = ['texture', 'quadrant', 'layer', 'opacities_list']

    class VertexTexture(ListComponent):
        FORMID_LISTMACRO(texture, 13, 1)
        exportattrs = copyattrs = ['texture']

    class Position(ListX2Component):
        FLOAT32_LISTX2MACRO(height, 14, 0, 1)
        UINT8_LISTX2MACRO(normalX, 14, 0, 2)
        UINT8_LISTX2MACRO(normalY, 14, 0, 3)
        UINT8_LISTX2MACRO(normalZ, 14, 0, 4)
        UINT8_LISTX2MACRO(red, 14, 0, 5)
        UINT8_LISTX2MACRO(green, 14, 0, 6)
        UINT8_LISTX2MACRO(blue, 14, 0, 7)
        FORMID_LISTX2MACRO(baseTexture, 14, 0, 8)
        FORMID_LISTX2MACRO(alphaLayer1Texture, 14, 0, 9)
        FLOAT32_LISTX2MACRO(alphaLayer1Opacity, 14, 0, 10)
        FORMID_LISTX2MACRO(alphaLayer2Texture, 14, 0, 11)
        FLOAT32_LISTX2MACRO(alphaLayer2Opacity, 14, 0, 12)
        FORMID_LISTX2MACRO(alphaLayer3Texture, 14, 0, 13)
        FLOAT32_LISTX2MACRO(alphaLayer3Opacity, 14, 0, 14)
        FORMID_LISTX2MACRO(alphaLayer4Texture, 14, 0, 15)
        FLOAT32_LISTX2MACRO(alphaLayer4Opacity, 14, 0, 16)
        FORMID_LISTX2MACRO(alphaLayer5Texture, 14, 0, 17)
        FLOAT32_LISTX2MACRO(alphaLayer5Opacity, 14, 0, 18)
        FORMID_LISTX2MACRO(alphaLayer6Texture, 14, 0, 19)
        FLOAT32_LISTX2MACRO(alphaLayer6Opacity, 14, 0, 20)
        FORMID_LISTX2MACRO(alphaLayer7Texture, 14, 0, 21)
        FLOAT32_LISTX2MACRO(alphaLayer7Opacity, 14, 0, 22)
        FORMID_LISTX2MACRO(alphaLayer8Texture, 14, 0, 23)
        FLOAT32_LISTX2MACRO(alphaLayer8Opacity, 14, 0, 24)
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

    UINT8_ARRAY_MACRO(data, 5)

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

    FLOAT32_MACRO(heightOffset, 7)

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

    UINT8_ARRAY_MACRO(unused1, 9, 3)

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

    LIST_MACRO(baseTextures, 11, self.BaseTexture)
    LIST_MACRO(alphaLayers, 12, self.AlphaLayer)
    LIST_MACRO(vertexTextures, 13, self.VertexTexture)
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
    copyattrs = ObFormIDRecord.baseattrs + ['data_p', 'normals_list', 'heights_list', 'heightOffset',
                                        'colors_list', 'baseTextures_list', 'alphaLayers_list',
                                        'vertexTextures_list']
    exportattrs = ObFormIDRecord.baseattrs + ['normals_list', 'heights_list', 'heightOffset',
                                        'colors_list', 'baseTextures_list', 'alphaLayers_list',
                                        'vertexTextures_list'] #'data_p', 

class ObPGRDRecord(ObFormIDRecord):
    def __init__(self, CollectionIndex, ModID, RecordID, ParentID=0, CopyFlags=0):
        ObFormIDRecord.__init__(self, CollectionIndex, ModID, RecordID, ParentID, CopyFlags)
        self._ParentID = ParentID

    _Type = 'PGRD'
    class PGRI(ListComponent):
        UINT16_LISTMACRO(point, 9, 1)
        UINT8_ARRAY_LISTMACRO(unused1, 9, 2, 2)
        FLOAT32_LISTMACRO(x, 9, 3)
        FLOAT32_LISTMACRO(y, 9, 4)
        FLOAT32_LISTMACRO(z, 9, 5)
        exportattrs = copyattrs = ['point', 'x', 'y', 'z']

    class PGRL(ListComponent):
        FORMID_LISTMACRO(reference, 10, 1)
        UINT32_ARRAY_LISTMACRO(points, 10, 2)
        exportattrs = copyattrs = ['reference', 'points']

    UINT16_MACRO(count, 5)

    LIST_MACRO(pgrp, 6, PGRP)
    UINT8_ARRAY_MACRO(pgag_p, 7)
    UINT8_ARRAY_MACRO(pgrr_p, 8)

    LIST_MACRO(pgri, 9, self.PGRI)
    LIST_MACRO(pgrl, 10, self.PGRL)
    copyattrs = ObFormIDRecord.baseattrs + ['count', 'pgrp_list', 'pgag_p', 'pgrr_p',
                                        'pgri_list', 'pgrl_list']
    exportattrs = ObFormIDRecord.baseattrs + ['count', 'pgrp_list',
                                        'pgri_list', 'pgrl_list'] # 'pgag_p', 'pgrr_p',

class ObROADRecord(ObFormIDRecord):
    def __init__(self, CollectionIndex, ModID, RecordID, ParentID=0, CopyFlags=0):
        ObFormIDRecord.__init__(self, CollectionIndex, ModID, RecordID, ParentID, CopyFlags)
        self._ParentID = ParentID

    _Type = 'ROAD'
    class PGRR(ListComponent):
        FLOAT32_LISTMACRO(x, 6, 1)
        FLOAT32_LISTMACRO(y, 6, 2)
        FLOAT32_LISTMACRO(z, 6, 3)
        exportattrs = copyattrs = ['x', 'y', 'z']

    LIST_MACRO(pgrp, 5, PGRP)
    LIST_MACRO(pgrr, 6, self.PGRR)
    exportattrs = copyattrs = ObFormIDRecord.baseattrs + ['pgrp_list', 'pgrr_list']

class ObACTIRecord(ObFormIDRecord):
    _Type = 'ACTI'
    STRING_MACRO(full, 5)
    ISTRING_MACRO(modPath, 6)
    FLOAT32_MACRO(modb, 7)
    UINT8_ARRAY_MACRO(modt_p, 8)
    FORMID_MACRO(script, 9)
    FORMID_MACRO(sound, 10)
    copyattrs = ObFormIDRecord.baseattrs + ['full', 'modPath', 'modb', 'modt_p', 'script',
                                        'sound']
    exportattrs = ObFormIDRecord.baseattrs + ['full', 'modPath', 'modb', 'script', 'sound'] #'modt_p', 

class ObALCHRecord(ObFormIDRecord):
    _Type = 'ALCH'
    STRING_MACRO(full, 5)
    ISTRING_MACRO(modPath, 6)
    FLOAT32_MACRO(modb, 7)
    UINT8_ARRAY_MACRO(modt_p, 8)
    ISTRING_MACRO(iconPath, 9)
    FORMID_MACRO(script, 10)
    FLOAT32_MACRO(weight, 11)
    SINT32_MACRO(value, 12)
    UINT8_FLAG_MACRO(flags, 13)
    UINT8_ARRAY_MACRO(unused1, 14, 3)

    LIST_MACRO(effects, 15, Effect)
    BasicFlagMACRO(IsNoAutoCalc, flags, 0x00000001)
    BasicFlagMACRO(IsFood, flags, 0x00000002)
    ##OBME Fields. Setting any of the below fields will make the mod require JRoush's OBME plugin for OBSE
    ##To see if OBME is in use, check the recordVersion field for a non-None value
    OBMEUINT8_MACRO(recordVersion, 16)
    OBMEUINT8_MACRO(betaVersion, 17)
    OBMEUINT8_MACRO(minorVersion, 18)
    OBMEUINT8_MACRO(majorVersion, 19)
    OBMEUINT8_ARRAY_MACRO(reserved, 20, 0x1C)
    OBMEUINT8_ARRAY_MACRO(datx_p, 21, 0x20)
    copyattrs = ObFormIDRecord.baseattrs + ['full', 'modPath', 'modb', 'modt_p',
                                        'iconPath', 'script', 'weight',
                                        'value', 'flags', 'effects_list']
    exportattrs = ObFormIDRecord.baseattrs + ['full', 'modPath', 'modb',
                                        'iconPath', 'script', 'weight',
                                        'value', 'flags', 'effects_list'] # 'modt_p',
    copyattrsOBME = copyattrs + ['recordVersion', 'betaVersion',
                                 'minorVersion', 'majorVersion',
                                 'reserved'] #, 'datx_p'

class ObAMMORecord(ObFormIDRecord):
    _Type = 'AMMO'
    STRING_MACRO(full, 5)
    ISTRING_MACRO(modPath, 6)
    FLOAT32_MACRO(modb, 7)
    UINT8_ARRAY_MACRO(modt_p, 8)
    ISTRING_MACRO(iconPath, 9)
    FORMID_MACRO(enchantment, 10)
    UINT16_MACRO(enchantPoints, 11)
    FLOAT32_MACRO(speed, 12)
    UINT8_FLAG_MACRO(flags, 13)
    UINT8_ARRAY_MACRO(unused1, 14, 3)
    UINT32_MACRO(value, 15)
    FLOAT32_MACRO(weight, 16)
    UINT16_MACRO(damage, 17)
    BasicFlagMACRO(IsNotNormal, flags, 0x00000001)
    BasicAliasMACRO(IsNotNormalWeapon, IsNotNormal)
    BasicInvertedFlagMACRO(IsNormal, IsNotNormal)
    BasicAliasMACRO(IsNormalWeapon, IsNormal)
    copyattrs = ObFormIDRecord.baseattrs + ['full', 'modPath', 'modb', 'modt_p',
                                        'iconPath', 'enchantment',
                                        'enchantPoints', 'speed', 'flags',
                                        'value', 'weight', 'damage']

    exportattrs = ObFormIDRecord.baseattrs + ['full', 'modPath', 'modb',
                                        'iconPath', 'enchantment',
                                        'enchantPoints', 'speed', 'flags',
                                        'value', 'weight', 'damage'] # 'modt_p',

class ObANIORecord(ObFormIDRecord):
    _Type = 'ANIO'
    ISTRING_MACRO(modPath, 5)
    FLOAT32_MACRO(modb, 6)
    UINT8_ARRAY_MACRO(modt_p, 7)
    FORMID_MACRO(animationId, 8)
    copyattrs = ObFormIDRecord.baseattrs + ['modPath', 'modb', 'modt_p', 'animationId']
    exportattrs = ObFormIDRecord.baseattrs + ['modPath', 'modb', 'animationId'] #'modt_p', 

class ObAPPARecord(ObFormIDRecord):
    _Type = 'APPA'
    STRING_MACRO(full, 5)
    ISTRING_MACRO(modPath, 6)
    FLOAT32_MACRO(modb, 7)
    UINT8_ARRAY_MACRO(modt_p, 8)
    ISTRING_MACRO(iconPath, 9)
    FORMID_MACRO(script, 10)
    UINT8_TYPE_MACRO(apparatusType, 11)
    UINT32_MACRO(value, 12)
    FLOAT32_MACRO(weight, 13)
    FLOAT32_MACRO(quality, 14)
    BasicTypeMACRO(IsMortarPestle, apparatus, 0, IsAlembic)
    BasicTypeMACRO(IsAlembic, apparatus, 1, IsMortarPestle)
    BasicTypeMACRO(IsCalcinator, apparatus, 2, IsMortarPestle)
    BasicTypeMACRO(IsRetort, apparatus, 3, IsMortarPestle)
    copyattrs = ObFormIDRecord.baseattrs + ['full', 'modPath', 'modb', 'modt_p',
                                        'iconPath', 'script', 'apparatusType',
                                        'value', 'weight', 'quality']
    exportattrs = ObFormIDRecord.baseattrs + ['full', 'modPath', 'modb',
                                        'iconPath', 'script', 'apparatusType',
                                        'value', 'weight', 'quality'] # 'modt_p',

class ObARMORecord(ObFormIDRecord):
    _Type = 'ARMO'
    STRING_MACRO(full, 5)
    FORMID_MACRO(script, 6)
    FORMID_MACRO(enchantment, 7)
    UINT16_MACRO(enchantPoints, 8)
    UINT32_FLAG_MACRO(flags, 9)
    GroupedValuesMACRO(maleBody, 10, Model)
    GroupedValuesMACRO(maleWorld, 13, Model)
    ISTRING_MACRO(maleIconPath, 16)
    GroupedValuesMACRO(femaleBody, 17, Model)
    GroupedValuesMACRO(femaleWorld, 20, Model)
    ISTRING_MACRO(femaleIconPath, 23)
    UINT16_MACRO(strength, 24)
    UINT32_MACRO(value, 25)
    UINT32_MACRO(health, 26)
    FLOAT32_MACRO(weight, 27)
    BasicFlagMACRO(IsHead, flags, 0x00000001)
    BasicFlagMACRO(IsHair, flags, 0x00000002)
    BasicFlagMACRO(IsUpperBody, flags, 0x00000004)
    BasicFlagMACRO(IsLowerBody, flags, 0x00000008)
    BasicFlagMACRO(IsHand, flags, 0x00000010)
    BasicFlagMACRO(IsFoot, flags, 0x00000020)
    BasicFlagMACRO(IsRightRing, flags, 0x00000040)
    BasicFlagMACRO(IsLeftRing, flags, 0x00000080)
    BasicFlagMACRO(IsAmulet, flags, 0x00000100)
    BasicFlagMACRO(IsWeapon, flags, 0x00000200)
    BasicFlagMACRO(IsBackWeapon, flags, 0x00000400)
    BasicFlagMACRO(IsSideWeapon, flags, 0x00000800)
    BasicFlagMACRO(IsQuiver, flags, 0x00001000)
    BasicFlagMACRO(IsShield, flags, 0x00002000)
    BasicFlagMACRO(IsTorch, flags, 0x00004000)
    BasicFlagMACRO(IsTail, flags, 0x00008000)
    BasicFlagMACRO(IsHideRings, flags, 0x00010000)
    BasicFlagMACRO(IsHideAmulets, flags, 0x00020000)
    BasicFlagMACRO(IsNonPlayable, flags, 0x00400000)
    BasicInvertedFlagMACRO(IsPlayable, IsNonPlayable)
    BasicFlagMACRO(IsHeavyArmor, flags, 0x00800000)
    exportattrs = copyattrs = ObFormIDRecord.baseattrs + ['full', 'script', 'enchantment', 'enchantPoints',
                                        'flags', 'maleBody_list', 'maleWorld_list', 'maleIconPath',
                                        'femaleBody_list', 'femaleWorld_list', 'femaleIconPath',
                                        'strength', 'value', 'health', 'weight']

class ObBOOKRecord(ObFormIDRecord):
    _Type = 'BOOK'
    STRING_MACRO(full, 5)
    ISTRING_MACRO(modPath, 6)
    FLOAT32_MACRO(modb, 7)
    UINT8_ARRAY_MACRO(modt_p, 8)
    ISTRING_MACRO(iconPath, 9)
    STRING_MACRO(text, 10)
    FORMID_MACRO(script, 11)
    FORMID_MACRO(enchantment, 12)
    UINT16_MACRO(enchantPoints, 13)
    UINT8_FLAG_MACRO(flags, 14)
    SINT8_MACRO(teaches, 15)
    UINT32_MACRO(value, 16)
    FLOAT32_MACRO(weight, 17)
    BasicFlagMACRO(IsScroll, flags, 0x00000001)
    BasicFlagMACRO(IsFixed, flags, 0x00000002)
    BasicAliasMACRO(IsCantBeTaken, IsFixed)
    copyattrs = ObFormIDRecord.baseattrs + ['full', 'modPath', 'modb', 'modt_p',
                                        'iconPath', 'text', 'script',
                                        'enchantment', 'enchantPoints',
                                        'flags', 'teaches', 'value', 'weight']
    exportattrs = ObFormIDRecord.baseattrs + ['full', 'modPath', 'modb',
                                        'iconPath', 'text', 'script',
                                        'enchantment', 'enchantPoints',
                                        'flags', 'teaches', 'value', 'weight'] # 'modt_p',

class ObBSGNRecord(ObFormIDRecord):
    _Type = 'BSGN'
    STRING_MACRO(full, 5)
    ISTRING_MACRO(iconPath, 6)
    STRING_MACRO(text, 7)
    FORMID_ARRAY_MACRO(spells, 8)
    exportattrs = copyattrs = ObFormIDRecord.baseattrs + ['full', 'iconPath', 'text', 'spells']

class ObCELLRecord(ObFormIDRecord):
    _Type = 'CELL'
    def __init__(self, CollectionIndex, ModID, RecordID, ParentID=0, CopyFlags=4):
        ##Record Creation Flags
        ##SetAsOverride       = 0x00000001,
        ##SetAsWorldCell      = 0x00000002,
        ##CopyWorldCellStatus = 0x00000004
        ObFormIDRecord.__init__(self, CollectionIndex, ModID, RecordID, ParentID, CopyFlags)

    @property
    def _ParentID(self):
        _CGetField.restype = POINTER(c_ulong)
        retValue = _CGetField(self._CollectionID, self._ModID, self._RecordID, 0, 40, 0, 0, 0, 0, 0, 0, 0)
        if(retValue): return retValue.contents.value
        return 0

    STRING_MACRO(full, 5)
    UINT8_FLAG_MACRO(flags, 6)
    UINT8_MACRO(ambientRed, 7)
    UINT8_MACRO(ambientGreen, 8)
    UINT8_MACRO(ambientBlue, 9)
    UINT8_ARRAY_MACRO(unused1, 10, 1)
    UINT8_MACRO(directionalRed, 11)
    UINT8_MACRO(directionalGreen, 12)
    UINT8_MACRO(directionalBlue, 13)
    UINT8_ARRAY_MACRO(unused2, 14, 1)
    UINT8_MACRO(fogRed, 15)
    UINT8_MACRO(fogGreen, 16)
    UINT8_MACRO(fogBlue, 17)
    UINT8_ARRAY_MACRO(unused3, 18, 1)
    FLOAT32_MACRO(fogNear, 19)
    FLOAT32_MACRO(fogFar, 20)
    SINT32_MACRO(directionalXY, 21)
    SINT32_MACRO(directionalZ, 22)
    FLOAT32_MACRO(directionalFade, 23)
    FLOAT32_MACRO(fogClip, 24)
    UINT8_MACRO(musicType, 25)
    FORMID_MACRO(owner, 26)
    SINT32_MACRO(rank, 27)
    FORMID_MACRO(globalVariable, 28)
    FORMID_MACRO(climate, 29)
    FLOAT32_MACRO(waterHeight, 30)
    FORMID_ARRAY_MACRO(regions, 31)
    SINT32_OR_UNKNOWN_MACRO(posX, 32)
    SINT32_OR_UNKNOWN_MACRO(posY, 33)
    FORMID_MACRO(water, 34)
    SUBRECORD_ARRAY_MACRO(ACHR, "ACHR", 35, ObACHRRecord, 0)
    SUBRECORD_ARRAY_MACRO(ACRE, "ACRE", 36, ObACRERecord, 0)
    SUBRECORD_ARRAY_MACRO(REFR, "REFR", 37, ObREFRRecord, 0)
    SUBRECORD_MACRO(PGRD, "PGRD", 38, ObPGRDRecord, 0)
    SUBRECORD_MACRO(LAND, "LAND", 39, ObLANDRecord, 0)
    BasicFlagMACRO(IsInterior, flags, 0x00000001)
    BasicFlagMACRO(IsHasWater, flags, 0x00000002)
    BasicFlagMACRO(IsInvertFastTravel, flags, 0x00000004)
    BasicFlagMACRO(IsForceHideLand, flags, 0x00000008)
    BasicFlagMACRO(IsPublicPlace, flags, 0x00000020)
    BasicFlagMACRO(IsHandChanged, flags, 0x00000040)
    BasicFlagMACRO(IsBehaveLikeExterior, flags, 0x00000080)
    BasicTypeMACRO(IsDefault, music, 0, IsPublic)
    BasicTypeMACRO(IsPublic, music, 1, IsDefault)
    BasicTypeMACRO(IsDungeon, music, 2, IsDefault)
    exportattrs = copyattrs = ObFormIDRecord.baseattrs + ['full', 'flags', 'ambientRed', 'ambientGreen', 'ambientBlue',
                                        'directionalRed', 'directionalGreen', 'directionalBlue',
                                        'fogRed', 'fogGreen', 'fogBlue', 'fogNear', 'fogFar',
                                        'directionalXY', 'directionalZ', 'directionalFade', 'fogClip',
                                        'musicType', 'owner', 'rank', 'globalVariable',
                                        'climate', 'waterHeight', 'regions', 'posX', 'posY',
                                        'water']

class ObCLASRecord(ObFormIDRecord):
    _Type = 'CLAS'
    STRING_MACRO(full, 5)
    STRING_MACRO(description, 6)
    ISTRING_MACRO(iconPath, 7)
    SINT32_MACRO(primary1, 8)
    SINT32_MACRO(primary2, 9)
    UINT32_MACRO(specialization, 10)
    SINT32_MACRO(major1, 11)
    SINT32_MACRO(major2, 12)
    SINT32_MACRO(major3, 13)
    SINT32_MACRO(major4, 14)
    SINT32_MACRO(major5, 15)
    SINT32_MACRO(major6, 16)
    SINT32_MACRO(major7, 17)
    UINT32_FLAG_MACRO(flags, 18)
    UINT32_FLAG_MACRO(services, 19)
    SINT8_MACRO(trainSkill, 20)
    UINT8_MACRO(trainLevel, 21)
    UINT8_ARRAY_MACRO(unused1, 22, 2)
    BasicFlagMACRO(IsPlayable, flags, 0x00000001)
    BasicFlagMACRO(IsGuard, flags, 0x00000002)
    BasicFlagMACRO(IsServicesWeapons, services, 0x00000001)
    BasicFlagMACRO(IsServicesArmor, services, 0x00000002)
    BasicFlagMACRO(IsServicesClothing, services, 0x00000004)
    BasicFlagMACRO(IsServicesBooks, services, 0x00000008)
    BasicFlagMACRO(IsServicesIngredients, services, 0x00000010)
    BasicFlagMACRO(IsServicesLights, services, 0x00000080)
    BasicFlagMACRO(IsServicesApparatus, services, 0x00000100)
    BasicFlagMACRO(IsServicesMiscItems, services, 0x00000400)
    BasicFlagMACRO(IsServicesSpells, services, 0x00000800)
    BasicFlagMACRO(IsServicesMagicItems, services, 0x00001000)
    BasicFlagMACRO(IsServicesPotions, services, 0x00002000)
    BasicFlagMACRO(IsServicesTraining, services, 0x00004000)
    BasicFlagMACRO(IsServicesRecharge, services, 0x00010000)
    BasicFlagMACRO(IsServicesRepair, services, 0x00020000)
    exportattrs = copyattrs = ObFormIDRecord.baseattrs + ['full', 'description', 'iconPath', 'primary1',
                                        'primary2', 'specialization', 'major1',
                                        'major2', 'major3', 'major4', 'major5',
                                        'major6', 'major7', 'flags', 'services',
                                        'trainSkill', 'trainLevel']

class ObCLMTRecord(ObFormIDRecord):
    _Type = 'CLMT'
    class Weather(ListComponent):
        FORMID_LISTMACRO(weather, 5, 1)
        SINT32_LISTMACRO(chance, 5, 2)
        copyattrs = ['weather', 'chance']

    LIST_MACRO(weathers, 5, self.Weather)
    ISTRING_MACRO(sunPath, 6)
    ISTRING_MACRO(glarePath, 7)
    ISTRING_MACRO(modPath, 8)
    FLOAT32_MACRO(modb, 9)
    UINT8_ARRAY_MACRO(modt_p, 10)
    UINT8_MACRO(riseBegin, 11)
    UINT8_MACRO(riseEnd, 12)
    UINT8_MACRO(setBegin, 13)
    UINT8_MACRO(setEnd, 14)
    UINT8_MACRO(volatility, 15)
    UINT8_MACRO(phaseLength, 16)
    copyattrs = ObFormIDRecord.baseattrs + ['weathers_list', 'sunPath', 'glarePath', 'modPath',
                                        'modb', 'modt_p', 'riseBegin', 'riseEnd',
                                        'setBegin', 'setEnd', 'volatility', 'phaseLength']
    exportattrs = ObFormIDRecord.baseattrs + ['weathers_list', 'sunPath', 'glarePath', 'modPath',
                                        'modb', 'riseBegin', 'riseEnd',
                                        'setBegin', 'setEnd', 'volatility', 'phaseLength'] #'modt_p', 

class ObCLOTRecord(ObFormIDRecord):
    _Type = 'CLOT'
    STRING_MACRO(full, 5)
    FORMID_MACRO(script, 6)
    FORMID_MACRO(enchantment, 7)
    UINT16_MACRO(enchantPoints, 8)
    UINT32_FLAG_MACRO(flags, 9)
    GroupedValuesMACRO(maleBody, 10, Model)
    GroupedValuesMACRO(maleWorld, 13, Model)
    ISTRING_MACRO(maleIconPath, 16)
    GroupedValuesMACRO(femaleBody, 17, Model)
    GroupedValuesMACRO(femaleWorld, 20, Model)
    ISTRING_MACRO(femaleIconPath, 23)
    UINT32_MACRO(value, 24)
    FLOAT32_MACRO(weight, 25)
    BasicFlagMACRO(IsHead, flags, 0x00000001)
    BasicFlagMACRO(IsHair, flags, 0x00000002)
    BasicFlagMACRO(IsUpperBody, flags, 0x00000004)
    BasicFlagMACRO(IsLowerBody, flags, 0x00000008)
    BasicFlagMACRO(IsHand, flags, 0x00000010)
    BasicFlagMACRO(IsFoot, flags, 0x00000020)
    BasicFlagMACRO(IsRightRing, flags, 0x00000040)
    BasicFlagMACRO(IsLeftRing, flags, 0x00000080)
    BasicFlagMACRO(IsAmulet, flags, 0x00000100)
    BasicFlagMACRO(IsWeapon, flags, 0x00000200)
    BasicFlagMACRO(IsBackWeapon, flags, 0x00000400)
    BasicFlagMACRO(IsSideWeapon, flags, 0x00000800)
    BasicFlagMACRO(IsQuiver, flags, 0x00001000)
    BasicFlagMACRO(IsShield, flags, 0x00002000)
    BasicFlagMACRO(IsTorch, flags, 0x00004000)
    BasicFlagMACRO(IsTail, flags, 0x00008000)
    BasicFlagMACRO(IsHideRings, flags, 0x00010000)
    BasicFlagMACRO(IsHideAmulets, flags, 0x00020000)
    BasicFlagMACRO(IsNonPlayable, flags, 0x00400000)
    BasicInvertedFlagMACRO(IsPlayable, IsNonPlayable)
    copyattrs = ObFormIDRecord.baseattrs + ['full', 'script', 'enchantment',
                                        'enchantPoints', 'flags', 'maleBody_list', 'maleWorld_list',
                                        'maleIconPath', 'femaleBody_list', 'femaleWorld_list',
                                        'femaleIconPath', 'value', 'weight']
    exportattrs = ObFormIDRecord.baseattrs + ['full', 'script', 'enchantment',
                                        'enchantPoints', 'flags', 'maleBody', 'maleWorld',
                                        'maleIconPath', 'femaleBody', 'femaleWorld',
                                        'femaleIconPath', 'value', 'weight']

class ObCONTRecord(ObFormIDRecord):
    _Type = 'CONT'
    def mergeFilter(self,modSet):
        """Filter out items that don't come from specified modSet.
        Filters items."""
        self.items = [x for x in self.items if (x.item)[0] in modSet]

    STRING_MACRO(full, 5)
    ISTRING_MACRO(modPath, 6)
    FLOAT32_MACRO(modb, 7)
    UINT8_ARRAY_MACRO(modt_p, 8)
    FORMID_MACRO(script, 9)

    LIST_MACRO(items, 10, Item)
    UINT8_FLAG_MACRO(flags, 11)
    FLOAT32_MACRO(weight, 12)
    FORMID_MACRO(soundOpen, 13)
    FORMID_MACRO(soundClose, 14)
    BasicFlagMACRO(IsRespawn, flags, 0x00000001)
    copyattrs = ObFormIDRecord.baseattrs + ['full', 'modPath', 'modb', 'modt_p',
                                        'script', 'items_list', 'flags', 'weight',
                                        'soundOpen', 'soundClose']

    exportattrs = ObFormIDRecord.baseattrs + ['full', 'modPath', 'modb',
                                        'script', 'items_list', 'flags', 'weight',
                                        'soundOpen', 'soundClose'] # 'modt_p',

class ObCREARecord(ObFormIDRecord):
    _Type = 'CREA'
    def mergeFilter(self,modSet):
        """Filter out items that don't come from specified modSet.
        Filters spells, factions and items."""
        self.spells = [x for x in self.spells if x[0] in modSet]
        self.factions = [x for x in self.factions if x.faction[0] in modSet]
        self.items = [x for x in self.items if x.item[0] in modSet]

    class Sound(ListComponent):
        UINT32_LISTMACRO(type, 58, 1)
        FORMID_LISTMACRO(sound, 58, 2)
        UINT8_LISTMACRO(chance, 58, 3)
        exportattrs = copyattrs = ['type', 'sound', 'chance']

    STRING_MACRO(full, 5)
    ISTRING_MACRO(modPath, 6)
    FLOAT32_MACRO(modb, 7)
    UINT8_ARRAY_MACRO(modt_p, 8)
    FORMID_ARRAY_MACRO(spells, 9)
    ISTRING_ARRAY_MACRO(bodyParts, 10)
    UINT8_ARRAY_MACRO(nift_p, 11)
    UINT32_FLAG_MACRO(flags, 12)
    UINT16_MACRO(baseSpell, 13)
    UINT16_MACRO(fatigue, 14)
    UINT16_MACRO(barterGold, 15)
    SINT16_MACRO(level, 16)
    UINT16_MACRO(calcMin, 17)
    UINT16_MACRO(calcMax, 18)

    LIST_MACRO(factions, 19, Faction)
    FORMID_MACRO(deathItem, 20)
    FORMID_MACRO(script, 21)

    LIST_MACRO(items, 22, Item)
    UINT8_MACRO(aggression, 23)
    UINT8_MACRO(confidence, 24)
    UINT8_MACRO(energyLevel, 25)
    UINT8_MACRO(responsibility, 26)
    UINT32_FLAG_MACRO(services, 27)
    SINT8_MACRO(trainSkill, 28)
    UINT8_MACRO(trainLevel, 29)
    UINT8_ARRAY_MACRO(unused1, 30, 2)
    FORMID_ARRAY_MACRO(aiPackages, 31)
    ISTRING_ARRAY_MACRO(animations, 32)
    UINT8_TYPE_MACRO(creatureType, 33)
    UINT8_MACRO(combat, 34)
    UINT8_MACRO(magic, 35)
    UINT8_MACRO(stealth, 36)
    UINT8_TYPE_MACRO(soulType, 37)
    UINT8_ARRAY_MACRO(unused2, 38, 1)
    UINT16_MACRO(health, 39)
    UINT8_ARRAY_MACRO(unused3, 40, 2)
    UINT16_MACRO(attackDamage, 41)
    UINT8_MACRO(strength, 42)
    UINT8_MACRO(intelligence, 43)
    UINT8_MACRO(willpower, 44)
    UINT8_MACRO(agility, 45)
    UINT8_MACRO(speed, 46)
    UINT8_MACRO(endurance, 47)
    UINT8_MACRO(personality, 48)
    UINT8_MACRO(luck, 49)
    UINT8_MACRO(attackReach, 50)
    FORMID_MACRO(combatStyle, 51)
    FLOAT32_MACRO(turningSpeed, 52)
    FLOAT32_MACRO(baseScale, 53)
    FLOAT32_MACRO(footWeight, 54)
    FORMID_MACRO(inheritsSoundsFrom, 55)
    ISTRING_MACRO(bloodSprayPath, 56)
    ISTRING_MACRO(bloodDecalPath, 57)

    LIST_MACRO(sounds, 58, self.Sound)
    BasicFlagMACRO(IsBiped, flags, 0x00000001)
    BasicFlagMACRO(IsEssential, flags, 0x00000002)
    BasicFlagMACRO(IsWeaponAndShield, flags, 0x00000004)
    BasicFlagMACRO(IsRespawn, flags, 0x00000008)
    BasicFlagMACRO(IsSwims, flags, 0x00000010)
    BasicFlagMACRO(IsFlies, flags, 0x00000020)
    BasicFlagMACRO(IsWalks, flags, 0x00000040)
    BasicFlagMACRO(IsPCLevelOffset, flags, 0x00000080)
    BasicFlagMACRO(IsNoLowLevel, flags, 0x00000200)
    BasicInvertedFlagMACRO(IsLowLevel, IsNoLowLevel)
    BasicFlagMACRO(IsNoBloodSpray, flags, 0x00000800)
    BasicInvertedFlagMACRO(IsBloodSpray, IsNoBloodSpray)
    BasicFlagMACRO(IsNoBloodDecal, flags, 0x00001000)
    BasicInvertedFlagMACRO(IsBloodDecal, IsNoBloodDecal)
    BasicFlagMACRO(IsSummonable, flags, 0x00004000)
    BasicFlagMACRO(IsNoHead, flags, 0x00008000)
    BasicInvertedFlagMACRO(IsHead, IsNoHead)
    BasicFlagMACRO(IsNoRightArm, flags, 0x00010000)
    BasicInvertedFlagMACRO(IsRightArm, IsNoRightArm)
    BasicFlagMACRO(IsNoLeftArm, flags, 0x00020000)
    BasicInvertedFlagMACRO(IsLeftArm, IsNoLeftArm)
    BasicFlagMACRO(IsNoCombatInWater, flags, 0x00040000)
    BasicInvertedFlagMACRO(IsCombatInWater, IsNoCombatInWater)
    BasicFlagMACRO(IsNoShadow, flags, 0x00080000)
    BasicInvertedFlagMACRO(IsShadow, IsNoShadow)
    BasicFlagMACRO(IsNoCorpseCheck, flags, 0x00100000)
    BasicInvertedFlagMACRO(IsCorpseCheck, IsNoCorpseCheck)
    BasicFlagMACRO(IsServicesWeapons, services, 0x00000001)
    BasicFlagMACRO(IsServicesArmor, services, 0x00000002)
    BasicFlagMACRO(IsServicesClothing, services, 0x00000004)
    BasicFlagMACRO(IsServicesBooks, services, 0x00000008)
    BasicFlagMACRO(IsServicesIngredients, services, 0x00000010)
    BasicFlagMACRO(IsServicesLights, services, 0x00000080)
    BasicFlagMACRO(IsServicesApparatus, services, 0x00000100)
    BasicFlagMACRO(IsServicesMiscItems, services, 0x00000400)
    BasicFlagMACRO(IsServicesSpells, services, 0x00000800)
    BasicFlagMACRO(IsServicesMagicItems, services, 0x00001000)
    BasicFlagMACRO(IsServicesPotions, services, 0x00002000)
    BasicFlagMACRO(IsServicesTraining, services, 0x00004000)
    BasicFlagMACRO(IsServicesRecharge, services, 0x00010000)
    BasicFlagMACRO(IsServicesRepair, services, 0x00020000)
    BasicTypeMACRO(IsCreature, creatureType, 0, IsDaedra)
    BasicTypeMACRO(IsDaedra, creatureType, 1, IsCreature)
    BasicTypeMACRO(IsUndead, creatureType, 2, IsCreature)
    BasicTypeMACRO(IsHumanoid, creatureType, 3, IsCreature)
    BasicTypeMACRO(IsHorse, creatureType, 4, IsCreature)
    BasicTypeMACRO(IsGiant, creatureType, 5, IsCreature)
    BasicTypeMACRO(IsNoSoul, soulType, 0, IsPettySoul)
    BasicTypeMACRO(IsPettySoul, soulType, 1, IsNoSoul)
    BasicTypeMACRO(IsLesserSoul, soulType, 2, IsNoSoul)
    BasicTypeMACRO(IsCommonSoul, soulType, 3, IsNoSoul)
    BasicTypeMACRO(IsGreaterSoul, soulType, 4, IsNoSoul)
    BasicTypeMACRO(IsGrandSoul, soulType, 5, IsNoSoul)
    copyattrs = ObFormIDRecord.baseattrs + ['full', 'modPath', 'modb', 'modt_p', 'spells',
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
    exportattrs = ObFormIDRecord.baseattrs + ['full', 'modPath', 'modb', 'spells',
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

class ObCSTYRecord(ObFormIDRecord):
    _Type = 'CSTY'
    UINT8_MACRO(dodgeChance, 5)
    UINT8_MACRO(lrChance, 6)
    UINT8_ARRAY_MACRO(unused1, 7, 2)
    FLOAT32_MACRO(lrTimerMin, 8)
    FLOAT32_MACRO(lrTimerMax, 9)
    FLOAT32_MACRO(forTimerMin, 10)
    FLOAT32_MACRO(forTimerMax, 11)
    FLOAT32_MACRO(backTimerMin, 12)
    FLOAT32_MACRO(backTimerMax, 13)
    FLOAT32_MACRO(idleTimerMin, 14)
    FLOAT32_MACRO(idleTimerMax, 15)
    UINT8_MACRO(blkChance, 16)
    UINT8_MACRO(atkChance, 17)
    UINT8_ARRAY_MACRO(unused2, 18, 2)
    FLOAT32_MACRO(atkBRecoil, 19)
    FLOAT32_MACRO(atkBUnc, 20)
    FLOAT32_MACRO(atkBh2h, 21)
    UINT8_MACRO(pAtkChance, 22)
    UINT8_ARRAY_MACRO(unused3, 23, 3)
    FLOAT32_MACRO(pAtkBRecoil, 24)
    FLOAT32_MACRO(pAtkBUnc, 25)
    UINT8_MACRO(pAtkNormal, 26)
    UINT8_MACRO(pAtkFor, 27)
    UINT8_MACRO(pAtkBack, 28)
    UINT8_MACRO(pAtkL, 29)
    UINT8_MACRO(pAtkR, 30)
    UINT8_ARRAY_MACRO(unused4, 31, 3)
    FLOAT32_MACRO(holdTimerMin, 32)
    FLOAT32_MACRO(holdTimerMax, 33)
    UINT8_FLAG_MACRO(flagsA, 34)
    UINT8_MACRO(acroDodge, 35)
    UINT8_ARRAY_MACRO(unused5, 36, 2)
    FLOAT32_MACRO(rMultOpt, 37)
    FLOAT32_MACRO(rMultMax, 38)
    FLOAT32_MACRO(mDistance, 39)
    FLOAT32_MACRO(rDistance, 40)
    FLOAT32_MACRO(buffStand, 41)
    FLOAT32_MACRO(rStand, 42)
    FLOAT32_MACRO(groupStand, 43)
    UINT8_MACRO(rushChance, 44)
    UINT8_ARRAY_MACRO(unused6, 45, 3)
    FLOAT32_MACRO(rushMult, 46)
    UINT32_FLAG_MACRO(flagsB, 47)
    FLOAT32_MACRO(dodgeFMult, 48)
    FLOAT32_MACRO(dodgeFBase, 49)
    FLOAT32_MACRO(encSBase, 50)
    FLOAT32_MACRO(encSMult, 51)
    FLOAT32_MACRO(dodgeAtkMult, 52)
    FLOAT32_MACRO(dodgeNAtkMult, 53)
    FLOAT32_MACRO(dodgeBAtkMult, 54)
    FLOAT32_MACRO(dodgeBNAtkMult, 55)
    FLOAT32_MACRO(dodgeFAtkMult, 56)
    FLOAT32_MACRO(dodgeFNAtkMult, 57)
    FLOAT32_MACRO(blockMult, 58)
    FLOAT32_MACRO(blockBase, 59)
    FLOAT32_MACRO(blockAtkMult, 60)
    FLOAT32_MACRO(blockNAtkMult, 61)
    FLOAT32_MACRO(atkMult, 62)
    FLOAT32_MACRO(atkBase, 63)
    FLOAT32_MACRO(atkAtkMult, 64)
    FLOAT32_MACRO(atkNAtkMult, 65)
    FLOAT32_MACRO(atkBlockMult, 66)
    FLOAT32_MACRO(pAtkFBase, 67)
    FLOAT32_MACRO(pAtkFMult, 68)
    BasicFlagMACRO(IsUseAdvanced, flagsA, 0x00000001)
    BasicFlagMACRO(IsUseChanceForAttack, flagsA, 0x00000002)
    BasicFlagMACRO(IsIgnoreAllies, flagsA, 0x00000004)
    BasicFlagMACRO(IsWillYield, flagsA, 0x00000008)
    BasicFlagMACRO(IsRejectsYields, flagsA, 0x00000010)
    BasicFlagMACRO(IsFleeingDisabled, flagsA, 0x00000020)
    BasicFlagMACRO(IsPrefersRanged, flagsA, 0x00000040)
    BasicFlagMACRO(IsMeleeAlertOK, flagsA, 0x00000080)
    BasicFlagMACRO(IsDoNotAcquire, flagsB, 0x00000001)
    exportattrs = copyattrs = ObFormIDRecord.baseattrs + ['dodgeChance', 'lrChance', 'lrTimerMin', 'lrTimerMax',
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

class ObDIALRecord(ObFormIDRecord):
    _Type = 'DIAL'
    FORMID_ARRAY_MACRO(quests, 5)
    FORMID_ARRAY_MACRO(removedQuests, 6)
    STRING_MACRO(full, 7)
    UINT8_TYPE_MACRO(dialType, 8)
    SUBRECORD_ARRAY_MACRO(INFO, "INFO", 9, ObINFORecord, 0)
    BasicTypeMACRO(IsTopic, dialType, 0, IsConversation)
    BasicTypeMACRO(IsConversation, dialType, 1, IsTopic)
    BasicTypeMACRO(IsCombat, dialType, 2, IsTopic)
    BasicTypeMACRO(IsPersuasion, dialType, 3, IsTopic)
    BasicTypeMACRO(IsDetection, dialType, 4, IsTopic)
    BasicTypeMACRO(IsService, dialType, 5, IsTopic)
    BasicTypeMACRO(IsMisc, dialType, 6, IsTopic)
    exportattrs = copyattrs = ObFormIDRecord.baseattrs + ['quests', 'removedQuests',
                                        'full', 'dialType']

class ObDOORRecord(ObFormIDRecord):
    _Type = 'DOOR'
    STRING_MACRO(full, 5)
    ISTRING_MACRO(modPath, 6)
    FLOAT32_MACRO(modb, 7)
    UINT8_ARRAY_MACRO(modt_p, 8)
    FORMID_MACRO(script, 9)
    FORMID_MACRO(soundOpen, 10)
    FORMID_MACRO(soundClose, 11)
    FORMID_MACRO(soundLoop, 12)
    UINT8_FLAG_MACRO(flags, 13)
    FORMID_ARRAY_MACRO(destinations, 14)
    BasicFlagMACRO(IsOblivionGate, flags, 0x00000001)
    BasicFlagMACRO(IsAutomatic, flags, 0x00000002)
    BasicFlagMACRO(IsHidden, flags, 0x00000004)
    BasicFlagMACRO(IsMinimalUse, flags, 0x00000008)
    copyattrs = ObFormIDRecord.baseattrs + ['full', 'modPath', 'modb', 'modt_p',
                                        'script', 'soundOpen',
                                        'soundClose', 'soundLoop',
                                        'flags', 'destinations']
    exportattrs = ObFormIDRecord.baseattrs + ['full', 'modPath', 'modb',
                                        'script', 'soundOpen',
                                        'soundClose', 'soundLoop',
                                        'flags', 'destinations'] # 'modt_p',

class ObEFSHRecord(ObFormIDRecord):
    _Type = 'EFSH'
    ISTRING_MACRO(fillTexturePath, 5)
    ISTRING_MACRO(particleTexturePath, 6)
    UINT8_FLAG_MACRO(flags, 7)
    UINT8_ARRAY_MACRO(unused1, 8, 3)
    UINT32_MACRO(memSBlend, 9)
    UINT32_MACRO(memBlendOp, 10)
    UINT32_MACRO(memZFunc, 11)
    UINT8_MACRO(fillRed, 12)
    UINT8_MACRO(fillGreen, 13)
    UINT8_MACRO(fillBlue, 14)
    UINT8_ARRAY_MACRO(unused2, 15, 1)
    FLOAT32_MACRO(fillAIn, 16)
    FLOAT32_MACRO(fillAFull, 17)
    FLOAT32_MACRO(fillAOut, 18)
    FLOAT32_MACRO(fillAPRatio, 19)
    FLOAT32_MACRO(fillAAmp, 20)
    FLOAT32_MACRO(fillAFreq, 21)
    FLOAT32_MACRO(fillAnimSpdU, 22)
    FLOAT32_MACRO(fillAnimSpdV, 23)
    FLOAT32_MACRO(edgeOff, 24)
    UINT8_MACRO(edgeRed, 25)
    UINT8_MACRO(edgeGreen, 26)
    UINT8_MACRO(edgeBlue, 27)
    UINT8_ARRAY_MACRO(unused3, 28, 1)
    FLOAT32_MACRO(edgeAIn, 29)
    FLOAT32_MACRO(edgeAFull, 30)
    FLOAT32_MACRO(edgeAOut, 31)
    FLOAT32_MACRO(edgeAPRatio, 32)
    FLOAT32_MACRO(edgeAAmp, 33)
    FLOAT32_MACRO(edgeAFreq, 34)
    FLOAT32_MACRO(fillAFRatio, 35)
    FLOAT32_MACRO(edgeAFRatio, 36)
    UINT8_MACRO(memDBlend, 37)
    UINT8_MACRO(partSBlend, 38)
    UINT8_MACRO(partBlendOp, 39)
    UINT8_MACRO(partZFunc, 40)
    UINT8_MACRO(partDBlend, 41)
    FLOAT32_MACRO(partBUp, 42)
    FLOAT32_MACRO(partBFull, 43)
    FLOAT32_MACRO(partBDown, 44)
    FLOAT32_MACRO(partBFRatio, 45)
    FLOAT32_MACRO(partBPRatio, 46)
    FLOAT32_MACRO(partLTime, 47)
    FLOAT32_MACRO(partLDelta, 48)
    FLOAT32_MACRO(partNSpd, 49)
    FLOAT32_MACRO(partNAcc, 50)
    FLOAT32_MACRO(partVel1, 51)
    FLOAT32_MACRO(partVel2, 52)
    FLOAT32_MACRO(partVel3, 53)
    FLOAT32_MACRO(partAcc1, 54)
    FLOAT32_MACRO(partAcc2, 55)
    FLOAT32_MACRO(partAcc3, 56)
    FLOAT32_MACRO(partKey1, 57)
    FLOAT32_MACRO(partKey2, 58)
    FLOAT32_MACRO(partKey1Time, 59)
    FLOAT32_MACRO(partKey2Time, 60)
    UINT8_MACRO(key1Red, 61)
    UINT8_MACRO(key1Green, 62)
    UINT8_MACRO(key1Blue, 63)
    UINT8_ARRAY_MACRO(unused4, 64, 1)
    UINT8_MACRO(key2Red, 65)
    UINT8_MACRO(key2Green, 66)
    UINT8_MACRO(key2Blue, 67)
    UINT8_ARRAY_MACRO(unused5, 68, 1)
    UINT8_MACRO(key3Red, 69)
    UINT8_MACRO(key3Green, 70)
    UINT8_MACRO(key3Blue, 71)
    UINT8_ARRAY_MACRO(unused6, 72, 1)
    FLOAT32_MACRO(key1A, 73)
    FLOAT32_MACRO(key2A, 74)
    FLOAT32_MACRO(key3A, 75)
    FLOAT32_MACRO(key1Time, 76)
    FLOAT32_MACRO(key2Time, 77)
    FLOAT32_MACRO(key3Time, 78)
    BasicFlagMACRO(IsNoMemShader, flags, 0x00000001)
    BasicAliasMACRO(IsNoMembraneShader, IsNoMemShader)
    BasicFlagMACRO(IsNoPartShader, flags, 0x00000008)
    BasicAliasMACRO(IsNoParticleShader, IsNoPartShader)
    BasicFlagMACRO(IsEdgeInverse, flags, 0x00000010)
    BasicAliasMACRO(IsEdgeEffectInverse, IsEdgeInverse)
    BasicFlagMACRO(IsMemSkinOnly, flags, 0x00000020)
    BasicAliasMACRO(IsMembraneShaderSkinOnly, IsMemSkinOnly)
    exportattrs = copyattrs = ObFormIDRecord.baseattrs + ['fillTexturePath', 'particleTexturePath', 'flags', 'memSBlend', 'memBlendOp',
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

class ObENCHRecord(ObFormIDRecord):
    _Type = 'ENCH'
    STRING_MACRO(full, 5)
    UINT32_TYPE_MACRO(itemType, 6)
    UINT32_MACRO(chargeAmount, 7)
    UINT32_MACRO(enchantCost, 8)
    UINT8_FLAG_MACRO(flags, 9)
    UINT8_ARRAY_MACRO(unused1, 10, 3)

    LIST_MACRO(effects, 11, Effect)
    BasicFlagMACRO(IsNoAutoCalc, flags, 0x00000001)
    BasicTypeMACRO(IsScroll, itemType, 0, IsStaff)
    BasicTypeMACRO(IsStaff, itemType, 1, IsScroll)
    BasicTypeMACRO(IsWeapon, itemType, 2, IsScroll)
    BasicTypeMACRO(IsApparel, itemType, 3, IsScroll)
    ##OBME Fields. Setting any of the below fields will make the mod require JRoush's OBME plugin for OBSE
    ##To see if OBME is in use, check the recordVersion field for a non-None value
    UINT8_MACRO(recordVersion, 12)
    UINT8_MACRO(betaVersion, 13)
    UINT8_MACRO(minorVersion, 14)
    UINT8_MACRO(majorVersion, 15)
    UINT8_ARRAY_MACRO(reserved, 16, 0x1C)
    UINT8_ARRAY_MACRO(datx_p, 17, 0x20)
    exportattrs = copyattrs = ObFormIDRecord.baseattrs + ['full', 'itemType', 'chargeAmount',
                                        'enchantCost', 'flags', 'effects_list']
    copyattrsOBME = copyattrs + ['recordVersion', 'betaVersion',
                                 'minorVersion', 'majorVersion',
                                 'reserved'] #, 'datx_p'

class ObEYESRecord(ObFormIDRecord):
    _Type = 'EYES'
    STRING_MACRO(full, 5)
    ISTRING_MACRO(iconPath, 6)
    UINT8_FLAG_MACRO(flags, 7)
    BasicFlagMACRO(IsPlayable, flags, 0x00000001)
    exportattrs = copyattrs = ObFormIDRecord.baseattrs + ['full', 'iconPath', 'flags']

class ObFACTRecord(ObFormIDRecord):
    _Type = 'FACT'
    class Rank(ListComponent):
        SINT32_LISTMACRO(rank, 10, 1)
        STRING_LISTMACRO(male, 10, 2)
        STRING_LISTMACRO(female, 10, 3)
        ISTRING_LISTMACRO(insigniaPath, 10, 4)
        exportattrs = copyattrs = ['rank', 'male', 'female', 'insigniaPath']

    STRING_MACRO(full, 5)

    LIST_MACRO(relations, 6, Relation)
    UINT8_FLAG_MACRO(flags, 7)
    FLOAT32_MACRO(crimeGoldMultiplier, 8)

    LIST_MACRO(ranks, 9, self.Rank)
    BasicFlagMACRO(IsHiddenFromPC, flags, 0x00000001)
    BasicFlagMACRO(IsEvil, flags, 0x00000002)
    BasicFlagMACRO(IsSpecialCombat, flags, 0x00000004)
    exportattrs = copyattrs = ObFormIDRecord.baseattrs + ['full', 'relations_list', 'flags',
                                        'crimeGoldMultiplier', 'ranks_list']

class ObFLORRecord(ObFormIDRecord):
    _Type = 'FLOR'
    STRING_MACRO(full, 5)
    ISTRING_MACRO(modPath, 6)
    FLOAT32_MACRO(modb, 7)
    UINT8_ARRAY_MACRO(modt_p, 8)
    FORMID_MACRO(script, 9)
    FORMID_MACRO(ingredient, 10)
    UINT8_MACRO(spring, 11)
    UINT8_MACRO(summer, 12)
    UINT8_MACRO(fall, 13)
    UINT8_MACRO(winter, 14)
    copyattrs = ObFormIDRecord.baseattrs + ['full', 'modPath', 'modb', 'modt_p',
                                        'script', 'ingredient', 'spring',
                                        'summer', 'fall', 'winter']
    exportattrs = ObFormIDRecord.baseattrs + ['full', 'modPath', 'modb',
                                        'script', 'ingredient', 'spring',
                                        'summer', 'fall', 'winter'] # 'modt_p',

class ObFURNRecord(ObFormIDRecord):
    _Type = 'FURN'
    STRING_MACRO(full, 5)
    ISTRING_MACRO(modPath, 6)
    FLOAT32_MACRO(modb, 7)
    UINT8_ARRAY_MACRO(modt_p, 8)
    FORMID_MACRO(script, 9)
    UINT32_FLAG_MACRO(flags, 10)
    BasicFlagMACRO(IsAnim01, flags, 0x00000001)
    BasicFlagMACRO(IsAnim02, flags, 0x00000002)
    BasicFlagMACRO(IsAnim03, flags, 0x00000004)
    BasicFlagMACRO(IsAnim04, flags, 0x00000008)
    BasicFlagMACRO(IsAnim05, flags, 0x00000010)
    BasicFlagMACRO(IsAnim06, flags, 0x00000020)
    BasicFlagMACRO(IsAnim07, flags, 0x00000040)
    BasicFlagMACRO(IsAnim08, flags, 0x00000080)
    BasicFlagMACRO(IsAnim09, flags, 0x00000100)
    BasicFlagMACRO(IsAnim10, flags, 0x00000200)
    BasicFlagMACRO(IsAnim11, flags, 0x00000400)
    BasicFlagMACRO(IsAnim12, flags, 0x00000800)
    BasicFlagMACRO(IsAnim13, flags, 0x00001000)
    BasicFlagMACRO(IsAnim14, flags, 0x00002000)
    BasicFlagMACRO(IsAnim15, flags, 0x00004000)
    BasicFlagMACRO(IsAnim16, flags, 0x00008000)
    BasicFlagMACRO(IsAnim17, flags, 0x00010000)
    BasicFlagMACRO(IsAnim18, flags, 0x00020000)
    BasicFlagMACRO(IsAnim19, flags, 0x00040000)
    BasicFlagMACRO(IsAnim20, flags, 0x00080000)
    BasicFlagMACRO(IsAnim21, flags, 0x00100000)
    BasicFlagMACRO(IsAnim22, flags, 0x00200000)
    BasicFlagMACRO(IsAnim23, flags, 0x00400000)
    BasicFlagMACRO(IsAnim24, flags, 0x00800000)
    BasicFlagMACRO(IsAnim25, flags, 0x01000000)
    BasicFlagMACRO(IsAnim26, flags, 0x02000000)
    BasicFlagMACRO(IsAnim27, flags, 0x04000000)
    BasicFlagMACRO(IsAnim28, flags, 0x08000000)
    BasicFlagMACRO(IsAnim29, flags, 0x10000000)
    BasicFlagMACRO(IsAnim30, flags, 0x20000000)
    MaskedTypeMACRO(IsSitAnim, flags, 0xC0000000, 0x40000000, IsSleepAnim)
    MaskedTypeMACRO(IsSleepAnim, flags, 0xC0000000, 0x80000000, IsSitAnim)
    copyattrs = ObFormIDRecord.baseattrs + ['full', 'modPath', 'modb',
                                        'modt_p', 'script', 'flags']
    exportattrs = ObFormIDRecord.baseattrs + ['full', 'modPath', 'modb',
                                        'script', 'flags'] #'modt_p', 

class ObGLOBRecord(ObFormIDRecord):
    _Type = 'GLOB'
    CHAR_MACRO(format, 5)
    FLOAT32_MACRO(value, 6)
    exportattrs = copyattrs = ObFormIDRecord.baseattrs + ['format', 'value']

class ObGRASRecord(ObFormIDRecord):
    _Type = 'GRAS'
    ISTRING_MACRO(modPath, 5)
    FLOAT32_MACRO(modb, 6)
    UINT8_ARRAY_MACRO(modt_p, 7)
    UINT8_MACRO(density, 8)
    UINT8_MACRO(minSlope, 9)
    UINT8_MACRO(maxSlope, 10)
    UINT8_ARRAY_MACRO(unused1, 11, 1)
    UINT16_MACRO(waterDistance, 12)
    UINT8_ARRAY_MACRO(unused2, 13, 2)
    UINT32_MACRO(waterOp, 14)
    FLOAT32_MACRO(posRange, 15)
    FLOAT32_MACRO(heightRange, 16)
    FLOAT32_MACRO(colorRange, 17)
    FLOAT32_MACRO(wavePeriod, 18)
    UINT8_FLAG_MACRO(flags, 19)
    UINT8_ARRAY_MACRO(unused3, 20, 3)
    BasicFlagMACRO(IsVLighting, flags, 0x00000001)
    BasicAliasMACRO(IsVertexLighting, IsVLighting)
    BasicFlagMACRO(IsUScaling, flags, 0x00000002)
    BasicAliasMACRO(IsUniformScaling, IsUScaling)
    BasicFlagMACRO(IsFitSlope, flags, 0x00000004)
    BasicAliasMACRO(IsFitToSlope, IsFitSlope)
    copyattrs = ObFormIDRecord.baseattrs + ['modPath', 'modb', 'modt_p', 'density',
                                        'minSlope', 'maxSlope', 'waterDistance',
                                        'waterOp', 'posRange', 'heightRange',
                                        'colorRange', 'wavePeriod', 'flags']
    exportattrs = ObFormIDRecord.baseattrs + ['modPath', 'modb', 'density',
                                        'minSlope', 'maxSlope', 'waterDistance',
                                        'waterOp', 'posRange', 'heightRange',
                                        'colorRange', 'wavePeriod', 'flags'] #'modt_p', 

class ObHAIRRecord(ObFormIDRecord):
    _Type = 'HAIR'
    STRING_MACRO(full, 5)
    ISTRING_MACRO(modPath, 6)
    FLOAT32_MACRO(modb, 7)
    UINT8_ARRAY_MACRO(modt_p, 8)
    ISTRING_MACRO(iconPath, 9)
    UINT8_FLAG_MACRO(flags, 10)
    BasicFlagMACRO(IsPlayable, flags, 0x00000001)
    BasicFlagMACRO(IsNotMale, flags, 0x00000002)
    BasicInvertedFlagMACRO(IsMale, IsNotMale)
    BasicFlagMACRO(IsNotFemale, flags, 0x00000004)
    BasicInvertedFlagMACRO(IsFemale, IsNotFemale)
    BasicFlagMACRO(IsFixedColor, flags, 0x00000008)
    copyattrs = ObFormIDRecord.baseattrs + ['full', 'modPath', 'modb',
                                        'modt_p', 'iconPath', 'flags']
    exportattrs = ObFormIDRecord.baseattrs + ['full', 'modPath', 'modb',
                                        'iconPath', 'flags'] #'modt_p', 

class ObIDLERecord(ObFormIDRecord):
    _Type = 'IDLE'
    ISTRING_MACRO(modPath, 5)
    FLOAT32_MACRO(modb, 6)
    UINT8_ARRAY_MACRO(modt_p, 7)

    LIST_MACRO(conditions, 8, Condition)
    UINT8_FLAG_TYPE_MACRO(group, 9)
    FORMID_MACRO(parent, 10)
    FORMID_MACRO(prevId, 11)
    MaskedTypeMACRO(IsLowerBody, group, 0x0F, 0x00, IsLeftArm)
    MaskedTypeMACRO(IsLeftArm, group, 0x0F, 0x01, IsLowerBody)
    MaskedTypeMACRO(IsLeftHand, group, 0x0F, 0x02, IsLowerBody)
    MaskedTypeMACRO(IsRightArm, group, 0x0F, 0x03, IsLowerBody)
    MaskedTypeMACRO(IsSpecialIdle, group, 0x0F, 0x04, IsLowerBody)
    MaskedTypeMACRO(IsWholeBody, group, 0x0F, 0x05, IsLowerBody)
    MaskedTypeMACRO(IsUpperBody, group, 0x0F, 0x06, IsLowerBody)
    BasicFlagMACRO(IsNotReturnFile, group, 0x80)
    BasicInvertedFlagMACRO(IsReturnFile, IsNotReturnFile)
    copyattrs = ObFormIDRecord.baseattrs + ['modPath', 'modb', 'modt_p',
                                        'conditions_list', 'group', 'parent', 'prevId']
    exportattrs = ObFormIDRecord.baseattrs + ['modPath', 'modb', 'conditions_list', 
                                            'group', 'parent', 'prevId'] # 'modt_p',

class ObINGRRecord(ObFormIDRecord):
    _Type = 'INGR'
    STRING_MACRO(full, 5)
    ISTRING_MACRO(modPath, 6)
    FLOAT32_MACRO(modb, 7)
    UINT8_ARRAY_MACRO(modt_p, 8)
    ISTRING_MACRO(iconPath, 9)
    FORMID_MACRO(script, 10)
    FLOAT32_MACRO(weight, 11)
    SINT32_MACRO(value, 12)
    UINT8_FLAG_MACRO(flags, 13)
    UINT8_ARRAY_MACRO(unused1, 14, 3)

    LIST_MACRO(effects, 15, Effect)
    BasicFlagMACRO(IsNoAutoCalc, flags, 0x00000001)
    BasicFlagMACRO(IsFood, flags, 0x00000002)
    ##OBME Fields. Setting any of the below fields will make the mod require JRoush's OBME plugin for OBSE
    ##To see if OBME is in use, check the recordVersion field for a non-None value
    UINT8_MACRO(recordVersion, 16)
    UINT8_MACRO(betaVersion, 17)
    UINT8_MACRO(minorVersion, 18)
    UINT8_MACRO(majorVersion, 19)
    UINT8_ARRAY_MACRO(reserved, 20, 0x1C)
    UINT8_ARRAY_MACRO(datx_p, 21, 0x20)
    copyattrs = ObFormIDRecord.baseattrs + ['full', 'modPath', 'modb', 'modt_p', 'iconPath',
                                        'script', 'weight', 'value', 'flags',
                                        'effects_list']
    exportattrs = ObFormIDRecord.baseattrs + ['full', 'modPath', 'modb', 'iconPath',
                                        'script', 'weight', 'value', 'flags',
                                        'effects_list'] #'modt_p', 
    copyattrsOBME = copyattrs + ['recordVersion', 'betaVersion',
                                 'minorVersion', 'majorVersion',
                                 'reserved'] #, 'datx_p'

class ObKEYMRecord(ObFormIDRecord):
    _Type = 'KEYM'
    STRING_MACRO(full, 5)
    ISTRING_MACRO(modPath, 6)
    FLOAT32_MACRO(modb, 7)
    UINT8_ARRAY_MACRO(modt_p, 8)
    ISTRING_MACRO(iconPath, 9)
    FORMID_MACRO(script, 10)
    SINT32_MACRO(value, 11)
    FLOAT32_MACRO(weight, 12)
    copyattrs = ObFormIDRecord.baseattrs + ['full', 'modPath', 'modb', 'modt_p', 'iconPath',
                                        'script', 'value', 'weight']
    exportattrs = ObFormIDRecord.baseattrs + ['full', 'modPath', 'modb', 'iconPath',
                                        'script', 'value', 'weight'] #'modt_p', 

class ObLIGHRecord(ObFormIDRecord):
    _Type = 'LIGH'
    ISTRING_MACRO(modPath, 5)
    FLOAT32_MACRO(modb, 6)
    UINT8_ARRAY_MACRO(modt_p, 7)
    FORMID_MACRO(script, 8)
    STRING_MACRO(full, 9)
    ISTRING_MACRO(iconPath, 10)
    SINT32_MACRO(duration, 11)
    UINT32_MACRO(radius, 12)
    UINT8_MACRO(red, 13)
    UINT8_MACRO(green, 14)
    UINT8_MACRO(blue, 15)
    UINT8_ARRAY_MACRO(unused1, 16, 1)
    UINT32_FLAG_MACRO(flags, 17)
    FLOAT32_MACRO(falloff, 18)
    FLOAT32_MACRO(fov, 19)
    UINT32_MACRO(value, 20)
    FLOAT32_MACRO(weight, 21)
    FLOAT32_MACRO(fade, 22)
    FORMID_MACRO(sound, 23)
    BasicFlagMACRO(IsDynamic, flags, 0x00000001)
    BasicFlagMACRO(IsCanTake, flags, 0x00000002)
    BasicFlagMACRO(IsNegative, flags, 0x00000004)
    BasicFlagMACRO(IsFlickers, flags, 0x00000008)
    BasicFlagMACRO(IsOffByDefault, flags, 0x00000020)
    BasicFlagMACRO(IsFlickerSlow, flags, 0x00000040)
    BasicFlagMACRO(IsPulse, flags, 0x00000080)
    BasicFlagMACRO(IsPulseSlow, flags, 0x00000100)
    BasicFlagMACRO(IsSpotLight, flags, 0x00000200)
    BasicFlagMACRO(IsSpotShadow, flags, 0x00000400)
    copyattrs = ObFormIDRecord.baseattrs + ['modPath', 'modb', 'modt_p', 'script', 'full',
                                        'iconPath', 'duration', 'radius', 'red',
                                        'green', 'blue', 'flags', 'falloff', 'fov',
                                        'value', 'weight', 'fade', 'sound']
    exportattrs = ObFormIDRecord.baseattrs + ['modPath', 'modb', 'script', 'full',
                                        'iconPath', 'duration', 'radius', 'red',
                                        'green', 'blue', 'flags', 'falloff', 'fov',
                                        'value', 'weight', 'fade', 'sound'] #'modt_p', 

class ObLSCRRecord(ObFormIDRecord):
    _Type = 'LSCR'
    class Location(ListComponent):
        FORMID_LISTMACRO(direct, 7, 1)
        FORMID_LISTMACRO(indirect, 7, 2)
        SINT16_LISTMACRO(gridY, 7, 3)
        SINT16_LISTMACRO(gridX, 7, 4)
        exportattrs = copyattrs = ['direct', 'indirect', 'gridY', 'gridX']

    ISTRING_MACRO(iconPath, 5)
    STRING_MACRO(text, 6)

    LIST_MACRO(locations, 7, self.Location)
    exportattrs = copyattrs = ObFormIDRecord.baseattrs + ['iconPath', 'text', 'locations_list']

class ObLTEXRecord(ObFormIDRecord):
    _Type = 'LTEX'
    ISTRING_MACRO(iconPath, 5)
    UINT8_FLAG_MACRO(flags, 6)
    UINT8_MACRO(friction, 7)
    UINT8_MACRO(restitution, 8)
    UINT8_MACRO(specular, 9)
    FORMID_ARRAY_MACRO(grass, 10)
    BasicFlagMACRO(IsStone, flags, 0x00000001)
    BasicFlagMACRO(IsCloth, flags, 0x00000002)
    BasicFlagMACRO(IsDirt, flags, 0x00000004)
    BasicFlagMACRO(IsGlass, flags, 0x00000008)
    BasicFlagMACRO(IsGrass, flags, 0x00000010)
    BasicFlagMACRO(IsMetal, flags, 0x00000020)
    BasicFlagMACRO(IsOrganic, flags, 0x00000040)
    BasicFlagMACRO(IsSkin, flags, 0x00000080)
    BasicFlagMACRO(IsWater, flags, 0x00000100)
    BasicFlagMACRO(IsWood, flags, 0x00000200)
    BasicFlagMACRO(IsHeavyStone, flags, 0x00000400)
    BasicFlagMACRO(IsHeavyMetal, flags, 0x00000800)
    BasicFlagMACRO(IsHeavyWood, flags, 0x00001000)
    BasicFlagMACRO(IsChain, flags, 0x00002000)
    BasicFlagMACRO(IsSnow, flags, 0x00004000)
    exportattrs = copyattrs = ObFormIDRecord.baseattrs + ['iconPath', 'flags', 'friction', 'restitution',
                                        'specular', 'grass']

class ObLVLCRecord(ObFormIDRecord):
    _Type = 'LVLC'
    class Entry(ListComponent):
        SINT16_LISTMACRO(level, 9, 1)
        UINT8_ARRAY_LISTMACRO(unused1, 9, 2, 2)
        FORMID_LISTMACRO(listId, 9, 3)
        SINT16_LISTMACRO(count, 9, 4)
        UINT8_ARRAY_LISTMACRO(unused2, 9, 5, 2)
        exportattrs = copyattrs = ['level', 'listId', 'count']

    def mergeFilter(self,modSet):
        """Filter out items that don't come from specified modSet."""
        self.entries = [entry for entry in self.entries if entry.listId[0] in modSet]

    UINT8_MACRO(chanceNone, 5)
    UINT8_FLAG_MACRO(flags, 6)
    FORMID_MACRO(script, 7)
    FORMID_MACRO(template, 8)

    LIST_MACRO(entries, 9, self.Entry)
    BasicFlagMACRO(IsCalcFromAllLevels, flags, 0x00000001)
    BasicFlagMACRO(IsCalcForEachItem, flags, 0x00000002)
    BasicFlagMACRO(IsUseAllSpells, flags, 0x00000004)
    exportattrs = copyattrs = ObFormIDRecord.baseattrs + ['chanceNone', 'flags', 'script',
                                        'template', 'entries_list']

class ObLVLIRecord(ObFormIDRecord):
    _Type = 'LVLI'
    class Entry(ListComponent):
        SINT16_LISTMACRO(level, 9, 1)
        UINT8_ARRAY_LISTMACRO(unused1, 9, 2, 2)
        FORMID_LISTMACRO(listId, 9, 3)
        SINT16_LISTMACRO(count, 9, 4)
        UINT8_ARRAY_LISTMACRO(unused2, 9, 5, 2)
        exportattrs = copyattrs = ['level', 'listId', 'count']

    def mergeFilter(self,modSet):
        """Filter out items that don't come from specified modSet."""
        self.entries = [entry for entry in self.entries if entry.listId[0] in modSet]

    UINT8_MACRO(chanceNone, 5)
    UINT8_FLAG_MACRO(flags, 6)

    LIST_MACRO(entries, 9, self.Entry)
    BasicFlagMACRO(IsCalcFromAllLevels, flags, 0x00000001)
    BasicFlagMACRO(IsCalcForEachItem, flags, 0x00000002)
    BasicFlagMACRO(IsUseAllSpells, flags, 0x00000004)
    exportattrs = copyattrs = ObFormIDRecord.baseattrs + ['chanceNone', 'flags', 'entries_list']

class ObLVSPRecord(ObFormIDRecord):
    _Type = 'LVSP'
    class Entry(ListComponent):
        SINT16_LISTMACRO(level, 9, 1)
        UINT8_ARRAY_LISTMACRO(unused1, 9, 2, 2)
        FORMID_LISTMACRO(listId, 9, 3)
        SINT16_LISTMACRO(count, 9, 4)
        UINT8_ARRAY_LISTMACRO(unused2, 9, 5, 2)
        exportattrs = copyattrs = ['level', 'listId', 'count']

    def mergeFilter(self,modSet):
        """Filter out items that don't come from specified modSet."""
        self.entries = [entry for entry in self.entries if entry.listId[0] in modSet]

    UINT8_MACRO(chanceNone, 5)
    UINT8_FLAG_MACRO(flags, 6)

    LIST_MACRO(entries, 9, self.Entry)
    BasicFlagMACRO(IsCalcFromAllLevels, flags, 0x00000001)
    BasicFlagMACRO(IsCalcForEachItem, flags, 0x00000002)
    BasicFlagMACRO(IsUseAllSpells, flags, 0x00000004)
    exportattrs = copyattrs = ObFormIDRecord.baseattrs + ['chanceNone', 'flags', 'entries_list']

class ObMGEFRecord(ObEditorIDRecord):
    _Type = 'MGEF'
    STRING_EDIDMACRO(full, 5)
    STRING_EDIDMACRO(text, 6)
    ISTRING_EDIDMACRO(iconPath, 7)
    ISTRING_EDIDMACRO(modPath, 8)
    FLOAT32_EDIDMACRO(modb, 9)
    UINT8_ARRAY_EDIDMACRO(modt_p, 10)
    UINT32_FLAG_EDIDMACRO(flags, 11)
    FLOAT32_EDIDMACRO(baseCost, 12)
    FORMID_EDIDMACRO(associated, 13)
    SINT32_EDIDMACRO(school, 14)
    ##0xFFFFFFFF is None for resistValue
    UINT32_EDIDMACRO(resistValue, 15)
    UINT16_EDIDMACRO(numCounters, 16)
    UINT8_ARRAY_EDIDMACRO(unused1, 17)
    FORMID_EDIDMACRO(light, 18)
    FLOAT32_EDIDMACRO(projectileSpeed, 19)
    FORMID_EDIDMACRO(effectShader, 20)
    FORMID_EDIDMACRO(enchantEffect, 21)
    FORMID_EDIDMACRO(castingSound, 22)
    FORMID_EDIDMACRO(boltSound, 23)
    FORMID_EDIDMACRO(hitSound, 24)
    FORMID_EDIDMACRO(areaSound, 25)
    FLOAT32_EDIDMACRO(cefEnchantment, 26)
    FLOAT32_EDIDMACRO(cefBarter, 27)
    MGEFCODE_OR_UINT32_ARRAY_EDIDMACRO(counterEffects, 28)
    #Note: the vanilla code discards mod changes to most flag bits
    #  only those listed as changeable below may be edited by non-obme mods
    # comments garnered from JRoush's OBME
    BasicFlagMACRO(IsHostile, flags, 0x00000001)
    BasicFlagMACRO(IsRecover, flags, 0x00000002)
    BasicFlagMACRO(IsDetrimental, flags, 0x00000004) #OBME Deprecated, used for ValueModifier effects AV is decreased rather than increased
    BasicFlagMACRO(IsMagnitudeIsPercent, flags, 0x00000008) #OBME Deprecated
    BasicFlagMACRO(IsSelf, flags, 0x00000010)
    BasicFlagMACRO(IsTouch, flags, 0x00000020)
    BasicFlagMACRO(IsTarget, flags, 0x00000040)
    BasicFlagMACRO(IsNoDuration, flags, 0x00000080)
    BasicFlagMACRO(IsNoMagnitude, flags, 0x00000100)
    BasicFlagMACRO(IsNoArea, flags, 0x00000200)
    BasicFlagMACRO(IsFXPersist, flags, 0x00000400) #Changeable
    BasicFlagMACRO(IsSpellmaking, flags, 0x00000800) #Changeable
    BasicFlagMACRO(IsEnchanting, flags, 0x00001000) #Changeable
    BasicFlagMACRO(IsNoIngredient, flags, 0x00002000) #Changeable
    BasicFlagMACRO(IsUnknownF, flags, 0x00004000) #no effects have this flag set
    BasicFlagMACRO(IsNoRecast, flags, 0x00008000) #no effects have this flag set
    BasicFlagMACRO(IsUseWeapon, flags, 0x00010000) #OBME Deprecated
    BasicFlagMACRO(IsUseArmor, flags, 0x00020000) #OBME Deprecated
    BasicFlagMACRO(IsUseCreature, flags, 0x00040000) #OBME Deprecated
    BasicFlagMACRO(IsUseSkill, flags, 0x00080000) #OBME Deprecated
    BasicFlagMACRO(IsUseAttr, flags, 0x00100000) #OBME Deprecated
    BasicFlagMACRO(IsPCHasEffect, flags, 0x00200000) #whether or not PC has effect, forced to zero during loading
    BasicFlagMACRO(IsDisabled, flags, 0x00400000) #Changeable, many if not all methods that loop over effects ignore those with this flag.
                                                    #  Spells with an effect with this flag are apparently uncastable.
    BasicFlagMACRO(IsUnknownO, flags, 0x00800000) #Changeable, POSN,DISE - these effects have *only* this bit set,
                                                    #  perhaps a flag for meta effects
    BasicFlagMACRO(IsUseAV, flags, 0x01000000) #OBME Deprecated, Changeable, but once set by default or by a previously loaded mod file
                                                    #  it cannot be unset by another mod, nor can the mgefParam be overriden

    MaskedTypeMACRO(IsBallType, flags, 0x06000000, 0, IsBoltType)  #Changeable
    MaskedTypeMACRO(IsFogType, flags, 0x06000000, 0x06000000, IsBallType)  #Changeable

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

    BasicFlagMACRO(IsFogType, flags, 0x06000000) #Changeable
    BasicFlagMACRO(IsNoHitEffect, flags, 0x08000000) #Changeable, no hit shader on target
    BasicFlagMACRO(IsPersistOnDeath, flags, 0x10000000) #Effect is not automatically removed when its target dies
    BasicFlagMACRO(IsExplodesWithForce, flags, 0x20000000) #causes explosion that can move loose objects (e.g. ragdolls)
    BasicFlagMACRO(IsMagnitudeIsLevel, flags, 0x40000000) #OBME Deprecated
    BasicFlagMACRO(IsMagnitudeIsFeet, flags, 0x80000000)  #OBME Deprecated
    ##OBME Fields. Setting any of the below fields will make the mod require JRoush's OBME plugin for OBSE
    ##To see if OBME is in use, check the recordVersion field for a non-None value
    OBMEUINT8_EDIDMACRO(recordVersion, 29)
    OBMEUINT8_EDIDMACRO(betaVersion, 30)
    OBMEUINT8_EDIDMACRO(minorVersion, 31)
    OBMEUINT8_EDIDMACRO(majorVersion, 32)
    OBMEUINT8_EDIDMACRO(mgefParamAInfo, 33)
    OBMEUINT8_EDIDMACRO(mgefParamBInfo, 34)
    OBMEUINT8_ARRAY_EDIDMACRO(reserved1, 35, 0x2)
    OBMEUINT32_EDIDMACRO(handlerCode, 36)
    OBMEUINT32_FLAG_EDIDMACRO(OBMEFlags, 37)
    OBMEUINT32_EDIDMACRO(mgefParamB, 38)
    OBMEUINT8_ARRAY_EDIDMACRO(reserved2, 39, 0x1C)
    OBMEMGEFCODE_EDIDMACRO(mgefCode, 40)
    OBMEUINT8_ARRAY_EDIDMACRO(datx_p, 41, 0x20)
    OBMEBasicFlagMACRO(IsBeneficial, OBMEFlags, 0x00000008)
    OBMEBasicFlagMACRO(IsMagnitudeIsRange, OBMEFlags, 0x00020000)
    OBMEBasicFlagMACRO(IsAtomicResistance, OBMEFlags, 0x00040000)
    OBMEBasicFlagMACRO(IsParamFlagA, OBMEFlags, 0x00000004) //Meaning varies with effect handler
    OBMEBasicFlagMACRO(IsParamFlagB, OBMEFlags, 0x00010000) //Meaning varies with effect handler
    OBMEBasicFlagMACRO(IsParamFlagC, OBMEFlags, 0x00080000) //Meaning varies with effect handler
    OBMEBasicFlagMACRO(IsParamFlagD, OBMEFlags, 0x00100000) //Meaning varies with effect handler
    OBMEBasicFlagMACRO(IsHidden, OBMEFlags, 0x40000000)
    copyattrs = ObEditorIDRecord.baseattrs + ['full', 'text', 'iconPath', 'modPath',
                                          'modb', 'modt_p', 'flags', 'baseCost',
                                          'associated', 'school', 'resistValue',
                                          'numCounters', 'light', 'projectileSpeed',
                                          'effectShader', 'enchantEffect',
                                          'castingSound', 'boltSound', 'hitSound',
                                          'areaSound', 'cefEnchantment', 'cefBarter',
                                          'counterEffects']
    exportattrs = ObEditorIDRecord.baseattrs + ['full', 'text', 'iconPath', 'modPath',
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

class ObMISCRecord(ObFormIDRecord):
    _Type = 'MISC'
    STRING_MACRO(full, 5)
    ISTRING_MACRO(modPath, 6)
    FLOAT32_MACRO(modb, 7)
    UINT8_ARRAY_MACRO(modt_p, 8)
    ISTRING_MACRO(iconPath, 9)
    FORMID_MACRO(script, 10)
    SINT32_MACRO(value, 11)
    FLOAT32_MACRO(weight, 12)
    copyattrs = ObFormIDRecord.baseattrs + ['full', 'modPath', 'modb', 'modt_p', 'iconPath',
                                        'script', 'value', 'weight']
    exportattrs = ObFormIDRecord.baseattrs + ['full', 'modPath', 'modb', 'iconPath',
                                        'script', 'value', 'weight'] #'modt_p', 

class ObNPC_Record(ObFormIDRecord):
    _Type = 'NPC_'
    def mergeFilter(self,modSet):
        """Filter out items that don't come from specified modSet.
        Filters spells, factions and items."""
        self.spells = [x for x in self.spells if x[0] in modSet]
        self.factions = [x for x in self.factions if x.faction[0] in modSet]
        self.items = [x for x in self.items if x.item[0] in modSet]

    STRING_MACRO(full, 5)
    ISTRING_MACRO(modPath, 6)
    FLOAT32_MACRO(modb, 7)
    UINT8_ARRAY_MACRO(modt_p, 8)
    UINT32_FLAG_MACRO(flags, 9)
    UINT16_MACRO(baseSpell, 10)
    UINT16_MACRO(fatigue, 11)
    UINT16_MACRO(barterGold, 12)
    SINT16_MACRO(level, 13)
    UINT16_MACRO(calcMin, 14)
    UINT16_MACRO(calcMax, 15)

    LIST_MACRO(factions, 16, Faction)
    FORMID_MACRO(deathItem, 17)
    FORMID_MACRO(race, 18)
    FORMID_ARRAY_MACRO(spells, 19)
    FORMID_MACRO(script, 20)

    LIST_MACRO(items, 21, Item)
    UINT8_MACRO(aggression, 22)
    UINT8_MACRO(confidence, 23)
    UINT8_MACRO(energyLevel, 24)
    UINT8_MACRO(responsibility, 25)
    UINT32_FLAG_MACRO(services, 26)
    SINT8_MACRO(trainSkill, 27)
    UINT8_MACRO(trainLevel, 28)
    UINT8_ARRAY_MACRO(unused1, 29, 2)
    FORMID_ARRAY_MACRO(aiPackages, 30)
    ISTRING_ARRAY_MACRO(animations, 31)
    FORMID_MACRO(iclass, 32)
    UINT8_MACRO(armorer, 33)
    UINT8_MACRO(athletics, 34)
    UINT8_MACRO(blade, 35)
    UINT8_MACRO(block, 36)
    UINT8_MACRO(blunt, 37)
    UINT8_MACRO(h2h, 38)
    UINT8_MACRO(heavyArmor, 39)
    UINT8_MACRO(alchemy, 40)
    UINT8_MACRO(alteration, 41)
    UINT8_MACRO(conjuration, 42)
    UINT8_MACRO(destruction, 43)
    UINT8_MACRO(illusion, 44)
    UINT8_MACRO(mysticism, 45)
    UINT8_MACRO(restoration, 46)
    UINT8_MACRO(acrobatics, 47)
    UINT8_MACRO(lightArmor, 48)
    UINT8_MACRO(marksman, 49)
    UINT8_MACRO(mercantile, 50)
    UINT8_MACRO(security, 51)
    UINT8_MACRO(sneak, 52)
    UINT8_MACRO(speechcraft, 53)
    UINT16_MACRO(health, 54)
    UINT8_ARRAY_MACRO(unused2, 55, 2)
    UINT8_MACRO(strength, 56)
    UINT8_MACRO(intelligence, 57)
    UINT8_MACRO(willpower, 58)
    UINT8_MACRO(agility, 59)
    UINT8_MACRO(speed, 60)
    UINT8_MACRO(endurance, 61)
    UINT8_MACRO(personality, 62)
    UINT8_MACRO(luck, 63)
    FORMID_MACRO(hair, 64)
    FLOAT32_MACRO(hairLength, 65)
    FORMID_MACRO(eye, 66)
    UINT8_MACRO(hairRed, 67)
    UINT8_MACRO(hairGreen, 68)
    UINT8_MACRO(hairBlue, 69)
    UINT8_ARRAY_MACRO(unused3, 70, 1)
    FORMID_MACRO(combatStyle, 71)
    UINT8_ARRAY_MACRO(fggs_p, 72, 200)
    UINT8_ARRAY_MACRO(fgga_p, 73, 120)
    UINT8_ARRAY_MACRO(fgts_p, 74, 200)
    UINT16_MACRO(fnam, 75)
    BasicFlagMACRO(IsFemale, flags, 0x00000001)
    BasicInvertedFlagMACRO(IsMale, IsFemale)
    BasicFlagMACRO(IsEssential, flags, 0x00000002)
    BasicFlagMACRO(IsRespawn, flags, 0x00000008)
    BasicFlagMACRO(IsAutoCalc, flags, 0x00000010)
    BasicFlagMACRO(IsPCLevelOffset, flags, 0x00000080)
    BasicFlagMACRO(IsNoLowLevel, flags, 0x00000200)
    BasicInvertedFlagMACRO(IsLowLevel, IsNoLowLevel)
    BasicFlagMACRO(IsNoRumors, flags, 0x00002000)
    BasicInvertedFlagMACRO(IsRumors, IsNoRumors)
    BasicFlagMACRO(IsSummonable, flags, 0x00004000)
    BasicFlagMACRO(IsNoPersuasion, flags, 0x00008000)
    BasicInvertedFlagMACRO(IsPersuasion, IsNoPersuasion)
    BasicFlagMACRO(IsCanCorpseCheck, flags, 0x00100000)
    BasicFlagMACRO(IsServicesWeapons, services, 0x00000001)
    BasicFlagMACRO(IsServicesArmor, services, 0x00000002)
    BasicFlagMACRO(IsServicesClothing, services, 0x00000004)
    BasicFlagMACRO(IsServicesBooks, services, 0x00000008)
    BasicFlagMACRO(IsServicesIngredients, services, 0x00000010)
    BasicFlagMACRO(IsServicesLights, services, 0x00000080)
    BasicFlagMACRO(IsServicesApparatus, services, 0x00000100)
    BasicFlagMACRO(IsServicesMiscItems, services, 0x00000400)
    BasicFlagMACRO(IsServicesSpells, services, 0x00000800)
    BasicFlagMACRO(IsServicesMagicItems, services, 0x00001000)
    BasicFlagMACRO(IsServicesPotions, services, 0x00002000)
    BasicFlagMACRO(IsServicesTraining, services, 0x00004000)
    BasicFlagMACRO(IsServicesRecharge, services, 0x00010000)
    BasicFlagMACRO(IsServicesRepair, services, 0x00020000)
    copyattrs = ObFormIDRecord.baseattrs + ['full', 'modPath', 'modb', 'modt_p',
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
    exportattrs = ObFormIDRecord.baseattrs + ['full', 'modPath', 'modb',
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

class ObPACKRecord(ObFormIDRecord):
    _Type = 'PACK'
    UINT32_FLAG_MACRO(flags, 5)
    UINT8_TYPE_MACRO(aiType, 6)
    UINT8_ARRAY_MACRO(unused1, 7, 3)
    SINT32_TYPE_MACRO(locType, 8)
    FORMID_OR_UINT32_MACRO(locId, 9)
    SINT32_MACRO(locRadius, 10)
    SINT8_MACRO(month, 11)
    SINT8_MACRO(day, 12)
    UINT8_MACRO(date, 13)
    SINT8_MACRO(time, 14)
    SINT32_MACRO(duration, 15)
    SINT32_TYPE_MACRO(targetType, 16)
    FORMID_OR_UINT32_MACRO(targetId, 17)
    SINT32_MACRO(targetCount, 18)

    LIST_MACRO(conditions, 19, Condition)
    BasicFlagMACRO(IsOffersServices, flags, 0x00000001)
    BasicFlagMACRO(IsMustReachLocation, flags, 0x00000002)
    BasicFlagMACRO(IsMustComplete, flags, 0x00000004)
    BasicFlagMACRO(IsLockAtStart, flags, 0x00000008)
    BasicFlagMACRO(IsLockAtEnd, flags, 0x00000010)
    BasicFlagMACRO(IsLockAtLocation, flags, 0x00000020)
    BasicFlagMACRO(IsUnlockAtStart, flags, 0x00000040)
    BasicFlagMACRO(IsUnlockAtEnd, flags, 0x00000080)
    BasicFlagMACRO(IsUnlockAtLocation, flags, 0x00000100)
    BasicFlagMACRO(IsContinueIfPcNear, flags, 0x00000200)
    BasicFlagMACRO(IsOncePerDay, flags, 0x00000400)
    BasicFlagMACRO(IsSkipFallout, flags, 0x00001000)
    BasicFlagMACRO(IsAlwaysRun, flags, 0x00002000)
    BasicFlagMACRO(IsAlwaysSneak, flags, 0x00020000)
    BasicFlagMACRO(IsAllowSwimming, flags, 0x00040000)
    BasicFlagMACRO(IsAllowFalls, flags, 0x00080000)
    BasicFlagMACRO(IsUnequipArmor, flags, 0x00100000)
    BasicFlagMACRO(IsUnequipWeapons, flags, 0x00200000)
    BasicFlagMACRO(IsDefensiveCombat, flags, 0x00400000)
    BasicFlagMACRO(IsUseHorse, flags, 0x00800000)
    BasicFlagMACRO(IsNoIdleAnims, flags, 0x01000000)
    BasicTypeMACRO(IsAIFind, aiType, 0, IsAIFollow)
    BasicTypeMACRO(IsAIFollow, aiType, 1, IsAIFind)
    BasicTypeMACRO(IsAIEscort, aiType, 2, IsAIFind)
    BasicTypeMACRO(IsAIEat, aiType, 3, IsAIFind)
    BasicTypeMACRO(IsAISleep, aiType, 4, IsAIFind)
    BasicTypeMACRO(IsAIWander, aiType, 5, IsAIFind)
    BasicTypeMACRO(IsAITravel, aiType, 6, IsAIFind)
    BasicTypeMACRO(IsAIAccompany, aiType, 7, IsAIFind)
    BasicTypeMACRO(IsAIUseItemAt, aiType, 8, IsAIFind)
    BasicTypeMACRO(IsAIAmbush, aiType, 9, IsAIFind)
    BasicTypeMACRO(IsAIFleeNotCombat, aiType, 10, IsAIFind)
    BasicTypeMACRO(IsAICastMagic, aiType, 11, IsAIFind)
    BasicTypeMACRO(IsLocNearReference, locType, 0, IsLocInCell)
    BasicTypeMACRO(IsLocInCell, locType, 1, IsLocNearReference)
    BasicTypeMACRO(IsLocNearCurrentLocation, locType, 2, IsLocNearReference)
    BasicTypeMACRO(IsLocNearEditorLocation, locType, 3, IsLocNearReference)
    BasicTypeMACRO(IsLocObjectID, locType, 4, IsLocNearReference)
    BasicTypeMACRO(IsLocObjectType, locType, 5, IsLocNearReference)
    BasicTypeMACRO(IsTargetReference, locType, 0, IsTargetObjectID)
    BasicTypeMACRO(IsTargetObjectID, locType, 1, IsTargetReference)
    BasicTypeMACRO(IsTargetObjectType, locType, 2, IsTargetReference)
    exportattrs = copyattrs = ObFormIDRecord.baseattrs + ['flags', 'aiType', 'locType', 'locId',
                                        'locRadius', 'month', 'day', 'date', 'time',
                                        'duration', 'targetType', 'targetId',
                                        'targetCount', 'conditions_list']

class ObQUSTRecord(ObFormIDRecord):
    _Type = 'QUST'
    class Stage(ListComponent):
        class Entry(ListX2Component):
            class ConditionX3(ListX3Component):
                UINT8_FLAG_TYPE_LISTX3MACRO(operType, 11, 2, 2, 1)
                UINT8_ARRAY_LISTX3MACRO(unused1, 11, 2, 2, 2, 3)
                FLOAT32_LISTX3MACRO(compValue, 11, 2, 2, 3)
                UINT32_TYPE_LISTX3MACRO(ifunc, 11, 2, 2, 4)
                UNKNOWN_OR_FORMID_OR_UINT32_LISTX3MACRO(param1, 11, 2, 2, 5)
                UNKNOWN_OR_FORMID_OR_UINT32_LISTX3MACRO(param2, 11, 2, 2, 6)
                UINT8_ARRAY_LISTX3MACRO(unused2, 11, 2, 2, 7, 4)
                MaskedTypeMACRO(IsEqual, operType, 0xF0, 0x00, IsNotEqual)
                MaskedTypeMACRO(IsNotEqual, operType, 0xF0, 0x20, IsEqual)
                MaskedTypeMACRO(IsGreater, operType, 0xF0, 0x40, IsEqual)
                MaskedTypeMACRO(IsGreaterOrEqual, operType, 0xF0, 0x60, IsEqual)
                MaskedTypeMACRO(IsLess, operType, 0xF0, 0x80, IsEqual)
                MaskedTypeMACRO(IsLessOrEqual, operType, 0xF0, 0xA0, IsEqual)
                BasicFlagMACRO(IsOr, operType, 0x01)
                BasicFlagMACRO(IsRunOnTarget, operType, 0x02)
                BasicFlagMACRO(IsUseGlobal, operType, 0x04)
                exportattrs = copyattrs = ['operType', 'compValue', 'ifunc', 'param1',
                             'param2']

            UINT8_FLAG_LISTX2MACRO(flags, 11, 2, 1)

            LIST_LISTX2MACRO(conditions, 11, 2, 2, self.ConditionX3)
            STRING_LISTX2MACRO(text, 11, 2, 3)
            UINT8_ARRAY_LISTX2MACRO(unused1, 11, 2, 4, 4)
            UINT32_LISTX2MACRO(numRefs, 11, 2, 5)
            UINT32_LISTX2MACRO(compiledSize, 11, 2, 6)
            UINT32_LISTX2MACRO(lastIndex, 11, 2, 7)
            UINT32_LISTX2MACRO(scriptType, 11, 2, 8)
            UINT8_ARRAY_LISTX2MACRO(compiled_p, 11, 2, 9)
            ISTRING_LISTX2MACRO(scriptText, 11, 2, 10)
            FORMID_OR_UINT32_ARRAY_LISTX2MACRO(references, 11, 2, 11)
            BasicFlagMACRO(IsCompletes, flags, 0x00000001)
            copyattrs = ['flags', 'conditions_list', 'text', 'numRefs', 'compiledSize',
                         'lastIndex', 'scriptType', 'compiled_p', 'scriptText',
                         'references']
            exportattrs = ['flags', 'conditions_list', 'text', 'numRefs', 'compiledSize',
                         'lastIndex', 'scriptType', 'scriptText',
                         'references'] #'compiled_p', 

        UINT16_LISTMACRO(stage, 11, 1)

        LIST_LISTMACRO(entries, 11, 2, self.Entry)
        exportattrs = copyattrs = ['stage', 'entries_list']

    class Target(ListComponent):
        class ConditionX2(ListX2Component):
            UINT8_FLAG_TYPE_LISTX2MACRO(operType, 12, 4, 1)
            UINT8_ARRAY_LISTX2MACRO(unused1, 12, 4, 2, 3)
            FLOAT32_LISTX2MACRO(compValue, 12, 4, 3)
            UINT32_TYPE_LISTX2MACRO(ifunc, 12, 4, 4)
            UNKNOWN_OR_FORMID_OR_UINT32_LISTX2MACRO(param1, 12, 4, 5)
            UNKNOWN_OR_FORMID_OR_UINT32_LISTX2MACRO(param2, 12, 4, 6)
            UINT8_ARRAY_LISTX2MACRO(unused2, 12, 4, 7, 4)
            MaskedTypeMACRO(IsEqual, operType, 0xF0, 0x00, IsNotEqual)
            MaskedTypeMACRO(IsNotEqual, operType, 0xF0, 0x20, IsEqual)
            MaskedTypeMACRO(IsGreater, operType, 0xF0, 0x40, IsEqual)
            MaskedTypeMACRO(IsGreaterOrEqual, operType, 0xF0, 0x60, IsEqual)
            MaskedTypeMACRO(IsLess, operType, 0xF0, 0x80, IsEqual)
            MaskedTypeMACRO(IsLessOrEqual, operType, 0xF0, 0xA0, IsEqual)
            BasicFlagMACRO(IsOr, operType, 0x01)
            BasicFlagMACRO(IsRunOnTarget, operType, 0x02)
            BasicFlagMACRO(IsUseGlobal, operType, 0x04)
            exportattrs = copyattrs = ['operType', 'compValue', 'ifunc', 'param1',
                         'param2']

        FORMID_LISTMACRO(targetId, 12, 1)
        UINT8_FLAG_LISTMACRO(flags, 12, 2)
        UINT8_ARRAY_LISTMACRO(unused1, 12, 3)

        LIST_LISTMACRO(conditions, 12, 4, self.ConditionX2)
        BasicFlagMACRO(IsIgnoresLocks, flags, 0x00000001)
        exportattrs = copyattrs = ['targetId', 'flags', 'conditions_list']

    FORMID_MACRO(script, 5)
    STRING_MACRO(full, 6)
    ISTRING_MACRO(iconPath, 7)
    UINT8_FLAG_MACRO(flags, 8)
    UINT8_MACRO(priority, 9)

    LIST_MACRO(conditions, 10, Condition)
    LIST_MACRO(stages, 11, self.Stage)
    LIST_MACRO(targets, 12, self.Target)
    BasicFlagMACRO(IsStartEnabled, flags, 0x00000001)
    BasicFlagMACRO(IsRepeatedTopics, flags, 0x00000004)
    BasicFlagMACRO(IsRepeatedStages, flags, 0x00000008)
    exportattrs = copyattrs = ObFormIDRecord.baseattrs + ['script', 'full', 'iconPath',
                                        'flags', 'priority', 'conditions_list',
                                        'stages_list', 'targets_list']

class ObRACERecord(ObFormIDRecord):
    _Type = 'RACE'
    class RaceModel(BaseComponent):
        ISTRING_GROUPEDMACRO(modPath, 0)
        FLOAT32_GROUPEDMACRO(modb, 1)
        ISTRING_GROUPEDMACRO(iconPath, 2)
        UINT8_ARRAY_GROUPEDMACRO(modt_p, 3)
        copyattrs = ['modPath', 'modb', 'iconPath', 'modt_p']
        exportattrs = ['modPath', 'modb', 'iconPath']#, 'modt_p']

    STRING_MACRO(full, 5)
    STRING_MACRO(text, 6)
    FORMID_ARRAY_MACRO(spells, 7)

    LIST_MACRO(relations, 8, Relation)
    SINT8_MACRO(skill1, 9)
    SINT8_MACRO(skill1Boost, 10)
    SINT8_MACRO(skill2, 11)
    SINT8_MACRO(skill2Boost, 12)
    SINT8_MACRO(skill3, 13)
    SINT8_MACRO(skill3Boost, 14)
    SINT8_MACRO(skill4, 15)
    SINT8_MACRO(skill4Boost, 16)
    SINT8_MACRO(skill5, 17)
    SINT8_MACRO(skill5Boost, 18)
    SINT8_MACRO(skill6, 19)
    SINT8_MACRO(skill6Boost, 20)
    SINT8_MACRO(skill7, 21)
    SINT8_MACRO(skill7Boost, 22)
    UINT8_ARRAY_MACRO(unused1, 23, 2)
    FLOAT32_MACRO(maleHeight, 24)
    FLOAT32_MACRO(femaleHeight, 25)
    FLOAT32_MACRO(maleWeight, 26)
    FLOAT32_MACRO(femaleWeight, 27)
    UINT32_MACRO(flags, 28)
    FORMID_MACRO(maleVoice, 29)
    FORMID_MACRO(femaleVoice, 30)
    FORMID_MACRO(defaultHairMale, 31)
    FORMID_MACRO(defaultHairFemale, 32)
    UINT8_MACRO(defaultHairColor, 33)
    FLOAT32_MACRO(mainClamp, 34)
    FLOAT32_MACRO(faceClamp, 35)
    UINT8_MACRO(maleStrength, 36)
    UINT8_MACRO(maleIntelligence, 37)
    UINT8_MACRO(maleWillpower, 38)
    UINT8_MACRO(maleAgility, 39)
    UINT8_MACRO(maleSpeed, 40)
    UINT8_MACRO(maleEndurance, 41)
    UINT8_MACRO(malePersonality, 42)
    UINT8_MACRO(maleLuck, 43)
    UINT8_MACRO(femaleStrength, 44)
    UINT8_MACRO(femaleIntelligence, 45)
    UINT8_MACRO(femaleWillpower, 46)
    UINT8_MACRO(femaleAgility, 47)
    UINT8_MACRO(femaleSpeed, 48)
    UINT8_MACRO(femaleEndurance, 49)
    UINT8_MACRO(femalePersonality, 50)
    UINT8_MACRO(femaleLuck, 51)
    GroupedValuesMACRO(head, 52, RaceModel)
    GroupedValuesMACRO(maleEars, 56, RaceModel)
    GroupedValuesMACRO(femaleEars, 60, RaceModel)
    GroupedValuesMACRO(mouth, 64, RaceModel)
    GroupedValuesMACRO(teethLower, 68, RaceModel)
    GroupedValuesMACRO(teethUpper, 72, RaceModel)
    GroupedValuesMACRO(tongue, 76, RaceModel)
    GroupedValuesMACRO(leftEye, 80, RaceModel)
    GroupedValuesMACRO(rightEye, 84, RaceModel)
    GroupedValuesMACRO(maleTail, 88, Model)
    ISTRING_MACRO(maleUpperBodyPath, 91)
    ISTRING_MACRO(maleLowerBodyPath, 92)
    ISTRING_MACRO(maleHandPath, 93)
    ISTRING_MACRO(maleFootPath, 94)
    ISTRING_MACRO(maleTailPath, 95)
    GroupedValuesMACRO(femaleTail, 96, Model)
    ISTRING_MACRO(femaleUpperBodyPath, 99)
    ISTRING_MACRO(femaleLowerBodyPath, 100)
    ISTRING_MACRO(femaleHandPath, 101)
    ISTRING_MACRO(femaleFootPath, 102)
    ISTRING_MACRO(femaleTailPath, 103)
    FORMID_ARRAY_MACRO(hairs, 104)
    FORMID_ARRAY_MACRO(eyes, 105)
    UINT8_ARRAY_MACRO(fggs_p, 106, 200)
    UINT8_ARRAY_MACRO(fgga_p, 107, 120)
    UINT8_ARRAY_MACRO(fgts_p, 108, 200)
    UINT8_ARRAY_MACRO(snam_p, 109, 2)
    BasicFlagMACRO(IsPlayable, flags, 0x00000001)
    copyattrs = ObFormIDRecord.baseattrs + ['full', 'text', 'spells',
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
    exportattrs = ObFormIDRecord.baseattrs + ['full', 'text', 'spells',
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

class ObREGNRecord(ObFormIDRecord):
    _Type = 'REGN'
    class Area(ListComponent):
        class Point(ListX2Component):
            FLOAT32_LISTX2MACRO(posX, 11, 2, 1)
            FLOAT32_LISTX2MACRO(posY, 11, 2, 2)
            exportattrs = copyattrs = ['posX', 'posY']

        FORMID_LISTMACRO(edgeFalloff, 11, 1)

        LIST_LISTMACRO(points, 11, 2, self.Point)
        exportattrs = copyattrs = ['edgeFalloff', 'points_list']

    class Entry(ListComponent):
        class Object(ListX2Component):
            FORMID_LISTX2MACRO(objectId, 12, 5, 1)
            UINT16_LISTX2MACRO(parentIndex, 12, 5, 2)
            UINT8_ARRAY_LISTX2MACRO(unused1, 12, 5, 3, 2)
            FLOAT32_LISTX2MACRO(density, 12, 5, 4)
            UINT8_LISTX2MACRO(clustering, 12, 5, 5)
            UINT8_LISTX2MACRO(minSlope, 12, 5, 6)
            UINT8_LISTX2MACRO(maxSlope, 12, 5, 7)
            UINT8_FLAG_LISTX2MACRO(flags, 12, 5, 8)
            UINT16_LISTX2MACRO(radiusWRTParent, 12, 5, 9)
            UINT16_LISTX2MACRO(radius, 12, 5, 10)
            UINT8_ARRAY_LISTX2MACRO(unk1, 12, 5, 11, 4)
            FLOAT32_LISTX2MACRO(maxHeight, 12, 5, 12)
            FLOAT32_LISTX2MACRO(sink, 12, 5, 13)
            FLOAT32_LISTX2MACRO(sinkVar, 12, 5, 14)
            FLOAT32_LISTX2MACRO(sizeVar, 12, 5, 15)
            UINT16_LISTX2MACRO(angleVarX, 12, 5, 16)
            UINT16_LISTX2MACRO(angleVarY, 12, 5, 17)
            UINT16_LISTX2MACRO(angleVarZ, 12, 5, 18)
            UINT8_ARRAY_LISTX2MACRO(unused2, 12, 5, 19, 1)
            UINT8_ARRAY_LISTX2MACRO(unk2, 12, 5, 20, 4)
            BasicFlagMACRO(IsConformToSlope, flags, 0x00000001)
            BasicFlagMACRO(IsPaintVertices, flags, 0x00000002)
            BasicFlagMACRO(IsSizeVariance, flags, 0x00000004)
            BasicFlagMACRO(IsXVariance, flags, 0x00000008)
            BasicFlagMACRO(IsYVariance, flags, 0x00000010)
            BasicFlagMACRO(IsZVariance, flags, 0x00000020)
            BasicFlagMACRO(IsTree, flags, 0x00000040)
            BasicFlagMACRO(IsHugeRock, flags, 0x00000080)
            exportattrs = copyattrs = ['objectId', 'parentIndex', 'density', 'clustering',
                         'minSlope', 'maxSlope', 'flags', 'radiusWRTParent',
                         'radius', 'unk1', 'maxHeight', 'sink', 'sinkVar',
                         'sizeVar', 'angleVarX', 'angleVarY', 'angleVarZ',
                         'unk2']

        class Grass(ListX2Component):
            FORMID_LISTX2MACRO(grass, 12, 8, 1)
            UINT8_ARRAY_LISTX2MACRO(unk1, 12, 8, 2, 4)
            exportattrs = copyattrs = ['grass', 'unk1']

        class Sound(ListX2Component):
            FORMID_LISTX2MACRO(sound, 12, 10, 1)
            UINT32_FLAG_LISTX2MACRO(flags, 12, 10, 2)
            UINT32_LISTX2MACRO(chance, 12, 10, 3)
            BasicFlagMACRO(IsPleasant, flags, 0x00000001)
            BasicFlagMACRO(IsCloudy, flags, 0x00000002)
            BasicFlagMACRO(IsRainy, flags, 0x00000004)
            BasicFlagMACRO(IsSnowy, flags, 0x00000008)
            exportattrs = copyattrs = ['sound', 'flags', 'chance']

        class Weather(ListX2Component):
            FORMID_LISTX2MACRO(weather, 12, 11, 1)
            UINT32_LISTX2MACRO(chance, 12, 11, 2)
            exportattrs = copyattrs = ['weather', 'chance']

        UINT32_TYPE_LISTMACRO(entryType, 12, 1)
        UINT8_FLAG_LISTMACRO(flags, 12, 2)
        UINT8_LISTMACRO(priority, 12, 3)
        UINT8_ARRAY_LISTMACRO(unused1, 12, 4)

        LIST_LISTMACRO(objects, 12, 5, self.Object)
        STRING_LISTMACRO(mapName, 12, 6)
        ISTRING_LISTMACRO(iconPath, 12, 7)

        LIST_LISTMACRO(grasses, 12, 8, self.Grass)
        UINT32_TYPE_LISTMACRO(musicType, 12, 9)

        LIST_LISTMACRO(sounds, 12, 10, self.Sound)
        LIST_LISTMACRO(weathers, 12, 11, self.Weather)
        BasicTypeMACRO(IsObject, entryType, 2, IsWeather)
        BasicTypeMACRO(IsWeather, entryType, 3, IsObject)
        BasicTypeMACRO(IsMap, entryType, 4, IsObject)
        BasicTypeMACRO(IsIcon, entryType, 5, IsObject)
        BasicTypeMACRO(IsGrass, entryType, 6, IsObject)
        BasicTypeMACRO(IsSound, entryType, 7, IsObject)
        BasicTypeMACRO(IsDefault, musicType, 0, IsPublic)
        BasicTypeMACRO(IsPublic, musicType, 1, IsDefault)
        BasicTypeMACRO(IsDungeon, musicType, 2, IsDefault)
        BasicFlagMACRO(IsOverride, flags, 0x00000001)
        exportattrs = copyattrs = ['entryType', 'flags', 'priority', 'objects_list', 'mapName',
                     'iconPath', 'grasses_list', 'musicType', 'sounds_list', 'weathers_list']

    ISTRING_MACRO(iconPath, 5)
    UINT8_MACRO(mapRed, 6)
    UINT8_MACRO(mapGreen, 7)
    UINT8_MACRO(mapBlue, 8)
    UINT8_ARRAY_MACRO(unused1, 9, 1)
    FORMID_MACRO(worldspace, 10)

    LIST_MACRO(areas, 11, self.Area)
    LIST_MACRO(entries, 12, self.Entry)
    exportattrs = copyattrs = ObFormIDRecord.baseattrs + ['iconPath', 'mapRed', 'mapGreen',
                                        'mapBlue', 'worldspace', 'areas_list',
                                        'entries_list']

class ObSBSPRecord(ObFormIDRecord):
    _Type = 'SBSP'
    FLOAT32_MACRO(sizeX, 5)
    FLOAT32_MACRO(sizeY, 6)
    FLOAT32_MACRO(sizeZ, 7)
    exportattrs = copyattrs = ObFormIDRecord.baseattrs + ['sizeX', 'sizeY', 'sizeZ']

class ObSCPTRecord(ObFormIDRecord):
    _Type = 'SCPT'
    class Var(ListComponent):
        UINT32_LISTMACRO(index, 12, 1)
        UINT8_ARRAY_LISTMACRO(unused1, 12, 2, 12)
        UINT8_FLAG_LISTMACRO(flags, 12, 3)
        UINT8_ARRAY_LISTMACRO(unused2, 12, 4, 7)
        STRING_LISTMACRO(name, 12, 5)
        BasicFlagMACRO(IsLongOrShort, flags, 0x00000001)
        exportattrs = copyattrs = ['index', 'flags', 'name']

    UINT8_ARRAY_MACRO(unused1, 5, 2)
    UINT32_MACRO(numRefs, 6)
    UINT32_MACRO(compiledSize, 7)
    UINT32_MACRO(lastIndex, 8)
    UINT32_MACRO(scriptType, 9)
    UINT8_ARRAY_MACRO(compiled_p, 10)
    ISTRING_MACRO(scriptText, 11)

    LIST_MACRO(vars, 12, self.Var)
    FORMID_OR_UINT32_ARRAY_MACRO(references, 13)
    copyattrs = ObFormIDRecord.baseattrs + ['numRefs', 'compiledSize', 'lastIndex',
                                        'scriptType', 'compiled_p', 'scriptText',
                                        'vars_list', 'references']
    exportattrs = ObFormIDRecord.baseattrs + ['numRefs', 'compiledSize', 'lastIndex',
                                        'scriptType', 'scriptText',
                                        'vars_list', 'references'] #'compiled_p', 

class ObSGSTRecord(ObFormIDRecord):
    _Type = 'SGST'
    STRING_MACRO(full, 5)
    ISTRING_MACRO(modPath, 6)
    FLOAT32_MACRO(modb, 7)
    UINT8_ARRAY_MACRO(modt_p, 8)
    ISTRING_MACRO(iconPath, 9)
    FORMID_MACRO(script, 10)

    LIST_MACRO(effects, 11, Effect)
    UINT8_MACRO(uses, 12)
    SINT32_MACRO(value, 13)
    FLOAT32_MACRO(weight, 14)
    ##OBME Fields. Setting any of the below fields will make the mod require JRoush's OBME plugin for OBSE
    ##To see if OBME is in use, check the recordVersion field for a non-None value
    UINT8_MACRO(recordVersion, 15)
    UINT8_MACRO(betaVersion, 16)
    UINT8_MACRO(minorVersion, 17)
    UINT8_MACRO(majorVersion, 18)
    UINT8_ARRAY_MACRO(reserved, 19, 0x1C)
    UINT8_ARRAY_MACRO(datx_p, 20, 0x20)
    copyattrs = ObFormIDRecord.baseattrs + ['full', 'modPath', 'modb', 'modt_p',
                                        'iconPath', 'script', 'effects_list',
                                        'uses', 'value', 'weight']
    exportattrs = ObFormIDRecord.baseattrs + ['full', 'modPath', 'modb',
                                        'iconPath', 'script', 'effects_list',
                                        'uses', 'value', 'weight'] # 'modt_p',
    copyattrsOBME = copyattrs + ['recordVersion', 'betaVersion',
                                 'minorVersion', 'majorVersion',
                                 'reserved'] #, 'datx_p'

class ObSKILRecord(ObFormIDRecord):
    _Type = 'SKIL'
    SINT32_MACRO(skill, 5)
    STRING_MACRO(description, 6)
    ISTRING_MACRO(iconPath, 7)
    SINT32_MACRO(action, 8)
    SINT32_MACRO(attribute, 9)
    UINT32_MACRO(specialization, 10)
    FLOAT32_MACRO(use0, 11)
    FLOAT32_MACRO(use1, 12)
    STRING_MACRO(apprentice, 13)
    STRING_MACRO(journeyman, 14)
    STRING_MACRO(expert, 15)
    STRING_MACRO(master, 16)
    exportattrs = copyattrs = ObFormIDRecord.baseattrs + ['skill', 'description', 'iconPath',
                                        'action', 'attribute', 'specialization',
                                        'use0', 'use1', 'apprentice',
                                        'journeyman', 'expert', 'master']

class ObSLGMRecord(ObFormIDRecord):
    _Type = 'SLGM'
    STRING_MACRO(full, 5)
    ISTRING_MACRO(modPath, 6)
    FLOAT32_MACRO(modb, 7)
    UINT8_ARRAY_MACRO(modt_p, 8)
    ISTRING_MACRO(iconPath, 9)
    FORMID_MACRO(script, 10)
    SINT32_MACRO(value, 11)
    FLOAT32_MACRO(weight, 12)
    UINT8_TYPE_MACRO(soulType, 13)
    UINT8_TYPE_MACRO(capacityType, 14)
    BasicTypeMACRO(IsNoSoul, soulType, 0, IsPettySoul)
    BasicTypeMACRO(IsPettySoul, soulType, 1, IsNoSoul)
    BasicTypeMACRO(IsLesserSoul, soulType, 2, IsNoSoul)
    BasicTypeMACRO(IsCommonSoul, soulType, 3, IsNoSoul)
    BasicTypeMACRO(IsGreaterSoul, soulType, 4, IsNoSoul)
    BasicTypeMACRO(IsGrandSoul, soulType, 5, IsNoSoul)
    BasicTypeMACRO(IsNoCapacity, capacityType, 0, IsPettyCapacity)
    BasicTypeMACRO(IsPettyCapacity, capacityType, 1, IsNoCapacity)
    BasicTypeMACRO(IsLesserCapacity, capacityType, 2, IsNoCapacity)
    BasicTypeMACRO(IsCommonCapacity, capacityType, 3, IsNoCapacity)
    BasicTypeMACRO(IsGreaterCapacity, capacityType, 4, IsNoCapacity)
    BasicTypeMACRO(IsGrandCapacity, capacityType, 5, IsNoCapacity)
    copyattrs = ObFormIDRecord.baseattrs + ['full', 'modPath', 'modb', 'modt_p',
                                        'iconPath', 'script', 'value',
                                        'weight', 'soulType', 'capacityType']
    exportattrs = ObFormIDRecord.baseattrs + ['full', 'modPath', 'modb',
                                        'iconPath', 'script', 'value',
                                        'weight', 'soulType', 'capacityType'] # 'modt_p',

class ObSOUNRecord(ObFormIDRecord):
    _Type = 'SOUN'
    ISTRING_MACRO(soundPath, 5)
    UINT8_MACRO(minDistance, 6)
    UINT8_MACRO(maxDistance, 7)
    SINT8_MACRO(freqAdjustment, 8)
    UINT8_ARRAY_MACRO(unused1, 9, 1)
    UINT16_FLAG_MACRO(flags, 10)
    UINT8_ARRAY_MACRO(unused2, 11, 2)
    SINT16_MACRO(staticAtten, 12)
    UINT8_MACRO(stopTime, 13)
    UINT8_MACRO(startTime, 14)
    BasicFlagMACRO(IsRandomFrequencyShift, flags, 0x00000001)
    BasicFlagMACRO(IsPlayAtRandom, flags, 0x00000002)
    BasicFlagMACRO(IsEnvironmentIgnored, flags, 0x00000004)
    BasicFlagMACRO(IsRandomLocation, flags, 0x00000008)
    BasicFlagMACRO(IsLoop, flags, 0x00000010)
    BasicFlagMACRO(IsMenuSound, flags, 0x00000020)
    BasicFlagMACRO(Is2D, flags, 0x00000040)
    BasicFlagMACRO(Is360LFE, flags, 0x00000080)
    exportattrs = copyattrs = ObFormIDRecord.baseattrs + ['soundPath', 'minDistance', 'maxDistance',
                                        'freqAdjustment', 'flags', 'staticAtten',
                                        'stopTime', 'startTime']

class ObSPELRecord(ObFormIDRecord):
    _Type = 'SPEL'
    STRING_MACRO(full, 5)
    UINT32_TYPE_MACRO(spellType, 6)
    UINT32_MACRO(cost, 7)
    UINT32_TYPE_MACRO(levelType, 8)
    UINT8_FLAG_MACRO(flags, 9)
    UINT8_ARRAY_MACRO(unused1, 10, 3)

    LIST_MACRO(effects, 11, Effect)
    BasicFlagMACRO(IsManualCost, flags, 0x00000001)
    BasicFlagMACRO(IsStartSpell, flags, 0x00000004)
    BasicFlagMACRO(IsSilenceImmune, flags, 0x0000000A)
    BasicFlagMACRO(IsAreaEffectIgnoresLOS, flags, 0x00000010)
    BasicAliasMACRO(IsAEIgnoresLOS, IsAreaEffectIgnoresLOS)
    BasicFlagMACRO(IsScriptAlwaysApplies, flags, 0x00000020)
    BasicFlagMACRO(IsDisallowAbsorbReflect, flags, 0x00000040)
    BasicAliasMACRO(IsDisallowAbsorb, IsDisallowAbsorbReflect)
    BasicAliasMACRO(IsDisallowReflect, IsDisallowAbsorbReflect)
    BasicFlagMACRO(IsTouchExplodesWOTarget, flags, 0x00000080)
    BasicAliasMACRO(IsTouchExplodes, IsTouchExplodesWOTarget)
    BasicTypeMACRO(IsSpell, spellType, 0, IsDisease)
    BasicTypeMACRO(IsDisease, spellType, 1, IsSpell)
    BasicTypeMACRO(IsPower, spellType, 2, IsSpell)
    BasicTypeMACRO(IsLesserPower, spellType, 3, IsSpell)
    BasicTypeMACRO(IsAbility, spellType, 4, IsSpell)
    BasicTypeMACRO(IsPoison, spellType, 5, IsSpell)
    BasicTypeMACRO(IsNovice, levelType, 0, IsApprentice)
    BasicTypeMACRO(IsApprentice, levelType, 1, IsNovice)
    BasicTypeMACRO(IsJourneyman, levelType, 2, IsNovice)
    BasicTypeMACRO(IsExpert, levelType, 3, IsNovice)
    BasicTypeMACRO(IsMaster, levelType, 4, IsNovice)
    ##OBME Fields. Setting any of the below fields will make the mod require JRoush's OBME plugin for OBSE
    ##To see if OBME is in use, check the recordVersion field for a non-None value
    UINT8_MACRO(recordVersion, 12)
    UINT8_MACRO(betaVersion, 13)
    UINT8_MACRO(minorVersion, 14)
    UINT8_MACRO(majorVersion, 15)
    UINT8_ARRAY_MACRO(reserved, 16, 0x1C)
    UINT8_ARRAY_MACRO(datx_p, 17, 0x20)
    exportattrs = copyattrs = ObFormIDRecord.baseattrs + ['full', 'spellType', 'cost',
                                        'level', 'flags', 'effects_list']
    copyattrsOBME = copyattrs + ['recordVersion', 'betaVersion',
                                 'minorVersion', 'majorVersion',
                                 'reserved'] #, 'datx_p'

class ObSTATRecord(ObFormIDRecord):
    _Type = 'STAT'
    ISTRING_MACRO(modPath, 5)
    FLOAT32_MACRO(modb, 6)
    UINT8_ARRAY_MACRO(modt_p, 7)
    copyattrs = ObFormIDRecord.baseattrs + ['modPath', 'modb', 'modt_p']
    exportattrs = ObFormIDRecord.baseattrs + ['modPath', 'modb']#, 'modt_p']

class ObTREERecord(ObFormIDRecord):
    _Type = 'TREE'
    ISTRING_MACRO(modPath, 5)
    FLOAT32_MACRO(modb, 6)
    UINT8_ARRAY_MACRO(modt_p, 7)
    ISTRING_MACRO(iconPath, 8)
    UINT32_ARRAY_MACRO(speedTree, 9)
    FLOAT32_MACRO(curvature, 10)
    FLOAT32_MACRO(minAngle, 11)
    FLOAT32_MACRO(maxAngle, 12)
    FLOAT32_MACRO(branchDim, 13)
    FLOAT32_MACRO(leafDim, 14)
    SINT32_MACRO(shadowRadius, 15)
    FLOAT32_MACRO(rockSpeed, 16)
    FLOAT32_MACRO(rustleSpeed, 17)
    FLOAT32_MACRO(widthBill, 18)
    FLOAT32_MACRO(heightBill, 19)
    copyattrs = ObFormIDRecord.baseattrs + ['modPath', 'modb', 'modt_p', 'iconPath',
                                        'speedTree', 'curvature', 'minAngle',
                                        'maxAngle', 'branchDim', 'leafDim',
                                        'shadowRadius', 'rockSpeed',
                                        'rustleSpeed', 'widthBill', 'heightBill']
    exportattrs = ObFormIDRecord.baseattrs + ['modPath', 'modb', 'iconPath',
                                        'speedTree', 'curvature', 'minAngle',
                                        'maxAngle', 'branchDim', 'leafDim',
                                        'shadowRadius', 'rockSpeed',
                                        'rustleSpeed', 'widthBill', 'heightBill'] #'modt_p', 

class ObWATRRecord(ObFormIDRecord):
    _Type = 'WATR'
    ISTRING_MACRO(texturePath, 5)
    UINT8_MACRO(opacity, 6)
    UINT8_FLAG_MACRO(flags, 7)
    ISTRING_MACRO(materialPath, 8)
    FORMID_MACRO(sound, 9)
    FLOAT32_MACRO(windVelocity, 10)
    FLOAT32_MACRO(windDirection, 11)
    FLOAT32_MACRO(waveAmp, 12)
    FLOAT32_MACRO(waveFreq, 13)
    FLOAT32_MACRO(sunPower, 14)
    FLOAT32_MACRO(reflectAmt, 15)
    FLOAT32_MACRO(fresnelAmt, 16)
    FLOAT32_MACRO(xSpeed, 17)
    FLOAT32_MACRO(ySpeed, 18)
    FLOAT32_MACRO(fogNear, 19)
    FLOAT32_MACRO(fogFar, 20)
    UINT8_MACRO(shallowRed, 21)
    UINT8_MACRO(shallowGreen, 22)
    UINT8_MACRO(shallowBlue, 23)
    UINT8_ARRAY_MACRO(unused1, 24, 1)
    UINT8_MACRO(deepRed, 25)
    UINT8_MACRO(deepGreen, 26)
    UINT8_MACRO(deepBlue, 27)
    UINT8_ARRAY_MACRO(unused2, 28, 1)
    UINT8_MACRO(reflRed, 29)
    UINT8_MACRO(reflGreen, 30)
    UINT8_MACRO(reflBlue, 31)
    UINT8_ARRAY_MACRO(unused3, 32, 1)
    UINT8_MACRO(blend, 33)
    UINT8_ARRAY_MACRO(unused4, 34, 3)
    FLOAT32_MACRO(rainForce, 35)
    FLOAT32_MACRO(rainVelocity, 36)
    FLOAT32_MACRO(rainFalloff, 37)
    FLOAT32_MACRO(rainDampner, 38)
    FLOAT32_MACRO(rainSize, 39)
    FLOAT32_MACRO(dispForce, 40)
    FLOAT32_MACRO(dispVelocity, 41)
    FLOAT32_MACRO(dispFalloff, 42)
    FLOAT32_MACRO(dispDampner, 43)
    FLOAT32_MACRO(dispSize, 44)
    UINT16_MACRO(damage, 45)
    FORMID_MACRO(dayWater, 46)
    FORMID_MACRO(nightWater, 47)
    FORMID_MACRO(underWater, 48)
    BasicFlagMACRO(IsCausesDamage, flags, 0x00000001)
    BasicAliasMACRO(IsCausesDmg, IsCausesDamage)
    BasicFlagMACRO(IsReflective, flags, 0x00000002)
    exportattrs = copyattrs = ObFormIDRecord.baseattrs + ['texturePath', 'opacity', 'flags', 'materialPath',
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

class ObWEAPRecord(ObFormIDRecord):
    _Type = 'WEAP'
    STRING_MACRO(full, 5)
    ISTRING_MACRO(modPath, 6)
    FLOAT32_MACRO(modb, 7)
    UINT8_ARRAY_MACRO(modt_p, 8)
    ISTRING_MACRO(iconPath, 9)
    FORMID_MACRO(script, 10)
    FORMID_MACRO(enchantment, 11)
    UINT16_MACRO(enchantPoints, 12)
    UINT32_TYPE_MACRO(weaponType, 13)
    FLOAT32_MACRO(speed, 14)
    FLOAT32_MACRO(reach, 15)
    UINT32_FLAG_MACRO(flags, 16)
    UINT32_MACRO(value, 17)
    UINT32_MACRO(health, 18)
    FLOAT32_MACRO(weight, 19)
    UINT16_MACRO(damage, 20)
    BasicTypeMACRO(IsBlade1Hand, weaponType, 0, IsBlade2Hand)
    BasicTypeMACRO(IsBlade2Hand, weaponType, 1, IsBlade1Hand)
    BasicTypeMACRO(IsBlunt1Hand, weaponType, 2, IsBlade1Hand)
    BasicTypeMACRO(IsBlunt2Hand, weaponType, 3, IsBlade1Hand)
    BasicTypeMACRO(IsStaff, weaponType, 4, IsBlade1Hand)
    BasicTypeMACRO(IsBow, weaponType, 5, IsBlade1Hand)
    BasicFlagMACRO(IsNotNormalWeapon, flags, 0x00000001)
    BasicAliasMACRO(IsNotNormal, IsNotNormalWeapon)
    BasicInvertedFlagMACRO(IsNormalWeapon, IsNotNormalWeapon)
    BasicAliasMACRO(IsNormal, IsNormalWeapon)
    copyattrs = ObFormIDRecord.baseattrs + ['full', 'modPath', 'modb', 'modt_p',
                                        'iconPath', 'script', 'enchantment',
                                        'enchantPoints', 'weaponType',
                                        'speed', 'reach', 'flags', 'value',
                                        'health', 'weight', 'damage']
    exportattrs = ObFormIDRecord.baseattrs + ['full', 'modPath', 'modb',
                                        'iconPath', 'script', 'enchantment',
                                        'enchantPoints', 'weaponType',
                                        'speed', 'reach', 'flags', 'value',
                                        'health', 'weight', 'damage'] # 'modt_p',

class ObWRLDRecord(ObFormIDRecord):
    _Type = 'WRLD'
    STRING_MACRO(full, 5)
    FORMID_MACRO(parent, 6)
    FORMID_MACRO(climate, 7)
    FORMID_MACRO(water, 8)
    ISTRING_MACRO(mapPath, 9)
    SINT32_MACRO(dimX, 10)
    SINT32_MACRO(dimY, 11)
    SINT16_MACRO(NWCellX, 12)
    SINT16_MACRO(NWCellY, 13)
    SINT16_MACRO(SECellX, 14)
    SINT16_MACRO(SECellY, 15)
    UINT8_FLAG_MACRO(flags, 16)
    FLOAT32_MACRO(unknown00, 17)
    FLOAT32_MACRO(unknown01, 18)
    FLOAT32_MACRO(unknown90, 19)
    FLOAT32_MACRO(unknown91, 20)
    UINT32_MACRO(musicType, 21)
    UINT8_ARRAY_MACRO(ofst_p, 22)
    SUBRECORD_MACRO(ROAD, "ROAD", 23, ObROADRecord, 0)
    SUBRECORD_MACRO(WorldCELL, "CELL", 24, ObCELLRecord, 2)
    SUBRECORD_ARRAY_MACRO(CELLS, "CELL", 25, ObCELLRecord, 0)
    BasicFlagMACRO(IsSmallWorld, flags, 0x00000001)
    BasicFlagMACRO(IsNoFastTravel, flags, 0x00000002)
    BasicInvertedFlagMACRO(IsFastTravel, IsNoFastTravel)
    BasicFlagMACRO(IsOblivionWorldspace, flags, 0x00000004)
    BasicFlagMACRO(IsNoLODWater, flags, 0x00000010)
    BasicInvertedFlagMACRO(IsLODWater, IsNoLODWater)
    BasicTypeMACRO(IsDefault, musicType, 0, IsPublic)
    BasicTypeMACRO(IsPublic, musicType, 1, IsDefault)
    BasicTypeMACRO(IsDungeon, musicType, 2, IsDefault)
    exportattrs = copyattrs = ObFormIDRecord.baseattrs + ['full', 'parent', 'climate', 'water', 'mapPath',
                                        'dimX', 'dimY', 'NWCellX', 'NWCellY', 'SECellX',
                                        'SECellY', 'flags', 'unknown00', 'unknown01',
                                        'unknown90', 'unknown91', 'musicType', 'ROAD', 'WorldCELL'] #'ofst_p', 

class ObWTHRRecord(ObFormIDRecord):
    _Type = 'WTHR'
    class WTHRColor(BaseComponent):
        UINT8_GROUPEDMACRO(riseRed, 0)
        UINT8_GROUPEDMACRO(riseGreen, 1)
        UINT8_GROUPEDMACRO(riseBlue, 2)
        UINT8_ARRAY_GROUPEDMACRO(unused1, 3, 1)
        UINT8_GROUPEDMACRO(dayRed, 4)
        UINT8_GROUPEDMACRO(dayGreen, 5)
        UINT8_GROUPEDMACRO(dayBlue, 6)
        UINT8_ARRAY_GROUPEDMACRO(unused2, 7, 1)
        UINT8_GROUPEDMACRO(setRed, 8)
        UINT8_GROUPEDMACRO(setGreen, 9)
        UINT8_GROUPEDMACRO(setBlue, 10)
        UINT8_ARRAY_GROUPEDMACRO(unused3, 11, 1)
        UINT8_GROUPEDMACRO(nightRed, 12)
        UINT8_GROUPEDMACRO(nightGreen, 13)
        UINT8_GROUPEDMACRO(nightBlue, 14)
        UINT8_ARRAY_GROUPEDMACRO(unused4, 15, 1)
        exportattrs = copyattrs = ['riseRed', 'riseGreen', 'riseBlue',
                     'dayRed', 'dayGreen', 'dayBlue',
                     'setRed', 'setGreen', 'setBlue',
                     'nightRed', 'nightGreen', 'nightBlue']

    class Sound(ListComponent):
        FORMID_LISTMACRO(sound, 203, 1)
        UINT32_TYPE_LISTMACRO(type, 203, 2)
        BasicTypeMACRO(IsDefault, type, 0, IsPrecip)
        BasicTypeMACRO(IsPrecipitation, type, 1, IsDefault)
        BasicAliasMACRO(IsPrecip, IsPrecipitation)
        BasicTypeMACRO(IsWind, type, 2, IsDefault)
        BasicTypeMACRO(IsThunder, type, 3, IsDefault)
        exportattrs = copyattrs = ['sound', 'type']

    ISTRING_MACRO(lowerLayerPath, 5)
    ISTRING_MACRO(upperLayerPath, 6)
    ISTRING_MACRO(modPath, 7)
    FLOAT32_MACRO(modb, 8)
    UINT8_ARRAY_MACRO(modt_p, 9)
    GroupedValuesMACRO(upperSky, 10, WTHRColor)
    GroupedValuesMACRO(fog, 26, WTHRColor)
    GroupedValuesMACRO(lowerClouds, 42, WTHRColor)
    GroupedValuesMACRO(ambient, 58, WTHRColor)
    GroupedValuesMACRO(sunlight, 74, WTHRColor)
    GroupedValuesMACRO(sun, 90, WTHRColor)
    GroupedValuesMACRO(stars, 106, WTHRColor)
    GroupedValuesMACRO(lowerSky, 122, WTHRColor)
    GroupedValuesMACRO(horizon, 138, WTHRColor)
    GroupedValuesMACRO(upperClouds, 154, WTHRColor)
    FLOAT32_MACRO(fogDayNear, 170)
    FLOAT32_MACRO(fogDayFar, 171)
    FLOAT32_MACRO(fogNightNear, 172)
    FLOAT32_MACRO(fogNightFar, 173)
    FLOAT32_MACRO(eyeAdaptSpeed, 174)
    FLOAT32_MACRO(blurRadius, 175)
    FLOAT32_MACRO(blurPasses, 176)
    FLOAT32_MACRO(emissiveMult, 177)
    FLOAT32_MACRO(targetLum, 178)
    FLOAT32_MACRO(upperLumClamp, 179)
    FLOAT32_MACRO(brightScale, 180)
    FLOAT32_MACRO(brightClamp, 181)
    FLOAT32_MACRO(lumRampNoTex, 182)
    FLOAT32_MACRO(lumRampMin, 183)
    FLOAT32_MACRO(lumRampMax, 184)
    FLOAT32_MACRO(sunlightDimmer, 185)
    FLOAT32_MACRO(grassDimmer, 186)
    FLOAT32_MACRO(treeDimmer, 187)
    UINT8_MACRO(windSpeed, 188)
    UINT8_MACRO(lowerCloudSpeed, 189)
    UINT8_MACRO(upperCloudSpeed, 190)
    UINT8_MACRO(transDelta, 191)
    UINT8_MACRO(sunGlare, 192)
    UINT8_MACRO(sunDamage, 193)
    UINT8_MACRO(rainFadeIn, 194)
    UINT8_MACRO(rainFadeOut, 195)
    UINT8_MACRO(boltFadeIn, 196)
    UINT8_MACRO(boltFadeOut, 197)
    UINT8_MACRO(boltFrequency, 198)
    UINT8_TYPE_MACRO(weatherType, 199)
    UINT8_MACRO(boltRed, 200)
    UINT8_MACRO(boltGreen, 201)
    UINT8_MACRO(boltBlue, 202)

    LIST_MACRO(sounds, 203, self.Sound)
    ##actually flags, but all are exclusive(except unknowns)...so like a Type
    ##Manual hackery will make the CS think it is multiple types. It isn't known how the game would react.
    MaskedTypeMACRO(IsNone, weatherType, 0x0F, 0x00, IsPleasant)
    MaskedTypeMACRO(IsPleasant, weatherType, 0x0F, 0x01, IsNone)
    MaskedTypeMACRO(IsCloudy, weatherType, 0x0F, 0x02, IsNone)
    MaskedTypeMACRO(IsRainy, weatherType, 0x0F, 0x04, IsNone)
    MaskedTypeMACRO(IsSnow, weatherType, 0x0F, 0x08, IsNone)
    BasicFlagMACRO(IsUnk1, weatherType, 0x40)
    BasicFlagMACRO(IsUnk2, weatherType, 0x80)
    copyattrs = ObFormIDRecord.baseattrs + ['lowerLayerPath', 'upperLayerPath', 'modPath',
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
    exportattrs = ObFormIDRecord.baseattrs + ['lowerLayerPath', 'upperLayerPath', 'modPath',
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

type_record = dict([('FID_',ObFormIDRecord),('EDID',ObEditorIDRecord),(None,None),('',None),
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
    def ModName(self):
        return _CGetModName(self._CollectionID, self._ModID) or 'Missing'

    @property
    def NormModName(self):
        ModName = _CGetModName(self._CollectionID, self._ModID) or 'Missing'
        if ModName[-6:] == '.ghost':
            return ModName[:-6]
        return ModName

    @property
    def GName(self):
        return GPath(self.NormModName)
    
    def HasRecord(self,RecordID):
        if not RecordID: return False
        if isinstance(RecordID, basestring): TestRecord = ObEditorIDRecord
        else: TestRecord = ObFormIDRecord
        return TestRecord(self._CollectionID, self._ModID, RecordID, 0, 0).fid

    def LookupRecord(self, RecordID):
        if isinstance(RecordID, basestring):
            RecordType = ObEditorIDRecord
        else:
            RecordID = MakeShortFid(self._CollectionID, RecordID)
            RecordType = ObFormIDRecord
        if not RecordID: return None
        testRecord = RecordType(self._CollectionID, self._ModID, RecordID, 0, 0)
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
        return ObTES4Record(self._CollectionID, self._ModID, 0, 0, 0)

    ObModEDIDRecordsMACRO(GMST)
    ObModRecordsMACRO(GLOB)
    ObModRecordsMACRO(CLAS)
    ObModRecordsMACRO(FACT)
    ObModRecordsMACRO(HAIR)
    ObModRecordsMACRO(EYES)
    ObModRecordsMACRO(RACE)
    ObModRecordsMACRO(SOUN)
    ObModRecordsMACRO(SKIL)
    ObModEDIDRecordsMACRO(MGEF)
    ObModRecordsMACRO(SCPT)
    ObModRecordsMACRO(LTEX)
    ObModRecordsMACRO(ENCH)
    ObModRecordsMACRO(SPEL)
    ObModRecordsMACRO(BSGN)
    ObModRecordsMACRO(ACTI)
    ObModRecordsMACRO(APPA)
    ObModRecordsMACRO(ARMO)
    ObModRecordsMACRO(BOOK)
    ObModRecordsMACRO(CLOT)
    ObModRecordsMACRO(CONT)
    ObModRecordsMACRO(DOOR)
    ObModRecordsMACRO(INGR)
    ObModRecordsMACRO(LIGH)
    ObModRecordsMACRO(MISC)
    ObModRecordsMACRO(STAT)
    ObModRecordsMACRO(GRAS)
    ObModRecordsMACRO(TREE)
    ObModRecordsMACRO(FLOR)
    ObModRecordsMACRO(FURN)
    ObModRecordsMACRO(WEAP)
    ObModRecordsMACRO(AMMO)
    ObModRecordsMACRO(NPC_)
    ObModRecordsMACRO(CREA)
    ObModRecordsMACRO(LVLC)
    ObModRecordsMACRO(SLGM)
    ObModRecordsMACRO(KEYM)
    ObModRecordsMACRO(ALCH)
    ObModRecordsMACRO(SBSP)
    ObModRecordsMACRO(SGST)
    ObModRecordsMACRO(LVLI)
    ObModRecordsMACRO(WTHR)
    ObModRecordsMACRO(CLMT)
    ObModRecordsMACRO(REGN)
    ObModRecordsMACRO(WRLD)
    ObModRecordsMACRO(CELL)
    ObModRecordsMACRO(DIAL)
    ObModRecordsMACRO(QUST)
    ObModRecordsMACRO(IDLE)
    ObModRecordsMACRO(PACK)
    ObModRecordsMACRO(CSTY)
    ObModRecordsMACRO(LSCR)
    ObModRecordsMACRO(LVSP)
    ObModRecordsMACRO(ANIO)
    ObModRecordsMACRO(WATR)
    ObModRecordsMACRO(EFSH)

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

class ObCollection:
    """Collection of esm/esp's."""
    def __init__(self, RecordID=None, ModsPath="."):
        if RecordID:
            self._CollectionID = RecordID
        else:
            self._CollectionID = _CCreateCollection(str(ModsPath), 0) #Oblivion collection type hardcoded for now
        self._ModIndex = -1
        self._NumMods = 0

    def __eq__(self, other):
        if type(other) is type(self):
            return self._CollectionID == other._CollectionID
        return False
        
    def __ne__(self, other):
        return not self.__eq__(other)

    def addMod(self, ModName, MinLoad=True, NoLoad=False, IgnoreExisting=False, Flags=0x00000078):
##        //MinLoad and FullLoad are exclusive
##        // If both are set, FullLoad takes priority
##        // If neither is set, the mod isn't loaded
##
##        //SkipNewRecords causes any new record to be ignored when the mod is loaded
##        // This may leave broken records behind (such as a quest override pointing to a new script that was ignored)
##        // So it shouldn't be used if planning on copying records unless you either check that there are no new records being referenced
##
##        //InLoadOrder makes the mod count towards the 255 limit and enables record creation / deletion / copying to.
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
##        //Only the following combinations are tested:
##        // Normal:  (fIsMinLoad or fIsFullLoad) + fIsInLoadOrder + fIsSaveable + fIsAddMasters + fIsLoadMasters
##        // Merged:  (fIsMinLoad or fIsFullLoad) + fIsSkipNewRecords
##        // Scanned: (fIsMinLoad or fIsFullLoad) + fIsSkipNewRecords + fIsExtendedConflicts
        
        fIsMinLoad            = 0x00000001
        fIsFullLoad           = 0x00000002
        fIsSkipNewRecords     = 0x00000004
        fIsInLoadOrder        = 0x00000008
        fIsSaveable           = 0x00000010
        fIsAddMasters         = 0x00000020
        fIsLoadMasters        = 0x00000040
        fIsExtendedConflicts  = 0x00000080
        fIsTrackNewTypes      = 0x00000100
        fIsIndexLANDs         = 0x00000200
        fIsFixupPlaceables    = 0x00000400
        fIsIgnoreExisting     = 0x00000800
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
        _CAddMod(self._CollectionID, str(ModName), Flags)
        return None

    def addMergeMod(self, ModName):
        return self.addMod(ModName, Flags=0x00000005)

    def addScanMod(self, ModName):
        return self.addMod(ModName, Flags=0x00000085)

    def load(self):
        _CLoadCollection(self._CollectionID)
        self._NumMods = _CGetNumMods(self._CollectionID)

    def LookupRecords(self, RecordID, GetExtendedConflicts=False):
        if isinstance(RecordID, basestring):
            _FormID = 0
            _EditorID = RecordID
            RecordType = ObEditorIDRecord
        else:
            _FormID = MakeShortFid(self._CollectionID, RecordID)
            _EditorID = 0
            RecordType = ObFormIDRecord
        if not (_FormID or _EditorID): return None
        numRecords = _CGetNumRecordConflicts(self._CollectionID, _FormID, _EditorID, c_ulong(GetExtendedConflicts))
        if(numRecords > 0):
            cModIDs = (c_ulong * numRecords)()
            _CGetRecordConflicts(self._CollectionID, _FormID, _EditorID, byref(cModIDs), c_ulong(GetExtendedConflicts))
            testRecord = RecordType(self._CollectionID, cModIDs[0], RecordID, 0, 0)
            RecordType = type_record[testRecord.recType]
            return [RecordType(self._CollectionID, cModIDs[x], RecordID, 0, 0) for x in range(0, numRecords)]
        return []

    def LookupModFile(self, ModName):
        ModID = _CGetModID(self._CollectionID, str(ModName))
        if(ModID != -1):
            return ObModFile(self._CollectionID, ModID)
        return None

    def UpdateReferences(self, FormIDToReplace, ReplacementFormID):
        count = 0
        for modFile in self:
            count += modFile.UpdateReferences(FormIDToReplace, ReplacementFormID)
        return count

    def Unload(self):
        _CUnloadCollection(self._CollectionID)

    def __del__(self):
        _CDeleteCollection(self._CollectionID)

    def __iter__(self):
        self._ModIndex = -1
        return self

    def __len__(self):
        return self._NumMods

    def next(self):
        self._ModIndex += 1
        if(self._ModIndex >= self._NumMods):
            raise StopIteration
        return ObModFile(self._CollectionID, self._ModIndex)

    def __getitem__(self, ModIndex):
        if(ModIndex < 0):
            ModIndex = self._NumMods + ModIndex + 1
        if(ModIndex >= self._NumMods):
            raise IndexError
        return ObModFile(self._CollectionID, ModIndex)