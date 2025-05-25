#pragma once
#include <vector>
#include "SimpleCharacter.h"

class Debug
{
public:
    static Debug& Instance(); 

    void AddDebug(SimpleCharacter* character);
    void Update();
    void Cleanup();

private:
    Debug() = default;                    // private constructor
    Debug(const Debug&) = delete;         // no copying
    Debug& operator=(const Debug&) = delete;

    std::vector<SimpleCharacter*> debugItems;
};