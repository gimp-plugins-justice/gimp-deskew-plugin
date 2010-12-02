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

#include <util/bitutil.h>

namespace pagetools{

BitUtil *BitUtil::instance_=0;

const unsigned char* 
BitUtil::bitcount(){
    if(!instance_){
        instance_=new BitUtil;
    }
    return instance_->bitcount_;
}

const unsigned char* 
BitUtil::invbits(){
    if(!instance_){
        instance_=new BitUtil;
    }
    return instance_->invbits_;
}

BitUtil::BitUtil(){
    bitcount_=new unsigned char[256];
    invbits_=new unsigned char[256];
    unsigned int i;
    for(i=0; i<256; i++){
        unsigned int j=i, cnt=0;
        do{
            cnt+=j&1;
        }while(j>>=1);
        char x=(i<<4)|(i>>4);
        x=((x&0xCC)>>2)|((x&0x33)<<2);
        x=((x&0xAA)>>1)|((x&0x55)<<1);
        bitcount_[i]=cnt;
        invbits_[i]=x;
    }
}

}
