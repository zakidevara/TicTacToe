#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<windows.h>
#include<time.h>
#define panjang 6000

#define BLACK           0
#define DARK_BLUE       1
#define GREEN           2
#define TURQUOISE       3
#define DARK_RED        4
#define PURPLE          5
#define FOREST_GREEN    6
#define LIGHT_GRAY      7
#define GRAY            8
#define BLUE            9
#define LIGHT_GREEN    10
#define LIGHT_BLUE     11
#define RED            12
#define PINK           13
#define YELLOW         14
#define WHITE          15
#define STDALERT      140
#define STDHEADER     143
#define STDBACKGROUND 159

const int O = 0, X = 1, kosong = 3;
const int hard = 3, normal = 4;
void menu();
void permainanKomputer(const int);
void permainanPlayer();

void warnateks(int warna) //modul yang berfungsi untuk memberi warna ke karakter
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, warna);
}

void inisialisasi(int *board) //modul untuk memberi nilai awal ke array board
{
	int i = 0;
	for(i=0; i<25; i++){
		board[i]=kosong;
	}
}

void gotoxy(int x, int y) //modul untuk memfungsikan fungsi gotoxy
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput,dwCursorPosition);
}

void xo(){ //memberi logo x dan o
	warnateks(LIGHT_GREEN);
	gotoxy(9,8); printf("??       ?? \n");
	gotoxy(9,9); printf("  ??   ?? \n");
	gotoxy(9,10); printf("    ??? \n");
	gotoxy(9,11); printf("    ??? \n");
	gotoxy(9,12); printf("  ??   ?? \n");
	gotoxy(9,13); printf("??       ?? \n");
	gotoxy(9,15);printf(" COMPUTER \n");
	warnateks(YELLOW);
	gotoxy(61,8); printf("    ????  \n");
	gotoxy(61,9); printf("  ??    ?? \n");
	gotoxy(61,10); printf("  ??    ?? \n");
	gotoxy(61,11); printf("  ??    ?? \n");
	gotoxy(61,12); printf("  ??    ?? \n");
	gotoxy(61,13); printf("    ???? \n");
	gotoxy(61,15);printf("    USER   \n");
}

void tampilan_board(const int *board) //modul untuk menampilkan array board ke layar
{
	int i = 0;
	char kar[] = "OX|_";
	xo();
	for(i=0; i<25; i++){
		if(i!=0 && i%5==0){
			printf("\n\n\n"); //memberi spasi untuk setiap baris
		}

		if(i%5 == 0){
			printf("\t\t\t");
		}

		if(board[i] == 0){
			warnateks(YELLOW); //memberi warna kuning ke karakter "O"
			printf("%6c", kar[board[i]]);
		}else if(board[i] == 1){
			warnateks(LIGHT_GREEN);  //memberi warna hijau ke karakter "X"
			printf("%6c", kar[board[i]]);
		}else{
			warnateks(WHITE);  //memberi warna putih ke karakter selain "X" "O"
			printf("%6d", i+1);
		}
	}
}

void tampilan_board_akhir(const int *board) //menampilkan kondisi array board terakhir setelah permainan selesai
{
	int i=0;
	char kar[] = "OX|_";
	printf("\n\n");
	warnateks(LIGHT_GREEN);
	xo();
	for(i=0; i<25; i++){
		if(i!=0 && i%5==0){
			printf("\n\n\n");
		}

		if(i%5 == 0){
			printf("\t\t\t");
		}

		if(board[i] == 0){
			warnateks(YELLOW);
			printf("%6c", kar[board[i]]);
		}else if(board[i] == 1){
			warnateks(LIGHT_GREEN);
			printf("%6c", kar[board[i]]);
		}else if(board[i] == 3){
			warnateks(WHITE);
			printf("%6c", kar[board[i]]);
		}
	}
	printf("\n\n");
}

void judul()//sebagai tampilan awal program
{
	warnateks(LIGHT_BLUE);
	gotoxy(8,1); printf("  ??????????  ??   ?????             ??????????   ????    ????? \n");
	printf("              ??      ??  ??                     ??      ??  ??  ??     \n");
	printf("              ??      ??  ??                     ??      ??  ??  ??     \n");
	printf("              ??      ??  ??                     ??      ??????  ??     \n");
	printf("              ??      ??  ??                     ??      ??  ??  ??     \n");
	printf("              ??      ??   ?????                 ??      ??  ??   ????? \n \n\n\n");

	printf("      		           ??????????  ?????   ????? \n");
	printf("	 	               ??     ??   ??  ?     \n");
	printf("		               ??     ??   ??  ????? \n");
	printf("		               ??     ??   ??  ? \n");
	printf("                               ??     ??   ??  ?     \n");
	printf("		               ??      ?????   ????? \n");

	warnateks(LIGHT_GREEN);
	gotoxy(9,18); printf("??       ?? \n");
	gotoxy(9,19); printf("  ??   ?? \n");
	gotoxy(9,20); printf("    ??? \n");
	gotoxy(9,21); printf("    ??? \n");
	gotoxy(9,22); printf("  ??   ?? \n");
	gotoxy(9,23); printf("??       ?? \n");
	warnateks(YELLOW);
	gotoxy(61,18); printf("    ????  \n");
	gotoxy(61,19); printf("  ??    ?? \n");
	gotoxy(61,20); printf("  ??    ?? \n");
	gotoxy(61,21); printf("  ??    ?? \n");
	gotoxy(61,22); printf("  ??    ?? \n");
	gotoxy(61,23); printf("    ???? \n");
}

void kecepatan(float seconds){// memberi interval waktu dalam satuan detik
	clock_t endwait;
	endwait=clock()+seconds*CLOCKS_PER_SEC;
	while(clock()<endwait){};
}

void loading()//modul untuk menapilkan tampilan loading
{
	int x = 28, y = 13, n;
	warnateks(WHITE);
	gotoxy(x,20); printf("       Please Wait");
	gotoxy(x,21);  printf("??????????????????????????");
	gotoxy(x,22);printf("?                        ?");
	gotoxy(x,23);printf("??????????????????????????");
	for(n=29;n<=50;n++){
		gotoxy(n,22);printf("?");
		kecepatan(0.1);
	};
}

void welcome_screen(){// menampilkan tampilan awal dijalankannya program
	gotoxy(22,28); printf(" Created By : Moh. Dwi, Rangga R, Silvi \n");
	judul();
	loading();
}

void aboutus(){//menampilkan file creator.txt
	FILE *creator;
	char creat[panjang];

	creator = fopen("creator.txt", "rt");
	while((fgets(creat, panjang, creator))!= NULL){
		printf("%s\r", creat);
	}

	fclose(creator);


	gotoxy(22,25); printf("   Press Any Key To Return.....");getch();
	system("CLS");
	menu();
}

void instructions(){//mmenampilkan file instruksi.txt
	FILE *instruksi;
	char instruk[panjang];

	instruksi = fopen("instruksi.txt", "rt");
	while((fgets(instruk, panjang, instruksi))!= NULL){
		printf("%s\r", instruk);
	}

	fclose(instruksi);


	gotoxy(22,25); printf("   Press Any Key To Return.....");getch();
	system("CLS");
	menu();
}

void menu() //modul untuk menampilkan main menu dari program
{
	int pilih_menu, i = 28;
	judul();
	warnateks(WHITE);
	gotoxy(i,18); printf(" ?????????????????????????\n");
   	gotoxy(i,19);printf(" ?      MAIN MENU        ?\n");
   	gotoxy(i,20);printf(" ?                       ?\n");
   	gotoxy(i,21);printf(" ?   [1] PLAY NOW !      ?\n");
   	gotoxy(i,22);printf(" ?   [2] INSTRUCTIONS    ?\n");
   	gotoxy(i,23);printf(" ?   [3] THE CREATOR     ?\n");
   	gotoxy(i,24);printf(" ?   [0] Exit            ?\n");
   	gotoxy(i,25);printf(" ?                       ?\n");
   	gotoxy(i,26);printf(" ?????????????????????????\n");
	gotoxy(i,28);printf("    Choose :            \n");
   	gotoxy(41,28);scanf("%d",&pilih_menu);
   	switch(pilih_menu){
			case 1:
				system("CLS");
				gotoxy(i,18);printf(" ?????????????????????????\n");
   				gotoxy(i,19);printf(" ?      MODE MAIN        ?\n");
   				gotoxy(i,20);printf(" ?                       ?\n");
   				gotoxy(i,21);printf(" ?   [1] VS COMPUTER     ?\n");
   				gotoxy(i,22);printf(" ?   [2] VS PLAYER       ?\n");
   				gotoxy(i,23);printf(" ?                       ?\n");
   				gotoxy(i,24);printf(" ?????????????????????????\n");
				gotoxy(i,25);printf("    Choose :            \n");
   				gotoxy(41,25);scanf("%d",&pilih_menu);
                switch(pilih_menu){
                    case 1 : system("CLS");
                        gotoxy(i,18);printf(" ?????????????????????????\n");
   						gotoxy(i,19);printf(" ?      DIFFICULTY       ?\n");
   						gotoxy(i,20);printf(" ?                       ?\n");
   						gotoxy(i,21);printf(" ?   [1] NORMAL   	     ?\n");
   						gotoxy(i,22);printf(" ?   [2] HARD            ?\n");
   						gotoxy(i,23);printf(" ?                       ?\n");
   						gotoxy(i,24);printf(" ?????????????????????????\n");
						gotoxy(i,25);printf("    Choose :            \n");
   						gotoxy(41,25);scanf("%d",&pilih_menu);
                        switch(pilih_menu){
                            case 1 : permainanKomputer(normal);break;
                            case 2 : permainanKomputer(hard);break;
                            default: menu();break;
                        }
                    case 2 : permainanPlayer();break;
                    default : menu();break;
                }

			break;

			case 2:
				system("CLS");
				instructions();
			break;

			case 3:
				system("CLS");
				aboutus();
			break;

			case 0:
				exit(1);
			break;

			default:
				menu();
			break;
	 }
}

int cek_h1(int kotak_a, const int *board, const int giliran){//cek horizontal di kanan kotak_a
	int ketemu = 0;
	int k = kotak_a + 1;
	while( true ){
		if(k % 5 == 0){
			break;
		}

		if ( board[k] != giliran || k > 24 || ketemu == 3){
			break;
		}else{
            ketemu++;
		}

		k = k + 1;
	}
	return ketemu;
}

int cek_h2(int kotak_a, const int *board, const int giliran){//cek horizontal di kiri kotak_a
	int ketemu = 0;
	int k = kotak_a - 1;
	while( k >= 0){
        if (k == 4 || k == 9 || k == 14 || k == 19){
			break;
		}

		if ( board[k] != giliran || ketemu == 3 || kotak_a % 5 == 0){
			break;
		}else{
			ketemu++;
		}

		k = k - 1;

	}
	return ketemu;
}

int cek_v(int kotak_a, const int *board, const int giliran, const int j){//cek vertikal kotak_a
	int ketemu = 0;
	int k = kotak_a + j;
	while(k >= 0 && k <= 24){
		if ( board[k] != giliran || ketemu == 3){
			break;
		}else{
			ketemu++;
		}

		k = k + j;
	}
	return ketemu;
}

int cek_d(int kotak_a, const int *board, const int giliran, const int j, const int m, const int n){//cek diagonal kotak_a
	int ketemu = 0;
	int k = kotak_a + j;
	while(k >= m && k <= n){
		if ( board[k] != giliran || ketemu == 3){
			break;
		}else{
			ketemu++;
		}
		k = k + j;
	}
	return ketemu;
}



int cek_status(const int *board, const int n_kotak, const int giliran)//modul untuk mengecek jumlah simbol sejajar terbanyak
{
    int status_max = 1;
	int j, status;

        status=1;	//cek horizontal
		status = status + cek_h1(n_kotak, board, giliran);//cek horizontal kanan n_kotak
		status = status + cek_h2(n_kotak, board, giliran);//cek horizontal kiri n_kotak
		if(status > status_max){
            status_max = status;
		}

		status = 1;		// cek vertikal
		j = 5;
		status = status + cek_v(n_kotak, board, giliran, j);//cek vertikal atas n_kotak
		status = status + cek_v(n_kotak, board, giliran, j*-1);//cek_vertikal bawah n_kotak
		if(status > status_max){
            status_max = status;
		}

        int m,n;
		if(n_kotak == 4 || n_kotak == 8 || n_kotak == 12 || n_kotak == 16 || n_kotak == 20){
            status = 1;		//cek diagonal kolom 5 - 21
            j = 4;
            m = 4;
            n = 20;
            status = status + cek_d(n_kotak, board, giliran, j, m, n);
            status = status + cek_d(n_kotak, board, giliran, j*-1, m, n);
            if(status > status_max){
            status_max = status;
            }
		}

		if(n_kotak == 0 || n_kotak == 6 || n_kotak == 12 || n_kotak == 18 || n_kotak == 24){
            status = 1;		//cek diagonal kolom 1 - 25
            j = 6;
            m = 0;
            n = 24;
            status = status + cek_d(n_kotak, board, giliran, j, m, n);
            status = status + cek_d(n_kotak, board, giliran, j*-1, m, n);
            if(status > status_max){
                status_max = status;
            }
		}

        if(n_kotak == 5 || n_kotak == 11 || n_kotak == 17 || n_kotak == 23){
            status = 1;		//cek diagonal kolom 6 - 24
            j = 6;
            m = 5;
            n = 23;
            status = status + cek_d(n_kotak, board, giliran, j, m, n);
            status = status + cek_d(n_kotak, board, giliran, j*-1, m, n);
            if(status > status_max){
                status_max = status;
            }
        }

        if(n_kotak == 1 || n_kotak == 7 || n_kotak == 13 || n_kotak == 19){
            status = 1;		//cek diagonal kolom 2 - 20
            j = 6;
            m = 1;
            n = 19;
            status = status + cek_d(n_kotak, board, giliran, j, m, n);
            status = status + cek_d(n_kotak, board, giliran, j*-1, m, n);
            if(status > status_max){
                status_max = status;
            }
        }

        if(n_kotak == 3 || n_kotak ==  7|| n_kotak == 11 || n_kotak == 15){
            status = 1;		//cek diagonal kolom 4 - 16
            j = 4;
            m = 3;
            n = 15;
            status = status + cek_d(n_kotak, board, giliran, j, m, n);
            status = status + cek_d(n_kotak, board, giliran, j*-1, m, n);
            if(status > status_max){
                status_max = status;
            }
        }

        if(n_kotak == 9 || n_kotak ==  13|| n_kotak == 17 || n_kotak == 21){
            status = 1;		//cek diagonal kolom 10 - 22
            j = 4;
            m = 9;
            n = 21;
            status = status + cek_d(n_kotak, board, giliran, j, m, n);
            status = status + cek_d(n_kotak, board, giliran, j*-1, m, n);
            if(status > status_max){
                status_max = status;
            }
        }
	return status_max;
}

int menangin_blocking(int *board, const int giliran, const int tingkat)//modul untuk menentukan langkah yang akan diambil oleh komputer untuk memenangkan permainan dan mencegah user menang
{
	int no_kotak = -1, i = 0;
	for(i = 0; i < 25; i++){
		if(board[i] == kosong){
			no_kotak = i;
			board[no_kotak] = giliran;
			if (cek_status(board, no_kotak, giliran) >= tingkat){
				break;
			} else {
				board[no_kotak] = kosong;
				no_kotak = -1;
			}
		}
	}
	return no_kotak;
}

int cek_draw(const int *board)//modul untuk mengecek apakah permainan draw atau tidak
{
	int i=0;
	for(i=0; i<25; i++){
		if(board[i] == kosong)
		return 1;
	}
	return 0;
}

int input_user(const int *board)//modul untuk memproses inputan langkah dari user pada saat permainan
{
	//char userinput[12];
	warnateks(WHITE);
	int keluar = 0;
	char pilih_kotak_string[3];
	int pilih_kotak=-1;
	while (keluar == 0) {
		printf("\n\n\n\t\t\tMasukan nomor kotak (1-25) :");
		label2 :
		scanf("%s", pilih_kotak_string);
        if(strlen(pilih_kotak_string) > 3 ){
            printf("\n\t\t\tTerlalu banyak character yang diinput\n");
            continue;
        }
        for(int i = 0; i < 3;i++){
            if(pilih_kotak_string[i] < '0' || pilih_kotak_string[i] > '9'){
                printf("\n\t\t\tInput harus berupa integer 1-25\n");
                break;
            }
        }

		pilih_kotak = atoi(pilih_kotak_string);

		if (pilih_kotak < 1 || pilih_kotak > 25){
			pilih_kotak = -1;
			printf("\n\t\t\tNomor yang anda masukan salah\n");
			continue;
		}

		pilih_kotak--;
		if( board[pilih_kotak] != kosong ){
			pilih_kotak=-1;
			printf("\n\t\t\tKotak tersebut sudah terisi, pilih kotak lain : ");
			continue;
		}
		//if(pilih_kotak>1 || pilih_kotak)
		keluar=1;
	}
	return pilih_kotak;
}

void isi_kotak(int *board,const int no_kotak,const int giliran)//modul untuk mengisi array board dengan tanda dari user dan komputer
{
	board[no_kotak] = giliran;
}

int gilirankomputer( int *board, const int _giliran,const int tingkat)//modul yang berfungsi untuk menentukan langkah komputer
{
	int i = 0, nomor_kotak = 0;
    if(tingkat == normal){//memprioritaskan menang kemudian block
        nomor_kotak = menangin_blocking(board, _giliran, 4);
        if(nomor_kotak != -1){
            return nomor_kotak;
        }

        nomor_kotak = menangin_blocking(board, _giliran ^ 1, 4);
        if(nomor_kotak != -1){
            return nomor_kotak;
        }
    }

    if(tingkat == hard){//memprioritaskan block kemudian menang
        nomor_kotak = menangin_blocking(board, _giliran, 4);
        if(nomor_kotak != -1){
            return nomor_kotak;
        }

        nomor_kotak = menangin_blocking(board, _giliran ^ 1, 3);
        if(nomor_kotak != -1){
            return nomor_kotak;
        }
    }


	nomor_kotak = 0;
	int nomor_kotak_kosong = 0;
	int kotak_tersedia[25];
	for(i = 0; i < 25; i++){
		if(board[i] == kosong){
			kotak_tersedia[nomor_kotak_kosong] = i;
			nomor_kotak_kosong++;
		}
	}
	nomor_kotak = (rand() % nomor_kotak_kosong);

	return kotak_tersedia[nomor_kotak];
}

void permainanKomputer(const int tingkat)//modul yang berfungsi untuk menentukan dan mengatur jalannya permainan vs komputer
{
	int board[25];
	int game_over = 0, giliran = O, no_kotak = -1;
	inisialisasi(&board[0]);

	while(game_over != 1) {
		system("cls");
		tampilan_board(&board[0]);
		if(giliran == O){
			no_kotak = input_user(&board[0]);
			isi_kotak(&board[0],no_kotak,giliran);
		}else{
			no_kotak = gilirankomputer(&board[0], giliran, tingkat);
			isi_kotak(&board[0], no_kotak, giliran);
            tampilan_board(&board[0]);
		}

		if( cek_status(board, no_kotak, giliran) >= 4 ){
			int i = 15, j = -1;
			system("cls");
			warnateks(WHITE);
			printf("\n\n\t\t\t\tG A M E  O V E R\n");
			tampilan_board_akhir(&board[0]);

            if(giliran == X){
                warnateks(LIGHT_GREEN);
                printf("\n\n\t\t\t\t Komputer Menang!\n");
            } else {
                warnateks(YELLOW);
                printf("\n\t\t\t\t    Anda Menang!\n\n");
            }

			warnateks(WHITE);
			printf("\n\t\t\t Anda Ingin Bermain Lagi? \n\t\t\t [1] YA\n\t\t\t [2] TIDAK\n\t\t\t Masukan No Pilihan : "); scanf("%d", &j);

            if(j==2){
                game_over = 1;
                system("CLS");
                menu();
            }else{
                game_over = 0;
                inisialisasi(&board[0]);
            }
		}

		if(cek_draw(board) == 0) {
			int j = -1;
			game_over = 1;
			system("cls");
			printf("\n\t\t\tD R A W\n");
			tampilan_board_akhir(&board[0]);
			warnateks(WHITE);
			printf("\n\t\t\t Anda Ingin Bermain Lagi? \n\t\t\t[1] YA\n\t\t\t[2] TIDAK\n\t\t\tMasukan No Pilihan : "); scanf("%d", &j);
            if(j==2){
                game_over = 1;
                break;
            }else{
                game_over = 0;
                inisialisasi(&board[0]);
            }
		}

		if(giliran == O){
            giliran = X;
		}else{
            giliran = O;
		}
	}
}

void permainanPlayer()//modul yang berfungsi untuk menentukan dan mengatur jalannya permainan vs player
{
	int board[25];
	int game_over = 0, giliran = O, no_kotak = -1;
	inisialisasi(&board[0]);

	while(game_over != 1) {
		system("cls");
		tampilan_board(&board[0]);
		if(giliran == O){
            warnateks(YELLOW);
            printf("\n\n\t\t\t\tGiliran Player O ");

            warnateks(WHITE);
			no_kotak = input_user(&board[0]);
			isi_kotak(&board[0],no_kotak,giliran);
			tampilan_board(&board[0]);
		}else{
		    warnateks(GREEN);
            printf("\n\n\t\t\t\tGiliran Player X ");

            warnateks(WHITE);
			no_kotak = input_user(&board[0]);
			isi_kotak(&board[0], no_kotak, giliran);
            tampilan_board(&board[0]);
		}

		if( cek_status(board, no_kotak, giliran) >= 4 ){
			int i = 15, j = -1;
			system("cls");
			warnateks(WHITE);
			printf("\n\n\t\t\t\tG A M E  O V E R\n");
			tampilan_board_akhir(&board[0]);

            if(giliran == X){
                warnateks(LIGHT_GREEN);
                printf("\n\n\t\t\t\t Player X Menang!\n");
            } else {
                warnateks(YELLOW);
                printf("\n\t\t\t\t    Player O Menang!\n\n");
            }

			warnateks(WHITE);
			printf("\n\t\t\t Anda Ingin Bermain Lagi? \n\t\t\t [1] YA\n\t\t\t [2] TIDAK\n\t\t\t Masukan No Pilihan : "); scanf("%d", &j);

            if(j==2){
                game_over = 1;
                system("CLS");
                menu();
            }else{
                game_over = 0;
                inisialisasi(&board[0]);
            }
		}

		if(cek_draw(board) == 0) {
			int j = -1;
			game_over = 1;
			system("cls");
			printf("\n\t\t\tD R A W\n");
			tampilan_board_akhir(&board[0]);
			warnateks(WHITE);
			printf("\n\t\t\t Anda Ingin Bermain Lagi? \n\t\t\t[1] YA\n\t\t\t[2] TIDAK\n\t\t\tMasukan No Pilihan : "); scanf("%d", &j);
            if(j==2){
                game_over = 1;
                break;
            }else{
                game_over = 0;
                inisialisasi(&board[0]);
            }
		}

		if(giliran == O){
            giliran = X;
		}else{
            giliran = O;
		}
	}
}

 main(){
	welcome_screen();
	system("CLS");
	menu();
	srand(time(NULL));
	system("CLS");
	getch();
}
