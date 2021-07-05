/*  CsPlotFunc.h*/
#ifndef CSPLOTFUNC_H_INCLUDED
#define CSPLOTFUNC_H_INCLUDED




#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <strings.h>

#define SDL_SCREEN_WIDTH  500
#define SDL_SCREEN_HEIGHT  500
#define LABELSCOUNT 10 //число промежутков
void DrawCurve(double *ArrT, double *ArrU, int N, double tend, double Umax, int winW, int winH, SDL_Renderer *r);

void CalcUmax(double *ArrU, int N, double *Umax);

void FormArrLablesx(double Xmax, double Ymax, int N, char **ArrText);
void FormArrLablesy(double Xmax, double Ymax, int N, char **ArrText);

void xyTowinXwinY(double x, double y, double xmax, double ymax, int *winX, int *winY, int winW, int winH);

void PlotAxes(SDL_Renderer *r, int winW, int winH);

void PlotSetOneLabel(SDL_Renderer *r, SDL_Texture **texture, SDL_Rect *rect, TTF_Font *font, int Labelx, int Labely,  char *ArrTextEl);

void PlotSetAndCopyLabelsx(SDL_Renderer *r, TTF_Font *font, int winW, int winH,  char **ArrText, SDL_Texture **texture1, SDL_Rect *rect1, double xmax);

void PlotSetAndCopyLabelsy(SDL_Renderer *r, TTF_Font *font, int winW, int winH,  char **ArrText, SDL_Texture **texture1, SDL_Rect *rect1);

int MainPlotFunc(double *ArrT, double *ArrU, int N, double tend);



#endif // CSPLOTFUNC_H_INCLUDED
