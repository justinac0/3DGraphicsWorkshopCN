#include <stdio.h>
#include <raylib.h>
#include <math.h>

// 1 meter = ~250px
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

vec3 vec3_unit(vec3 a) {
    double length = sqrtf(a.x*a.x+a.y*a.y+a.z*a.z);
    return (vec3){
        .x = a.x/length,
        .y = a.y/length,
        .z = a.z/length,
    };
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

    for (int j = 0; j < 4; j++) {
        for (int k = 0; k < 4; k++) {
            double sum = 0;
            for (int q = 0; q < 4; q++) {
                sum += a.mm[j][q] * b.mm[q][k];
            }
            result.mm[j][k] = sum;
        }
    }

    return result;
}

vec3 mat4x4_mul_vec3(mat4x4 a, vec3 v) {
    vec3 result = {0, 0, 0};

    result.x = a.m00 * v.x + a.m10 * v.y + a.m20 * v.y + a.m30;
    result.y = a.m01 * v.x + a.m11 * v.y + a.m21 * v.y + a.m31;
    result.z = a.m02 * v.x + a.m12 * v.y + a.m22 * v.y + a.m32;
    double w = a.m03 * v.x + a.m13 * v.y + a.m23 * v.y + a.m33;

    if (w != 0) {
        result.x /= w;
        result.y /= w;
        result.z /= w;
    }

    return result;
}

void mat4x4_print(mat4x4 a) {
    printf("Matrix:\n");
    printf("%f, %f, %f, %f\n", a.m00, a.m01, a.m02, a.m03);
    printf("%f, %f, %f, %f\n", a.m10, a.m11, a.m12, a.m13);
    printf("%f, %f, %f, %f\n", a.m20, a.m21, a.m22, a.m23);
    printf("%f, %f, %f, %f\n\n", a.m30, a.m31, a.m32, a.m33);
}

vec3 screen_to_world_space(vec3 position) {
    vec3 screenOffset = (vec3){
        .x = (double)(GetScreenWidth()/2.0),
        .y = (double)(GetScreenHeight()/2.0),
    };

    return vec3_add(vec3_scalar(position, METER), screenOffset);
}

void vec3_set(vec3 *v, double x, double y, double z) {
    if (!v) return;

    v->x = x;
    v->y = y;
    v->z = z;
}

int main(void) {
    InitWindow(1280, 720, "3D Graphics");
    
    mat4x4 model = {
        (vec4){1, 0, 0, 0},
        (vec4){0, 1, 0, 0},
        (vec4){0, 0, 1, 0},
        (vec4){0, 0, 0, 1},
    };
    mat4x4 projection = {
        (vec4){1, 0, 0, 0},
        (vec4){0, 1, 0, 0},
        (vec4){0, 0, 1, 0},
        (vec4){0, 0, 1, 1},
    };

    vec3 square[4] = {
        (vec3){ -1.0, 1.0, 0.0 },
        (vec3){  1.0, 1.0, 0.0 },
        (vec3){  1.0,-1.0, 0.0 },
        (vec3){ -1.0,-1.0, 0.0 },
    };

    mat4x4 MP;

    vec3 position = {};

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        for (int i = 0; i < 4; i++) {
            model.m33 = sinf(GetTime());

            MP = mat4x4_mul(model, projection);


            vec3 first = mat4x4_mul_vec3(MP, square[i]);
            vec3 next = mat4x4_mul_vec3(MP, square[(i+1)%4]);

            first = screen_to_world_space(first);
            next =  screen_to_world_space(next);

            DrawLine(first.x, first.y, next.x, next.y, RED);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}