%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% genetic.m
% Tarik Tosun, MAE 345 Assignment 5, 12/1/11
% Description:
%   Genetic algorithm returning the optimal system parameters and
%   corresponding optimal cost function value for Assignment 5.
%
%   numChrom argument indicates the number of chromosomes to use.
%
%   mutate arg indicates mutation frequency (in generations).  No mutations
%   occur if mutate is not a positive integer.
% 
%   noise arg specifies the percent standard deviation of gaussian random
%   error in the cost function residual.  Enter zero for no noise.
% Created: 12/1/11
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function [Jmax,psi,wn,Jt_rec,Jbest_rec,j] = genetic(numChrom, mutation, noise, thresh)
    %%% Arg Checking %%%
    if(mod(numChrom,2)~=0)
        error('numChron must be even.');
    end
    %%%%%%%%%%%%%%%%%%%%
    %%% Constants %%%
    GENE_LENGTH = 12;  
    NUM_GENES = 2;
    WINDOW = 50;
    THRESH = thresh;
    %%%%%%%%%%%%%%%%%
    
    chrom = randi([0,1],[numChrom,GENE_LENGTH*NUM_GENES]); %generate random chromosomes
    J = zeros(numChrom,1);
    
    % Iterate until total fitness stabilizes:
    Jt = 0;
    i=1;
    j=1;
    Jt_rec = -ones(1,WINDOW+1); Jbest_rec = 0;
    while(abs(Jt-mean(Jt_rec(end-WINDOW:end)))>THRESH)
        Jt_rec(j) = Jt;
        Jbest_rec(j) = max(J);
        [J,Jt] = geneFitness(chrom, GENE_LENGTH, noise);         % get fitness
        chrom = selectNewChrom(chrom,J,Jt);  % weighted roulette selection
        chrom = randomCross(chrom);          % perform random crossover
        if(mutation>0 && i==mutation)            % mutate as specified
            chrom = mutate(chrom);
            i = 0;  %incremented later
        end
        i=i+1;
        j=j+1;
    end
    
    % Pick best gene from stable generation:
    [Jmax,index] = max(J);
    bestChrom = chrom(index(1),:);
    %get values from genes:
    [psi,wn] = evalGenes(bestChrom, GENE_LENGTH);
end