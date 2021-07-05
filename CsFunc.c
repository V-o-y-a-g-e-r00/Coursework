/*  CsFunc.c*/
#include <stdio.h>
#include <stdlib.h> //atoi
#include <string.h>
#include <math.h>
#include <conio.h> //для getch

#include "CsFunc.h"
#include "CsPlotFunc.h"
#define DATACOUNT 13 //число вводимых величин
void TxtFromFile(char *filename, char *strcatn) //filename имя или путь к файлу. strcatn буфер, куда помещается весь файл целиком
{
    int i=0;    //счетчик строк
    char buff[2048]={0};    //буфер для считывания строки
    FILE *fin=fopen(filename, "rb");
    if(fin!=NULL)
    {
        while (!feof (fin))
        {
            if ( !feof(fin))    // для коррекции известной ошибки работы feof
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
void InputIntFromCons(int *a, char *name) // аналогично InputDoubleFromCons
{
    char buff[128];
    while(1)
    {
        printf("Введите %s:", name); //printf("Input %s:", name);
        fgets(buff, 127, stdin); //
        char *c = strchr(buff, '\n');     /* Ищем символ ‘\n’ в прочитанной строке */
        if(c != NULL) *c = '\0';          /* Запись символа ‘\0’вместо символа ‘\n’ */
        int i=strspn(buff, "+-1234567890"); /* длина начальной подстроки, с указанными символами strspn substring pointer number */
        if(i==strlen(buff))
        {
            *a=atoi(buff);
            return;
        }
        else printf("Недопустимые символы! Введите %s заново!\n", name);//printf("Unacceptable symbols! Input %s again!\n", name);
    }
}
void InputDoubleFromCons(double *a, char *name)
{
    char buff[128];
    while(1)
    {
        printf("Введите %s:", name); //printf("Input %s:", name);
        fgets(buff, 127, stdin); //
        char *c = strchr(buff, '\n');     /* Ищем символ ‘\n’ в прочитанной строке */
        if(c != NULL) *c = '\0';          /* Запись символа ‘\0’вместо символа ‘\n’ */
        int i=strspn(buff, "eE+-.1234567890"); /* длина начальной подстроки, с указанными символами strspn substring pointer number */
        if(i==strlen(buff))
        {
            *a=atof(buff);
            return;
        }
        else printf("Недопустимые символы! Введите %s заново!\n", name); //printf("Unacceptable symbols! Input %s again!\n", name);
    }
}
/* пункт 1 меню */
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
/* пункт 2 меню */
void InputDataFromFile(int *N, double *U, double *tstart, double *t1, double *t2, double *tend, double *a, double *b, double *Uin1, double *Uin2, double *C, double *Eps, int *Nmax, char *filename)
{
    int i=0, j=0, k;    //i счетчик строк j счетчик строк без комментариев
    char smallbuff[2048]={0}; //буфер для одной строки
    char buff[DATACOUNT][2048]={0};    //буфер для всех строк без знака #
    FILE *fin=fopen(filename, "rb");
    if(fin!=NULL)
    {
        while (!feof (fin))
        {
            if ( !feof(fin))    // для коррекции известной ошибки работы feof
            {
                i=i+1;
                fgets(smallbuff, 127, fin);
                char *c=strchr(smallbuff, '\n');    // убираем '\n' в конце строки.
                if (c!=NULL) *c='\0';
                if(smallbuff[0]!='#')
                {
                    strcpy(buff[j], smallbuff);
                    j++;
                    if(j>=DATACOUNT) break; //если число строк без комментариев (больше или равно) числу аргументов.

                }
             //   printf("%s string count=%d\n", buff, i);
            }
        }
//        printf("strcatn=%s", strcatn);

        for(k=0; k<j; k++) printf("buff[%d][]=%s\n", k, buff[k]); //проверка того, что оказалось в массиве строк

/* считываем из массива строк */
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
/* пункт 3 меню */
void InputDataFromFileForPlots(int *N, double *tend, double **ArrT, double **ArrUin, double **ArrUout, char *filename, int *FormArrFlag)
{
    *FormArrFlag=1;
    int i=0, j=0, k;    //i счетчик строк j счетчик строк без комментариев
    char smallbuff[2048]={0}; //буфер для одной строки
//    char buff[DATACOUNT][2048]={0};    //буфер для всех строк без знака #
    FILE *fin=fopen(filename, "rb");
    if(fin!=NULL)
    {
        while (!feof (fin)) //тут считываем N
        {
            if ( !feof(fin))    // для коррекции известной ошибки работы feof
            {
                i=i+1;
                fgets(smallbuff, 127, fin);
                char *c=strchr(smallbuff, '\n');    // убираем '\n' в конце строки.
                if (c!=NULL) *c='\0';
                if(smallbuff[0]!='#')
                {
                    sscanf(smallbuff, "%d", N);
                    break;

                }
            }
        }
        printf("N=%d\n", *N);
        free(*ArrT); //Освобождаем память, если раньше она уже была выделена
        free(*ArrUin);
        free(*ArrUout);

        *ArrT=(double *)malloc(sizeof(double)*(*N+1)); //Выделяем память
        *ArrUin=(double *)malloc(sizeof(double)*(*N+1));
        *ArrUout=(double *)malloc(sizeof(double)*(*N+1));
        while (!feof (fin)) //тут читаем в массивы ArrT ArrUin ArrUout
        {
            if ( !feof(fin))    // для коррекции известной ошибки работы feof
            {
                i=i+1;
                fgets(smallbuff, 127, fin);
                char *c=strchr(smallbuff, '\n');    // убираем '\n' в конце строки.
                if (c!=NULL) *c='\0';
                if(smallbuff[0]!='#')
                {
                    sscanf(smallbuff, "%*d%lf%lf%lf", &(*ArrT)[j], &(*ArrUin)[j], &(*ArrUout)[j]); //первый аргумент это номер, его отбрасываем
                    j++;
                    if(j>=(*N+1)) break; //если число строк без комментариев (больше или равно) числу элементов.

                }
             //   printf("%s string count=%d\n", buff, i);
            }
        }
//        printf("strcatn=%s", strcatn);

        for(k=0; k<j; k++) printf("ArrT[%d]=%lf\tArrUin[%d]=%lf\tArrUout[%d]=%lf\n", k, (*ArrT)[k], k, (*ArrUin)[k], k, (*ArrUout)[k]); //проверка того, что оказалось в массиве строк
    }
    else printf("TxtFromFile:Cannot open %s", filename);
    fclose(fin);
/*  тут присвоим значение tend это нужно для работы функий для графиков*/
    *tend=(*ArrT)[*N];
    printf("tend=%lf\n", *tend);
}

/* пункт 4 меню */
void FormArrT(int N, double tstart, double tend, double **ArrT, double *dt) // указатель на указатель нужен, чтобы мы могли изменять указатель (иначе он просто скопируется, и ничего не произойдет)
{
    int i;
    double currT=tstart;
    free(*ArrT);        //Если мы вызываем функцию повторно, то прошлую область памяти нужно освободить
    *ArrT=(double *)malloc(sizeof(double)*(N+1)); //разыменовываем указатель на указатель и связываем с памятью
    *dt=(tend-tstart)/N;
    for(i=0;i<(N+1);i++)
    {
       // *(*ArrT+i)=currT; // так присвоить элементу массива значение тоже можно. эта строка и строка ниже эквивалентны друг другу по смыслу
        (*ArrT)[i]=currT; //разыменовываем
        currT=currT+*dt;
    }
//    for(i=0;i<(N+1);i++) printf("(*ArrT)[%d]=%lf\n", i, (*ArrT)[i]); //проверка
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
// for(i=0;i<(N+1);i++) printf("(*ArrUin)[%d]=%lf\n", i, (*ArrUin)[i]); //проверка

}
void FormArrUout(int N, double a, double b, double Uin1, double Uin2, double *ArrUin, double **ArrUout, int *FormArrFlag)
{
    *FormArrFlag=1; //устанавливаем флаг
    int i;
    free(*ArrUout);
    *ArrUout=(double *)malloc(sizeof(double)*(N+1));

    for(i=0;i<(N+1);i++)
    {
        if(ArrUin[i]<=Uin1) (*ArrUout)[i]=a*Uin1+b;
        if((Uin1<ArrUin[i])&&(ArrUin[i]<=Uin2)) (*ArrUout)[i]=a*ArrUin[i]+b;
    if(ArrUin[i]>Uin2) (*ArrUout)[i]=a*Uin2+b;
    }
// for(i=0;i<(N+1);i++) printf("(*ArrUout)[%d]=%lf\n", i, (*ArrUout)[i]); //проверка
//for(i=0;i<(N+1);i++) printf("FormArrUout:(*ArrUin)[%d]=%lf\n", i, ArrUin[i]); //проверка

}
/* пункт 5 меню */
void CalcW(int *N, double U, double tstart, double t1, double t2, double tend, double a, double b, double Uin1, double Uin2, double C, double Eps, int Nmax, double **ArrT, double **ArrUin, double **ArrUout, double *dt, int *FormArrFlag, double *W, double *MeaErW, int DebFlag)
{
    int Nstart=*N; // понадобится для определения, посчитана ли W хотя бы 1 раз и хотя бы 2 раза
    *MeaErW=Eps+1; // чтобы первый раз зайти в цикл
    double Wold;
    double Umax, CUmax; //CUmax чисто для наглядности
    int i; //счетчик
    int K; //величина для нахождения погрешности
    while((*N<Nmax) &&(*MeaErW>Eps))
    {
        FormArrT(*N, tstart, tend, ArrT, dt);
        FormArrUin(*N, U, tstart, t1, t2, tend, *ArrT, ArrUin);
        FormArrUout(*N, a, b, Uin1, Uin2, *ArrUin, ArrUout, FormArrFlag);
/*  Находим Umax*/
        Umax=(*ArrUout)[0]; //инициализируем Umax
        for(i=0;i<(*N+1);i++) if(Umax<(*ArrUout)[i]) Umax=(*ArrUout)[i];

        CUmax=C*Umax;

/*  Находим K*/
        K=0;
        for(i=0;i<(*N+1);i++) if((*ArrUout)[i]>CUmax) K++;
/*  Находим W*/
        Wold=*W; //Сохраняем старое значение W
        *W=K/(double)(*N+1);
/*  Находим MeaErW*/
        if(*N!=Nstart) *MeaErW=fabs(*W-Wold);
/*  Вывод для проверки*/
        OutputResultToCons(*N, *ArrT, *ArrUin, *ArrUout, *dt);
        printf("K=%d\n", K);
        printf("Umax=%lf\n", Umax);
        printf("CUmax=%lf\n", CUmax);
        printf("N=%d\n", *N);
        printf("W=%lf\n", *W);
        printf("MeaErW=%lf\n", *MeaErW);
        if(DebFlag==1) //для режима Отладки
        {
            printf("Нажмите любую клавишу для продолжения\n");
            getch();
        }

        *N=*N*2;
    }
    if(*N!=Nstart) *N=*N/2; //Компенсируем последнее учеличение N
/*  Выводим результат */
    if(*MeaErW<Eps) printf("Характеристика \t\t\t\tW=%lf\n"
                                             "Найдена с относительной прогрешностью \tMeaErW=%lf<Eps=%lf\n"
                                            "При числе промежутков \t\t\tN=%d\n", *W, *MeaErW, Eps, *N);
    else printf("Требуемая точность не достигнута!\n");

}
/* пункт 6 меню */
void OutputResultToCons(int N, double *ArrT, double *ArrUin, double *ArrUout, double dt)
{
    int i;
    printf("№ п/п\tt\t\tUin\t\tUout\n");
    for(i=0;i<(N+1);i++) printf("%d\t%lf\t%lf\t%lf\n", i, ArrT[i], ArrUin[i], ArrUout[i]);
    printf("dt=%lf\n", dt);
//    printf("W=\n");
}
/* пункт 7 меню */
void OutputResultToFile(int N, double *ArrT, double *ArrUin, double *ArrUout, double dt, char *filename)
{
    int i;
    FILE *fout=fopen(filename, "w");
    if(fout!=NULL)
    {
        fputs("#№ п/п\tt\t\tUin\t\tUout\n", fout);
        fprintf(fout, "%d\n", N); //Пишем N это необходимо для меню пункт 3
        for(i=0;i<(N+1); i++)
        {
            fprintf(fout, "%d\t%lf\t%lf\t%lf\n", i, ArrT[i], ArrUin[i], ArrUout[i]);
        }
        fprintf(fout,"#dt=%lf\n", dt);
    }
    else printf("OutputResultToCons:Cannot open %s", filename);
    fclose(fout);
}
/* пункт 8 меню */
void OutputWToFile(int N, double W, double MeaErW, char *filename)
{
    FILE *fout=fopen(filename, "a");
    if(fout!=NULL) fprintf(fout, "#Характеристика \t\t\t\tW=%lf\n"
                                             "#Найдена с относительной прогрешностью \tMeaErW=%lf\n"
                                            "#При числе промежутков \t\t\tN=%d\n", W, MeaErW, N);
    else printf("Не удалось открыть %s", filename);
    fclose(fout);
}
/* пункт 13 меню */
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
