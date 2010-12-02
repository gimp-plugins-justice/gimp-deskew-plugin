#ifndef __CF_CNTPTR_H__
#define __CF_CNTPTR_H__

/*
    This file is part of Page Layout Detection Tools.

    This code is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This code is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this code; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/* Reference counted pointer. Scalar delete is called when the last reference is
unlinked. The stored pointer may be zero.
*/
namespace pagetools{

template <class T>
class CntPtr{
public:
    // Ctors
    CntPtr();
    CntPtr(T *obj); // obj must be created by scalar new or be zero
    CntPtr(const CntPtr<T>& rhs);

    // Dtor - made non-virtual on purpose
    ~CntPtr(){unlink();}

    // Assignment
    CntPtr<T>& operator =(const CntPtr<T>& rhs);
    CntPtr<T>& operator =(T *obj); // obj must be created by scalar new or be zero

    // Accessors
    T* get()const{return obj_;} // Returns raw pointer - don't delete it

    operator bool()const{return obj_!=0;}

    // Operators
    T& operator*()const{return *obj_;}

    T* operator->()const{return obj_;}

    bool operator ==(const CntPtr<T>& rhs){// Equality of pointees
        return obj_==rhs.obj_;
    }

private:
    void unlink();
    T *obj_;
    int *cnt_;
};

template <class T>
inline
CntPtr<T>::
CntPtr()
:obj_(0)
,cnt_(new int(1))
{}

template <class T>
inline
CntPtr<T>::
CntPtr(T *obj)
:obj_(obj)
,cnt_(new int(1))
{}

template <class T>
inline
CntPtr<T>::
CntPtr(const CntPtr<T>& rhs)
:obj_(rhs.obj_)
,cnt_(rhs.cnt_)
{
    ++*cnt_;
}

template <class T>
inline void
CntPtr<T>::
unlink()

{
    if(!(--*cnt_)){
        delete obj_;
        delete cnt_;
    }
}

template <class T>
inline CntPtr<T>&
CntPtr<T>::
operator =(const CntPtr<T>& rhs){
    if(obj_==rhs.obj_) {
        return *this; // Do nothing if a=a
    }
    unlink();
    obj_=rhs.obj_;
    cnt_=rhs.cnt_;
    ++*cnt_;
    return *this;
}

template <class T>
inline CntPtr<T>&
CntPtr<T>::
operator =(T *obj){
    if(obj_==obj) {
        return *this; // Do nothing if assigning the pointer to the same object
    }
    unlink(); 
    obj_=obj;
    cnt_=new int(1);
    return *this;
}

}// namespace pagetools

#endif//__CF_CNTPTR_H__
