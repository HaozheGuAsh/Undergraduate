pred = [1,mean(mdata(:,2:size(mdata,2)))];
[predict,cilow,ciup] = Q2predict(pred,all_w,w_model);