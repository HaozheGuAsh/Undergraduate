%%female folder
%%path = pwd();
path = 'C:\Users\Ash\Google Drive\Undergraduate\Junior & Senior\Winter 2017\ECS 170\p3';
%%list = importdata(strcat(pwd,'\Test\'));
for i = 1:40
    M = importdata(strcat(path,'\Test\',num2str(i),'.txt'));
    N = reshape(M', [128,120]);
    R = N';
    imagesc(R);
    colormap('gray');
end;

%%R(1:100,1:128) = 255*ones(100,128);

%%0 -> black;255 -> white
%%Note: lots of noise




