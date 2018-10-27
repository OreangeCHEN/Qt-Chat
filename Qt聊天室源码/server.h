#ifndef SERVER_H
#define SERVER_H
#include<QDialog>
#include <QTime>
class QFile;
class QTcpServer;//通过新创建QTcpServer对象实现创建一个发送对话框以供用户选择文件发送
class QTcpSocket;
namespace Ui {
class Server;
}

class Server : public QDialog
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent = 0);
    ~Server();
    void initSrv();//初始化服务器
    void refused();//关闭服务器
protected:
    void closeEvent(QCloseEvent *);
private:
    Ui::Server *ui;
    qint16 tPort;
    QTcpServer *tSrv;
    QString fileName;
    QString theFileName;
    QFile *locFile;//待发送的文件
    qint64 totalBytes;//总共需要发送的字节数
    qint64 bytesWritten;//已发送字节数
    qint64 bytesTobeWrite;//待发送字节数
    qint64 payloadSize;//被初始化为一个常量
    QByteArray outBlock;//缓存一次发送的数据
    QTcpSocket *clntConn;//客户端发送的套接字
    QTime time;
private slots:
    void sndMsg();//发送数据
    void updClntProgress(qint64 numBytes);//更新进度条
    void on_sOpenBtn_clicked();

    void on_sSendBtn_clicked();

    void on_sCloseBtn_clicked();

signals:
    void sndFileName(QString fileName);
};

#endif // SERVER_H
