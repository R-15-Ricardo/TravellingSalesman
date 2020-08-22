//La segunda es la vencida
#include "graphLib.h"
#include "rColors.h"
//#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

int main (int argc,char *argv[])
{
    //Checks for console arg validity
    if (argc<2)
    {
        cout<<"Error. El programa necesita parametro N"<<endl;
        exit(EXIT_SUCCESS);
    }
    int nodes=atoi(argv[1]);

    //int nodes=10;
    //random seed
    srand((unsigned)time(NULL));

    //Create window and resources
    VideoMode mode(WIDTH,HEIGHT,32);
    RenderWindow wnd;
    Event closed;
    wnd.create(mode,"Traveling Salesman Problem MST Aproximation");

    Font disp;
    disp.loadFromFile("VeraMono.ttf");

    Text Total;
    Total.setFont(disp);
    Total.setCharacterSize(15);
    Total.setFillColor(Color::Black);
    Total.setPosition(15,15);
    string totalText="Total cost: ";
    Text tags[nodes];

    CircleShape dots[nodes];

    bool ShowingP=0;

    //Genrates and print a random graph
    cout<<"Grafo completo:"<<endl;
    graph g1(atoi(argv[1]));

    for (int i=0;i<nodes;i++)
    {
        vert vertexToTag=g1.getV(i);
        string cTag=to_string(vertexToTag.n);
        tags[i].setFont(disp);
        tags[i].setCharacterSize(10);
        tags[i].setFillColor(Color::Black);
        tags[i].setPosition(vertexToTag.x-12,vertexToTag.y-12);
        tags[i].setString(cTag);

        dots[i].setFillColor(Color::Blue);
        dots[i].setRadius(5);
        dots[i].setPosition(vertexToTag.x-5,vertexToTag.y-5);
    }



    for (int i=0;i<g1.getM();i++)
    {
        edg e=g1.getE(i);
        cout<<"d("<<e.a.n<<","<<e.b.n<<")="<<e.getW()<<endl;
    }
    cout<<endl;

    //Gets set of edges of g1's MST
    vector <edg> mste;
    mste=MST(g1);

    //From set, generates adyacency matrix
    bool **adj;
    adj=new bool* [nodes];
    for (int i=0;i<nodes;i++) adj[i]=new bool [nodes];

    for (int i=0;i<mste.size();i++)
    {
        edg e=mste.at(i);
        adj[e.a.n][e.b.n]=adj[e.b.n][e.a.n]=1;
    }

    //Traverse MST and generates path
    vector <int> path;
    path=pathfinder(adj,nodes);

    //All paths
    Vertex lines [g1.getM()][2];
    for (int i=0;i<g1.getM();i++)
    {
        edg todraw=g1.getE(i);
        vert a,b;
        a=todraw.a;
        b=todraw.b;
        // float nxa,nya,nxb,nyb;
        // nxa=a.x-2;
        // nya=(((b.y-a.y)/(b.x-a.x))*(nxa-a.x))+a.y;
        // nxb=b.x-2;
        // nyb=(((b.y-a.y)/(b.x-a.x))*(nxb-a.x))+a.y;
        lines[i][0]=Vertex(Vector2f(a.x,a.y),Color::Black);
        //lines[i][1]=Vertex(Vector2f(nxa,nya),Color::Black);
        lines[i][1]=Vertex(Vector2f(b.x,b.y),Color::Black);
        //lines[i][3]=Vertex(Vector2f(nxb,nyb),Color::Black);
    }

    //Aproximated path
    Vertex pathshow[nodes-1][2];
    int hue=0;
    for (int i=0;i<nodes-1;i++)
    {
        Color pathColor=hsv(hue,1,1);
        edg todraw=g1.selectEdge(path.at(i),path.at(i+1));
        vert a,b;
        a=todraw.a;
        b=todraw.b;
        pathshow[i][0]=Vertex(Vector2f(a.x,a.y),pathColor);
        pathshow[i][1]=Vertex(Vector2f(b.x,b.y),pathColor);
        hue+=360/(nodes-1);
    }

    //Prints path and total cost
    cout<<"Aproximacion del TSP:"<<endl;
    float cost=0;
    for (int i=0;i<nodes-1;i++)
    {
        edg e=g1.selectEdge(path.at(i),path.at(i+1));
        cost+=e.getW();
        cout<<"d("<<e.a.n<<","<<e.b.n<<")="<<e.getW()<<endl;
    }
    cout<<"Total cost: "<<cost<<endl;
    cout<<"Press 'P' to show the Traveling Salesman path"<<endl;
    cout<<"Press 'O' to shot the full graph"<<endl;
    totalText+=to_string(cost);
    Total.setString(totalText);

    while (wnd.isOpen())
    {
        while (wnd.pollEvent(closed))
        {
            if (closed.type==Event::Closed)
                wnd.close();
        }
        wnd.clear(Color::White);

        //Toggle for showing path of fully conected graph
        if (Keyboard::isKeyPressed(Keyboard::P)) ShowingP=1;
        if (Keyboard::isKeyPressed(Keyboard::O)) ShowingP=0;

        if (ShowingP)
        {
            for (int i=0;i<nodes-1;i++)
            {
                wnd.draw(pathshow[i],2,Lines);
            }
        }
        else
        {
            for (int i=0;i<g1.getM();i++)
            {
                wnd.draw(lines[i],2,Lines);
            }
        }

        //Cities and tags
        for (int i=0;i<nodes;i++)
        {
            wnd.draw(dots[i]);
            wnd.draw(tags[i]);
        }

        wnd.draw(Total);

        wnd.display();
    }
}
