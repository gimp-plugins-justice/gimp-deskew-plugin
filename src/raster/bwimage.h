#ifndef __CF_BWIMAGE_H__
#define __CF_BWIMAGE_H__

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

namespace pagetools{

class BWImage{
public:
    typedef enum {MSB2LSB, LSB2MSB } bitorder_t;

    BWImage();
    BWImage(unsigned int w, unsigned int h);
    BWImage(unsigned int w, unsigned int h, unsigned int bw);
    virtual ~BWImage();

    // Accessor(s)

    unsigned int bytewidth()const{return bw_;}
    unsigned int width()const{return w_;}
    unsigned int height()const{return h_;}

    unsigned char const *scanline(unsigned int ir)const{
        return data_+ir*bw_;
    }

    // Modifiers
    unsigned char *scanline(unsigned int ir){
        return data_+ir*bw_;
    }

    void setSize(unsigned int w, unsigned int h); // Discards old data

    void setBitorder(bitorder_t bitorder);

    void zeroAll();

    inline void setPixelOn(unsigned int y, unsigned int x) {
        scanline(y)[x / 8] |= (1 << (x%8));
    }

private:
    unsigned char *data_;
    unsigned int w_; // Width
    unsigned int h_; // Height
    unsigned int bw_; // Byte width
    bitorder_t bitorder_;

    // Assignment and copy ctor prohibited:
    BWImage(const BWImage&);
    const BWImage& operator=(const BWImage&);
};
}// namespace pagetools
#endif//__CF_BWIMAGE_H__
