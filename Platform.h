#ifndef PLATFORM_H
#define PLATFORM_H

#include "raylib.h"
#include "Scenario.h"

class Platform : public Scenario
{

public:
    Platform(Texture2D txtr, int numFrames, Vector2 pos, Color c);
};

#endif