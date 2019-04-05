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


	
