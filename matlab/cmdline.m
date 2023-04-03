clear;clc;
Data=[2.72,2.75,2.65,2.71,2.62,2.45,2.62,2.70,2.67,2.73,2.74];
standard=0.95;
if length(Data)>30 || length(Data)<3
    disp("需输入3到30个数据");
end
%% 去除异常数据
keepon=1;
while keepon
    n=length(Data); 
    meanVal=mean(Data);
    stdVal=std(Data);
    [keepon,Data]=Gcheck(Data,standard,meanVal,stdVal,n);
end
%% 累进性误差
if mod(n,2)
    if sum(Data(1:n-1/2)) - sum(Data((n+1)/2:n)) > max(abs(Data-meanVal))
        disp("存在累进性误差");
    else
        disp("无累进性误差");
    end
else
    if sum(Data(1:n/2)) - sum(Data(n/2+1:n)) > max(abs(Data-meanVal))
        disp("存在累进性误差");
    else
        disp("无累进性误差");
    end
end
Vari = Data - meanVal;
%% 周期性误差
for i=1:n-1
    add = abs(Vari(i)*Vari(i+1));
end
if add > var(Data)*sqrt(n-1)
    disp("存在周期性误差");
else
    disp("无周期性误差");
end
%% 
stdAverage=stdVal/sqrt(n);
t=icdf("T",(1-standard)/2+standard,n-1);
range=[meanVal-t*stdAverage meanVal+t*stdAverage];
out=sprintf('%0.1f%%置信区间[%f,%f]',standard*100,range(1),range(2));
disp(out);


%% 格拉布斯准则
function [ret,retData]=Gcheck(x,standard,meanVal,stdVal,n) 
reg=abs((x-meanVal)./stdVal); 
[reg_max,i]=max(reg); 
%% 确定g值  
T=[1.153 1.463 1.672 1.822 1.938 2.032 2.11 2.176 2.234 2.285 2.331 2.371 2.409 2.443 2.475 2.501 2.532 2.557 2.58 2.603 2.624 2.644 2.663 2.681 2.698 2.714 2.73 2.745;...      
1.155 1.492 1.749 1.944 2.097 2.22 2.323 2.41 2.485 2.55 2.607 2.659 2.705 2.747 2.785 2.821 2.954 2.884 2.912 2.939 2.963 2.987 3.009 3.029 3.049 3.068 3.085  3.103]; 
switch standard
    case 0.95
        g=T(1,n-2); 
    case 0.99          
        g=T(2,n-2); 
    otherwise
        disp('输入了错误的置信概率'); 
end
%% 剔除
if reg_max>g     
    ret=1; 
    out=['剔除异常数据：',num2str(x(i))];
    disp(out);
    x(i)=[];
else
    ret=0;
    disp('无异常数据'); 
end
retData=x;
end
