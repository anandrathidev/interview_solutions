# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""

import numpy as np
from matplotlib import pyplot as plt

from sklearn.gaussian_process import GaussianProcessRegressor
from sklearn.gaussian_process.kernels import RBF, ConstantKernel as C

np.random.seed(1)

import pandas as pd

data_file = "D:/Users/anandrathi/Documents/Work/Kaggle/Santander/train.csv/train.csv"

yrbf_file = "D:/Users/anandrathi/Documents/Work/Kaggle/Santander//rbf_y.csv"

data = None
Y = None
try:
  data = pd.read_csv(data_file)
  list(data.columns)
  Y = data["target"]
  data = data.drop(columns=['ID', 'target'])
except Exception as e:
  print(e)

# Instanciate a Gaussian Process model
kernel = C(1.0, (1e-3, 1e3)) * RBF(10, (1e-2, 1e2))
gp = GaussianProcessRegressor(kernel=kernel, n_restarts_optimizer=9)

# Fit to data using Maximum Likelihood Estimation of the parameters
gp.fit(data, Y)

# Make the prediction on the meshed x-axis (ask for MSE as well)
y_pred, sigma = gp.predict(data, return_std=True)


from sklearn.metrics import mean_squared_error
from math import sqrt

y_pred = np.around(y_pred, decimals=2)
ypredDF = pd.DataFrame(y_pred.round()  , columns=["YHat"])

ypredDF["Y"] = Y

ypredDF.shape

trainrms = sqrt(mean_squared_error(ypredDF['Y'], ypredDF['YHat']))
print("RBF : trainrms {}".format(trainrms ) )

print(ypredDF.loc[ypredDF['Y'] == ypredDF['YHat'] ])

ypredDF.dtypes

ypredDF.to_csv(yrbf_file )

