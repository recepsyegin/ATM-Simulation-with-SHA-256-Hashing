#include <iostream>
#include <fstream>
#include "Account.h"
using namespace std;

void anaMenu();
void hesapOlustur();
void hesabaGiris();

int main() {
    int secim;
    do {
        cout << "\n*** BANKAMATIK SIMULASYONU ***\n";
        cout << "1. Hesap Olustur\n";
        cout << "2. Giris Yap\n";
        cout << "3. Cikis\n";
        cout << "Seciminiz: ";
        cin >> secim;

        switch (secim) {
        case 1: hesapOlustur(); break;
        case 2: hesabaGiris(); break;
        case 3: cout << "Cikis yapiliyor...\n"; break;
        default: cout << "Gecersiz secim!\n";
        }
    } while (secim != 3);

    return 0;
}

void hesapOlustur() {
    string hesapNo, sifre;
    cout << "Hesap No: ";
    cin >> hesapNo;
    cout << "Sifre: ";
    cin >> sifre;

    Hesap yeniHesap(hesapNo, sifre);
    yeniHesap.dosyayaKaydet();
    cout << "Hesap basariyla olusturuldu!\n";
}

void hesabaGiris() {
    string hesapNo, sifre;
    cout << "Hesap No: ";
    cin >> hesapNo;
    cout << "Sifre: ";
    cin >> sifre;

    Hesap hesap = Hesap::dosyadanOku(hesapNo);
    if (!hesap.sifreKontrol(sifre)) {
        cout << "Hatali sifre!\n";
        return;
    }

    int secim;
    do {
        cout << "\n*** HOSGELDINIZ ***\n";
        cout << "1. Bakiye Sorgula\n";
        cout << "2. Para Yatir\n";
        cout << "3. Para Cek\n";
        cout << "4. Hesap Hareketleri\n";
        cout << "5. Cikis\n";
        cout << "Seciminiz: ";
        cin >> secim;

        double miktar;
        switch (secim) {
        case 1:
            cout << "Bakiyeniz: " << hesap.getBakiye() << " TL\n";
            break;
        case 2:
            cout << "Yatirilacak miktar: ";
            cin >> miktar;
            hesap.paraYatir(miktar);
            hesap.dosyayaKaydet();
            break;
        case 3:
            cout << "Cekilecek miktar: ";
            cin >> miktar;
            hesap.paraCek(miktar);
            hesap.dosyayaKaydet();
            break;
        case 4:
            hesap.hareketleriGoster();
            break;
        }
    } while (secim != 5);
}