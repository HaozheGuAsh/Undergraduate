filename = 'auto-mpg.data';
delimiter = {'\t',' '};
startRow = [1,34,128,332,338,356,376];
endRow = [32,126,330,336,354,374,398];
formatSpec = '%q%q%q%q%q%q%q%q%[^\n\r]';
fileID = fopen(filename,'r');
dataArray = textscan(fileID, formatSpec, endRow(1)-startRow(1)+1, 'Delimiter', delimiter, 'MultipleDelimsAsOne', true, 'HeaderLines', startRow(1)-1, 'ReturnOnError', false, 'EndOfLine', '\r\n');
for block=2:length(startRow)
    frewind(fileID);
    dataArrayBlock = textscan(fileID, formatSpec, endRow(block)-startRow(block)+1, 'Delimiter', delimiter, 'MultipleDelimsAsOne', true, 'HeaderLines', startRow(block)-1, 'ReturnOnError', false, 'EndOfLine', '\r\n');
    for col=1:length(dataArray)
        dataArray{col} = [dataArray{col};dataArrayBlock{col}];
    end
end

fclose(fileID);
raw = repmat({''},length(dataArray{1}),length(dataArray)-1);
for col=1:length(dataArray)-1
    raw(1:length(dataArray{col}),col) = dataArray{col};
end
numericData = NaN(size(dataArray{1},1),size(dataArray,2));

for col=[1,2,3,4,5,6,7,8]

    rawData = dataArray{col};
    for row=1:size(rawData, 1)

        regexstr = '(?<prefix>.*?)(?<numbers>([-]*(\d+[\,]*)+[\.]{0,1}\d*[eEdD]{0,1}[-+]*\d*[i]{0,1})|([-]*(\d+[\,]*)*[\.]{1,1}\d+[eEdD]{0,1}[-+]*\d*[i]{0,1}))(?<suffix>.*)';
        try
            result = regexp(rawData{row}, regexstr, 'names');
            numbers = result.numbers;
            

            invalidThousandsSeparator = false;
            if any(numbers==',')
                thousandsRegExp = '^\d+?(\,\d{3})*\.{0,1}\d*$';
                if isempty(regexp(numbers, thousandsRegExp, 'once'))
                    numbers = NaN;
                    invalidThousandsSeparator = true;
                end
            end
 
            if ~invalidThousandsSeparator
                numbers = textscan(strrep(numbers, ',', ''), '%f');
                numericData(row, col) = numbers{1};
                raw{row, col} = numbers{1};
            end
        catch me
        end
    end
end

mpg = cell2mat(raw(:, 1));
cylinders = cell2mat(raw(:, 2));
displacement = cell2mat(raw(:, 3));
horsepower = cell2mat(raw(:, 4));
weight = cell2mat(raw(:, 5));
acceleration = cell2mat(raw(:, 6));
modelyear = cell2mat(raw(:, 7));
orginin = cell2mat(raw(:, 8));

clearvars filename delimiter startRow endRow formatSpec fileID block dataArrayBlock col dataArray ans raw numericData rawData row regexstr result numbers invalidThousandsSeparator thousandsRegExp me;

a = round(392/3);
sortmpg = sort(mpg);
low_to_medium = sortmpg(a,1);
medium_to_high = sortmpg(a*2,1);

clearvars a sortmpg;


