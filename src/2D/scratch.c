#include "scratch.h"

#include <stdio.h>
#include <raylib.h>
#include <math.h>

#define UNIT (250)

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
    vec2 screenOffset = (vec2){
        .x = (double)(GetScreenWidth()/2.0),
        .y = (double)(GetScreenHeight()/2.0),
    };

    return vec2_add(vec2_scalar(position, UNIT), screenOffset);
}

void vec2_set(vec2 *v, double x, double y) {
    if (!v) return;

    v->x = x;
    v->y = y;
}

static vec2 position;
static vec2 world;

void setup(void) {
    position = (vec2){0};
}

void update(void) {
    world = screen_to_world_space(position);
    vec2_set(&position, sinf(GetTime()), cosf(GetTime()));
}

void draw(void) {
    DrawCircle(world.x, world.y, 25, RED);
}
