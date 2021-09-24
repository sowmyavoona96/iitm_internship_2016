binranges = [1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25];
score1 = fopen('testScore_1.txt','r');
    x = fscanf(score1,'%lf');
    [sizeOfX m] = size(x);
score2 = fopen('testScore_2.txt','r');
    y = fscanf(score2,'%lf');
    [sizeOfY m] = size(y);
    
    %plot([x,y]);
    
  [binT indT] = histc(x,binranges);

for i=1 : size(binT,1)
  binT(i,1) = binT(i,1)/sizeOfX;
end

plot(binranges,binT,'g');

hold on;

[binF indF] = histc(y,binranges);

for i=1 : size(binF,1)
   binF(i,1) = binF(i,1)/sizeOfY;
end

plot(binranges,binF,'r');