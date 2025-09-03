#include <stdio.h>

int main(){
	int pares[10];
	int i;
	int ultimo;
	long nCuenta;
	
	for(i=0; i<10; i++){
		pares[i]=(i+1)*2;
	}
	for(i=9; i>=0; i--){
		printf("%d ",pares[i]);
	}
	printf("\nNumero de cuenta:424087214\n");
	
	for(i=9; i>5; i--){
		printf("%d ",pares[i]);
	}
	pares[3]=-1;
	printf("%d ",pares[3]);
	pares[3]=8;
	for(i=4; i>=0; i--){
		printf("%d ",pares[i]);
	}
	
	//segunda parte
	printf("\n\nIngresa el numero de cuenta: ");
	scanf("%ld",&nCuenta);
	ultimo=nCuenta % 10;
	for(i=0; i<10; i++){
		pares[i]=(i+1)*2;
	}
	
	if(ultimo>=0 || ultimo<10){
		pares[ultimo]=-1;
	}
	for(i=0; i<10; i++){
		printf("%d ",pares[i]);
	}
	
	
	
	return 0;
}
