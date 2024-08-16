#include <stdio.h>
#include <time.h>

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


int N = 256;
double M1[256][256];
double M2[256][256];
double M3[256][256];

int main(){
    struct timespec t;
    long long cpu_time;
    cpu_time = MulDouble(N,N,N,M1,M2,M3,1e6);
    printf("\nN = %d\ncpu\t%llde-3 s",N,cpu_time);
    return 0;
}
