X=zeros(92*112,192);
for i=1:32
    for j= 1:6
        A=imread(strcat('/home/karan/Desktop/5th Sem/CS663/assignment4/att_faces/s',num2str(i),'/',num2str(j),'.pgm'));
        [r,c]=size(A);
        B=reshape(A,[r*c,1]);
        X(:,6*(i-1)+j)=B(:,1);
    end
end
M=mean(X,2);
% M=repmat(X,240,1);
% X=X-M;
for i=1:192
%     M=mean(X(:,i));
    X(:,i)=X(:,i)-M;
end

% L=X'*X;
[V,E,W]=svd(X,'econ');
% [w,E]=sortem(W,E);
% V=X*W;
S=sum((V).^2).^0.5;
S=repmat(S,10304,1);
V=V./S;

% V=normc(V);
k_orl=[1, 2, 3, 5, 10, 15, 20, 30, 50, 75, 100, 150, 170];
[h,s_orl]=size(k_orl);
rec_rate_orl=zeros(1,s_orl);
k_yale=[1, 2, 3, 5, 10, 15, 20, 30, 50, 60, 65, 75, 100, 200, 300, 500, 1000];
[k,s_yale]=size(k_yale);
for l=1:s_orl
    k=k_orl(1,l);
    A=(V(:,1:k))'*X;
    count=0;
    for i=1:32
        for j=7:10
            count=count+1;
            B=imread(strcat('/home/karan/Desktop/5th Sem/CS663/assignment4/att_faces/s',num2str(i),'/',num2str(j),'.pgm'));
            [r,c]=size(B);
            B=reshape(B,[r*c,1]);
%             M=mean(B);
            B=double(B);
            B=B-M;
            B=(V(:,1:k))'*B;
            m=9999999999999879;
            index=1;
            for h=1:192
                D=B-A(:,h);
                D=D.^2;
                if m>sum(sum(D))
                    m=sum(sum(D));
                    index=h;
                end
            end
            if ceil(index/6)==i
                rec_rate_orl(1,l)=rec_rate_orl(1,l)+1;
            end
        end
    end
    rec_rate_orl(1,l)=rec_rate_orl(1,l)*100/count;
end
figure('Name','OrlRecognitionRateWithSVD');
plot(k_orl,rec_rate_orl,'b');