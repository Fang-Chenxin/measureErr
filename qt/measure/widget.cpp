#include "widget.h"
#include "ui_widget.h"
#include "QDebug"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->inputButton,SIGNAL(clicked(bool)),this,SLOT(readin()));//读取数据按钮
    connect(ui->testButton,SIGNAL(clicked(bool)),this,SLOT(test()));//输入预定义测试数据按钮
}

Widget::~Widget()
{
    delete ui;
}

/**
 * @brief 读取数据
 * 
 * @param c 待检测字符
 * @return true 是数字
 * @return false 不是数字
 */
bool isNum(QChar c)
{
    if (c>='0' && c<='9')
        return true;
    else
        return false;
}

/**
 * @brief 读取数据
 * 
 * @param s 待读取字符串
 * @return QList<double> 读取的数据
 */
QList<double> readnum(QString s)
{
    int len = s.length();
    QList<double> numbers;
    bool numExist = false;
    bool negNotExist = true;
    bool dotNotExist = true;    
    QString temp;
    for (int i = 0; i < len; ++i)
    {
        if (isNum(s[i]))//如果是数字
        {
            temp.append(s[i]);//加入临时字符串
            numExist = true;
        }
        else if (s[i] == '-' && negNotExist && not numExist)//如果是负号
        {
            temp.append(s[i]);//加入临时字符串
            negNotExist = false;
        }
        else if (s[i] == '.' && numExist)//如果是小数点
        {
            if (dotNotExist)
            {
                temp.append(s[i]);//加入临时字符串
                dotNotExist=false;
            }
            else//如果已经有小数点了
            {
                numbers.push_back(temp.toDouble());//输出数字
                temp.clear();//清空临时字符串
                numExist = false;
                negNotExist = true;
                dotNotExist = true;
            }
        }
        else//如果不是数字
        {
            if (numExist)//如果之前有数字
            {
                numbers.push_back(temp.toDouble());//输出数字
                temp.clear();//清空临时字符串
                numExist = false;
                negNotExist = true;
                dotNotExist = true;
            }
        }
    }
    if (numExist) numbers.push_back(temp.toDouble());//输出最后一个数字
    return numbers;
}

/**
 * @brief 读取数据
 * 
 */
void Widget::readin()
{
    QString s = ui->plainTextEdit->toPlainText();//读取输入框的数据
    qDebug()<<s;
    data.init(readnum(s));//将数据传入data
    ui->outputBox->append("已输入数据：");
    DataPrint(ui->outputBox,data.value);
    ListPrint(ui->textBrowser,data.value);
    qDebug("input OK");
    if (data.value.length() >= 3 && data.value.length() < 100)
    {
        process();//处理数据
    }
    else if (data.value.length() < 3)
    {
        ui->outputBox->append("至少需要输入3个数据");
    }
    else if (data.value.length() < 100)
    {
        ui->outputBox->append("至多输入100个数据");
    }
    else
    {
        ui->outputBox->append("输入部分出现异常错误（此行不应被输出）");
    }
}

/**
 * @brief 输入预定义测试数据
 * 
 */
void Widget::test()
{
    ui->outputBox->append("使用测试数据（同2-2-6）");
    data.init({2.72,2.76,2.65,2.71,2.62,2.45,2.62,2.70,2.67,2.73,2.74});
    ListPrint(ui->textBrowser,data.value);
    qDebug("input OK");
    process();//处理数据
}

/**
 * @brief 文本形式输出数据
 * 
 */
void Widget::DataPrint(QTextBrowser *p,QList<double> list)
{
    for (int i=0;i<list.length();i++)
    {
        qDebug()<<list[i];
        p->insertPlainText(QString::number(list[i]));
        p->insertPlainText(",");
    }
}

/**
 * @brief 列表形式输出数据
 * 
 */
void Widget::ListPrint(QTextBrowser *p,QList<double> list)
{
    p->clear();
    for (int i=0;i<list.length();i++)
    {
        p->append(QString::number(list[i]));
    }    
}

/**
 * @brief 判断误差类型
 * 
 */
void Widget::errJudge()
{
    if (data.accErrJudge())
    {
        ui->outputBox->append("有累计性误差");
        ui->acc_checkBox->setChecked(1);
    }
    else
    {
        ui->outputBox->append("无累计性误差");
        ui->acc_checkBox->setChecked(0);
    }
    if (data.perErrJudge())
    {
        ui->outputBox->append("有周期性误差");
        ui->per_checkBox->setChecked(1);
    }
    else
    {
        ui->outputBox->append("无周期性误差");
        ui->per_checkBox->setChecked(0);
    }
}

/**
 * @brief 界面显示
 * 
 */
void Widget::uiDisplay()
{
    ui->validNumber->display((int)data.value.length());
    ui->invalidNumber->display((int)data.deleted.length());
    ui->mean_lineEdit->setText(QString::number(data.mean));
    ui->std_lineEdit->setText(QString::number(data.std));
    ui->var_lineEdit->setText(QString::number(data.var));
    ui->conl_lineEdit->setText(QString::number(data.confidence_l));
    ui->conr_lineEdit->setText(QString::number(data.confidence_r));
}

/**
 * @brief 检查置信概率按钮选择
 * 
 * @return int 95%置信概率返回95，99%置信概率返回99，未选择返回0
 */
int Widget::buttonCheck()
{
    int group;
    if (ui->Button95->isChecked())
    {
        group = 95;
        ui->outputBox->append("已选择95%置信概率");
    }
    else if (ui->Button99->isChecked())
    {
        group = 99;
        ui->outputBox->append("已选择99%置信概率");
    }
    else
    {
        group = 0;
    }
    return group;
}

/**
 * @brief 处理数据
 * 
 */
void Widget::process()
{
    int group;
    char con[50];
    group = buttonCheck();//检查置信概率按钮选择
    data.check(group);//检查数据
    ui->outputBox->append("有效数据：");
    DataPrint(ui->outputBox,data.value);
    ListPrint(ui->textBrowser_2,data.value);
    ui->outputBox->append("无效数据：");
    DataPrint(ui->outputBox,data.deleted);
    ListPrint(ui->textBrowser_3,data.deleted);
    qDebug("check OK");

    errJudge();//判断误差类型
    data.confidence(group);//计算置信区间
    sprintf(con,"置信区间[%f,%f]",data.confidence_l,data.confidence_r);
    ui->outputBox->append(con);
    qDebug("finish");

    ui->outputBox->append("计算完毕");
    ui->outputBox->append("");
    uiDisplay();
}




