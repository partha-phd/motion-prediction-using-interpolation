%% Generation of Predicted Occupancy Grids (Reference)
function POG = generatePOG_Reference(x_Road, y_Road, x_Target, ...
    y_Target)
% Construction of grids 1m x 1m
X=0:200;
Y=0:0.5:14.5;
k=1;
gridNew=zeros(2,2,6000);
for i=1:size(Y,2)-1
    for j=1:size(X,2)-1
        grid=[X(j) X(j+1); Y(i) Y(i+1)];
        gridNew(:,:,k)=grid;
        k=k+1;
    end
end

% Initialisation
occupancyGrid = zeros(1, 6000);

% Vectorize the road points
x_Road = x_Road(:);
y_Road = y_Road(:);

% Probability to road points
% START loop over the grids
for m=1:6000
    xv = [gridNew(1,1,m) gridNew(1,2,m) gridNew(1,2,m) gridNew(1,1,m)...
        gridNew(1,1,m)];
    yv = [gridNew(2,1,m) gridNew(2,1,m) gridNew(2,2,m) gridNew(2,2,m)...
        gridNew(2,1,m)];
    in=inpolygon(x_Road,y_Road,xv,yv);
    if any(in)>=1
        occupancyGrid((m))=1;
    end
end
% END loop over the grids

% Probability to target
% START loop over the target
for i = 1:size(x_Target,2)
    % START loop over the grids
    for m = 1:6000
        xv = [gridNew(1,1,m) gridNew(1,2,m) gridNew(1,2,m)...
            gridNew(1,1,m) gridNew(1,1,m)];
        yv = [gridNew(2,1,m) gridNew(2,1,m) gridNew(2,2,m)...
            gridNew(2,2,m) gridNew(2,1,m)];
        xVehicle = [x_Target(1,i) x_Target(2,i) x_Target(3,i)...
            x_Target(4,i) x_Target(1,i)];
        yVehicle = [y_Target(1,i) y_Target(2,i) y_Target(3,i)...
            y_Target(4,i) y_Target(1,i)];
        
        in=inpolygon(xVehicle,yVehicle,xv,yv);
        in1=inpolygon(xv,yv, xVehicle, yVehicle);
        if any(in)==1 || any(in1)==1
            occupancyGrid(m)=1;
        end
    end
    % END loop over the grids
end
% END loop over the targets
POG = rot90(reshape(occupancyGrid, [200 30]));
end
