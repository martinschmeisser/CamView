#include "camview.h"
#include "ui_camview.h"

#include <QTime>
#include <QDate>
#include <QFileDialog>
#include <QTimer>
#include <QInputDialog>

#include <QFile>
#include <QTextStream>

#include <random>

using namespace Pylon;
using namespace std;


#include "tiffio.h"

CamView::CamView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CamView)
{
    cerr << "PylonProxy" << flush;
    pBuffer = NULL;
    bufferSize  = 0;
    imageWidth  = 0;
    imageHeight = 0;
    imageSize   = 0;
    /**   ---   UI related things here   ---   **/
    ui->setupUi(this);

    cerr << "PylonProxy" << flush;
    /**   ---   Pylon API related things here   ---   **/
    //initialize Pylon API
    hProxy = new PylonProxy;
    cerr << "PylonProxy" << flush;
    if (!(hProxy->isActive()))
    {
        cerr << " not active" << endl;
        ui->statusLabel->setText("could not initialize connection to camera.");
        msgBox.setText("could not initialize connection to camera.");
        msgBox.exec();
        ui->acquireButton->setDisabled(true);
        ui->acquireContinuousButton->setDisabled(true);
        return;
    }
    hProxy->getInfoArray(&Info[0]);
    cerr << " is active." << endl;
    imageHeight = Info[1];
    imageWidth = Info[0];
    imageSize = imageWidth*imageHeight;
    bufferSize = Info[2];
    cerr << "******" << imageSize << " " << bufferSize << endl;
    numBuffers = 5;
    pBuffer          = (int16_t*)malloc(numBuffers*bufferSize);
    backgroundBuffer = (int16_t*)malloc(           bufferSize);

    ui->exposureSlider->setMinimum(Info[3]);
    ui->exposureSlider->setMaximum(Info[4]);
    ui->exposureSlider->setValue(Info[5]);

    ui->gainSlider->setMinimum(Info[6]);
    ui->gainSlider->setMaximum(Info[7]);
    ui->gainSlider->setValue(Info[8]);

    ui->blackLevelSlider->setMinimum(Info[9]);
    ui->blackLevelSlider->setMaximum(Info[10]);
    ui->blackLevelSlider->setValue(Info[11]);

    verticalCurve = new QwtPlotCurve();
    verticalCurve->setPen( Qt::blue, 1 ),
    verticalCurve->setRenderHint( QwtPlotItem::RenderAntialiased, true );
    verticalCurve->attach( ui->verticalPlot );

    horizontalCurve = new QwtPlotCurve();
    horizontalCurve->setPen( Qt::blue, 1 ),
    horizontalCurve->setRenderHint( QwtPlotItem::RenderAntialiased, true );
    horizontalCurve->attach( ui->horizontalPlot );

    subtractBG = false;

    workerThread = new WorkerThread();
    pointsV = new QPolygonF;
    pointsH = new QPolygonF;
}

CamView::~CamView()
{
    delete hProxy;
    delete ui;
}

void CamView::processFrame()
//callback of the continuous mode timer, gets one picture from the pylon proxy's ring buffer and updates the display
//the timer that calls this function is activated in CamView::on_acquireContinuousButton_clicked() and should fire
//constantly to grab frames all the time
{
    if (acquireContinuously == false)
    {
        timer.stop();
        hProxy->stopContinuous();
        return;
    }

    //retrieve number of the frame in proxy's ring buffer
    int number = hProxy->getFrame();
    if (number != -1)
    {
        frameCounter += 1;

        int16_t *buffer = ((int16_t*)pBuffer) + number*imageSize;
        if (subtractBG)
            for (uint k = 0; k < imageSize; k++) buffer[k] -= backgroundBuffer[k];

        //compute histograms in parallel during image display
        workerThread->setWorkItem(buffer, imageWidth, imageHeight, pointsV, pointsH);
        workerThread->start();

        ui->widget->setImage(buffer, (int)imageSize, imageWidth, imageHeight);

        if (workerThread->wait(500))
        {
            verticalCurve->setSamples( *pointsV );
            horizontalCurve->setSamples( *pointsH );
            ui->horizontalPlot->replot();
            ui->verticalPlot->replot();
        }

        //tell proxy that he may re-use the buffer frame
        hProxy->requeue(number);
    }
    else
    {
        cout << "dropped one frame!" << endl;
    }
}

void CamView::saveTiffImage(int16_t *imageBuffer)
{
    if (!imageBuffer)
    {
        cerr << "No image buffer. Can't write to file." << endl;
        msgBox.setText("No image buffer. Can't write to file.");
        msgBox.exec();
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this, "save image data", "", "Image Files (*.tiff)");

    TIFF *img;
    int i;

    if (!(img = TIFFOpen (filename.toStdString().c_str(), "w")))
    {
        cerr << "Could not open image file for writing." << endl;
        msgBox.setText("Could not open image file for writing.");
        msgBox.exec();
        return;
    }

    TIFFSetField (img, TIFFTAG_IMAGEWIDTH, imageWidth);
    TIFFSetField (img, TIFFTAG_IMAGELENGTH, imageHeight);
    TIFFSetField (img, TIFFTAG_SAMPLESPERPIXEL, 1);

    TIFFSetField (img, TIFFTAG_COMPRESSION, COMPRESSION_NONE);
    TIFFSetField (img, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
    TIFFSetField (img, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
    TIFFSetField (img, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_MINISBLACK);
    TIFFSetField (img, TIFFTAG_ROWSPERSTRIP, 8);

    TIFFSetField (img, TIFFTAG_BITSPERSAMPLE, 16);
    for (i = 0; i < imageHeight; i++)
    {
        if (TIFFWriteScanline (img, imageBuffer + i * imageWidth, i, 0) < 0)
        {
            cerr << "ERROR DURING TIFF WRITE" << endl;
            msgBox.setText("Error during tiff write.");
            msgBox.exec();
            TIFFClose (img);
            return;
        }
    }

    TIFFClose (img);

    filename.append(".dat");
    QFile file(filename);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << "16 bit greyscale tiff generated by CamView using libtiff\n";

    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    out << date.toString() << " " << time.toString() << endl << endl;
    out << "width\t\t\t"            << Info[0] << endl;
    out << "height\t\t\t"           << Info[1] << endl;
    out << "exposure time (ms)\t" << Info[5] << endl;
    out << "gain\t\t\t"             << Info[8] << endl;
    out << "black level\t\t"      << Info[11] << endl;

    // optional, as QFile destructor will already do it:
    file.close();
}

void CamView::on_acquireButton_clicked()
//callback of the acquire button, gets one picture from the pylon proxy in single shot mode and updates the display
{
    hProxy->acquire(pBuffer);

    if (subtractBG)
        for (uint k = 0; k < imageSize; k++) pBuffer[k] -= backgroundBuffer[k];

    // have the histograms calculated in a separate thread
    QPolygonF *pointsV = new QPolygonF;
    QPolygonF *pointsH = new QPolygonF;
    WorkerThread *workerThread = new WorkerThread();
    workerThread->setWorkItem(pBuffer, imageWidth, imageHeight, pointsV, pointsH);
    connect(workerThread, &WorkerThread::finished, workerThread, &QObject::deleteLater);
    workerThread->start();

    // draw image in the meantime
    ui->widget->setImage((int16_t*)pBuffer, (int)imageSize, imageWidth, imageHeight);

    // now plot histograms
    if (workerThread->wait(500))
    {
        verticalCurve->setSamples( *pointsV );
        horizontalCurve->setSamples( *pointsH );
        ui->horizontalPlot->replot();
        ui->verticalPlot->replot();
    }
    delete pointsV;
    delete pointsH;
}

void CamView::on_acquireContinuousButton_clicked()
{
//callback of the button that toggles continuous image acquisition
//basically just turns the timer and the proxy on or off
    if (this->ui->acquireContinuousButton->isChecked())
    {
        acquireContinuously = true;

        // connect a timer that fires constantly to grab new frames
        // this way, the gui stays responsive
        connect(&timer, SIGNAL(timeout()), this, SLOT(processFrame()));
        hProxy->startContinuous(pBuffer, numBuffers, bufferSize);
        timer.setSingleShot(false);
        timer.start();
    }
    else
    {
        timer.stop();
        hProxy->stopContinuous();
        acquireContinuously = false;
    }
}

void CamView::on_saveButton_clicked()
{
    //save the current image buffer (or the first image in the ring buffer)
    //to a user-selected file in 16 bit tiff format
    saveTiffImage(pBuffer);
}

void CamView::on_saveDarkImageButton_clicked()
{
    saveTiffImage(backgroundBuffer);
}

void CamView::on_closeButton_clicked()
{
    this->close();
}

void CamView::on_exposureSlider_sliderMoved(int position)
{
    Info[5]  = position;
    hProxy->setInfoArray(&Info[0]);
}

void CamView::on_gainSlider_sliderMoved(int position)
{
    Info[8]  = position;
    hProxy->setInfoArray(&Info[0]);
}

void CamView::on_blackLevelSlider_sliderMoved(int position)
{
    Info[11] = position;
    hProxy->setInfoArray(&Info[0]);
}

void CamView::on_backgroundCheckBox_clicked()
{
    if (ui->backgroundCheckBox->isChecked())
    {
        bool ok;
        // ask user how many dark images to average
        int numBGFrames = QInputDialog::getInt(this, "subtract background image", "How many frames should be averaged for the background image : ", 10, 1, 1000, 1, &ok);

        if (!ok)
        {
            // user clicked "cancel" -> dont collect dark image
            ui->backgroundCheckBox->setChecked(false);
            subtractBG = false;
        }
        else
        {
            // user wants to collect dark image, stop current acquisition if active
            if (acquireContinuously)
            {
                acquireContinuously = false;
                timer.stop();
                hProxy->stopContinuous();
            }
            // now acquire dark images
            for (uint k = 0; k < imageSize; k++) backgroundBuffer[k] = 0;
            hProxy->startContinuous(pBuffer, numBuffers, bufferSize);

            for ( int i = 0; i<numBGFrames; i++)
            {
                int number = hProxy->getFrame();
                if (number != -1)
                {
                    int16_t *buffer = ((int16_t*)pBuffer) + number*imageSize;
                    for (uint k = 0; k < imageSize; k++) backgroundBuffer[k] += buffer[k];
                    hProxy->requeue(number);
                }
            }

            hProxy->stopContinuous();
            // average over the collected frames
            for (uint k = 0; k < imageSize; k++) backgroundBuffer[k] = floor((double)backgroundBuffer[k]/(double)numBGFrames+0.5);

            QString str = QString("dark image, ");
            QTime time = QTime::currentTime();
            str.append(time.toString());
            str.append(QString(", "));
            str.append(QString::number(numBGFrames));
            str.append(QString(" frames"));
            ui->darkImageLabel->setText(str);
            subtractBG = true;
        }
    }
    else
    {
        subtractBG = false;
    }
}

double my_normpdf(double x, double mu, double sigma)
{
//MY_NORMPDF normal distribution
// returns the normalized propability of a normal distribution (gaussian)
// with center mu, spread sigma
    double pi = 3.141592653589793;
    double e = (x-mu)/sigma;
    double p = 1.0/(sqrt(2.0*pi)*sigma) * exp(-(0.5)*e*e);
    return p;
}

void CamView::on_testImageButton_clicked()
{
    //generate a test image with white noise plus a gaussian profile
    //save the image and display it

    if (imageWidth < 100)
    {
        imageHeight = 494;
        imageWidth = 659;
    }

    //initialize the image buffer if it's not available yet
    if (!pBuffer)
    {
        bufferSize = imageWidth*imageHeight*sizeof(int16_t);
        pBuffer = (int16_t*)malloc(bufferSize);
    }
    if (bufferSize == 0)
    {
        delete(pBuffer);
        bufferSize = imageWidth*imageHeight*sizeof(int16_t);
        pBuffer = (int16_t*)malloc(bufferSize);
    }

    double noise_level = QInputDialog::getDouble(this, "noise level", "what should be the average level of noise : ", 0, 150, 1000, 1);

    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0,noise_level);

    for (int k = 0; k < imageHeight; k++)
    {
        for (int j=0; j < imageWidth; j++)
        {
            int i = k*imageWidth+j;
            int dist = sqrt((double)((k-250)*(k-250)+(j-350)*(j-350)));
            //add white noise to every pixel
            pBuffer[i] = distribution(generator);
            if (dist < 200)
            {
                //add gaussian profile if pixel is close to the center
                pBuffer[i] = pBuffer[i] + 200000*my_normpdf(dist, 0.0, 50);
            }
        }
    }
    saveTiffImage(pBuffer);
    ui->widget->setImage(pBuffer, imageWidth*imageHeight, imageWidth, imageHeight);
}

void CamView::on_pushButton_clicked()
{
    QFile file("D:/profile/jdo/desktop/out.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << "This file is generated by Qt\n";
    QTime time = QTime::currentTime();
    out << time.toString();

    QDate date = QDate::currentDate();
    out << date.toString();

    // optional, as QFile destructor will already do it:
    file.close();
}
