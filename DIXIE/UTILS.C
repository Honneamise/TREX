#include "DIXIE/BASE.H"

/*********/
int RectIntersect(int ax, int ay, int aw, int ah, 
                    int bx, int by, int bw, int bh,
                    int *rx, int *ry, int *rw, int *rh)
{
	
    int _rx = 0;
    int _ry = 0;
    int _rw = 0;
    int _rh = 0;

    int Amin = 0;
    int Amax = 0;
    int Bmin = 0;
    int Bmax = 0;

    /* Horizontal intersection */
    Amin = ax;
    Amax = Amin + aw;
    Bmin = bx;
    Bmax = Bmin + bw;
    if (Bmin > Amin) { Amin = Bmin; }
    _rx = Amin;
    if (Bmax < Amax) { Amax = Bmax; }
    _rw = Amax - Amin;

    /* Vertical intersection */
    Amin = ay;
    Amax = Amin + ah;
    Bmin = by;
    Bmax = Bmin + bh;
    if (Bmin > Amin) { Amin = Bmin; }
    _ry = Amin;
    if (Bmax < Amax) { Amax = Bmax; }
    _rh = Amax - Amin;

    if(_rw<=0 || _rh<=0)
    { 
        if(rx){ *rx = 0; }
        if(ry){ *ry = 0; }
        if(rw){ *rw = 0; }
        if(rh){ *rh = 0; }

        return 0; 
    }

    if(rx){ *rx = _rx; }
    if(ry){ *ry = _ry; }
    if(rw){ *rw = _rw; }
    if(rh){ *rh = _rh; }

    return 1;
}

/**********/
int ImageOverlap(byte *a, int ax, int ay, int aw, int ah, 
                    byte *b, int bx, int by, int bw, int bh, 
                    byte col)
{

    int i = 0;
    int j = 0;

    byte *_a = a;
    byte *_b = b;

    int rx = 0;
    int ry = 0;
    int rw = 0;
    int rh = 0;

	int res = RectIntersect(ax,ay,aw,ah,bx,by,bw,bh,&rx,&ry,&rw,&rh);
    
    if(res)
    {
        _a += (ry-ay)*aw + (rx-ax);
        _b += (ry-by)*bw + (rx-bx);

        for(i=0;i<rh;i++)
        {
            for(j=0;j<rw;j++)
            {
                if(_a[j]!=col && _b[j]!=col) { return 1; }
            } 
            _a+=aw;
            _b+=bw;
        }
    }

    return 0;
}
