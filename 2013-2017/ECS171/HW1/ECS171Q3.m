
function w = ECS171Q3(x,y,mode,learning_rate,difference)
if (nargin==2)
    mode = -1;
end;
if(mode ==-1)
    y = y(1:size(x,1));
    w = inv(x.' * x) * x.' * y;
elseif (mode ==1)
    [trainningsize,features] = size(x);
    w = ones(features,1);
    for iter = 1:50000
    tmp = w;
    val =  zeros(features,1);
    for i  = 1: trainningsize
        val = val + (y(i) - sigm(x(i,:) * w)) * x(i,:).';
    end;
    w= w + learning_rate*val;
    a = norm(w-tmp);
    if(a<=difference&&iter>200)
        break;
    end;
    end;
elseif(mode==2)
    [trainningsize,features] = size(x);
    mina = 100;
    w = ones(features,1);
    for iter = 1:500000
        tmp = w;
        val =  zeros(features,1);
        for i  = 1: trainningsize
          
            val = val + (y(i) - sigm(x(i,:) * w)) * x(i,:).';
        
        end;
        w= w + learning_rate*val;
        a = norm(w-tmp);
        if(a<=difference&&iter>200)
            break;
        end;
    end;
end;
    
end
function out = sigm(in)
out = 1 / (1+exp(-in));
end