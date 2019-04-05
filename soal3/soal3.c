#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<math.h>

int WakeUp_Status;
int Spirit_Status;
int counter;
int counter2;
int trigger;
int trigger2;
void *bangunmal(){
	while(1){
		if(trigger == 1)
		{
			WakeUp_Status = WakeUp_Status + 15;
			//printf("WakeUP_Status + 15\n");
			counter++;
			trigger = 0;
		}
		if(counter2 == 3)
			{
				printf("Fitur Agmal Ayo Bangun Disabled 10 s\n");		
				sleep(10);
				trigger=0;
				counter2=0;
			}
	}
	

}
void *tidurraj(){
	while(1){
		if(trigger2 == 1)
		{
			Spirit_Status = Spirit_Status - 20;
			//printf("Spirit_Status - 20\n");
			counter2++;
			trigger2 = 0;
		}
		if(counter == 3)
		{
			printf("Fitur Iraj Ayo Tidur Disabled 10 s\n");
			sleep(10);
			trigger2=0;
			counter=0;
		}
	}
	
	
}
//void *begin(){

//}
int main(){
	int i, fitur;
	WakeUp_Status=0;
	Spirit_Status=100;
	pthread_t tid[256];
	pthread_create(&tid[0], NULL, &bangunmal, NULL);
	pthread_create(&tid[1], NULL, &tidurraj, NULL);
	//pthread_create(&tid[2], NULL, begin, NULL);
	while(1){
		if(WakeUp_Status >= 100)
		{
			printf("Agmal Terbangun, mereka bangun pagi dan berolahraga\n");
			exit(0);
		}
		else if(Spirit_Status <= 0)
		{
			printf("Iraj ikut tidur, dan bangun kesiangan bersama agmal\n");
			exit(0);
		}
		else{
			printf("Pilihlah Fitur-fitur dibawah ini :\n");
			printf("1. All Status \n");
			printf("2. Agmal Ayo Bangun \n");
			printf("3. Iraj Ayo Tidur \n");
			printf("Masukkan Pilihan fitur : \n");
			scanf("%d", &fitur);
			if(fitur == 1)
			{
				printf("WakeUp_Status = %d \n", WakeUp_Status);
				printf("Spirit_Status = %d \n\n", Spirit_Status);
			}
			if(fitur == 2)
			{
				trigger = 1;
				usleep(500);
			}	
			else if(fitur == 3)
			{
				trigger2 = 1;
				usleep(500);
			}
				
		}
	}	
	
	pthread_join(tid[0],NULL);
	pthread_join(tid[1],NULL);
	exit(1);
	return 0;
}
