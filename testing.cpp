#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <windows.h>
using namespace std;

// 
bool MarkedBool = true;

// ===== FORWARD DECLARATIONS =====
void printSideBySide(const string& kiri, const string& kanan, int jarak);
void setWarna(int warna);
void StatsCharacter();
void initCharacter();
void BattleUI(int HpKawan, int HpMusuh, int UltPoin);
void Fight();
void IsiData();
void StatsMonster();
void AI(int CharacterMonster, int &HpKawan, int &HpMusuh, bool Defend, int CharacterKawan, int &PointULT, int &BuffSawit);

// ===== STRUCTS =====
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
    int level;
    int aggression;
    bool isBoss;
};

Pet Character[15];
Villain Monster[1];

// ===== UTILITY =====
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

void setWarna(int warna) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), warna);
}

// ===== DATA =====
void StatsMonster() {
    Monster[0].nama = "Shadow_Fang";
    Monster[0].Base_Damage = 10;
    Monster[0].Base_Hp = 16000;
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
}

void StatsCharacter() {
    // COMMON
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

    // RARE
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

    // EPIC
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

    // LEGENDARY
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

void IsiData() {
    StatsCharacter();
    initCharacter();
    StatsMonster();
}

// ===== BATTLE UI =====
void BattleUI(int HpKawan, int HpMusuh, int UltPoin, int MarkStatus, int MarkTurn, int Marked, bool ReviveK, int JumlahRevive, int MaxTurnK) {
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
    }
    else if (UltPoin >= 4)  {
    setWarna(11);
    cout << "[3.ULT]   ";
    }
    else {  setWarna(12);
    cout << "[3.ULT]   ";
    }
    setWarna(13); cout << "[4.INVENTORY]";
    setWarna(7);  cout << "   |\n";
    cout << pad << "|                                                      |\n";
    cout << pad << "+------------------------------------------------------+\n";
    cout << "HP Kamu: " << HpKawan << "  |  HP Musuh: " << HpMusuh << "  |  ULT Point: " << UltPoin << "/4\n";
    if (ReviveK) {
        cout << "MAX TURN " << MaxTurnK << "/" << "5";
        }
    if (MarkStatus == 1) {
        setWarna(5);
        cout << "MARK TURN " << MarkTurn << "/" << "10" << " || ENEMY MARKED" << Marked << "/" << "6";
        setWarna(7);
    }
    cout << "\nPilih aksi (1-4): ";
}

// ===== ULT =====
// FIX: renamed parameter 'ULT' -> 'statusULT' to avoid clash with function name
void doULT(int CharacterKawan, int CharacterMusuh, int &HpKawan, int &HpMusuh, bool &statusULT, int &PointULT,int &BuffSawit, int &BuffKevin, int &BuffRigby, int &BuffAren, int &MarkStatus, int &Marked, int &MarkTurn,bool &ReviveK,int &JumlahRevive,int &MaxTurnK) {
    bool check;
    switch (CharacterKawan) {
        case 0:
            cout << "Serangan Ireng!\n";
            Sleep(1000);
            PointULT = 0;
            HpMusuh -= (int)((Character[CharacterKawan].Base_Damage * (Character[CharacterKawan].crital_damage / 100.0)) * 1.2);
            cout << "DAMAGE: " << (int)((Character[CharacterKawan].Base_Damage * (Character[CharacterKawan].crital_damage / 100.0)) * 1.2) << "\n";
            statusULT = false;
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
            break;

        case 2:
            // FIX: tambah break agar tidak fall-through
            cout << "ULT Sawit_Bantul +20% CHANCE DEFLECT\n";
            statusULT = false;
            BuffSawit = 4;
            PointULT = 0;
            break;

        case 3:
            cout << "BERSEKER MODE (2.5X ATTACK BONUS AND - 30% OF YOUR FU**IN HP)\n";
            BuffKevin = 2;
            statusULT = false;
            PointULT = 0;
            break;

        case 4:
            cout << "RIGBY RIGBY RIGBY RIGBY EHEM EHEM 15% CRIT BONUS AND 1.5X DAMAGE\n";
            BuffRigby = 2;
            statusULT = false;
            PointULT = 0;
            break;
        
        case 5:
            cout << "Aduh Aren Please (REDUCE DAMAGE 50% AND 20% MORE DEFLECT)\n";
            BuffAren = 3;
            statusULT = false;
            PointULT = 0;
            break;

        case 6:
            cout << "Pin Arpin Pin please Pin Ulti dulu Pin Pin arpin Pin pin pin (HEAL FOR 40% HP)\n";
            HpKawan += Character[CharacterKawan].Base_Hp * 0.4;
            statusULT = false;
            PointULT = 0;
            break;

        case 7:
        {
            cout << "SERANG BERTUBI TUBI HUAWCHAW (4 HIT)\n";
            for (int i = 0; i < 4; i++) {
                int damage = Character[CharacterKawan].Base_Damage;
            int roll = rand() % 100 + 1;
                if (roll <= Character[CharacterKawan].crital_chance) {
            damage *= (Character[CharacterKawan].crital_damage / 100.0);
                cout << "CRIT HIT " << i+1 << "! ";
                }
             HpMusuh -= damage;
             cout << "Hit " << i+1 << ": " << damage << endl;
             Sleep(300);
                 }
             statusULT = false;
             PointULT = 0;
             break;
        }
        case 8:
        {
                int roll,damage;
                cout << "SLOT GACOR EUY PLEASE GACOR\n";
                for (int i = 0; i < 10; i++) {
                int temp = rand() % 100 + 1;
                 cout << "\rRolling: " << temp << "   ";
                Sleep(100); 
                }

                roll = rand() % 100 + 1;
                cout << "\rHASIL: " << roll << "     \n";
                float multiplier = 1.0;

                if (roll == 1) {
                    multiplier = 10;
                    cout << "WHAT? x10";
                }
                else if (roll <= 5) {
                    multiplier = 4;
                    cout << "JACKPOT!!! x4\n";
                }
                else if (roll <= 35) {
                    multiplier = 2;
                    cout << "GACOR x2\n";
                }
                else if (roll <= 70) {
                    multiplier = 1.5;
                    cout << "Lumayan x1.5\n";
                }
                else {
                    multiplier = 0.5;
                    cout << "TOLOL x0.5\n";
                }

                damage = (Character[CharacterKawan].Base_Damage * (Character[CharacterKawan].crital_damage / 100.0)) * multiplier;
             
                HpMusuh -= damage;

                cout << "DAMAGE: " << damage << endl;

                statusULT = false;
                PointULT = 0;
                break;
        }        


        case 9: 
        if (MarkedBool) {
        MarkStatus = 1;
        cout << "Si hanif tukang ninja "; setWarna(5);
        cout << "MARKED ACTIVE"; setWarna(7);
        MarkedBool = false;
        return;
        }
        int damage;
        cout << "MARKED EXECUTE";
        if (Marked == 0) {
        damage = (Character[CharacterKawan].Base_Damage * (Character[CharacterKawan].crital_damage / 100.0)) * 1.2;
        }
        if (Marked == 1) {
        damage = (Character[CharacterKawan].Base_Damage * (Character[CharacterKawan].crital_damage / 100.0)) * 1.5;
        }
        if (Marked == 2) {
        damage = (Character[CharacterKawan].Base_Damage * (Character[CharacterKawan].crital_damage / 100.0)) * 2.0;
        }
        if (Marked == 3) {
        damage = (Character[CharacterKawan].Base_Damage * (Character[CharacterKawan].crital_damage / 100.0)) * 2.5;
        }
        if (Marked == 4) {
        damage = (Character[CharacterKawan].Base_Damage * (Character[CharacterKawan].crital_damage / 100.0)) * 3.0;
        }
        if (Marked == 5) {
        damage = (Character[CharacterKawan].Base_Damage * (Character[CharacterKawan].crital_damage / 100.0)) * 3.5;
        }
        if (Marked == 6) {
        damage = (Character[CharacterKawan].Base_Damage * (Character[CharacterKawan].crital_damage / 100.0)) * 4.0;
        }
        HpMusuh -= damage;
        cout << " TOTAL " << damage << endl;
        Marked = 0;
        MarkTurn = 0;
        MarkStatus = 0;
        statusULT = false;
        MarkedBool = true;
        PointULT = 0;
        break;


        case 10:
        if (JumlahRevive <= 2) {
        ReviveK = true;
        cout << "MR KUCING MODE AKTIF\n";
        }
        else {
            cout << "ULTI GAGAL MELEBIHI BATAS";
        }
        MaxTurnK = 0;       // WAJIB
        PointULT = 0;
        statusULT = false;
        break;

        case 11: {
        setWarna(13);
        cout << "DESPERATE MEMORY \n";

        float hpPercent = (float)HpKawan / Character[CharacterKawan].Base_Hp;

        float multiplier = 1 + (1 - hpPercent) * 2;

        int damage = Character[CharacterKawan].Base_Damage * multiplier;

        setWarna(11);
        cout << "HP: " << HpKawan << "/" << Character[CharacterKawan].Base_Hp << endl;

        setWarna(14);
        cout << "MULTIPLIER: x" << multiplier << endl;

        setWarna(12);
        HpMusuh -= damage;
        cout << " DAMAGE: " << damage << endl;

        //  lifesteal saat kritis
        if (hpPercent < 0.2) {
            int heal = damage * 0.2;

            HpKawan += heal;

            setWarna(4);
            cout << " CRITICAL CONDITION!\n";

            setWarna(10);
            cout << " LIFESTEAL: +" << heal << endl;
        }

        setWarna(7); // reset warna
        PointULT = 0;
        break;
    }

        case 12: 



        








            PointULT = 0;
            break;
        

        default:
            cout << "ULT karakter ini belum diimplementasi.\n";
            statusULT = false;
            PointULT = 0;
            break;
    }
    Sleep(1000);
}

// ===== AI =====
void AI(int CharacterMonster, int &HpKawan, int &HpMusuh, bool Defend, int CharacterKawan, int &PointULT, int &BuffSawit,int &BuffAren,bool ReviveK) {
    int Buff = 0;
    int BuffA = 0;
    int BuffAd = 0;
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
            cout << "+20% CHANCE DEFLECT" << BuffSawit << "\n";
            Buff = 20;
            BuffSawit--;
        }

        if (roll <= 60 - Buff) {
            cout << "BLOCK! Damage diterima: " << finalDamage << "\n";
            HpKawan -= finalDamage;
        } else {
            cout << "DEFLECT! Damage diterima: " << finalDamage << "\n";
            HpKawan -= finalDamage; // block
            int reflectDamage = (int)(damage * 0.7);
            HpMusuh -= reflectDamage; //deflect
            cout << "Reflect damage ke musuh: " << reflectDamage << "\n";
            if (BuffSawit == 0 && BuffAren == 0 && ReviveK == false) {
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
void AttackCharacter(int Aksi, int &HpKawan, int &HpMusuh, int CharacterKawan, bool &Defend, bool &IsULT, int &PointULT, int CharacterMusuh, int &BuffSawit, int &BuffKevin, int &BuffRigby, int &BuffAren, int &MarkStatus, int &Marked, int &MarkTurn,bool &ReviveK,int &JumlahRevive, int &MaxTurnK) {
    int TempBaseDamageCrit = 0;
    int ChangeCrit = 0;
    int TempBaseDamage = 0;
    float BuffK = 1;
    float BuffR = 1;
    int BuffRcrit = 0;
    do {
        system("cls");
        printSideBySide(Character[CharacterKawan].design, Monster[CharacterMusuh].design, 30);
        BattleUI(HpKawan, HpMusuh, PointULT, MarkStatus, MarkTurn, Marked, ReviveK, JumlahRevive, MaxTurnK);
        cin >> Aksi;

        if (BuffKevin > 0) {
            cout << "(2.5X BONUS DAMAGE) TURN= " << BuffKevin << endl;
            BuffK = 2.5;
            BuffKevin--;
        }

        if (BuffRigby > 0) {
            cout << "15 CRIT BONUS AND 1.5X DAMAGE TURN= " << BuffRigby << endl;
            BuffR = 1.5;
            BuffRcrit = 15;
            BuffRigby--;
        }

        if (Aksi == 1) {
            ChangeCrit = rand() % 100 + 1;
            ChangeCrit = 1; // testing
            if (ChangeCrit <= (Character[CharacterKawan].crital_chance + BuffRcrit)) {
                TempBaseDamageCrit = (int)((Character[CharacterKawan].Base_Damage * (Character[CharacterKawan].crital_damage / 100.0)) * BuffK * BuffR);
                HpMusuh -= TempBaseDamageCrit;
                cout << "CRITICAL HIT! DAMAGE: " << TempBaseDamageCrit << endl;
                if (BuffKevin == 0 && BuffRigby == 0 && MarkStatus == 0 && ReviveK == false) {
                    PointULT++;
                }
            } else {
                TempBaseDamage = Character[CharacterKawan].Base_Damage * BuffK * BuffR;
                HpMusuh -= TempBaseDamage;
                cout << "DAMAGE: " << TempBaseDamage << endl;
            }
            break;
        }
        else if (Aksi == 2) {
            Defend = true;
            break;
        }
        else if (Aksi == 3) {
            if (IsULT) {
                doULT(CharacterKawan, CharacterMusuh, HpKawan, HpMusuh, IsULT, PointULT, BuffSawit ,BuffKevin, BuffRigby,BuffAren, MarkStatus, Marked, MarkTurn,ReviveK, JumlahRevive, MaxTurnK);
                if (HpMusuh <= 0) {
                break;
                }
                Sleep(1000);
            } else {
                cout << "ULT belum siap! (" << PointULT << "/4)\n";
                Sleep(1000);
            }
            continue;
        }
        else {
            cout << "Pilihan tidak valid!\n";
            Sleep(1000);
        }
    } while (true);
}

// ===== FIGHT =====
void Fight() {
    srand((unsigned int)time(0)); // FIX: seed random agar crit tidak selalu sama

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
    int BuffSawit = 0; // FIX: deklarasikan BuffSawit
    int BuffKevin = 0;
    int BuffRigby = 0;
    int BuffAren = 0;
    int MarkStatus = 0;
    int Marked = 0;
    int MarkTurn = 0;
    bool ReviveK = false;
    int JumlahRevive = 0;
    int MaxTurnK = 0;
    // Tampilkan daftar karakter
    cout << "=== PILIH KARAKTER ===\n";
    cout << "[COMMON]  0.Ireng_Jogja  1.Laba_Laba_Sunda  2.Sawit_Bantul\n";
    cout << "[RARE]    3.Kevin_Hitam  4.Rigby_Wonosobo  5.Aren_Gentong  6.Arpin_Gontor  7.Mister_orange  8.Slot_Gacor\n";
    cout << "[EPIC]    9.Hanip_Ninja  10.Mr_Kucing  11.Imissher_Kaliurang\n";
    cout << "[LEGEND]  12.Ryan_Gosling  13.Anakin_Skywalker  14.Thom_Yorke\n";
    cout << "Pilih Fighter (0-14): ";
    cin >> SelectC;

    // FIX: validasi input karakter
    if (SelectC < 0 || SelectC > 14) {
        cout << "Pilihan tidak valid! Default ke 0.\n";
        SelectC = 0;
    }

    cout << "Pilih Musuh (hanya 0 = Shadow_Fang): ";
    cin >> SelectV;

    // FIX: validasi input musuh
    if (SelectV < 0 || SelectV > 0) {
        cout << "Pilihan tidak valid! Default ke 0.\n";
        SelectV = 0;
    }

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
        // FIX: pass BuffSawit ke AI
        AttackCharacter(Action, TempHPC, TempHPV, SelectC, IsDefend, IsULT, PointULT, SelectV, BuffSawit, BuffKevin, BuffRigby, BuffAren, MarkStatus, Marked, MarkTurn,ReviveK,JumlahRevive,MaxTurnK);
     
        // 🔥 CEK MATI DULU (biar clean)
        if (ReviveK && TempHPC <= 0 && JumlahRevive < 3) {
            TempHPC = Character[SelectC].Base_Hp * 0.5;
            JumlahRevive++;
            ReviveK = false;
            cout << "MR MR MR REVIVE REVIVE REVIVE BANGKITLAHHHH";
            Sleep(1000);
        }

        AI(SelectV, TempHPC, TempHPV, IsDefend, SelectC, PointULT, BuffSawit, BuffAren, ReviveK);

        // 🔥 CEK LAGI (kalau mati dari AI)
        if (ReviveK && TempHPC <= 0 && JumlahRevive < 3) {
            TempHPC = Character[SelectC].Base_Hp * 0.5;
            JumlahRevive++;
            ReviveK = false;
            cout << "MR MR MR REVIVE REVIVE REVIVE BANGKITLAHHHH";
            Sleep(1000);
        }
        

        if (MarkStatus == 1) {  //HANIP NINJA
        int roll = rand() % 100 + 1;
        if (roll <= 30) {
        Marked++;
        cout << "MARKED " << Marked;
        }
        if (Marked > 6) {
            Marked = 6;
        }
        Sleep(500);
        MarkTurn++;
        if (MarkTurn > 10) {
            cout << "MARKED FAIL";
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

        if (TempHPC <= 0) { Kawan = false; break; }  // ← tambah break
        if (TempHPV <= 0) { Musuh = false; break; }  // ← tambah break
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
}

// ===== MAIN =====
int main() {
    IsiData();
    Fight();
    return 0;
}
