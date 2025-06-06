#include "raylib.h"
#include "Engine.h"

void Init();
void DeInit();
void UpdateDraw();
void Update();
void Draw();

Engine engine;

float screenHeight = 920;
float screenWidth = 400;

Color backgroundColor = BLACK;

const char* gameName = "BrickBreaker";

int main() {

    Init();
    
    while (!WindowShouldClose()) {
        
        UpdateDraw();
    }

	DeInit();

    return 0;
}

void Init()
{
    InitWindow(screenWidth, screenHeight, gameName);
    SetTargetFPS(60);

    engine.Init({screenWidth, screenHeight});
}

void DeInit()
{
    CloseWindow();
}

void UpdateDraw()
{
    Update();

    BeginDrawing();
    Draw();

    ClearBackground(backgroundColor);
    EndDrawing();
}

void Update()
{
    engine.Update();
}

void Draw()
{
    engine.Draw();
}

