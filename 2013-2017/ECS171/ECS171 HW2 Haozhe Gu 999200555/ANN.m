%ANN function version for homework, only one input of hidden layer [3] is
%one layer with 3 nodes [4,4] means 2 layer of 4 nodes

function [train_error,train_sum_error, test_error,test_sum_error,best_weight] =ANN(num_node_hidden,max_iteration) 
 
%setup parameters
[data, y] = Read_data();
tmpy = y;
num_rows = size(data,1);
num_train = round(num_rows*0.7);
num_test = num_rows-num_train;
num_in = size(data,2);
category = sort(unique(y));
num_out = size(category,1);
num_layer = 1+length(num_node_hidden)+1;
num_nodes_perlayer = [num_in+1 num_node_hidden+ones(1,length(num_node_hidden)) num_out];    %add one to input for x0
learning_rate = 0.4;



%shuffle the data
order = randperm(num_rows);
in_mat = [];
out_mat = [];
for i = 1:num_rows
    in_mat = [in_mat;data(order(i),:)];
    out_mat = [out_mat;zeros(1,num_out)];
    for j = 1:num_out
       if(strcmp(category(j),y(order(i))))
           out_mat(i,j) = 1;
       end;
    end;
end;
in_mat= [ones(num_rows,1),in_mat];      %add ones w0 for x0

%set up train and test
train_in_mat = in_mat(1:num_train,:);
test_in_mat = in_mat(num_train+1:num_rows,:);
train_out_mat = out_mat(1:num_train,:);
test_out_mat = out_mat(num_train+1:num_rows,:);

%initialize
weight = cell(1,num_layer-1);       %out layer dont have weight
for i = 1:num_layer-1
    weight{i} = rand(num_nodes_perlayer(i), num_nodes_perlayer(i+1))*2-1;
end;

activation = cell(1,num_layer);     %in layer dont have activation
for i = 1:num_layer
    activation {i} = zeros(1,num_nodes_perlayer(i));
end;

back_error = activation;

%calculate
%iteration

%each row, do forward and backward propagation
best_weight = weight;
best_weight_record = [];
best_error_record = [];
best_output_record = [];
tmp = 1e10;
for iter = 1:max_iteration
    weight_record = [];
    error_record = [];
    output_record = [];
    for m = 1:num_train
        weight_record = [weight_record;weight];
        activation{1} = train_in_mat(m,:);
        for L = 2:num_layer
            activation{L} = sigmoid(activation{L-1}*weight{L-1});
            if(L~=num_layer)
                activation{L}(1) = 1;
            end;
        end;
        back_error{num_layer} = activation{num_layer}-train_out_mat(m,:); %error formulae for out layer
        output_record = [output_record;activation{num_layer}];
        error_record = [error_record;norm(back_error{num_layer})];
        %iterate back for each layer
        for L = num_layer-1 : -1 : 1
            back_error{L} = ((weight{L}) * (back_error{L+1}).').' .* activation{L} .*(1-activation{L});
            %doing gradient descent update for  each value in one layer
            for i = 1: size(weight{L},1)
                for j = 1:size(weight{L},2)
                    weight{L}(i,j) = weight{L}(i,j) - learning_rate * ( activation{L}(:,i) *back_error{L+1}(:,j));
                end;
            end;
        end;
    end;
    if(tmp>sum(error_record))
        tmp = sum(error_record);
        best_weight = weight;
        best_weight_record = weight_record;
        best_error_record = error_record;
        best_output_record = output_record;
    end;
end;
error_record = best_error_record;
weight_record = best_weight_record;
output_record = best_output_record;

%statistics
table_train = [];
for m = 1:num_train
    activation = cell(1,num_layer); 
    activation{1} = train_in_mat(m,:);
    for L = 2:num_layer
        activation{L} = sigmoid(activation{L-1}*best_weight{L-1});
        if(L~=num_layer)
            activation{L}(1) = 1;
        end;
    end;
    [val,index] = max(activation{num_layer});
    table_train = [table_train;y(order(m)),category(index),strcmp(y(order(m)),category(index))];
    
end;
%fprintf('Trainning percentage error: ');
train_error = sum(cell2mat(table_train(:,end)))/num_train;
train_sum_error = sum(error_record);

table_test = [];
y = tmpy;
error_record = [];
output_record = [];
for m = 1:num_test
    activation = cell(1,num_layer); 
    activation{1} = test_in_mat(m,:);
    for L = 2:num_layer
        activation{L} = sigmoid(activation{L-1}*best_weight{L-1});
        if(L~=num_layer)
            activation{L}(1) = 1;
        end;
    end;
    output_record = [output_record;activation{num_layer}];
    error_record = [error_record;norm(activation{num_layer}-test_out_mat(m,:))];
    [val,index] = max(activation{num_layer});
    table_test = [table_test;y(order(m+num_train)),category(index),strcmp(y(order(m+num_train)),category(index))];
end;

%fprintf('Testing percentage error: ');
test_error = sum(cell2mat(table_test(:,end)))/num_test;

test_sum_error = sum(error_record);


end















