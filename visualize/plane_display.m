close all
clear all

% Plane Equation
% z = ax+by+d
a = -1/3;
b = -2/3;
d = 3;

x = 1:1:100;
y = 1:1:100;
[x, y] = meshgrid(x, y);
z = a*x+b*y+d;

figure, surf(x, y, z); hold on

title('plane display')
x1 = xlabel('x axis');
y1 = ylabel('y axis');
z1 = zlabel('z axis');