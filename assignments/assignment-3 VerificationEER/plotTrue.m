binranges = [1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23];
scoreBinsT = zeros(11,1);
countScoresT = zeros(11,1);

tscores = fopen('Tscores2.txt','r');
x = fscanf(tscores,'%lf');
[sizeOfX m] = size(x);
disp(sizeOfX);

[binT indT] = histc(x,binranges);

for i=1 : size(binT,1)
  binT(i,1) = binT(i,1)/62832;
end

plot(binranges,binT,'g');
%Y = discretize(x(:,1),edges);

% for  i = 1: sizeOfX
%     if(1< x(i,1) && x(i,1) < 2)
%         scoreBins(1,1) = scoreBins(1,1) + x(i,1);
%         countScores(1,1) = countScores(1,1) + 1;
%  
%     elseif(2 < x(i,1) && x(i,1) < 3)
%         scoreBins(2,1) = scoreBins(2,1) + x(i,1);
%         countScores(2,1) = countScores(2,1) + 1;
%         
%     
%     elseif(3 < x(i,1)  && x(i,1) < 4)
%         scoreBins(3,1) = scoreBins(3,1) + x(i,1); 
%         countScores(3,1) = countScores(3,1) + 1;
%     
%     elseif(4 < x(i,1)  && x(i,1) < 5)
%         scoreBins(4,1) = scoreBins(4,1) + x(i,1);
%         countScores(4,1) = countScores(4,1) + 1;
%     
%     elseif(5 < x(i,1)  && x(i,1) < 6)
%         scoreBins(5,1) = scoreBins(5,1) + x(i,1);
%         countScores(5,1) = countScores(5,1) + 1;
%     
%     elseif(6 < x(i,1)  && x(i,1) < 7)
%         scoreBins(6,1) = scoreBins(6,1) + x(i,1); 
%         countScores(6,1) = countScores(6,1) + 1;
%         
%     elseif(7 < x(i,1)  && x(i,1) < 8)
%         scoreBins(7,1) = scoreBins(7,1) + x(i,1); 
%         countScores(7,1) = countScores(7,1) + 1;
% 
%     elseif(8 < x(i,1)  && x(i,1) < 9)
%         scoreBins(8,1) = scoreBins(8,1) + x(i,1); 
%         countScores(8,1) = countScores(8,1) + 1;
%         
%     elseif(9 < x(i,1)  && x(i,1) < 10)
%         scoreBins(9,1) = scoreBins(9,1) + x(i,1); 
%         countScores(9,1) = countScores(9,1) + 1;
%     
%     elseif(10 < x(i,1)  && x(i,1) < 11)
%         scoreBins(10,1) = scoreBins(10,1) + x(i,1); 
%         countScores(10,1) = countScores(10,1) + 1;  
%         
%     elseif(11 < x(i,1)  && x(i,1) < 12)
%         scoreBins(11,1) = scoreBins(11,1) + x(i,1); 
%         countScores(11,1) = countScores(11,1) + 1;    
%     end
% end
% 
% total = sum(countScores);
% 
% for i=3 : 11
%     scoreBins(i,1) = scoreBins(i,1)/countScores(i,1);
%     countScores(i,1) =  countScores(i,1)/total;
%     
% end
% 
% 
% plot(scoreBins,countScores,'g');
