#include "Include.h"

int foo() {
    static int i = 0;
    return i++;
}