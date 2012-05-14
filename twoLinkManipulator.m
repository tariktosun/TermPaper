%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% twoLinkManipulator.m
% Tarik Tosun, Princeton University
% MAE 546 Final Assignment
%
% Returns kinematic chain of total length L corresponding to the two-link
% manipulator used in MAE 546 Term Paper and in MAE 345 Assignment 3.
%
% order: [d, theta, r, alpha]
% Created 5/13/12
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function arm = twoLinkManipulator(L)
    addpath('/home/tarik/tarik_retargeter/chainsolver');
    setup(); load('params.mat');
    
    ls = l*L/(l+d);
    ds = d*L/(l+d);

    orient = inline('[0, 0, 0, 0]','x');
    roll = inline(['[0, 0, ' num2str(ds) ', r]'],'r');    nl(1)=1;
    pitch = inline(['[0, p, ' num2str(ls) ', 0]'],'p');    nl(2)=1;
    
    LB = [-360, -180];
    UB = [360,  180];
    
    names = {'orient', 'roll', 'pitch'};
    DHfuncs = {orient, roll, pitch};
    armJoints = joints(names, LB, UB, '3D_DH', DHfuncs, nl);
    
    % make chain:
    orig = [0 0 0];
    lengths = [ds, ls];
    arm = chain3d(orig, lengths, armJoints);
end