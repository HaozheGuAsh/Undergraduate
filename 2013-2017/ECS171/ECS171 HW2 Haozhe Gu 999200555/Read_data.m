function [data,y] = Read_data()

filename = 'yeast.data';
formatSpec = '%*10s%6f%6f%6f%6f%6f%6f%6f%6f%s%[^\n\r]';
fileID = fopen(filename,'r');
dataArray = textscan(fileID, formatSpec, 'Delimiter', '', 'WhiteSpace', '',  'ReturnOnError', false);
dataArray{9} = strtrim(dataArray{9});
fclose(fileID);
var1 = dataArray{:, 1};
var2 = dataArray{:, 2};
var3 = dataArray{:, 3};
var4 = dataArray{:, 4};
var5 = dataArray{:, 5};
var6 = dataArray{:, 6};
var7 = dataArray{:, 7};
var8 = dataArray{:, 8};
y = dataArray{:, 9};
data =[var1, var2, var3, var4, var5, var6, var7, var8 ];


clearvars filename formatSpec fileID dataArray ans var1 var2 var3 var4 var5 var6 var7 var8;


end