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

	if (!InitialiseCamera())
	{
		qDebug() << "Failed to initialise the camera module";
		return;
	}

	pLayout = new QVBoxLayout;
	pLayout->addWidget(pViewFinder);
	ui->CaptureArea->setLayout(pLayout);

	//connect(ui->buttonClick, SIGNAL(clicked()), this, SLOT(on_buttonClick_clicked()));
}

CameraWidget::~CameraWidget()
{
	if (pLayout)
	{
		delete pLayout;
		pLayout = NULL;
	}
	if (pViewFinder)
	{
		delete pViewFinder;
		pViewFinder = NULL;
	}
	if (pImageCapture)
	{
		delete pImageCapture;
		pImageCapture = NULL;
	}
	if (pCamera)
	{
		pCamera->stop();
		pCamera->unload();
		pCamera->deleteLater();
		pCamera = NULL;
	}
	if (ui)
	{
		delete ui;
		ui = NULL;
	}
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
			pCamera->setCaptureMode(QCamera::CaptureStillImage);

            pImageCapture = new QCameraImageCapture(pCamera, this);
			QImageEncoderSettings encoder_setting = pImageCapture->encodingSettings();
			encoder_setting.setCodec("image/jpeg");
			encoder_setting.setQuality(QMultimedia::NormalQuality);
			encoder_setting.setResolution(800, 600);
			pImageCapture->setEncodingSettings(encoder_setting);
			connect(pImageCapture, SIGNAL(imageSaved(int, QString)), this, SLOT(processSavedImage(int, QString)));
            return true;
        }
    }
    return false;
}

void CameraWidget::on_buttonClick_clicked()
{
	//on half pressed shutter button
	pCamera->searchAndLock();

	//on shutter button pressed
	int id = pImageCapture->capture();

	//on shutter button released
	pCamera->unlock();
}

void CameraWidget::processSavedImage(int requestId, QString str)
{
	QImage my_image(str);

	//delete the image off the hdd and store it within the app and sed the image to the server for storing
}
