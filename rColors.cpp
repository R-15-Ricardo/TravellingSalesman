#include "rColors.h"

using namespace sf;

Color hsv(int,float,float);
double getHue (int,int,int);

Color hsv(int hue, float sat, float val)
{
    hue %= 360;
    while(hue<0) hue += 360;

    if(sat<0.f) sat = 0.f;
    if(sat>1.f) sat = 1.f;

    if(val<0.f) val = 0.f;
    if(val>1.f) val = 1.f;

    int h = hue/60;
    float f = float(hue)/60-h;
    float p = val*(1.f-sat);
    float q = val*(1.f-sat*f);
    float t = val*(1.f-sat*(1-f));

    switch(h)
    {
        default:
        case 0:
        case 6: return Color(val*255, t*255, p*255);
        case 1: return Color(q*255, val*255, p*255);
        case 2: return Color(p*255, val*255, t*255);
        case 3: return Color(p*255, q*255, val*255);
        case 4: return Color(t*255, p*255, val*255);
        case 5: return Color(val*255, p*255, q*255);
    }
}


double getHue (int r, int g, int b)
{
    double hue;
    double colors[3];
    colors[0]=r/(double)255;
    colors[1]=g/(double)255;
    colors[2]=b/(double)255;
    int maxindex=0;
    int minindex=0;
    for (int i=0;i<3;i++)
    {
        if (colors[maxindex]<colors[i]) maxindex=i;
        if (colors[minindex]>colors[i]) minindex=i;
    }
    switch (maxindex) {
        case 0:
            hue=(colors[1]-colors[2])/(colors[maxindex]-colors[minindex]);
            break;
        case 1:
            hue=2+(colors[2]-colors[0])/(colors[maxindex]-colors[minindex]);
            break;
        case 2:
            hue=4+(colors[0]-colors[1])/(colors[maxindex]-colors[minindex]);
            break;
    }
    return hue;
}
