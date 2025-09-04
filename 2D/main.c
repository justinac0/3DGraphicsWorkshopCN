#include <stdio.h>
#include <raylib.h>
#include <math.h>

#define METER (250)

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

vec2 vec2_unit(vec2 a) {
    double length = sqrtf(a.x*a.x+a.y*a.y);
    return (vec2){
        .x = a.x/length,
        .y = a.y/length,
    };
}

vec2 screen_to_world_space(vec2 position) {
    vec2 screenOffset = (vec2){
        .x = (double)(GetScreenWidth()/2.0),
        .y = (double)(GetScreenHeight()/2.0),
    };

    return vec2_add(vec2_scalar(position, METER), screenOffset);
}

void vec2_set(vec2 *v, double x, double y) {
    if (!v) return;

    v->x = x;
    v->y = y;
}

int main(void) {
    InitWindow(1280, 720, "2D Graphics");

    vec2 position = {};

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        vec2 world = screen_to_world_space(position);
        printf("world: %f, %f\n", world.x, world.y);
        vec2 world_unit = vec2_unit(world);
        printf("world_hat: %f, %f\n", world_unit.x, world_unit.y);

        DrawCircle(world.x, world.y, 25, RED);

        vec2_set(&position, sinf(GetTime()), cosf(GetTime()));

        EndDrawing();
    }

    CloseWindow();
    return 0;
}