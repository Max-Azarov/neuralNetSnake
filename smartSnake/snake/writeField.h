#ifndef WRITEDATA_H
#define WRITEDATA_H

#include <vector>

class Snake;

class WriteField
{
private:
    Snake* m_pSnake;
    //std::vector<int>& m_vRefInData;

public:
    WriteField(Snake* snake);
};

#endif // WRITEDATA_H
