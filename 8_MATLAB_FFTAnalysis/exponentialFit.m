% x = 0:100;
% y = 1 + sin(x - pi/3).*exp(-0.2*x);

function [f, b, c, raw] = exponentialFit(y)
% y = data{i}';

startInd = 1;
endInd = length(y)-250;

x = startInd:endInd;
y = y(startInd:endInd);

avg = mean(y);
ind = (y > avg);
x1 = x(ind);
y1 = log(y(ind) - avg);
A = [ones(numel(x1),1),x1(:)];

coeffs = lsqlin(A,y1(:),-A,-y1(:),[],[],[],[],[],optimset('algorithm','active-set','display','off'));

b = exp(coeffs(1));
c = coeffs(2);

f = avg+b*exp(c*x);

raw.x = x;
raw.y = y;
% figure, plot(x,y,'ro',x, f,'b-')