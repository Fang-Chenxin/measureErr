#ifndef DATA_H
#define DATA_H

#include "qtextbrowser.h"
#include <QWidget>

class Data
{
public:
    QList<double> value;//数据值
    QList<double> deleted;//删除的异常数据
    double mean;//平均值
    double var;//方差
    double confidence_l;//置信区间左值
    double confidence_r;//置信区间右值

    void init(const QList<double>);//输入数据赋值给value
    void printData(QTextBrowser *);//输出到指定文本显示框
    void update();//更新基础信息（调用四个无返回值私有函数）
    void check(int);//检查粗大误差（删除值移至deleted）
    bool accErrJudge();//判断是否为累进性误差（调用regAbsMaxCal）
    bool perErrJudge();//判断是否为周期性误差
    void confidence(int);//计算置信区间
private:
    QList<double> reg;//残差
    double regAbsMax;//残差绝对值最大值

    void meanCal();//计算平均值
    void varCal();//计算方差
    void stdCal();//计算标准差
    void regCal();//计算残差
    int regAbsMaxCal();//计算残差绝对值最大值
};

#endif // DATA_H
