/****************************************************************************
1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR CE BITI OZNACENO KAO "RE"
3. SPASAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URADJENOG ZADATKA
4. PROGRAMSKI CODE SE TAKODJER NALAZI U FAJLU CODE_.TXT
****************************************************************************/
#include<iostream>
using namespace std;

template<class T1, class T2>
class Kolekcija {
	T1 * _elementi1;
	T2 * _elementi2;
	int _trenutnoElemenata;
public:
	Kolekcija() {
		_elementi1 = nullptr;
		_elementi2 = nullptr;
		_trenutnoElemenata = 0;
	}
	Kolekcija(const Kolekcija& obj) {
		_elementi1 = new T1[obj._trenutnoElemenata];
		_elementi2 = new T2[obj._trenutnoElemenata];

		for (int i = 0; i < obj._trenutnoElemenata; i++) {
			_elementi1[i] = obj._elementi1[i];
			_elementi2[i] = obj._elementi2[i];
		}

		_trenutnoElemenata = obj._trenutnoElemenata;
	}
	~Kolekcija() {
		delete[] _elementi1;
		delete[] _elementi2;
		_elementi1 = nullptr;
		_elementi2 = nullptr;
	}
	Kolekcija& operator=(const Kolekcija& obj) {
		if (this != &obj) {
			delete[] _elementi1;
			delete[] _elementi2;

			_elementi1 = new T1[obj._trenutnoElemenata];
			_elementi2 = new T2[obj._trenutnoElemenata];

			for (int i = 0; i < obj._trenutnoElemenata; i++) {
				_elementi1[i] = obj._elementi1[i];
				_elementi2[i] = obj._elementi2[i];
			}

			_trenutnoElemenata = obj._trenutnoElemenata;
		}
		return *this;
	}
	void AddElement(T1 el1,T2 el2) {
		T1*temp1 = new T1[_trenutnoElemenata + 1];
		T2*temp2 = new T2[_trenutnoElemenata + 1];

		for (int i = 0; i < _trenutnoElemenata; i++) {
			temp1[i] = _elementi1[i];//operator=
			temp2[i] = _elementi2[i];
		}
		delete[] _elementi1;
		delete[] _elementi2;

		_elementi1 = temp1;
		_elementi2 = temp2;
		_elementi1[_trenutnoElemenata] = el1;
		_elementi2[_trenutnoElemenata++] = el2;
	}
	void RemoveElement(int index) {
		T1*temp1 = new T1[_trenutnoElemenata - 1];
		T2*temp2 = new T2[_trenutnoElemenata - 1];

		for (int i = 0, j=0; i < _trenutnoElemenata; i++) {
			if (i != index) {
				temp1[j] = _elementi1[i];//operator=
				temp2[j++] = _elementi2[i];
			}
		}
		delete[] _elementi1;
		delete[] _elementi2;

		_elementi1 = temp1;
		_elementi2 = temp2;
		_trenutnoElemenata--;
	}
	int getTrenutno()const {
		return _trenutnoElemenata;
	}
	T1& operator[](int i) {
		return _elementi1[i];
	}
	T2& GetElement2(int i) {
		return _elementi2[i];
	}
	friend ostream& operator<< <>(ostream& cout, Kolekcija<T1, T2>&element);
};
template<class T1,class T2>
ostream& operator<< <>(ostream& cout, Kolekcija<T1, T2>&element){
	for (int i = 0; i < element._trenutnoElemenata; i++) {
		cout << element._elementi1[i] << " " << element._elementi2[i] << endl;
	}
	return cout;
}
class Datum {
	int *_dan, *_mjesec, *_godina;
public:
	Datum(int dan = 1, int mjesec = 1, int godina = 2000) {
		_dan = new int(dan);
		_mjesec = new int(mjesec);
		_godina = new int(godina);
	}
	Datum(const Datum& obj) {
		_dan = new int(*obj._dan);
		_mjesec = new int(*obj._mjesec);
		_godina = new int(*obj._godina);
	}
	Datum& operator=(const Datum& obj) {
		if (this != &obj) {
			
			_dan = new int(*obj._dan);
			_mjesec = new int(*obj._mjesec);
			_godina = new int(*obj._godina);
		}
		return *this;
	}
	~Datum() {
		delete _dan; _dan = nullptr;
		delete _mjesec; _mjesec = nullptr;
		delete _godina; _godina = nullptr;
	}
	friend bool operator==(const Datum& date1, const Datum& date2);
	friend ostream& operator<< (ostream &COUT, Datum &obj) {
		COUT << *obj._dan << " " << *obj._mjesec << " " << *obj._godina;
		return COUT;
	}
};
bool operator==(const Datum& date1, const Datum& date2) {
	if (*date1._dan == *date2._dan && *date1._mjesec == *date2._mjesec && *date1._godina == *date2._godina)
		return true;
	return false;
}
class Student {
	char * _imePrezime;
	Datum * _datumRodjenja;
public:
	Student(const char * imePrezime = "---", Datum d = Datum()) {
		int size = strlen(imePrezime) + 1;
		_imePrezime = new char[size];
		strcpy_s(_imePrezime, size, imePrezime);
		_datumRodjenja = new Datum(d);
	}
	Student(const Student& obj) {
		int size = strlen(obj._imePrezime) + 1;
		_imePrezime = new char[size];
		strcpy_s(_imePrezime, size, obj._imePrezime);
		_datumRodjenja = new Datum(*obj._datumRodjenja);
	}
	Student& operator=(const Student& obj) {
		if (this != &obj) {
			delete[] _imePrezime;

			int size = strlen(obj._imePrezime) + 1;
			_imePrezime = new char[size];
			strcpy_s(_imePrezime, size, obj._imePrezime);
			*_datumRodjenja = *obj._datumRodjenja;// datum uvijek dobija novu vrijednost u konstruktoru, znaci da mu ovdje ne treba new
		}
		return *this;
	}
	~Student() { delete[] _imePrezime; delete _datumRodjenja; }
	friend bool operator==(const Student& student1, const Student& student2);
	friend ostream& operator<<(ostream& cout, Student& s);
};
bool operator==(const Student& student1, const Student& student2) {
	if (strcmp(student1._imePrezime, student2._imePrezime) == 0 && *student1._datumRodjenja==*student2._datumRodjenja)
		return true;
	return false;
}
ostream& operator<<(ostream& cout, Student& s) {
	cout << "Ime i prezime: " << s._imePrezime << endl;
	cout << "Datum rodjenja:" << *s._datumRodjenja << endl;
	return cout;
}
class Ispit {
	Datum _datumOdrzavanja;
	char * _opisIspita;
	Kolekcija<Student, Datum> _prijave;
	Kolekcija<Student, int> _rezultati;
public:
	Ispit(const char* opisIspita, Datum datumOdrzavanja){
		int v = strlen(opisIspita) + 1;
		_opisIspita = new char[v];
		strcpy_s(_opisIspita, v, opisIspita);

		_datumOdrzavanja = datumOdrzavanja;
	}
	Ispit(const Ispit& obj):_datumOdrzavanja(obj._datumOdrzavanja), _prijave(obj._prijave),_rezultati(obj._rezultati) {
		int v = strlen(obj._opisIspita) + 1;
		_opisIspita = new char[v];
		strcpy_s(_opisIspita, v, obj._opisIspita);

	}
	~Ispit() {
		delete[] _opisIspita;
		_opisIspita = nullptr;
	}
	bool DodajPrijavu(Student& student, Datum& datum) {
		//ne moze dvaput isti student
		for (int i = 0; i < _prijave.getTrenutno(); i++) {
			if (_prijave[i] == student) {
				return false;
			}
		}

		_prijave.AddElement(student, datum);
	}
	void DodajRezultat(Student& student, int ocjena) {
		//pohraniti u niz rezultati ako student postoji u nizu prijave
		for (int i = 0; i < _rezultati.getTrenutno(); i++) {
			if (_rezultati[i] == student) {
				_rezultati.GetElement2(i) = ocjena;
				return;
			}
		}
		for (int i = 0; i < _prijave.getTrenutno(); i++) {
			if (_prijave[i] == student) {
				_rezultati.AddElement(student, ocjena);
			}
		}
	}
	void Sortiraj() {
		int zavrsena;
		do {
			zavrsena = 1;
			for (int i = 0; i < _rezultati.getTrenutno() - 1; i++) {
				if (_rezultati.GetElement2(i) > _rezultati.GetElement2(i+1)) {
					int temp = _rezultati.GetElement2(i);
					_rezultati.GetElement2(i) = _rezultati.GetElement2(i + 1);
					_rezultati.GetElement2(i + 1) = temp;
					zavrsena = 0;
				}
			}
		} while (!zavrsena);
	}
	bool ZakljuciRezultate() {
		
		int index;
		for (int i = 0; i < _prijave.getTrenutno(); i++) {
			index = -1;
			for (int j = 0; j < _rezultati.getTrenutno(); j++) {
				if (_prijave[i] == _rezultati[j]) {
					index = i;
					return false;
					break;
				}
			}
			if (index == -1) {
				_rezultati.AddElement(_prijave[i], 5);
				return true;
			}
		}
	}
	friend ostream& operator<<(ostream& cout, Ispit& ispit);
};
ostream& operator<<(ostream& cout, Ispit& ispit) {
	cout << "Datum odrzavanja: " << ispit._datumOdrzavanja << endl;
	cout << "Opis ispita:" << ispit._opisIspita << endl;
	cout << "Prijave\n" << ispit._prijave << endl;
	cout << "Rezultati\n" << ispit._rezultati << endl;

	return cout;
}
const char *crt = "\n--------------------------------------------------\n";
void main() {

	//REGIONI olaksavaju organizaciju programskog code-a, te ih mozete ukloniti ukoliko vam otezavaju preglednost

#pragma region TestiranjeKolekcije
	Kolekcija<int, double> kolekcija1;
	for (size_t i = 0; i < 50; i++)
		kolekcija1.AddElement(i, i + 0.3);
	cout << kolekcija1 << endl;
	cout << crt;
	Kolekcija<int, double> kolekcija2;
	kolekcija2 = kolekcija1;
	kolekcija1.RemoveElement(2);//UMANJITI VELIÈINU NIZA
	cout << kolekcija2 << crt;
	if (kolekcija1.getTrenutno() == kolekcija2.getTrenutno())
		cout << "ISTI BROJ ELEMENATA" << endl;
	Kolekcija<int, double> kolekcija3(kolekcija2);
	cout << kolekcija3 << crt;
#pragma endregion

#pragma region TestiranjeDatuma
	Datum danas(26, 11, 2015);
	Datum sutra(danas); //konstruktor kopije
	Datum prekosutra;//defaultni konstruktor
	prekosutra = danas;//operator dodjele
	cout << danas << endl << sutra << endl << prekosutra << crt;//operator za ispis
#pragma endregion

#pragma region TestiranjeStudenta
	Student denis("Denis Music", Datum(26, 11, 1990));
	Student jasmin("Jasmin Azemovic", Datum(22, 11, 1990));
	Student goran;//defaultni konst
	goran = jasmin;//operator=
	Student adel("Adel Handzic", Datum(25, 8, 1990));
	Student marija("Marija Herceg", Datum(15, 6, 1990));
#pragma endregion

#pragma region TestiranjeIspita
	Ispit prIII("PRIII::26.11.2015", danas);
	//DodajPrijavu - dodaje novog studenta u listu prijavljenih za ispit. onemoguciti dodavanje dva ista studenta
	if (prIII.DodajPrijavu(denis, danas))
		cout << denis << " DODAT na spisak" << endl;
	if (prIII.DodajPrijavu(jasmin, danas))
		cout << jasmin << " DODAT na spisak" << endl;
	if (prIII.DodajPrijavu(goran, danas))//ovaj se nece dodati jer je goran ustvari jasmin
		cout << goran << " DODAT na spisak" << endl;
	if (prIII.DodajPrijavu(adel, danas))
		cout << adel << " DODAT na spisak" << endl;
	if (prIII.DodajPrijavu(marija, danas))
		cout << marija << " DODAT na spisak" << endl;

	cout << crt << endl;
	/*DodajRezultat - dodaje ocjenu koju je student ostvario na ispitu. 
	za dodavanje ocjene student je prethodno trebao biti prijavljen na ispit
	*/
	prIII.DodajRezultat(goran, 7);//ovo je ustvari jasmin
	prIII.DodajRezultat(jasmin, 6);
	prIII.DodajRezultat(adel, 8);
	prIII.DodajRezultat(marija, 9);

	///*Sortiraj - sortira rezultate ispita prema ocjeni*/
	prIII.Sortiraj();
	cout << prIII << endl;
	///*ZakljuciRezultate - dodaje ocjenu 5 svim studentima koji su prijavili ispit a nije im evidentirana ocjena*/
	if (prIII.ZakljuciRezultate()) {
		cout << prIII << crt;
	};
	//rezultati ispita se smiju ispisivati jedino ukoliko su prethodno zakljuèeni

	Ispit prIII_2(prIII);
	cout << prIII_2 << crt;
#pragma endregion

	system("pause>0");

}
