#ifndef ENDING_H
#define ENDING_H

#include "raylib.h"
#include "Player.h"

extern int currentScreen;
extern int playerSelected;

class EndingScreen
{

private:
    Font customFont{LoadFont("resources/fonts/playpenSans.ttf")};

    Music backgroundMusic{LoadMusicStream("resources/sounds/end.wav")};

    Texture2D backgroundBorder{LoadTexture("resources/textures/background/border.png")};
    Texture2D background{LoadTexture("resources/textures/background/menu.png")};

    Texture2D frogTexture{LoadTexture("resources/textures/characters/frog.png")};
    Texture2D blueGuyTexture{LoadTexture("resources/textures/characters/blue_guy.png")};
    Texture2D pinkGuyTexture{LoadTexture("resources/textures/characters/pink_guy.png")};

    Player player;

public:
    EndingScreen();
    void Init();
    void Render(Player &player);
    void Unload();
};

#endif