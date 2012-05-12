function [net,outputs] = create_pr_net(inputs,targets,nh,epochs,lr)
%CREATE_PR_NET Creates and trains a pattern recognition neural network.
%
%  NET = CREATE_PR_NET(INPUTS,TARGETS) takes these arguments:
%    INPUTS - RxQ matrix of Q R-element input samples
%    TARGETS - SxQ matrix of Q S-element associated target samples, where
%      each column contains a single 1, with all other elements set to 0.
%  and returns these results:
%    NET - The trained neural network
%
%  For example, to solve the Iris dataset problem with this function:
%
%    load iris_dataset
%    net = create_pr_net(irisInputs,irisTargets);
%    irisOutputs = sim(net,irisInputs);
%
%  To reproduce the results you obtained in NPRTOOL:
%
%    net = create_pr_net(set1',Target');

% Create Network
numHiddenNeurons = nh;  % Adjust as desired
net = newpr(inputs,targets,numHiddenNeurons);
net.layers{1}.transferFcn = 'logsig';
net.layers{2}.transferFcn = 'purelin';   
net.divideParam.trainRatio = 100/100;  % Adjust as desired
net.divideParam.valRatio = 100/100;  % Adjust as desired
net.divideParam.testRatio = 0/100;  % Adjust as desired

net.trainFcn = 'traingd';
net.trainParam.epochs = epochs;
net.trainParam.lr = lr;

% Train and Apply Network
[net,tr] = train(net,inputs,targets);
outputs = sim(net,inputs);

% Plot
%plotperf(tr);
%plotconfusion(targets,outputs)
