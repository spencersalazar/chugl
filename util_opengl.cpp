/*----------------------------------------------------------------------------
  chugl
  Chuck OpenGL library module

  Copyright (c) 2014 Spencer Salazar.  All rights reserved.
  https://ccrma.stanford.edu/~spencer/

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
  U.S.A.
-----------------------------------------------------------------------------*/

#include "util_opengl.h"

#include <stdlib.h>
#include <math.h>

template<typename V>
inline V &v2d_x(V *v, size_t i) { return v[i*2]; }
template<typename V>
inline V &v2d_y(V *v, size_t i) { return v[i*2+1]; }

void gen2d_ellipse_fan(GLfloat *buf, GLint nVertex, float x, float y, float xRadius, float yRadius)
{
    v2d_x(buf,0) = x; v2d_y(buf,0) = y;
    float two_pi = 2.0f*M_PI;
    for(int i = 1; i < nVertex; i++)
    {
        float fraction = ((float)(i-1))/(nVertex-2);
        v2d_x(buf, i) = x+xRadius*cos(fraction*two_pi);
        v2d_y(buf, i) = y+yRadius*sin(fraction*two_pi);
    }
}

// courtesy of http://www.cs.rit.edu/~ncs/color/t_convert.html
// r,g,b values are from 0 to 1
// h = [0,360], s = [0,1], v = [0,1]
//		if s == 0, then h = -1 (undefined)

// void RGBtoHSV( float r, float g, float b, float *h, float *s, float *v )
// {
//     float min, max, delta;
//     min = MIN( r, g, b );
//     max = MAX( r, g, b );
//     *v = max;                // v
//     delta = max - min;
//     if( max != 0 )
//         *s = delta / max;        // s
//     else {
//         // r = g = b = 0        // s = 0, v is undefined
//         *s = 0;
//         *h = -1;
//         return;
//     }
//     if( r == max )
//         *h = ( g - b ) / delta;        // between yellow & magenta
//     else if( g == max )
//         *h = 2 + ( b - r ) / delta;    // between cyan & yellow
//     else
//         *h = 4 + ( r - g ) / delta;    // between magenta & cyan
//     *h *= 60;                // degrees
//     if( *h < 0 )
//         *h += 360;
// }

void HSVtoRGB( t_CKFLOAT *r, t_CKFLOAT *g, t_CKFLOAT *b, t_CKFLOAT h, t_CKFLOAT s, t_CKFLOAT v )
{
    int i;
    float f, p, q, t;
    if( s == 0 ) {
        // achromatic (grey)
        *r = *g = *b = v;
        return;
    }
    h /= 60; // sector 0 to 5
    i = floor( h );
    f = h - i; // factorial part of h
    p = v * ( 1 - s );
    q = v * ( 1 - s * f );
    t = v * ( 1 - s * ( 1 - f ) );
    switch( i ) {
        case 0:
            *r = v;
            *g = t;
            *b = p;
            break;
        case 1:
            *r = q;
            *g = v;
            *b = p;
            break;
        case 2:
            *r = p;
            *g = v;
            *b = t;
            break;
        case 3:
            *r = p;
            *g = q;
            *b = v;
            break;
        case 4:
            *r = t;
            *g = p;
            *b = v;
            break;
        default: // case 5:
            *r = v;
            *g = p;
            *b = q;
            break;
    }
}


