#include "learnState.h"

LearnStateType1::LearnStateType1(Snake* snake) : ILearnState(new WriteInputDataType_1(snake)
                                                             , new ChoiseDirectionType_1(snake)
                                                             , new LearningType_1(snake)
                                                             )
{}

LearnStateType2::LearnStateType2(Snake* snake) : ILearnState(new WriteInputDataType_2(snake)
                                                             , new ChoiseDirectionType_2(snake)
                                                             , new LearningType_2(snake)
                                                             )
{}
