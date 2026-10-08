#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"
#include <sys/time.h>



static void task1(void){
    size_t sizes[7] = {8, 16, 32, 64, 128, 512, 1024};
    void *ptr[7];

    for (int i = 0; i < 7; i++){
        ptr[i] = malloc(sizes[i]);
    }
    for (int i = 6; i >= 0; i--){
        free(ptr[i]);
    }
}

static void task2(void){
    void *ptr[120];
    for (int i =0 ; i<120; i++){
        ptr[i] = malloc(1);
    }
    for(int i = 0;i<120;i++){
        free(ptr[i]);
    }
}

static void task3(void){
    void *ptr[120];
    int count = 0;
    int act = 0;
    
    while (count<120){
        int ran = rand() % 2;
        if (ran==0){
            ptr[act]=malloc(1);
            act++;
            count++;
        }else if (act > 0){
            int tmp =rand() % act;
            free(ptr[tmp]);
                act--;
            if (tmp < act) {
                ptr[tmp] = ptr[act];
            }
        }
    }
    for (int i = 0; i < act; i++){
        free(ptr[i]);
    }
}

static void task4(void){
    void *ptr[120]={NULL};
    for(int i= 0;i<80;i++){
        ptr[i]= malloc(24);
    }
    for(int o=1;o<80;o=o+2){
        free(ptr[o]);
        ptr[o]=NULL;
    }
    for(int p =80; p<120;p++){
        ptr[p]=malloc(16); 
    }
    for(int z=0;z<120;z++){
        if (ptr[z]!= NULL){
            free(ptr[z]);
        }
    }
}

static void task5(void){
    void *ptr[60];
    size_t sizes[3] = {8, 24, 40};
    for (int i = 0; i < 60; i++){
        ptr[i] = malloc(sizes[i % 3]);
    }
    for (int i = 0; i < 30; i++){
        free(ptr[i]);
        free(ptr[59 - i]);
    }
}







//main
int main(void)
{
    struct timeval start, end;
    gettimeofday(&start, NULL);
    for (int i = 0; i < 50; i++) {
        task1();
        task2();
        task3();
        task4();
        task5();
    }
    gettimeofday(&end, NULL);
    double total=(end.tv_sec - start.tv_sec) * 1000000.0+ (end.tv_usec - start.tv_usec);
    printf("Average workload time: %.2f microseconds\n",total/50.0);

    return 0;
}
