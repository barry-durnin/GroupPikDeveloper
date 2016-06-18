/*****************************************************************************
Camera widget
Initialises the devices camera and manages the camera functionality
Communicates with the camera widget ui and handles the user events
Stores the images captures and sends the byte data to the server

Authored by Barry Durnin.
******************************************************************************/

#ifndef CAMERAWIDGET_H
#define CAMERAWIDGET_H

#include <QWidget>

class QCamera;
class QCameraViewfinder;
class QCameraImageCapture;
class QVBoxLayout;

namespace Ui
{
    class CameraWidget;
}

class CameraWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CameraWidget(QWidget *parent = 0);
    ~CameraWidget();
    void show();
signals:
	void CameraWidgetCloseButton();
private slots:
	void on_buttonClick_clicked();
	void on_pushButtonClose_clicked();
	void processSavedImage(int requestId, QString str);
private:
    bool CheckCameraAvailability();
    bool InitialiseCamera();
private:
    Ui::CameraWidget* ui;
    QCamera* pCamera;
    QCameraViewfinder* pViewFinder;
    QCameraImageCapture* pImageCapture;
    QVBoxLayout* pLayout;
};

#endif // CAMERAWIDGET_H
