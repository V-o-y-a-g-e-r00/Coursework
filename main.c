/*  main.c*/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h> //для getch

#include<string.h> // для strcpy и других
#include "CsFunc.h"
#include "CsPlotFunc.h"


int main(int argc, char *argv[])
{
/* Смена кодировки и очистка экрана */
    system("chcp 1251");
    system("cls");
/*  Вывод заставки */
    char filename[128]="Splash.txt";
    char strcatn[2048]={0};
    TxtFromFile(filename, strcatn); //Ввод заставки в strcatn
    printf("%s\n", strcatn);  //вывод заставки на экран
/*  Загрузка меню */
    strcpy(filename, "menu.txt");
    char menustr[2048]={0};
    TxtFromFile(filename, menustr);
/*  Величины для входных данных расчета*/
    int N;
    double U, tstart, t1, t2, tend;
    double a, b, Uin1, Uin2;
    double C, Eps;
    int Nmax;
/*  Величины для выходных данных расчета*/
    double *ArrT=NULL;  //NULL необходим, чтобы можно было использовать free() для указателей, которым не выделена память
    double *ArrUin;
    ArrUin=NULL;
    double *ArrUout=NULL;
    double dt;

    double W;
    double MeaErW;
/*  Прочие переменные*/
 //   int i=0;
    int FormArrFlag=0; // флаг о существовании массивов.

int choice=0;
char smallbuff[128];
/* Основной цикл */
    while(1)
    {
        printf("%s\n", menustr); //вывод меню
        printf("Выберете пункт:\n");
        fgets(smallbuff, 10, stdin);
//        printf("%s", smallbuff);
        choice=atoi(smallbuff); //возвращается 0 в случае неудачи
        switch(choice)
        {
/* Ввод */
            case 1: // printf("main:Вы выбрали 1!\n");
                    InputDataFromCons(&N, &U, &tstart, &t1, &t2, &tend, &a, &b, &Uin1, &Uin2, &C, &Eps, &Nmax); break;
            case 2: //printf("main:Вы выбрали 2!\n");
                    InputDataFromFile(&N, &U, &tstart, &t1, &t2, &tend, &a, &b, &Uin1, &Uin2, &C, &Eps, &Nmax, "InputData.txt"); break;
            case 3: printf("main:Вы выбрали 3!\n");
                    InputDataFromFileForPlots(&N, &tend, &ArrT, &ArrUin, &ArrUout, "OutputResult.txt", &FormArrFlag);
                    break;
/* Расчет */
            case 4:// printf("main:Вы выбрали 4!\n");
                    printf("Формируется ArrT...\n");
                    FormArrT(N, tstart, tend, &ArrT, &dt);
                    printf("Формируется ArrUin...\n");
                    FormArrUin(N, U, tstart, t1, t2, tend, ArrT, &ArrUin);
                    printf("Формируется ArrUout...\n");
                    FormArrUout(N, a, b, Uin1, Uin2, ArrUin, &ArrUout, &FormArrFlag);
                  //  for(int i=0;i<(N+1);i++) printf("main:ArrT[%d]=%lf\n", i, ArrT[i]); //проверка
                 //   for(int i=0;i<(N+1);i++) printf("main:ArrUin[%d]=%lf\n", i, ArrUin[i]); //проверка
                 //   for(int i=0;i<(N+1);i++) printf("main:ArrUout[%d]=%lf\n", i, ArrUout[i]); //проверка
                    break;
            case 5: //printf("main:Вы выбрали 5!\n");
                    CalcW(&N, U, tstart, t1, t2, tend, a, b, Uin1, Uin2, C, Eps, Nmax, &ArrT, &ArrUin, &ArrUout, &dt, &FormArrFlag, &W, &MeaErW, 0);
                    break;
/* Вывод */
            case 6: //printf("main:Вы выбрали 6!\n");
                    if(FormArrFlag==1) OutputResultToCons(N, ArrT, ArrUin, ArrUout, dt);
                    else printf("Нет данных для вывода!\n");
                    break;
            case 7: //printf("main:Вы выбрали 7!\n");
                    if(FormArrFlag==1) OutputResultToFile(N, ArrT, ArrUin, ArrUout, dt, "OutputResult.txt");
                    else printf("Нет данных для вывода!\n");
                    break;
            case 8: //printf("main:Вы выбрали 8!\n");
                    OutputWToFile(N, W, MeaErW, "OutputResult.txt");
                    break;
/* Графики */
            case 9: printf("main:Вы выбрали 9!\n");
            MainPlotFunc(ArrT, ArrUin, N, tend);
            break;
            case 10: printf("main:Вы выбрали 10!\n");
            MainPlotFunc(ArrT, ArrUout, N, tend);
            break;
/* Выход */
            case 11: printf("main:Вы выбрали 11!\n");
            free(ArrT);
            free(ArrUin);
            free(ArrUout);
            return 0;
            break;
/* Отладка */
            case 12:// printf("main:Вы выбрали 12!\n");
                    CalcW(&N, U, tstart, t1, t2, tend, a, b, Uin1, Uin2, C, Eps, Nmax, &ArrT, &ArrUin, &ArrUout, &dt, &FormArrFlag, &W, &MeaErW, 1);
                    break;
            case 13: //printf("main:Вы выбрали 13!\n");
                    DebOutputCurrentToCons(N, U, tstart, t1, t2, tend, a, b, Uin1, Uin2, C, Eps, Nmax); break;

            default: printf("main:Нет такого пункта!\n"); break;
        }
        printf("Нажмите любую клавишу для возврата в меню\n");
        getch();
    }

    return 0;
}
