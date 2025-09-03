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

vec3 vec3_unit(vec3 a) {
    double length = sqrtf(a.x*a.x+a.y*a.y+a.z*a.z);
    return (vec3){
        .x = a.x/length,
        .y = a.y/length,
        .z = a.z/length,
    };
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
    InitWindow(1280, 720, "1D Graphics");

    vec3 position = {};

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        vec3 world = screen_to_world_space(position);
        DrawCircle(world.x, world.y, 25, RED);

        vec3_set(&position, sinf(GetTime()), cosf(GetTime()), 0);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}