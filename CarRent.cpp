#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Date {
	int _day;
	int _month;
	int _year;
public:
	Date() {
		_day = 1;
		_month = 1;
		_year = 1111;
	}
	Date(int day, int month, int year) {
		_day = day;
		_month = month;
		_year = year;
	}
	void Info() {
		cout << _day << "/" << _month << "/" << _year << endl;
	}
};
class Car {
	string _carManufacturer;
	string _carModel;
	string _carColor;
	double _price; //price od the car is displayed as a daily rent price in BAM (KM)
public:
	Car() {
		_carManufacturer = "Unknown";
		_carModel = "Unknown";
		_carColor = "Unknown";
		_price = 0.00;
	}
	
	Car(string carManufacturer, string carModel, string carColor, double price) {
		_carManufacturer = carManufacturer;
		_carModel = carModel;
		_carColor = carColor;
		_price = price;
	}
	Car(const Car& obj) { //this is a copy constructor
		_carManufacturer =obj._carManufacturer;
		_carModel = obj._carModel;
		_carColor = obj._carColor;
		_price = obj._price;
	}

	string getManMod() {
		return _carManufacturer + " " + _carModel;
	}
	double getPrice() {
		return _price;
	}
	
	void Info() {
		cout<< _carManufacturer << " " << _carModel << ", " << _carColor<< endl ;
		cout << "\t\t\t\tPrice: " << _price << " KM" << endl << endl;
	}
};
class Agency {
	string _agencyName;
	vector<Car> _cars; // making a vector, vector is like an array with no default array length, instead we can put as many objects as we want in it
		//without having to worry about array lenghts
public:
	Agency(string agencyName) {
		_agencyName = agencyName;
	}
	void addCars(const Car& car) {
		_cars.push_back(car);	//this is how we put objects into a VECTOR. Push back funtion demand a constructor copy od the object it's pushing into a vector.

	}
	void bubbleSort() {
		int finished = 0;
		do {
			finished = 1;
			for (int i = 0; i < _cars.size() - 1; i++) {
				if (_cars[i].getPrice() > _cars[i + 1].getPrice()) {
					Car temporary = _cars[i];
					_cars[i] = _cars[i + 1];
					_cars[i + 1] = temporary;
					finished = 0;
				}
			}
		} while (!finished);
	}
	void availableCars() {
		bubbleSort();
		for (int i = 0; i < _cars.size(); i++) {//built in function .size(), that shows the size of the vector
			cout << "\t\t\t" << i + 1 << ". ";
			_cars[i].Info(); //printing
		}
	}
	Car& getCar(int i) {
		return _cars[i];
	}
};
class Receipt {
	string _receiptNumber;
	Date _today;
	int _days;
	Car _rentedCar; 

public:
	Receipt() {
		_receiptNumber = "------";
		_days = 0;
	}
	Receipt(string receiptNumber, Date today,Car rentedCar, int days) {
		_receiptNumber = receiptNumber;
		_today = today;
		_days = days;
		_rentedCar = rentedCar;
	}
	void setDays(int newDays) {
		_days = newDays;
	}
	void Info() {
		system("cls");
		cout << "\n\n\n\n\t\t\t\tThis is your receipt !\n\n\n\n";
		cout << "\t\t\t\tRN " << _receiptNumber << "\t"; _today.Info();
		cout << "\t\t\t\t"<< _rentedCar.getManMod() << " x" << _days << " days" << endl;
		cout << "\t\t\t\t----------------------------\n";
		cout << "\t\t\t\tTotal price: " << _days * _rentedCar.getPrice() << endl;
	
	}
};

int main() {
	Agency Sija("Sija's Agency for CAR RENT");
	//making a few Car objects, these are the cars we have available for rent
	Car mazda6("Mazda", "6", "Silver", 85);
	Car mercedesCLA("Mercedes", "CLA", "Black", 100);
	Car citroenC3("Citroen", "C5", "Black", 65);
	Car volkswagenPolo("Volkswagen", "Polo", "Dark Blue", 40);
	Car BMW("BMW", "X5", "Blue", 90);

	Sija.addCars(mazda6);
	Sija.addCars(mercedesCLA);
	Sija.addCars(citroenC3);
	Sija.addCars(volkswagenPolo);
	Sija.addCars(BMW);
	//Making a Date object so I can use it in the receipt
	Date today(01, 02, 2019);

	string entrance;
	cout << "\n\n\t\t\t :: WELCOME TO SIJA'S CAR RENTAL ::\n";
	cout << "\n\n\n\n\t\t\tBack\t\t\t\tEnter" << endl;
	cin >> entrance;


	if (entrance == "e" ) 
	{
		system("cls"); //clear the screen
		int pickedCar;
		int day, month, year;
		cout << "\n\n\t\t\t :: WELCOME TO SIJA'S CAR RENTAL ::\n";
		cout << "\n\n\t\t\tThese are our available cars !\n\n\n";
		Sija.availableCars();
		cout << "\t\t\tPick one -> ";
		cin >> pickedCar;

		Receipt receipt;
		switch (pickedCar) {
		case 1: {
			system("cls");
			cout << "\n\n\n\n\n\n\t\t\t\t\You have picked "; Sija.getCar(0).Info(); //printing the info of the first car, because user picked the first one.
			cout << "\t\t\t\t\Please enter the rent days -> ";
			cin >> day;
			receipt = Receipt("MZD123", today,Sija.getCar(0), day); //making a receipt
			break;
		}
		case 2: {
			system("cls");
			cout << "\n\n\n\n\n\n\t\t\t\t\You have picked "; Sija.getCar(1).Info();
			cout << "\t\t\t\t\Please enter the rent days -> ";
			cin >> day;
			receipt = Receipt("MZCLA56", today, Sija.getCar(1),day); //making a receipt
			break;

		}
		case 3: {
			system("cls");
			cout << "\n\n\n\n\n\n\t\t\t\t\You have picked "; Sija.getCar(2).Info();
			cout << "\t\t\t\t\Please enter the rent days -> ";
			cin >> day;
			receipt = Receipt("CTRC516", today, Sija.getCar(2), day); //making a receipt
			break;

		}
		case 4: {
			system("cls");
			cout << "\n\n\n\n\n\n\t\t\t\t\You have picked "; Sija.getCar(3).Info();;
			cout << "\t\t\t\t\Please enter the rent days -> ";
			cin >> day;
			receipt = Receipt("VWPL891", today, Sija.getCar(3), day); //making a receipt
			break;

		}
		case 5: {
			system("cls");
			cout << "\n\n\n\n\n\n\t\t\t\t\You have picked "; Sija.getCar(4).Info();
			cout << "\t\t\t\t\Please enter the rent days -> ";
			cin >> day;
			receipt = Receipt("BWX5756", today, Sija.getCar(4), day); //making a receipt
			break;

		}
		}
		//ending switch
		receipt.Info();

		string changeDays;
		cout << "\n\n\t\t\tDo you want to change the number of days? (Y/N) ->";
		cin >> changeDays;
		
		if (changeDays == "Y") {
			cout << "\t\t\tChange it to -> ";
			cin >> day;
			receipt.setDays(day);
			system("cls");
			receipt.Info();
			cout << "\n\n\t\t\t\tHave a nice day !" << endl;

		}
		else if(changeDays == "N")
			cout << "\n\n\t\t\t\tHave a nice day !" << endl;
		

	}
	else if(entrance =="b"){ 
		return 0;
	}



	system("pause>0");
	return 0;
}