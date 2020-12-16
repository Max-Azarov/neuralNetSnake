#ifndef OUTPUTNEURON_H
#define OUTPUTNEURON_H

#include <iostream>

#include "neuron.h"

class OutputNeuron : public Neuron
{
private:
    double m_idealOut;
public:
    ~OutputNeuron() override;

    void setIdealOut(double idealOut) { m_idealOut = idealOut; }

    //void info() override { std::cout << "OutputNeuron" << std::endl; }
    virtual void calculateDelta(Parameters&) override;
    virtual void calculateDelta() override;
    virtual void calculateInCalculateOut() override;

protected:
    void setOut(double out) override;
};

#endif // OUTPUTNEURON_H
