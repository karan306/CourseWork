%% Kour code here
A=zeros(300,300);
B=zeros(300,300);
A(50:100,50:120)=255;
B(50-30:100-30,50+70:120+70)=255;
C=fft2(A);
D=fft2(B);


J=(C.*(conj(D)))./(abs(C).*abs(D));
J(isnan(J))=0;

K=ifftshift(fft2(J));
logj=log(abs(K));
figure();
imagesc(logj);
colormap("gray");
title('without noise');

[~,col1]=max(max(K));
[~,row1]=max(K);
row1=row1(col1);

row1 %-30 x-shift
col1 %70 y-shift

A=A+(20*randn(300));
B=B+(20*randn(300));
A2=fft2(A);
B2=fft2(B);

J=(A2.*(conj(B2)))./(abs(A2).*abs(B2));
J(isnan(J))=0;


K=ifftshift(fft2(J));
logj=log(abs(K));
figure();
imagesc(logj);
colormap("gray");
title('with noise');

[~,col2]=max(max(J));  
[~,row2]=max(K);
row2=row2(col2)
col2

