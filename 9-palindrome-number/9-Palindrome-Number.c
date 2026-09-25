#include <stdbool.h>

bool isPalindrome(int x) {
    int original = x;
    long long rev = 0;

    if (x < 0)
        return false;

    while (x != 0) {
        rev = rev * 10 + x % 10;
        x = x / 10;
    }

    return original == rev;
}