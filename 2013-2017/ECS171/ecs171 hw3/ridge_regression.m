function w = ridge_regression(y,x,lambda)
i = eye(size(x,2));
w = inv(x.' * x+ lambda *i ) * x.' * y;
end