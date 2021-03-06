/*

The MIT License (MIT)

Copyright (c) 2017 Tim Warburton, Noel Chalmers, Jesse Chan, Ali Karakus

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/


#ifndef OGS_GATHERMANY_TPP
#define OGS_GATHERMANY_TPP 1

#include "ogs.hpp"

template <class T> 
void gatherMany_add(const  dlong Ngather,
                   const int Nentries,
                   const dlong stride,
                   const dlong gstride,
                   const  dlong *  gatherStarts,
                   const  dlong *  gatherIds,
                   const  T     *  q,
                          T     *  gatherq) {
  for (int k=0;k<Nentries;k++) {
    for(dlong g=0;g<Ngather;++g){

      const dlong start = gatherStarts[g];
      const dlong end = gatherStarts[g+1];
   
      T gq = 0;
      for(dlong n=start;n<end;++n){
        const dlong id = gatherIds[n];
        gq += q[id+k*stride];
      }

      //contiguously packed
      gatherq[g+k*gstride] = gq;
    }
  }
}

template <class T> 
void gatherMany_mul(const  dlong Ngather,
                   const int Nentries,
                   const dlong stride,
                   const dlong gstride,
                   const  dlong *  gatherStarts,
                   const  dlong *  gatherIds,
                   const  T     *  q,
                          T     *  gatherq) {
  for (int k=0;k<Nentries;k++) {
    for(dlong g=0;g<Ngather;++g){

      const dlong start = gatherStarts[g];
      const dlong end = gatherStarts[g+1];
   
      T gq = 1;
      for(dlong n=start;n<end;++n){
        const dlong id = gatherIds[n];
        gq *= q[id+k*stride];
      }

      //contiguously packed
      gatherq[g+k*gstride] = gq;
    }
  }
}

template <class T> 
void gatherMany_min(const  dlong Ngather,
                   const int Nentries,
                   const dlong stride,
                   const dlong gstride,
                   const  dlong *  gatherStarts,
                   const  dlong *  gatherIds,
                   const  T     *  q,
                          T     *  gatherq) {
  for (int k=0;k<Nentries;k++) {
    for(dlong g=0;g<Ngather;++g){

      const dlong start = gatherStarts[g];
      const dlong end = gatherStarts[g+1];
   
      const dlong startId = gatherIds[start];
      T gq = q[startId+k*stride];
      for(dlong n=start+1;n<end;++n){
        const dlong id = gatherIds[n];
        gq = (q[id+k*stride] < gq) ? q[id+k*stride] : gq;
      }

      //contiguously packed
      gatherq[g+k*gstride] = gq;
    }
  }
}

template <class T> 
void gatherMany_max(const  dlong Ngather,
                   const int Nentries,
                   const dlong stride,
                   const dlong gstride,
                   const  dlong *  gatherStarts,
                   const  dlong *  gatherIds,
                   const  T     *  q,
                          T     *  gatherq) {
  for (int k=0;k<Nentries;k++) {
    for(dlong g=0;g<Ngather;++g){

      const dlong start = gatherStarts[g];
      const dlong end = gatherStarts[g+1];
   
      const dlong startId = gatherIds[start];
      T gq = q[startId+k*stride];
      for(dlong n=start+1;n<end;++n){
        const dlong id = gatherIds[n];
        gq = (q[id+k*stride] > gq) ? q[id+k*stride] : gq;
      }

      //contiguously packed
      gatherq[g+k*gstride] = gq;
    }
  }
}

#endif