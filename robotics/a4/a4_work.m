%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%   MAE 345 Assignment 4 Work
%   Tarik Tosun
%   10/20/11
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Part 1:  Set up F and G
syms('x1','x2','x3','x4','u1','u2','m','l','g');
F = [0  1   0   0; ...
     0  (x4*sin(2*x3))/(cos(x3)^2)    (x2*x4*sin(2*x3)+u1/(m*l^2))/(cos(x3)^2)    (x2*sin(2*x3))/(cos(x3)^2);...
     0  0   0   1;...
     0  -sin(2*x3)/2   (g/l)*sin(x3)-x2*cos(2*x3)    0 ...
    ];

G = [0  0;...
     1/(m*l^2*cos(x3)^2)  0;...
     0  0;...
     0  1/(m*l^2)...
     ];
%% Part 2a:  Numerical Values of F and G
clc;
x2 = 0;
x4 = 0;
d = 1.5;
m = 2;
l = 1;
g = 9.807;
u1 = 0;

%minus 45
x3 = (-45)*pi/180
Fm = eval(F)
Gm = eval(G)
%zero
x3 = 0
Fz = eval(F)
Gz = eval(G)
%plus 45
x3 = (45)*pi/180
Fp = eval(F)
Gp = eval(G)

%% Part 2b:  Eigenvalues of F
clc
disp('-45:')
em = eig(Fm)
disp('0:')
ez = eig(Fz)
disp('45:')
ez = eig(Fp)

%% Part 2d:  Step Responses
clc
close all
C = eye(4);
D = zeros(4,2);
sys_m = ss(Fm,Gm,C,D);
sys_z = ss(Fz,Gz,C,D);
sys_p = ss(Fp,Gp,C,D);


t = 0:100:10000;   %time
OFFSET = 10;

%minus 45
u1_m = [zeros(1,OFFSET),0.1*ones(1,(size(t,2)-OFFSET))];
u2_m = [zeros(1,OFFSET),0.2*ones(1,(size(t,2)-OFFSET))];

figure; lsim(sys_m,[u1_m; zeros(size(u1_m))],t); title('-45 u1 step response');
figure; lsim(sys_m,[zeros(size(u1_m)); u2_m],t); title('-45 u2 step response');
%{
x_m_1 = lsim(sys_m,[u1_m; zeros(size(u1_m))],t);
x_m_2 = lsim(sys_m,[zeros(size(u1_m)); u2_m],t);
figure; plot(x_m_1); title('-45 u1 step response');
figure; plot(x_m_2); title('-45 u2 step response');
%}

%zero
u1_z = [zeros(1,OFFSET),0.2*ones(1,(size(t,2)-OFFSET))];
u2_z = [zeros(1,OFFSET),0.2*ones(1,(size(t,2)-OFFSET))];

figure; lsim(sys_z,[u1_z; zeros(size(u1_z))],t); title('0 u1 step response');
figure; lsim(sys_z,[zeros(size(u1_z)); u2_z],t); title('0 u2 step response');
%{
x_z_1 = lsim(sys_z,[u1_z; zeros(size(u1_m))],t);
x_z_2 = lsim(sys_z,[zeros(size(u1_m)); u2_z],t);
figure; plot(x_z_1); title('0 u1 step response');
figure; plot(x_z_2); title('0 u2 step response');
%}

%plus 45
u1_p = [zeros(1,OFFSET),0.1*ones(1,(size(t,2)-OFFSET))];
u2_p = [zeros(1,OFFSET),0.2*ones(1,(size(t,2)-OFFSET))];

figure; lsim(sys_p,[u1_p; zeros(size(u1_p))],t); title('45 u1 step response');
figure; lsim(sys_p,[zeros(size(u1_p)); u2_p],t); title('45 u2 step response');

%{
x_p_1 = lsim(sys_p,[u1_p; zeros(size(u1_m))],t);
x_p_2 = lsim(sys_p,[zeros(size(u1_m)); u2_p],t);
figure; plot(x_p_1); title('45 u1 step response');
figure; plot(x_p_2); title('45 u2 step response');
%}

%% Part 2f:  Bode Plots
close all
tf_m = tf(sys_m);
tf_z = tf(sys_z);
tf_p = tf(sys_p);
%bode(tf_m(:,2));
%minus 45:
figure; bode(tf_m(3,2)); title('Bode for u2 to x3 (-45 degrees)');
figure; bode(tf_m(4,2)); title('Bode for u2 to x4 (-45 degrees)');
%zero:
figure; bode(tf_z(3,2)); title('Bode for u2 to x3 (0 degrees)');
figure; bode(tf_z(4,2)); title('Bode for u2 to x4 (0 degrees)');
%plus 45:
figure; bode(tf_p(3,2)); title('Bode for u2 to x3 (45 degrees)');
figure; bode(tf_p(4,2)); title('Bode for u2 to x4 (45 degrees)');

%% Problem 3 - eigenvalue variation
eig_m = zeros(1,4);
eig_z = eig_m; eig_p = eig_m;
for i = 1:72
    %minus 45
    x2 = 10*(i-1)*pi/180;
    x3 = (-45)*pi/180;
    Fm = eval(F);
    eig_m(i,:) = eig(Fm);
    %zero
    x3 = 0;
    Fz = eval(F);
    eig_z(i,:) = eig(Fz);
    %plus 45
    x3 = (45)*pi/180;
    Fp = eval(F);
    eig_p(i,:) = eig(Fp);
end
%% plot:
close all;
x2 = 0:10:710;
figure; plot(x2, imag(eig_m)); title('imaginary eigenvalues for the -45 degree case'); xlabel('x2 (degrees/sec)'); ylabel('im(eig(F))');
figure; plot(x2, imag(eig_z)); title('imaginary eigenvalues for the zero degree case'); xlabel('x2 (degrees/sec)'); ylabel('im(eig(F))');
figure; plot(x2, imag(eig_p)); title('imaginary eigenvalues for the positive 45 degree case'); xlabel('x2 (degrees/sec)'); ylabel('im(eig(F))');
figure; plot(x2, real(eig_m)); title('real eigenvalues for the -45 degree case'); xlabel('x2 (degrees/sec)'); ylabel('re(eig(F))');
figure; plot(x2, real(eig_z)); title('real eigenvalues for the zero degree case'); xlabel('x2 (degrees/sec)'); ylabel('re(eig(F))');
figure; plot(x2, real(eig_p)); title('real eigenvalues for the positive 45 degree case'); xlabel('x2 (degrees/sec)'); ylabel('re(eig(F))');

