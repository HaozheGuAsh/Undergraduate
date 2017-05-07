[data,mdata] = Q1data();
lambda = [ 1e-4,1e-3, 1e-2,1e-1,1,5,1e2,1e3,1e4,1e5];
err = ones(size(lambda,2));
%194 rows, divided into 10 fold, eachtime, take one fold(19) as testcase,
%others as traincase
[row,column] = size(mdata);


generror = ones(1,size(lambda,2));
w = cell(1,size(lambda,2));
count = zeros(10,10);
for lam = 1:size(lambda,2)
    w{lam} = ones(column,10);
    error = ones(1,10);
    perm = randperm(row);
    for k = 1:10
        testind = perm((k-1)*19+1:k*19);
        trainind = setdiff(perm,testind);
        testdata = mdata(testind,:);
        traindata = mdata(trainind,:);
        ytrain = traindata(:,1);
        ytest = testdata(:,1);
        xtest = [ones(size(testdata,1),1),testdata(:,2:column)];
        xtrain = [ones(size(traindata,1),1),traindata(:,2:column)];
        w{lam}(:,k) = ridge_regression(ytrain,xtrain,lambda(lam));
        error(:,k) =  sum((ytest-xtest*w{lam}(:,k)).^2);%+lambda(lam)*sum(w{lam}(:,k).^2);
        for in =1:4497
            if(abs(w{lam}(in,k))<1e-3)
                count(k,lam) = count(k,lam)+1;
            end;
        end;
        fprintf('lambda %d fold%d count:%d err:%d\n',lambda(lam),k,count(k,lam),error(:,k));
    end;
    generror(lam) = mean(error);
end;

%Plots
figure(1);
plot(log10(lambda(1:10)),log(generror(1:10)),'-x');
xlabel('Log of Lambda Value');
ylabel('Log of Generalized Residual Sum Error');
title('Lambda vs Log(RSS) for 10-fold Ridge Regression');
figure(2);
plot(log10(lambda(1:10)),mean(count(:,1:10)),'-x');
xlabel('Log of Lambda Value');
ylabel('Features Weights Close to 0 (1e-3)');
title('Lambda vs Features Weights Removed for 10-fold Ridge Regression');
figure(3)
coef = ones(15,10);
for i = 1:10
    coef(:,i) = mean(w{i}(1:15,:).').';
end;
for j = 1:15
    plot(log10(lambda(1:10)),coef(j,1:10),'-x');
    hold on;
end;
hold off;
xlabel('Log of Lambda Value');
ylabel('Weights of First Fifteen Features');
title('Lambda vs First Fifteen Weights for 10-fold Ridge Regression');

% Optimal Lambda
oplam = lambda(5);



%clearvars ans  count  err error  i k lam lambda  perm  testdata testind traindata trainind  xtest xtrain ytest ytrain;

