function [frequency] = FFTAnalysis(fileName, N)
    figure;

    N = double(N);

    % Change the current folder to the folder of this m-file.
    % Courtesy of Brett Shoelson
    if(~isdeployed)
      cd(fileparts(which(mfilename)));
    end
    dir = '..\5_C_Sharp_Egg_Test_Data_Logger\Data_Log_Files';

    Fs = 111.9;           % Sampling frequency
    T = 1/Fs;

    data = cell(1,N);
    
    for i=1:N;
        postfix = '.txt';
        fullFileName = strcat({dir},{'\'},{fileName},{int2str(i)},{postfix});
%         fullFileName = strcat({fileName},{int2str(i)},{postfix});
        data{i} = load(fullFileName{1});

        average = mean(data{i});
        indices = find(abs(data{i})>1000);
        data{i}(indices) = average;
        
        [m,v] = max(data{i});
        data{i} = data{i}(v:end);
%         [b,a] = butter(2,[1/(Fs/2) 4/(Fs/2)]);
%         [b,a] = butter(2,5.6/(Fs/2));
%         data{i} = filtfilt(b,a,data{i});

        L = length(data{i});

        Y = fft(data{i});
        P2 = abs(Y/L);
        P1 = P2(1:L/2+1);
        P1(1) = 0;
        P1(2:end-1) = 2*P1(2:end-1);
        f = Fs*(0:(L/2))/L;
        t = (0:L-1)*T;        % Time vector

        [m,n] = max(P1);
        frequency(i) = n*(Fs/L);
        
        subplot(3,N,i);
        plot(t,data{i});
        textFile = strcat({AppendBackslash(fileName)},{int2str(i)},{postfix});
        title({'Signal for ';textFile{1}});
        
        subplot(3,N,i+N);
        plot(f,P1);
        freq_avg(i) = mean(P1);
        freq_std(i) = std(P1);
        title(sprintf('Frequency Histogram\nMean: %.3f, SD: %.2f', freq_avg(i), freq_std(i)));
%         peakFreq = strcat({'Egg Frequency: '},{num2str(frequency(i))},{' Hz'});
%         title({'Frequency Histogram';peakFreq{1}});
        
        subplot(3,N,i+N*2);
%         data{i};
%         s=exp2fit(t,data{i},2,'no');
%         w=1e9;
%         %--- plot and compare
%         fun = @(s,t) s(1)+s(2)*exp(-t/s(3))+s(4)*exp(-t/s(5));
%         tt=linspace(0,20,200)*1e-9;
%         ff=fun(s,tt);
%         plot(t,data{i},'.',tt,real(ff));
%         %--- evaluate parameters:
% %         sprintf(['f=1+3*exp(-t/5e-9).*sin(w*(t-2e-9))\n',...
% %         'Frequency: w_fitted=',num2str(-imag(1/s(3)),3),' w_data=',num2str(w,3),'\n',...
% %         'Damping: tau=',num2str(1/real(1/s(3)),3),'\n',...
% %         'Offset: s1=',num2str(real(s(1)),3)])
%         tau(i) = 1/real(1/s(3));
%         damping = strcat({'Damping: tau='},{num2str(1/real(1/s(3)),3)});
        [E, const_b(i), const_c(i), rawData] = exponentialFit(data{i});
        hold on;
        plot(rawData.x, rawData.y, '.');
        plot(rawData.x, E,'r-');
        title(sprintf('Fitted Decay\nb = %.1f, c = %.5f',const_b(i), const_c(i)))
%         title(damping{1});
    end
    
    averageFrequency = mean(frequency)
    avgdecayC = mean(const_c)

%     indices = find(tau(i)>0);
%     averageTau = mean(tau(indices))
end

function [outStr] = AppendBackslash(tStr) 
    special = '_';

    outStr = '';
    for l = tStr
        if (length(find(special == l)) > 0)
            outStr = [outStr, '\', l];
        else
            outStr = [outStr, l];
        end
    end
end