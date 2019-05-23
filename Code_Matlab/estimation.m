function [phi_max, theta_max, I_ligne, I_col] = estimation(puissance, theta_t, phi_t)

[maximum, I] = max(puissance(:));
[I_ligne, I_col] = ind2sub(size(puissance),I);

theta_max = theta_t(I_ligne);
phi_max = phi_t(I_col);
