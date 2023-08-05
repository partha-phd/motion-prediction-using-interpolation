# Continuous Probabilistic Motion Prediction based on Latent Space Interpolation
![Architecture for the estimation of Predicted Occupancy Grid Maps](https://github.com/partha92/motion-prediction-using-interpolation/assets/64163836/1dc2fcc5-5533-4900-a6ce-460b2e58e41d)

Predicting and describing probabilistically the behavior of traffic participants is crucial for improving the trajectory planning of vehicles in critical traffic scenarios. A deep learning architecture is introduced in this work to predict a probabilistic space-time representation of the future, termed as the predicted Occupancy Grid Map (predicted OGM), that includes the interaction between the traffic participants as well as the uncertainties regarding their motion behavior. The architecture is based on Variational AutoEncoders (VAEs) and Random Forests (RFs) and it is introduced to obtain fine time step resolutions of the predicted OGMs that are required to plan a safe trajectory. The structure in the latent space of the VAEs is explored to enable the semantic manipulation of data. The VAEs are used for two purposes in this paper. One is to compress the input into a low dimensional space and the other is to sample in the latent space thereby generating realistic samples of the predicted OGMs. The proposed model is validated based on the publicly available highD dataset. The results demonstrate the effectiveness of the proposed method. Also, the possibility to use the predicted OGMs for safe trajectory planning of the ego vehicle is demonstrated.

## Get Started
### Dependecies 
Below are the environment and the corresponding dependencies with which the code was developed:
- Matlab 2022b
- Python 3.9
- Tensorflow 2.8

### Prepare Data 
- We use the publicly available highway data for the validation of our proposed model
- Download the publicly available highD dataset from [this link](https://www.highd-dataset.com)
- Store the downloaded data with folder name "data" under the folder POG_DataGeneration
- Run the script generateData.m to generate the augmented OGMs and the corresponding predicted OGMs

### Training
- Our architecture comprises of two Variational AutoEncoders and set of Random Forests for the estimation of predicted OGMs
- Run the script trainML.py under the folder "POG_Training" to train the model on the generated training data

### Validation
- Run the script validateML.py under the folder "POG_Validation" to validate the model on the generated test data

