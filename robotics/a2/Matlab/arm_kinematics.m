%% set joint angles:

s_roll = 0;
s_yaw = 0;
s_pitch = 0;
e_pitch = 0;
w_pitch = 0;
w_yaw = 0;
w_roll = 0;



%% Shoulder joints
d(1)=0;   theta(1)=0;   r(1)=0;   alpha(1)=0;   %roll
d(2)=0;   theta(2)=0 + s_roll;   r(2)=0;   alpha(2)=90;  %yaw
d(3)=0;   theta(3)=90 + s_yaw;  r(3)=0;   alpha(3)=90;  %pitch

t{1} = DenHart(d(1),theta(1),r(1),alpha(1));
t{2} = DenHart(d(2),theta(2),r(2),alpha(2));
t{3} = DenHart(d(3),theta(3),r(3),alpha(3));

%% Elbow joint
%d(4)=0;   theta(4)=180 + s_pitch;   r(4)=25;  alpha(4)=-35; %pitch
d(4)=0;   theta(4)=180 + s_pitch;   r(4)=25;  alpha(4)=0; %pitch

t{4} = DenHart(d(4),theta(4),r(4),alpha(4));

%% Wrist joints
%d(5)=0;   theta(5)=0 + e_pitch;   r(5)=25;  alpha(5)=-145;%pitch
d(5)=0;   theta(5)=0 + e_pitch;   r(5)=25;  alpha(5)=0;%pitch
d(6)=0;   theta(6)=90 + w_pitch;  r(6)=0;   alpha(6)=90;%roll
d(7)=0;   theta(7)=-90 + w_roll;  r(7)=0;   alpha(7)=-90;%yaw


%d(6)=0;   theta(6)=180 + w_pitch; r(6)=0;   alpha(6)=-90; %yaw
%d(7)=0;   theta(7)=-90 + w_yaw; r(7)=0;   alpha(7)=90; %roll

t{5} = DenHart(d(5),theta(5),r(5),alpha(5));
t{6} = DenHart(d(6),theta(6),r(6),alpha(6));
t{7} = DenHart(d(7),theta(7),r(7),alpha(7));

%% Hand:
d(8)=0;   theta(8)=-90 + w_yaw; r(8)=9;    alpha(8)=-90;

t{8} = DenHart(d(8),theta(8),r(8),alpha(8));

%% Output joint coords:

coords = JointCoords_DH(t);
lh_coords = JointCoords_DH(t)*[1 0 0; 0 1 0; 0 0 -1];
rh = chain3d([coords(:,3),coords(:,1),coords(:,2)]);
lh = chain3d([lh_coords(:,3),lh_coords(:,1),lh_coords(:,2)]);
figure; mc.draw('k'); rh.draw; axis([-60 60 -60 60 -60 60]);

c_ref_r = [coords(:,3),-coords(:,1),coords(:,2)]
c_ref_l = [lh_coords(:,3),-lh_coords(:,1),lh_coords(:,2)];

%%
for i=1:8
    disp(['T',int2str(i),':'])
    disp(t{i})
end
