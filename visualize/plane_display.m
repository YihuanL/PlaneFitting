close all
clear all
% z = ax+by+d
% a = -1/3; % -1/3.0 in CPP
% b = -2/3;
% d = 3;
a = 100;
b = 100;
d = 1;

x = 1:1:100;
y = 1:1:100;

[x, y] = meshgrid(x, y);
z = a*x+b*y+d;
%z2 = 2*a*x+2*b*y+d;
figure, surf(x, y, z); hold on
%surf(x, y, z2)
title('plane display')
x1 = xlabel('x axis');
y1 = ylabel('y axis');
z1 = zlabel('z axis');