%% MyMainScript

tic;
%% Your code here

sigr=20; %sigma for range kernel
sigs=2; %sigma for spatial kernel
w=20; %window size

inp=load('barbara.mat');
inp=double(inp.imageOrig);

m1=max(max(inp));
m2=min(min(inp));
rng=m1-m2;
inp=inp*255/rng;
% inp=uint8(inp);
[r,c]=size(inp);
noise=normrnd(0,0.05*256,[r,c]);
noisy_img=noise+inp;
noisy_img=max(0,noisy_img(:,:));
noisy_img=min(255,noisy_img(:,:));
out_img=zeros(r,c);
x=1:41;
dum1=repmat(x,41,1);
y=transpose(1:41);
dum2=repmat(y,1,41);
mask=((dum1-21).^2+(dum2-21).^2)*-1;
RMSD=10000000;
minsr=3;
minss=1;
minrmsd=RMSD;
for z=1:20
     sigs=0.3+z*0.1;
    for k=20:40
         sigr=k;
        for j=1:r
            for i=1:c
                i1=max(i-w,1);
                i2=min(i+w,c);
                j1=max(j-w,1);
                j2=min(j+w,r);
                temp=noisy_img(j1:j2,i1:i2);
                dum=mask(21-(j-j1):21+(j2-j),21-(i-i1):21+(i2-i));
                fr=exp(((temp-noisy_img(j,i)).^2)/(-2*sigr^2));
                gs=exp(dum/(2*sigs^2));
                bilfil=fr.*gs;
                norm=sum(sum(bilfil));
                out_img(j,i)=sum(sum(bilfil.*temp))/norm;
            end
        end
        fig=figure('Name','Bilateral Filtering','NumberTitle','off');
        subplot(1,3,1);
        imshow(uint8(inp),[]);axis on;
        subplot(1,3,2);
        imshow(uint8(noisy_img),[]);axis on;
        subplot(1,3,3);
        imshow(out_img,[]);axis on;
        RMC=sum(sum(((inp-out_img).^2)/(r*c)));
        RMSD=RMC^0.5
        if RMSD < minrmsd
            minrmsd=RMSD;
            minsr=sigr;
            minss=sigs;
        end
        saveas(fig,strcat('Desktop/sr=',num2str(sigr),' ss=',num2str(sigs),' rmsd=',num2str(RMSD),'.jpg'));
        close(fig);
    % imshow(uint8(noisy_img));
    end
end
toc;
