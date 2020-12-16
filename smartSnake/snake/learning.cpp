#include "snake/learning.h"

#include <QApplication>
#include <fstream>
#include <sstream>

Learning::Learning(Snake* pSnake) : m_pSnake { pSnake }
  , m_fInputData { "input.txt" }
  , m_fOutputDataIdeal { "outputIdeal.txt" }
{
    initFiles();
}

void Learning::learning() {
    //emit m_pSnake->signalRunInfo();
    if (
           m_pSnake->getStatusCollision()
        || m_pSnake->getStatusFruitEaten()
        || m_pSnake->getStatusHopelessSituation()
        )
    {

        if (m_pSnake->getStatusCollision() || m_pSnake->getStatusHopelessSituation()) {
            badMove();
        }

        if (m_pSnake->getStatusFruitEaten()) {
            goodMove();
        }
        // Записываем строчки в обучающую выборку
        addDataToTrainingSet();
        // Тренируем
        training();
    }
}

void Learning::goodMove() {

    // Добавляем мотивацию в выбранное направление, остальную уменьшаем на 50%
    auto itMedian = std::begin(*m_pSnake->getVOut()) + m_pSnake->getVOut()->size() / 2;
    for ( auto it = std::begin(*m_pSnake->getVOut()); it != itMedian; ++it) {
        (*it) = 0.5 * (*it);
    }
    m_pSnake->getVOut()->at(m_pSnake->getDirection()) = 1.0;// m_vOut[m_direction] = 1.0;
    // Страх не учим
    for ( auto it = itMedian; it != std::end(*m_pSnake->getVOut()); ++it) {
        (*it) = -1.0;
    }
}

void Learning::badMove() {
    // Добавляем страх неправильному выбор (1.0), уменьшаем на 50% остальной страх
    auto itMedian = std::begin(*m_pSnake->getVOut()) + m_pSnake->getVOut()->size() / 2;
    for ( auto it = itMedian; it != std::end(*m_pSnake->getVOut()); ++it) {
        (*it) = 0.5 * (*it);
    }
    m_pSnake->getVOut()->at(m_pSnake->getDirection() +  m_pSnake->getVOut()->size() / 2) = 1.0;

    // Мотивацию не обучаем (-1.0), кроме выбранного направления
    double diffMotivation = 0.5 * m_pSnake->getVOut()->at(m_pSnake->getDirection());
    for ( auto it = std::begin(*m_pSnake->getVOut()); it != itMedian; ++it) {
        (*it) = -1.0;
    }
    // Снижаем на 50% мотивацию идти в выбранное направление
    m_pSnake->getVOut()->at(m_pSnake->getDirection()) = diffMotivation;
}

void Learning::addDataToTrainingSet() {
    m_pSnake->incSetCount();
    // >> Добавляем данные в файлы обучающих выборок
    std::ofstream file; // файловый поток

    // Открываем входной файл
    QString fileName = m_fInputData;
    file.open(fileName.toStdString(), std::ios::app);
    if (!file) {
        QString message = "\"" + fileName + "\" could not be opened!";
        exitApp(message);
    }
    // Записываем данные
    for (auto it = std::begin(*m_pSnake->getVIn()); it != std::end(*m_pSnake->getVIn()); ++it) {
        file << *it << " ";
    }
    file << "\n";
    file.close();

    // Открываем выходной файл
    fileName = m_fOutputDataIdeal;
    file.open(fileName.toStdString(), std::ios::app);
    if (!file) {
        QString message = "\"" + fileName + "\" could not be opened!";
        exitApp(message);
    }
    // Записываем данные
    for (auto it = std::begin(*m_pSnake->getVOut()); it != std::end(*m_pSnake->getVOut()); ++it) {
        file << *it << " ";
    }
    file << "\n";
    file.close();
    // << Добавляем данные в файлы обучающих выборок

    // >> Добавляем данные в вектора обучающих выборок
    m_vInTrainingSet.push_back(*m_pSnake->getVIn());
    m_vOutTrainingSet.push_back(*m_pSnake->getVOut());
    // << Добавляем данные в вектора обучающих выборок

}

void Learning::readDataToTrainingSet() {

    m_vInTrainingSet.clear();
    m_vOutTrainingSet.clear();

    std::ifstream file; // файловый поток
    QString fileName;
    std::string tempString;
    std::stringstream ss; // строковый поток для преобразования входных данных из строки
    size_t count = 0;

// >> Считываем из файла входы и выходы
    fileName = m_fInputData;
    file.open(fileName.toStdString());
    if (!file) {
        QString message = fileName + " could not be opened!";
        exitApp(message);
    }

    // >> "input.txt" считываем данные в вектор
    int intemp;
    while(getline(file, tempString)) {
        m_vInTrainingSet.push_back(std::vector<int>());
        ss << tempString;
        while (ss >> intemp) {
            m_vInTrainingSet[count].push_back(intemp);
        }
        ss.clear(); // очищаем флаги потока
        tempString.clear();
        count++;
    }
    file.close();
    count = 0;
    // << "input.txt" считываем данные в вектор

    fileName = m_fOutputDataIdeal;
    file.open(fileName.toStdString());
    if (!file) {
        QString message = fileName + " could not be opened!";
        exitApp(message);
    }

    // >> "outputIdeal.txt" считываем данные в вектор
    double dTemp;
    while(getline(file, tempString)) {
        m_vOutTrainingSet.push_back(std::vector<double>());
        //m_vAcceptError.push_back(false);
        ss << tempString;
        while (ss >> dTemp) {
            m_vOutTrainingSet[count].push_back(dTemp);
        }
        ss.clear(); // очищаем флаги потока
        tempString.clear();
        count++;
    }
    file.close();
    // << "output.txt" считываем данные в вектор

    if (m_vInTrainingSet.size() != m_vOutTrainingSet.size()) {
        exitApp("The number of lines in the files " + m_fInputData + " and " + m_fOutputDataIdeal + " does not match!");
    }

// << Считываем из файла входы и выходы
}

void Learning::clearData() {
    m_vInTrainingSet.clear();
    m_vOutTrainingSet.clear();
    initFiles(true);
}

void Learning::initFiles(bool clearFiles) {
    createFile(m_fInputData, clearFiles);
    createFile(m_fOutputDataIdeal, clearFiles);
}

void Learning::createFile(const QString& fileName, bool clearFile) {
    std::fstream file; // файловый поток
    file.open(fileName.toStdString(), std::ios::in); // Проверяем, есть ли такой файл
    if (!file) {
        file.close();
        QString message = fileName + " could not be opened! Create new " + fileName;
        LogOut::messageOut(message, LogOut::LOGFILE);
        file.open(fileName.toStdString(), std::ios::out); // Если не открылся, создаем новый файл
    }
    file.close();

    if (clearFile) {
        // Удаляем содержимое файла
        file.open(fileName.toStdString(), std::ios::out | std::ios::trunc);
        if (!file) {
            QString message = fileName + " could not be opened!";
            exitApp(message);
        }
        file.close();
    }
}

void Learning::exitApp(const QString& message) {
    LogOut::messageOut(message, LogOut::LOGFILE);
    exit(EXIT_FAILURE);
}

//LearningType_1 ==========================================================
// Выборка прогоняется один раз, начиная с последнего опыта к первому
LearningType_1::LearningType_1(Snake* pSnake) : Learning(pSnake)
{

}



void LearningType_1::training() {
    // >> Обучаем
    if ( !m_pSnake->getStopStatus() ) {
        //emit m_pSnake->signalStatusInfo("learning");
        double sumError;
        double error;
        size_t countOfSet;
        size_t count;
        //size_t loopExit = 0;
        //do {
        count = 0;
        error = 0;
        countOfSet = 0;
        sumError = 0;

        auto itOut = std::end(m_vOutTrainingSet);
        auto itIn = std::end(m_vInTrainingSet);
        for ( ;
                itIn != std::begin(m_vInTrainingSet);
                --itIn, --itOut, ++countOfSet )
        {
            qApp->processEvents();
            //neuroNet->training().forwardPass(*std::prev(itIn), true); // with dropout
            m_pSnake->getNet()->training().forwardPass(*std::prev(itIn)); // without dropout
            error = m_pSnake->getNet()->training().calculateError(*std::prev(itOut));
            m_pSnake->getNet()->training().backprop(*std::prev(itOut));
            sumError += error;
            if ( error > m_pSnake->getAcceptError() ) {
                count++;
            }
        }
        sumError = sumError / countOfSet; // vSize;
        m_pSnake->setSummError(sumError);
        m_pSnake->setInfoCount(count);
        emit m_pSnake->signalErrorInfo();

            //loopExit++;
        //}
        //while (loopExit < 1);

        // << Обучаем
        //emit m_pSnake->signalStatusInfo("moving");
        m_pSnake->getNet()->training().saveWeightOfSynapses();
        m_pSnake->setSetCount(0);
    }
}

//LearningType_2 ==========================================================
// Выборка прогоняется один раз, начиная с первого опыта к последнему
LearningType_2::LearningType_2(Snake* pSnake) : Learning(pSnake)
  , m_allowBad { true }
  , m_allowGood { true }
  , m_allowUsually { true }
{

}

void LearningType_2::learning() {
//    if (
//           m_pSnake->getStatusCollision()
//        || m_pSnake->getStatusFruitEaten()
//        || m_pSnake->getStatusHopelessSituation()
//        )
//    {
        //emit m_pSnake->signalRunInfo();
        bool allowBad = m_allowBad;
        bool allowGood = m_allowGood;
        bool allowUsually = m_allowUsually;

        if ( m_pSnake->getStatusCollision() ) {
            if ( m_allowBad ) {
                badMove();
                m_allowGood = true;
                m_allowBad = false;
            }
        }

        if ( m_pSnake->getStatusHopelessSituation() ) {
            badMove();
        }

        if (m_pSnake->getStatusFruitEaten()) {
            if ( m_allowGood ) {
                goodMove();
                m_allowUsually = true;
                m_allowGood = false;
            }
        }
        if ( !(m_pSnake->getStatusCollision() || m_pSnake->getStatusHopelessSituation() || m_pSnake->getStatusFruitEaten()) ) {
            if (m_allowUsually) {
                usuallyMove();
                m_allowBad = true;
                m_allowUsually = false;
            }
        }

        // Записываем строчки в обучающую выборку
        if ( allowBad != m_allowBad
             || allowGood != m_allowGood
             || allowUsually != m_allowUsually
             || m_pSnake->getStatusHopelessSituation()
             )
        {
            addDataToTrainingSet();
            // Тренируем
            training();
        }


    //}
}

void LearningType_2::training() {
    // >> Обучаем
    if ( !m_pSnake->getStopStatus() ) {
        //emit m_pSnake->signalStatusInfo("learning");
        double sumError;
        double error;
        size_t countOfSet;
        size_t count;
        count = 0;
        error = 0;
        countOfSet = 0;
        sumError = 0;

        auto itOut = std::begin(m_vOutTrainingSet);
        auto itIn = std::begin(m_vInTrainingSet);
        for (  ;
                itIn != std::end(m_vInTrainingSet);
                ++itIn, ++itOut, ++countOfSet )
        {
            qApp->processEvents();
            //neuroNet->training().forwardPass(*itIn, true); // with dropout
            m_pSnake->getNet()->training().forwardPass(*itIn); // without dropout
            error = m_pSnake->getNet()->training().calculateError(*itOut);
            m_pSnake->getNet()->training().backprop(*itOut);
            sumError += error;
            if ( error > m_pSnake->getAcceptError() ) {
                count++;
            }
        }
        sumError = sumError / countOfSet; // vSize;
        m_pSnake->setSummError(sumError);
        m_pSnake->setInfoCount(count);
        emit m_pSnake->signalErrorInfo();

        // << Обучаем
        //emit m_pSnake->signalStatusInfo("moving");
        m_pSnake->getNet()->training().saveWeightOfSynapses();
        m_pSnake->setSetCount(0);
    }
}

void LearningType_2::usuallyMove() {
    auto itOut = std::begin(*m_pSnake->getVOut());

    // #Оставляем мотивацию без изменений (-1.0)
    // Добавляем мотивацию в выбранное направление (1.0)
    (*itOut) = 1.0;
    // Уменьшаем страх 0.0
    (*(++itOut)) = 0.0;
}

void LearningType_2::goodMove() {
    auto itOut = std::begin(*m_pSnake->getVOut());

    // Добавляем мотивацию в выбранное направление (1.0)
    (*itOut) = 1.0;
    // Уменьшаем страх 0.0
    (*(++itOut)) = 0.0;
}

void LearningType_2::badMove() {
    auto itOut = std::begin(*m_pSnake->getVOut());

    // Мотивацию Уменьшаем 0.0
    (*itOut) = 0.0;
    // Добавляем страх неправильному выбору (1.0)
    (*(++itOut)) = 1.0;
}




//LearningType_3 ==========================================================
// Выборка прогоняется один раз, начиная с первого опыта к последнему
LearningType_3::LearningType_3(Snake* pSnake) : Learning(pSnake)
{
}

void LearningType_3::training() {
    // >> Обучаем
    if ( !m_pSnake->getStopStatus() ) {
        double sumError;
        double error;
        size_t countOfSet;  // количество последних тренировочных выборок для обучения
        size_t count;
        size_t loopExit = 0;
        do {
            count = 0;
            error = 0;
            countOfSet = 0;
            sumError = 0;

            size_t numOfSet = 10;

            auto itOut = std::rbegin(m_vOutTrainingSet);
            auto itIn = std::rbegin(m_vInTrainingSet);
            for ( ;
                    ( itIn != std::rend(m_vInTrainingSet) ) && ( countOfSet < numOfSet );
                    ++itIn, ++itOut, ++countOfSet )
            {
                qApp->processEvents();
                //neuroNet->training().forwardPass(*itIn, true); // with dropout
                m_pSnake->getNet()->training().forwardPass(*itIn); // without dropout
                error = m_pSnake->getNet()->training().calculateError(*itOut);
                m_pSnake->getNet()->training().backprop(*itOut);
                sumError += error;
                if ( error > m_pSnake->getAcceptError() ) {
                    count++;
                }
            }
            sumError = sumError / countOfSet; // vSize;
            m_pSnake->setSummError(sumError);
            m_pSnake->setInfoCount(count);
            emit m_pSnake->signalErrorInfo();
            loopExit++;
        }
        while (
                loopExit < 10
                &&error > m_pSnake->getAcceptError()
                && !m_pSnake->getStopStatus()
                );
        // << Обучаем
        m_pSnake->getNet()->training().saveWeightOfSynapses();
        m_pSnake->setSetCount(0);
    }
}

void LearningType_3::learning() {
    usuallyMove();
    if (m_pSnake->getStatusCollision() || m_pSnake->getStatusHopelessSituation()) {
        badMove();
    }

    if (m_pSnake->getStatusFruitEaten()) {
        goodMove();
    }
    // Записываем строчки в обучающую выборку
    addDataToTrainingSet();
    // Тренируем
    training();
}

void LearningType_3::goodMove() {
    auto itOut = std::begin(*m_pSnake->getVOut());

    // Поощряем такую ситуацию и действия (1.0)
    *itOut += 1.0;
    if (*itOut > 1.0) *itOut = 1.0;
}

void LearningType_3::badMove() {
    auto itOut = std::begin(*m_pSnake->getVOut());

    // Осуждаем такую ситуацию и действия (0.0)
    *itOut = 0.0;
    //if (*itOut < 0.1) *itOut = 0.1;
}

void LearningType_3::usuallyMove() {
    auto itOut = std::begin(*m_pSnake->getVOut());

    // Обычный ход. Выдаем часть награды (0.1)
    //*itOut += 0.5;
    //if (*itOut > 1.0) *itOut = 1.0;
    //if (*itOut < 0.4) *itOut = 0.4;
    //if (*itOut > 0.6) *itOut = 0.6;
}
