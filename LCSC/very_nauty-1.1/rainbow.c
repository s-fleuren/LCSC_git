// KMB 2004 Jan 28 
// was rainbow.c-orig
// from http://www.netlib.org/graphics/index.html

/*   rainbow(double h, double s, double v, double *r, double *g, double *b)
 This routine computes colors suitable for use in color level plots.
 Typically s=v=1 and h varies from 0 (red) to 1 (blue) in
 equally spaced steps.  (h=.5 gives green; 1<h<1.5 gives magenta.)
 To convert for frame buffer, use   R = floor(255.999*pow(*r,1/gamma))  etc.
 To get tables calibrated for other devices or to report complaints,
 contact ehg@research.att.com.
*/

/*
 * The author of this software is Eric Grosse.  Copyright (c) 1986,1991 by AT&T.
 * Permission to use, copy, modify, and distribute this software for any
 * purpose without fee is hereby granted, provided that this entire notice
 * is included in all copies of any software which is or includes a copy
 * or modification of this software and in all copies of the supporting
 * documentation for such software.
 * THIS SOFTWARE IS BEING PROVIDED "AS IS", WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTY.  IN PARTICULAR, NEITHER THE AUTHORS NOR AT&T MAKE ANY
 * REPRESENTATION OR WARRANTY OF ANY KIND CONCERNING THE MERCHANTABILITY
 * OF THIS SOFTWARE OR ITS FITNESS FOR ANY PARTICULAR PURPOSE.
 */


#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void dhsv2rgb(double h, double s, double v, double *r, double *g, double *b);
void rainbow(double h, double s, double v, double *r, double *g, double *b);

double   huettab[] = {
 0.0000, 0.0062, 0.0130, 0.0202, 0.0280, 0.0365, 0.0457, 0.0559, 0.0671, 0.0796,
 0.0936, 0.1095, 0.1275, 0.1482, 0.1806, 0.2113, 0.2393, 0.2652, 0.2892, 0.3119,
 0.3333, 0.3556, 0.3815, 0.4129, 0.4526, 0.5060, 0.5296, 0.5501, 0.5679, 0.5834,
 0.5970, 0.6088, 0.6191, 0.6281, 0.6361, 0.6430, 0.6490, 0.6544, 0.6590, 0.6631,
 0.6667, 0.6713, 0.6763, 0.6815, 0.6873, 0.6937, 0.7009, 0.7092, 0.7190, 0.7308,
 0.7452, 0.7631, 0.7856, 0.8142, 0.8621, 0.9029, 0.9344, 0.9580, 0.9755, 0.9889,
 1.0000
};
/* computed from the FMC-1 color difference formula */
/* Barco monitor, max(r,g,b)=1, n=61 magenta,  2 Jan 1986 */

void rainbow(double h, double s, double v, double *r, double *g, double *b) {
   int i;
   double modf(),trash;
   h = 60 * modf(h / 1.5, &trash);
   i = floor(h);
   if (i<0) i=0; // ??
   h = huettab[i] + (huettab[i+1] - huettab[i]) * (h - i);
   dhsv2rgb(h, s, v, r, g, b);
}

void dhsv2rgb(double h, double s, double v, double *r, double *g, double *b)    /*...hexcone model...*/
/* all variables in range [0,1[ */
/* here, h=.667 gives blue, h=0 or 1 gives red. */
{  /* see Alvy Ray Smith, Color Gamut Transform Pairs, SIGGRAPH '78 */
   int   i;
   double   f, m, n, k;
   double   modf(), trash;
   h = 6 * modf(h, &trash);
   i = floor(h);
   f = h - i;
   m = (1 - s);
   n = (1 - s * f);
   k = (1 - (s * (1 - f)));
   switch (i) {
   case 0: 
      *r = 1; 
      *g = k; 
      *b = m; 
      break;
   case 1: 
      *r = n; 
      *g = 1; 
      *b = m; 
      break;
   case 2: 
      *r = m; 
      *g = 1; 
      *b = k; 
      break;
   case 3: 
      *r = m; 
      *g = n; 
      *b = 1; 
      break;
   case 4: 
      *r = k; 
      *g = m; 
      *b = 1; 
      break;
   case 5: 
   default:  // FIXME ??
      *r = 1; 
      *g = m; 
      *b = n; 
      break;
   //default:  // FIXME ??
   //   fprintf(stderr, "bad i: %f %d", h, i); 
   //   exit(1);
   }
   f = *r;
   if ( f < *g ) f = *g;
   if ( f < *b ) f = *b;
   f = v / f;
   *r *= f;
   *g *= f;
   *b *= f;
}


