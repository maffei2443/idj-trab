#include "Util.h"
#include <cmath>

bool IsFloatDiffZero(double x, double y) {
    return abs(x - y) < ep;
}

bool IsDoubleDiffZero(double x, double y) {
    return abs(x - y) < ep;
}

bool IsFloatZero(double x) {
    return abs(x) < ep;
}

bool IsDoubleZero(double x) {
    return abs(x) < ep;
}
