#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>

int status;

void* masukinaux(void *temp){
    int file=*((int*)temp);
    if(file ==1)
    {
	status++;
	while(status!=2);
        system("ps -aux | head -11 > /home/thalutn5/Documents/modul3/soal4/FolderProses1/SimpanProses1.txt");
    }
    else if(file == 2)
    {
	status++;
	while(status!=2);
        system("ps -aux | head -11 > /home/thalutn5/Documents/modul3/soal4/FolderProses2/SimpanProses2.txt");
    }
}
void* rubahzip(void *temp){
    int file=*((int*)temp);
    if(file ==1)
    {
	status++;
	while(status!=4);
        system("cd /home/thalutn5/Documents/modul3/soal4/FolderProses1/; zip KompresProses1.zip SimpanProses1.txt");
	remove("/home/thalutn5/Documents/modul3/soal4/FolderProses1/SimpanProses1.txt");
    }
    else if(file == 2)
    {
	status++;
	while(status!=4);
        system("cd /home/thalutn5/Documents/modul3/soal4/FolderProses2/; zip KompresProses2.zip SimpanProses2.txt");
	remove("/home/thalutn5/Documents/modul3/soal4/FolderProses2/SimpanProses2.txt");
    }
}
void* rubahfile(void *temp){
    int file=*((int*)temp);    
    if(file ==1)
    {
	status++;
	while(status!=6);
	sleep(15);
        system("cd /home/thalutn5/Documents/modul3/soal4/FolderProses1/; unzip KompresProses1.zip");
    }
    else if(file == 2)
    {
	status++;
	while(status!=6);
	sleep(15);
        system("cd /home/thalutn5/Documents/modul3/soal4/FolderProses2/; unzip KompresProses2.zip");
    }
}

int main(){
    pthread_t tid1, tid2, tid3, tid4, tid5, tid6;
    int file1=1;
    int file2=2;
    int *p=&file1;
    int *q=&file2;
    //printf("p = %d q = %d", *p, *q);
    int a = pthread_create( &tid1, NULL, masukinaux, (void*) p);
    if(a!=0){
			fprintf(stderr,"Error - pthread_create() return code: %d\n",a);
			exit(EXIT_FAILURE);
		}
    int d = pthread_create( &tid4, NULL, masukinaux, (void*) q);
    if(d!=0){
			fprintf(stderr,"Error - pthread_create() return code: %d\n",d);
			exit(EXIT_FAILURE);
		}
	pthread_join(tid1, NULL);
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
    int b = pthread_create( &tid2, NULL, rubahzip, (void*) p);
    if(b!=0){
			fprintf(stderr,"Error - pthread_create() return code: %d\n",b);
			exit(EXIT_FAILURE);
		}

    int e = pthread_create( &tid5, NULL, rubahzip, (void*) q);
    if(e!=0){
			fprintf(stderr,"Error - pthread_create() return code: %d\n",e);
			exit(EXIT_FAILURE);
		}
    pthread_join(tid2, NULL);

    ///////////////////////////////////////////////////////////////////////////
    int c = pthread_create( &tid3, NULL, rubahfile, (void*) p);
    if(c!=0){
			fprintf(stderr,"Error - pthread_create() return code: %d\n",c);
			exit(EXIT_FAILURE);
		}
    int f = pthread_create( &tid6, NULL, rubahfile, (void*) q);
    if(f!=0){
			fprintf(stderr,"Error - pthread_create() return code: %d\n",f);
			exit(EXIT_FAILURE);
		}
    pthread_join(tid6, NULL);
    
}
