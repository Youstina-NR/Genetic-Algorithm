#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <cstdio>
#include <string.h>

#define n 20
using namespace std;

void fitness();
void sort_fitness();
void print_G_F();
void init_distTable();
void print_D();
void init_genes();
void crossover();
void mutation();


int D[n][n];  //distance
int G[n][n];  //genes
int F[n];

int main()
{
    init_distTable();
   // print_D();

    init_genes();

    //calculate the fitness
    fitness();
    print_G_F();

    //sort genes according to fitness
    sort_fitness();
    print_G_F();

    int itr=50;
    while(itr--)
    {
       crossover();
       mutation();
       fitness();
       sort_fitness();
       print_G_F();
    }



    return 0;
}

void init_distTable()
{
    srand(time(NULL));
    int t;

    for(int i=0;i<n;i++)
    {
        D[i][i]=0;
        for(int j=i+1;j<n;j++)
        {
             t=rand()%1000;
             D[i][j]=D[j][i]=t;
        }
     }

}

void init_genes()
{
    for(int i=0;i<n;i++)
    {
       G[0][i]=i+1;
    }
    for(int i=1;i<n;i++)
    {
       for(int j=0;j<n;j+=2)
       {
          if(i&1)
          {
             G[i][j]=G[i-1][j+1];
             G[i][j+1]=G[i-1][j];
          }
          else
          {
             if(j==0 || j==n-1)
             {
                  G[i][j]=G[i-1][j];
                  j--;
             }

             else
             {
                 G[i][j]=G[i-1][j+1];
                 G[i][j+1]=G[i-1][j];
             }
          }

       }
    }
}

void print_D()
{
    for(int i=0;i<n;i++)
    {
       for(int j=0;j<n;j++)
       cout<<D[i][j]<<"  ";
       cout<<endl;
    }
}
void fitness()
{
    for(int i=0;i<n;i++)
    {
       int f=0;
       for(int j=0;j<n-1;j++)
          f+=D[G[i][j]-1][G[i][j+1]-1];
       f+=D[G[i][n-1]-1][G[i][0]-1];
       F[i]=f;
    }

}
void print_G_F()
{
   cout<<endl;
   for(int i=0;i<n;i++)
    {
       for(int j=0;j<n;j++)
       cout<<G[i][j]<<"  ";
       cout<<"        "<<F[i]<<endl;
    }
    cout<<endl;

}


void sort_fitness()
{
//int temp[6];
   for(int i=n-1;i>=0;i--)
   {
       for(int j=1;j<=i;j++)
       {
           if(F[j-1]>F[j])
           {

               //swap genes
               swap(G[j-1],G[j]);
               /*
               memcpy(temp,G[j-1],sizeof(temp));
               memcpy(G[j-1],G[j],sizeof(G[j-1]));
               memcpy(G[j],temp,sizeof(G[j]));
               */
               swap(F[j-1],F[j]);

           }
       }
   }

}

int found(int x,int i)
{
    for(int j=2;j<5;j++)
       if(G[i][j]==x)
           return 1;
    return 0;
}

void crossover()
{
     memcpy(G[2],G[0],sizeof(G[2]));
     memcpy(G[3],G[1],sizeof(G[3]));
     int j=5,k=5;
     while(k!=2)
     {
        if(!found(G[1][j],2))
        {
            G[2][k]=G[1][j];
            k++;
            k=k%6;

        }
        j++;
        j%=6;

     }
     j=5,k=5;
     while(k!=2)
     {
        if(!found(G[0][j],3))
        {
            G[3][k]=G[0][j];
            k++;
            k=k%6;

        }
        j++;
        j%=6;

     }


}

void mutation()
{
    int temp;
    temp=G[4][1];
    G[4][1]=G[4][4];
    G[4][4]=temp;

    temp=G[5][1];
    G[5][1]=G[5][4];
    G[5][4]=temp;
}
