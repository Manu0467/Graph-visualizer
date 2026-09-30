#ifndef CLASE_H
#define CLASE_H
#include <graphics.h>
#include <winbgim.h>
#include <iostream>
#include <cstring>
#include <cctype>
#include <math.h>
#include <cmath>
#include <cstdlib>
#include "Functii.h"

class Frame{
private:

public:
    int topLeftX, topLeftY, bottomRightX, bottomRightY;
    int centerX, centerY;
    UDim2 Position;
    UDim2 Size;
    Vector2 AnchorPoint;
    int Color;
    char imageFile[101];
    char text[101];

    Frame(UDim2 Position, UDim2 Size, Vector2 AnchorPoint, int Color = WHITE, char imageFile[] = "", char text[] = ""){
        // By default, anchor pointul e 0, 0.
        this -> Position = Position;
        this -> Size = Size;
        this -> Color = Color;
        strcpy(this -> text, text);

        strcpy(this -> imageFile, imageFile);

        int scalePositionX = int(lerp(0, ScreenSizeX, Position.x.scale));
        int scalePositionY = int(lerp(0, ScreenSizeY, Position.y.scale));

        int positionInPixelsX = scalePositionX + Position.x.offset;
        int positionInPixelsY = scalePositionY + Position.y.offset;

        int scaleSizeX = int(lerp(0, ScreenSizeX, Size.x.scale));
        int scaleSizeY = int(lerp(0, ScreenSizeY, Size.y.scale));

        int sizeInPixelsX = scaleSizeX + Size.x.offset;
        int sizeInPixelsY = scaleSizeY + Size.y.offset;

        topLeftX = positionInPixelsX - sizeInPixelsX * AnchorPoint.x;
        topLeftY = positionInPixelsY - sizeInPixelsY * AnchorPoint.y;
        bottomRightX = positionInPixelsX + sizeInPixelsX - sizeInPixelsX * AnchorPoint.x;
        bottomRightY = positionInPixelsY + sizeInPixelsY - sizeInPixelsY * AnchorPoint.y;
        centerX = topLeftX + sizeInPixelsX / 2;
        centerY = topLeftY + sizeInPixelsY / 2;
    }

    void Render(){
        if(strcmp(this -> imageFile, "") == 0){
            setfillstyle(SOLID_FILL, Color);
            bar(topLeftX, topLeftY, bottomRightX, bottomRightY);
        }
        else
        {
            readimagefile(this -> imageFile, topLeftX, topLeftY, bottomRightX, bottomRightY);
        }

        if(strcmp(this -> text, "") != 0){
            setcolor(this -> Color);
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 0);
            outtextxy(topLeftX, topLeftY, this -> text);
        }


    }

    void ChangeColor(int Color){
        this -> Color = Color;
        this -> Render();
    }

};


class Nod{

public:
    int centerX, centerY, Color, index, pixelRadius;
    float scaleRadius;
    UDim2 Position;

    Nod(int mouseX, int mouseY, int Color = WHITE, int indexNod = -1){

        if(indexNod != -1){
            pozitiiNoduri[indexNod][0] = mouseX;
            pozitiiNoduri[indexNod][1] = mouseY;
        }

        this -> centerX = mouseX;
        this -> centerY = mouseY;
        this -> Color = Color;
        this -> index = indexNod;

        this -> Position.x.scale = float(mouseX) / float(ScreenSizeX);
        this -> Position.y.scale = float(mouseY) / float(ScreenSizeY);

        // By default, raza ar trebui sa fie cam 0.015 scale (1.5%) din ecran.
        this -> scaleRadius = 0.015;

        /*
        Cum aspect ratioul poate fi diferit de 1x1 (patrat), raza pe pixeli trebuie sa fie calculata
        cu o medie intre screenSizeX si screenSizeY.
        */

        float avgPixelSize = (ScreenSizeX + ScreenSizeY) / 2;
        this -> pixelRadius = this -> scaleRadius * avgPixelSize;
    }

    void Render(){
        setcolor(this -> Color);
        circle(this -> centerX, this -> centerY, this -> pixelRadius);

        // Render text
        float smallXOffset;
        if(index >= 10){
            smallXOffset = 0.0045;
        }
        else
        {
            smallXOffset = 0.0025;
        }

        Frame newText(UDim2(Position.x.scale - smallXOffset, 0, Position.y.scale-0.005, 0), UDim2(0, 0, 0, 0), Vector2(0, 0), WHITE, "", intToChar(index));
        setbkcolor(BLACK);
        newText.Render();
    }
};






#endif