#include <raylib.h>
#include <string.h>
#include "scratch.h"

int main(void) {
    InitWindow(1280, 720, "3D Graphics Workshop");

    setup();

    // ref: https://www.gafferongames.com/post/fix_your_timestep/
    double t = 0.0;
    const double dt = 0.01;
    
    double currentTime = GetTime();
    double accumulator = 0.0;

    Camera2D camera;
    memset(&camera, 0, sizeof(Camera2D)); 
    camera.zoom = 1.0;

    while (!WindowShouldClose()) {
        camera.offset.x = GetScreenWidth()/2;
        camera.offset.y = GetScreenHeight()/2;

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
        BeginMode2D(camera);
        ClearBackground(BLACK);
        
        draw();
        EndMode2D();
        EndDrawing();
        
    }

    CloseWindow();
    return 0;
}
