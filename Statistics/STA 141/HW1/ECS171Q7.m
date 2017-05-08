trainningsize = 392;
features = 1+2*7;
trainningy = mpg;
trainningx = [ones(trainningsize,1),mat1(:,:),mat1(:,:).^2];


wpoly= ECS171Q3(trainningx,mpg);

testcase = [1,6,300,170,3600,9,80,1,36,300^2,170^2,3600^2,81,80^2,1];
Q7polypredict = testcase*wpoly;


for i = 1:trainningsize
    if (trainningy(i) <= low_to_medium)
        trainningy(i) = 0;
    else
        trainningy(i) = 1;
    end;
end;   
learning_rate = 0.001;
difference = 1e-3;
for i = 2:size(trainningx,2)
    trainningx(:,i) = (trainningx(:,i)- mean(trainningx(:,i)))/std(trainningx(:,i));
end;
wlogic1 = ECS171Q3(trainningx,trainningy,1,learning_rate,difference);


part1 = zeros(trainningsize,6);
for i = 1:trainningsize
    sig = sigm(trainningx(i,:) * wlogic1);
    if((sig)<=0.5)
        part1(i,:) = [mpg(i),sig,0,0,0,mpg(i)<=low_to_medium];
    else
        part1(i,:) = [mpg(i),sig,1.5,0,0,mpg(i)>low_to_medium];
    end;
end;

trainningy = mpg;
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
    newtrainningx = [newtrainningx;1,mat1(newtrainningy(i,2),:),mat1(newtrainningy(i,2),:).^2];
end;

for i = 2:features
    newtrainningx(:,i) = (newtrainningx(:,i)- mean(newtrainningx(:,i)))/std(newtrainningx(:,i));
end;

wlogic2 = ECS171Q3(newtrainningx,newtrainningy(:,1),2,learning_rate,difference);
Q7sig1 = sigm(testcase(1,:) * wlogic1);
Q7sig2 = sigm(testcase(1,:) * wlogic2);
q7part1 = part1;
clearvars trainningsize features trainningy trainningx wpoly testcase i learning_rate difference wlogic1 wlogic2 newtrainningx newtrainningy part1 sig;

function out = sigm(in)
out = 1 / (1+exp(-in));
end