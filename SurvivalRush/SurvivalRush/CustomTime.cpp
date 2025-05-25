#include "CustomTime.h"

CustomTime::CustomTime(std::chrono::steady_clock::time_point start)
    : lastFrame(start), deltaTime(0.0f)
{
}

float CustomTime::Update()
{
    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<float> elapsed = now - lastFrame;
    deltaTime = elapsed.count();
    lastFrame = now;
    return deltaTime;
}
