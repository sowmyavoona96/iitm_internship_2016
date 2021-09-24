clear all;
 
x = [1 1 2 3 2 0];
y = [0 1 1 2 3 2 1];
t1 = [0 1 2 3 4 5];
t2 = [0 1 2 3 4 5 6];

plot(t1,x,'r',t2,y,'g');

distances = zeros(length(y),length(x));

for i=1:length(y)
    for j=1:length(x)
        distances(i,j) = (y(i) - x(j))*(y(i) - x(j));
    end
end

disp (distances);
imagesc(distances);         
colormap(flipud(gray));

cost = zeros(length(y),length(x));
cost(1,1) = distances(1,1);

for j = 2:length(x)
    cost(1,j) = distances(1,j) + cost(1,j-1);
end
for i = 2:length(y)
    cost(i,1) = distances(i,1) + cost(i-1,1);
end

for i = 2:length(y)
    for j = 2: length(x)
        cost(i,j) = distances(i,j) + min([cost(i-1,j) cost(i,j-1) cost(i-1,j-1)]);
    end
end

disp(cost);
imagesc(cost);         
colormap(flipud(gray));

%finding path

path = [length(x) length(y)];

i = length(y); 
j = length(x);

while(i>1 && j>1)
  if (i==1)
      j = j-1;
  elseif (j==1)
      i = i-1;
  elseif (cost(i-1,j) == min([cost(i-1,j) cost(i,j-1) cost(i-1,j-1)]))
      i = i- 1;
  elseif (cost(i,j-1) == min([cost(i-1,j) cost(i,j-1) cost(i-1,j-1)]))
      j = j- 1;
  else
      i = i-1;
      j = j-1;
  end
  
  path = [path;[j i]];
end 
  path = [path;[1 1]];
disp(path);

path_x = path(:,1);
path_y = path(:,2);

plot(path_x,path_y);
totalCost = 0;

for i = 1: length(path(:,1))
    totalCost = totalCost + distances(path(i,2),path(i,1)); 
    
end

disp(totalCost);


s = 'featDir/ft_1a.mfcc';
disp(s(12:12));