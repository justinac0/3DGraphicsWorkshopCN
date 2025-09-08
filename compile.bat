mkdir bin
gcc src\1D\*.c -o bin\1D -lraylib -lm -lwinmm -lgdi32
gcc src\2D\*.c -o bin\2D -lraylib -lm -lwinmm -lgdi32
gcc src\3D\*.c -o bin\3D -lraylib -lm -lwinmm -lgdi32
