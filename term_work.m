%% plot required equilibrium torques:
% Note:  This is copied from 345 A3.
clc();
setup(); load('params.mat');

x3_deg = -90:5:90;
x3_nom = x3_deg*pi/180;
u2_nom = m*l*g*cos(x3_nom);
figure; plot(x3_deg,u2_nom);
xlabel('x3 (=theta2), in degrees');
ylabel('u2 (torque) in kg*m^2/s^2');
title('Part 2 - Plot of Torque versus Angle for Joint 2 in Equilibrium');

%% Compute LQR Feedback Matrices - schedule on theta2 = const only:
clc;
setup(); load('params.mat');
x4s = 0;
u2s = 0;

S.x1 = 0;
S.x2 = 0;
S.x4 = 0;
S.u1 = 0;

Q = [1 0 0 0; 0 0 0 0; 0 0 1 0; 0 0 0 0]*100000;
R = [1 0; 0 1];

Ccell = cell(36,1);
c1 = zeros(1,36);
i=0;
for x3 = -90:5:90
    if abs(x3)==90   %avoid singularity
        x3 = 0.99*x3;
    end
    S.x3 = x3*pi/180;   %convert to rads
    S.u2 = m*l*g*cos(S.x3);
    [F,G,L] = linMats(S);
    [C,s,e] = lqr(F,G,Q,R,0);
    Ccell{i+1}=C;
    i = i+1;
end

for i=1:size(Ccell,1)
    b = Ccell{i};
    for j=1:8
        K(j,i) = b(j);
    end
end

% save gain table:
r = -90:5:90;
save('gaintable.mat','K','r');

x3 = -90:5:90;
figure;
sub = [1 5 2 6 3 7 4 8];
r = [1 2 1 2 1 2 1 2];
c = [1 1 2 2 3 3 4 4];
for j=1:8
    subplot(2,4,sub(j));
    plot(x3,K(j,:),'o');  hold on;
    plot(x3,K(j,:));
    xlabel('Degrees');
    %c = mod(j,4);
    %if c==0; c=4; end;
    cc = int2str(c(j));
    rr = int2str(r(j));
    %r = int2str(ceil(j/4));
    ylabel(['C' rr cc]);
end
%% Pull in source data:
addpath('/home/tarik/MAE_546/TermPaper/');
addpath('/home/tarik/tarik_retargeter/chainsolver/');
[rMotion, lMotion] = bothArms3d('/home/tarik/MAE_546/TermPaper/oni/cap0.oni');
lChain = lMotion.chain;
LL = sum(lChain.lengths);
orig = lMotion;

%% cut to size
nf = 230;
lMotion.numFrames = nf;
lMotion.epHist = orig.epHist(1:lMotion.numFrames);
%% Create manipulator kinematic chain, and make imitation:
m = twoLinkManipulator(LL);
m = setJointAngles(m,[0 0]);
mIm = motionImitation(lMotion, m, 'cost_joints_ee', 'noscale', 1);

%% view:
figure; view([0 90]); grid on;
xlabel('x'); ylabel('y'); zlabel('z'); axis equal
animate(lMotion, mIm);

%% create simulink trajectory:
fr = 30;    % framerate
nf = mIm.numFrames;

ts = 0;
dt = 1/fr;
te = ts+dt*(nf-1);
t = ts:dt:te;
traj = mIm.angleHist';
traj(2,:) = traj(2,:) - 90*ones(size(traj(2,:)));

%% Test trajectory for simulink:
ts = 0;
te = 10;
dt = 0.1;
t = ts:dt:te;
traj = [sin(10*t)*100+100; ones(size(t))*-91];


%% simulink setup:
%{
setup(); load('params.mat');
load('gaintable.mat');
tfun = @(x) m*l*g*cos(x*pi/180);
%}

%% Linearization:  check the model matrices:
% Note: have to paste them in fresh to check each time!
syms x2 x3 x4 u1 u2 l m g;

    f23 = 2*sin(x3)*(u1/(l^2*m)+x2*x4*sin(2*x3))/cos(x3)^3 +...
          (2*x2*x4*cos(2*x3))/(cos(x3)^2);
    F = [0  1   0   0; ...
         0  (x4*sin(2*x3))/(cos(x3)^2)    f23   (x2*sin(2*x3))/cos(x3)^2;...
         0  0   0   1;...
         0  sin(2*x3)   (g/l)*sin(x3)-x2*cos(2*x3)  0];
         

    G = [0  0;...
         1/(m*l^2*cos(x3)^2)    0;...
         0  0;...
         0  1/(m*l^2);];

    L = G;
    
    