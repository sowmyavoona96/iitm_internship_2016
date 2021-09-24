testFile = 'featDir/ft_1a.mfcc';
trainFile = 'featDir/st_1b.mfcc';
fidTe = fopen(testFile,'r');

format long e
x = fscanf(fidTe,'%e');

noOfDimTe = x(1,1); 
noOfVecTe = x(2,1);

featureVectorSetTe = zeros(noOfVecTe,noOfDimTe);

count = 3;
for  i = 1:noOfVecTe
      for j = 1:noOfDimTe
          featureVectorSetTe(i,j) = x(count,1);  
          count = count + 1;
      end
end
 
fclose(fidTe);

%disp(featureVectorSetTe);
    
  %-----------------------read train feature vector set--------------%
    fidTr = fopen(trainFile,'r');
    
    y = fscanf(fidTr,'%e');
    noOfDimTr = y(1,1); 
    noOfVecTr = y(2,1);
    
    disp(noOfDimTr);
    disp(noOfVecTr);
    
    featureVectorSetTr = zeros(noOfVecTr,noOfDimTr);
    
    format long e
   
    count = 3;
    for  i = 1:noOfVecTr
          for j = 1:noOfDimTr
              featureVectorSetTr(i,j) = y(count,1);  
              count = count + 1;
          end
    end
    
    fclose(fidTr);
    
    %disp(featureVectorSetTr);
%%%%%%-------------------------dtw-------------------------%%%%%
    distances = zeros(noOfVecTe,noOfVecTr);

    for i=1:noOfVecTe
        for j=1:noOfVecTr
             distances(i,j) = norm(featureVectorSetTe(i,:) - featureVectorSetTr(j,:));
        end
    end
    
    cost = zeros(noOfVecTe,noOfVecTr);
    cost(1,1) = distances(1,1);

    for j = 2:noOfVecTr
        cost(1,j) = distances(1,j) + cost(1,j-1);
    end
    for i = 2:noOfVecTe
        cost(i,1) = distances(i,1) + cost(i-1,1);
    end

    for i = 2:noOfVecTe
        for j = 2: noOfVecTr
            cost(i,j) = distances(i,j) + min([cost(i-1,j) cost(i,j-1) cost(i-1,j-1)]);
        end
    end
    
    score = cost(noOfVecTe,noOfVecTr)/double(noOfVecTe+noOfVecTr);
    disp(score);
    