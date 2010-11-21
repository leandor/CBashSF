#include "..\Common.h"
#include "CSTYRecord.h"

signed long CSTYRecord::ParseRecord(unsigned char *buffer, const unsigned long &recSize)
    {
    if(IsLoaded())
        return -1;
    IsLoaded(true);
    unsigned long subType = 0;
    unsigned long subSize = 0;
    unsigned long curPos = 0;
    while(curPos < recSize){
        _readBuffer(&subType,buffer,4,curPos);
        switch(subType)
            {
            case eXXXX:
                curPos += 2;
                _readBuffer(&subSize,buffer,4,curPos);
                _readBuffer(&subType,buffer,4,curPos);
                curPos += 2;
                break;
            default:
                subSize = 0;
                _readBuffer(&subSize,buffer,2,curPos);
                break;
            }
        switch(subType)
            {
            case eEDID:
                EDID.Read(buffer, subSize, curPos);
                break;
            case eCSTD:
                CSTD.Read(buffer, subSize, curPos);
                break;
            case eCSAD:
                CSAD.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  CSTY: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

unsigned long CSTYRecord::GetSize(bool forceCalc)
    {
    if(!forceCalc && recData != NULL)
        return *(unsigned long*)&recData[-16];
    unsigned long cSize = 0;
    unsigned long TotSize = 0;
    if(EDID.IsLoaded())
        {
        cSize = EDID.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(CSTD.IsLoaded())
        TotSize += CSTD.GetSize() + 6;
    if(CSAD.IsLoaded())
        TotSize += CSAD.GetSize() + 6;
    return TotSize;
    }

signed long CSTYRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord(eEDID, EDID.value, EDID.GetSize());
    if(CSTD.IsLoaded())
        SaveHandler.writeSubRecord(eCSTD, &CSTD.value, CSTD.GetSize());
    if(CSAD.IsLoaded())
        SaveHandler.writeSubRecord(eCSAD, CSAD.value, CSAD.GetSize());
    return -1;
    }

#ifdef _DEBUG
void CSTYRecord::Debug(int debugLevel)
    {
    if(!IsLoaded())
        return;
    unsigned long indentation = 4;
    printf("  CSTY\n");
    if(Header.IsLoaded())
        Header.Debug(debugLevel, indentation);

    EDID.Debug("EDID", debugLevel, indentation);

    CSTD.Debug("CSTD", debugLevel, indentation);

    CSAD.Debug("CSAD", debugLevel, indentation);
    }
#endif
