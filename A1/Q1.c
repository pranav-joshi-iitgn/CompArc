#include <stdio.h>
#include <time.h>
long int fibo_rec(int n){
    long int x;
    if(n==1){x = 1;return x;}
    else if(n==2){x = 2;return x;}
    else if(n>2){return fibo_rec(n-1) + fibo_rec(n-2);}
    else {x = 0 ;return x;}
}
void Print_fib_rec_memo(int n,long result[2]){
    long int x;
    if(n==1){
        result[0] = 0;
        result[1] = 1;
        printf("%ld\n",result[1]);
    } else if(n==2){
        result[0] = 1;
        result[1] = 1;
        printf("%ld\n",result[1]);
    } else {
        Print_fib_rec_memo(n-1,result);
        x = result[0] + result[1];
        result[0] = result[1];
        result[1] = x;
        printf("%ld\n",result[1]);
    }
}
void Print_fib_loop(){
    long int x,y,z;
    x = 0; // fib(0)
    y = 1; // fib(1)
    for(int i=1;i<=50;i++){
        printf("%ld\n",y);
        z = x + y;
        x = y;
        y = z;
    }
}
void Print_fibo_rec(){
    for(int i=1;i<=50;i++){
        printf("%ld\n",fibo_rec(i));
    }
}
void Print_fibo_loop_memo(){
    long F[51];
    F[0] = 0;
    F[1] = 1;
    printf("%ld",F[1]);
    for(int i = 2;i<=50;i++){
        F[i] = F[i-1] + F[i-2];
        printf("%ld\n",F[i]);
    }
}
void method(int x){
    switch(x){
        case 0:Print_fibo_rec();
        case 1:Print_fib_loop();
        case 2:
            long result[2];
            Print_fib_rec_memo(50,result);
        case 3:Print_fibo_loop_memo();
    }
}
int main(){
    struct timespec t;
    long long T[4];
    long long t0s,t1s,t0ns,t1ns;
    long long scales[4] = {1e9,1e6,1e6,1};
    int reps = 3;
    for(int q=0;q<4;q++){
        timespec_get(&t,TIME_UTC);
        t0ns = t.tv_nsec;
        t0s = t.tv_sec;
        for(int i = 0;i<reps;i++){method(q);}
        timespec_get(&t,TIME_UTC);
        t1ns = t.tv_nsec;
        t1s = t.tv_sec;
        T[q] = (t1s - t0s)*(1e9/scales[q]) + (t1ns - t0ns)/scales[q];
        T[q] = T[q] / reps;
    }
    printf("Recursion         : Time = %lld s\n",T[0]);
    printf("Loop              : Time = %lld ms\n",T[1]);
    printf("Recur. with memo. : Time = %lld ms\n",T[2]);
    printf("Loop with memo.   : Time = %lld ns\n",T[3]);
    return 0;
}