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

#include <raster/bwimage.h>
#include <cstring>

namespace pagetools{

BWImage::BWImage()
:w_(0), h_(0), bw_(0), data_(0)
{
}


BWImage::BWImage(unsigned int w, unsigned int h)
:w_(w), h_(h)
{
    bw_=(w+7)/8;
    data_=new unsigned char[bw_*h_];
}

BWImage::BWImage(unsigned int w, unsigned int h, unsigned int bw)
:w_(w), h_(h), bw_(bw){
    data_=new unsigned char[bw_*h_];
}

BWImage::~BWImage(){
    delete [] data_;
}


void
BWImage::setSize(unsigned int w, unsigned int h){
    delete [] data_;
    w_=w;
    h_=h;
    bw_=(w+7)/8;
    data_=new unsigned char[bw_*h_];
}

void
BWImage::setBitorder(bitorder_t bitorder){
    bitorder_=bitorder;
}


void BWImage::zeroAll() {
    memset(data_, 0, bw_*h_);
}

}// namespace pagetools
