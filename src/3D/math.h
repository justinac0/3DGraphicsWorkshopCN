#ifndef MATH_H
#define MATH_H


#include <stdbool.h>
#include <math.h>

#define UNIT (150)

typedef struct vec2i {
  int x;
  int y;
} vec2i;

typedef struct vec3 {
  double x, y, z;
} vec3;

vec3 vec3_set(double x, double y, double z) {
    return (vec3){
        x, y, z
    };
}

vec3 vec3_add(vec3 a, vec3 b) {
  return (vec3){
      .x = a.x + b.x,
      .y = a.y + b.y,
      .z = a.z + b.z,
  };
}

vec3 vec3_sub(vec3 a, vec3 b) {
  return (vec3){
      .x = a.x - b.x,
      .y = a.y - b.y,
      .z = a.z - b.z,
  };
}

vec3 vec3_scalar(vec3 a, double s) {
  return (vec3){
      .x = a.x * s,
      .y = a.y * s,
      .z = a.z * s,
  };
}

double vec3_dot(vec3 a, vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

double vec3_mag(vec3 a) {
  return sqrtf(a.x*a.x + a.y*a.y + a.z*a.z);
}

vec3 vec3_norm(vec3 a) {
    double mag = vec3_mag(a);
    return (mag > 1e-8) ? (vec3){a.x/mag, a.y/mag, a.z/mag} : a;
}

vec3 vec3_cross(vec3 a, vec3 b) {
  return (vec3){
      .x = a.y * b.z - a.z * b.y,
      .y = a.z * b.x - a.x * b.z,
      .z = a.y * b.y - a.y * b.x,
  };
}

vec3 screen_to_world_space(vec3 position) {
  vec3 screenOffset = (vec3){
      .x = (double)(GetScreenWidth() / 2.0),
      .y = (double)(GetScreenHeight() / 2.0),
  };

  return vec3_add(vec3_scalar(position, UNIT), screenOffset);
}

typedef struct vec4 {
  double x, y, z, w;
} vec4;

typedef union mat4x4 {
  vec4 v[4];
  double mn[4][4];
  struct {
    double m00, m01, m02, m03;
    double m10, m11, m12, m13;
    double m20, m21, m22, m23;
    double m30, m31, m32, m33;
  };
} mat4x4;

mat4x4 mat4x4_fill(double v) {
    return (mat4x4){
        v, v, v, v,
        v, v, v, v,
        v, v, v, v,
        v, v, v, v,
    };
}

mat4x4 mat4x4_identity(void) {
    return (mat4x4){
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1,
    };
}

mat4x4 mat4x4_translate(vec3 pos) {
    mat4x4 m = mat4x4_identity();
    m.m03 = pos.x;
    m.m13 = pos.y;
    m.m23 = pos.z;

    return m;
}


mat4x4 mat4x4_rotate(double theta) {
    mat4x4 m = (mat4x4){
        cosf(theta), -sinf(theta), 0, 0,
        sinf(theta), cosf(theta), 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };

    return m;
}

vec3 mat4x4_mul_vec3(mat4x4 m, vec3 v) {
    vec3 result;
    result.x = (m.m00 * v.x) + (m.m01 * v.y) + (m.m02 * v.z) + (m.m03);
    result.y = (m.m10 * v.x) + (m.m11 * v.y) + (m.m12 * v.z) + (m.m13);
    result.z = (m.m20 * v.x) + (m.m21 * v.y) + (m.m22 * v.z) + (m.m23);
    double w = (m.m30 * v.x) + (m.m31 * v.y) + (m.m32 * v.z) + (m.m33);

    if (w != 0) {
        result.x /= w;
        result.y /= w;
        result.z /= w;
    }

    return result;
}

mat4x4 mat4x4_mul(mat4x4 a, mat4x4 b) {
    mat4x4 m;
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            m.mn[row][col] = 0;
            for (int k = 0; k < 4; k++) {
                m.mn[row][col] += a.mn[row][k] * b.mn[k][col];
            }
        }
    }

    return m;
}

mat4x4 mat4x4_perspective(void) {
    mat4x4 m = (mat4x4){
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 1,
        0, 0, 1, 0
    };

    return m;
}

#endif // MATH_H
