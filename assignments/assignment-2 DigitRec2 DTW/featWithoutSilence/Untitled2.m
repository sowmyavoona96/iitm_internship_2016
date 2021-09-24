testfile = 'featDir1/51a.mfcc'; 
trainfile = 'featDirTrain1/pb_9b.mfcc';
%----------- read test feature vector set --------%
    fidTe = fopen(testfile,'r');
    
    headerTe = textscan(fidTe,'%d %d',1);
    noOfDimTe = headerTe{1,1};
    noOfVecTe = headerTe{1,2};
    
    featureVectorSetTe = zeros(noOfVecTe,noOfDimTe);
    
    format long e

    for  i = 1:noOfVecTe
        for j = 1:noOfDimTe
             x = cell2mat(textscan(fidTe,'%f',1));
             featureVectorSetTe(i,j)  = x;
        end
    end
  
    fclose(fidTe);
    
  %-----------------------train feature vector set--------------%
    fidTr = fopen(trainfile,'r');
    headerTr = textscan(fidTr,'%d %d',1);

     noOfDimTr = headerTr{1,1};
     noOfVecTr = headerTr{1,2};
        
     if(noOfVecTe > (noOfVecTr))
         noOfVecTe = (noOfVecTr);
     end
    featureVectorSetTr = zeros(noOfVecTr,noOfDimTr);
    
    format long e

    for  i = 1:noOfVecTr
        for j = 1:noOfDimTr
           x = cell2mat(textscan(fidTr,'%f',1));
           featureVectorSetTr(i,j) = x;
        end
    end
    
    %-------------------------dtw-------------------------%
    distances = zeros(noOfVecTe,noOfVecTr);

    for i=1:noOfVecTe
        for j=1:noOfVecTr
             distances(i,j) = norm(featureVectorSetTe(i,:) - featureVectorSetTr(j,:));
        end
    end
    
%imagesc(distances);         
%colormap(flipud(gray));

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

%disp(cost);
%imagesc(cost);         
%colormap(flipud(gray));

arr = zeros(noOfVecTe,1);
for i=1:noOfVecTe
    arr(i,1) = cost(i,noOfVecTr)/double(i+noOfVecTr); 
end
disp('3n/2');
disp(noOfVecTe);
disp('n');
disp(noOfVecTr/4);
plot(arr);
    
   