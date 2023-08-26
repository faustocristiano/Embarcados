R = [14400 9060  2970];
T = [17+273 ; 27+273 ;  61+273];

R_log = log(R);

R_3_log= R_log.^3;

M = [1 1 1 ; R_log ; R_3_log]';

Coef = M \ (1./T)

R = 12000;
temp = (1/(Coef(1) + Coef(2)*log(R) + Coef(3)*log(R)^3)) - 273

