/*
GPL License and Copyright Notice ============================================
 This file is part of CBash.

 CBash is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 CBash is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with CBash; if not, write to the Free Software Foundation,
 Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

 CBash copyright (C) 2010 Waruddar
=============================================================================
*/

#include "GRUPRecord.h"

bool ProcessRecord(_FileHandler &ReadHandler, FormIDHandlerClass &FormIDHandler, RecordReader &reader, FormIDResolver &expander, Record *&curRecord, const ModFlags &Flags, boost::unordered_set<UINT32> &UsedFormIDs)
    {
    ReadHandler.read(&curRecord->flags, 4);
    ReadHandler.read(&curRecord->formID, 4);
    ReadHandler.read(&curRecord->flagsUnk, 4);
    expander.Accept(curRecord->formID);

    //Testing Messages
    if(curRecord->IsLoaded())
        printf("_fIsLoaded Flag used!!!! %s - %08X\n", curRecord->GetStrType(), curRecord->formID);
    if((curRecord->flags & 0x4000) != 0)
        printf("0x4000 used: %08X!!!!\n", curRecord->formID);

    if(Flags.IsSkipNewRecords && FormIDHandler.IsNewRecord(curRecord->formID))
        {
        delete curRecord;
        return false;
        }

    //Make sure the formID is unique within the mod
    if(UsedFormIDs.insert(curRecord->formID).second == true)
        {
        if(Flags.IsFullLoad)
            reader.Accept(&curRecord);
            //Threads.schedule(boost::bind(&RecordReader::Accept, reader, (Record **)&curRecord));
        if(Flags.IsTrackNewTypes)
            {
            if(curRecord->GetType() != 'TSMG' && curRecord->GetType() != 'FEGM' && FormIDHandler.IsNewRecord(curRecord->formID))
                FormIDHandler.NewTypes.insert(curRecord->GetType());
            }
        return true;
        }
    else
        {
        printf("Record skipped with duplicate formID: %08X\n", curRecord->formID);
        delete curRecord;
        return false;
        }
    return true;
    }