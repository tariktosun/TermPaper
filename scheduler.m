%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% scheduler.m
% TariC Tosun
% 4/3/12
% MAE 546 Assignment 4
% Interpolates on LQR matrices for gain scheduling.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function C = scheduler(x3)
    if(abs(x3)>90)
        x3 = mod(x3,90);
    end
    
    load('gaintable.mat');
    C = zeros(2,4);
    for i=1:8
        c = interp1(r,K(i,:),x3);
        C(i) = c;
    end
end