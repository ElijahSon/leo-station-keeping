function x = gali2loc(DeltaX,param_orb_cible)

mu = 3.986e14;

Delta_pos_gali = DeltaX(1:3);
Delta_vit_gali = DeltaX(4:6);
a1 = param_orb_cible(1);
ecc1 = param_orb_cible(2);
inc1 = param_orb_cible(3);
W1 = param_orb_cible(4);
w1 = param_orb_cible(5);
nu1 = param_orb_cible(6);

 P_gali2loc = [cos(W1)*cos(w1+nu1)-sin(W1)*cos(inc1)*sin(w1+nu1),...
     cos(W1)*sin(w1+nu1)+sin(W1)*cos(inc1)*cos(w1+nu1),...
     sin(W1)*sin(inc1);...
     -sin(W1)*cos(w1+nu1)-cos(W1)*cos(inc1)*sin(w1+nu1),...
     -sin(W1)*sin(w1+nu1)+cos(W1)*cos(inc1)*cos(w1+nu1),...
     cos(W1)*sin(inc1);...
     sin(inc1)*sin(w1+nu1),...
     -sin(inc1)*cos(w1+nu1),...
     cos(inc1)];
 Delta_pos_loc=(P_gali2loc)*Delta_pos_gali;
 Delta_vit_loc=(P_gali2loc)*Delta_vit_gali;

 Omega_R1_R0=[0;0;sqrt(mu/(a1^3))];
 Delta_vit_loc_R1=Delta_vit_loc+cross(Delta_pos_loc,Omega_R1_R0);
 
x=[Delta_pos_loc;Delta_vit_loc_R1];