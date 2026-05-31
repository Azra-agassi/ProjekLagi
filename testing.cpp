#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <windows.h>
using namespace std;

// ===== GLOBAL FLAGS =====
bool MarkedBool = true;
bool MarlongBool = true;

// ===== STRUCTS =====
struct Player {
    string username;
    int level;
    int xp;
    int primo;
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
    string rarity;
    bool unlock;
};

struct Villain {
    string nama;
    string design;
    int Base_Damage;
    int Base_Hp;
    int def;
    int crital_chance;
    int crital_damage;
    int level;
    int aggression;
    bool isBoss;
};

// ===== GLOBALS =====
Player currentplayer;
Pet Character[14];
Villain Monster[1];
string word;

// ===== FORWARD DECLARATIONS =====
void lore();
void Logo();
void Tutorial1();
void Fight();
void IsiData();
void initCharacter();
void StatsCharacter();
void StatsMonster();
void tampilSort();
void quickSort();
void printSideBySide(const string& kiri, const string& kanan, int jarak);
void BattleUI(int HpKawan, int HpMusuh, int UltPoin, int MarkStatus, int MarkTurn, int Marked, bool ReviveK, int JumlahRevive, int MaxTurnK, bool &MarlongMode, int &JumlahMarlong, int &MarlongTurn, bool DarkForce, int DarkForceTurn);
void doULT(int CharacterKawan, int CharacterMusuh, int &HpKawan, int &HpMusuh, bool &statusULT, int &PointULT, int &BuffSawit, int &BuffKevin, int &BuffRigby, int &BuffAren, int &MarkStatus, int &Marked, int &MarkTurn, bool &ReviveK, int &JumlahRevive, int &MaxTurnK, bool &MarlongMode, bool &DarkForce);
void AI(int CharacterMonster, int &HpKawan, int &HpMusuh, bool Defend, int CharacterKawan, int &PointULT, int &BuffSawit, int &BuffAren, bool ReviveK, bool MarlongMode, bool DarkForce);
void AttackCharacter(int Aksi, int &HpKawan, int &HpMusuh, int CharacterKawan, bool &Defend, bool &IsULT, int &PointULT, int CharacterMusuh, int &BuffSawit, int &BuffKevin, int &BuffRigby, int &BuffAren, int &MarkStatus, int &Marked, int &MarkTurn, bool &ReviveK, int &JumlahRevive, int &MaxTurnK, bool &MarlongMode, int &JumlahMarlong, int &MarlongTurn, bool &DarkForce, int &DarkForceTurn);

// ===== UTILITY =====
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

void pause() {
    cout << "Tekan ENTER...";
    cin.ignore(1000, '\n');
    cin.get();
}

void printSideBySide(const string& kiri, const string& kanan, int jarak = 4) {
    vector<string> barisKiri, barisKanan;
    stringstream ssKiri(kiri);
    string baris;
    while (getline(ssKiri, baris)) barisKiri.push_back(baris);
    stringstream ssKanan(kanan);
    while (getline(ssKanan, baris)) barisKanan.push_back(baris);

    int lebarKiri = 0;
    for (string& s : barisKiri)
        if ((int)s.size() > lebarKiri) lebarKiri = s.size();

    int totalBaris = max(barisKiri.size(), barisKanan.size());
    for (int i = 0; i < totalBaris; i++) {
        string colomKiri  = (i < (int)barisKiri.size())  ? barisKiri[i]  : "";
        string colomKanan = (i < (int)barisKanan.size()) ? barisKanan[i] : "";
        printf("%-*s%*s%s\n", lebarKiri, colomKiri.c_str(), jarak, "", colomKanan.c_str());
    }
}

// ===== INIT DATA =====
void IsiULT() {
    // COMMON
    Character[0].ULT =
    "Serangan Ireng\n"
    "Damage : (Base Damage * Crit Damage%) * 1.2\n"
    "Notes  : Burst finisher";

    Character[1].ULT =
    "Life Steal Jaring\n"
    "Damage : Base Damage\n"
    "Heal   : 50% dari damage\n"
    "Notes  : Sustain";

    Character[2].ULT =
    "Deflect Boost\n"
    "Effect : +20% chance DEFLECT\n"
    "Durasi : 4 turn\n"
    "Notes  : Counter";

    // RARE
    Character[3].ULT =
    "Berserker Mode\n"
    "Effect : Damage x2.5\n"
    "Durasi : 2 turn\n"
    "Notes  : High risk";

    Character[4].ULT =
    "Rigby Buff\n"
    "Effect : +15% Crit Chance\n"
    "        +1.5x Damage\n"
    "Durasi : 2 turn\n"
    "Notes  : DPS boost";

    Character[5].ULT =
    "Aren Shield\n"
    "Effect : -50% damage taken\n"
    "        +20% deflect\n"
    "Durasi : 3 turn\n"
    "Notes  : Tank";

    Character[6].ULT =
    "Arpin Heal\n"
    "Heal   : 40% Max HP\n"
    "Notes  : Recovery";

    Character[7].ULT =
    "Multi Strike\n"
    "Hit    : 4x attack\n"
    "Crit   : tiap hit bisa crit\n"
    "Notes  : Burst multi";

    Character[8].ULT =
    "Slot Gacor\n"
    "x10 : roll = 1\n"
    "x4  : 2-5\n"
    "x2  : 6-35\n"
    "x1.5: 36-70\n"
    "x0.5: 71-100\n"
    "Notes : RNG burst";

    // SR
    Character[9].ULT =
    "Marked System\n"
    "Stack : max 6\n"
    "Exec  : 1.2x - 4.0x damage\n"
    "Limit : 10 turn\n"
    "Notes : Setup burst";

    Character[10].ULT =
    "Revive Mode\n"
    "Effect : Auto revive\n"
    "Heal   : 50% HP\n"
    "Limit  : 3x\n"
    "Notes  : Sustain";

    Character[11].ULT =
    "Desperate Memory\n"
    "Scaling : makin rendah HP makin sakit\n"
    "Bonus   : lifesteal saat critical HP\n"
    "Notes   : Clutch";

    // SSR
    Character[12].ULT =
    "Marlong Mode\n"
    "Stack : max 6\n"
    "Durasi: 8 turn\n"
    "Burst : Base Damage * stack\n"
    "Notes : Scaling DPS";

    Character[13].ULT =
    "Dark Force\n"
    "HP <100% : x1.5\n"
    "HP <70%  : x2.0\n"
    "HP <50%  : x2.5\n"
    "HP <30%  : x3.0\n"
    "Durasi : 8 turn\n"
    "Notes  : Comeback";
}

int calcDamage(int level, int growth) {
    if (level == 0) return 0;

    return growth + calcDamage(level - 1, growth);
}

int calcCrit(int level, int growth) {
    if (level == 0) return 0;

    int add = 0;
    if (level % 5 == 0) add = growth;

    return add + calcCrit(level - 1, growth);
}

int calcDef(int level, int growth) {
    if (level == 0) return 0;

    int add = 0;
    if (level % 2 == 0) add = growth;

    return add + calcDef(level - 1, growth);
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

    Character[12].design = R"ASCII(
                    -,,,__
                     \    ``~~--,,__                /   /
                     /              ``~~--,,_     //--//
          _,,,,-----,\              ,,,,---- >   (c  c)\
      ,;''            `\,,,,----''''   ,,-'''---/   /_ ;___        -,_ 
     ( ''---,;====;,----/             (-,,_____/  /'/ `;   '''''----\ `:.
     (                 '               `      (oo)/   ;~~~~~~~~~~~~~/--~
      `;_           ;    \            ;   \   `  ' ,,' 
         ```-----...|     )___________|    )-----''
                        \   /             \   \\ 
                        /  /,              `\   \\ 
                   ,'---\ \              ,---`,;,
                         ```
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
}

void UpgradeSystem() {
    int lvl = currentplayer.level;

    for (int i = 0; i < 14; i++) {

        int dmg = 0, crit = 0, def = 0;

        if (Character[i].rarity == "C") {
            dmg = calcDamage(lvl, 2);
            crit = calcCrit(lvl, 1);
            def = calcDef(lvl, 2);
        }
        else if (Character[i].rarity == "R") {
            dmg = calcDamage(lvl, 2);
            crit = calcCrit(lvl, 1);
            def = calcDef(lvl, 2);
        }
        else if (Character[i].rarity == "SR") {
            dmg = calcDamage(lvl, 3);
            crit = calcCrit(lvl, 2);
            def = calcDef(lvl, 2);
        }
        else if (Character[i].rarity == "SSR") {
            dmg = calcDamage(lvl, 4);
            crit = calcCrit(lvl, 3);
            def = calcDef(lvl, 3);
        }

    }
}

void StatsCharacter() {

    Character[0].nama = "Ireng_Jogja";
    Character[0].Base_Damage = 20;
    Character[0].Base_Hp = 120;
    Character[0].def = 10;
    Character[0].crital_chance = 10;
    Character[0].crital_damage = 150;
    Character[0].ULT = "";
    Character[0].rarity = "C";
    Character[0].unlock = false;

    Character[1].nama = "Laba_Laba_Sunda";
    Character[1].Base_Damage = 18;
    Character[1].Base_Hp = 100;
    Character[1].def = 8;
    Character[1].crital_chance = 25;
    Character[1].crital_damage = 170;
    Character[1].ULT = "";
    Character[1].rarity = "C";
    Character[1].unlock = false;

    Character[2].nama = "Sawit_Bantul";
    Character[2].Base_Damage = 15;
    Character[2].Base_Hp = 150;
    Character[2].def = 20;
    Character[2].crital_chance = 5;
    Character[2].crital_damage = 130;
    Character[2].ULT = "";
    Character[2].rarity = "C";
    Character[2].unlock = false;

    // RARE
    Character[3].nama = "Kevin_Hitam";
    Character[3].Base_Damage = 35;
    Character[3].Base_Hp = 90;
    Character[3].def = 5;
    Character[3].crital_chance = 20;
    Character[3].crital_damage = 200;
    Character[3].ULT = "";
    Character[3].rarity = "R";
    Character[3].unlock = false;

    Character[4].nama = "Rigby_Wonosobo";
    Character[4].Base_Damage = 28;
    Character[4].Base_Hp = 130;
    Character[4].def = 12;
    Character[4].crital_chance = 15;
    Character[4].crital_damage = 160;
    Character[4].ULT = "";
    Character[4].rarity = "R";
    Character[4].unlock = false;

    Character[5].nama = "Aren_Gentong";
    Character[5].Base_Damage = 22;
    Character[5].Base_Hp = 180;
    Character[5].def = 25;
    Character[5].crital_chance = 10;
    Character[5].crital_damage = 140;
    Character[5].ULT = "";
    Character[5].rarity = "R";
    Character[5].unlock = false;

    Character[6].nama = "Arpin_Gontor";
    Character[6].Base_Damage = 18;
    Character[6].Base_Hp = 200;
    Character[6].def = 30;
    Character[6].crital_chance = 5;
    Character[6].crital_damage = 130;
    Character[6].ULT = "";
    Character[6].rarity = "R";
    Character[6].unlock = false;

    Character[7].nama = "Mister_orange";
    Character[7].Base_Damage = 24;
    Character[7].Base_Hp = 110;
    Character[7].def = 10;
    Character[7].crital_chance = 18;
    Character[7].crital_damage = 150;
    Character[7].ULT = "";
    Character[7].rarity = "R";
    Character[7].unlock = false;

    Character[8].nama = "Slot_Gacor";
    Character[8].Base_Damage = 15;
    Character[8].Base_Hp = 100;
    Character[8].def = 8;
    Character[8].crital_chance = 40;
    Character[8].crital_damage = 250;
    Character[8].ULT = "";
    Character[8].rarity = "R";
    Character[8].unlock = false;

    // SR (EPIC)
    Character[9].nama = "Hanip_Ninja";
    Character[9].Base_Damage = 45;
    Character[9].Base_Hp = 110;
    Character[9].def = 10;
    Character[9].crital_chance = 30;
    Character[9].crital_damage = 220;
    Character[9].ULT = "";
    Character[9].rarity = "SR";
    Character[9].unlock = false;

    Character[10].nama = "Mr_Kucing";
    Character[10].Base_Damage = 32;
    Character[10].Base_Hp = 160;
    Character[10].def = 18;
    Character[10].crital_chance = 20;
    Character[10].crital_damage = 170;
    Character[10].ULT = "";
    Character[10].rarity = "SR";
    Character[10].unlock = false;

    Character[11].nama = "Imissher_Kaliurang";
    Character[11].Base_Damage = 25;
    Character[11].Base_Hp = 120;
    Character[11].def = 12;
    Character[11].crital_chance = 25;
    Character[11].crital_damage = 180;
    Character[11].ULT = "";
    Character[11].rarity = "SR";
    Character[11].unlock = false;

    // SSR (LEGENDARY)
    Character[12].nama = "Marlong";
    Character[12].Base_Damage = 50;
    Character[12].Base_Hp = 200;
    Character[12].def = 20;
    Character[12].crital_chance = 25;
    Character[12].crital_damage = 200;
    Character[12].ULT = "";
    Character[12].rarity = "SSR";
    Character[12].unlock = false;

    Character[13].nama = "Anakin_Maguwoharjo";
    Character[13].Base_Damage = 60;
    Character[13].Base_Hp = 250;
    Character[13].def = 15;
    Character[13].crital_chance = 45;
    Character[13].crital_damage = 250;
    Character[13].ULT = "";
    Character[13].rarity = "SSR";
    Character[13].unlock = false;
}

void StatsMonster() {
    Monster[0].nama = "Shadow_Fang";
    Monster[0].Base_Damage = 10;
    Monster[0].Base_Hp = 160;
    Monster[0].def = 12;
    Monster[0].crital_chance = 20;
    Monster[0].crital_damage = 170;
    Monster[0].level = 7;
    Monster[0].aggression = 75;
    Monster[0].isBoss = false;
    Monster[0].design = R"MONSTER(
        /\_/\  
       ( o.o ) 
        > ^ <  
      /       \
     /|       |\
      |  |||  |
      |  |||  |
       \_____/
     SHADOW FANG
)MONSTER";

    Monster[1].nama = "Ayam_Galak";
    Monster[1].Base_Damage = 8;
    Monster[1].Base_Hp = 100;
    Monster[1].def = 5;
    Monster[1].crital_chance = 10;
    Monster[1].crital_damage = 130;
    Monster[1].level = 2;
    Monster[1].aggression = 60;
    Monster[1].isBoss = false;
}

void IsiData() {
    StatsCharacter();
    initCharacter();
    StatsMonster();
    IsiULT();
}

// ===== LORE =====
void lore() {
    system("cls");

    setWarna(11);
    ketik("LUMINARA — 20XX\n", 50);

    setWarna(7);
    ketik("11 September\n\n", 50);
    tunggu(800);

    ketik("Di dunia hewan dimana semua damai...\n\n");
    tunggu(1000);

    ketik("Lalu...\n\n");
    tunggu(700);

    setWarna(12);
    ketik("DUARRR!!!\n\n", 80);
    Beep(750, 200);
    tunggu(500);

    setWarna(14);
    ketik("Langit retak.\n\n");
    tunggu(800);

    setWarna(13);
    ketik("Bukan sekadar ledakan...\n");
    ketik("sesuatu... terbuka.\n\n");
    tunggu(1000);

    setWarna(11);
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

    setWarna(4);
    ketik("Monster.\n\n", 60);
    tunggu(1000);

    setWarna(10);
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

    setWarna(13);
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

    setWarna(10);
    ketik("adalah Keeper mereka.\n", 80);

    setWarna(7);

    tunggu(1500);
    cout << "\n\nTekan ENTER untuk lanjut...";
    // FIXED: ganti cin.ignore() + cin.get() dengan pause()
    pause();

    system("cls");
}

// ===== LOGO / MAIN MENU =====
void Logo() {
    int pilih = 0;
    int pilih1 = 0;

    ifstream Cek("save.txt");

    if (Cek.peek() == EOF) {
        cout << R"(
+-----------------------------------------------+
|                                               |
|         F E R A L   A W A K E N E D           |
|                                               |
+-----------------------------------------------+
|                    MENU                       |
+-----------------------------------------------+
| 1. New Game                                   |
| 2. Exit                                       |
+-----------------------------------------------+
)";
        cout << "Option darling? ";
        cin >> pilih1;
        cin.ignore(1000, '\n'); // FIXED: clear buffer setelah cin >>
    } else {
        cout << R"(
+-----------------------------------------------+
|                                               |
|         F E R A L   A W A K E N E D           |
|                                               |
+-----------------------------------------------+
|                    MENU                       |
+-----------------------------------------------+
| 1. Continue                                   |
| 2. Reset Data                                 |
| 3. Exit                                       |
+-----------------------------------------------+
)";
        cout << "Option darling? ";
        cin >> pilih;
        cin.ignore(1000, '\n'); // FIXED: clear buffer setelah cin >>
    }
    Cek.close();

    if (pilih1 == 1) {
        lore();
        ofstream Lore("save.txt", ios::app);
        Lore << "Lore_True" << " ";
        setWarna(10);
        ketik("Masukan Nama kamu Keeper: ");
        tunggu(1000);
        setWarna(7);
        cin >> currentplayer.username;
        cin.ignore(1000, '\n'); // FIXED: clear buffer setelah cin >>
        Lore << currentplayer.username << " ";
        Lore.close();
    }

    if (pilih1 == 2) {
        exit(0);
    }
    if (pilih == 1) {
        ifstream Load("save.txt");
        string token;
        while (Load >> token) {
            if (token != "Lore_True" && token != "Tutor_True" && token.substr(0,6) != "primo:") {
                bool ituKarakter = false;
                for (int i = 0; i < 14; i++)
                    if (Character[i].nama == token) { ituKarakter = true; break; }
                if (!ituKarakter) currentplayer.username = token;
            }
        }
        Load.close();
        return;
    }
    if (pilih == 2) {
        ofstream Reset("save.txt");
        Reset.close();
        cout << "RESET BERHASIL\n";
        system("pause");
        exit(0);
    }
    if (pilih == 3) {
        exit(0);
    }
}

// ===== TUTORIAL =====
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
    ketik("Tekan ENTER untuk lanjut ke Test Fight...");
    // FIXED: ganti cin.ignore() + cin.get() dengan pause()
    pause();

    system("cls");
}

// ===== BATTLE UI =====
void BattleUI(int HpKawan, int HpMusuh, int UltPoin, int MarkStatus, int MarkTurn, int Marked, bool ReviveK, int JumlahRevive, int MaxTurnK, bool &MarlongMode, int &JumlahMarlong, int &MarlongTurn, bool DarkForce, int DarkForceTurn) {
    string pad = "";
    setWarna(7);
    cout << "\n\n\n";
    cout << pad << "+------------------------------------------------------+\n";
    cout << pad << "|                                                      |\n";
    cout << pad << "|   ";
    setWarna(14); cout << "[1.FIGHT]   ";
    setWarna(6);  cout << "[2.DEFEND]   ";
    if (MarkStatus == 1) {
        setWarna(5);
        cout << "[MARKED]  ";
    } else if (UltPoin >= 4) {
        setWarna(11);
        cout << "[3.ULT]   ";
    } else {
        setWarna(12);
        cout << "[3.ULT]   ";
    }
    setWarna(13); cout << "[4.INVENTORY]";
    setWarna(7);  cout << "   |\n";
    cout << pad << "|                                                      |\n";
    cout << pad << "+------------------------------------------------------+\n";
    cout << "HP Kamu: " << HpKawan << "  |  HP Musuh: " << HpMusuh << "  |  ULT Point: " << UltPoin << "/4\n";
    if (ReviveK) {
        cout << "MAX TURN " << MaxTurnK << "/5";
    }
    if (MarkStatus == 1) {
        setWarna(5);
        cout << "MARK TURN " << MarkTurn << "/10 || ENEMY MARKED " << Marked << "/6";
        setWarna(7);
    }
    if (MarlongMode) {
        setWarna(4);
        cout << "MARLONG TURN " << MarlongTurn << "/8 || MARLONG HEAT " << JumlahMarlong << "/6";
        setWarna(7);
    }
    if (DarkForce) {
        setWarna(5);
        cout << "DARK TURN " << DarkForceTurn << "/8";
        setWarna(7);
    }
    cout << "\nPilih aksi (1-4): ";
}

// ===== ULT =====
void doULT(int CharacterKawan, int CharacterMusuh, int &HpKawan, int &HpMusuh, bool &statusULT, int &PointULT, int &BuffSawit, int &BuffKevin, int &BuffRigby, int &BuffAren, int &MarkStatus, int &Marked, int &MarkTurn, bool &ReviveK, int &JumlahRevive, int &MaxTurnK, bool &MarlongMode, bool &DarkForce) {
    switch (CharacterKawan) {
        case 0:
            cout << "Serangan Ireng!\n";
            Sleep(1000);
            PointULT = 0;
            HpMusuh -= (int)((Character[CharacterKawan].Base_Damage * (Character[CharacterKawan].crital_damage / 100.0)) * 1.2);
            cout << "DAMAGE: " << (int)((Character[CharacterKawan].Base_Damage * (Character[CharacterKawan].crital_damage / 100.0)) * 1.2) << "\n";
            statusULT = false;
            Sleep(1000);
            break;

        case 1:
            cout << "Life Steal Jaring!\n";
            Sleep(1000);
            PointULT = 0;
            HpMusuh -= Character[CharacterKawan].Base_Damage;
            HpKawan += (int)(Character[CharacterKawan].Base_Damage * 0.5);
            cout << "DAMAGE: " << Character[CharacterKawan].Base_Damage
                 << "\nLIFESTEAL: " << (int)(Character[CharacterKawan].Base_Damage * 0.5) << "\n";
            statusULT = false;
            Sleep(1000);
            break;

        case 2:
            cout << "ULT Sawit_Bantul +20% CHANCE DEFLECT\n";
            statusULT = false;
            BuffSawit = 4;
            PointULT = 0;
            Sleep(1000);
            break;

        case 3:
            cout << "BERSEKER MODE (2.5X ATTACK BONUS AND -30% OF YOUR HP)\n";
            BuffKevin = 2;
            statusULT = false;
            PointULT = 0;
            Sleep(1000);
            break;

        case 4:
            cout << "RIGBY RIGBY RIGBY EHEM EHEM 15% CRIT BONUS AND 1.5X DAMAGE\n";
            BuffRigby = 2;
            statusULT = false;
            PointULT = 0;
            Sleep(1000);
            break;

        case 5:
            cout << "Aduh Aren Please (REDUCE DAMAGE 50% AND 20% MORE DEFLECT)\n";
            BuffAren = 3;
            statusULT = false;
            PointULT = 0;
            Sleep(1000);
            break;

        case 6:
            cout << "Pin Arpin Pin please Pin Ulti dulu (HEAL FOR 40% HP)\n";
            HpKawan += (int)(Character[CharacterKawan].Base_Hp * 0.4);
            statusULT = false;
            PointULT = 0;
            Sleep(1000);
            break;

        case 7: {
            cout << "SERANG BERTUBI TUBI HUAWCHAW (4 HIT)\n";
            for (int i = 0; i < 4; i++) {
                int damage = Character[CharacterKawan].Base_Damage;
                int roll = rand() % 100 + 1;
                if (roll <= Character[CharacterKawan].crital_chance) {
                    damage = (int)(damage * (Character[CharacterKawan].crital_damage / 100.0));
                    cout << "CRIT HIT " << i+1 << "! ";
                }
                HpMusuh -= damage;
                cout << "Hit " << i+1 << ": " << damage << endl;
                Sleep(300);
            }
            statusULT = false;
            PointULT = 0;
            Sleep(1000);
            break;
        }

        case 8: {
            int roll, damage;
            cout << "SLOT GACOR EUY PLEASE GACOR\n";
            for (int i = 0; i < 10; i++) {
                int temp = rand() % 100 + 1;
                cout << "\rRolling: " << temp << "   ";
                Sleep(100);
            }
            roll = rand() % 100 + 1;
            cout << "\rHASIL: " << roll << "     \n";
            float multiplier = 1.0;
            if (roll == 1)        { multiplier = 10;  cout << "WHAT? x10\n"; }
            else if (roll <= 5)   { multiplier = 4;   cout << "JACKPOT!!! x4\n"; }
            else if (roll <= 35)  { multiplier = 2;   cout << "GACOR x2\n"; }
            else if (roll <= 70)  { multiplier = 1.5; cout << "Lumayan x1.5\n"; }
            else                  { multiplier = 0.5; cout << "TOLOL x0.5\n"; }
            damage = (int)((Character[CharacterKawan].Base_Damage * (Character[CharacterKawan].crital_damage / 100.0)) * multiplier);
            HpMusuh -= damage;
            cout << "DAMAGE: " << damage << endl;
            statusULT = false;
            PointULT = 0;
            Sleep(1000);
            break;
        }

        case 9:
            if (MarkedBool) {
                MarkStatus = 1;
                cout << "Si hanif tukang ninja ";
                setWarna(5);
                cout << "MARKED ACTIVE";
                setWarna(7);
                MarkedBool = false;
                return;
            }
            {
                int damage = 0;
                cout << "MARKED EXECUTE";
                if (Marked == 0) damage = (int)((Character[CharacterKawan].Base_Damage * (Character[CharacterKawan].crital_damage / 100.0)) * 1.2);
                if (Marked == 1) damage = (int)((Character[CharacterKawan].Base_Damage * (Character[CharacterKawan].crital_damage / 100.0)) * 1.5);
                if (Marked == 2) damage = (int)((Character[CharacterKawan].Base_Damage * (Character[CharacterKawan].crital_damage / 100.0)) * 2.0);
                if (Marked == 3) damage = (int)((Character[CharacterKawan].Base_Damage * (Character[CharacterKawan].crital_damage / 100.0)) * 2.5);
                if (Marked == 4) damage = (int)((Character[CharacterKawan].Base_Damage * (Character[CharacterKawan].crital_damage / 100.0)) * 3.0);
                if (Marked == 5) damage = (int)((Character[CharacterKawan].Base_Damage * (Character[CharacterKawan].crital_damage / 100.0)) * 3.5);
                if (Marked == 6) damage = (int)((Character[CharacterKawan].Base_Damage * (Character[CharacterKawan].crital_damage / 100.0)) * 4.0);
                HpMusuh -= damage;
                cout << " TOTAL " << damage << endl;
                Marked = 0;
                MarkTurn = 0;
                MarkStatus = 0;
                statusULT = false;
                MarkedBool = true;
                PointULT = 0;
                Sleep(1000);
            }
            break;

        case 10:
            if (JumlahRevive <= 2) {
                ReviveK = true;
                cout << "MR KUCING MODE AKTIF\n";
            } else {
                cout << "ULTI GAGAL MELEBIHI BATAS\n";
            }
            MaxTurnK = 0;
            PointULT = 0;
            statusULT = false;
            Sleep(1000);
            break;

        case 11: {
            cout << "DESPERATE MEMORY\n";
            float hpPercent = (float)HpKawan / Character[CharacterKawan].Base_Hp;
            float multiplier = 1 + (1 - hpPercent) * 2;
            int roll = rand() % 100 + 1;
            int damage;
            if (roll <= Character[CharacterKawan].crital_chance) {
                damage = (int)((Character[CharacterKawan].Base_Damage * (Character[CharacterKawan].crital_damage / 100.0)) * multiplier);
                setWarna(4);
                cout << " CRITICAL HIT!\n";
            } else {
                damage = (int)(Character[CharacterKawan].Base_Damage * multiplier);
            }
            setWarna(11);
            cout << "HP: " << HpKawan << "/" << Character[CharacterKawan].Base_Hp << endl;
            setWarna(14);
            cout << "MULTIPLIER: x" << multiplier << endl;
            setWarna(12);
            HpMusuh -= damage;
            cout << " DAMAGE: " << damage << endl;
            if (hpPercent < 0.2) {
                int heal = (int)(damage * 0.2);
                HpKawan += heal;
                setWarna(4);
                cout << " CRITICAL CONDITION!\n";
                setWarna(10);
                cout << " LIFESTEAL: +" << heal << endl;
            }
            setWarna(7);
            PointULT = 0;
            statusULT = false;
            Sleep(1000);
            break;
        }

        case 12:
            cout << "SEBAT SEBAT DULU EUY MARLONG ENAK BET\n";
            MarlongMode = true;
            statusULT = false;
            PointULT = 0;
            Sleep(1000);
            break;

        case 13:
            system("cls");
            for (int i = 0; i < 30; i++) {
                setWarna(5);
                cout << "THE DARK SHALL RECEIVE\n";
                Sleep(10);
            }
            DarkForce = true;
            setWarna(7);
            statusULT = false;
            PointULT = 0;
            break;

        default:
            cout << "ULT karakter ini belum diimplementasi.\n";
            statusULT = false;
            PointULT = 0;
            break;
    }
}

// ===== AI =====
void AI(int CharacterMonster, int &HpKawan, int &HpMusuh, bool Defend, int CharacterKawan, int &PointULT, int &BuffSawit, int &BuffAren, bool ReviveK, bool MarlongMode, bool DarkForce) {
    int Buff = 0;
    int BuffA = 0;

    if (Defend) {
        if (BuffAren > 0) {
            cout << "50% DEFEND + 20% DEFLECT\n";
            BuffA = 50;
            Buff = 20;
            BuffAren--;
        }

        int roll = rand() % 100 + 1;
        float reduction = (Character[CharacterKawan].def + BuffA) / 100.0f;
        if (reduction > 0.8f) reduction = 0.8f;

        int damage = Monster[CharacterMonster].Base_Damage;
        int finalDamage = (int)(damage * (1 - reduction));
        if (finalDamage < 1) finalDamage = 1;

        if (BuffSawit > 0) {
            cout << "+20% CHANCE DEFLECT " << BuffSawit << "\n";
            Buff = 20;
            BuffSawit--;
        }

        if (roll <= 60 - Buff) {
            cout << "BLOCK! Damage diterima: " << finalDamage << "\n";
            HpKawan -= finalDamage;
        } else {
            cout << "DEFLECT! Damage diterima: " << finalDamage << "\n";
            HpKawan -= finalDamage;
            int reflectDamage = (int)(damage * 0.7);
            HpMusuh -= reflectDamage;
            cout << "Reflect damage ke musuh: " << reflectDamage << "\n";
            if (BuffSawit == 0 && BuffAren == 0 && ReviveK == false && MarlongMode == false && DarkForce == false) {
                PointULT++;
            }
        }
        Sleep(1000);
    } else {
        cout << "Musuh menyerang! Damage: " << Monster[CharacterMonster].Base_Damage << "\n";
        HpKawan -= Monster[CharacterMonster].Base_Damage;
        Sleep(1000);
    }
}

// ===== ATTACK =====
void AttackCharacter(int Aksi, int &HpKawan, int &HpMusuh, int CharacterKawan, bool &Defend, bool &IsULT, int &PointULT, int CharacterMusuh, int &BuffSawit, int &BuffKevin, int &BuffRigby, int &BuffAren, int &MarkStatus, int &Marked, int &MarkTurn, bool &ReviveK, int &JumlahRevive, int &MaxTurnK, bool &MarlongMode, int &JumlahMarlong, int &MarlongTurn, bool &DarkForce, int &DarkForceTurn) {
    int TempBaseDamageCrit = 0;
    int ChangeCrit = 0;
    int TempBaseDamage = 0;
    float BuffK = 1;
    float BuffR = 1;
    int BuffRcrit = 0;

    do {
        system("cls");
        printSideBySide(Character[CharacterKawan].design, Monster[CharacterMusuh].design, 30);
        BattleUI(HpKawan, HpMusuh, PointULT, MarkStatus, MarkTurn, Marked, ReviveK, JumlahRevive, MaxTurnK, MarlongMode, JumlahMarlong, MarlongTurn, DarkForce, DarkForceTurn);
        cin >> Aksi;
        cin.ignore(1000, '\n'); // FIXED: clear buffer setelah cin >> Aksi

        BuffK = 1; BuffR = 1; BuffRcrit = 0;

        if (BuffKevin > 0) {
            cout << "(2.5X BONUS DAMAGE) TURN= " << BuffKevin << endl;
            BuffK = 2.5;
            BuffKevin--;
        }

        if (MarlongMode) {
            cout << "MARLONG BUFF (1.5x) + 15% MORE CRIT EUYY\n";
            BuffR = 1.5;
            BuffRcrit = 15;
        }

        if (BuffRigby > 0) {
            cout << "15 CRIT BONUS AND 1.5X DAMAGE TURN= " << BuffRigby << endl;
            BuffR = 1.5;
            BuffRcrit = 15;
            BuffRigby--;
        }

        if (DarkForce) {
            float hpPercent = (float)HpKawan / Character[CharacterKawan].Base_Hp;
            float DarkMultiplier = 1;
            DarkForceTurn++;
            if (hpPercent < 1.0) DarkMultiplier = 1.5;
            if (hpPercent < 0.7) DarkMultiplier = 2.0;
            if (hpPercent < 0.5) DarkMultiplier = 2.5;
            if (hpPercent < 0.3) DarkMultiplier = 3.0;
            BuffK *= DarkMultiplier;
            cout << "DARK FORCE ACTIVE x" << DarkMultiplier << endl;
            if (DarkForceTurn == 8) {
                DarkForceTurn = 0;
                DarkForce = false;
                cout << "Dark Cancel\n";
                Sleep(1000);
            }
        }

        if (Aksi == 1) {
            ChangeCrit = rand() % 100 + 1;
            if (ChangeCrit <= (Character[CharacterKawan].crital_chance + BuffRcrit)) {
                TempBaseDamageCrit = (int)((Character[CharacterKawan].Base_Damage * (Character[CharacterKawan].crital_damage / 100.0)) * BuffK * BuffR);
                HpMusuh -= TempBaseDamageCrit;
                cout << "CRITICAL HIT! DAMAGE: " << TempBaseDamageCrit << endl;
                if (BuffKevin == 0 && BuffRigby == 0 && MarkStatus == 0 && ReviveK == false && MarlongMode == false && DarkForce == false) {
                    PointULT++;
                }
                if (MarlongMode) {
                    JumlahMarlong++;
                    if (JumlahMarlong > 6) JumlahMarlong = 6;
                }
            } else {
                TempBaseDamage = (int)(Character[CharacterKawan].Base_Damage * BuffK * BuffR);
                HpMusuh -= TempBaseDamage;
                cout << "DAMAGE: " << TempBaseDamage << endl;
            }
            break;
        } else if (Aksi == 2) {
            Defend = true;
            break;
        } else if (Aksi == 3) {
            if (IsULT) {
                doULT(CharacterKawan, CharacterMusuh, HpKawan, HpMusuh, IsULT, PointULT, BuffSawit, BuffKevin, BuffRigby, BuffAren, MarkStatus, Marked, MarkTurn, ReviveK, JumlahRevive, MaxTurnK, MarlongMode, DarkForce);
                if (HpMusuh <= 0) break;
                Sleep(1000);
            } else {
                cout << "ULT belum siap! (" << PointULT << "/4)\n";
                Sleep(1000);
            }
            continue;
        } else {
            cout << "Pilihan tidak valid!\n";
            Sleep(1000);
        }
    } while (true);
}

// ===== FIGHT =====
void Fight(int PilihKarakter,int PilihMusuh) {
    srand((unsigned int)time(0));

    int SelectC = 0;
    int SelectV = 0;
    int TempHPC = 0;
    int TempHPV = 0;
    bool IsDefend = false;
    bool IsULT = false;
    bool Kawan = true;
    bool Musuh = true;
    int Action = 0;
    int PointULT = 0;
    int BuffSawit = 0;
    int BuffKevin = 0;
    int BuffRigby = 0;
    int BuffAren = 0;
    int MarkStatus = 0;
    int Marked = 0;
    int MarkTurn = 0;
    bool ReviveK = false;
    int JumlahRevive = 0;
    int MaxTurnK = 0;
    bool MarlongMode = false;
    int JumlahMarlong = 0;
    int MarlongTurn = 0;
    bool DarkForce = false;
    int DarkForceTurn = 0;

    // Reset global flags untuk fight baru
    MarkedBool = true;
    MarlongBool = true;

    system("cls");
    setWarna(14);
    cout << "=== PILIH KARAKTER ===\n";
    setWarna(7);
    //cout << "[COMMON]  0.Ireng_Jogja  1.Laba_Laba_Sunda  2.Sawit_Bantul\n";
    //cout << "[RARE]    3.Kevin_Hitam  4.Rigby_Wonosobo  5.Aren_Gentong  6.Arpin_Gontor  7.Mister_orange  8.Slot_Gacor\n";
    //cout << "[EPIC]    9.Hanip_Ninja  10.Mr_Kucing  11.Imissher_Kaliurang\n";
    //cout << "[LEGEND]  12.Marlong  13.Anakin_Maguwoharjo\n";
    //cout << "Pilih Fighter (0-13): ";
   // cin >> SelectC;
    SelectC = PilihKarakter;
    //cout << "Pilih Musuh (hanya 0 = Shadow_Fang): ";
    //cin >> SelectV;
    SelectV = PilihMusuh;
    cin.ignore(1000, '\n'); // FIXED: clear buffer setelah cin >>

    TempHPC = Character[SelectC].Base_Hp;
    TempHPV = Monster[SelectV].Base_Hp;
    system("cls");

    while (Kawan && Musuh) {
        IsDefend = false;

        if (ReviveK) {
            MaxTurnK++;
            if (MaxTurnK > 5 || JumlahRevive >= 3) {
                ReviveK = false;
            }
        }

        AttackCharacter(Action, TempHPC, TempHPV, SelectC, IsDefend, IsULT, PointULT, SelectV, BuffSawit, BuffKevin, BuffRigby, BuffAren, MarkStatus, Marked, MarkTurn, ReviveK, JumlahRevive, MaxTurnK, MarlongMode, JumlahMarlong, MarlongTurn, DarkForce, DarkForceTurn);

        if (ReviveK && TempHPC <= 0 && JumlahRevive < 3) {
            TempHPC = (int)(Character[SelectC].Base_Hp * 0.5);
            JumlahRevive++;
            ReviveK = false;
            cout << "MR MR MR REVIVE REVIVE REVIVE BANGKITLAHHHH\n";
            Sleep(1000);
        }

        if (MarlongMode) {
            MarlongTurn++;
            if (MarlongTurn == 8) {
                setWarna(4);
                cout << "\nMARLONG DAMAGE ";
                int marlongDmg = Character[SelectC].Base_Damage * JumlahMarlong;
                TempHPV -= marlongDmg;
                cout << marlongDmg;
                MarlongMode = false;
                MarlongTurn = 0;
                JumlahMarlong = 0;
                Sleep(1000);
                setWarna(7);
                cout << endl;
            }
        }

        if (TempHPC <= 0) { Kawan = false; break; }
        if (TempHPV <= 0) { Musuh = false; break; }

        AI(SelectV, TempHPC, TempHPV, IsDefend, SelectC, PointULT, BuffSawit, BuffAren, ReviveK, MarlongMode, DarkForce);

        if (ReviveK && TempHPC <= 0 && JumlahRevive < 3) {
            TempHPC = (int)(Character[SelectC].Base_Hp * 0.5);
            JumlahRevive++;
            ReviveK = false;
            cout << "MR MR MR REVIVE REVIVE REVIVE BANGKITLAHHHH\n";
            Sleep(1000);
        }

        if (MarkStatus == 1) {
            int roll = rand() % 100 + 1;
            if (roll <= 30) {
                Marked++;
                cout << "MARKED " << Marked << endl;
            }
            if (Marked > 6) Marked = 6;
            Sleep(500);
            MarkTurn++;
            if (MarkTurn > 10) {
                cout << "MARKED FAIL\n";
                Marked = 0;
                MarkStatus = 0;
                IsULT = false;
                PointULT = 0;
            }
        }

        if (PointULT >= 4) {
            PointULT = 4;
            IsULT = true;
        }

        TempHPV = max(0, TempHPV);
        TempHPC = max(0, TempHPC);

        if (TempHPC <= 0) { Kawan = false; break; }
        if (TempHPV <= 0) { Musuh = false; break; }
    }

    system("cls");
    if (!Kawan) {
        setWarna(12);
        cout << "\n=== KAMU KALAH! ===\n";
    } else {
        setWarna(10);
        cout << "\n=== KAMU MENANG! ===\n";
    }
    setWarna(7);
    cout << "\n";
}

// ===== POST-TUTORIAL TEST FIGHT =====
void TestFight() {
    setWarna(14);
    ketik("\n=== TEST FIGHT ===\n", 40);
    setWarna(7);
    ketik("Saatnya cobain battle pertama kamu, Keeper!\n\n");
    tunggu(1000);
    ketik("Tekan ENTER untuk mulai...");
    // FIXED: ganti cin.ignore() + cin.get() dengan pause()
    pause();
    Fight(1,1);
}

// 







// ===== GACHA =====
// Format save.txt: token dipisah spasi
// Lore_True Tutor_True NamaPlayer primo:100 Ireng_Jogja Marlong ...
void simpanData() {
    // Baca dulu flag & nama yang sudah ada di save.txt
    bool adaLore = false, adaTutor = false;
    string namaPlayer = "";
    {
        ifstream f("save.txt");
        string token;
        while (f >> token) {
            if (token == "Lore_True")  adaLore  = true;
            else if (token == "Tutor_True") adaTutor = true;
            else if (token.substr(0,6) != "primo:" ) {
                // cek bukan nama karakter
                bool ituKarakter = false;
                for (int i = 0; i < 14; i++)
                    if (Character[i].nama == token) { ituKarakter = true; break; }
                if (!ituKarakter) namaPlayer = token;
            }
        }
    }
    // Tulis ulang seluruh save.txt
    ofstream f("save.txt");
    if (adaLore)  f << "Lore_True ";
    if (adaTutor) f << "Tutor_True ";
    if (namaPlayer != "") f << namaPlayer << " ";
    f << "primo:" << currentplayer.primo << " ";
    for (int i = 0; i < 14; i++)
        if (Character[i].unlock) f << Character[i].nama << " ";
    f.close();
}

void loadData() {
    ifstream f("save.txt");
    if (!f) { currentplayer.primo = 10; return; }
    string token;
    bool primoKetemu = false;
    while (f >> token) {
        if (token.substr(0,6) == "primo:") {
            currentplayer.primo = stoi(token.substr(6));
            primoKetemu = true;
        } else {
            for (int i = 0; i < 14; i++)
                if (Character[i].nama == token) Character[i].unlock = true;
        }
    }
    if (!primoKetemu) currentplayer.primo = 10;
    f.close();
}

bool sudahPunya(string nama) {
    for (int i = 0; i < 14; i++) {
        if (Character[i].nama == nama && Character[i].unlock) return true;
    }
    return false;
}

int pilihDariRarity(string rarity) {
    int pool[14];
    int n = 0;
    for (int i = 0; i < 14; i++) {
        if (Character[i].rarity == rarity) {
            pool[n] = i;
            n++;
        }
    }
    if (n == 0) return -1;
    return pool[rand() % n];
}

void prosesHasil(string rarity, int& primo) {
    int idx = pilihDariRarity(rarity);
    if (idx == -1) { cout << "Tidak ada karakter dengan rarity ini.\n"; return; }

    string nama = Character[idx].nama;

    cout << "\n>>> HASIL GACHA <<<\n";
    cout << "Rarity : [" << rarity << "]\n";
    cout << "Nama   : " << nama << "\n";

    if (sudahPunya(nama)) {
        cout << "Kamu sudah punya karakter ini! +10 Primo sebagai gantinya.\n";
        primo += 10;
    } else {
        cout << "Selamat! Karakter baru masuk koleksi!\n";
        Character[idx].unlock = true;
    }
    simpanData();
}

void hasilGacha(int arand, int& primo, int rateSSR, int rateSR, int rateR) {
    string rarity;
    if      (arand <= rateSSR)                    rarity = "SSR";
    else if (arand <= rateSSR + rateSR)           rarity = "SR";
    else if (arand <= rateSSR + rateSR + rateR)   rarity = "R";
    else                                          rarity = "C";
    prosesHasil(rarity, primo);
}

void gachaPity(int pity, int& primo) {
    cout << "\n--- GACHA PITY ---\n";
    cout << "Pity kamu saat ini: " << pity << "\n";
    cout << "Rarity yang bisa dipilih:\n";
    if (pity >= 10) cout << "  a. Common (C)\n";
    if (pity >= 20) cout << "  b. Rare (R)\n";
    if (pity >= 25) cout << "  c. Epic (SR)\n";
    if (pity >= 50) cout << "  d. Legendary (SSR)\n";
    cout << "Pilih (a/b/c/d): ";
    char pilih; cin >> pilih;
    cin.ignore(1000, '\n'); // FIXED: clear buffer setelah cin >>

    string rarity = "";
    if      (pilih == 'a' && pity >= 10) rarity = "C";
    else if (pilih == 'b' && pity >= 20) rarity = "R";
    else if (pilih == 'c' && pity >= 25) rarity = "SR";
    else if (pilih == 'd' && pity >= 50) rarity = "SSR";

    if (rarity == "") { cout << "Pilihan tidak valid atau pity belum cukup!\n"; return; }
    prosesHasil(rarity, primo);
}

void gacha(int& primo) {
    int SSR = 5, SR = 20, R = 25;
    int pity = 0;
    char ulang;

    while (true) {
        if (primo < 10) {
            cout << "\nPrimo tidak cukup! Sisa: " << primo << "\n";
            break;
        }

        cout << "\n==============================\n";
        cout << "Primo  : " << primo << "\n";
        cout << "Pity   : " << pity << "\n";
        cout << "Rate SSR saat ini: " << SSR << "%\n";
        cout << "------------------------------\n";
        cout << "1. Gacha biasa (random)\n";
        cout << "2. Gacha pity (pilih rarity)\n";
        cout << "3. Keluar dari gacha\n";
        cout << "Pilih: ";

        int opsi; cin >> opsi;
        cin.ignore(1000, '\n'); // FIXED: clear buffer setelah cin >>
        if (opsi == 3) break;

        primo -= 10;
        int acha = rand() % 100 + 1;

        if (opsi == 1) {
            hasilGacha(acha, primo, SSR, SR, R);
            if (acha <= SSR) {
                cout << "[HOKI] Dapet SSR! Pity & rate di-reset.\n";
                pity = 0; SSR = 5;
            } else {
                pity++; SSR++;
                cout << "[PITY] Rate SSR naik ke: " << SSR << "%\n";
            }
        } else if (opsi == 2) {
            if (pity < 10) {
                cout << "Pity belum cukup! Minimal pity 10.\n";
                primo += 10;
            } else {
                gachaPity(pity, primo);
                pity = 0;
            }
        } else {
            cout << "Opsi tidak valid!\n";
            primo += 10;
        }

        cout << "\nGacha lagi? (y/n): ";
        cin >> ulang;
        cin.ignore(1000, '\n'); // FIXED: clear buffer setelah cin >>
        if (ulang == 'n' || ulang == 'N') break;
    }

    cout << "\nKeluar dari Gacha. Sisa Primo: " << primo << "\n";
}

void koleksi() {
    cout << "\n======= KOLEKSI KAMU =======\n";
    bool ada = false;
    for (int i = 0; i < 14; i++) {
        if (Character[i].unlock) {
            cout << "- [" << Character[i].rarity << "] " << Character[i].nama << "\n";
            ada = true;
        }
    }
    if (!ada) cout << "(Belum ada koleksi)\n";
    cout << "=============================\n";
}

void daftarchara() {
    system("cls");
    int pilih;
    cout << "\n======= DAFTAR KARAKTER (FULL STATS) =======\n";

    for (int i = 0; i < 14; i++) {
        cout << "\n====================================\n";

        cout << "[" << Character[i].rarity << "] " << Character[i].nama;

        if (Character[i].unlock)
            cout << " (UNLOCKED)\n";
        else
            cout << " (LOCKED)\n";

        cout << "------------------------------------\n";
        cout << "HP          : " << Character[i].Base_Hp << "\n";
        cout << "Damage      : " << Character[i].Base_Damage << "\n";
        cout << "Defense     : " << Character[i].def << "\n";
        cout << "Crit Chance : " << Character[i].crital_chance << "%\n";
        cout << "Crit Damage : " << Character[i].crital_damage << "%\n";
        cout << "ULT         : " << Character[i].ULT << "\n";

        if (Character[i].unlock) {
            cout << "\n" << Character[i].design << "\n";
        } else {
            cout << "\n(LOCKED)\n";
        }
    }

    cout << "\n====================================\n";

    cout << "Ingin menampilkan data secara spesifik? (1/0)";
    cin >> pilih;
    cin.ignore(1000, '\n'); // FIXED: clear buffer setelah cin >>
    if (pilih == 1) tampilSort();
}


void quickSort(int idx[], int low, int high, int mode) {
    if (low >= high) return;

    int pivot;
    
    // ambil pivot berdasarkan mode
    if (mode == 1) pivot = Character[idx[high]].Base_Hp;
    if (mode == 2) pivot = Character[idx[high]].Base_Damage;
    if (mode == 3) pivot = Character[idx[high]].def;
    if (mode == 4) pivot = Character[idx[high]].crital_chance;
    if (mode == 5) pivot = Character[idx[high]].crital_damage;

    int i = low - 1;

    for (int j = low; j < high; j++) {
        int value;

        if (mode == 1) value = Character[idx[j]].Base_Hp;
        if (mode == 2) value = Character[idx[j]].Base_Damage;
        if (mode == 3) value = Character[idx[j]].def;
        if (mode == 4) value = Character[idx[j]].crital_chance;
        if (mode == 5) value = Character[idx[j]].crital_damage;

        if (value > pivot) { // DESCENDING
            i++;
            int temp = idx[i];
            idx[i] = idx[j];
            idx[j] = temp;
        }
    }

    int temp = idx[i + 1];
    idx[i + 1] = idx[high];
    idx[high] = temp;

    int pi = i + 1;

    quickSort(idx, low, pi - 1, mode);
    quickSort(idx, pi + 1, high, mode);
}

void tampilSort() {
    int mode;
    char pilih;

do {
    cout << "\nSORT BERDASARKAN:\n";
    cout << "1. HP\n";
    cout << "2. Damage\n";
    cout << "3. Defense\n";
    cout << "4. Crit Chance\n";
    cout << "5. Crit Damage\n";
    cout << "Pilih: ";
    cin >> mode;
    cin.ignore(1000, '\n'); // FIXED: clear buffer setelah cin >>

    int idx[14];
    for (int i = 0; i < 14; i++) idx[i] = i;

    quickSort(idx, 0, 13, mode);

    system("cls");
    cout << "\n======= HASIL SORTING =======\n";

    for (int i = 0; i < 14; i++) {
        int k = idx[i];

        cout << "[" << Character[k].rarity << "] " << Character[k].nama
             << " | HP: " << Character[k].Base_Hp
             << " | DMG: " << Character[k].Base_Damage
             << " | DEF: " << Character[k].def
             << " | CRIT: " << Character[k].crital_chance
             << "% | CDMG: " << Character[k].crital_damage
             << "%\n";
    }
    cout << "Ingin melakukan Sort lagi (y/n) ";
    cin >> pilih;
}while (pilih != 'n');
    
}

// ===== GAME MENU (setelah login) =====
void GameMenu() {
    int pilih = 0;
    loadData();
    while (true) {
        system("cls");
        setWarna(11);
        cout << "\n  Selamat datang, Keeper " << currentplayer.username << "!\n";
        cout << "  Primo: " << currentplayer.primo << "\n\n";
        setWarna(7);
        cout << "+-------------------------------+\n";
        cout << "|          GAME MENU            |\n";
        cout << "+-------------------------------+\n";
        cout << "| 1. Battle (Fight)             |\n";
        cout << "| 2. Gacha                      |\n";
        cout << "| 3. Koleksi                    |\n";
        cout << "| 4. Daftar Karakter            |\n";
        cout << "| 5. Keluar ke Main Menu        |\n";
        cout << "+-------------------------------+\n";
        cout << "Pilih: ";
        cin >> pilih;
        cin.ignore(1000, '\n'); // FIXED: clear buffer setelah cin >>

        if (pilih == 1) {
            Fight(1,10);
            cout << "Tekan ENTER untuk kembali ke menu...";
            cin.get(); // FIXED: buffer sudah bersih, langsung cin.get()
        } else if (pilih == 2) {
            gacha(currentplayer.primo);
            cout << "Tekan ENTER untuk kembali ke menu...";
            cin.get(); // FIXED: buffer sudah bersih, langsung cin.get()
        } else if (pilih == 3) {
            koleksi();
            cout << "Tekan ENTER untuk kembali ke menu...";
            cin.get(); // FIXED: buffer sudah bersih, langsung cin.get()
        } else if (pilih == 4) {
            daftarchara();
            cout << "Tekan ENTER untuk kembali ke menu...";
             // FIXED: buffer sudah bersih, langsung cin.get()
        } else if (pilih == 5) {
            break;
        } else {
            cout << "Pilihan tidak valid!\n";
            Sleep(1000);
        }
    }
}

// ===== MAIN =====
int main() {
    IsiData();

    // Pastikan file save.txt ada
    ofstream File("save.txt", ios::app);
    File.close();

    // Main menu / logo
    Logo();

    // Cek apakah tutorial sudah pernah ditampilkan
    bool Tutor = true;
    {
        ifstream Tutorial("save.txt");
        while (Tutorial >> word) {
            if (word == "Tutor_True") {
                Tutor = false;
                break;
            }
        }
        Tutorial.close();
    }

    system("cls");

    if (Tutor) {
        Tutorial1();
        // Simpan flag tutorial
        ofstream SaveTutor("save.txt", ios::app);
        SaveTutor << "Tutor_True" << " ";
        SaveTutor.close();
        // Test Fight langsung setelah tutorial
        TestFight();
    }

    // Masuk ke game menu utama
    GameMenu();

    return 0;
}
