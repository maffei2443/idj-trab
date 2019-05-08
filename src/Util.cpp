#include "Util.h"
#include <cmath>

bool IsFloatDiffZero(double x, double y) {
    return fabs(x - y) < ep;
}

bool IsDoubleDiffZero(double x, double y) {
    return fabs(x - y) < ep;
}

bool IsFloatZero(double x) {
    return fabs(x) < ep;
}

bool IsDoubleZero(double x) {
    return fabs(x) < ep;
}
