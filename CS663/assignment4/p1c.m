X=zeros(192*168,1520);
top=0;
folders=dir('/home/karan/Desktop/5th Sem/CS663/assignment4/CroppedYale');
for i=1:38
    gallery=dir(strcat('/home/karan/Desktop/5th Sem/CS663/assignment4/CroppedYale/',folders(i+2).name));
    for j= 1:40
        A=imread(strcat('/home/karan/Desktop/5th Sem/CS663/assignment4/CroppedYale/',folders(i+2).name,'/',gallery(j+2).name));
        [r,c]=size(A);
        B=reshape(A,[r*c,1]);
        X(:,38*(i-1)+j)=B(:,1);
    end
end
M=mean(X,2);
% M=repmat(X,240,1);
% X=X-M;
for i=1:1520
%     M=mean(X(:,i));
    X(:,i)=X(:,i)-M;
end

L=X'*X;
[W,E]=eig(L);
% % [w,E]=sortem(W,E);
V=X*W;
% [V,E,W]=svd(X,'econ');

S=sum((V).^2).^0.5;
S=repmat(S,32256,1);
V=V./S;

% V=normc(V);
k_orl=[1, 2, 3, 5, 10, 15, 20, 30, 50, 60, 65, 75, 100, 200, 300, 500, 1000];
[h,s_orl]=size(k_orl);
rec_rate_orl=zeros(1,s_orl);
% k_yale=[1, 2, 3, 5, 10, 15, 20, 30, 50, 60, 65, 75, 100, 200, 300, 500, 1000];
% [k,s_yale]=size(k_yale);
for l=1:s_orl
    k=k_orl(1,l);
    A=(V(:,1521-k-top:1520-top))'*X;
    count=0;
    for i=1:38
        gallery=dir(strcat('/home/karan/Desktop/5th Sem/CS663/assignment4/CroppedYale/',folders(i+2).name));
        [q,w]=size(gallery);
        for j=43:q
            count=count+1;
            B=imread(strcat('/home/karan/Desktop/5th Sem/CS663/assignment4/CroppedYale/',folders(i+2).name,'/',gallery(j).name));
            [r,c]=size(B);
            B=reshape(B,[r*c,1]);
%             M=mean(B);
            B=double(B);
            B=B-M;
            B=(V(:,1521-k-top:1520-top))'*B;
            m=9999999999999879;
            index=1;
            for h=1:1520
                D=B-A(:,h);
                D=D.^2;
                if m>sum(sum(D))
                    m=sum(sum(D));
                    index=h;
                end
            end
            if ceil(index/40)==i
                rec_rate_orl(1,l)=rec_rate_orl(1,l)+1;
            end
        end
    end
    rec_rate_orl(1,l)=rec_rate_orl(1,l)*100/count;
end
figure('Name','YaleRecognitionRate');
plot(k_orl,rec_rate_orl,'b');
