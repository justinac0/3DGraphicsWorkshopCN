#include <raylib.h>
#include <math.h>

#define METER (250)

double unit_scale(double x) {
    return x * METER;
}

double screen_to_world_space(double position) {
    return unit_scale(position) + ((double)GetScreenWidth()/2);
}

int main(void) {
    InitWindow(1280, 720, "1D Graphics");

    double x = 0;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        x = sinf(GetTime());

        double world_x = screen_to_world_space(x);
        DrawCircle(world_x, GetScreenHeight()/2, 25, RED);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}