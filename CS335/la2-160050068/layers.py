import numpy as np

class FullyConnectedLayer:
	def __init__(self, in_nodes, out_nodes):
		# Method to initialize a Fully Connected Layer
		# Parameters
		# in_nodes - number of input nodes of this layer
		# out_nodes - number of output nodes of this layer
		self.in_nodes = in_nodes
		self.out_nodes = out_nodes
		# Stores the outgoing summation of weights * feautres 
		self.data = None

		# Initializes the Weights and Biases using a Normal Distribution with Mean 0 and Standard Deviation 0.1
		self.weights = np.random.normal(0,0.1,(in_nodes, out_nodes))	
		self.biases = np.random.normal(0,0.1, (1, out_nodes))
		###############################################
		# NOTE: You must NOT change the above code but you can add extra variables if necessary 

	def forwardpass(self, X):
		# print('Forward FC ',self.weights.shape)
		# Input
		# activations : Activations from previous layer/input
		# Output
		# activations : Activations after one forward pass through this layer
		
		n = X.shape[0]  # batch size
		# print(X.shape)
		# INPUT activation matrix  		:[n X self.in_nodes]
		# OUTPUT activation matrix		:[n X self.out_nodes]
		# return self.weights*X+self.biases
		###############################################
		# TASK 1 - YOUR CODE HERE
		self.data=np.matmul(X,self.weights)+self.biases
		return sigmoid(self.data)
		###############################################
		
	def backwardpass(self, lr, activation_prev, delta):
		# Input
		# lr : learning rate of the neural network
		# activation_prev : Activations from previous layer
		# delta : del_Error/ del_activation_curr
		# Output
		# new_delta : del_Error/ del_activation_prev
		
		# Update self.weights and self.biases for this layer by backpropagation
		n = activation_prev.shape[0] # batch size
		# print(activation_prev.shape)
		###############################################
		# TASK 2 - YOUR CODE HERE
		# print(delta.shape)

		y=derivative_sigmoid(self.data)*delta
		b=np.matmul(y,np.transpose(self.weights))

		y2=np.repeat(np.reshape(y,(n,1,self.out_nodes)),self.in_nodes,axis=1)
		a=np.repeat(np.reshape(activation_prev,(n,self.in_nodes,1)),self.out_nodes,axis=2)
		
		self.weights=self.weights-lr*np.sum(y2*a,axis=0)
		self.biases=self.biases-lr*np.sum(y,axis=0)

		return b
		# raise NotImplementedError
		###############################################

class ConvolutionLayer:
	def __init__(self, in_channels, filter_size, numfilters, stride):
		# Method to initialize a Convolution Layer
		# Parameters
		# in_channels - list of 3 elements denoting size of input for convolution layer
		# filter_size - list of 2 elements denoting size of kernel weights for convolution layer
		# numfilters  - number of feature maps (denoting output depth)
		# stride	  - stride to used during convolution forward pass
		self.in_depth, self.in_row, self.in_col = in_channels
		self.filter_row, self.filter_col = filter_size
		self.stride = stride
		# print(in_channels,self.in_depth,self.in_row,self.in_col,filter_size)


		self.out_depth = numfilters
		self.out_row = int((self.in_row - self.filter_row)/self.stride + 1)
		self.out_col = int((self.in_col - self.filter_col)/self.stride + 1)

		# Stores the outgoing summation of weights * feautres 
		self.data = None
		
		# Initializes the Weights and Biases using a Normal Distribution with Mean 0 and Standard Deviation 0.1
		self.weights = np.random.normal(0,0.1, (self.out_depth, self.in_depth, self.filter_row, self.filter_col))	
		self.biases = np.random.normal(0,0.1,self.out_depth)
		

	def forwardpass(self, x):
		# print('Forward CN ',self.weights.shape)
		# Input
		# X : Activations from previous layer/input
		# Output
		# activations : Activations after one forward pass through this layer
		n = x.shape[0]  # batch size
		# print(x.shape)
		# INPUT activation matrix  		:[n X self.in_channels[0] X self.in_channels[1] X self.in_channels[2]]
		# OUTPUT activation matrix		:[n X self.outputsize[0] X self.outputsize[1] X self.numfilters]

		###############################################
		# TASK 1 - YOUR CODE HERE
		a=np.zeros((n,self.out_depth,self.out_row,self.out_col))
		for i in range(n):
			for j in range(self.out_depth):
				for k in range(self.out_row):
					for l in range(self.out_col):
						# s=0;
						a[i,j,k,l]=np.sum(x[i,:,k*self.stride:k*self.stride+self.filter_row,l*self.stride:l*self.stride+self.filter_col]*self.weights[j,:,:,:])+self.biases[j]
						# for m in range(self.in_depth):
						# 	for p in range(self.filter_row):
						# 		for q in range(self.filter_col):
						# 			s+=x[i,j+m,k*self.stride+p,l*self.stride+q]*self.weights[j,m,p,q]
		self.data=a
		return sigmoid(a)
	
	
		# raise NotImplementedError
		###############################################

	def backwardpass(self, lr, activation_prev, delta):
		# Input
		# lr : learning rate of the neural network
		# activation_prev : Activations from previous layer
		# delta : del_Error/ del_activation_curr
		# Output
		# new_delta : del_Error/ del_activation_prev
		
		# Update self.weights and self.biases for this layer by backpropagation
		n = activation_prev.shape[0] # batch size
		# print(activation_prev.shape)
		###############################################
		# TASK 2 - YOUR CODE HERE
		# print(self.data.shape)
		# print(delta.shape)
		# y=derivative_sigmoid(self.data)*delta
		# f=np.flip(np.flip(self.weights,2),3)
		y=derivative_sigmoid(self.data)*delta
		for i in range(n):
			for j in range(self.out_depth):
				self.biases[j]=self.biases[j]-lr*np.sum(y[i,j,:,:])
				for m in range(self.in_depth):
					for k in range(self.filter_row):
						for l in range(self.filter_col):
							self.weights[j,m,k,l]=self.weights[j,m,k,l]-lr*np.sum(activation_prev[i,m,k*self.stride:k*self.stride+self.out_row,l*self.stride:l*self.stride+self.out_col]*y[i,j,:,:])
		# y1=np.zeros((delta.shape[0],delta.shape[1],delta.shape[2]*self.stride,delta.shape[3]*self.stride))
		
		# for i in range(delta.shape[0]):
		# 	for j in range(delta.shape[1]):
		# 		for k in range(delta.shape[2]):
		# 			for l in range(delta.shape[3]):
		# 				y1[i,j,k*self.stride,l*self.stride]=y[i,j,k,l]
		# y1=np.pad(y1,((0,0),(0,0),(self.filter_row-1,self.filter_row-1),(self.filter_col-1,self.filter_col-1)),'constant',constant_values=0)
		# a=np.zeros(activation_prev.shape)
		# for i in range(n):
		# 	for j in range(self.in_depth):
		# 		for k in range(a.shape[2]):
		# 			for l in range(a.shape[3]):
		# 				for m in range(self.out_depth):
		# 					a[i,j,k,l]+=np.sum(y1[i,m,k:k+self.filter_row,l:l+self.filter_col]*f[m,j,:,:])

		# return a


		# raise NotImplementedError
		###############################################
	
class AvgPoolingLayer:
	def __init__(self, in_channels, filter_size, stride):
		# Method to initialize a Convolution Layer
		# Parameters
		# in_channels - list of 3 elements denoting size of input for max_pooling layer
		# filter_size - list of 2 elements denoting size of kernel weights for convolution layer

		# NOTE: Here we assume filter_size = stride
		# And we will ensure self.filter_size[0] = self.filter_size[1]
		self.in_depth, self.in_row, self.in_col = in_channels
		self.filter_row, self.filter_col = filter_size
		self.stride = stride

		self.out_depth = self.in_depth
		self.out_row = int((self.in_row - self.filter_row)/self.stride + 1)
		self.out_col = int((self.in_col - self.filter_col)/self.stride + 1)
		# print(in_channels,self.in_depth,self.out_row,self.out_col,filter_size,stride)

	def forwardpass(self, x):
		# print('Forward MP ')
		# Input
		# X : Activations from previous layer/input
		# Output
		# activations : Activations after one forward pass through this layer
		
		n = x.shape[0]  # batch size
		# INPUT activation matrix  		:[n X self.in_channels[0] X self.in_channels[1] X self.in_channels[2]]
		# OUTPUT activation matrix		:[n X self.outputsize[0] X self.outputsize[1] X self.in_channels[2]]
		# print("hello",x.shape)
		###############################################
		# TASK 1 - YOUR CODE HERE
		a=np.zeros((n,self.out_depth,self.out_row,self.out_col))
		for i in range(n):
			for j in range(self.out_depth):
				for k in range(self.out_row):
					for l in range(self.out_col):
						a[i,j,k,l]=np.sum(x[i,j,k*self.stride:(k+1)*self.stride,l*self.stride:(l+1)*self.stride])/(self.stride**2)
		return a
		# raise NotImplementedError
		###############################################


	def backwardpass(self, alpha, activation_prev, delta):
		# Input
		# lr : learning rate of the neural network
		# activation_prev : Activations from previous layer
		# activations_curr : Activations of current layer
		# delta : del_Error/ del_activation_curr
		# Output
		# new_delta : del_Error/ del_activation_prev
		
		n = activation_prev.shape[0] # batch size

		###############################################
		# TASK 2 - YOUR CODE HERE
		return np.repeat(np.repeat(delta,self.stride,axis=3),self.stride,axis=2)
		# raise NotImplementedError
		###############################################


# Helper layer to insert between convolution and fully connected layers
class FlattenLayer:
    def __init__(self):
        pass
    
    def forwardpass(self, X):
        self.in_batch, self.r, self.c, self.k = X.shape
        return X.reshape(self.in_batch, self.r * self.c * self.k)

    def backwardpass(self, lr, activation_prev, delta):
        return delta.reshape(self.in_batch, self.r, self.c, self.k)


# Helper Function for the activation and its derivative
def sigmoid(x):
	return 1 / (1 + np.exp(-x))

def derivative_sigmoid(x):
	return sigmoid(x) * (1 - sigmoid(x))