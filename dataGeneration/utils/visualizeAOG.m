function plotH = visualizeAOG(AOG, scenarioNum)
% Plot the augmented occupancy grid
figure(3);
hold on;
subplot(6,1,1);
plotH(1) = imagesc(squeeze(AOG(scenarioNum, :, :, 1)));
%title('Occupancy');
axis off
subplot(6,1,2);
plotH(2) = imagesc(squeeze(AOG(scenarioNum, :, :, 2)));
%title('Velocity');
axis off
subplot(6,1,3);
plotH(3) = imagesc(squeeze(AOG(scenarioNum, :, :, 3)));
%title('Orientation');
axis off
subplot(6,1,4);
plotH(4) = imagesc(squeeze(AOG(scenarioNum, :, :, 4)));
%title('Longitudinal accleration');
axis off
subplot(6,1,5);
plotH(5) = imagesc(squeeze(AOG(scenarioNum, :, :, 5)));
axis off
%title('Lateral acceleration');
%subplot(6,1,6);
%plotH(6) = imagesc(squeeze(AOG(scenarioNum, :, :, 6)));
%title('Vehicle ID');
%sgtitle('Augmented Occupancy Grid');
hold off;
end