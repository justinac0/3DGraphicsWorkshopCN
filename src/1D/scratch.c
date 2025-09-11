#include "scratch.h"

#include <raylib.h>

#include <math.h>

#define UNIT (250)

double unit_scale(double x) {
    return x * UNIT;
}

double screen_to_world_space(double position) {
    return unit_scale(position) + ((double)GetScreenWidth()/2);
}

static double x;
static double world_x;

void setup(void) {
    x = 0;
    world_x = 0;
}

void update(void) {
    x = sinf(GetTime());
    world_x = screen_to_world_space(x);
}

void draw(void) {
    DrawCircle(world_x, GetScreenHeight()/2, 25, RED);
}
