#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
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
    bool LevelUnlock[14] = {false};
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
    bool isBoss;
};

// ===== GLOBALS =====
Player currentplayer;
Pet Character[14];
Villain Monster[13];
string word;

// ===== FORWARD DECLARATIONS =====
void lore();
void Logo();
void Tutorial1();
void AddXP(int amount);
bool Fight(int PilihKarakter,int PilihMusuh);
void IsiData();
void initCharacter();
void StatsCharacter();
void StatsMonster();
void tampilSort();
void quickSort();
void Xp();
void EndlessMode();
void simpanData();
void StoryMode();
void printSideBySide(const string& kiri, const string& kanan, int jarak);
void BattleUI(int HpKawan, int HpMusuh, int UltPoin, int MarkStatus, int MarkTurn, int Marked, bool ReviveK, int JumlahRevive, int MaxTurnK, bool &MarlongMode, int &JumlahMarlong, int &MarlongTurn, bool DarkForce, int DarkForceTurn);
void doULT(int CharacterKawan, int CharacterMusuh, int &HpKawan, int &HpMusuh, bool &statusULT, int &PointULT, int &BuffSawit, int &BuffKevin, int &BuffRigby, int &BuffAren, int &MarkStatus, int &Marked, int &MarkTurn, bool &ReviveK, int &JumlahRevive, int &MaxTurnK, bool &MarlongMode, bool &DarkForce);
void AI(int CharacterMonster, int &HpKawan, int &HpMusuh, bool Defend, int CharacterKawan, int &PointULT, int &BuffSawit, int &BuffAren, bool ReviveK, bool MarlongMode, bool DarkForce);
void AttackCharacter(int Aksi, int &HpKawan, int &HpMusuh, int CharacterKawan, bool &Defend, bool &IsULT, int &PointULT, int CharacterMusuh, int &BuffSawit, int &BuffKevin, int &BuffRigby, int &BuffAren, int &MarkStatus, int &Marked, int &MarkTurn, bool &ReviveK, int &JumlahRevive, int &MaxTurnK, bool &MarlongMode, int &JumlahMarlong, int &MarlongTurn, bool &DarkForce, int &DarkForceTurn);

// ===== UTILITY =====
void ketik(string text, int delay_ms = 30) {
    for (char c : text) {
        cout << c << flush; //fungsi flush biar gak langsung muncul
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
    cin.ignore(1000, '\n');
    cin.get();
}
 
void printSideBySide(const string& kiri, const string& kanan) {
    string baris;
    int lebar = 35;

    // Pass 1: cari lebar kolom kiri
    stringstream ss(kiri);
    while (getline(ss, baris))
        if ((int)baris.size() > lebar) lebar = baris.size();

    // Pass 2: print baris per baris
    stringstream ssK(kiri), ssKn(kanan);
    string L, R;
    while (true) {
        bool adaK  = (bool)getline(ssK,  L);
        bool adaKn = (bool)getline(ssKn, R);
        if (!adaK && !adaKn) break;
        if (!adaK)  L = "";
        if (!adaKn) R = "";
        printf("%-*s    %s\n", lebar, L.c_str(), R.c_str());
    }
}

void StoryMode() {
    system("cls");
    currentplayer.LevelUnlock[1] = true;

    // Tampilan level
    cout << "=============================\n";
    for (int i = 1; i <= 13; i++) {
        if (i == 1)  cout << "FLOOR 1 (1-5)\n";
        if (i == 6)  cout << "\nFLOOR 2 (6-10)\n";
        if (i == 11) cout << "\nFLOOR 3 (11-13)\n";

        if (currentplayer.LevelUnlock[i]) setWarna(10);
        else setWarna(12);

        cout << "[" << i << "] ";

        if (i == 5 || i == 10) cout << "\n";
    }
    setWarna(7);

    // Pilih karakter
    int pilihKarakter;
    cout << "\n\nList character\n";
    for (int i = 0; i < 14; i++)
        if (Character[i].unlock) cout << i+1 << ". " << Character[i].nama << "  ";

    do {
        cout << "\nPilih Karakter (1-14) (0 = BACK): ";
        cin >> pilihKarakter;
        if (pilihKarakter == 0) return;
        pilihKarakter--;
        if (pilihKarakter >= 0 && pilihKarakter < 14 && Character[pilihKarakter].unlock)
        break;
        cout << "Character Terkunci atau tidak valid!\n";
    } while (true);

    // Pilih level
    int pilihLevel;
    do {
        cout << "Pilih Level (1-13): ";
        cin >> pilihLevel;
        if (pilihLevel < 1 || pilihLevel > 13)
            cout << "Level tidak valid!\n";
        else if (!currentplayer.LevelUnlock[pilihLevel])
            cout << "LEVEL MASIH TERKUNCI!\n";
        else
            break;
    } while (true);

    // Fight & reward satu blok untuk semua level
    bool menang = Fight(pilihKarakter, pilihLevel - 1);

    if (menang) {
        int nextLevel = pilihLevel + 1;

        // Reward hanya kalau belum pernah clear
        if (nextLevel <= 13 && !currentplayer.LevelUnlock[nextLevel]) {
            AddXP(100);
            currentplayer.primo += 10;
            cout << "+10 Primo!\n";
        }

        // Unlock level berikutnya
        if (nextLevel <= 13)
            currentplayer.LevelUnlock[nextLevel] = true;

        simpanData();
        cout << "Level " << pilihLevel << " selesai!\n";
    } else {
        cout << "Kamu kalah! Coba lagi.\n";
    }
}

void EndlessMode() {
    system("cls");

    cout << "=============================\n";
    cout << "      ENDLESS MODE\n";
    cout << "=============================\n";
    for (int i = 0; i < 14; i++)
        if (Character[i].unlock) cout << i+1 << ". " << Character[i].nama << "  ";

    int pilihKarakter;
    do {
        cout << "\nPilih Karakter (1-14) (0 BACK): ";
        cin >> pilihKarakter;
        if (pilihKarakter == 0) return;
        pilihKarakter--;
    } while (pilihKarakter < 0 || pilihKarakter >= 14 || !Character[pilihKarakter].unlock);

    int wave    = 1;
    float multi = 1.0f;
    int hpAsli  = Monster[0].Base_Hp;
    int dmgAsli = Monster[0].Base_Damage;

    while (true) {
        Monster[0].Base_Hp     = (int)(hpAsli  * multi);
        Monster[0].Base_Damage = (int)(dmgAsli * multi);

        system("cls");
        setWarna(14); cout << "=== WAVE " << wave << " (x" << multi << ") ===\n";
        setWarna(11); cout << Monster[0].nama << " | HP: " << Monster[0].Base_Hp << " | DMG: " << Monster[0].Base_Damage << "\n";
        setWarna(7);  cout << "Tekan ENTER..."; cin.ignore(1000,'\n'); cin.get();

        bool menang = Fight(pilihKarakter, 0);

        Monster[0].Base_Hp     = hpAsli;
        Monster[0].Base_Damage = dmgAsli;

        if (!menang) break;

        AddXP((int)(50 * multi));
        currentplayer.primo += 5; cout << "+5 Primo!\n"; 
        simpanData();

        multi += 0.2f;
        wave++;

        int pilih;
        setWarna(10); cout << "Wave selesai! 1.Lanjut  2.Berhenti: ";
        setWarna(7);  cin >> pilih; cin.ignore(1000,'\n');
        if (pilih != 1) break;
    }

    system("cls");
    setWarna(12); cout << "=== ENDLESS SELESAI ===\n";
    setWarna(7);
    cout << "Wave  : " << wave << "\n";
    cout << "Multi : x" << multi << "\n";
    simpanData();
    cout << "Tekan ENTER..."; cin.ignore(1000,'\n'); cin.get();
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

void InfoSystem() {
    system("cls");
    setWarna(11);
    ketik("========================================\n", 5);
    ketik("         FERAL AWAKENED - INFO\n", 5);
    ketik("========================================\n\n", 5);

    // ===== STAT UPGRADE SYSTEM =====
    setWarna(14);
    ketik("[ SISTEM UPGRADE STAT ]\n", 5);
    setWarna(7);
    ketik("Stat karakter naik otomatis setiap level up.\n", 5);
    ketik("Rumus kenaikan dihitung dari level 1 s/d level sekarang.\n\n", 5);

    ketik("  Rarity |  DMG  |   HP            |  DEF        | CRIT\n", 5);
    ketik("  -------|-------|-----------------|-------------|------------------\n", 5);
    ketik("  C      | +2/lv | +5 (lv genap)   | +2 (lv gnp) | +1 (kelipatan 5)\n", 5);
    ketik("  R      | +2/lv | +10 (lv genap)  | +2 (lv gnp) | +1 (kelipatan 5)\n", 5);
    ketik("  SR     | +3/lv | +15 (lv genap)  | +2 (lv gnp) | +2 (kelipatan 5)\n", 5);
    ketik("  SSR    | +4/lv | +20 (lv genap)  | +3 (lv gnp) | +3 (kelipatan 5)\n\n", 5);

    ketik("  Contoh di level 10 rarity SSR:\n", 5);
    ketik("  DMG  : +4 x 10 = +40\n", 5);
    ketik("  HP   : +20 x 5 (lv 2,4,6,8,10) = +100\n", 5);
    ketik("  DEF  : +3 x 5 (lv 2,4,6,8,10) = +15\n", 5);
    ketik("  CRIT : +3 x 2 (lv 5,10) = +6\n\n", 5);

    // ===== BATTLE SYSTEM =====
    setWarna(14);
    ketik("[ SISTEM BATTLE ]\n", 5);
    setWarna(7);
    ketik("Turn-based. Kamu aksi duluan, lalu musuh balas.\n\n", 5);

    ketik("  [1] FIGHT  - Serang musuh\n", 5);
    ketik("  [2] DEFEND - Bertahan & kemungkinan deflect\n", 5);
    ketik("  [3] ULT    - Skill khusus (butuh 4 ULT Point)\n", 5);
    ketik("  [4] FLEE   - Kabur (HP jadi 0, dianggap kalah)\n\n", 5);

    // ===== CRIT SYSTEM =====
    setWarna(14);
    ketik("[ SISTEM CRITICAL HIT ]\n", 5);
    setWarna(7);
    ketik("Tiap serangan ada chance untuk critical hit.\n", 5);
    ketik("Damage crit = Base_Damage * (Crit_Damage / 100)\n", 5);
    ketik("Crit chance max = 95%\n\n", 5);

    // ===== DEFEND & DEFLECT =====
    setWarna(14);
    ketik("[ SISTEM DEFEND & DEFLECT ]\n", 5);
    setWarna(7);
    ketik("Saat DEFEND, damage dikurangi berdasarkan DEF:\n", 5);
    ketik("Reduction = DEF / 100 (max 80%)\n\n", 5);

    ketik("Chance DEFLECT base = 50%\n", 5);
    ketik("Jika deflect, damage tetap masuk tapi\n", 5);
    ketik("70% damage direflect balik ke musuh.\n\n", 5);

    ketik("Buff yang mempengaruhi deflect:\n", 5);
    ketik("- Sawit ULT  : +20% chance deflect (4 turn)\n", 5);
    ketik("- Aren ULT   : +20% chance deflect + 50% damage reduction (3 turn)\n\n", 5);

    // ===== ULT POINT =====
    setWarna(14);
    ketik("[ SISTEM ULT POINT ]\n", 5);
    setWarna(7);
    ketik("ULT Point didapat dari:\n", 5);
    ketik("- Critical hit saat FIGHT\n", 5);
    ketik("- Berhasil DEFLECT saat DEFEND\n", 5);
    ketik("ULT aktif saat poin = 4\n", 5);
    ketik("Catatan: poin TIDAK naik saat buff aktif\n", 5);
    ketik("(Kevin, Rigby, Mark, Revive, Marlong, DarkForce)\n\n", 5);

    // ===== MARKED SYSTEM =====
    setWarna(14);
    ketik("[ MARKED SYSTEM - Hanip Ninja ]\n", 5);
    setWarna(7);
    ketik("Fase 1: Aktifkan MARKED (musuh mulai di-stack)\n", 5);
    ketik("Tiap turn ada 30% chance stack +1 (max 6 stack)\n", 5);
    ketik("Batas waktu: 10 turn, lebih dari itu MARKED gagal\n\n", 5);

    ketik("Fase 2: Execute dengan ULT lagi\n", 5);
    ketik("Stack 0 = x1.2  |  Stack 1 = x1.5\n", 5);
    ketik("Stack 2 = x2.0  |  Stack 3 = x2.5\n", 5);
    ketik("Stack 4 = x3.0  |  Stack 5 = x3.5\n", 5);
    ketik("Stack 6 = x4.0\n", 5);
    ketik("Damage = Base_Damage * (Crit_Damage/100) * multiplier\n\n", 5);

    // ===== REVIVE SYSTEM =====
    setWarna(14);
    ketik("[ REVIVE SYSTEM - Mr. Kucing ]\n", 5);
    setWarna(7);
    ketik("Saat ULT aktif, mode revive menyala.\n", 5);
    ketik("Jika HP <= 0, otomatis bangkit dengan 50% HP.\n", 5);
    ketik("Maksimal 3x revive, dan hanya aktif 5 turn.\n\n", 5);

    // ===== MARLONG SYSTEM =====
    setWarna(14);
    ketik("[ MARLONG SYSTEM - Marlong ]\n", 5);
    setWarna(7);
    ketik("Setelah ULT aktif, tiap crit menambah HEAT (max 6).\n", 5);
    ketik("Durasi 8 turn.\n", 5);
    ketik("Di turn ke-8, meledak:\n", 5);
    ketik("Damage = Base_Damage * jumlah HEAT\n\n", 5);

    // ===== DARK FORCE =====
    setWarna(14);
    ketik("[ DARK FORCE - Anakin Maguwoharjo ]\n", 5);
    setWarna(7);
    ketik("Multiplier damage berdasarkan HP saat ini:\n", 5);
    ketik("HP < 100% : x1.5\n", 5);
    ketik("HP < 70%  : x2.0\n", 5);
    ketik("HP < 50%  : x2.5\n", 5);
    ketik("HP < 30%  : x3.0\n", 5);
    ketik("Durasi: 8 turn\n\n", 5);

    // ===== ENDLESS MODE =====
    setWarna(14);
    ketik("[ ENDLESS MODE ]\n", 5);
    setWarna(7);
    ketik("Musuh makin kuat tiap wave (+0.2x multiplier).\n", 5);
    ketik("Reward tiap wave: +50 XP * multiplier + 5 Primo.\n\n", 5);

    // ===== GACHA =====
    setWarna(14);
    ketik("[ GACHA ]\n", 5);
    setWarna(7);
    ketik("Biaya: 10 Primo per gacha\n", 5);
    ketik("Rate:\n", 5);
    ketik("SSR :  1%\n", 5);
    ketik("SR  :  8%\n", 5);
    ketik("R   : 20%\n", 5);
    ketik("C   : 71%\n\n", 5);

    setWarna(11);
    ketik("========================================\n", 5);
    setWarna(7);
    ketik("Tekan ENTER untuk kembali...", 5);

    cin.get();
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

    Character[9].design = R"(   .-'"""`-.
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
)";

    Character[10].design = R"( _._     _,-'""`-._
(,-.`._,'(       |\`-/|
    `-.-' \ )-`( , o o)
          `-    \`_`"'- 
)";

    Character[11].design = R"(               ___
      ~*    .'`  _\
           /  (o/       *
*         |     _\           *
           \  '==.    *
        *   '.____\       ~*
)";

    Character[12].design = R"(
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
)";

    Character[13].design = R"(                       .-.
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
)";
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

int calcHP(int level, int growth) {
    if (level == 0) return 0;
    int add = 0;
    if (level % 2 == 0) add = growth;
    return add + calcHP(level - 1, growth);
}

// ===== UPGRADE SYSTEM
void UpgradeSystem() {
    int lvl = currentplayer.level;

    for (int i = 0; i < 14; i++) {
        int dmg = 0, crit = 0, def = 0, hp = 0;

        if (Character[i].rarity == "C") {
            dmg  = calcDamage(lvl, 2);
            crit = calcCrit(lvl, 1);
            def  = calcDef(lvl, 2);
            hp = calcHP(lvl, 5);
        }
        else if (Character[i].rarity == "R") {
            dmg  = calcDamage(lvl, 2);
            crit = calcCrit(lvl, 1);
            def  = calcDef(lvl, 2);
            hp = calcHP(lvl, 5);
        }
        else if (Character[i].rarity == "SR") {
            dmg  = calcDamage(lvl, 3);
            crit = calcCrit(lvl, 2);
            def  = calcDef(lvl, 2);
            hp = calcHP(lvl, 10);
        }
        else if (Character[i].rarity == "SSR") {
            dmg  = calcDamage(lvl, 4);
            crit = calcCrit(lvl, 3);
            def  = calcDef(lvl, 3);
            hp = calcHP(lvl, 15);
        }

        Character[i].Base_Damage    += dmg;
        Character[i].Base_Hp += hp;
        Character[i].def            += def;
        Character[i].crital_chance  += crit;
    }
}

int xpTable[] = {
    0,    
    50,   
    75,   
    100,
    130,
    170,
    220,
    280,
    350,
    450,
    500,
    600,
    700,
    750,
    860,
    900,
    1000,
    1100,
    1200,
    1300,
    1400,
    1500,
    1600,
    1700,
    1800,
    1900,
    2000,
    2200,
    2300,
    2400,
    2500  // level 30 → max
};

void AddXP(int amount) {
    int MAX_LEVEL = 50;

    currentplayer.xp += amount;
    setWarna(14);
    cout << "+" << amount << " XP!\n";
    setWarna(7);

    //pakai level+1 sebagai index, stop di MAX_LEVEL
    while (currentplayer.level < MAX_LEVEL) {
        int xpNeed = xpTable[currentplayer.level + 1];

        if (currentplayer.xp >= xpNeed) {
            currentplayer.xp -= xpNeed;
            currentplayer.level++;

            setWarna(14);
            cout << "LEVEL UP! Level " << currentplayer.level << "\n";
            setWarna(7);

            UpgradeSystem();
        } else {
            break;
        }
    }

    if (currentplayer.level < MAX_LEVEL) {
        cout << "XP: " << currentplayer.xp << "/" << xpTable[currentplayer.level + 1] << "\n";
    } else {
        setWarna(14);
        cout << "MAX LEVEL REACHED!\n";
        setWarna(7);
    }

    Sleep(1500);
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

    Character[3].nama = "Kevin_Hitam";
    Character[3].Base_Damage = 35;
    Character[3].Base_Hp = 135;
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
    Character[6].crital_chance = 15;
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

    // ===== DESIGN (lama) =====
    Monster[0].design = R"(
          __
     w  c(..)o   (
      \_(-)    _)
          /\   (
         /()__)
         w /|
          | \
 m  m )";

    Monster[1].design = R"(
 _  (\ 
(_ \ ( '> 
  ) \/_)= 
 (( )_ 
)";

    Monster[2].design = R"(
   .-"""-.
  /      o\
 |    o   0).-.
 |       .-;(_/     .-.
  \     /  /)).---._|  `\   ,
   '.  '  /((        `'-./ _/|
     \  .'  )        .-.;`  /
      '.             |  `\-'
        '._        -'    /
           `""--------` )";

    Monster[3].design = R"(
     \\
      \\_
      ( _\
      / \__
     / _/"
    {\  )_
      """ )";

    Monster[4].design = R"(
               __
              / _)
     .----./ /
    /         /
 __/ (  | (  |
/_.-'||--|_| )";

    Monster[5].design = R"(
                       )/_
              .--..---"-,--c
        \L..'            .O)
,-.     _.+  _  \..--( /           
  `\.-''_.-' \ (      \      
    `'''        `\__   /\
                 ')_ )";

    Monster[6].design = R"(
                    __
          .,-;-;-,. /'_\
        ///|\\) /
       '-<><><><>=/\
     `//====//-'\_\
        ""     ""    "" )";

    Monster[7].design = R"(
    O~O
   (\")
  ("o"/)
  m`-'m'`---. )";

    Monster[8].design = R"(
       .'.'
      '-'-.
  .  (  o O)
   \_ `  _,   _
-._'.) ( ,-'
     '-.O.'-..-.. 
 ./\/\/ | \.-.
        ;
     ._/ )";

     Monster[9].design = R"(
      ////\\\\
      |      |
     @  O  O  @
      |  ~   |         \__
       \ -- /          |\ |
     ___|  |___        | \|
    /          \      /|__|
   /            \    / /
  /  /| .  . |\  \  / /
 /  / |      | \  \/ /
<  <  |      |  \   /
 \  \ |  .   |   \_/
  \  \|______|
    \_|______|
      |      |
      |  |   |
      |  |   |
      |__|___|
      |  |  |
      (  (  |
      |  |  |
      |  |  |
     _|  |  |
 cccC_Cccc___)
";

Monster[10].design = R"(
              ____==========_______
   _--____   |    | ""  " "|       \
  /  )8}  ^^^| 0  |  =     |  o  0  |
</_ +-==B vvv|""  |  =     | '  "" "|
   \_____/   |____|________|________|
            (_(  )\________/___(  )__)
              |\  \            /  /\
              | \  \          /  /\ \
              | |\  \        /  /  \ \
              (  )(  )       (  \   (  )
               \  / /        \  \   \  \
                \|  |\        \  \  |  |
                 |  | )____    \  \ \  )___
                 (  )  /  /    (  )  (/  /
                /___\ /__/     /___\ /__)
)";

Monster[11].design = R"(
  |\|\
>/ ( )=<
|`'o' ==
 \(^) =/
  `< ="
  /  ||"
 (   /)="
  \ (,3="
   `++||==
  __||||`==.
 (,(,___\ "==)
)";

Monster[12].design = R"(
   /\  /\
  /  \/  \
 / /\ \/\ \
 \ \/\ \/ /
  \/ /\/ /
  / /\/ /\
 / /\  /\ \
/ /  \/  \ \
\ \  /\  / /
 \ \/  \/ /
  \/ /\/ /
  / /\/ /\
 / /\ \/\ \
 \ \/\ \/ /
  \  /\  /
   \/  \/
)";

    // ===== DATA =====
    Monster[0].nama = "arem arem";
    Monster[0].Base_Hp = 200;
    Monster[0].Base_Damage = 8;
    Monster[0].crital_chance = 30;
    Monster[0].crital_damage = 120;
    Monster[0].level = 1;
    Monster[0].isBoss = false;

    Monster[1].nama = "whiskas";
    Monster[1].Base_Hp = 300;
    Monster[1].Base_Damage = 12;
    Monster[1].crital_chance = 5;
    Monster[1].crital_damage = 120;
    Monster[1].level = 2;
    Monster[1].isBoss = false;

    Monster[2].nama = "Nadragong";
    Monster[2].Base_Hp = 400;
    Monster[2].Base_Damage = 25;
    Monster[2].crital_chance = 10;
    Monster[2].crital_damage = 140;
    Monster[2].level = 3;
    Monster[2].isBoss = true;

    Monster[3].nama = "Wong Silver";
    Monster[3].Base_Hp = 500;
    Monster[3].Base_Damage = 22;
    Monster[3].crital_chance = 20;
    Monster[3].crital_damage = 150;
    Monster[3].level = 4;
    Monster[3].isBoss = false;

    Monster[4].nama = "KaKangkung";
    Monster[4].Base_Hp = 900;
    Monster[4].Base_Damage = 26;
    Monster[4].crital_chance = 8;
    Monster[4].crital_damage = 130;
    Monster[4].level = 5;
    Monster[4].isBoss = true;

    Monster[5].nama = "Lintah Darat";
    Monster[5].Base_Hp = 650;
    Monster[5].Base_Damage = 18;
    Monster[5].crital_chance = 25;
    Monster[5].crital_damage = 160;
    Monster[5].level = 6;
    Monster[5].isBoss = false;

    Monster[6].nama = "Bebek Ngeselin";
    Monster[6].Base_Hp = 550;
    Monster[6].Base_Damage = 20;
    Monster[6].crital_chance = 40;
    Monster[6].crital_damage = 170;
    Monster[6].level = 7;
    Monster[6].isBoss = false;

    Monster[7].nama = "Ikan Lohan";
    Monster[7].Base_Hp = 1200;
    Monster[7].Base_Damage = 45;
    Monster[7].crital_chance = 12;
    Monster[7].crital_damage = 150;
    Monster[7].level = 8;
    Monster[7].isBoss = true;

    Monster[8].nama = "Gogoboy";
    Monster[8].Base_Hp = 1300;
    Monster[8].Base_Damage = 40;
    Monster[8].crital_chance = 30;
    Monster[8].crital_damage = 180;
    Monster[8].level = 9;
    Monster[8].isBoss = false;

    Monster[9].nama = "Jungkir Balik";
    Monster[9].Base_Hp = 1500;
    Monster[9].Base_Damage = 55;
    Monster[9].crital_chance = 15;
    Monster[9].crital_damage = 160;
    Monster[9].level = 10;
    Monster[9].isBoss = false;

    Monster[10].nama = "Shadow Rift";
    Monster[10].Base_Hp = 1000;
    Monster[10].Base_Damage = 60;
    Monster[10].crital_chance = 50;
    Monster[10].crital_damage = 200;
    Monster[10].level = 11;
    Monster[10].isBoss = false;

    Monster[11].nama = "Witchak Cuk";
    Monster[11].Base_Hp = 1500;
    Monster[11].Base_Damage = 85;
    Monster[11].crital_chance = 25;
    Monster[11].crital_damage = 200;
    Monster[11].level = 12;
    Monster[11].isBoss = true;

    Monster[12].nama = "Rift Guardian";
    Monster[12].Base_Hp = 2000;
    Monster[12].Base_Damage = 70;
    Monster[12].crital_chance = 20;
    Monster[12].crital_damage = 180;
    Monster[12].level = 13;
    Monster[12].isBoss = true;
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
    ketik("TUGAS INI ADALAH SEBAGAI PROJEK AKHIR KITA ACID DAN AZRA\n", 60);
    tunggu(700);
    setWarna(4);
    ketik("SEMOGA TUHAN MEMBANTU KITA SEMUA", 120);
    tunggu(7000);
    system("cls");

    setWarna(11);
    ketik("LUMINARA — ???\n\n", 50);
    tunggu(600);

    setWarna(7);
    ketik("Tanggal tidak diketahui.\n");
    tunggu(700);

    setWarna(12);
    ketik("Langit tiba-tiba terbuka.\n\n", 60);
    tunggu(600);

    setWarna(4);
    ketik("RIFT.\n\n", 120);
    tunggu(700);

    setWarna(7);
    ketik("Tidak ada yang tahu kenapa.\n");
    ketik("Tidak ada yang bisa menghentikan.\n\n");
    tunggu(800);

    ketik("Yang masuk...\n");
    ketik("tidak selalu kembali.\n\n");
    tunggu(700);

    setWarna(13);
    ketik("Yang kembali...\n");
    ketik("tidak selalu sama.\n\n");
    tunggu(900);

    setWarna(10);
    ketik("Di dalam Rift:\n");
    ketik("- Floor berubah\n");
    ketik("- Musuh berubah\n");
    ketik("- Aturan berubah\n\n");
    tunggu(900);

    setWarna(12);
    ketik("Kadang kamu kuat.\n");
    ketik("Kadang kamu mati dalam 2 detik.\n\n");
    tunggu(800);

    setWarna(11);
    ketik("Tidak ada alasan.\n");
    ketik("Tidak ada keadilan.\n\n");
    tunggu(900);

    setWarna(14);
    ketik("Hanya RNG.\n\n", 100);
    tunggu(900);

    setWarna(7);
    ketik("Dan kamu...\n");
    ketik("tetap masuk.\n\n");
    tunggu(900);

    setWarna(12);
    ketik("Karena mungkin...\n");
    ketik("run berikutnya lebih baik.\n\n");
    tunggu(1000);

    cout << "\n\nTekan ENTER untuk mulai run yang mungkin gagal...";
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
        cin.ignore(1000, '\n');
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
        cin.ignore(1000, '\n');
    }
    Cek.close();

    if (pilih1 == 1) {
        lore();
        ofstream Lore("save.txt", ios::app);
        Lore << "Lore_True" << " ";
        setWarna(10);
        ketik("Masukan Nama kamu Nyong: ");
        tunggu(1000);
        setWarna(7);
        cin >> currentplayer.username;
        cin.ignore(1000, '\n');
        Lore << currentplayer.username << " ";
      
        Lore << "level:" << currentplayer.level << " ";
        Lore << "xp:" << currentplayer.xp << " ";
        Lore.close();
    }

    if (pilih1 == 2) {
        exit(0);
    }
    if (pilih == 1) {
        ifstream Load("save.txt");
        string token;
        while (Load >> token) {
            if (token != "Lore_True" && token != "Tutor_True"
                && token.substr(0,6) != "primo:"
                && token.substr(0,6) != "level:"   
                && token.substr(0,3) != "xp:") {   
                bool ituKarakter = false;
                for (int i = 0; i < 14; i++)
                if (Character[i].nama == token) { ituKarakter = true; break; }
                if (!ituKarakter) currentplayer.username = token; //Nyari nama
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
    system("cls");

    setWarna(10);
    ketik("=== TUTORIAL ===\n\n", 40);
    tunggu(500);

    setWarna(7);
    ketik("Game ini menggunakan sistem turn-based.\n");
    ketik("Setiap giliran, kamu bertindak.\n");
    ketik("Kemudian musuh akan merespons.\n\n");
    tunggu(800);

    ketik("Keputusanmu menentukan hasil pertarungan.\n\n");
    tunggu(700);

    setWarna(11);
    ketik("=== ACTION ===\n\n", 40);
    setWarna(7);

    ketik("- Fight   : Menyerang musuh\n");
    ketik("- Defend  : Mengurangi damage dan berpeluang melakukan deflect\n");
    ketik("- ULT     : Skill kuat dengan efek khusus\n\n");
    tunggu(1000);

    setWarna(12);
    ketik("=== ULT SYSTEM ===\n\n", 40);
    setWarna(7);

    ketik("ULT membutuhkan poin untuk digunakan.\n\n");

    ketik("Poin dapat diperoleh melalui:\n");
    ketik("- Critical hit\n");
    ketik("- Deflect saat bertahan\n\n");
    tunggu(1000);

    ketik("Saat poin penuh, ULT dapat digunakan.\n\n");
    tunggu(800);

    setWarna(13);
    ketik("=== DEFLECT ===\n\n", 40);
    setWarna(7);

    ketik("Saat bertahan, ada kemungkinan untuk melakukan deflect.\n");
    ketik("Deflect akan mengembalikan sebagian atau seluruh damage ke musuh.\n\n");
    tunggu(1000);

    setWarna(11);
    ketik("=== REWARD ===\n\n", 40);
    setWarna(7);

    ketik("Setelah menang, kamu akan mendapatkan reward.\n");
    ketik("Beberapa reward dapat digunakan untuk gacha.\n\n");

    ketik("Tingkat rarity:\n");
    ketik("- Common\n");
    ketik("- Rare\n");
    ketik("- Epic\n");
    ketik("- Legendary\n\n");
    tunggu(1200);

    ketik("Semakin tinggi rarity, semakin kuat efeknya.\n\n");
    tunggu(800);

    setWarna(12);
    ketik("=== OBJECTIVE ===\n\n", 40);
    setWarna(7);

    ketik("Masuk ke Rift.\n");
    ketik("Naik ke floor berikutnya.\n");
    ketik("Bertahan selama mungkin.\n\n");
    tunggu(1000);

    setWarna(10);
    ketik("Jika gagal, kamu bisa mencoba kembali.\n\n");

    setWarna(7);
    ketik("Tekan ENTER untuk memulai.");
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
    setWarna(13); cout << "[4.FLEEEEEE] ";
    setWarna(7);  cout << "   |\n";
    cout << pad << "|                                                      |\n";
    cout << pad << "+------------------------------------------------------+\n";
    cout << "Level: " << currentplayer.level << "  |  ";
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
    int damage;
    int roll;
    if (Defend) {
        if (BuffAren > 0) {
            cout << "50% DEFEND + 20% DEFLECT\n";
            BuffA = 50;
            Buff = 20;
            BuffAren--;
        }

        roll = rand() % 100 + 1;
        float reduction = (Character[CharacterKawan].def + BuffA) / 100.0f;
        if (reduction > 0.8f) reduction = 0.8f;
        roll = rand() % 100 + 1;
        if (roll <= Monster[CharacterMonster].crital_chance) {
        damage = (int)(Monster[CharacterMonster].Base_Damage * (Monster[CharacterMonster].crital_damage / 100.0));
        }
        else {
        damage = Monster[CharacterMonster].Base_Damage;  
        }
        int finalDamage = (int)(damage * (1 - reduction));
        if (finalDamage < 1) finalDamage = 1;

        if (BuffSawit > 0) {
            cout << "+20% CHANCE DEFLECT " << BuffSawit << "\n";
            Buff = 20;
            BuffSawit--;
        }

        if (roll <= 50 - Buff) {
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
        roll = rand() % 100 + 1;
        if (roll <= Monster[CharacterMonster].crital_chance) {
        damage = (int)(Monster[CharacterMonster].Base_Damage * (Monster[CharacterMonster].crital_damage / 100.0));
        HpKawan -= damage;
        cout << "CRITICAL HIT MONSTER!! " << damage;
        }
        else {
        cout << "Musuh menyerang! Damage: " << Monster[CharacterMonster].Base_Damage << "\n";
        HpKawan -= Monster[CharacterMonster].Base_Damage;
        }
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
        printSideBySide(Character[CharacterKawan].design, Monster[CharacterMusuh].design);
        BattleUI(HpKawan, HpMusuh, PointULT, MarkStatus, MarkTurn, Marked, ReviveK, JumlahRevive, MaxTurnK, MarlongMode, JumlahMarlong, MarlongTurn, DarkForce, DarkForceTurn);
        cin >> Aksi;
        cin.ignore(1000, '\n');

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
            Sleep(1000);
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
        } 
          else if (Aksi == 4)  {
            cout << "KABURRRR";
            Sleep(1000);
            HpKawan = 0;
            break;
          }
        else {
            cout << "Pilihan tidak valid!\n";
            Sleep(1000);
        }
    } while (true);
}

// ===== FIGHT =====
bool Fight(int PilihKarakter,int PilihMusuh) {
    

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

    MarkedBool = true;
    MarlongBool = true;

    SelectC = PilihKarakter;
    SelectV = PilihMusuh;
  
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
        return false;
    } else {
        setWarna(10);
        cout << "\n=== KAMU MENANG! ===\n";
        return true;
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
    pause();
    Fight(1,0);
}

// ===== GACHA =====
// Format save.txt: Lore_True Tutor_True NamaPlayer level:1 xp:0 primo:100 Ireng_Jogja 
void simpanData() {
    bool adaLore = false, adaTutor = false;
    string namaPlayer = "";
    {
        ifstream f("save.txt");
        string token;
        while (f >> token) {
            if (token == "Lore_True")       adaLore  = true;
            else if (token == "Tutor_True") adaTutor = true;
            else if (token.substr(0,6) != "primo:"
                  && token.substr(0,6) != "level:"
                  && token.substr(0,3) != "xp:"
                  && token.substr(0,10) != "lvlunlock:") {
                bool ituKarakter = false;
                for (int i = 0; i < 14; i++)
                if (Character[i].nama == token) { ituKarakter = true; break; }
                if (!ituKarakter) namaPlayer = token; // Nyari nama
            }
        }
    }
    
    ofstream f("save.txt"); //overwrite bikin baru
    if (adaLore)  f << "Lore_True ";
    if (adaTutor) f << "Tutor_True ";
    if (namaPlayer != "") f << namaPlayer << " ";
    //  simpan level & xp
    f << "level:" << currentplayer.level << " ";
    f << "xp:" << currentplayer.xp << " ";
    f << "primo:" << currentplayer.primo << " ";
    for (int i = 0; i < 14; i++)
        if (Character[i].unlock) f << Character[i].nama << " ";
    for (int i = 1; i <= 13; i++)
        if (currentplayer.LevelUnlock[i]) f << "lvlunlock:" << i << " ";
    f.close();
}

void loadData() {
    ifstream f("save.txt");
    if (!f) { currentplayer.primo = 10; currentplayer.level = 1; currentplayer.xp = 0; return; }
    
    string token;
    bool primoKetemu = false;
    
    while (f >> token) {
        if (token == "Lore_True" || token == "Tutor_True") {
            // skip, tidak perlu diproses
        }
        else if (token.substr(0,6) == "primo:") {
            currentplayer.primo = stoi(token.substr(6));
            primoKetemu = true;
        }
        else if (token.substr(0,6) == "level:") {
            currentplayer.level = stoi(token.substr(6));
        }
        else if (token.substr(0,3) == "xp:") {
            currentplayer.xp = stoi(token.substr(3));
        }
        else if (token.substr(0,10) == "lvlunlock:") {
            int idx = stoi(token.substr(10));
            if (idx >= 1 && idx <= 13)
                currentplayer.LevelUnlock[idx] = true;
        }
        else {
            // Cek dulu apakah ini nama karakter
            bool ituKarakter = false;
            for (int i = 0; i < 14; i++) {
                if (Character[i].nama == token) {
                    Character[i].unlock = true;
                    ituKarakter = true;
                    break;
                }
            }
            if (!ituKarakter) currentplayer.username = token;
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
        cout << "Kamu sudah punya karakter ini\n";
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


void gacha(int& primo) {
    int SSR = 1, SR = 8, R = 20;
    int pity = 0;
    char ulang;

    while (true) {
        if (primo < 10) {
            cout << "\nPrimo tidak cukup! Sisa: " << primo << "\n";
            break;
        }

        cout << "\n==============================\n";
        cout << "Primo  : " << primo << "\n";
        cout << "------------------------------\n";
        cout << "1. Gacha biasa (random)\n";
        cout << "2. Keluar dari gacha\n";
        cout << "Pilih: ";

        int opsi; cin >> opsi;
        cin.ignore(1000, '\n');
        if (opsi == 3) break;

        primo -= 10;
        int acha = rand() % 100 + 1;

        if (opsi == 1) {
            hasilGacha(acha, primo, SSR, SR, R);
        } else if (opsi == 2) {
        return;
        } else {
            cout << "Opsi tidak valid!\n";
        }

        cout << "\nGacha lagi? (y/n): ";
        cin >> ulang;
        system("cls");
        cin.ignore(1000, '\n');
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
    cin.ignore(1000, '\n');
    if (pilih == 1) tampilSort();
}


void quickSort(int idx[], int low, int high, int mode) {
    if (low >= high) return;

    int pivot;
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

        if (value > pivot) {
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
    cin.ignore(1000, '\n');

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

// ===== GAME MENU =====
void GameMenu() {
    int pilih = 0;
    loadData();

    if (currentplayer.level > 1) UpgradeSystem();

    while (true) {
        system("cls");
        setWarna(11);
        cout << "\n  Selamat datang, Keeper " << currentplayer.username << "!\n";
        cout << "  Level : " << currentplayer.level << "\n";
        if (currentplayer.level < 30) {
            cout << "  XP    : " << currentplayer.xp << "/" << xpTable[currentplayer.level + 1] << "\n";
        } else {
            cout << "  XP    : MAX LEVEL\n";
        }
        cout << "  Primo : " << currentplayer.primo << "\n\n";
        setWarna(7);
        cout << "+-------------------------------+\n";
        cout << "|          GAME MENU            |\n";
        cout << "+-------------------------------+\n";
        cout << "| 1. Story Mode                 |\n";
        cout << "| 2. Endless Mode               |\n";
        cout << "| 3. Gacha                      |\n";
        cout << "| 4. Koleksi                    |\n";
        cout << "| 5. Daftar Karakter            |\n";
        cout << "| 6. Info - Detail              |\n";
        cout << "| 7. Keluar ke Main Menu        |\n";
        cout << "+-------------------------------+\n";
        cout << "Pilih: ";
        cin >> pilih;
        cin.ignore(1000, '\n');

        if (pilih == 1) {
            StoryMode();
            cout << "Tekan ENTER untuk kembali ke menu...";
            cin.get();
        } 
          else if (pilih == 2) {
            EndlessMode();
        }        
          else if (pilih == 3) {
            gacha(currentplayer.primo);
            cout << "Tekan ENTER untuk kembali ke menu...";
            cin.get();
        } else if (pilih == 4) {
            koleksi();
            cout << "Tekan ENTER untuk kembali ke menu...";
            cin.get();
        } else if (pilih == 5) {
            daftarchara();
            cout << "Tekan ENTER untuk kembali ke menu...";
        }
          else if (pilih == 6)  {
             InfoSystem();   
          }
         else if (pilih == 7) {
            break;
        } else {
            cout << "Pilihan tidak valid!\n";
            Sleep(1000);
        }
    }
}

// ===== MAIN =====
int main() {
    system("cls");
    currentplayer.level = 1;
    currentplayer.xp = 0;
    Sleep(5000);
    system("cls");
    IsiData();

    ofstream File("save.txt", ios::app);
    File.close();

    Logo();

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
        ofstream SaveTutor("save.txt", ios::app);
        SaveTutor << "Tutor_True" << " ";
        SaveTutor.close();
        TestFight();
    }

    GameMenu();

    return 0;
}
