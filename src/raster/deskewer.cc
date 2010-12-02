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

#include <raster/deskewer.h>
#include <util/bitutil.h>
#include <math.h>
#include <memory.h>

namespace pagetools{

unsigned int 
Deskewer::next_pow2(unsigned int n){
    unsigned int retval=1;
    while(retval<n){
        retval<<=1;
    }
    return retval;
}

double 
Deskewer::findSkew(const BWImage& img){
    unsigned int w2=next_pow2(img.bytewidth());
    unsigned int ssize=2*w2-1; // Size of sharpness table
    unsigned int *sharpness=new unsigned int[ssize];
    radon(img, 1, sharpness);
    radon(img, -1, sharpness);
    unsigned int i, imax=0;
    unsigned int vmax=0;
    double sum=0.;
    for(i=0; i<ssize; i++){
        unsigned int s=sharpness[i];
        if(s>vmax){
            imax=i;
            vmax=s;
        }
        sum+=s;
    }
    unsigned int h=img.height();
    if(vmax<=3*sum/h){  // Heuristics !!!
        return 0;
    }
    int iskew= (int)imax-int(w2)+1;
    delete[] sharpness;
    return atan((double)iskew/(8*w2));

}

void 
Deskewer::radon(const BWImage& img, int sign, unsigned int sharpness[]){
    unsigned short int *p1_, *p2_; // Stored columnwise
    
    unsigned int w2=next_pow2(img.bytewidth());
    unsigned int w=img.bytewidth();
    unsigned int h=img.height();

    unsigned int s=h*w2;
    p1_=new unsigned short int[s];
    p2_=new unsigned short int[s];
    // Fill in the first table
    memset(p1_, 0, sizeof(unsigned short int)*s);
    unsigned int ir, ic;
    unsigned char const *bitcount=BitUtil::bitcount();
    for(ir=0; ir<h; ir++){
        unsigned char const *scl=img.scanline(ir);
        for(ic=0; ic<w; ic++){
            if(sign>0){
                p1_[h*ic+ir]=bitcount[scl[w-1-ic]];
                    
            }else{
                p1_[h*ic+ir]=bitcount[scl[ic]];
            }
        }
    }
    

    // Iterate
    unsigned short int *x1=p1_;
    unsigned short int *x2=p2_;
    unsigned int step=1;
    for(;;){
        unsigned int i;
        for(i=0; i<w2; i+=2*step){
            unsigned int j;
            for(j=0; j<step; j++){
                // Columns-sources:
                unsigned short int *s1=x1+h*(i+j);
                unsigned short int *s2=x1+h*(i+j+step);
                
                // Columns-targets:
                unsigned short int *t1=x2+h*(i+2*j);
                unsigned short int *t2=x2+h*(i+2*j+1);
                unsigned int m;
                for(m=0; m<h; m++){
                    t1[m]=s1[m];
                    t2[m]=s1[m];
                    if(m+j<h){
                        t1[m]+=s2[m+j];
                    }
                    if(m+j+1<h){
                        t2[m]+=s2[m+j+1];
                    }
                }
            }
        }
        // Swap the tables:
        unsigned short int *aux=x1;
        x1=x2;
        x2=aux;
        // Increase the step:
        step*=2;
        if(step>=w2) break;
    }
    // Now, compute the sum of squared finite differences:
    for(ic=0; ic<w2; ic++){
        unsigned int acc=0;
        unsigned short int *col=x1+h*ic;
        for(ir=0; ir+1<h; ir++){
            int diff=(int)(col[ir])-(int)(col[ir+1]);
            acc+=diff*diff;
        }
        sharpness[w2-1+sign*ic]=acc;
        
    }
    delete[] p1_;
    delete[] p2_;
}



}//namespace pagetools
