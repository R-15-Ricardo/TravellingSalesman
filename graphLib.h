#include <bits/stdc++.h>

//Iba a usar SFML para poder ver el camino en una ventana de 800x600. Por eso estos numeros
#define HEIGHT 600
#define WIDTH 800

//Vertes type
struct vert
{
    int n;
    int x;
    int y;
};

//Edge type
class edg {
    private:
        float w;
    public:
        vert a;
        vert b;
        edg()
        {
            w=0;
        }
        edg(vert a,vert b)
        {
            this->a=a;
            this->b=b;
            //w(a,b):= Euclidean distance
            this->w=sqrt(pow(abs(a.x-b.x),2)+pow(abs(a.y-b.y),2));
        }
        float getW()
        {
            return w;
        }
};

//Graph type
class graph {
    private:
        int n;
        int m;
        vert* V;
        edg* E;
    public:
        graph(int);
        void sortEdgs();
        edg selectEdge(int a,int b);
        int getN()
        {
            return n;
        }
        int getM()
        {
            return m;
        }
        edg getE (int i)
        {
            return E[i];
        }
        vert getV (int i)
        {
            return V[i];
        }
};

//Disjoint set type
struct mset
{
    int p;
    int rank;
};

//Path generating functions
std::vector <edg> MST (graph G);
std::vector <int> pathfinder (bool**,int);
