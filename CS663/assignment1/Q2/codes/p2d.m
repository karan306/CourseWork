tic;
input_im1 = imread('church.png');
range = 0:1:256;
final_im1 = zeros(size(input_im1));
if sum(size(size(input_im1))) == 3
    count = 1;
else
    count = 3;
end
[m,n] = size(input_im1(:,:,1));
b = 1200;
halfb = round(b/2);
block = zeros(b,b);
for k = 1:count
    im_part = input_im1(:,:,k);
    [m,n] = size(im_part);
    for i = 1:m
        top = max(1,i-halfb);
        bottom = min(i+halfb,m);
        block = im_part(top:bottom,1:halfb+1);
        hist_counts = histcounts(block,range);
        for j = 1:n
            if j <= halfb+1
                hist_add = histcounts(im_part(top:bottom,j+halfb),range);
                hist_counts = hist_counts + hist_add;
            elseif j > n - halfb
                hist_sub = histcounts(im_part(top:bottom,j-halfb-1),range);
                hist_counts = hist_counts - hist_sub;
            else
                hist_add = histcounts(im_part(top:bottom,j+halfb),range);
                hist_sub = histcounts(im_part(top:bottom,j-halfb-1),range);
                hist_counts = hist_counts - hist_sub + hist_add;
            end
            h = cumsum(hist_counts);
            h = h/h(size(h,2));
            final_im1(i,j,k) = round(h(im_part(i,j)+1)*255);
        end
    end
end
final_im1=uint8(final_im1);
subplot(1,2,1);imshow(input_im1(: , : ,:) ,[]);axis on;colorbar;
subplot(1,2,2);imshow(final_im1(: , : ,:),[]);axis on;colorbar;
toc;