%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%                                                                        %%
%%%                  Written by Matt Kontz                                 %%
%%%                  Walla Walla College                                   %%
%%%                  Edward F. Cross School of Engineering                 %%
%%%                  February 2001                                         %%
%%%                  Simulation of a planar three link robot.              %%
%%%                                                                        %%
%%%      The purpose of this program is to simulate a three link planar    %%		
%%%      robot located in the robots lab at Walla Walla College.  This     %%
%%%      robot demo simulates kinematics, inverse kinematics and real-     %%
%%%      time graphical inverse kinematics.                                %%
%%%                                                                        %%
%%%      To operate this program:                                          %% 
%%%           1)     Make sure that demobot, forkin, invkin, setplot       %%
%%%                       and option are in the appropriate path.          %%       
%%%           2)     Execute demobot.                                      %%
%%%           3)     Select on option from the push button gui.            %%
%%%           4)     Have fun!                                             %%
%%%                                                                        %%
%%%      All inverse and forward kinematics equations where derived by     %%
%%%      Matt Kontz.  The inverse kinematics equations come from basic     %%
%%%      high school level math such as the law of cosines, bouble angle   %%
%%%      formulas, trig identities and the quadratic eqaution.  Since      %%
%%%      this robot has three degrees of freedom and in only 2D a third    %% 
%%%      constaint was required.  The second and third joint angles        %%
%%%      are always equal.                                                 %%
%%%                                                                        %%
%%%      demobot.m  This is the main program which also all the            %%
%%%                       following programs.                              %%
%%%      forkin.m    Inputs three link angles and calculates the new       %%
%%%                       position matrices(forward kinematics).           %%
%%%      invkin.m    Inputs the position is spherical coordinates, does    %% 
%%%                       inverse kinematics and find link angles.         %%
%%%      setplot.m   Uses the data calculated in forkin to update the      %%   
%%%                       figure window.                                   %%
%%%      option.m    This program executes the various options: position   %% 
%%%                       sliders, click on target, click and drag and     %%
%%%                       angles sliders.                                  %%
%%%                                                                        %%
%%%      If you have question about this program email Don Riley           %%
%%%      <riledo@wwc.edu> or Matt Kontz <mkontz@mail.com>.  Don Riley is   %%
%%%      the Robotics professor at Walla Walla College and is responsible  %%
%%%      for assigning the class projects that this program is based       %%
%%%      on.  Starting in the fall of 2001 Matt Kontz will start his       %%
%%%      masters degree at Georgia Tech.                                   %% 
%%%                                                                        %%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
clf;clear all;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
global slider1 slider2 slider3 slider4 slider5
global PushBut1 PushBut2 PushBut3 PushBut4 
global x1 y1 x2 y2 x3 y3 xt yt Pt			% position variable
global S1 S2 S3 S4 S5 S6						% position strings 
global pF1 pF2 pF3								% handles for fill
global dis Down          						% handles for text display
global C2 C3 Ct txA tx							% handles for the joint's circle
global J2 J3 Jt 									% handles for the joint's pluses
global L1 L2 L3 Link1 Link2 Link3			% Link matrices
global T1 T2 T3 STOP Chose						% input variables
global l1 l2 l3 rmax rmin Bmax				% constants
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
fig=gcf;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Define Base	
angle=225:15:315;		% get rit of where links overlap
xa=1.125*cos(angle*pi/180);
ya=1.125*sin(angle*pi/180);
xb=[xa .875 .875 2.5  2.5 -2.5 -2.5 -.875 -.875];
yb=[ya -.707107 -1.25 -1.25 -2.875 -2.875 -1.25 -1.25 -.707107];
B=[xb' yb' zeros(size(xb))' ones(size(xb))']';  % Link3 matrix
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Link1 and Link2  
angle=265:-15:105;		% define an arc from 270 to 90 degree r=1.125
xa=1.125*cos(angle*pi/180);
ya=1.125*sin(angle*pi/180);
angle=150:15:210;		% get rit of where links overlap
xc=8.625+1.125*cos(angle*pi/180);
yc=1.125*sin(angle*pi/180);
xL1=[0 7.1875 7.1875 7.72978 xc 7.72978 7.1875 7.1875 0 xa 0];
yL1=[1.125 1.125 .875 .68133 yc -.68133 -.875 -1.125 -1.125 ya 1.125];
Link1=[xL1' yL1' zeros(size(xL1))' ones(size(xL1))']';  % Link1 matrix
Link2=Link1;				% Link1 and Link2 are the same
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Link3  
xL3=[0 2.875 3.125 3.125 4.875 6.625 6.6258 4.875 3.125 3.125 2.875 0 xa 0];
yL3=[1.125*ones(1,3) .875 .875 .25 -.25 -.875 -.875 -1.125*ones(1,3) ya 1.125];
Link3=[xL3' yL3' zeros(size(xL3))' ones(size(xL3))']';  % Link3 matrix
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
l1=8.625;				% distance between frame '1' and '2'
l2=l1;					% distance between frame '2' and '3'
l3=6.125;				% distance between frame '3' and 'tool'
rmax=l1+l2+l3;						% maximum distance between (0,0) and tool frame
rmin=(l2^2+(l1-l3)^2)^0.5;		% minimum distance between (0,0) and tool frame
Bmax=atan2(l1-l3,l2)+pi/2;
x0=0;						% x position of frame '0'	
y0=0;						% y position of frame '0'
x1=x0;					% x position of frame '1'	
y1=y0;					% y position of frame '1'
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
r_i=rmax;				% initial radius
psi_i=90*pi/180;		% initial angle
T1=0;T2=0;T3=0;
forkin
r=rmax;
psi=pi/2;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%           
tx(1)=text(29.7,-11,num2str(rmin),'HorizontalAlignment','right'); 
tx(2)=text(29.7,-4,'Radius','HorizontalAlignment','right');   
tx(3)=text(29.7,3,num2str(0.1*round(10*rmax)),'HorizontalAlignment','right');
tx(4)=text(29.7,11,'0^o','HorizontalAlignment','right'); 
tx(5)=text(29.7,18,'Angle','HorizontalAlignment','right');   
tx(6)=text(29.7,25,[num2str(180),'^o'],'HorizontalAlignment','right');
set(tx,'visible','off')			% sets label on slider and turns off
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
sr = ['r = get(gco,''Value'');' ...		% defines the new radius slider value
      'invkin(r,psi);' ...
      'forkin;' ...
      'setplot;'];% ...			% calls setplot to figure
slider4=uicontrol(fig,'Style','slider','Units','normalized', ...
   	'Position',[0.96 0.1 0.03 0.35],'min',rmin,'max',rmax, ...
   	'Value',r_i,'Callback',sr,'visible','off','BackgroundColor',[1 1 1]); 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
sp = ['psi_last=psi;' ...
   	'psi = get(gco,''Value'');' ...	% defines the new angle slider values
     	'if (psi_last>=pi/2 & psi<pi/2) | (psi_last<pi/2 & psi>=pi/2);' ...
      	'invkin(r,psi_last);' ...		% checks for cross over
        	'step=6;' ...
        	'T1_last=T1;' ...
  			'T2_last=T2;' ...
 	  		'T3_last=T3;' ...
      	'invkin(r,psi);' ...
      	'T1_goal=T1;' ...
      	'T2_goal=T2;' ...
 			'T3_goal=T3;' ...
  			'DeltaT1=(T1_goal-T1_last)/step;' ...
  			'DeltaT2=(T2_goal-T2_last)/step;' ...
   		'DeltaT3=(T3_goal-T3_last)/step;' ...
  			'for n=1:step;' ...		% animated robot from last to goal
     			'T1=T1_last+n*DeltaT1;' ...
     			'T2=T2_last+n*DeltaT2;' ...
     			'T3=T3_last+n*DeltaT3;' ...
       	 	'forkin;' ...
      	  	'setplot;' ...
     			'pause(0);' ...
  			'end;' ...
     	'else;' ...   
   		'invkin(r,psi);' ...
      	'forkin;' ...
      	'setplot;' ...
   	'end'];% ...			% calls setplot to figure
slider5=uicontrol(fig,'Style','slider','Units','normalized', ...
   	'Position',[0.96 0.55 0.03 0.35],'min',0,'max',pi, ...
      'Value',psi_i,'Callback',sp,'visible','off','BackgroundColor',[1 1 1]);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
txA(1)=text(29,17.25,'-90','HorizontalAlignment','right'); 
txA(2)=text(29,22.25,'\theta_{3}','HorizontalAlignment','right');   
txA(3)=text(29,27.25,'90','HorizontalAlignment','right');
txA(4)=text(29,1.5,'-90','HorizontalAlignment','right'); 
txA(5)=text(29,6.5,'\theta_{2}','HorizontalAlignment','right');   
txA(6)=text(29,11.5,'90','HorizontalAlignment','right');
txA(7)=text(29,-14.25,'-90','HorizontalAlignment','right'); 
txA(8)=text(29,-9.25,'\theta_{1}','HorizontalAlignment','right');   
txA(9)=text(29,-4.25,'90','HorizontalAlignment','right');
set(txA,'visible','off')			% sets label on slider and turns off
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
s3 = ['T3 = get(gco,''Value'');' ...		% defines T3 as slider value
      'forkin;' ...
      'setplot;'];		% calls setplot to figure
slider3=uicontrol(fig,'Style','slider','Units','normalized', ...
   	'Position',[0.95 0.7 0.03 0.25],'min',-90,'max',90, ...
      'Value',0,'Callback',s3,'visible','off','BackgroundColor',[.2 .2 .8]);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
s2 = ['T2 = get(gco,''Value'');' ...		% defines T2 as slider value
      'forkin;' ...
      'setplot;'];			% calls setplot to figure
slider2=uicontrol(fig,'Style','slider','Units','normalized', ...
   	'Position',[0.95 0.375 0.03 0.25],'min',-90,'max',90, ...
      'Value',0,'Callback',s2,'visible','off','BackgroundColor',[.8 .9 .2]);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
s1 = ['T1 = get(gco,''Value'');' ...		% defines T1 as slider value
      'forkin;' ...
   	'setplot;'];			% calls setplot to figure
slider1=uicontrol(fig,'Style','slider','Units','normalized', ...
   	'Position',[0.95 0.05 0.03 0.25],'min',-90,'max',90, ...
      'Value',0,'Callback',s1,'visible','off','BackgroundColor',[.2 .8 .2]);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
P1 = ['option(1,4);'];	
PushBut1=uicontrol(fig,'Style','pushbutton','Units','normalized', ...
   	'Position',[0.10 .02 0.17125 0.05],'string','Position-Sliders', ...
      'Callback',P1,'visible','on','BackgroundColor',[0.8 0.8 0.8]);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
P2 = ['option(2,0)'];
PushBut2=uicontrol(fig,'Style','pushbutton','Units','normalized', ...
   	'Position',[0.30125 .02 0.17125 0.05],'string','Click on Target', ...
      'Callback',P2,'visible','on','BackgroundColor',[0.8 0.8 0.8]);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
P3 = ['option(3,0);'];	
PushBut3=uicontrol(fig,'Style','pushbutton','Units','normalized', ...
   	'Position',[0.5025 .02 0.17125 0.05],'string','Click and Drag', ...
      'Callback',P3,'visible','on','BackgroundColor',[0.8 0.8 0.8]);   
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
P4 = ['option(4,4)'];
PushBut4=uicontrol(fig,'Style','pushbutton','Units','normalized', ...
   	'Position',[0.70375 .02 0.17125 0.05],'string', 'Angle-Sliders', ...
      'Callback',P4,'visible','on','BackgroundColor',[0.8 0.8 0.8]);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
P5 = ['close;'];	
PushBut5=uicontrol(fig,'Style','pushbutton','Units','normalized', ...
   	'Position',[0.1 .92 0.17 0.05],'string','EXIT', ...
      'Callback',P5,'visible','on','BackgroundColor',[0.8 0.8 0.8]);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
HELP=0;
P6 = ['if HELP==0;' ...
      'set(Help,''visible'',''on'');' ...
      'set(Help_mes,''visible'',''on'');' ...   
   	'set(pF1,''visible'',''off'');' ...    
  		'set(pF2,''visible'',''off'');' ...  
   	'set(pF3,''visible'',''off'');' ... 
   	'set(C2,''visible'',''off'');' ... 
      'set(C3,''visible'',''off'');' ... 
      'set(Ct,''visible'',''off'');' ... 
      'set(J2,''visible'',''off'');' ... 
      'set(J3,''visible'',''off'');' ... 
      'set(Jt,''visible'',''off'');' ...
   	'set(dis,''visible'',''off'');' ...   
   	'set(PushBut6,''string'',''HIDE HELP'');' ...
   	'HELP=1;' ...
   	'else;' ...
      'set(Help,''visible'',''off'');' ...
      'set(Help_mes,''visible'',''off'');' ...   
      'set(pF1,''visible'',''on'');' ...    
  		'set(pF2,''visible'',''on'');' ...  
   	'set(pF3,''visible'',''on'');' ... 
   	'set(C2,''visible'',''on'');' ... 
      'set(C3,''visible'',''on'');' ... 
      'set(Ct,''visible'',''on'');' ... 
      'set(J2,''visible'',''on'');' ... 
      'set(J3,''visible'',''on'');' ... 
      'set(Jt,''visible'',''on'');' ... 
      'set(dis,''visible'',''on'');' ... 
      'set(PushBut6,''string'',''HELP'');' ...
      'HELP=0;' ...
      'end;'];	
PushBut6=uicontrol(fig,'Style','pushbutton','Units','normalized', ...
   	'Position',[0.70375 .92 0.17 0.05],'string','HELP', ...
      'Callback',P6,'visible','on','BackgroundColor',[0.8 0.8 0.8]);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
figure(1)
title('Three Link Planar Robot','FontSize',14)
%xlabel('X-Position(in)')
%ylabel('Y-Position(in)')
axis([-25 25 -3 25])	% axis limits
axis manual					% set axis to exact manual value(i.e [-25 25 -10 25])
axis equal					% x-scale=y-scale
hold on						% does not erase previous graphs 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
arc=(0:1:180)*pi/180;		% plot desired workspace
arc2=(180:-1:0)*pi/180;
plot([rmax*cos(arc) rmin*cos(arc2) rmax],[rmax*sin(arc) rmin*sin(arc2) 0], ...
   'Color',[.8 .4 .2])
legend('Workspace')
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
grid off						% turns on grid
% manual grid so that axis will be black and grid gray

% minor grid lines
for y=0:1:24
   plot([-24.9 25],[y y],'Color',[.97,.97,.97])
end  
for x=-24:1:24
   plot([x x],[0 25],'Color',[.97,.97,.97])
end 
% major grid lines
for y=0:5:20
   plot([-24.9 25],[y y],'Color',[0.9 0.9 0.9])
end  
for x=-20:5:20
   plot([x x],[0 25],'Color',[.9,.9,.9])
end   
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
plot([rmax*cos(arc) rmin*cos(arc2) rmax],[rmax*sin(arc) rmin*sin(arc2) 0], ...
   'Color',[.8 .4 .2])
pos=[15,20];
lg=legend('Workspace',1); % plot workspace or grid
set(lg,'Position',[0.66 0.815 0.203571 0.0492857])
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
set(gca,'GridLineStyle','-')   	% solid lines
set(gca,'YColor',[0,0,0]) 	% y axis color
set(gca,'XColor',[0,0,0]) 	% y axis color
set(gca,'XTick',[-25:5:25])		% numbers on y-axis
set(gca,'YTick',[0:5:25])			% numbers onf x-axis
set(gca,'Color',[1,1,1]) 			% plot background color
set(gca,'FontSize',8);				
set(gcf,'Color',[.95,.95,.95])	% edge background color
set(gca,'Position',[0.10 0.11 0.775 0.815])	% size of data windown
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
BF=fill(B(1,:),B(2,:),'r');					% color fill base
set(BF,'FaceColor',[.8 .3 .3]);
pF1=fill(L1(1,:),L1(2,:),'g', 'erasemode','xor');	% color fill link1
set(pF1,'FaceColor',[.2 .8 .2]);
pF2=fill(L2(1,:),L2(2,:),'y', 'erasemode','xor');	% color fill link2
set(pF2,'FaceColor',[.8 .9 .2]);
pF3=fill(L3(1,:),L3(2,:),'b','erasemode','xor');	% color fill link3
set(pF3,'FaceColor',[.2 .2 .8]);
plot(x1,y1,'om');					% circle at joint '1'
C2=plot(x2,y2,'ob', 'erasemode','xor');		% circle at joint '2'
C3=plot(x3,y3,'oy', 'erasemode','xor');		% circle at joint '3'
Ct=plot(xt,yt,'oy', 'erasemode','xor');		% circle at joint 'T'
plot(x1,y1,'+m');					% plus at joint '1'
J2=plot(x2,y2,'+b', 'erasemode','xor');		% plus at joint '2'
J3=plot(x3,y3,'+y', 'erasemode','xor');		% plus at joint '3'
Jt=plot(xt,yt,'+y', 'erasemode','xor');		% plus at joint 'T'
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
dis(1)=fill([-15.5 -15.5 15.5 15.5 -15.5],[-9 -4 -4 -9 -9],'w'); % plot a white box
dis(2)=plot([-15.5 -15.5 15.5 15.5 -15.5],[-9 -4 -4 -9 -9],'k');	% box's black outline
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
yrange = axis;
vspace = (yrange(4) - yrange(3))/20;
px=-14;
py=-5.5;
dis(3)=text(px, py,            	mat2str(S1),'erasemode','xor');			% theta 1
dis(4)=text(px,(py-1.2*vspace), 	mat2str(S2),'erasemode','xor');		% xt
dis(5)=text(px+11, py,            	mat2str(S3),'erasemode','xor');		% theta2
dis(6)=text(px+11,(py-1.2*vspace), mat2str(S4),'erasemode','xor');		% yt
dis(7)=text(px+21, py,            	mat2str(S5),'erasemode','xor');		% theta3
dis(8)=text(px+21,(py-1.05*vspace), mat2str(S6),'erasemode','xor');		% phi
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
px=-24;
py=24;
text(px, py,'Matthew Kontz','FontSize',8);			
text(px,(py-1*vspace),'Walla Walla College','FontSize',8);		
text(px,(py-2*vspace),'February 2001','FontSize',8);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
set(gco,'BackingStore','off')					% for realtime inverse kinematics
set(gco,'Units','data')
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Help(1)=fill([-20 20 20 -20 -20 ],[20 20 -10 -10 20],'w'); % plot a white box
Help(2)=plot([-20 20 20 -20 -20 ],[20 20 -10 -10 20],'k');	% box's black outline
set(Help,'visible','off')
Help_mes(1)=text(-19,19,'There are four different ways you can manipulate this');
Help_mes(2)=text(-19,17,'three link planar robot.  Here are your choices.');
Help_mes(3)=text(-19,15,'Position sliders: For this option you can change r and \phi ');
Help_mes(4)=text(-19,13,'   by moving the sliders. (r and \phi are the polar coordinate');
Help_mes(5)=text(-19,11,'   equivalent of x and y in Cartesian coordinates.)');
Help_mes(6)=text(-19,9,'Click on Target: You click on any point inside the work-');
Help_mes(7)=text(-19,7,'   space and watch the robot move into that position.');
Help_mes(8)=text(-19,5,'Click and Drag:  Simply hold down your mouse button');
Help_mes(9)=text(-19,3,'   and drag the end of the robot around the workspace');
Help_mes(10)=text(-19,1,'   for real-time graphical inverse kinematics.');
Help_mes(11)=text(-19,-1,'Angle sliders: This allow you to manually change each');
Help_mes(12)=text(-19,-3,'   link and watch how the robot moves.');
Help_mes(13)=text(-19,-9,'To make a selection, click on one of the buttons below.');
Help_mes(14)=text(-19,-5,'NOTE:  \theta_{1},\theta_{2}, and \theta_{3} are joints space angles.  X_{t},Y_{t},');
Help_mes(15)=text(-19,-7,'   and \phi_{t} are the position and angle of the tool frame.');
set(Help_mes,'visible','off')