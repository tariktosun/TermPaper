%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% randomCross.m
% Tarik Tosun, MAE 345 Assignment 5, 12/1/11
% Description:
%
% Created 12/1/11
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function newChrom = randomCross(chrom)
    [N,L] = size(chrom);
    shuffledChrom = chrom(randperm(N),:);
    newChrom = zeros(size(chrom));
    for i=1:N-1
        cross_index = randi(L);
        offspring = cross([shuffledChrom(i,:);shuffledChrom(i+1,:)],cross_index);
        newChrom(i,:) = offspring(1,:);
        newChrom(i+1,:) = offspring(2,:);
    end
end