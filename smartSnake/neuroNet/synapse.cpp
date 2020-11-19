#include "synapse.h"

Synapse::Synapse()
{
    m_id = incId();
    //std::cout << "Create Synapse " << m_id << std::endl;
    m_status = ON;
}

int Synapse::incId(bool reset) {
    static size_t id = 0;
    if (!reset) {
        ++id;
    }
    else {
        id = 0;
    }
    return id;
}

void Synapse::updateWeight(double delta, Parameters& parameters)
{
    if (m_status == ON) {
        m_delta = delta;
        m_grad = m_delta * m_in;
        m_dWeight = parameters.getE() * m_grad +
                    parameters.getA() * m_dWeight;
        m_prevWeight = m_weight;
        m_weight += m_dWeight;
    }
}

void Synapse::updateWeight(double delta)
{
    if (m_status == ON) {
        m_delta = delta;
        m_grad = m_delta * m_in;
        m_dWeight = m_parameters->getE() * m_grad +
                    m_parameters->getA() * m_dWeight;
        m_prevWeight = m_weight;
        m_weight += m_dWeight;
    }
}
