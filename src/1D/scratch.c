#include "scratch.h"

#include <math.h>
#include <raylib.h>

#define WORLD_UNIT (100)
#define SCREEN_WIDTH (640)
#define SCREEN_HEIGHT (480)

double screen_x_to_world(double x, double unit) {
    return (x * unit) + GetScreenWidth()/2;
}

static double x;

void setup(void) {
    x = 0;
}

void update(void) {
    x = sinf(GetTime());
}

void draw(void) {
    double world_x = screen_x_to_world(x, GetScreenWidth()/2);
    DrawCircle(world_x, GetScreenHeight()/2, 25, GREEN);
}
