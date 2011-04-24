#include "Common.h"


    
template<class T> SimpleSubRecord<T>::SimpleSubRecord():
    isLoaded(false),
    value(0)
    {
    //
    }

template<class T> SimpleSubRecord<T>::~SimpleSubRecord()
    {
    //
    }

template<class T> UINT32 SimpleSubRecord<T>::GetSize() const
    {
    return sizeof(T);
    }

template<class T> bool SimpleSubRecord<T>::IsLoaded() const
    {
    return (isLoaded && value != 0);
    }

template<class T> void SimpleSubRecord<T>::Load()
    {
    isLoaded = true;
    }

template<class T> void SimpleSubRecord<T>::Unload()
    {
    value = 0;
    isLoaded = false;
    }

template<class T> bool SimpleSubRecord<T>::Read(unsigned char *buffer, UINT32 subSize, UINT32 &curPos)
    {
    if(isLoaded)
        {
        curPos += subSize;
        return false;
        }
    if(subSize > sizeof(T))
        {
        printf("Rec? subSize:%u, sizeof:%u\n", subSize, sizeof(T));
        memcpy(&value, buffer + curPos, sizeof(T));
        }
    else
        memcpy(&value, buffer + curPos, subSize);
    isLoaded = true;
    //size = subSize;
    curPos += subSize;
    return true;
    }

template<class T> bool SimpleSubRecord<T>::operator ==(const SimpleSubRecord<T> &other) const
    {
    return (isLoaded == other.isLoaded &&
            value == other.value);
    }

template<class T> bool SimpleSubRecord<T>::operator !=(const SimpleSubRecord<T> &other) const
    {
    return !(*this == other);
    }
    
template<class T> ReqSimpleSubRecord<T>::ReqSimpleSubRecord():
    value(0)
    {
    //
    }

template<class T> ReqSimpleSubRecord<T>::~ReqSimpleSubRecord()
    {
    //
    }

template<class T> UINT32 ReqSimpleSubRecord<T>::GetSize() const
    {
    return sizeof(T);
    }

template<class T> bool ReqSimpleSubRecord<T>::IsLoaded() const
    {
    return true;
    }

template<class T> void ReqSimpleSubRecord<T>::Load()
    {
    //
    }

template<class T> void ReqSimpleSubRecord<T>::Unload()
    {
    value = 0;
    }

template<class T> bool ReqSimpleSubRecord<T>::Read(unsigned char *buffer, UINT32 subSize, UINT32 &curPos)
    {
    if(subSize > sizeof(T))
        {
        printf("Req? subSize:%u, sizeof:%u\n", subSize, sizeof(T));
        memcpy(&value, buffer + curPos, sizeof(T));
        }
    else
        memcpy(&value, buffer + curPos, subSize);
    //size = subSize;
    curPos += subSize;
    return true;
    }

template<class T> bool ReqSimpleSubRecord<T>::operator ==(const ReqSimpleSubRecord<T> &other) const
    {
    return (value == other.value);
    }

template<class T> bool ReqSimpleSubRecord<T>::operator !=(const ReqSimpleSubRecord<T> &other) const
    {
    return !(*this == other);
    }

template<class T> OptSimpleSubRecord<T>::OptSimpleSubRecord():
    value(0)
    {
    //
    }

template<class T> OptSimpleSubRecord<T>::~OptSimpleSubRecord()
    {
    Unload();
    }

template<class T> UINT32 OptSimpleSubRecord<T>::GetSize() const
    {
    return sizeof(T);
    }

template<class T> bool OptSimpleSubRecord<T>::IsLoaded() const
    {
    return (value != 0);
    }

template<class T> void OptSimpleSubRecord<T>::Load()
    {
    //
    }

template<class T> void OptSimpleSubRecord<T>::Unload()
    {
    value = 0;
    }

template<class T> bool OptSimpleSubRecord<T>::Read(unsigned char *buffer, UINT32 subSize, UINT32 &curPos)
    {
    if(value != 0)
        {
        curPos += subSize;
        return false;
        }
    if(subSize > sizeof(T))
        {
        printf("Opt? subSize:%u, sizeof:%u\n", subSize, sizeof(T));
        memcpy(&value, buffer + curPos, sizeof(T));
        }
    else
        memcpy(&value, buffer + curPos, subSize);
    curPos += subSize;
    return true;
    }

template<class T> OptSimpleSubRecord<T>& OptSimpleSubRecord<T>::operator = (const OptSimpleSubRecord<T> &rhs)
    {
    if(this != &rhs)
        value = rhs.value;
    return *this;
    }

template<class T> bool OptSimpleSubRecord<T>::operator ==(const OptSimpleSubRecord<T> &other) const
    {
    return value == other.value;
    }

template<class T> bool OptSimpleSubRecord<T>::operator !=(const OptSimpleSubRecord<T> &other) const
    {
    return value != other.value;
    }
    
template<class T> SemiOptSimpleSubRecord<T>::SemiOptSimpleSubRecord():
    value(NULL)
    {
    //
    }

template<class T> SemiOptSimpleSubRecord<T>::~SemiOptSimpleSubRecord()
    {
    Unload();
    }

template<class T> UINT32 SemiOptSimpleSubRecord<T>::GetSize() const
    {
    return sizeof(T);
    }

template<class T> bool SemiOptSimpleSubRecord<T>::IsLoaded() const
    {
    return (value != NULL);
    }

template<class T> void SemiOptSimpleSubRecord<T>::Load()
    {
    if(value == NULL)
        value = new T(0);
    }

template<class T> void SemiOptSimpleSubRecord<T>::Unload()
    {
    delete value;
    value = NULL;
    }

template<class T> bool SemiOptSimpleSubRecord<T>::Read(unsigned char *buffer, UINT32 subSize, UINT32 &curPos)
    {
    if(value != NULL)
        {
        curPos += subSize;
        return false;
        }
    value = new T(0);
    if(subSize > sizeof(T))
        {
        printf("Opt? subSize:%u, sizeof:%u\n", subSize, sizeof(T));
        memcpy(value, buffer + curPos, sizeof(T));
        }
    else
        memcpy(value, buffer + curPos, subSize);
    curPos += subSize;
    return true;
    }

template<class T> T * SemiOptSimpleSubRecord<T>::operator->() const
    {
    return value;
    }

template<class T> SemiOptSimpleSubRecord<T>& SemiOptSimpleSubRecord<T>::operator = (const SemiOptSimpleSubRecord<T> &rhs)
    {
    if(this != &rhs)
        if(rhs.value != NULL)
            {
            if(value == NULL)
                {
                value = new T(0);
                }
            else
                value->~T();
            *value = *rhs.value;
            }
        else
            {
            delete value;
            value = NULL;
            }
    return *this;
    }

template<class T> bool SemiOptSimpleSubRecord<T>::operator ==(const SemiOptSimpleSubRecord<T> &other) const
    {
    if(!IsLoaded())
        {
        if(!other.IsLoaded())
            return true;
        }
    else if(other.IsLoaded() && *value == *other.value)
        return true;
    return false;
    }

template<class T> bool SemiOptSimpleSubRecord<T>::operator !=(const SemiOptSimpleSubRecord<T> &other) const
    {
    return !(*this == other);
    }

template<class T> SubRecord<T>::SubRecord():
    isLoaded(false),
    value()
    {
    //
    }

template<class T> SubRecord<T>::~SubRecord()
    {
    //
    }

template<class T> UINT32 SubRecord<T>::GetSize() const
    {
    return sizeof(T);
    }

template<class T> bool SubRecord<T>::IsLoaded() const
    {
    T defaultValue;
    return (isLoaded && value != defaultValue);
    }

template<class T> void SubRecord<T>::Load()
    {
    isLoaded = true;
    }

template<class T> void SubRecord<T>::Unload()
    {
    T newValue;
    value.~T();
    value = newValue;
    isLoaded = false;
    }

template<class T> bool SubRecord<T>::Read(unsigned char *buffer, UINT32 subSize, UINT32 &curPos)
    {
    if(isLoaded)
        {
        curPos += subSize;
        return false;
        }
    if(subSize > sizeof(T))
        {
        printf("Rec? subSize:%u, sizeof:%u\n", subSize, sizeof(T));
        memcpy(&value, buffer + curPos, sizeof(T));
        }
    else
        memcpy(&value, buffer + curPos, subSize);
    isLoaded = true;
    //size = subSize;
    curPos += subSize;
    return true;
    }

template<class T> T * SubRecord<T>::operator->() const
    {
    return &value;
    }

template<class T> bool SubRecord<T>::operator ==(const SubRecord<T> &other) const
    {
    return (value == other.value &&
            isLoaded == other.isLoaded);
    }

template<class T> bool SubRecord<T>::operator !=(const SubRecord<T> &other) const
    {
    return !(*this == other);
    }

template<class T> ReqSubRecord<T>::ReqSubRecord():
    value()
    {
    //
    }

template<class T> ReqSubRecord<T>::~ReqSubRecord()
    {
    //
    }

template<class T> UINT32 ReqSubRecord<T>::GetSize() const
    {
    return sizeof(T);
    }

template<class T> bool ReqSubRecord<T>::IsLoaded() const
    {
    return true;
    }

template<class T> void ReqSubRecord<T>::Load()
    {
    //
    }

template<class T> void ReqSubRecord<T>::Unload()
    {
    T newValue;
    value.~T();
    value = newValue;
    }

template<class T> bool ReqSubRecord<T>::Read(unsigned char *buffer, UINT32 subSize, UINT32 &curPos)
    {
    if(subSize > sizeof(T))
        {
        printf("Req? subSize:%u, sizeof:%u\n", subSize, sizeof(T));
        memcpy(&value, buffer + curPos, sizeof(T));
        }
    else
        memcpy(&value, buffer + curPos, subSize);
    //size = subSize;
    curPos += subSize;
    return true;
    }

template<class T> T * ReqSubRecord<T>::operator->() const
    {
    return &value;
    }

template<class T> bool ReqSubRecord<T>::operator ==(const ReqSubRecord<T> &other) const
    {
    return (value == other.value);
    }

template<class T> bool ReqSubRecord<T>::operator !=(const ReqSubRecord<T> &other) const
    {
    return !(*this == other);
    }

template<class T> OptSubRecord<T>::OptSubRecord():
    value(NULL)
    {
    //
    }

template<class T> OptSubRecord<T>::~OptSubRecord()
    {
    Unload();
    }

template<class T> UINT32 OptSubRecord<T>::GetSize() const
    {
    return sizeof(T);
    }

template<class T> bool OptSubRecord<T>::IsLoaded() const
    {
    T defaultValue;
    return (value != NULL && *value != defaultValue);
    }

template<class T> void OptSubRecord<T>::Load()
    {
    if(value == NULL)
        value = new T();
    }

template<class T> void OptSubRecord<T>::Unload()
    {
    delete value;
    value = NULL;
    }

template<class T> bool OptSubRecord<T>::Read(unsigned char *buffer, UINT32 subSize, UINT32 &curPos)
    {
    if(value != NULL)
        {
        curPos += subSize;
        return false;
        }
    value = new T();
    if(subSize > sizeof(T))
        {
        printf("Opt? subSize:%u, sizeof:%u\n", subSize, sizeof(T));
        memcpy(value, buffer + curPos, sizeof(T));
        }
    else
        memcpy(value, buffer + curPos, subSize);
    curPos += subSize;
    return true;
    }

template<class T> T * OptSubRecord<T>::operator->() const
    {
    return value;
    }

template<class T> OptSubRecord<T>& OptSubRecord<T>::operator = (const OptSubRecord<T> &rhs)
    {
    if(this != &rhs)
        if(rhs.value != NULL)
            {
            if(value == NULL)
                {
                value = new T();
                }
            else
                value->~T();
            *value = *rhs.value;
            }
        else
            {
            delete value;
            value = NULL;
            }
    return *this;
    }

template<class T> bool OptSubRecord<T>::operator ==(const OptSubRecord<T> &other) const
    {
    if(!IsLoaded())
        {
        if(!other.IsLoaded())
            return true;
        }
    else if(other.IsLoaded() && *value == *other.value)
        return true;
    return false;
    }

template<class T> bool OptSubRecord<T>::operator !=(const OptSubRecord<T> &other) const
    {
    return !(*this == other);
    }

template<class T> SemiOptSubRecord<T>::SemiOptSubRecord():
    value(NULL)
    {
    //
    }

template<class T> SemiOptSubRecord<T>::~SemiOptSubRecord()
    {
    Unload();
    }

template<class T> UINT32 SemiOptSubRecord<T>::GetSize() const
    {
    return sizeof(T);
    }

template<class T> bool SemiOptSubRecord<T>::IsLoaded() const
    {
    return (value != NULL);
    }

template<class T> void SemiOptSubRecord<T>::Load()
    {
    if(value == NULL)
        value = new T();
    }

template<class T> void SemiOptSubRecord<T>::Unload()
    {
    delete value;
    value = NULL;
    }

template<class T> bool SemiOptSubRecord<T>::Read(unsigned char *buffer, UINT32 subSize, UINT32 &curPos)
    {
    if(value != NULL)
        {
        curPos += subSize;
        return false;
        }
    value = new T();
    if(subSize > sizeof(T))
        {
        printf("Opt? subSize:%u, sizeof:%u\n", subSize, sizeof(T));
        memcpy(value, buffer + curPos, sizeof(T));
        }
    else
        memcpy(value, buffer + curPos, subSize);
    curPos += subSize;
    return true;
    }

template<class T> T * SemiOptSubRecord<T>::operator->() const
    {
    return value;
    }

template<class T> SemiOptSubRecord<T>& SemiOptSubRecord<T>::operator = (const SemiOptSubRecord<T> &rhs)
    {
    if(this != &rhs)
        if(rhs.value != NULL)
            {
            if(value == NULL)
                {
                value = new T();
                }
            else
                value->~T();
            *value = *rhs.value;
            }
        else
            {
            delete value;
            value = NULL;
            }
    return *this;
    }

template<class T> bool SemiOptSubRecord<T>::operator ==(const SemiOptSubRecord<T> &other) const
    {
    if(!IsLoaded())
        {
        if(!other.IsLoaded())
            return true;
        }
    else if(other.IsLoaded() && *value == *other.value)
        return true;
    return false;
    }

template<class T> bool SemiOptSubRecord<T>::operator !=(const SemiOptSubRecord<T> &other) const
    {
    return !(*this == other);
    }

template<class T> OBMEEFIXSubRecord<T>::OBMEEFIXSubRecord():
    value(NULL)
    {
    //
    }

template<class T> OBMEEFIXSubRecord<T>::~OBMEEFIXSubRecord()
    {
    Unload();
    }

template<class T> UINT32 OBMEEFIXSubRecord<T>::GetSize() const
    {
    return sizeof(T);
    }

template<class T> bool OBMEEFIXSubRecord<T>::IsLoaded()
    {
    if(value == NULL)
        return false;
    if(value->efixOverrides == 0)
        {
        Unload();
        return false;
        }
    T defaultValue;
    return (*value != defaultValue);
    }

template<class T> bool OBMEEFIXSubRecord<T>::Internal_IsLoaded() const
    {
    T defaultValue;
    return (value != NULL && *value != defaultValue);
    }

template<class T> void OBMEEFIXSubRecord<T>::Load()
    {
    if(value == NULL)
        value = new T();
    }

template<class T> void OBMEEFIXSubRecord<T>::Unload()
    {
    delete value;
    value = NULL;
    }

template<class T> bool OBMEEFIXSubRecord<T>::Read(unsigned char *buffer, UINT32 subSize, UINT32 &curPos)
    {
    if(value != NULL)
        {
        curPos += subSize;
        return false;
        }
    value = new T();
    if(subSize > sizeof(T))
        {
        printf("Opt? subSize:%u, sizeof:%u\n", subSize, sizeof(T));
        memcpy(value, buffer + curPos, sizeof(T));
        }
    else
        memcpy(value, buffer + curPos, subSize);
    curPos += subSize;
    return true;
    }

template<class T> T * OBMEEFIXSubRecord<T>::operator->() const
    {
    return value;
    }

template<class T> OBMEEFIXSubRecord<T>& OBMEEFIXSubRecord<T>::operator = (const OBMEEFIXSubRecord<T> &rhs)
    {
    if(this != &rhs)
        if(rhs.value != NULL)
            {
            if(value == NULL)
                {
                value = new T();
                }
            else
                value->~T();
            *value = *rhs.value;
            }
        else
            {
            delete value;
            value = NULL;
            }
    return *this;
    }

template<class T> bool OBMEEFIXSubRecord<T>::operator ==(const OBMEEFIXSubRecord<T> &other) const
    {
    if(!Internal_IsLoaded())
        {
        if(!other.Internal_IsLoaded())
            return true;
        }
    else if(other.Internal_IsLoaded() && *value == *other.value)
        return true;
    return false;
    }

template<class T> bool OBMEEFIXSubRecord<T>::operator !=(const OBMEEFIXSubRecord<T> &other) const
    {
    return !(*this == other);
    }