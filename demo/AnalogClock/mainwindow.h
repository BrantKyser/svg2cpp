#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QTimer>

#include "generated/SVGelementsAsQGraphicsItems.h"

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
    SVGelements mSVGelements;
};
#endif // MAINWINDOW_H
