#include <raylib.h>
#include <iostream>
#include "camera.hpp"

int main()
{
    // init window
    const int screenWidth = 1280;                      // width
    const int screenHeight = 720;                      // height
    InitWindow(screenWidth, screenHeight, "mcdonald"); // init window real
    DisableCursor();                                   // disable cursor
    SetTargetFPS(60);                                  // fps

    // make camera
    SwagCam camera;

    // load the mcdonalds model
    std::string modelPath = "mcdonalds.glb";
    Model mapModel = LoadModel(modelPath.c_str());
    if (mapModel.meshCount == 0)
    { // error handle
        std::cerr << "failed to load model: " << modelPath << std::endl;
        CloseWindow();
        return -1;
    }

    // main loop
    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();
        camera.Update(deltaTime);

        BeginDrawing();     // draw
            ClearBackground(RAYWHITE);
            BeginMode3D(camera.camera);
                DrawModel(mapModel, {0.0f, 0.0f, 0.0f}, 1.0f, WHITE);
            EndMode3D();
        EndDrawing();       // no draw
    }

    // unload and close stuff
    UnloadModel(mapModel);
    CloseWindow();
    return 0;
}
