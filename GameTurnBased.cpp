//INTI UTAMA CODING
#include <iostream>
#include <fstream>
//ANIMASI TIPIS2
#include <windows.h> //BUAT AMBIL WARNA
//BUAT COUT SAMPING KANAN KIRI
#include <sstream>   // stringstream
#include <vector>    // vector
#include <algorithm> // max
#include <cstdio>    // printf
//extra
#include <cstdlib> //BUAT EXIT 0 AJA
using namespace std;

void printSideBySide(const string& kiri, const string& kanan, int jarak = 4) {
    
    // Pisah ASCII art jadi baris-baris
    vector<string> barisKiri, barisKanan;
    
    stringstream ssKiri(kiri);
    string baris;
    while (getline(ssKiri, baris)) {
        barisKiri.push_back(baris);
    }
    
    stringstream ssKanan(kanan);
    while (getline(ssKanan, baris)) {
        barisKanan.push_back(baris);
    }

    // Cari baris terpanjang di sisi kiri (buat ngatur posisi kanan)
    int lebarKiri = 0;
    for (string& s : barisKiri) {
        if ((int)s.size() > lebarKiri) {
            lebarKiri = s.size();
        }
    }

    // Print baris kiri dan kanan secara bersamaan
    int totalBaris = max(barisKiri.size(), barisKanan.size());
    
    for (int i = 0; i < totalBaris; i++) {
        string colomKiri  = (i < barisKiri.size())  ? barisKiri[i]  : "";
        string colomKanan = (i < barisKanan.size()) ? barisKanan[i] : "";
        
        // %-*s = print kiri rata kiri, %*s = spasi jarak, %s = print kanan
        printf("%-*s%*s%s\n", lebarKiri, colomKiri.c_str(), jarak, "", colomKanan.c_str());
    }
}

struct Player {
    string username;
    int gold;
    int level;
    int Boost_damage;
    int xp;
};

struct Pet {
    string nama;
    int Base_Damage;
    int Base_Hp;
    string design;
    int def;
    int crital_chance;
    int crital_damage;
    string ULT;
};   


Player currentplayer;
Pet Character[15];
string word;


void StatsCharacter() {
// ================= COMMON =================
Character[0].nama = "Ireng_Jogja";
Character[0].Base_Damage = 20;
Character[0].Base_Hp = 120;
Character[0].def = 10;
Character[0].crital_chance = 10;
Character[0].crital_damage = 150;
Character[0].ULT = "";

Character[1].nama = "Laba_Laba_Sunda";
Character[1].Base_Damage = 18;
Character[1].Base_Hp = 100;
Character[1].def = 8;
Character[1].crital_chance = 25;
Character[1].crital_damage = 170;
Character[1].ULT = "";

Character[2].nama = "Sawit_Bantul";
Character[2].Base_Damage = 15;
Character[2].Base_Hp = 150;
Character[2].def = 20;
Character[2].crital_chance = 5;
Character[2].crital_damage = 130;
Character[2].ULT = "";

// ================= RARE =================
Character[3].nama = "Kevin_Hitam";
Character[3].Base_Damage = 35;
Character[3].Base_Hp = 90;
Character[3].def = 5;
Character[3].crital_chance = 20;
Character[3].crital_damage = 200;
Character[3].ULT = "";

Character[4].nama = "Rigby_Wonosobo";
Character[4].Base_Damage = 28;
Character[4].Base_Hp = 130;
Character[4].def = 12;
Character[4].crital_chance = 15;
Character[4].crital_damage = 160;
Character[4].ULT = "";

Character[5].nama = "Aren_Gentong";
Character[5].Base_Damage = 22;
Character[5].Base_Hp = 180;
Character[5].def = 25;
Character[5].crital_chance = 10;
Character[5].crital_damage = 140;
Character[5].ULT = "";

Character[6].nama = "Arpin_Gontor";
Character[6].Base_Damage = 18;
Character[6].Base_Hp = 200;
Character[6].def = 30;
Character[6].crital_chance = 5;
Character[6].crital_damage = 130;
Character[6].ULT = "";

Character[7].nama = "Mister_orange";
Character[7].Base_Damage = 24;
Character[7].Base_Hp = 110;
Character[7].def = 10;
Character[7].crital_chance = 18;
Character[7].crital_damage = 150;
Character[7].ULT = "";

Character[8].nama = "Slot_Gacor";
Character[8].Base_Damage = 15;
Character[8].Base_Hp = 100;
Character[8].def = 8;
Character[8].crital_chance = 40;
Character[8].crital_damage = 250;
Character[8].ULT = "";

// ================= EPIC =================
Character[9].nama = "Hanif_Ninja";
Character[9].Base_Damage = 45;
Character[9].Base_Hp = 110;
Character[9].def = 10;
Character[9].crital_chance = 30;
Character[9].crital_damage = 220;
Character[9].ULT = "";

Character[10].nama = "Mr_Kucing";
Character[10].Base_Damage = 32;
Character[10].Base_Hp = 160;
Character[10].def = 18;
Character[10].crital_chance = 20;
Character[10].crital_damage = 170;
Character[10].ULT = "";

Character[11].nama = "Imissher_Kaliurang";
Character[11].Base_Damage = 25;
Character[11].Base_Hp = 120;
Character[11].def = 12;
Character[11].crital_chance = 25;
Character[11].crital_damage = 180;
Character[11].ULT = "";

// ================= LEGENDARY =================
Character[12].nama = "Ryan_Gosling";
Character[12].Base_Damage = 50;
Character[12].Base_Hp = 180;
Character[12].def = 20;
Character[12].crital_chance = 25;
Character[12].crital_damage = 200;
Character[12].ULT = "";

Character[13].nama = "Anakin_Skywalker";
Character[13].Base_Damage = 60;
Character[13].Base_Hp = 150;
Character[13].def = 15;
Character[13].crital_chance = 35;
Character[13].crital_damage = 250;
Character[13].ULT = "";

Character[14].nama = "Thom_Yorke";
Character[14].Base_Damage = 40;
Character[14].Base_Hp = 140;
Character[14].def = 18;
Character[14].crital_chance = 30;
Character[14].crital_damage = 210;
Character[14].ULT = "";

}

void initCharacter() {

    Character[0].design = R"(    \\_//
   __/". 
  /__ |
  || ||)";

    Character[1].design = R"( /\ \  / /\
//\\ .. //\\
//\((  ))/\\
/  < `' >  \)";

    Character[2].design = R"( \ | /
-- O --
 / | \)";

 Character[3].design = R"(     .-"""-.__     
    /      ' o'\
 ,-;  '.  :   _c
:_."\._ ) ::-"
       ""m "m)";

Character[4].design = R"( ,_     _
 |\\_,-~/
 / _  _ |    ,--.
(  @  @ )   / ,-'
 \  _T_/-._( (
 /         `. \
|         _  \ |
 \ \ ,  /      |
  || |-_\__   /
 ((_/`(____,-')";

 Character[5].design = R"( /\     /\
{  `---'  }
{  O   O  }
~~>  V  <~~
 \  \|/  /
  `-----'__
  /     \  `^\_
 {       }\ |\_\_   W
 |  \_/  |/ /  \_\_( )
  \__/  /(_E     \__/
    (  /
     MM)";

Character[6].design = R"(    __    __
    \/----\/
     \0  0/    
     _\  /_
   _|  \/  |_
  | | |  | | |
 _| | |  | | |_
"---|_|--|_|---")";

Character[7].design = R"(         __
        /  \
       / ..|\
      (_\  |_)
      /  \@' 
     /     \
_   /  `   |
\\/  \  | _\
 \   /_ || \\_
  \____)|_) \_) )";

Character[8].design = R"(     _______
    |.-----.|
    ||     ||
    ||_____/|
    | .     |
    |-|-  oo|
    |  _ _  |
    |       /
    `""""""`)";

Character[9].design = R"ASCII(   .-'"""`-.
 .'  .-.-.  `.
/ |--| | |--| \
| |  `-^-'  | |
\_/   (_)   \_/
||           ||
\_)         (_/
  ".       ."
    |  |  |
    |  |  |     
   (___|___)
)ASCII";

Character[10].design = R"ASCII( _._     _,-'""`-._
(,-.`._,'(       |\`-/|
    `-.-' \ )-`( , o o)
          `-    \`_`"'- 
)ASCII";

Character[11].design = R"ASCII(               ___
      ~*    .'`  _\
           /  (o/       *
*         |     _\           *
           \  '==.    *
        *   '.____\       ~*
)ASCII";

Character[12].design = R"ASCII(              _                 __                 
      __.--**"""**--...__..--**""""*-.            
    .'                                `-.         
  .'                         _           \        
 /                         .'        .    \   _._ 
:                         :          :`*.  :-'.' ;
;    `                    ;          `.) \   /.-' 
:     `                             ; ' -*   ;    
       :.    \           :       :  :        :    
 ;     ; `.   `.         ;     ` |  '             
 |         `.            `. -*"*\; /        :     
 |    :     /`-.           `.    \/`.'  _    `.   
 :    ;    :    `*-.__.-*""":`.   \ ;  'o` `. /   
       ;   ;                ;  \   ;:       ;:   ,/
  |  | |               	 \    /`  | ,      `*-*'/ 
  `  : :  :                /  /    | : .    ._.-'  
   \  \ ,  \              :   `.   :  \ \   .'     
    :  *:   ;             :    |`*-'   `*+-*       
    `**-*`""               *---*
)ASCII";

Character[13].design = R"ASCII(                       .-.
                      |_:_|
                     /(_Y_)\
.                   ( \/M\/ )
 '.               _.'-/'-'\-'._
   ':           _/.--'[[[[]'--.\_
     ':        /_'  : |::"| :  '.\
       ':     //   ./ |oUU| \.'  :\
         ':  _:'..' \_|___|_/ :   :|
           ':.  .'  |_[___]_|  :.':\
            [::\ |  :  | |  :   ; : \
             '-'   \/'.| |.' \  .;.' |
             |\_    \  '-'   :       |
             |  \    \ .:    :   |   |
             |   \    | '.   :    \  |
             /       \   :. .;       |
            /     |   |  :__/     :  \\
           |  |   |    \:   | \   |   ||
          /    \  : :  |:   /  |__|   /|
          |     : : :_/_|  /'._\  '--|_\
          /___.-/_|-'   \  \
                         '-'
)ASCII";

Character[14].design = R"ASCII(           ___
          (___)
   ____
 _\___ \  |\_/|
\     \ \/ , , \ ___
 \__   \ \ ="= //|||
  |===  \/____)_)||||
  \______|    | ||||
      _/_|  | | =====
     (_/  \_)_) 
  _________________
 (                _)
  (__   '          )
    (___    _____)
        '--'
)ASCII";
}

void lore(),logo(),BattleUI();

void ketik(string text, int delay_ms = 30) {
    for (char c : text) {
        cout << c << flush;
        Sleep(delay_ms);
    }
}

void tunggu(int ms) {
    Sleep(ms);
}

void setWarna(int warna) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), warna);
}

void lore() {
    system("cls");

    setWarna(11); // cyan
    ketik("LUMINARA — 20XX\n", 50);

    setWarna(7); // putih
    ketik("11 September\n\n", 50);
    tunggu(800);

    ketik("Di dunia hewan dimana semua damai...\n\n");
    tunggu(1000);

    ketik("Lalu...\n\n");
    tunggu(700);

    setWarna(12); // merah
    ketik("DUARRR!!!\n\n", 80);
    Beep(750, 200);
    tunggu(500);

    setWarna(14); // kuning
    ketik("Langit retak.\n\n");
    tunggu(800);

    setWarna(13); // ungu
    ketik("Bukan sekadar ledakan...\n");
    ketik("sesuatu... terbuka.\n\n");
    tunggu(1000);

    setWarna(11); // cyan
    ketik("Cahaya aneh menyembur keluar.\n");
    ketik("Bumi bergetar.\n\n");
    tunggu(1000);

    setWarna(7);
    ketik("Naluri berubah.\n\n");
    tunggu(800);

    setWarna(12);
    ketik("Makhluk yang dulu jinak...\n");
    ketik("menjadi liar.\n\n");
    tunggu(1000);

    ketik("Sebagian... berubah menjadi sesuatu yang lebih buruk.\n\n");
    tunggu(1000);

    setWarna(4); // merah gelap
    ketik("Monster.\n\n", 60);
    tunggu(1000);

    setWarna(10); // hijau
    ketik("Namun tidak semua terpengaruh.\n\n");
    tunggu(1000);

    ketik("Beberapa tetap sadar.\n\n");
    tunggu(800);

    ketik("Mereka bangkit...\n");
    ketik("dengan kekuatan yang tidak seharusnya dimiliki.\n\n");
    tunggu(1200);

    setWarna(14);
    ketik("Mereka disebut...\n\n");
    tunggu(1000);

    setWarna(13); // ungu terang
    ketik("FERAL AWAKENED\n\n", 80);
    tunggu(1500);

    setWarna(7);
    ketik("Dan sejak hari itu...\n\n");
    tunggu(1000);

    ketik("Dunia tidak pernah sama lagi...\n\n");
    tunggu(1500);

    setWarna(11);
    ketik("Dan kamu...\n\n", 60);
    tunggu(800);

    setWarna(10); // hijau terang
    ketik("adalah Keeper mereka.\n", 80);

    setWarna(7);

    tunggu(1500);
    cout << "\n\nTekan ENTER untuk lanjut...";
    cin.ignore();
    cin.get();

    system("cls");
}

void Logo() {

int pilih = 0;
int pilih1 = 0;
int start;

ifstream Cek("save.txt");


if (Cek.peek() == EOF) {cout << R"(+----------------------------+
|            MENU            |
+----------------------------+
| 1. New game                |
| 2. Exit                    |
+----------------------------+
Option darling? )";cin >> pilih1;
}

else {
cout << R"(+----------------------------+
|            MENU            |
+----------------------------+
| 1. Continue?               |
| 2. Reset Data              |
| 3. Exit                    |
+----------------------------+
Option darling? )";cin >> pilih;
}
Cek.close();
if (pilih1 == 1) {
    lore();
    ofstream Lore("save.txt",ios::app);
    Lore << "Lore_True" << " ";
    setWarna(10); // hijau
    ketik("Masukan Nama kamu Keeper: "); 
    tunggu(1000);
    setWarna(7);
    cin >> currentplayer.username;
    Lore << currentplayer.username << " ";
    Lore.close();
}

if (pilih1 == 2) {
   exit(0);
}
if (pilih == 1) {
    return;
}
if (pilih == 2) {
    ofstream Reset("save.txt");
    cout << "RESET BERHASIL\n";
    system("pause");
    exit(0);
}
if (pilih == 3) {
    ofstream Reset("save.txt");
    exit(0);
}

}


void Tutorial1() {
    setWarna(10);
    ketik("TUTORIAL\n\n", 40);
    tunggu(500);

    setWarna(7);
    ketik("1. Kamu akan bertarung secara turn-based.\n");
    ketik("2. Pilih aksi saat giliranmu:\n");
    ketik("   - Fight  : menyerang musuh\n");
    ketik("   - Defend : mengurangi damage\n\n");
    tunggu(800);

    ketik("3. Setiap karakter punya:\n");
    ketik("   - HP\n");
    ketik("   - Damage\n");
    ketik("   - Defense\n");
    ketik("   - Critical Chance\n\n");
    tunggu(800);

    ketik("4. Kalahkan musuh untuk mendapatkan reward.\n");
    ketik("5. Gunakan reward untuk mendapatkan karakter baru.\n\n");
    tunggu(800);

    setWarna(10);
    ketik("Selesai. Siap bertarung?.\n\n", 50);

    setWarna(7);
    ketik("Tekan ENTER untuk lanjut...");
    cin.ignore();
    cin.get();

    system("cls");
}


void BattleUI() {
    string pad = "";

    setWarna(7);
    cout << "\n\n\n";

    cout << pad << "+------------------------------------------------------+\n";
    cout << pad << "|                                                      |\n";

    cout << pad << "|   ";

    setWarna(14);
    cout << "[1.FIGHT]   ";

    setWarna(6);
    cout << "[2.DEFEND]   ";

    setWarna(11);
    cout << "[3.ULT]   ";

    setWarna(12);
    cout << "[4.INVENTORY]";

    setWarna(7);
    cout << "   |\n"; //

    cout << pad << "|                                                      |\n";
    cout << pad << "+------------------------------------------------------+\n";

    cout << "\nPilih aksi (1-4): ";
}

void Testing() {
bool Main = true;
bool Player_isAlive = true;
bool Enemy_isAlive = true;

printSideBySide(Character[13].design, Character[7].design, 30);
BattleUI();

}














int main() {
StatsCharacter();
initCharacter();
ofstream File("save.txt", ios::app);
File.close();
Logo();
ifstream Tutorial("save.txt", ios::app);
/////////////////////////////////////// TUTORIAL FIGHT
system("cls");
bool Tutor = false;
while (Tutorial >> word) {
    if (word == "Tutor_True") {
        Tutor = false;
        break;
    }
}

if (Tutor) {
   Tutorial1();
}
//////////////////////////////////////
Testing();




return 0;

}
