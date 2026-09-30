
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
#include "Functii.h"
#include "Clase.h"
#include <ctime>

using namespace std;

ofstream writeToLogFile("LOG_FILE");
time_t timpAcum = time(0);
tm* dataLocala = localtime(&timpAcum);
int luna_curenta=1 + dataLocala->tm_mon;

bool BEZIER_MODE = false;
float BEZIER_CURVATURE = -0.1;


// Folosim obiectul asta pentru a prelua informatii importante despre noduri in general.
// De ex daca avem nevoie sa stim care este raza unui nod in pixeli => nodPrefab.pixelRadius
Nod nodPrefab(0, 0, WHITE, -1);


void BuildSecondMenuBackgroundFrames(){
    Frame leftFrame(UDim2(0, 0, 0, 0), UDim2(0.2, 0, 1, 0), Vector2(0, 0), GREEN);
    leftFrame.Render();

    Frame rightFrame(UDim2(1, 0, 0, 0), UDim2(0.2, 0, 1, 0), Vector2(1, 0), GREEN);
    rightFrame.Render();

    Frame bottomFrame(UDim2(0.5, 0, 1, 0), UDim2(0.6, 0, 0.3, 0), Vector2(0.5, 1), GREEN);
    bottomFrame.Render();

    Frame whiteBar1(UDim2(leftFrame.Position.x.scale + leftFrame.Size.x.scale, 0, 0, 0), UDim2(0.01, 0, 1, 0), Vector2(0, 0), WHITE);
    whiteBar1.Render();

    Frame whiteBar2(UDim2(rightFrame.Position.x.scale - rightFrame.Size.x.scale, 0, 0, 0), UDim2(0.01, 0, 1, 0), Vector2(1, 0), WHITE);
    whiteBar2.Render();

    Frame whiteBar3(UDim2(bottomFrame.Position.x.scale, 0, bottomFrame.Position.y.scale - bottomFrame.Size.y.scale, 0),
                    UDim2(bottomFrame.Size.x.scale, 0, 0.02, 0), Vector2(0.5, 1), WHITE);
    whiteBar3.Render();

    Frame rightHorizWhiteBar1(UDim2(whiteBar2.Position.x.scale, 0, 0.12, 0), UDim2(0.2, 0, 0.02, 0), Vector2(0, 0), WHITE);
    rightHorizWhiteBar1.Render();

    Frame rightHorizWhiteBar2(UDim2(whiteBar2.Position.x.scale, 0, 0.26, 0), UDim2(0.2, 0, 0.02, 0), Vector2(0, 0), WHITE);
    rightHorizWhiteBar2.Render();

    Frame leftHorizWhiteBar1(UDim2(whiteBar1.Position.x.scale, 0, 0.12, 0), UDim2(0.2, 0, 0.02, 0), Vector2(1, 0), WHITE);
    leftHorizWhiteBar1.Render();

    Frame leftHorizWhiteBar2(UDim2(whiteBar1.Position.x.scale, 0, 0.26, 0), UDim2(0.2, 0, 0.02, 0), Vector2(1, 0), WHITE);
    leftHorizWhiteBar2.Render();

    Frame algoritmiText(UDim2(rightHorizWhiteBar2.Position.x.scale + 0.01, 0, 0.24, 0), UDim2(0.17, 0, 0.08, 0), Vector2(0, 1), NULL, "Images/AlgoritmiText.jpg");
    algoritmiText.Render();

    Frame outputLogText(UDim2(leftHorizWhiteBar2.Position.x.scale - 0.01, 0, 0.24, 0), UDim2(0.17, 0, 0.08, 0), Vector2(1, 1), NULL, "Images/OutputLogText.jpg");
    outputLogText.Render();
}

bool isMouseOver(Frame f) {
    int mx = mousex();
    int my = mousey();

    return (mx >= f.topLeftX && mx <= f.bottomRightX && my >= f.topLeftY && my <= f.bottomRightY);
}

Frame adaugaNod(UDim2(0.37, 0, 0.77, 0), UDim2(0.23, 0, 0.12, 0), Vector2(0.5, 0.5), NULL, "Images/AdaugaNod.jpg");
Frame adaugaCost(UDim2(0.63, 0, 0.77, 0), UDim2(0.23, 0, 0.12, 0), Vector2(0.5, 0.5), NULL, "Images/AdaugaCost.jpg");
Frame adaugaMuchie(UDim2(0.37, 0, 0.9, 0), UDim2(0.23, 0, 0.12, 0), Vector2(0.5, 0.5), NULL, "Images/AdaugaMuchie.jpg");
Frame stergeGraf(UDim2(0.63, 0, 0.9, 0), UDim2(0.23, 0, 0.12, 0), Vector2(0.5, 0.5), NULL, "Images/StergeGraf.jpg");
Frame playgroundScreen(UDim2(0.50, 0, 0.34, 0), UDim2(0.555, 0, 0.635, 0), Vector2(0.5, 0.5), BLACK);
Frame playgroundScreenCover(UDim2(0.50, 0, 0.34, 0), UDim2(0.581, 0, 0.68, 0), Vector2(0.5, 0.5), BLACK);
Frame inapoi(UDim2(0.9, 0, 0.065, 0), UDim2(0.16, 0, 0.08, 0), Vector2(0.5, 0.5), NULL, "Images/Inapoi.jpg");
Frame deschideFisierLog(UDim2(0.1, 0, 0.065, 0), UDim2(0.16, 0, 0.08, 0), Vector2(0.5, 0.5), NULL, "Images/SalveazaInFisier.jpg");
Frame bfs(UDim2(0.9, 0, 0.365, 0), UDim2(0.16, 0, 0.08, 0), Vector2(0.5, 0.5), NULL, "Images/BFS.jpg");
Frame dfs(UDim2(0.9, 0, 0.465, 0), UDim2(0.16, 0, 0.08, 0), Vector2(0.5, 0.5), NULL, "Images/DFS.jpg");
Frame dijkstra(UDim2(0.9, 0, 0.565, 0), UDim2(0.16, 0, 0.08, 0), Vector2(0.5, 0.5), NULL, "Images/Dijkstra.jpg");
Frame Tarjan(UDim2(0.9, 0, 0.665, 0), UDim2(0.16, 0, 0.08, 0), Vector2(0.5, 0.5), NULL, "Images/Tarjan.jpg");
Frame prim(UDim2(0.9, 0, 0.765, 0), UDim2(0.16, 0, 0.08, 0), Vector2(0.5, 0.5), NULL, "Images/Prim.jpg");
Frame bezierModeOnButton(UDim2(0.9, 0, 0.91, 0), UDim2(0.16, 0, 0.08, 0), Vector2(0.5, 0.5), NULL, "Images/BezierModeOn.jpg");
Frame bezierModeOffButton(UDim2(0.9, 0, 0.91, 0), UDim2(0.16, 0, 0.08, 0), Vector2(0.5, 0.5), NULL, "Images/BezierModeOff.jpg");


Frame brad1(UDim2(.05, 0, .4, 0), UDim2(.3, 0, 0.5, 0), Vector2(0,0), NULL, "Images/LetMeCryLetMeCry.jpg");
Frame brad2(UDim2(.95, 0, .4, 0), UDim2(.3, 0, 0.5, 0), Vector2(1,0), NULL, "Images/LetMeCryLetMeCry.jpg");
Frame orientat(UDim2(0.5, 0, 0.43, 0), UDim2(0.24, 0, .12, 0), Vector2(0.5,0.5), NULL, "Images/OrientatButon.jpg");
Frame neorientat(UDim2(0.5, 0, 0.58, 0), UDim2(0.24, 0, .12, 0), Vector2(0.5,0.5), NULL, "Images/NeorientatButon.jpg");
Frame titlu(UDim2(.5, 0, .2, 0), UDim2(.7, 0, .25, 0), Vector2(.5, .5), NULL, "Images/Titlu.jpg");
Frame buton_exit(UDim2(0.5, 0, 0.75, 0), UDim2(0.18, 0, .12, 0), Vector2(0.5,0.5), NULL, "Images/ExitButton.jpg");

Frame ou1(UDim2(.05, 0, .65, 0), UDim2(.26, 0, 0.3, 0), Vector2(0,0), NULL, "Images/ouaPasteS.jpg");
Frame ou2(UDim2(.95, 0, .65, 0), UDim2(.26, 0, 0.3, 0), Vector2(1,0), NULL, "Images/ouaPasteD.jpg");
Frame orientatP(UDim2(0.5, 0, 0.43, 0), UDim2(0.24, 0, .12, 0), Vector2(0.5,0.5), NULL, "Images/OrientatButonP.jpg");
Frame neorientatP(UDim2(0.5, 0, 0.58, 0), UDim2(0.24, 0, .12, 0), Vector2(0.5,0.5), NULL, "Images/NeorientatButonP.jpg");
Frame titluP(UDim2(.5, 0, .16, 0), UDim2(.7, 0, .3, 0), Vector2(.5, .5), NULL, "Images/TitluP.jpg");
Frame buton_exitP(UDim2(0.5, 0, 0.75, 0), UDim2(0.18, 0, .12, 0), Vector2(0.5,0.5), NULL, "Images/ExitButtonP.jpg");

void EasterMenu(){
    setbkcolor(LIGHTBLUE);
    cleardevice();
    ou1.Render();
    ou2.Render();
    orientatP.Render();
    neorientatP.Render();
    titluP.Render();
    buton_exitP.Render();

}

void MainMenu(){
    setbkcolor(LIGHTMAGENTA);
    cleardevice();
    buton_exit.Render();
    titlu.Render();
    brad1.Render();
    brad2.Render();
    neorientat.Render();
    orientat.Render();

}

void SecondMenuOrientat(){
    setbkcolor(BLACK);
    cleardevice();
    BuildSecondMenuBackgroundFrames();
    adaugaNod.Render();
    adaugaCost.Render();
    adaugaMuchie.Render();
    stergeGraf.Render();
    inapoi.Render();
    deschideFisierLog.Render();
    bfs.Render();
    dfs.Render();
    dijkstra.Render();
    Tarjan.Render();
    bezierModeOffButton.Render();
    bezierModeOnButton.Render();
     if(BEZIER_MODE == true){
        bezierModeOnButton.Render();
    }
    else
        bezierModeOffButton.Render();

}
void SecondMenuNeorientat(){
    setbkcolor(BLACK);
    cleardevice();
    BuildSecondMenuBackgroundFrames();
    adaugaNod.Render();
    adaugaCost.Render();
    adaugaMuchie.Render();
    stergeGraf.Render();
    inapoi.Render();
    deschideFisierLog.Render();
    bfs.Render();
    dfs.Render();
    dijkstra.Render();
    prim.Render();
    Tarjan.Render();
    bezierModeOffButton.Render();
    bezierModeOnButton.Render();
     if(BEZIER_MODE == true){
        bezierModeOnButton.Render();
    }
    else
        bezierModeOffButton.Render();

}




// outputLogFrame.Render() pentru a goli output logul.
Frame outputLogFrame(UDim2(0, 0, 0.28, 0), UDim2(0.2, 0, 1, 0), Vector2(0, 0), GREEN);
int maxLogMessages = 24;
char outputLogMessages[25][80];
int outputLogColors[25];
int outputLogCounter = 0, logTextStartX = outputLogFrame.topLeftX;

void RenderLog(){
    outputLogFrame.Render();
    for(unsigned int i = 0; i < outputLogCounter; i++){
        Frame newText(UDim2(0.01, 0, 0.29 + i * 0.03, 0), UDim2(0, 0, 0, 0), Vector2(0, 0), outputLogColors[i], "", outputLogMessages[i]);
        setbkcolor(GREEN);
        newText.Render();
    }
}

void AddTextToLog(char text[], int color = WHITE){
    outputLogColors[outputLogCounter] = color;
    strcpy(outputLogMessages[outputLogCounter++], text);

    writeToLogFile << text << '\n';


    if(outputLogCounter == maxLogMessages){
        // shift to the start
        for(unsigned int i = 0; i < outputLogCounter; i++){
            outputLogColors[i] = outputLogColors[i + 1];
            strcpy(outputLogMessages[i], outputLogMessages[i + 1]);
        }
        outputLogCounter--;
    }

    // Re render everything.
    // Clear log
    RenderLog();
}

bool READING_FROM_KEYBOARD = false;
int citesteCostTastatura(int nodA = -1, int nodB = -1){
    char tasta;
    char costCitit[10]="";
    int poz=0;
    READING_FROM_KEYBOARD = true;
    while (true)
        {
            if (kbhit())
            {
                tasta=getch();

                if (tasta >= '0' && tasta <= '9')
                {
                   costCitit[poz++]=tasta;
                   costCitit[poz]='\0';
                   AddTextToLog(costCitit, WHITE);
                }


                if (tasta==13)
                {
                    int valoare=atoi(costCitit);

                    if (valoare > 0 && valoare<=MAX_PONDERE)
                    {
                        char mesaj[50]="- COST [";
                        strcat(mesaj, intToChar(nodA));
                        strcat(mesaj, "] -> [");
                        strcat(mesaj, intToChar(nodB));
                        strcat(mesaj, "]: ");
                        strcat(mesaj, costCitit);
                        AddTextToLog(mesaj, LIGHTGREEN);
                        READING_FROM_KEYBOARD = false;
                        return valoare;

                    }
                    else{
                        AddTextToLog("{Introduceti o valoare valida!}", LIGHTRED);
                        costCitit[0]='\0';
                        poz=0;

                    }

                }

            }


        }
}

void HandleNextLogMessage(){


    // Probably for button clicks:
    if(lastClick != clickedPlayground){
        if(actionState == adaugaNodSelected){
            AddTextToLog("- `ADAUGA NOD` selectat.");
        }
        else if(actionState == adaugaCostSelected){
            AddTextToLog("- `ADAUGA COST` selectat.");
            AddTextToLog("- CLICK PE PRIMUL NOD.");
        }
        else if(actionState == adaugaMuchieSelected){
            AddTextToLog("- `ADAUGA MUCHIE` selectat.");
        }
        else if(actionState == stergeGrafSelected){

            char s[51] = "- [";
            strcat(s, intToChar(LAST_CONTOR_NODURI));
            strcat(s, "] noduri sterse.");
            s[strlen(s)] = '\0';
            AddTextToLog(s);
        }
        else if (actionState==bfsSelected)
        {
            AddTextToLog("- `BFS` selectat.");
            AddTextToLog("- Apasati pe nodul de start.", WHITE);
        }
        else if (actionState==dfsSelected)
        {
            AddTextToLog("- `DFS` selectat.");
            AddTextToLog("- Apasati pe nodul de start.", WHITE);
        }
        else if (actionState==tarjanSelected)
        {
            AddTextToLog("- `Tarjan` selectat.");
            AddTextToLog("- Apasati pe nodul de start.", WHITE);
        }
        else if (actionState==dijkstraSelected)
        {
            AddTextToLog("- `DIJKSTRA` selectat.");
            AddTextToLog("- Apasati pe nodul de start.", WHITE);

        }
        else if (actionState==primSelected)
        {
            AddTextToLog("- `PRIM` selectat.");
            AddTextToLog("- Apasati pe nodul de start.", WHITE);
        }

    }
    else
    {
        if(actionState == adaugaNodSelected){

            if(LAST_CONTOR_NODURI < MAX_NODURI){
                char s[51] = "- Nodul [";
                strcat(s, intToChar(CONTOR_NODURI));
                strcat(s, "] adaugat.");
                s[strlen(s)] = '\0';

                AddTextToLog(s);
            }
            else
            {
                AddTextToLog("{PREA MULTE NODURI!}", LIGHTRED);
            }

        }
    }
}

int GetClickedNodeIndex(int mx, int my){
    int closestIndex = -1;
    float distMin = 9999;


    for(unsigned int i = 0; i <= CONTOR_NODURI; i++){
        float x, y, dist;
        x = pozitiiNoduri[i][0];
        y = pozitiiNoduri[i][1];

        dist = magnitude(x - mx, y - my);
        if(dist < distMin){
            distMin = dist;
            closestIndex = i;
        }
    }

    if(distMin > nodPrefab.pixelRadius){
        // Nu apasam pe nici un nod
        return -1;
    }

    return closestIndex;
}

Vector2 GetNodeEdgeTowards(int x1, int y1, int x2, int y2){
    int r = nodPrefab.pixelRadius;

    float dx = x2 - x1;
    float dy = y2 - y1;

    float len = magnitude(dx, dy); // lungimea vectorului
    if (len == 0) return Vector2(0, 0);

    float ux = dx / len; // unit x (normalizat)
    float uy = dy / len; // unit y (normalizat)

    int px = x1 + ux * r;
    int py = y1 + uy * r;

    return Vector2(px, py);
}


void ConnectViaBeziers(Vector2 p1, Vector2 p2)
{
    // direction
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;

    float dist = magnitude(dx, dy);
    if (dist == 0) return;

    
    float ux = dx / dist;
    float uy = dy / dist;

    
    float px = -uy;
    float py = ux;

    float curvature = dist * BEZIER_CURVATURE;
    if(selectedMenu == grafNeorientat) curvature = -curvature;

    
    Vector2 c1(
        p1.x + ux * dist * 0.25f + px * curvature,
        p1.y + uy * dist * 0.25f + py * curvature
    );

    Vector2 c2(
        p2.x - ux * dist * 0.25f + px * curvature,
        p2.y - uy * dist * 0.25f + py * curvature
    );


    Vector2 prev = p1;

    Vector2 lastPrev = p1;
    Vector2 last = p1;

    for (float t = 0; t <= 1.001f; t += 0.02f) {
        float u = 1.0f - t;

        Vector2 p(
            u*u*u * p1.x +
            3*u*u*t * c1.x +
            3*u*t*t * c2.x +
            t*t*t * p2.x,

            u*u*u * p1.y +
            3*u*u*t * c1.y +
            3*u*t*t * c2.y +
            t*t*t * p2.y
        );

        line(int(prev.x), int(prev.y), int(p.x), int(p.y));

        lastPrev = prev;
        last = p;

        prev = p;
    }

    // Desenam arrowheadul intre ultimul si penultimul punct
    if (BEZIER_MODE == true && selectedMenu == grafOrientat) {
        DrawArrowHeadOnly(int(lastPrev.x), int(lastPrev.y), int(last.x), int(last.y));
    }
}


void ConnectNodes(int x1, int y1, int x2, int y2) {
    Vector2 edge1 = GetNodeEdgeTowards(x1, y1, x2, y2);
    Vector2 edge2 = GetNodeEdgeTowards(x2, y2, x1, y1);

    setcolor(WHITE);

    if(selectedMenu == grafNeorientat){
        if(BEZIER_MODE == true){
            ConnectViaBeziers(
                Vector2(edge2.x, edge2.y),
                Vector2(edge1.x, edge1.y)
            );
        }
        else
        {
            line(edge1.x, edge1.y, edge2.x, edge2.y);
        }
    }
    else if(selectedMenu == grafOrientat){
        if(BEZIER_MODE == true){
            ConnectViaBeziers(
                Vector2(edge1.x, edge1.y),
                Vector2(edge2.x, edge2.y)
            );
        }
        else{
            drawArrow(edge1.x, edge1.y, edge2.x, edge2.y);
        }
    }
}
Vector2 findClickedLine(int mx, int my){
    //adj_mat CONTOR_NODURI pozitiiNoduri
    float minDist = 9999;
    int A = -1, B = -1;

    for(int i = 1; i <= CONTOR_NODURI; i++){
        for(int j = i + 1; j <= CONTOR_NODURI; j++){
            if(!adj_mat[i][j]) continue;
            float dist = distanceFromPointToLine(pozitiiNoduri[i][0], pozitiiNoduri[i][1], pozitiiNoduri[j][0], pozitiiNoduri[j][1], mx, my);
            if(dist < minDist){
                A = i;
                B = j;
                minDist = dist;
            }
        }
    }

    if(minDist / ScreenDiagSize > 0.02f){
        A = B = -1;
    }
    return Vector2(A, B);
}


void RegenTwoNodes(int i, int j){
    Vector2 nod1Pos(pozitiiNoduri[i][0], pozitiiNoduri[i][1]);
    Vector2 nod2Pos(pozitiiNoduri[j][0], pozitiiNoduri[j][1]);
    Vector2 lineMid(
        (nod1Pos.x + nod2Pos.x) / 2,
        (nod1Pos.y + nod2Pos.y) / 2
    );

    int cost = adj_mat[i][j];
    if(cost != 1){
        Vector2 textPosition;
        if(selectedMenu == grafOrientat)
            textPosition = GetPerpendicularOffsetPositionFromLine(nod1Pos, nod2Pos, -0.01);
        else{
            textPosition.x = lineMid.x;
            textPosition.y = lineMid.y;
        }

        setcolor(WHITE);
        setbkcolor(BLACK);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        outtextxy(textPosition.x, textPosition.y, intToChar(cost));
    }

    ConnectNodes(
        nod1Pos.x,
        nod1Pos.y,
        nod2Pos.x,
        nod2Pos.y
    );
}

void RegenNodes(){
    playgroundScreenCover.Render();

    for(unsigned int i = 1; i <= CONTOR_NODURI; i++){
        Nod n(pozitiiNoduri[i][0], pozitiiNoduri[i][1], WHITE, i);
        n.Render();
    }


    if(selectedMenu == grafNeorientat){
        for(unsigned int i = 1; i <= CONTOR_NODURI; i++){
            for(int j = i + 1; j <= CONTOR_NODURI; j++){
                if(adj_mat[i][j]){
                    RegenTwoNodes(i, j);
                }
            }
        }
    }
    else{
        for(unsigned int i = 1; i <= CONTOR_NODURI; i++){
            for(int j = 1; j <= CONTOR_NODURI; j++){
                if(adj_mat[i][j] && i != j){
                    RegenTwoNodes(i, j);
                }
            }
        }
    }
}

void ClickedOnPlayground(int mx, int my){

    if(actionState == adaugaNodSelected){
        if(CONTOR_NODURI == MAX_NODURI) return;

        CONTOR_NODURI++;
        Nod n(mx, my, WHITE, CONTOR_NODURI);
        n.Render();
    }
    else if(actionState == adaugaMuchieSelected){

        int nodIndex = GetClickedNodeIndex(mx, my); // retunreaza index daca gaseste, altfel -1 (adica daca nu apasa pe nici un nod)
        if(nodIndex == -1) return;

        if(NOD_SELECTAT != -1 && NOD_SELECTAT == nodIndex){
            // daca incercam sa conectam [i] -> [i] (acelasi nod)
            NOD_SELECTAT = -1;
            char s[51] = "- [";
            strcat(s, intToChar(nodIndex));
            strcat(s, "] deselectat.");
            s[strlen(s)] = '\0';
            AddTextToLog(s, LIGHTGREEN);
            return;
        }


        if(selectedMenu == grafNeorientat){

            if(NOD_SELECTAT == -1){
                if(adj_mat[NOD_SELECTAT][nodIndex] == 1) return;

                NOD_SELECTAT = nodIndex;

                char s[51] = "- [";
                strcat(s, intToChar(nodIndex));
                strcat(s, "] selectat.");
                s[strlen(s)] = '\0';
                AddTextToLog(s, LIGHTGREEN);
            }
            else
            {

                if(adj_mat[nodIndex][NOD_SELECTAT] == 1) return;
                adj_mat[nodIndex][NOD_SELECTAT] = adj_mat[NOD_SELECTAT][nodIndex] = 1;
                RegenNodes();

                char s[51] = "- [";
                strcat(s, intToChar(NOD_SELECTAT));
                strcat(s, "] conectat cu [");
                strcat(s, intToChar(nodIndex));
                strcat(s, "].");
                s[strlen(s)] = '\0';
                AddTextToLog(s, LIGHTGREEN);

                NOD_SELECTAT = -1;
            }

        }
        else if(selectedMenu == grafOrientat){

            if(NOD_SELECTAT == -1){
                if(adj_mat[nodIndex][NOD_SELECTAT] == 1 && adj_mat[NOD_SELECTAT][nodIndex] == 1) return;

                NOD_SELECTAT = nodIndex;

                char s[51] = "- [";
                strcat(s, intToChar(nodIndex));
                strcat(s, "] selectat.");
                s[strlen(s)] = '\0';
                AddTextToLog(s, LIGHTGREEN);
            }
            else
            {
                if(adj_mat[NOD_SELECTAT][nodIndex] == 1 && adj_mat[nodIndex][NOD_SELECTAT] == 1) return;
                adj_mat[NOD_SELECTAT][nodIndex] = 1;

                RegenNodes();

                char s[51] = "- [";
                strcat(s, intToChar(NOD_SELECTAT));
                strcat(s, "] conectat cu [");
                strcat(s, intToChar(nodIndex));
                strcat(s, "].");
                s[strlen(s)] = '\0';
                AddTextToLog(s, LIGHTGREEN);

                NOD_SELECTAT = -1;
            }

        }
    }

    else if(actionState == adaugaCostSelected){
        /*Vector2 ClickedLine = findClickedLine(mx, my); // x = nod 1, y = nod 2 din linie

        if(ClickedLine.x == -1){
            AddTextToLog("{NU S-A GASIT LINIE!}", LIGHTRED);
            return;
        }*/

        int nodIndex = GetClickedNodeIndex(mx, my); // retunreaza index daca gaseste, altfel -1 (adica daca nu apasa pe nici un nod)
        if(nodIndex == -1) return;

        if(NOD_SELECTAT != -1 && NOD_SELECTAT == nodIndex){
            // daca incercam sa adaugam cost de la [i] -> [i] (acelasi nod)
            NOD_SELECTAT = -1;
            char s[51] = "- [";
            strcat(s, intToChar(nodIndex));
            strcat(s, "] deselectat.");
            s[strlen(s)] = '\0';
            AddTextToLog(s, LIGHTGREEN);
            return;
        }

        if(NOD_SELECTAT != -1 && !adj_mat[NOD_SELECTAT][nodIndex]){
            AddTextToLog("{CONEXIUNE INVALIDA!}", LIGHTRED);
            return;
        }

        if(NOD_SELECTAT == -1){
            NOD_SELECTAT = nodIndex;
            char s[51] = "- [";
            strcat(s, intToChar(nodIndex));
            strcat(s, "] este primul nod.");
            s[strlen(s)] = '\0';
            AddTextToLog(s, LIGHTGREEN);
            return;
        }

        char s[51] = "- [";
        strcat(s, intToChar(nodIndex));
        strcat(s, "] este al doilea nod.");
        s[strlen(s)] = '\0';
        AddTextToLog(s, LIGHTGREEN);
        AddTextToLog("- INTRODUCETI COSTUL: ", LIGHTGREEN);


        int cost = citesteCostTastatura(NOD_SELECTAT, nodIndex); // This function asteapta inputul.

        if (selectedMenu==grafNeorientat)
        {
            adj_mat[NOD_SELECTAT][nodIndex] = adj_mat[nodIndex][NOD_SELECTAT] = cost;
        }
        else if (selectedMenu==grafOrientat)
        {
             adj_mat[NOD_SELECTAT][nodIndex]=cost;
        }

        RegenNodes();

        // Reset la primul nod.
        NOD_SELECTAT = -1;

    }
    else if(actionState == bfsSelected){
    int nodIndex = GetClickedNodeIndex(mx, my);
    if(nodIndex == -1){
        AddTextToLog("{INTRODUCETI UN NOD VALID!}", LIGHTRED);
        return;
    }

    if(selectedMenu == grafNeorientat || selectedMenu == grafOrientat){
        for (int i = 1; i <=CONTOR_NODURI; i++)
        {
            setfillstyle(SOLID_FILL, BLACK);
            floodfill(pozitiiNoduri[i][0]-10, pozitiiNoduri[i][1], WHITE);
        }
        AddTextToLog("- START -", YELLOW);
        BFS(nodIndex);
        for (int i = 1; i <= CONTOR_NODURI; i++)
        {
            if (coada_bfs[i]==0) break;
            
            char s[2 * MAX_NODURI];
            s[0] = 0;
            strcat(s, intToChar(i));
            strcat(s, ": ");
            strcat(s, intToChar(coada_bfs[i]));
            AddTextToLog(s, LIGHTGREEN);

            setfillstyle(SOLID_FILL, RED);
            floodfill(pozitiiNoduri[coada_bfs[i]][0]-10, pozitiiNoduri[coada_bfs[i]][1], WHITE);
            delay(500);
            setfillstyle(SOLID_FILL, GREEN);
            floodfill(pozitiiNoduri[coada_bfs[i]][0]-10, pozitiiNoduri[coada_bfs[i]][1], WHITE);
            delay(500);
        }

        AddTextToLog("- STOP -", LIGHTRED);
        RegenNodes();
    }
}
    else if(actionState == dfsSelected){
    int nodIndex = GetClickedNodeIndex(mx, my);
    if(nodIndex == -1){
        AddTextToLog("Introduceti un nod valid!!", LIGHTRED);
        return;
    }

    for (int i = 1; i <= MAX_NODURI; i++) {  //resetam valorile globale
        vizitatDFS[i] = 0;
        coada_dfs[i] = 0;
    }
    index_coada = 1;

    for (int i = 1; i <=CONTOR_NODURI; i++)
    {
        setfillstyle(SOLID_FILL, BLACK);
        floodfill(pozitiiNoduri[i][0]-10, pozitiiNoduri[i][1], WHITE);
    }

    DFS(nodIndex);

    for(int i = 1; i <= index_coada; i++)
    {
        setfillstyle(SOLID_FILL, RED);
        floodfill(pozitiiNoduri[coada_dfs[i]][0]-10, pozitiiNoduri[coada_dfs[i]][1], WHITE);
        delay(500);
        setfillstyle(SOLID_FILL, GREEN);
        floodfill(pozitiiNoduri[coada_dfs[i]][0]-10, pozitiiNoduri[coada_dfs[i]][1], WHITE);
        delay(500);
    }

    RegenNodes();
    char s[2*MAX_NODURI];
    s[0]='\0';
    for (int i = 1; i <= CONTOR_NODURI; i++)
    {
        if (coada_dfs[i]==0){
            break;
        }   
        strcat(s, intToChar(coada_dfs[i]));
        strcat(s, " ");
    }
    AddTextToLog(s, LIGHTGREEN);
}
else if(actionState == tarjanSelected){
    int nodIndex = GetClickedNodeIndex(mx, my);
    if(nodIndex == -1){
        AddTextToLog("Introduceti un nod valid!!", LIGHTRED);
        return;
    }

    for (int i = 1; i <=CONTOR_NODURI; i++)
    {
        setfillstyle(SOLID_FILL, BLACK);
        floodfill(pozitiiNoduri[i][0]-10, pozitiiNoduri[i][1], WHITE);
    }

    for (int i = 1; i <= MAX_NODURI; i++) {  //resetam valorile globale
        vizitatDFS[i] = 0;
        coada_dfs[i] = 0;
        componenteDFS[i]=0;
    }
    index_coada = 1;
    nrComponenteDFS=1;
    componenteDFS[index_coada]=1;   
   
    AddTextToLog("- START -", YELLOW);
    DFS(nodIndex); //incepem parcurgerea de la nodul introdus ca parametru

    for (int i = 1; i <= CONTOR_NODURI; i++) // daca gasim un nod care nu a fost vizitat atunci inseamna ca am gasit inca o componenta conexa
    {
       if (vizitatDFS[i]==0)
       {
        nrComponenteDFS++;
        componenteDFS[nrComponenteDFS]=index_coada; //memoram pozitia din coada la care incepe componenta
        DFS(i);
       }
       
    }

    for(int i = 1; i <= CONTOR_NODURI; i++)
    {
        setfillstyle(SOLID_FILL, RED);
        floodfill(pozitiiNoduri[coada_dfs[i]][0]-10, pozitiiNoduri[coada_dfs[i]][1], WHITE);
        delay(500);
        setfillstyle(SOLID_FILL, GREEN);
        floodfill(pozitiiNoduri[coada_dfs[i]][0]-10, pozitiiNoduri[coada_dfs[i]][1], WHITE);
        delay(500);
    }
        
    RegenNodes();
    componenteDFS[nrComponenteDFS+1]=index_coada;//marcam un index de final 

    for (int i = 1; i <= nrComponenteDFS; i++)
    {
        char p[255]="Componenta nr ";
        strcat(p, intToChar(i));
        strcat(p, ":");
        AddTextToLog(p, LIGHTGREEN);
        char s[2*MAX_NODURI];
        s[0]='\0';

             for (int j=componenteDFS[i]; j < componenteDFS[i+1]; j++)
        {   
            strcat(s, intToChar(coada_dfs[j]));
            strcat(s, " ");
        }
        AddTextToLog(s, WHITE);
        
        
    }
    AddTextToLog("- STOP -", LIGHTRED);
}
    

    if (actionState==dijkstraSelected)
    {
        int nodIndex = GetClickedNodeIndex(mx, my);
        if(nodIndex == -1){
            AddTextToLog("{INTRODUCETI UN NOD VALID!}", LIGHTRED);
            return;
        }

        AddTextToLog("- START -", YELLOW);
        DIJSKTRA(nodIndex);

        for (int i = 1; i <=CONTOR_NODURI; i++)
        {
            if (distDijkstra[i]!=infinit && i!=nodIndex)
            {
                char s[2*MAX_NODURI];
                s[0]='\0';
                strcat(s, "[");
                strcat(s, intToChar(nodIndex));
                strcat(s, "] la [");
                strcat(s,intToChar(i));
                strcat(s, "] = ");
                strcat(s,intToChar(distDijkstra[i]));
               AddTextToLog(s, LIGHTGREEN);
            }
            if (distDijkstra[i]==infinit && i!=nodIndex)
            {
                char s[2*MAX_NODURI];
                s[0]='\0';
                strcat(s, "[");
                strcat(s, intToChar(nodIndex));
                strcat(s, "] la [");
                strcat(s,intToChar(i));
                strcat(s, "] = ");
                strcat(s, "{NU EXISTA DRUM!}");
               AddTextToLog(s, LIGHTGREEN);
            }

        }
        AddTextToLog("- STOP -", LIGHTRED);
        RegenNodes();

    }
    if (actionState == primSelected && selectedMenu==grafNeorientat)
    {
        int nodIndex = GetClickedNodeIndex(mx, my);
        if(nodIndex == -1){
            AddTextToLog("INTRODUCETI UN NOD VALID!}", LIGHTRED);
            return;
        }

        AddTextToLog("- START -", YELLOW);
        PRIM(nodIndex);
       for (int i = 1; i <= CONTOR_NODURI; i++)
        {
            if (i!=nodIndex && tatiPrim[i]!=-1)
            {
                char s[100];
                s[0]='\0';
                strcat(s, "Muchie: ");
                strcat(s, intToChar(i));
                strcat(s, " -> ");
                strcat(s, intToChar(tatiPrim[i]));
                strcat(s, "  Pondere:");
                strcat(s,intToChar(cheiePrim[i]));
                AddTextToLog(s, LIGHTGREEN);

            }

        }
        AddTextToLog("- STOP -", LIGHTRED);
        RegenNodes();

    }

}

void ClearWholePlayground(){
    playgroundScreenCover.Render();
    NOD_SELECTAT = -1;

    for(unsigned int i = 1; i <= CONTOR_NODURI; i++){
        pozitiiNoduri[i][0] = 0;
        pozitiiNoduri[i][1] = 0;

        for(unsigned int j = 1; j <= CONTOR_NODURI; j++){
            adj_mat[i][j] = adj_mat[j][i] = 0;
        }
    }
    CONTOR_NODURI = 0;
}




void HandleEvents(){
    int nod_start;

    // Build graph playground:
    setbkcolor(BLACK);
    cleardevice();

    // Render buttons:
    if (luna_curenta!=4)
    {
       MainMenu();
    }
    else{
        EasterMenu();
    }



    bool running = true;
    while(running){
        if(ismouseclick(WM_LBUTTONDOWN) && !READING_FROM_KEYBOARD) {
            if(selectedMenu == mainMenu){
                if(isMouseOver(orientat)){
                    selectedMenu = grafOrientat;
                    SecondMenuOrientat();
                    RenderLog();
                }
                else if(isMouseOver(neorientat)){
                    selectedMenu = grafNeorientat;
                    SecondMenuNeorientat();
                    RenderLog();
                }
                else if(isMouseOver(buton_exit)){
                    running = false;
                }

            }
            else if(selectedMenu == grafOrientat || selectedMenu == grafNeorientat){

                bool mouseOverAnything = false;
                if(isMouseOver(adaugaNod)){
                    mouseOverAnything = true;
                    actionState = adaugaNodSelected;
                    lastClick = adaugaNodSelected;
                    NOD_SELECTAT = -1;
                }
                else if(isMouseOver(adaugaCost)){
                    mouseOverAnything = true;
                    actionState = adaugaCostSelected;
                    lastClick = adaugaCostSelected;
                    NOD_SELECTAT = -1;
                }
                else if(isMouseOver(adaugaMuchie)){
                    mouseOverAnything = true;
                    actionState = adaugaMuchieSelected;
                    lastClick = adaugaMuchieSelected;
                    NOD_SELECTAT = -1;

                }
                else if(isMouseOver(stergeGraf)){
                    mouseOverAnything = true;
                    actionState = stergeGrafSelected;
                    lastClick = stergeGrafSelected;

                    ClearWholePlayground();
                }
                else if(isMouseOver(playgroundScreen)){
                    mouseOverAnything = true;
                    lastClick = clickedPlayground;

                    ClickedOnPlayground(mousex(), mousey());
                }
                else if(isMouseOver(inapoi)){
                    if (luna_curenta!=4)
                    {
                    selectedMenu = mainMenu;
                    ClearWholePlayground();
                    MainMenu();
                    }
                    else{
                        selectedMenu = mainMenu;
                        ClearWholePlayground();
                        EasterMenu();
                    }

                }
                else if(isMouseOver(deschideFisierLog)){
                    openLogFiles("LOG_FILE");

                }
                else if (isMouseOver(dfs))
                {
                    actionState=dfsSelected;
                    mouseOverAnything=true;
                    lastClick=dfsSelected;
                }
                else if (isMouseOver(Tarjan))
                {
                    actionState=tarjanSelected;
                    mouseOverAnything=true;
                    lastClick=tarjanSelected;
                }
                else if (isMouseOver(bfs))
                {
                    actionState=bfsSelected;
                    lastClick=bfsSelected;
                    mouseOverAnything=true;
                }
                else if (isMouseOver(prim) && selectedMenu==grafNeorientat)
                {
                    actionState=primSelected;
                    lastClick=primSelected;
                    mouseOverAnything=true;
                }
                else if (isMouseOver(dijkstra) && (selectedMenu==grafNeorientat || selectedMenu == grafOrientat))
                {
                    actionState=dijkstraSelected;
                    lastClick=dijkstraSelected;
                    mouseOverAnything=true;
                }
                else if (isMouseOver(bezierModeOffButton)){
                    BEZIER_MODE = !BEZIER_MODE;
                    if(BEZIER_MODE == true)
                        bezierModeOnButton.Render();
                    else
                        bezierModeOffButton.Render();
                    RegenNodes();
                }

                if(mouseOverAnything == true){
                    HandleNextLogMessage();
                    LAST_CONTOR_NODURI = CONTOR_NODURI;
                }

            }

            clearmouseclick(WM_LBUTTONDOWN);
        }

    }
}



int main() {
    int gd = DETECT, gm;
    initwindow(ScreenSizeX, ScreenSizeY, "Window");

    HandleEvents();


    closegraph();
    return 0;
}

