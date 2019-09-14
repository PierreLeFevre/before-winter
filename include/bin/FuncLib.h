#ifndef FUNCLIB_H
#define FUNCLIB_H

void fixArrayBug(char* const buffer) {
    char* bufferP = buffer;
    int nBytesToMove = 0;
    for (bufferP = buffer; *(bufferP - 1) != 0; bufferP++) {
        *(bufferP - nBytesToMove) = *bufferP;
        if (*bufferP == '\r') {
            nBytesToMove++;
        }
    }
}

#endif