
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include "account.h"
#include "sha256.h"

using namespace std;


Hesap::Hesap(string hesapNo, string sifre, double bakiye) :
    hesapNo(hesapNo), sifreHash(SHA256::hash(sifre)), bakiye(bakiye)
{
}

bool Hesap::sifreKontrol(string girilenSifre) const
{
    return sifreHash == SHA256::hash(girilenSifre);
}


string Hesap::getHesapNo() const { return hesapNo; }
double Hesap::getBakiye() const { return bakiye; }


void Hesap::paraYatir(double miktar)
{
    if (miktar <= 0)
    {
        cout << "Gecersiz miktar\n";
        return;
    }
    bakiye += miktar;
    stringstream islem;
    islem << "Para yatirma + " << miktar;
    hareketEkle(islem.str());
    cout << miktar << " TL yatirildi. Yeni bakiye: " << bakiye << " TL\n";
}


void Hesap::paraCek(double miktar)
{
    if (miktar <= 0)
    {
        cout << "Gecersiz miktar\n";
        return;
    }
    if (miktar > bakiye)
    {
        cout << "Yetersiz Bakiye\n";
        return;
    }
    bakiye -= miktar;
    stringstream islem;
    islem << "Para cekme - " << miktar;
    hareketEkle(islem.str());
    cout << miktar << " TL Cekildi. Yeni bakiye: " << bakiye << " TL\n";
}

// Hareket ekleme - Islem Gecmisi -
void Hesap::hareketEkle(string islem)
{
    time_t now = time(0);
    tm* localtm = localtime(&now);
    stringstream tarih;
    tarih << put_time(localtm, "%Y-%m-%d");
    hareketler.push_back(tarih.str() + ": " + islem);
}

// Hareketleri gösterme
void Hesap::hareketleriGoster() const
{
    cout << "\n---ISLEM GECMISI---\n";
    for (const string& hareket : hareketler)
    {
        cout << hareket << endl;
    }
    cout << "----------\n";
}

// Dosyaya kaydet
void Hesap::dosyayaKaydet()
{
    ofstream dosya("hesaplar/" + hesapNo + ".txt");

    if (dosya.is_open())
    {
        dosya << hesapNo << endl;
        dosya << sifreHash << endl; // Hash'lenmiþ þifreyi kaydet
        dosya << bakiye << endl;
        for (const string& hareket : hareketler)
        {
            dosya << hareket << endl;
        }
    }
    else
    {
        cerr << "Hesap dosyasi acilamadi\n";
    }
}

// Dosyadan okuma
Hesap Hesap::dosyadanOku(string hesapNo)
{
    ifstream dosya("hesaplar/" + hesapNo + ".txt");
    string sifreHash;
    double bakiye = 0;
    vector<string> hareketler;

    if (dosya.is_open())
    {
        getline(dosya, hesapNo);
        getline(dosya, sifreHash); // Hash'lenmiþ þifreyi oku
        dosya >> bakiye;
        dosya.ignore();

        string hareket;
        while (getline(dosya, hareket))
        {
            hareketler.push_back(hareket);
        }
    }
    else
    {
        cerr << "Hesap bulunamadi!\n";
    }

    Hesap hesap(hesapNo, "", bakiye); // Þifre boþ geçiliyor, çünkü hash'ini zaten okuduk
    hesap.sifreHash = sifreHash; // Hash'lenmiþ þifreyi ata
    hesap.hareketler = hareketler;
    return hesap;
}
