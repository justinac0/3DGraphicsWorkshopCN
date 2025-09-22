#include "scratch.h"

#include "draw.h"
#include "math.h"

vec3 cube[8] = {
    (vec3){ 1, -1,  1},
    (vec3){ 1,  1,  1},
    (vec3){ 1, -1, -1},
    (vec3){ 1,  1, -1},
    (vec3){-1, -1,  1},
    (vec3){-1,  1,  1},
    (vec3){-1, -1, -1},
    (vec3){-1,  1, -1},
};

int indices[24] = {
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

mat4x4 model;
mat4x4 perspective;
mat4x4 MP;

void setup(void) {
    model = mat4x4_identity();
    perspective = mat4x4_perspective(100, 0.001, 70, 1);
}

void update(void) {
    model = mat4x4_translate((vec3){sinf(GetTime()), 0, -15});
    // model = mat4x4_mul(translate, mat4x4_rotate_x(GetTime()));
    MP = mat4x4_mul(perspective, model);
}

void draw(void) {
    draw_shape(MP, cube, 8, indices, 24);
}
