#pragma once
#include <iostream>
#include <utility>
#include <vector>
class Mouse
{
public:
    static double xPos;
    static double yPos;
    static float lastX;
    static float lastY;
    static bool first;
    static bool enabled;
    static std::pair<float ,float > GetMouseXY()
    {
        // std::cout<<"X: "<<xPos<<" Y: "<<yPos<<"\n";

        return {xPos,yPos};
    };
};
