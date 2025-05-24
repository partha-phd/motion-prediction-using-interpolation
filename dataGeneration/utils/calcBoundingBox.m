function [xBox, yBox] = calcBoundingBox(xRef, yRef, psi, length, width)
ex = cos(psi);
ey = sin(psi);
exOrtho = ex * cos(pi / 2) + ey * sin(pi / 2);
eyOrtho = -ex * sin(pi / 2) + ey * cos(pi / 2);
xBox(1) = xRef - ex * length / 2 - width / 2 * exOrtho;
yBox(1) = yRef - ey * length / 2 - width / 2 * eyOrtho;
xBox(2) = xRef - ex * length / 2 + width / 2 * exOrtho;
yBox(2) = yRef - ey * length / 2 + width / 2 * eyOrtho;
xBox(3) = xRef + ex * length / 2 + width / 2 * exOrtho;
yBox(3) = yRef + ey * length / 2 + width / 2 * eyOrtho;
xBox(4) = xRef + ex * length / 2 - width / 2 * exOrtho;
yBox(4) = yRef + ey * length / 2 - width / 2 * eyOrtho;
end