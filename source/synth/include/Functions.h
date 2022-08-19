#ifndef SYNTH_FUNCSINE_H
#define SYNTH_FUNCSINE_H

#include <cmath>

#ifndef M_PI
#   define M_PI 3.14159265358979323846
#endif

namespace Function {

class Sine
{
public:

    double operator()(double phase)
    {
        return sin(2 * M_PI * phase);
    }    
};

class Sawtooth
{
public:

    double operator()(double phase)
    {
        return 2.0 * phase - 1.0;
    }
};

class Square
{
public:

    double operator()(double phase)
    {
        return phase < 0.5 ? 1.0 : -1.0;
    }

};

class Triangle
{
public:

    double operator()(double phase)
    {
        return 2.0 * fabs(2.0 * phase - 1.0) - 1.0;
    }
};

} // namespace Function

#endif // SYNTH_FUNCSINE_H

