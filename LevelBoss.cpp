#include "LevelBoss.h"

LevelBoss::LevelBoss() {}

void LevelBoss::Init()
{
    // Background Music
    PlayMusicStream(backgroundMusic);

    // Initialize items that needs to be restarted if new game is started
    pigBoss = Enemy(pigBossTexture, 12, {700.0f, 375.0f}, disappearTexture, true);
    pig1 = Enemy(pigTexture, 16, {650.0f, 400.0f}, disappearTexture, true);
    pig2 = Enemy(pigTexture, 16, {450.0f, 400.0f}, disappearTexture, true);
    pig3 = Enemy(pigTexture, 16, {550.0f, 400.0f}, disappearTexture, true);

    bomb = Item(bombOffTexture, 1, {50.0f, 250.0f}, bombExplodingTexture);

    // Initilize boss health
    bossHealth = 10;
}

void LevelBoss::RenderBackground()
{
    DrawTexture(backgroundTextures.levelBoss, 0, 0, WHITE);
    DrawTexture(backgroundTextures.border, 0, 0, WHITE);
}

void LevelBoss::RenderItems()
{
    DrawText(TextFormat("Boss: %d %", bossHealth * 10), 650, 20, 20, BLACK);
    //----------------------------------------------------------------------------------
    // Render Elements
    //----------------------------------------------------------------------------------
    // Render status bar without flags and with instructions for boss level
    status.Render(-1);

    bomb.RenderBomb();
    pigBoss.Render();

    for (auto enemy : enemies)
    {
        enemy->Render();
    }

    for (auto platform : platforms)
    {
        platform->Render();
    }
}

void LevelBoss::Update(Player &player)
{
    UpdateMusicStream(backgroundMusic);

    //----------------------------------------------------------------------------------
    // Enemies Move
    //----------------------------------------------------------------------------------
    // Move is different in boss level
    pigBoss.MoveBossLevel(true);
    pig1.MoveBossLevel(false);
    pig2.MoveBossLevel(false);
    pig3.MoveBossLevel(false);

    //----------------------------------------------------------------------------------
    // Enemies Collisions
    //----------------------------------------------------------------------------------

    // Player can't hit boss
    if (CheckCollisionRecs(player.GetPositionRec(), pigBoss.GetPositionRec()))
    {
        player.Die();
    }

    for (auto enemy : enemies)
    {
        if (enemy->GetIsAlive() && CheckCollisionRecs(player.GetPositionRec(), enemy->GetPositionRec()))
        {
            // Check if colision comes from top
            if (player.GetPositionRec().y < enemy->GetPositionRec().y)
            {
                enemy->Die();
            }
            else
            {
                player.Die();
            }
        }
    }

    //----------------------------------------------------------------------------------
    // Bomb Collision
    //----------------------------------------------------------------------------------
    if (CheckCollisionRecs(player.GetPositionRec(), bomb.GetPositionRec()))
    {
        bomb.Activate(bombOnTexture, 4);
    }

    // Check things around bomb explosion
    if (bomb.GetIsExploding())
    {
        // Bomb can hit enemies up to 3 positions left or right
        Rectangle bombRect = bomb.GetPositionRec();
        bombRect.x -= 3;
        bombRect.width += 3;
        if (CheckCollisionRecs(bombRect, pigBoss.GetPositionRec()))
        {
            bossHealth -= 2;
            PlaySound(hitBossSound);
            bomb.SetIsExploding(false); // To avoid hitting multiple times with same bomb

            // End game
            if (bossHealth == 0)
            {
                pigBoss.Die();
                PlaySound(bossDiedSound);
                StopMusicStream(backgroundMusic);
                isEnd = true;
            }
        }

        // Bomb can kill enemies
        for (auto enemy : enemies)
        {
            if (enemy->GetIsAlive() && CheckCollisionRecs(bombRect, enemy->GetPositionRec()))
            {
                enemy->Die();
            }
        }
    }

    //----------------------------------------------------------------------------------
    // Platform Collisions
    //----------------------------------------------------------------------------------
    bool isOnPlatform = false;
    for (auto platform : platforms)
    {
        if (CheckCollisionRecs(player.GetPositionRec(), platform->GetPositionRec()))
        {
            if (player.GetPositionRec().y < platform->GetPositionRec().y)
            {
                player.SetIsPlayerOnPlatform(true);
                isOnPlatform = true;
                player.position.y = platform->GetPositionRec().y - platform->texture.height - 20;
            }
            // Player can only collide with one platform at the time
            // No need to check other platforms if already collided
            break;
        }
    }

    // If no collisions happened this turn, reset isPlayerOnPlatform
    // so player can fall if walk to outside platform
    if (!isOnPlatform)
    {
        if (player.GetIsPlayerOnPlatform())
        {
            player.SetIsPlayerOnPlatform(false);
        }
    }
}

void LevelBoss::Unload()
{
    UnloadTexture(disappearTexture);
    UnloadTexture(platformTexture);
    UnloadTexture(pigTexture);
    UnloadTexture(bombOffTexture);
    UnloadTexture(bombOnTexture);
    UnloadTexture(bombExplodingTexture);

    UnloadMusicStream(backgroundMusic);
    UnloadSound(hitBossSound);
    UnloadSound(bossDiedSound);
}
