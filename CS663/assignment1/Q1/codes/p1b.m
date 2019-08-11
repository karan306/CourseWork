% B=imread('barbaraSmall.png');
% B=double(B);
% [r,c]=size(B);
% d1=3;
% d2=2;
% p=1:r;
% q=1:c;
% p1=1:1/d1:r;
% q1=1:1/d2:c;
% r1=r+(d1-1)*(r-1);
% c1=c+(d2-1)*(c-1);
% L1=zeros(r1,c);
% L=zeros(r1,c1);
% for j=1:c
%     L1(:,j)=transpose(interp1(p,transpose(B(:,j)),p1));
% end
% for i=1:r1
%     L(i,:)=interp1(q,L1(i,:),q1);
% end
% L=uint8(L);
% imshow(L);
%     
d1=3;
d2=2;
B=imread('barbaraSmall.png');
B=double(B);
[r,c]=size(B);
r1=r+(r-1)*(d1-1);
c1=c+(c-1)*(d2-1);
L=zeros(r1,c1);
% L=uint8(L);
% L=im2double(L);
% imshow(uint8(B));
for x=d1:r*d1
    x1=floor(x/d1);
    x2=ceil(x/d1);
    if x1==x2
    	f1=0.5;
    	f2=0.5;
    else
    	f1=x/d1-x1;
    	f2=x2-x/d1;
    end
    for y=d2:c*d2
    	y1=floor(y/d2);
    	y2=ceil(y/d2);
    	if y1==y2
    		g1=0.5;
    		g2=0.5;
    	else 
    		g1=y/d2-y1;
    		g2=y2-y/d2;
        end
        L(x-d1+1,y-d2+1)=f2*g2*B(x1,y1)+f2*g1*B(x1,y2)+f1*g2*B(x2,y1)+f1*g1*B(x2,y2);
    end
end
L=uint8(L);
B=uint8(B);

figure(2)
imshow(L);
% imshow(B);