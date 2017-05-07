function [data,mdata] = Q1data()
%%
%%Set up
data = hw3import();
[row,column] = size(data);

%%
%%Deal with blank row
sum = 0;
count = 0;
for i = 1:row
    if(data{i,column}~=-1)
        sum = sum+data{i,column};
        count = count+1;
    end;
end;
avg = sum/count;
for k = 1:row
    if(data{k,column}==-1)
        data{k,column} = avg;
    end;
end;

%%
%%Standardization
mdata = data{:,6:column};
for j = 2:column-5
    %avg = mean(mdata(:,j));
   % sd = std(mdata(:,j));
    maxi = max(mdata(:,j));
    mini = min(mdata(:,j));
   % if(sd==0)
   %     sd=1;
   % end;
   
    for i = 1:row
        if(maxi~=mini)
            mdata(i,j) = (mdata(i,j)-mini)/(maxi-mini);
        else
            
    end;
end;
end