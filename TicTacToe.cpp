#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<windows.h>
#include<time.h>

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

void menu();
void permainanKomputer(int);
void permainanPlayer();
bool cekInputRange(int,int,int);
bool cekInputInteger(char*);


void warnateks(int warna) //modul yang berfungsi untuk memberi warna ke karakter
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, warna);
}

void inisialisasi(int *board) //modul untuk memberi nilai awal ke array board
{
    const int kosong = 3;
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

void xo(){//memberi logo x dan o
	warnateks(LIGHT_GREEN);		
	gotoxy(9,8); printf("ÛÛ       ÛÛ \n");		
	gotoxy(9,9); printf("  ÛÛ   ÛÛ \n");		
	gotoxy(9,10); printf("    ÛÛÛ \n");		
	gotoxy(9,11); printf("    ÛÛÛ \n");		
	gotoxy(9,12); printf("  ÛÛ   ÛÛ \n");		
	gotoxy(9,13); printf("ÛÛ       ÛÛ \n");			
	gotoxy(9,15);printf(" COMPUTER \n");		
	warnateks(YELLOW);		
	gotoxy(61,8); printf("    ÛÛÛÛ  \n");		
	gotoxy(61,9); printf("  ÛÛ    ÛÛ \n");		
	gotoxy(61,10); printf("  ÛÛ    ÛÛ \n");		
	gotoxy(61,11); printf("  ÛÛ    ÛÛ \n");		
	gotoxy(61,12); printf("  ÛÛ    ÛÛ \n");		
	gotoxy(61,13); printf("    ÛÛÛÛ \n");		
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
	gotoxy(8,1); printf("  ÛÛÛÛÛÛÛÛÛÛ  ÛÛ   ÛÛÛÛÛ             ÛÛÛÛÛÛÛÛÛÛ   ÛÛÛÛ    ÛÛÛÛÛ \n");
	printf("              ÛÛ      ÛÛ  ÛÛ                     ÛÛ      ÛÛ  ÛÛ  ÛÛ     \n");
	printf("              ÛÛ      ÛÛ  ÛÛ                     ÛÛ      ÛÛ  ÛÛ  ÛÛ     \n");
	printf("              ÛÛ      ÛÛ  ÛÛ                     ÛÛ      ÛÛÛÛÛÛ  ÛÛ     \n");
	printf("              ÛÛ      ÛÛ  ÛÛ                     ÛÛ      ÛÛ  ÛÛ  ÛÛ     \n");
	printf("              ÛÛ      ÛÛ   ÛÛÛÛÛ                 ÛÛ      ÛÛ  ÛÛ   ÛÛÛÛÛ \n \n\n\n");
	
	printf("      		           ÛÛÛÛÛÛÛÛÛÛ  ÛÛÛÛÛ   ÛÛÛÛÛ \n");
	printf("	 	               ÛÛ     ÛÛ   ÛÛ  Û     \n");
	printf("		               ÛÛ     ÛÛ   ÛÛ  ÛÛÛÛÛ \n");
	printf("		               ÛÛ     ÛÛ   ÛÛ  Û \n");
	printf("                               ÛÛ     ÛÛ   ÛÛ  Û     \n");
	printf("		               ÛÛ      ÛÛÛÛÛ   ÛÛÛÛÛ \n");
	
	warnateks(LIGHT_GREEN);
	gotoxy(9,18); printf("ÛÛ       ÛÛ \n");
	gotoxy(9,19); printf("  ÛÛ   ÛÛ \n");
	gotoxy(9,20); printf("    ÛÛÛ \n");
	gotoxy(9,21); printf("    ÛÛÛ \n");
	gotoxy(9,22); printf("  ÛÛ   ÛÛ \n");
	gotoxy(9,23); printf("ÛÛ       ÛÛ \n");	
	warnateks(YELLOW);
	gotoxy(61,18); printf("    ÛÛÛÛ  \n");
	gotoxy(61,19); printf("  ÛÛ    ÛÛ \n");
	gotoxy(61,20); printf("  ÛÛ    ÛÛ \n");
	gotoxy(61,21); printf("  ÛÛ    ÛÛ \n");
	gotoxy(61,22); printf("  ÛÛ    ÛÛ \n");
	gotoxy(61,23); printf("    ÛÛÛÛ \n");	
}

void jedaWaktu(float seconds){//memberi jeda waktu dalam satuan detik
	clock_t endwait;
	endwait=clock()+seconds*CLOCKS_PER_SEC;
	while(clock()<endwait){};
}

void loading()//modul untuk menapilkan tampilan loading
{
	int x = 28, y = 13, n;
	warnateks(WHITE);
	gotoxy(x,20); printf("       Please Wait");
	gotoxy(x,21);  printf("ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»");
	gotoxy(x,22);printf("º                        º");
	gotoxy(x,23);printf("ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼");
	for(n=29;n<=50;n++){
		gotoxy(n,22);printf("?");
		jedaWaktu(0.1);
	};
}

void welcome_screen(){//tampilan saat program pertama dijalankan
	gotoxy(22,28); printf(" Created By : Moh. Dwi, Rangga R, Silvi \n");
	judul();
	loading();
}

void aboutus(){//menampilkan file creator.txt tentang pembuat game
	FILE *creator;
	char creat[1000];

	creator = fopen("creator.txt", "rt");
	while((fgets(creat, 1000, creator))!= NULL){
		printf("%s\r", creat);
	}

	fclose(creator);


	gotoxy(22,25); printf("   Press Any Key To Return.....");_getch();
	system("CLS");
	menu();
}

void instructions(){//mmenampilkan file instruksi.txt tentang cara bermain game
	FILE *instruksi;
	char instruk[1000];

	instruksi = fopen("instruksi.txt", "rt");
	while((fgets(instruk, 1000, instruksi))!= NULL){
		printf("%s\r", instruk);
	}

	fclose(instruksi);


	gotoxy(22,25); printf("   Press Any Key To Return.....");_getch();
	system("CLS");
	menu();
}

void menu() //modul untuk menampilkan main menu dari program
{
	int i = 28;
	int normal=1;
	int hard=2;
	char pilih_menu[3];

	judul();
	warnateks(WHITE);
	gotoxy(i,18); printf(" ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»\n");
   	gotoxy(i,19);printf(" º      MAIN MENU        º\n");
   	gotoxy(i,20);printf(" º                       º\n");
   	gotoxy(i,21);printf(" º   [1] PLAY NOW !      º\n");
   	gotoxy(i,22);printf(" º   [2] INSTRUCTIONS    º\n");
   	gotoxy(i,23);printf(" º   [3] THE CREATOR     º\n");
   	gotoxy(i,24);printf(" º   [0] Exit            º\n");
   	gotoxy(i,25);printf(" º                       º\n");
   	gotoxy(i,26);printf(" ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼\n");
	gotoxy(i,28);printf("    Choose :            \n");
   	gotoxy(41,28);scanf("%s",pilih_menu);
   	if(!cekInputInteger(pilih_menu)){
        gotoxy(i,30);printf("Input harus berupa integer");
        strcpy(pilih_menu,"99");
    }

   	switch(atoi(pilih_menu)){
			case 1:
				system("CLS");
				gotoxy(i,18);printf(" ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»\n");
   				gotoxy(i,19);printf(" º      PLAY MODE        º\n");
   				gotoxy(i,20);printf(" º                       º\n");
   				gotoxy(i,21);printf(" º   [1] VS COMPUTER     º\n");
   				gotoxy(i,22);printf(" º   [2] VS PLAYER       º\n");
   				gotoxy(i,23);printf(" º                       º\n");
   				gotoxy(i,24);printf(" ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼\n");
				gotoxy(i,25);printf("    Choose :            \n");
   				gotoxy(41,25);scanf("%s",pilih_menu);
   				if(!cekInputInteger(pilih_menu)){
                    gotoxy(i,30);printf("Input harus berupa integer");
                    strcpy(pilih_menu,"99");
                }

                switch(atoi(pilih_menu)){
                    case 1 : system("CLS");
                        gotoxy(i,18);printf(" ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»\n");
   					gotoxy(i,19);printf(" º     BOT DIFFICULTY    º\n");
   					gotoxy(i,20);printf(" º                       º\n");
   					gotoxy(i,21);printf(" º   [1] NORMAL          º\n");
   					gotoxy(i,22);printf(" º   [2] HARD            º\n");
   					gotoxy(i,23);printf(" º                       º\n");
   					gotoxy(i,24);printf(" ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼\n");
					gotoxy(i,25);printf("    Choose :            \n");
   						gotoxy(41,25);scanf("%s",pilih_menu);
   						if(!cekInputInteger(pilih_menu)){
                            gotoxy(i,30);printf("Input harus berupa integer");
                            strcpy(pilih_menu,"99");
                        }

                        switch(atoi(pilih_menu)){
                            case 1 : permainanKomputer(normal);break;
                            case 2 : permainanKomputer(hard);break;
                            default: menu();gotoxy(i,27);printf("Menu tidak tersedia");break;
                        }
                    case 2 : permainanPlayer();break;
                    default : menu();gotoxy(i,27);printf("Menu tidak tersedia");break;
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
				menu();gotoxy(i,30);printf("Menu tidak tersedia");
			break;
	 }
}

int cek_h(int kotak_a, const int *board, const int simbol, int j)//modul untuk mengecek jml simbol secara horizontal
{
	int ketemu = 0;
	int k = kotak_a + (1*j);
	if(j==1){//j=1 berarti cek horizontal sebelah kanan kotak_a
        while( board[k] == simbol && k < 24 && k % 5 != 0){
            ketemu++;
            k = k + (j*1);
        }
        return ketemu;
	}else if(j==-1){//j=-1 berarti cek horizontal sebelah kiri kotak_a
        while( k >= 0 && board[k] == simbol && kotak_a % 5 != 0){
            if (k == 4 || k == 9 || k == 14 || k == 19){
                break;
            }

            ketemu++;
            k = k + (j*1);

        }
        return ketemu;
	}
}

int cek_v(int kotak_a, const int *board, const int simbol, int j)//modul untuk mengecek jml simbol secara vertikal
{
	int ketemu = 0;
	int k = kotak_a + (5*j);
	while(k >= 0 && k <= 24){
		if ( board[k] != simbol){
			break;
		}else{
			ketemu++;
		}

		k = k + (j*5);
	}
	return ketemu;
}

int cek_d(int kotak_a, const int *board, const int simbol, int j, int m, int n)//modul untuk mengecek jml simbol secara diagonal
{
	int ketemu = 0;
	int k,x;

	if((m == 4 && n==20)||(m==9 && n==21)||(m==3 && n==15)){
        x=4;
	}else{
        x=6;
	}

	k = kotak_a + (j*x);
	while(k >= m && k <= n){
		if ( board[k] != simbol ){
			break;
		}else{
			ketemu++;
		}
		k = k + (j*x);
	}
	return ketemu;
}

int cek_status_max(const int *board, const int n_kotak, const int simbol)//modul untuk mengecek jumlah simbol berderet paling banyak jika n_kotak diisi oleh parameter simbol
{
    int status_max = 1;
	int status;

        status=1;		//cek horizontal
		status = status + cek_h(n_kotak, board, simbol, 1);//horizontal kanan
		status = status + cek_h(n_kotak, board, simbol, -1);//horizontal kiri
		if(status > status_max){
            status_max = status;
		}

		status = 1;		// cek vertikal
		status = status + cek_v(n_kotak, board, simbol, 1);//vertikal atas
		status = status + cek_v(n_kotak, board, simbol, -1);//vertikal bawah
		if(status > status_max){
            status_max = status;
		}

        int m,n;
		if(n_kotak == 4 || n_kotak == 8 || n_kotak == 12 || n_kotak == 16 || n_kotak == 20){
            status = 1;		//cek diagonal kolom 4 - 20
            m = 4;
            n = 20;
            status = status + cek_d(n_kotak, board, simbol, 1, m, n);
            status = status + cek_d(n_kotak, board, simbol, -1, m, n);
            if(status > status_max){
                status_max = status;
            }
		}

		if(n_kotak == 0 || n_kotak == 6 || n_kotak == 12 || n_kotak == 18 || n_kotak == 24){
            status = 1;		//cek diagonal kolom 0 - 24
            m = 0;
            n = 24;
            status = status + cek_d(n_kotak, board, simbol, 1, m, n);
            status = status + cek_d(n_kotak, board, simbol, -1, m, n);
            if(status > status_max){
                status_max = status;
            }
		}

        if(n_kotak == 5 || n_kotak == 11 || n_kotak == 17 || n_kotak == 23){
            status = 1;		//cek diagonal kolom 5 - 23
            m = 5;
            n = 23;
            status = status + cek_d(n_kotak, board, simbol, 1, m, n);
            status = status + cek_d(n_kotak, board, simbol, -1, m, n);
            if(status > status_max){
                status_max = status;
            }
        }

        if(n_kotak == 1 || n_kotak == 7 || n_kotak == 13 || n_kotak == 19){
            status = 1;		//cek diagonal kolom 1 - 19
            m = 1;
            n = 19;
            status = status + cek_d(n_kotak, board, simbol, 1, m, n);
            status = status + cek_d(n_kotak, board, simbol, -1, m, n);
            if(status > status_max){
                status_max = status;
            }
        }

        if(n_kotak == 3 || n_kotak ==  7|| n_kotak == 11 || n_kotak == 15){
            status = 1;		//cek diagonal kolom 3 - 15
            m = 3;
            n = 15;
            status = status + cek_d(n_kotak, board, simbol, 1, m, n);
            status = status + cek_d(n_kotak, board, simbol, -1, m, n);
            if(status > status_max){
                status_max = status;
            }
        }

        if(n_kotak == 9 || n_kotak ==  13|| n_kotak == 17 || n_kotak == 21){
            status = 1;		//cek diagonal kolom 9 - 21
            m = 9;
            n = 21;
            status = status + cek_d(n_kotak, board, simbol, 1, m, n);
            status = status + cek_d(n_kotak, board, simbol, -1, m, n);
            if(status > status_max){
                status_max = status;
            }
        }
	return status_max;
}

int generateAngka(int *board, const int simbol, const int jumlah)//modul untuk men-generate angka yang apabila angka tersebut diisi dapat membentuk sederet simbol berjumlah sesuai dengan parameter jumlah
{
	int no_kotak, i;
	const int kosong = 3;
	//pencarian kotak tengah (index 12)
	no_kotak=12;
	if(board[no_kotak] == kosong){
			board[no_kotak] = simbol;
			if (cek_status_max(board, no_kotak, simbol) >= jumlah){
				return no_kotak;
			} else {
				board[no_kotak] = kosong;
				no_kotak = -1;
			}
    }

    //pencarian kotak kedua dari tengah
    for(i=6;i<=18;i++){
        if(board[i] == kosong && i != 12){
			no_kotak = i;
			board[no_kotak] = simbol;
			if (cek_status_max(board, no_kotak, simbol) >= jumlah){
				return no_kotak;
			} else {
				board[no_kotak] = kosong;
				no_kotak = -1;
			}
		}
		if(i==8||i==13||i==18){
            i=i+2;
		}
    }

    //pencarian kotak terluar
	for(i = 0; i <= 24; i++){
		if(board[i] == kosong){
			no_kotak = i;
			board[no_kotak] = simbol;
			if (cek_status_max(board, no_kotak, simbol) >= jumlah){
				return no_kotak;
			} else {
				board[no_kotak] = kosong;
				no_kotak = -1;
			}
		}
		if(i==5 || i==10 || i == 15){
            i=i+3;
		}
	}
	return no_kotak;
}

bool cek_draw(const int *board)//modul untuk mengecek apakah permainan draw atau tidak
{
	int i=0;
	const int kosong = 3;

	for(i=0; i<25; i++){
		if(board[i] == kosong)
		return false;
	}
	return true;
}
bool cekInputInteger(char input[3]){//mengecek apakah input berupa integer atau tidak
    for(int i = 0; i < strlen(input);i++){
        if(input[i] < '0' || input[i] > '9'){
            return false;
        }
    }
    return true;
}

bool cekInputRange(int input,int nilaiMin, int nilaiMax){//mengecek apakah input berada di range nilaiMin dan nilaiMax atau tidak
    if (input < nilaiMin || input > nilaiMax){
        return false;
    }else{
        return true;
    }
}

int input_permainan(const int *board)//modul untuk memproses inputan langkah dari user pada saat permainan
{
	char pilih_kotak_string[3];
	int pilih_kotak;
	const int kosong = 3;

	do{
		printf("\n\n\n\t\t\tMasukan nomor kotak (1-25) :");
		scanf("%s", pilih_kotak_string);
		pilih_kotak=atoi(pilih_kotak_string)-1;

        if(strlen(pilih_kotak_string) > 3 ){
            printf("\n\t\t\tInput harus kurang dari 3 karakter\n");
        }else if(!cekInputInteger(pilih_kotak_string)){
            printf("\n\t\t\tInput harus berupa integer\n");
		}else if(!cekInputRange(pilih_kotak+1,1,25)){
            printf("\n\t\t\tNomor yang anda masukan harus ada di range %d - %d\n",1,25);
		}else if( board[pilih_kotak] != kosong ){
            printf("\n\t\t\tKotak tersebut sudah terisi, pilih kotak lain ");
        }
	}while(!cekInputInteger(pilih_kotak_string) || !cekInputRange(pilih_kotak+1,1,25)|| board[pilih_kotak] != kosong||strlen(pilih_kotak_string)>3);

	return pilih_kotak;
}

void isi_kotak(int *board,const int no_kotak,const int giliran)//modul untuk mengisi array board dengan tanda dari user dan komputer
{
	board[no_kotak] = giliran;
}

int gilirankomputer( int *board, const int _giliran,int tingkat)//modul yang berfungsi untuk menentukan langkah komputer
{
	int i = 0, nomor_kotak = 0;
	int normal = 1;
	int hard = 2;
	const int kosong = 3;

    if(tingkat == normal){//memprioritaskan menang kemudian block
        nomor_kotak = generateAngka(board, _giliran, 4);
        if(nomor_kotak != -1){
            return nomor_kotak;
        }

        nomor_kotak = generateAngka(board, _giliran ^ 1, 4);
        if(nomor_kotak != -1){
            return nomor_kotak;
        }
    }

    if(tingkat == hard){//memprioritaskan block kemudian menang
        nomor_kotak = generateAngka(board, _giliran, 4);
        if(nomor_kotak != -1){
            return nomor_kotak;
        }

        nomor_kotak = generateAngka(board, _giliran ^ 1, 4);
        if(nomor_kotak != -1){
            return nomor_kotak;
        }

        nomor_kotak = generateAngka(board, _giliran, 3);
        if(nomor_kotak != -1){
            return nomor_kotak;
        }

        nomor_kotak = generateAngka(board, _giliran ^ 1, 3);
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

void permainanKomputer(int tingkat)//modul yang berfungsi untuk menentukan dan mengatur jalannya permainan vs komputer
{
	int board[25];
	const int O = 0, X = 1;
	int game_over = 0, giliran = O, no_kotak = -1;
	inisialisasi(&board[0]);

	while(game_over != 1) {
		system("cls");
		tampilan_board(&board[0]);
		if(giliran == O){
			no_kotak = input_permainan(&board[0]);
			isi_kotak(&board[0],no_kotak,giliran);
		}else{
			no_kotak = gilirankomputer(&board[0], giliran, tingkat);
			isi_kotak(&board[0], no_kotak, giliran);
            tampilan_board(&board[0]);
		}

		if( cek_status_max(board, no_kotak, giliran) >= 4 ){
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

		if(cek_draw(board)) {
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
	const int O = 0, X = 1;
	int game_over = 0, giliran = O, no_kotak = -1;
	inisialisasi(&board[0]);

	while(game_over != 1) {
		system("cls");
		tampilan_board(&board[0]);
		if(giliran == O){
            warnateks(YELLOW);
            printf("\n\n\t\t\t\tGiliran Player O ");

            warnateks(WHITE);
			no_kotak = input_permainan(&board[0]);
			isi_kotak(&board[0],no_kotak,giliran);
			tampilan_board(&board[0]);
		}else{
		    warnateks(LIGHT_GREEN);
            printf("\n\n\t\t\t\tGiliran Player X ");

            warnateks(WHITE);
			no_kotak = input_permainan(&board[0]);
			isi_kotak(&board[0], no_kotak, giliran);
            tampilan_board(&board[0]);
		}

		if( cek_status_max(board, no_kotak, giliran) >= 4 ){
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

		if(cek_draw(board)) {
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
