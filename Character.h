#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"
#include "Consts.h"
#include "Assets.h"

class Character
{
private:
    bool isAlive{true};
    int renderDied = 5; // To render the disappearing texture
    bool isDisappearAfterCollect{true};
    bool isFlipTexture{false}; // To flip texture when walking in opposite direction

public:
    TextureFrames textureWithFramesNumber;
    Vector2 position;

    // Used to change frames within texture
    Rectangle frameRec;
    int currentFrame;
    int framesCounter;

    TextureFrames killTextureFrames;

    // Constructors
    Character();
    Character(TextureFrames txtr, Vector2 pos, Texture2D disappearChar);
    Character(TextureFrames txtr, Vector2 pos, TextureFrames killTexture);

    // Getters and Setters
    bool GetIsAlive() { return isAlive; }
    void SetIsAlive(bool isCharAlive) { isAlive = isCharAlive; }
    void SetIsDisappearAfterCollect(bool disappear) { isDisappearAfterCollect = disappear; }
    Rectangle GetPositionRec() const;
    void SetTexture(Texture2D txtr) { textureWithFramesNumber.texture = txtr; }
    void SetFlipTexture(bool value) { isFlipTexture = value; }
    void SetNumFrames(int value) { textureWithFramesNumber.frames = value; }
    void SetTextureFrames(TextureFrames value) { textureWithFramesNumber = value; }

    void Render();
    void Restart();
    void Move(Vector2 offset);
};

#endif