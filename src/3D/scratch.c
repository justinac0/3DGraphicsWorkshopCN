#include "scratch.h"

#include <stdio.h>
#include <raylib.h>
#include <math.h>

#define METER (250)

typedef struct vec3 {
    double x, y, z;
} vec3;

vec3 vec3_add(vec3 a, vec3 b) {
    return (vec3){
        .x = a.x + b.x,
        .y = a.y + b.y,
        .z = a.z + b.z,
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
    vec3 screenOffset = (vec3){
        .x = (double)(GetScreenWidth()/2.0),
        .y = (double)(GetScreenHeight()/2.0),
    };

    return vec3_add(vec3_scalar(position, METER), screenOffset);
}

typedef struct vec4 {
    double x, y, z, w;
} vec4;

typedef union mat4x4 {
    vec4 v[4];
    double mm[4][4];
    struct {
        double m00, m01, m02, m03;
        double m10, m11, m12, m13;
        double m20, m21, m22, m23;
        double m30, m31, m32, m33;
    };
} mat4x4;

mat4x4 mat4x4_fill(double v) {
    mat4x4 result = {
        (vec4){v, v, v, v},
        (vec4){v, v, v, v},
        (vec4){v, v, v, v},
        (vec4){v, v, v, v},
    };
}

mat4x4 mat4x4_mul(mat4x4 a, mat4x4 b) {
    mat4x4 result = mat4x4_fill(0);

    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            double sum = 0;
            for (int q = 0; q < 4; q++) {
                sum += a.mm[row][q] * b.mm[q][col];
            }
            result.mm[row][col] = sum;
        }
    }

    return result;
}

// Transformations: Rotation (x, y, z)
mat4x4 mat4x4_rotate_x(double v) {
    mat4x4 m = {
        (vec4){1, 0,       0,        0},
        (vec4){0, cosf(v), -sinf(v), 0},
        (vec4){0, sinf(v), cosf(v),  0},
        (vec4){0, 0,       0,        1},
    };

    return m;
}

mat4x4 mat4x4_rotate_y(double v) {
    mat4x4 m = {
        (vec4){cosf(v),  0, sinf(v),  0},
        (vec4){0,        1, 0,        0},
        (vec4){-sinf(v), 0, cosf(v),  0},
        (vec4){0,        0, 0,        1},
    };
    
    return m;
}

mat4x4 mat4x4_rotate_z(double v) {
    mat4x4 m = {
        (vec4){cosf(v), -sinf(v), 0, 0},
        (vec4){sinf(v),  cos(v),  0, 0},
        (vec4){0,        0,       1, 0},
        (vec4){0,        0,       0, 1},
    };

    return m;
}

vec3 vec3_mul_mat4x4(mat4x4 a, vec3 v) {
    vec3 result = {0, 0, 0};

    result.x = a.m00 * v.x + a.m10 * v.y + a.m20 * v.z + a.m30;
    result.y = a.m01 * v.x + a.m11 * v.y + a.m21 * v.z + a.m31;
    result.z = a.m02 * v.x + a.m12 * v.y + a.m22 * v.z + a.m32;
    double w = a.m03 * v.x + a.m13 * v.y + a.m23 * v.z + a.m33;

    if (w != 0) {
        result.x /= w;
        result.y /= w;
        result.z /= w;
    }

    return result;
}

// Geometric Primitives
const double f = 0.5;
static vec3 cube[8] = {
    // front face
    (vec3){f, -f,  f},     // 0 front: tl
    (vec3){f,  f,  f},      // 1 front: tr
    (vec3){f, -f, -f},    // 2 front: bl
    (vec3){f,  f, -f},     // 3 front: br
    // back face
    (vec3){-f, -f, f},    // 4 back: tl
    (vec3){-f,  f, f},     // 5 back: tr
    (vec3){-f, -f,-f},    // 6 back: bl
    (vec3){-f,  f,-f},     // 7 back: br
};

static int lines[24] = {
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

// Matricies
static mat4x4 model;
static mat4x4 perspective;
static mat4x4 MP;

void setup(void) {
    model = (mat4x4){
        (vec4){1, 0, 0, 0},
        (vec4){0, 1, 0, 0},
        (vec4){0, 0, 1, 0},
        (vec4){0, 0, 0, 1},
    };
    
    // ref https://www.scratchapixel.com/lessons/3d-basic-rendering/perspective-and-orthographic-projection-matrix/building-basic-perspective-projection-matrix.html
    double fov = 90.0;
    double far = 100.0;
    double near = 0.01;
    double s = 1/(tanf((fov/2.0)*(PI/180.0)));
    perspective = (mat4x4){
        (vec4){s, 0, 0, 0},
        (vec4){0, s, 0, 0},
        (vec4){0, 0, -((far/(far-near))), -(far*near)/(far-near)},
        (vec4){0, 0, -1, 1},
    };
}

void update(void) {
    model.m33 = -2.0;

    model = mat4x4_mul(model, mat4x4_rotate_y(0.01));
    model = mat4x4_mul(model, mat4x4_rotate_z(0.01));

    MP = mat4x4_mul(model, perspective);
}

void draw(void) {
    for (int i = 0; i < sizeof(lines)/sizeof(*lines); i+=2) {
        int k0 = lines[i];
        int k1 = lines[i+1];

        vec3 first = vec3_mul_mat4x4(MP, cube[k0]);
        vec3 next = vec3_mul_mat4x4(MP, cube[k1]);

        first = screen_to_world_space(first);
        next =  screen_to_world_space(next);

        DrawLine(first.x, first.y, next.x, next.y, RED);        
    }

    for (int i = 0; i < sizeof(cube)/sizeof(*cube); i++) {
        vec3 world = vec3_mul_mat4x4(MP, cube[i]);
        world = screen_to_world_space(world);
        DrawCircle(world.x, world.y, 5, RED);
    }
}
