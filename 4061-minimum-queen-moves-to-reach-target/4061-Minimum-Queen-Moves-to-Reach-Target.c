#include <stdlib.h>

int minQueenMoves(int* source, int sourceSize, int* target, int targetSize) {
    int sr = source[0], sc = source[1];
    int tr = target[0], tc = target[1];
    if (sr == tr && sc == tc) {
        return 0;
    }
    if (sr == tr || sc == tc || abs(sr - tr) == abs(sc - tc)) {
        return 1;
    }
    return 2;
}