% two steps: first categorize between low and (median or high) using lower
% to medium cutoff, then categorize between median or high using median to
% high cutoff
%ysize = max(mpg)-min(mpg);
%adjustlowercutoff = (low_to_medium-min(mpg))/ysize;
%adjustuppercutoff = (medium_to_high-min(mpg))/ysize;
maxiteration = 100000;
trainningsize = 302;
testingsize = 90;
features = 7;
trainningy = mpg(1:302);
for i = 1:trainningsize
    if (trainningy(i) <= low_to_medium)
        trainningy(i) = 0;
    else
        trainningy(i) = 1;
    end;
end;   
trainningx = [ones(302,1),mat1(1:302,:)];
testingy = (mpg(303:392));
testingx = [ones(90,1),mat1(303:392,:)];

learning_rate = 0.001;
difference = 1e-3;

for i = 2:8
    trainningx(:,i) = (trainningx(:,i)- mean(trainningx(:,i)))/std(trainningx(:,i));
end;

for i = 2:8
    testingx(:,i) = (testingx(:,i)- mean(testingx(:,i)))/std(testingx(:,i));
end;
w = ECS171Q3(trainningx,trainningy,1,learning_rate,difference);


part1 = zeros(trainningsize,6);
for i = 1:trainningsize
    sig = sigm(trainningx(i,:) * w);
    if((sig)<=0.5)
        part1(i,:) = [mpg(i),sig,0,0,0,mpg(i)<=low_to_medium];
    else
        part1(i,:) = [mpg(i),sig,1.5,0,0,mpg(i)>low_to_medium];
    end;
end;


trainningy = mpg(1:302);
newtrainningy= [];
for i=1:trainningsize
    if(part1(i,3)==1.5)
        if(trainningy(i) <=medium_to_high)
            newtrainningy = [newtrainningy;0,i];
        elseif(trainningy(i) > medium_to_high)
            newtrainningy = [newtrainningy;1,i];
        end;
    end;
end;
newtrainningx = [];
for i = 1: size(newtrainningy,1)
    newtrainningx = [newtrainningx;1,mat1(newtrainningy(i,2),:)];
end;

for i = 2:8
    newtrainningx(:,i) = (newtrainningx(:,i)- mean(newtrainningx(:,i)))/std(newtrainningx(:,i));
end;
learning_rate = 0.002;
difference = 1e-6;
w1 = ECS171Q3(newtrainningx,newtrainningy(:,1),2,learning_rate,difference);

for i = 1:trainningsize
    if(part1(i,3)==1.5)
        sig = sigm(trainningx(i,:) * w1);
        if((sig)<=0.5)
            part1(i,:) = [mpg(i),part1(i,2),1.5,sig,1,mpg(i)<=medium_to_high];
        else
            part1(i,:) = [mpg(i),part1(i,2),1.5,sig,2,mpg(i)>medium_to_high];
        end;
    end;
end;
adjust = exp(mean(mpg(303:392))/mean(mpg(1:303)));
parttest = zeros(testingsize,6);
for i = 1:testingsize
    sig = sigm(testingx(i,:) * w);
    sig2 = sigm(testingx(i,:) * w1);
    if(sig<=(0.5/(2*adjust)))
        parttest(i,:) = [mpg(302+i),sig,0,sig2,0,testingy(i)<=low_to_medium];
    elseif(sig2<=(0.5/(2*adjust)))
        parttest(i,:) = [mpg(302+i),sig,1.5,sig2,1,testingy(i)>low_to_medium&& testingy(i)<=medium_to_high];
    else
        parttest(i,:) = [mpg(302+i),sig,1.5,sig2,2,testingy(i)>medium_to_high];
    end;
end;
q6part1 = part1;
q7parttest = parttest;
q6trainning_error_percentage=1-(sum(part1(:,6))/302);
q6testing_error_percentage = 1-(sum(parttest(:,6))/90);

clearvars features i iter learning_rate maxiteration sig sig2 testingsize val w trainningx trainningy w1 adjust testingx testingy trainningsize part1 parttest newtrainningx newtrainningy;
function out = sigm(in)
out = 1 / (1+exp(-in));
end



