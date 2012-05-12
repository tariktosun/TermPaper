%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% selectNewChrom.m
% Tarik Tosun, MAE 345 Assignment 5, 12/1/11
% Description:
%   Uses roulette-wheel selection to generate a new generation of
%   chromosomes based on previous generation chrom and their fitnesses J.
%   Jt is total fitness.
% Created 12/1/11.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function newChrom = selectNewChrom(chrom,J,Jt)
    N = size(J,1);
    prob = J/Jt;
    newChrom = zeros(size(chrom));
    for i=1:N
        newChrom(i,:) = roulette(chrom, prob);
    end
end