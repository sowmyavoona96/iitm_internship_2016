noOfTrainFiles = 1;
fidActual = fopen('actualDigit.txt','r');
x = fscanf(fidActual,'%d');
count = 1;
actualDigit = zeros(11,714);
for i=1:11
    for j=1:714
        actualDigit(i,j) = x(count,1);
        count = count+1;
    end
end

fclose(fidActual);

targetRec = zeros(11,714,1); 
for t =1:noOfTrainFiles
    digitRec = zeros(11,714);
    digitFile = strcat('digitRecNorm.txt');
    fidDigitRec = fopen(digitFile,'r');
    x = fscanf(fidDigitRec,'%e');
    count = 1;
    for i=1:11
        for j=1:714
             digitRec(i,j) = x(count,1);
             count = count+1;
        end
    end
    targetRec(:,:,t) = digitRec;

end


    plotconfusion(actualDigit,targetRec(:,:,1),'trainList3');
   % plotconfusion(actualDigit,targetRec(:,:,6));