%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% simulate_sys.m
% Tarik Tosun, MAE 345 Assignment 5, 12/1/11
% Description:
%   Simulates the dynamic system in Assignment 5, returning the actual x
%   vector for the given parameters as well as the fixed nominal x vector.
%
% Created 12/1/11.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function [x,xnom] = simulate_sys(psi,wn)
    % Simulate dynamic system:
    A = [0 1; -wn^2 -2*psi*wn]; %problem spec.
    C = eye(size(A));
    sys = ss(A,[],C,[]);

    t = 0:0.25:10;  %problem spec.
    x0  = [0;1];    %problem spec.
    x = initial(sys,x0,t);
    
    % Fill in the xnom vector (hard coded):
    load('C:\Users\Tarik\Documents\Schoolwork_F12\Robotics\Assignments\A5\MatLab\nom_data');
    xnom = [x1nom, x2nom];
end