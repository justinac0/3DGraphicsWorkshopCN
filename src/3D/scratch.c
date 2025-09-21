#include "scratch.h"

#include <stdio.h>
#include <raylib.h>
#include "math.h"

static vec3 cube[8] = {
    (vec3){ 1, -1,  1},
    (vec3){ 1,  1,  1},
    (vec3){ 1, -1, -1},
    (vec3){ 1,  1, -1},
    (vec3){-1, -1,  1},
    (vec3){-1,  1,  1},
    (vec3){-1, -1, -1},
    (vec3){-1,  1, -1},
};

static int indices[24] = {
    0, 1,
    0, 2,
    1, 3,
    2, 3,
    
    4, 5,
    5, 7,
    6, 7,
    4, 6,
    
    0, 4,
    1, 5,
    2, 6,
    3, 7,
};

void draw_primitives(mat4x4 *mp, vec3 *verts, size_t vert_count, int *indices, size_t ind_count) {
    for (int i = 0; i < ind_count; i+=2) {
        int k0 = indices[i];
        int k1 = indices[i+1];

        vec3 first = mat4x4_mul_vec3(*mp, verts[k0]);
        vec3 next = mat4x4_mul_vec3(*mp, verts[k1]);

        first = screen_to_world_space(first);
        next =  screen_to_world_space(next);

        DrawLine(first.x, first.y, next.x, next.y, RED);        
    }
}

static mat4x4 model;
static mat4x4 perspective;
static mat4x4 MP;

void setup(void) {
    model = mat4x4_identity();
    perspective = mat4x4_perspective();
}

void update(void) {
    model = mat4x4_translate((vec3){0, 0, -3});
    MP = mat4x4_mul(perspective, model);
}

void draw(void) {
    draw_primitives(&MP, cube, 8, indices, 24);
}
