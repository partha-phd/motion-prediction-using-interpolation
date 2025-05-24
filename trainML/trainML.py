# TRAINING OF MACHINE LEARNING ALGORITHMS TO MAP AOGs TO POGs

# Import the necessary libraries
import tensorflow as tf
import numpy as np
import scipy.io as sio
import matplotlib.pyplot as plt
import os.path
from sklearn.ensemble import RandomForestRegressor
import pickle
import os
from joblib import Parallel, delayed
import multiprocessing


# Respective classes
class AOG:
    def __init__(self):
        # Loading a mat file
        data_path = os.path.normpath(os.getcwd() + os.sep + os.pardir)
        data_file = sio.loadmat(data_path + "/POG_DataGeneration/generatedData/AOG_Training")
        self.train_input = data_file["AOG_Training"]
        self.num_train_examples = 8000 # Number of training samples
        self.train_epoch_completed = 0
        self.train_index_in_epoch = 0

    def next_train_batch(self, images, batch_size):
        start = self.train_index_in_epoch
        self.train_index_in_epoch += batch_size
        if self.train_index_in_epoch > self.num_train_examples:
            self.train_epoch_completed += 1
            start = 0
            self.train_index_in_epoch = batch_size
            assert batch_size <= self.num_train_examples
        end = self.train_index_in_epoch
        return images[start:end]

    def load_train_data(self, batch_size):
        input_train_np = self.next_train_batch(self.train_input, batch_size)
        return input_train_np


class POG:
    def __init__(self):
        # Loading a mat file
        data_path = os.path.normpath(os.getcwd() + os.sep + os.pardir);
        data_file = sio.loadmat(data_path + "/POG_DataGeneration/generatedData/POG_Training")
        self.train_input = data_file["POG_Training"]
        self.train_input = self.train_input[..., np.newaxis]
        self.num_train_examples = 3 * 75
        self.train_epoch_completed = 0
        self.train_index_in_epoch = 0

    def next_train_batch(self, images, batch_size):
        start = self.train_index_in_epoch
        self.train_index_in_epoch += batch_size
        if self.train_index_in_epoch > self.num_train_examples:
            self.train_epoch_completed += 1
            start = 0
            self.train_index_in_epoch = batch_size
            assert batch_size <= self.num_train_examples
        end = self.train_index_in_epoch
        return images[start:end]

    def load_train_data(self, batch_size):
        input_train_np = self.next_train_batch(self.train_input, batch_size)
        return input_train_np


# Variational AutoEncoder - 1
def variational_autoencoder_AOG(input_shape=None, n_latent=None):
    # Initialise input to the network
    if n_latent is None:
        n_latent = [None]
    if input_shape is None:
        input_shape = [None, 30, 200, 6]
    x = tf.placeholder(tf.float32, input_shape, name='x')

    # Encoder-----------------------------------------------------------------------------------------------------------
    # Convolution
    conv_1 = tf.keras.Conv2D(inputs=x, filters=32, kernel_size=(4, 4),
                              padding='same', strides=(2, 2), activation='relu')
    conv_2 = tf.keras.Conv2D(inputs=conv_1, filters=64, kernel_size=(4, 4),
                              padding='same', strides=(2, 2), activation='relu')
    conv_3 = tf.keras.conv2d(inputs=conv_2, filters=128, kernel_size=(4, 4),
                              padding='same', strides=(1, 1), activation='relu')

    # Reshaping
    dense_1 = tf.keras.layers.Flatten(conv_3)
    dense_2 = tf.keras.layers.Dense(inputs=dense_1, units=5000, activation='relu')

    # Sampling----------------------------------------------------------------------------------------------------------
    # Mean and standard deviation
    latent_space_mn = tf.keras.layers.Dense(inputs=dense_2, units=n_latent)
    latent_space_sd = 0.5 * tf.keras.layers.Dense(inputs=dense_2, units=n_latent)
    # Random sampling from normal distribution
    epsilon = tf.keras.random_normal(tf.stack([tf.keras.shape(dense_2)[0], n_latent]))
    z = (latent_space_mn + tf.multiply(epsilon, tf.keras.exp(latent_space_sd)))

    # Decoder-----------------------------------------------------------------------------------------------------------
    # Fully connected layer
    dense_3 = tf.keras.layers.Dense(inputs=z, units=5000, activation='relu')
    dense_4 = tf.keras.layers.Dense(inputs=dense_3, units=10976, activation='relu')
    reshape_1 = tf.keras.reshape(dense_4, [-1, 7, 49, 32])
    # Transposed Convolution
    deconv_1 = tf.layers.conv2d_transpose(inputs=reshape_1, filters=64, kernel_size=(3, 4),
                                          strides=(2, 2), padding='valid', activation=tf.nn.leaky_relu)
    deconv_2 = tf.layers.conv2d_transpose(inputs=deconv_1, filters=64, kernel_size=(4, 4),
                                          strides=(2, 2), padding='same', activation=tf.nn.leaky_relu)
    deconv_3 = tf.layers.conv2d_transpose(inputs=deconv_2, filters=5, kernel_size=(4, 4),
                                          strides=(1, 1), padding='same')

    # Reconstruction
    y = deconv_3

    # Cost
    img_loss = tf.reduce_sum(tf.square(y - x))
    latent_loss = -0.5 * tf.reduce_sum(1.0 + latent_space_sd - tf.square(latent_space_mn)
                                       - tf.exp(latent_space_sd), 1)
    cost = tf.reduce_mean(img_loss + latent_loss)

    # return the desired output (input, latent representation, mean, standard deviation,
    #                            reconstructed output and cost)
    return {'x': x, 'z': z, 'latent_space_mn': latent_space_mn, 'latent_space_sd': latent_space_sd,
            'y': y, 'cost': cost}


# Variational Autoencoder - 2
def variational_autoencoder_POG(input_shape=None, n_latent=None):
    # Initialise input to the network
    if n_latent is None:
        n_latent = [None]
    if input_shape is None:
        input_shape = [None, 30, 200, 1]
    x = tf.placeholder(tf.float32, input_shape, name='x')

    # Encoder-----------------------------------------------------------------------------------------------------------
    # Convolution
    conv_1 = tf.layers.conv2d(inputs=x, filters=64, kernel_size=(4, 4),
                              padding='same', strides=(2, 2), activation=tf.nn.leaky_relu)
    conv_1_bn = tf.layers.batch_normalization(inputs=conv_1)
    conv_2 = tf.layers.conv2d(inputs=conv_1_bn, filters=64, kernel_size=(4, 4),
                              padding='same', strides=(2, 2), activation=tf.nn.leaky_relu)
    conv_2_bn = tf.layers.batch_normalization(inputs=conv_2)
    conv_3 = tf.layers.conv2d(inputs=conv_2_bn, filters=64, kernel_size=(4, 4),
                              padding='same', strides=(1, 1), activation=tf.nn.leaky_relu)
    conv_3_bn = tf.layers.batch_normalization(inputs=conv_3)
    # Reshaping
    dense_1 = tf.contrib.layers.flatten(conv_3_bn)
    dense_2 = tf.layers.dense(inputs=dense_1, units=1000, activation=tf.nn.leaky_relu)
    dense_2_bn = tf.layers.batch_normalization(inputs=dense_2)
    # Sampling----------------------------------------------------------------------------------------------------------
    # Mean and standard deviation
    latent_space_mn = tf.layers.dense(inputs=dense_2_bn, units=n_latent)
    latent_space_sd = 0.5 * tf.layers.dense(inputs=dense_2_bn, units=n_latent)
    # Random sampling from normal distribution
    epsilon = tf.random_normal(tf.stack([tf.shape(dense_2_bn)[0], n_latent]))
    z = (latent_space_mn + tf.multiply(epsilon, tf.exp(latent_space_sd)))
    # Decoder-----------------------------------------------------------------------------------------------------------
    # Fully connected layer
    dense_3 = tf.layers.dense(inputs=z, units=1000, activation=tf.nn.leaky_relu)
    dense_4 = tf.layers.dense(inputs=dense_3, units=1715, activation=tf.nn.leaky_relu)
    reshape_1 = tf.reshape(dense_4, [-1, 7, 49, 5])
    # Transposed Convolution
    deconv_1 = tf.layers.conv2d_transpose(inputs=reshape_1, filters=64, kernel_size=(3, 4),
                                          strides=(2, 2), padding='valid', activation=tf.nn.leaky_relu)
    deconv_1_bn = tf.layers.batch_normalization(inputs=deconv_1)
    deconv_2 = tf.layers.conv2d_transpose(inputs=deconv_1_bn, filters=64, kernel_size=(4, 4),
                                          strides=(2, 2), padding='same', activation=tf.nn.leaky_relu)
    deconv_2_bn = tf.layers.batch_normalization(inputs=deconv_2)
    deconv_3 = tf.layers.conv2d_transpose(inputs=deconv_2_bn, filters=1, kernel_size=(4, 4),
                                          strides=(1, 1), padding='same')

    # Reconstruction
    y = deconv_3

    # Cost
    recon_loss = tf.reduce_sum(tf.square(y - x))
    latent_loss = -0.5 * tf.reduce_sum(1.0 + latent_space_sd - tf.square(latent_space_mn)
                                       - tf.exp(latent_space_sd), 1)
    cost = tf.reduce_mean(recon_loss + latent_loss)

    # return the desired output (input, latent representation, mean, standard deviation,
    #                            reconstructed output and cost)
    return {'x': x, 'z': z, 'latent_space_mn': latent_space_mn, 'latent_space_sd': latent_space_sd,
            'y': y, 'cost': cost}


# Random Forest
def predict_RF_output(no_of_pixels, test_input, t_val):
    file_name = os.getcwd() + '\\trainedModel\\trainedModel_RF\\' + t_val + '\\' + str(no_of_pixels)
    trained_model = pickle.load(open(file_name, 'rb'))
    test_output = trained_model.predict(test_input)
    return test_output


def train_random_forest(no_of_pixels, train_input, train_output, t_val):
    regression_model = RandomForestRegressor(n_estimators=50, min_samples_split=10, min_samples_leaf=5, random_state=0)
    regression_model.fit(train_input, train_output)
    file_name = os.getcwd() + '\\trainedModel\\trainedModel_RF\\' + t_val + '\\' + str(no_of_pixels)
    pickle.dump(regression_model, open(file_name, 'wb'))


if __name__ == '__main__':

    print('START: Training of VAE-1')
    # Load the dataset
    DATASET = AOG()

    # Hyper-parameters for training
    batch_size = 32
    n_latent_AOG = 1000
    n_epochs = 100
    learning_rate = 0.0001
    global_step = tf.Variable(0, name='global_step', trainable=False)

    # Calling the autoencoder
    vae_AOG = variational_autoencoder_AOG(n_latent=n_latent_AOG)

    # Define the optimization function
    optimizer = tf.train.AdamOptimizer(learning_rate).minimize(vae_AOG['cost'])

    # Add ops to save and restore all the variables
    saver = tf.train.Saver()

    # We create a session to use the graph
    sess = tf.Session()
    sess.run(tf.global_variables_initializer())

    # Performing the training
    for epoch_i in range(n_epochs):
        for batch_i in range(DATASET.num_train_examples // batch_size):
            train = DATASET.load_train_data(batch_size)
            sess.run(optimizer, feed_dict={vae_AOG['x']: train})
            features_train, recon_train = sess.run([vae_AOG['z'], vae_AOG['y']], feed_dict={vae_AOG['x']: train})
            if batch_i == 0:
                features_AOG_save = features_train
                recon_AOG_save = recon_train
                AOG_save = train
            else:
                features_AOG_save = np.concatenate((features_AOG_save, features_train))
                recon_AOG_save = np.concatenate((recon_AOG_save, recon_train))
                AOG_save = np.concatenate((AOG_save, train))
        print('Training Epoch: ', epoch_i, 'Training Cost: ', sess.run(vae_AOG['cost'],
                                                                       feed_dict={vae_AOG['x']: train}))

    # Saving the trained model
    save_path = saver.save(sess, "trainedModel\\model_VAE_AOG.ckpt")

    # Save the latent representation and the reconstructed AOG as a mat file
    output_VAE_1 = {'featuresAOG_Training': features_AOG_save}
    saveDir = os.getcwd() + '\\generatedData\\featuresAOG_Training'
    sio.savemat(saveDir, output_VAE_1)

    # Plot an example reconstruction of the data
    fig = plt.figure()
    a = fig.add_subplot(1, 2, 1)
    plt.imshow(recon_AOG_save[1, :, :, 0])
    a.set_title('Reconstructed AOG')
    a = fig.add_subplot(1, 2, 2)
    plt.imshow(AOG_save[1, :, :, 0])
    a.set_title('Ground truth AOG')
    fig.show()
    plt.draw()
    plt.waitforbuttonpress()

    print('END: Training of VAE-1')
    # ------------------------------------------------------------------------------------------------------------------
    print('START: Training of VAE-2')
    # Load the dataset
    DATASET = POG()

    # Hyper-parameters for training
    batch_size = 32
    n_latent_POG = 100
    n_epochs = 300
    learning_rate = 0.0001
    global_step = tf.Variable(0, name='global_step', trainable=False)

    # Calling the autoencoder
    vae_POG = variational_autoencoder_POG(n_latent=n_latent_POG)

    # Define the optimization function
    optimizer = tf.train.AdamOptimizer(learning_rate).minimize(vae_POG['cost'])

    # Add ops to save and restore all the variables
    saver = tf.train.Saver()

    # We create a session to use the graph
    sess = tf.Session()
    sess.run(tf.global_variables_initializer())

    # Performing the training
    for epoch_i in range(n_epochs):
        for batch_i in range(DATASET.num_train_examples // batch_size):
            train = DATASET.load_train_data(batch_size)
            sess.run(optimizer, feed_dict={vae_POG['x']: train})
            features_train, recon_train = sess.run([vae_POG['z'], vae_POG['y']], feed_dict={vae_POG['x']: train})
            if batch_i == 0:
                features_POG_save = features_train
                recon_POG_save = recon_train
                POG_save = train
            else:
                features_POG_save = np.concatenate((features_POG_save, features_train))
                recon_POG_save = np.concatenate((recon_POG_save, recon_train))
                POG_save = np.concatenate((POG_save, train))
        print('Training Epoch: ', epoch_i, 'Training Cost: ', sess.run(vae_POG['cost'],
                                                                       feed_dict={vae_POG['x']: train}))

    # Saving the trained model
    save_path = saver.save(sess, "trainedModel\\model_VAE_POG.ckpt")

    # Save the latent representation and the reconstructed POG as a mat file
    output_VAE_2 = {'featuresPOG_Training': features_POG_save}
    saveDir = os.getcwd() + '\\generatedData\\featuresPOG_Training'
    sio.savemat(saveDir, output_VAE_2)

    # Plot an example reconstruction of the data
    fig = plt.figure()
    a = fig.add_subplot(1, 2, 1)
    plt.imshow(recon_POG_save[0, :, :, 0])
    a.set_title('Reconstructed POG')
    a = fig.add_subplot(1, 2, 2)
    plt.imshow(POG_save[0, :, :, 0])
    a.set_title('Ground truth POG')
    fig.show()
    plt.draw()
    plt.waitforbuttonpress()

    print('END: Training of VAE-2')
    # ------------------------------------------------------------------------------------------------------------------
    print('START: Training of set of RFs')
    num_cores = multiprocessing.cpu_count()
    data_id = np.arange(6, 37, 6)
    str_array = ["t_05", "t_10", "t_15", "t_20", "t_25", "t_30"]
    # Set of RFs trained to predict POGs from 0 to 3s with step size of 0.5s
    for j in range(6):
        train_id = np.arange(data_id[j], 3 * 37, 37)
        t_val_str = str_array[j]
        Parallel(n_jobs=num_cores)(delayed(train_random_forest)(i, features_AOG_save, features_POG_save[train_id, i],
                                                                t_val_str) for i in range(n_latent_POG))
        predicted_output = Parallel(n_jobs=num_cores)(delayed(predict_RF_output)(i, features_AOG_save, t_val_str)
                                                      for i in range(n_latent_POG))
    output_RF = {'features_POG_predicted': predicted_output}
    saveDir = os.getcwd() + '\\generatedData\\featuresPOG_Predicted'
    sio.savemat(saveDir, output_RF)
    print('END: Training of set of RFs')
    # ------------------------------------------------------------------------------------------------------------------
