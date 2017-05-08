mat = [mpg,cylinders,displacement, horsepower, weight, acceleration, modelyear, orginin];
mat1 = [cylinders,displacement, horsepower, weight, acceleration, modelyear, orginin];
names = [string('Cyliner');string('Displacement');string('Horsepower');string('Weight');string('Acceleration');string('Modelyear');string('Orginin')];
for i = 1:7
    for j = 1:7
        if(i==j)
            subplot(7,7,7*(i-1)+j);
            histogram(mat1(:,i));
            xlabel(names(i));
            ylabel(names(j));
        else
            subplot(7,7,7*(i-1)+j);
            for x = 1:length(mpg)
                if(mpg(x)<=low_to_medium)
                    plot(mat1(x,i),mat1(x,j),'+','color','r');
                    hold on;
                elseif(mpg(x)<=medium_to_high)
                    plot(mat1(x,i),mat1(x,j),'+','color','y');
                    hold on;
                else
                    plot(mat1(x,i),mat1(x,j),'+','color','g');
                    hold on;
                end;
            end;
            xlabel(names(i));
            ylabel(names(j));
        end;
    end;
end;
clearvars i j x;
