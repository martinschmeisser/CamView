#include <QThread>
#include <QPointF>
#include <QPolygonF>

class WorkerThread : public QThread
{
    Q_OBJECT
    void run();// Q_DECL_OVERRIDE;

public:
    void setWorkItem(qint16 *buffer, int width, int height, QPolygonF *pointsV, QPolygonF *pointsH);

private:
    qint16 *buffer_;
    int imageWidth;
    int imageHeight;
    QPolygonF *pointsV_;
    QPolygonF *pointsH_;
};
