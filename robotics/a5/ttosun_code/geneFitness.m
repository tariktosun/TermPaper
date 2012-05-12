%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% geneFitness.m
% Tarik Tosun, MAE 345 Assignment 5, 12/1/11
% Description:
%   Calculates the fitness of each chromosome in the matrix chrom, as well
%   as the total fitness of the generation.
% Created 12/1/11.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function [J, Jt] = geneFitness(chrom, gene_length, noise)
    N = size(chrom,1);
    % get values from genes:
    psi_str = int2str(chrom(:,1:gene_length));
    wn_str = int2str(chrom(:,gene_length+1:end));
    psi = bin2dec(psi_str);
    wn = bin2dec(wn_str);
    [psi,wn] = evalGenes(chrom, gene_length);
    J = zeros(N,1);
    Jt = 0;
    for i=1:N
        [x,xnom] = simulate_sys(psi(i),wn(i));
        J(i) = fitness(x,xnom,noise);
        Jt = Jt+J(i);
    end
end