#include "raylib.h"
#include "Player.h"
#include "Menu.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "LevelBoss.h"

//----------------------------------------------------------------------------------
// Global Variables
//----------------------------------------------------------------------------------
int currentScreen = 0;
int score = 0;
int playerLives = 3;
int playerSelected = 0;
bool isGameOver = false;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Game Name");
    InitAudioDevice();

    Font customFont{LoadFont("resources/fonts/playpenSans.ttf")};

    Player player1(LoadTexture("resources/textures/characters/frog.png"), 11, {15.0f, 400.0f}, RAYWHITE);

    Menu mainMenu;
    mainMenu.Init();
    Level1 lvl1;
    lvl1.Init();
    Level2 lvl2;
    Level3 lvl3;
    LevelBoss lvlBoss;

    SetTargetFPS(60);
    int framesCounter = 0;

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch (currentScreen)
        {
        case 0:
            mainMenu.Render();
            mainMenu.Update();
            break;
        case 1:
            // lvl1.Init();
            lvl1.RenderBackground();
            lvl1.RenderItems();
            player1.Init(playerSelected);
            player1.Render();

            player1.Update();
            lvl1.Update(player1);
            break;
        case 2:
            lvl2.Init();
            lvl2.RenderBackground();
            lvl2.RenderItems();
            player1.Init(playerSelected);
            player1.Render();

            player1.Update();
            lvl2.Update(player1);
            break;
        case 3:
            lvl3.Init();
            lvl3.RenderBackground();
            lvl3.RenderItems();
            player1.Init(playerSelected);
            player1.Render();

            player1.Update();
            lvl3.Update(player1);
            break;
        case 4:
            lvlBoss.Init();
            lvlBoss.RenderBackground();
            lvlBoss.RenderItems();
            player1.Init(playerSelected);
            player1.Render();

            player1.Update();
            lvlBoss.Update(player1);
            break;

        default:
            break;
        }

        if (isGameOver)
        {
            DrawTextEx(customFont, "GAME OVER", (Vector2){170, 150}, 80, 20, RED);
            framesCounter++;

            // Wait 2 seconds then write text
            if (framesCounter > 120)
            {
                DrawTextEx(customFont, "Press ENTER to go back to menu", (Vector2){160, 300}, 40, 2, BLACK);
            }
            if (IsKeyPressed(KEY_ENTER))
            {
                // Restart variables
                score = 0;
                playerLives = 3;
                playerSelected = 0;
                isGameOver = false;
                currentScreen = 0;

                // Restart levels
                mainMenu.Init();
                lvl1.Init();
                player1.SetIsAlive(true);
            }
        }

        //----------------------------------------------------------------------------------
        // End
        //----------------------------------------------------------------------------------
        EndDrawing();
    }

    //----------------------------------------------------------------------------------
    // Unload and Close
    //----------------------------------------------------------------------------------
    mainMenu.Unload();
    lvl1.Unload();
    lvl2.Unload();
    lvl3.Unload();
    lvlBoss.Unload();
    player1.Unload();
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
