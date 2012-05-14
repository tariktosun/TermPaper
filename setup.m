%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% setup.m
% exports parameter variables to params.mat.
% for Assignment 4.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function setup()
    d = 1.5;    %m;     height of first link
    m = 2;      %kg;    mass
    l = 1;      %m;     length of second link
    g = 9.807;  %m/s^2; gravity
    
    tfinal = 1000;            % final time, s
    tstep = .1;
    save('params.mat')
end
