%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% fitness.m
% Tarik Tosun, MAE 345 Assignment 5, 12/1/11
% Description:
%
% Created 12/1/11.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function F = fitness(x, xnom)
    %%% Argument Checking %%%
    if(all(size(x)~=size(xnom)))
        error('x and xnom are different sizes.');
    elseif(size(x,2)~=2)
        error('x does not have two columns.');
    end
    %%%%%%%%%%%%%%%%%%%%%%%%%
    xe = x - xnom;                      % calculate error
    xe_vect = reshape(xe,numel(xe),1);   % vectorize
    J = 0.5*(xe_vect')*xe_vect;         % cost function
    F = exp(-J);                        % Fitness is positive-definite.
end