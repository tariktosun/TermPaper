%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% genetic.m
% Tarik Tosun, MAE 345 Assignment 5, 12/1/11
% Description:
%   Genetic algorithm returning the optimal system parameters and
%   corresponding optimal cost function value for Assignment 5.
%
%   numChrom argument indicates the number of chromosomes to use.
%   mutate arg indicates mutation frequency (in generations).  No mutations
%   occur if mutate is not a positive integer.
% Created: 12/1/11
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function [Jmax, psi, wn] = genetic(numChrom, mutate, thresh)
    %%% Arg Checking %%%
    if(mod(numChrom,2)~=0)
        error('numChron must be even.');
    end
    %%%%%%%%%%%%%%%%%%%%
    %%% Constants %%%
    GENE_LENGTH = 12;  
    NUM_GENES = 2;
    THRESH = thresh;
    %%%%%%%%%%%%%%%%%
    
    chrom = randi([0,1],[numChrom,GENE_LENGTH*NUM_GENES]); %generate random chromosomes
    J = zeros(numChrom,1);
    
    % Iterate until total fitness stabilizes:
    Jt = -1;  Jt_prev = 0; %starter values.  Jt will never be negative.
    i=1;
    while(abs(Jt-Jt_prev)>THRESH)
        Jt_prev = Jt;
        [J,Jt] = geneFitness(chrom, GENE_LENGTH);         % get fitness
        chrom = selectNewChrom(chrom,J,Jt);  % weighted roulette selection
        chrom = randomCross(chrom);          % perform random crossover
        if(mutate>0 && i==mutate)            % mutate as specified
            chrom = mutate(chrom);
            i = 0;  %incremented later
        end
        i=i+1;
    end
    
    % Pick best gene from stable generation:
    [Jmax,index] = max(J);
    bestChrom = chrom(index(1),:);
    %get values from genes:
    psi_str = int2str(bestChrom(:,1:GENE_LENGTH));
    wn_str = int2str(bestChrom(:,GENE_LENGTH+1:end));
    psi = bin2dec(psi_str);
    wn = bin2dec(wn_str);
end