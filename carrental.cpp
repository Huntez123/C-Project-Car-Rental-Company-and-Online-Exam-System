#include <iostream>
#include <string>

using namespace std;

class Vehicle 
{
protected:
    string make;
    string model;
    int year;

public:
    Vehicle(const string& make, const string& model, int year)
    : make(make), model(model), year(year) {}

    virtual double calculateRentalCost() const = 0;

    string getMake() const 
    { 
        return make; 
    }
    string getModel() const 
    { 
        return model; 
    }
    int getYear() const 
    { 
        return year; 
    }

    virtual ~Vehicle() {}
};

class Car : public Vehicle 
{
private:
    int numDoors;

public:
    Car(const string& make, const string& model, int year, int numDoors)
    : Vehicle(make, model, year), numDoors(numDoors) {}

    double calculateRentalCost() const override 
    {
        return 50.0; 
    }

    int getNumDoors() const 
    { 
        return numDoors; 
    }
};

class SUV : public Vehicle 
{
private:
bool allWheelDrive;

public:
    SUV(const string& make, const string& model, int year, bool allWheelDrive)
    : Vehicle(make, model, year), allWheelDrive(allWheelDrive) {}

    double calculateRentalCost() const override 
    {
        return 70.0; 
    }

    bool hasAllWheelDrive() const 
    { 
        return allWheelDrive; 
    }
};

class Truck : public Vehicle 
{
private:
double cargoCapacity; 

public:
    Truck(const string& make, const string& model, int year, double cargoCapacity)
    : Vehicle(make, model, year), cargoCapacity(cargoCapacity) {}

    double calculateRentalCost() const override 
    {
        return 100.0 + 15.0 * cargoCapacity; 
    }

    double getCargoCapacity() const 
    { 
        return cargoCapacity; 
    }
};

void inputVehicleDetails(string& make, string& model, int& year, string& category) 
{
    cout << "Enter the make of the vehicle: ";
    getline(cin, make);

    cout << "Enter the model of the vehicle: ";
    getline(cin, model);

    cout << "Enter the year of the vehicle: ";
    cin >> year;

    cin.ignore();

    cout << "Enter the category of the vehicle (Car, SUV, or Truck): ";
    getline(cin, category);
}

int main() 
{
    string make, model, category;
    int year;

    inputVehicleDetails(make, model, year, category);

    Vehicle* vehicle = nullptr;

    if (category == "Car")
    {
        int numDoors;
        cout << "Enter the number of doors: ";
        cin >> numDoors;
        cin.ignore();
        vehicle = new Car(make, model, year, numDoors);
    } 
    else if (category == "SUV") 
    {
        bool allWheelDrive;
        cout << "Does the SUV have all-wheel drive? (true/false): ";
        cin >> allWheelDrive;
        cin.ignore();
        vehicle = new SUV(make, model, year, allWheelDrive);
    } 
    else if (category == "Truck") 
    {
        double cargoCapacity;
        cout << "Enter the cargo capacity of the Truck (in tons): ";
        cin >> cargoCapacity;
        cin.ignore();
        vehicle = new Truck(make, model, year, cargoCapacity);
    }

    if (dynamic_cast<Car*>(vehicle)) 
    {
        Car* car = dynamic_cast<Car*>(vehicle);
        cout << "Car: " << car->getMake() << " " << car->getModel() << " " << car->getYear() << endl;
        cout << "Number of doors: " << car->getNumDoors() << endl;
        cout << "Rental Cost: $" << car->calculateRentalCost() << endl;
    } 
    else
    {
        cout << "Car: null" << endl;
    }

    if (dynamic_cast<SUV*>(vehicle)) 
    {
        SUV* suv = dynamic_cast<SUV*>(vehicle);
        cout << endl; 
        cout << "SUV: " << suv->getMake() << " " << suv->getModel() << " " << suv->getYear() << endl;
        cout << "All-wheel drive: " << (suv->hasAllWheelDrive() ? "Yes" : "No") << endl;
        cout << "Rental Cost: $" << suv->calculateRentalCost() << endl;
    } 
    else 
    {
        cout << "SUV: null" << endl;
    }

    if (dynamic_cast<Truck*>(vehicle)) 
    {
        Truck* truck = dynamic_cast<Truck*>(vehicle);
        cout << endl; 
        cout << "Truck: " << truck->getMake() << " " << truck->getModel() << " " << truck->getYear() << endl;
        cout << "Cargo capacity: " << truck->getCargoCapacity() << " tons" << endl;
        cout << "Rental Cost: $" << truck->calculateRentalCost() << endl;
    } 
    else 
    {
        cout << "Truck: null" << endl;
    }

    delete vehicle;

    return 0;
}
