% Generation of Augmented Occupancy Grids
function augmentedOccupancyGrid = generateAOG(x_Road, y_Road,...
    vehicleDatabase)

% Construction of grids 1m x 0.5m
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
occupancyGrid = zeros(1, 36000);
% 1 - occupancy, 2 - v, 3 - Phi, 4 - longAccln, 5 - latAccln, 6 - vehicleID
occ=1:6:36000;
vel=2:6:36000;
psi=3:6:36000;
ax=4:6:36000;
ay=5:6:36000;
id=6:6:36000;

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
    if any(in)
        occupancyGrid(occ(m))=1;
        occupancyGrid(vel(m))=0;
        occupancyGrid(psi(m))=0;
        occupancyGrid(ax(m))=0;
        occupancyGrid(ay(m))=0;
        occupancyGrid(id(m))=0;
    end
end
% END loop over the grids

% Probability to target
% START loop over the target
for i = 1:size(vehicleDatabase,1)
   
    % START loop over the grids
   for m = 1:6000
        xv = [gridNew(1,1,m) gridNew(1,2,m) gridNew(1,2,m)...
            gridNew(1,1,m) gridNew(1,1,m)];
        yv = [gridNew(2,1,m) gridNew(2,1,m) gridNew(2,2,m)...
            gridNew(2,2,m) gridNew(2,1,m)];
        xVehicle = vehicleDatabase(i,4,1).xCoordinates(2,:);
        yVehicle = vehicleDatabase(i,4,1).yCoordinates(2,:);

        in=inpolygon(xVehicle, yVehicle, xv, yv);
        in1=inpolygon(xv, yv, xVehicle, yVehicle);
        if any(in) || any(in1)
            occupancyGrid(occ(m))=1;
            occupancyGrid(vel(m))=vehicleDatabase(i,4,1).speed(2);
            occupancyGrid(psi(m))=vehicleDatabase(i,4,1).angleDir(2);
            occupancyGrid(ax(m))=...
                vehicleDatabase(i,4,1).longitudinalAccn(2);
            occupancyGrid(ay(m))=vehicleDatabase(i,4,1).lateralAccn(2);
            occupancyGrid(id(m))=vehicleDatabase(i,4,1).vehicleID;
        end
    end
    % END loop over the grids
end
% END loop over the targets
augmentedOccupancyGrid(:,:,1) = rot90(reshape(occupancyGrid(1:6:36000),...
    [200 30]));
augmentedOccupancyGrid(:,:,2) = rot90(reshape(occupancyGrid(2:6:36000),...
    [200 30]));
augmentedOccupancyGrid(:,:,3) = rot90(reshape(occupancyGrid(3:6:36000),...
    [200 30]));
augmentedOccupancyGrid(:,:,4) = rot90(reshape(occupancyGrid(4:6:36000),...
    [200 30]));
augmentedOccupancyGrid(:,:,5) = rot90(reshape(occupancyGrid(5:6:36000),...
    [200 30]));
augmentedOccupancyGrid(:,:,6) = rot90(reshape(occupancyGrid(6:6:36000),...
    [200 30]));
end
