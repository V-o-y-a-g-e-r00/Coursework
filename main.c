/*  main.c*/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h> //��� getch

#include<string.h> // ��� strcpy � ������
#include "CsFunc.h"
#include "CsPlotFunc.h"


int main(int argc, char *argv[])
{
/* ����� ��������� � ������� ������ */
    system("chcp 1251");
    system("cls");
/*  ����� �������� */
    char filename[128]="Splash.txt";
    char strcatn[2048]={0};
    TxtFromFile(filename, strcatn); //���� �������� � strcatn
    printf("%s\n", strcatn);  //����� �������� �� �����
/*  �������� ���� */
    strcpy(filename, "menu.txt");
    char menustr[2048]={0};
    TxtFromFile(filename, menustr);
/*  �������� ��� ������� ������ �������*/
    int N;
    double U, tstart, t1, t2, tend;
    double a, b, Uin1, Uin2;
    double C, Eps;
    int Nmax;
/*  �������� ��� �������� ������ �������*/
    double *ArrT=NULL;  //NULL ���������, ����� ����� ���� ������������ free() ��� ����������, ������� �� �������� ������
    double *ArrUin;
    ArrUin=NULL;
    double *ArrUout=NULL;
    double dt;

    double W;
    double MeaErW;
/*  ������ ����������*/
 //   int i=0;
    int FormArrFlag=0; // ���� � ������������� ��������.

int choice=0;
char smallbuff[128];
/* �������� ���� */
    while(1)
    {
        printf("%s\n", menustr); //����� ����
        printf("�������� �����:\n");
        fgets(smallbuff, 10, stdin);
//        printf("%s", smallbuff);
        choice=atoi(smallbuff); //������������ 0 � ������ �������
        switch(choice)
        {
/* ���� */
            case 1: // printf("main:�� ������� 1!\n");
                    InputDataFromCons(&N, &U, &tstart, &t1, &t2, &tend, &a, &b, &Uin1, &Uin2, &C, &Eps, &Nmax); break;
            case 2: //printf("main:�� ������� 2!\n");
                    InputDataFromFile(&N, &U, &tstart, &t1, &t2, &tend, &a, &b, &Uin1, &Uin2, &C, &Eps, &Nmax, "InputData.txt"); break;
            case 3: printf("main:�� ������� 3!\n");
                    InputDataFromFileForPlots(&N, &tend, &ArrT, &ArrUin, &ArrUout, "OutputResult.txt", &FormArrFlag);
                    break;
/* ������ */
            case 4:// printf("main:�� ������� 4!\n");
                    printf("����������� ArrT...\n");
                    FormArrT(N, tstart, tend, &ArrT, &dt);
                    printf("����������� ArrUin...\n");
                    FormArrUin(N, U, tstart, t1, t2, tend, ArrT, &ArrUin);
                    printf("����������� ArrUout...\n");
                    FormArrUout(N, a, b, Uin1, Uin2, ArrUin, &ArrUout, &FormArrFlag);
                  //  for(int i=0;i<(N+1);i++) printf("main:ArrT[%d]=%lf\n", i, ArrT[i]); //��������
                 //   for(int i=0;i<(N+1);i++) printf("main:ArrUin[%d]=%lf\n", i, ArrUin[i]); //��������
                 //   for(int i=0;i<(N+1);i++) printf("main:ArrUout[%d]=%lf\n", i, ArrUout[i]); //��������
                    break;
            case 5: //printf("main:�� ������� 5!\n");
                    CalcW(&N, U, tstart, t1, t2, tend, a, b, Uin1, Uin2, C, Eps, Nmax, &ArrT, &ArrUin, &ArrUout, &dt, &FormArrFlag, &W, &MeaErW, 0);
                    break;
/* ����� */
            case 6: //printf("main:�� ������� 6!\n");
                    if(FormArrFlag==1) OutputResultToCons(N, ArrT, ArrUin, ArrUout, dt);
                    else printf("��� ������ ��� ������!\n");
                    break;
            case 7: //printf("main:�� ������� 7!\n");
                    if(FormArrFlag==1) OutputResultToFile(N, ArrT, ArrUin, ArrUout, dt, "OutputResult.txt");
                    else printf("��� ������ ��� ������!\n");
                    break;
            case 8: //printf("main:�� ������� 8!\n");
                    OutputWToFile(N, W, MeaErW, "OutputResult.txt");
                    break;
/* ������� */
            case 9: printf("main:�� ������� 9!\n");
            MainPlotFunc(ArrT, ArrUin, N, tend);
            break;
            case 10: printf("main:�� ������� 10!\n");
            MainPlotFunc(ArrT, ArrUout, N, tend);
            break;
/* ����� */
            case 11: printf("main:�� ������� 11!\n");
            free(ArrT);
            free(ArrUin);
            free(ArrUout);
            return 0;
            break;
/* ������� */
            case 12:// printf("main:�� ������� 12!\n");
                    CalcW(&N, U, tstart, t1, t2, tend, a, b, Uin1, Uin2, C, Eps, Nmax, &ArrT, &ArrUin, &ArrUout, &dt, &FormArrFlag, &W, &MeaErW, 1);
                    break;
            case 13: //printf("main:�� ������� 13!\n");
                    DebOutputCurrentToCons(N, U, tstart, t1, t2, tend, a, b, Uin1, Uin2, C, Eps, Nmax); break;

            default: printf("main:��� ������ ������!\n"); break;
        }
        printf("������� ����� ������� ��� �������� � ����\n");
        getch();
    }

    return 0;
}
