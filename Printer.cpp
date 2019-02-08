#include<iostream>
#include<string>
#include<vector>
#include<iterator>
#include<regex>
#include<exception>
using namespace std;

const char *crt = "\n---------------------------------------\n";

class DatumVrijeme {
	int *_dan, *_mjesec, *_godina, *_sati, *_minuti;
public:
	DatumVrijeme(int dan = 1, int mjesec = 1, int godina = 2000, int sati = 0, int minuti = 0) {
		_dan = new int(dan);
		_mjesec = new int(mjesec);
		_godina = new int(godina);
		_sati = new int(sati);
		_minuti = new int(minuti);

	}
	DatumVrijeme(const DatumVrijeme &obj) {
		_dan = new int(*obj._dan);
		_mjesec = new int(*obj._mjesec);
		_godina = new int(*obj._godina);
		_sati = new int(*obj._sati);
		_minuti = new int(*obj._minuti);
	}
	DatumVrijeme& operator=(const DatumVrijeme& obj) {
		if (this != &obj) {
			delete _dan;
			delete _mjesec;
			delete _godina;
			delete _sati;
			delete _minuti;

			_dan = new int(*obj._dan);
			_mjesec = new int(*obj._mjesec);
			_godina = new int(*obj._godina);
			_sati = new int(*obj._sati);
			_minuti = new int(*obj._minuti);
		}
		return *this;
	}
	//operator dodjele eventualno
	~DatumVrijeme() {
		delete _dan; _dan = nullptr;
		delete _mjesec; _mjesec = nullptr;
		delete _godina; _godina = nullptr;
		delete _sati; _sati = nullptr;
		delete _minuti; _minuti = nullptr;

	}
	friend bool operator==(const DatumVrijeme& dat1, const DatumVrijeme& dat2);
	friend ostream& operator<< (ostream &COUT, const DatumVrijeme &obj) {
		COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina << " " << *obj._sati << ":" << *obj._minuti;
		return COUT;
	}
};
bool operator==(const DatumVrijeme& dat1, const DatumVrijeme& dat2) {
	if (dat1._godina == dat2._godina && dat1._mjesec == dat2._mjesec && dat1._dan == dat2._dan && dat1._minuti == dat2._minuti)
		return true;
}
template<class T1, class T2 = int>
class FITKolekcija {
	T1 * _elementi1;
	T2 * _elementi2;
	int _trenutno;
public:
	FITKolekcija() {
		_elementi1 = nullptr;
		_elementi2 = nullptr;
		_trenutno = 0;
	}
	~FITKolekcija() {
		delete[] _elementi1; _elementi1 = nullptr;
		delete[] _elementi2; _elementi2 = nullptr;
	}
	void Dodaj(const T1& el1, const T2& el2) {
		T1*elementi1 = new T1[_trenutno + 1];
		T2*elementi2 = new T2[_trenutno + 1];

		for (int i = 0; i < _trenutno; i++) {
			elementi1[i] = _elementi1[i];
			elementi2[i] = _elementi2[i];
		}
		delete[] _elementi1;
		delete[] _elementi2;

		elementi1[_trenutno] = el1;
		elementi2[_trenutno] = el2;
		_elementi1 = elementi1;
		_elementi2 = elementi2;

		_trenutno++;
	}
	void Sortiraj() {
		int zavrsena = 0;

		do {
			zavrsena = 1;
			for (int i = 0; i < _trenutno - 1; i++) {
				if (_elementi1[i] > _elementi1[i + 1]) {
					T1 temp = _elementi1[i];
					_elementi1[i] = _elementi1[i + 1];
					_elementi1[i + 1] = temp;
					zavrsena = 0;
				}
			}
		} while (!zavrsena);
	}
	void DodajNaLokaciju(const T1& el1, const T2& el2, int location) {
		T1*elementi1 = new T1[_trenutno + 1];
		T2*elementi2 = new T2[_trenutno + 1];

		for (int i = 0; i < _trenutno; i++) {
			if (i < location) {
				elementi1[i] = _elementi1[i];
				elementi2[i] = _elementi2[i];
			}
			else {
				for (int j = i+1; j < _trenutno+1; j++) {
					elementi1[j] = _elementi1[i];
					elementi2[j] = _elementi2[i];
				}
				elementi1[location] = el1;
				elementi2[location] = el2;
			}
		}
		delete[] _elementi1;
		delete[] _elementi2;

		
		_elementi1 = elementi1;
		_elementi2 = elementi2;

		_trenutno++;
	}
	FITKolekcija<T1, T2>* GetJedinstveni() {
		/*METODA GetJedinstveni VRAÆA LISTU JEDINSTVENIH ELEMENATA TJ. ELEMENATA KOJI NE SADRŽE DUPLIKATE (POJAM DUPLIKAT SE ODNOSI NA ISTE VRIJEDNOSTI ELEMENATA T1 I T2).
		//ELEMENTI KOJI SE DUPLIRAJU SE U OVOJ LISTI TREBAJU POJAVITI SAMO JEDNOM.*/

		FITKolekcija * _lista = new FITKolekcija<T1, T2>();
		bool jedinstven;
		for (int i = 0; i < _trenutno; i++) {
			jedinstven = true;
			for (int j = 0; j < _trenutno; j++) {
				if (i != j) {
					if (_elementi1[i] == _elementi1[j] && _elementi2[i] == _elementi2[j])
						jedinstven = false;
				}
			}
			if (jedinstven) {
				_lista->Dodaj(_elementi1[i], _elementi2[i]);
			}
		}
		return _lista;
	}
	T1 * GetT1() { return _elementi1; }
	T2 * GetT2() { return _elementi2; }
	T1& getElement1(int i) {
		return _elementi1[i];
	}
	T2& getElement2(int i) {
		return _elementi2[i];
	}
	int GetTrenutno() { return _trenutno; }

	friend ostream& operator<< (ostream &COUT, const FITKolekcija &obj) {
		for (size_t i = 0; i < obj._trenutno; i++)
			COUT << obj._elementi1[i] << " " << obj._elementi2[i] << endl;
		return COUT;
	}
};

enum vrstaDokumenta { PDF, DOC, TXT, HTML };

class Dokument {
	vrstaDokumenta _vrsta;
	string _naziv;
	string _sadrzaj;
	int _brojStranica;
public:
	Dokument() { _brojStranica = 0; }
	Dokument(vrstaDokumenta vrsta, string naziv) {
		_naziv = naziv; _vrsta = vrsta; _brojStranica = 0;
	}
	void DodajSadrzaj(string sadrzaj) {
		_sadrzaj = sadrzaj;
		//	//BROJ STRANICA DOKUMENTA SE AUTOMATSKI ODREÐUJE PRILIKOM DODAVANJA SADRŽAJA. ZA POTREBE ISPITA PRETPOSTAVLJAMO DA NA JEDNU STRANICU MOŽE STATI 30 ZNAKOVA UKLJUÈUJUÆI I 
	//RAZMAKE
		_brojStranica =sadrzaj.size();
		_brojStranica /= 30;
		if (_brojStranica % 30 >= 1)
			_brojStranica++;
	}
	string GetNaziv()const { return _naziv; };
	string GetSadrzaj()const { return _sadrzaj; };
	vrstaDokumenta GetVrsta() { return _vrsta; };
	void UvecajBrojStranica() { _brojStranica++; }
	int GetBrojStranica() { return _brojStranica; }
	friend ostream & operator<<(ostream&COUT, const Dokument & obj) {
		COUT << obj._naziv << "." << obj._vrsta << " (" << obj._brojStranica << ")\n" << obj._sadrzaj << endl;
		return COUT;
	}
};
class Uredjaj {
protected:
	char * _proizvodjac;
	char * _model;
public:
	Uredjaj(const char * proizvodjac, const char * model) {
		int vel = strlen(proizvodjac) + 1;
		_proizvodjac = new char[vel];
		strcpy_s(_proizvodjac, vel, proizvodjac);
		vel = strlen(model) + 1;
		_model = new char[vel];
		strcpy_s(_model, vel, model);
	}
	//konstruktor kopije sigurno
	//operator dodjele
	~Uredjaj() {
		delete[] _proizvodjac; _proizvodjac = nullptr;
		delete[] _model; _model = nullptr;
	}
	friend ostream & operator<<(ostream&COUT, const Uredjaj & obj) {
		COUT << obj._proizvodjac << "." << obj._model << endl;
		return COUT;
	}
};
class Printer : public Uredjaj {
	FITKolekcija<DatumVrijeme, Dokument> _printaniDokumenti;
	vector<string> _zabranjeneRijeci;
public:
	Printer(const char * proizvodjac, const char * model): Uredjaj(proizvodjac,model){}
	void DodajZabranjenuRijec(string zabranjenaRijec) {
		vector<string>::iterator it = _zabranjeneRijeci.begin();

		for (it; it < _zabranjeneRijeci.end(); it++) {
			if (*it == zabranjenaRijec) {
				cout << "Nisam dodao " << zabranjenaRijec << endl;
				return;
			}
		}
		_zabranjeneRijeci.push_back(zabranjenaRijec);
		

	}
	void Printaj(const DatumVrijeme& datum, const Dokument& doc) {
		/*
		DA BI PRINTER ISPRINTAO NEKI DOKUMENT MORAJU BITI ZADOVOLJENA SLJEDEÆA PRAVILA:
		1. NAZIV DOKUMENTA MORA BITI U SLJEDEÆEM FORMATU npr: ispitPRIII.doc
		NAZIV DOKUMENTA MOŽE SADRŽAVATI SAMO SLOVA (NAJMANJE 5, NAJVIŠE 15), A EKSTENZIJA MOŽE
		BITI SAMO NEKA OD DOZVOLJENIH VRSTOMDOKUMENTA

		2. SADRŽAJ DOKUMENTA U SEBI NE SMIJE POSJEDOVATI NITI JEDNU ZABRANJENU RIJEÈ
		UKOLIKO NEKI OD NAVEDENIH USLOVA NIJE ZADOVOLJEN FUNKCIJA TREBA DA BACI EXCEPTION SA
		ODGOVARAJUÆOM PORUKOM, ALI ÆE DOKUMENT BITI POHRANJEN U KOLEKCIJU _printaniDokumenti.
		UKOLIKO DOKUMENT ISPUNJAVA SVE USLOVE ZA PRINTANJE POTREBNO JE NA KONZOLU ISPISATI
		SADRŽAJ DOKUMENTA KOJI SE PRINTA

		*/
	
		_printaniDokumenti.Dodaj(datum, doc);

		if (!regex_match(doc.GetNaziv(), regex("([A-Za-z]{5,15})(\\.)(doc|txt|pdf|html)")))
			throw exception("Naziv dokumenta nije u ispravnom formatu");

		for (size_t i = 0; i < _zabranjeneRijeci.size(); i++)
			if (doc.GetSadrzaj().find(_zabranjeneRijeci[i]) != string::npos )
				throw exception("U sadrzaju dokumenta postoji zabranjenih rijeci");

	}
	double GetProsjecanBrojStranicaPoDatumu(const DatumVrijeme& date) {
		double suma = 0;
		double brojDatuma = 0;
		for (int i = 0; i < _printaniDokumenti.GetTrenutno(); i++) {
			if (_printaniDokumenti.getElement1(i) == date) {
				suma+=_printaniDokumenti.getElement2(i).GetBrojStranica();
				brojDatuma++;
			}
		}
		return suma / brojDatuma;
	}
	string GetTopZabranjenuRijec() {
		int trenutno = 0, najvise = 0, indeks = 0;

		for (int j = 0; j < _zabranjeneRijeci.size(); j++) {
			trenutno = 0;
			regex reg("(" + _zabranjeneRijeci[j] + ")");
			for (int i = 0; i < _printaniDokumenti.GetTrenutno(); i++) {
				string tekst = _printaniDokumenti.getElement2(i).GetSadrzaj();
				sregex_iterator its(tekst.begin(), tekst.end(), reg);
				sregex_iterator ite;
				while (its != ite) {
					its++;
					trenutno++;
				}
			}
			if (trenutno > najvise) { najvise = trenutno; indeks = j; }
		} return _zabranjeneRijeci[indeks];
	}
	void UkloniDokumente() {
		FITKolekcija<DatumVrijeme, Dokument> f;
		bool ukloni = false;
		for (size_t i = 0; i < _printaniDokumenti.GetTrenutno(); i++)
		{
			ukloni = false;
			if (!regex_match(_printaniDokumenti.getElement2(i).GetNaziv(), regex("([A-Za-z]{5,15})(\\.)(doc|txt|pdf|html)"))) {
				ukloni = true;
			}
			for (vector<string>::iterator j = _zabranjeneRijeci.begin(); j != _zabranjeneRijeci.end(); j++)
			{
				if (_printaniDokumenti.getElement2(i).GetSadrzaj().find(*j) != string::npos) {
					ukloni = true;
					break;
				}
			}
			if (!ukloni) {
				f.Dodaj(_printaniDokumenti.GetT1()[i], _printaniDokumenti.GetT2()[i]);
			}
		}
		_printaniDokumenti = f;
	}
	FITKolekcija<DatumVrijeme, Dokument> & GetPrintaniDokumenti() { return _printaniDokumenti; };
	vector<string> & GetZabranjeneRijeci() { return _zabranjeneRijeci; };
};

void main()
{
	/****************************************************************************
	1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
	2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR ÆE BITI OZNACENO KAO "RE"
	3. SPAŠAVAJTE PROJEKAT KAKO BI SE SPRIJEÈILO GUBLJENJE URAÐENOG ZADATKA
	4. PROGRAMSKI CODE SE TAKOÐER NALAZI U FAJLU CODE.TXT
	5. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTIÈNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U, OSIM U SLUÈAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMOÆNE FUNKCIJE MOŽETE IMENOVATI I DODAVATI PO ŽELJI.
	6. IZUZETAK BACITE U FUNKCIJAMA U KOJIMA JE TO NAZNAÈENO.
	****************************************************************************/

#pragma region TestiranjeDatumVrijeme
	DatumVrijeme danas(1, 2, 2017, 10, 15);
	DatumVrijeme sutra(danas); //konstrukor kopije
	DatumVrijeme prekosutra; //defaultni konstruktor
	prekosutra = danas; //operator =
	cout << danas << endl << sutra << endl << prekosutra << crt; //svi trebaju ispisati 1.2.2017 10:15
#pragma endregion
#pragma region FITKolekcija

	int v6 = 6, v13 = 13, v32 = 32, v63 = 63, v98 = 98, v109 = 109, v196 = 196;

	FITKolekcija<int, int> brojevi;
	brojevi.Dodaj(v196, v6);
	brojevi.Dodaj(v13, v32);
	brojevi.Dodaj(v98, v196);
	brojevi.Dodaj(v63, v13);
	brojevi.Dodaj(v98, v196);
	brojevi.Dodaj(v196, v6);
	brojevi.Dodaj(v196, v6); //dodajem jos jedan da bi fino provjerila jedinstvenost

	cout << brojevi << crt;
//	//SORTIRANJE ÈLANOVA KOLEKCIJE SE VRŠI U RASTUÆEM REDOSLIJEDU NA OSNOVU VRIJEDNOSTI ELEMENTA TIPA T1
	brojevi.Sortiraj();
	cout << brojevi << crt;
//	//BROJ 2 SE ODNOSI NA LOKACIJU/INDEKS UNUTAR LISTE NA KOJI JE POTREBNO DODATI NOVE ELEMENTE
	brojevi.DodajNaLokaciju(v109, v6, 2);
	cout << brojevi << crt;
	brojevi.Sortiraj();
	cout << brojevi << crt;
//	/*METODA GetJedinstveni VRAÆA LISTU JEDINSTVENIH ELEMENATA TJ. ELEMENATA KOJI NE SADRŽE DUPLIKATE (POJAM DUPLIKAT SE ODNOSI NA ISTE VRIJEDNOSTI ELEMENATA T1 I T2). 
	//ELEMENTI KOJI SE DUPLIRAJU SE U OVOJ LISTI TREBAJU POJAVITI SAMO JEDNOM.*/
	FITKolekcija<int, int> * jedinstveni = brojevi.GetJedinstveni();
	cout << "JEDINSTVENI: " << endl;
	
	cout << *jedinstveni << crt;
	*jedinstveni = brojevi; 
	cout << *jedinstveni << crt;
//
	Dokument ispitPRIII(DOC, "ispitPRIII.doc");
//	//BROJ STRANICA DOKUMENTA SE AUTOMATSKI ODREÐUJE PRILIKOM DODAVANJA SADRŽAJA. ZA POTREBE ISPITA PRETPOSTAVLJAMO DA NA JEDNU STRANICU MOŽE STATI 30 ZNAKOVA UKLJUÈUJUÆI I 
	//RAZMAKE
	ispitPRIII.DodajSadrzaj("NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR ÆE BITI OZNACENO KAO");
	cout << "Broj stranica -> " << ispitPRIII.GetBrojStranica() << endl;
	Dokument ispitBaze(DOC, "ispitBaze.doc");
	ispitBaze.DodajSadrzaj("PROGRAMSKI CODE SE TAKOÐER NALAZI U FAJLU CODE.TXT");
	cout << ispitBaze << endl;//ISPISUJE SVE DOSTUPNE PODATKE O DOKUMENTU
//
	Printer hp3200("HP", "3200");
//	//PRINTER NEÆE DOZVOLITI PRINTANJE DOKUMENATA U ÈIJEM SADRŽAJU SE NALAZI NEKA OD ZABRANJENIH RIJEÈI
	hp3200.DodajZabranjenuRijec("RE");// :)
	hp3200.DodajZabranjenuRijec("RAT");
	hp3200.DodajZabranjenuRijec("UBITI");
	hp3200.DodajZabranjenuRijec("RE");// ONEMOGUÆITI PONAVLJANJE ZABRANJENIH RIJEÈI, KORISTITI ITERATORE
	hp3200.DodajZabranjenuRijec("MRZITI");
	try
	{
		/*
		DA BI PRINTER ISPRINTAO NEKI DOKUMENT MORAJU BITI ZADOVOLJENA SLJEDEÆA PRAVILA:
		1. NAZIV DOKUMENTA MORA BITI U SLJEDEÆEM FORMATU npr: ispitPRIII.doc
		NAZIV DOKUMENTA MOŽE SADRŽAVATI SAMO SLOVA (NAJMANJE 5, NAJVIŠE 15), A EKSTENZIJA MOŽE
		BITI SAMO NEKA OD DOZVOLJENIH VRSTOMDOKUMENTA
		2. SADRŽAJ DOKUMENTA U SEBI NE SMIJE POSJEDOVATI NITI JEDNU ZABRANJENU RIJEÈ
		UKOLIKO NEKI OD NAVEDENIH USLOVA NIJE ZADOVOLJEN FUNKCIJA TREBA DA BACI EXCEPTION SA
		ODGOVARAJUÆOM PORUKOM, ALI ÆE DOKUMENT BITI POHRANJEN U KOLEKCIJU _printaniDokumenti.
		UKOLIKO DOKUMENT ISPUNJAVA SVE USLOVE ZA PRINTANJE POTREBNO JE NA KONZOLU ISPISATI
		SADRŽAJ DOKUMENTA KOJI SE PRINTA

		*/
		hp3200.Printaj(danas, ispitPRIII);
		hp3200.Printaj(danas, ispitBaze);

		/*
		IMPLEMENTIRATI PRINTANJE U ZASEBNIM NITIMA UZ KORIŠTENJE sleep_for FUNKCIJE
		VODITI RAÈUNA O DIJELJENJU ZAJEDNIÈKIH RESURSA
		*/

	}
	catch (exception& err)
	{
		cout << err.what() << endl;
	}
//
	
//	//KOD POREÐENJA DATUMA PRINTANJA NIJE POTREBNO POREDITI MINUTE, SAMO DATUM I SATE
	cout << "Prosjecan broj printanih stranica za " << danas << " je -> " << hp3200.GetProsjecanBrojStranicaPoDatumu(danas) << crt;
	cout << "Najcesce koristena zabranjena rijec je -> " << hp3200.GetTopZabranjenuRijec() << crt;
////
	Printer hp4000(hp3200);
	cout << "Prosjecan broj printanih stranica za " << danas << " je -> " << hp4000.GetProsjecanBrojStranicaPoDatumu(danas) << crt;
	cout << "Najcesce koristena zabranjena rijec je -> " << hp4000.GetTopZabranjenuRijec() << crt;
	hp4000.UkloniDokumente();//UKLANJA SVE DOKUMENTE KOJI NISU ZADOVOLJILI USLOVE ZA PRINTANJE
	cout << hp4000 << crt;

	system("pause");
#pragma endregion
}
