%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% crossover.m
% Tarik Tosun, MAE 345, 12/1/11
% Description:
%   Takes 2 binary strings as a column vector, and a crossover index value.
%   Swaps tails at crossover index.  index given is first value in the
%   tail.
%   It is up to the user to pass in only binary strings (zeros and ones).
% Created: 12/1/11
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function offspring = cross(parents, cross_index)
    L = size(parents,2);    %string length
    %%% Arg Checking %%%
    if(size(parents,1)~=2)
        error('did not recieve two parent strings');
    end
    if(~(cross_index>0 && cross_index<=L))
        error('cross_index out of bounds');
    end
    %%%%%%%%%%%%%%%%%%%%
    offspring = zeros(2,L);
    %swap the tails:
    off_11 = parents(1,1:cross_index-1);
    off_12 = parents(2,cross_index:end);    
    off_21 = parents(2,1:cross_index-1);
    off_22 = parents(1,cross_index:end);
    offspring = [off_11 off_12; off_21 off_22];
end

