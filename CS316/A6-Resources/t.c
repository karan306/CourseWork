int i1,i2;
int func1(int,int,float);
float f1,f2;
int func2(int,float,int);
float func3(int p,float q,float r);
int func4(float a,float b,float c);
int f(int a);
int func1(int a,int b,float c){
	int x;
	i2=a;
	x = b;
	f2=c;
	x = 1;
	f2 = func3(1,0.1,0.2);
	x = func4(0.1,0.1,0.1);	
	return a;
}

int f(int a)
{
	int b;
	b =1;
	b =2;
	b = f(1);
	return 1;
}
int func4(float a,float b,float c){
	i1=4;
	func1(1,2,0.1);
	return i1+i1;
}



// int func2(float b,int i1){
// 	// a=a+10;
// 	i1=5;
// 	i1 = 3+1;
// 	b = 1.2;
// 	i1 = func4(1);
// 	return i1>2?i1:i2;
// 	// return ;
// }

// float func3(int a,float b,float c){
// 	b =b+f2;
// 	c=c+10.5;
// 	return b+c;
// }

void main(){
	int a,b;
	// a=f(1);
	// b=1;
	// a = func1(1+1,2,0.1);
	// b = func1(1,2,0.2);
	// a = func2(1,2.0,1);
	// a = func4(1);
	// print i2; print f2;
	// i2 = func4();
	// // print i1; print i2;
	// i2 = func2(i1,f2,i2);
	// // print i1; print i2;
	// f2 = func3(i1,f1,f2);
	// print f1; print f2;
	a = func4(1.1,2.2,3.3);
	print a;
	return ;
}