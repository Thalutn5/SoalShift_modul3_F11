# SoalShift_modul3_F11

# Nomor1
Buatlah program C yang bisa menghitung faktorial secara parallel lalu menampilkan hasilnya secara berurutan
Contoh:
./faktorial 5 3 4
	
	3! = 6
	4! = 24
	5! = 120
Jawab :

- Untuk mengerjakan soal dibawah ini, kami menggunakan sebuah argumen
- Didalam fungsi utama kami menggunakan parameter (int argc, char *argv[]) 
- Lalu kami juga mendeklarasikan variabel i, j, temp, angka[argcc-1]

    	int i = 0;
    	int j, temp, angka[argc - 1]; //karena argc memulai dari indeks 1
	
- Lalu kami membuat for agar memasukkan inputan kedalam variabel array angka tadi

	    for(i = 1; i < argc; i++)
	    {
		angka[i - 1] = atoi(argv[i]);
		//printf("%d ", angka[i]);
		
- Setelah mendapatkan angka yang kita inputkan tadi, kami akan mensorting angka tersebut dari kecil ke besar mengunakan bubble sorting

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
- Lalu kita membuat thread dengan nama tid

		pthread_t tid[256];
		
- Kita juga membuat looping lagi sebanyak nilai yang kita inputkan, untuk mendapatkan nilai dari faktorial suatu angka tersebut dengan mempasing isi dari variabel angka tadi dengan membuat thread dan menjoinkannya

		for(i = 0; i < argc - 1; i++){
			pthread_create(&tid[i], NULL, faktorial, (void*)&angka[i]);
			pthread_join(tid[i],NULL);
		    }
		    
- Didalam Fungsi faktorial, pertama-tama saya mentypecasting dari void menjadi integer dan mendeklarasikan sebuah variabel dengan tipe long long int dengan nama hasilfaktorial

		int *angka=(int*)temp;//typecasting void ->int
		long long int hasilfaktorial = 1;
		
- Setelah itu kita membuat looping yang berisikan mencari nilai faktorial dari suatu angka

		for(int a = *angka; a > 0; a--)
		{hasilfaktorial=hasilfaktorial*a;}
		
- Dan yang terakhir adalah ngeprint hasil dari nilai faktorial tersebut

		printf("%d! = %lld\n", *angka, hasilfaktorial);
		
# Nomor 2
Pada suatu hari ada orang yang ingin berjualan 1 jenis barang secara private, dia memintamu membuat program C dengan spesifikasi sebagai berikut:

a. Terdapat 2 server: server penjual dan server pembeli

b. 1 server hanya bisa terkoneksi dengan 1 client

c. Server penjual dan server pembeli memiliki stok barang yang selalu sama

d. Client yang terkoneksi ke server penjual hanya bisa menambah stok

	- Cara menambah stok: client yang terkoneksi ke server penjual mengirim string “tambah” ke server lalu stok bertambah 1

e. Client yang terkoneksi ke server pembeli hanya bisa mengurangi stok

	- Cara mengurangi stok: client yang terkoneksi ke server pembeli mengirim string “beli” ke server lalu stok berkurang 1

f. Server pembeli akan mengirimkan info ke client yang terhubung dengannya apakah transaksi berhasil atau tidak berdasarkan ketersediaan stok

	- Jika stok habis maka client yang terkoneksi ke server pembeli akan mencetak “transaksi gagal”
	
	- Jika stok masih ada maka client yang terkoneksi ke server pembeli akan mencetak “transaksi berhasil”

g. Server penjual akan mencetak stok saat ini setiap 5 detik sekali

h. Menggunakan thread, socket, shared memory

Jawab :

# Pada Penjual

- Pertama-tama kami mengopas template server lalu kita membuat variabel global yang bernama stok

	  int *stok;
	 
- Setelah itu di dalam fungsi utama kita membuat varibel char dan membuat variabel thread

	  pthread_t tid;
	  pthread_create(&tid, NULL, &printstok, &stok);
	  char tambah[256];
	 
- Kita juga mengisikan isi dari varabel stok dengan angka 3

	  *stok = 3;
	  
	  
- Kita juga perlu menggunakan shared memory pada kodingan ini agar isi dari variabel stok sama dengan variabel stok pada pembeli

	  key_t key = 1234;
          int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
          stok = shmat(shmid, NULL, 0);

- Lalu kita mereset memory pada variabel tambah agar isinya tidak tersangkut pada itu itu saja

	  memset(tambah,0,sizeof(tambah));
	 
- Lalu kita membuat looping dengan syarat varlread tidak sama dengan 0 maka jika string yang diinputkan pada client1 adalah "tambah" maka stok akan bertambah 1 serta tidak lupa untuk mereset memory pada variabel tambah agar isinya tidak tersangkut pada itu itu saja

    	  while((valread = read(new_socket, tambah, 255)) != 0){
	  if(strcmp(tambah, "tambah")==0)
	  {*stok=*stok+1;;}
	   memset(tambah,0,sizeof(tambah));
	 
- Isi dari fungsi printstok adalah kita membuat looping yang mengeluarkan sebuah output yang berisi isi stok selama kurun waktu 5 detik

	  while(1){	
		printf("Stok yang tersedia adalah %d\n", *stok);
		sleep(5);
	  }
- Kita juga perlu menambahkan bagian akhir pada shared memory pada bagian akhir fungsi utama

	  shmdt(stok);
          shmctl(shmid, IPC_RMID, NULL);

# Pada Pembeli

- Hampir sama dengan penjual, Pertama-tama kami mengopas template server lalu kita membuat variabel global yang bernama stok

	  int *stok;
	 
- Setelah itu di dalam fungsi utama kita membuat varibel char dan membuat variabel thread

	  pthread_t tid;
	  pthread_create(&tid, NULL, &printstok, &stok);
	  char beli[256];
	  
- Kita juga mengisikan isi dari varabel stok dengan angka 3

	  *stok = 3;
	  
- Kita juga perlu menggunakan shared memory pada kodingan ini agar isi dari variabel stok sama dengan variabel stok pada pembeli

	  key_t key = 1234;
          int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
          stok = shmat(shmid, NULL, 0);

- Lalu kita mereset memory pada variabel tambah agar isinya tidak tersangkut pada itu itu saja

	  memset(tambah,0,sizeof(tambah));

- Kami juga membuat 2 variabel char pointer yang menampung "transaksi berhasil" dan "transaksi gagal"
    
    	  char *hello1 = "transaksi berhasil\n";
    	  char *hello2 = "transaksi gagal\n";
	
- Lalu kita mereset memory pada variabel beli agar isinya tidak tersangkut pada itu itu saja

    	memset(beli,0,sizeof(beli));
    
- Lalu kita membuat looping dengan syarat varlread tidak sama dengan 0 maka jika string yang diinputkan pada client2 adalah "beli" maka stok akan berkurang 1 serta jika stok tidak sama dengan nol maka dia akan mengirimkan pesan kepada client2 dengan tulisan transaksi berhasil. Jika stok sama dengan nol maka akan mengiimkan pesan transaksi gagal. Tidak lupa juga untuk mereset memory pada variabel beli agar isinya tidak tersangkut pada itu itu saja

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
- Kita juga perlu menambahkan bagian akhir pada shared memory pada bagian akhir fungsi utama	

      shmdt(stok);
      shmctl(shmid, IPC_RMID, NULL);	
   
 # Pada Client1
 
 - Setelah kita mengcopas tempalte client kita tinggal menambahkan beberapa syntax
 - Kita membuat ebuah variabel char bernama tambah
 
       char tambah[256];
    
 - Lalu kita membuat looping dimana isinya adalah menginputkan suatu string dan mengirim string tadi menuju Penjual
       
       while(1){
	   scanf("%s", tambah);//menginputkan sebuah variabel
	   send(sock, tambah, strlen(tambah),0);;//mengirim pesan isi dari string yg diinputkan
	   memset(tambah,0,sizeof(tambah));//seperti sebelumnya yaitu mereset variabel tambah
       }
       
 # Pada Client2
	
 - Setelah kita mengcopas tempalte client kita tinggal menambahkan beberapa syntax
 - Kita membuat ebuah variabel char bernama beli
 
       char beli[256];
       
 - Lalu kita membuat looping dimana isinya adalah menginputkan suatu string dan mengirim string tadi menuju Pembeli
 
       while(1){
	   scanf("%s", beli);//menginputkan sebuah variabel
	   send(sock, beli, strlen(beli),0);//mengirim pesan isi dari string yg diinputkan
	   valread = read(sock, buffer,1024);//menerima pesan
	   printf("%s", buffer);//mengeluarkan sebuah output berupa transaksi gagal/berhasil
	   memset(buffer,0,sizeof(buffer));//seperti sebelumnya yaitu mereset variabel buffer 
	   memset(beli,0,sizeof(beli));//seperti sebelumnya yaitu mereset variabel beli
      }

# Nomor 3
Agmal dan Iraj merupakan 2 sahabat yang sedang kuliah dan hidup satu kostan, sayangnya mereka mempunyai gaya hidup yang berkebalikan, dimana Iraj merupakan laki-laki yang sangat sehat,rajin berolahraga dan bangun tidak pernah kesiangan sedangkan Agmal hampir menghabiskan setengah umur hidupnya hanya untuk tidur dan ‘ngoding’. Dikarenakan mereka sahabat yang baik, Agmal dan iraj sama-sama ingin membuat satu sama lain mengikuti gaya hidup mereka dengan cara membuat Iraj sering tidur seperti Agmal, atau membuat Agmal selalu bangun pagi seperti Iraj. Buatlah suatu program C untuk menggambarkan kehidupan mereka dengan spesifikasi sebagai berikut:

a. Terdapat 2 karakter Agmal dan Iraj

b. Kedua karakter memiliki status yang unik

	- Agmal mempunyai WakeUp_Status, di awal program memiliki status 0
	- Iraj memiliki Spirit_Status, di awal program memiliki status 100
	- Terdapat 3 Fitur utama :
		+ All Status, yaitu menampilkan status kedua sahabat
		+ “Agmal Ayo Bangun” menambah WakeUp_Status Agmal sebesar 15 point
		+ “Iraj Ayo Tidur” mengurangi Spirit_Status Iraj sebanyak 20 point
	- Terdapat Kasus yang unik dimana:
		+ Jika Fitur “Agmal Ayo Bangun” dijalankan sebanyak 3 kali, maka Fitur “Iraj Ayo Tidur” Tidak bisa dijalankan selama 10 		Detik (Dengan mengirim pesan ke sistem “Fitur Iraj Ayo Tidur disabled 10 s”)
		+ Jika Fitur  “Iraj Ayo Tidur” dijalankan sebanyak 3 kali, maka Fitur “Agmal Ayo Bangun” Tidak bisa dijalankan selama 10 		detik (Dengan mengirim pesan ke sistem “Agmal Ayo Bangun disabled 10 s”)
	- Program akan berhenti jika Salah Satu :
		+ WakeUp_Status Agmal >= 100 (Tampilkan Pesan “Agmal Terbangun,mereka bangun pagi dan berolahraga”)
		+ Spirit_Status Iraj <= 0 (Tampilkan Pesan “Iraj ikut tidur, dan bangun kesiangan bersama Agmal”)
	- Syarat Menggunakan Lebih dari 1 Thread
Jawab :
 - Pertama-tama kami membuat sebuah variabel global untuk mempasing sebuah nilai nantinya 
 
		int WakeUp_Status;
		int Spirit_Status;
		int counter;
		int counter2;
		int trigger;
		int trigger2;
- Lalu didalam fungsi utama kita mendeklarasikan variabel i dan fitur. Serta mendeklarasikan isi dari variabel WakeUp_Status dan Spirit status. Kami juga membuat sebuah 2 thread dengan nama bangunmal dan tidurraj

		int i, fitur;
		WakeUp_Status=0;
		Spirit_Status=100;
		pthread_t tid[256];
		pthread_create(&tid[0], NULL, &bangunmal, NULL);
		pthread_create(&tid[1], NULL, &tidurraj, NULL);
		
- Setelah kami membuat looping dengan while selama ia bernilai true maka ia akan terus looping
- Isi dari looping tersebut mengecek apakah WakeUp_Status itu lebih besar sama dengan 100 atau tidak dan mengecek apakah Spirit_Status itu kurang dari sama dengan 0, kalo ya maka masuk kedalam if dan else if tersebut

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
- Jika tidak masuk kedalam if dan else if tersebut maka akan memasuki else dimana isinya adalah pilihan-pilihan fitur yang harus kita pilih

			printf("Pilihlah Fitur-fitur dibawah ini :\n");
			printf("1. All Status \n");
			printf("2. Agmal Ayo Bangun \n");
			printf("3. Iraj Ayo Tidur \n");
			printf("Masukkan Pilihan fitur : \n");
			scanf("%d", &fitur);
			
- Setelah kita menginputkan 1 pada scanf diatas maka akan memasuki if dimana dia akan ngeprint isi dari variabel WakeUp_Status dan Spirit_Status

			if(fitur == 1)
			{
				printf("WakeUp_Status = %d \n", WakeUp_Status);
				printf("Spirit_Status = %d \n\n", Spirit_Status);
			}	
- Dan misalnya yang dipilih adalah 2 dan 3 maka dia akan menset isi dari variabel trigger dan trigger2 menjadi 1 serta mensleep selama 0.5 detik.

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
- Didalam fungsi Bangunmal kita membuat looping dengan while, isi dari while tersebut adalah

		if(trigger == 1) //jika triggernya 1 maka masuk kedalam if ini yang bertujuan untuk menaikkan nilai dari WakeUp_Status
		{
			WakeUp_Status = WakeUp_Status + 15;
			counter++; //agar bisa menilai bahwa if ini sudah berapa kali dilakukan
			trigger = 0;
		}
		if(counter2 == 3) //jika counter2 atau fungsi tidurraj sudah dijalankan 3 kali maka akan memasuki if ini
			{
				printf("Fitur Agmal Ayo Bangun Disabled 10 s\n"); //akan mengeluarkan pesan 
				sleep(10); // dan sleep selama 10 detik
				trigger=0;
				counter2=0;
			}
- Didalam fungsi tidurraj kita membuat looping dengan while, isi dari while tersebut adalah

		if(trigger2 == 1)//jika trigger2nya 1 maka masuk kedalam if ini yang bertujuan untuk mengurangi nilai dari Spirit_Status
		{
			Spirit_Status = Spirit_Status - 20;
			counter2++;
			trigger2 = 0;
		}
		if(counter == 3) //jika counter atau fungsi bangunmal sudah dijalankan 3 kali maka akan memasuki if ini
		{
			printf("Fitur Iraj Ayo Tidur Disabled 10 s\n");//akan mengeluarkan pesan 
			sleep(10); // dan sleep selama 10 detik
			trigger2=0;
			counter=0;
		}
		
- Dan tidak lupa untuk menjoinkan kedua thread tadi pada fungsi utamanya

		pthread_join(tid[0],NULL);
		pthread_join(tid[1],NULL);
		
- Kesusahan pada soal ini adalah kurang telitinya jalan pada kodingan ini sehingga menimbulkan beberapa error dan yang tadi saat salah satu antara fitur 2 dan 3 dijalanan 3 kali maka salah satu dari mereka berdua akan disabled selama 10 detik, saya sempet mengalami error dimana yang saya buat itu tidak mendisabled salah satu fiturnya melainkan hanya menunda saja, untuk masalah ini saya mengisikan isi dari variabel trigger dan trigger2 dengan angka 0 pada if kedua di kedua fungsi setelah sleep 10.


# Nomor 4
Buatlah sebuah program C dimana dapat menyimpan list proses yang sedang berjalan (ps -aux) maksimal 10 list proses. Dimana awalnya list proses disimpan dalam di 2 file ekstensi .txt yaitu  SimpanProses1.txt di direktori /home/Document/FolderProses1 dan SimpanProses2.txt di direktori /home/Document/FolderProses2 , setelah itu masing2 file di  kompres zip dengan format nama file KompresProses1.zip dan KompresProses2.zip dan file SimpanProses1.txt dan SimpanProses2.txt akan otomatis terhapus, setelah itu program akan menunggu selama 15 detik lalu program akan mengekstrak kembali file KompresProses1.zip dan KompresProses2.zip 
Dengan Syarat : 
- Setiap list proses yang di simpan dalam masing-masing file .txt harus berjalan bersama-sama
- Ketika mengkompres masing-masing file .txt harus berjalan bersama-sama
- Ketika Mengekstrak file .zip juga harus secara bersama-sama
- Ketika Telah Selesai melakukan kompress file .zip masing-masing file, maka program akan memberi pesan “Menunggu 15 detik untuk mengekstrak kembali”
- Wajib Menggunakan Multithreading
- Boleh menggunakan system
Jawab :

- Pertama-tama kita membuat sebuah variabel global bernama status 

		int status;
	
- Setelah itu didalam fungsi utamanya kami mendeklarasikan beberapa variabel seperti variabel dibawah ini :

		 pthread_t tid1, tid2, tid3, tid4, tid5, tid6;
	    	 int file1=1;
	    	 int file2=2;
	  	 int *p=&file1;
	    	 int *q=&file2;
		 
- Lalu kami membuat 2 thread yang berguna untuk memasukan ps -aux kedalam 2 file tersebut
		
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
		
- Kami juga membuat 2 thread yang berguna nantinya untuk menzipkan dan menghapus file tersebut

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
	  
- Setelah itu kita juga membuat 2 thread yang berguna nantinya untuk mengunzip file tersebut

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
	 
- Lalu pada fungsi masukinaux kami membuat if dan else if dimana if ditujukan untuk file SimpanProses1.txt sedangkan else if ditujukan kepada file SimpanProses2.txt

	  if(file ==1)
    	  {
	   	 status++; //sebagai penghitung plus 1
		 while(status!=2); //untuk menunggu agar status=2 sehingga bisa dijalankan bersama-sama
        	 system("ps -aux | head -11 > /home/thalutn5/Documents/modul3/soal4/FolderProses1/SimpanProses1.txt");
		 //mengambil ps -aux sebanyak 10 baris lalu disimpan di file SimpanProses1.txt
    	  }
    	  else if(file == 2)
     	  {
		status++; //sebagai penghitung plus 1
		while(status!=2); //untuk menunggu agar status=2 sehingga bisa dijalankan bersama-sama
        	system("ps -aux | head -11 > /home/thalutn5/Documents/modul3/soal4/FolderProses2/SimpanProses2.txt");
		//mengambil ps -aux sebanyak 10 baris lalu disimpan di file SimpanProses2.txt
     	  } //maka status = 2

- Setelah itu pada fungsi rubahzip kami membuat if dan else if dimana if ditujukan untuk file SimpanProses1.txt sedangkan else if ditujukan kepada file SimpanProses2.txt

	  int file=*((int*)temp);
    	  if(file ==1)
    	  {
		 status++; //sebagai penghitung plus 1
		 while(status!=4); //untuk menunggu agar status=4 sehingga bisa dijalankan bersama-sama
        	 system("cd /home/thalutn5/Documents/modul3/soal4/FolderProses1/; zip KompresProses1.zip SimpanProses1.txt");
		 //mengekstrak SimpanProses1.txt
		 remove("/home/thalutn5/Documents/modul3/soal4/FolderProses1/SimpanProses1.txt");
		 //mendelete SimpanProses1.txt
    	  }
    	  else if(file == 2)
    	  {
		 status++; //sebagai penghitung plus 1
	 	 while(status!=4); //untuk menunggu agar status=4 sehingga bisa dijalankan bersama-sama
        	 system("cd /home/thalutn5/Documents/modul3/soal4/FolderProses2/; zip KompresProses2.zip SimpanProses2.txt");
		  //mengekstrak SimpanProses2.txt
		 remove("/home/thalutn5/Documents/modul3/soal4/FolderProses2/SimpanProses2.txt");
		 //mendelete SimpanProses2.txt
    	  }
	
- Dan yang terakhir adalah fungsi rubahfile

    	  if(file ==1)
    	  {
		status++; //sebagai penghitung plus 1
		while(status!=6);  //untuk menunggu agar status=6 sehingga bisa dijalankan bersama-sama
		sleep(15); //disleep agar menjalankan unzip 15 detik setelah mengektrak file tadi
        	system("cd /home/thalutn5/Documents/modul3/soal4/FolderProses1/; unzip KompresProses1.zip");//mengunzip file .zip tadi
    	  }
    	  else if(file == 2)
    	  {
		status++; //sebagai penghitung plus 1
		while(status!=6);  //untuk menunggu agar status=6 sehingga bisa dijalankan bersama-sama
		sleep(15); //disleep agar menjalankan unzip 15 detik setelah mengektrak file tadi
        	system("cd /home/thalutn5/Documents/modul3/soal4/FolderProses2/; unzip KompresProses2.zip");//mengunzip file .zip tadi
    	  }
	  
# Nomor 5 

Seperti dengan yang ada di soal, untuk mengerjakan nomor 5 kami menggunakan 2 kodingan. yang 1 sebagai kodingan utama sedangkan yang kedua sebagai shop

# Pada Kodingan soal5.c

- Pertama-tama kami membuat struct yang bernama monster yang berisikan monsterName, monsterHunger, monsterHealth, monsterHygiene, monsterFoodstock, dan monsterBathTimer. Selain itu kami juga membuat variabel global yang bernama monsterMaxHunger dengan isinya 200, monsterMaxhygiene dengan isinya 100, monsterMaxHealth 300 dan enemyHealth 100. Kita juga membuat variabel bernama gameState, gameOver, *foodStock, dan inputTemp.

		struct monster
		{
		    char monsterName[100];
		    int monsterHunger;
		    int monsterHealth;
		    int monsterHygiene;
		    int monsterFoodStock;
		    int monsterBathTimer;
		};

		struct monster *monstat;

		int monsterMaxHunger = 200;
		int monsterMaxHygiene = 100;
		int monsterMaxHealth = 300;
		int enemyHealth = 100;

		int gameState;
		int gameOver;
		int *foodStock;
		char inputTemp;
		
- Setelah itu kami menggunakan fungsi *render yang berguna untuk menginputkan suatu angka tanpa perlu mengetikkan enter
- Ada fungsi Hunger yang berfungsi untuk mengurangi poin hunger sebanyak 5 selama 5 detik
- Yang kedua ada fungsi hygiene yang berfungsi untuk mengurangi pion hygiene 10 setiap 30 detik
- Yang ketiga ada fungsi bath yang berfungsi sebagai timer dalam monsterBathTimer
- Dan yang terakhir ada fungsi regen yang berfungsi untuk menambah heatlh monster kita sebanyak 5 poin selama 10 detik
- Disini kami menggunakan shared memory pada variabel stok makanannya, lalu membuat thread tid1 sampai tid7. Lalu memasukkan variabel monterHealth, monsterHunger, dan monsterHygiene dengan maksimalnya. 

		key_t key = 4242;
		    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0777);
		    foodStock = shmat(shmid, NULL, 0);

		    gameState = 0;
		    gameOver = 0;

		    pthread_t tid1, tid2, tid3, tid4, tid5, tid6, tid7;
		    monstat = malloc(sizeof(struct monster));

		    monstat->monsterHealth = monsterMaxHealth;
		    monstat->monsterHunger = monsterMaxHunger;
		    monstat->monsterHygiene = monsterMaxHygiene;

- Lalu kita menginputkan nama monsternya

		    system("clear");
		    printf("Enter your desired name for your monster (1 word pls) : \n");
		    scanf("%s", monstat->monsterName);

		    printf("Great! your monster's name is %s \n", monstat->monsterName);
		    sleep(3);

		    system("clear");
		    
- Kita membuat while, dan jika gamestate=0 maka pada if pertama jika kita menginputkan angka 1 maka monster kita akan makan, selama makanan(Foodstock) kita masih tersedia. 
- Pada else if, jika kita menginputkan angka 2 maka monster kita akan mandi dan menambahkan isi dari variabel monsterHygiene dan tidak bisa menjalankannya lagi selama 20 detik
- Pada else if yang kedua, jika menginputkan angka 3 maka akan memasuki fase battle dan menggantikan isi dari variabel gamestate menjadi 1
- Pada else if yang ketiga, jika kita menginputkan angka 4 maka memasuki shop untuk menaikkan foodstock 
- Pada else if yang terakhir, jika kita  menginputkan angka 5 maka kita akan keluar dari game
- Jika Gamestate=1 maka mnster kita akan memasuki battle dimana kita bisa menyerang musuh atau kabur dari battle
- dan jika Gamestate=2 maka monster kita akan memasuki toko yang berguna untuk menambah foodstok dan keluar dari toko
- Dan tdak lupa untuk menggunakan shared memory pada variabel foodstock
- pada fungsi render yang kedua berfungsi untuk menampilkan printf-printf yang mengeluarkan output berupa fitur-fitur yang diinginkan

# Pada Kodingan soal5_shop.c

Pada kodingan ini kami mengopaskan template dari shared memory dan mengganti gantinya sedikit.
- Pada fungsi utamanya kami membuat sebuah fungsi yang bernama render yang bertujuan untuk mengeluarkan fitur-fitur yang tersedia pada shop.

		void *renderFunction(){
		    while(1){
			printf("FoodShop\n");
			printf("Food stock : %d\n", *foodStock);
			printf("Choices\n1. Restock\n2. Exit\n");
			sleep(1);
			system("clear");
		    }
		}

- Lalu kami membuat suatu while dimana jika kita menginputkan angka 1 maka foodstock akan bertambah 1 dan jika kita menginputkan angka 2 maka program akan dihentikkan

		    while(gameOver != 1){
			inputTemp = getch();
			if(inputTemp == '1'){
			    system("clear");
			    printf("added one food to the stock!\n");
			    *foodStock += 1;
			}
			else if(inputTemp == '2'){
			    gameOver = 1;
			}
		    }
		  
Kesusahan pada pengerjaan soal ini adalah soalnya banyak, jadi agak pusing ngeliatnya kalo ga ditulis ulang. Lalu sering terjadinya kesalahan dalam berfikir mana yang harus dilakukan mana yang selanjutnya dilakukan. Untuk menyelesaikan permasalahn tadi lebih fokus aja sih dalam berfikir agar tidak membuang-buang waktu pengerjaan.
