noOfDigits = 11;

fid = fopen('lists/testList','r');
testList= textscan(fid,'%s','Delimiter','\n');
fclose(fid);

fid = fopen('lists/trainList_1','r');
trainList_1= textscan(fid,'%s','Delimiter','\n');
fclose(fid);

noOfTrain = size(trainList_1{1,1},1);
noOfTest = size(testList{1,1},1);
%noOfTest = 2;

digitRec = zeros(11,noOfTest);
actualDigit = zeros(11,noOfTest);

for i = 1:noOfTest    
    score = zeros(noOfTrain,1);
    char = testList{1,1}{i,1}(12:12);
    
    %------------------actual Digit for test files----------------%
    
   if(char == 'o')
        actualDigit(10,i) = 1 ;
   elseif(char == 'z')
        actualDigit(11,i) = 1;
   else
        actualDigit((str2double(char)),i) = 1 ;
   end
    
    %-----------------digit recognized----------------%
    for j = 1:noOfTrain
       %disp(testList{1,1}{i,1});disp(trainList_1{1,1}{j,1});
       score(j,1) = findScore(testList{1,1}{i,1},trainList_1{1,1}{j,1});
       %disp(score(j,1));
    end
    
    %disp(score);
    
  index = 1;
  for k = 1:noOfTrain
      if(score(index,1)>score(k,1))
         index = k;
      end
  end
 
  digitRec(index,i) = 1;        
     
end

%disp(actualDigit);
plotconfusion(actualDigit,digitRec);