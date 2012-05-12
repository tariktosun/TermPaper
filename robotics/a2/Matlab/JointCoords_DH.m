%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% JointCoords_DH.m
% Tarik Tosun, MAE 345, Princeton University
% Created 4/12/12
% Description:
%   Function returning the joint coordinates of a kinematic chain given the
%   Denavit-Hartenberg matrices for its joints in their current state.
%   DH transformation matrices are passed in as a cell array of 4x3
%   matrices.  Returned joint coords vector has coordinates for N+1 joints,
%   where N is the number of transformation matrices (the first joint is
%   the base joint, [0 0 0]).
% Usage;
%   coords[x1,y1,z1;x2,y2,z2;...] = JointCoords_DH(DH_Mats{[1],[2],...});
%
% Last Edited: 4/12/12
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function coords = JointCoords_DH(DH_Mats)
    %check args
    if(~iscell(DH_Mats))
        error('DH_Mats must be a cell array.');
    end
    %%%
    N = size(DH_Mats,2);
    coords = zeros(N+1,3);
    xform = eye(4,4);
    for i=1:N
        %generate xform matrix for this joint:
        xform = xform * DH_Mats{i};
        c = xform * [0 0 0 1]';
        coords(i+1,:) = c(1:3)';
    end
end