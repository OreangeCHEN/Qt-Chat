
#ifndef DRAWER_H
#define DRAWER_H
#include<QToolButton>
#include <QToolBox>
#include"widget.h"
#include<QLabel>
class Drawer : public QToolBox
{
    Q_OBJECT
public:
     Drawer(QString username,QWidget *parent = 0,Qt::WindowFlags f=0);


private slots:
     void showChatWidget1();
     void showChatWidget2();
     void showChatWidget3();
     void showChatWidget4();
     void showChatWidget5();
     void showChatWidget6();
     void showChatWidget7();
     void showChatWidget8();
     void showChatWidget9();
     void showChatWidget10();//显示各个用户聊天窗口的函数

     void slot_closeWindow();

private:
     QToolButton *toolBtn1;
     QToolButton *toolBtn2;
     QToolButton *toolBtn3;
     QToolButton *toolBtn4;
     QToolButton *toolBtn5;
     QToolButton *toolBtn6;
     QToolButton *toolBtn7;
     QToolButton *toolBtn8;
     QToolButton *toolBtn9;
     QToolButton *toolBtn10;
       QToolButton *toolBtn11;
         QToolButton *toolBtn12;
     Widget *chatWidget1;
     Widget *chatWidget2;
     Widget *chatWidget3;
     Widget *chatWidget4;
     Widget *chatWidget5;
     Widget *chatWidget6;
     Widget *chatWidget7;
     Widget *chatWidget8;
     Widget *chatWidget9;
     Widget *chatWidget10;//对应聊天窗口对象的指针
     QToolButton *minBtn ;
     QToolButton *closeBbtn ;



};

#endif // DRAWER_H
