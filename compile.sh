# !/bin/bash
mkdir -p bin/
gcc src/1D/*.c -o bin/1D  -lraylib -lm 
gcc src/2D/*.c -o bin/2D  -lraylib -lm
gcc src/3D/*.c -o bin/3D -lraylib -lm
gcc src/live/*.c -o bin/live -lraylib -lm