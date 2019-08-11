function myHarrisCornerDetector(image_path,sigmax,sigmay,w)
    tic;
    
    %%  loading image
    I = load(image_path);
    I = I.imageOrig;

    %%    scale between [0,1]
    min_val_orig = min(min(I));
    max_val_orig = max(max(I));
    I = (I-min_val_orig)/(max_val_orig-min_val_orig);

    %%	Gaussian smoothing and rescaling
    Ix = imgaussfilt(I,sigmax);
    Iy = imgaussfilt(I,sigmay);

    min_val_orig = min(min(Ix));
    max_val_orig = max(max(Ix));
    Ix = (Ix-min_val_orig)/(max_val_orig-min_val_orig);

    min_val_orig = min(min(Iy));
    max_val_orig = max(max(Iy));
    Iy = (Iy-min_val_orig)/(max_val_orig-min_val_orig);
    
    %%   convolution with prewitt matrix for gradient
    h = fspecial('prewitt');
    
    Ix = conv2(h.',Ix);
    Iy = conv2(h,Iy);
    
    %%  iterating over image
    [r,c]=size(I);
    B = zeros(r,c);
    for j=1:r
        for i=1:c
            i1=max(i-w,1);
            i2=min(i+w,c);
            
            j1=max(j-w,1);
            j2=min(j+w,r);
    
            ix1=i-i1;
            ix2=i2-i;
            jy1=j-j1;
            jy2=j2-j;
            box_size = min([ix1 jy1 ix2 jy2]);
            win = fspecial('gaussian',2*box_size+1);
            A = [0 0; 0 0];
            for alpha=i-box_size:i+box_size
                for beta=j-box_size:j+box_size
                    A=A+(win(alpha-i+box_size+1,beta-j+box_size+1)*[(Ix(alpha,beta))^2 Ix(alpha,beta)*Iy(alpha,beta); Ix(alpha,beta)*Iy(alpha,beta) (Iy(alpha,beta))^2]);
                end
            end
            B(j,i)= det(A)-0.1*trace(A)^2;
        end
    end
    
    

    

    %% plotting images
    figure    
    subplot(1,4,1);
    imshow(I);
    axis on;colorbar;
    title('Original Image');
    
    subplot(1,4,2);
    imshow(Ix,[0,1]);
    axis on;colorbar;
    title('Image gradient along X axis');

    subplot(1,4,3);
    imshow(Iy,[0,1]);
    axis on;colorbar;
    title('Image gradient along Y axis');
    
    subplot(1,4,4);
    m1=min(min(B))
    m2=max(max(B))
    imshow((B-m1)/(m2-m1));
    axis on;colorbar;
    title('Final Image');
    toc;
    
end
