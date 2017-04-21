#include <iostream>
#include <windows.h>

#include "graphic_lib.h"

const COLORREF WHITE = RGB(255,255,255);
const COLORREF RED = RGB(255,0,0);
const COLORREF GREEN = RGB(0,255,0);
const COLORREF BLUE = RGB(0,0,255);

using namespace std;


int main()
{
    HWND hwnd = GetForegroundWindow();
    //CreateWindow("YW","mywindow",WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,NULL,NULL);//
    //ShowWindow(hwnd,SW_NORMAL);
    //
    //cout << "Hello world!" << endl;
    HDC hdc = GetDC(hwnd);
    draw_line(hdc,100,100,500,200,WHITE);
    draw_line(hdc,200,200,500,200,WHITE);
    draw_line(hdc,300,300,500,200,WHITE);
    draw_line(hdc,400,400,500,200,WHITE);
    draw_line(hdc,450,100,500,200,WHITE);
    draw_line(hdc,600,200,500,200,WHITE);
    draw_line(hdc,500,300,500,200,WHITE);

    draw_circle(hdc,200,200,50,RED);
    draw_arc(hdc,500,200,40,30,90,RED);

    draw_eclipse(hdc,700,200,100,50,30,180,BLUE);
    //cout << sin(30/180.0*M_PI);
    Polygon poly;

    //UpdateWindow(hwnd);
    return 0;
}
