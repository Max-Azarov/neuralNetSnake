#include <string>
#include <sstream>
#include <fstream>
#include <QDebug>

#include "training.h"
#include "net.h"
#include "_neuronet.h"

Training::Training(Net* net)
    : p_Net     { net },
      m_error   { 1.0 }
{
}

void Training::forwardPass(const std::vector<int> & in, bool dropout ) {
    //qDebug() << p_Net->getCountOfInputs();
    //qDebug() << in.size();
    m_dropout = false;
    if ( p_Net->getCountOfInputs() != in.size() ) {
        std::cerr << "The number of inputs in the training set does not match!" << std::endl;
        exit(EXIT_FAILURE);
    }
    // Передача значений на входы сети
    size_t count = 0;
    for (   auto itIn = std::begin(p_Net->getInputNeurons());
            itIn != std::prev(std::end(p_Net->getInputNeurons()));
            ++itIn   )
    {
        (*itIn)->setIn(static_cast<double>(in[count]));
        ++count;
    }

    // DropOut
    if (dropout) {
        m_dropout = true;
        auto itLayer = std::begin(p_Net->getNeuron());
        itLayer++;
        // цикл от 2го слоя до предпоследнего. Отключаем нейроны с определенной вероятностью rand() % 4
        for (; itLayer != std::prev(std::end(p_Net->getNeuron())); ++itLayer) {
            for (auto itNeuron = std::begin(*itLayer); itNeuron != std::end(*itLayer); ++itNeuron) {
                (*itNeuron)->setStatus((STATUS)(rand() % 4));
            }
        }
    }

    // Прямой проход по сети
    for (auto itLayer = std::begin(p_Net->getNeuron()); itLayer != std::end(p_Net->getNeuron()); ++itLayer) {
        for (auto itNeuron = std::begin(*itLayer); itNeuron != std::end(*itLayer); ++itNeuron) {
            (*itNeuron)->calculateInCalculateOut();
        }
    }
}

void Training::getOutValues(std::vector<double>* outValues) const {
    auto itLayer = std::crbegin(p_Net->getNeuron()); // Последний слой
    outValues->resize(itLayer->size());
    auto itOut = std::begin(*itLayer);
    auto itOutValues = std::begin(*outValues);
    for (; itOut != std::end(*itLayer); ++itOut, ++itOutValues) {
        // Перебираем все нейроны последнего слоя
        *itOutValues = (*itOut)->getOut();
    }
}

double Training::calculateError(const std::vector<double> & idealOut) {
    if ( p_Net->getCountOfOutputs() != idealOut.size() ) {
        std::cerr << "The number of outputs in the training set for calculating the error does not match!" << std::endl;
        exit(EXIT_FAILURE);
    }
    // Считаем ошибку после обучающей выборки
    // MSE   ERROR = ((I1 - A1)^2 + (I2 - A2)^2 + ... + (In - In)^2) / n
    double tempError = 0.0;
    double ideal;
    auto itIdealOut = std::begin(idealOut);
    auto itOut = std::begin(p_Net->getOutputNeurons());
    for (   /**/ ;
            itOut != std::end(p_Net->getOutputNeurons());
            ++itOut, ++itIdealOut )
    {
        ideal = (*itIdealOut == -1.0) ? (*itOut)->getOut() : *itIdealOut;
        tempError += ( ((*itOut)->getOut() - (ideal)) *
                       ((*itOut)->getOut() - (ideal)) );
    }
    m_error = tempError / p_Net->getCountOfOutputs();
    return m_error;
}

void Training::backprop(const std::vector<double> & idealOut) {
    if ( p_Net->getCountOfOutputs() != idealOut.size() ) {
        std::cerr << "The number of outputs in the training set does not match!" << std::endl;
        exit(EXIT_FAILURE);
    }
    // Считаем ошибку
    //calculateError(idealOut);

    // Передача идеальных значений в выходные нейроны
    auto itIdealOut = std::begin(idealOut);
    auto itOut = std::begin(p_Net->getOutputNeurons());
    double ideal;
    for (   ;
            itOut != std::end(p_Net->getOutputNeurons());
            ++itOut, ++itIdealOut )
    {
        ideal = (*itIdealOut == -1.0) ? (*itOut)->getOut() : *itIdealOut;
        static_cast<OutputNeuron*>(itOut->get())->setIdealOut(ideal);
    }

    // Распространяем ошибку в обратном направлении
    for (auto itLayer = std::end(p_Net->getNeuron()); itLayer != std::begin(p_Net->getNeuron()); --itLayer) {
        for (auto itNeuron = std::begin(*std::prev(itLayer)); itNeuron != std::end(*std::prev(itLayer)); ++itNeuron) {
            (*itNeuron)->calculateDelta();
        }
    }
    if (m_dropout) {
        auto itLayer = std::begin(p_Net->getNeuron());
        itLayer++;
        // цикл от 2го слоя до предпоследнего. Включаем отключенные нейроны
        for (; itLayer != std::prev(std::end(p_Net->getNeuron())); ++itLayer) {
            for (auto itNeuron = std::begin(*itLayer); itNeuron != std::end(*itLayer); ++itNeuron) {
                if ( !(*itNeuron)->getStatus() ) {
                    (*itNeuron)->setStatus(STATUS::ON);
                }
            }
        }
        m_dropout = false;
    }
}

void Training::saveWeightOfSynapses() {
    // Сохраняем веса синапсов в "weights.bin"
    std::string fileName {"weights.bin"};
    std::fstream weightsf; // файловый поток

    // Проверка на наличие файла
    weightsf.open(fileName, std::ios::in); // Проверяем, есть ли такой файл
    if (!weightsf) {
        weightsf.close();
        std::cerr << "\"" << fileName << "\" could not be opened! Create a new "<< fileName << std::endl;
        weightsf.open(fileName, std::ios::out); // Если не открылся, создаем новый файл
    }
    weightsf.close();

    weightsf.open(fileName, std::ios::out | std::ios::trunc | std::ios::binary);
    if (!weightsf)
    {
        std::cerr << "\"" << fileName << "\" could not be opened!" << std::endl;
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < p_Net->getNeuron().size(); ++i) {
        for (size_t j = 0; j < p_Net->getNeuron()[i].size(); ++j) {
            for ( auto  it =    std::begin(p_Net->getNeuron()[i][j]->getOutputSynapse());
                        it !=   std::end(p_Net->getNeuron()[i][j]->getOutputSynapse());
                        ++it) {
                weightsf << (*it)->getWeight() << " ";
            }
        }
    }
    weightsf.close();
}
