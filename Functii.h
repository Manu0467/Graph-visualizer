#ifndef FUNCTII_H
#define FUNCTII_H

#include <graphics.h>
#include <winbgim.h>
#include <iostream>
#include <cstring>
#include <cctype>
#include <math.h>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include "Algoritmi.h"



// Variabile Globale:
enum actionStateEnum{
    noButtonSelected,
    adaugaNodSelected,
    adaugaCostSelected,
    adaugaMuchieSelected,
    stergeGrafSelected,

    // algoritmi
    dfsSelected,
    tarjanSelected,
    bfsSelected,
    dijkstraSelected,
    primSelected,

    // for lastClicks
    nothing,
    clickedPlayground,

    mainMenu,
    grafOrientat,
    grafNeorientat,
};

actionStateEnum actionState = noButtonSelected;
actionStateEnum lastClick = nothing;
actionStateEnum selectedMenu = mainMenu;

//int ScreenSizeX = 500, ScreenSizeY = 500;

int ScreenSizeX = GetSystemMetrics(SM_CXSCREEN), ScreenSizeY = GetSystemMetrics(SM_CYSCREEN);
int ScreenDiagSize = sqrt(ScreenSizeX * ScreenSizeX + ScreenSizeY * ScreenSizeY);
int LAST_CONTOR_NODURI = 0, NOD_SELECTAT = -1, NOD_SELECTAT_ORIENTAT = -1;
float pozitiiNoduri[101][2];
float pi = 3.14159;
// pozitiiNoduri[i][0] = x
// pozitiiNoduri[i][1] = y




// Structs
struct UDimCoord{
    float scale;
    int offset;
};

struct UDim2{
    UDimCoord x, y;

    UDim2() {
        x = {0, 0};
        y = {0, 0};
    }

    UDim2(float scaleX, int offsetX, float scaleY, int offsetY){
        x = {scaleX, offsetX};
        y = {scaleY, offsetY};
    }
};

struct Vector2{
    float x, y;
    Vector2(){
        x = y = 0;
    }

    Vector2(float xSent, float ySent){
        x = xSent;
        y = ySent;
    }
};



// Functii utilitare:
float lerp(float a, float b, float c){
    return a + (b - a) * c;
}

float magnitude(float x = 0, float y = 0){
    return sqrt(x * x + y * y);
}

void openLogFiles(char fisier[52]){
    ShellExecute(NULL, "open", fisier, NULL, NULL, SW_NORMAL);
}

void DrawArrowHeadOnly(int x1, int y1, int x2, int y2)
{
    float dx = float(x2 - x1);
    float dy = float(y2 - y1);

    float len = sqrt(dx*dx + dy*dy);
    if (len == 0) return;

    dx /= len;
    dy /= len;

    float arrowLen = 15.0f;
    float angle = 30.0f * pi / 180.0f;

    dx = -dx;
    dy = -dy;

    float lx = dx * cos(angle)  - dy * sin(angle);
    float ly = dx * sin(angle)  + dy * cos(angle);

    float rx = dx * cos(-angle) - dy * sin(-angle);
    float ry = dx * sin(-angle) + dy * cos(-angle);

    line(x2, y2, int(x2 + lx * arrowLen), int(y2 + ly * arrowLen));
    line(x2, y2, int(x2 + rx * arrowLen), int(y2 + ry * arrowLen));
}

void drawArrow(int x1, int y1, int x2, int y2)
{
    // main line
    line(x1, y1, x2, y2);

    float dx = x2 - x1;
    float dy = y2 - y1;

    float len = sqrt(dx*dx + dy*dy);
    if (len == 0) return;

    dx /= len;
    dy /= len;

    float arrowLen = 15;
    float angle = 30 * pi / 180.0;

    dx = -dx;
    dy = -dy;

    float lx = dx * cos(angle) - dy * sin(angle);
    float ly = dx * sin(angle) + dy * cos(angle);

    float rx = dx * cos(-angle) - dy * sin(-angle);
    float ry = dx * sin(-angle) + dy * cos(-angle);

    line(x2, y2,
         x2 + lx * arrowLen,
         y2 + ly * arrowLen);

    line(x2, y2,
         x2 + rx * arrowLen,
         y2 + ry * arrowLen);
}

char* intToChar(int x) {
    static char c[12];
    int i = 0;

    if (x == 0) {
        c[0] = '0';
        c[1] = '\0';
        return c;
    }

    while (x > 0) {
        c[i++] = (x % 10) + '0';
        x /= 10;
    }

    c[i] = '\0';

    for (int j = 0; j < i / 2; j++) {
        char tmp = c[j];
        c[j] = c[i - j - 1];
        c[i - j - 1] = tmp;
    }

    return c;
}

float distanceFromPointToLine(int xA, int yA, int xB, int yB, int xM, int yM){
    if(xA == xB && yB == yA){
        return magnitude(xM - xA, yM - yA);
    }

    // Perfect verticala dreapta AB.
    if(xA == xB){
        // Verificam daca se afla si la y-ul corect.
        if((yA > yB && (yM > yA || yM < yB)) || (yB > yA && (yM < yA || yM > yB))){
            return 9999;
        }

        return fabs(xA - xM);
    }

    // Verificam daca se afla si la x-ul corect.
    if((xA > xB && (xM > xA || xM < xB)) || (xB > xA && (xM < xA || xM > xB)))
        return 9999;

    float m = (float(yB) - float(yA)) / (float(xB) - float(xA));
    float up = fabs(m * xM - yM + yA - m * xA);
    float down = sqrt(m * m + 1);

    return up / down;
}


bool isMouseOnArrow(
    int ax, int ay,
    int bx, int by,
    int mx, int my,
    float thickness
) {
    float ABx = bx - ax;
    float ABy = by - ay;

    float AMx = mx - ax;
    float AMy = my - ay;

    float abLenSq = ABx * ABx + ABy * ABy;
    if (abLenSq == 0) return false;

    float u = (AMx * ABx + AMy * ABy) / abLenSq;

    if (u < 0) u = 0;
    else if (u > 1) u = 1;

    float px = ax + u * ABx;
    float py = ay + u * ABy;

    float dx = mx - px;
    float dy = my - py;

    float distSq = dx * dx + dy * dy;

    return distSq <= (thickness * thickness) / 4.0f;
}

float scaleToOffset(float scale){
    return scale * ScreenDiagSize;
}

Vector2 GetPerpendicularOffsetPositionFromLine(Vector2 p1, Vector2 p2, float scaleOffset = 0){
    float pixelOffset = scaleToOffset(scaleOffset);

    Vector2 center(
        (p1.x + p2.x) * 0.5f,
        (p1.y + p2.y) * 0.5f
    );

    // Line direction
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;

    float len = sqrt(dx * dx + dy * dy);
    if (len == 0.0f)
        return center;

    // Perpendicular unit vector
    float px = -dy / len;
    float py =  dx / len;

    // Offset from center
    return Vector2(
        center.x + px * pixelOffset,
        center.y + py * pixelOffset
    );
}





#endif
