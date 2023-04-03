classdef app1_exported < matlab.apps.AppBase

    % Properties that correspond to app components
    properties (Access = public)
        UIFigure           matlab.ui.Figure
        Panel_2            matlab.ui.container.Panel
        Label_16           matlab.ui.control.Label
        Button_4           matlab.ui.control.Button
        Label              matlab.ui.control.Label
        TextArea           matlab.ui.control.TextArea
        Button             matlab.ui.control.Button
        ButtonGroup        matlab.ui.container.ButtonGroup
        Button_3           matlab.ui.control.RadioButton
        Button_2           matlab.ui.control.RadioButton
        Label_3            matlab.ui.control.Label
        Label_4            matlab.ui.control.Label
        Panel              matlab.ui.container.Panel
        Label_15           matlab.ui.control.Label
        EditField_10       matlab.ui.control.NumericEditField
        EditField_10Label  matlab.ui.control.Label
        EditField_9        matlab.ui.control.NumericEditField
        EditField_9Label   matlab.ui.control.Label
        EditField_8        matlab.ui.control.NumericEditField
        EditField_8Label   matlab.ui.control.Label
        EditField_7        matlab.ui.control.NumericEditField
        Label_14           matlab.ui.control.Label
        UITable            matlab.ui.control.Table
        UITable2           matlab.ui.control.Table
        Label_5            matlab.ui.control.Label
        EditField_6        matlab.ui.control.NumericEditField
        EditField_6Label   matlab.ui.control.Label
        EditField_5        matlab.ui.control.NumericEditField
        Label_13           matlab.ui.control.Label
        EditField_4        matlab.ui.control.EditField
        Label_12           matlab.ui.control.Label
        Label_11           matlab.ui.control.Label
        Lamp_2             matlab.ui.control.Lamp
        Label_10           matlab.ui.control.Label
        Lamp               matlab.ui.control.Lamp
        Label_9            matlab.ui.control.Label
        EditField_3        matlab.ui.control.NumericEditField
        Label_8            matlab.ui.control.Label
        EditField_2        matlab.ui.control.NumericEditField
        Label_7            matlab.ui.control.Label
    end

    
    properties (Access = public)
        Deleted=[];%异常数据
        Data=[];%有效数据
        cnt=0;%异常数据数
    end
    
    methods (Access = private)
        
        function [ret,retData]=Gcheck(app,x,meanVal,stdVal,n)%格拉布斯准则
        reg=abs((x-meanVal)./stdVal); 
        [reg_max,i]=max(reg); 
        %% 确定g值  
        T=[1.153 1.463 1.672 1.822 1.938 2.032 2.11 2.176 2.234 2.285 2.331 2.371 2.409 2.443 2.475 2.501 2.532 2.557 2.58 2.603 2.624 2.644 2.663 2.681 2.698 2.714 2.73 2.745;...      
           1.155 1.492 1.749 1.944 2.097 2.22 2.323 2.41 2.485 2.55 2.607 2.659 2.705 2.747 2.785 2.821 2.954 2.884 2.912 2.939 2.963 2.987 3.009 3.029 3.049 3.068 3.085  3.103]; 
        if app.Button_2.Value==true
                g=T(1,n-2); 
        else         
                g=T(2,n-2); 
        end
        %% 剔除
        if reg_max>g     
            ret=1;
            app.cnt=app.cnt+1;
            app.Deleted(app.cnt)=x(i);
            x(i)=[];
        else
            ret=0;
        end
        retData=x;
        end
    end
    
    methods (Access = public)
        
        function process(app)
            app.Deleted=[];
            app.cnt=0;
            if app.Button_2.Value==true
                standard=0.95;
            else
                standard=0.99;
            end                
            keepon=1;
            %% 剔除异常数据
            while keepon
                n=length(app.Data); 
                meanVal=mean(app.Data);
                stdVal=std(app.Data);
                [keepon,app.Data]=Gcheck(app,app.Data,meanVal,stdVal,n);
            end
            app.UITable.Data=app.Data;%有效数据
            app.UITable2.Data=app.Deleted';%异常数据
            app.EditField_5.Value=n;%有效数据数
            app.EditField_6.Value=app.cnt;%异常数据数
            app.EditField_2.Value=meanVal;%平均值
            app.EditField_3.Value=stdVal;%标准差估计值
            Vari = app.Data - meanVal;
            %% 累进性误差
            if mod(n,2)
                app.EditField_7.Value=abs(sum(Vari(1:n-1/2)) - sum(Vari((n+1)/2:n)));
                app.EditField_8.Value=max(abs(Vari-meanVal));
                if app.EditField_7.Value > app.EditField_8.Value                        
                    app.Lamp.Enable='on';
                else                        
                    app.Lamp.Enable='off';
                end
            else
                app.EditField_7.Value=abs(sum(Vari(1:n/2)) - sum(Vari(n/2+1:n)));
                app.EditField_8.Value=max(abs(Vari-meanVal));
                if app.EditField_7.Value > app.EditField_8.Value
                    app.Lamp.Enable='on';
                else
                    app.Lamp.Enable='off';
                end
            end
            %% 周期性误差
            for i=1:n-1
                add = abs(Vari(i)*Vari(i+1));
            end
            app.EditField_9.Value=add;
            app.EditField_10.Value=var(app.Data)*sqrt(n-1);
            if app.EditField_9.Value > app.EditField_10.Value
                app.Lamp_2.Enable='on';
            else
                app.Lamp_2.Enable='off';
            end
            %% 置信区间
            stdAverage=stdVal/sqrt(n);
            t=icdf("T",(1-standard)/2+standard,n-1);
            range=[meanVal-t*stdAverage meanVal+t*stdAverage];
            out=sprintf('[%f,%f]',range(1),range(2));
            app.EditField_4.Value=out;
        end
    end
    

    % Callbacks that handle component events
    methods (Access = private)

        % Button pushed function: Button
        function ButtonPushed(app, event)
            input=app.TextArea.Value;
            app.Data=str2double(input);
            n=length(app.Data);
            %% 数据检查
            if n<3
                app.Label_5.Text='至少输入3个数据';
            elseif n>30
                app.Label_5.Text='至多输入30个数据';
            elseif numel(find(isnan(app.Data)))
                app.Label_5.Text='输入数据无效，检测是否存在空行';
            else%开始处理数据
                out=sprintf('已输入%d个数据',n);
                app.Label_5.Text=out;
                process(app);
            end            
        end

        % Button pushed function: Button_4
        function Button_4Pushed(app, event)
            app.Data=[2.72,2.75,2.65,2.71,2.62,2.45,2.62,2.70,2.67,2.73,2.74]';
            app.Label_5.Text='使用测试数据（因舍入位数不太，结果略有差异）';
            process(app);
        end
    end

    % Component initialization
    methods (Access = private)

        % Create UIFigure and components
        function createComponents(app)

            % Create UIFigure and hide until all components are created
            app.UIFigure = uifigure('Visible', 'off');
            app.UIFigure.Position = [100 100 906 475];
            app.UIFigure.Name = 'MATLAB App';

            % Create Panel
            app.Panel = uipanel(app.UIFigure);
            app.Panel.TitlePosition = 'centertop';
            app.Panel.Title = '输出面板';
            app.Panel.FontWeight = 'bold';
            app.Panel.Position = [270 9 624 458];

            % Create Label_7
            app.Label_7 = uilabel(app.Panel);
            app.Label_7.Position = [258 259 41 22];
            app.Label_7.Text = '平均值';

            % Create EditField_2
            app.EditField_2 = uieditfield(app.Panel, 'numeric');
            app.EditField_2.HorizontalAlignment = 'left';
            app.EditField_2.Position = [315 258 94 24];

            % Create Label_8
            app.Label_8 = uilabel(app.Panel);
            app.Label_8.Position = [431 259 41 22];
            app.Label_8.Text = '标准差';

            % Create EditField_3
            app.EditField_3 = uieditfield(app.Panel, 'numeric');
            app.EditField_3.HorizontalAlignment = 'left';
            app.EditField_3.Position = [487 256 94 28];

            % Create Label_9
            app.Label_9 = uilabel(app.Panel);
            app.Label_9.HorizontalAlignment = 'right';
            app.Label_9.Position = [261 154 65 22];
            app.Label_9.Text = '累进性误差';

            % Create Lamp
            app.Lamp = uilamp(app.Panel);
            app.Lamp.Tooltip = {''; ''};
            app.Lamp.Position = [341 160 10 10];

            % Create Label_10
            app.Label_10 = uilabel(app.Panel);
            app.Label_10.HorizontalAlignment = 'right';
            app.Label_10.Position = [258 118 65 22];
            app.Label_10.Text = '周期性误差';

            % Create Lamp_2
            app.Lamp_2 = uilamp(app.Panel);
            app.Lamp_2.Position = [338 124 10 10];

            % Create Label_11
            app.Label_11 = uilabel(app.Panel);
            app.Label_11.HorizontalAlignment = 'center';
            app.Label_11.Position = [322 196 188 26];
            app.Label_11.Text = '灯亮有此类误差，灯灭无此类误差';

            % Create Label_12
            app.Label_12 = uilabel(app.Panel);
            app.Label_12.HorizontalAlignment = 'right';
            app.Label_12.Position = [252 56 53 22];
            app.Label_12.Text = '置信区间';

            % Create EditField_4
            app.EditField_4 = uieditfield(app.Panel, 'text');
            app.EditField_4.Position = [308 49 293 35];

            % Create Label_13
            app.Label_13 = uilabel(app.Panel);
            app.Label_13.HorizontalAlignment = 'right';
            app.Label_13.Position = [258 300 65 22];
            app.Label_13.Text = '有效数据数';

            % Create EditField_5
            app.EditField_5 = uieditfield(app.Panel, 'numeric');
            app.EditField_5.Position = [338 300 71 21];

            % Create EditField_6Label
            app.EditField_6Label = uilabel(app.Panel);
            app.EditField_6Label.HorizontalAlignment = 'right';
            app.EditField_6Label.Position = [427 299 65 22];
            app.EditField_6Label.Text = '异常数据数';

            % Create EditField_6
            app.EditField_6 = uieditfield(app.Panel, 'numeric');
            app.EditField_6.Position = [507 298 75 24];

            % Create Label_5
            app.Label_5 = uilabel(app.Panel);
            app.Label_5.HorizontalAlignment = 'center';
            app.Label_5.FontWeight = 'bold';
            app.Label_5.Position = [298 348 269 46];
            app.Label_5.Text = '未输入数据';

            % Create UITable2
            app.UITable2 = uitable(app.Panel);
            app.UITable2.ColumnName = {'异常数据'};
            app.UITable2.RowName = {};
            app.UITable2.Position = [118 11 106 418];

            % Create UITable
            app.UITable = uitable(app.Panel);
            app.UITable.ColumnName = {'有效数据'};
            app.UITable.RowName = {};
            app.UITable.FontWeight = 'bold';
            app.UITable.Position = [10 11 93 418];

            % Create Label_14
            app.Label_14 = uilabel(app.Panel);
            app.Label_14.HorizontalAlignment = 'right';
            app.Label_14.Position = [372 154 29 22];
            app.Label_14.Text = '左值';

            % Create EditField_7
            app.EditField_7 = uieditfield(app.Panel, 'numeric');
            app.EditField_7.Position = [416 154 59 19];

            % Create EditField_8Label
            app.EditField_8Label = uilabel(app.Panel);
            app.EditField_8Label.HorizontalAlignment = 'right';
            app.EditField_8Label.Position = [504 153 29 22];
            app.EditField_8Label.Text = '右值';

            % Create EditField_8
            app.EditField_8 = uieditfield(app.Panel, 'numeric');
            app.EditField_8.Position = [548 154 53 19];

            % Create EditField_9Label
            app.EditField_9Label = uilabel(app.Panel);
            app.EditField_9Label.HorizontalAlignment = 'right';
            app.EditField_9Label.Position = [372 118 29 22];
            app.EditField_9Label.Text = '左值';

            % Create EditField_9
            app.EditField_9 = uieditfield(app.Panel, 'numeric');
            app.EditField_9.Position = [416 118 59 19];

            % Create EditField_10Label
            app.EditField_10Label = uilabel(app.Panel);
            app.EditField_10Label.HorizontalAlignment = 'right';
            app.EditField_10Label.Position = [504 117 29 22];
            app.EditField_10Label.Text = '右值';

            % Create EditField_10
            app.EditField_10 = uieditfield(app.Panel, 'numeric');
            app.EditField_10.Position = [548 118 53 19];

            % Create Label_15
            app.Label_15 = uilabel(app.Panel);
            app.Label_15.Position = [288 175 272 22];
            app.Label_15.Text = '判据写为左值大于等于右值形式时，左值右值如下';

            % Create Panel_2
            app.Panel_2 = uipanel(app.UIFigure);
            app.Panel_2.TitlePosition = 'centertop';
            app.Panel_2.Title = '输入面板';
            app.Panel_2.FontWeight = 'bold';
            app.Panel_2.Position = [27 9 224 458];

            % Create Label_4
            app.Label_4 = uilabel(app.Panel_2);
            app.Label_4.WordWrap = 'on';
            app.Label_4.Position = [19 265 89 50];
            app.Label_4.Text = {'使用格拉布斯准则判断是否存在异常值'; ''};

            % Create Label_3
            app.Label_3 = uilabel(app.Panel_2);
            app.Label_3.WordWrap = 'on';
            app.Label_3.Position = [19 334 89 74];
            app.Label_3.Text = '换行分隔数据，不能有空行,数据数量3-30';

            % Create ButtonGroup
            app.ButtonGroup = uibuttongroup(app.Panel_2);
            app.ButtonGroup.Title = '置信概率';
            app.ButtonGroup.Position = [14 97 100 71];

            % Create Button_2
            app.Button_2 = uiradiobutton(app.ButtonGroup);
            app.Button_2.Text = '95%';
            app.Button_2.Position = [7 24 58 22];
            app.Button_2.Value = true;

            % Create Button_3
            app.Button_3 = uiradiobutton(app.ButtonGroup);
            app.Button_3.Text = '99%';
            app.Button_3.Position = [7 2 65 22];

            % Create Button
            app.Button = uibutton(app.Panel_2, 'push');
            app.Button.ButtonPushedFcn = createCallbackFcn(app, @ButtonPushed, true);
            app.Button.Position = [22 56 82 30];
            app.Button.Text = '确认输入';

            % Create TextArea
            app.TextArea = uitextarea(app.Panel_2);
            app.TextArea.Position = [119 11 80 397];

            % Create Label
            app.Label = uilabel(app.Panel_2);
            app.Label.HorizontalAlignment = 'right';
            app.Label.WordWrap = 'on';
            app.Label.Position = [135 407 48 21];
            app.Label.Text = '输入数据';

            % Create Button_4
            app.Button_4 = uibutton(app.Panel_2, 'push');
            app.Button_4.ButtonPushedFcn = createCallbackFcn(app, @Button_4Pushed, true);
            app.Button_4.Position = [20 20 87 29];
            app.Button_4.Text = '使用测试数据';

            % Create Label_16
            app.Label_16 = uilabel(app.Panel_2);
            app.Label_16.Position = [19 1 97 22];
            app.Label_16.Text = '即例2-2-6中数据';

            % Show the figure after all components are created
            app.UIFigure.Visible = 'on';
        end
    end

    % App creation and deletion
    methods (Access = public)

        % Construct app
        function app = app1_exported

            % Create UIFigure and components
            createComponents(app)

            % Register the app with App Designer
            registerApp(app, app.UIFigure)

            if nargout == 0
                clear app
            end
        end

        % Code that executes before app deletion
        function delete(app)

            % Delete UIFigure when app is deleted
            delete(app.UIFigure)
        end
    end
end