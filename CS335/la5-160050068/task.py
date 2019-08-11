import numpy as np
from utils import *

def preprocess(X, Y):
	''' TASK 0
	X = input feature matrix [N X D] 
	Y = output values [N X 1]
	Convert data X, Y obtained from read_data() to a usable format by gradient descent function
	Return the processed X, Y that can be directly passed to grad_descent function
	NOTE: X has first column denote index of data point. Ignore that column 
	and add constant 1 instead (for bias part of feature set)
	'''
	l=[1 for i in range(X.shape[1])]
	k=[[] for i in range(X.shape[1])]
	for i in range(X.shape[1]):
		if type(X[0,i])==str:
			l[i]=len(set(X[:,i]))
		else:
			m=np.mean(X[:,i])
			s=np.std(X[:,i])
			k[i].append(m)
			k[i].append(s)
		

	ans=np.zeros((X.shape[0],sum(l)))
	c=1
	for j in range(X.shape[0]):
		ans[j,0]=1
	for i in range(1,X.shape[1]):
		if type(X[0,i])==str:
			t=one_hot_encode(X[:,i],list(set(X[:,i])))
			# print(t.shape,X.shape[0],l[i])
			for j in range(X.shape[0]):
				for r in range(l[i]):
					ans[j,c+r]=t[j,r]
			c+=l[i]
		
		else:
			for j in range(X.shape[0]):
				ans[j,c]=(X[j,i]-k[i][0])/k[i][1]
			c+=1

	return ans.astype(float),Y.astype(float)

def grad_ridge(W, X, Y, _lambda):
	'''  TASK 2
	W = weight vector [D X 1]
	X = input feature matrix [N X D]
	Y = output values [N X 1]
	_lambda = scalar parameter lambda
	Return the gradient of ridge objective function (||Y - X W||^2  + lambda*||w||^2 )
	'''
	D=np.matmul(X,W)-Y
	D=np.reshape(D,(1,X.shape[0]))
	D=np.transpose(np.matmul(D,X))
	ans=2*(D+_lambda*W)
	return ans

def ridge_grad_descent(X, Y, _lambda, max_iter=30000, lr=0.00001, epsilon = 1e-4):
	''' TASK 2
	X 			= input feature matrix [N X D]
	Y 			= output values [N X 1]
	_lambda 	= scalar parameter lambda
	max_iter 	= maximum number of iterations of gradient descent to run in case of no convergence
	lr 			= learning rate
	epsilon 	= gradient norm below which we can say that the algorithm has converged 
	Return the trained weight vector [D X 1] after performing gradient descent using Ridge Loss Function 
	NOTE: You may precompure some values to make computation faster
	'''
	# def f(w):
	# 	a=0
	# 	for i in range(w.shape[0]):
	# 		a+=w[i,0]**2
	# 	return a**0.5
	W=np.random.random((X.shape[1],1))

	for _ in range(max_iter):
		gradient=grad_ridge(W,X,Y,_lambda)
		if np.linalg.norm(gradient)<epsilon:
			return W
		W=W-lr*gradient

	return W

def k_fold_cross_validation(X, Y, k, lambdas, algo):
	''' TASK 3
	X 			= input feature matrix [N X D]
	Y 			= output values [N X 1]
	k 			= number of splits to perform while doing kfold cross validation
	lambdas 	= list of scalar parameter lambda
	algo 		= one of {coord_grad_descent, ridge_grad_descent}
	Return a list of average SSE values (on validation set) across various datasets obtained from k equal splits in X, Y 
	on each of the lambdas given 
	'''
	sses=[0 for i in range(len(lambdas))]
	ws=[0 for i in range(len(lambdas))]
	N,_=X.shape
	n=N//k
	for l in range(len(lambdas)):
		s=[0 for i in range(k)]
		wzero=[0 for i in range(k)]
		for i in range(k):
			if i==k-1:
				trainX=np.delete(X,np.s_[i*n:N],axis=0)
				trainY=np.delete(Y,np.s_[i*n:N],axis=0)
				testX=X[i*n:N,:]
				testY=Y[i*n:N,:]
			else:
				trainX=np.delete(X,np.s_[i*n:i*n+n],axis=0)
				trainY=np.delete(Y,np.s_[i*n:i*n+n],axis=0)
				testX=X[i*n:i*n+n,:]
				testY=Y[i*n:i*n+n,:]
			W=algo(trainX,trainY,lambdas[l])
			for j in range(W.shape[0]):
				if abs(W[j,0])<1e-4:
					wzero[i]+=1
			# D=testY-np.matmul(testX,W)
			# D=np.matmul(np.transpose(D),D)
			# print(D[0,0])
			s[i]=sse(testX,testY,W)
		sses[l]=np.mean(np.array(s))
		ws[l]=np.mean(np.array(wzero))
	# print(ws)
	# from matplotlib import pyplot as plt
	# plt.plot(lambdas, ws)
	# plt.show()
	return sses


def coord_grad_descent(X, Y, _lambda, max_iter=1000):
	''' TASK 4
	X 			= input feature matrix [N X D]
	Y 			= output values [N X 1]
	_lambda 	= scalar parameter lambda
	max_iter 	= maximum number of iterations of gradient descent to run in case of no convergence
	Return the trained weight vector [D X 1] after performing gradient descent using Ridge Loss Function 
	'''
	W=np.random.random((X.shape[1],1))
	X1=np.matmul(np.transpose(X),X)
	Y1=np.matmul(np.transpose(X),Y)
	def lasso_grad_root(d,X,Y,W):
		W[d,0]=0
		r=2.0*X1[d,d]
		# r=np.matmul(np.transpose(Xd),Xd)[0,0]
		if r==0:
			return 0
		D=-2.0*(np.matmul(X1[d,:],W)-Y1[d])
		# print(D.shape)
		# D=np.matmul(X,W)-Y-(Xd*W[d,0])
		# D=np.matmul(np.transpose(Xd),D)
		# print(D,D[0,0],D.shape)
		ans1=(-1.0*_lambda+D[0])/r
		ans2=(_lambda+D[0])/r
		if ans1>=0:
			return ans1
		elif ans2<0:
			return ans2
		else:
			return 0	# print(X1.shape)	# print(X1.shape)	# print(X1.shape)

	for _ in range(max_iter):
		for j in range(X.shape[1]):
			W[j,0]=lasso_grad_root(j,X,Y,W)
		
	return W
	

	

if __name__ == "__main__":
	# Do your testing for Kfold Cross Validation in by experimenting with the code below 
	X, Y = read_data("./dataset/train.csv")
	X, Y = preprocess(X, Y)
	trainX, trainY, testX, testY = separate_data(X, Y)
	
	# lambdas = [2*i for i in range(10)]
	# lambdas = [0,5,10,11,11.5,12,12.5,13.0,15,20,100]
	lambdas = [12.0,12.25,12.5,12.75,13.0] # Assign a suitable list Task 5 need best SSE on test data so tune lambda accordingly
	scores = k_fold_cross_validation(trainX, trainY, 6, lambdas, ridge_grad_descent)
	plot_kfold(lambdas, scores)
	# lambdas = [10**i for i in range(10)]
	lambdas = [0.5*i*10**5 for i in range(1,20)]
	scores = k_fold_cross_validation(trainX, trainY, 6, lambdas, coord_grad_descent)
	plot_kfold(lambdas, scores)