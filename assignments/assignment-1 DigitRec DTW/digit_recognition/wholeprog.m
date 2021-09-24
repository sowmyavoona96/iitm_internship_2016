noOfTrainFiles = 1;

fid = fopen('lists/testList','r');
testList= textscan(fid,'%s','Delimiter','\n');
fclose(fid);
noOfTest = size(testList{1,1},1);

for t = 1:noOfTrainFiles
    filename = strcat('lists/trainList_',num2str(t));
   
    fid = fopen(filename,'r');
    trainList= textscan(fid,'%s','Delimiter','\n');
    fclose(fid);
    
    noOfSpeakers = length(trainList{1,1})/11;
    
    digitRec = zeros(11,noOfTest);
    actualDigit = zeros(11,noOfTest);

    for k = 1: noOfTest
        countOfDigit = zeros(11,1);
        %------------------actual Digit for test files----------------%
        char = testList{1,1}{k,1}(12:12);
        
        if(char == 'o')
           actualDigit(10,k) = 1 ;
        elseif(char == 'z')
            actualDigit(11,k) = 1;
        else
            actualDigit((str2double(char)),k) = 1 ;
        end
            
        for i = 1 : noOfSpeakers
            score = zeros(11,1);
            digit = 1;
            for j = i:noOfSpeakers:(i+(10*(noOfSpeakers)))
               score(digit,1) =  findScore(testList{1,1}{k,1},trainList{1,1}{j,1});
               digit = digit + 1;
            end
            
            index = 1;
            for ind = 1:11
                if(score(index,1)>score(ind,1))
                   index = ind;
                end
            end
            
            countOfDigit(index,1) = countOfDigit(index,1)+1;
        end
        
        mainIndex = 1;
        for mainInd = 1:11
            if(countOfDigit(mainInd,1)>countOfDigit(mainIndex,1))
                mainIndex = mainInd;
            end
        end
        
        digitRec(mainIndex,k) = 1;
    end
    %plotconfusion(actualDigit,digitRec);
    targetRec(t,:,:) = digitRec;
end

    
    