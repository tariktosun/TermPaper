%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% evalGenes.m
% Tarik Tosun, MAE 345 Assignment 5, 12/1/11
% Description:
%   Converts binary genes into decimal numbers.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function [psi,wn] = evalGenes(chrom, gene_length)
    MAX = 2;
    RES = 4096;
    scale = MAX/RES;
    psi_str = int2str(chrom(:,1:gene_length));
    wn_str = int2str(chrom(:,gene_length+1:end));
    psi = scale*bin2dec(psi_str);
    wn = scale*bin2dec(wn_str);
end