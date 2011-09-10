# -*- coding: utf-8 -*-

from ctypes import *
import struct
import math
from os.path import exists, join
try:
    #See if cint is being used by Wrye Bash
    from bolt import CBash as CBashEnabled
    from bolt import GPath, deprint, _, Path
except:
    #It isn't, so replace the imported items with bare definitions
    CBashEnabled = "."
    class Path(object):
        pass
    def GPath(obj):
        return obj
    def deprint(obj):
        print obj
    def _(obj):
        return obj

_CBashRequiredVersion = (0,6,0)

class CBashError(Exception):
    def __init__(self, value):
        self.value = value
    def __str__(self):
        return repr(self.value)

def ZeroIsErrorCheck(result, function, cArguments, *args):
    if result == 0:
        raise CBashError("Function returned an error code.")
    return result

def NegativeIsErrorCheck(result, function, cArguments, *args):
    if result < 0:
        raise CBashError("Function returned an error code.")
    return result

def PositiveIsErrorCheck(result, function, cArguments, *args):
    if result > 0:
        raise CBashError("Function returned an error code.")
    return result

CBash = None
# path to compiled dir hardcoded since importing bosh would be circular
# TODO: refactor to avoid circular deps
if CBashEnabled == 0: #regular depends on the filepath existing.
    paths = [join("bash", "compiled", "CBash.dll")]
elif CBashEnabled == 1: #force python mode
    paths = []
elif CBashEnabled == 2: #attempt to force CBash mode
    paths = [join("bash", "compiled", filename) for filename in ["CBash.dll","rename_CBash.dll","_CBash.dll"]]
else: #attempt to force path to CBash dll
    paths = [join(CBashEnabled,"CBash.dll")]

try:
    for path in paths:
        if exists(path):
            CBash = CDLL(path)
            break
    del paths
except AttributeError, error:
    CBash = None
    print error
except ImportError, error:
    CBash = None
    print error
except OSError, error:
    CBash = None
    print error
except:
    CBash = None
    raise

if(CBash):
    def LoggingCB(logString):
        print logString,
        return 0

    def RaiseCB():
        #Raising is mostly worthless in a callback
        #CTypes prints the error, but the traceback is useless
        #and it doesn't propagate properly

        #Apparently...
        #"The standard way of doing something meaningful with the exception is
        #to catch it in the callback, set a global flag, somehow encourage the
        #C code to unwind back to the original Python call and there check the
        #flag and re-raise the exception."

        #But this would lead to a large performance hit if it were checked after
        #every CBash call. An alternative might be to start a separate thread
        #that then raises the error in the main thread after control returns from
        #CBash. Dunno.

        #This particular callback may disappear, or be morphed into something else
        raise CBashError("Check the log.")
        return
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
        raise ImportError(_("cint.py requires CBash v%d.%d.%d or higher! (found v%d.%d.%d)") % (_CBashRequiredVersion + (_CGetVersionMajor(),_CGetVersionMinor(),_CGetVersionRevision())))
    _CCreateCollection = CBash.CreateCollection
    _CCreateCollection.errcheck = ZeroIsErrorCheck
    _CDeleteCollection = CBash.DeleteCollection
    _CDeleteCollection.errcheck = NegativeIsErrorCheck
    _CLoadCollection = CBash.LoadCollection
    _CLoadCollection.errcheck = NegativeIsErrorCheck
    _CUnloadCollection = CBash.UnloadCollection
    _CUnloadCollection.errcheck = NegativeIsErrorCheck
    _CGetCollectionType = CBash.GetCollectionType
    _CGetCollectionType.errcheck = NegativeIsErrorCheck
    _CUnloadAllCollections = CBash.UnloadAllCollections
    _CUnloadAllCollections.errcheck = NegativeIsErrorCheck
    _CDeleteAllCollections = CBash.DeleteAllCollections
    _CDeleteAllCollections.errcheck = NegativeIsErrorCheck
    _CAddMod = CBash.AddMod
    _CAddMod.errcheck = NegativeIsErrorCheck
    _CLoadMod = CBash.LoadMod
    _CLoadMod.errcheck = NegativeIsErrorCheck
    _CUnloadMod = CBash.UnloadMod
    _CUnloadMod.errcheck = NegativeIsErrorCheck
    _CCleanModMasters = CBash.CleanModMasters
    _CCleanModMasters.errcheck = NegativeIsErrorCheck
    _CSaveMod = CBash.SaveMod
    _CSaveMod.errcheck = NegativeIsErrorCheck
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
    _CGetModIDByRecordID = CBash.GetModIDByRecordID
    _CGetCollectionIDByRecordID = CBash.GetCollectionIDByRecordID
    _CGetCollectionIDByModID = CBash.GetCollectionIDByModID
    _CIsModEmpty = CBash.IsModEmpty
    _CGetModNumTypes = CBash.GetModNumTypes
    _CGetModNumTypes.errcheck = NegativeIsErrorCheck
    _CGetModTypes = CBash.GetModTypes
    _CGetModTypes.errcheck = NegativeIsErrorCheck
    _CGetModNumEmptyGRUPs = CBash.GetModNumEmptyGRUPs
    _CGetModNumEmptyGRUPs.errcheck = NegativeIsErrorCheck
    _CGetModNumOrphans = CBash.GetModNumOrphans
    _CGetModNumOrphans.errcheck = NegativeIsErrorCheck
    
    _CGetLongIDName = CBash.GetLongIDName
    _CMakeShortFormID = CBash.MakeShortFormID
    _CCreateRecord = CBash.CreateRecord
    _CCopyRecord = CBash.CopyRecord
    _CUnloadRecord = CBash.UnloadRecord
    _CResetRecord = CBash.ResetRecord
    _CDeleteRecord = CBash.DeleteRecord
    _CGetRecordID = CBash.GetRecordID
    _CGetNumRecords = CBash.GetNumRecords
    _CGetRecordIDs = CBash.GetRecordIDs
    _CIsRecordWinning = CBash.IsRecordWinning
    _CGetNumRecordConflicts = CBash.GetNumRecordConflicts
    _CGetRecordConflicts = CBash.GetRecordConflicts
    _CGetRecordHistory = CBash.GetRecordHistory
    _CGetNumIdenticalToMasterRecords = CBash.GetNumIdenticalToMasterRecords
    _CGetIdenticalToMasterRecords = CBash.GetIdenticalToMasterRecords
    _CUpdateReferences = CBash.UpdateReferences
    _CGetRecordUpdatedReferences = CBash.GetRecordUpdatedReferences
    _CSetIDFields = CBash.SetIDFields
    _CSetField = CBash.SetField
    _CDeleteField = CBash.DeleteField
    _CGetFieldAttribute = CBash.GetFieldAttribute
    _CGetField = CBash.GetField

    _CCreateCollection.restype = c_ulong
    _CDeleteCollection.restype = c_long
    _CLoadCollection.restype = c_long
    _CUnloadCollection.restype = c_long
    _CGetCollectionType.restype = c_long
    _CUnloadAllCollections.restype = c_long
    _CDeleteAllCollections.restype = c_long
    _CAddMod.restype = c_long
    _CLoadMod.restype = c_long
    _CUnloadMod.restype = c_long
    _CCleanModMasters.restype = c_long
    _CSaveMod.restype = c_long
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
    _CGetModIDByRecordID.restype = c_ulong
    _CGetCollectionIDByRecordID.restype = c_ulong
    _CGetCollectionIDByModID.restype = c_ulong
    _CIsModEmpty.restype = c_ulong
    _CGetModNumTypes.restype = c_long
    _CGetModTypes.restype = c_long
    _CGetModNumEmptyGRUPs.restype = c_long
    _CGetModNumOrphans.restype = c_long
    _CGetLongIDName.restype = c_char_p
    _CMakeShortFormID.restype = c_ulong
    _CCreateRecord.restype = c_ulong
    _CCopyRecord.restype = c_ulong
    _CUnloadRecord.restype = c_long
    _CResetRecord.restype = c_long
    _CDeleteRecord.restype = c_long
    _CGetRecordID.restype = c_ulong
    _CGetNumRecords.restype = c_long
    _CGetRecordIDs.restype = c_long
    _CIsRecordWinning.restype = c_long
    _CGetNumRecordConflicts.restype = c_long
    _CGetRecordConflicts.restype = c_long
    _CGetRecordHistory.restype = c_long
    _CGetNumIdenticalToMasterRecords.restype = c_long
    _CGetIdenticalToMasterRecords.restype = c_long
    _CUpdateReferences.restype = c_long
    _CGetRecordUpdatedReferences.restype = c_long
    _CSetIDFields.restype = c_long
    _CGetFieldAttribute.restype = c_ulong
    LoggingCallback = CFUNCTYPE(c_long, c_char_p)(LoggingCB)
    RaiseCallback = CFUNCTYPE(None)(RaiseCB)
    CBash.RedirectMessages(LoggingCallback)
    CBash.AllowRaising(RaiseCallback)

#Helper functions
class API_FIELDS(object):
    """These fields MUST be defined in the same order as in CBash's Common.h"""
    __slots__ = ['UNKNOWN', 'MISSING', 'JUNK', 'BOOL', 'SINT8', 'UINT8',
                 'SINT16', 'UINT16', 'SINT32', 'UINT32', 'FLOAT32', 'RADIAN',
                 'FORMID', 'MGEFCODE', 'ACTORVALUE', 'FORMID_OR_UINT32',
                 'FORMID_OR_FLOAT32', 'UINT8_OR_UINT32', 'FORMID_OR_STRING',
                 'UNKNOWN_OR_FORMID_OR_UINT32', 'UNKNOWN_OR_SINT32',
                 'UNKNOWN_OR_UINT32_FLAG', 'MGEFCODE_OR_UINT32',
                 'FORMID_OR_MGEFCODE_OR_ACTORVALUE_OR_UINT32',
                 'RESOLVED_MGEFCODE', 'STATIC_MGEFCODE', 'RESOLVED_ACTORVALUE',
                 'STATIC_ACTORVALUE', 'CHAR', 'CHAR4', 'STRING', 'ISTRING',
                 'STRING_OR_FLOAT32_OR_SINT32', 'LIST', 'PARENTRECORD',
                 'SUBRECORD', 'SINT8_FLAG', 'SINT8_TYPE', 'SINT8_FLAG_TYPE',
                 'SINT8_ARRAY', 'UINT8_FLAG', 'UINT8_TYPE', 'UINT8_FLAG_TYPE',
                 'UINT8_ARRAY', 'SINT16_FLAG', 'SINT16_TYPE',
                 'SINT16_FLAG_TYPE', 'SINT16_ARRAY', 'UINT16_FLAG', 'UINT16_TYPE',
                 'UINT16_FLAG_TYPE', 'UINT16_ARRAY', 'SINT32_FLAG', 'SINT32_TYPE',
                 'SINT32_FLAG_TYPE', 'SINT32_ARRAY', 'UINT32_FLAG', 'UINT32_TYPE',
                 'UINT32_FLAG_TYPE', 'UINT32_ARRAY', 'FLOAT32_ARRAY',
                 'RADIAN_ARRAY', 'FORMID_ARRAY', 'FORMID_OR_UINT32_ARRAY',
                 'MGEFCODE_OR_UINT32_ARRAY', 'STRING_ARRAY', 'ISTRING_ARRAY',
                 'SUBRECORD_ARRAY', 'UNDEFINED']

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

class FormID(object):
    """Represents a FormID"""

    class UnvalidatedFormID(object):
        """Represents an unchecked FormID. This the most common case by far.

           These occur when:
            1) A hard-coded Long FormID is used
            2) A Long FormID from a csv file is used
            3) Any CBash FormID is used

           It must be tested to see if it is safe for use in a particular collection.
           This class should never be instantiated except by class FormID(object)."""

        def __init__(self, master, objectID):
            self.master, self.objectID = GPath(master), objectID

        def __hash__(self):
            return hash((str(self.master), self.objectID))

        def __getitem__(self, x):
            if x == 0: return self.master
            return int(self.objectID & 0x00FFFFFFL)

        def __repr__(self):
            return "UnvalidatedFormID('%s', 0x%06X)" % (str(self.master), int(self.objectID & 0x00FFFFFFL))

        def Validate(self, target):
            """Unvalidated FormIDs have to be tested for each destination collection
               A FormID is valid if its master is part of the destination collection"""
            targetID = target.GetParentCollection()._CollectionID
            master = str(self.master)
            retValue = _CGetModIDByName(targetID, master)
            if retValue:
                return FormID.ValidFormID(self.master, self.objectID, _CMakeShortFormID(retValue, self.objectID , 0), targetID)
            return self

        def GetShortFormID(self, target):
            """Tries to resolve the formID for the given target.
               This should only get called if the FormID isn't validated prior to it being used by CBash."""
            formID = self.Validate(target)
            if isinstance(formID, FormID.ValidFormID):
                return formID.shortID
            raise TypeError(_("Attempted to set an invalid formID"))

    class InvalidFormID(object):
        """Represents an unsafe FormID.
           The FormIDs ModIndex won't properly match with the Collection's Load Order,
           so using it would cause the wrong record to become referenced.

           These occur when CBash is told to skip new records on loading a mod.
           This is most often done for scanned mods in Wrye Bash's Bashed Patch process.

           Invalid FormIDs are unsafe to use for any record in any collection.
           This class should never be instantiated except by class FormID(object)."""

        def __init__(self, objectID):
            self.objectID = objectID

        def __hash__(self):
            return hash((None, self.objectID))

        def __getitem__(self, x):
            if x == 0: return None
            return int(self.objectID & 0x00FFFFFFL)

        def __repr__(self):
            return "InvalidFormID(None, 0x%06X)" % (self.objectID,)

        def Validate(self, target):
            """No validation is needed. It's invalid."""
            return self

        def GetShortFormID(self, target):
            """It isn't safe to use this formID. Any attempt to resolve it will be wrong."""
            raise TypeError(_("Attempted to set an invalid formID"))

    class ValidFormID(object):
        """Represents a safe FormID.

           These occur when an unvalidated FormID is validated for a specific record.
           Technically, the validation is good for an entire collection, but it's rare
           for the same FormID instance to be used for multiple records.

           This class should never be instantiated except by class FormID(object)."""

        def __init__(self, master, objectID, shortID, collectionID):
            self.master, self.objectID, self.shortID, self._CollectionID = master, objectID, shortID, collectionID

        def __hash__(self):
            return hash((str(self.master), self.objectID))

        def __getitem__(self, x):
            if x == 0: return self.master
            return int(self.objectID & 0x00FFFFFFL)

        def __repr__(self):
            return "ValidFormID('%s', 0x%06X)" % (str(self.master), int(self.objectID & 0x00FFFFFFL))

        def Validate(self, target):
            """This FormID has already been validated for a specific collection.
               It must be revalidated if the target being used doesn't match the earlier validation."""
            if target.GetParentCollection()._CollectionID == self._CollectionID:
                return self
            return FormID.UnvalidatedFormID(self.master, self.objectID).Validate(target)

        def GetShortFormID(self, target):
            """This FormID has already been resolved for a specific record.
               It must be re-resolved if the target being used doesn't match the earlier validation."""
            if target.GetParentCollection()._CollectionID == self._CollectionID:
                return self.shortID
            test = FormID.UnvalidatedFormID(self.master, self.objectID).Validate(target)
            if isinstance(test, FormID.ValidFormID):
                return test.shortID
            raise TypeError(_("Attempted to set an invalid formID"))

    class EmptyFormID(ValidFormID):
        """Represents an empty FormID.

           These occur when a particular field isn't set, or is set to 0.

           Empty FormIDs are safe to use for any record in any collection.
           This class should never be instantiated except by class FormID(object)."""

        def __init__(self):
            pass

        def __hash__(self):
            return hash(0)

        def __getitem__(self, x):
            return None

        def __repr__(self):
            return "EmptyFormID(None, None)"

        def Validate(self, target):
            """No validation is needed. There's nothing to validate."""
            return self

        def GetShortFormID(self, target):
            """An empty FormID is always valid, so it isn't resolved. That's why it subclasses ValidFormID."""
            return 0

    class RawFormID(ValidFormID):
        """Represents a non-checkable FormID. Should rarely be used due to safety issues.
           This class should never be instantiated except by class FormID(object)."""

        def __init__(self, shortID):
            self.shortID = shortID

        def __hash__(self):
            return hash((self.shortID, None))

        def __getitem__(self, x):
            if x == 0: return self.shortID >> 24
            return int(self.shortID & 0x00FFFFFFL)

        def __repr__(self):
            return "RawFormID(0x%08X)" % (self.shortID,)

        def Validate(self, target):
            """No validation is possible. It is impossible to tell what collection the value came from."""
            return self

        def GetShortFormID(self, target):
            """The raw FormID isn't resolved, so it's always valid. That's why it subclasses ValidFormID."""
            return self.shortID

    def __init__(self, master, objectID=None):
        """Initializes a FormID from these possible inputs:
           CBash FormID = (int(RecordID)   , int(FormID)) Internal use by CBash / cint only!
           Long FormID  = (string(ModName) , int(ObjectID))
           FormID       = (FormID()        , None)
           Raw FormID   = (int(FormID)     , None)
           Empty FormID = (None            , None)"""

        if objectID is None:
            if isinstance(master, FormID):
                self.formID = master.formID
            elif master is None:
                self.formID = FormID.EmptyFormID()
            else:
                self.formID = FormID.RawFormID(master)
        else:
            if isinstance(master, (basestring, Path)):
                self.formID = FormID.UnvalidatedFormID(str(master), objectID)
            else:
                masterstr = _CGetLongIDName(master, objectID, 0)
                if masterstr:
                    #CBash FormID, pre-validated for its source collection
                    self.formID = FormID.ValidFormID(masterstr, objectID, objectID, _CGetCollectionIDByRecordID(master))
                else:
                    #CBash FormID, pre-invalidated for all collections
                    self.formID = FormID.InvalidFormID(objectID)

    def __hash__(self):
        return hash(self.formID)

    def __eq__(self, x):
        return x[1] == self.formID[1] and x[0] == self.formID[0]

    def __ne__(self, other):
        return x[1] != self.formID[1] or x[0] != self.formID[0]

    def __getitem__(self, x):
        if x == 0: return self.formID[0]
        return self.formID[1]

    def __setitem__(self, x, nValue):
        if x == 0:
            if nValue is None:
                self.formID = FormID.EmptyFormID()
            elif isinstance(nValue, basestring):
                self.formID = FormID.UnvalidatedFormID(nValue, self.formID[1])
            else:
                self.formID = FormID.RawFormID(nValue)
        else:
            if nValue is None:
                if self.formID[0] is None:
                    self.formID = FormID.EmptyFormID()
                else:
                    self.formID = FormID.RawFormID(self.formID[0])
            else:
                self.formID = FormID.UnvalidatedFormID(self.formID[0], nValue)

    def __len__(self):
        return 2

    def __repr__(self):
        return self.formID.__repr__()

    def __str__(self):
        return self.formID.__repr__()

    @staticmethod
    def FilterValid(formIDs, target, AsShort=False):
        if AsShort: return [x.GetShortFormID(target) for x in formIDs if x.ValidateFormID(target)]
        return [x for x in formIDs if x.ValidateFormID(target)]

    @staticmethod
    def FilterValidDict(formIDs, target, KeysAreFormIDs, ValuesAreFormIDs, AsShort=False):
        if KeysAreFormIDs:
            if ValuesAreFormIDs:
                if AsShort:
                    return dict([(key.GetShortFormID(target), value.GetShortFormID(target)) for key, value in formIDs.iteritems() if key.ValidateFormID(target) and value.ValidateFormID(target)])
                return dict([(key, value) for key, value in formIDs.iteritems() if key.ValidateFormID(target) and value.ValidateFormID(target)])                
            else:
                if AsShort:
                    return dict([(key.GetShortFormID(target), value) for key, value in formIDs.iteritems() if key.ValidateFormID(target)])
                return dict([(key, value) for key, value in formIDs.iteritems() if key.ValidateFormID(target)])
        else:
            if ValuesAreFormIDs:
                if AsShort:
                    return dict([(key, value.GetShortFormID(target)) for key, value in formIDs.iteritems() if value.ValidateFormID(target)])
                return dict([(key, value) for key, value in formIDs.iteritems() if value.ValidateFormID(target)])                
        return formIDs

    def ValidateFormID(self, target):
        """Tests whether the FormID is valid for the destination.
           The test result is saved, so work isn't duplicated if FormIDs are first
           filtered for validity before being set by CBash with GetShortFormID."""
        self.formID = self.formID.Validate(target)
        return isinstance(self.formID, FormID.ValidFormID)

    def GetShortFormID(self, target):
        """Resolves the various FormID classes to a single 32-bit value used by CBash"""
        return self.formID.GetShortFormID(target)

class ActorValue(object):
    """Represents an OBME ActorValue. It is mostly identical to a FormID in resolution.
       The difference lay in that it is only resolved if the value is >= 0x800"""

    class UnvalidatedActorValue(object):
        """Represents an unchecked ActorValue. This the most common case by far.

           These occur when:
            1) A hard-coded Long ActorValue is used
            2) A Long ActorValue from a csv file is used
            3) Any CBash ActorValue is used

           It must be tested to see if it is safe for use in a particular collection.
           This class should never be instantiated except by class ActorValue(object)."""
        def __init__(self, master, objectID):
            self.master, self.objectID = GPath(master), objectID

        def __hash__(self):
            return hash((str(self.master), self.objectID))

        def __getitem__(self, x):
            if x == 0: return self.master
            return int(self.objectID & 0x00FFFFFFL)

        def __repr__(self):
            return "UnvalidatedActorValue('%s', 0x%06X)" % (str(self.master), int(self.objectID & 0x00FFFFFFL))

        def Validate(self, target):
            """Unvalidated ActorValues have to be tested for each destination collection.
               A ActorValue is valid if its master is part of the destination collection.

               Resolved Actor Value's are not formIDs, but can be treated as such for resolution."""
            targetID = target.GetParentCollection()._CollectionID
            master = str(self.master)
            retValue = _CGetModIDByName(targetID, master)
            if retValue:
                return ActorValue.ValidActorValue(self.master, self.objectID, _CMakeShortFormID(retValue, self.objectID , 0), targetID)
            return self

        def GetShortActorValue(self, target):
            """Tries to resolve the ActorValue for the given record.
               This should only get called if the ActorValue isn't validated prior to it being used by CBash."""
            actorValue = self.Validate(target)
            if isinstance(actorValue, ActorValue.ValidActorValue):
                return actorValue.shortID
            raise TypeError(_("Attempted to set an invalid actorValue"))

    class InvalidActorValue(object):
        """Represents an unsafe ActorValue.
           The ActorValues ModIndex won't properly match with the Collection's Load Order,
           so using it would cause the wrong record to become referenced.

           These occur when CBash is told to skip new records on loading a mod.
           This is most often done for scanned mods in Wrye Bash's Bashed Patch process.

           Invalid ActorValues are unsafe to use for any record in any collection.
           This class should never be instantiated except by class ActorValue(object)."""
        def __init__(self, objectID):
            self.objectID = objectID

        def __hash__(self):
            return hash((None, self.objectID))

        def __getitem__(self, x):
            if x == 0: return None
            return int(self.objectID & 0x00FFFFFFL)

        def __repr__(self):
            return "InvalidActorValue(None, 0x%06X)" % (self.objectID,)

        def Validate(self, target):
            """No validation is needed. It's invalid."""
            return self

        def GetShortActorValue(self, target):
            """It isn't safe to use this ActorValue. Any attempt to resolve it will be wrong."""
            raise TypeError(_("Attempted to set an invalid actorValue"))

    class ValidActorValue(object):
        """Represents a safe ActorValue.

           These occur when an unvalidated ActorValue is validated for a specific record.
           Technically, the validation is good for an entire collection, but it's rare
           for the same ActorValue instance to be used for multiple records.

           This class should never be instantiated except by class ActorValue(object)."""
        def __init__(self, master, objectID, shortID, collectionID):
            self.master, self.objectID, self.shortID, self._CollectionID = master, objectID, shortID, collectionID

        def __hash__(self):
            return hash((str(self.master), self.objectID))

        def __getitem__(self, x):
            if x == 0: return self.master
            return int(self.objectID & 0x00FFFFFFL)

        def __repr__(self):
            return "ValidActorValue('%s', 0x%06X)" % (str(self.master), int(self.objectID & 0x00FFFFFFL))

        def Validate(self, target):
            """This ActorValue has already been validated for a specific record.
               It must be revalidated if the record being used doesn't match the earlier validation."""
            if target.GetParentCollection()._CollectionID == self._CollectionID:
                return self
            return ActorValue.UnvalidatedFormID(self.master, self.objectID).Validate(target)

        def GetShortActorValue(self, target):
            """This ActorValue has already been resolved for a specific record.
               It must be re-resolved if the record being used doesn't match the earlier validation."""
            if target.GetParentCollection()._CollectionID == self._CollectionID:
                return self.shortID
            test = ActorValue.UnvalidatedActorValue(self.master, self.objectID).Validate(target)
            if isinstance(test, ActorValue.ValidActorValue):
                return test.shortID
            raise TypeError(_("Attempted to set an invalid actorValue"))

    class EmptyActorValue(ValidActorValue):
        """Represents an empty ActorValue.

           These occur when a particular field isn't set, or is set to 0.

           Empty ActorValues are safe to use for any record in any collection.
           This class should never be instantiated except by class ActorValue(object)."""
        def __init__(self):
            pass

        def __hash__(self):
            return hash(0)

        def __getitem__(self, x):
            return None

        def __repr__(self):
            return "EmptyActorValue(None, None)"

        def Validate(self, target):
            """No validation is needed. There's nothing to validate."""
            return self

        def GetShortActorValue(self, target):
            """An empty ActorValue isn't resolved, because it's always valid. That's why it subclasses ValidActorValue."""
            return 0

    class RawActorValue(ValidActorValue):
        """Represents a non-checked ActorValue. It is either a static ActorValue, or a non-checkable ActorValue.
           Raw ActorValues < 0x800 (static) are safe since they aren't resolved,
           but raw values >= 0x800 should rarely be used due to safety issues.
           This class should never be instantiated except by class ActorValue(object)."""

        def __init__(self, shortID):
            self.shortID = shortID

        def __hash__(self):
            return hash((self.shortID, None))

        def __getitem__(self, x):
            if x == 0: return self.shortID >> 24
            return int(self.shortID & 0x00FFFFFFL)

        def __repr__(self):
            return "RawActorValue(0x%08X)" % (self.shortID,)

        def Validate(self, target):
            """No validation is possible. It is impossible to tell what collection the value came from."""
            return self

        def GetShortActorValue(self, target):
            """The raw ActorValue isn't resolved, so it's always valid. That's why it subclasses ValidActorValue."""
            return self.shortID


    def __init__(self, master, objectID=None):
        """Initializes an OBME ActorValue from these possible inputs:
           CBash ActorValue  = (int(RecordID)   , int(ActorValue)) Internal use by CBash / cint only!
           Long ActorValue   = (string(ModName) , int(ObjectID))
           ActorValue        = (ActorValue()    , None)
           Raw ActorValue    = (int(ActorValue) , None)
           Empty ActorValue  = (None            , None))"""

        if objectID is None:
            if isinstance(master, ActorValue): #initialize from ActorValue
                self.actorValue = master.actorValue
            elif master is None:
                self.actorValue = ActorValue.EmptyActorValue()
            else:
                self.actorValue = ActorValue.RawActorValue(master)
        else:
            if isinstance(master, (basestring, Path)):
                self.actorValue = ActorValue.UnvalidatedActorValue(str(master), objectID)
            else:
                if objectID < 0x800:
                    self.actorValue = ActorValue.RawActorValue(master, objectID) #Static ActorValue. No resolution takes place.
                else:
                    masterstr = _CGetLongIDName(master, objectID, 0)
                    if masterstr:
                        #CBash ActorValue, pre-validated for its source collection
                        self.actorValue = ActorValue.ValidActorValue(masterstr, objectID, objectID, _CGetCollectionIDByRecordID(master))
                    else:
                        #CBash ActorValue, pre-invalidated for all collections
                        self.actorValue = ActorValue.InvalidActorValue(objectID)

    def __hash__(self):
        return hash(self.actorValue)

    def __eq__(self, x):
        return x[1] == self.actorValue[1] and x[0] == self.actorValue[0]

    def __ne__(self, other):
        return x[1] != self.actorValue[1] or x[0] != self.actorValue[0]

    def __getitem__(self, x):
        if x == 0: return self.actorValue[0]
        return self.actorValue[1]

    def __setitem__(self, x, nValue):
        if x == 0:
            if nValue is None:
                self.actorValue = ActorValue.EmptyActorValue()
            elif isinstance(nValue, basestring):
                self.actorValue = ActorValue.UnvalidatedActorValue(nValue, self.actorValue[1])
            else:
                self.actorValue = ActorValue.RawActorValue(nValue)
        else:
            if nValue is None:
                if self.actorValue[0] is None:
                    self.actorValue = ActorValue.EmptyActorValue()
                else:
                    self.actorValue = ActorValue.RawActorValue(self.actorValue[0])
            else:
                if nValue < 0x800:
                    self.actorValue = ActorValue.RawActorValue(nValue)
                else:
                    self.actorValue = ActorValue.UnvalidatedActorValue(self.actorValue[0], nValue)

    def __len__(self):
        return 2

    def __repr__(self):
        return self.actorValue.__repr__()

    def __str__(self):
        return self.actorValue.__repr__()

    @staticmethod
    def FilterValid(actorValues, target, AsShort=False):
        if AsShort: return [x.GetShortActorValue(target) for x in actorValues if x.ValidateActorValue(target)]
        return [x for x in actorValues if x.ValidateActorValue(target)]

    @staticmethod
    def FilterValidDict(actorValues, target, KeysAreActorValues, ValuesAreActorValues, AsShort=False):
        if KeysAreActorValues:
            if ValuesAreActorValues:
                if AsShort:
                    return dict([(key.GetShortActorValue(target), value.GetShortFormID(target)) for key, value in actorValues.iteritems() if key.ValidateActorValue(target) and value.ValidateActorValue(target)])
                return dict([(key, value) for key, value in actorValues.iteritems() if key.ValidateActorValue(target) and value.ValidateActorValue(target)])                
            else:
                if AsShort:
                    return dict([(key.GetShortActorValue(target), value) for key, value in actorValues.iteritems() if key.ValidateActorValue(target)])
                return dict([(key, value) for key, value in actorValues.iteritems() if key.ValidateActorValue(target)])
        else:
            if ValuesAreActorValues:
                if AsShort:
                    return dict([(key, value.GetShortActorValue(target)) for key, value in actorValues.iteritems() if value.ValidateActorValue(target)])
                return dict([(key, value) for key, value in actorValues.iteritems() if value.ValidateActorValue(target)])                
        return actorValues
    
    def ValidateActorValue(self, target):
        """Tests whether the ActorValue is valid for the destination target.
           The test result is saved, so work isn't duplicated if ActorValues are first
           filtered for validity before being set by CBash with GetShortActorValue."""
        self.actorValue = self.actorValue.Validate(target)
        return isinstance(self.actorValue, ActorValue.ValidActorValue)

    def GetShortActorValue(self, target):
        """Resolves the various ActorValue classes to a single 32-bit value used by CBash"""
        return self.actorValue.GetShortActorValue(target)

class MGEFCode(object):
    """Represents an OBME MGEFCode. It is mostly identical to a FormID in resolution.
       The difference lay in that it is only resolved if the value is >= 0x80000000,
       and that the ModIndex is in the lower bits."""

    class UnvalidatedMGEFCode(object):
        """Represents an unchecked MGEFCode. This the most common case by far.

           These occur when:
            1) A hard-coded Long MGEFCode is used
            2) A Long MGEFCode from a csv file is used
            3) Any CBash MGEFCode is used

           It must be tested to see if it is safe for use in a particular collection.
           This class should never be instantiated except by class MGEFCode(object)."""
        def __init__(self, master, objectID):
            self.master, self.objectID = GPath(master), objectID

        def __hash__(self):
            return hash((str(self.master), self.objectID))

        def __getitem__(self, x):
            if x == 0: return self.master
            return int(self.objectID & 0xFFFFFF00L)

        def __repr__(self):
            return "UnvalidatedMGEFCode('%s', 0x%06X)" % (str(self.master), int(self.objectID & 0xFFFFFF00L))

        def Validate(self, target):
            """Unvalidated MGEFCodes have to be tested for each destination collection.
               A MGEFCode is valid if its master is part of the destination collection.

               Resolved MGEFCode's are not formIDs, but can be treated as such for resolution."""
            targetID = target.GetParentCollection()._CollectionID
            master = str(self.master)
            retValue = _CGetModIDByName(targetID, master)
            if retValue:
                return MGEFCode.ValidMGEFCode(self.master, self.objectID, _CMakeShortFormID(retValue, self.objectID , 1), targetID)
            return self

        def GetShortMGEFCode(self, target):
            """Tries to resolve the MGEFCode for the given record.
               This should only get called if the MGEFCode isn't validated prior to it being used by CBash."""
            mgefCode = self.Validate(target)
            if isinstance(mgefCode, MGEFCode.ValidMGEFCode):
                return mgefCode.shortID
            raise TypeError(_("Attempted to set an invalid mgefCode"))

    class InvalidMGEFCode(object):
        """Represents an unsafe MGEFCode.
           The MGEFCodes ModIndex won't properly match with the Collection's Load Order,
           so using it would cause the wrong record to become referenced.

           These occur when CBash is told to skip new records on loading a mod.
           This is most often done for scanned mods in Wrye Bash's Bashed Patch process.

           Invalid MGEFCodes are unsafe to use for any record in any collection.
           This class should never be instantiated except by class MGEFCode(object)."""
        def __init__(self, objectID):
            self.objectID = objectID

        def __hash__(self):
            return hash((None, self.objectID))

        def __getitem__(self, x):
            if x == 0: return None
            return int(self.objectID & 0xFFFFFF00L)

        def __repr__(self):
            return "InvalidMGEFCode(None, 0x%06X)" % (self.objectID,)

        def Validate(self, target):
            """No validation is needed. It's invalid."""
            return self

        def GetShortMGEFCode(self, target):
            """It isn't safe to use this MGEFCode. Any attempt to resolve it will be wrong."""
            raise TypeError(_("Attempted to set an invalid mgefCode"))

    class ValidMGEFCode(object):
        """Represents a safe MGEFCode.

           These occur when an unvalidated MGEFCode is validated for a specific record.
           Technically, the validation is good for an entire collection, but it's rare
           for the same MGEFCode instance to be used for multiple records.

           This class should never be instantiated except by class MGEFCode(object)."""
        def __init__(self, master, objectID, shortID, collectionID):
            self.master, self.objectID, self.shortID, self._CollectionID = master, objectID, shortID, collectionID

        def __hash__(self):
            return hash((str(self.master), self.objectID))

        def __getitem__(self, x):
            if x == 0: return self.master
            return int(self.objectID & 0xFFFFFF00L)

        def __repr__(self):
            return "ValidMGEFCode('%s', 0x%06X)" % (str(self.master), int(self.objectID & 0xFFFFFF00L))

        def Validate(self, target):
            """This MGEFCode has already been validated for a specific record.
               It must be revalidated if the record being used doesn't match the earlier validation."""
            if target.GetParentCollection()._CollectionID == self._CollectionID:
                return self
            return MGEFCode.UnvalidatedFormID(self.master, self.objectID).Validate(target)

        def GetShortMGEFCode(self, target):
            """This MGEFCode has already been resolved for a specific record.
               It must be re-resolved if the record being used doesn't match the earlier validation."""
            if target.GetParentCollection()._CollectionID == self._CollectionID:
                return self.shortID
            test = MGEFCode.UnvalidatedMGEFCode(self.master, self.objectID).Validate(target)
            if isinstance(test, MGEFCode.ValidMGEFCode):
                return test.shortID
            raise TypeError(_("Attempted to set an invalid mgefCode"))

    class EmptyMGEFCode(ValidMGEFCode):
        """Represents an empty MGEFCode.

           These occur when a particular field isn't set, or is set to 0.

           Empty MGEFCodes are safe to use for any record in any collection.
           This class should never be instantiated except by class MGEFCode(object)."""
        def __init__(self):
            pass

        def __hash__(self):
            return hash(0)

        def __getitem__(self, x):
            return None

        def __repr__(self):
            return "EmptyMGEFCode(None, None)"

        def Validate(self, target):
            """No validation is needed. There's nothing to validate."""
            return self

        def GetShortMGEFCode(self, target):
            """An empty MGEFCode isn't resolved, because it's always valid. That's why it subclasses ValidMGEFCode."""
            return 0

    class RawMGEFCode(ValidMGEFCode):
        """Represents a non-checked MGEFCode. It is either a static MGEFCode, or a non-checkable MGEFCode.
           Raw MGEFCodes < 0x80000000 (static) are safe since they aren't resolved,
           but raw values >= 0x80000000 should rarely be used due to safety issues.

           Without OBME, all MGEFCodes may be displayed as a 4 character sequence.
           Ex: SEFF for Script Effect

           This class should never be instantiated except by class MGEFCode(object)."""

        def __init__(self, shortID):
            self.shortID = shortID

        def __hash__(self):
            return hash((self.shortID, None))

        def __getitem__(self, x):
            if isinstance(self.shortID, basestring):
                return self.shortID
            if x == 0: return self.shortID >> 24
            return int(self.shortID & 0xFFFFFF00L)

        def __repr__(self):
            if isinstance(self.shortID, basestring):
                return "RawMGEFCode(%s)" % (self.shortID,)
            return "RawMGEFCode(0x%08X)" % (self.shortID,)

        def Validate(self, target):
            """No validation is possible. It is impossible to tell what collection the value came from."""
            return self

        def GetShortMGEFCode(self, target):
            """The raw MGEFCode isn't resolved, so it's always valid. That's why it subclasses ValidMGEFCode.
               If it is using a 4 character sequence, it needs to be cast as a 32 bit integer."""
            if isinstance(self.shortID, basestring):
                return cast(self.shortID, POINTER(c_ulong)).contents.value
            return self.shortID


    def __init__(self, master, objectID=None):
        """Initializes an OBME MGEFCode from these possible inputs:
           CBash MGEFCode  = (int(RecordID)   , int(MGEFCode)) Internal use by CBash / cint only!
           Long MGEFCode   = (string(ModName) , int(ObjectID))
           MGEFCode        = (MGEFCode()      , None)
           Raw MGEFCode    = (int(MGEFCode)   , None)
           Raw MGEFCode    = (string(MGEFCode), None)
           Empty MGEFCode  = (None            , None))"""

        if objectID is None:
            if isinstance(master, MGEFCode): #initialize from MGEFCode
                self.mgefCode = master.mgefCode
            elif master is None:
                self.mgefCode = MGEFCode.EmptyMGEFCode()
            else:
                self.mgefCode = MGEFCode.RawMGEFCode(master)
        else:
            if isinstance(master, (basestring, Path)):
                self.mgefCode = MGEFCode.UnvalidatedMGEFCode(str(master), objectID)
            else:
                if objectID < 0x80000000:
                    self.mgefCode = MGEFCode.RawMGEFCode(master, objectID) #Static MGEFCode. No resolution takes place.
                else:
                    masterstr = _CGetLongIDName(master, objectID, 1)
                    if masterstr:
                        #CBash MGEFCode, pre-validated for its source collection
                        self.mgefCode = MGEFCode.ValidMGEFCode(masterstr, objectID, objectID, _CGetCollectionIDByRecordID(master))
                    else:
                        #CBash MGEFCode, pre-invalidated for all collections
                        self.mgefCode = MGEFCode.InvalidMGEFCode(objectID)

    def __hash__(self):
        return hash(self.mgefCode)

    def __eq__(self, x):
        return x[1] == self.mgefCode[1] and x[0] == self.mgefCode[0]

    def __ne__(self, other):
        return x[1] != self.mgefCode[1] or x[0] != self.mgefCode[0]

    def __getitem__(self, x):
        if x == 0: return self.mgefCode[0]
        return self.mgefCode[1]

    def __setitem__(self, x, nValue):
        if x == 0:
            if nValue is None:
                self.mgefCode = MGEFCode.EmptyMGEFCode()
            elif isinstance(nValue, basestring):
                self.mgefCode = MGEFCode.UnvalidatedMGEFCode(nValue, self.mgefCode[1])
            else:
                self.mgefCode = MGEFCode.RawMGEFCode(nValue)
        else:
            if nValue is None:
                if self.mgefCode[0] is None:
                    self.mgefCode = MGEFCode.EmptyMGEFCode()
                else:
                    self.mgefCode = MGEFCode.RawMGEFCode(self.mgefCode[0])
            else:
                if nValue < 0x80000000:
                    self.mgefCode = MGEFCode.RawMGEFCode(nValue)
                else:
                    self.mgefCode = MGEFCode.UnvalidatedMGEFCode(self.mgefCode[0], nValue)

    def __len__(self):
        return 2

    def __repr__(self):
        return self.mgefCode.__repr__()

    def __str__(self):
        return self.mgefCode.__repr__()

    @staticmethod
    def FilterValid(mgefCodes, target, AsShort=False):
        if AsShort: return [x.GetShortMGEFCode(target) for x in mgefCodes if x.ValidateMGEFCode(target)]
        return [x for x in mgefCodes if x.ValidateMGEFCode(target)]

    @staticmethod
    def FilterValidDict(mgefCodes, target, KeysAreMGEFCodes, ValuesAreMGEFCodes, AsShort=False):
        if KeysAreMGEFCodes:
            if ValuesAreMGEFCodes:
                if AsShort:
                    return dict([(key.GetShortMGEFCode(target), value.GetShortFormID(target)) for key, value in mgefCodes.iteritems() if key.ValidateMGEFCode(target) and value.ValidateMGEFCode(target)])
                return dict([(key, value) for key, value in mgefCodes.iteritems() if key.ValidateMGEFCode(target) and value.ValidateMGEFCode(target)])                
            else:
                if AsShort:
                    return dict([(key.GetShortMGEFCode(target), value) for key, value in mgefCodes.iteritems() if key.ValidateMGEFCode(target)])
                return dict([(key, value) for key, value in mgefCodes.iteritems() if key.ValidateMGEFCode(target)])
        else:
            if ValuesAreMGEFCodes:
                if AsShort:
                    return dict([(key, value.GetShortMGEFCode(target)) for key, value in mgefCodes.iteritems() if value.ValidateMGEFCode(target)])
                return dict([(key, value) for key, value in mgefCodes.iteritems() if value.ValidateMGEFCode(target)])                
        return mgefCodes
    
    def ValidateMGEFCode(self, target):
        """Tests whether the MGEFCode is valid for the destination RecordID.
           The test result is saved, so work isn't duplicated if MGEFCodes are first
           filtered for validity before being set by CBash with GetShortMGEFCode."""
        self.mgefCode = self.mgefCode.Validate(target)
        return isinstance(self.mgefCode, MGEFCode.ValidMGEFCode)

    def GetShortMGEFCode(self, target):
        """Resolves the various MGEFCode classes to a single 32-bit value used by CBash"""
        return self.mgefCode.GetShortMGEFCode(target)

def getattr_deep(obj, attr):
    return reduce(getattr, attr.split('.'), obj)

def setattr_deep(obj, attr, value):
    attrs = attr.split('.')
    setattr(reduce(getattr, attrs[:-1], obj), attrs[-1], value)

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
        oElement = self._Type(instance._RecordID, self._FieldID)
        if(self._AsList): return tuple([getattr(oElement, attr) for attr in oElement.copyattrs])
        return oElement

    def __set__(self, instance, nElement):
        oElement = self._Type(instance._RecordID, self._FieldID)
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
        retValue = _CGetField(instance._RecordID, FieldID, 0, 0, 0, 0, 0, 0, 0)
        if(retValue): return retValue.contents.value
        return None

    def __set__(self, instance, nValue):
        FieldID = self._FieldID + instance._FieldID
        if nValue is None: _CDeleteField(instance._RecordID, FieldID, 0, 0, 0, 0, 0, 0)
        else: _CSetField(instance._RecordID, FieldID, 0, 0, 0, 0, 0, 0, byref(self._Type(nValue)), 0)

class CBashFORMID_GROUP(object):
    def __init__(self, FieldID):
        self._FieldID = FieldID

    def __get__(self, instance, owner):
        _CGetField.restype = POINTER(c_ulong)
        retValue = _CGetField(instance._RecordID, self._FieldID + instance._FieldID, 0, 0, 0, 0, 0, 0, 0)
        if(retValue): return FormID(instance._RecordID, retValue.contents.value)
        return None

    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._RecordID, self._FieldID + instance._FieldID, 0, 0, 0, 0, 0, 0)
        else: _CSetField(instance._RecordID, self._FieldID + instance._FieldID, 0, 0, 0, 0, 0, 0, byref(c_ulong(nValue.GetShortFormID(instance))), 0)

class CBashFORMID_OR_UINT32_ARRAY_GROUP(object):
    def __init__(self, FieldID, Size=None):
        self._FieldID = FieldID
        self._Size = Size

    def __get__(self, instance, owner):
        FieldID = self._FieldID + instance._FieldID
        values = []
        numRecords = _CGetFieldAttribute(instance._RecordID, FieldID, 0, 0, 0, 0, 0, 0, 1)
        if(numRecords > 0):
            cRecords = (c_ulong * numRecords)()
            _CGetField(instance._RecordID, FieldID, 0, 0, 0, 0, 0, 0, byref(cRecords))
            for x in range(numRecords):
                type = _CGetFieldAttribute(instance._RecordID, FieldID, x, 1, 0, 0, 0, 0, 2)
                if type == API_FIELDS.UINT32:
                    values.append(cRecords[x])
                elif type == API_FIELDS.FORMID:
                    values.append(FormID(instance._RecordID, cRecords[x]))
        return values

    def __set__(self, instance, nValue):
        FieldID = self._FieldID + instance._FieldID
        if nValue is None: _CDeleteField(instance._RecordID, FieldID, 0, 0, 0, 0, 0, 0)
        else:
            length = len(nValue)
            if self._Size and length != self._Size: return
            #Each element can be either a formID or UINT32, so they have to be set separately
            #Resize the list
            _CSetField(instance._RecordID, FieldID, 0, 0, 0, 0, 0, 0, 0, c_long(length))
            for x, value in enumerate(nValue):
                #Borrowing ArraySize to flag if the new value is a formID
                IsFormID = isinstance(value, FormID)
                if IsFormID:
                    value = value.GetShortFormID(instance)
                _CSetField(instance._RecordID, FieldID, x, 1, 0, 0, 0, 0, byref(c_ulong(value)), IsFormID)

class CBashUINT8ARRAY_GROUP(object):
    def __init__(self, FieldID, Size=None):
        self._FieldID = FieldID
        self._Size = Size

    def __get__(self, instance, owner):
        FieldID = self._FieldID + instance._FieldID
        numRecords = _CGetFieldAttribute(instance._RecordID, FieldID, 0, 0, 0, 0, 0, 0, 1)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            _CGetField(instance._RecordID, FieldID, 0, 0, 0, 0, 0, 0, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        return []

    def __set__(self, instance, nValue):
        FieldID = self._FieldID + instance._FieldID
        if nValue is None or not len(nValue): _CDeleteField(instance._RecordID, FieldID, 0, 0, 0, 0, 0, 0)
        else:
            length = len(nValue)
            if self._Size and length != self._Size: return
            cRecords = (c_ubyte * length)(*nValue)
            _CSetField(instance._RecordID, FieldID, 0, 0, 0, 0, 0, 0, byref(cRecords), length)

class CBashFLOAT32_GROUP(object):
    def __init__(self, FieldID):
        self._FieldID = FieldID

    def __get__(self, instance, owner):
        FieldID = self._FieldID + instance._FieldID
        _CGetField.restype = POINTER(c_float)
        retValue = _CGetField(instance._RecordID, FieldID, 0, 0, 0, 0, 0, 0, 0)
        if(retValue): return round(retValue.contents.value,6)
        return None

    def __set__(self, instance, nValue):
        FieldID = self._FieldID + instance._FieldID
        if nValue is None: _CDeleteField(instance._RecordID, FieldID, 0, 0, 0, 0, 0, 0)
        else: _CSetField(instance._RecordID, FieldID, 0, 0, 0, 0, 0, 0, byref(c_float(round(nValue,6))), 0)

class CBashSTRING_GROUP(object):
    def __init__(self, FieldID):
        self._FieldID = FieldID

    def __get__(self, instance, owner):
        FieldID = self._FieldID + instance._FieldID
        _CGetField.restype = c_char_p
        retValue = _CGetField(instance._RecordID, FieldID, 0, 0, 0, 0, 0, 0, 0)
        if(retValue): return retValue
        return None

    def __set__(self, instance, nValue):
        FieldID = self._FieldID + instance._FieldID
        if nValue is None: _CDeleteField(instance._RecordID, FieldID, 0, 0, 0, 0, 0, 0)
        else: _CSetField(instance._RecordID, FieldID, 0, 0, 0, 0, 0, 0, str(nValue), 0)

class CBashISTRING_GROUP(object):
    def __init__(self, FieldID):
        self._FieldID = FieldID

    def __get__(self, instance, owner):
        FieldID = self._FieldID + instance._FieldID
        _CGetField.restype = c_char_p
        retValue = _CGetField(instance._RecordID, FieldID, 0, 0, 0, 0, 0, 0, 0)
        if(retValue): return ISTRING(retValue)
        return None

    def __set__(self, instance, nValue):
        FieldID = self._FieldID + instance._FieldID
        if nValue is None: _CDeleteField(instance._RecordID, FieldID, 0, 0, 0, 0, 0, 0)
        else: _CSetField(instance._RecordID, FieldID, 0, 0, 0, 0, 0, 0, str(nValue), 0)

class CBashLIST_GROUP(object):
    def __init__(self, FieldID, Type, AsList=False):
        self._FieldID = FieldID
        self._Type = Type
        self._AsList = AsList

    def __get__(self, instance, owner):
        FieldID = self._FieldID + instance._FieldID
        numElements = _CGetFieldAttribute(instance._RecordID, FieldID, 0, 0, 0, 0, 0, 0, 1)
        oElements = [self._Type(instance._RecordID, FieldID, x) for x in range(0, numElements)]
        if(self._AsList): return ExtractCopyList(oElements)
        return oElements

    def __set__(self, instance, nElements):
        FieldID = self._FieldID + instance._FieldID
        if nElements is None or not len(nElements):
            _CDeleteField(instance._RecordID, FieldID, 0, 0, 0, 0, 0, 0)
        else:
            length = len(nElements)
            if isinstance(nElements[0], tuple): nValues = nElements
            else: nValues = ExtractCopyList(nElements)
            ##Resizes the list
            _CSetField(instance._RecordID, FieldID, 0, 0, 0, 0, 0, 0, 0, c_long(length))
            numElements = _CGetFieldAttribute(instance._RecordID, FieldID, 0, 0, 0, 0, 0, 0, 1)
            oElements = [self._Type(instance._RecordID, FieldID, x) for x in range(0, numElements)]
            SetCopyList(oElements, nValues)

# Top level Descriptors
class CBashLIST(object):
    def __init__(self, FieldID, Type, AsList=False):
        self._FieldID = FieldID
        self._Type = Type
        self._AsList = AsList

    def __get__(self, instance, owner):
        numElements = _CGetFieldAttribute(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 1)
        oElements = [self._Type(instance._RecordID, self._FieldID, x) for x in range(0, numElements)]
        if(self._AsList): return ExtractCopyList(oElements)
        return oElements

    def __set__(self, instance, nElements):
        if nElements is None or not len(nElements):
            _CDeleteField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0)
        else:
            length = len(nElements)
            if isinstance(nElements[0], tuple): nValues = nElements
            else: nValues = ExtractCopyList(nElements)
            ##Resizes the list
            _CSetField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 0, c_long(length))
            numElements = _CGetFieldAttribute(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 1)
            oElements = [self._Type(instance._RecordID, self._FieldID, x) for x in range(0, numElements)]
            SetCopyList(oElements, nValues)

class CBashUNKNOWN_OR_GENERIC(object):
    def __init__(self, FieldID, Type):
        self._FieldID = FieldID
        self._Type = Type
        self._ResType = POINTER(Type)

    def __get__(self, instance, owner):
        type = _CGetFieldAttribute(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 2)
        if type != API_FIELDS.UNKNOWN:
            _CGetField.restype = self._ResType
            retValue = _CGetField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 0)
            if(retValue): return retValue.contents.value
        return None

    def __set__(self, instance, nValue):
        type = _CGetFieldAttribute(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 2)
        if type != API_FIELDS.UNKNOWN:
            if nValue is None: _CDeleteField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0)
            else: _CSetField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, byref(self._Type(nValue)), 0)

class CBashXSED(object):
    """To delete the field, you have to set the current accessor to None."""
    def __init__(self, FieldID, AsOffset=False):
        self._FieldID = FieldID
        self._AsOffset = AsOffset

    def __get__(self, instance, owner):
        type = _CGetFieldAttribute(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 2)
        if self._AsOffset:
            if type == API_FIELDS.UINT32: return None #Mismatched variables
            _CGetField.restype = POINTER(c_ubyte)
        else:
            if type == API_FIELDS.UINT8: return None #Mismatched variables
            _CGetField.restype = POINTER(c_ulong)
        retValue = _CGetField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 0)
        if(retValue): return retValue.contents.value
        return None

    def __set__(self, instance, nValue):
        type = _CGetFieldAttribute(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 2)
        if nValue is None:
            if self._AsOffset:
                if type == API_FIELDS.UINT32: return #Mismatched variables
            else:
                if type == API_FIELDS.UINT8: return #Mismatched variables
            _CDeleteField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0)
        else:
            if self._AsOffset: nValue = c_ubyte(nValue)
            else: nValue = c_ulong(nValue)
            #Borrowing ArraySize to flag if the new value is an offset
            _CSetField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, byref(nValue), c_bool(self._AsOffset))

class CBashISTRINGARRAY(object):
    def __init__(self, FieldID):
        self._FieldID = FieldID

    def __get__(self, instance, owner):
        numRecords = _CGetFieldAttribute(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 1)
        if(numRecords > 0):
            cRecords = (POINTER(c_char_p) * numRecords)()
            _CGetField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, byref(cRecords))
            return [ISTRING(string_at(cRecords[x])) for x in range(0, numRecords)]
        return []

    def __set__(self, instance, nValue):
        if nValue is None or not len(nValue): _CDeleteField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0)
        else:
            length = len(nValue)
            cRecords = (c_char_p * length)(*nValue)
            _CSetField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, byref(cRecords), length)

class CBashGeneric(object):
    def __init__(self, FieldID, Type):
        self._FieldID = FieldID
        self._Type = Type
        self._ResType = POINTER(Type)

    def __get__(self, instance, owner):
        _CGetField.restype = self._ResType
        retValue = _CGetField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 0)
        if(retValue): return retValue.contents.value
        return None

    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0)
        else: _CSetField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, byref(self._Type(nValue)), 0)

class CBashFORMID(object):
    def __init__(self, FieldID):
        self._FieldID = FieldID

    def __get__(self, instance, owner):
        _CGetField.restype = POINTER(c_ulong)
        retValue = _CGetField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 0)
        if(retValue): return FormID(instance._RecordID, retValue.contents.value)
        return None

    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0)
        else: _CSetField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, byref(c_ulong(nValue.GetShortFormID(instance))), 0)

class CBashMGEFCODE(object):
    def __init__(self, FieldID):
        self._FieldID = FieldID

    def __get__(self, instance, owner):
        _CGetField.restype = POINTER(c_ulong)
        retValue = _CGetField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 0)
        if(retValue): return MGEFCode(instance._RecordID, retValue.contents.value)
        return None

    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0)
        else:
            _CSetField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, byref(c_ulong(nValue.GetShortMGEFCode(instance))), 0)

class CBashFORMIDARRAY(object):
    def __init__(self, FieldID):
        self._FieldID = FieldID

    def __get__(self, instance, owner):
        numRecords = _CGetFieldAttribute(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 1)
        if(numRecords > 0):
            cRecords = POINTER(c_ulong * numRecords)()
            _CGetField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, byref(cRecords))
            return [FormID(instance._RecordID, cRecords.contents[x]) for x in range(0, numRecords)]
        return []

    def __set__(self, instance, nValue):
        if nValue is None or not len(nValue): _CDeleteField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0)
        else:
            length = len(nValue)
            nValue = [x.GetShortFormID(instance) for x in nValue]
            cRecords = (c_ulong * length)(*nValue)
            _CSetField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, byref(cRecords), length)

class CBashFORMID_OR_UINT32(object):
    def __init__(self, FieldID):
        self._FieldID = FieldID

    def __get__(self, instance, owner):
        _CGetField.restype = POINTER(c_ulong)
        retValue = _CGetField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 0)
        if(retValue):
            type = _CGetFieldAttribute(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 2)
            if type == API_FIELDS.UINT32:
                return retValue.contents.value
            elif type == API_FIELDS.FORMID:
                return FormID(instance._RecordID, retValue.contents.value)
        return None

    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0)
        else:
            if isinstance(nValue, FormID):
                nValue = nValue.GetShortFormID(instance)
            _CSetField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, byref(c_ulong(nValue)), 0)

class CBashFORMID_OR_STRING(object):
    def __init__(self, FieldID):
        self._FieldID = FieldID

    def __get__(self, instance, owner):
        type = _CGetFieldAttribute(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 2)
        if type == API_FIELDS.FORMID:
            _CGetField.restype = POINTER(c_ulong)
            retValue = _CGetField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 0)
            if retValue: return FormID(instance._RecordID, retValue.contents.value)
        elif type == API_FIELDS.STRING:
            _CGetField.restype = c_char_p
            retValue = _CGetField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 0)
            if retValue: return retValue
        return None

    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0)
        else:
            type = _CGetFieldAttribute(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 2)
            if type == API_FIELDS.FORMID:
                _CSetField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, byref(c_ulong(nValue.GetShortFormID(instance))), 0)
            elif type == API_FIELDS.STRING:
                _CSetField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, str(nValue), 0)

class CBashFORMID_OR_UINT32_ARRAY(object):
    def __init__(self, FieldID, Size=None):
        self._FieldID = FieldID
        self._Size = Size

    def __get__(self, instance, owner):
        values = []
        numRecords = _CGetFieldAttribute(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 1)
        if(numRecords > 0):
            cRecords = (c_ulong * numRecords)()
            _CGetField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, byref(cRecords))
            for x in range(numRecords):
                type = _CGetFieldAttribute(instance._RecordID, self._FieldID, x, 1, 0, 0, 0, 0, 2)
                if type == API_FIELDS.UINT32:
                    values.append(cRecords[x])
                elif type == API_FIELDS.FORMID:
                    values.append(FormID(instance._RecordID, cRecords[x]))
        return values

    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0)
        else:
            length = len(nValue)
            if self._Size and length != self._Size: return
            #Each element can be either a formID or UINT32, so they have to be set separately
            #Resize the list
            _CSetField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 0, c_long(length))
            for x, value in enumerate(nValue):
                #Borrowing ArraySize to flag if the new value is a formID
                IsFormID = isinstance(value, FormID)
                if IsFormID:
                    value = value.GetShortFormID(instance)
                _CSetField(instance._RecordID, self._FieldID, x, 1, 0, 0, 0, 0, byref(c_ulong(value)), IsFormID)

class CBashMGEFCODE_OR_UINT32_ARRAY(object):
    def __init__(self, FieldID, Size=None):
        self._FieldID = FieldID
        self._Size = Size

    def __get__(self, instance, owner):
        values = []
        numRecords = _CGetFieldAttribute(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 1)
        if(numRecords > 0):
            cRecords = POINTER(c_ulong * numRecords)()
            _CGetField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, byref(cRecords))
            for x in range(numRecords):
                type = _CGetFieldAttribute(instance._RecordID, self._FieldID, x, 1, 0, 0, 0, 0, 2)
                if type == API_FIELDS.UINT32:
                    values.append(cRecords.contents[x])
                elif type in (API_FIELDS.STATIC_MGEFCODE, API_FIELDS.RESOLVED_MGEFCODE):
                    values.append(MGEFCode(instance._RecordID, cRecords.contents[x]))
        return values

    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0)
        else:
            length = len(nValue)
            if self._Size and length != self._Size: return
            #They are either all MGEFCodes or all UINT32's, so it can be set in one operation
            if len(nValue):
                if isinstance(nValue[0], MGEFCode):
                    nValue = [x.GetShortMGEFCode(instance) for x in nValue]
            else:
                nValue = []
            cRecords = (c_ulong * length)(*nValue)
            _CSetField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, byref(cRecords), length)

class CBashUINT8ARRAY(object):
    def __init__(self, FieldID, Size=None):
        self._FieldID = FieldID
        self._Size = Size

    def __get__(self, instance, owner):
        numRecords = _CGetFieldAttribute(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 1)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            _CGetField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        return []

    def __set__(self, instance, nValue):
        if nValue is None or not len(nValue): _CDeleteField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0)
        else:
            length = len(nValue)
            if self._Size and length != self._Size: return
            cRecords = (c_ubyte * length)(*nValue)
            _CSetField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, byref(cRecords), length)

class CBashUINT32ARRAY(object):
    def __init__(self, FieldID, Size=None):
        self._FieldID = FieldID
        self._Size = Size

    def __get__(self, instance, owner):
        numRecords = _CGetFieldAttribute(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 1)
        if(numRecords > 0):
            cRecords = POINTER(c_ulong * numRecords)()
            _CGetField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        return []

    def __set__(self, instance, nValue):
        if nValue is None or not len(nValue): _CDeleteField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0)
        else:
            length = len(nValue)
            if self._Size and length != self._Size: return
            cRecords = (c_ulong * length)(*nValue)
            _CSetField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, byref(cRecords), length)

class CBashSINT16ARRAY(object):
    def __init__(self, FieldID, Size=None):
        self._FieldID = FieldID
        self._Size = Size

    def __get__(self, instance, owner):
        numRecords = _CGetFieldAttribute(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 1)
        if(numRecords > 0):
            cRecords = POINTER(c_short * numRecords)()
            _CGetField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        return []

    def __set__(self, instance, nValue):
        if nValue is None or not len(nValue): _CDeleteField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0)
        else:
            length = len(nValue)
            if self._Size and length != self._Size: return
            cRecords = (c_short * length)(*nValue)
            _CSetField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, byref(cRecords), length)

class CBashFLOAT32(object):
    def __init__(self, FieldID):
        self._FieldID = FieldID

    def __get__(self, instance, owner):
        _CGetField.restype = POINTER(c_float)
        retValue = _CGetField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 0)
        if(retValue): return round(retValue.contents.value,6)
        return None

    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0)
        else: _CSetField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, byref(c_float(round(nValue,6))), 0)

class CBashDEGREES(object):
    def __init__(self, FieldID):
        self._FieldID = FieldID

    def __get__(self, instance, owner):
        _CGetField.restype = POINTER(c_float)
        retValue = _CGetField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 0)
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
        if nValue is None: _CDeleteField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0)
        else: _CSetField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, byref(c_float(round(nValue,6))), 0)

class CBashSTRING(object):
    def __init__(self, FieldID):
        self._FieldID = FieldID

    def __get__(self, instance, owner):
        _CGetField.restype = c_char_p
        retValue = _CGetField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 0)
        if(retValue): return retValue
        return None

    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0)
        else: _CSetField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, str(nValue), 0)

class CBashISTRING(object):
    def __init__(self, FieldID):
        self._FieldID = FieldID

    def __get__(self, instance, owner):
        _CGetField.restype = c_char_p
        retValue = _CGetField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 0)
        if(retValue): return ISTRING(retValue)
        return None

    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0)
        else: _CSetField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, str(nValue), 0)


class CBashRECORDARRAY(object):
    def __init__(self, Type, TypeName):
        self._Type = Type
        self._TypeName = cast(TypeName, POINTER(c_ulong)).contents.value

    def __get__(self, instance, owner):
        numRecords = _CGetNumRecords(instance._ModID, self._TypeName)
        if(numRecords > 0):
            cRecords = (c_ulong * numRecords)()
            _CGetRecordIDs(instance._ModID, self._TypeName, byref(cRecords))
            return [self._Type(x) for x in cRecords]
        return []

    def __set__(self, instance, nValue):
        return

class CBashSUBRECORD(object):
    def __init__(self, FieldID, Type, TypeName):
        self._FieldID = FieldID
        self._Type = Type
        self._TypeName = TypeName
        self._ResType = c_ulong

    def __get__(self, instance, owner):
        _CGetField.restype = self._ResType
        retValue = _CGetField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 0)
        if(retValue): return self._Type(retValue)
        return None

    def __set__(self, instance, nValue):
        _CGetField.restype = self._ResType
        retValue = _CGetField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 0)
        if(retValue): oSubRecord = self._Type(retValue)
        else: oSubRecord = None
        if nSubRecord is None and oSubRecord is not None: oSubRecord.DeleteRecord()
        else:
            if oSubRecord is None:
                RecordID = _CCreateRecord(instance.GetParentMod()._ModID, self._TypeName, 0, 0, instance._RecordID, c_ulong(self._CopyFlags))
                if(RecordID): oSubRecord = self._Type(RecordID)
            if oSubRecord is None:
                return
            SetCopyList(oSubRecord, ExtractCopyList(nSubRecord))

class CBashSUBRECORDARRAY(object):
    def __init__(self, FieldID, Type, TypeName):
        self._FieldID = FieldID
        self._Type = Type
        self._TypeName = TypeName

    def __get__(self, instance, owner):
        numRecords = _CGetFieldAttribute(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, 1)
        if(numRecords > 0):
            cRecords = (c_ulong * numRecords)()
            _CGetField(instance._RecordID, self._FieldID, 0, 0, 0, 0, 0, 0, byref(cRecords))
            return [self._Type(x) for x in cRecords]
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
        numElements = _CGetFieldAttribute(instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 1)
        oElements = [self._Type(instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, x) for x in range(0, numElements)]
        if(self._AsList): return ExtractCopyList(oElements)
        return oElements

    def __set__(self, instance, nElements):
        if nElements is None or not len(nElements):
            _CDeleteField(instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0)
        else:
            length = len(nElements)
            if isinstance(nElements[0], tuple): nValues = nElements
            else: nValues = ExtractCopyList(nElements)
            ##Resizes the list
            _CSetField(instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 0, c_long(length))
            numElements = _CGetFieldAttribute(instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 1)
            oElements = [self._Type(instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, x) for x in range(0, numElements)]
            SetCopyList(oElements, nValues)

class CBashGeneric_LIST(object):
    def __init__(self, ListFieldID, Type):
        self._ListFieldID = ListFieldID
        self._Type = Type
        self._ResType = POINTER(Type)

    def __get__(self, instance, owner):
        _CGetField.restype = self._ResType
        retValue = _CGetField(instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 0)
        if(retValue): return retValue.contents.value
        return None

    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0)
        else: _CSetField(instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, byref(self._Type(nValue)), 0)

class CBashFORMID_LIST(object):
    def __init__(self, ListFieldID):
        self._ListFieldID = ListFieldID

    def __get__(self, instance, owner):
        _CGetField.restype = POINTER(c_ulong)
        retValue = _CGetField(instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 0)
        if(retValue): return FormID(instance._RecordID, retValue.contents.value)
        return None

    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0)
        else: _CSetField(instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, byref(c_ulong(nValue.GetShortFormID(instance))), 0)

class CBashACTORVALUE_LIST(object):
    def __init__(self, ListFieldID):
        self._ListFieldID = ListFieldID

    def __get__(self, instance, owner):
        _CGetField.restype = POINTER(c_ulong)
        retValue = _CGetField(instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 0)
        if(retValue): return ActorValue(instance._RecordID, retValue.contents.value)
        return None

    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0)
        else:
            _CSetField(instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, byref(c_ulong(nValue.GetShortActorValue(instance))), 0)

class CBashFORMIDARRAY_LIST(object):
    def __init__(self, ListFieldID):
        self._ListFieldID = ListFieldID

    def __get__(self, instance, owner):
        numRecords = _CGetFieldAttribute(instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 1)
        if(numRecords > 0):
            cRecords = POINTER(c_ulong * numRecords)()
            _CGetField(instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, byref(cRecords))
            return [FormID(instance._RecordID, cRecords.contents[x]) for x in range(0, numRecords)]
        return []

    def __set__(self, instance, nValue):
        if nValue is None or not len(nValue): _CDeleteField(instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0)
        else:
            length = len(nValue)
            nValue = [x.GetShortFormID(instance) for x in nValue]
            cRecords = (c_ulong * length)(*nValue)
            _CSetField(instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, byref(cRecords), length)

class CBashUNKNOWN_OR_FORMID_OR_UINT32_LIST(object):
    def __init__(self, ListFieldID):
        self._ListFieldID = ListFieldID

    def __get__(self, instance, owner):
        type = _CGetFieldAttribute(instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 2)
        if type != API_FIELDS.UNKNOWN:
            _CGetField.restype = POINTER(c_ulong)
            retValue = _CGetField(instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 0)
            if(retValue):
                if type == API_FIELDS.UINT32:
                    return retValue.contents.value
                elif type == API_FIELDS.FORMID:
                    return FormID(instance._RecordID, retValue.contents.value)
        return None

    def __set__(self, instance, nValue):
        type = _CGetFieldAttribute(instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 2)
        if type != API_FIELDS.UNKNOWN:
            if nValue is None: _CDeleteField(instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0)
            else:
                if type == API_FIELDS.FORMID:
                    nValue = nValue.GetShortFormID(instance)
                _CSetField(instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, byref(c_ulong(nValue)), 0)

class CBashMGEFCODE_OR_UINT32_LIST(object):
    def __init__(self, ListFieldID):
        self._ListFieldID = ListFieldID

    def __get__(self, instance, owner):
        _CGetField.restype = POINTER(c_ulong)
        retValue = _CGetField(instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 0)
        if(retValue):
            type = _CGetFieldAttribute(instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 2)
            if type == API_FIELDS.UINT32:
                return retValue.contents.value
            elif type in (API_FIELDS.STATIC_MGEFCODE, API_FIELDS.RESOLVED_MGEFCODE):
                return MGEFCode(instance._RecordID, retValue.contents.value)
        return None

    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0)
        else:
            if isinstance(nValue, MGEFCode):
                nValue = nValue.GetShortMGEFCode(instance)
            _CSetField(instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, byref(c_ulong(nValue)), 0)

class CBashFORMID_OR_MGEFCODE_OR_ACTORVALUE_OR_UINT32_LIST(object):
    def __init__(self, ListFieldID):
        self._ListFieldID = ListFieldID

    def __get__(self, instance, owner):
        _CGetField.restype = POINTER(c_ulong)
        retValue = _CGetField(instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 0)
        if(retValue):
            type = _CGetFieldAttribute(instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 2)
            if type == (API_FIELDS.UINT32):
                return retValue.contents.value
            elif type == API_FIELDS.FORMID:
                return FormID(instance._RecordID, retValue.contents.value)
            elif type in (API_FIELDS.STATIC_ACTORVALUE, API_FIELDS.RESOLVED_ACTORVALUE):
                return ActorValue(instance._RecordID, retValue.contents.value)
            elif type in (API_FIELDS.STATIC_MGEFCODE, API_FIELDS.RESOLVED_MGEFCODE):
                return MGEFCode(instance._RecordID, retValue.contents.value)
        return None

    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0)
        else:
            type = _CGetFieldAttribute(instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 2)
            if type == API_FIELDS.FORMID and isinstance(nValue, FormID):
                nValue = nValue.GetShortFormID(instance)
            elif type in (API_FIELDS.STATIC_MGEFCODE, API_FIELDS.RESOLVED_MGEFCODE) and isinstance(nValue, MGEFCode):
                nValue = nValue.GetShortMGEFCode(instance)
            elif type in (API_FIELDS.STATIC_ACTORVALUE, API_FIELDS.RESOLVED_ACTORVALUE) and isinstance(nValue, ActorValue):
                nValue = nValue.GetShortActorValue(instance)
            _CSetField(instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, byref(c_ulong(nValue)), 0)

class CBashUINT8ARRAY_LIST(object):
    def __init__(self, ListFieldID, Size=None):
        self._ListFieldID = ListFieldID
        self._Size = Size

    def __get__(self, instance, owner):
        numRecords = _CGetFieldAttribute(instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 1)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            _CGetField(instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        return []

    def __set__(self, instance, nValue):
        if nValue is None or not len(nValue): _CDeleteField(instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0)
        else:
            length = len(nValue)
            if self._Size and length != self._Size: return
            cRecords = (c_ubyte * length)(*nValue)
            _CSetField(instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, byref(cRecords), length)

class CBashUINT32ARRAY_LIST(object):
    def __init__(self, ListFieldID, Size=None):
        self._ListFieldID = ListFieldID
        self._Size = Size
    def __get__(self, instance, owner):
        numRecords = _CGetFieldAttribute(instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 1)
        if(numRecords > 0):
            cRecords = POINTER(c_ulong * numRecords)()
            _CGetField(instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        return []
    def __set__(self, instance, nValue):
        if nValue is None or not len(nValue): _CDeleteField(instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0)
        else:
            length = len(nValue)
            if self._Size and length != self._Size: return
            cRecords = (c_ulong * length)(*nValue)
            _CSetField(instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, byref(cRecords), length)

class CBashFORMID_OR_UINT32_ARRAY_LIST(object):
    def __init__(self, ListFieldID, Size=None):
        self._ListFieldID = ListFieldID
        self._Size = Size

    def __get__(self, instance, owner):
        values = []
        numRecords = _CGetFieldAttribute(instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 1)
        if(numRecords > 0):
            cRecords = (c_ulong * numRecords)()
            _CGetField(instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, byref(cRecords))
            for x in range(numRecords):
                type = _CGetFieldAttribute(instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, x, 1, 0, 0, 2)
                if type == API_FIELDS.UINT32:
                    values.append(cRecords[x])
                elif type == API_FIELDS.FORMID:
                    values.append(FormID(instance._RecordID, cRecords[x]))
        return values

    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0)
        else:
            length = len(nValue)
            if self._Size and length != self._Size: return
            #Each element can be either a formID or UINT32, so they have to be set separately
            #Resize the list
            _CSetField(instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 0, c_long(length))
            for x, value in enumerate(nValue):
                #Borrowing ArraySize to flag if the new value is a formID
                IsFormID = isinstance(value, FormID)
                if IsFormID:
                    value = value.GetShortFormID(instance)
                _CSetField(instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, x, 1, 0, 0, byref(c_ulong(value)), IsFormID)

class CBashFLOAT32_LIST(object):
    def __init__(self, ListFieldID):
        self._ListFieldID = ListFieldID

    def __get__(self, instance, owner):
        _CGetField.restype = POINTER(c_float)
        retValue = _CGetField(instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 0)
        if(retValue): return round(retValue.contents.value,6)
        return None

    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0)
        else: _CSetField(instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, byref(c_float(round(nValue,6))), 0)

class CBashSTRING_LIST(object):
    def __init__(self, ListFieldID):
        self._ListFieldID = ListFieldID

    def __get__(self, instance, owner):
        _CGetField.restype = c_char_p
        retValue = _CGetField(instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 0)
        if(retValue): return retValue
        return None

    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0)
        else: _CSetField(instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, str(nValue), 0)

class CBashISTRING_LIST(object):
    def __init__(self, ListFieldID):
        self._ListFieldID = ListFieldID

    def __get__(self, instance, owner):
        _CGetField.restype = c_char_p
        retValue = _CGetField(instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, 0)
        if(retValue): return ISTRING(retValue)
        return None

    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0)
        else: _CSetField(instance._RecordID, instance._FieldID, instance._ListIndex, self._ListFieldID, 0, 0, 0, 0, str(nValue), 0)

# ListX2 Descriptors
class CBashLIST_LISTX2(object):
    def __init__(self, ListX2FieldID, Type, AsList=False):
        self._ListX2FieldID = ListX2FieldID
        self._Type = Type
        self._AsList = AsList

    def __get__(self, instance, owner):
        numElements = _CGetFieldAttribute(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, 1)
        oElements = [self._Type(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, x) for x in range(0, numElements)]
        if(self._AsList): return ExtractCopyList(oElements)
        return oElements

    def __set__(self, instance, nElements):
        if nElements is None or not len(nElements):
            _CDeleteField(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0)
        else:
            length = len(nElements)
            if isinstance(nElements[0], tuple): nValues = nElements
            else: nValues = ExtractCopyList(nElements)
            ##Resizes the list
            _CSetField(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, 0, c_long(length))
            numElements = _CGetFieldAttribute(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, 1)
            oElements = [self._Type(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, x) for x in range(0, numElements)]
            SetCopyList(oElements, nValues)

class CBashGeneric_LISTX2(object):
    def __init__(self, ListX2FieldID, Type):
        self._ListX2FieldID = ListX2FieldID
        self._Type = Type
        self._ResType = POINTER(Type)

    def __get__(self, instance, owner):
        _CGetField.restype = self._ResType
        retValue = _CGetField(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, 0)
        if(retValue): return retValue.contents.value
        return None

    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0)
        else: _CSetField(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, byref(self._Type(nValue)), 0)

class CBashFLOAT32_LISTX2(object):
    def __init__(self, ListX2FieldID):
        self._ListX2FieldID = ListX2FieldID

    def __get__(self, instance, owner):
        _CGetField.restype = POINTER(c_float)
        retValue = _CGetField(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, 0)
        if(retValue): return round(retValue.contents.value,6)
        return None

    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0)
        else: _CSetField(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, byref(c_float(round(nValue,6))), 0)

class CBashDEGREES_LISTX2(object):
    def __init__(self, ListX2FieldID):
        self._ListX2FieldID = ListX2FieldID

    def __get__(self, instance, owner):
        _CGetField.restype = POINTER(c_float)
        retValue = _CGetField(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, 0)
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
        if nValue is None: _CDeleteField(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0)
        else: _CSetField(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, byref(c_float(round(nValue,6))), 0)

class CBashUINT8ARRAY_LISTX2(object):
    def __init__(self, ListX2FieldID, Size=None):
        self._ListX2FieldID = ListX2FieldID
        self._Size = Size

    def __get__(self, instance, owner):
        numRecords = _CGetFieldAttribute(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, 1)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            _CGetField(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        return []

    def __set__(self, instance, nValue):
        if nValue is None or not len(nValue): _CDeleteField(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0)
        else:
            length = len(nValue)
            if self._Size and length != self._Size: return
            cRecords = (c_ubyte * length)(*nValue)
            _CSetField(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, byref(cRecords), length)

class CBashFORMID_OR_UINT32_ARRAY_LISTX2(object):
    def __init__(self, ListX2FieldID, Size=None):
        self._ListX2FieldID = ListX2FieldID
        self._Size = Size

    def __get__(self, instance, owner):
        values = []
        numRecords = _CGetFieldAttribute(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, 1)
        if(numRecords > 0):
            cRecords = (c_ulong * numRecords)()
            _CGetField(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, byref(cRecords))
            for x in range(numRecords):
                type = _CGetFieldAttribute(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, x, 1, 2)
                if type == API_FIELDS.UINT32:
                    values.append(cRecords[x])
                elif type == API_FIELDS.FORMID:
                    values.append(FormID(instance._RecordID, cRecords[x]))
        return values

    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0)
        else:
            length = len(nValue)
            if self._Size and length != self._Size: return
            #Each element can be either a formID or UINT32, so they have to be set separately
            #Resize the list
            _CSetField(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, 0, c_long(length))
            for x, value in enumerate(nValue):
                #Borrowing ArraySize to flag if the new value is a formID
                IsFormID = isinstance(value, FormID)
                if IsFormID:
                    value = value.GetShortFormID(instance)
                _CSetField(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, x, 1, byref(c_ulong(value)), IsFormID)

class CBashFORMID_LISTX2(object):
    def __init__(self, ListX2FieldID):
        self._ListX2FieldID = ListX2FieldID

    def __get__(self, instance, owner):
        _CGetField.restype = POINTER(c_ulong)
        retValue = _CGetField(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, 0)
        if(retValue): return FormID(instance._RecordID, retValue.contents.value)
        return None

    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0)
        else: _CSetField(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, byref(c_ulong(nValue.GetShortFormID(instance))), 0)

class CBashFORMID_OR_FLOAT32_LISTX2(object):
    def __init__(self, ListX2FieldID):
        self._ListX2FieldID = ListX2FieldID

    def __get__(self, instance, owner):
        type = _CGetFieldAttribute(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, 2)
        if type == API_FIELDS.FLOAT32:
            _CGetField.restype = POINTER(c_float)
            retValue = _CGetField(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, 0)
            if(retValue): return round(retValue.contents.value,6)
        else:
            _CGetField.restype = POINTER(c_ulong)
            retValue = _CGetField(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, 0)
            if(retValue): return FormID(instance._RecordID, retValue.contents.value)
        return None

    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0)
        else:
            type = _CGetFieldAttribute(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, 2)
            if type == API_FIELDS.FLOAT32:
                try:
                    value = float(nValue)
                except TypeError:
                    return
                _CSetField(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, byref(c_float(round(value,6))), 0)
            else:
                try:
                    value = nValue.GetShortFormID(instance)
                except TypeError:
                    return
                _CSetField(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, byref(c_ulong(value)), 0)

class CBashSTRING_LISTX2(object):
    def __init__(self, ListX2FieldID):
        self._ListX2FieldID = ListX2FieldID

    def __get__(self, instance, owner):
        _CGetField.restype = c_char_p
        retValue = _CGetField(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, 0)
        if(retValue): return retValue
        return None

    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0)
        else: _CSetField(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, str(nValue), 0)

class CBashISTRING_LISTX2(object):
    def __init__(self, ListX2FieldID):
        self._ListX2FieldID = ListX2FieldID

    def __get__(self, instance, owner):
        _CGetField.restype = c_char_p
        retValue = _CGetField(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, 0)
        if(retValue): return ISTRING(retValue)
        return None

    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0)
        else: _CSetField(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, str(nValue), 0)

class CBashUNKNOWN_OR_FORMID_OR_UINT32_LISTX2(object):
    def __init__(self, ListX2FieldID):
        self._ListX2FieldID = ListX2FieldID

    def __get__(self, instance, owner):
        type = _CGetFieldAttribute(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, 2)
        if type != API_FIELDS.UNKNOWN:
            _CGetField.restype = POINTER(c_ulong)
            retValue = _CGetField(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, 0)
            if(retValue):
                if type == API_FIELDS.UINT32:
                    return retValue.contents.value
                elif type == API_FIELDS.FORMID:
                    return FormID(instance._RecordID, retValue.contents.value)
        return None

    def __set__(self, instance, nValue):
        type = _CGetFieldAttribute(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, 2)
        if type != API_FIELDS.UNKNOWN:
            if nValue is None: _CDeleteField(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0)
            else:
                if type == API_FIELDS.FORMID:
                    nValue = nValue.GetShortFormID(instance)
                _CSetField(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, self._ListX2FieldID, 0, 0, byref(c_ulong(nValue)), 0)

# ListX3 Descriptors
class CBashGeneric_LISTX3(object):
    def __init__(self, ListX3FieldID, Type):
        self._ListX3FieldID = ListX3FieldID
        self._Type = Type
        self._ResType = POINTER(Type)

    def __get__(self, instance, owner):
        _CGetField.restype = self._ResType
        retValue = _CGetField(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, instance._ListX2FieldID, instance._ListX3Index, self._ListX3FieldID, 0)
        if(retValue): return retValue.contents.value
        return None

    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, instance._ListX2FieldID, instance._ListX3Index, self._ListX3FieldID)
        else: _CSetField(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, instance._ListX2FieldID, instance._ListX3Index, self._ListX3FieldID, byref(self._Type(nValue)), 0)

class CBashUINT8ARRAY_LISTX3(object):
    def __init__(self, ListX3FieldID, Size=None):
        self._ListX3FieldID = ListX3FieldID
        self._Size = Size

    def __get__(self, instance, owner):
        numRecords = _CGetFieldAttribute(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, instance._ListX2FieldID, instance._ListX3Index, self._ListX3FieldID, 1)
        if(numRecords > 0):
            cRecords = POINTER(c_ubyte * numRecords)()
            _CGetField(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, instance._ListX2FieldID, instance._ListX3Index, self._ListX3FieldID, byref(cRecords))
            return [cRecords.contents[x] for x in range(0, numRecords)]
        return []

    def __set__(self, instance, nValue):
        if nValue is None or not len(nValue): _CDeleteField(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, instance._ListX2FieldID, instance._ListX3Index, self._ListX3FieldID)
        else:
            length = len(nValue)
            if self._Size and length != self._Size: return
            cRecords = (c_ubyte * length)(*nValue)
            _CSetField(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, instance._ListX2FieldID, instance._ListX3Index, self._ListX3FieldID, byref(cRecords), length)

class CBashFORMID_OR_FLOAT32_LISTX3(object):
    def __init__(self, ListX3FieldID):
        self._ListX3FieldID = ListX3FieldID
    def __get__(self, instance, owner):
        type = _CGetFieldAttribute(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, instance._ListX2FieldID, instance._ListX3Index, self._ListX3FieldID, 2)
        if type == API_FIELDS.FLOAT32:
            _CGetField.restype = POINTER(c_float)
            retValue = _CGetField(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, instance._ListX2FieldID, instance._ListX3Index, self._ListX3FieldID, 0)
            if(retValue): return round(retValue.contents.value,6)
        else:
            _CGetField.restype = POINTER(c_ulong)
            retValue = _CGetField(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, instance._ListX2FieldID, instance._ListX3Index, self._ListX3FieldID, 0)
            if(retValue): return FormID(instance._RecordID, retValue.contents.value)
        return None
    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, instance._ListX2FieldID, instance._ListX3Index, self._ListX3FieldID)
        else:
            type = _CGetFieldAttribute(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, instance._ListX2FieldID, instance._ListX3Index, self._ListX3FieldID, 2)
            if type == API_FIELDS.FLOAT32:
                try:
                    value = float(nValue)
                except TypeError:
                    return
                _CSetField(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, instance._ListX2FieldID, instance._ListX3Index, self._ListX3FieldID, byref(c_float(round(value,6))), 0)
            else:
                try:
                    value = nValue.GetShortFormID(instance)
                except TypeError:
                    return
                _CSetField(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, instance._ListX2FieldID, instance._ListX3Index, self._ListX3FieldID, byref(c_ulong(value)), 0)

class CBashFLOAT32_LISTX3(object):
    def __init__(self, ListX3FieldID):
        self._ListX3FieldID = ListX3FieldID

    def __get__(self, instance, owner):
        _CGetField.restype = POINTER(c_float)
        retValue = _CGetField(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, instance._ListX2FieldID, instance._ListX3Index, self._ListX3FieldID, 0)
        if(retValue): return round(retValue.contents.value,6)
        return None

    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, instance._ListX2FieldID, instance._ListX3Index, self._ListX3FieldID)
        else: _CSetField(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, instance._ListX2FieldID, instance._ListX3Index, self._ListX3FieldID, byref(c_float(round(nValue,6))), 0)

class CBashSTRING_LISTX3(object):
    def __init__(self, ListX3FieldID):
        self._ListX3FieldID = ListX3FieldID

    def __get__(self, instance, owner):
        _CGetField.restype = c_char_p
        retValue = _CGetField(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, instance._ListX2FieldID, instance._ListX3Index, self._ListX3FieldID, 0)
        if(retValue): return retValue
        return None

    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, instance._ListX2FieldID, instance._ListX3Index, self._ListX3FieldID)
        else: _CSetField(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, instance._ListX2FieldID, instance._ListX3Index, self._ListX3FieldID, str(nValue), 0)

class CBashISTRING_LISTX3(object):
    def __init__(self, ListX3FieldID):
        self._ListX3FieldID = ListX3FieldID

    def __get__(self, instance, owner):
        _CGetField.restype = c_char_p
        retValue = _CGetField(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, instance._ListX2FieldID, instance._ListX3Index, self._ListX3FieldID, 0)
        if(retValue): return ISTRING(retValue)
        return None

    def __set__(self, instance, nValue):
        if nValue is None: _CDeleteField(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, instance._ListX2FieldID, instance._ListX3Index, self._ListX3FieldID)
        else: _CSetField(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, instance._ListX2FieldID, instance._ListX3Index, self._ListX3FieldID, str(nValue), 0)

class CBashUNKNOWN_OR_FORMID_OR_UINT32_LISTX3(object):
    def __init__(self, ListX3FieldID):
        self._ListX3FieldID = ListX3FieldID

    def __get__(self, instance, owner):
        type = _CGetFieldAttribute(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, instance._ListX2FieldID, instance._ListX3Index, self._ListX3FieldID, 2)
        if type != API_FIELDS.UNKNOWN:
            _CGetField.restype = POINTER(c_ulong)
            retValue = _CGetField(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, instance._ListX2FieldID, instance._ListX3Index, self._ListX3FieldID, 0)
            if(retValue):
                if type == API_FIELDS.UINT32:
                    return retValue.contents.value
                elif type == API_FIELDS.FORMID:
                    return FormID(instance._RecordID, retValue.contents.value)
        return None

    def __set__(self, instance, nValue):
        type = _CGetFieldAttribute(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, instance._ListX2FieldID, instance._ListX3Index, self._ListX3FieldID, 2)
        if type != API_FIELDS.UNKNOWN:
            if nValue is None: _CDeleteField(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, instance._ListX2FieldID, instance._ListX3Index, self._ListX3FieldID)
            else:
                if type == API_FIELDS.FORMID:
                    nValue = nValue.GetShortFormID(instance)
                _CSetField(instance._RecordID, instance._FieldID, instance._ListIndex, instance._ListFieldID, instance._ListX2Index, instance._ListX2FieldID, instance._ListX3Index, self._ListX3FieldID, byref(c_ulong(nValue)), 0)

#Record accessors
#--Accessor Components
class BaseComponent(object):
    def __init__(self, RecordID, FieldID):
        self._RecordID = RecordID
        self._FieldID = FieldID

    def GetParentCollection(self):
        return ObCollection(_CGetCollectionIDByRecordID(self._RecordID))

class ListComponent(object):
    def __init__(self, RecordID, FieldID, ListIndex):
        self._RecordID = RecordID
        self._FieldID = FieldID
        self._ListIndex = ListIndex

    def GetParentCollection(self):
        return ObCollection(_CGetCollectionIDByRecordID(self._RecordID))

class ListX2Component(object):
    def __init__(self, RecordID, FieldID, ListIndex, ListFieldID, ListX2Index):
        self._RecordID = RecordID
        self._FieldID = FieldID
        self._ListIndex = ListIndex
        self._ListFieldID = ListFieldID
        self._ListX2Index = ListX2Index

    def GetParentCollection(self):
        return ObCollection(_CGetCollectionIDByRecordID(self._RecordID))

class ListX3Component(object):
    def __init__(self, RecordID, FieldID, ListIndex, ListFieldID, ListX2Index, ListX2FieldID, ListX3Index):
        self._RecordID = RecordID
        self._FieldID = FieldID
        self._ListIndex = ListIndex
        self._ListFieldID = ListFieldID
        self._ListX2Index = ListX2Index
        self._ListX2FieldID = ListX2FieldID
        self._ListX3Index = ListX3Index

    def GetParentCollection(self):
        return ObCollection(_CGetCollectionIDByRecordID(self._RecordID))

class Model(BaseComponent):
    ISTRING_GROUPEDMACRO(modPath, 0)
    FLOAT32_GROUPEDMACRO(modb, 1)
    UINT8_ARRAY_GROUPEDMACRO(modt_p, 2)
    copyattrs = ['modPath', 'modb', 'modt_p']
    exportattrs = ['modPath', 'modb']#, 'modt_p']

class Item(ListComponent):
    FORMID_LISTMACRO(item, 1)
    SINT32_LISTMACRO(count, 2)
    exportattrs = copyattrs = ['item', 'count']

class FNVItem(ListComponent):
    FORMID_LISTMACRO(item, 1)
    SINT32_LISTMACRO(count, 2)
    FORMID_LISTMACRO(owner, 3)
    UNKNOWN_OR_FORMID_OR_UINT32_LISTMACRO(globalOrRank, 4)
    FLOAT32_LISTMACRO(condition, 5)
    exportattrs = copyattrs = ['item', 'count', 'owner',
                               'globalOrRank', 'condition']

class Condition(ListComponent):
    UINT8_FLAG_TYPE_LISTMACRO(operType, 1)
    UINT8_ARRAY_LISTMACRO(unused1, 2, 3)
    FLOAT32_LISTMACRO(compValue, 3)
    UINT32_TYPE_LISTMACRO(ifunc, 4)
    UNKNOWN_OR_FORMID_OR_UINT32_LISTMACRO(param1, 5)
    UNKNOWN_OR_FORMID_OR_UINT32_LISTMACRO(param2, 6)
    UINT8_ARRAY_LISTMACRO(unused2, 7, 4)
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

class FNVCondition(ListComponent):
    UINT8_FLAG_TYPE_LISTMACRO(operType, 1)
    UINT8_ARRAY_LISTMACRO(unused1, 2, 3)
    FLOAT32_LISTMACRO(compValue, 3)
    UINT32_TYPE_LISTMACRO(ifunc, 4)
    UNKNOWN_OR_FORMID_OR_UINT32_LISTMACRO(param1, 5)
    UNKNOWN_OR_FORMID_OR_UINT32_LISTMACRO(param2, 6)
    UINT32_TYPE_LISTMACRO(runOn, 7)
    UNKNOWN_OR_FORMID_OR_UINT32_LISTMACRO(reference, 8)
    MaskedTypeMACRO(IsEqual, operType, 0xF0, 0x00, IsNotEqual)
    MaskedTypeMACRO(IsNotEqual, operType, 0xF0, 0x20, IsEqual)
    MaskedTypeMACRO(IsGreater, operType, 0xF0, 0x40, IsEqual)
    MaskedTypeMACRO(IsGreaterOrEqual, operType, 0xF0, 0x60, IsEqual)
    MaskedTypeMACRO(IsLess, operType, 0xF0, 0x80, IsEqual)
    MaskedTypeMACRO(IsLessOrEqual, operType, 0xF0, 0xA0, IsEqual)
    BasicFlagMACRO(IsOr, operType, 0x01)
    BasicFlagMACRO(IsRunOnTarget, operType, 0x02)
    BasicFlagMACRO(IsUseGlobal, operType, 0x04)
    BasicTypeMACRO(IsResultOnSubject, runOn, 0, IsResultOnTarget)
    BasicTypeMACRO(IsResultOnTarget, runOn, 1, IsResultOnSubject)
    BasicTypeMACRO(IsResultOnReference, runOn, 2, IsResultOnSubject)
    BasicTypeMACRO(IsResultOnCombatTarget, runOn, 3, IsResultOnSubject)
    BasicTypeMACRO(IsResultOnLinkedReference, runOn, 4, IsResultOnSubject)
    exportattrs = copyattrs = ['operType', 'compValue', 'ifunc', 'param1',
                               'param2', 'runOn', 'reference']

class FNVConditionX2(ListX2Component):
    UINT8_FLAG_TYPE_LISTX2MACRO(operType, 1)
    UINT8_ARRAY_LISTX2MACRO(unused1, 2, 3)
    FORMID_OR_FLOAT32_LISTX2MACRO(compValue, 3)
    UINT32_TYPE_LISTX2MACRO(ifunc, 4)
    UNKNOWN_OR_FORMID_OR_UINT32_LISTX2MACRO(param1, 5)
    UNKNOWN_OR_FORMID_OR_UINT32_LISTX2MACRO(param2, 6)
    UINT32_TYPE_LISTX2MACRO(runOn, 7)
    UNKNOWN_OR_FORMID_OR_UINT32_LISTX2MACRO(reference, 8)
    MaskedTypeMACRO(IsEqual, operType, 0xF0, 0x00, IsNotEqual)
    MaskedTypeMACRO(IsNotEqual, operType, 0xF0, 0x20, IsEqual)
    MaskedTypeMACRO(IsGreater, operType, 0xF0, 0x40, IsEqual)
    MaskedTypeMACRO(IsGreaterOrEqual, operType, 0xF0, 0x60, IsEqual)
    MaskedTypeMACRO(IsLess, operType, 0xF0, 0x80, IsEqual)
    MaskedTypeMACRO(IsLessOrEqual, operType, 0xF0, 0xA0, IsEqual)
    BasicFlagMACRO(IsOr, operType, 0x01)
    BasicFlagMACRO(IsRunOnTarget, operType, 0x02)
    BasicFlagMACRO(IsUseGlobal, operType, 0x04)
    BasicTypeMACRO(IsResultOnSubject, runOn, 0, IsResultOnTarget)
    BasicTypeMACRO(IsResultOnTarget, runOn, 1, IsResultOnSubject)
    BasicTypeMACRO(IsResultOnReference, runOn, 2, IsResultOnSubject)
    BasicTypeMACRO(IsResultOnCombatTarget, runOn, 3, IsResultOnSubject)
    BasicTypeMACRO(IsResultOnLinkedReference, runOn, 4, IsResultOnSubject)
    exportattrs = copyattrs = ['operType', 'compValue', 'ifunc', 'param1',
                               'param2', 'runOn', 'reference']

class FNVConditionX3(ListX3Component):
    UINT8_FLAG_TYPE_LISTX3MACRO(operType, 1)
    UINT8_ARRAY_LISTX3MACRO(unused1, 2, 3)
    FORMID_OR_FLOAT32_LISTX3MACRO(compValue, 3)
    UINT32_TYPE_LISTX3MACRO(ifunc, 4)
    UNKNOWN_OR_FORMID_OR_UINT32_LISTX3MACRO(param1, 5)
    UNKNOWN_OR_FORMID_OR_UINT32_LISTX3MACRO(param2, 6)
    UINT32_TYPE_LISTX3MACRO(runOn, 7)
    UNKNOWN_OR_FORMID_OR_UINT32_LISTX3MACRO(reference, 8)
    MaskedTypeMACRO(IsEqual, operType, 0xF0, 0x00, IsNotEqual)
    MaskedTypeMACRO(IsNotEqual, operType, 0xF0, 0x20, IsEqual)
    MaskedTypeMACRO(IsGreater, operType, 0xF0, 0x40, IsEqual)
    MaskedTypeMACRO(IsGreaterOrEqual, operType, 0xF0, 0x60, IsEqual)
    MaskedTypeMACRO(IsLess, operType, 0xF0, 0x80, IsEqual)
    MaskedTypeMACRO(IsLessOrEqual, operType, 0xF0, 0xA0, IsEqual)
    BasicFlagMACRO(IsOr, operType, 0x01)
    BasicFlagMACRO(IsRunOnTarget, operType, 0x02)
    BasicFlagMACRO(IsUseGlobal, operType, 0x04)
    BasicTypeMACRO(IsResultOnSubject, runOn, 0, IsResultOnTarget)
    BasicTypeMACRO(IsResultOnTarget, runOn, 1, IsResultOnSubject)
    BasicTypeMACRO(IsResultOnReference, runOn, 2, IsResultOnSubject)
    BasicTypeMACRO(IsResultOnCombatTarget, runOn, 3, IsResultOnSubject)
    BasicTypeMACRO(IsResultOnLinkedReference, runOn, 4, IsResultOnSubject)
    exportattrs = copyattrs = ['operType', 'compValue', 'ifunc', 'param1',
                               'param2', 'runOn', 'reference']

class Var(ListComponent):
    UINT32_LISTMACRO(index, 1)
    UINT8_ARRAY_LISTMACRO(unused1, 2, 12)
    UINT8_FLAG_LISTMACRO(flags, 3)
    UINT8_ARRAY_LISTMACRO(unused2, 4, 7)
    ISTRING_LISTMACRO(name, 5)

    BasicFlagMACRO(IsLongOrShort, flags, 0x00000001)
    exportattrs = copyattrs = ['index', 'flags', 'name']

class VarX2(ListX2Component):
    UINT32_LISTX2MACRO(index, 1)
    UINT8_ARRAY_LISTX2MACRO(unused1, 2, 12)
    UINT8_FLAG_LISTX2MACRO(flags, 3)
    UINT8_ARRAY_LISTX2MACRO(unused2, 4, 7)
    ISTRING_LISTX2MACRO(name, 5)

    BasicFlagMACRO(IsLongOrShort, flags, 0x00000001)
    exportattrs = copyattrs = ['index', 'flags', 'name']

class VarX3(ListX3Component):
    UINT32_LISTX3MACRO(index, 1)
    UINT8_ARRAY_LISTX3MACRO(unused1, 2, 12)
    UINT8_FLAG_LISTX3MACRO(flags, 3)
    UINT8_ARRAY_LISTX3MACRO(unused2, 4, 7)
    ISTRING_LISTX3MACRO(name, 5)

    BasicFlagMACRO(IsLongOrShort, flags, 0x00000001)
    exportattrs = copyattrs = ['index', 'flags', 'name']

class Effect(ListComponent):
    ##name0 and name are both are always the same value, so setting one will set both. They're basically aliases
    MGEFCODE_OR_UINT32_LISTMACRO(name0, 1)
    MGEFCODE_OR_UINT32_LISTMACRO(name, 2)
    UINT32_LISTMACRO(magnitude, 3)
    UINT32_LISTMACRO(area, 4)
    UINT32_LISTMACRO(duration, 5)
    UINT32_LISTMACRO(rangeType, 6)
    OBMEFORMID_OR_MGEFCODE_OR_ACTORVALUE_OR_UINT32_LISTMACRO(actorValue, 7)
    OBMEFORMID_OR_MGEFCODE_OR_ACTORVALUE_OR_UINT32_LISTMACRO(script, 8)
    UINT32_LISTMACRO(school, 9)
    OBMEMGEFCODE_OR_UINT32_LISTMACRO(visual, 10)
    UINT8_FLAG_LISTMACRO(flags, 11)
    UINT8_ARRAY_LISTMACRO(unused1, 12, 3)
    OBMESTRING_LISTMACRO(full, 13)
    ##OBME Fields. Setting any of the below fields will make the mod require JRoush's OBME plugin for OBSE
    ##To see if OBME is in use, check the recordVersion field for a non-None value
    OBMEUINT8_LISTMACRO(recordVersion, 14)
    OBMEUINT8_LISTMACRO(betaVersion, 15)
    OBMEUINT8_LISTMACRO(minorVersion, 16)
    OBMEUINT8_LISTMACRO(majorVersion, 17)
    OBMEUINT8_LISTMACRO(efitParamInfo, 18)
    OBMEUINT8_LISTMACRO(efixParamInfo, 19)
    OBMEUINT8_ARRAY_LISTMACRO(reserved1, 20, 0xA)
    OBMEISTRING_LISTMACRO(iconPath, 21)
    ##If efixOverrides ever equals 0, the EFIX chunk will become unloaded
    ##This includes the fields: efixOverrides,  efixFlags, baseCost, resistAV, reserved2
    OBMEUINT32_FLAG_LISTMACRO(efixOverrides, 22)
    OBMEUINT32_FLAG_LISTMACRO(efixFlags, 23)
    OBMEFLOAT32_LISTMACRO(baseCost, 24)
    OBMEACTORVALUE_LISTMACRO(resistAV, 25)
    OBMEUINT8_ARRAY_LISTMACRO(reserved2, 26, 0x10)
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

class FNVEffect(ListComponent):
    FORMID_LISTMACRO(effect, 1)
    UINT32_LISTMACRO(magnitude, 2)
    UINT32_LISTMACRO(area, 3)
    UINT32_LISTMACRO(duration, 4)
    UINT32_LISTMACRO(rangeType, 5)
    SINT32_LISTMACRO(actorValue, 6)

    LIST_LISTMACRO(conditions, 7, FNVConditionX2)

    BasicTypeMACRO(IsSelf, rangeType, 0, IsTouch)
    BasicTypeMACRO(IsTouch, rangeType, 1, IsSelf)
    BasicTypeMACRO(IsTarget, rangeType, 2, IsSelf)
    exportattrs = copyattrs = ['effect', 'magnitude', 'area', 'duration',
                               'rangeType', 'actorValue', 'conditions_list']

class Faction(ListComponent):
    FORMID_LISTMACRO(faction, 1)
    UINT8_LISTMACRO(rank, 2)
    UINT8_ARRAY_LISTMACRO(unused1, 3, 3)
    exportattrs = copyattrs = ['faction', 'rank']

class Relation(ListComponent):
    FORMID_LISTMACRO(faction, 1)
    SINT32_LISTMACRO(mod, 2)
    exportattrs = copyattrs = ['faction', 'mod']

class FNVRelation(ListComponent):
    FORMID_LISTMACRO(faction, 1)
    SINT32_LISTMACRO(mod, 2)
    UINT32_TYPE_LISTMACRO(groupReactionType, 3)

    BasicTypeMACRO(IsNeutral, groupReactionType, 0, IsEnemy)
    BasicTypeMACRO(IsEnemy, groupReactionType, 1, IsNeutral)
    BasicTypeMACRO(IsAlly, groupReactionType, 2, IsNeutral)
    BasicTypeMACRO(IsFriend, groupReactionType, 3, IsNeutral)
    exportattrs = copyattrs = ['faction', 'mod', 'groupReactionType']

class FNVAltTexture(ListComponent):
    STRING_LISTMACRO(name, 1)
    FORMID_LISTMACRO(texture, 2)
    SINT32_LISTMACRO(index, 3)
    exportattrs = copyattrs = ['name', 'texture', 'index']

class FNVDestructable(BaseComponent):
    class Stage(ListComponent):
        UINT8_LISTMACRO(health, 1)
        UINT8_LISTMACRO(index, 2)
        UINT8_LISTMACRO(stage, 3)
        UINT8_FLAG_LISTMACRO(flags, 4)
        SINT32_LISTMACRO(dps, 5)
        FORMID_LISTMACRO(explosion, 6)
        FORMID_LISTMACRO(debris, 7)
        SINT32_LISTMACRO(debrisCount, 8)
        ISTRING_LISTMACRO(modPath, 9)
        UINT8_ARRAY_LISTMACRO(modt_p, 10)

        BasicFlagMACRO(IsCapDamage, flags, 0x01)
        BasicFlagMACRO(IsDisable, flags, 0x02)
        BasicFlagMACRO(IsDestroy, flags, 0x04)
        exportattrs = copyattrs = ['health', 'index', 'stage',
                                   'flags', 'dps', 'explosion',
                                   'debris', 'debrisCount',
                                   'modPath', 'modt_p']

    SINT32_GROUPEDMACRO(health, 0)
    UINT8_GROUPEDMACRO(count, 1)
    UINT8_FLAG_GROUPEDMACRO(flags, 2)
    UINT8_ARRAY_GROUPEDMACRO(unused1, 3, 2)

    LIST_GROUPEDMACRO(stages, 4, Stage)
    BasicFlagMACRO(IsVATSTargetable, flags, 0x01)
    exportattrs = copyattrs = ['health', 'count', 'flags', 'stages_list']

class WorldModel(BaseComponent):
    ISTRING_GROUPEDMACRO(modPath, 0)
    UINT8_ARRAY_GROUPEDMACRO(modt_p, 1)

    LIST_GROUPEDMACRO(altTextures, 2, FNVAltTexture)
    copyattrs = ['modPath', 'modt_p', 'altTextures_list']
    exportattrs = ['modPath', 'altTextures_list']#, 'modt_p']

class PGRP(ListComponent):
    FLOAT32_LISTMACRO(x, 1)
    FLOAT32_LISTMACRO(y, 2)
    FLOAT32_LISTMACRO(z, 3)
    UINT8_LISTMACRO(connections, 4)
    UINT8_ARRAY_LISTMACRO(unused1, 5, 3)
    exportattrs = copyattrs = ['x', 'y', 'z', 'connections']

#--Accessors
#--Fallout New Vegas
class FnvBaseRecord(object):
    _Type = 'BASE'
    def __init__(self, RecordID):
        self._RecordID = RecordID

    def __eq__(self, other):
        if type(other) is type(self):
            return self._RecordID == other._RecordID
        return False

    def __ne__(self, other):
        return not self.__eq__(other)

    def GetParentMod(self):
        return FnvModFile(_CGetModIDByRecordID(self._RecordID))

    def GetParentCollection(self):
        return ObCollection(_CGetCollectionIDByRecordID(self._RecordID))

    def ResetRecord(self):
        _CResetRecord(self._RecordID)

    def UnloadRecord(self):
        _CUnloadRecord(self._RecordID)

    def DeleteRecord(self):
        _CDeleteRecord(self._RecordID)

    def GetRecordUpdatedReferences(self):
        return _CGetRecordUpdatedReferences(0, self._RecordID)

    def UpdateReferences(self, Old_NewFormIDs):
        Old_NewFormIDs = FormID.FilterValidDict(Old_NewFormIDs, self, True, True)
        length = len(Old_NewFormIDs)
        if length != len(Old_NewFormIDs):
            return []
        OldFormIDs = (c_ulong * length)(*Old_NewFormIDs.keys())
        NewFormIDs = (c_ulong * length)(*Old_NewFormIDs.values())
        Changes = (c_ulong * length)()
        _CUpdateReferences(0, self._RecordID, OldFormIDs, NewFormIDs, byref(Changes), length)
        return [x for x in Changes]

    def History(self):
        cRecordIDs = (c_ulong * 257)() #just allocate enough for the max number + size
        numRecords = _CGetRecordHistory(self._RecordID, byref(cRecordIDs))
        return [self.__class__(cRecordIDs[x]) for x in range(0, numRecords)]

    def IsWinning(self, GetExtendedConflicts=False):
        """Returns true if the record is the last to load.
           If GetExtendedConflicts is True, scanned records will be considered.
           More efficient than running Conflicts() and checking the first value."""
        return _CIsRecordWinning(self._RecordID, c_ulong(GetExtendedConflicts))

    def Conflicts(self, GetExtendedConflicts=False):
        numRecords = _CGetNumRecordConflicts(self._RecordID, c_ulong(GetExtendedConflicts)) #gives upper bound
        if(numRecords > 1):
            cRecordIDs = (c_ulong * numRecords)()
            numRecords = _CGetRecordConflicts(self._RecordID, byref(cRecordIDs), c_ulong(GetExtendedConflicts))
            return [self.__class__(cRecordIDs[x]) for x in range(0, numRecords)]
        return []

    def ConflictDetails(self, attrs=None, GetExtendedConflicts=False):
        """New: attrs is an iterable, for each item, the following is checked:
           if the item is a string type: changes are reported
           if the item is another iterable (set,list,tuple), then if any of the subitems is
             different, then all sub items are reported.  This allows grouping of dependant
             items."""
        conflicting = {}
        if attrs is None:
            attrs = self.copyattrs
        if not attrs:
            return conflicting

        parentRecords = self.History()
        if parentRecords:
            for attr in attrs:
                if isinstance(attr,basestring):
                    # Single attr
                    conflicting.update([(attr,reduce(getattr, attr.split('.'), self)) for parentRecord in parentRecords if reduce(getattr, attr.split('.'), self) != reduce(getattr, attr.split('.'), parentRecord)])
                elif isinstance(attr,(list,tuple,set)):
                    # Group of attrs that need to stay together
                    for parentRecord in parentRecords:
                        subconflicting = {}
                        conflict = False
                        for subattr in attr:
                            self_value = reduce(getattr, subattr.split('.'), self)
                            if not conflict and self_value != reduce(getattr, subattr.split('.'), parentRecord):
                                conflict = True
                            subconflicting.update([(subattr,self_value)])
                        if conflict:
                            conflicting.update(subconflicting)
        else: #is the first instance of the record
            for attr in attrs:
                if isinstance(attr, basestring):
                    conflicting.update([(attr,reduce(getattr, attr.split('.'), self))])
                elif isinstance(attr,(list,tuple,set)):
                    conflicting.update([(subattr,reduce(getattr, subattr.split('.'), self)) for subattr in attr])

        skipped_conflicting = [(attr, value) for attr, value in conflicting.iteritems() if isinstance(value, FormID) and not value.ValidateFormID(self)]
        for attr, value in skipped_conflicting:
            try:
                deprint(_("%s attribute of %s record (maybe named: %s) importing from %s referenced an unloaded object (probably %s) - value skipped") % (attr, self.fid, self.full, self.GetParentMod().GName, value))
            except: #a record type that doesn't have a full chunk:
                deprint(_("%s attribute of %s record importing from %s referenced an unloaded object (probably %s) - value skipped") % (attr, self.fid, self.GetParentMod().GName, value))
            del conflicting[attr]

        return conflicting

    def mergeFilter(self,modSet):
        """This method is called by the bashed patch mod merger. The intention is
        to allow a record to be filtered according to the specified modSet. E.g.
        for a list record, items coming from mods not in the modSet could be
        removed from the list.

        In a case where items either cannot be filtered, or doing so will break
        the record, False should be returned.  If filtering was successful, True
        should be returned."""
        return True

    def CopyAsOverride(self, target, UseWinningParents=False, CopyFlags=0):
        if hasattr(self, '_ParentID'):
            if isinstance(target, FnvModFile):
                DestParentID = self._ParentID
                DestModID = target._ModID
            else:
                DestParentID = target._RecordID
                DestModID = target.GetParentMod()._ModID
        else:
            DestParentID = 0
            DestModID = target._ModID

        ##Record Creation Flags
        ##SetAsOverride       = 0x00000001
        ##CopyWinningParent   = 0x00000002
        #Set SetAsOverride
        CopyFlags |= 0x00000001
        if UseWinningParents:
            CopyFlags |= 0x00000002
        RecordID = _CCopyRecord(self._RecordID, DestModID, DestParentID, 0, 0, c_ulong(CopyFlags))
        #Clear SetAsOverride
        CopyFlags &= ~0x00000001
        if(RecordID): return self.__class__(RecordID)
        return None

    def CopyAsNew(self, target, UseWinningParents=False, RecordFormID=0, CopyFlags=0):
        if hasattr(self, '_ParentID'):
            if isinstance(target, FnvModFile):
                DestParentID = self._ParentID
                DestModID = target._ModID
            else:
                DestParentID = target._RecordID
                DestModID = target.GetParentMod()._ModID
        else:
            DestParentID = 0
            DestModID = target._ModID

        if RecordFormID:
            RecordFormID = RecordFormID.GetShortFormID(target)
        ##Record Creation Flags
        ##SetAsOverride       = 0x00000001
        ##CopyWinningParent   = 0x00000002
        #Clear SetAsOverride in case it was set
        CopyFlags &= ~0x00000001
        if UseWinningParents:
            CopyFlags |= 0x00000002
        RecordID = _CCopyRecord(self._RecordID, DestModID, DestParentID, RecordFormID, 0, c_ulong(CopyFlags))
        if(RecordID): return self.__class__(RecordID)
        return None

    @property
    def Parent(self):
        RecordID = getattr(self, '_ParentID', 0)
        if RecordID:
            testRecord = FnvBaseRecord(RecordID)
            RecordType = fnv_type_record[testRecord.recType]
            if RecordType:
                return RecordType(RecordID)
        return None

    @property
    def recType(self):
        _CGetFieldAttribute.restype = (c_char * 4)
        retValue = _CGetFieldAttribute(self._RecordID, 0, 0, 0, 0, 0, 0, 0, 0)
        _CGetFieldAttribute.restype = c_ulong
        if(retValue and retValue.value != ''): return retValue.value
        return None

    UINT32_FLAG_MACRO(flags1, 1)

    def get_fid(self):
        _CGetField.restype = POINTER(c_ulong)
        retValue = _CGetField(self._RecordID, 2, 0, 0, 0, 0, 0, 0, 0)
        if(retValue): return FormID(self._RecordID, retValue.contents.value)
        return None
    def set_fid(self, nValue):
        if nValue is None: nValue = 0
        else: nValue = nValue.GetShortFormID(self)
        _CSetIDFields(self._RecordID, nValue, self.eid or 0)
    fid = property(get_fid, set_fid)

    UINT8_ARRAY_MACRO(versionControl1, 3, 4)
    UINT16_MACRO(formVersion, 5)
    UINT8_ARRAY_MACRO(versionControl2, 6, 2)

    def get_eid(self):
        _CGetField.restype = c_char_p
        retValue = _CGetField(self._RecordID, 4, 0, 0, 0, 0, 0, 0, 0)
        if(retValue): return ISTRING(retValue)
        return None
    def set_eid(self, nValue):
        if nValue is None or not len(nValue): nValue = 0
        else: nValue = str(nValue)
        _CGetField.restype = POINTER(c_ulong)
        _CSetIDFields(self._RecordID, _CGetField(self._RecordID, 2, 0, 0, 0, 0, 0, 0, 0).contents.value, nValue)
    eid = property(get_eid, set_eid)

    BasicFlagMACRO(IsDeleted, flags1, 0x00000020)
    BasicFlagMACRO(IsHasTreeLOD, flags1, 0x00000040)
    BasicAliasMACRO(IsConstant, IsHasTreeLOD)
    BasicAliasMACRO(IsHiddenFromLocalMap, IsHasTreeLOD)
    BasicFlagMACRO(IsTurnOffFire, flags1, 0x00000080)
    BasicFlagMACRO(IsInaccessible, flags1, 0x00000100)
    BasicFlagMACRO(IsOnLocalMap, flags1, 0x00000200)
    BasicAliasMACRO(IsMotionBlur, IsOnLocalMap)
    BasicFlagMACRO(IsPersistent, flags1, 0x00000400)
    BasicAliasMACRO(IsQuest, IsPersistent)
    BasicAliasMACRO(IsQuestOrPersistent, IsPersistent)
    BasicFlagMACRO(IsInitiallyDisabled, flags1, 0x00000800)
    BasicFlagMACRO(IsIgnored, flags1, 0x00001000)
    BasicFlagMACRO(IsNoVoiceFilter, flags1, 0x00002000)
    BasicInvertedFlagMACRO(IsVoiceFilter, IsNoVoiceFilter)
    BasicFlagMACRO(IsVisibleWhenDistant, flags1, 0x00008000)
    BasicAliasMACRO(IsVWD, IsVisibleWhenDistant)
    BasicFlagMACRO(IsRandomAnimStartOrHighPriorityLOD, flags1, 0x00010000)
    BasicAliasMACRO(IsRandomAnimStart, IsRandomAnimStartOrHighPriorityLOD)
    BasicAliasMACRO(IsHighPriorityLOD, IsRandomAnimStartOrHighPriorityLOD)
    BasicFlagMACRO(IsTalkingActivator, flags1, 0x00020000)
    BasicFlagMACRO(IsCompressed, flags1, 0x00040000)
    BasicFlagMACRO(IsPlatformSpecificTexture, flags1, 0x00080000)
    BasicFlagMACRO(IsObstacleOrNoAIAcquire, flags1, 0x02000000)
    BasicAliasMACRO(IsObstacle, IsObstacleOrNoAIAcquire)
    BasicAliasMACRO(IsNoAIAcquire, IsObstacleOrNoAIAcquire)
    BasicFlagMACRO(IsNavMeshFilter, flags1, 0x04000000)
    BasicFlagMACRO(IsNavMeshBoundBox, flags1, 0x08000000)
    BasicFlagMACRO(IsNonPipboyOrAutoReflected, flags1, 0x10000000)
    BasicAliasMACRO(IsNonPipboy, IsNonPipboyOrAutoReflected)
    BasicAliasMACRO(IsAutoReflected, IsNonPipboyOrAutoReflected)
    BasicInvertedFlagMACRO(IsPipboy, IsNonPipboyOrAutoReflected)
    BasicFlagMACRO(IsChildUsableOrAutoRefracted, flags1, 0x20000000)
    BasicAliasMACRO(IsChildUsable, IsChildUsableOrAutoRefracted)
    BasicAliasMACRO(IsAutoRefracted, IsChildUsableOrAutoRefracted)
    BasicFlagMACRO(IsNavMeshGround, flags1, 0x40000000)
    baseattrs = ['flags1', 'versionControl1', 'formVersion', 'versionControl2', 'eid']

class FnvTES4Record(object):
    _Type = 'TES4'
    def __init__(self, RecordID):
        self._RecordID = RecordID

    def GetParentMod(self):
        return FnvModFile(_CGetModIDByRecordID(self._RecordID))

    def GetParentCollection(self):
        return ObCollection(_CGetCollectionIDByRecordID(self._RecordID))

    def ResetRecord(self):
        pass

    def UnloadRecord(self):
        pass

    @property
    def recType(self):
        return self._Type

    UINT32_FLAG_MACRO(flags1, 1)
    UINT8_ARRAY_MACRO(versionControl1, 3, 4)
    UINT16_MACRO(formVersion, 14)
    UINT8_ARRAY_MACRO(versionControl2, 15, 2)
    FLOAT32_MACRO(version, 5)
    UINT32_MACRO(numRecords, 6)
    UINT32_MACRO(nextObject, 7)
    UINT8_ARRAY_MACRO(ofst_p, 8)
    UINT8_ARRAY_MACRO(dele_p, 9)
    STRING_MACRO(author, 10)
    STRING_MACRO(description, 11)
    ISTRING_ARRAY_MACRO(masters, 12)
    JUNK_MACRO(DATA, 13)
    FORMID_ARRAY_MACRO(overrides, 16)
    UINT8_ARRAY_MACRO(screenshot_p, 17)

    BasicFlagMACRO(IsESM, flags1, 0x00000001)
    exportattrs = copyattrs = ['flags1', 'versionControl1', 'formVersion', 'versionControl2', 'version', 'numRecords', 'nextObject',
                 'author', 'description', 'masters', 'overrides', 'screenshot_p']

class FnvACHRRecord(FnvBaseRecord):
    @property
    def _ParentID(self):
        _CGetField.restype = c_ulong
        return _CGetField(self._RecordID, 55, 0, 0, 0, 0, 0, 0, 0)

    _Type = 'ACHR'
    class Decal(ListComponent):
        FORMID_LISTMACRO(reference, 1)
        UINT8_ARRAY_LISTMACRO(unknown1, 2, 24)
        copyattrs = ['reference', 'unknown1']
        exportattrs = ['reference']#, 'unknown1'

    class ParentRef(ListComponent):
        FORMID_LISTMACRO(reference, 1)
        FLOAT32_LISTMACRO(delay, 2)
        exportattrs = copyattrs = ['reference', 'delay']

    FORMID_MACRO(base, 7)
    FORMID_MACRO(encounterZone, 8)
    UINT8_ARRAY_MACRO(xrgd_p, 9)
    UINT8_ARRAY_MACRO(xrgb_p, 10)
    FLOAT32_MACRO(idleTime, 11)
    FORMID_MACRO(idle, 12)
    UINT8_ARRAY_MACRO(unused1, 13, 4)
    UINT32_MACRO(numRefs, 14)
    UINT32_MACRO(compiledSize, 15)
    UINT32_MACRO(lastIndex, 16)
    UINT16_TYPE_MACRO(scriptType, 17)
    UINT16_FLAG_MACRO(scriptFlags, 18)
    UINT8_ARRAY_MACRO(compiled_p, 19)
    ISTRING_MACRO(scriptText, 20)

    LIST_MACRO(vars, 21, Var)
    FORMID_OR_UINT32_ARRAY_MACRO(references, 22)
    FORMID_MACRO(topic, 23)
    SINT32_MACRO(levelMod, 24)
    FORMID_MACRO(merchantContainer, 25)
    SINT32_MACRO(count, 26)
    FLOAT32_MACRO(radius, 27)
    FLOAT32_MACRO(health, 28)

    LIST_MACRO(decals, 29, self.Decal)
    FORMID_MACRO(linkedReference, 30)
    UINT8_MACRO(startRed, 31)
    UINT8_MACRO(startGreen, 32)
    UINT8_MACRO(startBlue, 33)
    UINT8_ARRAY_MACRO(unused2, 34, 1)
    UINT8_MACRO(endRed, 35)
    UINT8_MACRO(endGreen, 36)
    UINT8_MACRO(endBlue, 37)
    UINT8_ARRAY_MACRO(unused3, 38, 1)
    UINT8_FLAG_MACRO(activateParentFlags, 39)

    LIST_MACRO(activateParentRefs, 40, self.ParentRef)
    STRING_MACRO(prompt, 41)
    FORMID_MACRO(parent, 42)
    UINT8_FLAG_MACRO(parentFlags, 43)
    UINT8_ARRAY_MACRO(unused4, 44, 3)
    FORMID_MACRO(emittance, 45)
    FORMID_MACRO(boundRef, 46)
    BOOL_MACRO(ignoredBySandbox, 47)
    FLOAT32_MACRO(scale, 48)
    FLOAT32_MACRO(posX, 49)
    FLOAT32_MACRO(posY, 50)
    FLOAT32_MACRO(posZ, 51)
    RADIAN_MACRO(rotX, 52)
    RADIAN_MACRO(rotY, 53)
    RADIAN_MACRO(rotZ, 54)

    BasicFlagMACRO(IsEnabled, scriptFlags, 0x0001)

    BasicFlagMACRO(IsOppositeParent, parentFlags, 0x00000001)
    BasicFlagMACRO(IsPopIn, parentFlags, 0x00000002)

    BasicTypeMACRO(IsObject, scriptType, 0x0000, IsQuest)
    BasicTypeMACRO(IsQuest, scriptType, 0x0001, IsObject)
    BasicTypeMACRO(IsEffect, scriptType, 0x0100, IsObject)

    copyattrs = FnvBaseRecord.baseattrs + ['base', 'encounterZone', 'xrgd_p', 'xrgb_p',
                                           'idleTime', 'idle', 'numRefs', 'compiledSize',
                                           'lastIndex', 'scriptType', 'scriptFlags',
                                           'compiled_p', 'scriptText', 'vars_list',
                                           'references', 'topic', 'levelMod',
                                           'merchantContainer', 'count',
                                           'radius', 'health', 'decals_list',
                                           'linkedReference',
                                           'startRed', 'startGreen', 'startBlue',
                                           'endRed', 'endGreen', 'endBlue',
                                           'activateParentFlags',
                                           'activateParentRefs_list', 'prompt',
                                           'parent', 'parentFlags', 'emittance',
                                           'boundRef', 'ignoredBySandbox', 'scale',
                                           'posX', 'posY', 'posZ', 'rotX', 'rotY', 'rotZ']

    exportattrs = FnvBaseRecord.baseattrs + ['base', 'encounterZone',
                                             'idleTime', 'idle', 'numRefs', 'compiledSize',
                                             'lastIndex', 'scriptType', 'scriptFlags',
                                             'scriptText', 'vars_list',
                                             'references', 'topic', 'levelMod',
                                             'merchantContainer', 'count',
                                             'radius', 'health', 'decals_list',
                                             'linkedReference',
                                             'startRed', 'startGreen', 'startBlue',
                                             'endRed', 'endGreen', 'endBlue',
                                             'activateParentFlags',
                                             'activateParentRefs_list', 'prompt',
                                             'parent', 'parentFlags', 'emittance',
                                             'boundRef', 'ignoredBySandbox', 'scale',
                                             'posX', 'posY', 'posZ', 'rotX', 'rotY', 'rotZ']# 'xrgd_p', 'xrgb_p', 'compiled_p',

class FnvACRERecord(FnvBaseRecord):
    @property
    def _ParentID(self):
        _CGetField.restype = c_ulong
        return _CGetField(self._RecordID, 57, 0, 0, 0, 0, 0, 0, 0)

    _Type = 'ACRE'
    class Decal(ListComponent):
        FORMID_LISTMACRO(reference, 1)
        UINT8_ARRAY_LISTMACRO(unknown1, 2, 24)
        copyattrs = ['reference', 'unknown1']
        exportattrs = ['reference']#, 'unknown1'

    class ParentRef(ListComponent):
        FORMID_LISTMACRO(reference, 1)
        FLOAT32_LISTMACRO(delay, 2)
        exportattrs = copyattrs = ['reference', 'delay']

    FORMID_MACRO(base, 7)
    FORMID_MACRO(encounterZone, 8)
    UINT8_ARRAY_MACRO(xrgd_p, 9)
    UINT8_ARRAY_MACRO(xrgb_p, 10)
    FLOAT32_MACRO(idleTime, 11)
    FORMID_MACRO(idle, 12)
    UINT8_ARRAY_MACRO(unused1, 13, 4)
    UINT32_MACRO(numRefs, 14)
    UINT32_MACRO(compiledSize, 15)
    UINT32_MACRO(lastIndex, 16)
    UINT16_TYPE_MACRO(scriptType, 17)
    UINT16_FLAG_MACRO(scriptFlags, 18)
    UINT8_ARRAY_MACRO(compiled_p, 19)
    ISTRING_MACRO(scriptText, 20)

    LIST_MACRO(vars, 21, Var)
    FORMID_OR_UINT32_ARRAY_MACRO(references, 22)
    FORMID_MACRO(topic, 23)
    SINT32_MACRO(levelMod, 24)
    FORMID_MACRO(owner, 25)
    SINT32_MACRO(rank, 26)
    FORMID_MACRO(merchantContainer, 27)
    SINT32_MACRO(count, 28)
    FLOAT32_MACRO(radius, 29)
    FLOAT32_MACRO(health, 30)

    LIST_MACRO(decals, 31, self.Decal)
    FORMID_MACRO(linkedReference, 32)
    UINT8_MACRO(startRed, 33)
    UINT8_MACRO(startGreen, 34)
    UINT8_MACRO(startBlue, 35)
    UINT8_ARRAY_MACRO(unused2, 36, 1)
    UINT8_MACRO(endRed, 37)
    UINT8_MACRO(endGreen, 38)
    UINT8_MACRO(endBlue, 39)
    UINT8_ARRAY_MACRO(unused3, 40, 1)
    UINT8_FLAG_MACRO(activateParentFlags, 41)

    LIST_MACRO(activateParentRefs, 42, self.ParentRef)
    STRING_MACRO(prompt, 43)
    FORMID_MACRO(parent, 44)
    UINT8_FLAG_MACRO(parentFlags, 45)
    UINT8_ARRAY_MACRO(unused4, 46, 3)
    FORMID_MACRO(emittance, 47)
    FORMID_MACRO(boundRef, 48)
    BOOL_MACRO(ignoredBySandbox, 49)
    FLOAT32_MACRO(scale, 50)
    FLOAT32_MACRO(posX, 51)
    FLOAT32_MACRO(posY, 52)
    FLOAT32_MACRO(posZ, 53)
    RADIAN_MACRO(rotX, 54)
    RADIAN_MACRO(rotY, 55)
    RADIAN_MACRO(rotZ, 56)

    BasicFlagMACRO(IsEnabled, scriptFlags, 0x0001)

    BasicFlagMACRO(IsOppositeParent, parentFlags, 0x00000001)
    BasicFlagMACRO(IsPopIn, parentFlags, 0x00000002)

    BasicTypeMACRO(IsObject, scriptType, 0x0000, IsQuest)
    BasicTypeMACRO(IsQuest, scriptType, 0x0001, IsObject)
    BasicTypeMACRO(IsEffect, scriptType, 0x0100, IsObject)

    copyattrs = FnvBaseRecord.baseattrs + ['base', 'encounterZone', 'xrgd_p', 'xrgb_p',
                                           'idleTime', 'idle', 'numRefs', 'compiledSize',
                                           'lastIndex', 'scriptType', 'scriptFlags',
                                           'compiled_p', 'scriptText', 'vars_list',
                                           'references', 'topic', 'levelMod', 'owner',
                                           'rank', 'merchantContainer', 'count',
                                           'radius', 'health', 'decals_list',
                                           'linkedReference',
                                           'startRed', 'startGreen', 'startBlue',
                                           'endRed', 'endGreen', 'endBlue',
                                           'activateParentFlags',
                                           'activateParentRefs_list', 'prompt',
                                           'parent', 'parentFlags', 'emittance',
                                           'boundRef', 'ignoredBySandbox', 'scale',
                                           'posX', 'posY', 'posZ', 'rotX', 'rotY', 'rotZ']

    exportattrs = FnvBaseRecord.baseattrs + ['base', 'encounterZone',
                                             'idleTime', 'idle', 'numRefs', 'compiledSize',
                                             'lastIndex', 'scriptType', 'scriptFlags',
                                             'scriptText', 'vars_list',
                                             'references', 'topic', 'levelMod', 'owner',
                                             'rank', 'merchantContainer', 'count',
                                             'radius', 'health', 'decals_list',
                                             'linkedReference',
                                             'startRed', 'startGreen', 'startBlue',
                                             'endRed', 'endGreen', 'endBlue',
                                             'activateParentFlags',
                                             'activateParentRefs_list', 'prompt',
                                             'parent', 'parentFlags', 'emittance',
                                             'boundRef', 'ignoredBySandbox', 'scale',
                                             'posX', 'posY', 'posZ', 'rotX', 'rotY', 'rotZ']# 'xrgd_p', 'xrgb_p', 'compiled_p',

class FnvREFRRecord(FnvBaseRecord):
    @property
    def _ParentID(self):
        _CGetField.restype = c_ulong
        return _CGetField(self._RecordID, 141, 0, 0, 0, 0, 0, 0, 0)

    _Type = 'REFR'
    class Decal(ListComponent):
        FORMID_LISTMACRO(reference, 1)
        UINT8_ARRAY_LISTMACRO(unknown1, 2, 24)
        copyattrs = ['reference', 'unknown1']
        exportattrs = ['reference']#, 'unknown1'

    class ParentRef(ListComponent):
        FORMID_LISTMACRO(reference, 1)
        FLOAT32_LISTMACRO(delay, 2)
        exportattrs = copyattrs = ['reference', 'delay']

    class ReflRefr(ListComponent):
        FORMID_LISTMACRO(reference, 1)
        UINT32_TYPE_LISTMACRO(type, 2)

        BasicTypeMACRO(IsReflection, type, 0, IsRefraction)
        BasicTypeMACRO(IsRefraction, type, 1, IsReflection)
        exportattrs = copyattrs = ['reference', 'type']

    FORMID_MACRO(base, 7)
    FORMID_MACRO(encounterZone, 8)
    UINT8_ARRAY_MACRO(xrgd_p, 9)
    UINT8_ARRAY_MACRO(xrgb_p, 10)
    FLOAT32_MACRO(idleTime, 11)
    FORMID_MACRO(idle, 12)
    UINT8_ARRAY_MACRO(unused1, 13, 4)
    UINT32_MACRO(numRefs, 14)
    UINT32_MACRO(compiledSize, 15)
    UINT32_MACRO(lastIndex, 16)
    UINT16_TYPE_MACRO(scriptType, 17)
    UINT16_FLAG_MACRO(scriptFlags, 18)
    UINT8_ARRAY_MACRO(compiled_p, 19)
    ISTRING_MACRO(scriptText, 20)

    LIST_MACRO(vars, 21, Var)
    FORMID_OR_UINT32_ARRAY_MACRO(references, 22)
    FORMID_MACRO(topic, 23)
    SINT32_MACRO(levelMod, 24)
    FORMID_MACRO(owner, 25)
    SINT32_MACRO(rank, 26)
    SINT32_MACRO(count, 27)
    FLOAT32_MACRO(radius, 28)
    FLOAT32_MACRO(health, 29)
    FLOAT32_MACRO(radiation, 30)
    FLOAT32_MACRO(charge, 31)

    LIST_MACRO(decals, 32, self.Decal)
    FORMID_MACRO(linkedReference, 33)
    UINT8_MACRO(startRed, 34)
    UINT8_MACRO(startRed, 35)
    UINT8_MACRO(startBlue, 36)
    UINT8_ARRAY_MACRO(unused2, 37, 1)
    UINT8_MACRO(endRed, 38)
    UINT8_MACRO(endGreen, 39)
    UINT8_MACRO(endBlue, 40)
    UINT8_ARRAY_MACRO(unused3, 41, 1)
    UINT8_ARRAY_MACRO(rclr_p, 42)
    UINT8_FLAG_MACRO(activateParentFlags, 43)

    LIST_MACRO(activateParentRefs, 44, self.ParentRef)
    STRING_MACRO(prompt, 45)
    FORMID_MACRO(parent, 46)
    UINT8_FLAG_MACRO(parentFlags, 47)
    UINT8_ARRAY_MACRO(unused4, 48, 3)
    FORMID_MACRO(emittance, 49)
    FORMID_MACRO(boundRef, 50)
    FLOAT32_MACRO(primitiveX, 51)
    FLOAT32_MACRO(primitiveY, 52)
    FLOAT32_MACRO(primitiveZ, 53)
    FLOAT32_MACRO(primitiveRed, 54)
    FLOAT32_MACRO(primitiveGreen, 55)
    FLOAT32_MACRO(primitiveBlue, 56)
    FLOAT32_MACRO(primitiveUnknown, 57)
    UINT32_TYPE_MACRO(primitiveType, 58)
    UINT32_TYPE_MACRO(collisionType, 59)
    FLOAT32_MACRO(extentX, 60)
    FLOAT32_MACRO(extentY, 61)
    FLOAT32_MACRO(extentZ, 62)
    FORMID_MACRO(destinationFid, 63)
    FLOAT32_MACRO(destinationPosX, 64)
    FLOAT32_MACRO(destinationPosY, 65)
    FLOAT32_MACRO(destinationPosZ, 66)
    RADIAN_MACRO(destinationRotX, 67)
    RADIAN_MACRO(destinationRotY, 68)
    RADIAN_MACRO(destinationRotZ, 69)
    UINT32_FLAG_MACRO(destinationFlags, 70)
    UINT8_FLAG_MACRO(markerFlags, 71)
    STRING_MACRO(markerFull, 72)
    UINT8_TYPE_MACRO(markerType, 73)
    UINT8_ARRAY_MACRO(unused5, 74, 1)
    FORMID_MACRO(markerReputation, 75)
    UINT8_ARRAY_MACRO(audioFull_p, 76)
    FORMID_MACRO(audioLocation, 77)
    UINT8_ARRAY_MACRO(audioBnam_p, 78)
    FLOAT32_MACRO(audioUnknown1, 79)
    FLOAT32_MACRO(audioUnknown2, 80)
    UINT8_ARRAY_MACRO(xsrf_p, 81)
    UINT8_ARRAY_MACRO(xsrd_p, 82)
    FORMID_MACRO(target, 83)
    FLOAT32_MACRO(rangeRadius, 84)
    UINT32_TYPE_MACRO(rangeType, 85)
    FLOAT32_MACRO(staticPercentage, 86)
    FORMID_MACRO(positionReference, 87)
    UINT8_MACRO(lockLevel, 88)
    UINT8_ARRAY_MACRO(unused6, 89, 3)
    FORMID_MACRO(lockKey, 90)
    UINT8_FLAG_MACRO(lockFlags, 91)
    UINT8_ARRAY_MACRO(unused7, 92, 3)
    UINT8_ARRAY_MACRO(lockUnknown1, 93)
    FORMID_MACRO(ammo, 94)
    SINT32_MACRO(ammoCount, 95)

    LIST_MACRO(reflrefrs, 96, self.ReflRefr)
    FORMID_ARRAY_MACRO(litWaters, 97)
    UINT32_FLAG_MACRO(actionFlags, 98)
    FORMID_MACRO(navMesh, 99)
    UINT16_MACRO(navUnknown1, 100)
    UINT8_ARRAY_MACRO(unused8, 101, 2)
    FORMID_MACRO(portalLinkedRoom1, 102)
    FORMID_MACRO(portalLinkedRoom2, 103)
    FLOAT32_MACRO(portalWidth, 104)
    FLOAT32_MACRO(portalHeight, 105)
    FLOAT32_MACRO(portalPosX, 106)
    FLOAT32_MACRO(portalPosY, 107)
    FLOAT32_MACRO(portalPosZ, 108)
    FLOAT32_MACRO(portalQ1, 109)
    FLOAT32_MACRO(portalQ2, 110)
    FLOAT32_MACRO(portalQ3, 111)
    FLOAT32_MACRO(portalQ4, 112)
    UINT8_MACRO(seed, 113)
    UINT16_MACRO(roomCount, 114)
    UINT8_ARRAY_MACRO(roomUnknown1, 115)
    FORMID_ARRAY_MACRO(rooms, 116)
    FLOAT32_MACRO(occPlaneWidth, 117)
    FLOAT32_MACRO(occPlaneHeight, 118)
    FLOAT32_MACRO(occPlanePosX, 119)
    FLOAT32_MACRO(occPlanePosY, 120)
    FLOAT32_MACRO(occPlanePosZ, 121)
    FLOAT32_MACRO(occPlaneQ1, 122)
    FLOAT32_MACRO(occPlaneQ2, 123)
    FLOAT32_MACRO(occPlaneQ3, 124)
    FLOAT32_MACRO(occPlaneQ4, 125)
    FORMID_MACRO(occPlaneRight, 126)
    FORMID_MACRO(occPlaneLeft, 127)
    FORMID_MACRO(occPlaneBottom, 128)
    FORMID_MACRO(occPlaneTop, 129)
    FLOAT32_MACRO(lod1, 130)
    FLOAT32_MACRO(lod2, 131)
    FLOAT32_MACRO(lod3, 132)
    BOOL_MACRO(ignoredBySandbox, 133)
    FLOAT32_MACRO(scale, 134)
    FLOAT32_MACRO(posX, 135)
    FLOAT32_MACRO(posY, 136)
    FLOAT32_MACRO(posZ, 137)
    RADIAN_MACRO(rotX, 138)
    RADIAN_MACRO(rotY, 139)
    RADIAN_MACRO(rotZ, 140)

    BasicFlagMACRO(IsEnabled, scriptFlags, 0x0001)

    BasicFlagMACRO(IsNoAlarm, destinationFlags, 0x00000001)

    BasicFlagMACRO(IsVisible, markerFlags, 0x00000001)
    BasicFlagMACRO(IsCanTravelTo, markerFlags, 0x00000002)

    BasicFlagMACRO(IsUseDefault, actionFlags, 0x00000001)
    BasicFlagMACRO(IsActivate, actionFlags, 0x00000002)
    BasicFlagMACRO(IsOpen, actionFlags, 0x00000004)
    BasicFlagMACRO(IsOpenByDefault, actionFlags, 0x00000008)

    BasicFlagMACRO(IsOppositeParent, parentFlags, 0x00000001)
    BasicFlagMACRO(IsPopIn, parentFlags, 0x00000002)

    BasicFlagMACRO(IsLeveledLock, lockFlags, 0x00000004)

    BasicTypeMACRO(IsObject, scriptType, 0x0000, IsQuest)
    BasicTypeMACRO(IsQuest, scriptType, 0x0001, IsObject)
    BasicTypeMACRO(IsEffect, scriptType, 0x0100, IsObject)

    BasicTypeMACRO(IsNone, primitiveType, 0, IsBox)
    BasicTypeMACRO(IsBox, primitiveType, 1, IsNone)
    BasicTypeMACRO(IsSphere, primitiveType, 2, IsNone)
    BasicTypeMACRO(IsPortalBox, primitiveType, 3, IsNone)

    BasicTypeMACRO(IsUnidentified, collisionType, 0, IsStatic)
    BasicTypeMACRO(IsStatic, collisionType, 1, IsUnidentified)
    BasicTypeMACRO(IsAnimStatic, collisionType, 2, IsUnidentified)
    BasicTypeMACRO(IsTransparent, collisionType, 3, IsUnidentified)
    BasicTypeMACRO(IsClutter, collisionType, 4, IsUnidentified)
    BasicTypeMACRO(IsWeapon, collisionType, 5, IsUnidentified)
    BasicTypeMACRO(IsProjectile, collisionType, 6, IsUnidentified)
    BasicTypeMACRO(IsSpell, collisionType, 7, IsUnidentified)
    BasicTypeMACRO(IsBiped, collisionType, 8, IsUnidentified)
    BasicTypeMACRO(IsTrees, collisionType, 9, IsUnidentified)
    BasicTypeMACRO(IsProps, collisionType, 10, IsUnidentified)
    BasicTypeMACRO(IsWater, collisionType, 11, IsUnidentified)
    BasicTypeMACRO(IsTrigger, collisionType, 12, IsUnidentified)
    BasicTypeMACRO(IsTerrain, collisionType, 13, IsUnidentified)
    BasicTypeMACRO(IsTrap, collisionType, 14, IsUnidentified)
    BasicTypeMACRO(IsNonCollidable, collisionType, 15, IsUnidentified)
    BasicTypeMACRO(IsCloudTrap, collisionType, 16, IsUnidentified)
    BasicTypeMACRO(IsGround, collisionType, 17, IsUnidentified)
    BasicTypeMACRO(IsPortal, collisionType, 18, IsUnidentified)
    BasicTypeMACRO(IsDebrisSmall, collisionType, 19, IsUnidentified)
    BasicTypeMACRO(IsDebrisLarge, collisionType, 20, IsUnidentified)
    BasicTypeMACRO(IsAcousticSpace, collisionType, 21, IsUnidentified)
    BasicTypeMACRO(IsActorZone, collisionType, 22, IsUnidentified)
    BasicTypeMACRO(IsProjectileZone, collisionType, 23, IsUnidentified)
    BasicTypeMACRO(IsGasTrap, collisionType, 24, IsUnidentified)
    BasicTypeMACRO(IsShellCasing, collisionType, 25, IsUnidentified)
    BasicTypeMACRO(IsTransparentSmall, collisionType, 26, IsUnidentified)
    BasicTypeMACRO(IsInvisibleWall, collisionType, 27, IsUnidentified)
    BasicTypeMACRO(IsTransparentSmallAnim, collisionType, 28, IsUnidentified)
    BasicTypeMACRO(IsDeadBip, collisionType, 29, IsUnidentified)
    BasicTypeMACRO(IsCharController, collisionType, 30, IsUnidentified)
    BasicTypeMACRO(IsAvoidBox, collisionType, 31, IsUnidentified)
    BasicTypeMACRO(IsCollisionBox, collisionType, 32, IsUnidentified)
    BasicTypeMACRO(IsCameraSphere, collisionType, 33, IsUnidentified)
    BasicTypeMACRO(IsDoorDetection, collisionType, 34, IsUnidentified)
    BasicTypeMACRO(IsCameraPick, collisionType, 35, IsUnidentified)
    BasicTypeMACRO(IsItemPick, collisionType, 36, IsUnidentified)
    BasicTypeMACRO(IsLineOfSight, collisionType, 37, IsUnidentified)
    BasicTypeMACRO(IsPathPick, collisionType, 38, IsUnidentified)
    BasicTypeMACRO(IsCustomPick1, collisionType, 39, IsUnidentified)
    BasicTypeMACRO(IsCustomPick2, collisionType, 40, IsUnidentified)
    BasicTypeMACRO(IsSpellExplosion, collisionType, 41, IsUnidentified)
    BasicTypeMACRO(IsDroppingPick, collisionType, 42, IsUnidentified)

    BasicTypeMACRO(IsMarkerNone, markerType, 0, IsMarkerNone)
    BasicTypeMACRO(IsCity, markerType, 1, IsMarkerNone)
    BasicTypeMACRO(IsSettlement, markerType, 2, IsMarkerNone)
    BasicTypeMACRO(IsEncampment, markerType, 3, IsMarkerNone)
    BasicTypeMACRO(IsNaturalLandmark, markerType, 4, IsMarkerNone)
    BasicTypeMACRO(IsCave, markerType, 5, IsMarkerNone)
    BasicTypeMACRO(IsFactory, markerType, 6, IsMarkerNone)
    BasicTypeMACRO(IsMonument, markerType, 7, IsMarkerNone)
    BasicTypeMACRO(IsMilitary, markerType, 8, IsMarkerNone)
    BasicTypeMACRO(IsOffice, markerType, 9, IsMarkerNone)
    BasicTypeMACRO(IsTownRuins, markerType, 10, IsMarkerNone)
    BasicTypeMACRO(IsUrbanRuins, markerType, 11, IsMarkerNone)
    BasicTypeMACRO(IsSewerRuins, markerType, 12, IsMarkerNone)
    BasicTypeMACRO(IsMetro, markerType, 13, IsMarkerNone)
    BasicTypeMACRO(IsVault, markerType, 14, IsMarkerNone)

    BasicTypeMACRO(IsRadius, rangeType, 0, IsEverywhere)
    BasicTypeMACRO(IsEverywhere, rangeType, 1, IsRadius)
    BasicTypeMACRO(IsWorldAndLinkedInteriors, rangeType, 2, IsRadius)
    BasicTypeMACRO(IsLinkedInteriors, rangeType, 3, IsRadius)
    BasicTypeMACRO(IsCurrentCellOnly, rangeType, 4, IsRadius)
    copyattrs = FnvBaseRecord.baseattrs + ['base', 'encounterZone', 'xrgd_p', 'xrgb_p',
                                           'idleTime', 'idle', 'numRefs',
                                           'compiledSize', 'lastIndex', 'scriptType',
                                           'scriptFlags', 'compiled_p', 'scriptText',
                                           'vars_list', 'references', 'topic', 'levelMod',
                                           'owner', 'rank', 'count', 'radius', 'health',
                                           'radiation', 'charge', 'decals_list',
                                           'linkedReference',
                                           'startRed', 'startRed', 'startBlue',
                                           'endRed', 'endGreen', 'endBlue',
                                           'rclr_p', 'activateParentFlags',
                                           'activateParentRefs_list', 'prompt', 'parent',
                                           'parentFlags', 'emittance', 'boundRef',
                                           'primitiveX', 'primitiveY', 'primitiveZ',
                                           'primitiveRed', 'primitiveGreen', 'primitiveBlue',
                                           'primitiveUnknown', 'primitiveType',
                                           'collisionType', 'extentX', 'extentY', 'extentZ',
                                           'destinationFid', 'destinationPosX',
                                           'destinationPosY', 'destinationPosZ',
                                           'destinationRotX', 'destinationRotY',
                                           'destinationRotZ', 'destinationFlags',
                                           'markerFlags', 'markerFull', 'markerType',
                                           'markerReputation', 'audioFull_p', 'audioLocation',
                                           'audioBnam_p', 'audioUnknown1', 'audioUnknown2',
                                           'xsrf_p', 'xsrd_p', 'target', 'rangeRadius',
                                           'rangeType', 'staticPercentage', 'positionReference',
                                           'lockLevel', 'lockKey', 'lockFlags', 'lockUnknown1',
                                           'ammo', 'ammoCount', 'reflrefrs_list', 'litWaters',
                                           'actionFlags', 'navMesh', 'navUnknown1',
                                           'portalLinkedRoom1', 'portalLinkedRoom2',
                                           'portalWidth', 'portalHeight', 'portalPosX',
                                           'portalPosY', 'portalPosZ', 'portalQ1', 'portalQ2',
                                           'portalQ3', 'portalQ4', 'seed', 'roomCount',
                                           'roomUnknown1', 'rooms', 'occPlaneWidth',
                                           'occPlaneHeight', 'occPlanePosX', 'occPlanePosY',
                                           'occPlanePosZ', 'occPlaneQ1', 'occPlaneQ2',
                                           'occPlaneQ3', 'occPlaneQ4', 'occPlaneRight',
                                           'occPlaneLeft', 'occPlaneBottom', 'occPlaneTop',
                                           'lod1', 'lod2', 'lod3', 'ignoredBySandbox',
                                           'scale', 'posX', 'posY', 'posZ', 'rotX', 'rotY', 'rotZ']
    exportattrs = FnvBaseRecord.baseattrs + ['base', 'encounterZone',
                                             'idleTime', 'idle', 'numRefs',
                                             'compiledSize', 'lastIndex', 'scriptType',
                                             'scriptFlags', 'scriptText',
                                             'vars_list', 'references', 'topic', 'levelMod',
                                             'owner', 'rank', 'count', 'radius', 'health',
                                             'radiation', 'charge', 'decals_list',
                                             'linkedReference',
                                             'startRed', 'startRed', 'startBlue',
                                             'endRed', 'endGreen', 'endBlue',
                                             'activateParentFlags',
                                             'activateParentRefs_list', 'prompt', 'parent',
                                             'parentFlags', 'emittance', 'boundRef',
                                             'primitiveX', 'primitiveY', 'primitiveZ',
                                             'primitiveRed', 'primitiveGreen', 'primitiveBlue',
                                             'primitiveUnknown', 'primitiveType',
                                             'collisionType', 'extentX', 'extentY', 'extentZ',
                                             'destinationFid', 'destinationPosX',
                                             'destinationPosY', 'destinationPosZ',
                                             'destinationRotX', 'destinationRotY',
                                             'destinationRotZ', 'destinationFlags',
                                             'markerFlags', 'markerFull', 'markerType',
                                             'markerReputation', 'audioLocation',
                                             'audioUnknown1', 'audioUnknown2',
                                             'target', 'rangeRadius',
                                             'rangeType', 'staticPercentage', 'positionReference',
                                             'lockLevel', 'lockKey', 'lockFlags', 'lockUnknown1',
                                             'ammo', 'ammoCount', 'reflrefrs_list', 'litWaters',
                                             'actionFlags', 'navMesh', 'navUnknown1',
                                             'portalLinkedRoom1', 'portalLinkedRoom2',
                                             'portalWidth', 'portalHeight', 'portalPosX',
                                             'portalPosY', 'portalPosZ', 'portalQ1', 'portalQ2',
                                             'portalQ3', 'portalQ4', 'seed', 'roomCount',
                                             'roomUnknown1', 'rooms', 'occPlaneWidth',
                                             'occPlaneHeight', 'occPlanePosX', 'occPlanePosY',
                                             'occPlanePosZ', 'occPlaneQ1', 'occPlaneQ2',
                                             'occPlaneQ3', 'occPlaneQ4', 'occPlaneRight',
                                             'occPlaneLeft', 'occPlaneBottom', 'occPlaneTop',
                                             'lod1', 'lod2', 'lod3', 'ignoredBySandbox',
                                             'scale', 'posX', 'posY', 'posZ', 'rotX', 'rotY', 'rotZ']# 'xsrf_p', 'xsrd_p', 'audioBnam_p', 'audioFull_p', 'rclr_p',  'xrgd_p', 'xrgb_p','compiled_p',

class FnvPGRERecord(FnvBaseRecord):
    @property
    def _ParentID(self):
        _CGetField.restype = c_ulong
        return _CGetField(self._RecordID, 56, 0, 0, 0, 0, 0, 0, 0)

    _Type = 'PGRE'
    class Decal(ListComponent):
        FORMID_LISTMACRO(reference, 1)
        UINT8_ARRAY_LISTMACRO(unknown1, 2, 24)
        copyattrs = ['reference', 'unknown1']
        exportattrs = ['reference']#, 'unknown1'

    class ParentRef(ListComponent):
        FORMID_LISTMACRO(reference, 1)
        FLOAT32_LISTMACRO(delay, 2)
        exportattrs = copyattrs = ['reference', 'delay']

    class ReflRefr(ListComponent):
        FORMID_LISTMACRO(reference, 1)
        UINT32_TYPE_LISTMACRO(type, 2)

        BasicTypeMACRO(IsReflection, type, 0, IsRefraction)
        BasicTypeMACRO(IsRefraction, type, 1, IsReflection)
        exportattrs = copyattrs = ['reference', 'type']

    FORMID_MACRO(base, 7)
    FORMID_MACRO(encounterZone, 8)
    UINT8_ARRAY_MACRO(xrgd_p, 9)
    UINT8_ARRAY_MACRO(xrgb_p, 10)
    FLOAT32_MACRO(idleTime, 11)
    FORMID_MACRO(idle, 12)
    UINT8_ARRAY_MACRO(unused1, 13, 4)
    UINT32_MACRO(numRefs, 14)
    UINT32_MACRO(compiledSize, 15)
    UINT32_MACRO(lastIndex, 16)
    UINT16_TYPE_MACRO(scriptType, 17)
    UINT16_FLAG_MACRO(scriptFlags, 18)
    UINT8_ARRAY_MACRO(compiled_p, 19)
    ISTRING_MACRO(scriptText, 20)

    LIST_MACRO(vars, 21, Var)
    FORMID_OR_UINT32_ARRAY_MACRO(references, 22)
    FORMID_MACRO(topic, 23)
    FORMID_MACRO(owner, 24)
    SINT32_MACRO(rank, 25)
    SINT32_MACRO(count, 26)
    FLOAT32_MACRO(radius, 27)
    FLOAT32_MACRO(health, 28)

    LIST_MACRO(decals, 29, self.Decal)
    FORMID_MACRO(linkedReference, 30)
    UINT8_MACRO(startRed, 31)
    UINT8_MACRO(startGreen, 32)
    UINT8_MACRO(startBlue, 33)
    UINT8_ARRAY_MACRO(unused2, 34, 1)
    UINT8_MACRO(endRed, 35)
    UINT8_MACRO(endGreen, 36)
    UINT8_MACRO(endBlue, 37)
    UINT8_ARRAY_MACRO(unused3, 38, 1)
    UINT8_FLAG_MACRO(activateParentFlags, 39)

    LIST_MACRO(activateParentRefs, 40, self.ParentRef)
    STRING_MACRO(prompt, 41)
    FORMID_MACRO(parent, 42)
    UINT8_FLAG_MACRO(parentFlags, 43)
    UINT8_ARRAY_MACRO(unused4, 44, 3)
    FORMID_MACRO(emittance, 45)
    FORMID_MACRO(boundRef, 46)

    LIST_MACRO(reflrefrs, 47, self.ReflRefr)
    BOOL_MACRO(ignoredBySandbox, 48)
    FLOAT32_MACRO(scale, 49)
    FLOAT32_MACRO(posX, 50)
    FLOAT32_MACRO(posY, 51)
    FLOAT32_MACRO(posZ, 52)
    RADIAN_MACRO(rotX, 53)
    RADIAN_MACRO(rotY, 54)
    RADIAN_MACRO(rotZ, 55)

    BasicFlagMACRO(IsEnabled, scriptFlags, 0x0001)

    BasicFlagMACRO(IsOppositeParent, parentFlags, 0x00000001)
    BasicFlagMACRO(IsPopIn, parentFlags, 0x00000002)

    BasicTypeMACRO(IsObject, scriptType, 0x0000, IsQuest)
    BasicTypeMACRO(IsQuest, scriptType, 0x0001, IsObject)
    BasicTypeMACRO(IsEffect, scriptType, 0x0100, IsObject)

    copyattrs = FnvBaseRecord.baseattrs + ['base', 'encounterZone', 'xrgd_p', 'xrgb_p',
                                           'idleTime', 'idle', 'numRefs', 'compiledSize',
                                           'lastIndex', 'scriptType', 'scriptFlags',
                                           'compiled_p', 'scriptText', 'vars_list',
                                           'references', 'topic', 'owner',
                                           'rank', 'count',
                                           'radius', 'health', 'decals_list',
                                           'linkedReference',
                                           'startRed', 'startGreen', 'startBlue',
                                           'endRed', 'endGreen', 'endBlue',
                                           'activateParentFlags',
                                           'activateParentRefs_list', 'prompt',
                                           'parent', 'parentFlags', 'emittance',
                                           'boundRef', 'reflrefrs_list',
                                           'ignoredBySandbox', 'scale',
                                           'posX', 'posY', 'posZ', 'rotX', 'rotY', 'rotZ']

    exportattrs = FnvBaseRecord.baseattrs + ['base', 'encounterZone',
                                             'idleTime', 'idle', 'numRefs', 'compiledSize',
                                             'lastIndex', 'scriptType', 'scriptFlags',
                                             'scriptText', 'vars_list',
                                             'references', 'topic', 'owner',
                                             'rank', 'count',
                                             'radius', 'health', 'decals_list',
                                             'linkedReference',
                                             'startRed', 'startGreen', 'startBlue',
                                             'endRed', 'endGreen', 'endBlue',
                                             'activateParentFlags',
                                             'activateParentRefs_list', 'prompt',
                                             'parent', 'parentFlags', 'emittance',
                                             'boundRef', 'reflrefrs_list',
                                             'ignoredBySandbox', 'scale',
                                             'posX', 'posY', 'posZ', 'rotX', 'rotY', 'rotZ']# 'xrgd_p', 'xrgb_p', 'compiled_p',

class FnvPMISRecord(FnvBaseRecord):
    @property
    def _ParentID(self):
        _CGetField.restype = c_ulong
        return _CGetField(self._RecordID, 56, 0, 0, 0, 0, 0, 0, 0)

    _Type = 'PMIS'
    class Decal(ListComponent):
        FORMID_LISTMACRO(reference, 1)
        UINT8_ARRAY_LISTMACRO(unknown1, 2, 24)
        copyattrs = ['reference', 'unknown1']
        exportattrs = ['reference']#, 'unknown1'

    class ParentRef(ListComponent):
        FORMID_LISTMACRO(reference, 1)
        FLOAT32_LISTMACRO(delay, 2)
        exportattrs = copyattrs = ['reference', 'delay']

    class ReflRefr(ListComponent):
        FORMID_LISTMACRO(reference, 1)
        UINT32_TYPE_LISTMACRO(type, 2)

        BasicTypeMACRO(IsReflection, type, 0, IsRefraction)
        BasicTypeMACRO(IsRefraction, type, 1, IsReflection)
        exportattrs = copyattrs = ['reference', 'type']

    FORMID_MACRO(base, 7)
    FORMID_MACRO(encounterZone, 8)
    UINT8_ARRAY_MACRO(xrgd_p, 9)
    UINT8_ARRAY_MACRO(xrgb_p, 10)
    FLOAT32_MACRO(idleTime, 11)
    FORMID_MACRO(idle, 12)
    UINT8_ARRAY_MACRO(unused1, 13, 4)
    UINT32_MACRO(numRefs, 14)
    UINT32_MACRO(compiledSize, 15)
    UINT32_MACRO(lastIndex, 16)
    UINT16_TYPE_MACRO(scriptType, 17)
    UINT16_FLAG_MACRO(scriptFlags, 18)
    UINT8_ARRAY_MACRO(compiled_p, 19)
    ISTRING_MACRO(scriptText, 20)

    LIST_MACRO(vars, 21, Var)
    FORMID_OR_UINT32_ARRAY_MACRO(references, 22)
    FORMID_MACRO(topic, 23)
    FORMID_MACRO(owner, 24)
    SINT32_MACRO(rank, 25)
    SINT32_MACRO(count, 26)
    FLOAT32_MACRO(radius, 27)
    FLOAT32_MACRO(health, 28)

    LIST_MACRO(decals, 29, self.Decal)
    FORMID_MACRO(linkedReference, 30)
    UINT8_MACRO(startRed, 31)
    UINT8_MACRO(startGreen, 32)
    UINT8_MACRO(startBlue, 33)
    UINT8_ARRAY_MACRO(unused2, 34, 1)
    UINT8_MACRO(endRed, 35)
    UINT8_MACRO(endGreen, 36)
    UINT8_MACRO(endBlue, 37)
    UINT8_ARRAY_MACRO(unused3, 38, 1)
    UINT8_FLAG_MACRO(activateParentFlags, 39)

    LIST_MACRO(activateParentRefs, 40, self.ParentRef)
    STRING_MACRO(prompt, 41)
    FORMID_MACRO(parent, 42)
    UINT8_FLAG_MACRO(parentFlags, 43)
    UINT8_ARRAY_MACRO(unused4, 44, 3)
    FORMID_MACRO(emittance, 45)
    FORMID_MACRO(boundRef, 46)

    LIST_MACRO(reflrefrs, 47, self.ReflRefr)
    BOOL_MACRO(ignoredBySandbox, 48)
    FLOAT32_MACRO(scale, 49)
    FLOAT32_MACRO(posX, 50)
    FLOAT32_MACRO(posY, 51)
    FLOAT32_MACRO(posZ, 52)
    RADIAN_MACRO(rotX, 53)
    RADIAN_MACRO(rotY, 54)
    RADIAN_MACRO(rotZ, 55)

    BasicFlagMACRO(IsEnabled, scriptFlags, 0x0001)

    BasicFlagMACRO(IsOppositeParent, parentFlags, 0x00000001)
    BasicFlagMACRO(IsPopIn, parentFlags, 0x00000002)

    BasicTypeMACRO(IsObject, scriptType, 0x0000, IsQuest)
    BasicTypeMACRO(IsQuest, scriptType, 0x0001, IsObject)
    BasicTypeMACRO(IsEffect, scriptType, 0x0100, IsObject)

    copyattrs = FnvBaseRecord.baseattrs + ['base', 'encounterZone', 'xrgd_p', 'xrgb_p',
                                           'idleTime', 'idle', 'numRefs', 'compiledSize',
                                           'lastIndex', 'scriptType', 'scriptFlags',
                                           'compiled_p', 'scriptText', 'vars_list',
                                           'references', 'topic', 'owner',
                                           'rank', 'count',
                                           'radius', 'health', 'decals_list',
                                           'linkedReference',
                                           'startRed', 'startGreen', 'startBlue',
                                           'endRed', 'endGreen', 'endBlue',
                                           'activateParentFlags',
                                           'activateParentRefs_list', 'prompt',
                                           'parent', 'parentFlags', 'emittance',
                                           'boundRef', 'reflrefrs_list',
                                           'ignoredBySandbox', 'scale',
                                           'posX', 'posY', 'posZ', 'rotX', 'rotY', 'rotZ']

    exportattrs = FnvBaseRecord.baseattrs + ['base', 'encounterZone',
                                             'idleTime', 'idle', 'numRefs', 'compiledSize',
                                             'lastIndex', 'scriptType', 'scriptFlags',
                                             'scriptText', 'vars_list',
                                             'references', 'topic', 'owner',
                                             'rank', 'count',
                                             'radius', 'health', 'decals_list',
                                             'linkedReference',
                                             'startRed', 'startGreen', 'startBlue',
                                             'endRed', 'endGreen', 'endBlue',
                                             'activateParentFlags',
                                             'activateParentRefs_list', 'prompt',
                                             'parent', 'parentFlags', 'emittance',
                                             'boundRef', 'reflrefrs_list',
                                             'ignoredBySandbox', 'scale',
                                             'posX', 'posY', 'posZ', 'rotX', 'rotY', 'rotZ']# 'xrgd_p', 'xrgb_p', 'compiled_p',

class FnvPBEARecord(FnvBaseRecord):
    @property
    def _ParentID(self):
        _CGetField.restype = c_ulong
        return _CGetField(self._RecordID, 56, 0, 0, 0, 0, 0, 0, 0)

    _Type = 'PBEA'
    class Decal(ListComponent):
        FORMID_LISTMACRO(reference, 1)
        UINT8_ARRAY_LISTMACRO(unknown1, 2, 24)
        copyattrs = ['reference', 'unknown1']
        exportattrs = ['reference']#, 'unknown1'

    class ParentRef(ListComponent):
        FORMID_LISTMACRO(reference, 1)
        FLOAT32_LISTMACRO(delay, 2)
        exportattrs = copyattrs = ['reference', 'delay']

    class ReflRefr(ListComponent):
        FORMID_LISTMACRO(reference, 1)
        UINT32_TYPE_LISTMACRO(type, 2)

        BasicTypeMACRO(IsReflection, type, 0, IsRefraction)
        BasicTypeMACRO(IsRefraction, type, 1, IsReflection)
        exportattrs = copyattrs = ['reference', 'type']

    FORMID_MACRO(base, 7)
    FORMID_MACRO(encounterZone, 8)
    UINT8_ARRAY_MACRO(xrgd_p, 9)
    UINT8_ARRAY_MACRO(xrgb_p, 10)
    FLOAT32_MACRO(idleTime, 11)
    FORMID_MACRO(idle, 12)
    UINT8_ARRAY_MACRO(unused1, 13, 4)
    UINT32_MACRO(numRefs, 14)
    UINT32_MACRO(compiledSize, 15)
    UINT32_MACRO(lastIndex, 16)
    UINT16_TYPE_MACRO(scriptType, 17)
    UINT16_FLAG_MACRO(scriptFlags, 18)
    UINT8_ARRAY_MACRO(compiled_p, 19)
    ISTRING_MACRO(scriptText, 20)

    LIST_MACRO(vars, 21, Var)
    FORMID_OR_UINT32_ARRAY_MACRO(references, 22)
    FORMID_MACRO(topic, 23)
    FORMID_MACRO(owner, 24)
    SINT32_MACRO(rank, 25)
    SINT32_MACRO(count, 26)
    FLOAT32_MACRO(radius, 27)
    FLOAT32_MACRO(health, 28)

    LIST_MACRO(decals, 29, self.Decal)
    FORMID_MACRO(linkedReference, 30)
    UINT8_MACRO(startRed, 31)
    UINT8_MACRO(startGreen, 32)
    UINT8_MACRO(startBlue, 33)
    UINT8_ARRAY_MACRO(unused2, 34, 1)
    UINT8_MACRO(endRed, 35)
    UINT8_MACRO(endGreen, 36)
    UINT8_MACRO(endBlue, 37)
    UINT8_ARRAY_MACRO(unused3, 38, 1)
    UINT8_FLAG_MACRO(activateParentFlags, 39)

    LIST_MACRO(activateParentRefs, 40, self.ParentRef)
    STRING_MACRO(prompt, 41)
    FORMID_MACRO(parent, 42)
    UINT8_FLAG_MACRO(parentFlags, 43)
    UINT8_ARRAY_MACRO(unused4, 44, 3)
    FORMID_MACRO(emittance, 45)
    FORMID_MACRO(boundRef, 46)

    LIST_MACRO(reflrefrs, 47, self.ReflRefr)
    BOOL_MACRO(ignoredBySandbox, 48)
    FLOAT32_MACRO(scale, 49)
    FLOAT32_MACRO(posX, 50)
    FLOAT32_MACRO(posY, 51)
    FLOAT32_MACRO(posZ, 52)
    RADIAN_MACRO(rotX, 53)
    RADIAN_MACRO(rotY, 54)
    RADIAN_MACRO(rotZ, 55)

    BasicFlagMACRO(IsEnabled, scriptFlags, 0x0001)

    BasicFlagMACRO(IsOppositeParent, parentFlags, 0x00000001)
    BasicFlagMACRO(IsPopIn, parentFlags, 0x00000002)

    BasicTypeMACRO(IsObject, scriptType, 0x0000, IsQuest)
    BasicTypeMACRO(IsQuest, scriptType, 0x0001, IsObject)
    BasicTypeMACRO(IsEffect, scriptType, 0x0100, IsObject)

    copyattrs = FnvBaseRecord.baseattrs + ['base', 'encounterZone', 'xrgd_p', 'xrgb_p',
                                           'idleTime', 'idle', 'numRefs', 'compiledSize',
                                           'lastIndex', 'scriptType', 'scriptFlags',
                                           'compiled_p', 'scriptText', 'vars_list',
                                           'references', 'topic', 'owner',
                                           'rank', 'count',
                                           'radius', 'health', 'decals_list',
                                           'linkedReference',
                                           'startRed', 'startGreen', 'startBlue',
                                           'endRed', 'endGreen', 'endBlue',
                                           'activateParentFlags',
                                           'activateParentRefs_list', 'prompt',
                                           'parent', 'parentFlags', 'emittance',
                                           'boundRef', 'reflrefrs_list',
                                           'ignoredBySandbox', 'scale',
                                           'posX', 'posY', 'posZ', 'rotX', 'rotY', 'rotZ']

    exportattrs = FnvBaseRecord.baseattrs + ['base', 'encounterZone',
                                             'idleTime', 'idle', 'numRefs', 'compiledSize',
                                             'lastIndex', 'scriptType', 'scriptFlags',
                                             'scriptText', 'vars_list',
                                             'references', 'topic', 'owner',
                                             'rank', 'count',
                                             'radius', 'health', 'decals_list',
                                             'linkedReference',
                                             'startRed', 'startGreen', 'startBlue',
                                             'endRed', 'endGreen', 'endBlue',
                                             'activateParentFlags',
                                             'activateParentRefs_list', 'prompt',
                                             'parent', 'parentFlags', 'emittance',
                                             'boundRef', 'reflrefrs_list',
                                             'ignoredBySandbox', 'scale',
                                             'posX', 'posY', 'posZ', 'rotX', 'rotY', 'rotZ']# 'xrgd_p', 'xrgb_p', 'compiled_p',

class FnvPFLARecord(FnvBaseRecord):
    @property
    def _ParentID(self):
        _CGetField.restype = c_ulong
        return _CGetField(self._RecordID, 56, 0, 0, 0, 0, 0, 0, 0)

    _Type = 'PFLA'
    class Decal(ListComponent):
        FORMID_LISTMACRO(reference, 1)
        UINT8_ARRAY_LISTMACRO(unknown1, 2, 24)
        copyattrs = ['reference', 'unknown1']
        exportattrs = ['reference']#, 'unknown1'

    class ParentRef(ListComponent):
        FORMID_LISTMACRO(reference, 1)
        FLOAT32_LISTMACRO(delay, 2)
        exportattrs = copyattrs = ['reference', 'delay']

    class ReflRefr(ListComponent):
        FORMID_LISTMACRO(reference, 1)
        UINT32_TYPE_LISTMACRO(type, 2)

        BasicTypeMACRO(IsReflection, type, 0, IsRefraction)
        BasicTypeMACRO(IsRefraction, type, 1, IsReflection)
        exportattrs = copyattrs = ['reference', 'type']

    FORMID_MACRO(base, 7)
    FORMID_MACRO(encounterZone, 8)
    UINT8_ARRAY_MACRO(xrgd_p, 9)
    UINT8_ARRAY_MACRO(xrgb_p, 10)
    FLOAT32_MACRO(idleTime, 11)
    FORMID_MACRO(idle, 12)
    UINT8_ARRAY_MACRO(unused1, 13, 4)
    UINT32_MACRO(numRefs, 14)
    UINT32_MACRO(compiledSize, 15)
    UINT32_MACRO(lastIndex, 16)
    UINT16_TYPE_MACRO(scriptType, 17)
    UINT16_FLAG_MACRO(scriptFlags, 18)
    UINT8_ARRAY_MACRO(compiled_p, 19)
    ISTRING_MACRO(scriptText, 20)

    LIST_MACRO(vars, 21, Var)
    FORMID_OR_UINT32_ARRAY_MACRO(references, 22)
    FORMID_MACRO(topic, 23)
    FORMID_MACRO(owner, 24)
    SINT32_MACRO(rank, 25)
    SINT32_MACRO(count, 26)
    FLOAT32_MACRO(radius, 27)
    FLOAT32_MACRO(health, 28)

    LIST_MACRO(decals, 29, self.Decal)
    FORMID_MACRO(linkedReference, 30)
    UINT8_MACRO(startRed, 31)
    UINT8_MACRO(startGreen, 32)
    UINT8_MACRO(startBlue, 33)
    UINT8_ARRAY_MACRO(unused2, 34, 1)
    UINT8_MACRO(endRed, 35)
    UINT8_MACRO(endGreen, 36)
    UINT8_MACRO(endBlue, 37)
    UINT8_ARRAY_MACRO(unused3, 38, 1)
    UINT8_FLAG_MACRO(activateParentFlags, 39)

    LIST_MACRO(activateParentRefs, 40, self.ParentRef)
    STRING_MACRO(prompt, 41)
    FORMID_MACRO(parent, 42)
    UINT8_FLAG_MACRO(parentFlags, 43)
    UINT8_ARRAY_MACRO(unused4, 44, 3)
    FORMID_MACRO(emittance, 45)
    FORMID_MACRO(boundRef, 46)

    LIST_MACRO(reflrefrs, 47, self.ReflRefr)
    BOOL_MACRO(ignoredBySandbox, 48)
    FLOAT32_MACRO(scale, 49)
    FLOAT32_MACRO(posX, 50)
    FLOAT32_MACRO(posY, 51)
    FLOAT32_MACRO(posZ, 52)
    RADIAN_MACRO(rotX, 53)
    RADIAN_MACRO(rotY, 54)
    RADIAN_MACRO(rotZ, 55)

    BasicFlagMACRO(IsEnabled, scriptFlags, 0x0001)

    BasicFlagMACRO(IsOppositeParent, parentFlags, 0x00000001)
    BasicFlagMACRO(IsPopIn, parentFlags, 0x00000002)

    BasicTypeMACRO(IsObject, scriptType, 0x0000, IsQuest)
    BasicTypeMACRO(IsQuest, scriptType, 0x0001, IsObject)
    BasicTypeMACRO(IsEffect, scriptType, 0x0100, IsObject)

    copyattrs = FnvBaseRecord.baseattrs + ['base', 'encounterZone', 'xrgd_p', 'xrgb_p',
                                           'idleTime', 'idle', 'numRefs', 'compiledSize',
                                           'lastIndex', 'scriptType', 'scriptFlags',
                                           'compiled_p', 'scriptText', 'vars_list',
                                           'references', 'topic', 'owner',
                                           'rank', 'count',
                                           'radius', 'health', 'decals_list',
                                           'linkedReference',
                                           'startRed', 'startGreen', 'startBlue',
                                           'endRed', 'endGreen', 'endBlue',
                                           'activateParentFlags',
                                           'activateParentRefs_list', 'prompt',
                                           'parent', 'parentFlags', 'emittance',
                                           'boundRef', 'reflrefrs_list',
                                           'ignoredBySandbox', 'scale',
                                           'posX', 'posY', 'posZ', 'rotX', 'rotY', 'rotZ']

    exportattrs = FnvBaseRecord.baseattrs + ['base', 'encounterZone',
                                             'idleTime', 'idle', 'numRefs', 'compiledSize',
                                             'lastIndex', 'scriptType', 'scriptFlags',
                                             'scriptText', 'vars_list',
                                             'references', 'topic', 'owner',
                                             'rank', 'count',
                                             'radius', 'health', 'decals_list',
                                             'linkedReference',
                                             'startRed', 'startGreen', 'startBlue',
                                             'endRed', 'endGreen', 'endBlue',
                                             'activateParentFlags',
                                             'activateParentRefs_list', 'prompt',
                                             'parent', 'parentFlags', 'emittance',
                                             'boundRef', 'reflrefrs_list',
                                             'ignoredBySandbox', 'scale',
                                             'posX', 'posY', 'posZ', 'rotX', 'rotY', 'rotZ']# 'xrgd_p', 'xrgb_p', 'compiled_p',

class FnvPCBERecord(FnvBaseRecord):
    @property
    def _ParentID(self):
        _CGetField.restype = c_ulong
        return _CGetField(self._RecordID, 56, 0, 0, 0, 0, 0, 0, 0)

    _Type = 'PCBE'
    class Decal(ListComponent):
        FORMID_LISTMACRO(reference, 1)
        UINT8_ARRAY_LISTMACRO(unknown1, 2, 24)
        copyattrs = ['reference', 'unknown1']
        exportattrs = ['reference']#, 'unknown1'

    class ParentRef(ListComponent):
        FORMID_LISTMACRO(reference, 1)
        FLOAT32_LISTMACRO(delay, 2)
        exportattrs = copyattrs = ['reference', 'delay']

    class ReflRefr(ListComponent):
        FORMID_LISTMACRO(reference, 1)
        UINT32_TYPE_LISTMACRO(type, 2)

        BasicTypeMACRO(IsReflection, type, 0, IsRefraction)
        BasicTypeMACRO(IsRefraction, type, 1, IsReflection)
        exportattrs = copyattrs = ['reference', 'type']

    FORMID_MACRO(base, 7)
    FORMID_MACRO(encounterZone, 8)
    UINT8_ARRAY_MACRO(xrgd_p, 9)
    UINT8_ARRAY_MACRO(xrgb_p, 10)
    FLOAT32_MACRO(idleTime, 11)
    FORMID_MACRO(idle, 12)
    UINT8_ARRAY_MACRO(unused1, 13, 4)
    UINT32_MACRO(numRefs, 14)
    UINT32_MACRO(compiledSize, 15)
    UINT32_MACRO(lastIndex, 16)
    UINT16_TYPE_MACRO(scriptType, 17)
    UINT16_FLAG_MACRO(scriptFlags, 18)
    UINT8_ARRAY_MACRO(compiled_p, 19)
    ISTRING_MACRO(scriptText, 20)

    LIST_MACRO(vars, 21, Var)
    FORMID_OR_UINT32_ARRAY_MACRO(references, 22)
    FORMID_MACRO(topic, 23)
    FORMID_MACRO(owner, 24)
    SINT32_MACRO(rank, 25)
    SINT32_MACRO(count, 26)
    FLOAT32_MACRO(radius, 27)
    FLOAT32_MACRO(health, 28)

    LIST_MACRO(decals, 29, self.Decal)
    FORMID_MACRO(linkedReference, 30)
    UINT8_MACRO(startRed, 31)
    UINT8_MACRO(startGreen, 32)
    UINT8_MACRO(startBlue, 33)
    UINT8_ARRAY_MACRO(unused2, 34, 1)
    UINT8_MACRO(endRed, 35)
    UINT8_MACRO(endGreen, 36)
    UINT8_MACRO(endBlue, 37)
    UINT8_ARRAY_MACRO(unused3, 38, 1)
    UINT8_FLAG_MACRO(activateParentFlags, 39)

    LIST_MACRO(activateParentRefs, 40, self.ParentRef)
    STRING_MACRO(prompt, 41)
    FORMID_MACRO(parent, 42)
    UINT8_FLAG_MACRO(parentFlags, 43)
    UINT8_ARRAY_MACRO(unused4, 44, 3)
    FORMID_MACRO(emittance, 45)
    FORMID_MACRO(boundRef, 46)

    LIST_MACRO(reflrefrs, 47, self.ReflRefr)
    BOOL_MACRO(ignoredBySandbox, 48)
    FLOAT32_MACRO(scale, 49)
    FLOAT32_MACRO(posX, 50)
    FLOAT32_MACRO(posY, 51)
    FLOAT32_MACRO(posZ, 52)
    RADIAN_MACRO(rotX, 53)
    RADIAN_MACRO(rotY, 54)
    RADIAN_MACRO(rotZ, 55)

    BasicFlagMACRO(IsEnabled, scriptFlags, 0x0001)

    BasicFlagMACRO(IsOppositeParent, parentFlags, 0x00000001)
    BasicFlagMACRO(IsPopIn, parentFlags, 0x00000002)

    BasicTypeMACRO(IsObject, scriptType, 0x0000, IsQuest)
    BasicTypeMACRO(IsQuest, scriptType, 0x0001, IsObject)
    BasicTypeMACRO(IsEffect, scriptType, 0x0100, IsObject)

    copyattrs = FnvBaseRecord.baseattrs + ['base', 'encounterZone', 'xrgd_p', 'xrgb_p',
                                           'idleTime', 'idle', 'numRefs', 'compiledSize',
                                           'lastIndex', 'scriptType', 'scriptFlags',
                                           'compiled_p', 'scriptText', 'vars_list',
                                           'references', 'topic', 'owner',
                                           'rank', 'count',
                                           'radius', 'health', 'decals_list',
                                           'linkedReference',
                                           'startRed', 'startGreen', 'startBlue',
                                           'endRed', 'endGreen', 'endBlue',
                                           'activateParentFlags',
                                           'activateParentRefs_list', 'prompt',
                                           'parent', 'parentFlags', 'emittance',
                                           'boundRef', 'reflrefrs_list',
                                           'ignoredBySandbox', 'scale',
                                           'posX', 'posY', 'posZ', 'rotX', 'rotY', 'rotZ']

    exportattrs = FnvBaseRecord.baseattrs + ['base', 'encounterZone',
                                             'idleTime', 'idle', 'numRefs', 'compiledSize',
                                             'lastIndex', 'scriptType', 'scriptFlags',
                                             'scriptText', 'vars_list',
                                             'references', 'topic', 'owner',
                                             'rank', 'count',
                                             'radius', 'health', 'decals_list',
                                             'linkedReference',
                                             'startRed', 'startGreen', 'startBlue',
                                             'endRed', 'endGreen', 'endBlue',
                                             'activateParentFlags',
                                             'activateParentRefs_list', 'prompt',
                                             'parent', 'parentFlags', 'emittance',
                                             'boundRef', 'reflrefrs_list',
                                             'ignoredBySandbox', 'scale',
                                             'posX', 'posY', 'posZ', 'rotX', 'rotY', 'rotZ']# 'xrgd_p', 'xrgb_p', 'compiled_p',

class FnvNAVMRecord(FnvBaseRecord):
    @property
    def _ParentID(self):
        _CGetField.restype = c_ulong
        return _CGetField(self._RecordID, 20, 0, 0, 0, 0, 0, 0, 0)

    _Type = 'NAVM'
    class Vertex(ListComponent):
        FLOAT32_LISTMACRO(x, 1)
        FLOAT32_LISTMACRO(y, 2)
        FLOAT32_LISTMACRO(z, 3)

        exportattrs = copyattrs = ['x', 'y', 'z']

    class Triangle(ListComponent):
        SINT16_LISTMACRO(vertex1, 1)
        SINT16_LISTMACRO(vertex2, 2)
        SINT16_LISTMACRO(vertex3, 3)
        SINT16_LISTMACRO(edge1, 4)
        SINT16_LISTMACRO(edge2, 5)
        SINT16_LISTMACRO(edge3, 6)
        UINT32_FLAG_LISTMACRO(flags, 7)

        BasicFlagMACRO(IsTriangle0External, flags, 0x00000001)
        BasicFlagMACRO(IsTriangle1External, flags, 0x00000002)
        BasicFlagMACRO(IsTriangle2External, flags, 0x00000004)
        BasicFlagMACRO(IsUnknown4, flags, 0x00000008)
        BasicFlagMACRO(IsUnknown5, flags, 0x00000010)
        BasicFlagMACRO(IsUnknown6, flags, 0x00000020)
        BasicFlagMACRO(IsUnknown7, flags, 0x00000040)
        BasicFlagMACRO(IsUnknown8, flags, 0x00000080)
        BasicFlagMACRO(IsUnknown9, flags, 0x00000100)
        BasicFlagMACRO(IsUnknown10, flags, 0x00000200)
        BasicFlagMACRO(IsUnknown11, flags, 0x00000400)
        BasicFlagMACRO(IsUnknown12, flags, 0x00000800)
        BasicFlagMACRO(IsUnknown13, flags, 0x00001000)
        BasicFlagMACRO(IsUnknown14, flags, 0x00002000)
        BasicFlagMACRO(IsUnknown15, flags, 0x00004000)
        BasicFlagMACRO(IsUnknown16, flags, 0x00008000)
        BasicFlagMACRO(IsUnknown17, flags, 0x00010000)
        BasicFlagMACRO(IsUnknown18, flags, 0x00020000)
        BasicFlagMACRO(IsUnknown19, flags, 0x00040000)
        BasicFlagMACRO(IsUnknown20, flags, 0x00080000)
        BasicFlagMACRO(IsUnknown21, flags, 0x00100000)
        BasicFlagMACRO(IsUnknown22, flags, 0x00200000)
        BasicFlagMACRO(IsUnknown23, flags, 0x00400000)
        BasicFlagMACRO(IsUnknown24, flags, 0x00800000)
        BasicFlagMACRO(IsUnknown25, flags, 0x01000000)
        BasicFlagMACRO(IsUnknown26, flags, 0x02000000)
        BasicFlagMACRO(IsUnknown27, flags, 0x04000000)
        BasicFlagMACRO(IsUnknown28, flags, 0x08000000)
        BasicFlagMACRO(IsUnknown29, flags, 0x10000000)
        BasicFlagMACRO(IsUnknown30, flags, 0x20000000)
        BasicFlagMACRO(IsUnknown31, flags, 0x40000000)
        BasicFlagMACRO(IsUnknown32, flags, 0x80000000)
        exportattrs = copyattrs = ['vertex1', 'vertex2', 'vertex3', 'edge1', 'edge2', 'edge3', 'flags']

    class Door(ListComponent):
        FORMID_LISTMACRO(door, 1)
        UINT16_LISTMACRO(unknown1, 2)
        UINT8_ARRAY_LISTMACRO(unused1, 3, 2)

        exportattrs = copyattrs = ['door', 'unknown1']

    class Connection(ListComponent):
        UINT8_ARRAY_LISTMACRO(unknown1, 1)
        FORMID_LISTMACRO(mesh, 2)
        UINT16_LISTMACRO(triangle, 3)

        exportattrs = copyattrs = ['unknown1', 'mesh', 'triangle']

    UINT32_MACRO(version, 7)
    FORMID_MACRO(cell, 8)
    UINT32_MACRO(numVertices, 9)
    UINT32_MACRO(numTriangles, 10)
    UINT32_MACRO(numConnections, 11)
    UINT32_MACRO(numUnknown, 12)
    UINT32_MACRO(numDoors, 13)

    LIST_MACRO(vertices, 14, self.Vertex)
    LIST_MACRO(triangles, 15, self.Triangle)
    SINT16_ARRAY_MACRO(unknown1, 16)

    LIST_MACRO(doors, 17, self.Door)
    UINT8_ARRAY_MACRO(nvgd_p, 18)

    LIST_MACRO(connections, 19, self.Connection)
    copyattrs = FnvBaseRecord.baseattrs + ['version', 'cell', 'numVertices',
                                           'numTriangles', 'numConnections',
                                           'numUnknown', 'numDoors',
                                           'vertices_list', 'triangles_list',
                                           'unknown1', 'doors_list', 'nvgd_p',
                                           'connections_list']
    exportattrs = FnvBaseRecord.baseattrs + ['version', 'cell', 'numVertices',
                                             'numTriangles', 'numConnections',
                                             'numUnknown', 'numDoors',
                                             'vertices_list', 'triangles_list',
                                             'unknown1', 'doors_list',
                                             'connections_list']# 'nvgd_p',

class FnvLANDRecord(FnvBaseRecord):
    @property
    def _ParentID(self):
        _CGetField.restype = c_ulong
        return _CGetField(self._RecordID, 17, 0, 0, 0, 0, 0, 0, 0)

    _Type = 'LAND'
    class Normal(ListX2Component):
        UINT8_LISTX2MACRO(x, 1)
        UINT8_LISTX2MACRO(y, 2)
        UINT8_LISTX2MACRO(z, 3)
        exportattrs = copyattrs = ['x', 'y', 'z']

    class Height(ListX2Component):
        SINT8_LISTX2MACRO(height, 1)
        exportattrs = copyattrs = ['height']

    class Color(ListX2Component):
        UINT8_LISTX2MACRO(red, 1)
        UINT8_LISTX2MACRO(green, 2)
        UINT8_LISTX2MACRO(blue, 3)
        exportattrs = copyattrs = ['red', 'green', 'blue']

    class BaseTexture(ListComponent):
        FORMID_LISTMACRO(texture, 1)
        SINT8_LISTMACRO(quadrant, 2)
        UINT8_ARRAY_LISTMACRO(unused1, 3, 1)
        SINT16_LISTMACRO(layer, 4)
        exportattrs = copyattrs = ['texture', 'quadrant', 'layer']

    class AlphaLayer(ListComponent):
        class Opacity(ListX2Component):
            UINT16_LISTX2MACRO(position, 1)
            UINT8_ARRAY_LISTX2MACRO(unused1, 2, 2)
            FLOAT32_LISTX2MACRO(opacity, 3)
            exportattrs = copyattrs = ['position', 'opacity']
        FORMID_LISTMACRO(texture, 1)
        SINT8_LISTMACRO(quadrant, 2)
        UINT8_ARRAY_LISTMACRO(unused1, 3, 1)
        SINT16_LISTMACRO(layer, 4)

        LIST_LISTMACRO(opacities, 5, self.Opacity)
        exportattrs = copyattrs = ['texture', 'quadrant', 'layer', 'opacities_list']

    class VertexTexture(ListComponent):
        FORMID_LISTMACRO(texture, 1)
        exportattrs = copyattrs = ['texture']

    class Position(ListX2Component):
        FLOAT32_LISTX2MACRO(height, 1)
        UINT8_LISTX2MACRO(normalX, 2)
        UINT8_LISTX2MACRO(normalY, 3)
        UINT8_LISTX2MACRO(normalZ, 4)
        UINT8_LISTX2MACRO(red, 5)
        UINT8_LISTX2MACRO(green, 6)
        UINT8_LISTX2MACRO(blue, 7)
        FORMID_LISTX2MACRO(baseTexture, 8)
        FORMID_LISTX2MACRO(alphaLayer1Texture, 9)
        FLOAT32_LISTX2MACRO(alphaLayer1Opacity, 10)
        FORMID_LISTX2MACRO(alphaLayer2Texture, 11)
        FLOAT32_LISTX2MACRO(alphaLayer2Opacity, 12)
        FORMID_LISTX2MACRO(alphaLayer3Texture, 13)
        FLOAT32_LISTX2MACRO(alphaLayer3Opacity, 14)
        FORMID_LISTX2MACRO(alphaLayer4Texture, 15)
        FLOAT32_LISTX2MACRO(alphaLayer4Opacity, 16)
        FORMID_LISTX2MACRO(alphaLayer5Texture, 17)
        FLOAT32_LISTX2MACRO(alphaLayer5Opacity, 18)
        FORMID_LISTX2MACRO(alphaLayer6Texture, 19)
        FLOAT32_LISTX2MACRO(alphaLayer6Opacity, 20)
        FORMID_LISTX2MACRO(alphaLayer7Texture, 21)
        FLOAT32_LISTX2MACRO(alphaLayer7Opacity, 22)
        FORMID_LISTX2MACRO(alphaLayer8Texture, 23)
        FLOAT32_LISTX2MACRO(alphaLayer8Opacity, 24)
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

    UINT8_ARRAY_MACRO(data_p, 7)

    def get_normals(self):
        return [[self.Normal(self._RecordID, 8, x, 0, y) for y in range(0,33)] for x in range(0,33)]
    def set_normals(self, nElements):
        if nElements is None or len(nElements) != 33: return
        if isinstance(nElements[0], tuple): nValues = nElements
        else: nValues = [ExtractCopyList(nElements[x]) for x in range(0,33)]
        oElements = self.normals
        for x in range(0,33):
            SetCopyList(oElements[x], nValues[x])
    normals = property(get_normals, set_normals)
    def get_normals_list(self):
        return [ExtractCopyList([self.Normal(self._RecordID, 8, x, 0, y) for y in range(0,33)]) for x in range(0,33)]

    normals_list = property(get_normals_list, set_normals)

    FLOAT32_MACRO(heightOffset, 9)

    def get_heights(self):
        return [[self.Height(self._RecordID, 10, x, 0, y) for y in range(0,33)] for x in range(0,33)]
    def set_heights(self, nElements):
        if nElements is None or len(nElements) != 33: return
        if isinstance(nElements[0], tuple): nValues = nElements
        else: nValues = [ExtractCopyList(nElements[x]) for x in range(0,33)]
        oElements = self.heights
        for x in range(0,33):
            SetCopyList(oElements[x], nValues[x])
    heights = property(get_heights, set_heights)
    def get_heights_list(self):
        return [ExtractCopyList([self.Height(self._RecordID, 10, x, 0, y) for y in range(0,33)]) for x in range(0,33)]
    heights_list = property(get_heights_list, set_heights)

    UINT8_ARRAY_MACRO(unused1, 11, 3)

    def get_colors(self):
        return [[self.Color(self._RecordID, 12, x, 0, y) for y in range(0,33)] for x in range(0,33)]
    def set_colors(self, nElements):
        if nElements is None or len(nElements) != 33: return
        if isinstance(nElements[0], tuple): nValues = nElements
        else: nValues = [ExtractCopyList(nElements[x]) for x in range(0,33)]
        oElements = self.colors
        for x in range(0,33):
            SetCopyList(oElements[x], nValues[x])
    colors = property(get_colors, set_colors)
    def get_colors_list(self):
        return [ExtractCopyList([self.Color(self._RecordID, 12, x, 0, y) for y in range(0,33)]) for x in range(0,33)]
    colors_list = property(get_colors_list, set_colors)

    LIST_MACRO(baseTextures, 13, self.BaseTexture)
    LIST_MACRO(alphaLayers, 14, self.AlphaLayer)
    LIST_MACRO(vertexTextures, 15, self.VertexTexture)
    ##The Positions accessor is unique in that it duplicates the above accessors. It just presents the data in a more friendly format.
    def get_Positions(self):
        return [[self.Position(self._RecordID, 16, row, 0, column) for column in range(0,33)] for row in range(0,33)]
    def set_Positions(self, nElements):
        if nElements is None or len(nElements) != 33: return
        if isinstance(nElements[0], tuple): nValues = nElements
        else: nValues = [ExtractCopyList(nElements[x]) for x in range(0,33)]
        oElements = self.Positions
        for x in range(0,33):
            SetCopyList(oElements[x], nValues[x])
    Positions = property(get_Positions, set_Positions)
    def get_Positions_list(self):
        return [ExtractCopyList([self.Position(self._RecordID, 16, x, 0, y) for y in range(0,33)]) for x in range(0,33)]
    Positions_list = property(get_Positions_list, set_Positions)
    copyattrs = FnvBaseRecord.baseattrs + ['data_p', 'normals_list', 'heights_list', 'heightOffset',
                                        'colors_list', 'baseTextures_list', 'alphaLayers_list',
                                        'vertexTextures_list']
    exportattrs = FnvBaseRecord.baseattrs + ['normals_list', 'heights_list', 'heightOffset',
                                        'colors_list', 'baseTextures_list', 'alphaLayers_list',
                                        'vertexTextures_list'] #'data_p',

class FnvINFORecord(FnvBaseRecord):
    @property
    def _ParentID(self):
        _CGetField.restype = c_ulong
        return _CGetField(self._RecordID, 44, 0, 0, 0, 0, 0, 0, 0)

    _Type = 'INFO'
    class Response(ListComponent):
        UINT32_TYPE_LISTMACRO(emotionType, 1)
        SINT32_LISTMACRO(emotionValue, 2)
        UINT8_ARRAY_LISTMACRO(unused1, 3, 4)
        UINT8_LISTMACRO(responseNum, 4)
        UINT8_ARRAY_LISTMACRO(unused2, 5, 3)
        FORMID_LISTMACRO(sound, 6)
        UINT8_FLAG_LISTMACRO(flags, 7)
        UINT8_ARRAY_LISTMACRO(unused3, 8, 3)
        STRING_LISTMACRO(responseText, 9)
        ISTRING_LISTMACRO(actorNotes, 10)
        ISTRING_LISTMACRO(editNotes, 11)
        FORMID_LISTMACRO(speakerAnim, 12)
        FORMID_LISTMACRO(listenerAnim, 13)

        BasicFlagMACRO(IsUseEmotionAnim, flags, 0x01)

        BasicTypeMACRO(IsNeutral, emotionType, 0, IsAnger)
        BasicTypeMACRO(IsAnger, emotionType, 1, IsNeutral)
        BasicTypeMACRO(IsDisgust, emotionType, 2, IsNeutral)
        BasicTypeMACRO(IsFear, emotionType, 3, IsNeutral)
        BasicTypeMACRO(IsSad, emotionType, 4, IsNeutral)
        BasicTypeMACRO(IsHappy, emotionType, 5, IsNeutral)
        BasicTypeMACRO(IsSurprise, emotionType, 6, IsNeutral)
        BasicTypeMACRO(IsPained, emotionType, 7, IsNeutral)
        exportattrs = copyattrs = ['emotionType', 'emotionValue', 'responseNum',
                                   'sound', 'flags', 'responseText', 'actorNotes',
                                   'editNotes', 'speakerAnim', 'listenerAnim']

    class InfoScript(BaseComponent):
        UINT8_ARRAY_GROUPEDMACRO(unused1, 0, 4)
        UINT32_GROUPEDMACRO(numRefs, 1)
        UINT32_GROUPEDMACRO(compiledSize, 2)
        UINT32_GROUPEDMACRO(lastIndex, 3)
        UINT16_TYPE_GROUPEDMACRO(scriptType, 4)
        UINT16_FLAG_GROUPEDMACRO(scriptFlags, 5)
        UINT8_ARRAY_GROUPEDMACRO(compiled_p, 6)
        ISTRING_GROUPEDMACRO(scriptText, 7)
        LIST_GROUPEDMACRO(vars, 8, Var)
        FORMID_OR_UINT32_ARRAY_GROUPEDMACRO(references, 9)

        BasicFlagMACRO(IsEnabled, scriptFlags, 0x0001)

        BasicTypeMACRO(IsObject, scriptType, 0x0000, IsQuest)
        BasicTypeMACRO(IsQuest, scriptType, 0x0001, IsObject)
        BasicTypeMACRO(IsEffect, scriptType, 0x0100, IsObject)
        copyattrs = ['numRefs', 'compiledSize', 'lastIndex',
                     'scriptType', 'scriptFlags', 'compiled_p',
                     'scriptText', 'vars_list', 'references']
        exportattrs = ['numRefs', 'compiledSize', 'lastIndex',
                       'scriptType', 'scriptFlags',
                       'scriptText', 'vars_list', 'references']#'compiled_p',

    UINT8_TYPE_MACRO(dialType, 7)
    UINT8_TYPE_MACRO(nextSpeaker, 8)
    UINT16_FLAG_MACRO(flags, 9)
    FORMID_MACRO(quest, 10)
    FORMID_MACRO(topic, 11)
    FORMID_MACRO(prevInfo, 12)
    FORMID_ARRAY_MACRO(addTopics, 13)

    LIST_MACRO(responses, 14, self.Response)
    LIST_MACRO(conditions, 15, FNVCondition)
    FORMID_ARRAY_MACRO(choices, 16)
    FORMID_ARRAY_MACRO(linksFrom, 17)
    FORMID_ARRAY_MACRO(unknown, 18)
    GroupedValuesMACRO(begin, 19, InfoScript)
    GroupedValuesMACRO(end, 29, InfoScript)
    FORMID_MACRO(unusedSound, 39)
    STRING_MACRO(prompt, 40)
    FORMID_MACRO(speaker, 41)
    FORMID_MACRO(actorValueOrPerk, 42)
    UINT32_TYPE_MACRO(challengeType, 43)

    BasicFlagMACRO(IsGoodbye, flags, 0x0001)
    BasicFlagMACRO(IsRandom, flags, 0x0002)
    BasicFlagMACRO(IsSayOnce, flags, 0x0004)
    BasicFlagMACRO(IsRunImmediately, flags, 0x0008)
    BasicFlagMACRO(IsInfoRefusal, flags, 0x0010)
    BasicFlagMACRO(IsRandomEnd, flags, 0x0020)
    BasicFlagMACRO(IsRunForRumors, flags, 0x0040)
    BasicFlagMACRO(IsSpeechChallenge, flags, 0x0080)
    BasicFlagMACRO(IsSayOnceADay, flags, 0x0100)
    BasicFlagMACRO(IsAlwaysDarken, flags, 0x0200)

    BasicTypeMACRO(IsTopic, dialType, 0, IsConversation)
    BasicTypeMACRO(IsConversation, dialType, 1, IsTopic)
    BasicTypeMACRO(IsCombat, dialType, 2, IsTopic)
    BasicTypeMACRO(IsPersuasion, dialType, 3, IsTopic)
    BasicTypeMACRO(IsDetection, dialType, 4, IsTopic)
    BasicTypeMACRO(IsService, dialType, 5, IsTopic)
    BasicTypeMACRO(IsMisc, dialType, 6, IsTopic)
    BasicTypeMACRO(IsRadio, dialType, 7, IsTopic)

    BasicTypeMACRO(IsTarget, nextSpeaker, 0, IsSelf)
    BasicTypeMACRO(IsSelf, nextSpeaker, 1, IsTarget)
    BasicTypeMACRO(IsEither, nextSpeaker, 2, IsTarget)

    BasicTypeMACRO(IsNone, challengeType, 0, IsVeryEasy)
    BasicTypeMACRO(IsVeryEasy, challengeType, 1, IsNone)
    BasicTypeMACRO(IsEasy, challengeType, 2, IsNone)
    BasicTypeMACRO(IsAverage, challengeType, 3, IsNone)
    BasicTypeMACRO(IsHard, challengeType, 4, IsNone)
    BasicTypeMACRO(IsVeryHard, challengeType, 5, IsNone)
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + ['dialType', 'nextSpeaker', 'flags',
                                                         'quest', 'topic', 'prevInfo',
                                                         'addTopics', 'responses_list',
                                                         'conditions_list', 'choices',
                                                         'linksFrom', 'unknown', 'begin_list',
                                                         'end_list', 'prompt', 'speaker',
                                                         'actorValueOrPerk', 'challengeType']

class FnvGMSTRecord(FnvBaseRecord):
    _Type = 'GMST'
    def get_value(self):
        rFormat = _CGetFieldAttribute(self._RecordID, 7, 0, 0, 0, 0, 0, 0, 2)
        if(rFormat == API_FIELDS.UNKNOWN):
            return None
        elif(rFormat == API_FIELDS.SINT32):
            _CGetField.restype = POINTER(c_long)
            retValue = _CGetField(self._RecordID, 7, 0, 0, 0, 0, 0, 0, 0)
            if(retValue): return retValue.contents.value
        elif(rFormat == API_FIELDS.FLOAT32):
            _CGetField.restype = POINTER(c_float)
            retValue = _CGetField(self._RecordID, 7, 0, 0, 0, 0, 0, 0, 0)
            if(retValue): return round(retValue.contents.value,6)
        elif(rFormat == API_FIELDS.STRING):
            _CGetField.restype = c_char_p
            return _CGetField(self._RecordID, 7, 0, 0, 0, 0, 0, 0, 0)
        return None
    def set_value(self, nValue):
        if nValue is None: _CDeleteField(self._RecordID, 7, 0, 0, 0, 0, 0, 0)
        else:
            rFormat = _CGetFieldAttribute(self._RecordID, 7, 0, 0, 0, 0, 0, 0, 2)
            if(rFormat == API_FIELDS.SINT32 and type(nValue) is int):
                _CSetField(self._RecordID, 7, 0, 0, 0, 0, 0, 0, byref(c_long(nValue)), 0)
            elif(rFormat == API_FIELDS.FLOAT32 == 10 and type(nValue) is float):
                _CSetField(self._RecordID, 7, 0, 0, 0, 0, 0, 0, byref(c_float(round(nValue,6))), 0)
            elif(rFormat == API_FIELDS.STRING and isinstance(nValue, basestring)):
                _CSetField(self._RecordID, 7, 0, 0, 0, 0, 0, 0, nValue, 0)
    value = property(get_value, set_value)
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + ['value']

class FnvTXSTRecord(FnvBaseRecord):
    _Type = 'TXST'
    SINT16_MACRO(boundX1, 7)
    SINT16_MACRO(boundY1, 8)
    SINT16_MACRO(boundZ1, 9)
    SINT16_MACRO(boundX2, 10)
    SINT16_MACRO(boundY2, 11)
    SINT16_MACRO(boundZ2, 12)
    ISTRING_MACRO(baseImageOrTransparencyPath, 13)
    ISTRING_MACRO(normalMapOrSpecularPath, 14)
    ISTRING_MACRO(envMapMaskOrUnkPath, 15)
    ISTRING_MACRO(glowMapOrUnusedPath, 16)
    ISTRING_MACRO(parallaxMapOrUnusedPath, 17)
    ISTRING_MACRO(envMapOrUnusedPath, 18)
    FLOAT32_MACRO(decalMinWidth, 19)
    FLOAT32_MACRO(decalMaxWidth, 20)
    FLOAT32_MACRO(decalMinHeight, 21)
    FLOAT32_MACRO(decalMaxHeight, 22)
    FLOAT32_MACRO(decalDepth, 23)
    FLOAT32_MACRO(decalShininess, 24)
    FLOAT32_MACRO(decalScale, 25)
    UINT8_MACRO(decalPasses, 26)
    UINT8_FLAG_MACRO(decalFlags, 27)
    UINT8_ARRAY_MACRO(decalUnused1, 28, 2)
    UINT8_MACRO(decalRed, 29)
    UINT8_MACRO(decalGreen, 30)
    UINT8_MACRO(decalBlue, 31)
    UINT8_ARRAY_MACRO(decalUnused2, 32, 1)
    UINT16_FLAG_MACRO(flags, 33)

    BasicFlagMACRO(IsNoSpecularMap, flags, 0x00000001)
    BasicInvertedFlagMACRO(IsSpecularMap, IsNoSpecularMap)

    BasicFlagMACRO(IsObjectParallax, decalFlags, 0x00000001)
    BasicFlagMACRO(IsObjectAlphaBlending, decalFlags, 0x00000002)
    BasicFlagMACRO(IsObjectAlphaTesting, decalFlags, 0x00000004)
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
    ISTRING_MACRO(iconPath, 7)
    ISTRING_MACRO(smallIconPath, 8)

    exportattrs = copyattrs = FnvBaseRecord.baseattrs + ['iconPath', 'smallIconPath']

class FnvGLOBRecord(FnvBaseRecord):
    _Type = 'GLOB'
    CHAR_MACRO(format, 7)
    FLOAT32_MACRO(value, 8)

    exportattrs = copyattrs = FnvBaseRecord.baseattrs + ['format', 'value']

class FnvCLASRecord(FnvBaseRecord):
    _Type = 'CLAS'
    STRING_MACRO(full, 7)
    STRING_MACRO(description, 8)
    ISTRING_MACRO(iconPath, 9)
    ISTRING_MACRO(smallIconPath, 10)
    SINT32_MACRO(tagSkills1, 11)
    SINT32_MACRO(tagSkills2, 12)
    SINT32_MACRO(tagSkills3, 13)
    SINT32_MACRO(tagSkills4, 14)
    UINT32_FLAG_MACRO(flags, 15)
    UINT32_FLAG_MACRO(services, 16)
    SINT8_MACRO(trainSkill, 17)
    UINT8_MACRO(trainLevel, 18)
    UINT8_ARRAY_MACRO(unused1, 19, 2)
    UINT8_MACRO(strength, 20)
    UINT8_MACRO(perception, 21)
    UINT8_MACRO(endurance, 22)
    UINT8_MACRO(charisma, 23)
    UINT8_MACRO(intelligence, 24)
    UINT8_MACRO(agility, 25)
    UINT8_MACRO(luck, 26)

    BasicFlagMACRO(IsPlayable, flags, 0x00000001)
    BasicFlagMACRO(IsGuard, flags, 0x00000002)

    BasicFlagMACRO(IsServicesWeapons, services, 0x00000001)
    BasicFlagMACRO(IsServicesArmor, services, 0x00000002)
    BasicFlagMACRO(IsServicesClothing, services, 0x00000004)
    BasicFlagMACRO(IsServicesBooks, services, 0x00000008)
    BasicFlagMACRO(IsServicesFood, services, 0x00000010)
    BasicFlagMACRO(IsServicesChems, services, 0x00000020)
    BasicFlagMACRO(IsServicesStimpacks, services, 0x00000040)
    BasicFlagMACRO(IsServicesLights, services, 0x00000080)
    BasicFlagMACRO(IsServicesMiscItems, services, 0x00000400)
    BasicFlagMACRO(IsServicesPotions, services, 0x00002000)
    BasicFlagMACRO(IsServicesTraining, services, 0x00004000)
    BasicFlagMACRO(IsServicesRecharge, services, 0x00010000)
    BasicFlagMACRO(IsServicesRepair, services, 0x00020000)
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + ['full', 'description', 'iconPath', 'smallIconPath',
                                                         'tagSkills1', 'tagSkills2', 'tagSkills3',
                                                         'tagSkills4', 'flags', 'services',
                                                         'trainSkill', 'trainLevel', 'strength',
                                                         'perception', 'endurance', 'charisma',
                                                         'intelligence', 'agility', 'luck']

class FnvFACTRecord(FnvBaseRecord):
    _Type = 'FACT'
    class Rank(ListComponent):
        SINT32_LISTMACRO(rank, 1)
        STRING_LISTMACRO(male, 2)
        STRING_LISTMACRO(female, 3)
        ISTRING_LISTMACRO(insigniaPath, 4)
        exportattrs = copyattrs = ['rank', 'male', 'female', 'insigniaPath']

    STRING_MACRO(full, 7)

    LIST_MACRO(relations, 8, FNVRelation)
    UINT16_FLAG_MACRO(flags, 9)
    UINT8_ARRAY_MACRO(unused1, 10, 2)
    FLOAT32_MACRO(crimeGoldMultiplier, 11)

    LIST_MACRO(ranks, 12, self.Rank)
    FORMID_MACRO(reputation, 13)

    BasicFlagMACRO(IsHiddenFromPC, flags, 0x0001)
    BasicFlagMACRO(IsEvil, flags, 0x0002)
    BasicFlagMACRO(IsSpecialCombat, flags, 0x0004)
    BasicFlagMACRO(IsTrackCrime, flags, 0x0100)
    BasicFlagMACRO(IsAllowSell, flags, 0x0200)
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + ['full', 'relations_list', 'flags',
                                        'crimeGoldMultiplier', 'ranks_list', 'reputation']

class FnvHDPTRecord(FnvBaseRecord):
    _Type = 'HDPT'
    STRING_MACRO(full, 7)
    ISTRING_MACRO(modPath, 8)
    FLOAT32_MACRO(modb, 9)
    UINT8_ARRAY_MACRO(modt_p, 10)

    LIST_MACRO(altTextures, 11, FNVAltTexture)
    UINT8_FLAG_MACRO(modelFlags, 12)
    UINT8_FLAG_MACRO(flags, 13)
    FORMID_ARRAY_MACRO(parts, 14)

    BasicFlagMACRO(IsPlayable, flags, 0x01)

    BasicFlagMACRO(IsHead, modelFlags, 0x01)
    BasicFlagMACRO(IsTorso, modelFlags, 0x02)
    BasicFlagMACRO(IsRightHand, modelFlags, 0x04)
    BasicFlagMACRO(IsLeftHand, modelFlags, 0x08)
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + ['full', 'modPath', 'modb',
                                                         'modt_p', 'altTextures_list',
                                                         'modelFlags', 'flags', 'parts']

class FnvHAIRRecord(FnvBaseRecord):
    _Type = 'HAIR'
    STRING_MACRO(full, 7)
    ISTRING_MACRO(modPath, 8)
    FLOAT32_MACRO(modb, 9)
    UINT8_ARRAY_MACRO(modt_p, 10)

    LIST_MACRO(altTextures, 11, FNVAltTexture)
    UINT8_FLAG_MACRO(modelFlags, 12)
    ISTRING_MACRO(iconPath, 13)
    UINT8_FLAG_MACRO(flags, 14)

    BasicFlagMACRO(IsPlayable, flags, 0x01)
    BasicFlagMACRO(IsNotMale, flags, 0x02)
    BasicInvertedFlagMACRO(IsMale, IsNotMale)
    BasicFlagMACRO(IsNotFemale, flags, 0x04)
    BasicInvertedFlagMACRO(IsFemale, IsNotFemale)
    BasicFlagMACRO(IsFixedColor, flags, 0x08)

    BasicFlagMACRO(IsHead, modelFlags, 0x01)
    BasicFlagMACRO(IsTorso, modelFlags, 0x02)
    BasicFlagMACRO(IsRightHand, modelFlags, 0x04)
    BasicFlagMACRO(IsLeftHand, modelFlags, 0x08)
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + ['full', 'modPath', 'modb',
                                                         'modt_p', 'altTextures_list',
                                                         'modelFlags', 'iconPath', 'flags']

class FnvEYESRecord(FnvBaseRecord):
    _Type = 'EYES'
    STRING_MACRO(full, 7)
    ISTRING_MACRO(iconPath, 8)
    UINT8_FLAG_MACRO(flags, 9)

    BasicFlagMACRO(IsPlayable, flags, 0x01)
    BasicFlagMACRO(IsNotMale, flags, 0x02)
    BasicInvertedFlagMACRO(IsMale, IsNotMale)
    BasicFlagMACRO(IsNotFemale, flags, 0x04)
    BasicInvertedFlagMACRO(IsFemale, IsNotFemale)
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + ['full', 'iconPath', 'flags']

class FnvRACERecord(FnvBaseRecord):
    _Type = 'RACE'
    class RaceModel(BaseComponent):
        ISTRING_GROUPEDMACRO(modPath, 0)
        FLOAT32_GROUPEDMACRO(modb, 1)
        UINT8_ARRAY_GROUPEDMACRO(modt_p, 2)

        LIST_GROUPEDMACRO(altTextures, 3, FNVAltTexture)
        UINT8_FLAG_GROUPEDMACRO(flags, 4)
        ISTRING_GROUPEDMACRO(iconPath, 5)
        ISTRING_GROUPEDMACRO(smallIconPath, 6)

        BasicFlagMACRO(IsHead, flags, 0x01)
        BasicFlagMACRO(IsTorso, flags, 0x02)
        BasicFlagMACRO(IsRightHand, flags, 0x04)
        BasicFlagMACRO(IsLeftHand, flags, 0x08)
        copyattrs = ['modPath', 'modb', 'modt_p', 'altTextures_list',
                     'flags', 'iconPath', 'smallIconPath']
        exportattrs = ['modPath', 'modb', 'altTextures_list',
                     'flags', 'iconPath', 'smallIconPath']#, 'modt_p']

    STRING_MACRO(full, 7)
    STRING_MACRO(description, 8)

    LIST_MACRO(relations, 9, FNVRelation)
    SINT8_MACRO(skill1, 10)
    SINT8_MACRO(skill1Boost, 11)
    SINT8_MACRO(skill2, 12)
    SINT8_MACRO(skill2Boost, 13)
    SINT8_MACRO(skill3, 14)
    SINT8_MACRO(skill3Boost, 15)
    SINT8_MACRO(skill4, 16)
    SINT8_MACRO(skill4Boost, 17)
    SINT8_MACRO(skill5, 18)
    SINT8_MACRO(skill5Boost, 19)
    SINT8_MACRO(skill6, 20)
    SINT8_MACRO(skill6Boost, 21)
    SINT8_MACRO(skill7, 22)
    SINT8_MACRO(skill7Boost, 23)
    UINT8_ARRAY_MACRO(unused1, 24, 2)
    FLOAT32_MACRO(maleHeight, 25)
    FLOAT32_MACRO(femaleHeight, 26)
    FLOAT32_MACRO(maleWeight, 27)
    FLOAT32_MACRO(femaleWeight, 28)
    UINT32_FLAG_MACRO(flags, 29)
    FORMID_MACRO(older, 30)
    FORMID_MACRO(younger, 31)
    FORMID_MACRO(maleVoice, 32)
    FORMID_MACRO(femaleVoice, 33)
    FORMID_MACRO(defaultHairMale, 34)
    FORMID_MACRO(defaultHairFemale, 35)
    UINT8_MACRO(defaultHairMaleColor, 36)
    UINT8_MACRO(defaultHairFemaleColor, 37)
    FLOAT32_MACRO(mainClamp, 38)
    FLOAT32_MACRO(faceClamp, 39)
    UINT8_ARRAY_MACRO(attr_p, 40)
    GroupedValuesMACRO(maleHead, 41, RaceModel)
    GroupedValuesMACRO(maleEars, 48, RaceModel)
    GroupedValuesMACRO(maleMouth, 55, RaceModel)
    GroupedValuesMACRO(maleTeethLower, 62, RaceModel)
    GroupedValuesMACRO(maleTeethUpper, 69, RaceModel)
    GroupedValuesMACRO(maleTongue, 76, RaceModel)
    GroupedValuesMACRO(maleLeftEye, 83, RaceModel)
    GroupedValuesMACRO(maleRightEye, 90, RaceModel)
    GroupedValuesMACRO(femaleHead, 97, RaceModel)
    GroupedValuesMACRO(femaleEars, 104, RaceModel)
    GroupedValuesMACRO(femaleMouth, 111, RaceModel)
    GroupedValuesMACRO(femaleTeethLower, 118, RaceModel)
    GroupedValuesMACRO(femaleTeethUpper, 125, RaceModel)
    GroupedValuesMACRO(femaleTongue, 132, RaceModel)
    GroupedValuesMACRO(femaleLeftEye, 139, RaceModel)
    GroupedValuesMACRO(femaleRightEye, 146, RaceModel)
    GroupedValuesMACRO(maleUpperBody, 153, RaceModel)
    GroupedValuesMACRO(maleLeftHand, 160, RaceModel)
    GroupedValuesMACRO(maleRightHand, 167, RaceModel)
    GroupedValuesMACRO(maleUpperBodyTexture, 174, RaceModel)
    GroupedValuesMACRO(femaleUpperBody, 181, RaceModel)
    GroupedValuesMACRO(femaleLeftHand, 188, RaceModel)
    GroupedValuesMACRO(femaleRightHand, 195, RaceModel)
    GroupedValuesMACRO(femaleUpperBodyTexture, 202, RaceModel)
    FORMID_ARRAY_MACRO(hairs, 209)
    FORMID_ARRAY_MACRO(eyes, 210)
    UINT8_ARRAY_MACRO(maleFggs_p, 211, 200)
    UINT8_ARRAY_MACRO(maleFgga_p, 212, 120)
    UINT8_ARRAY_MACRO(maleFgts_p, 213, 200)
    UINT8_ARRAY_MACRO(maleSnam_p, 214, 2)
    UINT8_ARRAY_MACRO(femaleFggs_p, 215, 200)
    UINT8_ARRAY_MACRO(femaleFgga_p, 216, 120)
    UINT8_ARRAY_MACRO(femaleFgts_p, 217, 200)
    UINT8_ARRAY_MACRO(femaleSnam_p, 218, 2)

    BasicFlagMACRO(IsPlayable, flags, 0x00000001)
    BasicFlagMACRO(IsChild, flags, 0x00000004)
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
    SINT16_MACRO(boundX1, 7)
    SINT16_MACRO(boundY1, 8)
    SINT16_MACRO(boundZ1, 9)
    SINT16_MACRO(boundX2, 10)
    SINT16_MACRO(boundY2, 11)
    SINT16_MACRO(boundZ2, 12)
    ISTRING_MACRO(soundPath, 13)
    UINT8_MACRO(chance, 14)
    UINT8_MACRO(minDistance, 15)
    UINT8_MACRO(maxDistance, 16)
    SINT8_MACRO(freqAdjustment, 17)
    UINT8_ARRAY_MACRO(unused1, 18, 1)
    UINT32_FLAG_MACRO(flags, 19)
    SINT16_MACRO(staticAtten, 20)
    UINT8_MACRO(stopTime, 21)
    UINT8_MACRO(startTime, 22)
    SINT16_ARRAY_MACRO(attenCurve, 23, 5)
    SINT16_MACRO(reverb, 24)
    SINT32_MACRO(priority, 25)
    SINT32_MACRO(x, 26)
    SINT32_MACRO(y, 27)

    BasicFlagMACRO(IsRandomFrequencyShift, flags, 0x00000001)
    BasicFlagMACRO(IsPlayAtRandom, flags, 0x00000002)
    BasicFlagMACRO(IsEnvironmentIgnored, flags, 0x00000004)
    BasicFlagMACRO(IsRandomLocation, flags, 0x00000008)
    BasicFlagMACRO(IsLoop, flags, 0x00000010)
    BasicFlagMACRO(IsMenuSound, flags, 0x00000020)
    BasicFlagMACRO(Is2D, flags, 0x00000040)
    BasicFlagMACRO(Is360LFE, flags, 0x00000080)
    BasicFlagMACRO(IsDialogueSound, flags, 0x00000100)
    BasicFlagMACRO(IsEnvelopeFast, flags, 0x00000200)
    BasicFlagMACRO(IsEnvelopeSlow, flags, 0x00000400)
    BasicFlagMACRO(Is2DRadius, flags, 0x00000800)
    BasicFlagMACRO(IsMuteWhenSubmerged, flags, 0x00001000)
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
    SINT16_MACRO(boundX1, 7)
    SINT16_MACRO(boundY1, 8)
    SINT16_MACRO(boundZ1, 9)
    SINT16_MACRO(boundX2, 10)
    SINT16_MACRO(boundY2, 11)
    SINT16_MACRO(boundZ2, 12)
    FORMID_MACRO(dawnOrDefaultLoop, 13)
    FORMID_MACRO(afternoon, 14)
    FORMID_MACRO(dusk, 15)
    FORMID_MACRO(night, 16)
    FORMID_MACRO(walla, 17)
    UINT32_MACRO(wallaTriggerCount, 18)
    FORMID_MACRO(regionSound, 19)
    UINT32_TYPE_MACRO(environmentType, 20)
    UINT32_TYPE_MACRO(spaceType, 21)

    BasicTypeMACRO(IsEnvironmentNone, environmentType, 0, IsEnvironmentDefault)
    BasicTypeMACRO(IsEnvironmentDefault, environmentType, 1, IsEnvironmentNone)
    BasicTypeMACRO(IsEnvironmentGeneric, environmentType, 2, IsEnvironmentNone)
    BasicTypeMACRO(IsEnvironmentPaddedCell, environmentType, 3, IsEnvironmentNone)
    BasicTypeMACRO(IsEnvironmentRoom, environmentType, 4, IsEnvironmentNone)
    BasicTypeMACRO(IsEnvironmentBathroom, environmentType, 5, IsEnvironmentNone)
    BasicTypeMACRO(IsEnvironmentLivingroom, environmentType, 6, IsEnvironmentNone)
    BasicTypeMACRO(IsEnvironmentStoneRoom, environmentType, 7, IsEnvironmentNone)
    BasicTypeMACRO(IsEnvironmentAuditorium, environmentType, 8, IsEnvironmentNone)
    BasicTypeMACRO(IsEnvironmentConcerthall, environmentType, 9, IsEnvironmentNone)
    BasicTypeMACRO(IsEnvironmentCave, environmentType, 10, IsEnvironmentNone)
    BasicTypeMACRO(IsEnvironmentArena, environmentType, 11, IsEnvironmentNone)
    BasicTypeMACRO(IsEnvironmentHangar, environmentType, 12, IsEnvironmentNone)
    BasicTypeMACRO(IsEnvironmentCarpetedHallway, environmentType, 13, IsEnvironmentNone)
    BasicTypeMACRO(IsEnvironmentHallway, environmentType, 14, IsEnvironmentNone)
    BasicTypeMACRO(IsEnvironmentStoneCorridor, environmentType, 15, IsEnvironmentNone)
    BasicTypeMACRO(IsEnvironmentAlley, environmentType, 16, IsEnvironmentNone)
    BasicTypeMACRO(IsEnvironmentForest, environmentType, 17, IsEnvironmentNone)
    BasicTypeMACRO(IsEnvironmentCity, environmentType, 18, IsEnvironmentNone)
    BasicTypeMACRO(IsEnvironmentMountains, environmentType, 19, IsEnvironmentNone)
    BasicTypeMACRO(IsEnvironmentQuarry, environmentType, 20, IsEnvironmentNone)
    BasicTypeMACRO(IsEnvironmentPlain, environmentType, 21, IsEnvironmentNone)
    BasicTypeMACRO(IsEnvironmentParkinglot, environmentType, 22, IsEnvironmentNone)
    BasicTypeMACRO(IsEnvironmentSewerpipe, environmentType, 23, IsEnvironmentNone)
    BasicTypeMACRO(IsEnvironmentUnderwater, environmentType, 24, IsEnvironmentNone)
    BasicTypeMACRO(IsEnvironmentSmallRoom, environmentType, 25, IsEnvironmentNone)
    BasicTypeMACRO(IsEnvironmentMediumRoom, environmentType, 26, IsEnvironmentNone)
    BasicTypeMACRO(IsEnvironmentLargeRoom, environmentType, 27, IsEnvironmentNone)
    BasicTypeMACRO(IsEnvironmentMediumHall, environmentType, 28, IsEnvironmentNone)
    BasicTypeMACRO(IsEnvironmentLargeHall, environmentType, 29, IsEnvironmentNone)
    BasicTypeMACRO(IsEnvironmentPlate, environmentType, 30, IsEnvironmentNone)

    BasicTypeMACRO(IsSpaceExterior, spaceType, 0, IsSpaceInterior)
    BasicTypeMACRO(IsSpaceInterior, spaceType, 1, IsSpaceExterior)
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                                         'boundX2', 'boundY2', 'boundZ2',
                                                         'dawnOrDefaultLoop', 'afternoon',
                                                         'dusk', 'night', 'walla',
                                                         'wallaTriggerCount', 'regionSound',
                                                         'environmentType', 'spaceType']

class FnvMGEFRecord(FnvBaseRecord):
    _Type = 'MGEF'
    STRING_MACRO(full, 7)
    STRING_MACRO(description, 8)
    ISTRING_MACRO(iconPath, 9)
    ISTRING_MACRO(smallIconPath, 10)
    ISTRING_MACRO(modPath, 11)
    FLOAT32_MACRO(modb, 12)
    UINT8_ARRAY_MACRO(modt_p, 13)

    LIST_MACRO(altTextures, 14, FNVAltTexture)
    UINT8_FLAG_MACRO(modelFlags, 15)
    UINT32_FLAG_MACRO(flags, 16)
    FLOAT32_MACRO(baseCostUnused, 17)
    FORMID_MACRO(associated, 18)
    SINT32_MACRO(schoolUnused, 19)
    SINT32_TYPE_MACRO(resistType, 20)
    UINT16_MACRO(numCounters, 21)
    UINT8_ARRAY_MACRO(unused1, 22, 2)
    FORMID_MACRO(light, 23)
    FLOAT32_MACRO(projectileSpeed, 24)
    FORMID_MACRO(effectShader, 25)
    FORMID_MACRO(displayShader, 26)
    FORMID_MACRO(effectSound, 27)
    FORMID_MACRO(boltSound, 28)
    FORMID_MACRO(hitSound, 29)
    FORMID_MACRO(areaSound, 30)
    FLOAT32_MACRO(cefEnchantmentUnused, 31)
    FLOAT32_MACRO(cefBarterUnused, 32)
    UINT32_TYPE_MACRO(archType, 33)
    SINT32_TYPE_MACRO(actorValue, 34)

    BasicFlagMACRO(IsHostile, flags, 0x00000001)
    BasicFlagMACRO(IsRecover, flags, 0x00000002)
    BasicFlagMACRO(IsDetrimental, flags, 0x00000004)
    BasicFlagMACRO(IsSelf, flags, 0x00000010)
    BasicFlagMACRO(IsTouch, flags, 0x00000020)
    BasicFlagMACRO(IsTarget, flags, 0x00000040)
    BasicFlagMACRO(IsNoDuration, flags, 0x00000080)
    BasicFlagMACRO(IsNoMagnitude, flags, 0x00000100)
    BasicFlagMACRO(IsNoArea, flags, 0x00000200)
    BasicFlagMACRO(IsFXPersist, flags, 0x00000400)
    BasicFlagMACRO(IsGoryVisuals, flags, 0x00001000)
    BasicFlagMACRO(IsDisplayNameOnly, flags, 0x00002000)
    BasicFlagMACRO(IsRadioBroadcast, flags, 0x00008000)
    BasicFlagMACRO(IsUseSkill, flags, 0x00080000)
    BasicFlagMACRO(IsUseAttr, flags, 0x00100000)
    BasicFlagMACRO(IsPainless, flags, 0x01000000)
    BasicFlagMACRO(IsSprayType, flags, 0x02000000)
    BasicFlagMACRO(IsBoltType, flags, 0x04000000)
    BasicFlagMACRO(IsFogType, flags, 0x06000000)
    BasicFlagMACRO(IsNoHitEffect, flags, 0x08000000)
    BasicFlagMACRO(IsPersistOnDeath, flags, 0x10000000)
    BasicFlagMACRO(IsUnknown1, flags, 0x20000000)

    BasicFlagMACRO(IsHead, modelFlags, 0x01)
    BasicFlagMACRO(IsTorso, modelFlags, 0x02)
    BasicFlagMACRO(IsRightHand, modelFlags, 0x04)
    BasicFlagMACRO(IsLeftHand, modelFlags, 0x08)

    BasicTypeMACRO(IsValueModifier, archType, 0, IsScript)
    BasicTypeMACRO(IsScript, archType, 1, IsValueModifier)
    BasicTypeMACRO(IsDispel, archType, 2, IsValueModifier)
    BasicTypeMACRO(IsCureDisease, archType, 3, IsValueModifier)
    BasicTypeMACRO(IsInvisibility, archType, 11, IsValueModifier)
    BasicTypeMACRO(IsChameleon, archType, 12, IsValueModifier)
    BasicTypeMACRO(IsLight, archType, 13, IsValueModifier)
    BasicTypeMACRO(IsLock, archType, 16, IsValueModifier)
    BasicTypeMACRO(IsOpen, archType, 17, IsValueModifier)
    BasicTypeMACRO(IsBoundItem, archType, 18, IsValueModifier)
    BasicTypeMACRO(IsSummonCreature, archType, 19, IsValueModifier)
    BasicTypeMACRO(IsParalysis, archType, 24, IsValueModifier)
    BasicTypeMACRO(IsCureParalysis, archType, 30, IsValueModifier)
    BasicTypeMACRO(IsCureAddiction, archType, 31, IsValueModifier)
    BasicTypeMACRO(IsCurePoison, archType, 32, IsValueModifier)
    BasicTypeMACRO(IsConcussion, archType, 33, IsValueModifier)
    BasicTypeMACRO(IsValueAndParts, archType, 34, IsValueModifier)
    BasicTypeMACRO(IsLimbCondition, archType, 35, IsValueModifier)
    BasicTypeMACRO(IsTurbo, archType, 36, IsValueModifier)
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
    def mergeFilter(self, modSet):
        """Filter references that don't come from the specified modSet.
           Since we can't actually do this for SCPT records, return False if
           any references are to mods not in modSet."""
        for ref in self.references:
            if not isinstance(ref,FormID):
                continue
            if ref[0] not in modSet: return False
        return True

    UINT8_ARRAY_MACRO(unused1, 7, 4)
    UINT32_MACRO(numRefs, 8)
    UINT32_MACRO(compiledSize, 9)
    UINT32_MACRO(lastIndex, 10)
    UINT16_TYPE_MACRO(scriptType, 11)
    UINT16_FLAG_MACRO(scriptFlags, 12)
    UINT8_ARRAY_MACRO(compiled_p, 13)
    ISTRING_MACRO(scriptText, 14)

    LIST_MACRO(vars, 15, Var)
    FORMID_OR_UINT32_ARRAY_MACRO(references, 16)

    BasicFlagMACRO(IsEnabled, scriptFlags, 0x0001)

    BasicTypeMACRO(IsObject, scriptType, 0x0000, IsQuest)
    BasicTypeMACRO(IsQuest, scriptType, 0x0001, IsObject)
    BasicTypeMACRO(IsEffect, scriptType, 0x0100, IsObject)
    copyattrs = FnvBaseRecord.baseattrs + ['unused1', 'numRefs', 'compiledSize',
                                           'lastIndex', 'scriptType', 'scriptFlags',
                                           'compiled_p', 'scriptText',
                                           'vars_list', 'references']
    exportattrs = FnvBaseRecord.baseattrs + ['numRefs', 'compiledSize',
                                             'lastIndex', 'scriptType', 'scriptFlags',
                                             'scriptText',
                                             'vars_list', 'references'] #'unused1', 'compiled_p',

class FnvLTEXRecord(FnvBaseRecord):
    _Type = 'LTEX'
    ISTRING_MACRO(iconPath, 7)
    ISTRING_MACRO(smallIconPath, 8)
    FORMID_MACRO(texture, 9)
    UINT8_TYPE_MACRO(types, 10)
    UINT8_MACRO(friction, 11)
    UINT8_MACRO(restitution, 12)
    UINT8_MACRO(specularExponent, 13)
    FORMID_ARRAY_MACRO(grasses, 14)

    BasicTypeMACRO(IsStone, types, 0, IsCloth)
    BasicTypeMACRO(IsCloth, types, 1, IsStone)
    BasicTypeMACRO(IsDirt, types, 2, IsStone)
    BasicTypeMACRO(IsGlass, types, 3, IsStone)
    BasicTypeMACRO(IsGrass, types, 4, IsStone)
    BasicTypeMACRO(IsMetal, types, 5, IsStone)
    BasicTypeMACRO(IsOrganic, types, 6, IsStone)
    BasicTypeMACRO(IsSkin, types, 7, IsStone)
    BasicTypeMACRO(IsWater, types, 8, IsStone)
    BasicTypeMACRO(IsWood, types, 9, IsStone)
    BasicTypeMACRO(IsHeavyStone, types, 10, IsStone)
    BasicTypeMACRO(IsHeavyMetal, types, 11, IsStone)
    BasicTypeMACRO(IsHeavyWood, types, 12, IsStone)
    BasicTypeMACRO(IsChain, types, 13, IsStone)
    BasicTypeMACRO(IsSnow, types, 14, IsStone)
    BasicTypeMACRO(IsElevator, types, 15, IsStone)
    BasicTypeMACRO(IsHollowMetal, types, 16, IsStone)
    BasicTypeMACRO(IsSheetMetal, types, 17, IsStone)
    BasicTypeMACRO(IsSand, types, 18, IsStone)
    BasicTypeMACRO(IsBrokenConcrete, types, 19, IsStone)
    BasicTypeMACRO(IsVehicleBody, types, 20, IsStone)
    BasicTypeMACRO(IsVehiclePartSolid, types, 21, IsStone)
    BasicTypeMACRO(IsVehiclePartHollow, types, 22, IsStone)
    BasicTypeMACRO(IsBarrel, types, 23, IsStone)
    BasicTypeMACRO(IsBottle, types, 24, IsStone)
    BasicTypeMACRO(IsSodaCan, types, 25, IsStone)
    BasicTypeMACRO(IsPistol, types, 26, IsStone)
    BasicTypeMACRO(IsRifle, types, 27, IsStone)
    BasicTypeMACRO(IsShoppingCart, types, 28, IsStone)
    BasicTypeMACRO(IsLunchBox, types, 29, IsStone)
    BasicTypeMACRO(IsBabyRattle, types, 30, IsStone)
    BasicTypeMACRO(IsRubberBall, types, 31, IsStone)
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + ['iconPath', 'smallIconPath', 'texture',
                                                         'types', 'friction', 'restitution',
                                                         'specularExponent', 'grasses']

class FnvENCHRecord(FnvBaseRecord):
    _Type = 'ENCH'
    STRING_MACRO(full, 7)
    UINT32_TYPE_MACRO(itemType, 8)
    UINT32_MACRO(chargeAmountUnused, 9)
    UINT32_MACRO(enchantCostUnused, 10)
    UINT8_FLAG_MACRO(flags, 11)
    UINT8_ARRAY_MACRO(unused1, 12, 3)

    LIST_MACRO(effects, 13, FNVEffect)

    BasicFlagMACRO(IsNoAutoCalc, flags, 0x01)
    BasicInvertedFlagMACRO(IsAutoCalc, IsNoAutoCalc)
    BasicFlagMACRO(IsHideEffect, flags, 0x04)
    BasicTypeMACRO(IsWeapon, itemType, 2, IsApparel)
    BasicTypeMACRO(IsApparel, itemType, 3, IsWeapon)
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + ['full', 'itemType', 'chargeAmountUnused',
                                                         'enchantCostUnused', 'flags', 'effects_list']

class FnvSPELRecord(FnvBaseRecord):
    _Type = 'SPEL'
    STRING_MACRO(full, 7)
    UINT32_TYPE_MACRO(spellType, 8)
    UINT32_MACRO(costUnused, 9)
    UINT32_TYPE_MACRO(levelTypeUnused, 10)
    UINT8_FLAG_MACRO(flags, 11)
    UINT8_ARRAY_MACRO(unused1, 12, 3)

    LIST_MACRO(effects, 13, FNVEffect)

    BasicFlagMACRO(IsManualCost, flags, 0x01)
    BasicFlagMACRO(IsStartSpell, flags, 0x04)
    BasicFlagMACRO(IsSilenceImmune, flags, 0x0A)
    BasicFlagMACRO(IsAreaEffectIgnoresLOS, flags, 0x10)
    BasicAliasMACRO(IsAEIgnoresLOS, IsAreaEffectIgnoresLOS)
    BasicFlagMACRO(IsScriptAlwaysApplies, flags, 0x20)
    BasicFlagMACRO(IsDisallowAbsorbReflect, flags, 0x40)
    BasicAliasMACRO(IsDisallowAbsorb, IsDisallowAbsorbReflect)
    BasicAliasMACRO(IsDisallowReflect, IsDisallowAbsorbReflect)
    BasicFlagMACRO(IsTouchExplodesWOTarget, flags, 0x80)
    BasicAliasMACRO(IsTouchExplodes, IsTouchExplodesWOTarget)

    BasicTypeMACRO(IsActorEffect, spellType, 0, IsDisease)
    BasicTypeMACRO(IsDisease, spellType, 1, IsActorEffect)
    BasicTypeMACRO(IsPower, spellType, 2, IsActorEffect)
    BasicTypeMACRO(IsLesserPower, spellType, 3, IsActorEffect)
    BasicTypeMACRO(IsAbility, spellType, 4, IsActorEffect)
    BasicTypeMACRO(IsPoison, spellType, 5, IsActorEffect)
    BasicTypeMACRO(IsAddiction, spellType, 10, IsActorEffect)
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + ['full', 'spellType', 'costUnused',
                                                         'levelTypeUnused', 'flags', 'effects_list']

class FnvACTIRecord(FnvBaseRecord):
    _Type = 'ACTI'
    SINT16_MACRO(boundX1, 7)
    SINT16_MACRO(boundY1, 8)
    SINT16_MACRO(boundZ1, 9)
    SINT16_MACRO(boundX2, 10)
    SINT16_MACRO(boundY2, 11)
    SINT16_MACRO(boundZ2, 12)
    STRING_MACRO(full, 13)
    ISTRING_MACRO(modPath, 14)
    FLOAT32_MACRO(modb, 15)
    UINT8_ARRAY_MACRO(modt_p, 16)

    LIST_MACRO(altTextures, 17, FNVAltTexture)
    UINT8_FLAG_MACRO(modelFlags, 18)
    FORMID_MACRO(script, 19)
    GroupedValuesMACRO(destructable, 20, FNVDestructable)
    FORMID_MACRO(loopSound, 25)
    FORMID_MACRO(actSound, 26)
    FORMID_MACRO(radioTemplate, 27)
    FORMID_MACRO(radioStation, 28)
    FORMID_MACRO(water, 29)
    STRING_MACRO(prompt, 30)

    BasicFlagMACRO(IsHead, modelFlags, 0x01)
    BasicFlagMACRO(IsTorso, modelFlags, 0x02)
    BasicFlagMACRO(IsRightHand, modelFlags, 0x04)
    BasicFlagMACRO(IsLeftHand, modelFlags, 0x08)
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
    SINT16_MACRO(boundX1, 7)
    SINT16_MACRO(boundY1, 8)
    SINT16_MACRO(boundZ1, 9)
    SINT16_MACRO(boundX2, 10)
    SINT16_MACRO(boundY2, 11)
    SINT16_MACRO(boundZ2, 12)
    STRING_MACRO(full, 13)
    ISTRING_MACRO(modPath, 14)
    FLOAT32_MACRO(modb, 15)
    UINT8_ARRAY_MACRO(modt_p, 16)

    LIST_MACRO(altTextures, 17, FNVAltTexture)
    UINT8_FLAG_MACRO(modelFlags, 18)
    FORMID_MACRO(script, 19)
    GroupedValuesMACRO(destructable, 20, FNVDestructable)
    FORMID_MACRO(loopSound, 25)
    FORMID_MACRO(voice, 26)
    FORMID_MACRO(radioTemplate, 27)

    BasicFlagMACRO(IsHead, modelFlags, 0x01)
    BasicFlagMACRO(IsTorso, modelFlags, 0x02)
    BasicFlagMACRO(IsRightHand, modelFlags, 0x04)
    BasicFlagMACRO(IsLeftHand, modelFlags, 0x08)
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                                         'boundX2', 'boundY2', 'boundZ2',
                                                         'full', 'modPath', 'modb', 'modt_p',
                                                         'altTextures_list', 'modelFlags',
                                                         'script', 'destructable_list',
                                                         'loopSound', 'voice', 'radioTemplate']

class FnvTERMRecord(FnvBaseRecord):
    _Type = 'TERM'
    class Menu(ListComponent):
        STRING_LISTMACRO(text, 1)
        STRING_LISTMACRO(resultText, 2)
        UINT8_FLAG_LISTMACRO(flags, 3)
        FORMID_LISTMACRO(displayNote, 4)
        FORMID_LISTMACRO(subMenu, 5)
        UINT8_ARRAY_LISTMACRO(unused1, 6, 4)
        UINT32_LISTMACRO(numRefs, 7)
        UINT32_LISTMACRO(compiledSize, 8)
        UINT32_LISTMACRO(lastIndex, 9)
        UINT16_TYPE_LISTMACRO(scriptType, 10)
        UINT16_FLAG_LISTMACRO(scriptFlags, 11)
        UINT8_ARRAY_LISTMACRO(compiled_p, 12)
        ISTRING_LISTMACRO(scriptText, 13)

        LIST_LISTMACRO(vars, 14, VarX2)

        FORMID_OR_UINT32_ARRAY_LISTMACRO(references, 15)
        LIST_LISTMACRO(conditions, 16, FNVConditionX2)

        BasicFlagMACRO(IsAddNote, flags, 0x01)
        BasicFlagMACRO(IsForceRedraw, flags, 0x02)

        BasicFlagMACRO(IsEnabled, scriptFlags, 0x0001)

        BasicTypeMACRO(IsObject, scriptType, 0x0000, IsQuest)
        BasicTypeMACRO(IsQuest, scriptType, 0x0001, IsObject)
        BasicTypeMACRO(IsEffect, scriptType, 0x0100, IsObject)
        copyattrs = ['text', 'resultText', 'flags',
                     'displayNote', 'subMenu', 'numRefs',
                     'compiledSize', 'lastIndex',
                     'scriptType', 'scriptFlags', 'compiled_p',
                     'scriptText', 'vars_list',
                     'references', 'conditions_list',]
        exportattrs = ['text', 'resultText', 'flags',
                       'displayNote', 'subMenu', 'numRefs',
                       'compiledSize', 'lastIndex',
                       'scriptType', 'scriptFlags',
                       'scriptText', 'vars_list',
                       'references', 'conditions_list',] # 'compiled_p',

    SINT16_MACRO(boundX1, 7)
    SINT16_MACRO(boundY1, 8)
    SINT16_MACRO(boundZ1, 9)
    SINT16_MACRO(boundX2, 10)
    SINT16_MACRO(boundY2, 11)
    SINT16_MACRO(boundZ2, 12)
    STRING_MACRO(full, 13)
    ISTRING_MACRO(modPath, 14)
    FLOAT32_MACRO(modb, 15)
    UINT8_ARRAY_MACRO(modt_p, 16)

    LIST_MACRO(altTextures, 17, FNVAltTexture)
    UINT8_FLAG_MACRO(modelFlags, 18)
    FORMID_MACRO(script, 19)
    GroupedValuesMACRO(destructable, 20, FNVDestructable)
    STRING_MACRO(description, 25)
    FORMID_MACRO(loopSound, 26)
    FORMID_MACRO(passNote, 27)
    UINT8_TYPE_MACRO(difficultyType, 28)
    UINT8_FLAG_MACRO(flags, 29)
    UINT8_TYPE_MACRO(serverType, 30)
    UINT8_ARRAY_MACRO(unused1, 31, 1)

    LIST_MACRO(menus, 32, self.Menu)

    BasicTypeMACRO(IsVeryEasy, difficultyType, 0, IsEasy)
    BasicTypeMACRO(IsEasy, difficultyType, 1, IsVeryEasy)
    BasicTypeMACRO(IsAverage, difficultyType, 2, IsVeryEasy)
    BasicTypeMACRO(IsHard, difficultyType, 3, IsVeryEasy)
    BasicTypeMACRO(IsVeryHard, difficultyType, 4, IsVeryEasy)
    BasicTypeMACRO(IsRequiresKey, difficultyType, 5, IsVeryEasy)

    BasicFlagMACRO(IsLeveled, flags, 0x01)
    BasicFlagMACRO(IsUnlocked, flags, 0x02)
    BasicFlagMACRO(IsAlternateColors, flags, 0x04)
    BasicFlagMACRO(IsHideWelcomeTextWhenDisplayingImage, flags, 0x08)

    BasicFlagMACRO(IsHead, modelFlags, 0x01)
    BasicFlagMACRO(IsTorso, modelFlags, 0x02)
    BasicFlagMACRO(IsRightHand, modelFlags, 0x04)
    BasicFlagMACRO(IsLeftHand, modelFlags, 0x08)

    BasicTypeMACRO(IsServer1, serverType, 0, IsServer2)
    BasicTypeMACRO(IsServer2, serverType, 1, IsServer1)
    BasicTypeMACRO(IsServer3, serverType, 2, IsServer1)
    BasicTypeMACRO(IsServer4, serverType, 3, IsServer1)
    BasicTypeMACRO(IsServer5, serverType, 4, IsServer1)
    BasicTypeMACRO(IsServer6, serverType, 5, IsServer1)
    BasicTypeMACRO(IsServer7, serverType, 6, IsServer1)
    BasicTypeMACRO(IsServer8, serverType, 7, IsServer1)
    BasicTypeMACRO(IsServer9, serverType, 8, IsServer1)
    BasicTypeMACRO(IsServer10, serverType, 9, IsServer1)
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
        ISTRING_GROUPEDMACRO(modPath, 0)
        UINT8_ARRAY_GROUPEDMACRO(modt_p, 1)

        LIST_GROUPEDMACRO(altTextures, 2, FNVAltTexture)
        UINT8_FLAG_GROUPEDMACRO(flags, 3)

        BasicFlagMACRO(IsHead, flags, 0x01)
        BasicFlagMACRO(IsTorso, flags, 0x02)
        BasicFlagMACRO(IsRightHand, flags, 0x04)
        BasicFlagMACRO(IsLeftHand, flags, 0x08)
        copyattrs = ['modPath', 'modt_p', 'altTextures_list',
                     'flags']
        exportattrs = ['modPath', 'altTextures_list', 'flags']#, 'modt_p']

    class Sound(ListComponent):
        FORMID_LISTMACRO(sound, 1)
        UINT8_LISTMACRO(chance, 2)
        UINT8_ARRAY_LISTMACRO(unused1, 3, 3)
        UINT32_TYPE_LISTMACRO(type, 4)
        BasicTypeMACRO(IsWalk, type, 17, IsSneak)
        BasicTypeMACRO(IsSneak, type, 18, IsWalk)
        BasicTypeMACRO(IsRun, type, 19, IsWalk)
        BasicTypeMACRO(IsSneakArmor, type, 20, IsWalk)
        BasicTypeMACRO(IsRunArmor, type, 21, IsWalk)
        BasicTypeMACRO(IsWalkArmor, type, 22, IsWalk)
        exportattrs = copyattrs = ['sound', 'chance', 'type']

    SINT16_MACRO(boundX1, 7)
    SINT16_MACRO(boundY1, 8)
    SINT16_MACRO(boundZ1, 9)
    SINT16_MACRO(boundX2, 10)
    SINT16_MACRO(boundY2, 11)
    SINT16_MACRO(boundZ2, 12)
    STRING_MACRO(full, 13)
    FORMID_MACRO(script, 14)
    FORMID_MACRO(effect, 15)
    UINT32_FLAG_MACRO(flags, 16)
    UINT8_FLAG_MACRO(extraFlags, 17)
    UINT8_ARRAY_MACRO(unused1, 18, 3)
    GroupedValuesMACRO(male, 19, BipedModel)
    GroupedValuesMACRO(maleWorld, 23, WorldModel)
    ISTRING_MACRO(maleIconPath, 26)
    ISTRING_MACRO(maleSmallIconPath, 27)
    GroupedValuesMACRO(female, 28, BipedModel)
    GroupedValuesMACRO(femaleWorld, 32, WorldModel)
    ISTRING_MACRO(femaleIconPath, 35)
    ISTRING_MACRO(femaleSmallIconPath, 36)
    ISTRING_MACRO(ragdollTemplatePath, 37)
    FORMID_MACRO(repairList, 38)
    FORMID_MACRO(modelList, 39)
    SINT32_TYPE_MACRO(equipmentType, 40)
    FORMID_MACRO(pickupSound, 41)
    FORMID_MACRO(dropSound, 42)
    SINT32_MACRO(value, 43)
    SINT32_MACRO(health, 44)
    FLOAT32_MACRO(weight, 45)
    SINT16_MACRO(AR, 46)
    UINT16_FLAG_MACRO(voiceFlags, 47)
    FLOAT32_MACRO(DT, 48)
    UINT8_ARRAY_MACRO(unknown1, 49, 4)
    UINT32_TYPE_MACRO(overrideSounds, 50)
    LIST_MACRO(sounds, 51, self.Sound)
    FORMID_MACRO(soundsTemplate, 52)

    BasicFlagMACRO(IsHead, flags, 0x00000001)
    BasicFlagMACRO(IsHair, flags, 0x00000002)
    BasicFlagMACRO(IsUpperBody, flags, 0x00000004)
    BasicFlagMACRO(IsLeftHand, flags, 0x00000008)
    BasicFlagMACRO(IsRightHand, flags, 0x00000010)
    BasicFlagMACRO(IsWeapon, flags, 0x00000020)
    BasicFlagMACRO(IsPipBoy, flags, 0x00000040)
    BasicFlagMACRO(IsBackpack, flags, 0x00000080)
    BasicFlagMACRO(IsNecklace, flags, 0x00000100)
    BasicFlagMACRO(IsHeadband, flags, 0x00000200)
    BasicFlagMACRO(IsHat, flags, 0x00000400)
    BasicFlagMACRO(IsEyeGlasses, flags, 0x00000800)
    BasicFlagMACRO(IsNoseRing, flags, 0x00001000)
    BasicFlagMACRO(IsEarrings, flags, 0x00002000)
    BasicFlagMACRO(IsMask, flags, 0x00004000)
    BasicFlagMACRO(IsChoker, flags, 0x00008000)
    BasicFlagMACRO(IsMouthObject, flags, 0x00010000)
    BasicFlagMACRO(IsBodyAddon1, flags, 0x00020000)
    BasicFlagMACRO(IsBodyAddon2, flags, 0x00040000)
    BasicFlagMACRO(IsBodyAddon3, flags, 0x00080000)

    BasicFlagMACRO(IsUnknown1, extraFlags, 0x0001)
    BasicFlagMACRO(IsUnknown2, extraFlags, 0x0002)
    BasicFlagMACRO(IsHasBackpack, extraFlags, 0x0004)
    BasicFlagMACRO(IsMedium, extraFlags, 0x0008)
    BasicFlagMACRO(IsUnknown3, extraFlags, 0x0010)
    BasicFlagMACRO(IsPowerArmor, extraFlags, 0x0020)
    BasicFlagMACRO(IsNonPlayable, extraFlags, 0x0040)
    BasicFlagMACRO(IsHeavy, extraFlags, 0x0080)

    BasicTypeMACRO(IsNone, equipmentType, -1, IsBigGuns)
    BasicTypeMACRO(IsBigGuns, equipmentType, 0, IsNone)
    BasicTypeMACRO(IsEnergyWeapons, equipmentType, 1, IsNone)
    BasicTypeMACRO(IsSmallGuns, equipmentType, 2, IsNone)
    BasicTypeMACRO(IsMeleeWeapons, equipmentType, 3, IsNone)
    BasicTypeMACRO(IsUnarmedWeapon, equipmentType, 4, IsNone)
    BasicTypeMACRO(IsThrownWeapons, equipmentType, 5, IsNone)
    BasicTypeMACRO(IsMine, equipmentType, 6, IsNone)
    BasicTypeMACRO(IsBodyWear, equipmentType, 7, IsNone)
    BasicTypeMACRO(IsHeadWear, equipmentType, 8, IsNone)
    BasicTypeMACRO(IsHandWear, equipmentType, 9, IsNone)
    BasicTypeMACRO(IsChems, equipmentType, 10, IsNone)
    BasicTypeMACRO(IsStimpack, equipmentType, 11, IsNone)
    BasicTypeMACRO(IsEdible, equipmentType, 12, IsNone)
    BasicTypeMACRO(IsAlcohol, equipmentType, 13, IsNone)

    BasicTypeMACRO(IsNotOverridingSounds, overrideSounds, 0, IsOverridingSounds)
    BasicTypeMACRO(IsOverridingSounds, overrideSounds, 1, IsNotOverridingSounds)

    BasicFlagMACRO(IsModulatesVoice, voiceFlags, 0x0001)
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                                         'boundX2', 'boundY2', 'boundZ2',
                                                         'full', 'script', 'effect',
                                                         'flags', 'extraFlags',
                                                         'male_list', 'maleWorld_list',
                                                         'maleIconPath', 'maleSmallIconPath',
                                                         'female_list', 'femaleWorld_list',
                                                         'femaleIconPath', 'femaleSmallIconPath',
                                                         'ragdollTemplatePath', 'repairList',
                                                         'modelList', 'equipmentType',
                                                         'pickupSound', 'dropSound', 'value',
                                                         'health', 'weight', 'AR', 'voiceFlags',
                                                         'DT', 'unknown1', 'overrideSounds',
                                                         'sounds_list', 'soundsTemplate']

class FnvBOOKRecord(FnvBaseRecord):
    _Type = 'BOOK'
    SINT16_MACRO(boundX1, 7)
    SINT16_MACRO(boundY1, 8)
    SINT16_MACRO(boundZ1, 9)
    SINT16_MACRO(boundX2, 10)
    SINT16_MACRO(boundY2, 11)
    SINT16_MACRO(boundZ2, 12)
    STRING_MACRO(full, 13)
    ISTRING_MACRO(modPath, 14)
    FLOAT32_MACRO(modb, 15)
    UINT8_ARRAY_MACRO(modt_p, 16)

    LIST_MACRO(altTextures, 17, FNVAltTexture)
    UINT8_FLAG_MACRO(modelFlags, 18)
    ISTRING_MACRO(iconPath, 19)
    ISTRING_MACRO(smallIconPath, 20)
    FORMID_MACRO(script, 21)
    STRING_MACRO(description, 22)
    GroupedValuesMACRO(destructable, 23, FNVDestructable)
    UINT8_FLAG_MACRO(flags, 28)
    SINT8_TYPE_MACRO(teaches, 29)
    SINT32_MACRO(value, 30)
    FLOAT32_MACRO(weight, 31)

    BasicFlagMACRO(IsHead, modelFlags, 0x01)
    BasicFlagMACRO(IsTorso, modelFlags, 0x02)
    BasicFlagMACRO(IsRightHand, modelFlags, 0x04)
    BasicFlagMACRO(IsLeftHand, modelFlags, 0x08)

    BasicFlagMACRO(IsFixed, flags, 0x00000002)
    BasicAliasMACRO(IsCantBeTaken, IsFixed)
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
        return True

    SINT16_MACRO(boundX1, 7)
    SINT16_MACRO(boundY1, 8)
    SINT16_MACRO(boundZ1, 9)
    SINT16_MACRO(boundX2, 10)
    SINT16_MACRO(boundY2, 11)
    SINT16_MACRO(boundZ2, 12)
    STRING_MACRO(full, 13)
    ISTRING_MACRO(modPath, 14)
    FLOAT32_MACRO(modb, 15)
    UINT8_ARRAY_MACRO(modt_p, 16)

    LIST_MACRO(altTextures, 17, FNVAltTexture)
    UINT8_FLAG_MACRO(modelFlags, 18)
    FORMID_MACRO(script, 19)

    LIST_MACRO(items, 20, FNVItem)
    GroupedValuesMACRO(destructable, 21, FNVDestructable)
    UINT8_FLAG_MACRO(flags, 26)
    FLOAT32_MACRO(weight, 27)
    FORMID_MACRO(openSound, 28)
    FORMID_MACRO(closeSound, 29)
    FORMID_MACRO(loopSound, 30)

    BasicFlagMACRO(IsHead, modelFlags, 0x01)
    BasicFlagMACRO(IsTorso, modelFlags, 0x02)
    BasicFlagMACRO(IsRightHand, modelFlags, 0x04)
    BasicFlagMACRO(IsLeftHand, modelFlags, 0x08)

    BasicFlagMACRO(IsRespawn, flags, 0x00000001)
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
    SINT16_MACRO(boundX1, 7)
    SINT16_MACRO(boundY1, 8)
    SINT16_MACRO(boundZ1, 9)
    SINT16_MACRO(boundX2, 10)
    SINT16_MACRO(boundY2, 11)
    SINT16_MACRO(boundZ2, 12)
    STRING_MACRO(full, 13)
    ISTRING_MACRO(modPath, 14)
    FLOAT32_MACRO(modb, 15)
    UINT8_ARRAY_MACRO(modt_p, 16)

    LIST_MACRO(altTextures, 17, FNVAltTexture)
    UINT8_FLAG_MACRO(modelFlags, 18)
    FORMID_MACRO(script, 19)
    GroupedValuesMACRO(destructable, 20, FNVDestructable)
    FORMID_MACRO(openSound, 25)
    FORMID_MACRO(closeSound, 26)
    FORMID_MACRO(loopSound, 27)
    UINT8_FLAG_MACRO(flags, 28)

    BasicFlagMACRO(IsHead, modelFlags, 0x01)
    BasicFlagMACRO(IsTorso, modelFlags, 0x02)
    BasicFlagMACRO(IsRightHand, modelFlags, 0x04)
    BasicFlagMACRO(IsLeftHand, modelFlags, 0x08)

    BasicFlagMACRO(IsAutomatic, flags, 0x02)
    BasicFlagMACRO(IsHidden, flags, 0x04)
    BasicFlagMACRO(IsMinimalUse, flags, 0x08)
    BasicFlagMACRO(IsSlidingDoor, flags, 0x10)
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
    SINT16_MACRO(boundX1, 7)
    SINT16_MACRO(boundY1, 8)
    SINT16_MACRO(boundZ1, 9)
    SINT16_MACRO(boundX2, 10)
    SINT16_MACRO(boundY2, 11)
    SINT16_MACRO(boundZ2, 12)
    STRING_MACRO(full, 13)
    ISTRING_MACRO(modPath, 14)
    FLOAT32_MACRO(modb, 15)
    UINT8_ARRAY_MACRO(modt_p, 16)

    LIST_MACRO(altTextures, 17, FNVAltTexture)
    UINT8_FLAG_MACRO(modelFlags, 18)
    ISTRING_MACRO(iconPath, 19)
    ISTRING_MACRO(smallIconPath, 20)
    FORMID_MACRO(script, 21)
    SINT32_TYPE_MACRO(equipmentType, 22)
    FLOAT32_MACRO(weight, 23)
    SINT32_MACRO(value, 24)
    UINT8_FLAG_MACRO(flags, 25)
    UINT8_ARRAY_MACRO(unused1, 26, 3)

    LIST_MACRO(effects, 27, FNVEffect)

    BasicFlagMACRO(IsHead, modelFlags, 0x01)
    BasicFlagMACRO(IsTorso, modelFlags, 0x02)
    BasicFlagMACRO(IsRightHand, modelFlags, 0x04)
    BasicFlagMACRO(IsLeftHand, modelFlags, 0x08)
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
    SINT16_MACRO(boundX1, 7)
    SINT16_MACRO(boundY1, 8)
    SINT16_MACRO(boundZ1, 9)
    SINT16_MACRO(boundX2, 10)
    SINT16_MACRO(boundY2, 11)
    SINT16_MACRO(boundZ2, 12)
    STRING_MACRO(full, 13)
    ISTRING_MACRO(modPath, 14)
    FLOAT32_MACRO(modb, 15)
    UINT8_ARRAY_MACRO(modt_p, 16)

    LIST_MACRO(altTextures, 17, FNVAltTexture)
    UINT8_FLAG_MACRO(modelFlags, 18)
    ISTRING_MACRO(iconPath, 19)
    ISTRING_MACRO(smallIconPath, 20)
    FORMID_MACRO(script, 21)
    SINT32_MACRO(duration, 22)
    UINT32_MACRO(radius, 23)
    UINT8_MACRO(red, 24)
    UINT8_MACRO(green, 25)
    UINT8_MACRO(blue, 26)
    UINT8_ARRAY_MACRO(unused1, 27, 1)
    UINT32_FLAG_MACRO(flags, 28)
    FLOAT32_MACRO(falloff, 29)
    FLOAT32_MACRO(fov, 30)
    UINT32_MACRO(value, 31)
    FLOAT32_MACRO(weight, 32)
    FLOAT32_MACRO(fade, 33)
    FORMID_MACRO(sound, 34)

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

    BasicFlagMACRO(IsHead, modelFlags, 0x01)
    BasicFlagMACRO(IsTorso, modelFlags, 0x02)
    BasicFlagMACRO(IsRightHand, modelFlags, 0x04)
    BasicFlagMACRO(IsLeftHand, modelFlags, 0x08)
    copyattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                           'boundX2', 'boundY2', 'boundZ2',
                                           'full', 'modPath', 'modb', 'modt_p',
                                           'altTextures_list', 'modelFlags',
                                           'iconPath', 'smallIconPath',
                                           'script', 'duration', 'radius',
                                           'red', 'green', 'blue',
                                           'flags', 'falloff', 'fov',
                                           'value', 'weight', 'fade', 'sound']
    exportattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                             'boundX2', 'boundY2', 'boundZ2',
                                             'full', 'modPath', 'modb',
                                             'altTextures_list', 'modelFlags',
                                             'iconPath', 'smallIconPath',
                                             'script', 'duration', 'radius',
                                             'red', 'green', 'blue',
                                             'flags', 'falloff', 'fov',
                                             'value', 'weight', 'fade', 'sound']# 'modt_p',

class FnvMISCRecord(FnvBaseRecord):
    _Type = 'MISC'
    SINT16_MACRO(boundX1, 7)
    SINT16_MACRO(boundY1, 8)
    SINT16_MACRO(boundZ1, 9)
    SINT16_MACRO(boundX2, 10)
    SINT16_MACRO(boundY2, 11)
    SINT16_MACRO(boundZ2, 12)
    STRING_MACRO(full, 13)
    ISTRING_MACRO(modPath, 14)
    FLOAT32_MACRO(modb, 15)
    UINT8_ARRAY_MACRO(modt_p, 16)

    LIST_MACRO(altTextures, 17, FNVAltTexture)
    UINT8_FLAG_MACRO(modelFlags, 18)
    ISTRING_MACRO(iconPath, 19)
    ISTRING_MACRO(smallIconPath, 20)
    FORMID_MACRO(script, 21)
    GroupedValuesMACRO(destructable, 22, FNVDestructable)
    FORMID_MACRO(pickupSound, 27)
    FORMID_MACRO(dropSound, 28)
    SINT32_MACRO(value, 29)
    FLOAT32_MACRO(weight, 30)
    FORMID_MACRO(loopSound, 31)

    BasicFlagMACRO(IsHead, modelFlags, 0x01)
    BasicFlagMACRO(IsTorso, modelFlags, 0x02)
    BasicFlagMACRO(IsRightHand, modelFlags, 0x04)
    BasicFlagMACRO(IsLeftHand, modelFlags, 0x08)
    copyattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                           'boundX2', 'boundY2', 'boundZ2',
                                           'full', 'modPath', 'modb', 'modt_p',
                                           'altTextures_list', 'modelFlags',
                                           'iconPath', 'smallIconPath',
                                           'script', 'destructable_list',
                                           'pickupSound', 'dropSound',
                                           'value', 'weight', 'loopSound']
    exportattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                             'boundX2', 'boundY2', 'boundZ2',
                                             'full', 'modPath', 'modb',
                                             'altTextures_list', 'modelFlags',
                                             'iconPath', 'smallIconPath',
                                             'script', 'destructable_list',
                                             'pickupSound', 'dropSound',
                                             'value', 'weight', 'loopSound']# 'modt_p',

class FnvSTATRecord(FnvBaseRecord):
    _Type = 'STAT'
    SINT16_MACRO(boundX1, 7)
    SINT16_MACRO(boundY1, 8)
    SINT16_MACRO(boundZ1, 9)
    SINT16_MACRO(boundX2, 10)
    SINT16_MACRO(boundY2, 11)
    SINT16_MACRO(boundZ2, 12)
    ISTRING_MACRO(modPath, 13)
    FLOAT32_MACRO(modb, 14)
    UINT8_ARRAY_MACRO(modt_p, 15)

    LIST_MACRO(altTextures, 16, FNVAltTexture)
    UINT8_FLAG_MACRO(modelFlags, 17)
    SINT8_TYPE_MACRO(passSound, 18)
    FORMID_MACRO(loopSound, 19)

    BasicFlagMACRO(IsHead, modelFlags, 0x01)
    BasicFlagMACRO(IsTorso, modelFlags, 0x02)
    BasicFlagMACRO(IsRightHand, modelFlags, 0x04)
    BasicFlagMACRO(IsLeftHand, modelFlags, 0x08)

    BasicTypeMACRO(IsNone, passSound, -1, IsBushA)
    BasicTypeMACRO(IsBushA, passSound, 0, IsNone)
    BasicTypeMACRO(IsBushB, passSound, 1, IsNone)
    BasicTypeMACRO(IsBushC, passSound, 2, IsNone)
    BasicTypeMACRO(IsBushD, passSound, 3, IsNone)
    BasicTypeMACRO(IsBushE, passSound, 4, IsNone)
    BasicTypeMACRO(IsBushF, passSound, 5, IsNone)
    BasicTypeMACRO(IsBushG, passSound, 6, IsNone)
    BasicTypeMACRO(IsBushH, passSound, 7, IsNone)
    BasicTypeMACRO(IsBushI, passSound, 8, IsNone)
    BasicTypeMACRO(IsBushJ, passSound, 9, IsNone)
    copyattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                           'boundX2', 'boundY2', 'boundZ2',
                                           'modPath', 'modb', 'modt_p',
                                           'altTextures_list', 'modelFlags',
                                           'passSound', 'loopSound', ]
    exportattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                             'boundX2', 'boundY2', 'boundZ2',
                                             'modPath', 'modb',
                                             'altTextures_list', 'modelFlags',
                                             'passSound', 'loopSound', ]#, 'modt_p'

class FnvSCOLRecord(FnvBaseRecord):
    _Type = 'SCOL'
    class Static(ListComponent):
        class Placement(ListX2Component):
            FLOAT32_LISTX2MACRO(posX, 1)
            FLOAT32_LISTX2MACRO(posY, 2)
            FLOAT32_LISTX2MACRO(posZ, 3)
            RADIAN_LISTX2MACRO(rotX, 4)
            RADIAN_LISTX2MACRO(rotY, 5)
            RADIAN_LISTX2MACRO(rotZ, 6)
            FLOAT32_LISTX2MACRO(scale, 7)
            exportattrs = copyattrs = ['posX', 'posY', 'posZ',
                                       'rotX', 'rotY', 'rotZ',
                                       'scale']

        FORMID_LISTMACRO(static, 1)

        LIST_LISTMACRO(placements, 2, Placement)
        exportattrs = copyattrs = ['static', 'placements_list']

    SINT16_MACRO(boundX1, 7)
    SINT16_MACRO(boundY1, 8)
    SINT16_MACRO(boundZ1, 9)
    SINT16_MACRO(boundX2, 10)
    SINT16_MACRO(boundY2, 11)
    SINT16_MACRO(boundZ2, 12)
    ISTRING_MACRO(modPath, 13)
    FLOAT32_MACRO(modb, 14)
    UINT8_ARRAY_MACRO(modt_p, 15)

    LIST_MACRO(altTextures, 16, FNVAltTexture)
    UINT8_FLAG_MACRO(modelFlags, 17)

    LIST_MACRO(statics, 18, Static)

    BasicFlagMACRO(IsHead, modelFlags, 0x01)
    BasicFlagMACRO(IsTorso, modelFlags, 0x02)
    BasicFlagMACRO(IsRightHand, modelFlags, 0x04)
    BasicFlagMACRO(IsLeftHand, modelFlags, 0x08)
    copyattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                           'boundX2', 'boundY2', 'boundZ2',
                                           'modPath', 'modb', 'modt_p',
                                           'altTextures_list', 'modelFlags',
                                           'statics_list']
    exportattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                             'boundX2', 'boundY2', 'boundZ2',
                                             'modPath', 'modb',
                                             'altTextures_list', 'modelFlags',
                                             'statics_list']# 'modt_p',

class FnvMSTTRecord(FnvBaseRecord):
    _Type = 'MSTT'
    SINT16_MACRO(boundX1, 7)
    SINT16_MACRO(boundY1, 8)
    SINT16_MACRO(boundZ1, 9)
    SINT16_MACRO(boundX2, 10)
    SINT16_MACRO(boundY2, 11)
    SINT16_MACRO(boundZ2, 12)
    STRING_MACRO(full, 13)
    ISTRING_MACRO(modPath, 14)
    FLOAT32_MACRO(modb, 15)
    UINT8_ARRAY_MACRO(modt_p, 16)

    LIST_MACRO(altTextures, 17, FNVAltTexture)
    UINT8_FLAG_MACRO(modelFlags, 18)
    GroupedValuesMACRO(destructable, 19, FNVDestructable)
    UINT8_ARRAY_MACRO(data_p, 24)
    FORMID_MACRO(sound, 25)

    BasicFlagMACRO(IsHead, modelFlags, 0x01)
    BasicFlagMACRO(IsTorso, modelFlags, 0x02)
    BasicFlagMACRO(IsRightHand, modelFlags, 0x04)
    BasicFlagMACRO(IsLeftHand, modelFlags, 0x08)
    copyattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                           'boundX2', 'boundY2', 'boundZ2',
                                           'full', 'modPath', 'modb', 'modt_p',
                                           'altTextures_list', 'modelFlags',
                                           'destructable_list', 'data_p',
                                           'sound']
    exportattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                             'boundX2', 'boundY2', 'boundZ2',
                                             'full', 'modPath', 'modb',
                                             'altTextures_list', 'modelFlags',
                                             'destructable_list',
                                             'sound']# 'modt_p', 'data_p',

class FnvPWATRecord(FnvBaseRecord):
    _Type = 'PWAT'
    SINT16_MACRO(boundX1, 7)
    SINT16_MACRO(boundY1, 8)
    SINT16_MACRO(boundZ1, 9)
    SINT16_MACRO(boundX2, 10)
    SINT16_MACRO(boundY2, 11)
    SINT16_MACRO(boundZ2, 12)
    ISTRING_MACRO(modPath, 13)
    FLOAT32_MACRO(modb, 14)
    UINT8_ARRAY_MACRO(modt_p, 15)

    LIST_MACRO(altTextures, 16, FNVAltTexture)
    UINT8_FLAG_MACRO(modelFlags, 17)
    UINT32_FLAG_MACRO(flags, 18)
    FORMID_MACRO(water, 19)

    BasicFlagMACRO(IsHead, modelFlags, 0x01)
    BasicFlagMACRO(IsTorso, modelFlags, 0x02)
    BasicFlagMACRO(IsRightHand, modelFlags, 0x04)
    BasicFlagMACRO(IsLeftHand, modelFlags, 0x08)

    BasicFlagMACRO(IsReflects, flags, 0x00000001)
    BasicFlagMACRO(IsReflectsActors, flags, 0x00000002)
    BasicFlagMACRO(IsReflectsLand, flags, 0x00000004)
    BasicFlagMACRO(IsReflectsLODLand, flags, 0x00000008)
    BasicFlagMACRO(IsReflectsLODBuildings, flags, 0x00000010)
    BasicFlagMACRO(IsReflectsTrees, flags, 0x00000020)
    BasicFlagMACRO(IsReflectsSky, flags, 0x00000040)
    BasicFlagMACRO(IsReflectsDynamicObjects, flags, 0x00000080)
    BasicFlagMACRO(IsReflectsDeadBodies, flags, 0x00000100)
    BasicFlagMACRO(IsRefracts, flags, 0x00000200)
    BasicFlagMACRO(IsRefractsActors, flags, 0x00000400)
    BasicFlagMACRO(IsRefractsLand, flags, 0x00000800)
    BasicFlagMACRO(IsRefractsDynamicObjects, flags, 0x00010000)
    BasicFlagMACRO(IsRefractsDeadBodies, flags, 0x00020000)
    BasicFlagMACRO(IsSilhouetteReflections, flags, 0x00040000)
    BasicFlagMACRO(IsDepth, flags, 0x10000000)
    BasicFlagMACRO(IsObjectTextureCoordinates, flags, 0x20000000)
    BasicFlagMACRO(IsNoUnderwaterFog, flags, 0x80000000)
    BasicInvertedFlagMACRO(IsUnderwaterFog, IsNoUnderwaterFog)
    copyattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                           'boundX2', 'boundY2', 'boundZ2',
                                           'modPath', 'modb', 'modt_p',
                                           'altTextures_list',
                                           'modelFlags', 'flags', 'water', ]
    exportattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                             'boundX2', 'boundY2', 'boundZ2',
                                             'modPath', 'modb',
                                             'altTextures_list',
                                             'modelFlags', 'flags', 'water', ]# 'modt_p',

class FnvGRASRecord(FnvBaseRecord):
    _Type = 'GRAS'
    SINT16_MACRO(boundX1, 7)
    SINT16_MACRO(boundY1, 8)
    SINT16_MACRO(boundZ1, 9)
    SINT16_MACRO(boundX2, 10)
    SINT16_MACRO(boundY2, 11)
    SINT16_MACRO(boundZ2, 12)
    ISTRING_MACRO(modPath, 13)
    FLOAT32_MACRO(modb, 14)
    UINT8_ARRAY_MACRO(modt_p, 15)

    LIST_MACRO(altTextures, 16, FNVAltTexture)
    UINT8_FLAG_MACRO(modelFlags, 17)
    UINT8_MACRO(density, 18)
    UINT8_MACRO(minSlope, 19)
    UINT8_MACRO(maxSlope, 20)
    UINT8_ARRAY_MACRO(unused1, 21, 1)
    UINT16_MACRO(waterDistance, 22)
    UINT8_ARRAY_MACRO(unused2, 23, 2)
    UINT32_MACRO(waterOp, 24)
    FLOAT32_MACRO(posRange, 25)
    FLOAT32_MACRO(heightRange, 26)
    FLOAT32_MACRO(colorRange, 27)
    FLOAT32_MACRO(wavePeriod, 28)
    UINT8_FLAG_MACRO(flags, 29)
    UINT8_ARRAY_MACRO(unused3, 30, 3)

    BasicFlagMACRO(IsHead, modelFlags, 0x01)
    BasicFlagMACRO(IsTorso, modelFlags, 0x02)
    BasicFlagMACRO(IsRightHand, modelFlags, 0x04)
    BasicFlagMACRO(IsLeftHand, modelFlags, 0x08)

    BasicFlagMACRO(IsVLighting, flags, 0x00000001)
    BasicAliasMACRO(IsVertexLighting, IsVLighting)
    BasicFlagMACRO(IsUScaling, flags, 0x00000002)
    BasicAliasMACRO(IsUniformScaling, IsUScaling)
    BasicFlagMACRO(IsFitSlope, flags, 0x00000004)
    BasicAliasMACRO(IsFitToSlope, IsFitSlope)
    copyattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                           'boundX2', 'boundY2', 'boundZ2',
                                           'modPath', 'modb', 'modt_p',
                                           'altTextures_list', 'modelFlags',
                                           'density', 'minSlope', 'maxSlope',
                                           'waterDistance', 'waterOp',
                                           'posRange', 'heightRange',
                                           'colorRange', 'wavePeriod',
                                           'flags']
    exportattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                             'boundX2', 'boundY2', 'boundZ2',
                                             'modPath', 'modb',
                                             'altTextures_list', 'modelFlags',
                                             'density', 'minSlope', 'maxSlope',
                                             'waterDistance', 'waterOp',
                                             'posRange', 'heightRange',
                                             'colorRange', 'wavePeriod',
                                             'flags']# 'modt_p',

class FnvTREERecord(FnvBaseRecord):
    _Type = 'TREE'
    SINT16_MACRO(boundX1, 7)
    SINT16_MACRO(boundY1, 8)
    SINT16_MACRO(boundZ1, 9)
    SINT16_MACRO(boundX2, 10)
    SINT16_MACRO(boundY2, 11)
    SINT16_MACRO(boundZ2, 12)
    ISTRING_MACRO(modPath, 13)
    FLOAT32_MACRO(modb, 14)
    UINT8_ARRAY_MACRO(modt_p, 15)

    LIST_MACRO(altTextures, 16, FNVAltTexture)
    UINT8_FLAG_MACRO(modelFlags, 17)
    ISTRING_MACRO(iconPath, 18)
    ISTRING_MACRO(smallIconPath, 19)
    UINT32_ARRAY_MACRO(speedTree, 20)
    FLOAT32_MACRO(curvature, 21)
    FLOAT32_MACRO(minAngle, 22)
    FLOAT32_MACRO(maxAngle, 23)
    FLOAT32_MACRO(branchDim, 24)
    FLOAT32_MACRO(leafDim, 25)
    SINT32_MACRO(shadowRadius, 26)
    FLOAT32_MACRO(rockSpeed, 27)
    FLOAT32_MACRO(rustleSpeed, 28)
    FLOAT32_MACRO(widthBill, 29)
    FLOAT32_MACRO(heightBill, 30)
    copyattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                           'boundX2', 'boundY2', 'boundZ2',
                                           'modPath', 'modb', 'modt_p',
                                           'altTextures_list', 'modelFlags',
                                           'iconPath', 'smallIconPath',
                                           'speedTree', 'curvature',
                                           'minAngle', 'maxAngle',
                                           'branchDim', 'leafDim',
                                           'shadowRadius', 'rockSpeed',
                                           'rustleSpeed', 'widthBill',
                                           'heightBill']
    exportattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                             'boundX2', 'boundY2', 'boundZ2',
                                             'modPath', 'modb',
                                             'altTextures_list', 'modelFlags',
                                             'iconPath', 'smallIconPath',
                                             'speedTree', 'curvature',
                                             'minAngle', 'maxAngle',
                                             'branchDim', 'leafDim',
                                             'shadowRadius', 'rockSpeed',
                                             'rustleSpeed', 'widthBill',
                                             'heightBill']# 'modt_p',

class FnvFURNRecord(FnvBaseRecord):
    _Type = 'FURN'
    SINT16_MACRO(boundX1, 7)
    SINT16_MACRO(boundY1, 8)
    SINT16_MACRO(boundZ1, 9)
    SINT16_MACRO(boundX2, 10)
    SINT16_MACRO(boundY2, 11)
    SINT16_MACRO(boundZ2, 12)
    STRING_MACRO(full, 13)
    ISTRING_MACRO(modPath, 14)
    FLOAT32_MACRO(modb, 15)
    UINT8_ARRAY_MACRO(modt_p, 16)

    LIST_MACRO(altTextures, 17, FNVAltTexture)
    UINT8_FLAG_MACRO(modelFlags, 18)
    FORMID_MACRO(script, 19)
    GroupedValuesMACRO(destructable, 20, FNVDestructable)
    UINT32_FLAG_MACRO(flags, 25)

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
    copyattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                           'boundX2', 'boundY2', 'boundZ2',
                                           'full', 'modPath', 'modb', 'modt_p',
                                           'altTextures_list', 'modelFlags',
                                           'script', 'destructable_list',
                                           'flags']
    exportattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                             'boundX2', 'boundY2', 'boundZ2',
                                             'full', 'modPath', 'modb',
                                             'altTextures_list', 'modelFlags',
                                             'script', 'destructable_list',
                                             'flags']# 'modt_p',

class FnvWEAPRecord(FnvBaseRecord):
    _Type = 'WEAP'
    SINT16_MACRO(boundX1, 7)
    SINT16_MACRO(boundY1, 8)
    SINT16_MACRO(boundZ1, 9)
    SINT16_MACRO(boundX2, 10)
    SINT16_MACRO(boundY2, 11)
    SINT16_MACRO(boundZ2, 12)
    STRING_MACRO(full, 13)
    ISTRING_MACRO(modPath, 14)
    FLOAT32_MACRO(modb, 15)
    UINT8_ARRAY_MACRO(modt_p, 16)

    LIST_MACRO(altTextures, 17, FNVAltTexture)
    UINT8_FLAG_MACRO(modelFlags, 18)
    ISTRING_MACRO(iconPath, 19)
    ISTRING_MACRO(smallIconPath, 20)
    FORMID_MACRO(script, 21)
    FORMID_MACRO(effect, 22)
    SINT16_MACRO(chargeAmount, 23)
    FORMID_MACRO(ammo, 24)
    GroupedValuesMACRO(destructable, 25, FNVDestructable)
    FORMID_MACRO(repairList, 30)
    SINT32_TYPE_MACRO(equipmentType, 31)
    FORMID_MACRO(modelList, 32)
    FORMID_MACRO(pickupSound, 33)
    FORMID_MACRO(dropSound, 34)
    GroupedValuesMACRO(shell, 35, WorldModel)
    GroupedValuesMACRO(scope, 38, WorldModel)
    FORMID_MACRO(scopeEffect, 41)
    GroupedValuesMACRO(world, 42, WorldModel)
    STRING_MACRO(vatsName, 45)
    STRING_MACRO(weaponNode, 46)
    ISTRING_MACRO(model1Path, 47)
    ISTRING_MACRO(model2Path, 48)
    ISTRING_MACRO(model12Path, 49)
    ISTRING_MACRO(model3Path, 50)
    ISTRING_MACRO(model13Path, 51)
    ISTRING_MACRO(model23Path, 52)
    ISTRING_MACRO(model123Path, 53)
    FORMID_MACRO(impact, 54)
    FORMID_MACRO(model, 55)
    FORMID_MACRO(model1, 56)
    FORMID_MACRO(model2, 57)
    FORMID_MACRO(model12, 58)
    FORMID_MACRO(model3, 59)
    FORMID_MACRO(model13, 60)
    FORMID_MACRO(model23, 61)
    FORMID_MACRO(model123, 62)
    FORMID_MACRO(mod1, 63)
    FORMID_MACRO(mod2, 64)
    FORMID_MACRO(mod3, 65)
    FORMID_MACRO(sound3D, 66)
    FORMID_MACRO(soundDist, 67)
    FORMID_MACRO(sound2D, 68)
    FORMID_MACRO(sound3DLoop, 69)
    FORMID_MACRO(soundMelee, 70)
    FORMID_MACRO(soundBlock, 71)
    FORMID_MACRO(soundIdle, 72)
    FORMID_MACRO(soundEquip, 73)
    FORMID_MACRO(soundUnequip, 74)
    FORMID_MACRO(soundMod3D, 75)
    FORMID_MACRO(soundModDist, 76)
    FORMID_MACRO(soundMod2D, 77)
    SINT32_MACRO(value, 78)
    SINT32_MACRO(health, 79)
    FLOAT32_MACRO(weight, 80)
    SINT16_MACRO(damage, 81)
    UINT8_MACRO(clipSize, 82)
    UINT32_TYPE_MACRO(animType, 83)
    FLOAT32_MACRO(animMult, 84)
    FLOAT32_MACRO(reach, 85)
    UINT8_FLAG_MACRO(flags, 86)
    UINT8_TYPE_MACRO(gripAnim, 87)
    UINT8_MACRO(ammoUse, 88)
    UINT8_TYPE_MACRO(reloadAnim, 89)
    FLOAT32_MACRO(minSpread, 90)
    FLOAT32_MACRO(spread, 91)
    FLOAT32_MACRO(unknown1, 92)
    FLOAT32_MACRO(sightFOV, 93)
    FLOAT32_MACRO(unknown2, 94)
    FORMID_MACRO(projectile, 95)
    UINT8_MACRO(VATSHitChance, 96)
    UINT8_TYPE_MACRO(attackAnim, 97)
    UINT8_MACRO(projectileCount, 98)
    UINT8_TYPE_MACRO(weaponAV, 99)
    FLOAT32_MACRO(minRange, 100)
    FLOAT32_MACRO(maxRange, 101)
    UINT32_TYPE_MACRO(onHit, 102)
    UINT32_FLAG_MACRO(extraFlags, 103)
    FLOAT32_MACRO(animAttackMult, 104)
    FLOAT32_MACRO(fireRate, 105)
    FLOAT32_MACRO(overrideAP, 106)
    FLOAT32_MACRO(leftRumble, 107)
    FLOAT32_MACRO(timeRumble, 108)
    FLOAT32_MACRO(overrideDamageToWeapon, 109)
    FLOAT32_MACRO(reloadTime, 110)
    FLOAT32_MACRO(jamTime, 111)
    FLOAT32_MACRO(aimArc, 112)
    SINT32_MACRO(skill, 113)
    UINT32_TYPE_MACRO(rumbleType, 114)
    FLOAT32_MACRO(rumbleWavelength, 115)
    FLOAT32_MACRO(limbDamageMult, 116)
    SINT32_TYPE_MACRO(resistType, 117)
    FLOAT32_MACRO(sightUsage, 118)
    FLOAT32_MACRO(semiFireDelayMin, 119)
    FLOAT32_MACRO(semiFireDelayMax, 120)
    FLOAT32_MACRO(unknown3, 121)
    UINT32_MACRO(effectMod1, 122)
    UINT32_MACRO(effectMod2, 123)
    UINT32_MACRO(effectMod3, 124)
    FLOAT32_MACRO(valueAMod1, 125)
    FLOAT32_MACRO(valueAMod2, 126)
    FLOAT32_MACRO(valueAMod3, 127)
    UINT32_TYPE_MACRO(overridePwrAtkAnim, 128)
    UINT32_MACRO(strengthReq, 129)
    UINT8_MACRO(unknown4, 130)
    UINT8_TYPE_MACRO(reloadAnimMod, 131)
    UINT8_ARRAY_MACRO(unknown5, 132, 2)
    FLOAT32_MACRO(regenRate, 133)
    FLOAT32_MACRO(killImpulse, 134)
    FLOAT32_MACRO(valueBMod1, 135)
    FLOAT32_MACRO(valueBMod2, 136)
    FLOAT32_MACRO(valueBMod3, 137)
    UINT32_MACRO(skillReq, 138)
    UINT16_MACRO(critDamage, 139)
    UINT8_ARRAY_MACRO(unused1, 140, 2)
    FLOAT32_MACRO(critMult, 141)
    UINT8_FLAG_MACRO(critFlags, 142)
    UINT8_ARRAY_MACRO(unused2, 143, 3)
    FORMID_MACRO(critEffect, 144)
    FORMID_MACRO(vatsEffect, 145)
    FLOAT32_MACRO(vatsSkill, 146)
    FLOAT32_MACRO(vatsDamageMult, 147)
    FLOAT32_MACRO(AP, 148)
    UINT8_TYPE_MACRO(silenceType, 149)
    UINT8_TYPE_MACRO(modRequiredType, 150)
    UINT8_ARRAY_MACRO(unused3, 151, 2)
    UINT32_MACRO(soundLevelType, 152)

    BasicFlagMACRO(IsNotNormalWeapon, flags, 0x01)
    BasicInvertedFlagMACRO(IsNormalWeapon, IsNotNormalWeapon)
    BasicFlagMACRO(IsAutomatic, flags, 0x02)
    BasicFlagMACRO(IsHasScope, flags, 0x04)
    BasicFlagMACRO(IsCantDrop, flags, 0x08)
    BasicInvertedFlagMACRO(IsCanDrop, IsCantDrop)
    BasicFlagMACRO(IsHideBackpack, flags, 0x10)
    BasicFlagMACRO(IsEmbeddedWeapon, flags, 0x20)
    BasicFlagMACRO(IsDontUse1stPersonISAnimations, flags, 0x40)
    BasicInvertedFlagMACRO(IsUse1stPersonISAnimations, IsDontUse1stPersonISAnimations)
    BasicFlagMACRO(IsNonPlayable, flags, 0x80)
    BasicInvertedFlagMACRO(IsPlayable, IsNonPlayable)

    BasicFlagMACRO(IsPlayerOnly, extraFlags, 0x00000001)
    BasicFlagMACRO(IsNPCsUseAmmo, extraFlags, 0x00000002)
    BasicFlagMACRO(IsNoJamAfterReload, extraFlags, 0x00000004)
    BasicInvertedFlagMACRO(IsJamAfterReload, IsNoJamAfterReload)
    BasicFlagMACRO(IsOverrideActionPoints, extraFlags, 0x00000008)
    BasicFlagMACRO(IsMinorCrime, extraFlags, 0x00000010)
    BasicFlagMACRO(IsRangeFixed, extraFlags, 0x00000020)
    BasicFlagMACRO(IsNotUsedInNormalCombat, extraFlags, 0x00000040)
    BasicInvertedFlagMACRO(IsUsedInNormalCombat, IsNotUsedInNormalCombat)
    BasicFlagMACRO(IsOverrideDamageToWeaponMult, extraFlags, 0x00000080)
    BasicFlagMACRO(IsDontUse3rdPersonISAnimations, extraFlags, 0x00000100)
    BasicInvertedFlagMACRO(IsUse3rdPersonISAnimations, IsDontUse3rdPersonISAnimations)
    BasicFlagMACRO(IsShortBurst, extraFlags, 0x00000200)
    BasicFlagMACRO(IsRumbleAlternate, extraFlags, 0x00000400)
    BasicFlagMACRO(IsLongBurst, extraFlags, 0x00000800)
    BasicFlagMACRO(IsScopeHasNightVision, extraFlags, 0x00001000)
    BasicFlagMACRO(IsScopeFromMod, extraFlags, 0x00002000)

    BasicFlagMACRO(IsCritOnDeath, critFlags, 0x01)

    BasicFlagMACRO(IsHead, modelFlags, 0x01)
    BasicFlagMACRO(IsTorso, modelFlags, 0x02)
    BasicFlagMACRO(IsRightHand, modelFlags, 0x04)
    BasicFlagMACRO(IsLeftHand, modelFlags, 0x08)

    BasicTypeMACRO(IsNone, equipmentType, -1, IsBigGuns)
    BasicTypeMACRO(IsBigGuns, equipmentType, 0, IsNone)
    BasicTypeMACRO(IsEnergyWeapons, equipmentType, 1, IsNone)
    BasicTypeMACRO(IsSmallGuns, equipmentType, 2, IsNone)
    BasicTypeMACRO(IsMeleeWeapons, equipmentType, 3, IsNone)
    BasicTypeMACRO(IsUnarmedWeapon, equipmentType, 4, IsNone)
    BasicTypeMACRO(IsThrownWeapons, equipmentType, 5, IsNone)
    BasicTypeMACRO(IsMine, equipmentType, 6, IsNone)
    BasicTypeMACRO(IsBodyWear, equipmentType, 7, IsNone)
    BasicTypeMACRO(IsHeadWear, equipmentType, 8, IsNone)
    BasicTypeMACRO(IsHandWear, equipmentType, 9, IsNone)
    BasicTypeMACRO(IsChems, equipmentType, 10, IsNone)
    BasicTypeMACRO(IsStimpack, equipmentType, 11, IsNone)
    BasicTypeMACRO(IsEdible, equipmentType, 12, IsNone)
    BasicTypeMACRO(IsAlcohol, equipmentType, 13, IsNone)

    BasicTypeMACRO(IsHand2Hand, animType, 0, IsMelee1Hand)
    BasicTypeMACRO(IsMelee1Hand, animType, 1, IsHand2Hand)
    BasicTypeMACRO(IsMelee2Hand, animType, 2, IsHand2Hand)
    BasicTypeMACRO(IsPistolBallistic1Hand, animType, 3, IsHand2Hand)
    BasicTypeMACRO(IsPistolEnergy1Hand, animType, 4, IsHand2Hand)
    BasicTypeMACRO(IsRifleBallistic2Hand, animType, 5, IsHand2Hand)
    BasicTypeMACRO(IsRifleAutomatic2Hand, animType, 6, IsHand2Hand)
    BasicTypeMACRO(IsRifleEnergy2Hand, animType, 7, IsHand2Hand)
    BasicTypeMACRO(IsHandle2Hand, animType, 8, IsHand2Hand)
    BasicTypeMACRO(IsLauncher2Hand, animType, 9, IsHand2Hand)
    BasicTypeMACRO(IsGrenadeThrow1Hand, animType, 10, IsHand2Hand)
    BasicTypeMACRO(IsLandMine1Hand, animType, 11, IsHand2Hand)
    BasicTypeMACRO(IsMineDrop1Hand, animType, 12, IsHand2Hand)
    BasicTypeMACRO(IsThrown1Hand, animType, 13, IsHand2Hand)

    BasicTypeMACRO(IsHandGrip1, gripAnim, 230, IsHandGrip2)
    BasicTypeMACRO(IsHandGrip2, gripAnim, 231, IsHandGrip1)
    BasicTypeMACRO(IsHandGrip3, gripAnim, 232, IsHandGrip1)
    BasicTypeMACRO(IsHandGrip4, gripAnim, 233, IsHandGrip1)
    BasicTypeMACRO(IsHandGrip5, gripAnim, 234, IsHandGrip1)
    BasicTypeMACRO(IsHandGrip6, gripAnim, 235, IsHandGrip1)
    BasicTypeMACRO(IsHandGripDefault, gripAnim, 236, IsHandGrip1)

    BasicTypeMACRO(IsReloadA, reloadAnim, 0, IsReloadB)
    BasicTypeMACRO(IsReloadB, reloadAnim, 1, IsReloadA)
    BasicTypeMACRO(IsReloadC, reloadAnim, 2, IsReloadA)
    BasicTypeMACRO(IsReloadD, reloadAnim, 3, IsReloadA)
    BasicTypeMACRO(IsReloadE, reloadAnim, 4, IsReloadA)
    BasicTypeMACRO(IsReloadF, reloadAnim, 5, IsReloadA)
    BasicTypeMACRO(IsReloadG, reloadAnim, 6, IsReloadA)
    BasicTypeMACRO(IsReloadH, reloadAnim, 7, IsReloadA)
    BasicTypeMACRO(IsReloadI, reloadAnim, 8, IsReloadA)
    BasicTypeMACRO(IsReloadJ, reloadAnim, 9, IsReloadA)
    BasicTypeMACRO(IsReloadK, reloadAnim, 10, IsReloadA)
    BasicTypeMACRO(IsReloadL, reloadAnim, 11, IsReloadA)
    BasicTypeMACRO(IsReloadM, reloadAnim, 12, IsReloadA)
    BasicTypeMACRO(IsReloadN, reloadAnim, 13, IsReloadA)
    BasicTypeMACRO(IsReloadO, reloadAnim, 14, IsReloadA)
    BasicTypeMACRO(IsReloadP, reloadAnim, 15, IsReloadA)
    BasicTypeMACRO(IsReloadQ, reloadAnim, 16, IsReloadA)
    BasicTypeMACRO(IsReloadR, reloadAnim, 17, IsReloadA)
    BasicTypeMACRO(IsReloadS, reloadAnim, 18, IsReloadA)
    BasicTypeMACRO(IsReloadW, reloadAnim, 19, IsReloadA)
    BasicTypeMACRO(IsReloadX, reloadAnim, 20, IsReloadA)
    BasicTypeMACRO(IsReloadY, reloadAnim, 21, IsReloadA)
    BasicTypeMACRO(IsReloadZ, reloadAnim, 22, IsReloadA)

    BasicTypeMACRO(IsAttackLeft, attackAnim, 26, IsAttackRight)
    BasicTypeMACRO(IsAttackRight, attackAnim, 32, IsAttackLeft)
    BasicTypeMACRO(IsAttack3, attackAnim, 38, IsAttackLeft)
    BasicTypeMACRO(IsAttack4, attackAnim, 44, IsAttackLeft)
    BasicTypeMACRO(IsAttack5, attackAnim, 50, IsAttackLeft)
    BasicTypeMACRO(IsAttack6, attackAnim, 56, IsAttackLeft)
    BasicTypeMACRO(IsAttack7, attackAnim, 62, IsAttackLeft)
    BasicTypeMACRO(IsAttack8, attackAnim, 68, IsAttackLeft)
    BasicTypeMACRO(IsAttack9, attackAnim, 144, IsAttackLeft)
    BasicTypeMACRO(IsAttackLoop, attackAnim, 74, IsAttackLeft)
    BasicTypeMACRO(IsAttackSpin, attackAnim, 80, IsAttackLeft)
    BasicTypeMACRO(IsAttackSpin2, attackAnim, 86, IsAttackLeft)
    BasicTypeMACRO(IsAttackThrow, attackAnim, 114, IsAttackLeft)
    BasicTypeMACRO(IsAttackThrow2, attackAnim, 120, IsAttackLeft)
    BasicTypeMACRO(IsAttackThrow3, attackAnim, 126, IsAttackLeft)
    BasicTypeMACRO(IsAttackThrow4, attackAnim, 132, IsAttackLeft)
    BasicTypeMACRO(IsAttackThrow5, attackAnim, 138, IsAttackLeft)
    BasicTypeMACRO(IsAttackThrow6, attackAnim, 150, IsAttackLeft)
    BasicTypeMACRO(IsAttackThrow7, attackAnim, 156, IsAttackLeft)
    BasicTypeMACRO(IsAttackThrow8, attackAnim, 162, IsAttackLeft)
    BasicTypeMACRO(IsPlaceMine, attackAnim, 102, IsAttackLeft)
    BasicTypeMACRO(IsPlaceMine2, attackAnim, 108, IsAttackLeft)
    BasicTypeMACRO(IsAttackDefault, attackAnim, 255, IsAttackLeft)

    BasicTypeMACRO(IsNormalFormulaBehavior, weaponAV, 0, IsDismemberOnly)
    BasicTypeMACRO(IsDismemberOnly, weaponAV, 1, IsNormalFormulaBehavior)
    BasicTypeMACRO(IsExplodeOnly, weaponAV, 2, IsNormalFormulaBehavior)
    BasicTypeMACRO(IsNoDismemberExplode, weaponAV, 3, IsNormalFormulaBehavior)
    BasicInvertedFlagMACRO(IsDismemberExplode, IsNoDismemberExplode)

    BasicTypeMACRO(IsOnHitPerception, onHit, 0, IsEndurance)
    BasicTypeMACRO(IsOnHitEndurance, onHit, 1, IsPerception)
    BasicTypeMACRO(IsOnHitLeftAttack, onHit, 2, IsPerception)
    BasicTypeMACRO(IsOnHitRightAttack, onHit, 3, IsPerception)
    BasicTypeMACRO(IsOnHitLeftMobility, onHit, 4, IsPerception)
    BasicTypeMACRO(IsOnHitRightMobilty, onHit, 5, IsPerception)
    BasicTypeMACRO(IsOnHitBrain, onHit, 6, IsPerception)

    BasicTypeMACRO(IsRumbleConstant, rumbleType, 0, IsSquare)
    BasicTypeMACRO(IsRumbleSquare, rumbleType, 1, IsConstant)
    BasicTypeMACRO(IsRumbleTriangle, rumbleType, 2, IsConstant)
    BasicTypeMACRO(IsRumbleSawtooth, rumbleType, 3, IsConstant)

    BasicTypeMACRO(IsUnknown0, overridePwrAtkAnim, 0, IsAttackCustom1Power)
    BasicTypeMACRO(IsAttackCustom1Power, overridePwrAtkAnim, 97, IsAttackCustom2Power)
    BasicTypeMACRO(IsAttackCustom2Power, overridePwrAtkAnim, 98, IsAttackCustom1Power)
    BasicTypeMACRO(IsAttackCustom3Power, overridePwrAtkAnim, 99, IsAttackCustom1Power)
    BasicTypeMACRO(IsAttackCustom4Power, overridePwrAtkAnim, 100, IsAttackCustom1Power)
    BasicTypeMACRO(IsAttackCustom5Power, overridePwrAtkAnim, 101, IsAttackCustom1Power)
    BasicTypeMACRO(IsAttackCustomDefault, overridePwrAtkAnim, 255, IsAttackCustom1Power)

    BasicTypeMACRO(IsModReloadA, reloadAnimMod, 0, IsModReloadB)
    BasicTypeMACRO(IsModReloadB, reloadAnimMod, 1, IsModReloadA)
    BasicTypeMACRO(IsModReloadC, reloadAnimMod, 2, IsModReloadA)
    BasicTypeMACRO(IsModReloadD, reloadAnimMod, 3, IsModReloadA)
    BasicTypeMACRO(IsModReloadE, reloadAnimMod, 4, IsModReloadA)
    BasicTypeMACRO(IsModReloadF, reloadAnimMod, 5, IsModReloadA)
    BasicTypeMACRO(IsModReloadG, reloadAnimMod, 6, IsModReloadA)
    BasicTypeMACRO(IsModReloadH, reloadAnimMod, 7, IsModReloadA)
    BasicTypeMACRO(IsModReloadI, reloadAnimMod, 8, IsModReloadA)
    BasicTypeMACRO(IsModReloadJ, reloadAnimMod, 9, IsModReloadA)
    BasicTypeMACRO(IsModReloadK, reloadAnimMod, 10, IsModReloadA)
    BasicTypeMACRO(IsModReloadL, reloadAnimMod, 11, IsModReloadA)
    BasicTypeMACRO(IsModReloadM, reloadAnimMod, 12, IsModReloadA)
    BasicTypeMACRO(IsModReloadN, reloadAnimMod, 13, IsModReloadA)
    BasicTypeMACRO(IsModReloadO, reloadAnimMod, 14, IsModReloadA)
    BasicTypeMACRO(IsModReloadP, reloadAnimMod, 15, IsModReloadA)
    BasicTypeMACRO(IsModReloadQ, reloadAnimMod, 16, IsModReloadA)
    BasicTypeMACRO(IsModReloadR, reloadAnimMod, 17, IsModReloadA)
    BasicTypeMACRO(IsModReloadS, reloadAnimMod, 18, IsModReloadA)
    BasicTypeMACRO(IsModReloadW, reloadAnimMod, 19, IsModReloadA)
    BasicTypeMACRO(IsModReloadX, reloadAnimMod, 20, IsModReloadA)
    BasicTypeMACRO(IsModReloadY, reloadAnimMod, 21, IsModReloadA)
    BasicTypeMACRO(IsModReloadZ, reloadAnimMod, 22, IsModReloadA)

    BasicTypeMACRO(IsVATSNotSilent, silenceType, 0, IsVATSSilent)
    BasicTypeMACRO(IsVATSSilent, silenceType, 1, IsVATSNotSilent)

    BasicTypeMACRO(IsVATSNotModRequired, modRequiredType, 0, IsVATSNotModRequired)
    BasicTypeMACRO(IsVATSModRequired, modRequiredType, 1, IsVATSModRequired)

    BasicTypeMACRO(IsLoud, soundLevelType, 0, IsNormal)
    BasicTypeMACRO(IsNormal, soundLevelType, 1, IsLoud)
    BasicTypeMACRO(IsSilent, soundLevelType, 2, IsLoud)
    copyattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                           'boundX2', 'boundY2', 'boundZ2',
                                           'full', 'modPath', 'modb', 'modt_p',
                                           'altTextures_list', 'modelFlags',
                                           'iconPath', 'smallIconPath', 'script',
                                           'effect', 'chargeAmount', 'ammo',
                                           'destructable_list', 'repairList',
                                           'equipmentType', 'modelList',
                                           'pickupSound', 'dropSound', 'shell_list',
                                           'scope_list', 'scopeEffect', 'world_list',
                                           'vatsName', 'weaponNode', 'model1Path',
                                           'model2Path', 'model12Path', 'model3Path',
                                           'model13Path', 'model23Path',
                                           'model123Path', 'impact', 'model',
                                           'model1', 'model2', 'model12', 'model3',
                                           'model13', 'model23', 'model123', 'mod1',
                                           'mod2', 'mod3', 'sound3D', 'soundDist',
                                           'sound2D', 'sound3DLoop', 'soundMelee',
                                           'soundBlock', 'soundIdle', 'soundEquip',
                                           'soundUnequip', 'soundMod3D',
                                           'soundModDist', 'soundMod2D', 'value',
                                           'health', 'weight', 'damage', 'clipSize',
                                           'animType', 'animMult', 'reach', 'flags',
                                           'gripAnim', 'ammoUse', 'reloadAnim',
                                           'minSpread', 'spread', 'unknown1',
                                           'sightFOV', 'unknown2', 'projectile',
                                           'VATSHitChance', 'attackAnim',
                                           'projectileCount', 'weaponAV',
                                           'minRange', 'maxRange', 'onHit',
                                           'extraFlags', 'animAttackMult',
                                           'fireRate', 'overrideAP', 'leftRumble',
                                           'timeRumble', 'overrideDamageToWeapon',
                                           'reloadTime', 'jamTime', 'aimArc',
                                           'skill', 'rumbleType',
                                           'rumbleWavelength', 'limbDamageMult',
                                           'resistType', 'sightUsage',
                                           'semiFireDelayMin', 'semiFireDelayMax',
                                           'unknown3', 'effectMod1', 'effectMod2',
                                           'effectMod3', 'valueAMod1', 'valueAMod2',
                                           'valueAMod3', 'overridePwrAtkAnim',
                                           'strengthReq', 'unknown4',
                                           'reloadAnimMod', 'unknown5', 'regenRate',
                                           'killImpulse', 'valueBMod1', 'valueBMod2',
                                           'valueBMod3', 'skillReq', 'critDamage',
                                           'critMult', 'critFlags', 'critEffect',
                                           'vatsEffect', 'vatsSkill', 'vatsDamageMult', 'AP',
                                           'silenceType', 'modRequiredType',
                                           'soundLevelType']
    exportattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                             'boundX2', 'boundY2', 'boundZ2',
                                             'full', 'modPath', 'modb',
                                             'altTextures_list', 'modelFlags',
                                             'iconPath', 'smallIconPath', 'script',
                                             'effect', 'chargeAmount', 'ammo',
                                             'destructable_list', 'repairList',
                                             'equipmentType', 'modelList',
                                             'pickupSound', 'dropSound', 'shell_list',
                                             'scope_list', 'scopeEffect', 'world_list',
                                             'vatsName', 'weaponNode', 'model1Path',
                                             'model2Path', 'model12Path', 'model3Path',
                                             'model13Path', 'model23Path',
                                             'model123Path', 'impact', 'model',
                                             'model1', 'model2', 'model12', 'model3',
                                             'model13', 'model23', 'model123', 'mod1',
                                             'mod2', 'mod3', 'sound3D', 'soundDist',
                                             'sound2D', 'sound3DLoop', 'soundMelee',
                                             'soundBlock', 'soundIdle', 'soundEquip',
                                             'soundUnequip', 'soundMod3D',
                                             'soundModDist', 'soundMod2D', 'value',
                                             'health', 'weight', 'damage', 'clipSize',
                                             'animType', 'animMult', 'reach', 'flags',
                                             'gripAnim', 'ammoUse', 'reloadAnim',
                                             'minSpread', 'spread', 'unknown1',
                                             'sightFOV', 'unknown2', 'projectile',
                                             'VATSHitChance', 'attackAnim',
                                             'projectileCount', 'weaponAV',
                                             'minRange', 'maxRange', 'onHit',
                                             'extraFlags', 'animAttackMult',
                                             'fireRate', 'overrideAP', 'leftRumble',
                                             'timeRumble', 'overrideDamageToWeapon',
                                             'reloadTime', 'jamTime', 'aimArc',
                                             'skill', 'rumbleType',
                                             'rumbleWavelength', 'limbDamageMult',
                                             'resistType', 'sightUsage',
                                             'semiFireDelayMin', 'semiFireDelayMax',
                                             'unknown3', 'effectMod1', 'effectMod2',
                                             'effectMod3', 'valueAMod1', 'valueAMod2',
                                             'valueAMod3', 'overridePwrAtkAnim',
                                             'strengthReq', 'unknown4',
                                             'reloadAnimMod', 'unknown5', 'regenRate',
                                             'killImpulse', 'valueBMod1', 'valueBMod2',
                                             'valueBMod3', 'skillReq', 'critDamage',
                                             'critMult', 'critFlags', 'critEffect',
                                             'vatsEffect', 'vatsSkill', 'vatsDamageMult', 'AP',
                                             'silenceType', 'modRequiredType',
                                             'soundLevelType']#'modt_p',

class FnvAMMORecord(FnvBaseRecord):
    _Type = 'AMMO'
    SINT16_MACRO(boundX1, 7)
    SINT16_MACRO(boundY1, 8)
    SINT16_MACRO(boundZ1, 9)
    SINT16_MACRO(boundX2, 10)
    SINT16_MACRO(boundY2, 11)
    SINT16_MACRO(boundZ2, 12)
    STRING_MACRO(full, 13)
    ISTRING_MACRO(modPath, 14)
    FLOAT32_MACRO(modb, 15)
    UINT8_ARRAY_MACRO(modt_p, 16)

    LIST_MACRO(altTextures, 17, FNVAltTexture)
    UINT8_FLAG_MACRO(modelFlags, 18)
    ISTRING_MACRO(iconPath, 19)
    ISTRING_MACRO(smallIconPath, 20)
    FORMID_MACRO(script, 21)
    GroupedValuesMACRO(destructable, 22, FNVDestructable)
    FORMID_MACRO(pickupSound, 27)
    FORMID_MACRO(dropSound, 28)
    FLOAT32_MACRO(speed, 29)
    UINT8_FLAG_MACRO(flags, 30)
    UINT8_ARRAY_MACRO(unused1, 31, 3)
    SINT32_MACRO(value, 32)
    UINT8_MACRO(clipRounds, 33)
    UINT32_MACRO(projectilesPerShot, 34)
    FORMID_MACRO(projectile, 35)
    FLOAT32_MACRO(weight, 36)
    FORMID_MACRO(consumedAmmo, 37)
    FLOAT32_MACRO(consumedPercentage, 38)
    STRING_MACRO(shortName, 39)
    STRING_MACRO(abbreviation, 40)
    FORMID_ARRAY_MACRO(effects, 41)

    BasicFlagMACRO(IsNotNormalWeapon, flags, 0x01)
    BasicInvertedFlagMACRO(IsNormalWeapon, IsNotNormalWeapon)
    BasicFlagMACRO(IsNonPlayable, flags, 0x02)
    BasicInvertedFlagMACRO(IsPlayable, IsNonPlayable)

    BasicFlagMACRO(IsHead, modelFlags, 0x01)
    BasicFlagMACRO(IsTorso, modelFlags, 0x02)
    BasicFlagMACRO(IsRightHand, modelFlags, 0x04)
    BasicFlagMACRO(IsLeftHand, modelFlags, 0x08)
    copyattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                           'boundX2', 'boundY2', 'boundZ2',
                                           'full', 'modPath', 'modb', 'modt_p',
                                           'altTextures_list', 'modelFlags',
                                           'iconPath', 'smallIconPath', 'script',
                                           'destructable_list', 'pickupSound',
                                           'dropSound', 'speed', 'flags',
                                           'value', 'clipRounds',
                                           'projectilesPerShot', 'projectile',
                                           'weight', 'consumedAmmo',
                                           'consumedPercentage', 'shortName',
                                           'abbreviation', 'effects']
    exportattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                             'boundX2', 'boundY2', 'boundZ2',
                                             'full', 'modPath', 'modb',
                                             'altTextures_list', 'modelFlags',
                                             'iconPath', 'smallIconPath', 'script',
                                             'destructable_list', 'pickupSound',
                                             'dropSound', 'speed', 'flags',
                                             'value', 'clipRounds',
                                             'projectilesPerShot', 'projectile',
                                             'weight', 'consumedAmmo',
                                             'consumedPercentage', 'shortName',
                                             'abbreviation', 'effects']

class FnvNPC_Record(FnvBaseRecord):
    _Type = 'NPC_'
    def mergeFilter(self,modSet):
        """Filter out items that don't come from specified modSet.
        Filters items."""
        self.items = [x for x in self.items if x.item[0] in modSet]
        return True

    SINT16_MACRO(boundX1, 7)
    SINT16_MACRO(boundY1, 8)
    SINT16_MACRO(boundZ1, 9)
    SINT16_MACRO(boundX2, 10)
    SINT16_MACRO(boundY2, 11)
    SINT16_MACRO(boundZ2, 12)
    STRING_MACRO(full, 13)
    ISTRING_MACRO(modPath, 14)
    FLOAT32_MACRO(modb, 15)
    UINT8_ARRAY_MACRO(modt_p, 16)

    LIST_MACRO(altTextures, 17, FNVAltTexture)
    UINT8_FLAG_MACRO(modelFlags, 18)
    UINT32_FLAG_MACRO(flags, 19)
    UINT16_MACRO(fatigue, 20)
    UINT16_MACRO(barterGold, 21)
    SINT16_MACRO(level, 22)
    UINT16_MACRO(calcMin, 23)
    UINT16_MACRO(calcMax, 24)
    UINT16_MACRO(speedMult, 25)
    FLOAT32_MACRO(karma, 26)
    SINT16_MACRO(dispBase, 27)
    UINT16_FLAG_MACRO(templateFlags, 28)

    LIST_MACRO(factions, 29, Faction)
    FORMID_MACRO(deathItem, 30)
    FORMID_MACRO(voice, 31)
    FORMID_MACRO(template, 32)
    FORMID_MACRO(race, 33)
    FORMID_ARRAY_MACRO(actorEffects, 34)
    FORMID_MACRO(unarmedEffect, 35)
    UINT16_TYPE_MACRO(unarmedAnim, 36)
    GroupedValuesMACRO(destructable, 37, FNVDestructable)
    FORMID_MACRO(script, 42)

    LIST_MACRO(items, 43, FNVItem)
    UINT8_MACRO(aggression, 44)
    UINT8_MACRO(confidence, 45)
    UINT8_MACRO(energyLevel, 46)
    UINT8_MACRO(responsibility, 47)
    UINT8_MACRO(mood, 48)
    UINT8_ARRAY_MACRO(unused1, 49, 3)
    UINT32_FLAG_MACRO(services, 50)
    SINT8_TYPE_MACRO(trainSkill, 51)
    UINT8_MACRO(trainLevel, 52)
    UINT8_MACRO(assistance, 53)
    UINT8_FLAG_MACRO(aggroFlags, 54)
    SINT32_MACRO(aggroRadius, 55)
    FORMID_ARRAY_MACRO(aiPackages, 56)
    FORMID_MACRO(iclass, 57)
    SINT32_MACRO(baseHealth, 58)
    UINT8_MACRO(strength, 59)
    UINT8_MACRO(perception, 60)
    UINT8_MACRO(endurance, 61)
    UINT8_MACRO(charisma, 62)
    UINT8_MACRO(intelligence, 63)
    UINT8_MACRO(agility, 64)
    UINT8_MACRO(luck, 65)
    UINT8_MACRO(barter, 66)
    UINT8_MACRO(bigGuns, 67)
    UINT8_MACRO(energy, 68)
    UINT8_MACRO(explosives, 69)
    UINT8_MACRO(lockpick, 70)
    UINT8_MACRO(medicine, 71)
    UINT8_MACRO(melee, 72)
    UINT8_MACRO(repair, 73)
    UINT8_MACRO(science, 74)
    UINT8_MACRO(guns, 75)
    UINT8_MACRO(sneak, 76)
    UINT8_MACRO(speech, 77)
    UINT8_MACRO(survival, 78)
    UINT8_MACRO(unarmed, 79)
    UINT8_MACRO(barterBoost, 80)
    UINT8_MACRO(bigGunsBoost, 81)
    UINT8_MACRO(energyBoost, 82)
    UINT8_MACRO(explosivesBoost, 83)
    UINT8_MACRO(lockpickBoost, 84)
    UINT8_MACRO(medicineBoost, 85)
    UINT8_MACRO(meleeBoost, 86)
    UINT8_MACRO(repairBoost, 87)
    UINT8_MACRO(scienceBoost, 88)
    UINT8_MACRO(gunsBoost, 89)
    UINT8_MACRO(sneakBoost, 90)
    UINT8_MACRO(speechBoost, 91)
    UINT8_MACRO(survivalBoost, 92)
    UINT8_MACRO(unarmedBoost, 93)
    FORMID_ARRAY_MACRO(headParts, 94)
    FORMID_MACRO(hair, 95)
    FLOAT32_MACRO(hairLength, 96)
    FORMID_MACRO(eyes, 97)
    UINT8_MACRO(hairRed, 98)
    UINT8_MACRO(hairGreen, 99)
    UINT8_MACRO(hairBlue, 100)
    UINT8_ARRAY_MACRO(unused2, 101, 1)
    FORMID_MACRO(combatStyle, 102)
    UINT32_TYPE_MACRO(impactType, 103)
    UINT8_ARRAY_MACRO(fggs_p, 104, 200)
    UINT8_ARRAY_MACRO(fgga_p, 105, 120)
    UINT8_ARRAY_MACRO(fgts_p, 106, 200)
    UINT16_MACRO(unknown, 107)
    FLOAT32_MACRO(height, 108)
    FLOAT32_MACRO(weight, 109)

    BasicFlagMACRO(IsFemale, flags, 0x00000001)
    BasicFlagMACRO(IsEssential, flags, 0x00000002)
    BasicFlagMACRO(IsCharGenFacePreset, flags, 0x00000004)
    BasicFlagMACRO(IsRespawn, flags, 0x00000008)
    BasicFlagMACRO(IsAutoCalcStats, flags, 0x00000010)
    BasicFlagMACRO(IsPCLevelOffset, flags, 0x00000080)
    BasicFlagMACRO(IsUseTemplate, flags, 0x00000100)
    BasicFlagMACRO(IsNoLowLevel, flags, 0x00000200)
    BasicFlagMACRO(IsNoBloodSpray, flags, 0x00000800)
    BasicFlagMACRO(IsNoBloodDecal, flags, 0x00001000)
    BasicFlagMACRO(IsNoVATSMelee, flags, 0x00100000)
    BasicFlagMACRO(IsCanBeAllRaces, flags, 0x00400000)
    BasicFlagMACRO(IsAutoCalcService, flags, 0x00800000)
    BasicFlagMACRO(IsNoKnockdowns, flags, 0x03000000)
    BasicFlagMACRO(IsNotPushable, flags, 0x08000000)
    BasicFlagMACRO(IsNoHeadTracking, flags, 0x40000000)

    BasicFlagMACRO(IsUseTraits, templateFlags, 0x00000001)
    BasicFlagMACRO(IsUseStats, templateFlags, 0x00000002)
    BasicFlagMACRO(IsUseFactions, templateFlags, 0x00000004)
    BasicFlagMACRO(IsUseAEList, templateFlags, 0x00000008)
    BasicFlagMACRO(IsUseAIData, templateFlags, 0x00000010)
    BasicFlagMACRO(IsUseAIPackages, templateFlags, 0x00000020)
    BasicFlagMACRO(IsUseModelAnim, templateFlags, 0x00000040)
    BasicFlagMACRO(IsUseBaseData, templateFlags, 0x00000080)
    BasicFlagMACRO(IsUseInventory, templateFlags, 0x00000100)
    BasicFlagMACRO(IsUseScript, templateFlags, 0x00000200)

    BasicFlagMACRO(IsAggroRadiusBehavior, aggroFlags, 0x01)

    BasicFlagMACRO(IsHead, modelFlags, 0x01)
    BasicFlagMACRO(IsTorso, modelFlags, 0x02)
    BasicFlagMACRO(IsRightHand, modelFlags, 0x04)
    BasicFlagMACRO(IsLeftHand, modelFlags, 0x08)

    BasicTypeMACRO(IsUnaggressive, aggression, 0, IsAggressive)
    BasicTypeMACRO(IsAggressive, aggression, 1, IsUnaggressive)
    BasicTypeMACRO(IsVeryAggressive, aggression, 2, IsUnaggressive)
    BasicTypeMACRO(IsFrenzied, aggression, 3, IsUnaggressive)

    BasicTypeMACRO(IsCowardly, confidence, 0, IsCautious)
    BasicTypeMACRO(IsCautious, confidence, 1, IsCowardly)
    BasicTypeMACRO(IsAverage, confidence, 2, IsCowardly)
    BasicTypeMACRO(IsBrave, confidence, 3, IsCowardly)
    BasicTypeMACRO(IsFoolhardy, confidence, 4, IsCowardly)

    BasicTypeMACRO(IsNeutral, mood, 0, IsAfraid)
    BasicTypeMACRO(IsAfraid, mood, 1, IsNeutral)
    BasicTypeMACRO(IsAnnoyed, mood, 2, IsNeutral)
    BasicTypeMACRO(IsCocky, mood, 3, IsNeutral)
    BasicTypeMACRO(IsDrugged, mood, 4, IsNeutral)
    BasicTypeMACRO(IsPleasant, mood, 5, IsNeutral)
    BasicTypeMACRO(IsAngry, mood, 6, IsNeutral)
    BasicTypeMACRO(IsSad, mood, 7, IsNeutral)

    BasicTypeMACRO(IsHelpsNobody, assistance, 0, IsHelpsAllies)
    BasicTypeMACRO(IsHelpsAllies, assistance, 1, IsHelpsNobody)
    BasicTypeMACRO(IsHelpsFriendsAndAllies, assistance, 2, IsHelpsNobody)

    BasicTypeMACRO(IsStone, impactType, 0, IsDirt)
    BasicTypeMACRO(IsDirt, impactType, 1, IsStone)
    BasicTypeMACRO(IsGrass, impactType, 2, IsStone)
    BasicTypeMACRO(IsGlass, impactType, 3, IsStone)
    BasicTypeMACRO(IsMetal, impactType, 4, IsStone)
    BasicTypeMACRO(IsWood, impactType, 5, IsStone)
    BasicTypeMACRO(IsOrganic, impactType, 6, IsStone)
    BasicTypeMACRO(IsCloth, impactType, 7, IsStone)
    BasicTypeMACRO(IsWater, impactType, 8, IsStone)
    BasicTypeMACRO(IsHollowMetal, impactType, 9, IsStone)
    BasicTypeMACRO(IsOrganicBug, impactType, 10, IsStone)
    BasicTypeMACRO(IsOrganicGlow, impactType, 11, IsStone)
    copyattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                           'boundX2', 'boundY2', 'boundZ2',
                                           'full', 'modPath', 'modb', 'modt_p',
                                           'altTextures_list', 'modelFlags',
                                           'flags', 'fatigue', 'barterGold',
                                           'level', 'calcMin', 'calcMax',
                                           'speedMult', 'karma', 'dispBase',
                                           'templateFlags', 'factions_list',
                                           'deathItem', 'voice', 'template',
                                           'race', 'actorEffects', 'unarmedEffect',
                                           'unarmedAnim', 'destructable_list',
                                           'script', 'items_list', 'aggression',
                                           'confidence', 'energyLevel',
                                           'responsibility', 'mood',
                                           'services', 'trainSkill', 'trainLevel',
                                           'assistance', 'aggroFlags',
                                           'aggroRadius', 'aiPackages', 'iclass',
                                           'baseHealth', 'strength', 'perception',
                                           'endurance', 'charisma', 'intelligence',
                                           'agility', 'luck', 'barter', 'bigGuns',
                                           'energy', 'explosives', 'lockpick',
                                           'medicine', 'melee', 'repair',
                                           'science', 'guns', 'sneak', 'speech',
                                           'survival', 'unarmed', 'barterBoost',
                                           'bigGunsBoost', 'energyBoost',
                                           'explosivesBoost', 'lockpickBoost',
                                           'medicineBoost', 'meleeBoost',
                                           'repairBoost', 'scienceBoost',
                                           'gunsBoost', 'sneakBoost', 'speechBoost',
                                           'survivalBoost', 'unarmedBoost',
                                           'headParts', 'hair', 'hairLength', 'eyes',
                                           'hairRed', 'hairGreen', 'hairBlue',
                                           'combatStyle', 'impactType', 'fggs_p',
                                           'fgga_p', 'fgts_p', 'unknown',
                                           'height', 'weight']
    exportattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                             'boundX2', 'boundY2', 'boundZ2',
                                             'full', 'modPath', 'modb',
                                             'altTextures_list', 'modelFlags',
                                             'flags', 'fatigue', 'barterGold',
                                             'level', 'calcMin', 'calcMax',
                                             'speedMult', 'karma', 'dispBase',
                                             'templateFlags', 'factions_list',
                                             'deathItem', 'voice', 'template',
                                             'race', 'actorEffects', 'unarmedEffect',
                                             'unarmedAnim', 'destructable_list',
                                             'script', 'items_list', 'aggression',
                                             'confidence', 'energyLevel',
                                             'responsibility', 'mood',
                                             'services', 'trainSkill', 'trainLevel',
                                             'assistance', 'aggroFlags',
                                             'aggroRadius', 'aiPackages', 'iclass',
                                             'baseHealth', 'strength', 'perception',
                                             'endurance', 'charisma', 'intelligence',
                                             'agility', 'luck', 'barter', 'bigGuns',
                                             'energy', 'explosives', 'lockpick',
                                             'medicine', 'melee', 'repair',
                                             'science', 'guns', 'sneak', 'speech',
                                             'survival', 'unarmed', 'barterBoost',
                                             'bigGunsBoost', 'energyBoost',
                                             'explosivesBoost', 'lockpickBoost',
                                             'medicineBoost', 'meleeBoost',
                                             'repairBoost', 'scienceBoost',
                                             'gunsBoost', 'sneakBoost', 'speechBoost',
                                             'survivalBoost', 'unarmedBoost',
                                             'headParts', 'hair', 'hairLength', 'eyes',
                                             'hairRed', 'hairGreen', 'hairBlue',
                                             'combatStyle', 'impactType',
                                             'unknown',
                                             'height', 'weight']# 'fggs_p', 'fgga_p', 'fgts_p',  'modt_p',

class FnvCREARecord(FnvBaseRecord):
    _Type = 'CREA'
    def mergeFilter(self,modSet):
        """Filter out items that don't come from specified modSet.
        Filters items."""
        self.items = [x for x in self.items if x.item[0] in modSet]
        return True

    class SoundType(ListComponent):
        class Sound(ListX2Component):
            FORMID_LISTX2MACRO(sound, 1)
            UINT8_LISTX2MACRO(chance, 2)
            exportattrs = copyattrs = ['sound', 'chance']

        UINT32_TYPE_LISTMACRO(soundType, 1)
        LIST_LISTMACRO(sounds, 2, self.Sound)

        BasicTypeMACRO(IsLeftFoot, soundType, 0, IsRightFoot)
        BasicTypeMACRO(IsRightFoot, soundType, 1, IsLeftFoot)
        BasicTypeMACRO(IsLeftBackFoot, soundType, 2, IsLeftFoot)
        BasicTypeMACRO(IsRightBackFoot, soundType, 3, IsLeftFoot)
        BasicTypeMACRO(IsIdle, soundType, 4, IsLeftFoot)
        BasicTypeMACRO(IsAware, soundType, 5, IsLeftFoot)
        BasicTypeMACRO(IsAttack, soundType, 6, IsLeftFoot)
        BasicTypeMACRO(IsHit, soundType, 7, IsLeftFoot)
        BasicTypeMACRO(IsDeath, soundType, 8, IsLeftFoot)
        BasicTypeMACRO(IsWeapon, soundType, 9, IsLeftFoot)
        BasicTypeMACRO(IsMovementLoop, soundType, 10, IsLeftFoot)
        BasicTypeMACRO(IsConsciousLoop, soundType, 11, IsLeftFoot)
        BasicTypeMACRO(IsAuxiliary1, soundType, 12, IsLeftFoot)
        BasicTypeMACRO(IsAuxiliary2, soundType, 13, IsLeftFoot)
        BasicTypeMACRO(IsAuxiliary3, soundType, 14, IsLeftFoot)
        BasicTypeMACRO(IsAuxiliary4, soundType, 15, IsLeftFoot)
        BasicTypeMACRO(IsAuxiliary5, soundType, 16, IsLeftFoot)
        BasicTypeMACRO(IsAuxiliary6, soundType, 17, IsLeftFoot)
        BasicTypeMACRO(IsAuxiliary7, soundType, 18, IsLeftFoot)
        BasicTypeMACRO(IsAuxiliary8, soundType, 19, IsLeftFoot)
        BasicTypeMACRO(IsJump, soundType, 20, IsLeftFoot)
        BasicTypeMACRO(IsPlayRandomLoop, soundType, 21, IsLeftFoot)
        exportattrs = copyattrs = ['soundType', 'sounds_list']

    SINT16_MACRO(boundX1, 7)
    SINT16_MACRO(boundY1, 8)
    SINT16_MACRO(boundZ1, 9)
    SINT16_MACRO(boundX2, 10)
    SINT16_MACRO(boundY2, 11)
    SINT16_MACRO(boundZ2, 12)
    STRING_MACRO(full, 13)
    ISTRING_MACRO(modPath, 14)
    FLOAT32_MACRO(modb, 15)
    UINT8_ARRAY_MACRO(modt_p, 16)

    LIST_MACRO(altTextures, 17, FNVAltTexture)
    UINT8_FLAG_MACRO(modelFlags, 18)
    FORMID_ARRAY_MACRO(actorEffects, 19)
    FORMID_MACRO(unarmedEffect, 20)
    UINT16_TYPE_MACRO(unarmedAnim, 21)
    ISTRING_ARRAY_MACRO(bodyParts, 22)
    UINT8_ARRAY_MACRO(nift_p, 23)
    UINT32_FLAG_MACRO(flags, 24)
    UINT16_MACRO(fatigue, 25)
    UINT16_MACRO(barterGold, 26)
    SINT16_MACRO(level, 27)
    UINT16_MACRO(calcMin, 28)
    UINT16_MACRO(calcMax, 29)
    UINT16_MACRO(speedMult, 30)
    FLOAT32_MACRO(karma, 31)
    SINT16_MACRO(dispBase, 32)
    UINT16_FLAG_MACRO(templateFlags, 33)
    LIST_MACRO(factions, 34, Faction)
    FORMID_MACRO(deathItem, 35)
    FORMID_MACRO(voice, 36)
    FORMID_MACRO(template, 37)
    GroupedValuesMACRO(destructable, 38, FNVDestructable)
    FORMID_MACRO(script, 43)

    LIST_MACRO(items, 44, FNVItem)
    UINT8_TYPE_MACRO(aggression, 45)
    UINT8_TYPE_MACRO(confidence, 46)
    UINT8_MACRO(energyLevel, 47)
    UINT8_MACRO(responsibility, 48)
    UINT8_TYPE_MACRO(mood, 49)
    UINT8_ARRAY_MACRO(unused1, 50, 3)
    UINT32_FLAG_MACRO(services, 51)
    SINT8_TYPE_MACRO(trainSkill, 52)
    UINT8_MACRO(trainLevel, 53)
    UINT8_TYPE_MACRO(assistance, 54)
    UINT8_FLAG_MACRO(aggroFlags, 55)
    SINT32_MACRO(aggroRadius, 56)
    FORMID_ARRAY_MACRO(aiPackages, 57)
    ISTRING_ARRAY_MACRO(animations, 58)
    UINT8_TYPE_MACRO(creatureType, 59)
    UINT8_MACRO(combat, 60)
    UINT8_MACRO(magic, 61)
    UINT8_MACRO(stealth, 62)
    UINT16_MACRO(health, 63)
    UINT8_ARRAY_MACRO(unused2, 64, 2)
    SINT16_MACRO(attackDamage, 65)
    UINT8_MACRO(strength, 66)
    UINT8_MACRO(perception, 67)
    UINT8_MACRO(endurance, 68)
    UINT8_MACRO(charisma, 69)
    UINT8_MACRO(intelligence, 70)
    UINT8_MACRO(agility, 71)
    UINT8_MACRO(luck, 72)
    UINT8_MACRO(attackReach, 73)
    FORMID_MACRO(combatStyle, 74)
    FORMID_MACRO(partData, 75)
    FLOAT32_MACRO(turningSpeed, 76)
    FLOAT32_MACRO(baseScale, 77)
    FLOAT32_MACRO(footWeight, 78)
    UINT32_TYPE_MACRO(impactType, 79)
    UINT32_MACRO(soundLevel, 80)
    FORMID_MACRO(inheritsSoundsFrom, 81)

    LIST_MACRO(soundTypes, 82, SoundType)
    FORMID_MACRO(impactData, 83)
    FORMID_MACRO(meleeList, 84)

    BasicFlagMACRO(IsBiped, flags, 0x00000001)
    BasicFlagMACRO(IsEssential, flags, 0x00000002)
    BasicFlagMACRO(IsWeaponAndShield, flags, 0x00000004)
    BasicFlagMACRO(IsRespawn, flags, 0x00000008)
    BasicFlagMACRO(IsSwims, flags, 0x00000010)
    BasicFlagMACRO(IsFlies, flags, 0x00000020)
    BasicFlagMACRO(IsWalks, flags, 0x00000040)
    BasicFlagMACRO(IsPCLevelOffset, flags, 0x00000080)
    BasicFlagMACRO(IsUnknown1, flags, 0x00000100)
    BasicFlagMACRO(IsNoLowLevel, flags, 0x00000200)
    BasicInvertedFlagMACRO(IsLowLevel, IsNoLowLevel)
    BasicFlagMACRO(IsNoBloodSpray, flags, 0x00000800)
    BasicInvertedFlagMACRO(IsBloodSpray, IsNoBloodSpray)
    BasicFlagMACRO(IsNoBloodDecal, flags, 0x00001000)
    BasicInvertedFlagMACRO(IsBloodDecal, IsNoBloodDecal)
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
    BasicFlagMACRO(IsNoVATSMelee, flags, 0x00100000)
    BasicInvertedFlagMACRO(IsVATSMelee, IsNoVATSMelee)
    BasicFlagMACRO(IsAllowPCDialogue, flags, 0x00200000)
    BasicFlagMACRO(IsCantOpenDoors, flags, 0x00400000)
    BasicInvertedFlagMACRO(IsCanOpenDoors, IsCantOpenDoors)
    BasicFlagMACRO(IsImmobile, flags, 0x00800000)
    BasicFlagMACRO(IsTiltFrontBack, flags, 0x01000000)
    BasicFlagMACRO(IsTiltLeftRight, flags, 0x02000000)
    BasicFlagMACRO(IsNoKnockdowns, flags, 0x03000000)
    BasicInvertedFlagMACRO(IsKnockdowns, IsNoKnockdowns)
    BasicFlagMACRO(IsNotPushable, flags, 0x08000000)
    BasicInvertedFlagMACRO(IsPushable, IsNotPushable)
    BasicFlagMACRO(IsAllowPickpocket, flags, 0x10000000)
    BasicFlagMACRO(IsGhost, flags, 0x20000000)
    BasicFlagMACRO(IsNoHeadTracking, flags, 0x40000000)
    BasicInvertedFlagMACRO(IsHeadTracking, IsNoHeadTracking)
    BasicFlagMACRO(IsInvulnerable, flags, 0x80000000)

    BasicFlagMACRO(IsUseTraits, templateFlags, 0x00000001)
    BasicFlagMACRO(IsUseStats, templateFlags, 0x00000002)
    BasicFlagMACRO(IsUseFactions, templateFlags, 0x00000004)
    BasicFlagMACRO(IsUseAEList, templateFlags, 0x00000008)
    BasicFlagMACRO(IsUseAIData, templateFlags, 0x00000010)
    BasicFlagMACRO(IsUseAIPackages, templateFlags, 0x00000020)
    BasicFlagMACRO(IsUseModelAnim, templateFlags, 0x00000040)
    BasicFlagMACRO(IsUseBaseData, templateFlags, 0x00000080)
    BasicFlagMACRO(IsUseInventory, templateFlags, 0x00000100)
    BasicFlagMACRO(IsUseScript, templateFlags, 0x00000200)

    BasicFlagMACRO(IsAggroRadiusBehavior, aggroFlags, 0x01)

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

    BasicFlagMACRO(IsHead, modelFlags, 0x01)
    BasicFlagMACRO(IsTorso, modelFlags, 0x02)
    BasicFlagMACRO(IsRightHand, modelFlags, 0x04)
    BasicFlagMACRO(IsLeftHand, modelFlags, 0x08)

    BasicTypeMACRO(IsAnimal, creatureType, 0, IsMutatedAnimal)
    BasicTypeMACRO(IsMutatedAnimal, creatureType, 1, IsAnimal)
    BasicTypeMACRO(IsMutatedInsect, creatureType, 2, IsAnimal)
    BasicTypeMACRO(IsAbomination, creatureType, 3, IsAnimal)
    BasicTypeMACRO(IsSuperMutant, creatureType, 4, IsAnimal)
    BasicTypeMACRO(IsFeralGhoul, creatureType, 5, IsAnimal)
    BasicTypeMACRO(IsRobot, creatureType, 6, IsAnimal)
    BasicTypeMACRO(IsGiant, creatureType, 7, IsAnimal)

    BasicTypeMACRO(IsLoud, soundLevel, 0, IsNormal)
    BasicTypeMACRO(IsNormal, soundLevel, 1, IsLoud)
    BasicTypeMACRO(IsSilent, soundLevel, 2, IsLoud)

    BasicTypeMACRO(IsUnaggressive, aggression, 0, IsAggressive)
    BasicTypeMACRO(IsAggressive, aggression, 1, IsUnaggressive)
    BasicTypeMACRO(IsVeryAggressive, aggression, 2, IsUnaggressive)
    BasicTypeMACRO(IsFrenzied, aggression, 3, IsUnaggressive)

    BasicTypeMACRO(IsCowardly, confidence, 0, IsCautious)
    BasicTypeMACRO(IsCautious, confidence, 1, IsCowardly)
    BasicTypeMACRO(IsAverage, confidence, 2, IsCowardly)
    BasicTypeMACRO(IsBrave, confidence, 3, IsCowardly)
    BasicTypeMACRO(IsFoolhardy, confidence, 4, IsCowardly)

    BasicTypeMACRO(IsNeutral, mood, 0, IsAfraid)
    BasicTypeMACRO(IsAfraid, mood, 1, IsNeutral)
    BasicTypeMACRO(IsAnnoyed, mood, 2, IsNeutral)
    BasicTypeMACRO(IsCocky, mood, 3, IsNeutral)
    BasicTypeMACRO(IsDrugged, mood, 4, IsNeutral)
    BasicTypeMACRO(IsPleasant, mood, 5, IsNeutral)
    BasicTypeMACRO(IsAngry, mood, 6, IsNeutral)
    BasicTypeMACRO(IsSad, mood, 7, IsNeutral)

    BasicTypeMACRO(IsHelpsNobody, assistance, 0, IsHelpsAllies)
    BasicTypeMACRO(IsHelpsAllies, assistance, 1, IsHelpsNobody)
    BasicTypeMACRO(IsHelpsFriendsAndAllies, assistance, 2, IsHelpsNobody)

    BasicTypeMACRO(IsStone, impactType, 0, IsDirt)
    BasicTypeMACRO(IsDirt, impactType, 1, IsStone)
    BasicTypeMACRO(IsGrass, impactType, 2, IsStone)
    BasicTypeMACRO(IsGlass, impactType, 3, IsStone)
    BasicTypeMACRO(IsMetal, impactType, 4, IsStone)
    BasicTypeMACRO(IsWood, impactType, 5, IsStone)
    BasicTypeMACRO(IsOrganic, impactType, 6, IsStone)
    BasicTypeMACRO(IsCloth, impactType, 7, IsStone)
    BasicTypeMACRO(IsWater, impactType, 8, IsStone)
    BasicTypeMACRO(IsHollowMetal, impactType, 9, IsStone)
    BasicTypeMACRO(IsOrganicBug, impactType, 10, IsStone)
    BasicTypeMACRO(IsOrganicGlow, impactType, 11, IsStone)

    BasicTypeMACRO(IsAttackLeft, unarmedAnim, 26, IsAttackLeftUp)
    BasicTypeMACRO(IsAttackLeftUp, unarmedAnim, 27, IsAttackLeft)
    BasicTypeMACRO(IsAttackLeftDown, unarmedAnim, 28, IsAttackLeft)
    BasicTypeMACRO(IsAttackLeftIS, unarmedAnim, 29, IsAttackLeft)
    BasicTypeMACRO(IsAttackLeftISUp, unarmedAnim, 30, IsAttackLeft)
    BasicTypeMACRO(IsAttackLeftISDown, unarmedAnim, 31, IsAttackLeft)
    BasicTypeMACRO(IsAttackRight, unarmedAnim, 32, IsAttackLeft)
    BasicTypeMACRO(IsAttackRightUp, unarmedAnim, 33, IsAttackLeft)
    BasicTypeMACRO(IsAttackRightDown, unarmedAnim, 34, IsAttackLeft)
    BasicTypeMACRO(IsAttackRightIS, unarmedAnim, 35, IsAttackLeft)
    BasicTypeMACRO(IsAttackRightISUp, unarmedAnim, 36, IsAttackLeft)
    BasicTypeMACRO(IsAttackRightISDown, unarmedAnim, 37, IsAttackLeft)
    BasicTypeMACRO(IsAttack3, unarmedAnim, 38, IsAttackLeft)
    BasicTypeMACRO(IsAttack3Up, unarmedAnim, 39, IsAttackLeft)
    BasicTypeMACRO(IsAttack3Down, unarmedAnim, 40, IsAttackLeft)
    BasicTypeMACRO(IsAttack3IS, unarmedAnim, 41, IsAttackLeft)
    BasicTypeMACRO(IsAttack3ISUp, unarmedAnim, 42, IsAttackLeft)
    BasicTypeMACRO(IsAttack3ISDown, unarmedAnim, 43, IsAttackLeft)
    BasicTypeMACRO(IsAttack4, unarmedAnim, 44, IsAttackLeft)
    BasicTypeMACRO(IsAttack4Up, unarmedAnim, 45, IsAttackLeft)
    BasicTypeMACRO(IsAttack4Down, unarmedAnim, 46, IsAttackLeft)
    BasicTypeMACRO(IsAttack4IS, unarmedAnim, 47, IsAttackLeft)
    BasicTypeMACRO(IsAttack4ISUp, unarmedAnim, 48, IsAttackLeft)
    BasicTypeMACRO(IsAttack4ISDown, unarmedAnim, 49, IsAttackLeft)
    BasicTypeMACRO(IsAttack5, unarmedAnim, 50, IsAttackLeft)
    BasicTypeMACRO(IsAttack5Up, unarmedAnim, 51, IsAttackLeft)
    BasicTypeMACRO(IsAttack5Down, unarmedAnim, 52, IsAttackLeft)
    BasicTypeMACRO(IsAttack5IS, unarmedAnim, 53, IsAttackLeft)
    BasicTypeMACRO(IsAttack5ISUp, unarmedAnim, 54, IsAttackLeft)
    BasicTypeMACRO(IsAttack5ISDown, unarmedAnim, 55, IsAttackLeft)
    BasicTypeMACRO(IsAttack6, unarmedAnim, 56, IsAttackLeft)
    BasicTypeMACRO(IsAttack6Up, unarmedAnim, 57, IsAttackLeft)
    BasicTypeMACRO(IsAttack6Down, unarmedAnim, 58, IsAttackLeft)
    BasicTypeMACRO(IsAttack6IS, unarmedAnim, 59, IsAttackLeft)
    BasicTypeMACRO(IsAttack6ISUp, unarmedAnim, 60, IsAttackLeft)
    BasicTypeMACRO(IsAttack6ISDown, unarmedAnim, 61, IsAttackLeft)
    BasicTypeMACRO(IsAttack7, unarmedAnim, 62, IsAttackLeft)
    BasicTypeMACRO(IsAttack7Up, unarmedAnim, 63, IsAttackLeft)
    BasicTypeMACRO(IsAttack7Down, unarmedAnim, 64, IsAttackLeft)
    BasicTypeMACRO(IsAttack7IS, unarmedAnim, 65, IsAttackLeft)
    BasicTypeMACRO(IsAttack7ISUp, unarmedAnim, 66, IsAttackLeft)
    BasicTypeMACRO(IsAttack7ISDown, unarmedAnim, 67, IsAttackLeft)
    BasicTypeMACRO(IsAttack8, unarmedAnim, 68, IsAttackLeft)
    BasicTypeMACRO(IsAttack8Up, unarmedAnim, 69, IsAttackLeft)
    BasicTypeMACRO(IsAttack8Down, unarmedAnim, 70, IsAttackLeft)
    BasicTypeMACRO(IsAttack8IS, unarmedAnim, 71, IsAttackLeft)
    BasicTypeMACRO(IsAttack8ISUp, unarmedAnim, 72, IsAttackLeft)
    BasicTypeMACRO(IsAttack8ISDown, unarmedAnim, 73, IsAttackLeft)
    BasicTypeMACRO(IsAttackLoop, unarmedAnim, 74, IsAttackLeft)
    BasicTypeMACRO(IsAttackLoopUp, unarmedAnim, 75, IsAttackLeft)
    BasicTypeMACRO(IsAttackLoopDown, unarmedAnim, 76, IsAttackLeft)
    BasicTypeMACRO(IsAttackLoopIS, unarmedAnim, 77, IsAttackLeft)
    BasicTypeMACRO(IsAttackLoopISUp, unarmedAnim, 78, IsAttackLeft)
    BasicTypeMACRO(IsAttackLoopISDown, unarmedAnim, 79, IsAttackLeft)
    BasicTypeMACRO(IsAttackSpin, unarmedAnim, 80, IsAttackLeft)
    BasicTypeMACRO(IsAttackSpinUp, unarmedAnim, 81, IsAttackLeft)
    BasicTypeMACRO(IsAttackSpinDown, unarmedAnim, 82, IsAttackLeft)
    BasicTypeMACRO(IsAttackSpinIS, unarmedAnim, 83, IsAttackLeft)
    BasicTypeMACRO(IsAttackSpinISUp, unarmedAnim, 84, IsAttackLeft)
    BasicTypeMACRO(IsAttackSpinISDown, unarmedAnim, 85, IsAttackLeft)
    BasicTypeMACRO(IsAttackSpin2, unarmedAnim, 86, IsAttackLeft)
    BasicTypeMACRO(IsAttackSpin2Up, unarmedAnim, 87, IsAttackLeft)
    BasicTypeMACRO(IsAttackSpin2Down, unarmedAnim, 88, IsAttackLeft)
    BasicTypeMACRO(IsAttackSpin2IS, unarmedAnim, 89, IsAttackLeft)
    BasicTypeMACRO(IsAttackSpin2ISUp, unarmedAnim, 90, IsAttackLeft)
    BasicTypeMACRO(IsAttackSpin2ISDown, unarmedAnim, 91, IsAttackLeft)
    BasicTypeMACRO(IsAttackPower, unarmedAnim, 92, IsAttackLeft)
    BasicTypeMACRO(IsAttackForwardPower, unarmedAnim, 93, IsAttackLeft)
    BasicTypeMACRO(IsAttackBackPower, unarmedAnim, 94, IsAttackLeft)
    BasicTypeMACRO(IsAttackLeftPower, unarmedAnim, 95, IsAttackLeft)
    BasicTypeMACRO(IsAttackRightPower, unarmedAnim, 96, IsAttackLeft)
    BasicTypeMACRO(IsPlaceMine, unarmedAnim, 97, IsAttackLeft)
    BasicTypeMACRO(IsPlaceMineUp, unarmedAnim, 98, IsAttackLeft)
    BasicTypeMACRO(IsPlaceMineDown, unarmedAnim, 99, IsAttackLeft)
    BasicTypeMACRO(IsPlaceMineIS, unarmedAnim, 100, IsAttackLeft)
    BasicTypeMACRO(IsPlaceMineISUp, unarmedAnim, 101, IsAttackLeft)
    BasicTypeMACRO(IsPlaceMineISDown, unarmedAnim, 102, IsAttackLeft)
    BasicTypeMACRO(IsPlaceMine2, unarmedAnim, 103, IsAttackLeft)
    BasicTypeMACRO(IsPlaceMine2Up, unarmedAnim, 104, IsAttackLeft)
    BasicTypeMACRO(IsPlaceMine2Down, unarmedAnim, 105, IsAttackLeft)
    BasicTypeMACRO(IsPlaceMine2IS, unarmedAnim, 106, IsAttackLeft)
    BasicTypeMACRO(IsPlaceMine2ISUp, unarmedAnim, 107, IsAttackLeft)
    BasicTypeMACRO(IsPlaceMine2ISDown, unarmedAnim, 108, IsAttackLeft)
    BasicTypeMACRO(IsAttackThrow, unarmedAnim, 109, IsAttackLeft)
    BasicTypeMACRO(IsAttackThrowUp, unarmedAnim, 110, IsAttackLeft)
    BasicTypeMACRO(IsAttackThrowDown, unarmedAnim, 111, IsAttackLeft)
    BasicTypeMACRO(IsAttackThrowIS, unarmedAnim, 112, IsAttackLeft)
    BasicTypeMACRO(IsAttackThrowISUp, unarmedAnim, 113, IsAttackLeft)
    BasicTypeMACRO(IsAttackThrowISDown, unarmedAnim, 114, IsAttackLeft)
    BasicTypeMACRO(IsAttackThrow2, unarmedAnim, 115, IsAttackLeft)
    BasicTypeMACRO(IsAttackThrow2Up, unarmedAnim, 116, IsAttackLeft)
    BasicTypeMACRO(IsAttackThrow2Down, unarmedAnim, 117, IsAttackLeft)
    BasicTypeMACRO(IsAttackThrow2IS, unarmedAnim, 118, IsAttackLeft)
    BasicTypeMACRO(IsAttackThrow2ISUp, unarmedAnim, 119, IsAttackLeft)
    BasicTypeMACRO(IsAttackThrow2ISDown, unarmedAnim, 120, IsAttackLeft)
    BasicTypeMACRO(IsAttackThrow3, unarmedAnim, 121, IsAttackLeft)
    BasicTypeMACRO(IsAttackThrow3Up, unarmedAnim, 122, IsAttackLeft)
    BasicTypeMACRO(IsAttackThrow3Down, unarmedAnim, 123, IsAttackLeft)
    BasicTypeMACRO(IsAttackThrow3IS, unarmedAnim, 124, IsAttackLeft)
    BasicTypeMACRO(IsAttackThrow3ISUp, unarmedAnim, 125, IsAttackLeft)
    BasicTypeMACRO(IsAttackThrow3ISDown, unarmedAnim, 126, IsAttackLeft)
    BasicTypeMACRO(IsAttackThrow4, unarmedAnim, 127, IsAttackLeft)
    BasicTypeMACRO(IsAttackThrow4Up, unarmedAnim, 128, IsAttackLeft)
    BasicTypeMACRO(IsAttackThrow4Down, unarmedAnim, 129, IsAttackLeft)
    BasicTypeMACRO(IsAttackThrow4IS, unarmedAnim, 130, IsAttackLeft)
    BasicTypeMACRO(IsAttackThrow4ISUp, unarmedAnim, 131, IsAttackLeft)
    BasicTypeMACRO(IsAttackThrow4ISDown, unarmedAnim, 132, IsAttackLeft)
    BasicTypeMACRO(IsAttackThrow5, unarmedAnim, 133, IsAttackLeft)
    BasicTypeMACRO(IsAttackThrow5Up, unarmedAnim, 134, IsAttackLeft)
    BasicTypeMACRO(IsAttackThrow5Down, unarmedAnim, 135, IsAttackLeft)
    BasicTypeMACRO(IsAttackThrow5IS, unarmedAnim, 136, IsAttackLeft)
    BasicTypeMACRO(IsAttackThrow5ISUp, unarmedAnim, 137, IsAttackLeft)
    BasicTypeMACRO(IsAttackThrow5ISDown, unarmedAnim, 138, IsAttackLeft)
    BasicTypeMACRO(IsPipBoy, unarmedAnim, 167, IsAttackLeft)
    BasicTypeMACRO(IsPipBoyChild, unarmedAnim, 178, IsAttackLeft)
    BasicTypeMACRO(IsANY, unarmedAnim, 255, IsAttackLeft)
    copyattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                           'boundX2', 'boundY2', 'boundZ2',
                                           'full', 'modPath', 'modb', 'modt_p',
                                           'altTextures_list', 'modelFlags',
                                           'actorEffects', 'unarmedEffect',
                                           'unarmedAnim', 'bodyParts', 'nift_p',
                                           'flags', 'fatigue', 'barterGold',
                                           'level', 'calcMin', 'calcMax',
                                           'speedMult', 'karma', 'dispBase',
                                           'templateFlags', 'factions_list',
                                           'deathItem', 'voice', 'template',
                                           'destructable_list', 'script',
                                           'items_list', 'aggression',
                                           'confidence', 'energyLevel',
                                           'responsibility', 'mood',
                                           'services', 'trainSkill',
                                           'trainLevel', 'assistance',
                                           'aggroFlags', 'aggroRadius',
                                           'aiPackages', 'animations',
                                           'creatureType', 'combat', 'magic',
                                           'stealth', 'health', 'attackDamage',
                                           'strength', 'perception',
                                           'endurance', 'charisma',
                                           'intelligence', 'agility', 'luck',
                                           'attackReach', 'combatStyle',
                                           'partData', 'turningSpeed',
                                           'baseScale', 'footWeight',
                                           'impactType', 'soundLevel',
                                           'inheritsSoundsFrom',
                                           'soundTypes_list', 'impactData',
                                           'meleeList']
    exportattrs  = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                              'boundX2', 'boundY2', 'boundZ2',
                                              'full', 'modPath', 'modb',
                                              'altTextures_list', 'modelFlags',
                                              'actorEffects', 'unarmedEffect',
                                              'unarmedAnim', 'bodyParts',
                                              'flags', 'fatigue', 'barterGold',
                                              'level', 'calcMin', 'calcMax',
                                              'speedMult', 'karma', 'dispBase',
                                              'templateFlags', 'factions_list',
                                              'deathItem', 'voice', 'template',
                                              'destructable_list', 'script',
                                              'items_list', 'aggression',
                                              'confidence', 'energyLevel',
                                              'responsibility', 'mood',
                                              'services', 'trainSkill',
                                              'trainLevel', 'assistance',
                                              'aggroFlags', 'aggroRadius',
                                              'aiPackages', 'animations',
                                              'creatureType', 'combat', 'magic',
                                              'stealth', 'health', 'attackDamage',
                                              'strength', 'perception',
                                              'endurance', 'charisma',
                                              'intelligence', 'agility', 'luck',
                                              'attackReach', 'combatStyle',
                                              'partData', 'turningSpeed',
                                              'baseScale', 'footWeight',
                                              'impactType', 'soundLevel',
                                              'inheritsSoundsFrom',
                                              'soundTypes_list', 'impactData',
                                              'meleeList']# 'modt_p', 'nift_p',

class FnvLVLCRecord(FnvBaseRecord):
    _Type = 'LVLC'
    def mergeFilter(self,modSet):
        """Filter out items that don't come from specified modSet."""
        self.entries = [entry for entry in self.entries if entry.listId[0] in modSet]
        return True

    class Entry(ListComponent):
        SINT16_LISTMACRO(level, 1)
        UINT8_ARRAY_LISTMACRO(unused1, 2, 2)
        FORMID_LISTMACRO(listId, 3)
        SINT16_LISTMACRO(count, 4)
        UINT8_ARRAY_LISTMACRO(unused2, 5, 2)
        FORMID_LISTMACRO(owner, 6)
        UNKNOWN_OR_FORMID_OR_UINT32_LISTMACRO(globalOrRank, 7)
        FLOAT32_LISTMACRO(condition, 8)
        exportattrs = copyattrs = ['level', 'listId', 'count', 'owner', 'globalOrRank', 'condition']

    SINT16_MACRO(boundX1, 7)
    SINT16_MACRO(boundY1, 8)
    SINT16_MACRO(boundZ1, 9)
    SINT16_MACRO(boundX2, 10)
    SINT16_MACRO(boundY2, 11)
    SINT16_MACRO(boundZ2, 12)
    UINT8_MACRO(chanceNone, 13)
    UINT8_FLAG_MACRO(flags, 14)

    LIST_MACRO(entries, 15, self.Entry)
    ISTRING_MACRO(modPath, 16)
    FLOAT32_MACRO(modb, 17)
    UINT8_ARRAY_MACRO(modt_p, 18)

    LIST_MACRO(altTextures, 19, FNVAltTexture)
    UINT8_FLAG_MACRO(modelFlags, 20)

    BasicFlagMACRO(IsCalcFromAllLevels, flags, 0x00000001)
    BasicFlagMACRO(IsCalcForEachItem, flags, 0x00000002)
    BasicFlagMACRO(IsUseAll, flags, 0x00000004)

    BasicFlagMACRO(IsHead, modelFlags, 0x01)
    BasicFlagMACRO(IsTorso, modelFlags, 0x02)
    BasicFlagMACRO(IsRightHand, modelFlags, 0x04)
    BasicFlagMACRO(IsLeftHand, modelFlags, 0x08)
    copyattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                           'boundX2', 'boundY2', 'boundZ2',
                                           'chanceNone', 'flags',
                                           'entries_list', 'modPath',
                                           'modb', 'modt_p',
                                           'altTextures_list', 'modelFlags']
    exportattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                             'boundX2', 'boundY2', 'boundZ2',
                                             'chanceNone', 'flags',
                                             'entries_list', 'modPath',
                                             'modb',
                                             'altTextures_list', 'modelFlags']#'modt_p',

class FnvLVLNRecord(FnvBaseRecord):
    _Type = 'LVLN'
    def mergeFilter(self,modSet):
        """Filter out items that don't come from specified modSet."""
        self.entries = [entry for entry in self.entries if entry.listId[0] in modSet]
        return True

    class Entry(ListComponent):
        SINT16_LISTMACRO(level, 1)
        UINT8_ARRAY_LISTMACRO(unused1, 2, 2)
        FORMID_LISTMACRO(listId, 3)
        SINT16_LISTMACRO(count, 4)
        UINT8_ARRAY_LISTMACRO(unused2, 5, 2)
        FORMID_LISTMACRO(owner, 6)
        UNKNOWN_OR_FORMID_OR_UINT32_LISTMACRO(globalOrRank, 7)
        FLOAT32_LISTMACRO(condition, 8)
        exportattrs = copyattrs = ['level', 'listId', 'count', 'owner', 'globalOrRank', 'condition']

    SINT16_MACRO(boundX1, 7)
    SINT16_MACRO(boundY1, 8)
    SINT16_MACRO(boundZ1, 9)
    SINT16_MACRO(boundX2, 10)
    SINT16_MACRO(boundY2, 11)
    SINT16_MACRO(boundZ2, 12)
    UINT8_MACRO(chanceNone, 13)
    UINT8_FLAG_MACRO(flags, 14)

    LIST_MACRO(entries, 15, self.Entry)
    ISTRING_MACRO(modPath, 16)
    FLOAT32_MACRO(modb, 17)
    UINT8_ARRAY_MACRO(modt_p, 18)

    LIST_MACRO(altTextures, 19, FNVAltTexture)
    UINT8_FLAG_MACRO(modelFlags, 20)

    BasicFlagMACRO(IsCalcFromAllLevels, flags, 0x00000001)
    BasicFlagMACRO(IsCalcForEachItem, flags, 0x00000002)
    BasicFlagMACRO(IsUseAll, flags, 0x00000004)

    BasicFlagMACRO(IsHead, modelFlags, 0x01)
    BasicFlagMACRO(IsTorso, modelFlags, 0x02)
    BasicFlagMACRO(IsRightHand, modelFlags, 0x04)
    BasicFlagMACRO(IsLeftHand, modelFlags, 0x08)
    copyattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                           'boundX2', 'boundY2', 'boundZ2',
                                           'chanceNone', 'flags',
                                           'entries_list', 'modPath',
                                           'modb', 'modt_p',
                                           'altTextures_list', 'modelFlags']
    exportattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                             'boundX2', 'boundY2', 'boundZ2',
                                             'chanceNone', 'flags',
                                             'entries_list', 'modPath',
                                             'modb',
                                             'altTextures_list', 'modelFlags']#'modt_p',

class FnvKEYMRecord(FnvBaseRecord):
    _Type = 'KEYM'
    SINT16_MACRO(boundX1, 7)
    SINT16_MACRO(boundY1, 8)
    SINT16_MACRO(boundZ1, 9)
    SINT16_MACRO(boundX2, 10)
    SINT16_MACRO(boundY2, 11)
    SINT16_MACRO(boundZ2, 12)
    STRING_MACRO(full, 13)
    ISTRING_MACRO(modPath, 14)
    FLOAT32_MACRO(modb, 15)
    UINT8_ARRAY_MACRO(modt_p, 16)

    LIST_MACRO(altTextures, 17, FNVAltTexture)
    UINT8_FLAG_MACRO(modelFlags, 18)
    ISTRING_MACRO(iconPath, 19)
    ISTRING_MACRO(smallIconPath, 20)
    FORMID_MACRO(script, 21)
    GroupedValuesMACRO(destructable, 22, FNVDestructable)
    FORMID_MACRO(pickupSound, 27)
    FORMID_MACRO(dropSound, 28)
    SINT32_MACRO(value, 29)
    FLOAT32_MACRO(weight, 30)
    FORMID_MACRO(loopSound, 31)

    BasicFlagMACRO(IsHead, modelFlags, 0x01)
    BasicFlagMACRO(IsTorso, modelFlags, 0x02)
    BasicFlagMACRO(IsRightHand, modelFlags, 0x04)
    BasicFlagMACRO(IsLeftHand, modelFlags, 0x08)
    copyattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                           'boundX2', 'boundY2', 'boundZ2',
                                           'full', 'modPath', 'modb', 'modt_p',
                                           'altTextures_list', 'modelFlags',
                                           'iconPath', 'smallIconPath',
                                           'script', 'destructable_list',
                                           'pickupSound', 'dropSound',
                                           'value', 'weight', 'loopSound']
    exportattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                             'boundX2', 'boundY2', 'boundZ2',
                                             'full', 'modPath', 'modb',
                                             'altTextures_list', 'modelFlags',
                                             'iconPath', 'smallIconPath',
                                             'script', 'destructable_list',
                                             'pickupSound', 'dropSound',
                                             'value', 'weight', 'loopSound']# 'modt_p',

class FnvALCHRecord(FnvBaseRecord):
    _Type = 'ALCH'
    SINT16_MACRO(boundX1, 7)
    SINT16_MACRO(boundY1, 8)
    SINT16_MACRO(boundZ1, 9)
    SINT16_MACRO(boundX2, 10)
    SINT16_MACRO(boundY2, 11)
    SINT16_MACRO(boundZ2, 12)
    STRING_MACRO(full, 13)
    ISTRING_MACRO(modPath, 14)
    FLOAT32_MACRO(modb, 15)
    UINT8_ARRAY_MACRO(modt_p, 16)

    LIST_MACRO(altTextures, 17, FNVAltTexture)
    UINT8_FLAG_MACRO(modelFlags, 18)
    ISTRING_MACRO(iconPath, 19)
    ISTRING_MACRO(smallIconPath, 20)
    FORMID_MACRO(script, 21)
    SINT32_TYPE_MACRO(equipmentType, 22)
    FLOAT32_MACRO(weight, 23)
    SINT32_MACRO(value, 24)
    UINT8_FLAG_MACRO(flags, 25)
    UINT8_ARRAY_MACRO(unused1, 26, 3)

    FORMID_MACRO(withdrawalEffect, 27)
    FLOAT32_MACRO(addictionChance, 28)
    FORMID_MACRO(consumeSound, 29)

    LIST_MACRO(effects, 30, FNVEffect)
    GroupedValuesMACRO(destructable, 31, FNVDestructable)
    FORMID_MACRO(pickupSound, 36)
    FORMID_MACRO(dropSound, 37)

    BasicFlagMACRO(IsNoAutoCalc, flags, 0x00000001)
    BasicInvertedFlagMACRO(IsAutoCalc, IsNoAutoCalc)
    BasicFlagMACRO(IsFood, flags, 0x00000002)
    BasicFlagMACRO(IsMedicine, flags, 0x00000004)

    BasicFlagMACRO(IsHead, modelFlags, 0x01)
    BasicFlagMACRO(IsTorso, modelFlags, 0x02)
    BasicFlagMACRO(IsRightHand, modelFlags, 0x04)
    BasicFlagMACRO(IsLeftHand, modelFlags, 0x08)

    BasicTypeMACRO(IsNone, equipmentType, -1, IsBigGuns)
    BasicTypeMACRO(IsBigGuns, equipmentType, 0, IsNone)
    BasicTypeMACRO(IsEnergyWeapons, equipmentType, 1, IsNone)
    BasicTypeMACRO(IsSmallGuns, equipmentType, 2, IsNone)
    BasicTypeMACRO(IsMeleeWeapons, equipmentType, 3, IsNone)
    BasicTypeMACRO(IsUnarmedWeapon, equipmentType, 4, IsNone)
    BasicTypeMACRO(IsThrownWeapons, equipmentType, 5, IsNone)
    BasicTypeMACRO(IsMine, equipmentType, 6, IsNone)
    BasicTypeMACRO(IsBodyWear, equipmentType, 7, IsNone)
    BasicTypeMACRO(IsHeadWear, equipmentType, 8, IsNone)
    BasicTypeMACRO(IsHandWear, equipmentType, 9, IsNone)
    BasicTypeMACRO(IsChems, equipmentType, 10, IsNone)
    BasicTypeMACRO(IsStimpack, equipmentType, 11, IsNone)
    BasicTypeMACRO(IsEdible, equipmentType, 12, IsNone)
    BasicTypeMACRO(IsAlcohol, equipmentType, 13, IsNone)
    copyattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                           'boundX2', 'boundY2', 'boundZ2',
                                           'full', 'modPath', 'modb', 'modt_p',
                                           'altTextures_list', 'modelFlags',
                                           'iconPath', 'smallIconPath',
                                           'script', 'equipmentType', 'weight',
                                           'value', 'flags', 'withdrawalEffect',
                                           'addictionChance', 'consumeSound',
                                           'effects_list', 'destructable_list',
                                           'pickupSound', 'dropSound']
    exportattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                             'boundX2', 'boundY2', 'boundZ2',
                                             'full', 'modPath', 'modb',
                                             'altTextures_list', 'modelFlags',
                                             'iconPath', 'smallIconPath',
                                             'script', 'equipmentType', 'weight',
                                             'value', 'flags', 'withdrawalEffect',
                                             'addictionChance', 'consumeSound',
                                             'effects_list', 'destructable_list',
                                             'pickupSound', 'dropSound']# 'modt_p',

class FnvIDLMRecord(FnvBaseRecord):
    _Type = 'IDLM'
    SINT16_MACRO(boundX1, 7)
    SINT16_MACRO(boundY1, 8)
    SINT16_MACRO(boundZ1, 9)
    SINT16_MACRO(boundX2, 10)
    SINT16_MACRO(boundY2, 11)
    SINT16_MACRO(boundZ2, 12)
    UINT8_MACRO(flags, 13)
    UINT8_MACRO(count, 14)
    FLOAT32_MACRO(timer, 15)
    FORMID_ARRAY_MACRO(animations, 16)

    BasicFlagMACRO(IsRunInSequence, flags, 0x00000001)
    BasicFlagMACRO(IsDoOnce, flags, 0x00000004)
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                                         'boundX2', 'boundY2', 'boundZ2',
                                                         'flags', 'count', 'timer',
                                                         'animations']

class FnvNOTERecord(FnvBaseRecord):
    _Type = 'NOTE'
    SINT16_MACRO(boundX1, 7)
    SINT16_MACRO(boundY1, 8)
    SINT16_MACRO(boundZ1, 9)
    SINT16_MACRO(boundX2, 10)
    SINT16_MACRO(boundY2, 11)
    SINT16_MACRO(boundZ2, 12)
    STRING_MACRO(full, 13)
    ISTRING_MACRO(modPath, 14)
    FLOAT32_MACRO(modb, 15)
    UINT8_ARRAY_MACRO(modt_p, 16)

    LIST_MACRO(altTextures, 17, FNVAltTexture)
    UINT8_FLAG_MACRO(modelFlags, 18)
    ISTRING_MACRO(iconPath, 19)
    ISTRING_MACRO(smallIconPath, 20)
    FORMID_MACRO(pickupSound, 21)
    FORMID_MACRO(dropSound, 22)
    UINT8_TYPE_MACRO(noteType, 23)
    FORMID_ARRAY_MACRO(quests, 24)
    ISTRING_MACRO(texturePath, 25)
    FORMID_OR_STRING_MACRO(textOrTopic, 26) #Is a topic formID if IsVoice is true, otherwise text
    FORMID_MACRO(sound, 27)

    BasicTypeMACRO(IsSound, flags, 0, IsText)
    BasicTypeMACRO(IsText, flags, 1, IsSound)
    BasicTypeMACRO(IsImage, flags, 2, IsSound)
    BasicTypeMACRO(IsVoice, flags, 3, IsSound)

    BasicFlagMACRO(IsHead, modelFlags, 0x01)
    BasicFlagMACRO(IsTorso, modelFlags, 0x02)
    BasicFlagMACRO(IsRightHand, modelFlags, 0x04)
    BasicFlagMACRO(IsLeftHand, modelFlags, 0x08)
    copyattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                           'boundX2', 'boundY2', 'boundZ2',
                                           'full', 'modPath', 'modb', 'modt_p',
                                           'altTextures_list', 'modelFlags',
                                           'iconPath', 'smallIconPath',
                                           'pickupSound', 'dropSound',
                                           'noteType', 'quests', 'texturePath',
                                           'textOrTopic', 'sound']
    exportattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                             'boundX2', 'boundY2', 'boundZ2',
                                             'full', 'modPath', 'modb',
                                             'altTextures_list', 'modelFlags',
                                             'iconPath', 'smallIconPath',
                                             'pickupSound', 'dropSound',
                                             'noteType', 'quests', 'texturePath',
                                             'textOrTopic', 'sound']# 'modt_p',

class FnvCOBJRecord(FnvBaseRecord):
    _Type = 'COBJ'
    SINT16_MACRO(boundX1, 7)
    SINT16_MACRO(boundY1, 8)
    SINT16_MACRO(boundZ1, 9)
    SINT16_MACRO(boundX2, 10)
    SINT16_MACRO(boundY2, 11)
    SINT16_MACRO(boundZ2, 12)
    STRING_MACRO(full, 13)
    ISTRING_MACRO(modPath, 14)
    FLOAT32_MACRO(modb, 15)
    UINT8_ARRAY_MACRO(modt_p, 16)

    LIST_MACRO(altTextures, 17, FNVAltTexture)
    UINT8_FLAG_MACRO(modelFlags, 18)
    ISTRING_MACRO(iconPath, 19)
    ISTRING_MACRO(smallIconPath, 20)
    FORMID_MACRO(script, 21)
    FORMID_MACRO(pickupSound, 22)
    FORMID_MACRO(dropSound, 23)
    SINT32_MACRO(value, 24)
    FLOAT32_MACRO(weight, 25)

    BasicFlagMACRO(IsHead, modelFlags, 0x01)
    BasicFlagMACRO(IsTorso, modelFlags, 0x02)
    BasicFlagMACRO(IsRightHand, modelFlags, 0x04)
    BasicFlagMACRO(IsLeftHand, modelFlags, 0x08)
    copyattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                           'boundX2', 'boundY2', 'boundZ2',
                                           'full', 'modPath', 'modb', 'modt_p',
                                           'altTextures_list', 'modelFlags',
                                           'iconPath', 'smallIconPath',
                                           'script', 'pickupSound',
                                           'dropSound', 'value', 'weight']
    exportattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                             'boundX2', 'boundY2', 'boundZ2',
                                             'full', 'modPath', 'modb',
                                             'altTextures_list', 'modelFlags',
                                             'iconPath', 'smallIconPath',
                                             'script', 'pickupSound',
                                             'dropSound', 'value', 'weight']# 'modt_p',

class FnvPROJRecord(FnvBaseRecord):
    _Type = 'PROJ'
    SINT16_MACRO(boundX1, 7)
    SINT16_MACRO(boundY1, 8)
    SINT16_MACRO(boundZ1, 9)
    SINT16_MACRO(boundX2, 10)
    SINT16_MACRO(boundY2, 11)
    SINT16_MACRO(boundZ2, 12)
    STRING_MACRO(full, 13)
    ISTRING_MACRO(modPath, 14)
    FLOAT32_MACRO(modb, 15)
    UINT8_ARRAY_MACRO(modt_p, 16)

    LIST_MACRO(altTextures, 17, FNVAltTexture)
    UINT8_FLAG_MACRO(modelFlags, 18)
    GroupedValuesMACRO(destructable, 19, FNVDestructable)
    UINT16_FLAG_MACRO(flags, 24)
    UINT16_TYPE_MACRO(projType, 25)
    FLOAT32_MACRO(gravity, 26)
    FLOAT32_MACRO(speed, 27)
    FLOAT32_MACRO(range, 28)
    FORMID_MACRO(light, 29)
    FORMID_MACRO(flash, 30)
    FLOAT32_MACRO(tracerChance, 31)
    FLOAT32_MACRO(altExplProximityTrigger, 32)
    FLOAT32_MACRO(altExplProximityTimer, 33)
    FORMID_MACRO(explosion, 34)
    FORMID_MACRO(sound, 35)
    FLOAT32_MACRO(flashDuration, 36)
    FLOAT32_MACRO(fadeDuration, 37)
    FLOAT32_MACRO(impactForce, 38)
    FORMID_MACRO(soundCountdown, 39)
    FORMID_MACRO(soundDisable, 40)
    FORMID_MACRO(defaultWeaponSource, 41)
    FLOAT32_MACRO(rotX, 42)
    FLOAT32_MACRO(rotY, 43)
    FLOAT32_MACRO(rotZ, 44)
    FLOAT32_MACRO(bouncyMult, 45)
    ISTRING_MACRO(modelPath, 46)
    UINT8_ARRAY_MACRO(nam2_p, 47)
    UINT32_MACRO(soundLevel, 48)

    BasicFlagMACRO(IsHitscan, flags, 0x0001)
    BasicFlagMACRO(IsExplosion, flags, 0x0002)
    BasicFlagMACRO(IsAltTrigger, flags, 0x0004)
    BasicFlagMACRO(IsMuzzleFlash, flags, 0x0008)
    BasicFlagMACRO(IsDisableable, flags, 0x0020)
    BasicFlagMACRO(IsPickupable, flags, 0x0040)
    BasicFlagMACRO(IsSupersonic, flags, 0x0080)
    BasicFlagMACRO(IsPinsLimbs, flags, 0x0100)
    BasicFlagMACRO(IsPassSmallTransparent, flags, 0x0200)
    BasicFlagMACRO(IsDetonates, flags, 0x0400)
    BasicFlagMACRO(IsRotation, flags, 0x0800)

    BasicFlagMACRO(IsHead, modelFlags, 0x01)
    BasicFlagMACRO(IsTorso, modelFlags, 0x02)
    BasicFlagMACRO(IsRightHand, modelFlags, 0x04)
    BasicFlagMACRO(IsLeftHand, modelFlags, 0x08)

    BasicTypeMACRO(IsMissile, projType, 1, IsLobber)
    BasicTypeMACRO(IsLobber, projType, 2, IsMissile)
    BasicTypeMACRO(IsBeam, projType, 4, )
    BasicTypeMACRO(IsFlame, projType, 8, IsMissile)
    BasicTypeMACRO(IsContinuousBeam, projType, 16, IsMissile)

    BasicTypeMACRO(IsLoud, soundLevel, 0, IsNormal)
    BasicTypeMACRO(IsNormal, soundLevel, 1, IsLoud)
    BasicTypeMACRO(IsSilent, soundLevel, 2, IsLoud)
    copyattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                           'boundX2', 'boundY2', 'boundZ2',
                                           'full', 'modPath', 'modb', 'modt_p',
                                           'altTextures_list', 'modelFlags',
                                           'destructable_list', 'flags',
                                           'projType', 'gravity', 'speed',
                                           'range', 'light', 'flash',
                                           'tracerChance',
                                           'altExplProximityTrigger',
                                           'altExplProximityTimer',
                                           'explosion', 'sound',
                                           'flashDuration', 'fadeDuration',
                                           'impactForce', 'soundCountdown',
                                           'soundDisable',
                                           'defaultWeaponSource', 'rotX',
                                           'rotY', 'rotZ', 'bouncyMult',
                                           'modelPath', 'nam2_p',
                                           'soundLevel']
    exportattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                             'boundX2', 'boundY2', 'boundZ2',
                                             'full', 'modPath', 'modb',
                                             'altTextures_list', 'modelFlags',
                                             'destructable_list', 'flags',
                                             'projType', 'gravity', 'speed',
                                             'range', 'light', 'flash',
                                             'tracerChance',
                                             'altExplProximityTrigger',
                                             'altExplProximityTimer',
                                             'explosion', 'sound',
                                             'flashDuration', 'fadeDuration',
                                             'impactForce', 'soundCountdown',
                                             'soundDisable',
                                             'defaultWeaponSource', 'rotX',
                                             'rotY', 'rotZ', 'bouncyMult',
                                             'modelPath',
                                             'soundLevel']# 'nam2_p', 'modt_p',

class FnvLVLIRecord(FnvBaseRecord):
    _Type = 'LVLI'
    def mergeFilter(self,modSet):
        """Filter out items that don't come from specified modSet."""
        self.entries = [entry for entry in self.entries if entry.listId[0] in modSet]
        return True

    class Entry(ListComponent):
        SINT16_LISTMACRO(level, 1)
        UINT8_ARRAY_LISTMACRO(unused1, 2, 2)
        FORMID_LISTMACRO(listId, 3)
        SINT16_LISTMACRO(count, 4)
        UINT8_ARRAY_LISTMACRO(unused2, 5, 2)
        FORMID_LISTMACRO(owner, 6)
        UNKNOWN_OR_FORMID_OR_UINT32_LISTMACRO(globalOrRank, 7)
        FLOAT32_LISTMACRO(condition, 8)
        exportattrs = copyattrs = ['level', 'listId', 'count', 'owner', 'globalOrRank', 'condition']

    SINT16_MACRO(boundX1, 7)
    SINT16_MACRO(boundY1, 8)
    SINT16_MACRO(boundZ1, 9)
    SINT16_MACRO(boundX2, 10)
    SINT16_MACRO(boundY2, 11)
    SINT16_MACRO(boundZ2, 12)
    UINT8_MACRO(chanceNone, 13)
    UINT8_FLAG_MACRO(flags, 14)
    FORMID_MACRO(globalId, 15)

    LIST_MACRO(entries, 16, self.Entry)

    BasicFlagMACRO(IsCalcFromAllLevels, flags, 0x00000001)
    BasicFlagMACRO(IsCalcForEachItem, flags, 0x00000002)
    BasicFlagMACRO(IsUseAll, flags, 0x00000004)
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                                         'boundX2', 'boundY2', 'boundZ2',
                                                         'chanceNone', 'flags',
                                                         'globalId', 'entries_list']

class FnvWTHRRecord(FnvBaseRecord):
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

        UINT8_GROUPEDMACRO(noonRed, 16)
        UINT8_GROUPEDMACRO(noonGreen, 17)
        UINT8_GROUPEDMACRO(noonBlue, 18)
        UINT8_ARRAY_GROUPEDMACRO(unused5, 19, 1)

        UINT8_GROUPEDMACRO(midnightRed, 20)
        UINT8_GROUPEDMACRO(midnightGreen, 21)
        UINT8_GROUPEDMACRO(midnightBlue, 22)
        UINT8_ARRAY_GROUPEDMACRO(unused6, 23, 1)
        exportattrs = copyattrs = ['riseRed', 'riseGreen', 'riseBlue',
                                   'dayRed', 'dayGreen', 'dayBlue',
                                   'setRed', 'setGreen', 'setBlue',
                                   'nightRed', 'nightGreen', 'nightBlue',
                                   'noonRed', 'noonGreen', 'noonBlue',
                                   'midnightRed', 'midnightGreen', 'midnightBlue']

    class Sound(ListComponent):
        FORMID_LISTMACRO(sound, 1)
        UINT32_TYPE_LISTMACRO(type, 2)
        BasicTypeMACRO(IsDefault, type, 0, IsPrecip)
        BasicTypeMACRO(IsPrecipitation, type, 1, IsDefault)
        BasicAliasMACRO(IsPrecip, IsPrecipitation)
        BasicTypeMACRO(IsWind, type, 2, IsDefault)
        BasicTypeMACRO(IsThunder, type, 3, IsDefault)
        exportattrs = copyattrs = ['sound', 'type']

    FORMID_MACRO(sunriseImageSpace, 7)
    FORMID_MACRO(dayImageSpace, 8)
    FORMID_MACRO(sunsetImageSpace, 9)
    FORMID_MACRO(nightImageSpace, 10)
    FORMID_MACRO(unknown1ImageSpace, 11)
    FORMID_MACRO(unknown2ImageSpace, 12)
    ISTRING_MACRO(cloudLayer0Path, 13)
    ISTRING_MACRO(cloudLayer1Path, 14)
    ISTRING_MACRO(cloudLayer2Path, 15)
    ISTRING_MACRO(cloudLayer3Path, 16)
    ISTRING_MACRO(modPath, 17)
    FLOAT32_MACRO(modb, 18)
    UINT8_ARRAY_MACRO(modt_p, 19)

    LIST_MACRO(altTextures, 20, FNVAltTexture)
    UINT8_FLAG_MACRO(modelFlags, 21)
    UINT32_MACRO(unknown1, 22)
    UINT8_MACRO(layer0Speed, 23)
    UINT8_MACRO(layer1Speed, 24)
    UINT8_MACRO(layer2Speed, 25)
    UINT8_MACRO(layer3Speed, 26)
    UINT8_ARRAY_MACRO(pnam_p, 27)
    GroupedValuesMACRO(upperSky, 28, WTHRColor)
    GroupedValuesMACRO(fog, 52, WTHRColor)
    GroupedValuesMACRO(lowerClouds, 76, WTHRColor)
    GroupedValuesMACRO(ambient, 100, WTHRColor)
    GroupedValuesMACRO(sunlight, 124, WTHRColor)
    GroupedValuesMACRO(sun, 148, WTHRColor)
    GroupedValuesMACRO(stars, 172, WTHRColor)
    GroupedValuesMACRO(lowerSky, 196, WTHRColor)
    GroupedValuesMACRO(horizon, 220, WTHRColor)
    GroupedValuesMACRO(upperClouds, 244, WTHRColor)
    FLOAT32_MACRO(fogDayNear, 268)
    FLOAT32_MACRO(fogDayFar, 269)
    FLOAT32_MACRO(fogNightNear, 270)
    FLOAT32_MACRO(fogNightFar, 271)
    FLOAT32_MACRO(fogDayPower, 272)
    FLOAT32_MACRO(fogNightPower, 273)
    UINT8_ARRAY_MACRO(inam_p, 274)
    UINT8_MACRO(windSpeed, 275)
    UINT8_MACRO(lowerCloudSpeed, 276)
    UINT8_MACRO(upperCloudSpeed, 277)
    UINT8_MACRO(transDelta, 278)
    UINT8_MACRO(sunGlare, 279)
    UINT8_MACRO(sunDamage, 280)
    UINT8_MACRO(rainFadeIn, 281)
    UINT8_MACRO(rainFadeOut, 282)
    UINT8_MACRO(boltFadeIn, 283)
    UINT8_MACRO(boltFadeOut, 284)
    UINT8_MACRO(boltFrequency, 285)
    UINT8_TYPE_MACRO(weatherType, 286)
    UINT8_MACRO(boltRed, 287)
    UINT8_MACRO(boltGreen, 288)
    UINT8_MACRO(boltBlue, 289)

    LIST_MACRO(sounds, 290, self.Sound)
    ##actually flags, but all are exclusive(except unknowns)...so like a Type
    ##Manual hackery will make the CS think it is multiple types. It isn't known how the game would react.
    MaskedTypeMACRO(IsNone, weatherType, 0x0F, 0x00, IsPleasant)
    MaskedTypeMACRO(IsPleasant, weatherType, 0x0F, 0x01, IsNone)
    MaskedTypeMACRO(IsCloudy, weatherType, 0x0F, 0x02, IsNone)
    MaskedTypeMACRO(IsRainy, weatherType, 0x0F, 0x04, IsNone)
    MaskedTypeMACRO(IsSnow, weatherType, 0x0F, 0x08, IsNone)
    BasicFlagMACRO(IsUnk1, weatherType, 0x40)
    BasicFlagMACRO(IsUnk2, weatherType, 0x80)
    copyattrs = FnvBaseRecord.baseattrs + ['sunriseImageSpace', 'dayImageSpace',
                                           'sunsetImageSpace', 'nightImageSpace',
                                           'unknown1ImageSpace', 'unknown2ImageSpace',
                                           'cloudLayer0Path', 'cloudLayer1Path',
                                           'cloudLayer2Path', 'cloudLayer3Path',
                                           'modPath', 'modb', 'modt_p',
                                           'altTextures_list', 'modelFlags',
                                           'unknown1', 'layer0Speed', 'layer1Speed',
                                           'layer2Speed', 'layer3Speed', 'pnam_p',
                                           'upperSky_list', 'fog_list',
                                           'lowerClouds_list', 'ambient_list',
                                           'sunlight_list', 'sun_list', 'stars_list',
                                           'lowerSky_list', 'horizon_list',
                                           'upperClouds_list', 'fogDayNear',
                                           'fogDayFar', 'fogNightNear',
                                           'fogNightFar', 'fogDayPower',
                                           'fogNightPower', 'inam_p', 'windSpeed',
                                           'lowerCloudSpeed', 'upperCloudSpeed',
                                           'transDelta', 'sunGlare', 'sunDamage',
                                           'rainFadeIn', 'rainFadeOut',
                                           'boltFadeIn', 'boltFadeOut',
                                           'boltFrequency', 'weatherType',
                                           'boltRed', 'boltGreen', 'boltBlue',
                                           'sounds_list']
    exportattrs = FnvBaseRecord.baseattrs + ['sunriseImageSpace', 'dayImageSpace',
                                             'sunsetImageSpace', 'nightImageSpace',
                                             'unknown1ImageSpace', 'unknown2ImageSpace',
                                             'cloudLayer0Path', 'cloudLayer1Path',
                                             'cloudLayer2Path', 'cloudLayer3Path',
                                             'modPath', 'modb',
                                             'altTextures_list', 'modelFlags',
                                             'unknown1', 'layer0Speed', 'layer1Speed',
                                             'layer2Speed', 'layer3Speed',
                                             'upperSky_list', 'fog_list',
                                             'lowerClouds_list', 'ambient_list',
                                             'sunlight_list', 'sun_list', 'stars_list',
                                             'lowerSky_list', 'horizon_list',
                                             'upperClouds_list', 'fogDayNear',
                                             'fogDayFar', 'fogNightNear',
                                             'fogNightFar', 'fogDayPower',
                                             'fogNightPower', 'windSpeed',
                                             'lowerCloudSpeed', 'upperCloudSpeed',
                                             'transDelta', 'sunGlare', 'sunDamage',
                                             'rainFadeIn', 'rainFadeOut',
                                             'boltFadeIn', 'boltFadeOut',
                                             'boltFrequency', 'weatherType',
                                             'boltRed', 'boltGreen', 'boltBlue',
                                             'sounds_list']# 'modt_p', 'pnam_p', 'inam_p',

class FnvCLMTRecord(FnvBaseRecord):
    _Type = 'CLMT'
    class Weather(ListComponent):
        FORMID_LISTMACRO(weather, 1)
        SINT32_LISTMACRO(chance, 2)
        FORMID_LISTMACRO(globalId, 3)
        copyattrs = ['weather', 'chance', 'globalId']

    LIST_MACRO(weathers, 7, self.Weather)
    ISTRING_MACRO(sunPath, 8)
    ISTRING_MACRO(glarePath, 9)
    ISTRING_MACRO(modPath, 10)
    FLOAT32_MACRO(modb, 11)
    UINT8_ARRAY_MACRO(modt_p, 12)

    LIST_MACRO(altTextures, 13, FNVAltTexture)
    UINT8_FLAG_MACRO(modelFlags, 14)
    UINT8_MACRO(riseBegin, 15)
    UINT8_MACRO(riseEnd, 16)
    UINT8_MACRO(setBegin, 17)
    UINT8_MACRO(setEnd, 18)
    UINT8_MACRO(volatility, 19)
    UINT8_MACRO(phaseLength, 20)

    BasicFlagMACRO(IsHead, modelFlags, 0x01)
    BasicFlagMACRO(IsTorso, modelFlags, 0x02)
    BasicFlagMACRO(IsRightHand, modelFlags, 0x04)
    BasicFlagMACRO(IsLeftHand, modelFlags, 0x08)
    copyattrs = FnvBaseRecord.baseattrs + ['weathers_list', 'sunPath',
                                           'glarePath', 'modPath',
                                           'modb', 'modt_p',
                                           'altTextures_list',
                                           'modelFlags', 'riseBegin',
                                           'riseEnd', 'setBegin',
                                           'setEnd', 'volatility',
                                           'phaseLength']
    exportattrs = FnvBaseRecord.baseattrs + ['weathers_list', 'sunPath',
                                             'glarePath', 'modPath',
                                             'modb',
                                             'altTextures_list',
                                             'modelFlags', 'riseBegin',
                                             'riseEnd', 'setBegin',
                                             'setEnd', 'volatility',
                                             'phaseLength']# 'modt_p',

class FnvREGNRecord(FnvBaseRecord):
    _Type = 'REGN'
    class Area(ListComponent):
        class Point(ListX2Component):
            FLOAT32_LISTX2MACRO(posX, 1)
            FLOAT32_LISTX2MACRO(posY, 2)
            exportattrs = copyattrs = ['posX', 'posY']

        FORMID_LISTMACRO(edgeFalloff, 1)

        LIST_LISTMACRO(points, 2, self.Point)
        exportattrs = copyattrs = ['edgeFalloff', 'points_list']

    class Entry(ListComponent):
        class Object(ListX2Component):
            FORMID_LISTX2MACRO(objectId, 1)
            UINT16_LISTX2MACRO(parentIndex, 2)
            UINT8_ARRAY_LISTX2MACRO(unused1, 3, 2)
            FLOAT32_LISTX2MACRO(density, 4)
            UINT8_LISTX2MACRO(clustering, 5)
            UINT8_LISTX2MACRO(minSlope, 6)
            UINT8_LISTX2MACRO(maxSlope, 7)
            UINT8_FLAG_LISTX2MACRO(flags, 8)
            UINT16_LISTX2MACRO(radiusWRTParent, 9)
            UINT16_LISTX2MACRO(radius, 10)
            UINT8_ARRAY_LISTX2MACRO(unk1, 11, 4)
            FLOAT32_LISTX2MACRO(maxHeight, 12)
            FLOAT32_LISTX2MACRO(sink, 13)
            FLOAT32_LISTX2MACRO(sinkVar, 14)
            FLOAT32_LISTX2MACRO(sizeVar, 15)
            UINT16_LISTX2MACRO(angleVarX, 16)
            UINT16_LISTX2MACRO(angleVarY, 17)
            UINT16_LISTX2MACRO(angleVarZ, 18)
            UINT8_ARRAY_LISTX2MACRO(unused2, 19, 1)
            UINT8_ARRAY_LISTX2MACRO(unk2, 20, 4)
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
            FORMID_LISTX2MACRO(grass, 1)
            UINT8_ARRAY_LISTX2MACRO(unk1, 2, 4)
            exportattrs = copyattrs = ['grass', 'unk1']

        class Sound(ListX2Component):
            FORMID_LISTX2MACRO(sound, 1)
            UINT32_FLAG_LISTX2MACRO(flags, 2)
            UINT32_LISTX2MACRO(chance, 3)
            BasicFlagMACRO(IsPleasant, flags, 0x00000001)
            BasicFlagMACRO(IsCloudy, flags, 0x00000002)
            BasicFlagMACRO(IsRainy, flags, 0x00000004)
            BasicFlagMACRO(IsSnowy, flags, 0x00000008)
            exportattrs = copyattrs = ['sound', 'flags', 'chance']

        class Weather(ListX2Component):
            FORMID_LISTX2MACRO(weather, 1)
            UINT32_LISTX2MACRO(chance, 2)
            FORMID_LISTX2MACRO(globalId, 1)
            exportattrs = copyattrs = ['weather', 'chance', 'globalId']

        UINT32_TYPE_LISTMACRO(entryType, 1)
        UINT8_FLAG_LISTMACRO(flags, 2)
        UINT8_LISTMACRO(priority, 3)
        UINT8_ARRAY_LISTMACRO(unused1, 4, 4)

        LIST_LISTMACRO(objects, 5, self.Object)
        STRING_LISTMACRO(mapName, 6)
        STRING_LISTMACRO(iconPath, 7)

        LIST_LISTMACRO(grasses, 8, self.Grass)
        UINT32_TYPE_LISTMACRO(musicType, 9)
        FORMID_LISTMACRO(music, 10)
        FORMID_LISTMACRO(incidentalMedia, 11)
        FORMID_ARRAY_LISTMACRO(battleMedias, 12)

        LIST_LISTMACRO(sounds, 13, self.Sound)

        LIST_LISTMACRO(weathers, 14, self.Weather)
        FORMID_ARRAY_LISTMACRO(imposters, 15)

        BasicFlagMACRO(IsOverride, flags, 0x00000001)

        BasicTypeMACRO(IsObject, entryType, 2, IsWeather)
        BasicTypeMACRO(IsWeather, entryType, 3, IsObject)
        BasicTypeMACRO(IsMap, entryType, 4, IsObject)
        BasicTypeMACRO(IsLand, entryType, 5, IsObject)
        BasicTypeMACRO(IsGrass, entryType, 6, IsObject)
        BasicTypeMACRO(IsSound, entryType, 7, IsObject)
        BasicTypeMACRO(IsImposter, entryType, 8, IsObject)
        BasicTypeMACRO(IsDefault, musicType, 0, IsPublic)
        BasicTypeMACRO(IsPublic, musicType, 1, IsDefault)
        BasicTypeMACRO(IsDungeon, musicType, 2, IsDefault)
        exportattrs = copyattrs = ['entryType', 'flags', 'priority', 'objects_list',
                                   'mapName', 'iconPath', 'grasses_list', 'musicType',
                                   'music', 'incidentalMedia', 'battleMedias',
                                   'sounds_list', 'weathers_list', 'imposters']

    ISTRING_MACRO(iconPath, 7)
    ISTRING_MACRO(smallIconPath, 8)
    UINT8_MACRO(mapRed, 9)
    UINT8_MACRO(mapGreen, 10)
    UINT8_MACRO(mapBlue, 11)
    UINT8_ARRAY_MACRO(unused1, 12, 1)
    FORMID_MACRO(worldspace, 13)

    LIST_MACRO(areas, 14, self.Area)
    LIST_MACRO(entries, 15, self.Entry)
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + ['iconPath', 'smallIconPath',
                                                         'mapRed', 'mapGreen', 'mapBlue',
                                                         'worldspace', 'areas_list',
                                                         'entries_list']

class FnvNAVIRecord(FnvBaseRecord):
    _Type = 'NAVI'
    class _NVMI(ListComponent):
        UINT8_ARRAY_LISTMACRO(unknown1, 1, 4)
        FORMID_LISTMACRO(mesh, 2)
        FORMID_LISTMACRO(location, 3)
        SINT16_LISTMACRO(xGrid, 4)
        SINT16_LISTMACRO(yGrid, 5)
        UINT8_ARRAY_LISTMACRO(unknown2_p, 6)
        copyattrs = ['unknown1', 'mesh', 'location',
                     'xGrid', 'yGrid', 'unknown2_p']
        exportattrs = ['mesh', 'location',
                       'xGrid', 'yGrid']#'unknown1', 'unknown2_p'

    class _NVCI(ListComponent):
        FORMID_LISTMACRO(unknown1, 1)
        FORMID_ARRAY_LISTMACRO(unknown2, 2)
        FORMID_ARRAY_LISTMACRO(unknown3, 3)
        FORMID_ARRAY_LISTMACRO(doors, 4)
        exportattrs = copyattrs = ['unknown1', 'unknown2',
                                   'unknown3', 'doors']

    UINT32_MACRO(version, 7)

    LIST_MACRO(NVMI, 8, self._NVMI)

    LIST_MACRO(NVCI, 9, self._NVCI)
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + ['version', 'NVMI_list', 'NVCI_list']

class FnvCELLRecord(FnvBaseRecord):
    _Type = 'CELL'
    @property
    def _ParentID(self):
        _CGetField.restype = c_ulong
        return _CGetField(self._RecordID, 67, 0, 0, 0, 0, 0, 0, 0)

    @property
    def bsb(self):
        """Returns tesfile block and sub-block indices for cells in this group.
        For interior cell, bsb is (blockNum,subBlockNum). For exterior cell, bsb is
        ((blockX,blockY),(subblockX,subblockY))."""
        #--Interior cell
        if self.IsInterior:
            ObjectID = self.fid[1]
            blockNum = ObjectID % 10
            subBlockNum = (ObjectID / 10) % 10
            return (blockNum, subBlockNum)
        #--Exterior cell
        else:
            blockX = int(math.floor(self.posX or 0 / 8.0))
            blockY = int(math.floor(self.posY or 0 / 8.0))
            subblockX = int(math.floor(blockX / 4.0))
            subblockY = int(math.floor(blockY / 4.0))
            return ((blockX, blockY), (subblockX, subblockY))

    class SwappedImpact(ListComponent):
        UINT32_TYPE_LISTMACRO(material, 1)
        FORMID_LISTMACRO(oldImpact, 2)
        FORMID_LISTMACRO(newImpact, 3)

        BasicTypeMACRO(IsStone, material, 0, IsDirt)
        BasicTypeMACRO(IsDirt, material, 1, IsStone)
        BasicTypeMACRO(IsGrass, material, 2, IsStone)
        BasicTypeMACRO(IsGlass, material, 3, IsStone)
        BasicTypeMACRO(IsMetal, material, 4, IsStone)
        BasicTypeMACRO(IsWood, material, 5, IsStone)
        BasicTypeMACRO(IsOrganic, material, 6, IsStone)
        BasicTypeMACRO(IsCloth, material, 7, IsStone)
        BasicTypeMACRO(IsWater, material, 8, IsStone)
        BasicTypeMACRO(IsHollowMetal, material, 9, IsStone)
        BasicTypeMACRO(IsOrganicBug, material, 10, IsStone)
        BasicTypeMACRO(IsOrganicGlow, material, 11, IsStone)
        exportattrs = copyattrs = ['material', 'oldImpact', 'newImpact']

    STRING_MACRO(full, 7)
    UINT8_MACRO(flags, 8)
    UNKNOWN_OR_SINT32_MACRO(posX, 9)
    UNKNOWN_OR_SINT32_MACRO(posY, 10)
    UNKNOWN_OR_UINT32_FLAG_MACRO(quadFlags, 11)
    UINT8_MACRO(ambientRed, 12)
    UINT8_MACRO(ambientGreen, 13)
    UINT8_MACRO(ambientBlue, 14)
    UINT8_ARRAY_MACRO(unused1, 15, 1)
    UINT8_MACRO(directionalRed, 16)
    UINT8_MACRO(directionalGreen, 17)
    UINT8_MACRO(directionalBlue, 18)
    UINT8_ARRAY_MACRO(unused2, 19, 1)
    UINT8_MACRO(fogRed, 20)
    UINT8_MACRO(fogGreen, 21)
    UINT8_MACRO(fogBlue, 22)
    UINT8_ARRAY_MACRO(unused3, 23, 1)
    FLOAT32_MACRO(fogNear, 24)
    FLOAT32_MACRO(fogFar, 25)
    SINT32_MACRO(directionalXY, 26)
    SINT32_MACRO(directionalZ, 27)
    FLOAT32_MACRO(directionalFade, 28)
    FLOAT32_MACRO(fogClip, 29)
    FLOAT32_MACRO(fogPower, 30)

    LIST_MACRO(swappedImpacts, 31, self.SwappedImpact)
    STRING_MACRO(concSolid, 32)
    STRING_MACRO(concBroken, 33)
    STRING_MACRO(metalSolid, 34)
    STRING_MACRO(metalHollow, 35)
    STRING_MACRO(metalSheet, 36)
    STRING_MACRO(wood, 37)
    STRING_MACRO(sand, 38)
    STRING_MACRO(dirt, 39)
    STRING_MACRO(grass, 40)
    STRING_MACRO(water, 41)
    FORMID_MACRO(lightTemplate, 42)
    UINT32_FLAG_MACRO(lightFlags, 43)
    FLOAT32_MACRO(waterHeight, 44)
    ISTRING_MACRO(waterNoisePath, 45)
    FORMID_ARRAY_MACRO(regions, 46)
    FORMID_MACRO(imageSpace, 47)
    UINT8_ARRAY_MACRO(xcet_p, 48)
    FORMID_MACRO(encounterZone, 49)
    FORMID_MACRO(climate, 50)
    FORMID_MACRO(water, 51)
    FORMID_MACRO(owner, 52)
    SINT32_MACRO(rank, 53)
    FORMID_MACRO(acousticSpace, 54)
    UINT8_ARRAY_MACRO(xcmt_p, 55)
    FORMID_MACRO(music, 56)
    SUBRECORD_ARRAY_MACRO(ACHR, "ACHR", 57, FnvACHRRecord)
    SUBRECORD_ARRAY_MACRO(ACRE, "ACRE", 58, FnvACRERecord)
    SUBRECORD_ARRAY_MACRO(REFR, "REFR", 59, FnvREFRRecord)
    SUBRECORD_ARRAY_MACRO(PGRE, "PGRE", 60, FnvPGRERecord)
    SUBRECORD_ARRAY_MACRO(PMIS, "PMIS", 61, FnvPMISRecord)
    SUBRECORD_ARRAY_MACRO(PBEA, "PBEA", 62, FnvPBEARecord)
    SUBRECORD_ARRAY_MACRO(PFLA, "PFLA", 63, FnvPFLARecord)
    SUBRECORD_ARRAY_MACRO(PCBE, "PCBE", 64, FnvPCBERecord)
    SUBRECORD_ARRAY_MACRO(NAVM, "NAVM", 65, FnvNAVMRecord)
    SUBRECORD_MACRO(LAND, "LAND", 66, FnvLANDRecord)

    BasicFlagMACRO(IsInterior, flags, 0x00000001)
    BasicFlagMACRO(IsHasWater, flags, 0x00000002)
    BasicFlagMACRO(IsInvertFastTravel, flags, 0x00000004)
    BasicFlagMACRO(IsForceHideLand, flags, 0x00000008) #Exterior cells only
    BasicFlagMACRO(IsOblivionInterior, flags, 0x00000008) #Interior cells only
    BasicFlagMACRO(IsPublicPlace, flags, 0x00000020)
    BasicFlagMACRO(IsHandChanged, flags, 0x00000040)
    BasicFlagMACRO(IsBehaveLikeExterior, flags, 0x00000080)

    BasicFlagMACRO(IsQuad1ForceHidden, quadFlags, 0x00000001)
    BasicFlagMACRO(IsQuad2ForceHidden, quadFlags, 0x00000002)
    BasicFlagMACRO(IsQuad3ForceHidden, quadFlags, 0x00000004)
    BasicFlagMACRO(IsQuad4ForceHidden, quadFlags, 0x00000008)

    BasicFlagMACRO(IsLightAmbientInherited, lightFlags, 0x00000001)
    BasicFlagMACRO(IsLightDirectionalColorInherited, lightFlags, 0x00000002)
    BasicFlagMACRO(IsLightFogColorInherited, lightFlags, 0x00000004)
    BasicFlagMACRO(IsLightFogNearInherited, lightFlags, 0x00000008)
    BasicFlagMACRO(IsLightFogFarInherited, lightFlags, 0x00000010)
    BasicFlagMACRO(IsLightDirectionalRotationInherited, lightFlags, 0x00000020)
    BasicFlagMACRO(IsLightDirectionalFadeInherited, lightFlags, 0x00000040)
    BasicFlagMACRO(IsLightFogClipInherited, lightFlags, 0x00000080)
    BasicFlagMACRO(IsLightFogPowerInherited, lightFlags, 0x00000100)
    copyattrs = FnvBaseRecord.baseattrs + ['full', 'flags', 'posX', 'posY', 'quadFlags',
                                           'ambientRed', 'ambientGreen', 'ambientBlue',
                                           'directionalRed', 'directionalGreen', 'directionalBlue',
                                           'fogRed', 'fogGreen', 'fogBlue',
                                           'fogNear', 'fogFar', 'directionalXY', 'directionalZ',
                                           'directionalFade', 'fogClip', 'fogPower', 'concSolid',
                                           'concBroken', 'metalSolid', 'metalHollow', 'metalSheet',
                                           'wood', 'sand', 'dirt', 'grass', 'water',
                                           'lightTemplate', 'lightFlags', 'waterHeight',
                                           'waterNoisePath', 'regions', 'imageSpace', 'xcet_p',
                                           'encounterZone', 'climate', 'water', 'owner',
                                           'rank', 'acousticSpace', 'xcmt_p', 'music']
    exportattrs = FnvBaseRecord.baseattrs + ['full', 'flags', 'posX', 'posY', 'quadFlags',
                                             'ambientRed', 'ambientGreen', 'ambientBlue',
                                             'directionalRed', 'directionalGreen', 'directionalBlue',
                                             'fogRed', 'fogGreen', 'fogBlue',
                                             'fogNear', 'fogFar', 'directionalXY', 'directionalZ',
                                             'directionalFade', 'fogClip', 'fogPower', 'concSolid',
                                             'concBroken', 'metalSolid', 'metalHollow', 'metalSheet',
                                             'wood', 'sand', 'dirt', 'grass', 'water',
                                             'lightTemplate', 'lightFlags', 'waterHeight',
                                             'waterNoisePath', 'regions', 'imageSpace',
                                             'encounterZone', 'climate', 'water', 'owner',
                                             'rank', 'acousticSpace', 'music']# 'xcet_p', 'xcmt_p',

class FnvWRLDRecord(FnvBaseRecord):
    _Type = 'WRLD'
    class SwappedImpact(ListComponent):
        UINT32_TYPE_LISTMACRO(material, 1)
        FORMID_LISTMACRO(oldImpact, 2)
        FORMID_LISTMACRO(newImpact, 3)

        BasicTypeMACRO(IsStone, material, 0, IsDirt)
        BasicTypeMACRO(IsDirt, material, 1, IsStone)
        BasicTypeMACRO(IsGrass, material, 2, IsStone)
        BasicTypeMACRO(IsGlass, material, 3, IsStone)
        BasicTypeMACRO(IsMetal, material, 4, IsStone)
        BasicTypeMACRO(IsWood, material, 5, IsStone)
        BasicTypeMACRO(IsOrganic, material, 6, IsStone)
        BasicTypeMACRO(IsCloth, material, 7, IsStone)
        BasicTypeMACRO(IsWater, material, 8, IsStone)
        BasicTypeMACRO(IsHollowMetal, material, 9, IsStone)
        BasicTypeMACRO(IsOrganicBug, material, 10, IsStone)
        BasicTypeMACRO(IsOrganicGlow, material, 11, IsStone)
        exportattrs = copyattrs = ['material', 'oldImpact', 'newImpact']

    STRING_MACRO(full, 7)
    FORMID_MACRO(encounterZone, 8)
    FORMID_MACRO(parent, 9)
    UINT16_FLAG_MACRO(parentFlags, 10)
    FORMID_MACRO(climate, 11)
    FORMID_MACRO(water, 12)
    FORMID_MACRO(lodWater, 13)
    FLOAT32_MACRO(lodWaterHeight, 14)
    FLOAT32_MACRO(defaultLandHeight, 15)
    FLOAT32_MACRO(defaultWaterHeight, 16)
    ISTRING_MACRO(iconPath, 17)
    ISTRING_MACRO(smallIconPath, 18)
    SINT32_MACRO(dimX, 19)
    SINT32_MACRO(dimY, 20)
    SINT16_MACRO(NWCellX, 21)
    SINT16_MACRO(NWCellY, 22)
    SINT16_MACRO(SECellX, 23)
    SINT16_MACRO(SECellY, 24)
    FLOAT32_MACRO(mapScale, 25)
    FLOAT32_MACRO(xCellOffset, 26)
    FLOAT32_MACRO(yCellOffset, 27)
    FORMID_MACRO(imageSpace, 28)
    UINT8_FLAG_MACRO(flags, 29)
    FLOAT32_MACRO(xMinObjBounds, 30)
    FLOAT32_MACRO(yMinObjBounds, 31)
    FLOAT32_MACRO(xMaxObjBounds, 32)
    FLOAT32_MACRO(yMaxObjBounds, 33)
    FORMID_MACRO(music, 34)
    ISTRING_MACRO(canopyShadowPath, 35)
    ISTRING_MACRO(waterNoisePath, 36)

    LIST_MACRO(swappedImpacts, 37, self.SwappedImpact)
    STRING_MACRO(concSolid, 38)
    STRING_MACRO(concBroken, 39)
    STRING_MACRO(metalSolid, 40)
    STRING_MACRO(metalHollow, 41)
    STRING_MACRO(metalSheet, 42)
    STRING_MACRO(wood, 43)
    STRING_MACRO(sand, 44)
    STRING_MACRO(dirt, 45)
    STRING_MACRO(grass, 46)
    STRING_MACRO(water, 47)
    UINT8_ARRAY_MACRO(ofst_p, 48)

    SUBRECORD_MACRO(WorldCELL, "WCEL", 49, FnvCELLRecord) ##"WCEL" is an artificial type CBash uses to distinguish World Cells
    SUBRECORD_ARRAY_MACRO(CELLS, "CELL", 50, FnvCELLRecord)

    BasicFlagMACRO(IsSmallWorld, flags, 0x01)
    BasicFlagMACRO(IsNoFastTravel, flags, 0x02)
    BasicFlagMACRO(IsUnknown2, flags, 0x04)
    BasicFlagMACRO(IsNoLODWater, flags, 0x10)
    BasicFlagMACRO(IsNoLODNoise, flags, 0x20)
    BasicFlagMACRO(IsNoNPCFallDmg, flags, 0x40)

    BasicFlagMACRO(IsUseLandData, parentFlags, 0x0001)
    BasicFlagMACRO(IsUseLODData, parentFlags, 0x0002)
    BasicFlagMACRO(IsUseMapData, parentFlags, 0x0004)
    BasicFlagMACRO(IsUseWaterData, parentFlags, 0x0008)
    BasicFlagMACRO(IsUseClimateData, parentFlags, 0x0010)
    BasicFlagMACRO(IsUseImageSpaceData, parentFlags, 0x0020)
    BasicFlagMACRO(IsUnknown1, parentFlags, 0x0040)
    BasicFlagMACRO(IsNeedsWaterAdjustment, parentFlags, 0x0080)
    copyattrs = FnvBaseRecord.baseattrs + ['full', 'encounterZone', 'parent',
                                           'parentFlags', 'climate', 'water',
                                           'lodWater', 'lodWaterHeight',
                                           'defaultLandHeight',
                                           'defaultWaterHeight', 'iconPath',
                                           'smallIconPath', 'dimX', 'dimY',
                                           'NWCellX', 'NWCellY', 'SECellX',
                                           'SECellY', 'mapScale', 'xCellOffset',
                                           'yCellOffset', 'imageSpace', 'flags',
                                           'xMinObjBounds', 'yMinObjBounds',
                                           'xMaxObjBounds', 'yMaxObjBounds',
                                           'music', 'canopyShadowPath',
                                           'waterNoisePath',
                                           'swappedImpacts_list', 'concSolid',
                                           'concBroken', 'metalSolid',
                                           'metalHollow', 'metalSheet', 'wood',
                                           'sand', 'dirt', 'grass', 'water',
                                           'ofst_p']

    exportattrs = FnvBaseRecord.baseattrs + ['full', 'encounterZone', 'parent',
                                             'parentFlags', 'climate', 'water',
                                             'lodWater', 'lodWaterHeight',
                                             'defaultLandHeight',
                                             'defaultWaterHeight', 'iconPath',
                                             'smallIconPath', 'dimX', 'dimY',
                                             'NWCellX', 'NWCellY', 'SECellX',
                                             'SECellY', 'mapScale', 'xCellOffset',
                                             'yCellOffset', 'imageSpace', 'flags',
                                             'xMinObjBounds', 'yMinObjBounds',
                                             'xMaxObjBounds', 'yMaxObjBounds',
                                             'music', 'canopyShadowPath',
                                             'waterNoisePath',
                                             'swappedImpacts_list', 'concSolid',
                                             'concBroken', 'metalSolid',
                                             'metalHollow', 'metalSheet', 'wood',
                                             'sand', 'dirt', 'grass', 'water']#,'ofst_p'

class FnvDIALRecord(FnvBaseRecord):
    _Type = 'DIAL'
    class Quest(ListComponent):
        class QuestUnknown(ListX2Component):
            FORMID_LISTX2MACRO(unknownId, 1)
            SINT32_LISTX2MACRO(unknown, 2)
            exportattrs = copyattrs = ['unknownId', 'unknown']

        FORMID_LISTMACRO(quest, 1)

        LIST_LISTMACRO(unknowns, 2, self.QuestUnknown)
        exportattrs = copyattrs = ['quest', 'unknowns_list']

    LIST_MACRO(quests, 7, self.Quest)
    LIST_MACRO(removedQuests, 8, self.Quest)

    STRING_MACRO(full, 9)
    FLOAT32_MACRO(priority, 10)
    STRING_MACRO(unknown, 11)
    UINT8_TYPE_MACRO(dialType, 12)
    UINT8_FLAG_MACRO(flags, 13)
    SUBRECORD_ARRAY_MACRO(INFO, "INFO", 14, FnvINFORecord)

    BasicFlagMACRO(IsRumors, flags, 0x01)
    BasicFlagMACRO(IsTopLevel, flags, 0x02)

    BasicTypeMACRO(IsTopic, dialType, 0, IsConversation)
    BasicTypeMACRO(IsConversation, dialType, 1, IsTopic)
    BasicTypeMACRO(IsCombat, dialType, 2, IsTopic)
    BasicTypeMACRO(IsPersuasion, dialType, 3, IsTopic)
    BasicTypeMACRO(IsDetection, dialType, 4, IsTopic)
    BasicTypeMACRO(IsService, dialType, 5, IsTopic)
    BasicTypeMACRO(IsMisc, dialType, 6, IsTopic)
    BasicTypeMACRO(IsRadio, dialType, 7, IsTopic)
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + ['quests_list', 'removedQuests_list',
                                                         'full', 'priority', 'unknown',
                                                         'dialType', 'flags']

class FnvQUSTRecord(FnvBaseRecord):
    _Type = 'QUST'
    def mergeFilter(self,modSet):
        """Filter out items that don't come from specified modSet.
        Filters items."""
        self.conditions = [x for x in self.conditions if (
            (not isinstance(x.param1,FormID) or x.param1[0] in modSet)
            and
            (not isinstance(x.param2,FormID) or x.param2[0] in modSet)
            )]
        #for target in self.targets_list:
        #    target.conditions = [x for x in target.conditions_list if (
        #        (not isinstance(x.param1,FormID) or x.param1[0] in modSet)
        #        and
        #        (not isinstance(x.param2,FormID) or x.param2[0] in modSet)
        #        )]
        return True

    class Stage(ListComponent):
        class Entry(ListX2Component):
            UINT8_FLAG_LISTX2MACRO(flags, 1)

            LIST_LISTX2MACRO(conditions, 2, FNVConditionX3)
            STRING_LISTX2MACRO(text, 3)
            UINT8_ARRAY_LISTX2MACRO(unused1, 4, 4)
            UINT32_LISTX2MACRO(numRefs, 5)
            UINT32_LISTX2MACRO(compiledSize, 6)
            UINT32_LISTX2MACRO(lastIndex, 7)
            UINT32_LISTX2MACRO(scriptType, 8)
            UINT16_FLAG_LISTX2MACRO(scriptFlags, 9)
            UINT8_ARRAY_LISTX2MACRO(compiled_p, 10)
            ISTRING_LISTX2MACRO(scriptText, 11)

            LIST_LISTX2MACRO(vars, 12, VarX3)
            FORMID_OR_UINT32_ARRAY_LISTX2MACRO(references, 13)
            FORMID_LISTX2MACRO(nextQuest, 14)

            BasicFlagMACRO(IsCompletes, flags, 0x00000001)
            BasicFlagMACRO(IsFailed, flags, 0x00000002)

            BasicFlagMACRO(IsEnabled, scriptFlags, 0x0001)

            BasicTypeMACRO(IsObject, scriptType, 0x0000, IsQuest)
            BasicTypeMACRO(IsQuest, scriptType, 0x0001, IsObject)
            BasicTypeMACRO(IsEffect, scriptType, 0x0100, IsObject)
            copyattrs = ['flags', 'conditions_list', 'text',
                         'numRefs', 'compiledSize',
                         'lastIndex', 'scriptType', 'flags',
                         'compiled_p', 'scriptText',
                         'vars_list', 'references',
                         'nextQuest']
            exportattrs = ['flags', 'conditions_list', 'text',
                           'numRefs', 'compiledSize',
                           'lastIndex', 'scriptType', 'flags',
                           'scriptText',
                           'vars_list', 'references',
                           'nextQuest']#'compiled_p',

        SINT16_LISTMACRO(stage, 1)

        LIST_LISTMACRO(entries, 2, self.Entry)
        exportattrs = copyattrs = ['stage', 'entries_list']

    class Objective(ListComponent):
        class Target(ListX2Component):
            FORMID_LISTX2MACRO(targetId, 1)
            UINT8_FLAG_LISTX2MACRO(flags, 2)
            UINT8_ARRAY_LISTX2MACRO(unused1, 3, 3)

            LIST_LISTX2MACRO(conditions, 4, FNVConditionX3)

            BasicFlagMACRO(IsIgnoresLocks, flags, 0x00000001)
            exportattrs = copyattrs = ['targetId', 'flags', 'conditions_list']

        SINT32_LISTMACRO(objective, 1)
        STRING_LISTMACRO(text, 2)

        LIST_LISTMACRO(targets, 3, self.Target)
        exportattrs = copyattrs = ['objective', 'text', 'targets_list']

    FORMID_MACRO(script, 7)
    STRING_MACRO(full, 8)
    ISTRING_MACRO(iconPath, 9)
    ISTRING_MACRO(smallIconPath, 10)
    UINT8_FLAG_MACRO(flags, 11)
    UINT8_MACRO(priority, 12)
    UINT8_ARRAY_MACRO(unused1, 13, 2)
    FLOAT32_MACRO(delay, 14)

    LIST_MACRO(conditions, 15, FNVCondition)
    LIST_MACRO(stages, 16, self.Stage)
    LIST_MACRO(objectives, 17, self.Objective)

    BasicFlagMACRO(IsStartEnabled, flags, 0x00000001)
    BasicFlagMACRO(IsRepeatedTopics, flags, 0x00000004)
    BasicFlagMACRO(IsRepeatedStages, flags, 0x00000008)
    BasicFlagMACRO(IsUnknown, flags, 0x00000010)
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + ['script', 'full', 'iconPath',
                                                         'smallIconPath', 'flags',
                                                         'priority', 'delay',
                                                         'conditions_list',
                                                         'stages_list', 'objectives_list']

class FnvIDLERecord(FnvBaseRecord):
    _Type = 'IDLE'
    ISTRING_MACRO(modPath, 7)
    FLOAT32_MACRO(modb, 8)
    UINT8_ARRAY_MACRO(modt_p, 9)

    LIST_MACRO(altTextures, 10, FNVAltTexture)
    UINT8_FLAG_MACRO(modelFlags, 11)
    LIST_MACRO(conditions, 12, FNVCondition)
    FORMID_ARRAY_MACRO(animations, 13)
    UINT8_MACRO(group, 14)
    UINT8_MACRO(minLooping, 15)
    UINT8_MACRO(maxLooping, 16)
    UINT8_ARRAY_MACRO(unused1, 17, 1)
    SINT16_MACRO(replayDelay, 18)
    UINT8_FLAG_MACRO(flags, 19)
    UINT8_ARRAY_MACRO(unused2, 20, 1)

    BasicFlagMACRO(IsNoAttacking, flags, 0x00000001)
    BasicInvertedFlagMACRO(IsAttacking, IsNoAttacking)

    MaskedTypeMACRO(IsIdle, group, ~0xC0, 0, IsIdle)
    MaskedTypeMACRO(IsMovement, group, ~0xC0, 1, IsMovement)
    MaskedTypeMACRO(IsLeftArm, group, ~0xC0, 2, IsMovement)
    MaskedTypeMACRO(IsLeftHand, group, ~0xC0, 3, IsMovement)
    MaskedTypeMACRO(IsWeapon, group, ~0xC0, 4, IsMovement)
    MaskedTypeMACRO(IsWeaponUp, group, ~0xC0, 5, IsMovement)
    MaskedTypeMACRO(IsWeaponDown, group, ~0xC0, 6, IsMovement)
    MaskedTypeMACRO(IsSpecialIdle, group, ~0xC0, 7, IsMovement)
    MaskedTypeMACRO(IsWholeBody, group, ~0xC0, 20, IsMovement)
    MaskedTypeMACRO(IsUpperBody, group, ~0xC0, 21, IsMovement)

    BasicFlagMACRO(IsUnknown1, group, 0x40)
    BasicFlagMACRO(IsNotReturnFile, group, 0x80)
    BasicInvertedFlagMACRO(IsReturnFile, IsNotReturnFile)
    copyattrs = FnvBaseRecord.baseattrs + ['modPath', 'modb', 'modt_p',
                                           'altTextures_list', 'modelFlags',
                                           'conditions_list', 'animations',
                                           'group', 'minLooping',
                                           'maxLooping', 'replayDelay',
                                           'flags']
    exportattrs = FnvBaseRecord.baseattrs + ['modPath', 'modb',
                                             'altTextures_list', 'modelFlags',
                                             'conditions_list', 'animations',
                                             'group', 'minLooping',
                                             'maxLooping', 'replayDelay',
                                             'flags']# 'modt_p',

class FnvPACKRecord(FnvBaseRecord):
    _Type = 'PACK'
    class PackScript(BaseComponent):
        FORMID_GROUPEDMACRO(idle, 0)
        UINT8_ARRAY_GROUPEDMACRO(unused1, 1, 4)
        UINT32_GROUPEDMACRO(numRefs, 2)
        UINT32_GROUPEDMACRO(compiledSize, 3)
        UINT32_GROUPEDMACRO(lastIndex, 4)
        UINT16_TYPE_GROUPEDMACRO(scriptType, 5)
        UINT16_FLAG_GROUPEDMACRO(scriptFlags, 6)
        UINT8_ARRAY_GROUPEDMACRO(compiled_p, 7)
        ISTRING_GROUPEDMACRO(scriptText, 8)
        LIST_GROUPEDMACRO(vars, 9, Var)
        FORMID_OR_UINT32_ARRAY_GROUPEDMACRO(references, 10)
        FORMID_GROUPEDMACRO(topic, 11)

        BasicFlagMACRO(IsEnabled, scriptFlags, 0x0001)

        BasicTypeMACRO(IsObject, scriptType, 0x0000, IsQuest)
        BasicTypeMACRO(IsQuest, scriptType, 0x0001, IsObject)
        BasicTypeMACRO(IsEffect, scriptType, 0x0100, IsObject)
        copyattrs = ['idle', 'numRefs', 'compiledSize',
                     'lastIndex', 'scriptType', 'scriptFlags',
                     'compiled_p', 'scriptText',
                     'vars_list', 'references', 'topic']
        exportattrs = ['idle', 'numRefs', 'compiledSize',
                       'lastIndex', 'scriptType', 'scriptFlags',
                       'scriptText',
                       'vars_list', 'references', 'topic']#'compiled_p',

    UINT32_FLAG_MACRO(flags, 7)
    UINT8_TYPE_MACRO(aiType, 8)
    UINT8_ARRAY_MACRO(unused1, 9, 1)
    UINT16_FLAG_MACRO(behaviorFlags, 10)
    UINT16_FLAG_MACRO(specificFlags, 11)
    UINT8_ARRAY_MACRO(unused2, 12, 2)
    SINT32_TYPE_MACRO(loc1Type, 13)
    FORMID_OR_UINT32_MACRO(loc1Id, 14)
    SINT32_MACRO(loc1Radius, 15)
    SINT32_TYPE_MACRO(loc2Type, 16)
    FORMID_OR_UINT32_MACRO(loc2Id, 17)
    SINT32_MACRO(loc2Radius, 18)
    SINT8_MACRO(month, 19)
    SINT8_MACRO(day, 20)
    UINT8_MACRO(date, 21)
    SINT8_MACRO(time, 22)
    SINT32_MACRO(duration, 23)
    SINT32_TYPE_MACRO(target1Type, 24)
    FORMID_OR_UINT32_MACRO(target1Id, 25)
    SINT32_MACRO(target1CountOrDistance, 26)
    FLOAT32_MACRO(target1Unknown, 27)

    LIST_MACRO(conditions, 28, FNVCondition)
    UINT8_FLAG_MACRO(idleAnimFlags, 29)
    UINT8_MACRO(idleAnimCount, 30)
    FLOAT32_MACRO(idleTimer, 31)
    FORMID_ARRAY_MACRO(animations, 32)
    UINT8_ARRAY_MACRO(unusedIDLB_p, 33)
    UINT32_MACRO(escortDistance, 34)
    FORMID_MACRO(combatStyle, 35)
    FLOAT32_MACRO(followTriggerRadius, 36)
    UINT16_TYPE_MACRO(patrolType, 37)
    UINT32_FLAG_MACRO(weaponFlags, 38)
    UINT8_TYPE_MACRO(fireRate, 39)
    UINT8_TYPE_MACRO(fireType, 40)
    UINT16_MACRO(burstNum, 41)
    UINT16_MACRO(minShots, 42)
    UINT16_MACRO(maxShots, 43)
    FLOAT32_MACRO(minPause, 44)
    FLOAT32_MACRO(maxPause, 45)
    UINT8_ARRAY_MACRO(unused3, 46, 4)
    SINT32_TYPE_MACRO(target2Type, 47)
    FORMID_OR_UINT32_MACRO(target2Id, 48)
    SINT32_MACRO(target2CountOrDistance, 49)
    FLOAT32_MACRO(target2Unknown, 50)
    FLOAT32_MACRO(FOV, 51)
    FORMID_MACRO(topic, 52)
    UINT32_FLAG_MACRO(dialFlags, 53)
    UINT8_ARRAY_MACRO(unused4, 54, 4)
    UINT32_TYPE_MACRO(dialType, 55)
    UINT8_ARRAY_MACRO(dialUnknown, 56)
    GroupedValuesMACRO(begin, 57, PackScript)
    GroupedValuesMACRO(end, 69, PackScript)
    GroupedValuesMACRO(change, 81, PackScript)

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
    BasicFlagMACRO(IsHeadTrackingOff, flags, 0x00100000)
    BasicFlagMACRO(IsUnequipWeapons, flags, 0x00200000)
    BasicFlagMACRO(IsDefensiveCombat, flags, 0x00400000)
    BasicFlagMACRO(IsWeaponDrawn, flags, 0x00800000)
    BasicFlagMACRO(IsNoIdleAnims, flags, 0x01000000)
    BasicFlagMACRO(IsPretendInCombat, flags, 0x02000000)
    BasicFlagMACRO(IsContinueDuringCombat, flags, 0x04000000)
    BasicFlagMACRO(IsNoCombatAlert, flags, 0x08000000)
    BasicFlagMACRO(IsNoWarnAttackBehavior, flags, 0x10000000)

    BasicFlagMACRO(IsHellosToPlayer, behaviorFlags, 0x00000001)
    BasicFlagMACRO(IsRandomConversations, behaviorFlags, 0x00000002)
    BasicFlagMACRO(IsObserveCombatBehavior, behaviorFlags, 0x00000004)
    BasicFlagMACRO(IsUnknown4, behaviorFlags, 0x00000008)
    BasicFlagMACRO(IsReactionToPlayerActions, behaviorFlags, 0x00000010)
    BasicFlagMACRO(IsFriendlyFireComments, behaviorFlags, 0x00000020)
    BasicFlagMACRO(IsAggroRadiusBehavior, behaviorFlags, 0x00000040)
    BasicFlagMACRO(IsAllowIdleChatter, behaviorFlags, 0x00000080)
    BasicFlagMACRO(IsAvoidRadiation, behaviorFlags, 0x00000100)

    BasicFlagMACRO(IsHide, specificFlags, 0x00000001) #Ambush only
    BasicFlagMACRO(IsNoEating, specificFlags, 0x00000001)
    BasicFlagMACRO(IsNoSleeping, specificFlags, 0x00000002)
    BasicFlagMACRO(IsSitDown, specificFlags, 0x00000002) #Use Item At only
    BasicFlagMACRO(IsNoConversation, specificFlags, 0x00000004)
    BasicFlagMACRO(IsRemainNearReference, specificFlags, 0x00000004) #Guard only
    BasicFlagMACRO(IsNoIdleMarkers, specificFlags, 0x00000008)
    BasicFlagMACRO(IsNoFurniture, specificFlags, 0x00000010)
    BasicFlagMACRO(IsNoWandering, specificFlags, 0x00000020)
    BasicFlagMACRO(IsAllowBuying, specificFlags, 0x00000100)
    BasicFlagMACRO(IsAllowKilling, specificFlags, 0x00000200)
    BasicFlagMACRO(IsAllowStealing, specificFlags, 0x00000400)

    BasicFlagMACRO(IsRunInSequence, idleAnimFlags, 0x00000001)
    BasicFlagMACRO(IsDoOnce, idleAnimFlags, 0x00000004)

    BasicFlagMACRO(IsAlwaysHit, weaponFlags, 0x00000001)
    BasicFlagMACRO(IsDoNoDamage, weaponFlags, 0x00000100)
    BasicFlagMACRO(IsCrouchToReload, weaponFlags, 0x00010000)
    BasicFlagMACRO(IsHoldFireWhenBlocked, weaponFlags, 0x01000000)

    BasicFlagMACRO(IsNoHeadtracking, dialFlags, 0x00000001)
    BasicFlagMACRO(IsDontControlTargetMovement, dialFlags, 0x00000100)

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
    BasicTypeMACRO(IsAISandbox, aiType, 12, IsAIFind)
    BasicTypeMACRO(IsAIPatrol, aiType, 13, IsAIFind)
    BasicTypeMACRO(IsAIGuard, aiType, 14, IsAIFind)
    BasicTypeMACRO(IsAIDialogue, aiType, 15, IsAIFind)
    BasicTypeMACRO(IsAIUseWeapon, aiType, 16, IsAIFind)

    BasicTypeMACRO(IsLoc1NearReference, loc1Type, 0, IsLoc1InCell)
    BasicTypeMACRO(IsLoc1InCell, loc1Type, 1, IsLoc1NearReference)
    BasicTypeMACRO(IsLoc1NearCurrentLocation, loc1Type, 2, IsLoc1NearReference)
    BasicTypeMACRO(IsLoc1NearEditorLocation, loc1Type, 3, IsLoc1NearReference)
    BasicTypeMACRO(IsLoc1ObjectID, loc1Type, 4, IsLoc1NearReference)
    BasicTypeMACRO(IsLoc1ObjectType, loc1Type, 5, IsLoc1NearReference)
    BasicTypeMACRO(IsLoc1NearLinkedReference, loc1Type, 6, IsLoc1NearReference)
    BasicTypeMACRO(IsLoc1AtPackageLocation, loc1Type, 7, IsLoc1NearReference)

    BasicTypeMACRO(IsLoc2NearReference, loc2Type, 0, IsLoc2InCell)
    BasicTypeMACRO(IsLoc2InCell, loc2Type, 1, IsLoc2NearReference)
    BasicTypeMACRO(IsLoc2NearCurrentLocation, loc2Type, 2, IsLoc2NearReference)
    BasicTypeMACRO(IsLoc2NearEditorLocation, loc2Type, 3, IsLoc2NearReference)
    BasicTypeMACRO(IsLoc2ObjectID, loc2Type, 4, IsLoc2NearReference)
    BasicTypeMACRO(IsLoc2ObjectType, loc2Type, 5, IsLoc2NearReference)
    BasicTypeMACRO(IsLoc2NearLinkedReference, loc2Type, 6, IsLoc2NearReference)
    BasicTypeMACRO(IsLoc2AtPackageLocation, loc2Type, 7, IsLoc2NearReference)

    BasicTypeMACRO(IsAnyDay, day, -1, IsSunday)
    BasicTypeMACRO(IsSunday, day, 0, IsAnyDay)
    BasicTypeMACRO(IsMonday, day, 1, IsAnyDay)
    BasicTypeMACRO(IsTuesday, day, 2, IsAnyDay)
    BasicTypeMACRO(IsWednesday, day, 3, IsAnyDay)
    BasicTypeMACRO(IsThursday, day, 4, IsAnyDay)
    BasicTypeMACRO(IsFriday, day, 5, IsAnyDay)
    BasicTypeMACRO(IsSaturday, day, 6, IsAnyDay)
    BasicTypeMACRO(IsWeekdays, day, 7, IsAnyDay)
    BasicTypeMACRO(IsWeekends, day, 8, IsAnyDay)
    BasicTypeMACRO(IsMWF, day, 9, IsAnyDay)
    BasicTypeMACRO(IsTTh, day, 10, IsAnyDay)

    BasicTypeMACRO(IsTarget1Reference, target1Type, 0, IsTarget1Reference)
    BasicTypeMACRO(IsTarget1ObjectID, target1Type, 1, IsTarget1Reference)
    BasicTypeMACRO(IsTarget1ObjectType, target1Type, 2, IsTarget1Reference)
    BasicTypeMACRO(IsTarget1LinkedReference, target1Type, 3, IsTarget1Reference)

    BasicTypeMACRO(IsTarget2Reference, target2Type, 0, IsTarget2Reference)
    BasicTypeMACRO(IsTarget2ObjectID, target2Type, 1, IsTarget2Reference)
    BasicTypeMACRO(IsTarget2ObjectType, target2Type, 2, IsTarget2Reference)
    BasicTypeMACRO(IsTarget2LinkedReference, target2Type, 3, IsTarget2Reference)

    BasicTypeMACRO(IsNotRepeatable, patrolType, 0, IsRepeatable)
    BasicTypeMACRO(IsRepeatable, patrolType, 1, IsNotRepeatable)

    BasicTypeMACRO(IsAutoFire, fireRate, 0, IsVolleyFire)
    BasicTypeMACRO(IsVolleyFire, fireRate, 1, IsAutoFire)

    BasicTypeMACRO(IsNumberOfBursts, fireType, 0, IsRepeatFire)
    BasicTypeMACRO(IsRepeatFire, fireType, 1, IsNumberOfBursts)

    BasicTypeMACRO(IsConversation, dialType, 0, IsSayTo)
    BasicTypeMACRO(IsSayTo, dialType, 1, IsConversation)
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + ['flags', 'aiType', 'behaviorFlags',
                                                         'specificFlags', 'loc1Type', 'loc1Id',
                                                         'loc1Radius', 'loc2Type', 'loc2Id',
                                                         'loc2Radius', 'month', 'day', 'date',
                                                         'time', 'duration', 'target1Type',
                                                         'target1Id', 'target1CountOrDistance',
                                                         'target1Unknown', 'conditions_list',
                                                         'idleAnimFlags', 'idleAnimCount',
                                                         'idleTimer', 'animations',
                                                         'escortDistance', 'combatStyle',
                                                         'followTriggerRadius', 'patrolType',
                                                         'weaponFlags', 'fireRate', 'fireType',
                                                         'burstNum', 'minShots', 'maxShots',
                                                         'minPause', 'maxPause', 'target2Type',
                                                         'target2Id', 'target2CountOrDistance',
                                                         'target2Unknown', 'FOV', 'topic',
                                                         'dialFlags', 'dialType', 'dialUnknown',
                                                         'begin_list', 'end_list', 'change_list']

class FnvCSTYRecord(FnvBaseRecord):
    _Type = 'CSTY'
    UINT8_MACRO(dodgeChance, 7)
    UINT8_MACRO(lrChance, 8)
    UINT8_ARRAY_MACRO(unused1, 9, 2)
    FLOAT32_MACRO(lrTimerMin, 10)
    FLOAT32_MACRO(lrTimerMax, 11)
    FLOAT32_MACRO(forTimerMin, 12)
    FLOAT32_MACRO(forTimerMax, 13)
    FLOAT32_MACRO(backTimerMin, 14)
    FLOAT32_MACRO(backTimerMax, 15)
    FLOAT32_MACRO(idleTimerMin, 16)
    FLOAT32_MACRO(idleTimerMax, 17)
    UINT8_MACRO(blkChance, 18)
    UINT8_MACRO(atkChance, 19)
    UINT8_ARRAY_MACRO(unused2, 20, 2)
    FLOAT32_MACRO(atkBRecoil, 21)
    FLOAT32_MACRO(atkBUnc, 22)
    FLOAT32_MACRO(atkBh2h, 23)
    UINT8_MACRO(pAtkChance, 24)
    UINT8_ARRAY_MACRO(unused3, 25, 3)
    FLOAT32_MACRO(pAtkBRecoil, 26)
    FLOAT32_MACRO(pAtkBUnc, 27)
    UINT8_MACRO(pAtkNormal, 28)
    UINT8_MACRO(pAtkFor, 29)
    UINT8_MACRO(pAtkBack, 30)
    UINT8_MACRO(pAtkL, 31)
    UINT8_MACRO(pAtkR, 32)
    UINT8_ARRAY_MACRO(unused4, 33, 3)
    FLOAT32_MACRO(holdTimerMin, 34)
    FLOAT32_MACRO(holdTimerMax, 35)
    UINT16_FLAG_MACRO(flags, 36)
    UINT8_ARRAY_MACRO(unused5, 37, 2)
    UINT8_MACRO(acroDodge, 38)
    UINT8_MACRO(rushChance, 39)
    UINT8_ARRAY_MACRO(unused6, 40, 2)
    FLOAT32_MACRO(rushMult, 41)
    FLOAT32_MACRO(dodgeFMult, 42)
    FLOAT32_MACRO(dodgeFBase, 43)
    FLOAT32_MACRO(encSBase, 44)
    FLOAT32_MACRO(encSMult, 45)
    FLOAT32_MACRO(dodgeAtkMult, 46)
    FLOAT32_MACRO(dodgeNAtkMult, 47)
    FLOAT32_MACRO(dodgeBAtkMult, 48)
    FLOAT32_MACRO(dodgeBNAtkMult, 49)
    FLOAT32_MACRO(dodgeFAtkMult, 50)
    FLOAT32_MACRO(dodgeFNAtkMult, 51)
    FLOAT32_MACRO(blockMult, 52)
    FLOAT32_MACRO(blockBase, 53)
    FLOAT32_MACRO(blockAtkMult, 54)
    FLOAT32_MACRO(blockNAtkMult, 55)
    FLOAT32_MACRO(atkMult, 56)
    FLOAT32_MACRO(atkBase, 57)
    FLOAT32_MACRO(atkAtkMult, 58)
    FLOAT32_MACRO(atkNAtkMult, 59)
    FLOAT32_MACRO(atkBlockMult, 60)
    FLOAT32_MACRO(pAtkFBase, 61)
    FLOAT32_MACRO(pAtkFMult, 62)
    FLOAT32_MACRO(coverRadius, 63)
    FLOAT32_MACRO(coverChance, 64)
    FLOAT32_MACRO(waitTimerMin, 65)
    FLOAT32_MACRO(waitTimerMax, 66)
    FLOAT32_MACRO(waitFireTimerMin, 67)
    FLOAT32_MACRO(waitFireTimerMax, 68)
    FLOAT32_MACRO(fireTimerMin, 69)
    FLOAT32_MACRO(fireTimerMax, 70)
    FLOAT32_MACRO(rangedRangeMultMin, 71)
    UINT8_ARRAY_MACRO(unused7, 72, 4)
    UINT32_TYPE_MACRO(weaponRestrictions, 73)
    FLOAT32_MACRO(rangedRangeMultMax, 74)
    FLOAT32_MACRO(targetMaxFOV, 75)
    FLOAT32_MACRO(combatRadius, 76)
    FLOAT32_MACRO(semiAutoFireDelayMultMin, 77)
    FLOAT32_MACRO(semiAutoFireDelayMultMax, 78)

    BasicFlagMACRO(IsUseChanceForAttack, flags, 0x00000001)
    BasicFlagMACRO(IsMeleeAlertOK, flags, 0x00000002)
    BasicFlagMACRO(IsFleeForSurvival, flags, 0x00000004)
    BasicFlagMACRO(IsIgnoreThreats, flags, 0x00000010)
    BasicFlagMACRO(IsIgnoreDamagingSelf, flags, 0x00000020)
    BasicFlagMACRO(IsIgnoreDamagingGroup, flags, 0x00000040)
    BasicFlagMACRO(IsIgnoreDamagingSpectator, flags, 0x00000080)
    BasicFlagMACRO(IsNoUseStealthboy, flags, 0x00000100)

    BasicTypeMACRO(IsNone, weaponRestrictions, 0, IsMeleeOnly)
    BasicTypeMACRO(IsMeleeOnly, weaponRestrictions, 1, IsNone)
    BasicTypeMACRO(IsRangedOnly, weaponRestrictions, 2, IsNone)
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + ['dodgeChance', 'lrChance', 'lrTimerMin',
                                                         'lrTimerMax', 'forTimerMin', 'forTimerMax',
                                                         'backTimerMin', 'backTimerMax', 'idleTimerMin',
                                                         'idleTimerMax', 'blkChance', 'atkChance',
                                                         'atkBRecoil', 'atkBUnc', 'atkBh2h', 'pAtkChance',
                                                         'pAtkBRecoil', 'pAtkBUnc', 'pAtkNormal',
                                                         'pAtkFor', 'pAtkBack', 'pAtkL', 'pAtkR',
                                                         'holdTimerMin', 'holdTimerMax', 'flags',
                                                         'acroDodge', 'rushChance', 'rushMult',
                                                         'dodgeFMult', 'dodgeFBase', 'encSBase',
                                                         'encSMult', 'dodgeAtkMult', 'dodgeNAtkMult',
                                                         'dodgeBAtkMult', 'dodgeBNAtkMult',
                                                         'dodgeFAtkMult', 'dodgeFNAtkMult', 'blockMult',
                                                         'blockBase', 'blockAtkMult', 'blockNAtkMult',
                                                         'atkMult', 'atkBase', 'atkAtkMult',
                                                         'atkNAtkMult', 'atkBlockMult', 'pAtkFBase',
                                                         'pAtkFMult', 'coverRadius', 'coverChance',
                                                         'waitTimerMin', 'waitTimerMax',
                                                         'waitFireTimerMin', 'waitFireTimerMax',
                                                         'fireTimerMin', 'fireTimerMax',
                                                         'rangedRangeMultMin', 'weaponRestrictions',
                                                         'rangedRangeMultMax', 'targetMaxFOV',
                                                         'combatRadius', 'semiAutoFireDelayMultMin',
                                                         'semiAutoFireDelayMultMax']

class FnvLSCRRecord(FnvBaseRecord):
    _Type = 'LSCR'
    class Location(ListComponent):
        FORMID_LISTMACRO(direct, 1)
        FORMID_LISTMACRO(indirect, 2)
        SINT16_LISTMACRO(gridY, 3)
        SINT16_LISTMACRO(gridX, 4)
        exportattrs = copyattrs = ['direct', 'indirect', 'gridY', 'gridX']

    ISTRING_MACRO(iconPath, 7)
    ISTRING_MACRO(smallIconPath, 8)
    STRING_MACRO(text, 9)

    LIST_MACRO(locations, 10, self.Location)
    FORMID_MACRO(screentype, 11)
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + ['iconPath', 'smallIconPath', 'text',
                                                         'locations_list', 'screentype']

class FnvANIORecord(FnvBaseRecord):
    _Type = 'ANIO'
    ISTRING_MACRO(modPath, 7)
    FLOAT32_MACRO(modb, 8)
    UINT8_ARRAY_MACRO(modt_p, 9)

    LIST_MACRO(altTextures, 10, FNVAltTexture)
    UINT8_FLAG_MACRO(modelFlags, 11)
    FORMID_MACRO(animation, 12)
    copyattrs = FnvBaseRecord.baseattrs + ['modPath', 'modb', 'modt_p',
                                           'altTextures_list',
                                           'modelFlags', 'animation']
    exportattrs = FnvBaseRecord.baseattrs + ['modPath', 'modb',
                                             'altTextures_list',
                                             'modelFlags', 'animation']# 'modt_p',

class FnvWATRRecord(FnvBaseRecord):
    _Type = 'WATR'
    STRING_MACRO(full, 7)
    ISTRING_MACRO(noisePath, 8)
    UINT8_MACRO(opacity, 9)
    UINT8_MACRO(flags, 10)
    ISTRING_MACRO(material, 11)
    FORMID_MACRO(sound, 12)
    FORMID_MACRO(effect, 13)
    UINT16_MACRO(damage, 14)
    FLOAT32_MACRO(unknown1, 15)
    FLOAT32_MACRO(unknown2, 16)
    FLOAT32_MACRO(unknown3, 17)
    FLOAT32_MACRO(unknown4, 18)
    FLOAT32_MACRO(sunPower, 19)
    FLOAT32_MACRO(reflectAmt, 20)
    FLOAT32_MACRO(fresnelAmt, 21)
    UINT8_ARRAY_MACRO(unused1, 22, 4)
    FLOAT32_MACRO(fogNear, 23)
    FLOAT32_MACRO(fogFar, 24)
    UINT8_MACRO(shallowRed, 25)
    UINT8_MACRO(shallowGreen, 26)
    UINT8_MACRO(shallowBlue, 27)
    UINT8_ARRAY_MACRO(unused2, 28, 1)
    UINT8_MACRO(deepRed, 29)
    UINT8_MACRO(deepGreen, 30)
    UINT8_MACRO(deepBlue, 31)
    UINT8_ARRAY_MACRO(unused3, 32, 1)
    UINT8_MACRO(reflRed, 33)
    UINT8_MACRO(reflGreen, 34)
    UINT8_MACRO(reflBlue, 35)
    UINT8_ARRAY_MACRO(unused4, 36, 1)
    UINT8_ARRAY_MACRO(unused5, 37, 4)
    FLOAT32_MACRO(rainForce, 38)
    FLOAT32_MACRO(rainVelocity, 39)
    FLOAT32_MACRO(rainFalloff, 40)
    FLOAT32_MACRO(rainDampner, 41)
    FLOAT32_MACRO(dispSize, 42)
    FLOAT32_MACRO(dispForce, 43)
    FLOAT32_MACRO(dispVelocity, 44)
    FLOAT32_MACRO(dispFalloff, 45)
    FLOAT32_MACRO(dispDampner, 46)
    FLOAT32_MACRO(rainSize, 47)
    FLOAT32_MACRO(normalsNoiseScale, 48)
    FLOAT32_MACRO(noise1Direction, 49)
    FLOAT32_MACRO(noise2Direction, 50)
    FLOAT32_MACRO(noise3Direction, 51)
    FLOAT32_MACRO(noise1Speed, 52)
    FLOAT32_MACRO(noise2Speed, 53)
    FLOAT32_MACRO(noise3Speed, 54)
    FLOAT32_MACRO(normalsFalloffStart, 55)
    FLOAT32_MACRO(normalsFalloffEnd, 56)
    FLOAT32_MACRO(fogAmt, 57)
    FLOAT32_MACRO(normalsUVScale, 58)
    FLOAT32_MACRO(underFogAmt, 59)
    FLOAT32_MACRO(underFogNear, 60)
    FLOAT32_MACRO(underFogFar, 61)
    FLOAT32_MACRO(distAmt, 62)
    FLOAT32_MACRO(shininess, 63)
    FLOAT32_MACRO(hdrMult, 64)
    FLOAT32_MACRO(lightRadius, 65)
    FLOAT32_MACRO(lightBright, 66)
    FLOAT32_MACRO(noise1UVScale, 67)
    FLOAT32_MACRO(noise2UVScale, 68)
    FLOAT32_MACRO(noise3UVScale, 69)
    FLOAT32_MACRO(noise1AmpScale, 70)
    FLOAT32_MACRO(noise2AmpScale, 71)
    FLOAT32_MACRO(noise3AmpScale, 72)
    FORMID_MACRO(dayWater, 73)
    FORMID_MACRO(nightWater, 74)
    FORMID_MACRO(underWater, 75)
    BasicFlagMACRO(IsCausesDamage, flags, 0x01)
    BasicFlagMACRO(IsReflective, flags, 0x02)
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + ['full', 'noisePath', 'opacity', 'flags',
                                                         'material', 'sound', 'effect', 'damage',
                                                         'unknown1', 'unknown2', 'unknown3', 'unknown4',
                                                         'sunPower', 'reflectAmt', 'fresnelAmt',
                                                         'fogNear', 'fogFar',
                                                         'shallowRed', 'shallowGreen', 'shallowBlue',
                                                         'deepRed', 'deepGreen', 'deepBlue',
                                                         'reflRed', 'reflGreen', 'reflBlue',
                                                         'rainForce', 'rainVelocity', 'rainFalloff',
                                                         'rainDampner', 'dispSize', 'dispForce',
                                                         'dispVelocity', 'dispFalloff', 'dispDampner',
                                                         'rainSize', 'normalsNoiseScale',
                                                         'noise1Direction', 'noise2Direction', 'noise3Direction',
                                                         'noise1Speed', 'noise2Speed', 'noise3Speed',
                                                         'normalsFalloffStart', 'normalsFalloffEnd',
                                                         'fogAmt', 'normalsUVScale', 'underFogAmt', 'underFogNear',
                                                         'underFogFar', 'distAmt', 'shininess', 'hdrMult',
                                                         'lightRadius', 'lightBright',
                                                         'noise1UVScale', 'noise2UVScale', 'noise3UVScale',
                                                         'noise1AmpScale', 'noise2AmpScale', 'noise3AmpScale',
                                                         'dayWater', 'nightWater', 'underWater']

class FnvEFSHRecord(FnvBaseRecord):
    _Type = 'EFSH'
    ISTRING_MACRO(fillPath, 7)
    ISTRING_MACRO(particlePath, 8)
    ISTRING_MACRO(holesPath, 9)
    UINT8_FLAG_MACRO(flags, 10)
    UINT8_ARRAY_MACRO(unused1, 11, 3)
    UINT32_MACRO(memSBlend, 12)
    UINT32_MACRO(memBlendOp, 13)
    UINT32_MACRO(memZFunc, 14)
    UINT8_MACRO(fillRed, 15)
    UINT8_MACRO(fillGreen, 16)
    UINT8_MACRO(fillBlue, 17)
    UINT8_ARRAY_MACRO(unused2, 18, 1)
    FLOAT32_MACRO(fillAIn, 19)
    FLOAT32_MACRO(fillAFull, 20)
    FLOAT32_MACRO(fillAOut, 21)
    FLOAT32_MACRO(fillAPRatio, 22)
    FLOAT32_MACRO(fillAAmp, 23)
    FLOAT32_MACRO(fillAFreq, 24)
    FLOAT32_MACRO(fillAnimSpdU, 25)
    FLOAT32_MACRO(fillAnimSpdV, 26)
    FLOAT32_MACRO(edgeEffOff, 27)
    UINT8_MACRO(edgeEffRed, 28)
    UINT8_MACRO(edgeEffGreen, 29)
    UINT8_MACRO(edgeEffBlue, 30)
    UINT8_ARRAY_MACRO(unused3, 31, 1)
    FLOAT32_MACRO(edgeEffAIn, 32)
    FLOAT32_MACRO(edgeEffAFull, 33)
    FLOAT32_MACRO(edgeEffAOut, 34)
    FLOAT32_MACRO(edgeEffAPRatio, 35)
    FLOAT32_MACRO(edgeEffAAmp, 36)
    FLOAT32_MACRO(edgeEffAFreq, 37)
    FLOAT32_MACRO(fillAFRatio, 38)
    FLOAT32_MACRO(edgeEffAFRatio, 39)
    UINT32_MACRO(memDBlend, 40)
    UINT32_MACRO(partSBlend, 41)
    UINT32_MACRO(partBlendOp, 42)
    UINT32_MACRO(partZFunc, 43)
    UINT32_MACRO(partDBlend, 44)
    FLOAT32_MACRO(partBUp, 45)
    FLOAT32_MACRO(partBFull, 46)
    FLOAT32_MACRO(partBDown, 47)
    FLOAT32_MACRO(partBFRatio, 48)
    FLOAT32_MACRO(partBPRatio, 49)
    FLOAT32_MACRO(partLTime, 50)
    FLOAT32_MACRO(partLDelta, 51)
    FLOAT32_MACRO(partNSpd, 52)
    FLOAT32_MACRO(partNAcc, 53)
    FLOAT32_MACRO(partVel1, 54)
    FLOAT32_MACRO(partVel2, 55)
    FLOAT32_MACRO(partVel3, 56)
    FLOAT32_MACRO(partAcc1, 57)
    FLOAT32_MACRO(partAcc2, 58)
    FLOAT32_MACRO(partAcc3, 59)
    FLOAT32_MACRO(partKey1, 60)
    FLOAT32_MACRO(partKey2, 61)
    FLOAT32_MACRO(partKey1Time, 62)
    FLOAT32_MACRO(partKey2Time, 63)
    UINT8_MACRO(key1Red, 64)
    UINT8_MACRO(key1Green, 65)
    UINT8_MACRO(key1Blue, 66)
    UINT8_ARRAY_MACRO(unused4, 67, 1)
    UINT8_MACRO(key2Red, 68)
    UINT8_MACRO(key2Green, 69)
    UINT8_MACRO(key2Blue, 70)
    UINT8_ARRAY_MACRO(unused5, 71, 1)
    UINT8_MACRO(key3Red, 72)
    UINT8_MACRO(key3Green, 73)
    UINT8_MACRO(key3Blue, 74)
    UINT8_ARRAY_MACRO(unused6, 75, 1)
    FLOAT32_MACRO(key1A, 76)
    FLOAT32_MACRO(key2A, 77)
    FLOAT32_MACRO(key3A, 78)
    FLOAT32_MACRO(key1Time, 79)
    FLOAT32_MACRO(key2Time, 80)
    FLOAT32_MACRO(key3Time, 81)
    FLOAT32_MACRO(partInitSpd, 82)
    FLOAT32_MACRO(partInitRot, 83)
    FLOAT32_MACRO(partInitRotDelta, 84)
    FLOAT32_MACRO(partRotSpd, 85)
    FLOAT32_MACRO(partRotDelta, 86)
    FORMID_MACRO(addon, 87)
    FLOAT32_MACRO(holesSTime, 88)
    FLOAT32_MACRO(holesETime, 89)
    FLOAT32_MACRO(holesSValue, 90)
    FLOAT32_MACRO(holesEValue, 91)
    FLOAT32_MACRO(edgeWidth, 92)
    UINT8_MACRO(edgeRed, 93)
    UINT8_MACRO(edgeGreen, 94)
    UINT8_MACRO(edgeBlue, 95)
    UINT8_ARRAY_MACRO(unused7, 96, 1)
    FLOAT32_MACRO(explWindSpd, 97)
    UINT32_MACRO(textCountU, 98)
    UINT32_MACRO(textCountV, 99)
    FLOAT32_MACRO(addonFITime, 100)
    FLOAT32_MACRO(addonFOTime, 101)
    FLOAT32_MACRO(addonScaleStart, 102)
    FLOAT32_MACRO(addonScaleEnd, 103)
    FLOAT32_MACRO(addonScaleInTime, 104)
    FLOAT32_MACRO(addonScaleOutTime, 105)

    BasicFlagMACRO(IsNoMemShader, flags, 0x00000001)
    BasicFlagMACRO(IsNoPartShader, flags, 0x00000008)
    BasicFlagMACRO(IsEdgeInverse, flags, 0x00000010)
    BasicFlagMACRO(IsMemSkinOnly, flags, 0x00000020)
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + ['fillPath', 'particlePath', 'holesPath',
                                                         'flags', 'memSBlend', 'memBlendOp',
                                                         'memZFunc',
                                                         'fillRed', 'fillGreen', 'fillBlue',
                                                         'fillAIn', 'fillAFull', 'fillAOut',
                                                         'fillAPRatio', 'fillAAmp', 'fillAFreq',
                                                         'fillAnimSpdU', 'fillAnimSpdV',
                                                         'edgeEffOff',
                                                         'edgeEffRed', 'edgeEffGreen', 'edgeEffBlue',
                                                         'edgeEffAIn', 'edgeEffAFull', 'edgeEffAOut',
                                                         'edgeEffAPRatio', 'edgeEffAAmp',
                                                         'edgeEffAFreq', 'fillAFRatio',
                                                         'edgeEffAFRatio', 'memDBlend', 'partSBlend',
                                                         'partBlendOp', 'partZFunc', 'partDBlend',
                                                         'partBUp', 'partBFull', 'partBDown',
                                                         'partBFRatio', 'partBPRatio', 'partLTime',
                                                         'partLDelta', 'partNSpd', 'partNAcc',
                                                         'partVel1', 'partVel2', 'partVel3',
                                                         'partAcc1', 'partAcc2', 'partAcc3',
                                                         'partKey1', 'partKey2',
                                                         'partKey1Time', 'partKey2Time',
                                                         'key1Red', 'key1Green', 'key1Blue',
                                                         'key2Red', 'key2Green', 'key2Blue',
                                                         'key3Red', 'key3Green', 'key3Blue',
                                                         'key1A', 'key2A', 'key3A',
                                                         'key1Time', 'key2Time', 'key3Time',
                                                         'partInitSpd', 'partInitRot',
                                                         'partInitRotDelta', 'partRotSpd',
                                                         'partRotDelta', 'addon', 'holesSTime',
                                                         'holesETime', 'holesSValue', 'holesEValue',
                                                         'edgeWidth',
                                                         'edgeRed', 'edgeGreen', 'edgeBlue',
                                                         'explWindSpd', 'textCountU', 'textCountV',
                                                         'addonFITime', 'addonFOTime',
                                                         'addonScaleStart', 'addonScaleEnd',
                                                         'addonScaleInTime', 'addonScaleOutTime']

class FnvEXPLRecord(FnvBaseRecord):
    _Type = 'EXPL'
    SINT16_MACRO(boundX1, 7)
    SINT16_MACRO(boundY1, 8)
    SINT16_MACRO(boundZ1, 9)
    SINT16_MACRO(boundX2, 10)
    SINT16_MACRO(boundY2, 11)
    SINT16_MACRO(boundZ2, 12)
    STRING_MACRO(full, 13)
    ISTRING_MACRO(modPath, 14)
    FLOAT32_MACRO(modb, 15)
    UINT8_ARRAY_MACRO(modt_p, 16)

    LIST_MACRO(altTextures, 17, FNVAltTexture)
    UINT8_FLAG_MACRO(modelFlags, 18)
    FORMID_MACRO(effect, 19)
    FORMID_MACRO(imageSpace, 20)
    FLOAT32_MACRO(force, 21)
    FLOAT32_MACRO(damage, 22)
    FLOAT32_MACRO(radius, 23)
    FORMID_MACRO(light, 24)
    FORMID_MACRO(sound1, 25)
    UINT32_FLAG_MACRO(flags, 26)
    FLOAT32_MACRO(ISRadius, 27)
    FORMID_MACRO(impactDataSet, 28)
    FORMID_MACRO(sound2, 29)
    FLOAT32_MACRO(radLevel, 30)
    FLOAT32_MACRO(radTime, 31)
    FLOAT32_MACRO(radRadius, 32)
    UINT32_MACRO(soundLevel, 33)
    FORMID_MACRO(impact, 34)

    BasicFlagMACRO(IsUnknown1, flags, 0x00000001)
    BasicFlagMACRO(IsAlwaysUsesWorldOrientation, flags, 0x00000002)
    BasicFlagMACRO(IsAlwaysKnockDown, flags, 0x00000004)
    BasicFlagMACRO(IsFormulaKnockDown, flags, 0x00000008)
    BasicFlagMACRO(IsIgnoreLOS, flags, 0x00000010)
    BasicFlagMACRO(IsPushExplosionSourceRefOnly, flags, 0x00000020)
    BasicFlagMACRO(IsIgnoreImageSpaceSwap, flags, 0x00000040)

    BasicFlagMACRO(IsHead, modelFlags, 0x01)
    BasicFlagMACRO(IsTorso, modelFlags, 0x02)
    BasicFlagMACRO(IsRightHand, modelFlags, 0x04)
    BasicFlagMACRO(IsLeftHand, modelFlags, 0x08)

    BasicTypeMACRO(IsLoud, soundLevel, 0, IsNormal)
    BasicTypeMACRO(IsNormal, soundLevel, 1, IsLoud)
    BasicTypeMACRO(IsSilent, soundLevel, 2, IsLoud)
    copyattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                           'boundX2', 'boundY2', 'boundZ2',
                                           'full', 'modPath', 'modb', 'modt_p',
                                           'altTextures_list', 'modelFlags',
                                           'effect', 'imageSpace', 'force',
                                           'damage', 'radius', 'light',
                                           'sound1', 'flags', 'ISRadius',
                                           'impactDataSet', 'sound2',
                                           'radLevel', 'radTime',
                                           'radRadius', 'soundLevel', 'impact']
    exportattrs = FnvBaseRecord.baseattrs + ['boundX1', 'boundY1', 'boundZ1',
                                             'boundX2', 'boundY2', 'boundZ2',
                                             'full', 'modPath', 'modb',
                                             'altTextures_list', 'modelFlags',
                                             'effect', 'imageSpace', 'force',
                                             'damage', 'radius', 'light',
                                             'sound1', 'flags', 'ISRadius',
                                             'impactDataSet', 'sound2',
                                             'radLevel', 'radTime',
                                             'radRadius', 'soundLevel', 'impact']# 'modt_p',

class FnvDEBRRecord(FnvBaseRecord):
    _Type = 'DEBR'
    class DebrisModel(ListComponent):
        UINT8_LISTMACRO(percentage, 1)
        ISTRING_LISTMACRO(modPath, 2)
        UINT8_FLAG_LISTMACRO(flags, 3)
        UINT8_ARRAY_LISTMACRO(modt_p, 4)

        BasicFlagMACRO(IsHasCollisionData, flags, 0x01)
        copyattrs = ['percentage', 'modPath', 'flags', 'modt_p']
        exportattrs = ['percentage', 'modPath', 'flags']#, 'modt_p'

    LIST_MACRO(models, 7, self.DebrisModel)
    exportattrs = copyattrs = FnvBaseRecord.baseattrs + ['models_list']

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
    def __init__(self, RecordID):
        self._RecordID = RecordID

    def __eq__(self, other):
        if type(other) is type(self):
            return self._RecordID == other._RecordID
        return False

    def __ne__(self, other):
        return not self.__eq__(other)

    def GetParentMod(self):
        return ObModFile(_CGetModIDByRecordID(self._RecordID))

    def GetParentCollection(self):
        return ObCollection(_CGetCollectionIDByRecordID(self._RecordID))

    def ResetRecord(self):
        _CResetRecord(self._RecordID)

    def UnloadRecord(self):
        _CUnloadRecord(self._RecordID)

    def DeleteRecord(self):
        _CDeleteRecord(self._RecordID)

    def GetRecordUpdatedReferences(self):
        return _CGetRecordUpdatedReferences(0, self._RecordID)

    def UpdateReferences(self, Old_NewFormIDs):
        Old_NewFormIDs = FormID.FilterValidDict(Old_NewFormIDs, self, True, True)
        length = len(Old_NewFormIDs)
        if length != len(Old_NewFormIDs):
            return []
        OldFormIDs = (c_ulong * length)(*Old_NewFormIDs.keys())
        NewFormIDs = (c_ulong * length)(*Old_NewFormIDs.values())
        Changes = (c_ulong * length)()
        _CUpdateReferences(0, self._RecordID, OldFormIDs, NewFormIDs, byref(Changes), length)
        return [x for x in Changes]

    def History(self):
        cRecordIDs = (c_ulong * 257)() #just allocate enough for the max number + size
        numRecords = _CGetRecordHistory(self._RecordID, byref(cRecordIDs))
        return [self.__class__(self._RecordID, cRecordIDs[x]) for x in range(0, numRecords)]

    def IsWinning(self, GetExtendedConflicts=False):
        """Returns true if the record is the last to load.
           If GetExtendedConflicts is True, scanned records will be considered.
           More efficient than running Conflicts() and checking the first value."""
        return _CIsRecordWinning(self._RecordID, c_ulong(GetExtendedConflicts))

    def Conflicts(self, GetExtendedConflicts=False):
        numRecords = _CGetNumRecordConflicts(self._RecordID, c_ulong(GetExtendedConflicts)) #gives upper bound
        if(numRecords > 1):
            cRecordIDs = (c_ulong * numRecords)()
            numRecords = _CGetRecordConflicts(self._RecordID, byref(cRecordIDs), c_ulong(GetExtendedConflicts))
            return [self.__class__(cRecordIDs[x]) for x in range(0, numRecords)]
        return []

    def ConflictDetails(self, attrs=None, GetExtendedConflicts=False):
        """New: attrs is an iterable, for each item, the following is checked:
           if the item is a string type: changes are reported
           if the item is another iterable (set,list,tuple), then if any of the subitems is
             different, then all sub items are reported.  This allows grouping of dependant
             items."""
        conflicting = {}
        if attrs is None:
            attrs = self.copyattrs
        if not attrs:
            return conflicting

        parentRecords = self.History()
        if parentRecords:
            for attr in attrs:
                if isinstance(attr,basestring):
                    # Single attr
                    conflicting.update([(attr,reduce(getattr, attr.split('.'), self)) for parentRecord in parentRecords if reduce(getattr, attr.split('.'), self) != reduce(getattr, attr.split('.'), parentRecord)])
                elif isinstance(attr,(list,tuple,set)):
                    # Group of attrs that need to stay together
                    for parentRecord in parentRecords:
                        subconflicting = {}
                        conflict = False
                        for subattr in attr:
                            self_value = reduce(getattr, subattr.split('.'), self)
                            if not conflict and self_value != reduce(getattr, subattr.split('.'), parentRecord):
                                conflict = True
                            subconflicting.update([(subattr,self_value)])
                        if conflict:
                            conflicting.update(subconflicting)
        else: #is the first instance of the record
            for attr in attrs:
                if isinstance(attr, basestring):
                    conflicting.update([(attr,reduce(getattr, attr.split('.'), self))])
                elif isinstance(attr,(list,tuple,set)):
                    conflicting.update([(subattr,reduce(getattr, subattr.split('.'), self)) for subattr in attr])

        skipped_conflicting = [(attr, value) for attr, value in conflicting.iteritems() if isinstance(value, FormID) and not value.ValidateFormID(self)]
        for attr, value in skipped_conflicting:
            try:
                deprint(_("%s attribute of %s record (maybe named: %s) importing from %s referenced an unloaded object (probably %s) - value skipped") % (attr, self.fid, self.full, self.GetParentMod().GName, value))
            except: #a record type that doesn't have a full chunk:
                deprint(_("%s attribute of %s record importing from %s referenced an unloaded object (probably %s) - value skipped") % (attr, self.fid, self.GetParentMod().GName, value))
            del conflicting[attr]

        return conflicting

    def mergeFilter(self,modSet):
        """This method is called by the bashed patch mod merger. The intention is
        to allow a record to be filtered according to the specified modSet. E.g.
        for a list record, items coming from mods not in the modSet could be
        removed from the list.

        In a case where items either cannot be filtered, or doing so will break
        the record, False should be returned.  If filtering was successful, True
        should be returned."""
        return True

    def CopyAsOverride(self, target, UseWinningParents=False, CopyFlags=0):
        if hasattr(self, '_ParentID'):
            if isinstance(target, ObModFile):
                DestParentID = self._ParentID
                DestModID = target._ModID
            else:
                DestParentID = target._RecordID
                DestModID = target.GetParentMod()._ModID
        else:
            DestParentID = 0
            DestModID = target._ModID

        ##Record Creation Flags
        ##SetAsOverride       = 0x00000001
        ##CopyWinningParent   = 0x00000002
        #Set SetAsOverride
        CopyFlags |= 0x00000001
        if UseWinningParents:
            CopyFlags |= 0x00000002
        RecordID = _CCopyRecord(self._RecordID, DestModID, DestParentID, 0, 0, c_ulong(CopyFlags))
        #Clear SetAsOverride
        CopyFlags &= ~0x00000001
        if(RecordID): return self.__class__(RecordID)
        return None

    def CopyAsNew(self, target, UseWinningParents=False, RecordFormID=0, CopyFlags=0):
        if hasattr(self, '_ParentID'):
            if isinstance(target, ObModFile):
                DestParentID = self._ParentID
                DestModID = target._ModID
            else:
                DestParentID = target._RecordID
                DestModID = target.GetParentMod()._ModID
        else:
            DestParentID = 0
            DestModID = target._ModID
        if RecordFormID:
            RecordFormID = RecordFormID.GetShortFormID(target)
        ##Record Creation Flags
        ##SetAsOverride       = 0x00000001
        ##CopyWinningParent   = 0x00000002
        #Clear SetAsOverride in case it was set
        CopyFlags &= ~0x00000001
        if UseWinningParents:
            CopyFlags |= 0x00000002
        RecordID = _CCopyRecord(self._RecordID, DestModID, DestParentID, RecordFormID, 0, c_ulong(CopyFlags))
        if(RecordID): return self.__class__(RecordID)
        return None

    @property
    def Parent(self):
        RecordID = getattr(self, '_ParentID', 0)
        if RecordID:
            testRecord = ObBaseRecord(RecordID)
            RecordType = type_record[testRecord.recType]
            if RecordType:
                return RecordType(RecordID)
        return None

    @property
    def recType(self):
        _CGetFieldAttribute.restype = (c_char * 4)
        retValue = _CGetFieldAttribute(self._RecordID, 0, 0, 0, 0, 0, 0, 0, 0)
        _CGetFieldAttribute.restype = c_ulong
        if(retValue and retValue.value != ''): return retValue.value
        return None

    UINT32_FLAG_MACRO(flags1, 1)

    def get_fid(self):
        _CGetField.restype = POINTER(c_ulong)
        retValue = _CGetField(self._RecordID, 2, 0, 0, 0, 0, 0, 0, 0)
        if(retValue): return FormID(self._RecordID, retValue.contents.value)
        return None
    def set_fid(self, nValue):
        if nValue is None: nValue = 0
        else: nValue = nValue.GetShortFormID(self)
        _CSetIDFields(self._RecordID, nValue, self.eid or 0)
    fid = property(get_fid, set_fid)

    UINT32_FLAG_MACRO(flags2, 3)

    def get_eid(self):
        _CGetField.restype = c_char_p
        retValue = _CGetField(self._RecordID, 4, 0, 0, 0, 0, 0, 0, 0)
        if(retValue): return ISTRING(retValue)
        return None
    def set_eid(self, nValue):
        if nValue is None or not len(nValue): nValue = 0
        else: nValue = str(nValue)
        _CGetField.restype = POINTER(c_ulong)
        _CSetIDFields(self._RecordID, _CGetField(self._RecordID, 2, 0, 0, 0, 0, 0, 0, 0).contents.value, nValue)
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

class ObTES4Record(object):
    _Type = 'TES4'
    def __init__(self, RecordID):
        self._RecordID = RecordID

    def GetParentMod(self):
        return ObModFile(_CGetModIDByRecordID(self._RecordID))

    def GetParentCollection(self):
        return ObCollection(_CGetCollectionIDByRecordID(self._RecordID))

    def ResetRecord(self):
        pass

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

class ObGMSTRecord(ObBaseRecord):
    _Type = 'GMST'
    def get_value(self):
        rFormat = _CGetFieldAttribute(self._RecordID, 5, 0, 0, 0, 0, 0, 0, 2)
        if(rFormat == API_FIELDS.UNKNOWN):
            return None
        elif(rFormat == API_FIELDS.SINT32):
            _CGetField.restype = POINTER(c_long)
            retValue = _CGetField(self._RecordID, 5, 0, 0, 0, 0, 0, 0, 0)
            if(retValue): return retValue.contents.value
        elif(rFormat == API_FIELDS.FLOAT32):
            _CGetField.restype = POINTER(c_float)
            retValue = _CGetField(self._RecordID, 5, 0, 0, 0, 0, 0, 0, 0)
            if(retValue): return round(retValue.contents.value,6)
        elif(rFormat == API_FIELDS.STRING):
            _CGetField.restype = c_char_p
            return _CGetField(self._RecordID, 5, 0, 0, 0, 0, 0, 0, 0)
        return None
    def set_value(self, nValue):
        if nValue is None: _CDeleteField(self._RecordID, 5, 0, 0, 0, 0, 0, 0)
        else:
            rFormat = _CGetFieldAttribute(self._RecordID, 5, 0, 0, 0, 0, 0, 0, 2)
            if(rFormat == API_FIELDS.SINT32 and type(nValue) is int):
                _CSetField(self._RecordID, 5, 0, 0, 0, 0, 0, 0, byref(c_long(nValue)), 0)
            elif(rFormat == API_FIELDS.FLOAT32 == 10 and type(nValue) is float):
                _CSetField(self._RecordID, 5, 0, 0, 0, 0, 0, 0, byref(c_float(round(nValue,6))), 0)
            elif(rFormat == API_FIELDS.STRING and isinstance(nValue, basestring)):
                _CSetField(self._RecordID, 5, 0, 0, 0, 0, 0, 0, nValue, 0)
    value = property(get_value, set_value)
    exportattrs = copyattrs = ObBaseRecord.baseattrs + ['value']

class ObACHRRecord(ObBaseRecord):
    @property
    def _ParentID(self):
        _CGetField.restype = c_ulong
        return _CGetField(self._RecordID, 24, 0, 0, 0, 0, 0, 0, 0)

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
    copyattrs = ObBaseRecord.baseattrs + ['base', 'unknownXPCIFormID', 'unknownXPCIString',
                                        'lod1', 'lod2', 'lod3', 'parent', 'parentFlags',
                                        'merchantContainer', 'horse', 'xrgd_p', 'scale',
                                        'posX', 'posY', 'posZ', 'rotX', 'rotY', 'rotZ']
    exportattrs = ObBaseRecord.baseattrs + ['base', 'unknownXPCIFormID', 'unknownXPCIString',
                                        'lod1', 'lod2', 'lod3', 'parent', 'parentFlags',
                                        'merchantContainer', 'horse', 'scale',
                                        'posX', 'posY', 'posZ', 'rotX', 'rotY', 'rotZ'] #'xrgd_p',

class ObACRERecord(ObBaseRecord):
    @property
    def _ParentID(self):
        _CGetField.restype = c_ulong
        return _CGetField(self._RecordID, 23, 0, 0, 0, 0, 0, 0, 0)

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
    copyattrs = ObBaseRecord.baseattrs + ['base', 'owner', 'rank', 'globalVariable',
                                        'lod1', 'lod2', 'lod3', 'parent', 'parentFlags',
                                        'xrgd_p', 'scale', 'posX', 'posY', 'posZ', 'rotX',
                                        'rotY', 'rotZ']
    exportattrs = ObBaseRecord.baseattrs + ['base', 'owner', 'rank', 'globalVariable',
                                        'lod1', 'lod2', 'lod3', 'parent', 'parentFlags',
                                        'scale', 'posX', 'posY', 'posZ', 'rotX',
                                        'rotY', 'rotZ'] #'xrgd_p',

class ObREFRRecord(ObBaseRecord):
    @property
    def _ParentID(self):
        _CGetField.restype = c_ulong
        return _CGetField(self._RecordID, 50, 0, 0, 0, 0, 0, 0, 0)

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
    @property
    def _ParentID(self):
        _CGetField.restype = c_ulong
        return _CGetField(self._RecordID, 23, 0, 0, 0, 0, 0, 0, 0)

    _Type = 'INFO'
    class Response(ListComponent):
        UINT32_TYPE_LISTMACRO(emotionType, 1)
        SINT32_LISTMACRO(emotionValue, 2)
        UINT8_ARRAY_LISTMACRO(unused1, 3, 4)
        UINT8_LISTMACRO(responseNum, 4)
        UINT8_ARRAY_LISTMACRO(unused2, 5, 3)
        STRING_LISTMACRO(responseText, 6)
        ISTRING_LISTMACRO(actorNotes, 7)
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
    BasicTypeMACRO(IsObject, scriptType, 0x00000000, IsQuest)
    BasicTypeMACRO(IsQuest, scriptType, 0x00000001, IsObject)
    BasicTypeMACRO(IsMagicEffect, scriptType, 0x00000100, IsObject)
    BasicFlagMACRO(IsGoodbye, flags, 0x00000001)
    BasicFlagMACRO(IsRandom, flags, 0x00000002)
    BasicFlagMACRO(IsSayOnce, flags, 0x00000004)
    BasicFlagMACRO(IsRunImmediately, flags, 0x00000008)
    BasicFlagMACRO(IsInfoRefusal, flags, 0x00000010)
    BasicFlagMACRO(IsRandomEnd, flags, 0x00000020)
    BasicFlagMACRO(IsRunForRumors, flags, 0x00000040)
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
    @property
    def _ParentID(self):
        _CGetField.restype = c_ulong
        return _CGetField(self._RecordID, 15, 0, 0, 0, 0, 0, 0, 0)

    _Type = 'LAND'
    class Normal(ListX2Component):
        UINT8_LISTX2MACRO(x, 1)
        UINT8_LISTX2MACRO(y, 2)
        UINT8_LISTX2MACRO(z, 3)
        exportattrs = copyattrs = ['x', 'y', 'z']

    class Height(ListX2Component):
        SINT8_LISTX2MACRO(height, 1)
        exportattrs = copyattrs = ['height']

    class Color(ListX2Component):
        UINT8_LISTX2MACRO(red, 1)
        UINT8_LISTX2MACRO(green, 2)
        UINT8_LISTX2MACRO(blue, 3)
        exportattrs = copyattrs = ['red', 'green', 'blue']

    class BaseTexture(ListComponent):
        FORMID_LISTMACRO(texture, 1)
        SINT8_LISTMACRO(quadrant, 2)
        UINT8_ARRAY_LISTMACRO(unused1, 3, 1)
        SINT16_LISTMACRO(layer, 4)
        exportattrs = copyattrs = ['texture', 'quadrant', 'layer']

    class AlphaLayer(ListComponent):
        class Opacity(ListX2Component):
            UINT16_LISTX2MACRO(position, 1)
            UINT8_ARRAY_LISTX2MACRO(unused1, 2, 2)
            FLOAT32_LISTX2MACRO(opacity, 3)
            exportattrs = copyattrs = ['position', 'opacity']
        FORMID_LISTMACRO(texture, 1)
        SINT8_LISTMACRO(quadrant, 2)
        UINT8_ARRAY_LISTMACRO(unused1, 3, 1)
        SINT16_LISTMACRO(layer, 4)

        LIST_LISTMACRO(opacities, 5, self.Opacity)
        exportattrs = copyattrs = ['texture', 'quadrant', 'layer', 'opacities_list']

    class VertexTexture(ListComponent):
        FORMID_LISTMACRO(texture, 1)
        exportattrs = copyattrs = ['texture']

    class Position(ListX2Component):
        FLOAT32_LISTX2MACRO(height, 1)
        UINT8_LISTX2MACRO(normalX, 2)
        UINT8_LISTX2MACRO(normalY, 3)
        UINT8_LISTX2MACRO(normalZ, 4)
        UINT8_LISTX2MACRO(red, 5)
        UINT8_LISTX2MACRO(green, 6)
        UINT8_LISTX2MACRO(blue, 7)
        FORMID_LISTX2MACRO(baseTexture, 8)
        FORMID_LISTX2MACRO(alphaLayer1Texture, 9)
        FLOAT32_LISTX2MACRO(alphaLayer1Opacity, 10)
        FORMID_LISTX2MACRO(alphaLayer2Texture, 11)
        FLOAT32_LISTX2MACRO(alphaLayer2Opacity, 12)
        FORMID_LISTX2MACRO(alphaLayer3Texture, 13)
        FLOAT32_LISTX2MACRO(alphaLayer3Opacity, 14)
        FORMID_LISTX2MACRO(alphaLayer4Texture, 15)
        FLOAT32_LISTX2MACRO(alphaLayer4Opacity, 16)
        FORMID_LISTX2MACRO(alphaLayer5Texture, 17)
        FLOAT32_LISTX2MACRO(alphaLayer5Opacity, 18)
        FORMID_LISTX2MACRO(alphaLayer6Texture, 19)
        FLOAT32_LISTX2MACRO(alphaLayer6Opacity, 20)
        FORMID_LISTX2MACRO(alphaLayer7Texture, 21)
        FLOAT32_LISTX2MACRO(alphaLayer7Opacity, 22)
        FORMID_LISTX2MACRO(alphaLayer8Texture, 23)
        FLOAT32_LISTX2MACRO(alphaLayer8Opacity, 24)
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

    UINT8_ARRAY_MACRO(data_p, 5)

    def get_normals(self):
        return [[self.Normal(self._RecordID, 6, x, 0, y) for y in range(0,33)] for x in range(0,33)]
    def set_normals(self, nElements):
        if nElements is None or len(nElements) != 33: return
        if isinstance(nElements[0], tuple): nValues = nElements
        else: nValues = [ExtractCopyList(nElements[x]) for x in range(0,33)]
        oElements = self.normals
        for x in range(0,33):
            SetCopyList(oElements[x], nValues[x])
    normals = property(get_normals, set_normals)
    def get_normals_list(self):
        return [ExtractCopyList([self.Normal(self._RecordID, 6, x, 0, y) for y in range(0,33)]) for x in range(0,33)]

    normals_list = property(get_normals_list, set_normals)

    FLOAT32_MACRO(heightOffset, 7)

    def get_heights(self):
        return [[self.Height(self._RecordID, 8, x, 0, y) for y in range(0,33)] for x in range(0,33)]
    def set_heights(self, nElements):
        if nElements is None or len(nElements) != 33: return
        if isinstance(nElements[0], tuple): nValues = nElements
        else: nValues = [ExtractCopyList(nElements[x]) for x in range(0,33)]
        oElements = self.heights
        for x in range(0,33):
            SetCopyList(oElements[x], nValues[x])
    heights = property(get_heights, set_heights)
    def get_heights_list(self):
        return [ExtractCopyList([self.Height(self._RecordID, 8, x, 0, y) for y in range(0,33)]) for x in range(0,33)]
    heights_list = property(get_heights_list, set_heights)

    UINT8_ARRAY_MACRO(unused1, 9, 3)

    def get_colors(self):
        return [[self.Color(self._RecordID, 10, x, 0, y) for y in range(0,33)] for x in range(0,33)]
    def set_colors(self, nElements):
        if nElements is None or len(nElements) != 33: return
        if isinstance(nElements[0], tuple): nValues = nElements
        else: nValues = [ExtractCopyList(nElements[x]) for x in range(0,33)]
        oElements = self.colors
        for x in range(0,33):
            SetCopyList(oElements[x], nValues[x])
    colors = property(get_colors, set_colors)
    def get_colors_list(self):
        return [ExtractCopyList([self.Color(self._RecordID, 10, x, 0, y) for y in range(0,33)]) for x in range(0,33)]
    colors_list = property(get_colors_list, set_colors)

    LIST_MACRO(baseTextures, 11, self.BaseTexture)
    LIST_MACRO(alphaLayers, 12, self.AlphaLayer)
    LIST_MACRO(vertexTextures, 13, self.VertexTexture)
    ##The Positions accessor is unique in that it duplicates the above accessors. It just presents the data in a more friendly format.
    def get_Positions(self):
        return [[self.Position(self._RecordID, 14, row, 0, column) for column in range(0,33)] for row in range(0,33)]
    def set_Positions(self, nElements):
        if nElements is None or len(nElements) != 33: return
        if isinstance(nElements[0], tuple): nValues = nElements
        else: nValues = [ExtractCopyList(nElements[x]) for x in range(0,33)]
        oElements = self.Positions
        for x in range(0,33):
            SetCopyList(oElements[x], nValues[x])
    Positions = property(get_Positions, set_Positions)
    def get_Positions_list(self):
        return [ExtractCopyList([self.Position(self._RecordID, 14, x, 0, y) for y in range(0,33)]) for x in range(0,33)]
    Positions_list = property(get_Positions_list, set_Positions)
    copyattrs = ObBaseRecord.baseattrs + ['data_p', 'normals_list', 'heights_list', 'heightOffset',
                                        'colors_list', 'baseTextures_list', 'alphaLayers_list',
                                        'vertexTextures_list']
    exportattrs = ObBaseRecord.baseattrs + ['normals_list', 'heights_list', 'heightOffset',
                                        'colors_list', 'baseTextures_list', 'alphaLayers_list',
                                        'vertexTextures_list'] #'data_p',

class ObPGRDRecord(ObBaseRecord):
    @property
    def _ParentID(self):
        _CGetField.restype = c_ulong
        return _CGetField(self._RecordID, 11, 0, 0, 0, 0, 0, 0, 0)

    _Type = 'PGRD'
    class PGRI(ListComponent):
        UINT16_LISTMACRO(point, 1)
        UINT8_ARRAY_LISTMACRO(unused1, 2, 2)
        FLOAT32_LISTMACRO(x, 3)
        FLOAT32_LISTMACRO(y, 4)
        FLOAT32_LISTMACRO(z, 5)
        exportattrs = copyattrs = ['point', 'x', 'y', 'z']

    class PGRL(ListComponent):
        FORMID_LISTMACRO(reference, 1)
        UINT32_ARRAY_LISTMACRO(points, 2)
        exportattrs = copyattrs = ['reference', 'points']

    UINT16_MACRO(count, 5)

    LIST_MACRO(pgrp, 6, PGRP)
    UINT8_ARRAY_MACRO(pgag_p, 7)
    UINT8_ARRAY_MACRO(pgrr_p, 8)

    LIST_MACRO(pgri, 9, self.PGRI)
    LIST_MACRO(pgrl, 10, self.PGRL)
    copyattrs = ObBaseRecord.baseattrs + ['count', 'pgrp_list', 'pgag_p', 'pgrr_p',
                                        'pgri_list', 'pgrl_list']
    exportattrs = ObBaseRecord.baseattrs + ['count', 'pgrp_list',
                                        'pgri_list', 'pgrl_list'] # 'pgag_p', 'pgrr_p',

class ObROADRecord(ObBaseRecord):
    @property
    def _ParentID(self):
        _CGetField.restype = c_ulong
        return _CGetField(self._RecordID, 7, 0, 0, 0, 0, 0, 0, 0)

    _Type = 'ROAD'
    class PGRR(ListComponent):
        FLOAT32_LISTMACRO(x, 1)
        FLOAT32_LISTMACRO(y, 2)
        FLOAT32_LISTMACRO(z, 3)
        exportattrs = copyattrs = ['x', 'y', 'z']

    LIST_MACRO(pgrp, 5, PGRP)
    LIST_MACRO(pgrr, 6, self.PGRR)
    exportattrs = copyattrs = ObBaseRecord.baseattrs + ['pgrp_list', 'pgrr_list']

class ObACTIRecord(ObBaseRecord):
    _Type = 'ACTI'
    STRING_MACRO(full, 5)
    ISTRING_MACRO(modPath, 6)
    FLOAT32_MACRO(modb, 7)
    UINT8_ARRAY_MACRO(modt_p, 8)
    FORMID_MACRO(script, 9)
    FORMID_MACRO(sound, 10)
    copyattrs = ObBaseRecord.baseattrs + ['full', 'modPath', 'modb', 'modt_p', 'script',
                                        'sound']
    exportattrs = ObBaseRecord.baseattrs + ['full', 'modPath', 'modb', 'script', 'sound'] #'modt_p',

class ObALCHRecord(ObBaseRecord):
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
    BasicInvertedFlagMACRO(IsAutoCalc, IsNoAutoCalc)
    BasicFlagMACRO(IsFood, flags, 0x00000002)
    ##OBME Fields. Setting any of the below fields will make the mod require JRoush's OBME plugin for OBSE
    ##To see if OBME is in use, check the recordVersion field for a non-None value
    OBMEUINT8_MACRO(recordVersion, 16)
    OBMEUINT8_MACRO(betaVersion, 17)
    OBMEUINT8_MACRO(minorVersion, 18)
    OBMEUINT8_MACRO(majorVersion, 19)
    OBMEUINT8_ARRAY_MACRO(reserved, 20, 0x1C)
    OBMEUINT8_ARRAY_MACRO(datx_p, 21, 0x20)
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
    ISTRING_MACRO(modPath, 5)
    FLOAT32_MACRO(modb, 6)
    UINT8_ARRAY_MACRO(modt_p, 7)
    FORMID_MACRO(animationId, 8)
    copyattrs = ObBaseRecord.baseattrs + ['modPath', 'modb', 'modt_p', 'animationId']
    exportattrs = ObBaseRecord.baseattrs + ['modPath', 'modb', 'animationId'] #'modt_p',

class ObAPPARecord(ObBaseRecord):
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
    copyattrs = ObBaseRecord.baseattrs + ['full', 'modPath', 'modb', 'modt_p',
                                        'iconPath', 'script', 'apparatusType',
                                        'value', 'weight', 'quality']
    exportattrs = ObBaseRecord.baseattrs + ['full', 'modPath', 'modb',
                                        'iconPath', 'script', 'apparatusType',
                                        'value', 'weight', 'quality'] # 'modt_p',

class ObARMORecord(ObBaseRecord):
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
    exportattrs = copyattrs = ObBaseRecord.baseattrs + ['full', 'script', 'enchantment', 'enchantPoints',
                                        'flags', 'maleBody_list', 'maleWorld_list', 'maleIconPath',
                                        'femaleBody_list', 'femaleWorld_list', 'femaleIconPath',
                                        'strength', 'value', 'health', 'weight']

class ObBOOKRecord(ObBaseRecord):
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
    STRING_MACRO(full, 5)
    ISTRING_MACRO(iconPath, 6)
    STRING_MACRO(text, 7)
    FORMID_ARRAY_MACRO(spells, 8)
    exportattrs = copyattrs = ObBaseRecord.baseattrs + ['full', 'iconPath', 'text', 'spells']

class ObCELLRecord(ObBaseRecord):
    _Type = 'CELL'
    @property
    def _ParentID(self):
        _CGetField.restype = c_ulong
        return _CGetField(self._RecordID, 40, 0, 0, 0, 0, 0, 0, 0)

    @property
    def bsb(self):
        """Returns tesfile block and sub-block indices for cells in this group.
        For interior cell, bsb is (blockNum,subBlockNum). For exterior cell, bsb is
        ((blockX,blockY),(subblockX,subblockY))."""
        #--Interior cell
        if self.IsInterior:
            ObjectID = self.fid[1]
            blockNum = ObjectID % 10
            subBlockNum = (ObjectID / 10) % 10
            return (blockNum, subBlockNum)
        #--Exterior cell
        else:
            blockX = int(math.floor(self.posX or 0 / 8.0))
            blockY = int(math.floor(self.posY or 0 / 8.0))
            subblockX = int(math.floor(blockX / 4.0))
            subblockY = int(math.floor(blockY / 4.0))
            return ((blockX, blockY), (subblockX, subblockY))

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
    UNKNOWN_OR_SINT32_MACRO(posX, 32)
    UNKNOWN_OR_SINT32_MACRO(posY, 33)
    FORMID_MACRO(water, 34)
    SUBRECORD_ARRAY_MACRO(ACHR, "ACHR", 35, ObACHRRecord)
    SUBRECORD_ARRAY_MACRO(ACRE, "ACRE", 36, ObACRERecord)
    SUBRECORD_ARRAY_MACRO(REFR, "REFR", 37, ObREFRRecord)
    SUBRECORD_MACRO(PGRD, "PGRD", 38, ObPGRDRecord)
    SUBRECORD_MACRO(LAND, "LAND", 39, ObLANDRecord)
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
    exportattrs = copyattrs = ObBaseRecord.baseattrs + ['full', 'flags', 'ambientRed', 'ambientGreen', 'ambientBlue',
                                        'directionalRed', 'directionalGreen', 'directionalBlue',
                                        'fogRed', 'fogGreen', 'fogBlue', 'fogNear', 'fogFar',
                                        'directionalXY', 'directionalZ', 'directionalFade', 'fogClip',
                                        'musicType', 'owner', 'rank', 'globalVariable',
                                        'climate', 'waterHeight', 'regions', 'posX', 'posY',
                                        'water']

class ObCLASRecord(ObBaseRecord):
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
    exportattrs = copyattrs = ObBaseRecord.baseattrs + ['full', 'description', 'iconPath', 'primary1',
                                        'primary2', 'specialization', 'major1',
                                        'major2', 'major3', 'major4', 'major5',
                                        'major6', 'major7', 'flags', 'services',
                                        'trainSkill', 'trainLevel']

class ObCLMTRecord(ObBaseRecord):
    _Type = 'CLMT'
    class Weather(ListComponent):
        FORMID_LISTMACRO(weather, 1)
        SINT32_LISTMACRO(chance, 2)
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
    copyattrs = ObBaseRecord.baseattrs + ['weathers_list', 'sunPath', 'glarePath', 'modPath',
                                        'modb', 'modt_p', 'riseBegin', 'riseEnd',
                                        'setBegin', 'setEnd', 'volatility', 'phaseLength']
    exportattrs = ObBaseRecord.baseattrs + ['weathers_list', 'sunPath', 'glarePath', 'modPath',
                                        'modb', 'riseBegin', 'riseEnd',
                                        'setBegin', 'setEnd', 'volatility', 'phaseLength'] #'modt_p',

class ObCLOTRecord(ObBaseRecord):
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
        return True

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
        return True

    class Sound(ListComponent):
        UINT32_LISTMACRO(soundType, 1)
        FORMID_LISTMACRO(sound, 2)
        UINT8_LISTMACRO(chance, 3)
        BasicTypeMACRO(IsLeftFoot, soundType, 0, IsRightFoot)
        BasicTypeMACRO(IsRightFoot, soundType, 1, IsLeftFoot)
        BasicTypeMACRO(IsLeftBackFoot, soundType, 2, IsLeftFoot)
        BasicTypeMACRO(IsRightBackFoot, soundType, 3, IsLeftFoot)
        BasicTypeMACRO(IsIdle, soundType, 4, IsLeftFoot)
        BasicTypeMACRO(IsAware, soundType, 5, IsLeftFoot)
        BasicTypeMACRO(IsAttack, soundType, 6, IsLeftFoot)
        BasicTypeMACRO(IsHit, soundType, 7, IsLeftFoot)
        BasicTypeMACRO(IsDeath, soundType, 8, IsLeftFoot)
        BasicTypeMACRO(IsWeapon, soundType, 9, IsLeftFoot)
        exportattrs = copyattrs = ['soundType', 'sound', 'chance']

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
    FORMID_ARRAY_MACRO(quests, 5)
    FORMID_ARRAY_MACRO(removedQuests, 6)
    STRING_MACRO(full, 7)
    UINT8_TYPE_MACRO(dialType, 8)
    SUBRECORD_ARRAY_MACRO(INFO, "INFO", 9, ObINFORecord)
    BasicTypeMACRO(IsTopic, dialType, 0, IsConversation)
    BasicTypeMACRO(IsConversation, dialType, 1, IsTopic)
    BasicTypeMACRO(IsCombat, dialType, 2, IsTopic)
    BasicTypeMACRO(IsPersuasion, dialType, 3, IsTopic)
    BasicTypeMACRO(IsDetection, dialType, 4, IsTopic)
    BasicTypeMACRO(IsService, dialType, 5, IsTopic)
    BasicTypeMACRO(IsMisc, dialType, 6, IsTopic)
    exportattrs = copyattrs = ObBaseRecord.baseattrs + ['quests', 'removedQuests',
                                        'full', 'dialType']

class ObDOORRecord(ObBaseRecord):
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
    STRING_MACRO(full, 5)
    UINT32_TYPE_MACRO(itemType, 6)
    UINT32_MACRO(chargeAmount, 7)
    UINT32_MACRO(enchantCost, 8)
    UINT8_FLAG_MACRO(flags, 9)
    UINT8_ARRAY_MACRO(unused1, 10, 3)

    LIST_MACRO(effects, 11, Effect)
    BasicFlagMACRO(IsNoAutoCalc, flags, 0x00000001)
    BasicInvertedFlagMACRO(IsAutoCalc, IsNoAutoCalc)
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
    exportattrs = copyattrs = ObBaseRecord.baseattrs + ['full', 'itemType', 'chargeAmount',
                                        'enchantCost', 'flags', 'effects_list']
    copyattrsOBME = copyattrs + ['recordVersion', 'betaVersion',
                                 'minorVersion', 'majorVersion',
                                 'reserved'] #, 'datx_p'

class ObEYESRecord(ObBaseRecord):
    _Type = 'EYES'
    STRING_MACRO(full, 5)
    ISTRING_MACRO(iconPath, 6)
    UINT8_FLAG_MACRO(flags, 7)
    BasicFlagMACRO(IsPlayable, flags, 0x00000001)
    exportattrs = copyattrs = ObBaseRecord.baseattrs + ['full', 'iconPath', 'flags']

class ObFACTRecord(ObBaseRecord):
    _Type = 'FACT'
    class Rank(ListComponent):
        SINT32_LISTMACRO(rank, 1)
        STRING_LISTMACRO(male, 2)
        STRING_LISTMACRO(female, 3)
        ISTRING_LISTMACRO(insigniaPath, 4)
        exportattrs = copyattrs = ['rank', 'male', 'female', 'insigniaPath']

    STRING_MACRO(full, 5)

    LIST_MACRO(relations, 6, Relation)
    UINT8_FLAG_MACRO(flags, 7)
    FLOAT32_MACRO(crimeGoldMultiplier, 8)

    LIST_MACRO(ranks, 9, self.Rank)
    BasicFlagMACRO(IsHiddenFromPC, flags, 0x00000001)
    BasicFlagMACRO(IsEvil, flags, 0x00000002)
    BasicFlagMACRO(IsSpecialCombat, flags, 0x00000004)
    exportattrs = copyattrs = ObBaseRecord.baseattrs + ['full', 'relations_list', 'flags',
                                        'crimeGoldMultiplier', 'ranks_list']

class ObFLORRecord(ObBaseRecord):
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
    copyattrs = ObBaseRecord.baseattrs + ['full', 'modPath', 'modb', 'modt_p',
                                        'script', 'ingredient', 'spring',
                                        'summer', 'fall', 'winter']
    exportattrs = ObBaseRecord.baseattrs + ['full', 'modPath', 'modb',
                                        'script', 'ingredient', 'spring',
                                        'summer', 'fall', 'winter'] # 'modt_p',

class ObFURNRecord(ObBaseRecord):
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
    copyattrs = ObBaseRecord.baseattrs + ['full', 'modPath', 'modb',
                                        'modt_p', 'script', 'flags']
    exportattrs = ObBaseRecord.baseattrs + ['full', 'modPath', 'modb',
                                        'script', 'flags'] #'modt_p',

class ObGLOBRecord(ObBaseRecord):
    _Type = 'GLOB'
    CHAR_MACRO(format, 5)
    FLOAT32_MACRO(value, 6)
    exportattrs = copyattrs = ObBaseRecord.baseattrs + ['format', 'value']

class ObGRASRecord(ObBaseRecord):
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
    copyattrs = ObBaseRecord.baseattrs + ['full', 'modPath', 'modb',
                                        'modt_p', 'iconPath', 'flags']
    exportattrs = ObBaseRecord.baseattrs + ['full', 'modPath', 'modb',
                                        'iconPath', 'flags'] #'modt_p',

class ObIDLERecord(ObBaseRecord):
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
    copyattrs = ObBaseRecord.baseattrs + ['modPath', 'modb', 'modt_p',
                                        'conditions_list', 'group', 'parent', 'prevId']
    exportattrs = ObBaseRecord.baseattrs + ['modPath', 'modb', 'conditions_list',
                                            'group', 'parent', 'prevId'] # 'modt_p',

class ObINGRRecord(ObBaseRecord):
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
    BasicInvertedFlagMACRO(IsAutoCalc, IsNoAutoCalc)
    BasicFlagMACRO(IsFood, flags, 0x00000002)
    ##OBME Fields. Setting any of the below fields will make the mod require JRoush's OBME plugin for OBSE
    ##To see if OBME is in use, check the recordVersion field for a non-None value
    UINT8_MACRO(recordVersion, 16)
    UINT8_MACRO(betaVersion, 17)
    UINT8_MACRO(minorVersion, 18)
    UINT8_MACRO(majorVersion, 19)
    UINT8_ARRAY_MACRO(reserved, 20, 0x1C)
    UINT8_ARRAY_MACRO(datx_p, 21, 0x20)
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
    STRING_MACRO(full, 5)
    ISTRING_MACRO(modPath, 6)
    FLOAT32_MACRO(modb, 7)
    UINT8_ARRAY_MACRO(modt_p, 8)
    ISTRING_MACRO(iconPath, 9)
    FORMID_MACRO(script, 10)
    SINT32_MACRO(value, 11)
    FLOAT32_MACRO(weight, 12)
    copyattrs = ObBaseRecord.baseattrs + ['full', 'modPath', 'modb', 'modt_p', 'iconPath',
                                        'script', 'value', 'weight']
    exportattrs = ObBaseRecord.baseattrs + ['full', 'modPath', 'modb', 'iconPath',
                                        'script', 'value', 'weight'] #'modt_p',

class ObLIGHRecord(ObBaseRecord):
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
        FORMID_LISTMACRO(direct, 1)
        FORMID_LISTMACRO(indirect, 2)
        SINT16_LISTMACRO(gridY, 3)
        SINT16_LISTMACRO(gridX, 4)
        exportattrs = copyattrs = ['direct', 'indirect', 'gridY', 'gridX']

    ISTRING_MACRO(iconPath, 5)
    STRING_MACRO(text, 6)

    LIST_MACRO(locations, 7, self.Location)
    exportattrs = copyattrs = ObBaseRecord.baseattrs + ['iconPath', 'text', 'locations_list']

class ObLTEXRecord(ObBaseRecord):
    _Type = 'LTEX'
    ISTRING_MACRO(iconPath, 5)
    UINT8_TYPE_MACRO(types, 6)
    UINT8_MACRO(friction, 7)
    UINT8_MACRO(restitution, 8)
    UINT8_MACRO(specular, 9)
    FORMID_ARRAY_MACRO(grass, 10)
    BasicTypeMACRO(IsStone, types, 0, IsDirt)
    BasicTypeMACRO(IsCloth, types, 1, IsDirt)
    BasicTypeMACRO(IsDirt, types, 2, IsStone)
    BasicTypeMACRO(IsGlass, types, 3, IsDirt)
    BasicTypeMACRO(IsGrass, types, 4, IsDirt)
    BasicTypeMACRO(IsMetal, types, 5, IsDirt)
    BasicTypeMACRO(IsOrganic, types, 6, IsDirt)
    BasicTypeMACRO(IsSkin, types, 7, IsDirt)
    BasicTypeMACRO(IsWater, types, 8, IsDirt)
    BasicTypeMACRO(IsWood, types, 9, IsDirt)
    BasicTypeMACRO(IsHeavyStone, types, 10, IsDirt)
    BasicTypeMACRO(IsHeavyMetal, types, 11, IsDirt)
    BasicTypeMACRO(IsHeavyWood, types, 12, IsDirt)
    BasicTypeMACRO(IsChain, types, 13, IsDirt)
    BasicTypeMACRO(IsSnow, types, 14, IsDirt)
    BasicTypeMACRO(IsStoneStairs, types, 15, IsDirt)
    BasicTypeMACRO(IsClothStairs, types, 16, IsDirt)
    BasicTypeMACRO(IsDirtStairs, types, 17, IsDirt)
    BasicTypeMACRO(IsGlassStairs, types, 18, IsDirt)
    BasicTypeMACRO(IsGrassStairs, types, 19, IsDirt)
    BasicTypeMACRO(IsMetalStairs, types, 20, IsDirt)
    BasicTypeMACRO(IsOrganicStairs, types, 21, IsDirt)
    BasicTypeMACRO(IsSkinStairs, types, 22, IsDirt)
    BasicTypeMACRO(IsWaterStairs, types, 23, IsDirt)
    BasicTypeMACRO(IsWoodStairs, types, 24, IsDirt)
    BasicTypeMACRO(IsHeavyStoneStairs, types, 25, IsDirt)
    BasicTypeMACRO(IsHeavyMetalStairs, types, 26, IsDirt)
    BasicTypeMACRO(IsHeavyWoodStairs, types, 27, IsDirt)
    BasicTypeMACRO(IsChainStairs, types, 28, IsDirt)
    BasicTypeMACRO(IsSnowStairs, types, 29, IsDirt)
    BasicTypeMACRO(IsElevator, types, 30, IsDirt)
    exportattrs = copyattrs = ObBaseRecord.baseattrs + ['iconPath', 'types', 'friction', 'restitution',
                                        'specular', 'grass']

class ObLVLCRecord(ObBaseRecord):
    _Type = 'LVLC'
    class Entry(ListComponent):
        SINT16_LISTMACRO(level, 1)
        UINT8_ARRAY_LISTMACRO(unused1, 2, 2)
        FORMID_LISTMACRO(listId, 3)
        SINT16_LISTMACRO(count, 4)
        UINT8_ARRAY_LISTMACRO(unused2, 5, 2)
        exportattrs = copyattrs = ['level', 'listId', 'count']

    def mergeFilter(self,modSet):
        """Filter out items that don't come from specified modSet."""
        self.entries = [entry for entry in self.entries if entry.listId[0] in modSet]
        return True

    UINT8_MACRO(chanceNone, 5)
    UINT8_FLAG_MACRO(flags, 6)
    FORMID_MACRO(script, 7)
    FORMID_MACRO(template, 8)

    LIST_MACRO(entries, 9, self.Entry)
    BasicFlagMACRO(IsCalcFromAllLevels, flags, 0x00000001)
    BasicFlagMACRO(IsCalcForEachItem, flags, 0x00000002)
    BasicFlagMACRO(IsUseAllSpells, flags, 0x00000004)
    exportattrs = copyattrs = ObBaseRecord.baseattrs + ['chanceNone', 'flags', 'script',
                                        'template', 'entries_list']

class ObLVLIRecord(ObBaseRecord):
    _Type = 'LVLI'
    class Entry(ListComponent):
        SINT16_LISTMACRO(level, 1)
        UINT8_ARRAY_LISTMACRO(unused1, 2, 2)
        FORMID_LISTMACRO(listId, 3)
        SINT16_LISTMACRO(count, 4)
        UINT8_ARRAY_LISTMACRO(unused2, 5, 2)
        exportattrs = copyattrs = ['level', 'listId', 'count']

    def mergeFilter(self,modSet):
        """Filter out items that don't come from specified modSet."""
        self.entries = [entry for entry in self.entries if entry.listId[0] in modSet]
        return True

    UINT8_MACRO(chanceNone, 5)
    UINT8_FLAG_MACRO(flags, 6)
    JUNK_MACRO(script, 7) #Doesn't actually exist, but is here so that LVLC,LVLI,LVSP can be processed similarly
    JUNK_MACRO(template, 8) #ditto

    LIST_MACRO(entries, 9, self.Entry)
    BasicFlagMACRO(IsCalcFromAllLevels, flags, 0x00000001)
    BasicFlagMACRO(IsCalcForEachItem, flags, 0x00000002)
    BasicFlagMACRO(IsUseAllSpells, flags, 0x00000004)
    exportattrs = copyattrs = ObBaseRecord.baseattrs + ['chanceNone', 'flags', 'entries_list']

class ObLVSPRecord(ObBaseRecord):
    _Type = 'LVSP'
    class Entry(ListComponent):
        SINT16_LISTMACRO(level, 1)
        UINT8_ARRAY_LISTMACRO(unused1, 2, 2)
        FORMID_LISTMACRO(listId, 3)
        SINT16_LISTMACRO(count, 4)
        UINT8_ARRAY_LISTMACRO(unused2, 5, 2)
        exportattrs = copyattrs = ['level', 'listId', 'count']

    def mergeFilter(self,modSet):
        """Filter out items that don't come from specified modSet."""
        self.entries = [entry for entry in self.entries if entry.listId[0] in modSet]
        return True

    UINT8_MACRO(chanceNone, 5)
    UINT8_FLAG_MACRO(flags, 6)
    JUNK_MACRO(script, 7) #Doesn't actually exist, but is here so that LVLC,LVLI,LVSP can be processed similarly
    JUNK_MACRO(template, 8) #ditto

    LIST_MACRO(entries, 9, self.Entry)
    BasicFlagMACRO(IsCalcFromAllLevels, flags, 0x00000001)
    BasicFlagMACRO(IsCalcForEachItem, flags, 0x00000002)
    BasicFlagMACRO(IsUseAllSpells, flags, 0x00000004)
    exportattrs = copyattrs = ObBaseRecord.baseattrs + ['chanceNone', 'flags', 'entries_list']

class ObMGEFRecord(ObBaseRecord):
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
    OBMEBasicFlagMACRO(IsParamFlagA, OBMEFlags, 0x00000004) #Meaning varies with effect handler
    OBMEBasicFlagMACRO(IsParamFlagB, OBMEFlags, 0x00010000) #Meaning varies with effect handler
    OBMEBasicFlagMACRO(IsParamFlagC, OBMEFlags, 0x00080000) #Meaning varies with effect handler
    OBMEBasicFlagMACRO(IsParamFlagD, OBMEFlags, 0x00100000) #Meaning varies with effect handler
    OBMEBasicFlagMACRO(IsHidden, OBMEFlags, 0x40000000)
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
    STRING_MACRO(full, 5)
    ISTRING_MACRO(modPath, 6)
    FLOAT32_MACRO(modb, 7)
    UINT8_ARRAY_MACRO(modt_p, 8)
    ISTRING_MACRO(iconPath, 9)
    FORMID_MACRO(script, 10)
    SINT32_MACRO(value, 11)
    FLOAT32_MACRO(weight, 12)
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
        return True

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
    exportattrs = copyattrs = ObBaseRecord.baseattrs + ['flags', 'aiType', 'locType', 'locId',
                                        'locRadius', 'month', 'day', 'date', 'time',
                                        'duration', 'targetType', 'targetId',
                                        'targetCount', 'conditions_list']

class ObQUSTRecord(ObBaseRecord):
    _Type = 'QUST'
    def mergeFilter(self,modSet):
        """Filter out items that don't come from specified modSet.
        Filters items."""
        self.conditions = [x for x in self.conditions if (
            (not isinstance(x.param1,FormID) or x.param1[0] in modSet)
            and
            (not isinstance(x.param2,FormID) or x.param2[0] in modSet)
            )]
        #for target in self.targets_list:
        #    target.conditions = [x for x in target.conditions_list if (
        #        (not isinstance(x.param1,FormID) or x.param1[0] in modSet)
        #        and
        #        (not isinstance(x.param2,FormID) or x.param2[0] in modSet)
        #        )]
        return True

    class Stage(ListComponent):
        class Entry(ListX2Component):
            class ConditionX3(ListX3Component):
                UINT8_FLAG_TYPE_LISTX3MACRO(operType, 1)
                UINT8_ARRAY_LISTX3MACRO(unused1, 2, 3)
                FLOAT32_LISTX3MACRO(compValue, 3)
                UINT32_TYPE_LISTX3MACRO(ifunc, 4)
                UNKNOWN_OR_FORMID_OR_UINT32_LISTX3MACRO(param1, 5)
                UNKNOWN_OR_FORMID_OR_UINT32_LISTX3MACRO(param2, 6)
                UINT8_ARRAY_LISTX3MACRO(unused2, 7, 4)
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

            UINT8_FLAG_LISTX2MACRO(flags, 1)

            LIST_LISTX2MACRO(conditions, 2, self.ConditionX3)
            STRING_LISTX2MACRO(text, 3)
            UINT8_ARRAY_LISTX2MACRO(unused1, 4, 4)
            UINT32_LISTX2MACRO(numRefs, 5)
            UINT32_LISTX2MACRO(compiledSize, 6)
            UINT32_LISTX2MACRO(lastIndex, 7)
            UINT32_LISTX2MACRO(scriptType, 8)
            UINT8_ARRAY_LISTX2MACRO(compiled_p, 9)
            ISTRING_LISTX2MACRO(scriptText, 10)
            FORMID_OR_UINT32_ARRAY_LISTX2MACRO(references, 11)
            BasicFlagMACRO(IsCompletes, flags, 0x00000001)
            BasicTypeMACRO(IsObject, scriptType, 0x00000000, IsQuest)
            BasicTypeMACRO(IsQuest, scriptType, 0x00000001, IsObject)
            BasicTypeMACRO(IsMagicEffect, scriptType, 0x00000100, IsObject)
            copyattrs = ['flags', 'conditions_list', 'text', 'numRefs', 'compiledSize',
                         'lastIndex', 'scriptType', 'compiled_p', 'scriptText',
                         'references']
            exportattrs = ['flags', 'conditions_list', 'text', 'numRefs', 'compiledSize',
                         'lastIndex', 'scriptType', 'scriptText',
                         'references'] #'compiled_p',

        UINT16_LISTMACRO(stage, 1)

        LIST_LISTMACRO(entries, 2, self.Entry)
        exportattrs = copyattrs = ['stage', 'entries_list']

    class Target(ListComponent):
        class ConditionX2(ListX2Component):
            UINT8_FLAG_TYPE_LISTX2MACRO(operType, 1)
            UINT8_ARRAY_LISTX2MACRO(unused1, 2, 3)
            FLOAT32_LISTX2MACRO(compValue, 3)
            UINT32_TYPE_LISTX2MACRO(ifunc, 4)
            UNKNOWN_OR_FORMID_OR_UINT32_LISTX2MACRO(param1, 5)
            UNKNOWN_OR_FORMID_OR_UINT32_LISTX2MACRO(param2, 6)
            UINT8_ARRAY_LISTX2MACRO(unused2, 7, 4)
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

        FORMID_LISTMACRO(targetId, 1)
        UINT8_FLAG_LISTMACRO(flags, 2)
        UINT8_ARRAY_LISTMACRO(unused1, 3, 3)

        LIST_LISTMACRO(conditions, 4, self.ConditionX2)
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
    exportattrs = copyattrs = ObBaseRecord.baseattrs + ['script', 'full', 'iconPath',
                                        'flags', 'priority', 'conditions_list',
                                        'stages_list', 'targets_list']

class ObRACERecord(ObBaseRecord):
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
    UINT32_FLAG_MACRO(flags, 28)
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
            FLOAT32_LISTX2MACRO(posX, 1)
            FLOAT32_LISTX2MACRO(posY, 2)
            exportattrs = copyattrs = ['posX', 'posY']

        UINT32_LISTMACRO(edgeFalloff, 1)

        LIST_LISTMACRO(points, 2, self.Point)
        exportattrs = copyattrs = ['edgeFalloff', 'points_list']

    class Entry(ListComponent):
        class Object(ListX2Component):
            FORMID_LISTX2MACRO(objectId, 1)
            UINT16_LISTX2MACRO(parentIndex, 2)
            UINT8_ARRAY_LISTX2MACRO(unused1, 3, 2)
            FLOAT32_LISTX2MACRO(density, 4)
            UINT8_LISTX2MACRO(clustering, 5)
            UINT8_LISTX2MACRO(minSlope, 6)
            UINT8_LISTX2MACRO(maxSlope, 7)
            UINT8_FLAG_LISTX2MACRO(flags, 8)
            UINT16_LISTX2MACRO(radiusWRTParent, 9)
            UINT16_LISTX2MACRO(radius, 10)
            UINT8_ARRAY_LISTX2MACRO(unk1, 11, 4)
            FLOAT32_LISTX2MACRO(maxHeight, 12)
            FLOAT32_LISTX2MACRO(sink, 13)
            FLOAT32_LISTX2MACRO(sinkVar, 14)
            FLOAT32_LISTX2MACRO(sizeVar, 15)
            UINT16_LISTX2MACRO(angleVarX, 16)
            UINT16_LISTX2MACRO(angleVarY, 17)
            UINT16_LISTX2MACRO(angleVarZ, 18)
            UINT8_ARRAY_LISTX2MACRO(unused2, 19, 1)
            UINT8_ARRAY_LISTX2MACRO(unk2, 20, 4)
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
            FORMID_LISTX2MACRO(grass, 1)
            UINT8_ARRAY_LISTX2MACRO(unk1, 2, 4)
            exportattrs = copyattrs = ['grass', 'unk1']

        class Sound(ListX2Component):
            FORMID_LISTX2MACRO(sound, 1)
            UINT32_FLAG_LISTX2MACRO(flags, 2)
            UINT32_LISTX2MACRO(chance, 3)
            BasicFlagMACRO(IsPleasant, flags, 0x00000001)
            BasicFlagMACRO(IsCloudy, flags, 0x00000002)
            BasicFlagMACRO(IsRainy, flags, 0x00000004)
            BasicFlagMACRO(IsSnowy, flags, 0x00000008)
            exportattrs = copyattrs = ['sound', 'flags', 'chance']

        class Weather(ListX2Component):
            FORMID_LISTX2MACRO(weather, 1)
            UINT32_LISTX2MACRO(chance, 2)
            exportattrs = copyattrs = ['weather', 'chance']

        UINT32_TYPE_LISTMACRO(entryType, 1)
        UINT8_FLAG_LISTMACRO(flags, 2)
        UINT8_LISTMACRO(priority, 3)
        UINT8_ARRAY_LISTMACRO(unused1, 4, 4)

        LIST_LISTMACRO(objects, 5, self.Object)
        STRING_LISTMACRO(mapName, 6)
        ISTRING_LISTMACRO(iconPath, 7)

        LIST_LISTMACRO(grasses, 8, self.Grass)
        UINT32_TYPE_LISTMACRO(musicType, 9)

        LIST_LISTMACRO(sounds, 10, self.Sound)
        LIST_LISTMACRO(weathers, 11, self.Weather)
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
    exportattrs = copyattrs = ObBaseRecord.baseattrs + ['iconPath', 'mapRed', 'mapGreen',
                                        'mapBlue', 'worldspace', 'areas_list',
                                        'entries_list']

class ObSBSPRecord(ObBaseRecord):
    _Type = 'SBSP'
    FLOAT32_MACRO(sizeX, 5)
    FLOAT32_MACRO(sizeY, 6)
    FLOAT32_MACRO(sizeZ, 7)
    exportattrs = copyattrs = ObBaseRecord.baseattrs + ['sizeX', 'sizeY', 'sizeZ']

class ObSCPTRecord(ObBaseRecord):
    _Type = 'SCPT'
    def mergeFilter(self, modSet):
        """Filter references that don't come from the specified modSet.
           Since we can't actually do this for SCPT records, return False if
           any references are to mods not in modSet."""
        for ref in self.references:
            if not isinstance(ref,FormID):
                continue
            if ref[0] not in modSet: return False
        return True

    UINT8_ARRAY_MACRO(unused1, 5, 2)
    UINT32_MACRO(numRefs, 6)
    UINT32_MACRO(compiledSize, 7)
    UINT32_MACRO(lastIndex, 8)
    UINT32_TYPE_MACRO(scriptType, 9)
    UINT8_ARRAY_MACRO(compiled_p, 10)
    ISTRING_MACRO(scriptText, 11)

    LIST_MACRO(vars, 12, Var)
    FORMID_OR_UINT32_ARRAY_MACRO(references, 13)

    BasicTypeMACRO(IsObject, scriptType, 0x00000000, IsQuest)
    BasicTypeMACRO(IsQuest, scriptType, 0x00000001, IsObject)
    BasicTypeMACRO(IsMagicEffect, scriptType, 0x00000100, IsObject)
    copyattrs = ObBaseRecord.baseattrs + ['numRefs', 'compiledSize', 'lastIndex',
                                        'scriptType', 'compiled_p', 'scriptText',
                                        'vars_list', 'references']
    exportattrs = ObBaseRecord.baseattrs + ['numRefs', 'compiledSize', 'lastIndex',
                                        'scriptType', 'scriptText',
                                        'vars_list', 'references'] #'compiled_p',

class ObSGSTRecord(ObBaseRecord):
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
    exportattrs = copyattrs = ObBaseRecord.baseattrs + ['skill', 'description', 'iconPath',
                                        'action', 'attribute', 'specialization',
                                        'use0', 'use1', 'apprentice',
                                        'journeyman', 'expert', 'master']

class ObSLGMRecord(ObBaseRecord):
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
    copyattrs = ObBaseRecord.baseattrs + ['full', 'modPath', 'modb', 'modt_p',
                                        'iconPath', 'script', 'value',
                                        'weight', 'soulType', 'capacityType']
    exportattrs = ObBaseRecord.baseattrs + ['full', 'modPath', 'modb',
                                        'iconPath', 'script', 'value',
                                        'weight', 'soulType', 'capacityType'] # 'modt_p',

class ObSOUNRecord(ObBaseRecord):
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
    exportattrs = copyattrs = ObBaseRecord.baseattrs + ['soundPath', 'minDistance', 'maxDistance',
                                        'freqAdjustment', 'flags', 'staticAtten',
                                        'stopTime', 'startTime']

class ObSPELRecord(ObBaseRecord):
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
    exportattrs = copyattrs = ObBaseRecord.baseattrs + ['full', 'spellType', 'cost',
                                        'levelType', 'flags', 'effects_list']
    copyattrsOBME = copyattrs + ['recordVersion', 'betaVersion',
                                 'minorVersion', 'majorVersion',
                                 'reserved'] #, 'datx_p'

class ObSTATRecord(ObBaseRecord):
    _Type = 'STAT'
    ISTRING_MACRO(modPath, 5)
    FLOAT32_MACRO(modb, 6)
    UINT8_ARRAY_MACRO(modt_p, 7)
    copyattrs = ObBaseRecord.baseattrs + ['modPath', 'modb', 'modt_p']
    exportattrs = ObBaseRecord.baseattrs + ['modPath', 'modb']#, 'modt_p']

class ObTREERecord(ObBaseRecord):
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
    FLOAT32_MACRO(xMinObjBounds, 17)
    FLOAT32_MACRO(yMinObjBounds, 18)
    FLOAT32_MACRO(xMaxObjBounds, 19)
    FLOAT32_MACRO(yMaxObjBounds, 20)
    UINT32_MACRO(musicType, 21)
    UINT8_ARRAY_MACRO(ofst_p, 22)
    SUBRECORD_MACRO(ROAD, "ROAD", 23, ObROADRecord)
    SUBRECORD_MACRO(WorldCELL, "WCEL", 24, ObCELLRecord) ##"WCEL" is an artificial type CBash uses to distinguish World Cells
    SUBRECORD_ARRAY_MACRO(CELLS, "CELL", 25, ObCELLRecord)
    BasicFlagMACRO(IsSmallWorld, flags, 0x00000001)
    BasicFlagMACRO(IsNoFastTravel, flags, 0x00000002)
    BasicInvertedFlagMACRO(IsFastTravel, IsNoFastTravel)
    BasicFlagMACRO(IsOblivionWorldspace, flags, 0x00000004)
    BasicFlagMACRO(IsNoLODWater, flags, 0x00000010)
    BasicInvertedFlagMACRO(IsLODWater, IsNoLODWater)
    BasicTypeMACRO(IsDefault, musicType, 0, IsPublic)
    BasicTypeMACRO(IsPublic, musicType, 1, IsDefault)
    BasicTypeMACRO(IsDungeon, musicType, 2, IsDefault)
    exportattrs = copyattrs = ObBaseRecord.baseattrs + ['full', 'parent', 'climate', 'water', 'mapPath',
                                        'dimX', 'dimY', 'NWCellX', 'NWCellY', 'SECellX',
                                        'SECellY', 'flags', 'xMinObjBounds', 'yMinObjBounds',
                                        'xMaxObjBounds', 'yMaxObjBounds', 'musicType', 'ROAD', 'WorldCELL'] #'ofst_p',

class ObWTHRRecord(ObBaseRecord):
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
        FORMID_LISTMACRO(sound, 1)
        UINT32_TYPE_LISTMACRO(type, 2)
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

fnv_validTypes = set([])

fnv_aggregateTypes = set([])

fnv_pickupables = set([])

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
                        ('CELL',FnvCELLRecord),('ACHR',FnvACHRRecord),('ACRE',FnvACRERecord),
                        ('REFR',FnvREFRRecord),('PGRE',FnvPGRERecord),('PMIS',FnvPMISRecord),
                        ('PBEA',FnvPBEARecord),('NAVM',FnvNAVMRecord),('WRLD',FnvWRLDRecord),
                        ('LAND',FnvLANDRecord),('DIAL',FnvDIALRecord),('INFO',FnvINFORecord),
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
    def __init__(self, ModID):
        self._ModID = ModID

    def __eq__(self, other):
        if type(other) is type(self):
            return self._ModID == other._ModID
        return False

    def __ne__(self, other):
        return not self.__eq__(other)

    @property
    def FileName(self):
        return _CGetFileNameByID(self._ModID) or 'Missing'

    @property
    def ModName(self):
        return _CGetModNameByID(self._ModID) or 'Missing'

    @property
    def GName(self):
        return GPath(self.ModName)

    def GetParentCollection(self):
        return ObCollection(_CGetCollectionIDByModID(self._ModID))

    def HasRecord(self, RecordIdentifier):
        if not RecordIdentifier: return False
        if isinstance(RecordIdentifier, basestring):
            _FormID = 0
            _EditorID = RecordIdentifier
        else:
            _FormID = FormID(RecordIdentifier).GetShortFormID(self)
            _EditorID = 0
        if not (_EditorID or _FormID): return False
        if _CGetRecordID(self._ModID, _FormID, _EditorID):
            return True
        return False

    def LookupRecord(self, RecordIdentifier):
        if not RecordIdentifier: return None
        if isinstance(RecordIdentifier, basestring):
            _FormID = 0
            _EditorID = RecordIdentifier
        else:
            _FormID = FormID(RecordIdentifier).GetShortFormID(self)
            _EditorID = 0
        if not (_EditorID or _FormID): return None
        RecordID = _CGetRecordID(self._ModID, _FormID, _EditorID)
        if RecordID:
            _CGetFieldAttribute.restype = (c_char * 4)
            RecordType = type_record[_CGetFieldAttribute(RecordID, 0, 0, 0, 0, 0, 0, 0, 0).value]
            _CGetFieldAttribute.restype = c_ulong
            if RecordType:
                return RecordType(RecordID)
        return None

    def IsEmpty(self):
        return _CIsModEmpty(self._ModID)

    def GetNewRecordTypes(self):
        numRecords = _CGetModNumTypes(self._ModID)
        if(numRecords > 0):
            cRecords = ((c_char * 4) * numRecords)()
            _CGetModTypes(self._ModID, byref(cRecords))
            return [cRecord.value for cRecord in cRecords if cRecord]
        return []

    def UpdateReferences(self, Old_NewFormIDs):
        Old_NewFormIDs = FormID.FilterValidDict(Old_NewFormIDs, self, True, True)
        length = len(Old_NewFormIDs)
        if length != len(Old_NewFormIDs):
            return []
        OldFormIDs = (c_ulong * length)(*Old_NewFormIDs.keys())
        NewFormIDs = (c_ulong * length)(*Old_NewFormIDs.values())
        Changes = (c_ulong * length)()
        _CUpdateReferences(self._ModID, 0, OldFormIDs, NewFormIDs, byref(Changes), length)
        return [x for x in Changes]

    def CleanMasters(self):
        return _CCleanModMasters(self._ModID)

    def GetRecordsIdenticalToMaster(self):
        numRecords = _CGetNumIdenticalToMasterRecords(self._ModID)
        if(numRecords > 0):
            cRecords = (c_ulong * numRecords)()
            _CGetIdenticalToMasterRecords(self._ModID, byref(cRecords))
            _CGetFieldAttribute.restype = (c_char * 4)
            values = [type_record[_CGetFieldAttribute(x, 0, 0, 0, 0, 0, 0, 0, 0).value](x) for x in cRecords]
            _CGetFieldAttribute.restype = c_ulong
            return values
        return []

    def Load(self):
        _CLoadMod(self._ModID)

    def Unload(self):
        _CUnloadMod(self._ModID)

    def save(self, CloseCollection=True, CleanMasters=True):
        flags = 0
        if(CleanMasters):
            flags |= 0x00000001
        if(CloseCollection):
            flags |= 0x00000002
        return _CSaveMod(self._ModID, c_ulong(flags))

    @property
    def TES4(self):
        RecordID = _CGetRecordID(self._ModID, 0, 0)
        return ObTES4Record(RecordID)

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
    WorldCELLS = CBashRECORDARRAY(ObCELLRecord, 'WCEL') ##"WCEL" is an artificial type CBash uses to distinguish World Cells
    CELLS = CBashRECORDARRAY(ObCELLRecord, 'CLLS') ##"CLLS" is an artificial type CBash uses to distinguish all cells (includes WCEL)
    INFOS = CBashRECORDARRAY(ObINFORecord, 'INFO')
    ACHRS = CBashRECORDARRAY(ObACHRRecord, 'ACHR')
    ACRES = CBashRECORDARRAY(ObACRERecord, 'ACRE')
    REFRS = CBashRECORDARRAY(ObREFRRecord, 'REFR')
    PGRDS = CBashRECORDARRAY(ObPGRDRecord, 'PGRD')
    LANDS = CBashRECORDARRAY(ObLANDRecord, 'LAND')
    ROADS = CBashRECORDARRAY(ObROADRecord, 'ROAD')

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
    def __init__(self, ModID):
        self._ModID = ModID

    def __eq__(self, other):
        if type(other) is type(self):
            return self._ModID == other._ModID
        return False

    def __ne__(self, other):
        return not self.__eq__(other)

    @property
    def FileName(self):
        return _CGetFileNameByID(self._ModID) or 'Missing'

    @property
    def ModName(self):
        return _CGetModNameByID(self._ModID) or 'Missing'

    @property
    def GName(self):
        return GPath(self.ModName)

    def GetParentCollection(self):
        return ObCollection(_CGetCollectionIDByModID(self._ModID))

    def HasRecord(self, RecordIdentifier):
        if not RecordIdentifier: return False
        if isinstance(RecordIdentifier, basestring):
            _FormID = 0
            _EditorID = RecordIdentifier
        else:
            _FormID = FormID(RecordIdentifier).GetShortFormID(self)
            _EditorID = 0
        if not (_EditorID or _FormID): return False
        if _CGetRecordID(self._ModID, _FormID, _EditorID):
            return True
        return False

    def LookupRecord(self, RecordIdentifier):
        if not RecordIdentifier: return None
        if isinstance(RecordIdentifier, basestring):
            _FormID = 0
            _EditorID = RecordIdentifier
        else:
            _FormID = FormID(RecordIdentifier).GetShortFormID(self)
            _EditorID = 0
        if not (_EditorID or _FormID): return None
        RecordID = _CGetRecordID(self._ModID, _FormID, _EditorID)
        if RecordID:
            _CGetFieldAttribute.restype = (c_char * 4)
            RecordType = fnv_type_record[_CGetFieldAttribute(RecordID, 0, 0, 0, 0, 0, 0, 0, 0).value]
            _CGetFieldAttribute.restype = c_ulong
            if RecordType:
                return RecordType(RecordID)
        return None

    def IsEmpty(self):
        return _CIsModEmpty(self._ModID)

    def GetNewRecordTypes(self):
        numRecords = _CGetModNumTypes(self._ModID)
        if(numRecords > 0):
            cRecords = ((c_char * 4) * numRecords)()
            _CGetModTypes(self._ModID, byref(cRecords))
            return [cRecord.value for cRecord in cRecords if cRecord]
        return []

    def UpdateReferences(self, Old_NewFormIDs):
        Old_NewFormIDs = FormID.FilterValidDict(Old_NewFormIDs, self, True, True)
        length = len(Old_NewFormIDs)
        if length != len(Old_NewFormIDs):
            return []
        OldFormIDs = (c_ulong * length)(*Old_NewFormIDs.keys())
        NewFormIDs = (c_ulong * length)(*Old_NewFormIDs.values())
        Changes = (c_ulong * length)()
        _CUpdateReferences(self._ModID, 0, OldFormIDs, NewFormIDs, byref(Changes), length)
        return [x for x in Changes]

    def CleanMasters(self):
        return _CCleanModMasters(self._ModID)

    def GetRecordsIdenticalToMaster(self):
        numRecords = _CGetNumIdenticalToMasterRecords(self._ModID)
        if(numRecords > 0):
            cRecords = (c_ulong * numRecords)()
            _CGetIdenticalToMasterRecords(self._ModID, byref(cRecords))
            _CGetFieldAttribute.restype = (c_char * 4)
            values = [fnv_type_record[_CGetFieldAttribute(x, 0, 0, 0, 0, 0, 0, 0, 0).value](x) for x in cRecords]
            _CGetFieldAttribute.restype = c_ulong
            return values
        return []

    def Load(self):
        _CLoadMod(self._ModID)

    def Unload(self):
        _CUnloadMod(self._ModID)

    def save(self, CloseCollection=True, CleanMasters=True):
        flags = 0
        if(CleanMasters):
            flags |= 0x00000001
        if(CloseCollection):
            flags |= 0x00000002
        return _CSaveMod(self._ModID, c_ulong(flags))

    @property
    def TES4(self):
        RecordID = _CGetRecordID(self._ModID, 0, 0)
        return FnvTES4Record(RecordID)

    FnvModEDIDRecordsMACRO(GMST)
    FnvModRecordsMACRO(TXST)
    FnvModRecordsMACRO(MICN)
    FnvModRecordsMACRO(GLOB)
    FnvModRecordsMACRO(CLAS)
    FnvModRecordsMACRO(FACT)
    FnvModRecordsMACRO(HDPT)
    FnvModRecordsMACRO(HAIR)
    FnvModRecordsMACRO(EYES)
    FnvModRecordsMACRO(RACE)
    FnvModRecordsMACRO(SOUN)
    FnvModRecordsMACRO(ASPC)
    FnvModRecordsMACRO(MGEF)
    FnvModRecordsMACRO(SCPT)
    FnvModRecordsMACRO(LTEX)
    FnvModRecordsMACRO(ENCH)
    FnvModRecordsMACRO(SPEL)
    FnvModRecordsMACRO(ACTI)
    FnvModRecordsMACRO(TACT)
    FnvModRecordsMACRO(TERM)
    FnvModRecordsMACRO(ARMO)
    FnvModRecordsMACRO(BOOK)
    FnvModRecordsMACRO(CONT)
    FnvModRecordsMACRO(DOOR)
    FnvModRecordsMACRO(INGR)
    FnvModRecordsMACRO(LIGH)
    FnvModRecordsMACRO(MISC)
    FnvModRecordsMACRO(STAT)
    FnvModRecordsMACRO(SCOL)
    FnvModRecordsMACRO(MSTT)
    FnvModRecordsMACRO(PWAT)
    FnvModRecordsMACRO(GRAS)
    FnvModRecordsMACRO(TREE)
    FnvModRecordsMACRO(FURN)
    FnvModRecordsMACRO(WEAP)
    FnvModRecordsMACRO(AMMO)
    FnvModRecordsMACRO(NPC_)
    FnvModRecordsMACRO(CREA)
    FnvModRecordsMACRO(LVLC)
    FnvModRecordsMACRO(LVLN)
    FnvModRecordsMACRO(KEYM)
    FnvModRecordsMACRO(ALCH)
    FnvModRecordsMACRO(IDLM)
    FnvModRecordsMACRO(NOTE)
    FnvModRecordsMACRO(COBJ)
    FnvModRecordsMACRO(PROJ)
    FnvModRecordsMACRO(LVLI)
    FnvModRecordsMACRO(WTHR)
    FnvModRecordsMACRO(CLMT)
    FnvModRecordsMACRO(REGN)
    FnvModRecordsMACRO(NAVI)
    FnvModRecordsMACRO(CELL)
    FnvModRecordsMACRO(WRLD)
    FnvModRecordsMACRO(DIAL)
    FnvModRecordsMACRO(QUST)
    FnvModRecordsMACRO(IDLE)
    FnvModRecordsMACRO(PACK)
    FnvModRecordsMACRO(CSTY)
    FnvModRecordsMACRO(LSCR)
    FnvModRecordsMACRO(ANIO)
    FnvModRecordsMACRO(WATR)
    FnvModRecordsMACRO(EFSH)
    FnvModRecordsMACRO(EXPL)
    FnvModRecordsMACRO(DEBR)
    FnvModRecordsMACRO(IMGS)
    FnvModRecordsMACRO(IMAD)
    FnvModRecordsMACRO(FLST)
    FnvModRecordsMACRO(PERK)
    FnvModRecordsMACRO(BPTD)
    FnvModRecordsMACRO(ADDN)
    FnvModRecordsMACRO(AVIF)
    FnvModRecordsMACRO(RADS)
    FnvModRecordsMACRO(CAMS)
    FnvModRecordsMACRO(CPTH)
    FnvModRecordsMACRO(VTYP)
    FnvModRecordsMACRO(IPCT)
    FnvModRecordsMACRO(IPDS)
    FnvModRecordsMACRO(ARMA)
    FnvModRecordsMACRO(ECZN)
    FnvModRecordsMACRO(MESG)
    FnvModRecordsMACRO(RGDL)
    FnvModRecordsMACRO(DOBJ)
    FnvModRecordsMACRO(LGTM)
    FnvModRecordsMACRO(MUSC)
    FnvModRecordsMACRO(IMOD)
    FnvModRecordsMACRO(REPU)
    FnvModRecordsMACRO(RCPE)
    FnvModRecordsMACRO(RCCT)
    FnvModRecordsMACRO(CHIP)
    FnvModRecordsMACRO(CSNO)
    FnvModRecordsMACRO(LSCT)
    FnvModRecordsMACRO(MSET)
    FnvModRecordsMACRO(ALOC)
    FnvModRecordsMACRO(CHAL)
    FnvModRecordsMACRO(AMEF)
    FnvModRecordsMACRO(CCRD)
    FnvModRecordsMACRO(CMNY)
    FnvModRecordsMACRO(CDCK)
    FnvModRecordsMACRO(DEHY)
    FnvModRecordsMACRO(HUNG)
    FnvModRecordsMACRO(SLPD)
    ##Aggregate properties. Useful for iterating through all records without going through the parent records.
    WorldCELLS = CBashRECORDARRAY(FnvCELLRecord, 'WCEL') ##"WCEL" is an artificial type CBash uses to distinguish World Cells
    CELLS = CBashRECORDARRAY(FnvCELLRecord, 'CLLS') ##"CLLS" is an artificial type CBash uses to distinguish all cells (includes WCEL)
    INFOS = CBashRECORDARRAY(FnvINFORecord, 'INFO')
    ACHRS = CBashRECORDARRAY(FnvACHRRecord, 'ACHR')
    ACRES = CBashRECORDARRAY(FnvACRERecord, 'ACRE')
    REFRS = CBashRECORDARRAY(FnvREFRRecord, 'REFR')
    PGRES = CBashRECORDARRAY(FnvPGRERecord, 'PGRE')
    PMISS = CBashRECORDARRAY(FnvPMISRecord, 'PMIS')
    PBEAS = CBashRECORDARRAY(FnvPBEARecord, 'PBEA')
    PFLAS = CBashRECORDARRAY(FnvPFLARecord, 'PFLA')
    PCBES = CBashRECORDARRAY(FnvPCBERecord, 'PCBE')
    NAVMS = CBashRECORDARRAY(FnvNAVMRecord, 'NAVM')
    LANDS = CBashRECORDARRAY(FnvLANDRecord, 'LAND')

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
                     ("CELL", self.CELLS),("ACHR", self.ACHRS),("ACRE", self.ACRES),
                     ("REFR", self.REFRS),("PGRE", self.PGRES),("PMIS", self.PMISS),
                     ("PBEA", self.PBEAS),("PFLA", self.PFLAS),("PCBE", self.PCBES),
                     ("NAVM", self.NAVMS),("WRLD", self.WRLD),("LAND", self.LANDS),
                     ("DIAL", self.DIAL),("INFO", self.INFOS),
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
        if CollectionID:
            self._CollectionID = CollectionID
            self._WhichGame = _CGetCollectionType(CollectionID)
        else:
            self._CollectionID = _CCreateCollection(str(ModsPath), CollectionType)
            self._WhichGame = CollectionType
        self._ModIndex = -1
        self.LoadOrderMods = []
        self.AllMods = []

    def __eq__(self, other):
        if type(other) is type(self):
            return self._CollectionID == other._CollectionID
        return False

    def __ne__(self, other):
        return not self.__eq__(other)

    def GetParentCollection(self):
        return self

    def Unload(self):
        _CUnloadCollection(self._CollectionID)

    def Close(self):
        _CDeleteCollection(self._CollectionID)

    @staticmethod
    def UnloadAllCollections():
        return _CUnloadAllCollections()

    @staticmethod
    def DeleteAllCollections():
        return _CDeleteAllCollections()

    def addMod(self, FileName, MinLoad=True, NoLoad=False, IgnoreExisting=False, Saveable=True, LoadMasters=True, Flags=0x00000079):
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

        if Saveable:
            Flags |= fIsSaveable
        else:
            Flags &= ~fIsSaveable

        if LoadMasters:
            Flags |= fIsLoadMasters
        else:
            Flags &= ~fIsLoadMasters

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
                self.LoadOrderMods = [ObModFile(ModID) for ModID in cModIDs]
            elif self._WhichGame == 2:
                self.LoadOrderMods = [FnvModFile(ModID) for ModID in cModIDs]

        _NumModsIDs = _CGetAllNumMods(self._CollectionID)
        if _NumModsIDs > 0:
            cModIDs = (c_ulong * _NumModsIDs)()
            _CGetAllModIDs(self._CollectionID, byref(cModIDs))
            if self._WhichGame == 0:
                self.AllMods = [ObModFile(ModID) for ModID in cModIDs]
            elif self._WhichGame == 2:
                self.AllMods = [FnvModFile(ModID) for ModID in cModIDs]

    def LookupRecords(self, RecordIdentifier, GetExtendedConflicts=False):
        if not RecordIdentifier: return None
        if GetExtendedConflicts:
            records = [mod.LookupRecord(RecordIdentifier) for mod in reversed(self.AllMods)]
        else:
            records = [mod.LookupRecord(RecordIdentifier) for mod in reversed(self.LoadOrderMods)]
        return [record for record in records if record is not None]

    def LookupModFile(self, ModName):
        ModID = _CGetModIDByName(self._CollectionID, str(ModName))
        if(ModID == -1):
            raise KeyError(_("ModName(%s) not found in collection (%08X)\n") % (ModName, self._CollectionID) + self.Debug_DumpModFiles())
        if self._WhichGame == 0:
            return ObModFile(ModID)
        elif self._WhichGame == 2:
            return FnvModFile(ModID)

    def LookupModFileLoadOrder(self, ModName):
        return _CGetModLoadOrderByName(self._CollectionID, str(ModName))

    def UpdateReferences(self, OldFormIDs, NewFormIDs):
        return sum([mod.UpdateReferences(OldFormIDs, NewFormIDs) for mod in self.LoadOrderMods])

    def ClearReferenceLog(self):
        return _CGetRecordUpdatedReferences(0, self._CollectionID)

    def Debug_DumpModFiles(self):
        value = _("Collection (%08X) contains the following modfiles:\n") % (self._CollectionID,)
        for mod in self.AllMods:
            LoadOrder = _CGetModLoadOrderByID(mod._ModID)
            if LoadOrder == -1: LoadOrder = '--'
            else: LoadOrder = '%02X' % (LoadOrder,)
            ModName, FileName = mod.ModName, mod.FileName
            if ModName == FileName:
                value += _("Load Order (%s), Name(%s)\n") % (LoadOrder, ModName)
            else:
                value += _("Load Order (%s), ModName(%s) FileName(%s)\n") % (LoadOrder, ModName, FileName)
        return value