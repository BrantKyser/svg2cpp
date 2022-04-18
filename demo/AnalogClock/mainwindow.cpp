#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDateTime>

MainWindow::MainWindow( QWidget * parent )
    : QMainWindow( parent )
    , ui( new Ui::MainWindow )
    , mClockTick( this )
    , mClockFace( -100, -100, 200, 200 )
    , mSecondHand( 0, 0, 0, -100)
    , mMinuteHand( 0, 0, 0, -75)
    , mHourHand( 0, 0, 0, -50)

{
    ui->setupUi( this );

    mScene.setBackgroundBrush( QBrush( Qt::white, Qt::SolidPattern ) );

    mScene.addItem( &mClockFace );
    mScene.addItem( &mSecondHand );
    mScene.addItem( &mMinuteHand );
    mScene.addItem( &mHourHand );

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

    mSecondHand.setRotation( 360.0 * ( currentTime.time().second() / 60.0 ) );
    mMinuteHand.setRotation( 360.0 * ( currentTime.time().minute() / 60.0 ) );
    mHourHand.setRotation( 360.0 * ( currentTime.time().hour() / 12.0 ) );
}
