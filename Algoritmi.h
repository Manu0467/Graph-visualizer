#ifndef ALGORITMI_H
#define ALGORITMI_H

#include <iostream>
#include <graphics.h>
#include "Functii.h"

using namespace std;
const int MAX_NODURI=101;
const int MAX_PONDERE=100000;
const int infinit=100001;



int CONTOR_NODURI=0;
int muchii_curente;
int adj_mat[MAX_NODURI][MAX_NODURI];
int coada_dfs[MAX_NODURI], coada_bfs[MAX_NODURI];
int distDijkstra[MAX_NODURI];
int tatiPrim[MAX_NODURI];
int cheiePrim[MAX_NODURI];
int componenteDFS[MAX_NODURI];
int nrComponenteDFS;


void BFS(int n){
 int indice_global=1;
 int k,st,dr;

 int x[MAX_NODURI]={0}, v[MAX_NODURI]={0};

 for (int j = 0; j <= MAX_NODURI; j++)
 {
    coada_bfs[j]=0; //resetam coada declarata global
 }
 
   
        st = dr = 1;
        x[1] = n;
        v[n] = 1;
        coada_bfs[indice_global++] = n;

        while (st <= dr) {
            k = x[st++];
            for (int i = 1; i <= CONTOR_NODURI; i++) {
                if (v[i] == 0 && adj_mat[k][i] != 0) {
                    v[i] = 1;
                    x[++dr] = i;
                    coada_bfs[indice_global++] = i;
                }
            }
        }
    
   
 
}

int vizitatDFS[MAX_NODURI]={0}, index_coada=1;
void DFS(int n){
    vizitatDFS[n]=1;
    coada_dfs[index_coada]=n;
    index_coada++;
    
    for (int i = 1; i <= CONTOR_NODURI; i++)
    {
        if (adj_mat[n][i]!=0 && vizitatDFS[i]==0 )
        {
            DFS(i);
        }
        
    }
}

void DIJSKTRA(int nod_start)
{
int dist[MAX_NODURI];
bool noduri_vizitate[MAX_NODURI];
int ultimul_nod[MAX_NODURI];



for (int i = 1; i <= CONTOR_NODURI; i++)//initializez distanta de la un nod la sine insusi cu 0
    {           
        adj_mat[i][i]=0;
    }
for (int i = 1; i <= CONTOR_NODURI; i++)//initializez distanta pana la fiecare nod
{                                       //resetam valorile globale
    dist[i]=infinit;
    ultimul_nod[i]=-1;
    noduri_vizitate[i]=0;
    distDijkstra[i]=infinit;
}

dist[nod_start]=0; //distanta de la nodul de start va fi 0

for (int j = 1; j <= CONTOR_NODURI; j++)
{
    int min_dist=INT_MAX;
    int nod_curent=-1;

    for (int k = 1; k <= CONTOR_NODURI; k++) //determina nodul cel mai apropiat de distanta minima de nodul sursa
    {
        if (dist[k]<min_dist && noduri_vizitate[k]==0)
        {
            min_dist=dist[k];
            nod_curent=k;
        } 
    }

    if (nod_curent == -1 || dist[nod_curent]==infinit) break; //daca nodul este inaccesibil sau este izolat programul se opreste

    noduri_vizitate[nod_curent]=1;//vizitam nodul curent

    for (int j = 1; j <= CONTOR_NODURI; j++)//determina costul minim pentru nodurile nevizitate vecine cu nodul curent(relaxarea vecinilor)
    {
        if (noduri_vizitate[j]==0  && adj_mat[nod_curent][j]>0)//daca nodul nu este vizitat si exista o muchie intre cele 2 noduri
        {
            if ((dist[nod_curent]+adj_mat[nod_curent][j])<dist[j])  //daca distanta curenta este mai mica decat distanta pana la acel nod, actualizam distanta          
            {
                dist[j]=dist[nod_curent]+adj_mat[nod_curent][j];
                ultimul_nod[j]=nod_curent;
            }
        } 
    }     
}

for (int i = 1; i <= CONTOR_NODURI; i++)
{
           distDijkstra[i]=dist[i];
}

}
void PRIM(int nod_start){
int tati[MAX_NODURI];
int vizitat[MAX_NODURI];
int cheie[MAX_NODURI];

for (int i = 1; i <= CONTOR_NODURI; i++)
{
    tati[i]=-1;
    cheie[i]=infinit;
    vizitat[i]=0;
    tatiPrim[i]=-1;
    cheiePrim[i]=infinit;

}

tati[nod_start]=0;
cheie[nod_start]=0;
tatiPrim[nod_start]=0;
cheiePrim[nod_start]=0;


for (int i = 1; i <= CONTOR_NODURI; i++)
{
    int cost_min=infinit;
    int nod_urmator=-1;

    for (int j = 1; j <= CONTOR_NODURI; j++)
    {
        if (!vizitat[j] && cheie[j]<cost_min )
        {
            cost_min=cheie[j];
            nod_urmator=j;
        }
        
    }
     if (nod_urmator==-1)//daca urmatorul nod este deconectat de graf ne oprim
    {
        break;
    }
    
     vizitat[nod_urmator]=true;

    for (int k = 1; k <= CONTOR_NODURI; k++)
    {   
        int cost_muchie=adj_mat[nod_urmator][k];
        
        if (!vizitat[k] && cost_muchie!=0 && cost_muchie<cheie[k])
        {
            tati[k]=nod_urmator;
            cheie[k]=cost_muchie;
        }
        
    }  
    
}
for (int i = 1; i <= CONTOR_NODURI; i++)
{
    tatiPrim[i]=tati[i];
    cheiePrim[i]=cheie[i];
}

}

#endif