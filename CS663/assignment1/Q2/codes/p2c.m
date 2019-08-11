tic;
ref=imread('retinaRef.png');
refmas=imread('retinaRefMask.png');
[r,c,l]=size(ref);
for i=1:r
    for j=1:c
        if refmas(i,j)==0
            ref(i,j,:)=zeros(1,1,l)+258;
        end
    end
end
inpmas=imread('retinaMask.png');
inp=imread('retina.png');
[r,c,l]=size(inp);
for i=1:r
    for j=1:c
        if inpmas(i,j)==0
            inp(i,j,:)=zeros(1,1,l)+258;
        end
    end
end
inp=inp+1;
ref=ref+1;
% ref=double(B);

final=uint8(zeros(r,c,l));
x=0:256;
for p=1:l
    F=cumsum(histcounts(ref(:,:,p),x));
    G=cumsum(histcounts(inp(:,:,p),x));
    M=uint8(zeros(1,256));
    j=1;
    for i=1:256
        m=10000000;
        for k=1:256
            if (G(i)-F(k))>=0
                m=G(i)-F(k);
                j=k;
%                 break;
            end
        end
        M(i)=j;
    end
    final(:,:,p)=M(inp(:,:,p));
end
% final=final-1;
for i=1:r
    for j=1:c
        if inpmas(i,j)==0
            final(i,j,:)=zeros(1,1,l);
        end
    end
end
ref=ref-1;
imshow(final);
% figure(2)
% imshow(ref);
toc;
