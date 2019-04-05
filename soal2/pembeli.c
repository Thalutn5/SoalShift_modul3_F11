#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#define PORT 8181

int *stok;

void* printstok(void* argc){
	int num;
	while(1){
		//num=*(int*)argc;
		printf("Stok yang tersedia adalah %d\n", *stok);
		sleep(5);
	}
}

int main(int argc, char const *argv[]) {

    char beli[256];
    //int stok = 3;
    /*pthread_t tid;
    if(pthread_create(&tid, NULL, &printstok, &stok)){
    	printf("failed\n");
    	}*/

    key_t key = 1234;
    //int *stok;

    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    stok = shmat(shmid, NULL, 0);

    *stok = 3;
    pthread_t tid;
    pthread_create(&tid, NULL, &printstok, NULL);
       

    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    //char *hello = "Hello from server";
      
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

    char *hello1 = "transaksi berhasil\n";
    char *hello2 = "transaksi gagal\n";
    memset(beli,0,sizeof(beli));
    while((valread = read(new_socket, beli, 255)) != 0){
	if(*stok!=0){
		if(strcmp(beli, "beli")==0)
		{*stok=*stok-1;}
		//printf("transaksi berhasil\n");
		send(new_socket, hello1,strlen(hello1),0);
	}
	else{
		//printf("transaksi gagal\n");
		send(new_socket, hello2,strlen(hello2),0);
	}

	memset(beli,0,sizeof(beli));
   }
   shmdt(stok);
   shmctl(shmid, IPC_RMID, NULL);
}
