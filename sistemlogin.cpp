#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <limits>
using namespace std;

bool pass1 = false, pass2 = false, pass3 = false, pass4 = false;

void LoginRegister() {
    int opsi;
    string text, TempUser, TempPw, RegisUser, RegisPw;
    char OpsiLagi;
    int CountUser = 0, CountPw = 0;
    bool skip = false;

    cout << R"(+----------------------------+
|        MENU UTAMA          |
+----------------------------+
| 1. Login                   |
| 2. Register                |
| 3. Exit                    |
+----------------------------+
Pilih opsi: )";
    cin >> opsi;

    // ===== LOGIN =====
    if (opsi == 1) {
        bool loginLoop = true;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        while (loginLoop) {
            system("cls");

            cout << "Masukan User Anda (ketik 'cancel' untuk kembali): ";
            getline(cin, TempUser);

            // CANCEL
            if (TempUser == "cancel") return;

            if (TempUser.find(' ') != string::npos || TempUser.empty()) {
                cout << "Username tidak boleh mengandung spasi atau kosong\n";
                system("pause");
                continue;
            }

            cout << "Masukan Password Anda (ketik 'cancel' untuk kembali): ";
            getline(cin, TempPw);

            // CANCEL
            if (TempPw == "cancel") return;

            if (TempPw.find(' ') != string::npos || TempPw.empty()) {
                cout << "Password tidak boleh mengandung spasi atau kosong\n";
                system("pause");
                continue;
            }

            // RESET COUNTER tiap percobaan
            CountUser = 0;
            CountPw = 0;
            pass1 = pass2 = pass3 = false;

            ifstream CekLogin("user.txt");
            while (CekLogin >> text) {
                CountUser++;
                if (TempUser == text) { pass1 = true; break; }
            }
            CekLogin.close();

            if (pass1) {
                ifstream CekPw("pw.txt");
                while (CekPw >> text) {
                    CountPw++;
                    if (TempPw == text) { pass2 = true; break; }
                }
                CekPw.close();
            }

            if (pass1 && pass2 && CountPw == CountUser) {
                pass3 = true;
                loginLoop = false; // login berhasil, keluar loop
            } else {
                pass1 = pass2 = pass3 = false;
                for (int i = 3; i >= 1; i--) {
                    system("cls");
                    cout << "User atau Password salah, coba lagi (balik ke menu dalam " << i << ")";
                    this_thread::sleep_for(chrono::seconds(1));
                }
                // tidak return, lanjut loop → minta input lagi
            }
        }
    }

    // ===== REGISTER =====
    else if (opsi == 2) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        do {
            skip = false;
            system("cls");
            cout << "Register\n";

            cout << "Masukan User (ketik 'cancel' untuk kembali): ";
            getline(cin, RegisUser);

            // CANCEL
            if (RegisUser == "cancel") return;

            bool adaKapital = false;
            for (char c : RegisUser)
                if (isupper(c)) { adaKapital = true; break; }

            if (RegisUser.empty() || RegisUser.find(' ') != string::npos || adaKapital) {
                cout << "Username tidak valid (tidak boleh kosong / ada spasi / ada kapital)\n";
                system("pause"); continue;
            }

            if (RegisUser.length() > 12) {
                cout << "Maximal 12 karakter\n";
                system("pause"); continue;
            }

            cout << "Masukan Password (ketik 'cancel' untuk kembali): ";
            getline(cin, RegisPw);

            // CANCEL
            if (RegisPw == "cancel") return;

            if (RegisPw.length() < 8) {
                cout << "Minimal Password 8 karakter\n";
                system("pause"); continue;
            }
            if (RegisPw.length() > 16) {
                cout << "Maximal Password 16 karakter\n";
                system("pause"); continue;
            }
            if (RegisPw.find(' ') != string::npos) {
                cout << "Password tidak boleh mengandung spasi\n";
                system("pause"); continue;
            }

            ifstream Cek("user.txt");
            string nama;
            while (Cek >> nama) {
                if (nama == RegisUser) {
                    cout << "User sudah dipakai\n";
                    system("pause");
                    skip = true; break;
                }
            }
            Cek.close();
            if (skip) continue;

            // KONFIRMASI
            system("cls");
            cout << "===== KONFIRMASI REGISTRASI =====\n";
            cout << "  Username : " << RegisUser << "\n";
            cout << "  Password : " << RegisPw << "\n";
            cout << "=================================\n";
            cout << "Apakah anda sudah yakin? (y = lanjut / n = ulangi / c = cancel): ";
            cin >> OpsiLagi;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            // CANCEL di konfirmasi lalu balik ke menu
            if (OpsiLagi == 'c') return;

        } while (OpsiLagi != 'y');

        system("cls");

        // Simpan dengan separator spasi
        ofstream InputUser("user.txt", ios::app);
        InputUser << " " << RegisUser;
        InputUser.close();

        ofstream InputPw("pw.txt", ios::app);
        InputPw << " " << RegisPw;
        InputPw.close();

        cout << "REGISTRASI SELESAI\n";
        system("pause");
        system("cls");
    }

    // ===== EXIT =====
    else if (opsi == 3) {
        cout << "Keluar dari program...\n";
        exit(0);
    }

    else {
        cout << "Opsi tidak valid\n";
        system("pause");
        system("cls");
    }
}

void Game() {

}

int main() {
system("cls");
    do {
        system("cls");
        LoginRegister();
        if (pass1 && pass2 && pass3) {
            pass4 = true;
        }
    } while (!pass4);

    Game();
}
