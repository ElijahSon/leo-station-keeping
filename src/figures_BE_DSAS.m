%% figure BE DSAS\

squeeze(x);
squeeze (dtX); 
figure(1); 
plot(x(1,:),x(2,:),'r','LineWidth',1); grid; 
title('Orbite du satellite'); xlabel('x'),ylabel('YM'); axis equal;
legend('Orbite')

figure(2); 
subplot(611),plot(t,x(1,:),'LineWidth',2); grid; 
subplot(612),plot(t,x(2,:),'LineWidth',2); grid; 
subplot(613),plot(t,x(3,:),'LineWidth',2); grid; 
subplot(614),plot(t,x(4,:),'b','LineWidth',2); grid; 
subplot(615),plot(t,x(5,:),'b','LineWidth',2); grid; 
subplot(616),plot(t,x(6,:),'b','LineWidth',2); grid; 
title('Evolution temporelle des etats'); xlabel('Temps (s)'),ylabel('x'); 

figure(3) 
plot(Xch(1,:),Xch(2,:)) ; grid; 
title(''); xlabel('t en secondes'),ylabel('Xch'); axis equal;
% legend('')
% 
figure(4) 
plot(Xci(1,:),Xci(2,:)) ; grid; 
title(''); xlabel('t en secondes'),ylabel('Xch'); axis equal;
% % legend('')


figure(5) 
plot(t,dtX) ; grid; 
title(''); xlabel('t en secondes'),ylabel('dtX'); axis equal;
% % legend('')

