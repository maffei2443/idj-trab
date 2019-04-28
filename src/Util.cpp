#include "Util.h"
#include <cmath>

bool IsFloatDiffZero(double x, double y) {
    return abs(x - y) < ERR;
}

bool IsDoubleDiffZero(double x, double y) {
    return abs(x - y) < ERR;
}

bool IsFloatZero(double x) {
    return abs(x) < ERR;
}

bool IsDoubleZero(double x) {
    return abs(x) < ERR;
}
