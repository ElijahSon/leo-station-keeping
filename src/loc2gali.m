function U = loc2gali(param_orb_cible,u)

mu = 3.986e14;

ux_loc = u(1);
uy_loc = u(2);
uz_loc = u(3);
a1 = param_orb_cible(1);
ecc1 = param_orb_cible(2);
inc1 = param_orb_cible(3);
W1 = param_orb_cible(4);
w1 = param_orb_cible(5);
nu1 = param_orb_cible(6);

 uloc=[ux_loc;uy_loc;uz_loc];
 P_gali2loc = [cos(W1)*cos(w1+nu1)-sin(W1)*cos(inc1)*sin(w1+nu1),...
     cos(W1)*sin(w1+nu1)+sin(W1)*cos(inc1)*cos(w1+nu1),...
     sin(W1)*sin(inc1);...
     -sin(W1)*cos(w1+nu1)-cos(W1)*cos(inc1)*sin(w1+nu1),...
     -sin(W1)*sin(w1+nu1)+cos(W1)*cos(inc1)*cos(w1+nu1),...
     cos(W1)*sin(inc1);...
     sin(inc1)*sin(w1+nu1),...
     -sin(inc1)*cos(w1+nu1),...
     cos(inc1)];
 ugali=(P_gali2loc')*uloc;

U=ugali;