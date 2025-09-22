#ifndef MATH_H
#define MATH_H 1

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

vec3 screen_to_world_space(vec3 position) {
  vec3 worldPos = (vec3){
      .x = (position.x * (GetScreenWidth()/2)) + (GetScreenWidth()/2),
      .y = (position.y * (GetScreenHeight()/2)) + (GetScreenHeight()/2),
  };

  return worldPos;
}

typedef struct vec4 {
  double x, y, z, w;
} vec4;

typedef union mat4x4 {
  vec4 v[4];
  double rc[4][4];
  struct {
    double m00, m01, m02, m03;
    double m10, m11, m12, m13;
    double m20, m21, m22, m23;
    double m30, m31, m32, m33;
  };
} mat4x4;

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

mat4x4 mat4x4_scale(vec3 scale) {
    mat4x4 m = mat4x4_identity();
    m.m00 = scale.x;
    m.m11 = scale.y;
    m.m22 = scale.z;

    return m;
}

mat4x4 mat4x4_rotate_x(double theta) {
    mat4x4 m = mat4x4_identity();
    m.m11 = cosf(theta);
    m.m12 = -sinf(theta);
    m.m21 = sinf(theta);
    m.m22 = cosf(theta);

    return m;
}

mat4x4 mat4x4_rotate_y(double theta) {
    mat4x4 m = mat4x4_identity();
    m.m00 = cosf(theta);
    m.m02 = sinf(theta);
    m.m20 = -sinf(theta);
    m.m22 = cosf(theta);

    return m;
}

mat4x4 mat4x4_rotate_z(double theta) {
    mat4x4 m = mat4x4_identity();
    m.m00 = cosf(theta);
    m.m01 = -sinf(theta);
    m.m10 = sinf(theta);
    m.m11 = cosf(theta);

    return m;
}

vec4 mat4x4_mul_vec4(mat4x4 m, vec4 v) {
    vec4 result;
    result.x = (m.m00 * v.x) + (m.m01 * v.y) + (m.m02 * v.z) + (m.m03 * v.w);
    result.y = (m.m10 * v.x) + (m.m11 * v.y) + (m.m12 * v.z) + (m.m13 * v.w);
    result.z = (m.m20 * v.x) + (m.m21 * v.y) + (m.m22 * v.z) + (m.m23 * v.w);
    result.w = (m.m30 * v.x) + (m.m31 * v.y) + (m.m32 * v.z) + (m.m33 * v.w);

    return result;
}

mat4x4 mat4x4_mul(mat4x4 a, mat4x4 b) {
    mat4x4 m;
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            m.rc[row][col] = 0;
            for (int k = 0; k < 4; k++) {
                m.rc[row][col] += a.rc[row][k] * b.rc[k][col];
            }
        }
    }

    return m;
}

mat4x4 mat4x4_perspective(double zfar, double znear, double fovdeg, double aspect) {
    fovdeg *= (PI/180);
    mat4x4 m = mat4x4_identity();
    double f = 1/tanf(fovdeg * 0.5);

    m.m00 = f/aspect;
    m.m11 = f;

    m.m22 = -(zfar + znear) / (znear - zfar);
    m.m23 = -(2.0 * zfar * znear) / (znear - zfar);
    m.m32 = -1.0;

    return m;
}

#endif // MATH_H
