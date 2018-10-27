#ifndef WIDGET_H
#define WIDGET_H
#include <QWidget>
#include<QColorDialog>
class QUdpSocket;
class Server;
#include<QTextCharFormat>
namespace Ui {
    class Widget;
}
enum MsgType{Msg,UsrEnter,UsrLeft,FileName,Refuse};//使用枚举变量区分不同的广播
class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent,QString usrname);
    ~Widget();

protected:
    void usrEnter(QString usrname,QString ipaddr);//处理新用户加入
    void usrLeft(QString usrname,QString time);//处理用户离开
    void sndMsg(MsgType type,QString srvaddr="");//广播UDP地址
    void hasPendingFile(QString usrname,QString srvaddr,QString clntaddr,QString filename);//用于收到文件名UDP信息时判断是否接收该文件
    QString getIP();
    QString getUsr();
    QString getMsg();
    bool saveFile(const QString &filename);
    void closeEvent(QCloseEvent *event);
private:
    Ui::Widget *ui;
    QUdpSocket *udpSocket;
    qint16 port;
    QString uName;
    QString fileName;
    Server *srv;
    QColor color;
private slots:
    void processPendingDatagrams();//接收UDP消息
    void on_sendBtn_clicked();
    void getFileName(QString);//用来获取服务器类sndFileName()信号发送过来的文件名
    void on_sendTBtn_triggered(QAction *arg1);
    void on_sendTBtn_clicked();
    void on_fontCbx_currentFontChanged(const QFont &f);
    void on_sizeCbx_currentIndexChanged(const QString &arg1);
    void on_boldTBtn_clicked(bool checked);
    void on_italicTBtn_clicked(bool checked);
    void on_underlineTBtn_clicked(bool checked);
    void on_colorTBtn_clicked();
    void curFmtChanged(const QTextCharFormat &fmt);
    void on_saveTBtn_clicked();
    void on_clearTBtn_clicked();
    void on_exitBtn_clicked();
};

#endif // WIDGET_H
