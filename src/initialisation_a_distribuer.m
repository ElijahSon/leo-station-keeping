clear all;

mu = 3.986e14;

a(1)=7068*1e3;
ecc(1)=0;%0.1
inc(1)=0;
W(1)=0;
w(1)=0;
nu(1)=0;

a(2)=7068*1e3;
ecc(2)=0%+1.41e-5;
inc(2)=0;
W(2)=0;
w(2)=0;
nu(2)=0+1.41e-5;

for k=1:2, % k=1: cible, k=2: chasseur

n(k) = sqrt(mu/((a(k))^3));

% Calcul de quelques expressions partielles
    
K1(k) = a(k) * (1-ecc(k)^2) / (1 + ecc(k) * cos(nu(k)));
K2(k) = a(k) * ecc(k) * n(k) * sin(nu(k)) / sqrt(1-ecc(k)^2);
K3(k) = a(k) * n(k) * (1 + ecc(k) * cos(nu(k))) / sqrt(1-ecc(k)^2);
    
% Calcul de la position initiale a partir des param orbitaux
    
x_init(k) = K1(k) * (cos(W(k)) * cos(nu(k)+w(k)) - sin(W(k))*cos(inc(k))*sin(nu(k)+w(k)));
y_init(k) = K1(k) * (sin(W(k))*cos(nu(k)+w(k)) + cos(W(k))*cos(inc(k))*sin(nu(k)+w(k)));
z_init(k) = K1(k) * sin(inc(k))*sin(nu(k)+w(k));

% Calcul de la vitesse initiale a partir des param orbitaux
    
Vx_init(k) = K2(k) * (cos(W(k))*cos(nu(k)+w(k)) - sin(W(k))*cos(inc(k))*sin(nu(k)+w(k))) - K3(k) * (cos(W(k))*sin(nu(k)+w(k)) + sin(W(k))*cos(inc(k))*cos(nu(k)+w(k)));
Vy_init(k) = K2(k) * (sin(W(k))*cos(nu(k)+w(k)) + cos(W(k))*cos(inc(k))*sin(nu(k)+w(k))) + K3(k) * (-sin(W(k))*sin(nu(k)+w(k)) + cos(W(k))*cos(inc(k))*cos(nu(k)+w(k)));
Vz_init(k) = K2(k) * sin(inc(k)) * sin(nu(k)+w(k)) + K3(k) * sin(inc(k)) * cos(nu(k)+w(k));

end

% Conditions initiales de la cible et du chasseur (valeur du vecteur d
% etat)
X_init_cible=[x_init(1);y_init(1);z_init(1);Vx_init(1);Vy_init(1);Vz_init(1)];
X_init_chasseur=[x_init(2);y_init(2);z_init(2);Vx_init(2);Vy_init(2);Vz_init(2)];

% Calcul du correcteur

