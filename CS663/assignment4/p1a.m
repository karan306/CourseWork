function p1a(inp_path,np,ni,h,w,k_orl,nt,offset,top)
    X=zeros(h*w,np*ni);
    folders=dir(inp_path);
    folders(4).name
    for i=1:np
        gallery=dir(strcat(inp_path,'/',folders(i+offset).name));
        for j= 3:ni+2
            A=imread(strcat(inp_path,'/',folders(i+offset).name,'/',gallery(j).name));
            [r,c]=size(A);
            B=reshape(A,[r*c,1]);
            X(:,ni*(i-1)+j-2)=B(:,1);
        end
    end
   % X(:,1)
    M=mean(X,2);
    % M=repmat(X,240,1);
    % X=X-M;
    for i=1:np*ni
    %     M=mean(X(:,i));
        X(:,i)=X(:,i)-M;
    end

    L=X'*X;
    [W,E]=eig(L);
    % [w,E]=sortem(W,E);
    V=X*W;
    S=sum((V).^2).^0.5;
    S=repmat(S,h*w,1);
    V=V./S;

    % V=normc(V);
    %k_orl=[1, 2, 3, 5, 10, 15, 20, 30, 50, 75, 100, 150, 170];
    [h,s_orl]=size(k_orl);
    rec_rate_orl=zeros(1,s_orl);
   % k_yale=[1, 2, 3, 5, 10, 15, 20, 30, 50, 60, 65, 75, 100, 200, 300, 500, 1000];
    %[k,s_yale]=size(k_yale);
    for l=1:s_orl
        k=k_orl(1,l);
        A=(V(:,(ni*np+1-k-top):ni*np-top))'*X;
        count=0;
        for i=1:np
             gallery=dir(strcat(inp_path,'/',folders(i+offset).name));
             [q,w]=size(gallery);
            for j=ni+3:q
                count=count+1;
                B=imread(strcat(inp_path,'/',folders(i+offset).name,'/',gallery(j).name));
                [r,c]=size(B);
                B=reshape(B,[r*c,1]);
    %             M=mean(B);
                B=double(B);
                B=B-M;
                B=(V(:,(ni*np+1-k-top):ni*np-top))'*B;
                m=9999999999999879;
                index=1;
                for h=1:ni*np
                    D=B-A(:,h);
                    D=D.^2;
                    if m>sum(sum(D))
                        m=sum(sum(D));
                        index=h;
                    end
                    
                end
                if ceil(index/ni)==i
                    rec_rate_orl(1,l)=rec_rate_orl(1,l)+1;
                end
            end
        end
        rec_rate_orl(1,l)=rec_rate_orl(1,l)*100/count;
    end
    rec_rate_orl
end
