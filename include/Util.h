#ifndef UTIL_H
#define UTIL_H
#define ep 0.01
#define ERR std::cerr
#define RAND_INT(mod) rand()%(mod)

bool IsFloatDiffZero(double, double);
bool IsFloatZero(double);
bool IsDoubleDiffZero(double, double);
bool IsDoubleZero(double);
#endif