#pragma once

#include <string>
#include <cmath>

#include "Vector2D.h"

struct Dot {
    Dot(int X = 0, int Y = 0) {
        this->X = X;
        this->Y = Y;
    }
    int X;
    int Y;
};

struct Color {
    int R;
    int G;
    int B;
};


inline double rad_to_deg(double radians) {
    return radians * (180.0 / M_PI);
}

class Renderer {
public:
    int WinWidth = 1000;
    int WinHeight = 1000;
    float Zoom = 1.0;
    Dot Offset = {0, 0};

    virtual bool init() = 0;

    virtual void clear() = 0;
    virtual void update() = 0;

    virtual void setColor(Color C, int Alpha = 255) = 0;

    // Fixed
    virtual void drawLine(Vector2D Start, Vector2D End) = 0;
    virtual void drawRect(Vector2D Pos, int Width, int Height) = 0;
    virtual void drawCircle(Vector2D Center, int Radius) = 0;
    virtual void drawPie(Vector2D Center, int Radius, int Start, int End) = 0;
    virtual void drawText(std::string Text, Vector2D Pos, Color Background = {0, 0, 0}) = 0;

    // Relative
    virtual void drawLineRel(Vector2D Start, Vector2D End) = 0;
    virtual void drawRectRel(Vector2D Pos, int Width, int Height) = 0;
    virtual void drawCircleRel(Vector2D Center, int Radius) = 0;
    virtual void drawPieRel(Vector2D Center, int Radius, int Start, int End) = 0;
    virtual void drawTextRel(std::string Text, Vector2D Pos, Color Background = {0, 0, 0}) = 0;

    // Relative functions
    inline int rel(int Val) { return int(Val * Zoom); }
    inline int relX(int Val) { return int((Val - Offset.X) * Zoom); }
    inline int relY(int Val) { return int((Val - Offset.Y) * Zoom); }

    // Inverse relative functions
    inline int iRel(int Val) { return int(Val / Zoom); }
    inline int iRelX(int Val) { return int((Val / Zoom) + Offset.X); }
    inline int iRelY(int Val) { return int((Val / Zoom) + Offset.Y); }
};

