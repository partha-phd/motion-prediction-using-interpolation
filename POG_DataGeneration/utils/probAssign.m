% Function to assign probabilities to the main and sub hypotheses
function probAssign(vehicleDatabase, ~, n, scenario)

[numTarget, numLatHypotheses, numLongHypotheses] = size(vehicleDatabase);
% START loop over the target
for i = 1:numTarget
    multiplePathsLat = nan(numLatHypotheses, numLongHypotheses);
    multiplePathsLong = nan(numLatHypotheses, numLongHypotheses);
    probLat = nan(numLatHypotheses, numLongHypotheses);
    probLong = nan(numLatHypotheses, numLongHypotheses);

    % Estimation of lateral and longitudinal displacements of the
    % hypotheses
    for k = 1:size(vehicleDatabase, 3)
        for j = 1:size(vehicleDatabase,2)
            if ~isempty(vehicleDatabase(i,j,k).xCoordinates)
                multiplePathsLong(j,k) = ...
                    vehicleDatabase(i,j,k).xCG(n);
                multiplePathsLat(j,k) = vehicleDatabase(i,j,k).yCG(n);
            end
        end
    end

    % Triangle distribution based on lateral displacement
    for k = 1:numLongHypotheses
        distCurrentY = scenario.Target(i).yCG_New(n);
        if distCurrentY > max(multiplePathsLat(:,k))
            distCurrentY = max(multiplePathsLat(:,k));
        end
        if distCurrentY < min(multiplePathsLat(:,k))
            distCurrentY = min(multiplePathsLat(:,k));
        end
        try
            pd = makedist('Triangular', 'a', min(multiplePathsLat(:,k)),...
                'b', distCurrentY, 'c', max(multiplePathsLat(:,k)));
        catch
            pd = makedist('Triangular', 'a', min(multiplePathsLat(:,k))-0.01,...
                'b', distCurrentY, 'c', max(multiplePathsLat(:,k)));
        end
        idLat = find(~isnan(multiplePathsLat(:,k)));
        probLat(idLat,k) = pdf(pd, multiplePathsLat(idLat,k)');
        probLat(idLat,k) = (probLat(idLat,k)/sum(probLat(idLat,k)));
    end

    % Triangle distribution on longitudinal displacement
    for j = 1:numLatHypotheses
        distCurrentX = scenario.Target(i).xCG_New(n);
        if distCurrentX > max(multiplePathsLong(j,:))
            distCurrentX = max(multiplePathsLong(j,:));
        end
        if distCurrentX < min(multiplePathsLong(j,:))
            distCurrentX = min(multiplePathsLong(j,:));
        end
        if ~isnan(multiplePathsLong(j,:))
            pd = makedist('Triangular', 'a', min(multiplePathsLong(j,:)),...
                'b', distCurrentX, 'c', max(multiplePathsLong(j,:)));
            idLong = find(~isnan(multiplePathsLong(j,:)));
            probLong(j,idLong) = pdf(pd, multiplePathsLong(j,idLong)');
            probLong(j,idLong) = (probLong(j,idLong)/sum(probLong(j,idLong)));
        end
    end

    probMatrix = probLong .* probLat;

    % Assignment of probabilities
    for j = 1:numLatHypotheses
        for k = 1:numLongHypotheses
            vehicleDatabase(i,j,k).minProb = probMatrix(j,k);
        end
    end

end
% END loop over the target
end