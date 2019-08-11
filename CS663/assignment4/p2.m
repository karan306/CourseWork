folders=dir('/home/karan/Desktop/5th Sem/CS663/assignment4/CroppedYale');
gallery=dir(strcat('/home/karan/Desktop/5th Sem/CS663/assignment4/CroppedYale/',folders(3).name));
A=zeros(32256,64);
for i=3:66
    X=imread(strcat('/home/karan/Desktop/5th Sem/CS663/assignment4/CroppedYale/',folders(3).name,'/',gallery(i).name));
    X=reshape(X,[32256,1]);
    A(:,i-2)=X;
end
M=mean(A,2);
for i=1:64
%     M=mean(X(:,i));
    A(:,i)=A(:,i)-M;
end
%X=imread(strcat('/home/karan/Desktop/5th Sem/CS663/assignment4/CroppedYale/',folders(3).name,'/',gallery(3).name));
%X=double(X);
k=[2, 10, 20, 50, 75, 100, 125, 150,175];
[r,s]=size(k);
[U,S,V]=svd(A,'econ');
S=sum((U).^2).^0.5;
S=repmat(S,32256,1);
U=U./S;

figure('Name','Image Reconstruction using SVD','NumberTitle','off');
for i=1:s
    
    X=(U(:,1:min(64,k(i))))'*A;
    subplot(4,3,i+3);
    I=M+U(:,1:min(64,k(i)))*X(:,1);
    m1=min(min(I));
    m2=max(max(I));
    I=(I-m1)*255/(m2-m1);
    imshow(uint8(reshape(I,[192,168])));
end

figure('Name','Eigenvectors','NumberTitle','off');
for i=1:25
    subplot(5,5,i);
    I=U(:,i);
     m1=min(min(I));
    m2=max(max(I));
    I=(I-m1)*255/(m2-m1);
    imshow(uint8(reshape(I,[192,168])));
end