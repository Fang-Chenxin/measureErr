#include "Data.h"

/**
 * @brief 赋值给value
 * 
 * @param input 读取到的值
 */
void Data::init(const QList<double> input)
{
    value = input;
    update();
}

/**
 * @brief 计算平均值
 * 
 */
void Data::meanCal()
{
    double sum=0;
    for (int i=0;i<value.length();i++)
    {
        sum += value[i];
    }
    mean = sum/value.length();
}

/**
 * @brief 计算残差
 * 
 */
void Data::regCal()
{
    reg.clear();
    for (int i=0;i<value.length();i++)
    {
        reg.push_back(value[i]-mean);
    }
}

/**
 * @brief 计算方差
 * 
 */
void Data::varCal()
{
    var = 0;
    for (int i=0;i<reg.length();i++)
    {
        var += abs(reg[i]*reg[i]);
    }
    var /= (reg.length()-1);
}

/**
 * @brief 计算标准差
 * 
 */
void Data::stdCal()
{
    std = sqrt(var);
}

/**
 * @brief 更新基础信息（调用四个无返回值私有函数）
 * 
 */
void Data::update()
{
    meanCal();
    regCal();
    varCal();
    stdCal();
}

/**
 * @brief 计算残差绝对值最大值
 * 
 * @return int 最大值位置
 */
int Data::regAbsMaxCal()
{
    int pos = 0;
    regAbsMax = abs(reg[0]);
    for (int i=1;i<reg.length();i++)
    {
        if (regAbsMax < abs(reg[i]))
        {
            regAbsMax = abs(reg[i]);
            pos=i;
        }
    }
    return pos;
}

/**
 * @brief 检查粗大误差（删除值移至deleted）
 * 
 * @param group 置信标准
 */
void Data::check(int group)
{
    int pos;
    bool deleteNum = true;
    double t;
    double T_95[98] =  {1.153,1.463,1.672,1.822,1.938,2.032,2.110,2.176,2.234,2.285,2.331,2.371,2.409,2.443,2.475,2.501,2.532,2.557,
            2.580,2.603,2.624,2.644,2.663,2.681,2.698,2.714,2.730,2.745,2.759,2.773,2.786,2.799,2.811,2.823,2.835,2.846,2.857,2.866,
            2.877,2.887,2.896,2.905,2.914,2.923,2.931,2.940,2.948,2.956,2.943,2.971,2.978,2.986,2.992,3.000,3.006,3.013,3.019,3.025,
            3.032,3.037,3.044,3.049,3.055,3.061,3.066,3.071,3.076,3.082,3.087,3.092,3.098,3.102,3.107,3.111,3.117,3.121,3.125,3.130,
            3.134,3.139,3.143,3.147,3.151,3.155,3.160,3.163,3.167,3.171,3.174,3.179,3.182,3.186,3.189,3.193,3.196,3.201,3.204,3.207};
    double T_99[98] =  {1.155,1.492,1.749,1.944,2.097,2.22,2.323,2.410,2.485,2.550,2.607,2.659,2.705,2.747,2.785,2.821,2.954,2.884,
            2.912,2.939,2.963,2.987,3.009,3.029,3.049,3.068,3.085,3.103,3.119,3.135,3.150,3.164,3.178,3.191,3.204,3.216,3.228,3.240,
            3.251,3.261,3.271,3.282,3.292,3.302,3.310,3.319,3.329,3.336,3.345,3.353,3.361,3.388,3.376,3.383,3.391,3.397,3.405,3.411,
            3.418,3.424,3.430,3.437,3.442,3.449,3.454,3.460,3.466,3.471,3.476,3.482,3.487,3.492,3.496,3.502,3.507,3.511,3.516,3.521,
            3.525,3.529,3.534,3.539,3.543,3.547,3.551,3.555,3.559,3.563,3.567,3.570,3.575,3.579,3.582,3.586,3.589,3.593,3.597,3.600};
    deleted = {};
    while (deleteNum)
    {
        switch (group) {
        case 95:
            t = T_95[value.length()-2];
            break;
        case 99:
            t = T_99[value.length()-2];
            break;
        default:
            t = 0;
            break;
        }
        pos = regAbsMaxCal();
        if (regAbsMax > t*std)
        {
            deleted.push_back(value[pos]);
            value.removeAt(pos);
            update();
        }
        else
        {
            deleteNum = false;
        }
    }
}


/**
 * @brief 判断是否为累进性误差（调用regAbsMaxCal）
 * 
 * @return true 是
 * @return false 否
 */
bool Data::accErrJudge()
{
    double sum = 0;
    int end = floor(value.length()/2);
    for (int i=0;i<end;i++)
    {
        sum += abs(value[i] - value[i+end]);
    }
    return sum > regAbsMax;
}

/**
 * @brief 判断是否为周期性误差
 * 
 * @return true 是
 * @return false 否
 */
bool Data::perErrJudge()
{
    double sum = 0;
    for (int i=0;i<reg.length()-1;i++)
    {
        sum += reg[i]*reg[i+1];
    }
    return abs(sum) > sqrt(reg.length())*var;
}

/**
 * @brief 计算置信区间
 * 
 * @param int 置信标准
 */
void Data::confidence(int group)
{
    double T_95[100] = {
        12.70620474,4.30265273,3.182446305,2.776445105,2.570581836,2.446911851,2.364624252,2.306004135,2.262157163,2.228138852,
        2.20098516,2.17881283,2.160368656,2.144786688,2.131449546,2.119905299,2.109815578,2.10092204,2.093024054,2.085963447,
        2.079613845,2.073873068,2.06865761,2.063898562,2.059538553,2.055529439,2.051830516,2.048407142,2.045229642,2.042272456,
        2.039513446,2.036933343,2.034515297,2.032244509,2.030107928,2.028094001,2.026192463,2.024394164,2.02269092,2.02107539,
        2.01954097,2.018081703,2.016692199,2.015367574,2.014103389,2.012895599,2.011740514,2.010634758,2.009575237,2.008559112,
        2.00758377,2.006646805,2.005745995,2.004879288,2.004044783,2.003240719,2.002465459,2.001717484,2.000995378,2.000297822,
        1.999623585,1.998971517,1.998340543,1.997729654,1.997137908,1.996564419,1.996008354,1.995468931,1.994945415,1.994437112,
        1.993943368,1.993463567,1.992997126,1.992543495,1.992102154,1.99167261,1.991254395,1.990847069,1.99045021,1.990063421,
        1.989686323,1.989318557,1.98895978,1.988609667,1.988267907,1.987934206,1.987608282,1.987289865,1.9869787,1.986674541,
        1.986377154,1.986086317,1.985801814,1.985523442,1.985251004,1.984984312,1.984723186,1.984467455,1.984216952,1.983971519
    };
    double T_99[100] = {
        63.65674116,9.924843201,5.84090931,4.604094871,4.032142984,3.707428021,3.499483297,3.355387331,3.249835542,3.169272673,
        3.105806516,3.054539589,3.012275839,2.976842734,2.946712883,2.920781622,2.89823052,2.878440473,2.860934606,2.84533971,
        2.831359558,2.818756061,2.807335684,2.796939505,2.787435814,2.778714533,2.770682957,2.763262455,2.756385904,2.749995654,
        2.744041919,2.738481482,2.733276642,2.728394367,2.723805589,2.71948463,2.715408722,2.711557602,2.707913184,2.704459267,
        2.701181304,2.698066186,2.695102079,2.692278266,2.689585019,2.687013492,2.684555618,2.682204027,2.679951974,2.677793271,
        2.675722234,2.673733631,2.671822636,2.669984796,2.668215988,2.666512398,2.664870482,2.663286954,2.661758752,2.660283029,
        2.658857127,2.657478565,2.656145025,2.654854337,2.653604469,2.652393515,2.651219685,2.650081299,2.648976774,2.647904624,
        2.646863444,2.645851913,2.644868782,2.643912872,2.642983067,2.642078313,2.641197611,2.640340015,2.639504627,2.638690596,
        2.637897113,2.63712341,2.636368757,2.635632458,2.634913852,2.634212309,2.633527229,2.632858038,2.632204191,2.631565166,
        2.630940463,2.630329608,2.629732145,2.629147638,2.628575671,2.628015844,2.627467774,2.626931096,2.626405457,2.625890521
    };
    double delta;
    double t;
    switch (group) {
    case 95:
        t = T_95[value.length()-1];
        break;
    case 99:
        t = T_99[value.length()-1];
        break;
    default:
        t = 0;
    }
    delta = t * std / sqrt(value.length());
    confidence_l = mean - delta;
    confidence_r = mean + delta;
}