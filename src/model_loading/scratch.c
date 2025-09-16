#include "scratch.h"

#include <stdio.h>
#include <raylib.h>
#include <math.h>

#define UNIT (250)

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

    return vec3_add(vec3_scalar(position, UNIT), screenOffset);
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
                sum +=  a.mm[col][q] * b.mm[q][row];
            }
            result.mm[row][col] = sum;
        }
    }

    return result;
}

mat4x4 mat4x4_translate(vec3 offset) {
    mat4x4 m = {
        (vec4){1, 0, 0, offset.x},
        (vec4){0, 1, 0, offset.y},
        (vec4){0, 0, 1, offset.z},
        (vec4){0, 0, 0, 1},
    };

    return m;
}

vec3 mat4x4_mul_vec3(mat4x4 a, vec3 v) {
    vec3 result = {0, 0, 0};

    result.x = (a.m00 * v.x) + (a.m10 * v.y) + (a.m20 * v.z) + (a.m30);
    result.y = (a.m01 * v.x) + (a.m11 * v.y) + (a.m21 * v.z) + (a.m31);
    result.z = (a.m02 * v.x) + (a.m12 * v.y) + (a.m22 * v.z) + (a.m32);
    double w = (a.m03 * v.x) + (a.m13 * v.y) + (a.m23 * v.z) + (a.m33);

    if (w != 0) {
        result.x /= w;
        result.y /= w;
        result.z /= w;
    }

    return result;
}

void load_obj(const char *filepath) {
    FILE *file = fopen(filepath, "r");
    if (!file) {
        perror("failed to load file");
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
}

const double f = 0.5;
static vec3 cube[8] = {
    (vec3){f, -f,  f},
    (vec3){f,  f,  f},
    (vec3){f, -f, -f},
    (vec3){f,  f, -f},
    // back face
    (vec3){-f, -f, f},
    (vec3){-f,  f, f},
    (vec3){-f, -f,-f},
    (vec3){-f,  f,-f},
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

    perspective = (mat4x4){
        (vec4){1, 0, 0, 0},
        (vec4){0, 1, 0, 0},
        (vec4){0, 0, 0, 0},
        (vec4){0, 0, 0, 0},
    };

    load_obj("models/cube.obj");    
}

void update(void) {
    model = mat4x4_translate((vec3){0,sinf(GetTime()), -2.2});
    MP = mat4x4_mul(perspective, model);
}

void draw(void) {
    for (int i = 0; i < sizeof(lines)/sizeof(*lines); i+=2) {
        int k0 = lines[i];
        int k1 = lines[i+1];

        vec3 first = mat4x4_mul_vec3(MP, cube[k0]);
        vec3 next = mat4x4_mul_vec3(MP, cube[k1]);

        first = screen_to_world_space(first);
        next =  screen_to_world_space(next);

        DrawLine(first.x, first.y, next.x, next.y, RED);        
    }

    for (int i = 0; i < sizeof(cube)/sizeof(*cube); i++) {
        vec3 world = mat4x4_mul_vec3(MP, cube[i]);
        world = screen_to_world_space(world);
        DrawCircle(world.x, world.y, 3, RED);
    }
}
