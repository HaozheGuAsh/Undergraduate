function [predict,cilow,ciup] = Q2predict(x,all_w,w_model)
    all_y = ones(size(all_w,1),1);
    iter = size(all_w,1);
    for i = 1: size(all_y,1)
        all_y(i) = x*all_w(i,:).';
    end;
    %plot for check distribution
        histfit(all_y);
        str = sprintf('Bootstrapping %d distribution Plot',iter);
        title(str);
        xlabel('predicted Growth');
        
        
    %because the distribution of wibootstrap look approximate normal, we can
    %use quantile to derive the confidence interval
    %under 80% confidence interval, CI = (Q0.1,Q0.9)
    all_y = sort(all_y);
    cilow = all_y(floor(0.1*iter),:);
    ciup = all_y(floor(0.9*iter),:);
    predict = x*w_model;
    
end