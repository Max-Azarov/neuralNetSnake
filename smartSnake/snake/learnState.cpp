#include "learnState.h"

ILearnState::ILearnState(Snake* snake, WriteInputData* writeInputData, ChoiseDirection* choiseDirection, Learning* learning) :
    m_pWriteInputData { std::move(writeInputData) }
  , m_pChoiseDirection { std::move(choiseDirection) }
  , m_pLearning { std::move(learning) }
{
    LogOut::messageOut("create ILearnState");
    snake->readDataToTrainingSet(*m_pLearning);
    snake->writeInputData(*m_pWriteInputData); // Для вычисления количества необходимых входов НС
}

LearnStateType1::LearnStateType1(Snake* snake, int sizeOfArea) :
    ILearnState(snake
                  , new WriteInputDataType_1(snake, sizeOfArea)
                  , new ChoiseDirectionType_1(snake)
                  , new LearningType_1(snake)
                )
{
    LogOut::messageOut("create LearnStateType1");
}

LearnStateType2::LearnStateType2(Snake* snake, int depthOfVision) :
    ILearnState( snake
                 , new WriteInputDataType_2(snake, depthOfVision)
                 , new ChoiseDirectionType_2(snake)
                 , new LearningType_2(snake)
                 )
{
    LogOut::messageOut("create LearnStateType2");
}

LearnStateType3::LearnStateType3(Snake* snake, int sizeOfArea) :
    ILearnState(snake
                  , new WriteInputDataType_3(snake, sizeOfArea)
                  , new ChoiseDirectionType_3(snake)
                  , new LearningType_3(snake)
                )
{
    LogOut::messageOut("create LearnStateType3");
}
