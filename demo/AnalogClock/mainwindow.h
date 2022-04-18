#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void UpdateClock();

private:
    Ui::MainWindow *ui;

    QTimer mClockTick;
    QGraphicsScene mScene;

    QGraphicsEllipseItem mClockFace;
    QGraphicsLineItem mSecondHand;
    QGraphicsLineItem mMinuteHand;
    QGraphicsLineItem mHourHand;
};
#endif // MAINWINDOW_H
