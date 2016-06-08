#include "camerawidget.h"
#include "ui_camerawidget.h"
#include <QCamera>
#include <QCameraInfo>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QVBoxLayout>

CameraWidget::CameraWidget(QWidget *parent) : QWidget(parent), ui(new Ui::CameraWidget)
{
    ui->setupUi(this);
    pCamera = NULL;
    pViewFinder = NULL;
    pImageCapture = NULL;
    pLayout = NULL;
    InitialiseCamera();

    pLayout = new QVBoxLayout;
    pLayout->addWidget(pViewFinder);
    ui->CaptureArea->setLayout(pLayout);
}

CameraWidget::~CameraWidget()
{
    if(pViewFinder)
    {
        delete pViewFinder;
    }
    if(pImageCapture)
    {
        delete pImageCapture;
    }
    if(pCamera)
    {
        pCamera->stop();
        pCamera->unload();
        pCamera->deleteLater();
    }
    delete ui;
}

//Override the show event
void CameraWidget::show()
{
    CameraDialogOpen();
    QWidget::show();
}

void CameraWidget::CameraDialogOpen()
{
    if(pCamera && pViewFinder)
    {
        pCamera->start();
    }
}

bool CameraWidget::CheckCameraAvailability()
{
    if (QCameraInfo::availableCameras().count() > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool CameraWidget::InitialiseCamera()
{
    if(CheckCameraAvailability())
    {
        QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
        foreach (const QCameraInfo &cameraInfo, cameras)
        {
            QString name = cameraInfo.deviceName();
            if (name == "mycamera")
            {
                pCamera = new QCamera(cameraInfo);
                break;
            }
        }

        if(!pCamera)
        {
            //could not find my camera. select the back facing camera
            pCamera = new QCamera(QCamera::BackFace);
        }

        if(pCamera)
        {
            pViewFinder = new QCameraViewfinder(this);
            pCamera->setViewfinder(pViewFinder);

            pImageCapture = new QCameraImageCapture(pCamera, this);
            return true;
        }
    }
    return false;
}
