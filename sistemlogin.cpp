#include <iostream>
#include <fstream>
#include <thread>
#include <iomanip>
#include <chrono>
using namespace std;

bool pass1 = false;
bool pass2 = false;
bool pass3 = false;
bool pass4 = false;

void LoginRegister() {
int opsi; string text;
string TempUser,TempPw,RegisUser,RegisPw;
char OpsiLagi;
int CountUser = 0;
int CountPw = 0;
bool skip = false;

cout << R"(+----------------------------+
|        MENU UTAMA          |
+----------------------------+
| 1. Login                   |
| 2. Register                |
| 3. Exit                    |
+----------------------------+
Pilih opsi: )"; cin >> opsi;

//SISTEM LOGIN DAN REGISTER
if (opsi == 1) {
    system("cls");
    cout << "Masukan User Anda: "; cin >> TempUser;
    cout << "Masukan Password Anda: "; cin >> TempPw;
    ifstream CekLogin("user.txt");
    while (CekLogin >> text) {
        CountUser++;
            if (TempUser == text) {
                pass1 = true;
                break;
    }
}
    if (pass1) {
    ifstream CekPw("pw.txt");
    while (CekPw >> text) {
        CountPw++;
        if (TempPw == text) {
        cout << "pwnemu";
        pass2 = true;
        break;
        }
    }
}
    if (pass1 && pass2) {
        if (CountPw == CountUser) {
            pass3 = true;
        }
    }
    else {
            pass1 = false;
            pass2 = false;
            pass3 = false;
            system("cls");
            cout << "User atau Password salah (balik ke menu dalam 3)";
            this_thread::sleep_for(chrono::seconds(1));
            system("cls");
            cout << "User atau Password salah (balik ke menu dalam 2)";
            this_thread::sleep_for(chrono::seconds(1));
            system("cls");
            cout << "User atau Password salah (balik ke menu dalam 1)";
            this_thread::sleep_for(chrono::seconds(1));
            system("cls");
    }
}

   if (opsi == 2) {
    // Bersihkan buffer SEKALI sebelum loop
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    do {
        skip = false;
        system("cls");

        cout << "Register\n";

        // INPUT USERNAME
        cout << "Masukan User: ";
        getline(cin, RegisUser);

        // VALIDASI USERNAME
        bool adaKapital = false;
        for (char c : RegisUser) {
            if (isupper(c)) {
                adaKapital = true;
                break;
            }
        }

        if (RegisUser.find(' ') != string::npos || RegisUser.empty() || adaKapital) {
            cout << "Username tidak valid (tidak boleh kosong / ada spasi / ada kapital)\n";
            system("pause");
            continue;
        }

        if (RegisUser.length() > 11) {
            cout << "Maximal 12 Karakter\n";
            system("pause");
            continue;
        }

        // INPUT PASSWORD
        cout << "Masukan Password: ";
        getline(cin, RegisPw);

        // VALIDASI PASSWORD
        if (RegisPw.length() < 8) {
            cout << "Minimal Password 8 karakter\n";
            system("pause");
            continue;
        }

        if (RegisPw.length() >= 16) {
            cout << "Maximal Password 16 karakter\n";
            system("pause");
            continue;
        }

        if (RegisPw.find(' ') != string::npos) {
            cout << "Password tidak boleh mengandung spasi\n";
            system("pause");
            continue;
        }

        // VALIDASI USERNAME DI FILE
        ifstream Cek("user.txt");
        string nama;

        while (Cek >> nama) {
            if (nama == RegisUser) {
                cout << "User yang anda gunakan sudah dipakai\n";
                system("pause");
                skip = true;
                break;
            }
        }
        Cek.close(); 

        if (skip) continue;

        // KONFIRMASI
        cout << "Apakah anda sudah yakin? (y/n): ";
        cin >> OpsiLagi;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

    } while (OpsiLagi != 'y');
    system("cls");


   cout << "===== KONFIRMASI REGISTRASI =====\n";
   cout << "  Username : " << RegisUser << "\n";
   cout << "  Password : " << RegisPw << "\n";
   cout << "=================================\n";
   cout << "Apakah anda sudah yakin? (y/n): ";
   cin >> OpsiLagi;

   if (OpsiLagi == 'y') {
    system("cls");
    ofstream InputUser("user.txt", ios::app);
    InputUser << " " << RegisUser;
    InputUser.close();

    ofstream InputPw("pw.txt", ios::app);
    InputPw << " " << RegisPw;
    InputPw.close();
    cout << "REGISTRASI SELESAI\n";
    system("pause");
    system("cls");
    return;
   }

   else {   
            system("cls");
            cout << "(balik ke menu dalam 3)";
            this_thread::sleep_for(chrono::seconds(1));
            system("cls");
            cout << "(balik ke menu dalam 2)";
            this_thread::sleep_for(chrono::seconds(1));
            system("cls");
            cout << "(balik ke menu dalam 1)";
            this_thread::sleep_for(chrono::seconds(1));
            system("cls");
            return;
   }
}

    else {
    system("cls");
    }
}



int main() {

do {
LoginRegister();
    if (pass1 && pass2 && pass3) {
        pass4 = true;
    }
} while (!pass4);
cout << "game dimulai";


}
