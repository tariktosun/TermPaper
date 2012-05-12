%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% mutate.m
% Tarik Tosun, MAE 345 Assignment 5, 12/1/11
% Description:
%   Flips a bit at a randomly chosen location on a randomly chosen
%   chromosome from generation chrom.
% Created 12/1/11
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function newChrom = mutate(chrom)
    [r,c] = size(chrom);
    index = [randi(r),randi(c)];    %generate a random index.
    newChrom = chrom;
    newChrom(index) = ~newChrom(index); %flip
end