%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% a6script.m
% Tarik Tosun, MAE 345 Assignment 6 Neural Network
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% create target matrix (3x21)
% convention:  row 1 - BRCA1, row 2 - BRCA2, row 3 - Sporadic
%              Sample columns are arranged in same order as spreadsheet.
clear all; clc
o = ones(1,7);
z = zeros(1,7);
targets = [o z z; z o z; z z o];
%% create training matrix (18x21)
load set2.mat;  % load training set 1 - first 18 from the paper.
%% Do hidden neurons - epoch performance analysis:
nh = [1 2 4 8 16];
epochs = [1 2 3 4 5 6 7 8 9 10];
N = size(nh,2);
E = size(epochs,2);
conf = zeros(N,E);
for i=1:N
    for j=1:E
        [net,outputs] = create_pr_net(set2,targets,nh(i),epochs(j),0.01);
        [c,cm,ind,per] = confusion(targets,outputs);
        conf(i,j) = c;
    end
end

figure; surf(epochs,nh,conf)
xlabel('Epochs')
ylabel('Hidden Nodes')
zlabel('Confusion Percentage')
title('Confusion Percentage vs. Number of Epochs and Hidden Nodes')

%% Effects of learning rate on network convergence
lr = [0.001,0.01,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1,2,3,4,5,6];

L = size(lr,2);
conf_lr = zeros(1,L);
numAvg = 5;
for i=1:L
    curSum = 0;
    for j=1:numAvg
        [net,outputs] = create_pr_net(set2,targets,16,100,lr(i));
        [c,cm,ind,per] = confusion(targets,outputs);
        curSum = curSum + c;
    end
    conf_lr(i) = c/5;
end
figure; plot(lr,conf_lr); hold on; plot(lr,conf_lr,'o');
xlabel('learning rate');
ylabel('Confusion');
title('Confusion vs. Learning Rate');
%% leave-one-out validation
N = 21; % number of samples
out = zeros(3,N);
for i=1:N
    s = set2;
    s(:,i)=[];
    t = targets;
    t(:,i)=[];
    [net,outputs] = create_pr_net(s,t,16,100,0.01);
    out(:,i) = sim(net,set2(:,i));
end
plotconfusion(targets,out)