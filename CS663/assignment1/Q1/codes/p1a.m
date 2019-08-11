d=3;
A=imread('circles_concentric.png');
% imshow(A);
A=double(A);
[r,c,l]=size(A);
%  B=zeroes(r/d,c/d,l)
B=A(1:d:r,1:d:c,l)
B=uint8(B);
imshow(B);