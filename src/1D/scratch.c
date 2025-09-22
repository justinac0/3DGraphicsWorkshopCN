#include "scratch.h"

#include <raylib.h>

#include <math.h>

#define UNIT (100)

double unit_scale(double x) {
    return x * UNIT;
}

double screen_to_world_space(double position) {
    return unit_scale(position) + (GetScreenWidth()/2.0);
}

static double x;

void setup(void) {
    x = 0;
}

void update(void) {
    x = sinf(GetTime());
}

void draw(void) {
    double world_x = screen_to_world_space(x);
    DrawCircle(world_x, GetScreenHeight()/2, 25, RED);
}
