mkdir bin
gcc src\2D\scratch.c src\2D\main.c -o bin\2D  -lraylib -lm -lwinmm -lgdi32
gcc src\3D\scratch.c src\3D\main.c -o bin\3D -lraylib -lm -lwinmm -lgdi32
gcc src\model_loading\*.c -o bin\obj -lraylib -lm -lwinmm -lgdi32
