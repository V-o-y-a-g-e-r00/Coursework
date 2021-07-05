/*  CsFunc.h*/
#ifndef CSFUNC_H_INCLUDED
#define CSFUNC_H_INCLUDED



void TxtFromFile(char *filename, char *strcatn);

void InputDataFromCons(int *N, double *U, double *tstart, double *t1, double *t2, double *tend, double *a, double *b, double *Uin1, double *Uin2, double *C, double *Eps, int *Nmax);
void InputIntFromCons(int *a, char *name);
void InputDoubleFromCons(double *a, char *name);

void InputDataFromFile(int *N, double *U, double *tstart, double *t1, double *t2, double *tend, double *a, double *b, double *Uin1, double *Uin2, double *C, double *Eps, int *Nmax, char *filename);
void InputDataFromFileForPlots(int *N, double *tend, double **ArrT, double **ArrUin, double **ArrUout, char *filename, int *FormArrFlag);

void FormArrT(int N, double tstart, double tend, double **ArrT, double *dt);
void FormArrUin(int N, double U, double tstart, double t1, double t2, double tend, double *ArrT, double **ArrUin);
void FormArrUout(int N, double a, double b, double Uin1, double Uin2, double *ArrUin, double **ArrUout, int *FormArrFlag);

void CalcW(int *N, double U, double tstart, double t1, double t2, double tend, double a, double b, double Uin1, double Uin2, double C, double Eps, int Nmax, double **ArrT, double **ArrUin, double **ArrUout, double *dt, int *FormArrFlag, double *W, double *MeaErW, int DebFlag);

void OutputResultToCons(int N, double *ArrT, double *ArrUin, double *ArrUout, double dt);
void OutputResultToFile(int N, double *ArrT, double *ArrUin, double *ArrUout, double dt, char *filename);
void OutputWToFile(int N, double W, double MeaErW, char *filename);

void DebOutputCurrentToCons(int N, double U, double tstart, double t1, double t2, double tend, double a, double b, double Uin1, double Uin2, double C, double Eps, int Nmax);



#endif // CSFUNC_H_INCLUDED
