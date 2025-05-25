#pragma once
#include <chrono>

class CustomTime
{
public:
    CustomTime(std::chrono::steady_clock::time_point start);
    float Update();

    float deltaTime;

private:
    std::chrono::steady_clock::time_point lastFrame;
};
