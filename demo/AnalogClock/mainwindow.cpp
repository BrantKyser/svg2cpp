#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDateTime>

MainWindow::MainWindow( QWidget * parent )
    : QMainWindow( parent )
    , ui( new Ui::MainWindow )
    , mClockTick( this )
{
    ui->setupUi( this );

    mScene.setBackgroundBrush( QBrush( Qt::white, Qt::SolidPattern ) );

    mScene.addItem( &mSVGelements.mClockFace );
    mScene.addItem( &mSVGelements.mSecondHand );
    mScene.addItem( &mSVGelements.mMinuteHand );
    mScene.addItem( &mSVGelements.mHourHand );

    ui->graphicsView->setScene( &mScene );

    connect( &mClockTick, &QTimer::timeout, this, &MainWindow::UpdateClock );

    mClockTick.setInterval( 1000 );
    mClockTick.start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void
MainWindow::UpdateClock()
{
    QDateTime currentTime = QDateTime::currentDateTime();
    QString currentTimeString( currentTime.toString( "hh:mm:ss" ) );

    qDebug() << "Clock Tick:" <<  currentTimeString;

    mSVGelements.mSecondHand.setRotation( 360.0 * ( currentTime.time().second() / 60.0 ) );
    mSVGelements.mMinuteHand.setRotation( 360.0 * ( currentTime.time().minute() / 60.0 ) );
    mSVGelements.mHourHand.setRotation( 360.0 * ( currentTime.time().hour() / 12.0 ) );
}
