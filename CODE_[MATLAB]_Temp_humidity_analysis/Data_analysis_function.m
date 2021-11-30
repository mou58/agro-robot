function[] = Data_analysis_function()
clear
close all
global tem;
global HUM;
global AG;
global SOIL;
s = serial('COM19','BaudRate',9600,'DataBits',8);
fopen(s);
pause(2)
header1 = 'Date ';
header2 = 'Time';
temp3 = 'Temperature';
tempt=fopen('Temperature.txt','w');
fprintf(tempt, [ header1 ' ' header2 ' ' temp3 '\r\n']);
fclose(tempt);
hum3 = 'Humidity';
humt=fopen('Humidity.txt','w');
fprintf(humt, [ header1 ' ' header2 ' ' hum3 '\r\n']);
fclose(humt);
soil3 = 'Moisture';
soil=fopen('Moisture.txt','w');
fprintf(soil, [ header1 ' ' header2 ' ' soil3 '\r\n']);
fclose(soil);
AG=0;
server=fopen('D:\xampp\htdocs\EMA(FINAL)\res.txt','w');
fprintf(server,[AG ' ' ]);
fclose(server);
pause(1);
%

fprintf(s,'%s\n','F')
pause(2)
tem = fscanf(s)
A  = datestr(date, 'dd/mm/yyyy');
B = datestr(now,'HH:MM');
C = tem;
tempt=fopen('Temperature.txt','a');
fprintf(tempt, '%s %s', [ A ' ' B ' ' C ]);
fprintf(tempt,'\r\n' );
fclose(tempt);
fprintf(s,'%s\n','G')
pause(2)
HUM = fscanf(s)
A  = datestr(date, 'dd/mm/yyyy');
B = datestr(now,'HH:MM');
C = HUM;
humt=fopen('Humidity.txt','a');
fprintf(humt, '%s %s', [ A ' ' B ' ' C ]);
fprintf(humt,'\r\n' );
fclose(humt);
fprintf(s,'%s\n','L')
pause(2)
SOIL = fscanf(s)
A  = datestr(date, 'dd/mm/yyyy');
B = datestr(now,'HH:MM');
C = SOIL;
soil=fopen('Moisture.txt','a');
fprintf(soil, '%s %s', [ A ' ' B ' ' C ]);
fprintf(soil,'\r\n' );
fclose(soil);
%
%
S.control = figure('units','pixels',...
              'position',[1 60 1500 680],...
              'menubar','none',...
              'numbertitle','off',...
              'name','Control_panel',...
              'resize','on');     
set(S.control ,'deletefcn',{@exit})

%%
tmr = timer('Name','Reminder',...
            'Period',75,...  % Update the time every 60 seconds.
            'ExecutionMode','fixedSpacing',...
            'TimerFcn',{@updater}); 
start(tmr);  % Start the timer object.
function [] = updater(hObject, eventdata, handles)
try
fprintf(s,'%s\n','F')
pause(1)
tem = fscanf(s)
fprintf(s,'%s\n','G')
pause(1)
HUM = fscanf(s)
fprintf(s,'%s\n','L')
pause(1)
SOIL = fscanf(s)
server=fopen('D:\xampp\htdocs\EMA(FINAL)\server.txt','w');
fprintf(server, [ tem ' ' HUM ' ' SOIL '\r\n']);
fclose(server);
IRI=str2num(SOIL);
TA=str2num(tem);
HU=str2num(HUM);
if (IRI<10)
AG=((TA+HU)*(100-IRI)*10)
fprintf(s,'%s\n','M')
pause(1);
fprintf(s,'%d\n',AG)
pause(2);
end
if(IRI>10)
   server=fopen('D:\xampp\htdocs\EMA(FINAL)\server.txt','w');
fprintf(server, [ tem ' ' HUM ' ' SOIL '\r\n']);
fclose(server);
pause(15);
server=fopen('D:\xampp\htdocs\EMA(FINAL)\res.txt','rt');
REA= fscanf(server,'%d')
AG=REA
fclose(server);
fprintf(s,'%s\n','M')
pause(.5);
fprintf(s,'%d\n',AG)
pause(1);
end
A  = datestr(date, 'dd/mm/yyyy');
B = datestr(now,'HH:MM');
C = tem;
tempt=fopen('Temperature.txt','a');
fprintf(tempt, '%s %s', [ A ' ' B ' ' C ]);
fprintf(tempt,'\r\n' );
fclose(tempt);
A  = datestr(date, 'dd/mm/yyyy');
B = datestr(now,'HH:MM');
C = HUM;
humt=fopen('Humidity.txt','a');
fprintf(humt, '%s %s', [ A ' ' B ' ' C ]);
fprintf(humt,'\r\n' );
fclose(humt);
A  = datestr(date, 'dd/mm/yyyy');
B = datestr(now,'HH:MM');
C = SOIL;
soil=fopen('Moisture.txt','a');
fprintf(soil, '%s %s', [ A ' ' B ' ' C ]);
fprintf(soil,'\r\n' );
fclose(soil);
%%
humt = fopen('Humidity.txt','rt');
header = textscan(humt,'%s %s %s ',1);  %#ok<NASGU>
data = textscan(humt,'%s %s %s ');
data = cellfun(@(x) strrep(x,',','.'),data,'UniformOutput',false);
clean_data(:,1) = arrayfun(@(x) datenum([data{1}{x} ' ' data{2}{x}]), 1:length(data{1}) )';
clean_data(:,2) = cell2mat(cellfun(@str2num , [data{3}],'UniformOutput',false));
fclose(humt);
datestr(clean_data(:,1))
clean_data(:,2)
subplot(1,3,2)
plot(clean_data(:,1),clean_data(:,2))
datetick         
 title('Humidity')
xlabel('Time in Hour')
ylabel('Humidity in %')
tempt = fopen('Temperature.txt','rt');
header = textscan(tempt,'%s %s %s ',1);  %#ok<NASGU>
data = textscan(tempt,'%s %s %s ');
data = cellfun(@(x) strrep(x,',','.'),data,'UniformOutput',false);
clean_data(:,1) = arrayfun(@(x) datenum([data{1}{x} ' ' data{2}{x}]), 1:length(data{1}) )';
clean_data(:,2) = cell2mat(cellfun(@str2num , [data{3}],'UniformOutput',false));
fclose(tempt);
datestr(clean_data(:,1))
clean_data(:,2)
subplot(1,3,1)
plot(clean_data(:,1),clean_data(:,2))
datetick         
 title('Temperature')
xlabel('Time in Hour')
ylabel('temperature in C')
soil = fopen('Moisture.txt','rt');
header = textscan(soil,'%s %s %s ',1);  %#ok<NASGU>
data = textscan(soil,'%s %s %s ');
data = cellfun(@(x) strrep(x,',','.'),data,'UniformOutput',false);
clean_data(:,1) = arrayfun(@(x) datenum([data{1}{x} ' ' data{2}{x}]), 1:length(data{1}) )';
clean_data(:,2) = cell2mat(cellfun(@str2num , [data{3}],'UniformOutput',false));
fclose(soil);
datestr(clean_data(:,1))
clean_data(:,2)
subplot(1,3,3)
plot(clean_data(:,1),clean_data(:,2))
datetick         
title('Moisture')
xlabel('Time in Hour')
ylabel('Soil Moisture in %')
%%.
catch
end
end
function exit (hObject, eventdata, handles) 
stop(tmr);
delete(tmr);
fclose(s);
close all;
clear all;
end
end