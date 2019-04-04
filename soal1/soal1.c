#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<math.h>

void *faktorial(void* temp){

	int *angka=(int*)temp;//typecasting void ->int
	long long int hasilfaktorial = 1;
	for(int a = *angka; a > 0; a--)
	{hasilfaktorial=hasilfaktorial*a;}
	printf("%d! = %lld\n", *angka, hasilfaktorial);
}

int main(int argc, char *argv[]){
    int i = 0;
    int j, temp, angka[argc - 1];
    for(i = 1; i < argc; i++)
    {
	angka[i - 1] = atoi(argv[i]);
	//printf("%d ", angka[i]);
    }
    while(1)
    {
	int stop = 1;
	for(i = 1; i < argc - 1; i++)
	{
		if(angka[i] < angka[i-1])
		{
			stop = 0;
			temp = angka[i];
			angka[i] = angka[i - 1];
			angka[i - 1] = temp;
		}
	}
	if(stop)
	{break;}

    }
    /*for(i = 1; i < argc; i++)
    {
    	for(j = i; j < argc; j++)
	{
		if(angka[i] > angka[j])
		{
			temp=angka[j];
			angka[j] = angka[i];
			angka[i] = temp;		
		}	
	}
    }*/
    //for(i = 0; i < argc - 1; i++)
    //{printf("%d!\n", angka[i]);}
    pthread_t tid[256];
    for(i = 0; i < argc - 1; i++){
        pthread_create(&tid[i], NULL, faktorial, (void*)&angka[i]);
        pthread_join(tid[i],NULL);
    }
       
    return 0;
}
