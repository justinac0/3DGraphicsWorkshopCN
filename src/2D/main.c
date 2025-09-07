#include <raylib.h>
#include "scratch.h"

int main(void) {
    InitWindow(640, 480, "3D Graphics Workshop - The world of 1D");

    setup();

    // ref: https://www.gafferongames.com/post/fix_your_timestep/
    double t = 0.0;
    const double dt = 0.01;
    
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

    CloseWindow();
    return 0;
}
