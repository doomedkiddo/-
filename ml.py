import numpy as np
import pandas as pd
from matplotlib import pyplot as plt
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import LSTM
from tensorflow.keras.layers import Dense, Dropout
from sklearn.preprocessing import MinMaxScaler
from scikeras.wrappers import KerasClassifier, KerasRegressor
from sklearn.model_selection import GridSearchCV

from matplotlib import pyplot
import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'
df = pd.read_csv('data-ML.csv')
print(df.size)
def load_data(file_name):
    df = pd.read_csv(file_name, encoding='gbk')
    columns = df.columns
    df.fillna(df.mean(), inplace=True)
    return df
print(load_data('data-ML.csv'))
df = df[1:]
df = df.dropna(axis=0,how='any')


print(df.shape)
df = df.iloc[:,3:]
test_split=round((len(df)-1)*0.20)
print(test_split)
df_for_training=df[:-test_split]
df_for_testing=df[-test_split:]
print(df_for_training.shape)
print(df_for_testing.shape)




scaler = MinMaxScaler(feature_range=(0,1))
df_for_training_scaled = scaler.fit_transform(df_for_training)
df_for_testing_scaled=scaler.transform(df_for_testing)


def createXY(dataset,n_past):
    dataX = []
    dataY = []
    for i in range(n_past, len(dataset)):
            dataX.append(dataset[i - n_past:i, 0:dataset.shape[1]])
            dataY.append(dataset[i,0])
    return np.array(dataX),np.array(dataY)

trainX,trainY=createXY(df_for_training_scaled,30)
testX,testY=createXY(df_for_testing_scaled,30)
print("trainX Shape-- ",trainX.shape)
print("trainY Shape-- ",trainY.shape)
print("testX Shape-- ",testX.shape)
print("testY Shape-- ",testY.shape)
print("trainX[0]-- \n",trainX[0])
print("trainY[0]-- ",trainY[0])

print(trainX.shape[1], trainX.shape[2])




grid_model = Sequential()
grid_model.add(LSTM(50,return_sequences=True,input_shape=(trainX.shape[1], trainX.shape[2])))
grid_model.add(LSTM(50))
grid_model.add(Dropout(0.2))
grid_model.add(Dense(1))
grid_model.compile(loss = 'mse',optimizer = 'adam')


history = grid_model.fit(trainX,trainY, epochs = 50, batch_size=20, validation_data = (testX, testY))

grid_model.save('m2.h5')
pyplot.plot(history.history['loss'], label='train')
pyplot.plot(history.history['val_loss'], label='test')
pyplot.legend()
pyplot.show()
y_predict = grid_model.predict(testX)
mse_test=np.sum((y_predict-testY)**2)/len(testY)
print(mse_test)
