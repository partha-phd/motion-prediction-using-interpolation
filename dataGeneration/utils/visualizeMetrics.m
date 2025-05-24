function plotH = visualizeMetrics(scenario, scenarioNum, idTimeStep)
% Plot the TTC
figure(2);
hold on;
subplot(1,2,1);
plotH(1) = plot(0.04:0.04:idTimeStep * 0.04,...
    scenario(scenarioNum).EGO.TTC(1:idTimeStep), 'LineWidth', 2);
xlabel('Simulation time in [s]');
ylabel('Time To Collision in [s]');
title('Time To Collision');
% Plot the THW
subplot(1,2,2);
plotH(2) = plot(0.04:0.04:idTimeStep * 0.04,...
    scenario(scenarioNum).EGO.THW(1:idTimeStep), 'LineWidth', 2);
xlabel('Simulation time in [s]');
ylabel('Headway Time in [s]');
title('Headway Time');
sgtitle('Criticality Metrics')
hold off;
end