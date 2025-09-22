#include <math.h>
#include <raylib.h>

#define WORLD_UNIT (100)
#define SCREEN_WIDTH (640)
#define SCREEN_HEIGHT (480)

double screen_x_to_world(double x, double unit) {
    return (x * unit) + GetScreenWidth()/2;
}

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "RaylibExample");

    double x = 0;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawCircle(screen_x_to_world(x, GetScreenWidth()/2), GetScreenHeight()/2, 15, GREEN);
        EndDrawing();
    
        x = sinf(GetTime());
    }

    CloseWindow();

    return 0;
}
