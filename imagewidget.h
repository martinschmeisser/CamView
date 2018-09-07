#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include <QVector>

class ImageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ImageWidget(QWidget *parent = 0);
    void setImage(qint16 * const buffer, int imageSize, int width, int height);
    void makeImage(QImage &image);

signals:

public slots:
    void paintEvent(QPaintEvent*);

private:
    quint8 *pBufferImage;
    int buffersize_, width_, height_;

};

#endif // IMAGEWIDGET_H
