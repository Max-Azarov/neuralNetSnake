#ifndef LEARNSTATE_H
#define LEARNSTATE_H

#include <memory>

#include "snake/writeInputData.h"
#include "snake/choiseDirection.h"
#include "snake/learning.h"

class Snake;
class WriteInputData;
class ChoiseDirection;
class Learning;

class ILearnState {
protected:
    // Type of Learning
    std::unique_ptr<WriteInputData> m_pWriteInputData;
    std::unique_ptr<ChoiseDirection> m_pChoiseDirection;
    std::unique_ptr<Learning> m_pLearning;

protected:
    ILearnState(const ILearnState&) = delete;
    ILearnState& operator=(const ILearnState&) = delete;
    ILearnState(ILearnState&&) = delete;
    ILearnState&& operator= (ILearnState&&) = delete;

public:
    ILearnState(Snake* snake, WriteInputData* writeInputData, ChoiseDirection* choiseDirection, Learning* learning);

    virtual ~ILearnState() {}

    WriteInputData* getWriteInputData() const { return m_pWriteInputData.get(); }
    ChoiseDirection* getChoiseDirection() const { return m_pChoiseDirection.get(); }
    Learning* getLearning() const { return m_pLearning.get(); }

};

class LearnStateType1 : public ILearnState {

public:
    LearnStateType1(Snake* snake, int sizeOfArea);

};

class LearnStateType2 : public ILearnState {

public:
    LearnStateType2(Snake* snake, int depthOfVision);

};

class LearnStateType3 : public ILearnState {

public:
    LearnStateType3(Snake* snake, int sizeOfArea);

};

#endif // LEARNSTATE_H
