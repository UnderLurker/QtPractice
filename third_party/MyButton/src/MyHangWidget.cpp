//
// Created by 常笑男 on 2023/10/1.
//

#include "MyHangWidget.h"
#include <QPainter>
#include <QDebug>
#include <QBitmap>
#include <QMouseEvent>
#include <QGuiApplication>
#include <QScreen>
#include <QMouseEvent>
#include <QTimer>
#include <QHostAddress>
#include <QProcess>

MyHangWidget::MyHangWidget(QWidget *_p) : QWidget(_p){
    pos = QPoint();
    setWindowFlags(Qt::FramelessWindowHint | Qt::SubWindow);
    setAttribute(Qt::WA_TranslucentBackground); //不加这个会导致图片边缘有白边
    //强制初始化qrc资源，原因：本代码用于编译静态库，qt中资源文件若要编译就要生成一个cpp文件，需要这个宏
    Q_INIT_RESOURCE(resource);
    memoryImage = new QImage(":/hang/Resources/hang/memory.png");
    cpuImage = new QImage(":/hang/Resources/hang/cpu.png");
    Q_CLEANUP_RESOURCE(resource);

    QScreen *screen = QGuiApplication::primaryScreen();
    move(screen->availableGeometry().width()-memoryImage->size().width()-100,100);
    resize(250,100);

    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&MyHangWidget::timeOut);
    timer->start(1000);
}

void MyHangWidget::paintEvent(QPaintEvent *event) {
    QPen textPen(QBrush(Qt::black),10);
    QFont textFont(tr("Consolas"),20,QFont::Bold);

    QPainter painter(this);
    painter.save();

    QString mem=QString::number(memoryStatus.dwMemoryLoad);
    QString cpu=QString::number(cpuLoad);
    if(memoryStatus.dwMemoryLoad>100||memoryStatus.dwMemoryLoad<0){
        mem = tr("0");
    }
    painter.drawImage(QRect(0,0,50,50),*memoryImage);
    painter.drawImage(QRect(0,50,50,50),*cpuImage);
    painter.setPen(textPen);
    painter.setFont(textFont);
    painter.drawText(QRectF(50,0,200,50),Qt::AlignVCenter,"MEM:"+mem+"%");
    painter.drawText(QRectF(50,50,200,50),Qt::AlignVCenter,"CPU:"+cpu+"%");

    painter.restore();
}

MyHangWidget::~MyHangWidget() {
    timer->stop();
    delete memoryImage;
    delete cpuImage;
    delete timer;
    delete tcpSocket;
}

bool MyHangWidget::event(QEvent *event) {
    auto *mouseEvent = (QMouseEvent*)event;
    switch (event->type()) {
        case QEvent::MouseButtonPress:{
            pos = mouseEvent->globalPos()-geometry().topLeft();
            return true;
        }
        case QEvent::MouseMove:{
            if(pos == QPoint())
                return false;
            move(mouseEvent->globalPos()-pos);
            return true;
        }
        case QEvent::MouseButtonRelease:{
            pos = QPoint();
            return true;
        }
//        case QEvent::Enter:{
//            state = event->type();
//            table->move(window()->pos().x()+20,window()->pos().y()+10);
//            table->show();
//            return true;
//        }
//        case QEvent::Leave:{
//            state = event->type();
//            table->hide();
//            return true;
//        }
        default:
            break;
    }
    return QWidget::event(event);
}

int64_t Filetime2Int64(const FILETIME &ftime)
{
    LARGE_INTEGER li;
    li.LowPart = ftime.dwLowDateTime;
    li.HighPart = ftime.dwHighDateTime;
    return li.QuadPart;
}

int64_t CompareFileTime(const FILETIME& preTime,const FILETIME& nowTime){
    return Filetime2Int64(nowTime) - Filetime2Int64(preTime);
}

void MyHangWidget::timeOut() {
    FILETIME idleTime;
    FILETIME kernelTime;
    FILETIME userTime;
    GetSystemTimes(&idleTime,&kernelTime,&userTime);

    auto idle = CompareFileTime(preIdleTime, idleTime);
    auto kernel = CompareFileTime(preKernelTime, kernelTime);
    auto user = CompareFileTime(preUserTime, userTime);

    if (kernel + user == 0)
        cpuLoad = 0;

    cpuLoad = int(1000.0*(kernel + user - idle) / (kernel + user))/10.0;

    preIdleTime = idleTime;
    preKernelTime = kernelTime;
    preUserTime = userTime;

    memoryStatus.dwLength = sizeof(memoryStatus);
    if(!GlobalMemoryStatusEx(&memoryStatus)){
        qDebug()<<"通过windows获取信息失败";
    }
    update();
//    QProcess cpuProcess;
//    cpuProcess.start("wmic cpu get Name");
//    cpuProcess.waitForFinished();
//    qDebug()<<cpuProcess.readAllStandardOutput().replace("\r","").replace("\n","");

//    QProcess gpuProcess;
//    cpuProcess.start("wmic path win32_VideoController get Name");
//    cpuProcess.waitForFinished();
//    qDebug()<<cpuProcess.readAllStandardOutput().replace("\r","").replace("\n","");
}
