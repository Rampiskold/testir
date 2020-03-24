#include "rank.h"
#include <cmath>

float sum_naive(const float* vec, size_t n)
{
    float val = 0.f;
    for (size_t i = 0; i < n; i++)
    {
        val += vec[i];
    }
    return val;
}

double sum_naive(const double* vec, size_t n)
{
    double val = 0.f;
    for (size_t i = 0; i < n; i++) {
        val += vec[i];
    }
    return val;
}

/**
 * return (-1)^{i+1} \cdot \frac{1}{i^3}
 */
template<class T>
T findItem(size_t i)
{
    int sign = (i & 1) ? 1 : -1;
    return (T)(sign * ((T)1) / pow((T)i, 3));
}

float getItemf(size_t i)
{
    return findItem<float>(i);
}

double getItemd(size_t i)
{
    return findItem<double>(i);
}

template<class T>
T sumrank(size_t n, bool rev = false)
{
    T val = 0;
    if (!rev) {
        for (size_t i = 1; i <= n; i++) {
            val += findItem<T>(i);
        }
    }
    else {
        for (size_t i = n; i > 0; i--) {
            val += findItem<T>(i);
        }
    }
    return val;
}


float  sumrank(size_t n, float rev)
{
    return sumrank<float>(n, (rev != 0.f));
}

double sumrank(size_t n, double rev)
{
    return sumrank<double>(n, (rev != 0.));
}

template<class T>
T sumrankAlgFast(T error, size_t& iterations, T& reserr)
{
    T sumPrev = 0;
    int i = 1;
    T curErr = 0;
    T sumCur  = findItem<T>(i++);
    do {
        sumPrev = sumCur;
        sumCur += findItem<T>(i++);
        curErr = fabs(sumPrev - sumCur);
    } while(curErr > error);
    iterations = i-1;
    reserr = curErr;
    return sumCur;
}

template<class T>
T sumrankAlg(T error, size_t& iterations, T& reserr, bool rev = false)
{
    if (rev == false)
        return sumrankAlgFast<T>(error, iterations, reserr);

    T sumPrev = 0;
    int i = 1;
    T curErr = 0;
    T sumCur  = sumrank(i++, (T)1);
    do {
        sumPrev = sumCur;
        sumCur = sumrank(i++, (T)1);
        curErr = fabs(sumPrev - sumCur);
    } while(curErr > error);
    iterations = i-1;
    reserr = curErr;
    return sumCur;
}

float  sumrank(float error, size_t* it, float* comperr, bool rev)
{
    size_t i;
    float err;
    float sum = sumrankAlg(fabsf(error), i, err, rev);
    if (it != nullptr)
        *it = i;
    if (comperr != nullptr)
        *comperr = err;
    return sum;
}

double sumrank(double error, size_t* it, double* comperr, bool rev)
{
    size_t i;
    double err;
    double sum = sumrankAlg(fabs(error), i, err, rev);
    if (it != nullptr)
        *it = i;
    if (comperr != nullptr)
        *comperr = err;
    return sum;
}
