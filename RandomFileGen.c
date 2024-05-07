#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int Filesize = 0;
char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.-#'?!";

void randomFileGen(int Filesize, char filename[]);

int main(){
    int i;
    char filename[] = "TestDoc#000.txt";
    for(i = 0 ; i< 100; i++){
        Filesize += 100;
        filename[10] = '0' + i%10;
        filename[9] = '0' + (i/10);
        filename[8] = '0' + (i/100);
        srand(i);
        randomFileGen(Filesize, filename);
    }
    return 0;
}

void randomFileGen(int Filesize, char filename[]){
    FILE *toWriteIn;
    toWriteIn = fopen(filename, "w");
    if(toWriteIn == NULL){
        printf("%d\n", Filesize);
        printf("Error opening file\n");
        exit(1);
    }
    int i;
    for(i = 0; i < Filesize; i++){
        fputc(charset[rand() % 69], toWriteIn);
    }
    fclose(toWriteIn);
}