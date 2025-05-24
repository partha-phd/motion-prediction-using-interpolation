% Function to estimate probabilities to the main hypotheses
function target = probEstimate(vehPosX, vehPosY, vehPsi, vehVel,...
    vehAx, vehAy, vehLanePos, vehType, EGO)
% Augmenting with the EGO vehicle information
vehPosX = [vehPosX EGO.PosX];
vehPosY = [vehPosY EGO.PosY];
vehPsi = [vehPsi EGO.Psi];
vehVel = [vehVel EGO.Vel];
vehAx = [vehAx EGO.Ax];
vehAy = [vehAy EGO.Ay];
vehLanePos = [vehLanePos 2];
vehType = [vehType EGO.Type];

% Number of target
noOfTarget = size(vehPosX,2)-1; %-1 to exclude the EGO
% possible hypotheses
for i = 1:noOfTarget
    target(i).FL = 0; % follow lane
    target(i).RLC = 0; % right lane change
    target(i).LLC = 0; % left lane change
    target(i).B = 0; % Brake percentage
end
% START loop over the target vehicles
for i = 1:noOfTarget
    target(i).Ax = vehAx(i);
    target(i).laneID = vehLanePos(i);
    gridX(1,:) = [vehPosX(i)+50 vehPosX(i)+20 vehPosX(i)+20 ...
        vehPosX(i)+50 vehPosX(i)+50];
    gridY(1,:) = [13.6 13.6 9.47 9.47 13.6];
    gridX(2,:) = [vehPosX(i)+20 vehPosX(i)-20 vehPosX(i)-20 ...
        vehPosX(i)+20 vehPosX(i)+20];
    gridY(2,:) = [13.6 13.6 9.47 9.47 13.6];
    gridX(3,:) = [vehPosX(i)-20 vehPosX(i)-50 vehPosX(i)-50 ...
        vehPosX(i)-20 vehPosX(i)-20];
    gridY(3,:) = [13.6 13.6 9.47 9.47 13.6];
    gridX(4,:) = [vehPosX(i)+50 vehPosX(i)+20 vehPosX(i)+20 ...
        vehPosX(i)+50 vehPosX(i)+50];
    gridY(4,:) = [9.47 9.47 5.8 5.8 9.47];
    gridX(5,:) = [vehPosX(i)+20 vehPosX(i)-20 vehPosX(i)-20 ...
        vehPosX(i)+20 vehPosX(i)+20];
    gridY(5,:) = [9.47 9.47 5.8 5.8 9.47];
    gridX(6,:) = [vehPosX(i)-20 vehPosX(i)-50 vehPosX(i)-50 ...
        vehPosX(i)-20 vehPosX(i)-20];
    gridY(6,:) = [9.47 9.47 5.8 5.8 9.47];
    gridX(7,:) = [vehPosX(i)+50 vehPosX(i)+20 vehPosX(i)+20 ...
        vehPosX(i)+50 vehPosX(i)+50];
    gridY(7,:) = [5.8 5.8 1.5 1.5 5.8];
    gridX(8,:) = [vehPosX(i)+20 vehPosX(i)-20 vehPosX(i)-20 ...
        vehPosX(i)+20 vehPosX(i)+20];
    gridY(8,:) = [5.8 5.8 1.5 1.5 5.8];
    gridX(9,:) = [vehPosX(i)-20 vehPosX(i)-50 vehPosX(i)-50 ...
        vehPosX(i)-20 vehPosX(i)-20];
    gridY(9,:) = [5.8 5.8 1.5 1.5 5.8];
    
    %% Finding the surrounding vehicles
    if vehLanePos(i) == 1 % Lower lane
        target(i).surroundVehVel(1:9)=0;
        % START loop over the target
        for j = 1:noOfTarget
            if i == j
                continue
            else
                % START loop over the grids
                for k = 4:9
                    in = inpolygon(vehPosX(j), vehPosY(j),...
                        gridX(k,:), gridY(k,:));
                    if in == 1
                        target(i).surroundVehVel(k)=vehVel(j);
                    end
                end
                % END loop over the grids
            end
        end
        % END loop over the target
    elseif vehLanePos(i) == 2% Middle lane
        target(i).surroundVehVel(1:9)=0;
        % START loop over the target
        for j = 1:noOfTarget
            if i == j
                continue
            else
                % START loop over the grids
                for k = 1:9
                    in = inpolygon(vehPosX(j), vehPosY(j),...
                        gridX(k,:), gridY(k,:));
                    if in == 1
                        target(i).surroundVehVel(k)=vehVel(j);
                    end
                end
                % END loop over the grids
            end
        end
        % END loop over the target
    elseif vehLanePos(i) == 3 % Upper lane
        target(i).surroundVehVel(1:9)=0;
        % START loop over the target
        for j = 1:noOfTarget
            if i == j
                continue
            else
                % START loop over the grids
                for k = 1:6
                    in = inpolygon(vehPosX(j), vehPosY(j),...
                        gridX(k,:), gridY(k,:));
                    if in == 1
                        target(i).surroundVehVel(k)=vehVel(j);
                    end
                end
                % END loop over the grids
            end
        end
        % END loop over the target
    end
    
    %% Probability assignment
    %%% LOWER LANE %%%
    if vehLanePos(i) == 1
        psi = vehPsi(i);
        if target(i).surroundVehVel(7)~=0 % Lead vehicle present
            relVel = vehVel(i)-target(i).surroundVehVel(7);
            if relVel < 0 % fast lead vehicle present
                target(i).FL = 1;
            elseif relVel > 0  % slow lead vehicle
                target(i).B = relVel/vehVel(i);
                if target(i).surroundVehVel(5)==0 &&...
                        target(i).surroundVehVel(4)==0 &&...
                        target(i).surroundVehVel(6) < ...
                        vehVel(i) % left lane free
                    if psi > 0.3 % current state of the vehicle
                        target(i).FL = 0.1;
                        target(i).LLC = 0.9;
                    elseif psi <=0.3
                        if vehType(i) == 1 % car
                            target(i).FL = 0.7;
                            target(i).LLC = 0.3;
                        else % truck
                            target(i).FL = 0.8;
                            target(i).LLC = 0.2;
                        end
                    end
                elseif target(i).surroundVehVel(5)~=0 % left lane not free
                    if psi > 0.3  % current state of the vehicle
                        target(i).FL = 0.7;
                        target(i).LLC = 0.3;
                    elseif psi <=0.3
                        target(i).FL = 0.9;
                        target(i).LLC = 0.1;
                    end
                else % left lane partially free
                    if psi > 0.3 % current state of the vehicle
                        target(i).FL = 0.2;
                        target(i).LLC = 0.8;
                    elseif psi <=0.3
                        target(i).FL = 0.7;
                        target(i).LLC = 0.3;
                    end
                end
            end
        else % Lead vehicle not present
            target(i).FL = 1;
        end
        
        %%% MIDDLE LANE %%%
    elseif vehLanePos(i) == 2
        psi = vehPsi(i);
        if target(i).surroundVehVel(4)~=0 % Lead vehicle present
            relVel = vehVel(i)-target(i).surroundVehVel(4);
            if relVel > 0 % slow lead vehicle
                target(i).B = relVel/vehVel(i);
                if target(i).surroundVehVel(1)==0 &&...
                        target(i).surroundVehVel(2)== 0 &&...
                        target(i).surroundVehVel(3) <...
                        0.8*vehVel(i) % left lane free
                    if psi > 0.3  % current state of vehicle
                        target(i).LLC = 0.9;
                        target(i).FL = 0.1;
                    else
                        if vehType(i)==1 % car
                            target(i).LLC = 0.3;
                            target(i).FL = 0.7;
                        else % Truck
                            target(i).LLC = 0.05;
                            target(i).FL = 0.95;
                        end
                    end
                elseif target(i).surroundVehVel(2)~=0 % left lane not free
                    if psi > 0.3 % current state of vehicle
                        target(i).LLC = 0.8;
                        target(i).FL = 0.2;
                    else
                        target(i).LLC = 0.1;
                        target(i).FL = 0.9;
                    end
                else % left lane partially free
                    if psi > 0.3 % current state of vehicle
                        target(i).LLC = 0.7;
                        target(i).FL = 0.3;
                    else
                        if vehType(i)==1 % car
                            target(i).LLC = 0.3;
                            target(i).FL = 0.7;
                        else % Truck
                            target(i).LLC = 0.2;
                            target(i).FL = 0.8;
                        end
                    end
                end
                
            else % fast lead vehicle
                if target(i).surroundVehVel(8)~=0 % right lane not free
                    if psi < -0.3 % current state of vehicle
                        target(i).RLC = 0.7;
                        target(i).FL = 0.3;
                    else
                        target(i).RLC = 0.1;
                        target(i).FL = 0.9;
                    end
                else % right lane free/ partially free
                    if psi < -0.3 % current state of vehicle
                        target(i).RLC = 0.7;
                        target(i).FL = 0.3;
                    else
                        target(i).RLC = 0.2;
                        target(i).FL = 0.8;
                    end
                end
            end
        elseif target(i).surroundVehVel(4)==0 % lead vehicle not present
            if target(i).surroundVehVel(8)==0 &&...
                    target(i).surroundVehVel(7)==0 &&...
                    target(i).surroundVehVel(9) < vehVel(i)%right lane free
                if vehType(i) == 2 % truck
                    if psi < -0.3 % current state of vehicle
                        target(i).RLC = 0.9;
                        target(i).FL = 0.1;
                    else
                        target(i).RLC = 0.3;
                        target(i).FL = 0.7;
                    end
                elseif vehType(i) == 1 % car
                    if psi < -0.3 % current state of vehicle
                        target(i).RLC = 0.9;
                        target(i).FL = 0.1;
                    else
                        target(i).RLC = 0.3;
                        target(i).FL = 0.7;
                    end
                end
            elseif target(i).surroundVehVel(8)~=0 % right lane not free
                if psi < -0.3 % current state of vehicle
                    target(i).RLC = 0.7;
                    target(i).FL = 0.3;
                else
                    target(i).RLC = 0.1;
                    target(i).FL = 0.9;
                end
            else % right lane partially free
                if psi < -0.3 % current state of vehicle
                    target(i).RLC = 0.7;
                    target(i).FL = 0.3;
                else
                    target(i).RLC = 0.2;
                    target(i).FL = 0.8;
                end
            end
        end
        %%% UPPER LANE %%%
    elseif vehLanePos(i) == 3 % Upper lane
        psi = vehPsi(i);
        ay = vehAy(i);
        if target(i).surroundVehVel(3)~=0 % following vehicle present
            if target(i).surroundVehVel(4)==0 &&...
                    target(i).surroundVehVel(5)==0 &&...
                    target(i).surroundVehVel(6) < vehVel(i)%right lane free
                if psi < -0.3 % current state of vehicle
                    target(i).RLC = 0.9;
                    target(i).FL = 0.1;
                else
                    target(i).RLC = 0.3;
                    target(i).FL = 0.7;
                end
            elseif target(i).surroundVehVel(5)~=0 ||...
                    target(i).surroundVehVel(4)~=0% right lane not free
                if psi < -0.3 % current state of vehicle
                    target(i).RLC = 0.7;
                    target(i).FL = 0.3;
                else
                    target(i).RLC = 0.1;
                    target(i).FL = 0.9;
                end
            else % right lane partially free
                if psi < -0.3 % current state of vehicle
                    target(i).RLC = 0.8;
                    target(i).FL = 0.2;
                else
                    target(i).RLC = 0.25;
                    target(i).FL = 0.75;
                end
            end
        else % following vehicle not present
            if target(i).surroundVehVel(4)==0 &&...
                    target(i).surroundVehVel(5)==0 &&...
                    target(i).surroundVehVel(6) < vehVel(i)%right lane free
                if psi < -0.3 % current state of vehicle
                    target(i).RLC = 0.8;
                    target(i).FL = 0.2;
                else
                    target(i).RLC = 0.3;
                    target(i).FL = 0.7;
                end
            elseif target(i).surroundVehVel(5)~=0 ||...
                    target(i).surroundVehVel(4)~=0% right lane not free
                if psi < -0.3 % current state of vehicle
                    target(i).RLC = 0.7;
                    target(i).FL = 0.3;
                else
                    target(i).RLC = 0.1;
                    target(i).FL = 0.9;
                end
            else % right lane partially free
                if psi < -0.3 % current state of vehicle
                    target(i).RLC = 0.75;
                    target(i).FL = 0.25;
                else
                    target(i).RLC = 0.2;
                    target(i).FL = 0.8;
                end
            end
        end
        if target(i).surroundVehVel(1)~= 0 % lead vehicle present
            relVel = vehVel(i)-target(i).surroundVehVel(4);
            if relVel > 0 % slow lead vehicle
                target(i).B = relVel/vehVel(i);
            end
        end
    end
end
% END loop over the target vehicles
end