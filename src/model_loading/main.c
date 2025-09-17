#include <raylib.h>
#include "scratch.h"

int main(void) {
    InitWindow(1280, 720, "3D Graphics Workshop");

    setup();

    // ref: https://www.gafferongames.com/post/fix_your_timestep/
    double t = 0.0;
    const double dt = 0.01;

    HideCursor();
    double currentTime = GetTime();
    double accumulator = 0.0;
    
    while (!WindowShouldClose()) {
        double newTime = GetTime();
        double frameTime = newTime - currentTime;
        currentTime = newTime;

        accumulator += frameTime;

        while (accumulator >= dt) {
            update();
            accumulator -= dt;
            t += dt;
        }

        BeginDrawing();
        ClearBackground(BLACK);
        
        draw();
        
        EndDrawing();
    }

    cleanup();
    CloseWindow();
    return 0;
}
