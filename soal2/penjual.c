#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <pthread.h>
#define PORT 8080

int *stok;
void* printstok(void *argc){
	int num;
	while(1){
		//num=*(int*)argc;
		printf("Stok yang tersedia adalah %d\n", *stok);
		sleep(5);
	}
}

int main(int argc, char const *argv[]) {
    char tambah[256];
    //int stok = 0;
            pthread_t tid;
        key_t key = 1234;
        //int *stok;

        int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
        stok = shmat(shmid, NULL, 0);
        *stok=3;
        pthread_create(&tid, NULL, &printstok, &stok);
        //printf("failed\n");
        

    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "Hello from server";
      
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
  
    //printf("tes\n");
    
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    //printf("tes\n");

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    //printf("tes\n");

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    //printf("tes\n");
   	/*pthread_t tid;
	key_t key = 1234;
        //int *stok;

        int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
        stok = shmat(shmid, NULL, 0);
	*stok=3;
	if(pthread_create(&tid, NULL, &printstok, &stok)){
        printf("failed\n");
        }*/

    memset(tambah,0,sizeof(tambah));
    while((valread = read(new_socket, tambah, 255)) != 0){
	if(strcmp(tambah, "tambah")==0)
	{*stok=*stok+1;;}
	memset(tambah,0,sizeof(tambah));
    }
	shmdt(stok);
        shmctl(shmid, IPC_RMID, NULL);
}
