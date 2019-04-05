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
	    }
