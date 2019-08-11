def detection(list):
	lm=list[-10:]
	par=list[:-10]
	bottom=par[:5]
	right=par[5:]
	m=[0]*(20-len(l))
	l=lm.append(m)
	l1=l[0:5]
	l2=l[5:10]
	l3=l[10:15]
	l4=l[15:20]
	l=[l1,l2,l3,l4]
	[c_bottom,c_right]=par_gen(l)
	
	c=0
	
	bl=lis_com(bottom,c_bottom)
	rl=lis_com(right[0:4],c_right[0:4])
	b=len(bl)
	r=len(rl)

	if(parity(bottom)==right[4] and parity(right[0:4])==right(4)):
		c=0
	else:
		c=1

	if(b==1 and r==1 and c==0 ):
		if((bl[0]+rl[0]*5)<len(lm)):
			lm[bl[0]+rl[0]*5]=not lm[bl[0]+rl[0]*5] 
		return [0]+lm
	elif(b==0 and r==0 and c==1):
		return [0]+lm
	elif((b==0 and r==2 and c==0) or (b==2 and r==0 and c==0)):
		return [0]+lm
	else:
		return [1,1]

def lis_com(l1,l2):
	error=[]
	if len(l1)==len(l2):
		n=len(l1)
		p=range(0,n)
		for x in p:
			if(l1[x]!=l2[x]):
				error.append(x)

	return error



def parity(x):
	return sum(x)%2

def par_gen(a):
	right=map(lambda x: parity(x),a)
	a_=zip(*a[::1])
	bottom=map(lambda x: parity(x),a_)
	right.append(parity(bottom))
	return [bottom,right]