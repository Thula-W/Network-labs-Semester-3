// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // stdlib includes malloc() and free()
#include<string.h>
#include <math.h>
// user-defined header files
#include "mypcm.h"


// function prototypes
void run(asignal * inputsignal);


int main()
{
    asignal * inputsignal = (asignal *) malloc(sizeof(asignal));
    run(inputsignal);

    //call any other function here

    free(inputsignal);
    return 0;
}

void run(asignal * inputsignal)
{
    char input[100];
    float data1[3];
    int data2[3];
    fgets(input,100,stdin);
    char* token = strtok(input, " ");

    // Convert the tokens to integers
    for (int i =0; i<3 ;i++){
        data1[i]= atof(token);
        token = strtok(NULL , " ");
    }

    for (int i=0 ; i<3 ; i++){
        data2[i] = atoi(token);
        token = strtok (NULL, " ");
    }
    inputsignal->A = data1[0];
    inputsignal->omega =data1[1];
    inputsignal->sigma = data1[2];
    inputsignal->duration =data2[0];

    int no_of_samples = (data2[0]/data2[1]) +1;
    int total_bits =data2[2]*no_of_samples;
    int levels = pow(2,data2[2]);
    float * samples= (float *) malloc(sizeof(float)* (no_of_samples+2));
    int * pcmpulses = (int*) malloc(sizeof(int)* no_of_samples);
    int * dsignal = (int*) malloc(sizeof(int)* total_bits);

    // **for my convenience I have used the 0 index of each array to store its size
    samples[0]= no_of_samples;
    pcmpulses[0]= no_of_samples;

    sampler(samples , data2[1], *inputsignal);
    quantizer(samples,pcmpulses, levels);
    encoder(pcmpulses,dsignal,data2[2]);

    for (int i=0; i<total_bits; i++){
        printf("%d" , dsignal[i]);
    }
}


