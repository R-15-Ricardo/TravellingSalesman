#include "graphLib.h"

using namespace std;

//Graph initializer from vertx count
graph::graph (int n)
{
    V=new vert [n];
    for (int i=0;i<n;i++)
    {
        V[i].n=i;
        V[i].x=rand()%(WIDTH-80)+40;
        V[i].y=rand()%(HEIGHT-80)+40;
    }
    int nEdges=((n-1)*n)/2;
    E=new edg [nEdges];
    int index=0;
    for (int i=0;i<n;i++)
    {
        for (int j=i+1;j<n;j++)
        {
            E[index]=edg(V[i],V[j]);
            index++;
        }
    }
    this->n=n;
    this->m=nEdges;
}

//sorts edges using ||a-b|| in non-decresing order
void graph::sortEdgs ()
{
    sort(E,E+m,[](edg a,edg b){return a.getW()<b.getW();});
}

//Since graph is complete, choose any edge
edg graph::selectEdge(int a,int b)
{
    return edg(V[a],V[b]);
}


//FIND-SET operation on tree
int find(mset ssets[], int u)
{
    if (ssets[u].p != u)
        ssets[u].p = find(ssets, ssets[u].p);
    return ssets[u].p;
}

//UNION operation on tree
void Union(mset ssets[], int u, int v)
{
    int uroot = find(ssets, u);
    int vroot = find(ssets, v);
    if (ssets[uroot].rank < ssets[vroot].rank)
        ssets[uroot].p = vroot;
    else if (ssets[uroot].rank > ssets[vroot].rank)
        ssets[vroot].p = uroot;
    else
    {
        ssets[vroot].p = uroot;
        ssets[uroot].rank++;
    }
}

//Kruskal MST algorithm
vector <edg> MST (graph G)
{
    vector <edg> A;
    mset ssets[G.getN()];
    //MAKE-SET operation on tree
    for (int i=0;i<G.getN();i++)
    {
        ssets[i].p=i;
        ssets[i].rank=0;
    }
    G.sortEdgs();
    for (int i=0;i<G.getM();i++)
    {
        //If no-cycle, add to edge-set
        if (find(ssets,G.getE(i).a.n)!=find(ssets,G.getE(i).b.n))
        {
            A.push_back(G.getE(i));
            Union(ssets,G.getE(i).a.n,G.getE(i).b.n);
        }
    }
    return A;
}

//Modified BFS to traverse MST
vector <int> pathfinder (bool **adj,int n)
{
    vector <int> pth;
    queue <int> track;
    bool seen[n]={0};

    track.push(0);
    seen[0]=1;

    while (!track.empty())
    {
        int now=track.front();
        track.pop();
        pth.push_back(now);
        for (int i=0;i<n;i++)
        {
            if (adj[now][i] && !seen[i])
            {
                seen[i]=1;
                track.push(i);
            }
        }
    }
    return pth;
}
