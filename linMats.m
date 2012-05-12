%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% modelMats.m
% Tarik Tosun
% 4/3/12
% MAE 546 Term Project
% function computing linearized model matrices.  All inputs are nominal
% steady-state values.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function [F,G,L] = linMats(x2,x3,x4,u1,u2)
    setup();
    load('params.mat');

    f23 = 2*sin(x3)*(u1/(l^2*m)+x2*x4*sin(2*x3))/cos(x3)^3 +...
          (2*x2*x4*cos(2*x3))/(cos(x3)^2);
    F = [0  1   0   0; ...
         0  (x4*sin(2*x3))/(cos(x3)^2)    f23   (x2*sin(2*x3))/cos(x3)^2;...
         0  0   0   1;...
         0  sin(2*x3)   (g/l)*sin(x3)-x2*cos(2*x3)  0];
         

    G = [0  0;...
         1/(m*l^2*cos(x3)^2)    0;...
         0  0;...
         0  1/(m*l^2);];

    L = G;
end 