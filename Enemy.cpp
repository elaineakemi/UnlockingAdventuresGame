#include "Enemy.h"

Enemy::Enemy(Texture2D txtr, int numFrames, Vector2 pos, Color c, Texture2D disappearChar, bool kill)
    : Character(txtr, numFrames, pos, c, disappearChar), isOnGround(true), canBeKilled(kill), initialPosition(pos)
{
}

void Enemy::Drop()
{
    // Get delta
    float dt = GetFrameTime() * GetFPS();

    if (!isOnGround)
    {
        // Drop enemy with delta * 5 speed
        if (position.y < GetScreenHeight() - 30 - texture.height)
        {
            position.y += dt * 5;
        }
        else
        {
            isOnGround = true;
        }
    }
    else
    {
        // Enemy goes up with 0.5 delta speed
        if (position.y >= initialPosition.y)
        {
            position.y -= dt / 2;
        }
        else
        {
            isOnGround = false;
        }
    }
}

void Enemy::Move()
{
    if (!GetIsAlive())
        return;
    float dt = GetFrameTime() * GetFPS();

    if (position.x > 20)
    {
        position.x -= dt / 2;
    }
    else
    {
        SetIsAlive(false);
    }
}
