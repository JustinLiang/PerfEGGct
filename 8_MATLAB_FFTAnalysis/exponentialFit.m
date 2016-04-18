function [f, b, c, raw] = exponentialFit(y)

avg = mean(y(250:length(y)));
startInd = 1;
% endInd = length(y)-400 ;
endInd = length(y);

x = startInd:endInd;
y = y(startInd:endInd);

ind = (y > avg);
x1 = x(ind);
y1 = log(y(ind) - avg);

% % Incremental Method 2 Unknowns
% x1 = [];
% y1 = [];
% max_num=[];
% max_ind=[];
% incr = 25;
% for i=1:floor(size(y,1)/incr)
%     [max_num(end+1),max_ind(end+1)] = max(y(1+incr*(i-1):incr*i));
%     max_ind(end) = max_ind(end) + incr*(i-1);
%     if max_num(end) > avg
%         x1(end+1) = max_ind(end);
%         y1(end+1) = log(max_num(end)-290);
%     end
% end
% plot(max_ind,max_num,'x','Color','r'); hold on;
% coeffs = polyfit(x1,y1,1)
% b = exp(coeffs(2));
% c = coeffs(1);

% Incremental Method 1 Unknown (b is constrained y(1)-290 = b)
b = y(1) - avg;
c = [];
max_num=[];
max_ind=[];
incr = 25;
for i=1:floor(size(y,1)/incr)
    [max_num(end+1),max_ind(end+1)] = max(y(1+incr*(i-1):incr*i));
    max_ind(end) = max_ind(end) + incr*(i-1);
    if max_num(end) > avg
        c(end+1) = (log(max_num(end)-avg)-log(b))/max_ind(end);
    end
end
plot(max_ind,max_num,'x','Color','r'); hold on;
c = mean(c);

% Find Peaks Method
% [max_num,max_ind] = findpeaks(y(ind));
% plot(max_ind,max_num,'x','Color','r'); hold on;
% x1 = max_ind;
% y1 = log(max_num-290);
% coeffs = polyfit(x1,y1,1)
% b = exp(coeffs(2));
% c = coeffs(1);

% Lsqlin Method
% A = [ones(numel(x1),1),x1(:)]*1.00;
% coeffs = lsqlin(A,y1(:),-A,-y1(:),[],[],[],[],[],optimset('algorithm','active-set','display','off'));
% b = exp(coeffs(2));
% c = coeffs(1);

% % RANSAC Method
% ind = (y > avg);
% x1 = x(ind);
% y1 = log(y(ind) - avg);
% iterNum = 300;
% thDist = 0.5;
% thInlrRatio = .1;
% [t,r] = ransac([x1;y1'],iterNum,thDist,thInlrRatio);
% k1 = -tan(t);
% b1 = r/cos(t);
% % plot(x1,k1*x1+b1,'r'); hold on;
% b = exp(b1);
% c = k1;

% plot(x1,y1,'.'); hold on;

yfit=log(b)+c*x1;
% plot(x1,yfit);

f = avg+b*exp(c*x);

raw.x = x;
raw.y = y;
% figure, plot(x,y,'ro',x, f,'b-'); hold on;