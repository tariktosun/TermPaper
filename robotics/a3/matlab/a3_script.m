%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%   a3_script.m
%   Tarik Tosun
%   10/11/11
%   Description:  Script to produce plot for MAE 345 Assignment 3 Part 2.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% plot required equilibrium torques:
m = 2;      %kg
l = 1;      %m
g = 9.807;  %m/s^2

x3_deg = -90:5:90;
x3 = x3_deg*pi/180;
u2 = m*l*g*cos(x3);
plot(x3_deg,u2);
xlabel('x3 (=theta2), in degrees');
ylabel('u2 (torque) in kg*m^2/s^2');
title('Part 2 - Plot of Torque versus Angle for Joint 2 in Equilibrium');