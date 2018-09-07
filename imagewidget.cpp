#include "imagewidget.h"
#include <QPainter>
#include <QDebug>

ImageWidget::ImageWidget(QWidget *parent) :
    QWidget(parent)
{
    pBufferImage = NULL;
    buffersize_ = 0;
}

void ImageWidget::setImage(qint16 * const buffer, int imageSize, int width, int height)
{
    buffersize_ = imageSize;
    width_ = width;
    height_ = height;

    if(!pBufferImage) pBufferImage = new quint8[ imageSize*4 ];
    quint8 temp;

    //convert 16bit greyscale to 32bit grey argb (8bit on 4 channels)
    for (int i = 0; i<imageSize; i++)
    {
        temp = quint8((double)buffer[i]/(double)4095.0*(double)256.0);

        pBufferImage[4*i+0]=temp;
        pBufferImage[4*i+1]=temp;
        pBufferImage[4*i+2]=temp;
        pBufferImage[4*i+3]=0;
    }

    this->repaint();
}

void ImageWidget::makeImage(QImage &image)
{
    if(pBufferImage)
    {
        QImage _image((uchar*) pBufferImage, width_, height_, QImage::Format_RGB32);
        image = _image;
    }
}

void ImageWidget::paintEvent(QPaintEvent*)
{
//draw image from the converted buffer on every event
    if(pBufferImage)
    {
        QImage image((uchar*) pBufferImage, width_, height_, QImage::Format_RGB32);
        QPainter p(this);
        p.drawImage(0,0,image, 0, 0);
        p.end();
    }
}
