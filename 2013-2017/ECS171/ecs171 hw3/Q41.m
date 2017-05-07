data=importdata('ecs171.dataset.xlsx');
A=struct2cell(data);
B=A{2,1};
C=A{1,1};
Text=B.data;
X=C.data;
X=X(:,2:4496);
Y=Text(2:195,2:5);
ordering = randperm(194);
X=X(ordering, :);
Y=Y(ordering,:);
%%svm
for i=1:4
    for j=1:10
        if(j~=10)
            trainset=[X(1:19*j,:);X(19*(j+1)+1:194,:)];
            testset=X(19*j+1:19*(j+1),:);
            Ytrain=[Y(1:19*j,i);Y(19*(j+1)+1:194,i)];
            Ytest=Y(19*j+1:19*(j+1),i);
        else
            trainset=X(20:194,:);
            testset=X(1:19,:);
            Ytrain=Y(20:194,i);
            Ytest=Y(20:194,i);
        end
        
        classes = unique(Ytrain);
        SVMModels = cell(numel(classes),1);
        for k = 1:numel(classes);
            indx = strcmp(Ytrain,classes{k,1}); 
            SVMModels{k} = fitcsvm(trainset,indx);
        end
        if(j==1)
            scores=zeros(19,numel(classes));
        end
        for k = 1:numel(classes);
            for n=1:19
                [~,s]= predict(SVMModels{k},testset(n,:));
                scores(n,k)=s(2)+scores(n,k);
            end
        end
    end
    scores=scores/10;
    index=zeros(19,numel(classes));
    for w=1:19
        [P(w),L(w)]=max(scores(w,:));
        index(w,:)=strcmp(classes,Ytest(w));
    end
    subplot(1,4,i);
    threhold=-3:0.01:6;
    for T=1:numel(threhold)
        TP=0;
        FP=0;
        for w=1:19
          if(P(w)>=threhold(T))
              P_1(w)=1;
          else
              P_1(w)=0;
          end
          [~,a]=max(index(w,:));
          if(P_1(w)==1&&L(w)==a)
              TP=TP+1;
          elseif(P_1(w)==1&&index(w,L(w))==0)
              FP=FP+1;    
          end
        end
        plot(TP/19,FP/19,'-x');hold on;
    end
    
end

