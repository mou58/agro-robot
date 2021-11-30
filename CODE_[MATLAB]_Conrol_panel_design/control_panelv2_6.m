function [] = control_panelv2_6()
clear
close all
%for opening serial terminal
 s = serial('COM3','BaudRate',9600,'DataBits',8);
 fopen(s);
 pause(2)
 %end
 %figure design
S.control = figure('units','pixels',...
              'position',[180 80 1000 650],...
              'menubar','none',...
              'numbertitle','off',...
              'name','Control_panel',...
              'resize','off'); 
notice = uipanel('Title','Result','FontSize',10,...
             'unit','pix',...  
             'Position',[700 1 300 255]);
control = uipanel('Title','Manual control','FontSize',10,...
             'unit','pix',...  
             'Position',[2 1 465 250]);
Robot_control=uipanel(control,'Title','Robot Control','FontSize',10,...
             'unit','pix',...  
             'Position',[1 1 300 200]);
hand_control=uipanel(control,'Title','ARM Control','FontSize',10,...
             'unit','pix',...  
             'Position',[300 1 165 200]);
Live_p= uipanel('Title','Live','FontSize',10,...
             'unit','pix',...  
             'Position',[280 280 465 370]);
Live= axes('Parent',Live_p,'units','pixels',...
            'position',[1 50 460 320]);
set(Live,'xtick',[],'ytick',[])  % Get rid of ticks.
 set(Live,'Visible','off'); 
%cam selection
Camera= uicontrol(Live_p,'style','push','FontSize',10,...
                 'unit','pix',...
                 'position',[30 10 80 30],...
                 'string','Cam',...
                 'backgroundColor','default',...
                 'fontweight','bold',...
                 'Callback',@sel_cam);
                        
%start button for live cam
start_cam= uicontrol( Live_p,'style','push','FontSize',10,...
                 'unit','pix',...
                 'position',[120 10 100 30],...
                 'fontweight','bold',...
                 'string','Start',...
                 'Callback',@Start_call);

% image capture button
 Quad= uicontrol(Live_p,'style','push','FontSize',10,...
                 'unit','pix',...
                 'position',[225 10 100 30],...
                 'fontweight','bold',...
                 'string','Quad Cam',...
                 'Callback',@Quad_call);

%stop button for live cam
Stop= uicontrol(Live_p,'style','push','FontSize',10,...
                 'unit','pix',...
                 'position',[330 10 100 30],...
                 'fontweight','bold',...
                 'string','Stop',...
                 'Callback',@Stop_video);        
%Robot operation sclection 
Automatic= uicontrol(control,'style','push','FontSize',10,...
                 'unit','pix',...
                 'position',[320 202 100 30],...
                 'fontweight','bold',...
                 'string','Automatic',...
                 'Callback',@auto_call);
             
semi_Automatic= uicontrol(control,'style','push','FontSize',10,...
                 'unit','pix',...
                 'position',[215 202 100 30],...
                 'fontweight','bold',...
                 'string','Semi Auto',...
                 'Callback',@semi_auto_call);
%manual
Manual= uicontrol(control,'style','push','FontSize',10,...
                 'unit','pix',...
                 'position',[110 202 100 30],...
                 'fontweight','bold',...
                 'string','Manual',...
                 'Callback',@manual_call);             
RForward= uicontrol(Robot_control,'style','push','FontSize',10,...
                 'unit','pix',...
                 'position',[98 125 100 40],...
                 'fontweight','bold',...
                 'string','Forward',...
                 'Callback',@robofor);
RStop= uicontrol(Robot_control,'style','push','FontSize',10,...
                 'unit','pix',...
                 'position',[115 85 70 30],...
                 'fontweight','bold',...
                 'string','STOP',...
                 'Callback',@robostop);
RBackward= uicontrol(Robot_control,'style','push','FontSize',10,...
                 'unit','pix',...
                 'position',[98 35 100 40],...
                 'fontweight','bold',...
                 'string','Reverse',...
                 'Callback',@roborev);

RLeft= uicontrol(Robot_control,'style','push','FontSize',10,...
                 'unit','pix',...
                 'position',[3 80 100 40],...
                 'fontweight','bold',...
                 'string','Left',...
                 'Callback',@robolef);
RRight= uicontrol(Robot_control,'style','push','FontSize',10,...
                 'unit','pix',...
                 'position',[193 80 100 40],...
                 'fontweight','bold',...
                 'string','Right',...
                 'Callback',@roborig);
%ARMS 
Initial= uicontrol(hand_control,'style','push','FontSize',10,...
                 'unit','pix',...
                 'position',[10 155 140 25],...
                 'fontweight','bold',...
                 'string','Initial Mode',...
                 'Callback',@initial_call);
picking_mode= uicontrol(hand_control,'style','push','FontSize',10,...
                 'unit','pix',...
                 'position',[10 125 140 25],...
                 'fontweight','bold',...
                 'string','Picking Mode',...
                 'Callback',@picking_call);
picking_auto= uicontrol(hand_control,'style','push','FontSize',10,...
                 'unit','pix',...
                 'position',[10 95 140 25],...
                 'fontweight','bold',...
                 'string','Auto Picking ',...
                 'Callback',@picking_auto_call);
X_value= uicontrol(hand_control,'style','push','FontSize',10,...
                 'unit','pix',...
                 'position',[10 65 140 25],...
                 'fontweight','bold',...
                 'string','Value of "X"',...
                 'Callback',@X_call);
Y_value= uicontrol(hand_control,'style','push','FontSize',10,...
                 'unit','pix',...
                 'position',[10 35 140 25],...
                 'fontweight','bold',...
                 'string','Value of "Y"',...
                 'Callback',@Y_call);
unload= uicontrol(hand_control,'style','push','FontSize',10,...
                 'unit','pix',...
                 'position',[10 5 140 25],...
                 'fontweight','bold',...
                 'string','UNLOAD',...
                 'Callback',@unload_call);
%set notice board
Date_show=uicontrol(notice,'style','text','FontSize',14,...
                 'unit','pix',...
                 'position',[110 213 180 25],...
                 'FontWeight','bold',...
                 'ForegroundColor','white',...
                 'BackgroundColor','black');
date_text=uicontrol(notice,'style','text','FontSize',12,...
                 'unit','pix',...
                 'position',[1 213 100 25],...
                 'string','DATE',...
                 'ForegroundColor','white',...
                 'FontWeight','bold',...
                 'BackgroundColor','blue');             
S.clock= uicontrol(notice,'style','text',...
                 'unit','pix',...
                 'position',[110 183 180 25],...
                 'string',datestr(now,16),...
                 'backgroundc','black',...
                 'fontsize',14,...
                 'fontweight','bold',...
                 'foregroundcolor','white');
time=uicontrol(notice,'style','text','FontSize',12,...
                 'unit','pix',...
                 'position',[1 183 100 25],...
                 'string','TIME',...
                 'ForegroundColor','white',...
                 'FontWeight','bold',...
                 'BackgroundColor','blue');  
total_show= uicontrol(notice,'style','text','FontSize',12,...
                 'unit','pix',...
                 'position',[180 153 110 25],...
                 'FontWeight','bold',...
                 'ForegroundColor','white',...
                 'BackgroundColor','black');
Total_text= uicontrol(notice,'style','text','FontSize',12,...
                 'unit','pix',...
                 'position',[1 153 170 25],...
                 'string','Total Ripe Tomato:',...
                 'ForegroundColor','white',...
                 'FontWeight','bold',...
                 'BackgroundColor','blue');
location_text= uicontrol(notice,'style','text','FontSize',12,...
                 'unit','pix',...
                 'position',[1 123 140 25],...
                 'string','Tomato Location',...
                 'ForegroundColor','white',...
                 'FontWeight','bold',...
                 'BackgroundColor','blue');
location_show= uicontrol(notice,'style','text','FontSize',12,...
                 'unit','pix',...
                 'position',[150 123 140 25],...
                 'FontWeight','bold',...
                 'ForegroundColor','white',...
                 'BackgroundColor','black');
T_Wide_text= uicontrol(notice,'style','text','FontSize',12,...
                 'unit','pix',...
                 'position',[1 93 140 25],...
                 'string','Tomato Size',...
                 'ForegroundColor','white',...
                 'FontWeight','bold',...
                 'BackgroundColor','blue');
tomoto_wide= uicontrol(notice,'style','text','FontSize',12,...
                 'unit','pix',...
                 'position',[150 93 140 25],...
                  'ForegroundColor','white',...
                 'FontWeight','bold',...
                 'BackgroundColor','black');
%timer start
set(Date_show,'String',datestr(date, 'mm/dd/yyyy'));
set(S.control ,'deletefcn',{@exit})
global ac;
ab=0;
ac=0;
global rip;
global location ;
global size ;
l1X=0;
l1Y=0;
% bk=0;
global pi;
pi = timer('Name','Reminder',...
            'Period',40,...  % Update the time every 60 seconds.
            'ExecutionMode','fixedSpacing',...
            'TimerFcn',{@data}); 

function [] = data(hObject, eventdata, handles)
         try
 fprintf(s,'%s\n','X')
pause(.5);
fprintf(s,'%d\n',l1X)
set(temp_show,'String',l1X);
pause(5);
fprintf(s,'%s\n','Y')
pause(.5);
fprintf(s,'%d\n',l1Y)
set(temp_show,'String',l1Y);
pause(10);
catch
end
end
STRT = 60 - str2double(datestr(now,'MM')); % So we can update every minute.
tmr = timer('Name','Reminder',...
            'Period',60,...  % Update the time every 60 seconds.
            'StartDelay',STRT,... % In seconds.
            'TasksToExecute',inf,...  % number of times to update
            'ExecutionMode','fixedSpacing',...
            'TimerFcn',{@updater}); 


start(tmr);  % Start the timer object.
%%
temp_text= uicontrol(notice,'style','push','FontSize',12,...
                 'unit','pix',...
                 'position',[1 63 140 25],...
                 'string','Send Data',...
                 'ForegroundColor','white',...
                 'FontWeight','bold',...
                 'BackgroundColor','blue',...
                 'Callback',@size_call);
temp_show= uicontrol(notice,'style','text','FontSize',12,...
                 'unit','pix',...
                 'position',[150 63 140 25],...
                 'ForegroundColor','white',...
                 'FontWeight','bold',...
                 'BackgroundColor','black');
lamp_on= uicontrol(notice,'style','push','FontSize',12,...
                 'unit','pix',...
                 'position',[20 20 100 30],...
                 'string','LAMP ON',...
                 'ForegroundColor','black',...
                 'FontWeight','bold',...
                 'Callback',@lamp_on_call);
lamp_off= uicontrol(notice,'style','push','FontSize',12,...
                 'unit','pix',...
                 'position',[170 20 100 30],...
                 'string','LAMP OFF',...
                 'ForegroundColor','black',...
                 'FontWeight','bold',...
                 'Callback',@lamp_off_call);
%%

    function [] = updater(hObject, eventdata, handles)
         try
 set(S.clock,'string',datestr(now,16))
catch
end
end
function sel_cam(hObject, eventdata, handles)
% hObject    handle to sel_cam (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% Open GUI to select the camera
sel_camera
% wait until
uiwait
% Bring the camera features
global id es_web_ext
handles.es_web_ext=es_web_ext;
handles.id=id;
if es_web_ext==0
    formato='YUY2_640x480';
    set(Camera,'backgroundcolor','green')
else
    formato='YUY2_720x480';
end
try
    % Create video object
    vid = videoinput('winvideo',id,formato); %#ok<NASGU>
catch
    msgbox('Check the connection of the camera','Camera')
end
end
function Quad_call(hObject, eventdata, handles)
    ab=0;
    pause(.5);
global id es_web_ext
handles.es_web_ext=es_web_ext;
handles.id=id;
if es_web_ext==0
    formato='YUY2_640x480';
else
    formato='YUY2_720x576';
end
try
    % Create video object
    vid = videoinput('winvideo',id,formato);
end
vid = videoinput('winvideo',id,formato);
vid.FramesPerTrigger = 1;
% output would image in RGB color space
vid.ReturnedColorspace = 'rgb';
% tell matlab to start the webcam on user request, not automatically
triggerconfig(vid, 'manual');
% we need this to know the image height and width
vidRes = get(vid, 'VideoResolution');
% image width
imWidth = vidRes(1);
% image height
imHeight = vidRes(2);
% number of bands of our image (should be 3 because it's RGB)
nBands = get(vid, 'NumberOfBands');
% create an empty image container and show it on axPreview
hImage = image(zeros(imHeight, imWidth, nBands), 'parent',Live)
% begin the webcam preview
preview(vid, hImage);
set(Live,'xtick',[],'ytick',[])  % Get rid of ticks.
 set(Live,'Visible','off');
end
function Start_call(hObject, eventdata, handles) 
    closepreview;
 pause(.5);
Live= axes('Parent',Live_p,'units','pixels',...
            'position',[1 50 460 320]);
set(Live,'xtick',[],'ytick',[])  % Get rid of ticks.
global id es_web_ext
handles.es_web_ext=es_web_ext;
handles.id=id;
if es_web_ext==0
    formato='YUY2_640x480';
else
    formato='YUY2_720x480';
end
try
    % Create video object
    vid = videoinput('winvideo',id,formato);
catch
    msgbox('Check the connection of the camera','Camera')
end
set(Live,'xtick',[],'ytick',[])  % Get rid of ticks.
 set(Live,'Visible','off');        
set(vid, 'FramesPerTrigger', Inf);
set(vid, 'ReturnedColorspace', 'rgb')
vid.FrameGrabInterval = 25;

%start the video aquisition here
start(vid)
% Set a loop that stop after 100 frames of aquisition
ab=1;
%video prosessing start
while ab
    data = getsnapshot(vid);
%     data=imresize(data, [480 480]);
%     data = imcrop(data,[200 280 200 480]);
%     data = flipdim(data,2); % obtain the mirror image for displaying
    R=data(:,:,1);
    diff_im = imsubtract(R,rgb2gray(data));
    %Use a median filter to filter out noise
    diff_im = medfilt2(diff_im, [3 3]);
    % Convert the resulting grayscale image into a binary image.
    diff_im = im2bw(diff_im,0.2);
    
    % Remove all those pixels less than 300px
    diff_im = bwareaopen(diff_im,300);
    
    % Label all the connected components in the image.
    bw = bwlabel(diff_im, 8);
    
    % Here we do the image blob analysis.
    % We get a set of properties for each labeled region.
    stats = regionprops(bw, 'BoundingBox', 'Centroid'); %#ok<MRPBW>
    
imshow(data);

    hold on
    l1X=0;
    l1Y=0;
    %This is a loop to bound the red objects in a rectangular box.
    for object = 1:length(stats)
        bb = stats(object).BoundingBox;
        bc = stats(object).Centroid;
        rectangle('Position',bb,'EdgeColor','r','LineWidth',2)
        plot(bc(1),bc(2), '-m+')
        l1X=round(bc(1));
        l1Y=round(bc(2));
        location=strcat('X: ', num2str(round(bc(1))), '    Y: ', num2str(round(bc(2))));
        a=text(bc(1)+15,bc(2), strcat('X: ', num2str(round(bc(1))), '    Y: ', num2str(round(bc(2)))));
        set(a, 'FontName', 'Arial', 'FontWeight', 'bold', 'FontSize', 12, 'Color', 'yellow');
        %%
         %plot(bb(3),bb(4),'-m+')
         fW=(round(bb(3))/12);
         size=strcat('W: ', num2str(round(fW)),'cm','  H: ', num2str(round(bb(4)/12)),'cm');
         set(tomoto_wide,'String',size);
        %%
        rip=strcat(num2str(length(stats)));
         set(total_show,'String',rip);
          set(location_show,'String',location);
    end
    
    hold off
    flushdata(vid);
end
% Both the loops end here.

% Stop the video aquisition.
stop(vid);

% Flush all the image data stored in the memory buffer.
flushdata(vid);
cla(Live,'reset') 
set(Live,'xtick',[],'ytick',[])  % Get rid of ticks.
 set(Live,'Visible','off'); 
end
function Stop_video (hObject, eventdata, handles)
    closepreview;
ab=0;      
cla(Live,'reset') 
set(Live,'xtick',[],'ytick',[])  % Get rid of ticks.
 set(Live,'Visible','off'); 

end
function semi_auto_call (hObject, eventdata, handles) 
set( findall(hand_control, '-property', 'Enable'), 'Enable', 'on')
set( findall(Robot_control, '-property', 'Enable'), 'Enable', 'off')
  ac=1;
end
function auto_call (hObject, eventdata, handles)  
set(findall(Robot_control, '-property', 'Enable'), 'Enable', 'off')
set(findall(hand_control, '-property', 'Enable'), 'Enable', 'off')
end
function manual_call (hObject, eventdata, handles)  
set( findall(Robot_control, '-property', 'Enable'), 'Enable', 'on')
set( findall(hand_control, '-property', 'Enable'), 'Enable', 'on')
stop(pi);
end
function exit (hObject, eventdata, handles)
    closepreview;
    delete(pi);
ab=0;
stop(tmr);
delete(tmr);
fclose(s);
clear all;
close all;
end
function robofor(hObject, eventdata, handles)
fprintf(s,'%s\n','A')
end
function robostop(hObject, eventdata, handles)
fprintf(s,'%s\n','E')
end
function roborev(hObject, eventdata, handles)
fprintf(s,'%s\n','B')
end
function roborig(hObject, eventdata, handles)
fprintf(s,'%s\n','D')
end
function robolef(hObject, eventdata, handles)
fprintf(s,'%s\n','C')
end
function initial_call(hObject, eventdata, handles)
fprintf(s,'%s\n','I')
end
function picking_call(hObject, eventdata, handles)
fprintf(s,'%s\n','H')
end
function X_call(hObject, eventdata, handles)
fprintf(s,'%s\n','X')
pause(.5);
fprintf(s,'%d\n',l1X)
set(temp_show,'String',l1X);
end
function Y_call(hObject, eventdata, handles)
fprintf(s,'%s\n','Y')
pause(.5);
fprintf(s,'%d\n',l1Y)
set(temp_show,'String',l1Y);
end
function unload_call(hObject, eventdata, handles)
fprintf(s,'%s\n','N')
end
function lamp_on_call(hObject, eventdata, handles)
fprintf(s,'%s\n','J')
end
function lamp_off_call(hObject, eventdata, handles)
fprintf(s,'%s\n','K')
end
function picking_auto_call(hObject, eventdata, handles)
start(pi);
end
end