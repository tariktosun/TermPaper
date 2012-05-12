%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% grad_fit.m
% Tarik Tosun, MAE 345 Assignment 5, 12/1/11
% Description:
%   Fitness function for use with fminsearch.
%
% Created 12/1/11
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function F = grad_fit(x)
    psi = x(1);
    wn = x(2);
    [x,xnom] = simulate_sys(psi,wn);
    F = fitness(x,xnom);
end