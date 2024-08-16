#include <stdio.h>
#include <time.h>

void MulInt(int a,int b, int c, int M1[a][b],int M2[b][c], int M3[a][c]){
    for(int i=0;i<a;i++){
        for(int j=0;j<c;j++){
            M3[i][j] = 0;
            for(int k=0;k<b;k++){
                M3[i][j] += M1[i][k] * M2[k][j];
            }
        }
    }
}

long long MulDouble(int a,int b, int c, double M1[a][b],double M2[b][c],double M3[a][c], long long scale){
    long long T = 0;
    long long T0s,T1s,T0ns,T1ns,Ts,Tns;
    struct timespec t;
    timespec_get(&t,TIME_UTC);
    T0s = t.tv_sec;
    T0ns = t.tv_nsec;
    for(int i=0;i<a;i++){
        for(int j=0;j<c;j++){
            M3[i][j] = 0;
            for(int k=0;k<b;k++){
                M3[i][j] += M1[i][k] * M2[k][j];
            }
        }
    }
    timespec_get(&t,TIME_UTC);
    T1s = t.tv_sec;
    T1ns = t.tv_nsec;
    Ts = T1s - T0s;
    Tns = T1ns - T0ns;
    T = Ts * (1e9/scale) + Tns / scale;
    return T;
}

int X = 1;
int P = 101;

void PopulateInt(int N,int M[N][N]){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            M[i][j] = X;
            X = ((P - (2*X)%P)*X) % P;
        }
    }
}

void PopulateDouble(int N,double M[N][N]){
    //int x = 1;
    double y = 0;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            y = X;
            y += 0.5;
            M[i][j] = y;
            X = ((P - (2*X)%P)*X) % P;
        }
    }
}

int M1[1024][1024];
int M2[1024][1024];
int M3[1024][1024];
double M4[1024][1024];
double M5[1024][1024];
double M6[1024][1024];

int main(){
    struct timespec t;
    // Different values of N to be used are
    // 64
    // 128
    // 256
    // 512
    // 1024
    //We'll store the average time required for interger matrix multiplication in I[5] , in order.
    //and avg. time required for double matrix multiplication in D[5]
    long long I[5];
    long long D[5];
    long long Icpu[5];
    long long Dcpu[5];
    int Nlis[5] = {64,128,256,512,1024};
    long long t0,t1;
    long long CLOCK_PER_MS = CLOCKS_PER_SEC / 1000;
    clock_t c0,c1;
    //Integers
    printf("\n\nInteger multiplication\n");
    int N;
    for(int q=0;q<5;q++){
        N = Nlis[q];
        PopulateInt(N,M1);
        PopulateInt(N,M2);
        timespec_get(&t,TIME_UTC);
        t0 = (q<3) ? t.tv_nsec >> 20 : t.tv_sec;
        Icpu[q] = 0;
        for(int i = 0;i<3;i++){
            c0 = clock(); 
            MulInt(N,N,N,M1,M2,M3);
            timespec_get(&t,TIME_UTC);
            c1 = clock();
            Icpu[q] = ((c1 - c0)/3)/CLOCK_PER_MS;
        }
        t1 = (q<3) ? t.tv_nsec >> 20 : t.tv_sec;
        I[q] = (t1 - t0)/3; //ms
        printf("N = %d : exec. time = %lld %s , cpu. time = %lld ms \n",N,I[q],(q<3) ? "ms":"s",Icpu[q]);
    }

    //Double
    printf("\n\nDouble multiplication\n");
    for(int q=0;q<5;q++){
        N = Nlis[q];
        PopulateDouble(N,M4);
        PopulateDouble(N,M5);
        D[q] = 0;
        Dcpu[q] = 0;
        for(int i = 0;i<3;i++){
            timespec_get(&t,TIME_UTC);
            t0 = (q<3) ? t.tv_nsec >> 20 : t.tv_sec;
            c0 = clock();
            MulDouble(N,N,N,M4,M5,M6);
            c1 = clock();
            Dcpu[q] += ((c1 - c0)/3)/CLOCK_PER_MS;
            timespec_get(&t,TIME_UTC);
            t1 = (q<3) ? t.tv_nsec >> 20 : t.tv_sec;
            D[q] += (t1 - t0)/3;
        }
        printf("N = %d : exec. time = %lld %s , cpu. time = %lld ms \n",N,D[q],(q<3) ? "ms":"s",Dcpu[q]);
    }
    return 0;
}