#include "camerawidget.h"

//local
#include "gdp.h"
#include "tcpclient.h"

//message library
#include <gdpmessages.h>
#include <messagebase.h>
#include <messagefile.h>

//QT
#include "ui_camerawidget.h"
#include <QBuffer>
#include <QCamera>
#include <QCameraInfo>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QDebug>
#include <QMessageBox>
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
	QByteArray message = "";
	QImage image(str);
	QByteArray szFile;

	QSize size = image.size();

	if (image.isNull())
	{
		QMessageBox messageBox;
		messageBox.critical(this, "Error", "image cannot be opened");
		messageBox.setFixedSize(500, 200);
		return;
	}

	//convert to qbyte array
	QBuffer buffer(&szFile);
	buffer.open(QIODevice::WriteOnly);
	if (!image.save(&buffer, "PNG"))
	{
		qDebug() << "Failed to create qbyte buffer from captured image";
		return;
	}
	buffer.close();
	

	//delete the image off the hdd and store it within the app and sed the image to the server for storing
	
	//process
	MessageBaseData* data = NULL;
	TcpClient* pClient = new TcpClient(this);
	if (pClient->IsConnected())
	{
		MessageFileData fileData(szFile);
		Q_ASSERT(pClient->GetMessageManager());
		if (!pClient->GetMessageManager()->CreateMessage(message, &fileData))
		{
			//error
		}
	

		pClient->Write(message);
		pClient->Flush();
		pClient->WaitForBytesWritten(1000);

		pClient->WaitForBytesRead();
		data = pClient->GetLastMessage();
		if (data)
		{
			QMessageBox messageBox;
			switch (data->eType)
			{
			case fail:
				messageBox.critical(this, "Error", "Failed to upload photo");
				messageBox.setFixedSize(500, 200);
				break;
			case success:
				break;
			default:
				qDebug() << "Unknown message recieved id: " << data->eType;
				break;
			}
		}
	}

	//close connection
	delete pClient;
	pClient = NULL;

	//delete the file off the device
	if (!QFile::remove(str))
	{
		qDebug() << "Major error cannot remove the captured image fomr the device";
	}
}
