# !/bin/bash
mkdir -p bin/
gcc src/raylib_example/main.c -o bin/raylib_example  -lraylib -lm
gcc src/1D/scratch.c src/1D/main.c -o bin/1D  -lraylib -lm 
gcc src/2D/scratch.c src/2D/main.c -o bin/2D  -lraylib -lm
gcc src/3D/scratch.c src/3D/main.c -o bin/3D -lraylib -lm
gcc src/model_loading/*.c -o bin/obj -lraylib -lm
