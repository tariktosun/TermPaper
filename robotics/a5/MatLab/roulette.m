%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% roulette.m
% Tarik Tosun, MAE 345 Assignment 5
% Desription:
%   Simulates one spin of a roulette wheel for genetic alg. strings.
%   Probabilities must sum to 1.
%   Takes COLUMN VECTORS.
%
% Created: 12/1/11
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function selected_string = roulette(strings, probabilities)
    %%% Arg Checking %%%
    if(size(strings,1)~=size(probabilities,1))
        error('strings and probabilities vectors must be same size');
    end
    %if(sum(probabilities)~=1)
    %    error('Sum of probabilities must be 1.');
    %end
    %%%%%%%%%%%%%%%%%%%%

    N = size(strings,1);    %both are COLUMN vectors
    cum_prob = cumsum(probabilities);
    r = rand(); %random number, 0 to 1 uniform
    for i=1:N %check each slice of the wheel
       if(r<=cum_prob(i))
           selected_string = strings(i,:);
           break;
       end
    end
end