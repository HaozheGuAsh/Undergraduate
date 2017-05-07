%Bootstrapping 200 times
all_w = ones(200,column);
for iter = 1:200
    sample = datasample(mdata,size(mdata,1));
    y = sample(:,1);
    train = [ones(size(mdata,1),1),mdata(:,2:column)];
    all_w(iter,:) = ridge_regression(y,train,oplam);
end;



% Prediction w
perm = randperm(row);
sample = mdata(perm,:);
y = sample(:,1);
train = [ones(size(mdata,1),1),mdata(:,2:column)];
w_model = ridge_regression(y,train,oplam);

