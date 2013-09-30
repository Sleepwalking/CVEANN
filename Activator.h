#ifndef ACTIVATOR_H
#define ACTIVATOR_H

typedef float (*Activator)(float);

extern void Sigmoid_Init() __attribute__ ((constructor));
extern void Sigmoid_Exit() __attribute__ ((destructor));

extern float Activator_Step(float Input);
extern float Activator_Sgn(float Input);
extern float Activator_Sigmoid(float Input);
extern float Activator_TanSigmoid(float Input);

extern float Activator_DSigmoid(float Input);
extern float Activator_DTanSigmoid(float Input);

extern void Activator_SetSigmoidStretch(float Ratio);
#endif
