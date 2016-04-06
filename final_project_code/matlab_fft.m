function [frequency] = FFTAnalysis(fileName, N)

close all
clear all

N = 5;
Fs = 111.9;           % Sampling frequency
T = 1/Fs;

data = cell(1,N);

for i=1:N;
%     fileName = 'DATA_3MIN_3_';
    postfix = '.txt';
    fileName = strcat({fileName},{int2str(i)},{postfix});
    data{i} = load(fileName{1});
    
    average = mean(data{i});
    indices = find(abs(data{i})>1000);
    data{i}(indices) = average;
    
    [b,a] = butter(4,[5/(Fs/2) 12/(Fs/2)]);
    data{i} = filtfilt(b,a,data{i});
    
    L = length(data{i});

    Y = fft(data{i});
    P2 = abs(Y/L);
    P1 = P2(1:L/2+1);
    P1(1) = 0;
    P1(2:end-1) = 2*P1(2:end-1);
    f = Fs*(0:(L/2))/L;
    t = (0:L-1)*T;        % Time vector
    
    subplot(2,N,i);
    plot(t,data{i});
    
    subplot(2,N,i+N);
    plot(f,P1);
    title(strcat({fileName},{int2str(i)},{postfix}));
    
    [m,n] = max(P1);
    frequency(i) = n*(Fs/L);
end

frequency