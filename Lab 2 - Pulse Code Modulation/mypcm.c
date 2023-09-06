// general purpose standard C lib
#include <stdio.h>
#include <math.h>
#include <stdlib.h> // includes malloc(),free()
//Add any necessary headers here

// user-defined header files
#include "mypcm.h" // do not modify this file

// put your function prototypes for additional helper functions below:
float get_absolute_A(asignal signal){
    return signal.A;
}

// implementation
float analog_signal_generator(asignal signal, int t)
{
    float value;
    float A = signal.A;
    value = sinf(signal.omega * t + signal.sigma);
    value *= A;
    return value;
}
void sampler(float *samples, int interval, asignal signal)
{
    int time = 0;
    int i = 2;
    samples[1]= get_absolute_A(signal);
    // ** the value of A is stored in the 1 index of samples ,for later use
    while (time <= signal.duration){
        float temp = analog_signal_generator(signal , time);
        samples[i] = temp;
        i++;
        time += interval;
    }
}
void quantizer(float *samples, int *pcmpulses, int levels)
{
    float A_max = samples[1];
    float A_min = A_max*(-1);
    int size = samples[0];  //according to my convention
    for (int i =1 ; i<=size ; i++){
        int Q_level = floorf(((samples[i+1]-A_min)/(A_max - A_min))*levels);
        pcmpulses[i] = Q_level;
    }
}
void encoder(int *pcmpulses, int *dsignal, int encoderbits)
{
    int size = pcmpulses[0]; //according to my convention
    for (int i=0 ; i<size ; i++){
        int temp = pcmpulses[i+1];
        for (int j = 0 ; j<encoderbits ; j++){
            int value = temp%2;
            dsignal[(i+1)*encoderbits-j-1] = value;
            temp /= 2;
        }
    }
}