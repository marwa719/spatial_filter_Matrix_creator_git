clear
close all
clc




%% LECTURE

[mic_0, Fe] = audioread('channel_0.wav');
mic_1       = audioread('channel_1.wav');
mic_2       = audioread('channel_2.wav');
mic_3       = audioread('channel_3.wav');
mic_4       = audioread('channel_4.wav');
mic_5       = audioread('channel_5.wav');
mic_6       = audioread('channel_6.wav');
mic_7       = audioread('channel_7.wav');


mic = [mic_0(:), mic_1(:), mic_2(:), mic_3(:), mic_4(:), mic_5(:), mic_6(:), mic_7(:)];


mic_filt = mic;


%Calcul de puissance:
theta_t = linspace(0, 2*pi, 26);
theta_t(end) = [];

phi_t = linspace(0, pi/2, 11);
phi_t(end) = [];

puissance = zeros(size(theta_t,2), size(phi_t,2));
for i = 1:length(theta_t)
    for j = 1 : length (phi_t)
        i
        [signal_out, micf] = rephase(mic_filt, Fe, theta_t(i), phi_t(j));
        puissance(i,j) = var(signal_out);
    end    
end

% Récupération de theta et phi
T = 5;
t = (0:1/Fe:T - 1/Fe);
[phi, theta, I_ligne, I_col] = estimation (puissance, theta_t , phi_t);
[signal_out, micf] = rephase(mic_filt, Fe, theta, phi);

% Visualisation figure :
figure(1), plot(t,micf(1:length(t), :))
figure(2), polar(theta_t, puissance(:, I_col)');
figure(3), plot(phi_t*180/pi, puissance(I_ligne, :));





