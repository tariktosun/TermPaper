%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%   a3_sysDynamics.m
%   Tarik Tosun
%   MAE 345, 10/11/11
%   Description:  Contains system dynamics information for Assignment 3
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function xdot = a3_sysDynamics(input)
    %%% Break up input vector into components: %%%
    x = input(1:4);
    u = input(5:6);
    m = input(7);
    l = input(8);
    g = input(9);
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    xdot(1) = x(2);
    xdot(2) = (1/(cos(x(3))^2))*(x(2)*x(4)*sin(2*x(3))+u(1)/(m*l^2));
    xdot(3) = x(4);
    xdot(4) = (-g/l)*cos(x(3))-(x(2)/2)*sin(2*x(3))+u(2)/(m*l^2);
end