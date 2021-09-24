noOfTrainFiles = 6;
fidActual = fopen('actualDigit.txt','r');
x = fscanf(fidActual,'%d');
count = 1;
actualDigit = zeros(11,550);
for i=1:11
    for j=1:550
        actualDigit(i,j) = x(count,1);
        count = count+1;
    end
end

fclose(fidActual);

targetRec = zeros(11,550,6); 
for t =1:noOfTrainFiles
    digitRec = zeros(11,550);
    digitFile = strcat('digitRec_',num2str(t),'.txt');
    fidDigitRec = fopen(digitFile,'r');
    x = fscanf(fidDigitRec,'%e');
    count = 1;
    for i=1:11
        for j=1:550
             digitRec(i,j) = x(count,1);
             count = count+1;
        end
    end
    targetRec(:,:,t) = digitRec;

end


    plotconfusion(actualDigit,targetRec(:,:,1),'trainList1',actualDigit,targetRec(:,:,2),'trainList2',actualDigit,targetRec(:,:,3),'trainList3',actualDigit,targetRec(:,:,4),'trainList4',actualDigit,targetRec(:,:,5),'trainList5',actualDigit,targetRec(:,:,6),'trainList6');
   % plotconfusion(actualDigit,targetRec(:,:,6));