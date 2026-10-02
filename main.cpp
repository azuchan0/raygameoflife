#include <raylib.h> 
#include <iostream>
#include "simulation.hpp"

using namespace std;

int main()
{
    Color GREY = { 29, 29, 29, 255 };
    const int GRID_WIDTH = 750;
    const int UI_WIDTH = 260;
    const int WINDOW_WIDTH = GRID_WIDTH + UI_WIDTH;
    const int WINDOW_HEIGHT = 750;
    const int CELL_SIZE = 15;
    
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Game Of Life");
    int targetFps = 20;
    SetTargetFPS(targetFps);

    const Rectangle playButton = { GRID_WIDTH + 24.0f, 72.0f, 212.0f, 44.0f };
    const Rectangle resetButton = { GRID_WIDTH + 24.0f, 128.0f, 212.0f, 36.0f };
    const Rectangle patternButton = { GRID_WIDTH + 24.0f, 180.0f, 212.0f, 36.0f };
    const Rectangle fpsSliderTrack = { GRID_WIDTH + 24.0f, 410.0f, 212.0f, 8.0f };
    const Rectangle fpsSliderHitArea = { GRID_WIDTH + 12.0f, 394.0f, 236.0f, 40.0f };
    bool isRunning = false;
    bool isDraggingFpsSlider = false;
    bool isPatternMenuOpen = false;

    const char* patternNames[] = { "Glider", "Blinker", "Toad", "Pulsar", "LWSS", "Gosper Gun" };
    const int patternCount = 6;
    const Rectangle patternMenuItems[] = {
        { GRID_WIDTH + 24.0f, 216.0f, 212.0f, 28.0f },
        { GRID_WIDTH + 24.0f, 244.0f, 212.0f, 28.0f },
        { GRID_WIDTH + 24.0f, 272.0f, 212.0f, 28.0f },
        { GRID_WIDTH + 24.0f, 300.0f, 212.0f, 28.0f },
        { GRID_WIDTH + 24.0f, 328.0f, 212.0f, 28.0f },
        { GRID_WIDTH + 24.0f, 356.0f, 212.0f, 28.0f }
    };

    Simulation sim(GRID_WIDTH, WINDOW_HEIGHT, CELL_SIZE);

    //sim loops
    while (WindowShouldClose() == false)
    {
        //event handling
        const Vector2 mousePosition = GetMousePosition();
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            if (CheckCollisionPointRec(mousePosition, playButton))
            {
                isRunning = !isRunning;
            }
            else if (CheckCollisionPointRec(mousePosition, resetButton))
            {
                sim.Clear();
                isRunning = false;
            }
            else if (CheckCollisionPointRec(mousePosition, patternButton))
            {
                isPatternMenuOpen = !isPatternMenuOpen;
            }
            else if (isPatternMenuOpen)
            {
                bool patternSelected = false;
                for (int i = 0; i < patternCount; i++)
                {
                    if (CheckCollisionPointRec(mousePosition, patternMenuItems[i]))
                    {
                        sim.Clear();
                        if (i == 0) {
                            sim.SetCellValue(10, 10, 1);
                            sim.SetCellValue(11, 11, 1);
                            sim.SetCellValue(12, 9, 1);
                            sim.SetCellValue(12, 10, 1);
                            sim.SetCellValue(12, 11, 1);
                        }
                        else if (i == 1) {
                            sim.SetCellValue(10, 10, 1);
                            sim.SetCellValue(10, 11, 1);
                            sim.SetCellValue(10, 12, 1);
                        }
                        else if (i == 2) {
                            sim.SetCellValue(10, 11, 1);
                            sim.SetCellValue(10, 12, 1);
                            sim.SetCellValue(11, 10, 1);
                            sim.SetCellValue(11, 13, 1);
                        }
                        else if (i == 3) {
                            for (int r = 0; r < 13; r++) {
                                for (int c = 0; c < 13; c++) {
                                    if ((r == 0 || r == 5 || r == 7 || r == 12) && (c == 2 || c == 3 || c == 4 || c == 8 || c == 9 || c == 10))
                                        sim.SetCellValue(5 + r, 5 + c, 1);
                                    else if ((r == 2 || r == 10) && (c == 0 || c == 1 || c == 5 || c == 11 || c == 12))
                                        sim.SetCellValue(5 + r, 5 + c, 1);
                                    else if ((r == 3 || r == 9) && (c == 0 || c == 12))
                                        sim.SetCellValue(5 + r, 5 + c, 1);
                                    else if ((r == 4 || r == 8) && c == 0)
                                        sim.SetCellValue(5 + r, 5 + c, 1);
                                    else if ((r == 6) && (c == 0 || c == 12))
                                        sim.SetCellValue(5 + r, 5 + c, 1);
                                }
                            }
                        }
                        else if (i == 4) {
                            sim.SetCellValue(10, 10, 1);
                            sim.SetCellValue(10, 13, 1);
                            sim.SetCellValue(11, 10, 1);
                            sim.SetCellValue(11, 14, 1);
                            sim.SetCellValue(12, 10, 1);
                            sim.SetCellValue(12, 11, 1);
                            sim.SetCellValue(12, 12, 1);
                            sim.SetCellValue(12, 13, 1);
                        }
                        else if (i == 5) {
                            int gliderGun[][2] = {
                                {0,24},{1,22},{1,24},{2,12},{2,13},{2,20},{2,21},{2,34},{2,35},
                                {3,11},{3,15},{3,20},{3,21},{3,34},{3,35},{4,0},{4,1},{4,10},
                                {4,16},{4,20},{4,21},{5,0},{5,1},{5,10},{5,14},{5,16},{5,17},
                                {5,22},{5,24},{6,10},{6,16},{6,24},{7,11},{7,15},{8,12},{8,13}
                            };
                            for (auto& cell : gliderGun) {
                                sim.SetCellValue(2 + cell[0], 2 + cell[1], 1);
                            }
                        }
                        isPatternMenuOpen = false;
                        patternSelected = true;
                        break;
                    }
                }
                if (!patternSelected)
                {
                    isPatternMenuOpen = false;
                }
            }
            else if (CheckCollisionPointRec(mousePosition, fpsSliderHitArea))
            {
                isDraggingFpsSlider = true;
            }
            else if (!isRunning &&
                mousePosition.x >= 0.0f && mousePosition.x < GRID_WIDTH &&
                mousePosition.y >= 0.0f && mousePosition.y < WINDOW_HEIGHT)
            {
                const int column = static_cast<int>(mousePosition.x) / CELL_SIZE;
                const int row = static_cast<int>(mousePosition.y) / CELL_SIZE;
                sim.ToggleCellValue(row, column);
            }
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            isDraggingFpsSlider = false;
        }

        if (isDraggingFpsSlider && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            float sliderPosition = (mousePosition.x - fpsSliderTrack.x) / fpsSliderTrack.width;
            if (sliderPosition < 0.0f) sliderPosition = 0.0f;
            if (sliderPosition > 1.0f) sliderPosition = 1.0f;

            const int newTargetFps = 1 + static_cast<int>(sliderPosition * 119.0f + 0.5f);
            if (newTargetFps != targetFps)
            {
                targetFps = newTargetFps;
                SetTargetFPS(targetFps);
            }
        }

        //updating
        if (isRunning)
        {
            sim.Update();
        }

        //drawing
        BeginDrawing();
        ClearBackground(GREY);
        sim.Draw();

        DrawRectangleRec(playButton, isRunning ? MAROON : DARKGREEN);
        const char* playButtonLabel = isRunning ? "STOP" : "PLAY";
        const int playButtonLabelWidth = MeasureText(playButtonLabel, 20);
        DrawText(playButtonLabel,
            static_cast<int>(playButton.x + (playButton.width - playButtonLabelWidth) / 2),
            static_cast<int>(playButton.y + 8), 20, RAYWHITE);

        DrawRectangleRec(resetButton, DARKGRAY);
        const int resetLabelWidth = MeasureText("RESET", 18);
        DrawText("RESET",
            static_cast<int>(resetButton.x + (resetButton.width - resetLabelWidth) / 2),
            static_cast<int>(resetButton.y + 9), 18, RAYWHITE);

        DrawRectangleRec(patternButton, isPatternMenuOpen ? LIGHTGRAY : DARKGRAY);
        const char* patternLabel = isPatternMenuOpen ? "Patterns ^" : "Patterns v";
        const int patternLabelWidth = MeasureText(patternLabel, 18);
        DrawText(patternLabel,
            static_cast<int>(patternButton.x + (patternButton.width - patternLabelWidth) / 2),
            static_cast<int>(patternButton.y + 9), 18, RAYWHITE);

        if (isPatternMenuOpen)
        {
            DrawRectangleRec(Rectangle{ patternButton.x, patternButton.y + patternButton.height, patternButton.width, patternCount * 28.0f + 4.0f }, Color{ 60, 60, 60, 255 });
            for (int i = 0; i < patternCount; i++)
            {
                bool isHovered = CheckCollisionPointRec(mousePosition, patternMenuItems[i]);
                DrawRectangleRec(patternMenuItems[i], isHovered ? Color{ 80, 80, 80, 255 } : Color{ 50, 50, 50, 255 });
                DrawText(patternNames[i], static_cast<int>(patternMenuItems[i].x + 10), static_cast<int>(patternMenuItems[i].y + 6), 16, RAYWHITE);
            }
        }

        DrawText(TextFormat("%d FPS", targetFps), GRID_WIDTH + 24, 370, 18, RAYWHITE);
        DrawRectangleRec(fpsSliderTrack, DARKGRAY);
        const float sliderProgress = (targetFps - 1) / 119.0f;
        DrawRectangleRec(
            Rectangle{ fpsSliderTrack.x, fpsSliderTrack.y, fpsSliderTrack.width * sliderProgress, fpsSliderTrack.height },
            SKYBLUE);
        DrawCircle(static_cast<int>(fpsSliderTrack.x + fpsSliderTrack.width * sliderProgress),
            static_cast<int>(fpsSliderTrack.y + fpsSliderTrack.height / 2), 9, RAYWHITE);
        DrawText("1", GRID_WIDTH + 24, 427, 14, LIGHTGRAY);
        DrawText("120", GRID_WIDTH + 212, 427, 14, LIGHTGRAY);

        EndDrawing();
    }
    CloseWindow();
}
