% manipulatorScript.m
% for MAE 546 Term Paper

%% Create chains:
addpath('/home/tarik/MAE_546/TermPaper');
m = twoLinkManipulator(sum(kLMotion.chain.lengths));

%% make imitation:
m = setJointAngles(m,[0 0]);
mIm = motionImitation(kLMotion, m, 'cost_joints_ee', 'noscale', 1);

%% animate:
headAnimate(kLMotion, mIm);