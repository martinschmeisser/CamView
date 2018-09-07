#ifndef CAMVIEW_H
#define CAMVIEW_H

#include "WorkerThread.h"

#include <QWidget>
#include <QTimer>
#include <QMessageBox>
#include <pylon/PylonIncludes.h>

#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>

#include "../PylonProxy/PylonProxy.h"

#if defined( USE_1394 )
// Settings to use  Basler 1394 cameras
#include <pylon/1394/Basler1394Camera.h>
typedef Pylon::CBasler1394Camera Camera_t;
using namespace Basler_IIDC1394CameraParams;
using namespace Basler_IIDC1394StreamParams;
#elif defined ( USE_GIGE )
// Settings to use Basler GigE cameras
#include <pylon/gige/BaslerGigECamera.h>
typedef Pylon::CBaslerGigECamera Camera_t;
using namespace Basler_GigECameraParams;
using namespace Basler_GigEStreamParams;
#else
#error Camera type is not specified. For example, define USE_GIGE for using GigE cameras
#endif

namespace Ui {
class CamView;
}

class CamView : public QWidget
{
    Q_OBJECT

public:
    explicit CamView(QWidget *parent = 0);

    ~CamView();

public slots:

private slots:
    void processFrame();

    void saveTiffImage(int16_t *imageBuffer);

    void on_acquireButton_clicked();

    void on_acquireContinuousButton_clicked();

    void on_saveButton_clicked();

    void on_closeButton_clicked();

    void on_exposureSlider_sliderMoved(int position);

    void on_gainSlider_sliderMoved(int position);

    void on_blackLevelSlider_sliderMoved(int position);

    void on_backgroundCheckBox_clicked();

    void on_testImageButton_clicked();

    void on_saveDarkImageButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::CamView *ui;                // stores the user interface

    int16_t *pBuffer;              // ring buffer for image aquisition
    int16_t *backgroundBuffer;     // buffer for a single image, subtract this from cquired image if subtractBG==true

    bool acquireContinuously;       // is true during continuous acquisition, set false to stop
    bool subtractBG;                // if true, the image in backgroundBuffer will be subtracted from every acquired image

    size_t imageSize;               // image size in pixels
    size_t bufferSize;              // buffer size in bytes
    int numBuffers;                 // how many images are in the ring buffer "pBuffer"
    int numRegBuffers;              // how many buffers from the ring buffers are registered with pylon
    int frameCounter;
    QTimer timer;                   // fires constantly to collect frames

    int imageWidth, imageHeight;

    PylonProxy *hProxy;             // proxy class to pylon API
    uint64_t Info[12];              // stores acquisition parameters, see PylonProxy.h for doc

    QwtPlotCurve *horizontalCurve;
    QwtPlotCurve *verticalCurve;

    WorkerThread *workerThread;
    QPolygonF *pointsV;
    QPolygonF *pointsH;

    QMessageBox msgBox;
};

#endif // CAMVIEW_H
