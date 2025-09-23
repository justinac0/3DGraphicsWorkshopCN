#include "scratch.h"

#include <assert.h>
#include <math.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mesh.h"
#include "math.h"

typedef struct {
  vec3 position;
  double yaw;
  double pitch;
} camera;

static mat4x4 view;
static mat4x4 perspective;
static mat4x4 orthographic;
static mat4x4 MVP;

static mat4x4 model0;
static mesh geometry0;
static mat4x4 model1;
static mesh geometry1;
static camera cam;

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
  model0 = mat4x4_mul(model0, rot);
  model0 = mat4x4_mul(model0, scale);
}

void setup(void) {
  geometry0 = load_wavefront("models/isosphere.obj");
  geometry1 = load_wavefront("models/text.obj");

  model0 = mat4x4_identity();
  model1 = mat4x4_translate((vec3){0, -8, 0});

  perspective = mat4x4_perspective(100, 0.001, 70, 1);
  orthographic = mat4x4_orthographic(100, 0.001, 10, -10, 10, -10);
}

void update(void) {}

void draw(void) {
  model0 = mat4x4_translate(vec3_set(0, 0, -1));
  manual_rotate_model();

  mesh_draw(&geometry0, mat4x4_mul(perspective, model0), GRAY);
  mesh_draw(&geometry1, mat4x4_mul(orthographic, model1), GREEN);
}

void cleanup(void) { mesh_free(&geometry0); }
