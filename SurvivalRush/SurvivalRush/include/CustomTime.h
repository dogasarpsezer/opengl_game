#pragma once
#include <chrono>

class CustomTime
{
public:
    static CustomTime& Instance();
    void Init(std::chrono::steady_clock::time_point startFrame);
    float Update();

    float deltaTime;

private:
    CustomTime() = default;                    // private constructor
    CustomTime(const CustomTime&) = delete;         // no copying
    CustomTime& operator=(const CustomTime&) = delete;
    std::chrono::steady_clock::time_point lastFrame;
};
