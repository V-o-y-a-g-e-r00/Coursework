/*  CsPlotFunc.c*/
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <strings.h>
#include "CsPlotFunc.h"

#define SDL_SCREEN_WIDTH  500
#define SDL_SCREEN_HEIGHT  500
#define LABELSCOUNT 10 //число промежутков для y
#define LABELSCOUNT_ADD 50
void DrawCurve(double *ArrT, double *ArrU, int N, double tend, double Umax, int winW, int winH, SDL_Renderer *r)
{
    SDL_SetRenderDrawColor(r, 255, 0, 0, 255);
    int i;
    int winX1, winY1, winX2, winY2;
    xyTowinXwinY(ArrT[0], ArrU[0], tend, Umax, &winX1, &winY1, winW, winH);
    printf("winX1=%d winY1=%d\n",winX1, winY1);
    printf("ArrT[0]=%lf\n", ArrT[0]);
    for(i=1;i<(N+1);i++)
    {
        xyTowinXwinY(ArrT[i], ArrU[i], tend, Umax, &winX2, &winY2, winW, winH);
 //       printf("winX2=%d winY2=%d\n",winX2, winY2);
        SDL_RenderSetScale(r, 1, 1);
        SDL_RenderDrawLine(r, winX1, winY1, winX2, winY2);
        winX1=winX2;
        winY1=winY2;
    }
}
void CalcUmax(double *ArrU, int N, double *Umax)
{
    int i;
    *Umax=ArrU[0];
    for(i=0; i<(N+1); i++) if(*Umax<ArrU[i]) *Umax=ArrU[i];
    *Umax=*Umax*1.1; //немного скорректируем, чтобы было пространство сверху
    printf("Umax=%lf", *Umax);
}
void FormArrLablesx(double Xmax, double Ymax, int N, char **ArrText)
{
 //   double dx;
    double cx=0;
  //  int j=Xmax/N;
    for(int i=0;i< LABELSCOUNT_ADD ; i++)
    {
        sprintf(ArrText[i], "%1.0lf", cx);
        //ArrText[i]='1';
        printf("ArrText=%s\n", ArrText[i]);
        cx+=5; //Будем выводить шагом в 5
    }
}
void FormArrLablesy(double Xmax, double Ymax, int N, char **ArrText)
{
    double dy=Ymax/N;
    double dx=Xmax/N;
    double cx=0, cy=0;
     printf("Ly:Ymax=%lf\n", Ymax);
    for(int i=0;i<(N+1); i++)
    {
        sprintf(ArrText[i], "%1.1lf", cy);
        //ArrText[i]='1';
        printf("Ly:ArrText=%s\n", ArrText[i]);
        cx+=dx;
        cy+=dy;
    }
}
void xyTowinXwinY(double x, double y, double xmax, double ymax, int *winX, int *winY, int winW, int winH)
{
    *winX=(int)(x*0.9*(double)winW/(double)xmax+(double)winW*0.1);
    *winY=(int)(y*(-(double)winH*0.9/(double)ymax)+(double)winH*0.9);
}
void PlotAxes(SDL_Renderer *r, int winW, int winH)
{
    SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
    SDL_RenderDrawLine(r, 0, winH*0.9 , winW, winH*0.9); //ось ox
    SDL_RenderDrawLine(r, winW*0.1 , 0, winW*0.1, winH); //ось oy
}
void PlotSetOneLabel(SDL_Renderer *r, SDL_Texture **texture, SDL_Rect *rect, TTF_Font *font, int Labelx, int Labely,  char *ArrTextEl)
{
    int text_width;
    int text_height;
    SDL_Surface *surface;
    SDL_Color textColor = {0, 0, 0, 255};

    surface = TTF_RenderText_Solid(font, ArrTextEl, textColor);
    SDL_DestroyTexture(*texture);
    *texture = SDL_CreateTextureFromSurface(r, surface);
    text_width = surface->w;
    text_height = surface->h;
    SDL_FreeSurface(surface);
    rect->x = Labelx;
    rect->y = Labely;
    rect->w = text_width;
    rect->h = text_height;
}
void PlotSetAndCopyLabelsx(SDL_Renderer *r, TTF_Font *font, int winW, int winH,  char **ArrText, SDL_Texture **texture1, SDL_Rect *rect1, double xmax)
{
    int dx;
    int winY; //требуется для работы xyTowinXwinY
    int xnul;
    xyTowinXwinY(5, 5, xmax, 0, &dx, &winY, winW, winH);
    xyTowinXwinY(0, 0, xmax, 0, &xnul, &winY, winW, winH);
    dx=dx-xnul;
    int i;
    int Labelx;
    int Labely;
    xyTowinXwinY(0, 0, xmax, 0, &Labelx, &Labely, winW, winH);
    for(i=0;i< LABELSCOUNT_ADD ;i++)
    {
        PlotSetOneLabel(r, texture1, rect1, font, Labelx, 0.9*winH, ArrText[i]);
        SDL_RenderCopy(r, *texture1, NULL, rect1);
        printf("Labelx=%d\n", Labelx);
        Labelx+=dx;
    }
}
void PlotSetAndCopyLabelsy(SDL_Renderer *r, TTF_Font *font, int winW, int winH,  char **ArrText, SDL_Texture **texture1, SDL_Rect *rect1)
{

   // int dx=winW*0.9/ LABELSCOUNT ;
    int dy=winH*0.9/ LABELSCOUNT ;
    int i;
    int Labelx=0;
    int Labely=0.9*winH;
    for(i=0;i< LABELSCOUNT +1;i++)
    {
        PlotSetOneLabel(r, texture1, rect1, font, Labelx, Labely, ArrText[i]);
        SDL_RenderCopy(r, *texture1, NULL, rect1);
        Labely-=dy;
    }
}
int MainPlotFunc(double *ArrT, double *ArrU, int N, double tend)
{
    tend=tend*1.1; //небольшая коррекция, чтобы было пространство справа
    /*  Инициализация SDL*/
     if( SDL_Init( SDL_INIT_EVERYTHING ) != 0 )
    {
        printf("SDL could not init!");
        return 1;
    }
    SDL_Window* window = NULL;
    window = SDL_CreateWindow("CourseWorkPlot",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SDL_SCREEN_WIDTH, SDL_SCREEN_HEIGHT, SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE); //инициализируем окно(указатель)
    if (window == NULL) {
        printf("Cannot open the window!\n");
        return 1;
    }
    SDL_Renderer *r = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); //инициализация рендерера -1 будет использоваться первый подходящий драйвер SDL_RENDERER_ACCELERATED будет использоваться ускорение
    if (r == NULL)
    {
        printf("SDL_CreateRenderer Error\n");
        return 1;
    }
/*  Рисуем SDL*/
/*  Заливаем область цветом*/
    SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
    SDL_RenderClear(r);
/*  Получаем размер окна*/
    int winW, winH;
    SDL_Surface *SurfWH=SDL_GetWindowSurface(window);
    winW=SurfWH->w;
    winH=SurfWH->h;
    SDL_FreeSurface(SurfWH);
/*  Рисуем оси*/
    PlotAxes(r, winW, winH);
/*  Инициализируем SDL_ttf*/
    TTF_Init();

    TTF_Font* font = TTF_OpenFont("FreeSans.ttf", 14); //this opens a font style and sets a size
    if (font == NULL)
    {
        printf("TTF_OpenFont Error\n");
        return 1;
    }
    else
    {
        printf("TTF_OpenFont success\n");
    }
/*  Рисуем цифры*/
    char **ArrText; //будет заполянтся автоматически
    ArrText=(char **)malloc(sizeof(char *)*( LABELSCOUNT_ADD +1));
    for(int i=0; i< LABELSCOUNT_ADD +1; i++) ArrText[i]=(char *)malloc(sizeof(char)*128); //не забыть освободить но после выхода из цикла SDL

    for(int i=0; i< LABELSCOUNT_ADD +1; i++)
    {
        ArrText[i][0]='1';
        ArrText[i][1]='\0';
        printf("ArrText=%s", ArrText[i]);
    }
    double Umax;
    CalcUmax(ArrU, N, &Umax);
    FormArrLablesx(tend, Umax, LABELSCOUNT , ArrText);
    SDL_Texture *texture1=NULL;
    SDL_Rect rect1;
    int winX, winY;
    xyTowinXwinY(0, 0, 100, 100, &winX, &winY, winW, winH);
    printf("\nwinX=%d winY=%d winW*0.1=%d winH*0.9=%d", winX, winY, (int)(winW*0.1), (int)(winH*0.9));
   // PlotSetOneLabel(r, &texture1, &rect1, font, winX, winY, ArrText[0]);
  //  SDL_RenderCopy(r, texture1, NULL, &rect1);

    PlotSetAndCopyLabelsx(r, font, winW, winH, ArrText, &texture1, &rect1, tend);

    printf("Umax=%lf", Umax);
    FormArrLablesy(tend, Umax, LABELSCOUNT , ArrText);
    PlotSetAndCopyLabelsy(r, font, winW, winH, ArrText, &texture1, &rect1);

  //  for(int i=0; i< LABELSCOUNT_ADD +1; i++) free(ArrText[i]);
 //   free(ArrText);
    SDL_DestroyTexture(texture1);
// ////////////////
/*  Рисуем кривую*/

    DrawCurve(ArrT, ArrU, N, tend, Umax, winW, winH, r);

    SDL_RenderPresent(r);
/*  Пошел основной цикл SDL*/
    int quit = 0;
    SDL_Event e;
    while(!quit)
    {
    //  printf("%d", SDL_PollEvent(&e));
        while(SDL_PollEvent(&e) != 0) //SDL_PollEvent(SDL_Event * event) возвращает 1 если в очереди есть события и 0 если нет. Сохраняет событие в структуре event.
        {
            switch (e.type)
            {
            case SDL_QUIT:
                quit = 1;
                break;
            case SDL_WINDOWEVENT:
                if (e.window.event == SDL_WINDOWEVENT_RESIZED)
                {
                    printf("window resized!");
/* засовываем сюда все что сверху*/
 //   SDL_DestroyRenderer(r); //А вот этого делать не надо: устройство само попытается это сделать. Иначе будут вылеты

  //  SDL_Renderer *r = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); //инициализация рендерера -1 будет использоваться первый подходящий драйвер SDL_RENDERER_ACCELERATED будет использоваться ускорение
    if (r == NULL)
    {
        printf("SDL_CreateRenderer Error\n");
        return 1;
    }
/*  Рисуем SDL*/
/*  Заливаем область цветом*/
    SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
    SDL_RenderClear(r);
    SDL_RenderClear(r);
/*  Получаем размер окна*/
    int winW, winH;
    SDL_Surface *SurfWH=SDL_GetWindowSurface(window);
    winW=SurfWH->w;
    winH=SurfWH->h;
    SDL_FreeSurface(SurfWH);
    SDL_RenderClear(r);
/*  Рисуем оси*/
    PlotAxes(r, winW, winH);
/*  Инициализируем SDL_ttf*/
//Мы уже один раз инициализировали, больше не надо
/*  Рисуем цифры*/
 //   char **ArrText; //будет заполянтся автоматически
 //   ArrText=(char **)malloc(sizeof(char *)*( LABELSCOUNT +1));
 //   for(int i=0; i< LABELSCOUNT +1; i++) ArrText[i]=(char *)malloc(sizeof(char)*128); //не забыть освободить но после выхода из цикла SDL

    for(int i=0; i< LABELSCOUNT +1; i++)
    {
        ArrText[i][0]='1';
        ArrText[i][1]='\0';
        printf("ArrText=%s", ArrText[i]);
    }
    double Umax;
    CalcUmax(ArrU, N, &Umax);
    FormArrLablesx(tend, Umax, LABELSCOUNT_ADD , ArrText);
    SDL_Texture *texture1=NULL;
    SDL_Rect rect1;
    int winX, winY;
    xyTowinXwinY(0, 0, 100, 100, &winX, &winY, winW, winH);
    printf("\nwinX=%d winY=%d winW*0.1=%d winH*0.9=%d", winX, winY, (int)(winW*0.1), (int)(winH*0.9));
   // PlotSetOneLabel(r, &texture1, &rect1, font, winX, winY, ArrText[0]);
  //  SDL_RenderCopy(r, texture1, NULL, &rect1);

    PlotSetAndCopyLabelsx(r, font, winW, winH, ArrText, &texture1, &rect1, tend);

    printf("Umax=%lf", Umax);
    FormArrLablesy(tend, Umax, LABELSCOUNT , ArrText);
    PlotSetAndCopyLabelsy(r, font, winW, winH, ArrText, &texture1, &rect1);

 //   for(int i=0; i< LABELSCOUNT +1; i++) free(ArrText[i]);
 //   free(ArrText);
    SDL_DestroyTexture(texture1);
// ////////////////
/*  Рисуем кривую*/
//SDL_RenderPresent(r);
//SDL_Delay(500);
SDL_RenderSetScale(r, 10, 10);
    DrawCurve(ArrT, ArrU, N, tend, Umax, winW, winH, r);
// /////////////////////////////////////////
              //     SDL_RenderPresent(r);
                }
                break;
            }
        }
       // SDL_UpdateWindowSurface(window);
        SDL_RenderPresent(r);
        SDL_Delay(10); // небольшая задержка, чтобы не тратить ресурсы процессора
    }
 //   SDL_Delay(500);
// /////////////////////////////
/*  Закрываем окно и разынизиализируем все*/
    for(int i=0; i< LABELSCOUNT_ADD +1; i++) free(ArrText[i]);
    free(ArrText);
    SDL_DestroyWindow(window); //
    SDL_Quit(); //освобождение указателей
    return 0;
}

