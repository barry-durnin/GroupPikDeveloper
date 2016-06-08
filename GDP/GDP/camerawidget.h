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
private:
    void CameraDialogOpen();
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
