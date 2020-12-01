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
    if (    m_pSnake->m_loopMotion
        ||  m_pSnake->m_collision
        ||  m_pSnake->m_isTheFruitEaten
        ||  m_pSnake->m_isHopelessSituation
        )
    {
        emit m_pSnake->signalRunInfo();
        if (m_pSnake->m_collision || m_pSnake->m_isHopelessSituation) {
            badMove();
        }

        if (m_pSnake->m_loopMotion) {
        }

        if (m_pSnake->m_isTheFruitEaten) {
            goodMove();
        }
        // Записываем строчки в обучающую выборку
        if ( !(m_pSnake->m_loopMotion || m_pSnake->m_isHopelessSituation) ) {
            addDataToTrainingSet();
        }
        training();
    }
}

void Learning::training() {
    // >> Обучаем
    if ( !m_pSnake->m_bStop) {
    //if ( m_setCount > 10 && m_setCount > m_average * m_average && !m_bStop) {
        emit m_pSnake->signalStatusInfo("learning");
        double sumError;
        double error;
        size_t countOfSet;
        size_t count;
        size_t loopExit = 0;
        do {
            count = 0;
            error = 0;
            countOfSet = 0;
            sumError = 0;

            auto itOut = std::end(m_vOutTrainingSet);
            auto itIn = std::end(m_vInTrainingSet);
            for ( ;
                    itIn != std::begin(m_vInTrainingSet);
                    --itIn, --itOut, ++countOfSet )

            /*
            auto itOut = std::begin(m_vOutTrainingSet);
            auto itIn = std::begin(m_vInTrainingSet);
            for (  ;
                    itIn != std::end(m_vInTrainingSet);
                    ++itIn, ++itOut, ++countOfSet )
            */
            {
                qApp->processEvents();
                //neuroNet->training().forwardPass(*std::prev(itIn), true); // with dropout
                m_pSnake->neuroNet->training().forwardPass(*std::prev(itIn)); // without dropout
                error = m_pSnake->neuroNet->training().calculateError(*std::prev(itOut));
                m_pSnake->neuroNet->training().backprop(*std::prev(itOut));
                sumError += error;
                if ( error > m_pSnake->m_acceptError ) {
                    count++;
                }
//                if (m_bStop) break;
                //if (countOfSet > 2000) break;
            }
//            if (m_bStop) break;
            sumError = sumError / countOfSet; // vSize;
            //qDebug() << count << "=== Total error:" << sumError << "===";
            m_pSnake->m_infoSumError = sumError;
            m_pSnake->m_infoCount = count;
            emit m_pSnake->signalErrorInfo();

            loopExit++;
        }
        while (loopExit < 1);
//        while ( count > 2 * (double)countOfSet/neuroNet->getCountOfOutputs()
//                || sumError  > m_acceptError);
        // << Обучаем
        emit m_pSnake->signalStatusInfo("moving");
        m_pSnake->neuroNet->training().saveWeightOfSynapses();
        //averageNumberOfSteps(false);
        m_pSnake->m_setCount = 0;
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
    m_pSnake->m_setCount++;
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
    for (size_t i = 0; i < m_pSnake->m_vIn.size(); ++i) {
        file << m_pSnake->m_vIn[i] << " ";
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
/*
    // Записываем данные
    for (size_t i = 0; i < m_vOutMotivation.size(); ++i) {
        file << m_vOutMotivation[i] << " ";
    }
    for (size_t i = 0; i < m_vOutFear.size(); ++i) {
        file << m_vOutFear[i] << " ";
    }
    file << "\n";
*/
    // Записываем данные
    for (size_t i = 0; i < m_pSnake->m_vOut.size(); ++i) {
        file << m_pSnake->m_vOut[i] << " ";
    }
    file << "\n";
    file.close();
    // << Добавляем данные в файлы обучающих выборок
/*
    // >> Добавляем данные в вектора обучающих выборок
    m_vInTrainingSet.push_back(m_vIn);
    std::vector<double> tempArr{ m_vOutMotivation };
    tempArr.insert(std::end(tempArr), std::begin(m_vOutFear), std::end(m_vOutFear));
    m_vOutTrainingSet.push_back(tempArr);
    //m_vAcceptError.push_back(false);
    // << Добавляем данные в вектора обучающих выборок
*/
    // >> Добавляем данные в вектора обучающих выборок
    m_vInTrainingSet.push_back(m_pSnake->m_vIn);
    m_vOutTrainingSet.push_back(m_pSnake->m_vOut);
    //m_vAcceptError.push_back(false);
    // << Добавляем данные в вектора обучающих выборок

}

void Learning::readDataToTrainingSet() {

    std::ifstream file; // файловый поток
    QString fileName;
    std::string tempString;
    std::stringstream ss; // строковый поток для преобразования входных данных из строки
    size_t count = 0;

// >> Считываем из файла входы и выходы
    fileName = m_fInputData;
    file.open(fileName.toStdString());
    if (!file) {
        QString message = "\"" + fileName + "\" could not be opened!";
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
        QString message = "\"" + fileName + "\" could not be opened!";
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
