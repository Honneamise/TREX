#ifndef _CORE
#define _CORE

#include "DIXIE/BASE.H"

#define WIDTH 320
#define HEIGHT 200

#define PALETTE_0 0x00
#define PALETTE_1 0x01

#define COLOR_0 0x00
#define COLOR_1 0x01
#define COLOR_2 0x02
#define COLOR_3 0x03

#define P 0
#define C  4560
#define C_ 4304
#define D  4063
#define D_ 3834
#define E  3619
#define F  3416
#define F_ 3224
#define G  3043
#define G_ 2873
#define A  2711
#define A_ 2559
#define B  2415

void Init();

void Close();

void Update();

void Palette(byte p);

void Clear(byte c);

void SwapBuffers();

void Color(byte c);

void Pixel(int x, int y);

void Line(int sx, int sy, int dx, int dy);

void Triangle(int ax, int ay, int bx, int by, int cx, int cy);

void TriangleFill(int ax, int ay, int bx, int by, int cx, int cy);

void Rectangle(int x, int y, int w, int h);

void RectangleFill(int x, int y, int w, int h);

void Circle(int cx, int cy, int r);

void CircleFill(int cx, int cy, int r);

void Image(byte *buf, int w, int h, int x, int y);

void ImageMask(byte *buf, int w, int h, int x, int y, byte mask);

void Char(char c, int x, int y);

void String(char *s, int x, int y);

void Sound(int note, float len);

void StopSound();

int SoundPlaying();

#endif