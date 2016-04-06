function [frequency] = FFTAnalysis( N)
    close all
    N = double(N);

    % Change the current folder to the folder of this m-file.
    % Courtesy of Brett Shoelson
    if(~isdeployed)
      cd(fileparts(which(mfilename)));
    end

    Fs = 111.9;           % Sampling frequency
    T = 1/Fs;

    data = cell(1,N);

    for i=1:N;
        fileName = 'DATA_3MIN_3_';
        postfix = '.txt';
        fullFileName = strcat({fileName},{int2str(i)},{postfix});
        data{i} = load(fullFileName{1});

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

        [m,n] = max(P1);
        frequency = n*(Fs/L);
        
        subplot(2,N,i);
        plot(t,data{i});
        textFile = strcat({AppendBackslash(fileName)},{int2str(i)},{postfix});
        title({'Raw Signal for ';textFile{1}});
        
        subplot(2,N,i+N);
        plot(f,P1);
        peakFreq = strcat({'Egg Frequency: '},{num2str(frequency)},{' Hz'});
        title({'Frequency Histogram';peakFreq{1}});
    end
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
