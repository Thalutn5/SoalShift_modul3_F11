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
		
- Kita juga membuat looping lagi sebanyak nilai yang kita inputkan, untuk mendapatkan nilai dari faktorial suatu angka tersebut dengan mempasing isi dari variabel angka tadi

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


	
