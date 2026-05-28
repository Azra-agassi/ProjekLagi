#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>   // stringstream
#include <vector>    // vector
#include <algorithm> // max
#include <cstdio>    // printf
#include <windows.h>
#include <ctime>
using namespace std;

void PrintSideByside(),setWarna(),StatsCharacter(),initCharacter(),BattleUI(),Fight(),IsiData(),StatsMonster(), AI();

void IsiData() {
    StatsCharacter();
    initCharacter();
    StatsMonster();
}

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
void setWarna(int warna) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), warna);
}

struct Pet {
    string nama;
    int Base_Damage;
    int Base_Hp;
    int def;
    string design;
    int crital_chance;
    int crital_damage;
    string ULT;
};

struct Villain {
    string nama;
    string design;
    int Base_Damage;
    int Base_Hp;
    int def;
    int crital_chance;
    int crital_damage;
    int level;        // scaling musuh
    int aggression;   // seberapa sering attack (AI)
    bool isBoss;      // boss atau bukan
};

Pet Character[15];
Villain Monster[1];
string word;

void StatsMonster() {
Monster[0].nama = "Shadow_Fang";
Monster[0].Base_Damage = 30;
Monster[0].Base_Hp = 1400;
Monster[0].def = 12;
Monster[0].crital_chance = 20;
Monster[0].crital_damage = 170;
Monster[0].level = 7;
Monster[0].aggression = 75;  // sering attack
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
    
}

void StatsCharacter() {
// ================= COMMON =================
Character[0].nama = "Ireng_Jogja";
Character[0].Base_Damage = 20;
Character[0].Base_Hp = 1200;
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
Character[9].nama = "Hanip_Ninja";
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
Character[13].crital_chance = 45;
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

void BattleUI(int HpKawan,int HpMusuh,int UltPoin) {
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

    if (UltPoin >= 4) {
    setWarna(11);
    }
    else {
    setWarna(12); //MERAH
    }
    cout << "[3.ULT]   ";

    setWarna(13);
    cout << "[4.INVENTORY]";

    setWarna(7);
    cout << "   |\n"; //

    cout << pad << "|                                                      |\n";
    cout << pad << "+------------------------------------------------------+\n";
    cout << HpKawan << " " << HpMusuh;
    cout << "\nPilih aksi (1-4): ";
}

void ulti() {
    

}


void AI(int CharacterMonster,int &HpKawan,int &HpMusuh,bool Defend,int CharacterKawan,int &PointULT) {

if (Defend) {
    int roll = rand() % 100 + 1;

    float reduction = Character[CharacterKawan].def / 100.0;

    // cap biar gak OP
    if (reduction > 0.8) reduction = 0.8;

    int damage = Monster[CharacterMonster].Base_Damage;
    int finalDamage = damage * (1 - reduction);

    if (finalDamage < 1) finalDamage = 1;

    if (roll <= 60) {
        cout << "BLOCK!\n";
        HpKawan -= finalDamage;
    }
    else {
        cout << "DEFLECT!\n";
        HpKawan -= finalDamage;

        // reflect sebagian damage 
        int reflectDamage = damage * 0.9; // 90% reflect
        HpMusuh -= reflectDamage;
        PointULT++;
    }
    Sleep(1000);
}

else {
    HpKawan -= Monster[CharacterMonster].Base_Damage;
}



}

void AttackCharacter(int Aksi,int HpKawan,int &HpMusuh,int CharacterKawan,bool &Defend,bool ULTI,int &PointULT,int CharacterMusuh) {
int TempBaseDamageCrit = 0;
int TempDefend = 0;
int ChangeCrit = 0;

do {
    printSideBySide(Character[CharacterKawan].design, Monster[CharacterMusuh].design, 30);
    BattleUI(HpKawan,HpMusuh,PointULT);
    cin >> Aksi;

    if (Aksi == 1) {
        ChangeCrit = rand() % 100 + 1;

        if (ChangeCrit <= Character[CharacterKawan].crital_chance) {
            // Sistem Crit
            TempBaseDamageCrit =
                Character[CharacterKawan].Base_Damage *
                (Character[CharacterKawan].crital_damage / 100.0);

            HpMusuh -= TempBaseDamageCrit;

            cout << "CRIT: " << TempBaseDamageCrit << endl;

            PointULT++;
            Sleep(1000);
            break;
        } 
        else {
            HpMusuh -= Character[CharacterKawan].Base_Damage;
            break;
        }
    }

    else if (Aksi == 2) {
        Defend = true;
        break;
    }

    else if (Aksi == 3) {
        if (ULTI) {
            ulti();
            cout << "MELAKUKAN ULT" << endl;
            break;
        } else {
            cout << "ULT belum siap!" << endl;
            Sleep(1000);
            system("cls");
            continue;
        }
    }

    else {
        cout << "Pilihan tidak valid!" << endl;
        Sleep(1000);
        system("cls");
    }
} while (true);


}


void Fight() {
int SelectC;
int SelectV;
int TempHPC = 0;
int TempHPV = 0;
bool IsDefend;
bool IsULT = false;
bool Kawan = true;
bool Musuh = true;
int Action = 0;
int PointULT = 0;
int EffectUlt = 0;

cout << "Pilih Fighter: "; cin >> SelectC;
cout << "Pilih Musuh: "; cin >> SelectV;
TempHPC = Character[SelectC].Base_Hp;
TempHPV = Monster[SelectV].Base_Hp;
system("cls");

while (Kawan && Musuh) {
IsDefend = false;
system("cls");


AttackCharacter(Action,TempHPC,TempHPV,SelectC,IsDefend,IsULT,PointULT,SelectV);
AI(SelectV,TempHPC,TempHPV,IsDefend,SelectC,PointULT);

if (PointULT >= 4) {
    PointULT = 4;
    cout << PointULT;
    IsULT = true;
}

if (TempHPC <= 0) {
    Kawan = false;
}
if (TempHPV <= 0) {
    Musuh = false;
}



}

}



int main() {

IsiData();
Fight();



}
