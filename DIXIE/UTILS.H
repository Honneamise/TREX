#ifndef _UTILS
#define _UTILS

/* HEADERS */
#include "DIXIE/BASE.H"

/*********/
/* UTILS */
/*********/
int RectIntersect(int ax, int ay, int aw, int ah, 
                    int bx, int by, int bw, int bh,
					int *rx, int *ry, int *rw, int *rh);
					
int ImageOverlap(byte *a, int ax, int ay, int aw, int ah, 
                    byte *b, int bx, int by, int bw, int bh, 
                    byte col);

#endif