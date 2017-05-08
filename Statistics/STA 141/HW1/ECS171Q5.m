trainning  = mat1(1:302,:);
testing  = mat1 (303:392,:);


zeroorder = ones(302,1);
w0 = ECS171Q3(zeroorder,mpg);
trainningmse = sum((mpg(1:302)-zeroorder*w0).^2)/302;
tm0 = ones(90,1);
testingmse = sum((mpg(303:392)- tm0*w0).^2)/90;

firstorder = [zeroorder, trainning.^1];
w1= ECS171Q3(firstorder,mpg);
trainningmse = [trainningmse;sum((mpg(1:302)-firstorder*w1).^2)/302];
tm1 = [tm0,testing];
testingmse = [testingmse;sum((mpg(303:392)- tm1*w1).^2)/90];

secondorder = [firstorder,trainning.^2];
w2 = ECS171Q3(secondorder,mpg);
trainningmse = [trainningmse;sum((mpg(1:302)-secondorder*w2).^2)/302];
tm2 = [tm1,testing.^2];
testingmse = [testingmse;sum((mpg(303:392)- tm2*w2).^2)/90];

q5trainningmse = trainningmse;
q5testingmse = testingmse;

clearvars w0 w1 w2 zeroorder firstorder secondorder tm0 tm1 tm2 trainningmse testingmse testing trainning