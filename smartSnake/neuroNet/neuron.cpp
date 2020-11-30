#include "neuron.h"

#include <cmath>

Neuron::Neuron() {

    m_id = incId();
    //std::cout << "Create Neuron " << m_id << std::endl;
    m_delta = 0;
    m_in = 0;
    m_out = 0;
    m_status = ON;
    m_typeActivation = SIGMOID;
}

size_t Neuron::incId(bool reset) {
    static size_t id = 0;
    if (!reset) {
        ++id;
    }
    else {
        id = 0;
    }
    return id;
}

void Neuron::activationFunction()
{
    double out = 0.0;
    if (m_status) {
        switch (m_typeActivation) {
        case(SIGMOID) :
            // sigmoid
            out = 1.0 / (1.0 + exp(-m_in));
            break;
        case(RELU) :
            // ReLu
            if (m_in > 0) out = m_in;
            else out = 0.1 * m_in;
            break;
        default:;
        }
        setOut(out);
        return;
    }
    setOut(out);
}

double Neuron::getDerivative()
{
    if (m_status) {
        switch (m_typeActivation) {
        case(SIGMOID) :
            // derived from a sigmoid
            return (1.0 - m_out) * m_out;
        case(RELU) :
            // ReLu
            if (m_in > 0) return 1.0;
            else return 0.1;
        default:;
        }
    }
    return 0.0;
}

void Neuron::calculateInCalculateOut() {
    if (m_status) {
        double sum = 0;
        for (auto it = std::begin(v_synapseIn); it != std::end(v_synapseIn); ++it) {
            sum += (*it)->getOut();
        }
        m_in = sum;
        activationFunction();
        passToSynapse();
    }
}

void Neuron::passToSynapse() {
    for (auto it = std::begin(v_synapseOut); it != std::end(v_synapseOut); ++it) {
        (*it)->setInCalculateOut(m_out);
    }
}

void Neuron::setOut(double out) {
    if (m_status) {
        m_out = out;
    }
    else {
        m_out = 0.0;
    }
    passToSynapse();
}

void Neuron::calculateDelta(Parameters& parameters)
{
    if (m_status == ON) {
        double dTempSum = 0;
        for (auto it = std::begin(v_synapseOut); it != std::end(v_synapseOut); ++it) {
            dTempSum += (*it)->getWeightMultipliedDelta();
        }
        m_delta = getDerivative() * dTempSum;
        for (auto it = std::begin(v_synapseIn); it != std::end(v_synapseIn); ++it) {
            (*it)->updateWeight(m_delta, parameters);
        }
    }
}

void Neuron::calculateDelta()
{
    if (m_status == ON) {
        double dTempSum = 0;
        for (auto it = std::begin(v_synapseOut); it != std::end(v_synapseOut); ++it) {
            dTempSum += (*it)->getWeightMultipliedDelta();
        }
        m_delta = getDerivative() * dTempSum;
        for (auto it = std::begin(v_synapseIn); it != std::end(v_synapseIn); ++it) {
            (*it)->updateWeight(m_delta);
        }
    }
}
