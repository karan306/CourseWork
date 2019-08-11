def decoder(List):
	Final=[]
	prev = 3
	for i in List:
		if i == prev:
			continue
		elif (i == 3 or i==2):
			prev=i
		else:
			Final.append(i)
			prev=i
	return Final

def nearer(x):
	diffs=map(lambda k: abs(k-x),constants.frequencies)


if __name__ == '__main__':
	print decoder([1,1,1,1,2,2,2,1,1,1,0,1,0,0,1,1,0,0,0,1,2,2,1,1])