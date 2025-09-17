#include "scratch.h"

#include <assert.h>
#include <math.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mesh.h"
#include "math.h"

static mat4x4 model;
static mat4x4 view;
static mat4x4 perspective;
static mat4x4 MVP;

static mesh geometry;

typedef struct {
    vec3 position;
    vec3 forward;
    vec3 up;
    double yaw;
    double pitch;
} camera;

static camera cam;

void setup(void) {
  cam.position = vec3_set(0, 0, 0);
  cam.up       = vec3_set(0, 1, 0);

  geometry = load_wavefront("models/house.obj");

  model = mat4x4_identity();
  view = mat4x4_identity();
  perspective = mat4x4_perspective(100, 0.001, 70, 4/3);
}

static double wheel = 1;
void manual_rotate_model(void) {
  double speed = 0.1;
  double sens = 0.01;

  cam.position.x += -(IsKeyDown(KEY_D) - IsKeyDown(KEY_A)) * speed;
  cam.position.z += (IsKeyDown(KEY_W) - IsKeyDown(KEY_S)) * speed;
  cam.position.y += -(IsKeyDown(KEY_SPACE) - IsKeyDown(KEY_LEFT_SHIFT)) * speed;

  Vector2 delta = GetMouseDelta();
  SetMousePosition(GetScreenWidth()/2, GetScreenHeight()/2);
  cam.yaw   -= delta.x * sens;
  cam.pitch += delta.y * sens;

  mat4x4 roty = mat4x4_rotate_y(cam.yaw);
  mat4x4 rotx = mat4x4_rotate_x(cam.pitch);
  mat4x4 rot = mat4x4_mul(rotx, roty);

  wheel += GetMouseWheelMove()/5.0;
  if (wheel > 4.0f) wheel = 4.0;
  if (wheel < 0.2) wheel = 0.2;

  mat4x4 scale = mat4x4_scale(vec3_set(wheel, wheel, wheel));
  model = mat4x4_mul(model, rot);
  model = mat4x4_mul(model, scale);
}

void update(void) {}

void draw(void) {
  mat4x4 translate = mat4x4_translate(vec3_set(0, 0, -5));
  
  model = mat4x4_mul(mat4x4_identity(), translate);
  manual_rotate_model();
  
  MVP = mat4x4_mul(perspective, view);
  MVP = mat4x4_mul(MVP, model);
  mesh_draw(&geometry, &MVP);
}

void cleanup(void) { mesh_free(&geometry); }
