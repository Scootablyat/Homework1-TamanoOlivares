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
const int TIMESTEP = 1/FPS;


struct object{ // @Christian this is what I'm using to store object name and position. -JT
    std::string objectName;
    Vector2 objectPos;
    bool isFound = false;
    Color color;
};

void movement(int up, int down, int right, int left, float speed, Vector2& circle){
    if(IsKeyDown(up)){
        circle.y -= speed*GetFrameTime();
    }
    if(IsKeyDown(down)){
        circle.y += speed*GetFrameTime();
    }
    if(IsKeyDown(right)){
        circle.x += speed*GetFrameTime();
    }
    if(IsKeyDown(left)){
        circle.x -= speed*GetFrameTime();
    }
}

bool IsInSelectionArea(Vector2 point, Vector2 squarePos, float size) {
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
                cameraDriftSpeed = (float) std::stoi(line.erase(0, searchTarget.length()));
            }
        }
    }
}


int main(){
    bool movementEnabled = true;
    float speed = 220;
    int fontSize = 16;
    Vector2 player = {(WINDOW_WIDTH/2) + 100, (WINDOW_HEIGHT/2) + 100};
    float playerSize = 100;
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
    Camera2D camera_view = { 0 };
    float EDGE_X[2], EDGE_Y[2];

    // camera settings
    camera_view.target = player;
    Vector2 defaultOffset = {WINDOW_WIDTH/2, WINDOW_HEIGHT/2};
    camera_view.offset = defaultOffset;
    camera_view.zoom = 1.0f;
    int victoryCounter = 0;
    //////////////////
    InitWindow(800, 600, "Tamano_Olivares - Homework 1");
    parseSettingsFile(imageName, object1, object2, object3, object4, object5, EDGE_X, EDGE_Y, cameraWindowDimensions, cameraDriftSpeed);
    std::cout << "EDGE_X[0] = " << EDGE_X[0] << " AND EDGE_X[1] = " << EDGE_X[1] << std::endl;
    std::cout << "EDGE_Y[0] = " << EDGE_Y[0] << " AND EDGE_Y[1] = " << EDGE_Y[1] << std::endl;
    Image displayedImage = LoadImage("toybox.jpg");
    Texture texture = LoadTextureFromImage(displayedImage);
    std::vector<object> allObjects = {object1, object2, object3, object4, object5};

    while(!WindowShouldClose()){
        victoryCounter = 0;
        if(movementEnabled){
            movement(KEY_W, KEY_S, KEY_D, KEY_A, speed, player);
        }
        if(IsKeyPressed(KEY_ENTER)){
            camera_view.zoom = 1.4f;
            movementEnabled = false;
        }
        if(IsKeyPressed(KEY_TAB)){
            camera_view.zoom = 1.0f;
            movementEnabled = true;
        }
        for (size_t i = 0; i < allObjects.size(); i++){
            if(CheckCollisionPointRec(allObjects[i].objectPos, (Rectangle){player.x, player.y, playerSize, playerSize})){
                allObjects[i].isFound = true;
                allObjects[i].color = GREEN;

                std::cout << allObjects[i].color.r << " " << allObjects[i].color.g << std::endl;
            }
        }

        for (size_t i = 0; i < allObjects.size(); i++){
            if(allObjects[i].isFound == true){
                victoryCounter++;
            }
        }
        
        
        if(!(player.x - defaultOffset.x <= EDGE_X[0] || player.x + defaultOffset.x >= EDGE_X[1])){
            if(player.x <= camera_view.target.x - cameraWindowDimensions.x/2){
                camera_view.target.x = player.x + cameraWindowDimensions.x/2;
            }
            if(player.x + playerSize >= camera_view.target.x + cameraWindowDimensions.x/2){
                camera_view.target.x = player.x + playerSize - cameraWindowDimensions.x/2;
            }
            // camera_view.offset.x = defaultOffset.x;
        }
        if(!(player.y - defaultOffset.y <= EDGE_Y[0] || player.y + defaultOffset.y >= EDGE_Y[1])){
            if(player.y <= camera_view.target.y - cameraWindowDimensions.y/2){
                camera_view.target.y = player.y + cameraWindowDimensions.y/2;
            }
            if(player.y + playerSize >= camera_view.target.y + cameraWindowDimensions.y/2){
                camera_view.target.y = player.y + playerSize - cameraWindowDimensions.y/2;
            }
            // camera_view.offset.y = defaultOffset.y;
        }
        /*
        */
        
        //std::cout << camera_view.target.x << " " << camera_view.target.y<< std::endl;
        /*
        if(player.x - defaultOffset.x <= EDGE_X[0]){
            //camera_view.target.x = camera_view.target.x;
            camera_view.offset.x = camera_view.target.x + abs(EDGE_X[0] - camera_view.target.x) - defaultOffset.x;
        }
        if(player.x + defaultOffset.x >= EDGE_X[1]){
            //camera_view.target.x = camera_view.target.x;
            camera_view.offset.x = camera_view.target.x - abs(EDGE_X[0] - camera_view.target.x) + defaultOffset.x;
            //camera_view.offset.x -= abs(EDGE_X[1] - camera_view.target.x);
        }
        if(player.y - defaultOffset.y <= EDGE_Y[0]){
            //camera_view.target.y = camera_view.target.y;
            camera_view.offset.y = camera_view.target.y + abs(EDGE_Y[0] - camera_view.target.y) - defaultOffset.y;
        }
        if(player.y + defaultOffset.y >= EDGE_Y[1]){
            //camera_view.target.y = camera_view.target.y;
            camera_view.offset.y = camera_view.target.y - abs(EDGE_Y[0] - camera_view.target.y) + defaultOffset.y;
            //camera_view.offset.y -= abs(EDGE_Y[1] - camera_view.target.y);
        }
        if(!(player.x - defaultOffset.x <= EDGE_X[0] || player.x + defaultOffset.x >= EDGE_X[1])){
            camera_view.target.x = player.x;
            // camera_view.offset.x = defaultOffset.x;
        }
        if(!(player.y - defaultOffset.y <= EDGE_Y[0] || player.y + defaultOffset.y >= EDGE_Y[1])){
            camera_view.target.y = player.y;
            // camera_view.offset.y = defaultOffset.y;
        }
        */

        // Draw Step
        BeginDrawing();
        BeginMode2D(camera_view);

        ClearBackground(BLACK);
        DrawTexture(texture, 0, 0, WHITE);
        DrawRectangleLines((camera_view.target.x) - cameraWindowDimensions.x/2 , (camera_view.target.y) - cameraWindowDimensions.y/2, cameraWindowDimensions.x, cameraWindowDimensions.y, RED);
        DrawText(object1.objectName.c_str(), camera_view.target.x - cameraWindowDimensions.x/2 - 200, (camera_view.target.y) - (cameraWindowDimensions.y/2) - 150, fontSize, object1.color);
        DrawText(object2.objectName.c_str(), camera_view.target.x - cameraWindowDimensions.x/2 - 200, (camera_view.target.y) - (cameraWindowDimensions.y/2) - 150 + fontSize+1, fontSize, object2.color);
        DrawText(object3.objectName.c_str(), camera_view.target.x - cameraWindowDimensions.x/2 - 200, (camera_view.target.y) - (cameraWindowDimensions.y/2) - 150 + ((fontSize+1) * 2), fontSize, object3.color);
        DrawText(object4.objectName.c_str(), camera_view.target.x - cameraWindowDimensions.x/2 - 200, (camera_view.target.y) - (cameraWindowDimensions.y/2) - 150 + ((fontSize+1) * 3), fontSize, object4.color);
        DrawText(object5.objectName.c_str(), camera_view.target.x - cameraWindowDimensions.x/2 - 200, (camera_view.target.y) - (cameraWindowDimensions.y/2) - 150 + ((fontSize+1) * 4), fontSize, object5.color);
        DrawRectangle(player.x, player.y, playerSize, playerSize, PINK);
        
        if(victoryCounter == allObjects.size()){
            DrawText("YOU WIN!",(camera_view.target.x) - cameraWindowDimensions.x/2 , (camera_view.target.y) - cameraWindowDimensions.y/2, 40, BLUE);
        }

        EndMode2D();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}