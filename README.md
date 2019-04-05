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
- Didalam fungsi Bangunmal


