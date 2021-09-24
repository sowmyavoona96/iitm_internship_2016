fscores = fopen('task2-avgF.txt','r');
y = fscanf(fscores,'%lf');
[sizeOfY t] = size(y);
disp(sizeOfY);

[z mean sigma] = zscore(y);

fwrite = fopen('fnormAvg.txt','w');
  
  for i = 1 : sizeOfY
    fprintf(fwrite,'%e\n',z(i,1));
  end
 fclose(fwrite); 
 
binranges = linspace(-4,4,20);
[binF indF] = histc(z,binranges);

for i=1 : size(binF,1)
   binF(i,1) = binF(i,1)/sizeOfY;
end

%plot(binranges,binF,'r');

%plot(zscore);

tscores = fopen('task2-avgT.txt','r');
x = fscanf(tscores,'%lf');
[sizeOfX m] = size(x);
disp(sizeOfX);
[zX meanX,sigmaX] = zscore(x);
hold on;

   for i=1:sizeOfX
      x(i,1) = (x(i,1)-mean)/sigma;
   end
   
   
  twrite = fopen('tnormAvg.txt','w+');
  for i = 1 : sizeOfX
    fprintf(twrite,'%e\n',x(i,1));
    disp(x(i,1));
  end
  
  fclose(twrite);
  
 [binT indT] = histc(x,binranges);

for i=1 : size(binT,1)
  binT(i,1) =  (binT(i,1)/sizeOfX);
end

plot(binranges,binF);
plot(binranges,binT);

legend('fscores','tscores');
disp(max(binF));
disp(max(binT));

