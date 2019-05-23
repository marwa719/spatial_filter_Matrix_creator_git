function [signal_out, micf] = rephase(mic, Fe, theta_s,phi_s)
r = 0.0525; %la carte a un rayon de 5.25 cm
v = 340; %vitesse du son dans l'air
theta_0 = theta_s;
theta_i = -3*pi/8 : 2*pi/8 : 11*pi/8;%0 : 2*pi/8 : 14*pi/8; -3*pi/8 : 2*pi/8 : 11*pi/8;
Te = 1/Fe;

mic = (mic - repmat(mean(mic),size(mic,1),1))./repmat(std(mic),size(mic,1),1);

 % on calcule les écarts temporels
tau_i = (r/v) * sin(phi_s) * (cos (theta_0 - theta_s) - cos(theta_i  - theta_s));
 % on traduit le retard (s) en nombre d echantillons
ecart_ech_i = tau_i/Te; 
 % On veut decaler tous les signaux de 'decalage' echantillons pour avoir un delai fractionnaire toujours positif
decalage = ceil(abs(max(ecart_ech_i)));


ecart_ech_dec_i = decalage-ecart_ech_i;  
partie_entiere = floor(ecart_ech_dec_i);
frac = ecart_ech_dec_i - partie_entiere;

% Décalage entier et fractionnaire :

micd = zeros(size(mic,1),8);
micf = zeros(size(mic,1),8);
coeffs = [-1/6 1/2 -1/3 0;1/2 -1 -1/2 1;
-1/2 1/2 1 0;1/6 0 -1/6 0];

for i = 1:8
    delay_line = zeros(1,10);
    delay_line(partie_entiere(i)+1) = 1;
    micd(:,i) = filter(delay_line, 1, mic(:,i)); % décalge par convolution avec un dirac
    Hd = dfilt.farrowfd(frac(i), coeffs);
    micf(:,i) = filter(Hd, micd(:,i));
end

signal_out = mean(micf,2);