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
    mScene.addItem( &mSVGelements.mHourHand );
    mScene.addItem( &mSVGelements.mMinuteHand );
    mScene.addItem( &mSVGelements.mSecondHand );

    // Set the translation origins for the clock hands so that the hands rotate around the bottom center of the hand
    mSVGelements.mSecondHand.setTransformOriginPoint(
        mSVGelements.mSecondHand.rect().x() + mSVGelements.mSecondHand.rect().width() / 2.0,
        mSVGelements.mSecondHand.rect().y() + mSVGelements.mSecondHand.rect().height() );

    mSVGelements.mMinuteHand.setTransformOriginPoint(
        mSVGelements.mMinuteHand.rect().x() + mSVGelements.mMinuteHand.rect().width() / 2.0,
        mSVGelements.mMinuteHand.rect().y() + mSVGelements.mMinuteHand.rect().height() );

    mSVGelements.mHourHand.setTransformOriginPoint(
        mSVGelements.mHourHand.rect().x() + mSVGelements.mHourHand.rect().width() / 2.0,
        mSVGelements.mHourHand.rect().y() + mSVGelements.mHourHand.rect().height() );

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

    // Set the rotation of each hand based on the time
    mSVGelements.mSecondHand.setRotation( 360.0 * ( currentTime.time().second() / 60.0 ) );
    mSVGelements.mMinuteHand.setRotation( 360.0 * ( currentTime.time().minute() / 60.0 ) );
    mSVGelements.mHourHand.setRotation( 360.0 * ( currentTime.time().hour() / 12.0 ) );
}
