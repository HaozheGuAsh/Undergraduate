clearvars all;
layer_config = cell(3,4);
for L = 1:3
    for J = 1:4
        num_nodes = J*3;
        tmp = [];
        for(i = L:-1:1)
            tmp = [tmp,num_nodes];
            layer_config{L,J} = tmp;
        end;
        layer_config{L,J} = tmp;
    end;
end;

all_test_percent= zeros(3,4);
all_test_error= zeros(3,4);
all_train_error= zeros(3,4);


for L = 1:3
    for J = 1:4
        [train_percent,train_error,test_percent,test_error] = ANN(layer_config{L,J},50);
        all_test_percent(L,J) = test_percent;
        all_test_error(L,J) = test_error;
        all_train_error(L,J) = train_percent;
    end;
end;
        
