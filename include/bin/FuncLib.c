#include "FuncLib.h"

#include <stdio.h>
#include <math.h>

void RemoveCharacterFromArray(char* const buffer, char toRemove) {
    char* bufferP = buffer;
    int nBytesToMove = 0;
    for (bufferP = buffer; *(bufferP - 1) != 0; bufferP++) {
        *(bufferP - nBytesToMove) = *bufferP;
        if (*bufferP == toRemove) {
            nBytesToMove++;
        }
    }
}

double Map(double value, double in_min, double in_max, double out_min, double out_max){
    if(in_min > in_max || out_min > out_max){
        return -1;
    }
    if(value > in_min || value < out_max){
        return (value - in_min) * ((out_max - out_min)/(in_max - in_min)) + out_min;
    }
    else{
        return value;
    }
}

int Cap(int value_in, int cap_to){
    if(value_in > abs(cap_to)){
        return abs(cap_to);
    }else if(value_in < -abs(cap_to)){
        return -abs(cap_to);
    }else{
        return value_in;
    }
}