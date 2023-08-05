% Generation of Predicted Occupancy Grids
function [pogProb, pogID] = generatePOG(x_Road, y_Road,...
    vehicleDatabase, n)

% Construction of grids 0.5m x 0.5m
X=0:0.5:200;
Y=0:0.5:14.5;
k=1;
numCellsX = size(X,2)-1;
numCellsY = size(Y,2);
numCells = numCellsY * numCellsX;
gridNew=zeros(2,2,numCells);
for i=1:size(Y,2)-1
    for j=1:size(X,2)-1
        grid=[X(j) X(j+1); Y(i) Y(i+1)];
        gridNew(:,:,k)=grid;
        k=k+1;
    end
end

% Initialisation
[numTargets, numLatHypotheses, numLongHypotheses] = size(vehicleDatabase);
pogProb = zeros(30, 400);
pogID = zeros(30, 400);

% Vectorize the road points
x_Road = x_Road(:);
y_Road = y_Road(:);

% Initialisation
occupancyGridProb = zeros(numCells, 1);
occupancyGridID = zeros(numCells, 1);

% Probability to target
% START loop over the grids
for m = 1:numCells
    xvGrid = [gridNew(1,1,m) gridNew(1,2,m) gridNew(1,2,m)...
        gridNew(1,1,m) gridNew(1,1,m)];
    yvGrid = [gridNew(2,1,m) gridNew(2,1,m) gridNew(2,2,m)...
        gridNew(2,2,m) gridNew(2,1,m)];
    in=inpolygon(x_Road,y_Road,xvGrid,yvGrid);
    if any(in)
        occupancyGridProb(m) = 1;
        continue;
    end
    sumProb = zeros(numTargets, 1);
    occProb = zeros(numTargets, numLatHypotheses, numLongHypotheses);
    % START loop over the target
    for i = 1:numTargets
        % START loop over the multiple hypotheses (lateral)
        for j = 1:numLatHypotheses
            % START loop over the multiple hypotheses(longitudinal)
            for k = 1:numLongHypotheses
                if ~isempty(vehicleDatabase(i,j,k).xCoordinates)
                    xVehicle = [vehicleDatabase(i,j,k).xCoordinates(n,1)...
                        vehicleDatabase(i,j,k).xCoordinates(n,2)...
                        vehicleDatabase(i,j,k).xCoordinates(n,3)...
                        vehicleDatabase(i,j,k).xCoordinates(n,4)...
                        vehicleDatabase(i,j,k).xCoordinates(n,1)];
                    yVehicle = [vehicleDatabase(i,j,k).yCoordinates(n,1)...
                        vehicleDatabase(i,j,k).yCoordinates(n,2)...
                        vehicleDatabase(i,j,k).yCoordinates(n,3)...
                        vehicleDatabase(i,j,k).yCoordinates(n,4)...
                        vehicleDatabase(i,j,k).yCoordinates(n,1)];
                    in=inpolygon(xVehicle,yVehicle,xvGrid,yvGrid);
                    in1=inpolygon(xvGrid,yvGrid, xVehicle, yVehicle);
                    if any(in) || any(in1)
                        occProb(i,j,k) = vehicleDatabase(i,j,k).minProb;
                    else
                        occProb(i,j,k) = 0;
                    end
                end
            end
            % END loop over the multiple hypotheses (longitudinal)
        end
        % END loop over the multiple hypotheses (lateral)
        targetProb = occProb(i,:,:);
        sumProb(i) = sum(targetProb(:));
    end
    % END loop over the targets
    id = find(sumProb > 0.001);
    if ~isempty(id)
        occupancyGridProb(m) = sum(sumProb(id));
        if size(id,1) == 1
            occupancyGridID(m) = id;
        else
            occupancyGridID(m) = id(1);
        end
    end
    % END loop over the cells

    % Calculating the predicted occupancy grid
    pogProb = rot90(reshape(occupancyGridProb, [numCellsX numCellsY]));
    pogProb(pogProb>1) = 1;
    pogID = rot90(reshape(occupancyGridID, [numCellsX numCellsY]));
end
