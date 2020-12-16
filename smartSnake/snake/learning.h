#ifndef SNAKETRAINING_H
#define SNAKETRAINING_H

#include "snake/snake.h"

#include <vector>

class Snake;

class Learning {
protected:
    Snake* m_pSnake;

    // Вектора, содержащие обучающие выборки
    std::vector<std::vector<int>> m_vInTrainingSet;
    std::vector<std::vector<double>> m_vOutTrainingSet;

    // Названия файлов, содержащие обучающие выборки
    QString m_fInputData;
    QString m_fOutputDataIdeal;

protected:
    virtual void goodMove();
    virtual void badMove();
    virtual void training() = 0;
    void addDataToTrainingSet();
    void createFile(const QString& fileName, bool clearFile = false);
    void initFiles(bool clearFiles = false);
    void exitApp(const QString& message = "Exit application");

public:
    Learning(Snake* pSnake);
    virtual ~Learning() {}

    virtual void learning();
    void readDataToTrainingSet();
    void clearData();
    size_t getNumTrainingSet() const { return m_vInTrainingSet.size(); }

};

class LearningType_1 : public Learning {
    // Вся тренировочная Выборка прогоняется один раз, начиная с последнего опыта к первому
public:
    LearningType_1(Snake* pSnake);

    void training() override;
};


class LearningType_2 : public Learning {
    // Вся тренировочная Выборка прогоняется один раз, начиная с первого опыта к последнему
    // Применяется только совместно с ChoiseDirectionType_2 и WriteInputDataType_2
private:
    bool m_allowBad;
    bool m_allowGood;
    bool m_allowUsually;

private:
    void usuallyMove();

protected:
    void goodMove() override;
    void badMove() override;


public:
    LearningType_2(Snake* pSnake);

    void training() override;
    void learning() override;
};


class LearningType_3 : public Learning {
    // Вся тренировочная Выборка прогоняется один раз, начиная с первого опыта к последнему
public:
    LearningType_3(Snake* pSnake);

    void training() override;
    void learning() override;

protected:
    void goodMove() override;
    void badMove() override;
    void usuallyMove();
};

#endif // SNAKETRAINING_H
