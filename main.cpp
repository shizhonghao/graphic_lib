#include <iostream>
#include <windows.h>

#include "graphic_lib.h"

const COLORREF WHITE = RGB(255,255,255);
const COLORREF RED = RGB(255,0,0);
const COLORREF GREEN = RGB(0,255,0);
const COLORREF BLUE = RGB(0,0,255);
const COLORREF GREY = RGB(50,50,50);

using namespace std;

int pat[10][10];
int main()
{
    HWND hwnd = GetForegroundWindow();
    //CreateWindow("YW","mywindow",WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,NULL,NULL);//
    //ShowWindow(hwnd,SW_NORMAL);
    //
    //cout << "Hello world!" << endl;
    HDC hdc = GetDC(hwnd);/*
    draw_line(hdc,100,100,500,200,WHITE);
    draw_line(hdc,200,200,500,200,WHITE);
    draw_line(hdc,300,300,500,200,WHITE);
    draw_line(hdc,400,400,500,200,WHITE);
    draw_line(hdc,450,100,500,200,WHITE);
    draw_line(hdc,600,200,500,200,WHITE);
    draw_line(hdc,500,300,500,200,WHITE);
*/
    draw_circle(hdc,150,150,50,GREEN);
    draw_arc(hdc,500,200,40,30,90,RED);

    //cout << sin(30/180.0*M_PI);


    draw_line(hdc,50,200,70,230,WHITE);
    draw_line(hdc,10,250,120,250,WHITE);
    draw_line(hdc,50,250,10,420,WHITE);
    //draw_line(hdc,40,300,90,300,WHITE);
    //draw_line(hdc,90,420,90,300,WHITE);
    draw_eclipse(hdc,40,370,50,70,70,270,BLUE);
    draw_line(hdc,170,200,130,290,WHITE);
    draw_line(hdc,250,240,150,240,WHITE);
    draw_line(hdc,110,340,230,300,WHITE);
    draw_line(hdc,230,300,230,370,WHITE);
    draw_line(hdc,180,270,180,390,WHITE);
    draw_line(hdc,140,290,140,420,WHITE);
    draw_line(hdc,140,420,250,420,WHITE);

    draw_line(hdc,400,440,400,200,WHITE);
    polygon *poly = new polygon;
    poly->add_point(300,250);
    poly->add_point(300,340);
    poly->add_point(500,340);
    poly->add_point(500,250);
    poly->build(hdc,WHITE);
    for(int i=0;i<10;i++)
    {
        pat[5][i] = 1;
    }
    poly->set_pattern(10,10,(int*)pat);
    poly->fill_shade(hdc,GREY);
    //UpdateWindow(hwnd);

    poly = new polygon;
    poly->add_point(600,210);
    poly->add_point(600,270);
    poly->add_point(740,270);
    poly->add_point(740,210);
    poly->build(hdc,WHITE);
    poly->fill_color(hdc,GREY);
    draw_line(hdc,600,240,740,240,WHITE);
    draw_line(hdc,570,310,770,310,WHITE);
    draw_line(hdc,550,350,790,350,WHITE);

    draw_arc(hdc,550,310,120,0,90,RED);
    draw_arc(hdc,790,310,120,270,0,RED);


    return 0;
}
