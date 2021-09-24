clear all;
clc;

opFiles = char('output/output_6/output_1');
for i = 2 : 11
    s = strcat('output/output_6/output_',num2str(i));
    opFiles = char(opFiles,s);
end

% for i = 1 : 11
%     opFid(i,1) = fopen(opFiles(i,:),'r');
% end    

testScore = zeros(550,11);

 for i = 1:11
    x(i,1) = importdata(opFiles(i,:),' ',9);
 end 

 for k = 1:11
     i = 6;
    for j = 1 : 550
        l = cell2mat((x(k).textdata(i,5)));
        testScore(j,k) = str2num(l(1,:));
        i = i + 1;
    end
 end

 digitRec = zeros(550,11);
 
 for  i = 1 : 550
     ind = 1;
   for j = 1 : 11
       if testScore(i,j) > testScore(i,ind)
           ind = j ;
       end
   end
   digitRec(i,ind) = 1;
 end
 
 fid = fopen('testScores.txt','w');
 for i = 1:550
     for j = 1:11
        fprintf(fid,'%d ', testScore(i,j));
     end
     fprintf(fid,'\n');
 end
 %% ---------------------------- score plot for eer ------------------------- 
 
 binranges = linspace(100,800,14);
 
 for i = 1 : 11
       trueScores = testScore(i,i);
 end
 
