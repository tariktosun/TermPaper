%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% A5Script.m
% Tarik Tosun, MAE 345 Assignment 5, 12/1/11
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Roulette Wheel Test
N = 1000000;
probs = [0.1, 0.2, 0.05, 0.15, 0.11, 0.07, 0.04, 0.12, 0.08, 0.08]';
strings = [1:size(probs,1)]';
count = zeros(size(strings));
for i = 1:N
    index = roulette(strings,probs);
    count(index) = count(index)+1;
end
dist = count/N;

%% Crossover Test
s = [1 0 1 0 1 0 1 1; 0 1 0 1 0 1 0 0; 1 1 1 1 1 0 0 1; 1 1 0 1 0 1 1 1];
randomCross(s);
cross([s(1,:);s(2,:)],3);
cross([s(3,:);s(4,:)],3);
%% run genetic algorithm:
[Jmax, psi, wn] = genetic(64,5,0.0001)

%% Comparison with fminsearch:
psi = 50;
wn = 5000;
[x_fms,J_fms] = fminsearch(@(x)grad_fit(x),[psi,wn]);
