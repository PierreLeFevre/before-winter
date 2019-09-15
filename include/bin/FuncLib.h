#ifndef FUNCLIB_H
#define FUNCLIB_H

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

#endif