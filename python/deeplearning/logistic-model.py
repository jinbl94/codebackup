#! /usr/bin/python

import numpy as np
import matplotlib.pyplot as plt
from nn_utils import *

def initialize_with_zeros(dim):
	w = np.zeros((dim,1))
	b = 0
	
	assert(w.shape == (dim, 1))
	assert(isinstance(b, float) or isinstance(b, int))
	
	return w, b

def propagate(w,b,X,Y):
	m = X.shape[1]
	
	A = sigmoid(np.dot(w.T,X)+b)
	cost = -(np.dot(Y,np.log(A.T))+np.dot((1-Y),np.log(1-A.T)))/m

	dw = np.dot(X,(A-Y).T)/m
	db = np.sum(A-Y)/m
	
	assert(dw.shape == w.shape)
	assert(db.dtype == float)
	cost = np.squeeze(cost)
	assert(cost.shape == ())
	
	grads = {"dw": dw,
	         "db": db}
	
	return grads, cost

def optimize(w, b, X, Y, num_iterations, learning_rate, print_cost = False):
	costs = []
	
	for i in range(num_iterations):
	    grads, cost = propagate(w,b,X,Y)
	    dw = grads["dw"]
	    db = grads["db"]

	    w = w-learning_rate*dw
	    b = b-learning_rate*db
	    
	    if i % 100 == 0:
	        costs.append(cost)
	    
	    if print_cost and i % 100 == 0:
	        print ("Cost after iteration %i: %f" %(i, cost))
	
	params = {"w": w,
	          "b": b}
	
	grads = {"dw": dw,
	         "db": db}
	
	return params, grads, costs

def predict(w, b, X):
	m = X.shape[1]
	Y_prediction = np.zeros((1,m))
	w = w.reshape(X.shape[0], 1)
	
	A = sigmoid(np.dot(w.T,X)+b)
	
	for i in range(A.shape[1]):
	    Y_prediction[0][i]=(0 if A[0][i]<=0.5 else 1)
	assert(Y_prediction.shape == (1, m))
	
	return Y_prediction

def model(X_train, Y_train, num_iterations = 50, learning_rate = 1, print_cost = False):
	w, b = initialize_with_zeros(X_train.shape[0])
	parameters, grads, costs = optimize(w,b,X_train,Y_train,num_iterations,learning_rate,print_cost)
	
	w = parameters["w"]
	b = parameters["b"]
	
	d = {"costs": costs,
	     "w" : w, 
	     "b" : b,
	     "learning_rate" : learning_rate,
	     "num_iterations": num_iterations}
	
	return d

def gen_data(n=0):
	x=np.random.random((2,n))
	#x=np.array([[1,1,2,1,4,5,6,6],
	#			[1,2,2,0,5,6,7,6]])
	y=np.zeros((1,n))
	#y=np.array([[1,1,1,1,0,0,0,0]])

	for i in range(n):
		if sum(x.T[i])>=1:
			y[0][i]=1

	return x*30-15,y
#	return x,y

def draw_x():
	n_str=input('Number of points: ')
	try:
		n_num=int(n_str)
	except ValueError:
		exit('Not Integer!')
	X_train,Y_train=gen_data(n_num)
##	X_train,Y_train=gen_data()
	d=model(X_train,Y_train,num_iterations=1000,learning_rate=1)
	w=d["w"]
	b=d["b"]
	print(w,b)
	x0=[];
	x1=[];
	y0=[];
	y1=[];
	for i in range(X_train.shape[1]):
		if Y_train[0][i]==0:
			x0.append(X_train[0][i])
			y0.append(X_train[1][i])
		else:
			x1.append(X_train[0][i])
			y1.append(X_train[1][i])
	x=np.arange(-15,15,2)
	y=(-b-w[0]*x)/w[1]
	fig=plt.figure()
	ax=fig.add_subplot(111)
	ax.scatter(x0,y0,s=10,c='red')
	ax.scatter(x1,y1,s=10,c='green')
	ax.plot(x,y)
	plt.xlabel('x')
	plt.ylabel('y')
	plt.title('Binary Logistic Regression')
	plt.show()
	
np.seterr(all='ignore')
draw_x()
