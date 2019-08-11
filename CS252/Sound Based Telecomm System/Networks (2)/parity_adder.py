def parity_adder(List):
	List_len=len(List)
	List.extend([0]*(20-List_len))
	Ans=[]
	out = [[List[k],List[k+5],List[k+10],List[k+15]] for k in range(0,5)]
	Ans.extend(map(parity,out))
	out = [List[k:k+5] for k in range(0,20,5)]
	Ans.extend(map(parity,out))
	Ans.append(parity(List))
	return Ans

def parity(List):
	count =0
	for i in List:
		if i==1:
			count+=1
	if count%2==0 :
		return 0
	else:
		return 1

if __name__ == '__main__':
	print parity_adder([1,0,1,0,1,0,1,1])

