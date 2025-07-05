#pragma once

#include <string>
#include <vector>
#include "sha256.h"

class Hesap
{
private:
    std::string hesapNo;
    std::string sifreHash; // Þifre artýk hash'lenmiþ olarak saklanacak
    double bakiye;
    std::vector<std::string> hareketler;

public:
    Hesap(std::string hesapNo, std::string sifre, double bakiye = 0.0);

    // Getters
    std::string getHesapNo() const;
    bool sifreKontrol(std::string girilenSifre) const;
    double getBakiye() const;

    // Banka islemleri
    void paraYatir(double miktar);
    void paraCek(double miktar);
    void hareketEkle(std::string islem);
    void hareketleriGoster() const;

    // Dosya islemleri
    void dosyayaKaydet();
    static Hesap dosyadanOku(std::string hesapNo);
};