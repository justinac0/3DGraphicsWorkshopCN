#include "scratch.h"

#include <stddef.h>
#include <raylib.h>
#include "math.h"

static vec2 verts[4] = {
    {-1,  1},
    { 1,  1},
    { 1, -1},
    {-1, -1},
};

static int indices[8] = {
    0, 1,
    1, 2,
    2, 3,
    3, 0
};

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

vec2 mat3x3_mul_vec2(mat3x3 m, vec2 v) {
    vec2 result;
    result.x = (m.m00 * v.x) + (m.m01 * v.y) + (m.m02);
    result.y = (m.m10 * v.x) + (m.m11 * v.y) + (m.m12);

    return result;
}

mat3x3 mat3x3_identity(void) {
    return (mat3x3){
        1, 0, 0,
        0, 1, 0,
        0, 0, 1
    };
}

void draw_primitives(mat3x3 *m, vec2 *verts, size_t vert_count, int *indices, size_t ind_count) {
    for (int i = 0; i < ind_count; i+=2) {
        int k0 = indices[i];
        int k1 = indices[i+1];

        vec2 first = mat3x3_mul_vec2(*m, verts[k0]);
        vec2 next = mat3x3_mul_vec2(*m, verts[k1]);

        first = screen_to_world_space(first);
        next =  screen_to_world_space(next);

        DrawLine(first.x, first.y, next.x, next.y, RED);        
    }
}

mat3x3 model;

void setup(void) {
    model = mat3x3_identity();
}

void update(void) {

}

void draw(void) {
    draw_primitives(&model, verts, 4, indices, 8);
}
