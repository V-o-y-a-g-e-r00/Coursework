/*  CsFunc.c*/
#include <stdio.h>
#include <stdlib.h> //atoi
#include <string.h>
#include <math.h>
#include <conio.h> //��� getch

#include "CsFunc.h"
#include "CsPlotFunc.h"
#define DATACOUNT 13 //����� �������� �������
void TxtFromFile(char *filename, char *strcatn) //filename ��� ��� ���� � �����. strcatn �����, ���� ���������� ���� ���� �������
{
    int i=0;    //������� �����
    char buff[2048]={0};    //����� ��� ���������� ������
    FILE *fin=fopen(filename, "rb");
    if(fin!=NULL)
    {
        while (!feof (fin))
        {
            if ( !feof(fin))    // ��� ��������� ��������� ������ ������ feof
            {
                i=i+1;
                fgets(buff, 127, fin);
                strcat(strcatn, buff);
             //   printf("%s string count=%d\n", buff, i);
            }
        }
//        printf("strcatn=%s", strcatn);
    }
    else printf("TxtFromFile:Cannot open %s", filename);
    fclose(fin);
}
void InputIntFromCons(int *a, char *name) // ���������� InputDoubleFromCons
{
    char buff[128];
    while(1)
    {
        printf("������� %s:", name); //printf("Input %s:", name);
        fgets(buff, 127, stdin); //
        char *c = strchr(buff, '\n');     /* ���� ������ �\n� � ����������� ������ */
        if(c != NULL) *c = '\0';          /* ������ ������� �\0������� ������� �\n� */
        int i=strspn(buff, "+-1234567890"); /* ����� ��������� ���������, � ���������� ��������� strspn substring pointer number */
        if(i==strlen(buff))
        {
            *a=atoi(buff);
            return;
        }
        else printf("������������ �������! ������� %s ������!\n", name);//printf("Unacceptable symbols! Input %s again!\n", name);
    }
}
void InputDoubleFromCons(double *a, char *name)
{
    char buff[128];
    while(1)
    {
        printf("������� %s:", name); //printf("Input %s:", name);
        fgets(buff, 127, stdin); //
        char *c = strchr(buff, '\n');     /* ���� ������ �\n� � ����������� ������ */
        if(c != NULL) *c = '\0';          /* ������ ������� �\0������� ������� �\n� */
        int i=strspn(buff, "eE+-.1234567890"); /* ����� ��������� ���������, � ���������� ��������� strspn substring pointer number */
        if(i==strlen(buff))
        {
            *a=atof(buff);
            return;
        }
        else printf("������������ �������! ������� %s ������!\n", name); //printf("Unacceptable symbols! Input %s again!\n", name);
    }
}
/* ����� 1 ���� */
void InputDataFromCons(int *N, double *U, double *tstart, double *t1, double *t2, double *tend, double *a, double *b, double *Uin1, double *Uin2, double *C, double *Eps, int *Nmax)
{
    InputIntFromCons(N, "N");

    InputDoubleFromCons(U, "U");
    InputDoubleFromCons(tstart, "tstart");
    InputDoubleFromCons(t1, "t1");
    InputDoubleFromCons(t2, "t2");
    InputDoubleFromCons(tend, "tend");

    InputDoubleFromCons(a, "a");
    InputDoubleFromCons(b, "b");
    InputDoubleFromCons(Uin1, "Uin1");
    InputDoubleFromCons(Uin2, "Uin2");

    InputDoubleFromCons(C, "C");
    InputDoubleFromCons(Eps, "Eps");
    InputIntFromCons(Nmax, "Nmax");
}
/* ����� 2 ���� */
void InputDataFromFile(int *N, double *U, double *tstart, double *t1, double *t2, double *tend, double *a, double *b, double *Uin1, double *Uin2, double *C, double *Eps, int *Nmax, char *filename)
{
    int i=0, j=0, k;    //i ������� ����� j ������� ����� ��� ������������
    char smallbuff[2048]={0}; //����� ��� ����� ������
    char buff[DATACOUNT][2048]={0};    //����� ��� ���� ����� ��� ����� #
    FILE *fin=fopen(filename, "rb");
    if(fin!=NULL)
    {
        while (!feof (fin))
        {
            if ( !feof(fin))    // ��� ��������� ��������� ������ ������ feof
            {
                i=i+1;
                fgets(smallbuff, 127, fin);
                char *c=strchr(smallbuff, '\n');    // ������� '\n' � ����� ������.
                if (c!=NULL) *c='\0';
                if(smallbuff[0]!='#')
                {
                    strcpy(buff[j], smallbuff);
                    j++;
                    if(j>=DATACOUNT) break; //���� ����� ����� ��� ������������ (������ ��� �����) ����� ����������.

                }
             //   printf("%s string count=%d\n", buff, i);
            }
        }
//        printf("strcatn=%s", strcatn);

        for(k=0; k<j; k++) printf("buff[%d][]=%s\n", k, buff[k]); //�������� ����, ��� ��������� � ������� �����

/* ��������� �� ������� ����� */
        *N=atoi(buff[0]);

        *U=atof(buff[1]);
        *tstart=atof(buff[2]);
        *t1=atof(buff[3]);
        *t2=atof(buff[4]);
        *tend=atof(buff[5]);

        *a=atof(buff[6]);
        *b=atof(buff[7]);
        *Uin1=atof(buff[8]);
        *Uin2=atof(buff[9]);

        *C=atof(buff[10]);
        *Eps=atof(buff[11]);
        *Nmax=atoi(buff[12]);
    }
    else printf("TxtFromFile:Cannot open %s", filename);
    fclose(fin);
}
/* ����� 3 ���� */
void InputDataFromFileForPlots(int *N, double *tend, double **ArrT, double **ArrUin, double **ArrUout, char *filename, int *FormArrFlag)
{
    *FormArrFlag=1;
    int i=0, j=0, k;    //i ������� ����� j ������� ����� ��� ������������
    char smallbuff[2048]={0}; //����� ��� ����� ������
//    char buff[DATACOUNT][2048]={0};    //����� ��� ���� ����� ��� ����� #
    FILE *fin=fopen(filename, "rb");
    if(fin!=NULL)
    {
        while (!feof (fin)) //��� ��������� N
        {
            if ( !feof(fin))    // ��� ��������� ��������� ������ ������ feof
            {
                i=i+1;
                fgets(smallbuff, 127, fin);
                char *c=strchr(smallbuff, '\n');    // ������� '\n' � ����� ������.
                if (c!=NULL) *c='\0';
                if(smallbuff[0]!='#')
                {
                    sscanf(smallbuff, "%d", N);
                    break;

                }
            }
        }
        printf("N=%d\n", *N);
        free(*ArrT); //����������� ������, ���� ������ ��� ��� ���� ��������
        free(*ArrUin);
        free(*ArrUout);

        *ArrT=(double *)malloc(sizeof(double)*(*N+1)); //�������� ������
        *ArrUin=(double *)malloc(sizeof(double)*(*N+1));
        *ArrUout=(double *)malloc(sizeof(double)*(*N+1));
        while (!feof (fin)) //��� ������ � ������� ArrT ArrUin ArrUout
        {
            if ( !feof(fin))    // ��� ��������� ��������� ������ ������ feof
            {
                i=i+1;
                fgets(smallbuff, 127, fin);
                char *c=strchr(smallbuff, '\n');    // ������� '\n' � ����� ������.
                if (c!=NULL) *c='\0';
                if(smallbuff[0]!='#')
                {
                    sscanf(smallbuff, "%*d%lf%lf%lf", &(*ArrT)[j], &(*ArrUin)[j], &(*ArrUout)[j]); //������ �������� ��� �����, ��� �����������
                    j++;
                    if(j>=(*N+1)) break; //���� ����� ����� ��� ������������ (������ ��� �����) ����� ���������.

                }
             //   printf("%s string count=%d\n", buff, i);
            }
        }
//        printf("strcatn=%s", strcatn);

        for(k=0; k<j; k++) printf("ArrT[%d]=%lf\tArrUin[%d]=%lf\tArrUout[%d]=%lf\n", k, (*ArrT)[k], k, (*ArrUin)[k], k, (*ArrUout)[k]); //�������� ����, ��� ��������� � ������� �����
    }
    else printf("TxtFromFile:Cannot open %s", filename);
    fclose(fin);
/*  ��� �������� �������� tend ��� ����� ��� ������ ������ ��� ��������*/
    *tend=(*ArrT)[*N];
    printf("tend=%lf\n", *tend);
}

/* ����� 4 ���� */
void FormArrT(int N, double tstart, double tend, double **ArrT, double *dt) // ��������� �� ��������� �����, ����� �� ����� �������� ��������� (����� �� ������ �����������, � ������ �� ����������)
{
    int i;
    double currT=tstart;
    free(*ArrT);        //���� �� �������� ������� ��������, �� ������� ������� ������ ����� ����������
    *ArrT=(double *)malloc(sizeof(double)*(N+1)); //�������������� ��������� �� ��������� � ��������� � �������
    *dt=(tend-tstart)/N;
    for(i=0;i<(N+1);i++)
    {
       // *(*ArrT+i)=currT; // ��� ��������� �������� ������� �������� ���� �����. ��� ������ � ������ ���� ������������ ���� ����� �� ������
        (*ArrT)[i]=currT; //��������������
        currT=currT+*dt;
    }
//    for(i=0;i<(N+1);i++) printf("(*ArrT)[%d]=%lf\n", i, (*ArrT)[i]); //��������
}
void FormArrUin(int N, double U, double tstart, double t1, double t2, double tend, double *ArrT, double **ArrUin)
{
    int i;
    free(*ArrUin);
    *ArrUin=(double *)malloc(sizeof(double)*(N+1));

    for(i=0;i<(N+1);i++)
    {
        if((tstart<=ArrT[i]) && (ArrT[i]<=t1)) (*ArrUin)[i]=0;
        if((t1<ArrT[i]) && (ArrT[i]<=t2)) (*ArrUin)[i]=U/(t2-t1)*(ArrT[i])-U*t1/(t2-t1);
        if((t2<ArrT[i]) && (ArrT[i]<=tend)) (*ArrUin)[i]=U/(t2-tend)*(ArrT[i])-U*tend/(t2-tend);
    }
// for(i=0;i<(N+1);i++) printf("(*ArrUin)[%d]=%lf\n", i, (*ArrUin)[i]); //��������

}
void FormArrUout(int N, double a, double b, double Uin1, double Uin2, double *ArrUin, double **ArrUout, int *FormArrFlag)
{
    *FormArrFlag=1; //������������� ����
    int i;
    free(*ArrUout);
    *ArrUout=(double *)malloc(sizeof(double)*(N+1));

    for(i=0;i<(N+1);i++)
    {
        if(ArrUin[i]<=Uin1) (*ArrUout)[i]=a*Uin1+b;
        if((Uin1<ArrUin[i])&&(ArrUin[i]<=Uin2)) (*ArrUout)[i]=a*ArrUin[i]+b;
    if(ArrUin[i]>Uin2) (*ArrUout)[i]=a*Uin2+b;
    }
// for(i=0;i<(N+1);i++) printf("(*ArrUout)[%d]=%lf\n", i, (*ArrUout)[i]); //��������
//for(i=0;i<(N+1);i++) printf("FormArrUout:(*ArrUin)[%d]=%lf\n", i, ArrUin[i]); //��������

}
/* ����� 5 ���� */
void CalcW(int *N, double U, double tstart, double t1, double t2, double tend, double a, double b, double Uin1, double Uin2, double C, double Eps, int Nmax, double **ArrT, double **ArrUin, double **ArrUout, double *dt, int *FormArrFlag, double *W, double *MeaErW, int DebFlag)
{
    int Nstart=*N; // ����������� ��� �����������, ��������� �� W ���� �� 1 ��� � ���� �� 2 ����
    *MeaErW=Eps+1; // ����� ������ ��� ����� � ����
    double Wold;
    double Umax, CUmax; //CUmax ����� ��� �����������
    int i; //�������
    int K; //�������� ��� ���������� �����������
    while((*N<Nmax) &&(*MeaErW>Eps))
    {
        FormArrT(*N, tstart, tend, ArrT, dt);
        FormArrUin(*N, U, tstart, t1, t2, tend, *ArrT, ArrUin);
        FormArrUout(*N, a, b, Uin1, Uin2, *ArrUin, ArrUout, FormArrFlag);
/*  ������� Umax*/
        Umax=(*ArrUout)[0]; //�������������� Umax
        for(i=0;i<(*N+1);i++) if(Umax<(*ArrUout)[i]) Umax=(*ArrUout)[i];

        CUmax=C*Umax;

/*  ������� K*/
        K=0;
        for(i=0;i<(*N+1);i++) if((*ArrUout)[i]>CUmax) K++;
/*  ������� W*/
        Wold=*W; //��������� ������ �������� W
        *W=K/(double)(*N+1);
/*  ������� MeaErW*/
        if(*N!=Nstart) *MeaErW=fabs(*W-Wold);
/*  ����� ��� ��������*/
        OutputResultToCons(*N, *ArrT, *ArrUin, *ArrUout, *dt);
        printf("K=%d\n", K);
        printf("Umax=%lf\n", Umax);
        printf("CUmax=%lf\n", CUmax);
        printf("N=%d\n", *N);
        printf("W=%lf\n", *W);
        printf("MeaErW=%lf\n", *MeaErW);
        if(DebFlag==1) //��� ������ �������
        {
            printf("������� ����� ������� ��� �����������\n");
            getch();
        }

        *N=*N*2;
    }
    if(*N!=Nstart) *N=*N/2; //������������ ��������� ���������� N
/*  ������� ��������� */
    if(*MeaErW<Eps) printf("�������������� \t\t\t\tW=%lf\n"
                                             "������� � ������������� ������������� \tMeaErW=%lf<Eps=%lf\n"
                                            "��� ����� ����������� \t\t\tN=%d\n", *W, *MeaErW, Eps, *N);
    else printf("��������� �������� �� ����������!\n");

}
/* ����� 6 ���� */
void OutputResultToCons(int N, double *ArrT, double *ArrUin, double *ArrUout, double dt)
{
    int i;
    printf("� �/�\tt\t\tUin\t\tUout\n");
    for(i=0;i<(N+1);i++) printf("%d\t%lf\t%lf\t%lf\n", i, ArrT[i], ArrUin[i], ArrUout[i]);
    printf("dt=%lf\n", dt);
//    printf("W=\n");
}
/* ����� 7 ���� */
void OutputResultToFile(int N, double *ArrT, double *ArrUin, double *ArrUout, double dt, char *filename)
{
    int i;
    FILE *fout=fopen(filename, "w");
    if(fout!=NULL)
    {
        fputs("#� �/�\tt\t\tUin\t\tUout\n", fout);
        fprintf(fout, "%d\n", N); //����� N ��� ���������� ��� ���� ����� 3
        for(i=0;i<(N+1); i++)
        {
            fprintf(fout, "%d\t%lf\t%lf\t%lf\n", i, ArrT[i], ArrUin[i], ArrUout[i]);
        }
        fprintf(fout,"#dt=%lf\n", dt);
    }
    else printf("OutputResultToCons:Cannot open %s", filename);
    fclose(fout);
}
/* ����� 8 ���� */
void OutputWToFile(int N, double W, double MeaErW, char *filename)
{
    FILE *fout=fopen(filename, "a");
    if(fout!=NULL) fprintf(fout, "#�������������� \t\t\t\tW=%lf\n"
                                             "#������� � ������������� ������������� \tMeaErW=%lf\n"
                                            "#��� ����� ����������� \t\t\tN=%d\n", W, MeaErW, N);
    else printf("�� ������� ������� %s", filename);
    fclose(fout);
}
/* ����� 13 ���� */
void DebOutputCurrentToCons(int N, double U, double tstart, double t1, double t2, double tend, double a, double b, double Uin1, double Uin2, double C, double Eps, int Nmax)
{
    printf("N=\t%d\n", N);

    printf("U=\t%lf\n", U);
    printf("tstart=\t%lf\n", tstart);
    printf("t1=\t%lf\n", t1);
    printf("t2=\t%lf\n", t2);
    printf("tend=\t%lf\n", tend);

    printf("a=\t%lf\n", a);
    printf("b=\t%lf\n", b);
    printf("Uin1=\t%lf\n", Uin1);
    printf("Uin2=\t%lf\n", Uin2);

    printf("C=\t%lf\n", C);
    printf("Eps=\t%lf\n", Eps);
    printf("Nmax=\t%d\n", Nmax);
}
