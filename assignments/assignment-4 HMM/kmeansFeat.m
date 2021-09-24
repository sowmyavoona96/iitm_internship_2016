clear all;
clc;

trainfiles = (importdata('lists/trainList_6'));
noOfFiles = size(trainfiles,1);

noOfSpeakers = noOfFiles/11;
trainData(1,1) = importdata(trainfiles{1,1},' ',1);
allFeatVec = trainData(1,1).data;
for i=2:noOfFiles
    trainData(i,1) = importdata(trainfiles{i,1},' ',1);
    allFeatVec = [allFeatVec;trainData(i,1).data];
end

[clustData C] = kmeans(allFeatVec,50);
trNames = char('trainFiles/trainFile_6/trainFiles_1.txt');
for i = 2 : 11
    s = strcat('trainFiles/trainFile_6/trainFiles_',num2str(i),'.txt');
    trNames = char(trNames,s);
end

for i = 1 : 11
    trainFid(i,1) = fopen(trNames(i,:),'w');
end    

k = 1;

for i = 1: noOfFiles
    
    digit = int16(floor((i-1)/noOfSpeakers) + 1);
    disp('i');
    disp(i);
    disp('digit');
    disp(digit);
    disp(trNames(digit,:));
    
    s = (trainData(i,1).textdata(1,1));
    [dim noOfVec] = strread(s{1,1});
    
    disp('noOfVec');
    disp(noOfVec);
    
    for j = 1 : noOfVec
        disp(k);
        fprintf(trainFid(digit,1),'%d ',clustData(k,1));
        k = k + 1;
    end
          fprintf(trainFid(digit,1),'\n');
end

for i = 1 : 11
    fclose(trainFid(i,1));
end  

testfiles = (importdata('lists/testlist'));
noOftestFiles = size(testfiles,1);
testFid = fopen('testFiles_6.txt','w');
global featVec;
for i=1:noOftestFiles
    disp('file number: ');
    disp(i);
    testData(1,1) = importdata(testfiles{i,1},' ',1);
    featVec = testData(1,1).data;
    noOfVecTe = size(featVec);
    
    for j=1 : noOfVecTe
        distances = pdist2(featVec(j,:),C);
        [minDist ,ind] = min(distances);
        fprintf(testFid,'%d ',ind);
        disp(j); disp(' ');disp(ind);
    end
        fprintf(testFid,'\n');
        disp('\n');
end

fclose(testFid);
