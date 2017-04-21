#include <windows.h>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <vector>

using namespace std;

void draw_line(HDC hdc,int x0,int y0,int x1,int y1,COLORREF color)
{
    int i;
    //printf("%d\n",hdc);
    if(x0>x1)
    {
        swap(x0,x1);
        swap(y0,y1);
    }
    int dx = x1 - x0;
    int dy = y1 - y0;
    if(dx>=abs(dy))
    {
        int pos = dy>0 ? 1 : -1;
        int e = 2*pos*dy - dx;
        int x = x0;
        int y = y0;
        for(i=0;i<=dx;i++)
        {
            SetPixel(hdc,x,y,color);
            x++;
            if(e>=0)
            {
                y += pos;
                e += 2*pos*dy - 2*dx;
            }
            else
            {
                e += 2*pos*dy;
            }
        }
    }
    else
    {
        if(y0>y1)
        {
            swap(x0,x1);
            swap(y0,y1);
        }
        dx = x1 - x0;
        dy = y1 - y0;
        int pos = dx>0 ? 1 : -1;
        int e = 2*pos*dx - dy;
        int x = x0;
        int y = y0;
        for(i=0;i<=dy;i++)
        {
            SetPixel(hdc,x,y,color);
            y++;
            if(e>=0)
            {
                x += pos;
                e += 2*pos*dx - 2*dy;
            }
            else
            {
                e += 2*pos*dx;
            }
        }
    }
}


void circle_points(HDC hdc,int x,int y,int x0,int y0,COLORREF color)
{
    //cout << x << ' ' << y << endl;
    SetPixel(hdc,x+x0,y+y0,color);
    SetPixel(hdc,-x+x0,y+y0,color);
    SetPixel(hdc,x+x0,-y+y0,color);
    SetPixel(hdc,-x+x0,-y+y0,color);
    SetPixel(hdc,y+y0,x+x0,color);
    SetPixel(hdc,-y+y0,x+x0,color);
    SetPixel(hdc,y+y0,-x+x0,color);
    SetPixel(hdc,-y+y0,-x+x0,color);
}

void draw_circle(HDC hdc,int x0,int y0,int r,COLORREF color)
{
    int x = 0;
    int y = r;
    int e = 1-r;
    circle_points(hdc,x,y,x0,y0,color);
    while(x<=y)
    {
        if(e<0)
        {
            e += 2*x+3;
        }
        else
        {
            e += 2*(x-y) + 5;
            y--;
        }
        x++;
        circle_points(hdc,x,y,x0,y0,color);
    }
}

struct point
{
    int x,y;
    bool operator < (const point &p) const
    {
        if(x*p.x<0)
        {
            return x<p.x;
        }
        return x*p.y < y*p.x;
    }
};

vector<point> circ;

void add_points(int x0,int y0,int x,int y)
{
    point p;
    int i,j;
    for(i=-1;i<2;i+=2)
    {
        for(j=-1;j<2;j+=2)
        {
            p.x = i*x;
            p.y = j*y;
            circ.push_back(p);
        }
    }
    for(i=-1;i<2;i+=2)
    {
        for(j=-1;j<2;j+=2)
        {
            p.x = i*y;
            p.y = j*x;
            circ.push_back(p);
        }
    }
}

void draw_arc(HDC hdc,int x0,int y0,int r,double ang1,double ang2,COLORREF color)
{
    int i = 0;
    int x = 0;
    int y = r;
    int e = 1-r;
    int x1,y1,x2,y2;
    x1 = round(r*sin(ang1/180.0*M_PI));
    y1 = round(r*cos(ang1/180.0*M_PI));
    x2 = round(r*sin(ang2/180.0*M_PI));
    y2 = round(r*cos(ang2/180.0*M_PI));
    add_points(x0,y0,x,y);
    while(x<=y)
    {
        if(e<0)
        {
            e += 2*x+3;
        }
        else
        {
            e += 2*(x-y) + 5;
            y--;
        }
        x++;
        add_points(x0,y0,x,y);
    }
    cout << circ.size();
    sort(circ.begin(),circ.end());
    for(int i=0;i<circ.size();i++)
    {
        //cout << circ[i].x << ' ' << circ[i].y << endl;
    }
    bool draw = false;
    while(true)
    {
        //cout << i << ' ' << circ[i].x << ' ' << circ[i].y << endl;
        i = (i+1) % circ.size();
        if(x1==circ[i].x && y1==circ[i].y)
        {
            draw = true;
        }
        if(draw)
        {
            SetPixel(hdc,x0+circ[i].x,y0+circ[i].y,color);
        }
        if(circ[i].x==x2 && circ[i].y==y2 && draw==true)
        {
            break;
        }
    }
    circ.clear();
}

vector<point> ecli;

void add_ecli_point(int x,int y)
{
    point p;
    int i,j;
    for(i=-1;i<2;i+=2)
    {
        for(j=-1;j<2;j+=2)
        {
            p.x = i*x;
            p.y = j*y;
            ecli.push_back(p);
        }
    }
}

void draw_eclipse(HDC hdc,int x0,int y0,int a,int b,double ang1,double ang2, COLORREF color)
{
    int aa = a*a,bb = b*b;
    int twoaa = 2*aa, twobb = 2*bb;
    int x = 0,y = b;
    int d;
    int dx = 0;
    int dy = twoaa*y;
    d = int(bb+aa*(-b+0.25)+0.5);
    add_ecli_point(x,y);
    while(dx<dy)
    {
        x++;
        dx += twobb;
        if(d<0)
        {
            d += bb + dx;
        }
        else
        {
            dy -= twoaa;
            d += bb + dx - dy;
            y--;
        }
        add_ecli_point(x,y);
    }
    d = int(bb*(x+0.5)*(x+0.5) + aa*(y-1)*(y-1) - aa*bb + 0.5);
    while(y>0)
    {
        y--;
        dy -= twoaa;
        if(d>0)
        {
            d += aa - dy;
        }
        else
        {
            x++;
            dx += twobb;
            d += aa - dy + dx;
        }
        add_ecli_point(x,y);
    }

    sort(ecli.begin(),ecli.end());
    int x1,y1,x2,y2;
    x1 = round(a*cos(ang1/180.0*M_PI));
    y1 = round(b*sin(ang1/180.0*M_PI));
    x2 = round(a*cos(ang2/180.0*M_PI));
    y2 = round(b*sin(ang2/180.0*M_PI));
    //cout << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << endl;
    bool draw = false;
    int i = 0;
    while(true)
    {
        //cout << i << ' ' << ecli[i].x << ' ' << ecli[i].y << endl;
        i = (i+1) % ecli.size();
        if(x1==ecli[i].x && y1==ecli[i].y)
        {
            draw = true;
        }
        if(draw)
        {
            SetPixel(hdc,x0+ecli[i].x,y0+ecli[i].y,color);
        }
        if(ecli[i].x==x2 && ecli[i].y==y2 && draw==true)
        {
            break;
        }
    }
    ecli.clear();
}

class Polygon
{
private:
    vector<point> p;
    vector<
public:
    void build()
    {

    }
    void clear()
    {
        p.clear();
    }
    void fill_color(HDC hdc,COLORREF color,Polygon p)
    {

    }

    void fill_shade(HDC hdc,COLORREF color,Polygon p)
    {

    }
};

