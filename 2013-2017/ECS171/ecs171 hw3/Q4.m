Y = data{:,2:5};
clearvars predict;
%4 separate SVM
perm = randperm(row);
for svm = 1:4
    for k = 1:10
        testind = perm((k-1)*19+1:k*19);
        trainind = setdiff(perm,testind);
        testdata = mdata(testind,:);
        traindata = mdata(trainind,:);
        for i = 1:size(testind,2)
            ytest{i} = Y{testind(i),svm};
        end;
        for i = 1:size(trainind,2)
            ytrain{i} = Y{trainind(i),svm};
        end;
        xtest = testdata(:,2:column);
        xtrain = traindata(:,2:column);
        % Set up train test above
    
        % Set class
        class = unique(ytrain);
        models = cell(numel(class),1);
        % Fit svm
        for i  = 1:numel(class)
            index = strcmp(ytrain,class{i,1});
            models{i} = fitcsvm(xtrain,index);
        end;
        % Store Statistic
        if(k==1)
            score = zeros(19,numel(class));
        end;
        
        for i = 1:numel(class)
            for j=1:19
                [~,s]= predict(models{i},xtest(j,:));
                score(j,i)=s(2);
            end
        end
        
        index2=zeros(19,numel(class));
        for w=1:19
            [value(w),in(w)]=max(score(w,:));
            index2(w,:)=strcmp(class,ytest(w));
        end
        if(k==10)
        subplot(2,2,svm);
        threhold=linspace(-2,6,1000);
        for t=1:numel(threhold)
            tpr=0;
            fpr=0;
            for w=1:19
              if(value(w)>=threhold(t))
                  valuetmp(w)=1;
              else
                  valuetmp(w)=0;
              end
              [~,a]=max(index2(w,:));
              if(valuetmp(w)==1&&in(w)==a)
                  tpr = tpr+1;
              elseif(valuetmp(w)==1&&index2(w,in(w))==0)
                  fpr = fpr+1;    
              end
            end
            plot(tpr/19,fpr/19,'-x');
            hold on;
            if(t ==1)
                all_rate = [tpr/19,fpr/19];
            else
                all_rate = [all_rate;tpr/19,fpr/19];
            end;
        end
        plot(all_rate(1:numel(threhold),1),all_rate(1:numel(threhold),2),'-x');
        end;
    end;
end;
 