function plotH = visualizePOG(POG, scenarioNum, idTimeStep, scenario)
% Plot the Predicted Occupancy Grid for each time step
figure(4);
hold on;
POG_Pred = squeeze(POG(scenarioNum, idTimeStep, :, :));
noisefactor = idTimeStep * 0.0002;
POG_Noise = POG_Pred + noisefactor*randn(size(POG_Pred)) + noisefactor;
plotH = imagesc(flipud(POG_Noise));
% Plot the target vehicle
for idTarget = 1:size(scenario(scenarioNum).Target,2)
    [xBox, yBox] = ...
        calcBoundingBox(scenario(scenarioNum).Target(idTarget).xCG_New(idTimeStep+1)*2,...
        scenario(scenarioNum).Target(idTarget).yCG_New(idTimeStep+1)*2,...
        deg2rad(scenario(scenarioNum).Target(idTarget).psi_New(idTimeStep+1)),...
        scenario(scenarioNum).Target(idTarget).bbox(idTimeStep+1, 3)*2,...
        scenario(scenarioNum).Target(idTarget).bbox(idTimeStep+1, 4)*2);
    plotH(end + 1) = plot([xBox xBox(1)], [yBox yBox(1)], 'r', 'LineWidth', 2);
end
hold off;
axis equal
axis([0 400 0 30])
axis off
end