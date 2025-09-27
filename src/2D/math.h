#ifndef MATH_H
#define MATH_H

#include <math.h>
#include <raylib.h>

typedef struct vec2 {
    double x, y;
} vec2;

vec2 vec2_add(vec2 a, vec2 b) {
    return (vec2){
        .x = a.x + b.x,
        .y = a.y + b.y,
    };
}

vec2 vec2_scalar(vec2 a, double s) {
    return (vec2){
        .x = a.x * s,
        .y = a.y * s,
    };
}

vec2 screen_to_world_space(vec2 position) {
    vec2 worldPos = (vec2){
        .x = (position.x * GetScreenWidth()/2),
        .y = (position.y * GetScreenHeight()/2),
    };

    return worldPos;
}

typedef struct vec3 {
  double x, y, z;
} vec3;

typedef union mat3x3 {
  vec3 v[3];
  double mn[3][3];
  struct {
    double m00, m01, m02;
    double m10, m11, m12;
    double m20, m21, m22;
  };
} mat3x3;

vec3 mat3x3_mul_vec3(mat3x3 m, vec3 v) {
    vec3 result;
    result.x = (m.m00 * v.x) + (m.m01 * v.y) + (m.m02 * v.z);
    result.y = (m.m10 * v.x) + (m.m11 * v.y) + (m.m12 * v.z);
    result.z = (m.m20 * v.x) + (m.m21 * v.y) + (m.m22 * v.z);

    return result;
}

mat3x3 mat3x3_identity(void) {
    return (mat3x3){
        1, 0, 0,
        0, 1, 0,
        0, 0, 1
    };
}

#endif // MATH_H
