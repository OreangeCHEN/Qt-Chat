#include "server.h"
#include "ui_server.h"
#include<QFile>
#include<QTcpServer>
#include<QTcpSocket>
#include<QMessageBox>
#include<QFileDialog>
#include<QDebug>

Server::Server(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Server)
{
    ui->setupUi(this);
    setFixedSize(456,224);
    tPort=5555;
    tSrv=new QTcpServer(this);
    connect(tSrv,SIGNAL(newConnection()),this,SLOT(sndMsg()));
    initSrv();
}

Server::~Server()
{
    delete ui;
}

void Server::initSrv(){
    payloadSize=64*1024;
    totalBytes=0;
    bytesWritten=0;
    bytesTobeWrite=0;
    ui->sStatusLbl->setText(tr("请选择要传输的文件"));
    ui->progressBar->reset();
    ui->sOpenBtn->setEnabled(true);
    ui->sSendBtn->setEnabled(false);
    tSrv->close();


}//服务器初始状态


void Server::sndMsg(){
    ui->sSendBtn->setEnabled(false);
    clntConn=tSrv->nextPendingConnection();
    connect(clntConn,SIGNAL(bytesWritten(qint64)),this,SLOT(updClntProgress(qint64)));
    ui->sStatusLbl->setText(tr("开始传送文件%1").arg(theFileName));
    locFile=new QFile(fileName);
    if(!locFile->open((QFile::ReadOnly))){
        QMessageBox::warning(this,tr("应用程序"),tr("无法读取文件%1：\n%2").arg(fileName).arg(locFile->errorString()));
        return;
    }//以只读方式打开选中的文件
    totalBytes=locFile->size();//通过size函数获取待发送文件的大小
    QDataStream sendOut(&outBlock,QIODevice::WriteOnly);
    //将发送缓冲区的outBlock封装在一个QDataStream类型的变量中以方便的通过运算符重载<<填写文件头结构
    sendOut.setVersion(QDataStream::Qt_5_8);
    time.start();//计时
    QString curFile=fileName.right(fileName.size()-fileName.lastIndexOf('/')-1);//保留文件名部分
    sendOut<<qint64(0)<<qint64(0)<<curFile;//构造一个临时的文件头将该值追加到totalBytes字段从而完成实际需要发送字节数的记录
    totalBytes+=outBlock.size();
    sendOut.device()->seek(0);//将读写操作设置为从头开始
    sendOut<<totalBytes<<qint64((outBlock.size()-sizeof(qint64)*2));
    bytesTobeWrite=totalBytes-clntConn->write(outBlock);//将该文件头发出同时修改待发送字节数bytesTObyWrite
    outBlock.resize(0);//清空缓冲区
}




void Server::updClntProgress(qint64 numBytes){

    qApp->processEvents();//避免传输大文件时冻结
    bytesWritten+=(int)numBytes;
    if(bytesTobeWrite>0){
      outBlock=locFile->read(qMin(bytesTobeWrite,payloadSize));
      bytesTobeWrite-=(int)clntConn->write(outBlock);
      outBlock.resize(0);
    }else{
        locFile->close();
    }
    ui->progressBar->setMaximum(totalBytes);
    ui->progressBar->setValue(bytesWritten);
    float useTime=time.elapsed();
    double speed=bytesWritten/useTime;
    ui->sStatusLbl->setText(tr("已发送%1MB（%2MB/s）\n共%3MB 已用时：%4s\n估计剩余时间：%5s").arg(bytesWritten/(1024*1024)).arg(speed*1000/(1024*1024),0,'f',2).arg(totalBytes/(1024*1024)).arg(useTime/1000,0,'f',0).arg(totalBytes/speed/1000-useTime/1000,0,'f',0));
    if(bytesWritten==totalBytes){
        locFile->close();
        tSrv->close();
        ui->sStatusLbl->setText(tr("传送文件%1成功").arg(theFileName));

    }
}




























void Server::on_sOpenBtn_clicked()
{
    fileName=QFileDialog::getOpenFileName(this);
    if(!fileName.isEmpty()){
        theFileName=fileName.right(fileName.size()-fileName.lastIndexOf('/')-1);
        ui->sStatusLbl->setText(tr("要传送的文件为：%1").arg(theFileName));
        ui->sSendBtn->setEnabled(true);
        ui->sOpenBtn->setEnabled(false);
    }
}

void Server::on_sSendBtn_clicked()
{
    if(!tSrv->listen(QHostAddress::Any,tPort)){
        qDebug()<<tSrv->errorString();
        close();
        return;

    }
    ui->sStatusLbl->setText(tr("等待对方接收... ..."));
    emit sndFileName(theFileName);
}

void Server::on_sCloseBtn_clicked()
{
    if(tSrv->isListening()){
        tSrv->close();
        if(locFile->isOpen())locFile->close();
        clntConn->abort();
    }
    close();
}

void Server::closeEvent(QCloseEvent *){

    on_sCloseBtn_clicked();
}

void Server::refused(){
    tSrv->close();
    ui->sStatusLbl->setText(tr("对方拒绝接收！"));

}
