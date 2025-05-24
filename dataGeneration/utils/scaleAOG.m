% Function to scale the values of AOG to lie in the interval [0,1]
function AOG_Scaled = scaleAOG(AOG)
% Channel 1(occupancy) and 6(vehicle ID) does not require scaling

vel_vec = AOG(:,:,:,2);
acc_x_vec = AOG(:,:,:,3);
acc_y_vec = AOG(:,:,:,4);
psi_vec = AOG(:,:,:,5);

% Range of velocity channel
max_vel = max(vel_vec(:));
min_vel = min(vel_vec(:));
range_vel = (max_vel - min_vel)+eps(max_vel - min_vel);

% Range of longitudinal acceleration
max_acc_x = max(acc_x_vec(:));
min_acc_x = min(acc_x_vec(:));
range_acc_x = (max_acc_x - min_acc_x)+eps(max_acc_x - min_acc_x);

% Range of lateral acceleration
max_acc_y = max(acc_y_vec(:));
min_acc_y = min(acc_y_vec(:));
range_acc_y = (max_acc_y - min_acc_y)+eps(max_acc_y - min_acc_y);

% Range of orientation
max_psi = max(psi_vec(:));
min_psi = min(psi_vec(:));
range_psi = (max_psi - min_psi)+eps(max_psi - min_psi);

AOG_Scaled = AOG;
% START loop over the number of scenarios
for i = 1:size(AOG,1)
    
    % Identify the vehicles pixels
    [row_id_vehicles, col_id_vehicles] = find(squeeze(AOG(i,:,:,2)));
    
    % START loop over the vehicle pixels
    for j = 1:size(row_id_vehicles,1)
        % Scaling of velocity channel
        AOG_Scaled(i,row_id_vehicles(j),col_id_vehicles(j),2) =...
            (AOG(i,row_id_vehicles(j),col_id_vehicles(j),2)-...
            (min_vel-eps(min_vel)))/range_vel;
        
        % Scaling of longitudinal acceleration channel
        AOG_Scaled(i,row_id_vehicles(j),col_id_vehicles(j),3) =...
            (AOG(i,row_id_vehicles(j),col_id_vehicles(j),3)-...
            (min_acc_x -eps(min_acc_x)))/range_acc_x;
        
        % Scaling of lateral acceleration channel
        AOG_Scaled(i,row_id_vehicles(j),col_id_vehicles(j),4) =...
            (AOG(i,row_id_vehicles(j),col_id_vehicles(j),4)-...
            (min_acc_y - eps(min_acc_y)))/range_acc_y;
        
        % Scaling of orientation channel
        AOG_Scaled(i,row_id_vehicles(j),col_id_vehicles(j),5) =...
            (AOG(i,row_id_vehicles(j),col_id_vehicles(j),5)-...
            (min_psi-eps(min_psi)))/range_psi;
    end
    % END loop over the vehicle pixels
end
% END loop over the number of scenarios
end