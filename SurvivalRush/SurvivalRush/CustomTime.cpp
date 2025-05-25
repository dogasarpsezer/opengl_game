#include "CustomTime.h"

CustomTime& CustomTime::Instance()
{
    static CustomTime instance; // only created once
    return instance;
}

void CustomTime::Init(std::chrono::steady_clock::time_point startFrame)
{
    lastFrame = startFrame;
}

float CustomTime::Update()
{
    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<float> elapsed = now - lastFrame;
    deltaTime = elapsed.count();
    lastFrame = now;
    return deltaTime;
}
