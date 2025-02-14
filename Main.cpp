#include <raylib.h>
#include <raymath.h>
#include <math.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int FPS = 60;
const int TIMESTEP = 1 / FPS;

struct object
{ // @Christian this is what I'm using to store object name and position. -JT
    std::string objectName;
    Vector2 objectPos;
    bool isFound = false;
    Color color = RED;
};

void movement(float edge_x[2], float edge_y[2], float speed, Vector2 &circle, Vector2 &camera, float &circle_size, bool &movement)
{
    if (movement)
    {
        if (IsKeyDown(KEY_W) && (circle.y - circle_size / 2) > edge_y[0])
        {
            circle.y -= speed * GetFrameTime();
        }
        if (IsKeyDown(KEY_S) && (circle.y + circle_size / 2) < edge_y[1])
        {
            circle.y += speed * GetFrameTime();
        }
        if (IsKeyDown(KEY_A) && (circle.x - circle_size / 2) > edge_x[0])
        {
            circle.x -= speed * GetFrameTime();
        }
        if (IsKeyDown(KEY_D) && (circle.x + circle_size / 2) < edge_x[1])
        {
            circle.x += speed * GetFrameTime();
        }
    }
    else
    {
        if (IsKeyDown(KEY_W) && (circle.y - camera.y) >= -(WINDOW_HEIGHT * .4 / 2))
        {
            circle.y -= speed * GetFrameTime();
        }
        if (IsKeyDown(KEY_S) && (circle.y - camera.y) <= (WINDOW_HEIGHT * .4 / 2))
        {
            circle.y += speed * GetFrameTime();
        }
        if (IsKeyDown(KEY_A) && (circle.x - camera.x) >= -(WINDOW_WIDTH * .5 / 2))
        {
            circle.x -= speed * GetFrameTime();
        }
        if (IsKeyDown(KEY_D) && (circle.x - camera.x) <= (WINDOW_WIDTH * .5 / 2))
        {
            circle.x += speed * GetFrameTime();
        }
    }
}

bool IsInSelectionArea(Vector2 point, Vector2 squarePos, float size)
{
    return (point.x >= squarePos.x && point.x <= squarePos.x + size && point.y >= squarePos.y && point.y <= squarePos.y + size);
}

void parseSettingsFile(std::string &imageName, object &object1, object &object2, object &object3, object &object4, object &object5,
                       float (&EDGE_X)[2], float (&EDGE_Y)[2], Vector2 &cameraWindowDimensions, float &cameraDriftSpeed)
{
    std::fstream settings;
    settings.open("Settings.txt", std::ios::in);
    std::string line;
    if (settings.is_open())
    {
        while (std::getline(settings, line))
        {
            // std::cout << line << std::endl;
            std::string searchTarget;
            if (line.find("ImageName = ") == 0)
            {
                searchTarget = "ImageName = ";
                imageName = line.erase(0, searchTarget.length());
            }
            /////////////////////////////////////////////////////////////////////////////////////
            if (line.find("Object1 = ") == 0)
            {
                searchTarget = "Object1 = ";
                object1.objectName = line.erase(0, searchTarget.length());
            }
            if (line.find("Obj1X = ") == 0)
            {
                searchTarget = "Obj1X = ";
                object1.objectPos.x = std::stoi(line.erase(0, searchTarget.length()));
            }
            if (line.find("Obj1Y = ") == 0)
            {
                searchTarget = "Obj1Y = ";
                object1.objectPos.y = std::stoi(line.erase(0, searchTarget.length()));
            }
            /////////////////////////////////////////////////////////////////////////////////////
            if (line.find("Object2 = ") == 0)
            {
                searchTarget = "Object2 = ";
                object2.objectName = line.erase(0, searchTarget.length());
            }
            if (line.find("Obj2X = ") == 0)
            {
                searchTarget = "Obj2X = ";
                object2.objectPos.x = std::stoi(line.erase(0, searchTarget.length()));
            }
            if (line.find("Obj2Y = ") == 0)
            {
                searchTarget = "Obj2Y = ";
                object2.objectPos.y = std::stoi(line.erase(0, searchTarget.length()));
            }
            /////////////////////////////////////////////////////////////////////////////////////
            if (line.find("Object3 = ") == 0)
            {
                searchTarget = "Object3 = ";
                object3.objectName = line.erase(0, searchTarget.length());
            }
            if (line.find("Obj3X = ") == 0)
            {
                searchTarget = "Obj3X = ";
                object3.objectPos.x = std::stoi(line.erase(0, searchTarget.length()));
            }
            if (line.find("Obj3Y = ") == 0)
            {
                searchTarget = "Obj3Y = ";
                object3.objectPos.y = std::stoi(line.erase(0, searchTarget.length()));
            }
            /////////////////////////////////////////////////////////////////////////////////////
            if (line.find("Object4 = ") == 0)
            {
                searchTarget = "Object4 = ";
                object4.objectName = line.erase(0, searchTarget.length());
            }
            if (line.find("Obj4X = ") == 0)
            {
                searchTarget = "Obj4X = ";
                object4.objectPos.x = std::stoi(line.erase(0, searchTarget.length()));
            }
            if (line.find("Obj4Y = ") == 0)
            {
                searchTarget = "Obj4Y = ";
                object4.objectPos.y = std::stoi(line.erase(0, searchTarget.length()));
            }
            /////////////////////////////////////////////////////////////////////////////////////
            if (line.find("Object5 = ") == 0)
            {
                searchTarget = "Object5 = ";
                object5.objectName = line.erase(0, searchTarget.length());
            }
            if (line.find("Obj5X = ") == 0)
            {
                searchTarget = "Obj5X = ";
                object5.objectPos.x = std::stoi(line.erase(0, searchTarget.length()));
            }
            if (line.find("Obj5Y = ") == 0)
            {
                searchTarget = "Obj5Y = ";
                object5.objectPos.y = std::stoi(line.erase(0, searchTarget.length()));
            }
            /////////////////////////////////////////////////////////////////////////////////////
            if (line.find("CameraWindowWidth = ") == 0)
            {
                searchTarget = "CameraWindowWidth = ";
                cameraWindowDimensions.x = std::stoi(line.erase(0, searchTarget.length()));
            }
            if (line.find("CameraWindowHeight = ") == 0)
            {
                searchTarget = "CameraWindowHeight = ";
                cameraWindowDimensions.y = std::stoi(line.erase(0, searchTarget.length()));
            }
            /////////////////////////////////////////////////////////////////////////////////////
            if (line.find("CameraEdgeX0 = ") == 0)
            {
                searchTarget = "CameraEdgeX0 = ";
                EDGE_X[0] = std::stoi(line.erase(0, searchTarget.length()));
            }
            if (line.find("CameraEdgeX1 = ") == 0)
            {
                searchTarget = "CameraEdgeX1 = ";
                EDGE_X[1] = std::stoi(line.erase(0, searchTarget.length()));
            }
            if (line.find("CameraEdgeY0 = ") == 0)
            {
                searchTarget = "CameraEdgeY0 = ";
                EDGE_Y[0] = std::stoi(line.erase(0, searchTarget.length()));
            }
            if (line.find("CameraEdgeY1 = ") == 0)
            {
                searchTarget = "CameraEdgeY1 = ";
                EDGE_Y[1] = std::stoi(line.erase(0, searchTarget.length()));
            }
            if (line.find("CameraDrift = ") == 0)
            {
                searchTarget = "CameraDrift = ";
                cameraDriftSpeed = (float)std::stoi(line.erase(0, searchTarget.length()));
            }
        }
    }
}

int main()
{
    bool movementEnabled = true;
    float speed = 440;
    int fontSize = 24;
    Vector2 player = {(WINDOW_WIDTH / 2) + 500, (WINDOW_HEIGHT / 2) + 500};
    float playerSize = 200;
    Vector2 cameraWindowDimensions;
    float cameraDriftSpeed;
    std::string imageName;
    object object1;
    object object2;
    object object3;
    object object4;
    object object5;

    // camera stuff
    int cam_type;
    Camera2D camera_view = {0};
    float EDGE_X[2], EDGE_Y[2];

    // camera settings
    camera_view.target = player;
    Vector2 defaultOffset = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};
    camera_view.offset = defaultOffset;
    camera_view.zoom = 1.0f;
    int victoryCounter = 0;
    //////////////////
    InitWindow(800, 600, "Tamano_Olivares - Homework 1");
    parseSettingsFile(imageName, object1, object2, object3, object4, object5, EDGE_X, EDGE_Y, cameraWindowDimensions, cameraDriftSpeed);
    std::cout << "EDGE_X[0] = " << EDGE_X[0] << " AND EDGE_X[1] = " << EDGE_X[1] << std::endl;
    std::cout << "EDGE_Y[0] = " << EDGE_Y[0] << " AND EDGE_Y[1] = " << EDGE_Y[1] << std::endl;
    // Image displayedImage = LoadImage("toybox.jpg");
    Image displayedImage = LoadImage(imageName.c_str());
    Texture texture = LoadTextureFromImage(displayedImage);
    std::vector<object> allObjects = {object1, object2, object3, object4, object5};

    while (!WindowShouldClose())
    {
        victoryCounter = 0;
        movement(EDGE_X, EDGE_Y, speed, player, camera_view.target, playerSize, movementEnabled);

        if (IsKeyPressed(KEY_ENTER) && movementEnabled)
        {
            // Sauce: https://www.raylib.com/examples/core/loader.html?name=core_2d_camera_mouse_zoom
            // Vector2 mouseWorldPos = GetScreenToWorld2D(player, camera_view);
            // camera_view.offset = player;
            // camera_view.target = mouseWorldPos;

            camera_view.zoom = 1.4f;
            movementEnabled = false;
        }
        else if (IsKeyPressed(KEY_ENTER) && !movementEnabled)
        {
            for (size_t i = 0; i < allObjects.size(); i++)
            {
                if (CheckCollisionPointRec(allObjects[i].objectPos, (Rectangle){player.x - (playerSize / 2), player.y - (playerSize / 2), playerSize, playerSize}))
                {
                    allObjects[i].isFound = true;
                    allObjects[i].color = GREEN;
                }
            }
        }

        if (IsKeyPressed(KEY_TAB))
        {
            // Vector2 mouseWorldPos = GetScreenToWorld2D(player, camera_view);
            // camera_view.offset = player;
            // camera_view.target = mouseWorldPos;

            camera_view.zoom = 1.0f;
            movementEnabled = true;
        }

        for (size_t i = 0; i < allObjects.size(); i++)
        {
            if (allObjects[i].isFound == true)
            {
                victoryCounter++;
            }
        }

        // Camera-Window & Position-Snapping is enabled when there's no Edge-Snapping
        bool hasNoInput = !(IsKeyDown(KEY_W) || IsKeyDown(KEY_A) || IsKeyDown(KEY_S) || IsKeyDown(KEY_D));
        if (movementEnabled)
        {

            if (camera_view.target.x < (WINDOW_WIDTH / 2)) // If you're in a position to edge-snap
                camera_view.offset.x = defaultOffset.x;
            else
            {
                if (player.x - (playerSize / 2) <= camera_view.target.x - cameraWindowDimensions.x / 2) // Camera Window
                    camera_view.target.x = player.x - (playerSize / 2) + cameraWindowDimensions.x / 2;
                if (std::round(player.x) < std::round(camera_view.target.x) && hasNoInput) // Position Snapping
                    camera_view.target.x -= cameraDriftSpeed * .1;
            }

            if (camera_view.target.x > EDGE_X[1] - (WINDOW_WIDTH / 2))
                camera_view.offset.x = defaultOffset.x;
            else
            {
                if (player.x + (playerSize / 2) >= camera_view.target.x + cameraWindowDimensions.x / 2)
                    camera_view.target.x = player.x + (playerSize / 2) - (cameraWindowDimensions.x / 2);
                if (std::round(player.x) > std::round(camera_view.target.x) && hasNoInput)
                    camera_view.target.x += cameraDriftSpeed * .1;
            }

            if (camera_view.target.y < (WINDOW_HEIGHT / 2))
                camera_view.offset.y = defaultOffset.y;
            else
            {
                if (player.y - (playerSize / 2) <= camera_view.target.y - (cameraWindowDimensions.y / 2))
                    camera_view.target.y = player.y - (playerSize / 2) + cameraWindowDimensions.y / 2;
                if (std::round(player.y) < std::round(camera_view.target.y) && hasNoInput)
                    camera_view.target.y -= cameraDriftSpeed * .05;
            }
            if (camera_view.target.y > EDGE_Y[1] - (WINDOW_HEIGHT / 2))
                camera_view.offset.y = defaultOffset.y;
            else
            {
                if (player.y + (playerSize / 2) >= camera_view.target.y + cameraWindowDimensions.y / 2)
                    camera_view.target.y = player.y + (playerSize / 2) - cameraWindowDimensions.y / 2;
                if (player.y > camera_view.target.y && hasNoInput)
                    camera_view.target.y += cameraDriftSpeed * .05;
            }
        }

        // if (!(camera_view.target.x - (playerSize / 2) - defaultOffset.x <= EDGE_X[0]) && movementEnabled)
        // {
        //     if (player.x - (playerSize / 2) <= camera_view.target.x - cameraWindowDimensions.x / 2)
        //         camera_view.target.x = player.x - (playerSize / 2) + cameraWindowDimensions.x / 2;
        //     if (player.x < camera_view.target.x && hasNoInput)
        //         camera_view.target.x -= cameraDriftSpeed * .05;
        // }
        // if (!(camera_view.target.x + defaultOffset.x >= EDGE_X[1]) && movementEnabled) // < EDGE_X Max
        // {
        //     if (player.x + (playerSize / 2) >= camera_view.target.x + cameraWindowDimensions.x / 2)
        //         camera_view.target.x = player.x + (playerSize / 2) - (cameraWindowDimensions.x / 2);
        //     if (player.x > camera_view.target.x && hasNoInput)
        //         camera_view.target.x += cameraDriftSpeed * .05;
        // }

        // if (!(camera_view.target.y - defaultOffset.y <= EDGE_Y[0]) && movementEnabled) // < EDGE_Y Min
        // {
        //     if (player.y - (playerSize / 2) <= camera_view.target.y - cameraWindowDimensions.y / 2)
        //         camera_view.target.y = player.y - (playerSize / 2) + cameraWindowDimensions.y / 2;
        //     if (player.y < camera_view.target.y && hasNoInput)
        //         camera_view.target.y -= cameraDriftSpeed * .05;
        // }
        // if (!(camera_view.target.y + defaultOffset.y >= EDGE_Y[1]) && movementEnabled) // < EDGE_Y Max
        // {
        //     if (player.y + (playerSize / 2) >= camera_view.target.y + cameraWindowDimensions.y / 2)
        //         camera_view.target.y = player.y + (playerSize / 2) - cameraWindowDimensions.y / 2;
        //     if (player.y > camera_view.target.y && hasNoInput)
        //         camera_view.target.y += cameraDriftSpeed * .05;
        // }

        // Draw Step
        BeginDrawing();
        BeginMode2D(camera_view);

        ClearBackground(BLACK);
        DrawTexture(texture, 0, 0, WHITE);
        // if (movementEnabled)
        //     DrawRectangleLines((camera_view.target.x) - cameraWindowDimensions.x / 2, (camera_view.target.y) - cameraWindowDimensions.y / 2, cameraWindowDimensions.x, cameraWindowDimensions.y, RED);
        DrawRectangleLines(player.x - (playerSize / 2), player.y - (playerSize / 2), playerSize, playerSize, PINK);

        EndMode2D();

        DrawText(object1.objectName.c_str(), 10, 10, fontSize, allObjects[0].color);
        DrawText(object2.objectName.c_str(), 10, 35, fontSize, allObjects[1].color);
        DrawText(object3.objectName.c_str(), 10, 60, fontSize, allObjects[2].color);
        DrawText(object4.objectName.c_str(), 10, 85, fontSize, allObjects[3].color);
        DrawText(object5.objectName.c_str(), 10, 110, fontSize, allObjects[4].color);
        if (victoryCounter == allObjects.size())
        {
            DrawText("YOU WIN!", (WINDOW_WIDTH / 2) - 100, WINDOW_HEIGHT / 2, 40, BLUE);
        }

        EndDrawing();
    }
    CloseWindow();
    return 0;
}