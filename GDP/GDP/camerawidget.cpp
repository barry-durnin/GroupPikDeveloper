/*****************************************************************************
Camera widget
Initialises the devices camera and manages the camera functionality
Communicates with the camera widget ui and handles the user events
Stores the images captures and sends the byte data to the server

Authored by Barry Durnin.
******************************************************************************/
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

/**************************************************************************************************************
Constructor
Initialises the camera device
Initialises the camera graphic area to display the image in
 **************************************************************************************************************/
CameraWidget::CameraWidget(TcpClient* pClientConnection, QWidget *parent) : QWidget(parent), ui(new Ui::CameraWidget)
{
    ui->setupUi(this);
    pCamera = NULL;
    pViewFinder = NULL;
    pImageCapture = NULL;
    pLayout = NULL;

	int alignW = (parent->width() - width()) * 0.5f;
	int alignH = (parent->height() - height()) * 0.5f;
	move(alignW, alignH);

	if (!InitialiseCamera())
	{
		qDebug() << "Failed to initialise the camera module";
	}

	pLayout = new QVBoxLayout;
	pLayout->addWidget(pViewFinder);
	ui->CaptureArea->setLayout(pLayout);

	pClient = pClientConnection;
}

/**************************************************************************************************************
Destructor
Clean up the objects
**************************************************************************************************************/
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

/**************************************************************************************************************
Override show event
Trigger the camera start event
**************************************************************************************************************/
void CameraWidget::show()
{
	if (pCamera && pViewFinder)
	{
		pCamera->start();
	}
	QWidget::show();
}

/**************************************************************************************************************
Override show event
Trigger the camera start event
**************************************************************************************************************/
bool CameraWidget::CheckCameraAvailability()
{
    //if (QCameraInfo::availableCameras().count() > 0)
    //{
    //    return true;
    //}
    //else
    //{
    //    return false;
    //}
    return true;
}

/**************************************************************************************************************
Check the devices and create the camera object
Create the graphic view finder object
Create the image processing object
create a signal event when images ares saved (imageSaved signals after the image capture object calls capture)
**************************************************************************************************************/
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

/**************************************************************************************************************
Click button event signaled from the ui
Captures the image within the graphic view
**************************************************************************************************************/
void CameraWidget::on_buttonClick_clicked()
{
	if (pCamera && pImageCapture)
	{
		//on half pressed shutter button
		pCamera->searchAndLock();

		//on shutter button pressed
		int id = pImageCapture->capture();

		//on shutter button released
		pCamera->unlock();
	}
	else
	{
		qDebug() << "Camera has not been initialsed correctly";
	}
}

/**************************************************************************************************************
Close button event signaled from the ui
Stops the camera and emits the CameraWidgetCloseButton signal
**************************************************************************************************************/
void CameraWidget::on_pushButtonClose_clicked()
{
	if (pCamera)
	{
		pCamera->stop();
	}
	emit CameraWidgetCloseButton();
}

/**************************************************************************************************************
Signal captured on image save
Process the raw data into an image
Send the raw information to the server 
Listen for a response (success or fail)
TODO: do not create a client connection. use the main client connection when is is created at a later date
Remove the image from the device
**************************************************************************************************************/
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

#if 0
	//test the byte buffer
	QImage testImage(640, 480, QImage::Format_Indexed8);
	testImage = QImage::fromData(szFile, "PNG");
	if (testImage.save("image.png"))
	{
		qDebug() << "Success";
	}
#endif

	//process
	MessageBaseData* data = NULL;
	if (pClient->IsConnected())
	{
		MessageFileData fileData(szFile);
		Q_ASSERT(pClient->GetMessageManager());
		if (!pClient->GetMessageManager()->CreateMessage(message, &fileData))
		{
			//error
		}
#if 0
		MessageBaseData* tmpdata = pClient->GetMessageManager()->ReadMessage(message);
		if (!tmpdata)
		{
			qDebug() << "Fail";
		}

		MessageFileData* fData = static_cast<MessageFileData*>(tmpdata);
		if (fData->szFile != szFile)
		{
			qDebug() << "Fail";
		}

		QImage testImage1(640, 480, QImage::Format_Indexed8);
		testImage1 = QImage::fromData(fData->szFile, "PNG");
		if (testImage1.save("image.png"))
		{
			qDebug() << "Success";
		}
#endif

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

	//delete the file off the device
	if (!QFile::remove(str))
	{
		qDebug() << "Major error cannot remove the captured image fomr the device";
	}
}
