%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%                                                                        %%
%%%                  Written by Matthew Kontz                              %%
%%%                  Walla Walla College                                   %%
%%%                  Edward F. Cross School of Engineering                 %%
%%%                  February 2001 (Updated in December of 2001)           %%
%%%                  Simulation of a planar three link robot.              %%																								%%%
%%%                                                                        %%
%%%      The purpose of this function is to calculate link angles using    %%		
%%%      inverse kinematics.  This function inputs r and psi (polar        %%
%%%      coordinate for x,y) of the tool frame.                            %%                  %%
%%%                                                                        %%
%%%      This function is called by demobot.  To use, first execute        %%
%%%      demobot.  There are five files needed to run demobot: demobot.m,  %%
%%%      option.m, forkin, invkin and setplot.                             %%
%%%                                                                        %%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [] = invkin(r,psi)
global T1 T2 T3 PT 						% input/ouput variables
global l1 l2 l3 				% constants
sinA=sqrt((3*l3-l1)/(8*l3)+sqrt(((3*l3-l1)/(8*l3))^2-(l3^2-r^2)/(16*l1*l3)));
A=asin(sinA);
d=2*l1*sinA;	
B=acos((r^2+d^2-l3^2)/(2*r*d));
S=sign(psi-pi/2);
if S==0
   S=1;
end
T1=(psi-pi/2-S*(pi/2-A+B))*180/pi;
T2=S*(pi-2*A)*180/pi;
T3=S*(pi-2*A)*180/pi;
%PT=90+T1+T2+T3;
