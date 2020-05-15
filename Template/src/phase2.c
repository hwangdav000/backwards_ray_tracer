#include "phase2.h"

//  calculate length of vector
float calcLength(VectorType v1) {
  return sqrt(v1.x*v1.x + v1.y*v1.y + v1.z*v1.z);
}

//  calculate dot product of vector
float dotProduct(VectorType v1, VectorType v2) {
  return (v1.x*v2.x + v1.y*v2.y + v1.z*v2.z);
}
//  checks if num is negative if so return 0
float max(float num) {
  if (0.0 > num) {
    return 0.0;
  }
  return num;
}
//  if over 1 clamps to 1 if under 0 clamps to 0
float clamp(float num) {
  if (num > 1.0) {
    return 1.0;
  }
  if (num < 0.0) {
    return 0.0;
  }
  return num;
}

//  if over 1 clamps to 1 if under 0 clamps to 0
int clamp2(float num) {
  if (num > 255.0) {
    return 255;
  }
  if (num < 0.0) {
    return 0;
  }
  return (int)num;
}

//  calculate the cross of two vectors v1 x v2
VectorType calcCross(VectorType v1, VectorType v2) {
  VectorType cross;

  //  cross of two vectors
  cross.x = v1.y*v2.z - v1.z*v2.y;
  cross.y = v1.z*v2.x - v1.x*v2.z;
  cross.z = v1.x*v2.y - v1.y*v2.x;

  return cross;
}

//  calculate the sub of v1 and v2
VectorType sub(VectorType v1, VectorType v2) {
  VectorType result;

  //  sub the two vectors
  result.x = v1.x - v2.x;
  result.y = v1.y - v2.y;
  result.z = v1.z - v2.z;

  return result;
}

//  calculate the add of v1 and v2
VectorType add(VectorType v1, VectorType v2) {
  VectorType result;

  //  sub the two vectors
  result.x = v1.x + v2.x;
  result.y = v1.y + v2.y;
  result.z = v1.z + v2.z;

  return result;
}

//  calculate the add of v1 and v2
VectorType multiply(VectorType v1, float c) {
  VectorType result;

  //  sub the two vectors
  result.x = v1.x*c;
  result.y = v1.y*c;
  result.z = v1.z*c;

  return result;
}

VectorType normalize(VectorType v1) {
  VectorType result;
  float length = calcLength(v1);

  result.x = v1.x / length;
  result.y = v1.y / length;
  result.z = v1.z / length;

  return result;
}

VectorType negation(VectorType v1) {
  VectorType result;
  result.x = -v1.x;
  result.y = -v1.y;
  result.z = -v1.z;

  return result;
}

VectorType col_to_vect(ColorType v1) {
  VectorType result;
  result.x = v1.r;
  result.y = v1.g;
  result.z = v1.b;

  return result;
}
ColorType vect_to_col(VectorType v1) {
  ColorType result;
  result.r = v1.x;
  result.g = v1.y;
  result.b = v1.z;

  return result;
}

//  degree to radian
float dToR(float degrees){
  return (degrees * (M_PI/180));
}

//  set variables
void setVar() {

  //printf("setting vars\n");
  distance = 30;
  //  calculate unit vector u
  VectorType u = (calcCross(viewdir, updir));
  float uLength = calcLength(u);

  u.x = u.x/uLength;
  u.y = u.y/uLength;
  u.z = u.z/uLength;

  //  calculate unit vector v
  VectorType v = (calcCross(u, viewdir));
  float vLength = calcLength(v);

  v.x = v.x/vLength;
  v.y = v.y/vLength;
  v.z = v.z/vLength;

  //  set u and v
  v_width = (int) round(2 * distance * tan(dToR(hfov)/2));

  aspect_ratio = (float)width / (float)height;

  v_height = (int) round(v_width/aspect_ratio);

  //  set n :unit vector in viewing direction
  float nLength = calcLength(viewdir);
  n.x = viewdir.x;
  n.y = viewdir.y;
  n.z = viewdir.z;
  //div by 0
  if (nLength == 0) {
    printf("error by 0 in init vars");
    return;
  }
  n.x = n.x/nLength;
  n.y = n.y/nLength;
  n.z = n.z/nLength;

  //  set corners of viewing window
  ul.x = eye.x + distance*n.x - (v_width/2)*u.x + (v_height/2)*v.x;
  ul.y = eye.y + distance*n.y - (v_width/2)*u.y + (v_height/2)*v.y;
  ul.z = eye.z + distance*n.z - (v_width/2)*u.z + (v_height/2)*v.z;

  ur.x = eye.x + distance*n.x + (v_width/2)*u.x + (v_height/2)*v.x;
  ur.y = eye.y + distance*n.y + (v_width/2)*u.y + (v_height/2)*v.y;
  ur.z = eye.z + distance*n.z + (v_width/2)*u.z + (v_height/2)*v.z;

  ll.x = eye.x + distance*n.x - (v_width/2)*u.x - (v_height/2)*v.x;
  ll.y = eye.y + distance*n.y - (v_width/2)*u.y - (v_height/2)*v.y;
  ll.z = eye.z + distance*n.z - (v_width/2)*u.z - (v_height/2)*v.z;

  lr.x = eye.x + distance*n.x + (v_width/2)*u.x - (v_height/2)*v.x;
  lr.y = eye.y + distance*n.y + (v_width/2)*u.y - (v_height/2)*v.y;
  lr.z = eye.z + distance*n.z + (v_width/2)*u.z - (v_height/2)*v.z;

  //  calculate the center of viewing window
  c_horizontal.x = (ur.x - ul.x)/(2*width);
  c_horizontal.y = (ur.y - ul.y)/(2*width);
  c_horizontal.z = (ur.z - ul.z)/(2*width);

  c_vertical.x = (ll.x - ul.x)/(2*height);
  c_vertical.y = (ll.y - ul.y)/(2*height);
  c_vertical.z = (ll.z - ul.z)/(2*height);

  //  caculate the offset for viewing window
  h_offset.x = (ur.x - ul.x)/(width-1);
  h_offset.y = (ur.y - ul.y)/(width-1);
  h_offset.z = (ur.z - ul.z)/(width-1);

  v_offset.x = (ll.x - ul.x)/(height-1);
  v_offset.y = (ll.y - ul.y)/(height-1);
  v_offset.z = (ll.z - ul.z)/(height-1);
  ////////////TESTING

  //  get index of vertices
  int v1 = triangle[1].v1;
  int v2 = triangle[1].v2;
  int v3 = triangle[1].v3;
  //printf("%f %f %f\n", ul.x, ul.y, ul.z);
  //printf("ending vars\n");
}
//  quadratic equation
float quadratic(float A, float B, float C){
  //  check if t exists
  float disc =(pow(B,2) - 4*A*C);
  float solution = -1;

  //  if disc positive or zero there exist a solution
  if (disc >= 0){
    //  only interested in situations in which distance t is positive
    float s1 = (-B + sqrt(disc))/ (2*A);
    float s2 = (-B - sqrt(disc))/ (2*A);

    //  check for smallest positive t;
    if (s1 > 0 && s2 > 0) {
      if (s1 > s2) {
        solution = s2;
      } else {
        solution = s1;
      }
      //  s1 is positive and s2 is negativ
    } else if (s1 > 0 && s2 < 0) {
      solution = s1;

      //  contra
    } else if (s1 < 0 && s2 > 0) {
      solution = s2;

    }
  }

  return solution;
}

//  determine color of pane
//  id is id of sphere
ColorType Shade_Ray(int id, int type, RayType ray, int depth) {
  //  type can be  either 0 or 1
  // 0: sphere
  // 1: triangle

  if (type == 0) {
    //  get respective mtl id
    //  use phong illumination model to calculate light intensity
    ColorType result;
    int mtl_id;
    mtl_id = sphere[id].m;
    //  get n_ill, surface normal where illumination is calc.
    n_ill.x = (rs_int.x - sphere[id].x)/sphere[id].r;
    n_ill.y = (rs_int.y - sphere[id].y)/sphere[id].r;
    n_ill.z = (rs_int.z - sphere[id].z)/sphere[id].r;

    //  get ambient
    ColorType ambient;

    //  check if sphere has texture
    if (sphere[id].text) {
      //  M_PI is pi
      float theta = atan((float) (rs_int.y - sphere[id].y)/(rs_int.x - sphere[id].x));
      //  returns in radians
      float phi = acos((float) (rs_int.z - sphere[id].z) / sphere[id].r);


      float v = (float) phi / M_PI;
      // in case of theta is less than 0
      if (theta < 0) {
        theta = theta + 2*M_PI;
      }
      float u = (float) (theta)/ (2*M_PI);

      //  u and v are between the image width and height of the texture
      // u is going to the the width v is going to be the height index

      int iu = round(u * (t_width-1));
      int iv = round(v * (t_height-1));

      if (iu < 0 || iv < 0) {
        iu = 0;
        iv = 0;
      }

      int text_id = sphere[id].texture;
      //printf("%d %d %d\n", iv , iu, text_id);


      ambient.r =  mtlcolor[mtl_id].ka *m_array[text_id][iv][iu].r;
      ambient.g =  mtlcolor[mtl_id].ka *m_array[text_id][iv][iu].g;
      ambient.b =  mtlcolor[mtl_id].ka *m_array[text_id][iv][iu].b;
    } else {

      //  no texture
      ambient.r =  mtlcolor[mtl_id].ka * mtlcolor[mtl_id].r;
      ambient.g =  mtlcolor[mtl_id].ka * mtlcolor[mtl_id].g;
      ambient.b =  mtlcolor[mtl_id].ka * mtlcolor[mtl_id].b;
    }
    //  initialize ambience
    result.r = ambient.r;
    result.g = ambient.g;
    result.b = ambient.b;

    //  get diffuse
    ColorType diffuse;
    //  get specular diffusion
    ColorType specular;

    //  for each light source calculate diffuse and specular
    //  and consecutively add up light intensities
    for (int i = 0 ; i < l_index+1; i++) {
      //  need N(n_ill), H(h_ill), L(l_ill)
      //  calculate L need to check if light is directional or point
      VectorType temp_light;
      temp_light.x = light[l_index].x;
      temp_light.y = light[l_index].y;
      temp_light.z = light[l_index].z;

      //  negative of view direction
      VectorType v_ill;

      //  initialize L and H
      VectorType l_ill;
      VectorType h_ill;
      float v_length = calcLength(viewdir);
      v_ill.x = -viewdir.x / v_length;
      v_ill.y = -viewdir.y / v_length;
      v_ill.z = -viewdir.z / v_length;

      if (light[l_index].w == 0) { //  directional

        //  calculate direction light length
        float l_length = calcLength(temp_light);

        //  calculate directional light
        l_ill.x = (-light[l_index].x/l_length);
        l_ill.y = (-light[l_index].y/l_length);
        l_ill.z = (-light[l_index].z/l_length);

        //  shadow dir
        //  origin at ray/surface intersection point
        ////////////////////////////////
        VectorType shadowDir;
        shadowDir.x = l_ill.x;
        shadowDir.y = l_ill.y;
        shadowDir.z = l_ill.z;

        bool is_intersect = false;
        //  no shadow
        shadow[l_index] = 1.0;
        //  check for intersection with each object
        for(int i = 0; i < s_index+1; i++) {

          //  pass own object
          if (i == id) {
            continue;
          }

          //  check for intersection of object
          float A = 1;
          float B = 2 * (shadowDir.x * (rs_int.x-sphere[i].x) + shadowDir.y * (rs_int.y-sphere[i].y) + shadowDir.z * (rs_int.z - sphere[i].z));
          float C = pow((rs_int.x - sphere[i].x),2) + pow((rs_int.y - sphere[i].y),2) + pow((rs_int.z - sphere[i].z),2) - pow(sphere[i].r,2);
          float t = quadratic(A,B,C);

          //  just care if there is an intersection
          if (t > 0) {
            is_intersect = true;
            shadow[l_index] = shadow[l_index]*(1-in_ref);
            break;
          }
        }

        VectorType addV;
        addV.x = v_ill.x + l_ill.x;
        addV.y = v_ill.y + l_ill.y;
        addV.z = v_ill.z + l_ill.z;

        float addv_length = calcLength(addV);
        //  calculate H (calculate L+V (normalized))
        h_ill.x = (l_ill.x + v_ill.x)/(addv_length);
        h_ill.y = (l_ill.y + v_ill.y)/(addv_length);
        h_ill.z = (l_ill.z + v_ill.z)/(addv_length);

        //  get diffuse
        float d_temp;
        //  check is sphere has texture
        if (sphere[id].text){
          d_temp = max(dotProduct(n_ill, l_ill));
          diffuse.r = mtlcolor[mtl_id].kd *ambient.r*d_temp;
          diffuse.g = mtlcolor[mtl_id].kd *ambient.g*d_temp;
          diffuse.b = mtlcolor[mtl_id].kd *ambient.b*d_temp;
        } else {
          d_temp = max(dotProduct(n_ill, l_ill));
          diffuse.r = mtlcolor[mtl_id].kd * mtlcolor[mtl_id].r*d_temp;
          diffuse.g = mtlcolor[mtl_id].kd * mtlcolor[mtl_id].g*d_temp;
          diffuse.b = mtlcolor[mtl_id].kd * mtlcolor[mtl_id].b*d_temp;
        }
        //  specular
        float s_temp;

        s_temp = max(dotProduct(n_ill, h_ill));
        s_temp = pow(s_temp, mtlcolor[mtl_id].n);
        specular.r = mtlcolor[mtl_id].ks * mtlcolor[mtl_id].sr*s_temp;
        specular.g = mtlcolor[mtl_id].ks * mtlcolor[mtl_id].sg*s_temp;
        specular.b = mtlcolor[mtl_id].ks * mtlcolor[mtl_id].sb*s_temp;

        //  add to result consecutively
        result.r = result.r + (diffuse.r + specular.r)*light[l_index].r*shadow[l_index];
        result.g = result.g + (diffuse.g + specular.g)*light[l_index].g*shadow[l_index];
        result.b = result.b + (diffuse.b + specular.b)*light[l_index].b*shadow[l_index];

      } else { //  point

        //  calculate point light length
        temp_light.x = light[l_index].x - rs_int.x;
        temp_light.y = light[l_index].y - rs_int.y;
        temp_light.z = light[l_index].z - rs_int.z;
        float l_length = calcLength(temp_light);

        //  light position - surface position
        l_ill.x = (light[l_index].x - rs_int.x)/l_length;
        l_ill.y = (light[l_index].y - rs_int.y)/l_length;
        l_ill.z = (light[l_index].z - rs_int.z)/l_length;

        //  check if there is a shadow
        //  origin at ray/surface intersection point
        ///////////////////////////////////
        VectorType shadowDir;
        shadowDir.x = l_ill.x;
        shadowDir.y = l_ill.y;
        shadowDir.z = l_ill.z;

        bool is_intersect = false;
        shadow[l_index] = 1.0;

        //  check for intersection with each object
        for(int i = 0; i < s_index+1; i++) {

          //  pass own object
          if (i == id) {
            continue;
          }
          //  check for intersection of object
          float A = 1;
          float B = 2 * (shadowDir.x * (rs_int.x-sphere[i].x) + shadowDir.y * (rs_int.y-sphere[i].y) + shadowDir.z * (rs_int.z - sphere[i].z));
          float C = pow((rs_int.x - sphere[i].x),2) + pow((rs_int.y - sphere[i].y),2) + pow((rs_int.z - sphere[i].z),2) - pow(sphere[i].r,2);
          float t = quadratic(A,B,C);

          //  just care if there is an intersection
          if (t > 0 ) {
            is_intersect = true;
            shadow[l_index] = shadow[l_index]*(1-in_ref);
            break;
          }
        }

        VectorType addV;
        addV.x = v_ill.x + l_ill.x;
        addV.y = v_ill.y + l_ill.y;
        addV.z = v_ill.z + l_ill.z;

        float addv_length = calcLength(addV);
        //  calculate H (calculate L+V (normalized))
        h_ill.x = (l_ill.x + v_ill.x)/(addv_length);
        h_ill.y = (l_ill.y + v_ill.y)/(addv_length);
        h_ill.z = (l_ill.z + v_ill.z)/(addv_length);

        //  get diffuse
        float d_temp;
        //  check is sphere has texture
        if (sphere[id].text){
          d_temp = max(dotProduct(n_ill, l_ill));
          diffuse.r = ambient.r*d_temp;
          diffuse.g = ambient.g*d_temp;
          diffuse.b = ambient.b*d_temp;
        } else {
          d_temp = max(dotProduct(n_ill, l_ill));
          diffuse.r = mtlcolor[mtl_id].kd * mtlcolor[mtl_id].r*d_temp;
          diffuse.g = mtlcolor[mtl_id].kd * mtlcolor[mtl_id].g*d_temp;
          diffuse.b = mtlcolor[mtl_id].kd * mtlcolor[mtl_id].b*d_temp;
        }
        //  specular
        float s_temp;
        s_temp = max(dotProduct(n_ill, h_ill));
        s_temp = pow(s_temp, mtlcolor[mtl_id].n);
        specular.r = mtlcolor[mtl_id].ks * mtlcolor[mtl_id].sr*s_temp;
        specular.g = mtlcolor[mtl_id].ks * mtlcolor[mtl_id].sg*s_temp;
        specular.b = mtlcolor[mtl_id].ks * mtlcolor[mtl_id].sb*s_temp;

        //  add to result consecutively
        result.r = result.r + (diffuse.r + specular.r)*light[l_index].r*shadow[l_index];
        result.g = result.g + (diffuse.g + specular.g)*light[l_index].g*shadow[l_index];
        result.b = result.b + (diffuse.b + specular.b)*light[l_index].b*shadow[l_index];
      }
    }

    // FINDME1
    ///////////////////////////////////////////////////
    // Specular Reflection
    // spec reflectance and fresnel
    //  case if depth too large

    if (depth > 0) {

      VectorType s_ref;
      RayType refl_ray;
      float Fr;

      //  get I'
      I.x = rs_int.x - ray.x;
      I.y = rs_int.y - ray.y;
      I.z = rs_int.z - ray.z;

      // normalize I;
      I = normalize(I);

      // reverse i' to get I
      I.x = -I.x;
      I.y = -I.y;
      I.z = -I.z;

      // cosine of the angle of incidence
      float a = dotProduct(n_ill, I);

      //  check if n_ill is facing wrong way
      if (a < 0) {
        n_ill = negation(n_ill);
        a = dotProduct(n_ill, I);
      }

      /////////////////////////////////////////
      // accumulate reflection
      //  compute specular reflection dir
      s_ref = sub(multiply(n_ill, 2*a), I);

      // create reflect ray
      refl_ray.x = rs_int.x;
      refl_ray.y = rs_int.y;
      refl_ray.z = rs_int.z;
      refl_ray.dx = s_ref.x;
      refl_ray.dy = s_ref.y;
      refl_ray.dz = s_ref.z;

      //// compute fresnel reflectance coefficient
      float F0 = pow((mtlcolor[mtl_id].ref-in_ref)/(mtlcolor[mtl_id].ref+in_ref),2);
      Fr = F0 + (1-F0)*pow((1-a), 5);

      //  Fr is to the power of depth
      //  Fr will have values in range [F0, 1]
      if (Fr < F0 || Fr > 1) {
        //  change value to F0
        if (Fr < F0) {
          Fr = F0;
        } else {
          Fr = 1;
        }
      }
      Fr = pow(Fr, depth_max+1 - depth);

      //printf("Fr %f\n", Fr);
      //result2 = vect_to_col(add(col_to_vect(result2), multiply(col_to_vect(Trace_Ray(refl_ray, depth-1)), Fr)));
      result = vect_to_col(add(col_to_vect(result), multiply(col_to_vect(Trace_Ray(refl_ray, depth-1)), Fr)));
      //////////////////////////////////////////////
      //  compute transparency in ray tracing / refraction

      // account for total internal reflection
      // if incident ray starts in air and goes to more dense material fraction
      // nt/ ni will be greater than 1 so total internal reflection cannot occur

      // if incident ray starts in a more dense material then exists into a
      // less dense material then nt/ ni will be less than  1 and it will
      // be possible to have total internal reflection which transmits no ray
      if (mtlcolor[mtl_id].ref > in_ref) {
        //  will have TIR from crit_angle to 90
        float crit_angle = asin(mtlcolor[mtl_id].ref/in_ref);
        float cos_in = a;
        float sin_in = sqrt(1-pow(cos_in,2));
        float sin_at = (in_ref / mtlcolor[mtl_id].ref)*sin_in;
        float check_cos_at = 1-pow(sin_at, 2);

        // no transmitted ray
        if(check_cos_at < 0 || (sin_in > (mtlcolor[mtl_id].ref/in_ref)) ) {
          //printf("not transmited");
          return result;
        }
      }


      float cos_in = a;
      float sin_in = sqrt(1-pow(cos_in,2));
      float sin_at = (in_ref / mtlcolor[mtl_id].ref)*sin_in;
      float cos_at = sqrt(1-pow(sin_at, 2));

      VectorType T;
      VectorType temp = sub(multiply(n_ill, cos_in), I);
      T = add(multiply(negation(n_ill),cos_at),multiply(temp, (in_ref/(float)mtlcolor[mtl_id].ref)));

      //in_ref is the previous object refraction
      in_ref = mtlcolor[mtl_id].ref;
      //transp = multiply(T, (1-Fr)*(1-mtlcolor[mtl_id].o));

      RayType refr_ray;
      refr_ray.x = rs_int.x;
      refr_ray.y = rs_int.y;
      refr_ray.z = rs_int.z;
      refr_ray.dx = T.x;
      refr_ray.dy = T.y;
      refr_ray.dz = T.z;

      result = vect_to_col(add(col_to_vect(result), multiply(col_to_vect(Trace_Ray(refr_ray, depth-1)), (1-Fr)*(1-mtlcolor[mtl_id].o))));
    }



    result.r = clamp(result.r);
    result.g = clamp(result.g);
    result.b = clamp(result.b);
    if (result.r < 0 || result.g < 0 || result.b < 0 || result.r > 1.0 || result.g > 1.0 || result.b > 1.0) {
      printf("clamping not working\n");
      printf("red: %f\n" , result.r);
      printf("green: %f\n" , result.g);
      printf("blue: %f\n" , result.b);
      exit(0);
    }
    //  get result of phong illumination
    return result;

  } else if (type == 1) { //  triangles

    ColorType result;
    // change later
    int c_id = triangle[id].m;
    int text_id = triangle[id].texture;
    //  Need to know if point p is inside the triangle or not
    //  p is where ray intersect plane of triangle (rt_int)
    //////////////////////////////
    //  TRIANGLE BARYCENTRIC COORD

    int v1 = triangle[id].v1;
    int v2 = triangle[id].v2;
    int v3 = triangle[id].v3;

    VectorType e1 = sub(vertex[v2], vertex[v1]);
    VectorType e2 = sub(vertex[v3], vertex[v1]);

    //  triangle normal (e1 x e2) n
    VectorType n= calcCross(e1, e2);

    //  get respective mtl id
    int mtl_id;
    mtl_id = triangle[id].m;

    //  use phong illumination model to calculate light intensity
    VectorType n_ill;
    //  get n_ill, surface normal where illumination is calc.
    //  smooth calcs
    if (triangle[id].t == 1 || triangle[id].t == 3) {
      //  index of normals

      int i_vn1 = triangle[id].vn1;
      int i_vn2 = triangle[id].vn2;
      int i_vn3 = triangle[id].vn3;
      //printf("%f %f %f\n", r_Alpha, r_Beta, r_Zeta);
      //printf("TRIANGLE ID: %d %f %f %f\n", id, normal[i_vn1].x, normal[i_vn1].y, normal[i_vn1].z);
      VectorType a_1 = multiply(normal[i_vn1], r_Alpha);
      VectorType a_2 = multiply(normal[i_vn2], r_Beta);
      VectorType a_3 = multiply(normal[i_vn3], r_Zeta);
      VectorType a_sum = add(a_1, a_2);
      VectorType sum = add(a_sum, a_3);
      VectorType norm = normalize(sum);
      VectorType renorm = normalize(norm);

      n_ill = renorm;

    } else {
      // for base and not smooth but textured

      n_ill = normalize(n);
    }
    //  get ambient
    ColorType ambient;
    ColorType textc;
    //  if triangle is textured by ppm
    if ((triangle[id].t == 2 || triangle[id].t == 3) && triangle[id].text) {
      //printf("check\n");
      //  get u and v
      //  index of vertex coord
      //printf("check\n");
      //printf("A: %f %f %f\n", r_Alpha, r_Beta, r_Zeta);
      int i_vt1 = triangle[id].vt1;
      int i_vt2 = triangle[id].vt2;
      int i_vt3 = triangle[id].vt3;
      float u = r_Alpha*vertext[i_vt1].i + r_Beta*vertext[i_vt2].i + r_Zeta*vertext[i_vt3].i;
      float v = r_Alpha*vertext[i_vt1].j + r_Beta*vertext[i_vt2].j + r_Zeta*vertext[i_vt3].j;
      //printf("B: %f %f %f\n",vertext[i_vt1].i, vertext[i_vt2].i, vertext[i_vt3].i);
      int i = round(u*(t_width-1));
      int j = round(v*(t_height-1));
      //printf("R: %d %d\n", i ,j);
      //exit(0);
      ambient.r =  mtlcolor[mtl_id].ka * m_array[text_id][j][i].r;
      ambient.g =  mtlcolor[mtl_id].ka * m_array[text_id][j][i].g;
      ambient.b =  mtlcolor[mtl_id].ka * m_array[text_id][j][i].b;

      textc.r =  m_array[text_id][j][i].r;
      textc.g =  m_array[text_id][j][i].g;
      textc.b =  m_array[text_id][j][i].b;
    } else {
      //  if triangle does not have texture
      ambient.r =  mtlcolor[mtl_id].ka * mtlcolor[mtl_id].r;
      ambient.g =  mtlcolor[mtl_id].ka * mtlcolor[mtl_id].g;
      ambient.b =  mtlcolor[mtl_id].ka * mtlcolor[mtl_id].b;
    }
    //  initialize ambience
    result.r = ambient.r;
    result.g = ambient.g;
    result.b = ambient.b;

    //  get diffuse
    ColorType diffuse;
    //  get specular diffusion
    ColorType specular;
    //  for each light source calculate diffuse and specular
    //  and consecutively add up light intensities
    for (int i = 0 ; i < l_index+1; i++) {
      //  need N(n_ill), H(h_ill), L(l_ill)
      //  calculate L need to check if light is directional or point
      VectorType temp_light;
      temp_light.x = light[l_index].x;
      temp_light.y = light[l_index].y;
      temp_light.z = light[l_index].z;

      //  negative of view direction
      VectorType v_ill;

      //  initialize L and H
      VectorType l_ill;
      VectorType h_ill;
      float v_length = calcLength(viewdir);
      v_ill.x = -viewdir.x / v_length;
      v_ill.y = -viewdir.y / v_length;
      v_ill.z = -viewdir.z / v_length;

      if (light[l_index].w == 0) { //  directional

        //  calculate direction light length
        float l_length = calcLength(temp_light);

        //  calculate directional light
        l_ill.x = (-light[l_index].x/l_length);
        l_ill.y = (-light[l_index].y/l_length);
        l_ill.z = (-light[l_index].z/l_length);

        //  shadow dir
        //  origin at ray/surface intersection point
        ////////////////////////////////
        VectorType shadowDir;
        shadowDir.x = l_ill.x;
        shadowDir.y = l_ill.y;
        shadowDir.z = l_ill.z;

        bool is_intersect = false;
        //  no shadow
        shadow[l_index] = true;
        //  handle shadows later

        VectorType addV;
        addV.x = v_ill.x + l_ill.x;
        addV.y = v_ill.y + l_ill.y;
        addV.z = v_ill.z + l_ill.z;

        float addv_length = calcLength(addV);
        //  calculate H (calculate L+V (normalized))
        h_ill.x = (l_ill.x + v_ill.x)/(addv_length);
        h_ill.y = (l_ill.y + v_ill.y)/(addv_length);
        h_ill.z = (l_ill.z + v_ill.z)/(addv_length);

        //  get diffuse
        // check if has texture
        float d_temp;
        if (triangle[id].text && (triangle[id].t == 2 || triangle[id].t == 3)){
          d_temp = max(dotProduct(n_ill, l_ill));
          diffuse.r = mtlcolor[mtl_id].kd * textc.r*d_temp;
          diffuse.g = mtlcolor[mtl_id].kd * textc.g*d_temp;
          diffuse.b = mtlcolor[mtl_id].kd * textc.b*d_temp;
        } else {
          d_temp = max(dotProduct(n_ill, l_ill));
          diffuse.r = mtlcolor[mtl_id].kd * mtlcolor[mtl_id].r*d_temp;
          diffuse.g = mtlcolor[mtl_id].kd * mtlcolor[mtl_id].g*d_temp;
          diffuse.b = mtlcolor[mtl_id].kd * mtlcolor[mtl_id].b*d_temp;
        }

        //  specular
        float s_temp;
        s_temp = max(dotProduct(n_ill, h_ill));
        s_temp = pow(s_temp, mtlcolor[mtl_id].n);
        specular.r = mtlcolor[mtl_id].ks * mtlcolor[mtl_id].sr*s_temp;
        specular.g = mtlcolor[mtl_id].ks * mtlcolor[mtl_id].sg*s_temp;
        specular.b = mtlcolor[mtl_id].ks * mtlcolor[mtl_id].sb*s_temp;

        //  add to result consecutively
        result.r = result.r + (diffuse.r + specular.r)*light[l_index].r;//*shadow[l_index];
        result.g = result.g + (diffuse.g + specular.g)*light[l_index].g;//*shadow[l_index];
        result.b = result.b + (diffuse.b + specular.b)*light[l_index].b;//*shadow[l_index];

      } else { //  point

        //  calculate point light length
        temp_light.x = light[l_index].x - rt_int.x;
        temp_light.y = light[l_index].y - rt_int.y;
        temp_light.z = light[l_index].z - rt_int.z;
        float l_length = calcLength(temp_light);

        //  light position - surface position
        l_ill.x = (light[l_index].x - rt_int.x)/l_length;
        l_ill.y = (light[l_index].y - rt_int.y)/l_length;
        l_ill.z = (light[l_index].z - rt_int.z)/l_length;

        //  check if there is a shadow
        //  origin at ray/surface intersection point
        ///////////////////////////////////
        VectorType shadowDir;
        shadowDir.x = l_ill.x;
        shadowDir.y = l_ill.y;
        shadowDir.z = l_ill.z;

        //  handle shadows later
        /////////////////////////////
        VectorType addV;
        addV.x = v_ill.x + l_ill.x;
        addV.y = v_ill.y + l_ill.y;
        addV.z = v_ill.z + l_ill.z;

        float addv_length = calcLength(addV);
        //  calculate H (calculate L+V (normalized))
        h_ill.x = (l_ill.x + v_ill.x)/(addv_length);
        h_ill.y = (l_ill.y + v_ill.y)/(addv_length);
        h_ill.z = (l_ill.z + v_ill.z)/(addv_length);

        //  get diffuse
        float d_temp;
        //  check if has texture
        if (triangle[id].text && (triangle[id].text == 2 || triangle[id].text == 3)) {
          d_temp = max(dotProduct(n_ill, l_ill));
          diffuse.r = mtlcolor[mtl_id].kd * textc.r*d_temp;
          diffuse.g = mtlcolor[mtl_id].kd * textc.g*d_temp;
          diffuse.b = mtlcolor[mtl_id].kd * textc.b*d_temp;
        } else {
          d_temp = max(dotProduct(n_ill, l_ill));
          diffuse.r = mtlcolor[mtl_id].kd * mtlcolor[mtl_id].r*d_temp;
          diffuse.g = mtlcolor[mtl_id].kd * mtlcolor[mtl_id].g*d_temp;
          diffuse.b = mtlcolor[mtl_id].kd * mtlcolor[mtl_id].b*d_temp;
        }
        //  specular
        float s_temp;
        s_temp = max(dotProduct(n_ill, h_ill));
        s_temp = pow(s_temp, mtlcolor[mtl_id].n);
        specular.r = mtlcolor[mtl_id].ks * mtlcolor[mtl_id].sr*s_temp;
        specular.g = mtlcolor[mtl_id].ks * mtlcolor[mtl_id].sg*s_temp;
        specular.b = mtlcolor[mtl_id].ks * mtlcolor[mtl_id].sb*s_temp;

        //  add to result consecutively
        result.r = result.r + (diffuse.r + specular.r)*light[l_index].r;//*shadow[l_index];
        result.g = result.g + (diffuse.g + specular.g)*light[l_index].g;//*shadow[l_index];
        result.b = result.b + (diffuse.b + specular.b)*light[l_index].b;//*shadow[l_index];
      }
    }

    result.r = clamp(result.r);
    result.g = clamp(result.g);
    result.b = clamp(result.b);
    //  get result of phong illumination
    return result;

  }
}
//////FINDME3
//  check for each ray/object intersection, keep track of closest intersection point
ColorType Trace_Ray(RayType ray, int depth) {
  //  check for each ray/object intersection (only spheres here)
  //  keep track of closest intersection point
  //  (want to only color closest intersection point)
  bool sphere_intersect = false;
  int si_index;
  float tmin = -1;

  //  ray/sphere intersection for sphere
  for(int i = 0; i < s_index+1; i++) {
    //  check for intersection of object
    float A = 1;
    float B = 2 * (ray.dx * (ray.x-sphere[i].x) + ray.dy * (ray.y-sphere[i].y) + ray.dz * (ray.z - sphere[i].z));
    float C = pow((ray.x - sphere[i].x),2) + pow((ray.y - sphere[i].y),2) + pow((ray.z - sphere[i].z),2) - pow(sphere[i].r,2);
    float t = quadratic(A,B,C);

    //  want smallest positive t
    //  initalize for first intersection
    if (t > 0.0001 && (sphere_intersect == false)) {
      si_index = i;
      sphere_intersect = true;
      tmin = t;

      //printf("inside tmin %f %d\n", tmin, s_index);
    }
    //  check to see if t is smaller than tmin for subsequent checks
    if (t > 0.0001 && (tmin > t)) {
      si_index = i;
      tmin = t;

    }
  }

  bool triangle_intersect = false;
  int ti_index;

  //  ray/plane intersection
  for(int i=1; i< t_index+1; i++)  {
    //  get index of vertices
    int v1 = triangle[i].v1;
    int v2 = triangle[i].v2;
    int v3 = triangle[i].v3;

    VectorType e1 = sub(vertex[v2], vertex[v1]);
    VectorType e2 = sub(vertex[v3], vertex[v1]);
    VectorType n = calcCross(e1 , e2);

    float D = -(n.x*vertex[v1].x) -(n.y*vertex[v1].y) -(n.z*vertex[v1].z);

    //  when denominator is zero means ray is parallel to plane skip
    float denom = (n.x*ray.dx) + (n.y*ray.dy) + (n.z*ray.dz);
    if (denom == 0.0) {
      continue;
    }
    float t = -(n.x*ray.x + n.y*ray.y + n.z*ray.z + D)/denom;
    int id;

    //  check that plane intersect occurs
    //  if tmin is not initialized
    if (t > 0.0001 && (tmin < 0)) {
      id = i;

      // set where ray hits the plane
      rt_int.x = ray.x + t*ray.dx;
      rt_int.y = ray.y + t*ray.dy;
      rt_int.z = ray.z + t*ray.dz;
      //  plane is closer than sphere/ray intersection
    } else if (t > 0 && (tmin > t)) {
      id = i;

      // set where ray hits the plane
      rt_int.x = ray.x + t*ray.dx;
      rt_int.y = ray.y + t*ray.dy;
      rt_int.z = ray.z + t*ray.dz;

    } else {
      //  t invalid
      continue;
    }
    ////////////////////////////////////
    //  check is it inside a triangle

    VectorType e3 = sub(rt_int, vertex[v2]);
    VectorType e4 = sub(rt_int, vertex[v3]);

    //  total area of triangle
    float t_area = 0.5 * calcLength(n);
    if (t_area == 0) {
      printf("zero error %f", t_area);
    }
    //  triangle portion a
    VectorType a = calcCross(e3, e4);
    float a_area = 0.5 * calcLength(a);

    //  triangle portion b
    VectorType b = calcCross(e4, e2);
    float b_area = 0.5 * calcLength(b);

    //  triangle portion c
    VectorType c= calcCross(e1,e3);
    float c_area = 0.5 * calcLength(c);

    //  area of parts to whole, barycentric coordinates
    float Alpha = a_area/t_area;
    float Beta = b_area/t_area;
    float Zeta = c_area/t_area;

    //printf("original %f %f %f\n", Alpha, Beta, Zeta);
    //  see if triangle portion is greater than 1
    //  points outside the triangle
    if (Alpha > 1 || Alpha < 0|| Beta >1 || Beta < 0 || Zeta < 0 || Zeta > 1 || !(Alpha + Beta + Zeta < 1.00001 && Alpha + Beta + Zeta > .99999)) {
      //POINT IS OUTSIDE TRIANGLE
      //skip
      continue;
    }
    //  point is inside the triangle
    tmin = t;
    r_Alpha = Alpha;
    r_Beta = Beta;
    r_Zeta = Zeta;
    triangle_intersect = true;
    sphere_intersect = false;
    ti_index = i;

  }


  //  ray/triangle intersection point
  if (tmin > 0.0001 && triangle_intersect){
    // set where ray hits the triangle
    rt_int.x = ray.x + tmin*ray.dx;
    rt_int.y = ray.y + tmin*ray.dy;
    rt_int.z = ray.z + tmin*ray.dz;
  }

  //  need to check if triangle is closer
  if(tmin > 0.0001 && sphere_intersect){
    //printf("t is %f\n", tmin);
    //if (tmin == 0) {
    //  printf("equal zero\n");
    //}
    // set where ray hits the sphere
    rs_int.x = ray.x + tmin*ray.dx;
    rs_int.y = ray.y + tmin*ray.dy;
    rs_int.z = ray.z + tmin*ray.dz;
  }

  //  return color
  ColorType r_color;

  //  get the color of the closest instersection point of object
  if (sphere_intersect) {
    //  use phong illumination model
    r_color = Shade_Ray(si_index, 0, ray, depth);

  } else if (triangle_intersect) {
    //r_color = Shade_Ray(ti_index, 1);
    r_color = Shade_Ray(ti_index, 1, ray, depth);
  } else {  //  default if no intersection
    r_color.r = bkgcolor.r;
    r_color.g = bkgcolor.g;
    r_color.b = bkgcolor.b;
  }

  return r_color;
}

//  builds array and sets
//  background to bkgcolor
void init_array() {
  //printf("INIT_ARRAY\n");
  //  dynamically size array
  array = (ColorType **)malloc(height * sizeof(ColorType *));

  for (int i = 0 ; i < height ; i++) {
    array[i] = (ColorType *)malloc(width * sizeof (ColorType));
  }

  //  create array of shadows
  shadow = (float *)malloc((l_index+1)*sizeof(float));
  for (int i = 0 ; i < l_index+1; i++) {
    shadow[i] = false;
  }

  //  set image of view
  for (int i = 0 ; i < height ; i++) {
    for (int j = 0; j < width ; j++) {
      //  calculate point of viewing window
      VectorType point;
      point.x = ul.x + (j*h_offset.x)+(i*v_offset.x)+c_horizontal.x+c_vertical.x;
      point.y = ul.y + (j*h_offset.y)+(i*v_offset.y)+c_horizontal.y+c_vertical.y;
      point.z = ul.z + (j*h_offset.z)+(i*v_offset.z)+c_horizontal.z+c_vertical.z;

      //  create ray
      RayType ray;
      VectorType tmp;
      //  origin of ray
      ray.x = eye.x;
      ray.y = eye.y;
      ray.z = eye.z;

      tmp.x = (point.x - eye.x);
      tmp.y = (point.y - eye.y);
      tmp.z = (point.z - eye.z);
      //FINDME2
      //  division by 0
      if  (calcLength(tmp) == 0) {
        printf("division by 0");
        continue;
      }
      //  ray direction
      ray.dx = (point.x - eye.x)/calcLength(tmp);
      ray.dy = (point.y - eye.y)/calcLength(tmp);
      ray.dz = (point.z - eye.z)/calcLength(tmp);
      //  set base index of refraction
      in_ref = 1.0;
      //  set recursion vars
      result2.r = 0;
      result2.g = 0;
      result2.b = 0;
      result3.r = 0;
      result3.g = 0;
      result3.b = 0;
      depth1 = 5;
      depth_max = 5;
      //  get color of pane, define ray and depth
      //  depth of 10 to recurse
      ColorType tempC = Trace_Ray(ray, depth1);

      // color view window
      array[i][j].r = tempC.r;
      array[i][j].g = tempC.g;
      array[i][j].b = tempC.b;
      //printf("going through\n");
    }
  }
}

//  deallocate memory set for array
void deallocate_array(){
  for (int i = 0 ; i < v_height ; i++) {
    free(array[i]);
  }
  free(array);
}

//  create PPM text file
void build_PPM() {
  //  width and height
  //  format (for reference)
  /* P3
  * #comments
  * width height
  * 1
  * r(0,0) g(0,0) b(0,0) etc
  */
  char * comment = "# comments";
  char * max_color = "255";
  char * format = "P3";
  //  store integer values of height and width

  //  create ppm file and open for writing
  FILE *fp;
  fp = fopen ("test.ppm", "wb");

  // strip new lines from width and height
  char l_width[10];
  char l_height[10];

  sprintf(l_width, "%d", width);
  sprintf(l_height, "%d", height);

  //  writing input to ppm file
  //TODO  cleanup formatting later
  fputs(format, fp);
  fputs("\n", fp);
  fputs(comment, fp);
  fputs("\n", fp);
  fputs(l_width, fp);
  fputs(" ",fp);
  fputs(l_height, fp);
  fputs("\n",fp);
  fputs(max_color, fp);
  fputs("\n", fp);
  //  write colors
  int i = 0;
  int j = 0;
  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      char * msgColor;
      //  may need to change how big the f goes to
      asprintf(&msgColor, "%d %d %d ",clamp2((array[i][j].r*255)), clamp2((array[i][j].g*255)), clamp2((array[i][j].b*255)));
      if ( clamp2(array[i][j].r*255) < 0 || clamp2(array[i][j].r*255) > 256) {
        printf("error in clamp 2\n");
        printf("red: %f\n", array[i][j].r);
        exit(0);
      }
      fputs(msgColor, fp);
      fputs("\n", fp);
      free(msgColor);
    }
  }

  fclose(fp);
}
