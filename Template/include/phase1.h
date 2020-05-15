#ifndef PHASE1_H
#define PHASE1_H

#define _GNU_SOURCE

#define LINE_SIZE 256
#define MAX_VARS 20
#define R_SIZE 10000
#define MAX_SPHERES 5000
#define MAX_MTLCOLOR 100
#define MAX_TEXTURE 100
#define MAX_LIGHTS 100
#define MAX_VERTEX 5000
#define MAX_TRIANGLE 5000
#define MAX_REFRACTION 200

#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <dirent.h>
#include <time.h>
#include <ctype.h>

//  color needs 3 values r g b
typedef struct {
  float r, g, b;
} ColorType;

typedef struct {
  int v1, v2, v3;
  int vn1, vn2, vn3;
  int vt1, vt2, vt3;
  //  material color
  int m;
  //  type of triangle
  int t;
  bool text;
  int texture;
} TriangleType;
//  mtlcolor
typedef struct {
  //  intrinsic color of object
  float r, g, b;
  //  color for specular highlight
  float sr, sg, sb;
  //  weights that control surface ambient, diffuse, specular
  float ka, kd, ks;
  //  rate of falloff for specular hightlight
  int n;
  // material opacity
  float o;
  // index of refraction
  float ref;
} MtlColorType;

//  Raytype
typedef struct {
  float x, y, z;  //  origin
  float dx, dy, dz;  //  direction of

} RayType;

//  SphereType
typedef struct {
  float x, y, z;
  float r; //  radius
  int m; // index of mtl color specified
  bool text;
  int texture;
} SphereType;

//  Vector types
typedef struct {
  float x, y, z;
} VectorType;

//  Vector type2
typedef struct {
  float i, j;
} VectorType2;

//  Light types
typedef struct {
  //  could be direction or point
  float x, y, z;
  //  directional(0)/point(1)
  int w;
  //  color
  //  use less than (1,1,1) with multiple lights
  float r, g, b;
} LightType;

//  Values (stored as chars for building ppm)
//  default value -1 check for errors
int line_count;
int width;
int height;

VectorType eye;
VectorType viewdir;
VectorType updir;
float hfov;
ColorType bkgcolor;

//  have to make sure mtlcolor
//  precedes every sphere
//  now need ambient diffuse specular and n
MtlColorType mtlcolor[MAX_MTLCOLOR];

//  could be multiple spheres or cylinders
SphereType sphere[MAX_SPHERES];

//  have light types
LightType light[MAX_LIGHTS];

//  vertex types
VectorType vertex[MAX_VERTEX];

//  vertext types
VectorType2 vertext[MAX_VERTEX];

// normal array
VectorType normal[MAX_VERTEX];


//  regular triangle types
TriangleType triangle[MAX_TRIANGLE];
//  type of triangles
// 0 : base
// 1 : smooth
// 2 : textured
// 3 : smooth and textured


//  check if mtlcolor precedes sphere
bool check;
bool check2;

//  index of normal array
int n_index;
//  index of mtlcolor;
int m_index;
//  index of sphere
int s_index;
//  index of light
int l_index;
//  index of Vertex
int v_index;
//  index of Vertext
int vt_index;
//  index of triangles
int t_index;

//  height and width of texture
int t_height;
int t_width;

//  check for arguments provided
bool arg_1;
bool arg_2;
bool arg_3;
bool arg_4;
bool arg_5;
bool arg_6;
bool arg_7;

//float *cylinder[8] ;

//  have to dynamically size array
//  use width and height for boundaries
ColorType **array;

//  store material ppm array has index height width
ColorType ***m_array;
int text_index;


//  holds the file line
char file_line[R_SIZE][LINE_SIZE];

//  function to process the input file
int process_file(char *fname);
//  function to process ppm file


//  parse file_line into variables
int parser();
//  form parser initialize vars
int init_vars();

#endif
