#include <iostream>
#include "Algoritmi.h"

using namespace std;
const int MAX_NODURI=100;
const int MAX_PONDERE=100000;
const int infinit=100001;


int CONTOR_NODURI;
int muchii_curente;
int adj_mat[MAX_NODURI][MAX_NODURI];

void init_oriented_graph(int n, int m){

    CONTOR_NODURI=n;
    muchii_curente=m;
    for (int i = 1; i <= CONTOR_NODURI; i++)
    {
        for (int j = 1; j <= CONTOR_NODURI; j++)
        {
            adj_mat[i][j]=MAX_PONDERE;
        } 
    }
    for (int i = 1; i <= m; i++)
    {
        int p, q;
        cin>>p>>q;
        adj_mat[p][q]=1;
    }
}
void init_noriented_graph(int n, int m){
    CONTOR_NODURI=n;
    muchii_curente=m;
    for (int i = 1; i <= CONTOR_NODURI; i++)
    {
        for (int j = 1; j <= CONTOR_NODURI; j++)
        {
            adj_mat[i][j]=MAX_PONDERE;
        } 
    }
    for (int i = 1; i <= m; i++)
    {
        int p, q, inf;
        cin>>p>>q>>inf;
        adj_mat[p][q]=inf;
        adj_mat[q][p]=inf;
    }
}

void DIJSKTRA(int nod_start)
{
int dist[CONTOR_NODURI];
bool noduri_vizitate[CONTOR_NODURI]={0};
int ultimul_nod[CONTOR_NODURI];

for (int i = 1; i <= CONTOR_NODURI; i++)//initializez distanta de la un nod la sine insusi cu 0
    {           
        adj_mat[i][i]=0;
    }
for (int i = 1; i <= CONTOR_NODURI; i++)//initializez distanta pana la fiecare nod
{
    dist[i]=infinit;
    ultimul_nod[i]=-1;
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

    if (nod_curent == -1) break; //daca nodul este inaccesibil sau este izolat programul se opreste

    noduri_vizitate[nod_curent]=1;//vizitam nodul curent

    for (int j = 1; j <= CONTOR_NODURI; j++)//determina costul minim pentru nodurile nevizitate vecine cu nodul curent(relaxarea vecinilor)
    {
        if (noduri_vizitate[j]==0  && adj_mat[nod_curent][j]!=MAX_PONDERE)//daca nodul nu este vizitat si exista o muchie intre cele 2 noduri
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
    cout<<"Distanta de la nodul "<<nod_start<<" la nodul "<<i<<" este:"<<dist[i]<<endl;
}

}
void BFS(int n){
 int i,k,st,dr;

 int x[CONTOR_NODURI]={0}, v[CONTOR_NODURI]={0};
  st=dr=1;
  x[1]=n;
  v[n]=1;//vizitez varful initial
  while(st<=dr)//cat timp coada nu este vida
  {
    k=x[st];//preiau un element din coada
    //cout<<k<<" ";
    for(i=1; i<=CONTOR_NODURI; i++)//parcurg varfurile
      if(v[i]==0 && adj_mat[k][i]!=0)//daca i este vecin cu k si nu este vizitat
      {
        v[i]=1;//il vizitez
        x[++dr]=i;//il adaug in coada
      }
    st++;//sterg din coada
  }
for (int i = 1; i <= dr; i++)
{
    cout<<x[i]<<" ";
}

}
int vizitat[MAX_NODURI]={0};
void DFS(int n){
    vizitat[n]=1;
    cout<<n<<" ";
    
    for (int i = 1; i <= CONTOR_NODURI; i++)
    {
        if (adj_mat[n][i]!=0 && vizitat[i]==0 )
        {
            DFS(i);
        }
        
    }
}

void PRIM(int nod_start){
int tati[MAX_NODURI];
int vizitat[MAX_NODURI]={0};
int cheie[MAX_NODURI];

for (int i = 1; i <= CONTOR_NODURI; i++)
{
    tati[i]=-1;
    cheie[i]=infinit;
}

tati[nod_start]=0;
cheie[nod_start]=0;


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
        
        if (!vizitat[k] && cost_muchie!=MAX_PONDERE && cost_muchie<cheie[k])
        {
            tati[k]=nod_urmator;
            cheie[k]=cost_muchie;
        }
        
    }  
    
}
for (int i = 1; i <= CONTOR_NODURI; i++)
{
    if (i!=nod_start && tati[i]!=-1)
    {

            cout<<"Muchie:"<<tati[i]<<"->"<<i<<"  Pondere:"<<cheie[i]<<endl;
        
    }
    
}

}
int main(){
    int n, m;
    cin>>n>>m;
    init_noriented_graph(n, m);
    for (int i = 1; i <= CONTOR_NODURI; i++)
    {
        for (int j = 1; j <= CONTOR_NODURI; j++)
        {
            cout<<adj_mat[i][j]<<"  ";
        }
        cout<<endl;
        
    }

   PRIM(2);
   DIJSKTRA(2);
    

    
    return 0;
}
