clear all;
clc;

binranges = [1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25];
%scoreBinsT = zeros(11,1);
%countScoresT = zeros(11,1);

tscores = fopen('task2-avgT.txt','r');
x = fscanf(tscores,'%lf');
[sizeOfX m] = size(x);
disp(sizeOfX);

[binT indT] = histc(x,binranges);

for i=1 : size(binT,1)
  binT(i,1) = binT(i,1)/sizeOfX;
end

plot(binranges,binT,'g');

hold on;

%--------------impostor ------------------------
scoreBinsF = zeros(11,1);
countScoresF = zeros(11,1);

fscores = fopen('task2-avgF.txt','r');
y = fscanf(fscores,'%lf');
[sizeOfY z] = size(y);
disp(sizeOfY);


[binF indF] = histc(y,binranges);

for i=1 : size(binF,1)
   binF(i,1) = binF(i,1)/sizeOfY;
end

plot(binranges,binF,'r');

legend('Tscores','FScores');
%Y = discretize(x(:,1),'g');

% for  i = 1: sizeOfY
%     if(1< y(i,1) && y(i,1) < 2)
%         scoreBinsF(1,1) = scoreBinsF(1,1) + y(i,1);
%         countScoresF(1,1) = countScoresF(1,1) + 1;
%  
%     elseif(2 < y(i,1) && y(i,1) < 3)
%         scoreBinsF(2,1) = scoreBinsF(2,1) + y(i,1);
%         countScoresF(2,1) = countScoresF(2,1) + 1;
%         
%     
%     elseif(3 < y(i,1)  && y(i,1) < 4)
%         scoreBinsF(3,1) = scoreBinsF(3,1) + y(i,1); 
%         countScoresF(3,1) = countScoresF(3,1) + 1;
%     
%     elseif(4 < y(i,1)  && y(i,1) < 5)
%         scoreBinsF(4,1) = scoreBinsF(4,1) + y(i,1);
%         countScoresF(4,1) = countScoresF(4,1) + 1;
%     
%     elseif(5 < y(i,1)  && y(i,1) < 6)
%         scoreBinsF(5,1) = scoreBinsF(5,1) + y(i,1);
%         countScoresF(5,1) = countScoresF(5,1) + 1;
%     
%     elseif(6 < y(i,1)  && y(i,1) < 7)
%         scoreBinsF(6,1) = scoreBinsF(6,1) + y(i,1); 
%         countScoresF(6,1) = countScoresF(6,1) + 1;
%         
%     elseif(7 < y(i,1)  && y(i,1) < 8)
%         scoreBinsF(7,1) = scoreBinsF(7,1) + y(i,1); 
%         countScoresF(7,1) = countScoresF(7,1) + 1;
% 
%     elseif(8 < y(i,1)  && y(i,1) < 9)
%         scoreBinsF(8,1) = scoreBinsF(8,1) + y(i,1); 
%         countScoresF(8,1) = countScoresF(8,1) + 1;
%         
%     elseif(9 < y(i,1)  && y(i,1) < 10)
%         scoreBinsF(9,1) = scoreBinsF(9,1) + y(i,1); 
%         countScoresF(9,1) = countScoresF(9,1) + 1;
%         
%     elseif(10 < y(i,1)  && y(i,1) < 11)
%         scoreBinsF(10,1) = scoreBinsF(10,1) + y(i,1); 
%         countScoresF(10,1) = countScoresF(10,1) + 1;  
%         
%     elseif(11 < y(i,1)  && y(i,1) < 12)
%         scoreBinsF(11,1) = scoreBinsF(11,1) + y(i,1); 
%         countScoresF(11,1) = countScoresF(11,1) + 1;     
%     end
% end
% 
% totalF = sum(countScoresF);
% 
% for i=3 : 11
%     scoreBinsF(i,1) = scoreBinsF(i,1)/countScoresF(i,1);
%     countScoresF(i,1) =  countScoresF(i,1)/totalF;
%     
% end
% 
% plot(scoreBinsF,countScoresF,'r');