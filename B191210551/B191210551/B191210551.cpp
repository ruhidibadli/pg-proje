/****************************************************************************
**
**				ÖĞRENCİ ADI:RUHİD İBADLI
**				ÖĞRENCİ NUMARASI:B191210551
**				DERS GRUBU:1C
****************************************************************************/




#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <time.h>
#include <Windows.h>


using namespace std;

char solUstKose = 201;
char duz = 205;
char sagUstKose = 187;
char solAltKose = 200;
char sagAltKose = 188;
char dikey = 186;

void koordinatAta(int x, int y) //Çizimleri yapmak için kursorun konumunu değişiyor
{
	COORD kordinatlar;
	kordinatlar.X = x;
	kordinatlar.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), kordinatlar);
}


class Ogrenci
{
private:
	string isim;
	string soyisim;
	int numara;

public:
	//Dışarıdan erişime kapalı olan değişkenlere değer atamak için kullanılan 3 fonksiyon
	void isimGonder(string m_isim)
	{
		isim = m_isim;
	}
	void soyisimGonder(string m_soyisim)
	{
		soyisim = m_soyisim;
	}
	void numaraGonder(int m_numara)
	{
		numara = m_numara;
	}
	//Dışarıdan erişime kapalı olan değişkenlerin tuttukları değerleri ekrana yazdıran 3 fonksiyon
	string isimGoster()
	{
		return isim;
	}
	string soyisimGoster() {
		return soyisim;
	}
	int numaraGoster() {
		return numara;
	}
	void ogrenciDegistir();//Numarası verilen öğrenciyi değiştirip yerine yeni öğrenci yazdırması için
};


class sinif
{
public:
	char sinifHarfi;
	Ogrenci ogrenciler[100];
	string sinifIsmi;
	int ogrenciSayi = 0;
	string geciciIsim, geciciSoyisim, geciciSinifisim;
	int gecici = 0, geciciNumara, geciciOgrenci;
	void ogrenciEkle(Ogrenci ogr1);//Programa ve diziye öğrenci eklenilmesinde kullanılan fonksiyon(Gövdesi aşağıdadır)
	void ogrenciSil(int s_numara, int indis);//Numarası girilen öğrencinin diziden silinmesinde kullanılan fonksiyon(Gövdesi aşağıdadır)

	int sinifSayisiBelirle()//Ekrana yazdırmada ve menülerin çalışma aşamasında sınıf sayısının doğru belirlenmesini sağlayan fonksiyon
	{
		ifstream dosyaOku2("kayitlar.txt");
		while (!dosyaOku2.eof())
		{
			dosyaOku2 >> geciciSinifisim >> geciciOgrenci;
			for (int k = 0; k < geciciOgrenci; k++) {
				dosyaOku2 >> geciciIsim >> geciciSoyisim >> geciciNumara;
			}
			gecici++;
		}
		return gecici;
		dosyaOku2.close();
	}
	int sinifSayisi = sinifSayisiBelirle() - 1;//Sınıf sayısı fonksiyon kullanılarak burada atanıyor
	string sinifIsmiAta() //Sınıfa random isim atayan fonksiyon
	{
		sinifSayisi++;
		sinifHarfi = rand() % 26 + 65;
		sinifIsmi = to_string(sinifSayisi) + sinifHarfi;
		return sinifIsmi;
	}
};

class dosyaYonetim
{
public:
	sinif s1;
	Ogrenci ogr1;
	string g_isim;
	string g_soyisim;
	int g_numara;

	void isimAta() //İsimler dosyasından random isim çeken fonksiyon
	{
		string gecici;
		int sayac = 0;
		ifstream dosyaOku("isimler.txt");
		int rastgele = rand() % 4945;
		while (!dosyaOku.eof())//Dosyanın sonuna kadar döngüyü çalıştırır
		{
			sayac++;
			dosyaOku >> gecici;
			if (sayac == rastgele) {
				dosyaOku >> g_isim;
			}
		}
		dosyaOku.close();
	}
	void soyIsimAta()//Soyisimler dosyasından random soyisim çeken fonksiyon
	{
		string gecici;
		int sayac = 0;
		ifstream dosyaOku1("soyisimler.txt");
		int rastgele = rand() % 278;
		while (!dosyaOku1.eof())//Dosyanın sonuna kadar döngüyü çalıştırır
		{
			sayac++;
			dosyaOku1 >> gecici;
			if (sayac == rastgele)
			{
				dosyaOku1 >> g_soyisim;
			}
		}
		dosyaOku1.close();
	}
	void numaraAta()//Random oğrenci numarası atayan fonksiyon
	{
		g_numara = rand() % 100 + 100;
	}
	void sinifYaz() // Dosyaya sınıfı yazdıran fonksiyon
	{
		ofstream dosyaYaz("kayitlar.txt", ios::app);
		dosyaYaz.seekp(0, ios::end);
		dosyaYaz << s1.sinifIsmi << endl;
		dosyaYaz.close();
	}

	void kayitYaz()// Dosyaya oğrenci kayıtlarını yazdıran fonksiyon
	{
		ofstream dosyaYaz("kayitlar.txt", ios::app);

		dosyaYaz.seekp(0, ios::end);
		dosyaYaz << g_isim << " " << g_soyisim << " " << g_numara << endl;
	}

};


class Okul :sinif
{
public:
	dosyaYonetim d2;
	sinif siniflar[25];
	int ordinat;

	//Okul sınıfının kurucu fonksiyonunda kayıtlar dosyasından sınıf dizisine ve bünyesinde bulunan öğrenci dizisine öğrenci bilgileri atanıyor
	Okul()
	{
		ifstream kayitOku("kayitlar.txt");
		string t_isim;
		string t_soyisim;
		int t_numara;
		for (int i = 0; i < 25; i++) {
			kayitOku >> siniflar[i].sinifIsmi;
			kayitOku >> siniflar[i].ogrenciSayi;
			for (int k = 0; k < siniflar[i].ogrenciSayi; k++) {
				kayitOku >> t_isim;
				kayitOku >> t_soyisim;
				kayitOku >> t_numara;
				siniflar[i].ogrenciler[k].isimGonder(t_isim);
				siniflar[i].ogrenciler[k].soyisimGonder(t_soyisim);
				siniflar[i].ogrenciler[k].numaraGonder(t_numara);
			}
		}
		kayitOku.close();
	}
	//Programda önemli olan fonksiyonlardandır.İçinde öğrenci bilgileri olan sınıfları yazdırmak için kullanılır
	//KoordinatAta fonksiyonu burada kullanılmıştır
	void yazdir()
	{
		int apsis = 0;

		for (int i = 0; i < sinifSayisi; i++) {
			ordinat = 3;
			//Sınıfın üst kısmını yazdırıyor
			koordinatAta(apsis, 0);
			cout << solUstKose;
			for (int a = 0; a < 14; a++)
			{
				cout << duz;
			}
			cout << sagUstKose << endl;
			//Sınıfın ismini ve kenarlarını yazdırıyor
			koordinatAta(apsis, 1);
			cout << dikey << setw(7) << siniflar[i].sinifIsmi << setw(8) << dikey << endl;
			//Sınıfın altını yazdırıyor
			koordinatAta(apsis, 2);
			cout << solAltKose;

			for (int b = 0; b < 14; b++)
			{
				cout << duz;
			}
			cout << sagAltKose << endl;

			for (int k = 0; k < siniflar[i].ogrenciSayi; k++) {
				//Öğrencinin üst kısmını çizdiriyor
				koordinatAta(apsis + 2, ordinat);
				cout << solUstKose;
				for (int a = 0; a < 10; a++)
				{
					cout << duz;
				}
				cout << sagUstKose << endl;

				//Öğrenci bilgilerini ve kenarlarını çizdiriyor
				koordinatAta(apsis + 2, (ordinat)+1);
				cout << dikey << setw(10) << siniflar[i].ogrenciler[k].isimGoster() << dikey << endl;

				koordinatAta(apsis + 2, (ordinat)+2);
				cout << dikey << setw(10) << siniflar[i].ogrenciler[k].soyisimGoster() << dikey << endl;

				koordinatAta(apsis + 2, (ordinat)+3);
				cout << dikey << setw(10) << siniflar[i].ogrenciler[k].numaraGoster() << dikey << endl;
				//Öğrencinin altını çizdiriyor
				koordinatAta(apsis + 2, (ordinat)+4);
				cout << solAltKose;

				for (int b = 0; b < 10; b++)
				{
					cout << duz;
				}
				cout << sagAltKose << endl;

				ordinat += 5;//Ordinatın değerini yükseltip ekranda düzgün durmasını sağlıyor

			}
			apsis += 16;//Apsis değerini yükseltip ekranda düzgün durmasını sağlıyor
		}

	}
	//Sınıf ve bünyesinde barındırdığı öğrenci dizisinin içindeki bilgileri kayıtlar dosyasına yazdırıyor
	//Menünün 6. seçeneüinde kullanılıcak
	void kayitYazdir()
	{
		ofstream kayitYaz("kayitlar.txt", ios::out);
		for (int i = 0; i < sinifSayisi; i++) {

			kayitYaz << siniflar[i].sinifIsmi << endl;
			kayitYaz << siniflar[i].ogrenciSayi << endl;
			siniflar[i].sinifSayisi++;
			for (int k = 0; k < siniflar[i].ogrenciSayi; k++) {
				kayitYaz << siniflar[i].ogrenciler[k].isimGoster() << " ";
				kayitYaz << siniflar[i].ogrenciler[k].soyisimGoster() << " ";
				kayitYaz << siniflar[i].ogrenciler[k].numaraGoster() << endl;
			}
		}
	}
	void sinifEkle();//Programa sınıf eklenmesinde kullanılan fonksiyon
	void sinifSil(int k);//Programdan sınıf silmek için kullanılan fonksiyon
};
//Programa ve diziye öğrenci eklenilmesinde kullanılan fonksiyon
//Burada yazılmasının nedeni nesne tanımlanmaları zamanları hataların oluşması
void sinif::ogrenciEkle(Ogrenci ogr1)
{
	dosyaYonetim dosya2;
	dosya2.isimAta();
	dosya2.soyIsimAta();
	dosya2.numaraAta();
	ogr1.isimGonder(dosya2.g_isim);
	ogr1.soyisimGonder(dosya2.g_soyisim);
	ogr1.numaraGonder(dosya2.g_numara);
	cout << "Ogrenci adi : " << ogr1.isimGoster() << endl;
	cout << "Ogrenci soyisim : " << ogr1.soyisimGoster() << endl;
	cout << "Ogrenci numara : " << ogr1.numaraGoster() << endl;
	ogrenciler[ogrenciSayi] = ogr1;
	ogrenciSayi++;

}
//Numarası verilen öğrenciyi değiştirip yerine yeni öğrenci yazdırması için
void Ogrenci::ogrenciDegistir()
{
	dosyaYonetim dosya2;
	dosya2.isimAta();
	dosya2.soyIsimAta();
	dosya2.numaraAta();
	isimGonder(dosya2.g_isim);
	soyisimGonder(dosya2.g_soyisim);
	numaraGonder(dosya2.g_numara);
	cout << "Ogrenci adi : " << isimGoster() << endl;
	cout << "Ogrenci soyisim : " << soyisimGoster() << endl;
	cout << "Ogrenci numara : " << numaraGoster() << endl;
}
//Numarası girilen öğrencinin diziden silinmesinde kullanılan fonksiyon
void sinif::ogrenciSil(int s_numara, int indis)
{
	if (ogrenciler[indis].numaraGoster() == s_numara)
		for (int g = indis; g < ogrenciSayi + 1; g++) {
			Ogrenci temp = ogrenciler[g];
			ogrenciler[g] = ogrenciler[g + 1];
			ogrenciler[g + 1] = temp;
		}
	ogrenciSayi--;
}
//Sınıf dizisine yeni Sınıfın eklenmesinde kullanılan fonksiyon
void Okul::sinifEkle()
{
	siniflar[sinifSayisi - 1].sinifIsmi = sinifIsmiAta();
	siniflar[sinifSayisi - 1].ogrenciSayi = 0;
}
//Sınıf dizisinden seçilmiş sınıfın silinmesini sağlayan fonksiyon
//NOT : Bu işlemi görsel olarak daha da geliştirmek mümkün.Sadece hocamızın exe doyasında yaptığının aynısını yapmak istedim.Saygılar. 
void Okul::sinifSil(int k)
{
	sinifSayisi--;
	siniflar[k] = siniflar[k + 1];
}
//Program sınıfı ana işlemlerin yapıldığı sınıftır
class Program :sinif
{
public:

	Okul okul1;
	sinif s1;
	Ogrenci ogr1;
	int secim;
	string sinifSecim;
	int numaraSecim;
	//Tüm menü ve yazdırma işlemleri bu fonksiyonun içinde yapılıyor
	void calistir()
	{
		while (true)
		{
			okul1.yazdir();//Kayıtlar dosyasında bulunan bilgilere göre ekrana sınıf ve öğrenci dizilerini bastırır
			//Menü ekrana bastırılır ve kullanıcıdan bir seçim yapması beklenir
			koordinatAta(0, okul1.ordinat + 25);
			cout << "1.Ogrenci ekle " << endl;
			cout << "2.Sinif ekle " << endl;
			cout << "3.Ogrenci degistir " << endl;
			cout << "4.Ogrenci sil " << endl;
			cout << "5.Sinif sil " << endl;
			cout << "6.Cikis " << endl;
			cin >> secim;
			//Kullanıcının yaptığı seçime göre kullanıcıdan gerekli bilgiler istenir
			if (secim == 1)
			{
				cout << "Sinif giriniz : ";
				cin >> sinifSecim;
			}
			else if (secim == 3)
			{
				cout << "Ogrenci numarasi : ";
				cin >> numaraSecim;
			}
			else if (secim == 4)
			{
				cout << "Ogrenci numarasi : ";
				cin >> numaraSecim;
			}
			else if (secim == 5)
			{
				cout << "Sinif seciniz : ";
				cin >> sinifSecim;
			}
			//Gerekli bilgiler alındıktan sonra işlemlere geçit yapıyoruz
			for (int i = 0; i < s1.sinifSayisi; i++)
			{
				if (secim == 1 && sinifSecim == okul1.siniflar[i].sinifIsmi) //Burada programa ve öğrenci dizisine yeni öğrenci ekleniyor
				{
					okul1.siniflar[i].ogrenciEkle(ogr1);
					system("pause");
					break;
				}
				else if (secim == 2 && i == okul1.siniflar[i].sinifSayisi - 1)//Burada programa ve sınıf dizisine yeni sınıf ekleniyor 
				{
					okul1.sinifEkle();
					s1.sinifSayisi++;
					system("cls");
					break;
				}
				else if (secim == 5 && sinifSecim == okul1.siniflar[i].sinifIsmi)//Burada seçilmiş sınıf ekrandan ve diziden siliniyor
				{
					okul1.sinifSil(i);
				}

				for (int k = 0; k < okul1.siniflar[i].ogrenciSayi; k++)
				{
					//Burada numarası girilmiş öğrenci yenisine değiştiriliyor
					if (secim == 3 && numaraSecim == okul1.siniflar[i].ogrenciler[k].numaraGoster())
					{
						okul1.siniflar[i].ogrenciler[k].ogrenciDegistir();
						system("pause");
						break;
					}
					//Burada numarası girilen öğrencinin kaydı diziden ve ekrandan siliniyor
					else if (secim == 4 && numaraSecim == okul1.siniflar[i].ogrenciler[k].numaraGoster())
					{
						okul1.siniflar[i].ogrenciSil(numaraSecim, k);
						break;
					}
					//Burada diziler ve içerikleri kayıtlar dosyasına kaydediliyor ve programdan çıkış yapılıyor
					else if (secim == 6)
					{
						okul1.kayitYazdir();
						DebugBreak();
					}
				}
			}
			//Burada ekran siliniyor ve yapılan değişiklikler ekrana bastırılıyor
			system("cls");
		}
	}
};
//Main fonksiyonunda program nesnesi çalıştırılıyor
int main()
{
	Program prog;
	prog.calistir();
}