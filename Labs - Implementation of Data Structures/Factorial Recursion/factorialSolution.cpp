int factorial(int * pn){
	
	int f = 1;
	
	for (int i = 1; i <= *pn; i++){
		f *= i;
	}
	
	return f;
	
}

//Alternative solution
/*

int fact_rec(int n){
	if (n==1) return 1;
	
	return n*fact_rec(n-1);
}

int factorial(int * pn){
	
	return fact_rec(*pn);
	
}

*/
