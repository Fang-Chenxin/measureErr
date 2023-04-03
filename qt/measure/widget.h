#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "Data.h"
#include "qtextbrowser.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    Data data;//数据类
private slots:
    void readin();//读取数据
    void test();//输入预定义测试数据
private:
    Ui::Widget *ui;
    void DataPrint(QTextBrowser *,QList<double> list);//文本形式输出数据
    void ListPrint(QTextBrowser *,QList<double> list);//列表形式输出数据
    void uiDisplay();//界面显示
    int buttonCheck();//检查置信概率按钮选择
    void errJudge();//判断误差类型
    void process();//处理数据
};
#endif // WIDGET_H

