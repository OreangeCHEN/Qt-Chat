#ifndef CLIENT_H
#define CLIENT_H
#include<QHostAddress>
#include <QDialog>
#include<QFile>
#include<QTime>
class QTcpSocket;
namespace Ui {
class Client;
}

class Client : public QDialog
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = 0);
    ~Client();
    void setHostAddr(QHostAddress addr);//获取发送端IP地址
    void setFileName(QString name);//获取文件保存路径
protected:
    void closeEvent(QCloseEvent *);
private:
    Ui::Client *ui;
    QTcpSocket *tClnt;
    quint16 blockSize;
    QHostAddress hostAddr;
    qint16 tPort;
    qint64 totalBytes;
    qint64 bytesRecieved;
    qint64 fileNameSize;
    QString fileName;
    QFile *locFile;
    QByteArray inBlock;
    QTime time;
private slots:
    void newConn();//连接到服务器
    void readMsg();//读取文件数据
    void displayErr(QAbstractSocket::SocketError);//显示错误信息

    void on_cCancleBtn_clicked();
    void on_cCloseBtn_clicked();
};

#endif // CLIENT_H
