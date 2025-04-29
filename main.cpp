#include "raylib.h"
#include <iostream>

using namespace std;

int main() {


    InitWindow(300, 300, "BrickBreaker");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(DARKGREEN);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}