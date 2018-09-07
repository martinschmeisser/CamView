/********************************************************************************
** Form generated from reading UI file 'camview.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMVIEW_H
#define UI_CAMVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "imagewidget.h"
#include "qwt_plot.h"

QT_BEGIN_NAMESPACE

class Ui_CamView
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QPushButton *acquireButton;
    QPushButton *acquireContinuousButton;
    QPushButton *saveButton;
    QPushButton *saveDarkImageButton;
    QPushButton *closeButton;
    QGroupBox *groupBox;
    QWidget *gridLayoutWidget_2;
    QFormLayout *formLayout;
    QLabel *exposureTimeLabel;
    QSlider *exposureSlider;
    QLabel *gainLabel;
    QSlider *gainSlider;
    QLabel *blackLevelLabel;
    QSlider *blackLevelSlider;
    QCheckBox *autoAcquireCheckBox;
    QCheckBox *backgroundCheckBox;
    QLabel *darkImageLabel;
    QPushButton *testImageButton;
    QPushButton *pushButton;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout;
    QLabel *statusLabel;
    ImageWidget *widget;
    QwtPlot *horizontalPlot;
    QwtPlot *verticalPlot;

    void setupUi(QWidget *CamView)
    {
        if (CamView->objectName().isEmpty())
            CamView->setObjectName(QStringLiteral("CamView"));
        CamView->resize(1098, 735);
        horizontalLayoutWidget = new QWidget(CamView);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 10, 901, 561));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        acquireButton = new QPushButton(horizontalLayoutWidget);
        acquireButton->setObjectName(QStringLiteral("acquireButton"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(acquireButton->sizePolicy().hasHeightForWidth());
        acquireButton->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(acquireButton);

        acquireContinuousButton = new QPushButton(horizontalLayoutWidget);
        acquireContinuousButton->setObjectName(QStringLiteral("acquireContinuousButton"));
        acquireContinuousButton->setCheckable(true);
        acquireContinuousButton->setChecked(false);

        verticalLayout->addWidget(acquireContinuousButton);

        saveButton = new QPushButton(horizontalLayoutWidget);
        saveButton->setObjectName(QStringLiteral("saveButton"));

        verticalLayout->addWidget(saveButton);

        saveDarkImageButton = new QPushButton(horizontalLayoutWidget);
        saveDarkImageButton->setObjectName(QStringLiteral("saveDarkImageButton"));

        verticalLayout->addWidget(saveDarkImageButton);

        closeButton = new QPushButton(horizontalLayoutWidget);
        closeButton->setObjectName(QStringLiteral("closeButton"));

        verticalLayout->addWidget(closeButton);

        groupBox = new QGroupBox(horizontalLayoutWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setMinimumSize(QSize(0, 100));
        gridLayoutWidget_2 = new QWidget(groupBox);
        gridLayoutWidget_2->setObjectName(QStringLiteral("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(10, 20, 221, 94));
        formLayout = new QFormLayout(gridLayoutWidget_2);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setSizeConstraint(QLayout::SetMinimumSize);
        formLayout->setVerticalSpacing(0);
        formLayout->setContentsMargins(0, 0, 0, 0);
        exposureTimeLabel = new QLabel(gridLayoutWidget_2);
        exposureTimeLabel->setObjectName(QStringLiteral("exposureTimeLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, exposureTimeLabel);

        exposureSlider = new QSlider(gridLayoutWidget_2);
        exposureSlider->setObjectName(QStringLiteral("exposureSlider"));
        exposureSlider->setOrientation(Qt::Horizontal);

        formLayout->setWidget(0, QFormLayout::FieldRole, exposureSlider);

        gainLabel = new QLabel(gridLayoutWidget_2);
        gainLabel->setObjectName(QStringLiteral("gainLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, gainLabel);

        gainSlider = new QSlider(gridLayoutWidget_2);
        gainSlider->setObjectName(QStringLiteral("gainSlider"));
        gainSlider->setOrientation(Qt::Horizontal);

        formLayout->setWidget(1, QFormLayout::FieldRole, gainSlider);

        blackLevelLabel = new QLabel(gridLayoutWidget_2);
        blackLevelLabel->setObjectName(QStringLiteral("blackLevelLabel"));

        formLayout->setWidget(2, QFormLayout::LabelRole, blackLevelLabel);

        blackLevelSlider = new QSlider(gridLayoutWidget_2);
        blackLevelSlider->setObjectName(QStringLiteral("blackLevelSlider"));
        blackLevelSlider->setOrientation(Qt::Horizontal);

        formLayout->setWidget(2, QFormLayout::FieldRole, blackLevelSlider);

        autoAcquireCheckBox = new QCheckBox(gridLayoutWidget_2);
        autoAcquireCheckBox->setObjectName(QStringLiteral("autoAcquireCheckBox"));

        formLayout->setWidget(3, QFormLayout::FieldRole, autoAcquireCheckBox);


        verticalLayout->addWidget(groupBox);

        backgroundCheckBox = new QCheckBox(horizontalLayoutWidget);
        backgroundCheckBox->setObjectName(QStringLiteral("backgroundCheckBox"));

        verticalLayout->addWidget(backgroundCheckBox);

        darkImageLabel = new QLabel(horizontalLayoutWidget);
        darkImageLabel->setObjectName(QStringLiteral("darkImageLabel"));

        verticalLayout->addWidget(darkImageLabel);

        testImageButton = new QPushButton(horizontalLayoutWidget);
        testImageButton->setObjectName(QStringLiteral("testImageButton"));

        verticalLayout->addWidget(testImageButton);

        pushButton = new QPushButton(horizontalLayoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        statusLabel = new QLabel(horizontalLayoutWidget);
        statusLabel->setObjectName(QStringLiteral("statusLabel"));

        gridLayout->addWidget(statusLabel, 0, 0, 1, 1);


        verticalLayout_2->addLayout(gridLayout);

        widget = new ImageWidget(horizontalLayoutWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMinimumSize(QSize(650, 490));

        verticalLayout_2->addWidget(widget);


        horizontalLayout->addLayout(verticalLayout_2);

        horizontalPlot = new QwtPlot(CamView);
        horizontalPlot->setObjectName(QStringLiteral("horizontalPlot"));
        horizontalPlot->setGeometry(QRect(209, 579, 701, 141));
        horizontalPlot->setAutoReplot(true);
        verticalPlot = new QwtPlot(CamView);
        verticalPlot->setObjectName(QStringLiteral("verticalPlot"));
        verticalPlot->setGeometry(QRect(930, 70, 161, 521));

        retranslateUi(CamView);

        QMetaObject::connectSlotsByName(CamView);
    } // setupUi

    void retranslateUi(QWidget *CamView)
    {
        CamView->setWindowTitle(QApplication::translate("CamView", "CamView", 0));
        acquireButton->setText(QApplication::translate("CamView", "acquire image", 0));
        acquireContinuousButton->setText(QApplication::translate("CamView", "acquire continuously", 0));
        saveButton->setText(QApplication::translate("CamView", "save image", 0));
        saveDarkImageButton->setText(QApplication::translate("CamView", "save dark image", 0));
        closeButton->setText(QApplication::translate("CamView", "close", 0));
        groupBox->setTitle(QApplication::translate("CamView", "Camera Controls", 0));
        exposureTimeLabel->setText(QApplication::translate("CamView", "exposure time", 0));
        gainLabel->setText(QApplication::translate("CamView", "gain", 0));
        blackLevelLabel->setText(QApplication::translate("CamView", "black level", 0));
        autoAcquireCheckBox->setText(QApplication::translate("CamView", "auto acquire on change", 0));
        backgroundCheckBox->setText(QApplication::translate("CamView", "subtract dark image", 0));
        darkImageLabel->setText(QString());
        testImageButton->setText(QApplication::translate("CamView", "generate test image", 0));
        pushButton->setText(QApplication::translate("CamView", "random test button", 0));
        statusLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CamView: public Ui_CamView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMVIEW_H
