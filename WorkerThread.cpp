#include "WorkerThread.h"
#include <iostream>

void WorkerThread::run()
{
    pointsH_->resize(imageWidth);
    pointsV_->resize(imageHeight);

    for (int i=0; i< imageHeight; i++)
    {
        int sum = 0;
        for (int j=0; j< imageWidth; j++)
        {
            sum += buffer_[i*imageWidth+j];
        }
        (*pointsV_)[i] = QPointF(sum,imageHeight-i);
    }

    for (int i=0; i< imageWidth; i++)
    {
        int sum = 0;
        for (int j=0; j< imageHeight; j++)
        {
            sum += buffer_[i+j*imageWidth];
        }
        (*pointsH_)[i] = QPointF(i,sum);
    }
}

void WorkerThread::setWorkItem(qint16 *buffer, int width, int height, QPolygonF *pointsV, QPolygonF *pointsH)
{
    buffer_ = buffer;
    imageWidth = width;
    imageHeight = height;
    pointsV_ = pointsV;
    pointsH_ = pointsH;
}
