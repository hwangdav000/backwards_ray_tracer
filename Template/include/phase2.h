#ifndef PHASE2_H
#define PHASE2_H

#define M_PI 3.14159265358979323846

#include "phase1.h"
#include <math.h>

//  vectors for viewing window
VectorType u;
VectorType v;
VectorType n;

//  corners of viewing window
VectorType ul;
VectorType ur;
VectorType ll;
VectorType lr;

//  vectors for phong illumination
VectorType n_ill;
//  vector for direction of incoming Ray
VectorType I;


//  ray/sphere intersection
VectorType rs_int;
//  ray/triangle intersection
VectorType rt_int;

//  triangle area
float r_Alpha;
float r_Beta;
float r_Zeta;

//  arbitrary distance from origin to viewing window
float distance;

// depth of recursion max
float depth1;
float depth_max;
//  width and height of viewing window
//  need to be int cannot have half a pixel
int v_width;
int v_height;
float aspect_ratio;
float *shadow;
//  center of viewing window
VectorType c_horizontal;
VectorType c_vertical;

//  offset for viewing window
VectorType h_offset;
VectorType v_offset;

// incoming refraction index
float in_ref;

//  result of reflection and refraction
ColorType result2;
ColorType result3;

//  build PPM of array
void build_PPM();

//  calculate length of vector
float calcLength(VectorType v1);

//  calculate dot product of two vectors
float dotProduct(VectorType v1, VectorType v2);

//  calculate degrees to radian
float dToR(float degrees);

//  quadratic equation
float quadratic(float A, float B, float C);
//  calculate the cross of two vectors
VectorType calcCross(VectorType v1, VectorType v2);

//  set u and v
void setVar();

//  max
float max(float num);

//  clamp
float clamp(float num);

//  initialize array
void init_array();

void deallocate_array();

ColorType Trace_Ray(RayType Ray, int depth);

ColorType Shade_Ray(int id, int type, RayType Ray, int depth);

#endif
