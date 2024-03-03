#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

bool isFileExisting(const std::string& filename) {
    ifstream file(filename);
    return file.good();
}

vector<vector<std::string > > readDataFromCSV(const std::string& filename) {
    vector<vector<string> > data;
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        vector<string> row;
        string cell;
        while (getline(ss, cell, ',')) {
            row.push_back(cell);
        }
        data.push_back(row);
    }
    return data;
}

void writeDataToCSV(const std::string& filename, const vector<vector<std::string> >& data) {
    ofstream file(filename);
    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            file << row[i];
            if (i != row.size() - 1) {
                file << ",";
            }
        }
        file << endl;
    }
}

void removeRowFromCSV(const std::string& filename, int row) {
    vector<vector< string > > data = readDataFromCSV(filename);
    data.erase(data.begin() + row);
    writeDataToCSV(filename, data);
}

void appendRowToCSV(const std::string& filename, const vector<std::string>& newRow) {
    vector<vector<string> > data = readDataFromCSV(filename);
    data.push_back(newRow);
    writeDataToCSV(filename, data);
}

void modifyRowInCSV(const std::string& filename, int row, const vector<std::string>& newRow) {
    vector<vector<string> > data = readDataFromCSV(filename);
    data[row] = newRow;
    writeDataToCSV(filename, data);
}

class CarRental {
private:
    std::string id; // Car ID
    std::string licensePlate;
    std::string brand;
public:
    std::string model;
    std::string color;
    std::string status;
    int isRented;
    int dueDate;
    int damage;
    std::string renterId;
    std::string renterName;
    static std::string file;
    static int vehicleCount;
    static int rentalCostPerDay;
    static int finePerDay;
    static int damageCost;

    CarRental(std::string id, std::string brand, std::string model, std::string color, std::string status, int isRented, int dueDate, int damage, std::string renterId, std::string renterName, std::string licensePlate) {
        this->id = id;
        this->licensePlate = licensePlate;
        this->brand = brand;
        this->model = model;
        this->color = color;
        this->status = status;
        this->isRented = isRented;
        this->dueDate = dueDate;
        this->damage = damage;
        this->renterId = renterId;
        this->renterName = renterName;
    }

    void setVal(std::string id,std::string brand, std::string model, std::string color, std::string status, int isRented, int dueDate, int damage, std::string renterId, std::string renterName, std::string licensePlate) {
        this->id = id;
        this->licensePlate = licensePlate;
        this->brand = brand;
        this->model = model;
        this->color = color;
        this->status = status;
        this->isRented = isRented;
        this->dueDate = dueDate;
        this->damage = damage;
        this->renterId = renterId;
        this->renterName = renterName;
    }

    void addCar();
    void removeCar();
    void updateCar();
};

int CarRental::vehicleCount = 0;
int CarRental::rentalCostPerDay = 1500;
int CarRental::finePerDay = 1500;
int CarRental::damageCost = 300;

void CarRental::addCar() {
    appendRowToCSV(CarRental::file, {this->id, this->licensePlate, this->brand, this->model, this->color, this->status, "0", "0", "0", "0", "0"});
    CarRental::vehicleCount++;
    cout << "Car successfully added." << endl;
    cout << "Car ID: " << id << endl;
    cout << "License plate: " << licensePlate << endl;
}

void CarRental::removeCar() {
    vector<vector<std::string> > data = readDataFromCSV(CarRental::file);
    bool carFound = false;

    for (int i = 0; i < data.size(); ++i) {
        if (data[i][0] == this->id) {
            if (data[i][5] == "0") {
                removeRowFromCSV(CarRental::file, i);
                cout << "Car removed successfully." << endl;
            } else {
                cout << "Car is currently rented and cannot be removed." << endl;
            }
            carFound = true;
            break;
        }
    }

    if (!carFound) {
        cout << "Car with ID " << this->id << " not found." << endl;
    }
}

void CarRental::updateCar() {
    vector<vector<string> > data = readDataFromCSV(CarRental::file);
bool carFound = false;

for (int i = 0; i < data.size(); ++i) {
    if (data[i][0] == this->id) {
        if (data[i][5] == "0") {
            CarRental currentCar(data[i][0], data[i][1], data[i][2], data[i][3], data[i][4], stoi(data[i][5]), stoi(data[i][6]), stoi(data[i][7]), data[i][8], data[i][9], data[i][10]);
            cout << "Enter updated details of the car:" << endl;
            cout << "Color: ";
            cin >> currentCar.color;
            cout << "Status: ";
            cin >> currentCar.status;
            cout << "Rental status (0 for not rented, 1 for rented): ";
            cin >> currentCar.isRented;
            cout << "Due date: ";
            cin >> currentCar.dueDate;
            cout << "Damage: ";
            cin >> currentCar.damage;
            cout << "Renter ID: ";
            cin >> currentCar.renterId;
            cout << "Renter name: ";
            cin >> currentCar.renterName;

            data[i][3] = currentCar.color;
            data[i][4] = currentCar.status;
            data[i][5] = to_string(currentCar.isRented);
            data[i][6] = to_string(currentCar.dueDate);
            data[i][7] = to_string(currentCar.damage);
            data[i][8] = currentCar.renterId;
            data[i][9] = currentCar.renterName;
            data[i][10] = currentCar.licensePlate;
            modifyRowInCSV(CarRental::file, i, data[i]);
            cout << "Car details updated successfully." << endl;
        } else {
            cout << "Car is currently rented and cannot be updated." << endl;
        }
        carFound = true;
        break;
    }
}

if (!carFound) {
    cout << "Car with ID " << this->id << " not found." << endl;
    }
}

class User {
    protected:
        std::string id;
        std::string name;
        std::string password;
};

class Customer : public User {
public:
    int userRecord;
    int userFine;
    int userDiscount;
    int rentedCarsCount;

    static int avgCustomerRecord;
    static int numCustomers;
    static int customerIdCount;
    static string customerFile;

    Customer(std::string id, std::string name, std::string password, int fine, int record, int discount, int rentedCars)
    {
        this->id = id;
        this->name = name;
        this->password = password;
        this->userFine = fine;
        this->userRecord = record;
        this->userDiscount = discount;
        this->rentedCarsCount = rentedCars;
    }

    void showAvailableCars();
    void showRentedCars();
    void rentCar();
    void returnCar();
    void clearFine();
    void viewProfile();
};

class Employee : public User {
public:
    int userRecord;
    int userFine;
    int userDiscount;
    int rentedCarsCount; 

    static int avgEmployeeRecord;
    static int numEmployees;
    static int employeeIdCount;
    static std::string employeeFile;

    Employee(std::string id, std::string name, std::string password, int fine, int record, int discount, int rentedCars) {
        this->id = id;
        this->name = name;
        this->password = password;
        this->userFine = fine;
        this->userRecord = record;
        this->userDiscount = discount;
        this->rentedCarsCount = rentedCars;
    }

    void showAvailableCars();
    void showRentedCars();
    void rentCar();
    void returnCar();
    void clearFine();
    void viewProfile(); 
};

void Customer::showAvailableCars() {
    vector<vector<string>> data = readDataFromCSV(CarRental::file);
    bool carAvailable = false;

    for (auto car : data) {
        if (car[5] == "0") {
            carAvailable = true;
            cout << "Car ID: " << car[0] << "\tCar licensePlate: " << car[10] << "\tCar Model: " << car[1] << "\tCar Model: " << car[2] << "\tCar Color: " << car[3] << "\tCar Status: " << car[4] << endl;
        }
    }

    if (!carAvailable) {
        cout << "No cars available" << endl;
    }
}

void Customer::showRentedCars() {
    vector<vector<string>> data = readDataFromCSV(CarRental::file);
    bool carsRented = false;

    for (auto car : data) {
        if (car[5] == "1" && car[8] == this->id) {
            carsRented = true;
            cout << "Car ID: " << car[0] << "\tCar licensePlate: " << car[10] << "\tCar Model: " << car[1] << "\tCar Model: " << car[2] << "\tCar Color: " << car[3] << "\tCar Status: " << car[4] << "\tDue Date: " << car[6] << endl;
        }
    }

    if (!carsRented) {
        cout << "No cars rented" << endl;
    }
}


std::string calculateDueDate(int days) {
    time_t currentTime = time(0);
    struct tm* currentDate = localtime(&currentTime);
    chrono::system_clock::time_point currentTimePoint = chrono::system_clock::from_time_t(currentTime);
    currentTimePoint += chrono::hours(24 * days);
    time_t dueTime = chrono::system_clock::to_time_t(currentTimePoint);
    struct tm* dueDate = localtime(&dueTime);
    stringstream ss;
    ss << setfill('0') << setw(2) << dueDate->tm_mday << "-" << setw(2) << dueDate->tm_mon + 1 << "-" << setw(4) << dueDate->tm_year + 1900;
    return ss.str();
}

void Customer::rentCar() {
    if (this->userFine > 0) {
        cout << "You have a fine of " << this->userFine << " rupees. You cannot rent a car until you pay the fine" << endl;
        return;
    }

    vector<vector<std::string> > data = readDataFromCSV(CarRental::file);
    if (this->userRecord <= this->rentedCarsCount) {
        cout << "Your record is " << this->userRecord << " and you have presently rented " << this->rentedCarsCount << " cars. So you cannot rent more cars." << endl;
        return;
    }

    int availableCarsCount = 0;
    for (auto car : data) {
        if (car[5] == "0") {
            availableCarsCount++;
        }
    }
    if (availableCarsCount == 0) {
        cout << "No cars available" << endl;
        return;
    }

    cout << "Enter the ID of the car you want to rent: ";
    std::string carId;
    cin >> carId;
    cout << endl;

    int flag = 0;
    for (int i = 0; i < data.size(); ++i) {
        if (data[i][0] == carId) {
            if (data[i][5] == "0") {
                data[i][5] = "1";
                int days = -1;
                cout << "Enter the number of days you want to rent the car: ";
                while (days <= 0) {
                    cin >> days;
                    if (days <= 0) cout << "Invalid input.\nPlease enter a valid number of days: ";
                }
                cout << "You need to pay " << (int)(days * CarRental::rentalCostPerDay * (1 - (this->userDiscount / 100.0))) << " rupees" << endl;
                cout << "Car rented successfully" << endl;
                data[i][6] = calculateDueDate(days);
                data[i][8] = this->id;
                data[i][9] = this->name;
                modifyRowInCSV(CarRental::file, i, data[i]);
                this->rentedCarsCount++;

                vector<vector<std::string> > customerData;
                if (this->id[0] == 'c') customerData = readDataFromCSV(Customer::customerFile);
                else customerData = readDataFromCSV(Employee::employeeFile);

                for (int j = 0; j < customerData.size(); ++j) {
                    if (customerData[j][0] == this->id) {
                        customerData[j][6] = to_string(this->rentedCarsCount);
                        if (this->id[0] == 'c') modifyRowInCSV(Customer::customerFile, j, customerData[j]);
                        else modifyRowInCSV(Employee::employeeFile, j, customerData[j]);
                        break;
                    }
                }

                flag = 1;
                break;
            }
            else {
                cout << "Car is already rented" << endl;
                flag = 1;
                break;
            }
        }
    }
    if (!flag) cout << "Car not found" << endl;
}

int calculateFine(std::string dueDateStr) {
    int day, month, year;
    char separator;
    stringstream ss(dueDateStr);
    ss >> day >> separator >> month >> separator >> year;
    struct tm dueDate = {0, 0, 0, day, month - 1, year - 1900};
    time_t dueTime = mktime(&dueDate);
    time_t currentTime = time(0);
    double seconds = difftime(currentTime, dueTime);
    if (seconds <= 0) return 0;
    else return (int)(ceil(seconds / 86400.0)) * CarRental::finePerDay;
}

void Customer::returnCar() {
    if (this->rentedCarsCount == 0) {
        cout << "You have not rented any cars" << endl;
        return;
    }

    this->showRentedCars();
    cout << "You have the above rented cars" << endl << "Enter the ID of the car you want to return: ";
    std::string carId;
    cin >> carId;
    cout << endl;

    vector<vector<std::string> > data = readDataFromCSV(CarRental::file);
    int flag = 0;
    for (int i = 0; i < data.size(); ++i) {
        if (data[i][0] == carId) {
            if (data[i][5] == "1" && data[i][8] == this->id) {
                double damage;
                cout << "Is there any damage to the car?" << endl << "Enter the amount of damage [0 means no damage; 10 means heavy damage]: ";
                cin >> damage;
                damage = (int)min(10.0, max(0.0, damage));
                int fine = damage * CarRental::damageCost + calculateFine(data[i][6]);

                if (fine > 0) {
                    cout << "You are " << calculateFine(data[i][6]) / CarRental::finePerDay << " days late" << endl;
                    cout << "Your damage fine is " << damage * CarRental::damageCost << " rupees" << endl;
                    cout << "You need to pay a fine of " << fine << " rupees" << endl;
                    cout << "This fine has been added to your account" << endl;
                    this->userRecord--;

                    if (this->id[0] == 'c') Customer::avgCustomerRecord = (Customer::avgCustomerRecord * (Customer::numCustomers - 1) + this->userRecord) / Customer::numCustomers;
                    else Employee::avgEmployeeRecord = (Employee::avgEmployeeRecord * (Employee::numEmployees - 1) + this->userRecord) / Employee::numEmployees;
                }

                this->userFine += fine;
                this->rentedCarsCount--;
                vector<vector<std::string> > customerData;
                if (this->id[0] == 'c') customerData = readDataFromCSV(Customer::customerFile);
                else customerData = readDataFromCSV(Employee::employeeFile);

                for (int j = 0; j < customerData.size(); ++j) {
                    if (customerData[j][0] == this->id) {
                        customerData[j][3] = to_string(this->userFine);
                        customerData[j][4] = to_string(this->userRecord);
                        customerData[j][6] = to_string(this->rentedCarsCount);
                        if (this->id[0] == 'c') modifyRowInCSV(Customer::customerFile, j, customerData[j]);
                        else modifyRowInCSV(Employee::employeeFile, j, customerData[j]);
                        break;
                    }
                }

                cout << "Car returned successfully" << endl;
                data[i][5] = "0";
                data[i][6] = "0";
                data[i][7] = to_string((int)damage);
                data[i][8] = "0";
                data[i][9] = "0";
                modifyRowInCSV(CarRental::file, i, data[i]);
                flag = 1;
                break;
            }
            else {
                cout << "Car is not rented by you" << endl;
                flag = 1;
                break;
            }
        }
    }
    if (!flag) cout << "Car not found" << endl;
}

void Customer::clearFine() {
    if (this->userFine == 0) {
        cout << "You do not have any fine" << endl;
        return;
    }
    cout << "You have a fine of " << this->userFine << " rupees" << endl;
    cout << "Do you want to clear the fine? [y/n]: ";
    char choice;
    cin >> choice;
    if (choice == 'y') {
        this->userFine = 0;
        vector<vector<std::string> > data;
        if (this->id[0] == 'c') data = readDataFromCSV(Customer::customerFile);
        else data = readDataFromCSV(Employee::employeeFile);

        for (int i = 0; i < data.size(); ++i) {
            if (data[i][0] == this->id) {
                data[i][3] = "0";
                if (this->id[0] == 'c') modifyRowInCSV(Customer::customerFile, i, data[i]);
                else modifyRowInCSV(Employee::employeeFile, i, data[i]);
                break;
            }
        }
        cout << "Fine cleared successfully" << endl;
    }
    else if (choice == 'n') {
        cout << "Fine not cleared" << endl;
    }
    else {
        cout << "Invalid choice" << endl;
    }
    return;
}

void Customer::viewProfile() {
    cout << "Your ID: " << this->id << "\tYour Name: " << this->name << "\tYour Password: " << this->password << "\tYour Fine: " << this->userFine << "\tYour Record: " << this->userRecord << "\tYour Number of Rented Cars: " << this->rentedCarsCount << endl;
}

void Employee::showAvailableCars() {
    vector<vector<string> > data = readDataFromCSV(CarRental::file);
    bool availableCarsFound = false;
    for (const auto& car : data) {
        if (car[5] == "0") {
            availableCarsFound = true;
            cout << "Car ID: " << car[0] << "\tCar licensePlate: " << car[10] << "\tCar Model: " << car[1] << "\tCar Model: " << car[2] << "\tCar Color: " << car[3] << "\tCar Status: " << car[4] << endl;
        }
    }
    if (!availableCarsFound) {
        cout << "No cars available" << endl;
    }
}

void Employee::showRentedCars() {
    vector<vector<string> > data = readDataFromCSV(CarRental::file);
    bool carsRented = false;

    for (auto car : data) {
        if (car[5] == "1" && car[8] == this->id) {
            carsRented = true;
            cout << "Car ID: " << car[0] << "\tCar licensePlate: " << car[10] << "\tCar Model: " << car[1] << "\tCar Model: " << car[2] << "\tCar Color: " << car[3] << "\tCar Status: " << car[4] << "\tDue Date: " << car[6] << endl;
        }
    }

    if (!carsRented) {
        cout << "No cars rented" << endl;
    }
}

void Employee::rentCar() {
    if (this->userFine > 0) {
        cout << "You have a fine of " << this->userFine << " rupees. You cannot rent a car until you pay the fine" << endl;
        return;
    }

    vector<vector<std::string> > data = readDataFromCSV(CarRental::file);
    if (this->userRecord <= this->rentedCarsCount) {
        cout << "Your record is " << this->userRecord << " and you have presently rented " << this->rentedCarsCount << " cars. So you cannot rent more cars." << endl;
        return;
    }

    int availableCarsCount = 0;
    for (auto car : data) {
        if (car[5] == "0") {
            availableCarsCount++;
        }
    }
    if (availableCarsCount == 0) {
        cout << "No cars available" << endl;
        return;
    }

    cout << "Enter the ID of the car you want to rent: ";
    std::string carId;
    cin >> carId;
    cout << endl;

    int flag = 0;
    for (int i = 0; i < data.size(); ++i) {
        if (data[i][0] == carId) {
            if (data[i][5] == "0") {
                data[i][5] = "1";
                int days = -1;
                cout << "Enter the number of days you want to rent the car: ";
                while (days <= 0) {
                    cin >> days;
                    if (days <= 0) cout << "Invalid input.\nPlease enter a valid number of days: ";
                }
                cout << "You need to pay " << (int)(days * CarRental::rentalCostPerDay * (1 - (this->userDiscount / 100.0))) << " rupees" << endl;
                cout << "Car rented successfully" << endl;
                data[i][6] = calculateDueDate(days);
                data[i][8] = this->id;
                data[i][9] = this->name;
                modifyRowInCSV(CarRental::file, i, data[i]);
                this->rentedCarsCount++;

                vector<vector<std::string> > customerData;
                if (this->id[0] == 'c') customerData = readDataFromCSV(Customer::customerFile);
                else customerData = readDataFromCSV(Employee::employeeFile);

                for (int j = 0; j < customerData.size(); ++j) {
                    if (customerData[j][0] == this->id) {
                        customerData[j][6] = to_string(this->rentedCarsCount);
                        if (this->id[0] == 'c') modifyRowInCSV(Customer::customerFile, j, customerData[j]);
                        else modifyRowInCSV(Employee::employeeFile, j, customerData[j]);
                        break;
                    }
                }

                flag = 1;
                break;
            }
            else {
                cout << "Car is already rented" << endl;
                flag = 1;
                break;
            }
        }
    }
    if (!flag) cout << "Car not found" << endl;
}

void Employee::returnCar() {
    if (this->rentedCarsCount == 0) {
        cout << "You have not rented any cars" << endl;
        return;
    }

    this->showRentedCars();
    cout << "You have the above rented cars" << endl << "Enter the ID of the car you want to return: ";
    std::string carId;
    cin >> carId;
    cout << endl;

    vector<vector<std::string> > data = readDataFromCSV(CarRental::file);
    int flag = 0;
    for (int i = 0; i < data.size(); ++i) {
        if (data[i][0] == carId) {
            if (data[i][5] == "1" && data[i][8] == this->id) {
                double damage;
                cout << "Is there any damage to the car?" << endl << "Enter the amount of damage [0 means no damage; 10 means heavy damage]: ";
                cin >> damage;
                damage = (int)min(10.0, max(0.0, damage));
                int fine = damage * CarRental::damageCost + calculateFine(data[i][6]);

                if (fine > 0) {
                    cout << "You are " << calculateFine(data[i][6]) / CarRental::finePerDay << " days late" << endl;
                    cout << "Your damage fine is " << damage * CarRental::damageCost << " rupees" << endl;
                    cout << "You need to pay a fine of " << fine << " rupees" << endl;
                    cout << "This fine has been added to your account" << endl;
                    this->userRecord--;

                    if (this->id[0] == 'c') Customer::avgCustomerRecord = (Customer::avgCustomerRecord * (Customer::numCustomers - 1) + this->userRecord) / Customer::numCustomers;
                    else Employee::avgEmployeeRecord = (Employee::avgEmployeeRecord * (Employee::numEmployees - 1) + this->userRecord) / Employee::numEmployees;
                }

                this->userFine += fine;
                this->rentedCarsCount--;
                vector<vector<std::string> > customerData;
                if (this->id[0] == 'c') customerData = readDataFromCSV(Customer::customerFile);
                else customerData = readDataFromCSV(Employee::employeeFile);

                for (int j = 0; j < customerData.size(); ++j) {
                    if (customerData[j][0] == this->id) {
                        customerData[j][3] = to_string(this->userFine);
                        customerData[j][4] = to_string(this->userRecord);
                        customerData[j][6] = to_string(this->rentedCarsCount);
                        if (this->id[0] == 'c') modifyRowInCSV(Customer::customerFile, j, customerData[j]);
                        else modifyRowInCSV(Employee::employeeFile, j, customerData[j]);
                        break;
                    }
                }

                cout << "Car returned successfully" << endl;
                data[i][5] = "0";
                data[i][6] = "0";
                data[i][7] = to_string((int)damage);
                data[i][8] = "0";
                data[i][9] = "0";
                modifyRowInCSV(CarRental::file, i, data[i]);
                flag = 1;
                break;
            }
            else {
                cout << "Car is not rented by you" << endl;
                flag = 1;
                break;
            }
        }
    }
    if (!flag) cout << "Car not found" << endl;
}

void Employee::clearFine() {
    if (this->userFine == 0) {
        cout << "You do not have any fine" << endl;
        return;
    }
    cout << "You have a fine of " << this->userFine << " rupees" << endl;
    cout << "Do you want to clear the fine? [y/n]: ";
    char choice;
    cin >> choice;
    if (choice == 'y') {
        this->userFine = 0;
        vector<vector<std::string> > data;
        if (this->id[0] == 'c') data = readDataFromCSV(Customer::customerFile);
        else data = readDataFromCSV(Employee::employeeFile);

        for (int i = 0; i < data.size(); ++i) {
            if (data[i][0] == this->id) {
                data[i][3] = "0";
                if (this->id[0] == 'c') modifyRowInCSV(Customer::customerFile, i, data[i]);
                else modifyRowInCSV(Employee::employeeFile, i, data[i]);
                break;
            }
        }
        cout << "Fine cleared successfully" << endl;
    }
    else if (choice == 'n') {
        cout << "Fine not cleared" << endl;
    }
    else {
        cout << "Invalid choice" << endl;
    }
    return;
}

void Employee::viewProfile() {
    cout << "Your ID: " << this->id << "\tYour Name: " << this->name << "\tYour Password: " << this->password << "\tYour Fine: " << this->userFine << "\tYour Record: " << this->userRecord << "\tYour Number of Rented Cars: " << this->rentedCarsCount << endl;
} 

class Manager : public User {
    public:

        static int managerIdCount;

        Manager(std::string id, std::string name, std::string password) {
            this->id = id;
            this->name = name;
            this->password = password;
        }

        void displayAllCars();
        void displayAllCustomers();
        void displayAllEmployees();
        void displayAllManagers(vector<vector<std::string> > &managers);

        void addCustomer();
        void removeCustomer();
        void updateCustomer();
        void addEmployee();
        void removeEmployee();
        void updateEmployee();
        void addManager(vector<vector<std::string> > &managers);
        void removeManager(vector<vector<std::string> > &managers);
        void updateManager(vector<vector<std::string> > &managers);
        void searchCustomerById();
        void searchCustomerByName();
        void searchEmployeeById();
        void searchEmployeeByName();
        void searchManagerById(vector<vector<std::string> > &managers);
        void searchManagerByName(vector<vector<std::string> > &managers);
        void searchCarById();
        void searchCarByName();
        void searchCarByModel();
        void searchCarByColor();
        void searchCarByCondition();
        void searchCarByRenterID();
        void searchCarByRenterName();
        void displayRentedCars();
};

int Manager::managerIdCount = 0;


void Manager::displayAllCars() {
    vector<vector<std::string> > data = readDataFromCSV(CarRental::file);
    int flag = 0;
    for (auto i : data)
    {
        flag = 1;
        cout << "Car ID: " << i[0] << "\tCar Name: " << i[1] << "\tCar Model: " << i[2] << "\tCar Color: " << i[3] << "\tCar Condition: " << i[4] << "\tBooking Status: " << i[5] << "\tDue Date: " << i[6] << "\tDamage: " << i[7] << "\tRenter ID: " << i[8] << "\tRenter Name: " << i[9] << endl;
    }
    if (!flag)
        cout << "No cars present" << endl;
    cout << endl;
    return;
}

void Manager::displayAllCustomers() {
    vector<vector<std::string> > data = readDataFromCSV(Customer::customerFile);
    int flag = 0;
    for (auto i : data)
    {
        flag = 1;
        cout << "Customer ID: " << i[0] << "\tCustomer Name: " << i[1] << "\tCustomer Password: " << i[2] << "\tCustomer Fine: " << i[3] << "\tCustomer Record: " << i[4] << endl;
    }
    if (!flag)
        cout << "No customers available" << endl;
    cout << endl
         << endl;
    return;
}

void Manager::displayAllEmployees() {
    vector<vector<std::string> > data = readDataFromCSV(Employee::employeeFile);
    int flag = 0;
    for (auto i : data)
    {
        flag = 1;
        cout << "Employee ID: " << i[0] << "\tEmployee Name: " << i[1] << "\tEmployee Password: " << i[2] << "\tEmployee Fine: " << i[3] << "\tEmployee Record: " << i[4] << endl;
    }
    if (!flag)
        cout << "No employees available" << endl;
    cout << endl;
    return;
}

void Manager::displayAllManagers(vector<vector<std::string> > &managers) {
    int flag = 0;
    for (auto i : managers)
    {
        flag = 1;
        cout << "Manager ID: " << i[0] << "\tManager Name:" << i[1] << "\tManager Password: " << i[2] << endl;
    }
    if (!flag)
        cout << "No managers available" << endl;
    cout << endl;
    return;
}

void Manager::addCustomer() {
    std::cout << "Enter the name of the customer: ";
    std::string name;
    cin >> name;
    std::cout << "Enter the password of the customer: ";
    std::string password;
    cin >> password;
    std::cout << endl;

    std::string id = "c";
    id += to_string(Customer::customerIdCount);
    appendRowToCSV(Customer::customerFile, {id, name, password, "0", to_string(Customer::avgCustomerRecord), "0", "0"});
    std::cout << "Customer added successfully" << endl;
    std::cout << "The customer ID is " << id << endl;
    Customer::numCustomers++;
    Customer::customerIdCount++;
    return;
}

void Manager::removeCustomer() {
    std::cout << "Enter the ID of the customer you want to remove: ";
    std::string customer_id;
    cin >> customer_id;
    std::cout << endl;

    vector<vector<std::string> > data = readDataFromCSV(Customer::customerFile);
    int flg = 0;
    for (int i = 0; i < data.size(); ++i) {
        if (data[i][0] == customer_id) {
            int count_booked_cars = stoi(data[i][6]);
            if (count_booked_cars == 0) {
                removeRowFromCSV(Customer::customerFile, i);
                flg = 1;
                std::cout << "Customer removed successfully" << endl;
                break;
            } else {
                std::cout << "Customer has rented cars. Do you still want to remove them? [y/n]:";
                char choice;
                cin >> choice;
                if (choice == 'y') {
                    removeRowFromCSV(Customer::customerFile, i);
                    std::cout << "Customer removed successfully" << endl;
                    Customer::numCustomers--;
                } else {
                    std::cout << "Customer not removed" << endl;
                }
                flg = 1;
                break;
            }
        }
    }
    if (!flg) std::cout << "Customer not found" << endl;
    return;
}

void Manager::updateCustomer() {
    std::cout << "Enter the ID of the customer you want to update: ";
    std::string customer_id;
    cin >> customer_id;
    std::cout << endl;

    vector<vector<std::string> > data = readDataFromCSV(Customer::customerFile);
    int flg = 0;
    for (int i = 0; i < data.size(); i++) {
        if (data[i][0] == customer_id) {
            std::cout << "Please enter the updated details of the customer" << endl;
            std::cout << "Enter the new name of the customer: ";
            cin >> data[i][1];
            std::cout << "Enter the new password of the customer: ";
            cin >> data[i][2];
            std::cout << "Enter the updated fine of the customer: ";
            cin >> data[i][3];
            std::cout << "Enter the updated record of the customer: ";
            cin >> data[i][4];
            std::cout << "Enter the updated number of cars rented by the customer: ";
            cin >> data[i][6];

            modifyRowInCSV(Customer::customerFile, i, data[i]);
            flg = 1;
            std::cout << "Customer updated successfully" << endl;
            break;
        }
    }
    if (!flg) std::cout << "Customer not found" << endl;
    return;
}

void Manager::addEmployee() {
    std::cout << "Enter the name of the employee: ";
    std::string name;
    cin >> name;
    std::cout << "Enter the password of the employee: ";
    std::string password;
    cin >> password;
    std::cout << endl;

    std::string id = "e";
    id += to_string(Employee::employeeIdCount);
    appendRowToCSV(Employee::employeeFile, {id, name, password, "0", to_string(Employee::avgEmployeeRecord), "15", "0"});
    std::cout << "Employee added successfully" << endl;
    std::cout << "The employee ID is " << id << endl;
    Employee::numEmployees++;
    Employee::employeeIdCount++;
    return;
}

void Manager::removeEmployee() {
    std::cout << "Enter the ID of the employee you want to remove: ";
    std::string employee_id;
    cin >> employee_id;
    std::cout << endl;

    vector<vector<std::string> > data = readDataFromCSV(Employee::employeeFile);
    int flag = 0;
    for (int i = 0; i < data.size(); ++i) {
        if (data[i][0] == employee_id) {
            int booked_cars = stoi(data[i][6]);
            if (booked_cars == 0) {
                removeRowFromCSV(Employee::employeeFile, i);
                flag = 1;
                std::cout << "Employee removed successfully" << endl;
                break;
            } else {
                std::cout << "Employee has rented cars. Do you still want to remove them? [y/n]:";
                char choice;
                cin >> choice;
                if (choice == 'y') {
                    removeRowFromCSV(Employee::employeeFile, i);
                    std::cout << "Employee removed successfully" << endl;
                    Employee::numEmployees--;
                } else {
                    std::cout << "Employee not removed" << endl;
                }
                flag = 1;
                break;
            }
        }
    }
    if (!flag) std::cout << "Employee not found" << endl;
    return;
}

void Manager::updateEmployee() {
    std::cout << "Enter the ID of the employee you want to update: ";
    std::string employee_id;
    cin >> employee_id;
    std::cout << endl;

    vector<vector<std::string> > data = readDataFromCSV(Employee::employeeFile);
    int flag = 0;
    for (int i = 0; i < data.size(); ++i) {
        if (data[i][0] == employee_id) {
            std::cout << "Please enter the updated details of the employee" << endl;
            std::cout << "Enter the new name of the employee: ";
            cin >> data[i][1];
            std::cout << "Enter the new password of the employee: ";
            cin >> data[i][2];
            std::cout << "Enter the updated fine of the employee: ";
            cin >> data[i][3];
            std::cout << "Enter the updated record of the employee: ";
            cin >> data[i][4];
            std::cout << "Enter the updated number of cars rented by the employee: ";
            cin >> data[i][6];

            modifyRowInCSV(Employee::employeeFile, i, data[i]);
            flag = 1;
            std::cout << "Employee updated successfully" << endl;
            break;
        }
    }
    if (!flag) std::cout << "Employee not found" << endl;
    return;
}

void Manager::addManager(vector<vector<std::string> > &managers) {
    std::cout << "Enter the name of the manager: ";
    std::string name;
    cin >> name;
    std::cout << "Enter the password of the manager: ";
    std::string password;
    cin >> password;
    std::cout << endl;

    std::string id = "m";
    id += to_string(Manager::managerIdCount);
    managers.push_back({id, name, password});
    std::cout << "Manager added successfully with manager ID " << id << endl;
    Manager::managerIdCount++;
    return;
}

void Manager::removeManager(vector<vector<std::string> > &managers) {
    std::cout << "Enter the ID of the manager you want to remove: ";
    std::string manager_id;
    cin >> manager_id;
    std::cout << endl;

    if (this->id == manager_id) {
        std::cout << "You cannot remove yourself" << endl;
        return;
    }

    int flag = 0;
    for (int i = 0; i < managers.size(); ++i) {
        if (managers[i][0] == manager_id) {
            managers.erase(managers.begin() + i);
            flag = 1;
            std::cout << "Manager removed successfully" << endl;
            break;
        }
    }
    if (!flag) std::cout << "Manager not found" << endl;
    return;
}

void Manager::updateManager(vector<vector<std::string> > &managers) {
    std::cout << "Enter the ID of the manager you want to update: ";
    std::string manager_id;
    cin >> manager_id;
    std::cout << endl;

    int flag = 0;
    for (int i = 0; i < managers.size(); ++i) {
        if (managers[i][0] == manager_id) {
            std::cout << "Please enter the updated details of the manager" << endl;
            std::cout << "Enter the name of the manager: ";
            std::string name;
            cin >> name;
            std::cout << "Enter the password of the manager: ";
            std::string password;
            cin >> password;
            std::cout << endl;

            managers[i][1] = name;
            managers[i][2] = password;
            flag = 1;
            std::cout << "Manager updated successfully" << endl;
            break;
        }
    }
    if (!flag) std::cout << "Manager not found" << endl;
    return;
}

void Manager::searchCustomerById() {
    std::cout << "Enter the ID of the customer you want to search: ";
    std::string customer_id;
    cin >> customer_id;
    std::cout << endl;

    vector<vector<std::string> > data = readDataFromCSV(Customer::customerFile);
    int flag = 0;
    for (auto i : data) {
        if (i[0] == customer_id) {
            flag = 1;
            std::cout << "Customer ID: " << i[0] << "\tCustomer Name: " << i[1] << "\tCustomer Password: " << i[2] << "\tCustomer Fine: " << i[3] << "\tCustomer Record: " << i[4] << "\tNumber of rented cars: " << i[6] << endl;
            break;
        }
    }
    if (!flag) std::cout << "Customer not found" << endl;
    return;
}

void Manager::searchCustomerByName() {
    std::cout << "Enter the name of the customer you want to search: ";
    std::string customer_name;
    cin >> customer_name;
    std::cout << endl;

    vector<vector<std::string> > data = readDataFromCSV(Customer::customerFile);
    int flag = 0;
    for (auto i : data) {
        if (i[1] == customer_name) {
            flag = 1;
            std::cout << "Customer ID: " << i[0] << "\tCustomer Name: " << i[1] << "\tCustomer Password: " << i[2] << "\tCustomer Fine: " << i[3] << "\tCustomer Record: " << i[4] << "\tNumber of cars rented: " << i[6] << endl;
        }
    }
    if (!flag) std::cout << "Customer not found" << endl;
    return;
}

void Manager::searchEmployeeById() {
    std::cout << "Enter the ID of the employee you want to search: ";
    std::string employee_id;
    cin >> employee_id;
    std::cout << endl;

    vector<vector<std::string> > data = readDataFromCSV(Employee::employeeFile);
    int flag = 0;
    for (auto i : data) {
        if (i[0] == employee_id) {
            flag = 1;
            std::cout << "Employee ID: " << i[0] << "\tEmployee Name: " << i[1] << "\tEmployee Password: " << i[2] << "\tEmployee Fine: " << i[3] << "\tEmployee Record: " << i[4] << "\tNumber of cars rented: " << i[6] << endl;
            break;
        }
    }
    if (!flag) std::cout << "Employee not found" << endl;
    return;
}

void Manager::searchEmployeeByName() {
    std::cout << "Enter the name of the employee you want to search: ";
    std::string employee_name;
    cin >> employee_name;
    std::cout << endl;

    vector<vector<std::string> > data = readDataFromCSV(Employee::employeeFile);
    int flag = 0;
    for (auto i : data) {
        if (i[1] == employee_name) {
            flag = 1;
            std::cout << "Employee ID: " << i[0] << "\tEmployee Name: " << i[1] << "\tEmployee Password: " << i[2] << "\tEmployee Fine: " << i[3] << "\tEmployee Record: " << i[4] << "\tNumber of cars rented: " << i[6] << endl;
        }
    }
    if (!flag) std::cout << "Employee not found" << endl;
    return;
}

void Manager::searchManagerById(vector<vector<std::string> > &managers) {
    std::cout << "Enter the ID of the manager you want to search: ";
    std::string manager_id;
    cin >> manager_id;
    std::cout << endl;

    int flag = 0;
    for (auto i : managers) {
        if (i[0] == manager_id) {
            flag = 1;
            std::cout << "Manager ID: " << i[0] << "\tManager Name: " << i[1] << "\tManager Password: " << i[2] << endl;
            break;
        }
    }
    if (!flag) std::cout << "Manager not found" << endl;
    return;
}

void Manager::searchManagerByName(vector<vector<std::string> > &managers) {
    std::cout << "Enter the name of the manager you want to search: ";
    std::string manager_name;
    cin >> manager_name;
    std::cout << endl;

    int flag = 0;
    for (auto i : managers) {
        if (i[1] == manager_name) {
            flag = 1;
            std::cout << "Manager ID: " << i[0] << "\tManager Name: " << i[1] << "\tManager Password: " << i[2] << endl;
        }
    }
    if (!flag) std::cout << "Manager not found" << endl;
    return;
}

void Manager::searchCarById() {
    std::cout << "Enter the ID of the car you want to search: ";
    std::string car_id;
    cin >> car_id;
    std::cout << endl;

    vector<vector<std::string> > data = readDataFromCSV(CarRental::file);
    int flag = 0;
    for (auto i : data) {
        if (i[0] == car_id) {
            flag = 1;
            std::cout << "Car ID: " << i[0] << "\tCar Name: " << i[1] << "\tCar Model: " << i[2] << "\tCar Color: " << i[3] << "\tCar Condition: " << i[4] << "\tBooking Status: " << i[5] << "\tDue Date: " << i[6] << "\tDamage: " << i[7] << "\tRenter ID: " << i[8] << "\tRenter Name: " << i[9] << endl;
            break;
        }
    }
    if (!flag) std::cout << "Car not found" << endl;
    return;
}

void Manager::searchCarByName() {
    std::cout << "Enter the name of the car you want to search: ";
    std::string car_name;
    cin >> car_name;
    std::cout << endl;

    vector<vector<std::string> > data = readDataFromCSV(CarRental::file);
    int flag = 0;
    for (auto i : data) {
        if (i[1] == car_name) {
            flag = 1;
            std::cout << "Car ID: " << i[0] << "\tCar Name: " << i[1] << "\tCar Model: " << i[2] << "\tCar Color: " << i[3] << "\tCar Condition: " << i[4] << "\tBooking Status: " << i[5] << "\tDue Date: " << i[6] << "\tDamage: " << i[7] << "\tRenter ID: " << i[8] << "\tRenter Name: " << i[9] << endl;
        }
    }
    if (!flag) std::cout << "Car not found" << endl;
    return;
}

void Manager::searchCarByModel() {
    std::cout << "Enter the model of the car you want to search: ";
    std::string car_model;
    cin >> car_model;
    std::cout << endl;

    vector<vector<std::string> > data = readDataFromCSV(CarRental::file);
    int flag = 0;
    for (auto i : data) {
        if (i[2] == car_model) {
            flag = 1;
            std::cout << "Car ID: " << i[0] << "\tCar Name: " << i[1] << "\tCar Model: " << i[2] << "\tCar Color: " << i[3] << "\tCar Condition: " << i[4] << "\tBooking Status: " << i[5] << "\tDue Date: " << i[6] << "\tDamage: " << i[7] << "\tRenter ID: " << i[8] << "\tRenter Name: " << i[9] << endl;
        }
    }
    if (!flag) std::cout << "Car not found" << endl;
    return;
}

void Manager::searchCarByColor() {
    std::cout << "Enter the color of the car you want to search: ";
    std::string car_color;
    cin >> car_color;
    std::cout << endl;

    vector<vector<std::string> > data = readDataFromCSV(CarRental::file);
    int flag = 0;
    for (auto i : data) {
        if (i[3] == car_color) {
            flag = 1;
            std::cout << "Car ID: " << i[0] << "\tCar Name: " << i[1] << "\tCar Model: " << i[2] << "\tCar Color: " << i[3] << "\tCar Condition: " << i[4] << "\tBooking Status: " << i[5] << "\tDue Date: " << i[6] << "\tDamage: " << i[7] << "\tRenter ID: " << i[8] << "\tRenter Name: " << i[9] << endl;
        }
    }
    if (!flag) std::cout << "Car not found" << endl;
    return;
}

void Manager::searchCarByCondition() {
    std::cout << "Enter the condition of the car you want to search: ";
    std::string car_condition;
    cin >> car_condition;
    std::cout << endl;

    vector<vector<std::string> > data = readDataFromCSV(CarRental::file);
    int flag = 0;
    for (auto i : data) {
        if (i[4] == car_condition) {
            flag = 1;
            std::cout << "Car ID: " << i[0] << "\tCar Name: " << i[1] << "\tCar Model: " << i[2] << "\tCar Color: " << i[3] << "\tCar Condition: " << i[4] << "\tBooking Status: " << i[5] << "\tDue Date: " << i[6] << "\tDamage: " << i[7] << "\tRenter ID: " << i[8] << "\tRenter Name: " << i[9] << endl;
        }
    }
    if (!flag) std::cout << "Car not found" << endl;
    return;
}

void Manager::searchCarByRenterID() {
    std::cout << "Enter the renter ID of the car you want to search: ";
    std::string renter_id;
    cin >> renter_id;
    std::cout << endl;

    vector<vector<std::string> > data = readDataFromCSV(CarRental::file);
    int flag = 0;
    for (auto i : data) {
        if (i[8] == renter_id) {
            flag = 1;
            std::cout << "Car ID: " << i[0] << "\tCar Name: " << i[1] << "\tCar Model: " << i[2] << "\tCar Color: " << i[3] << "\tCar Condition: " << i[4] << "\tBooking Status: " << i[5] << "\tDue Date: " << i[6] << "\tDamage: " << i[7] << "\tRenter ID: " << i[8] << "\tRenter Name: " << i[9] << endl;
        }
    }
    if (!flag) std::cout << "Car not found" << endl;
    return;
}

void Manager::searchCarByRenterName() {
    std::cout << "Enter the renter name of the car you want to search: ";
    std::string renter_name;
    cin >> renter_name;
    std::cout << endl;

    vector<vector<std::string> > data = readDataFromCSV(CarRental::file);
    int flag = 0;
    for (auto i : data) {
        if (i[9] == renter_name) {
            flag = 1;
            std::cout << "Car ID: " << i[0] << "\tCar Name: " << i[1] << "\tCar Model: " << i[2] << "\tCar Color: " << i[3] << "\tCar Condition: " << i[4] << "\tBooking Status: " << i[5] << "\tDue Date: " << i[6] << "\tDamage: " << i[7] << "\tRenter ID: " << i[8] << "\tRenter Name: " << i[9] << endl;
        }
    }
    if (!flag) std::cout << "Car not found" << endl;
    return;
}

void Manager::displayRentedCars() {
    vector<vector<std::string> > data = readDataFromCSV(CarRental::file);
    int flag = 0;
    for (auto i : data) {
        if (i[5] == "1") {
            flag = 1;
            std::cout << "Car ID: " << i[0] << "\tCar Name: " << i[1] << "\tCar Model: " << i[2] << "\tCar Color: " << i[3] << "\tCar Condition: " << i[4] << "\tBooking Status: " << i[5] << "\tDue Date: " << i[6] << "\tDamage: " << i[7] << "\tRenter ID: " << i[8] << "\tRenter Name: " << i[9] << endl;
        }
    }
    if (!flag) std::cout << "No cars are rented" << endl;
    return;
}

void customerLogin() {
    std::string userID, password;
    cout << "Enter your UserID: ";
    cin >> userID;
    cout << "Enter your Password: ";
    cin >> password;
    cout << endl;

    int flag = 0, recordIndex = -1, loginFinish = 0;

    vector<vector<std::string> > customerData = readDataFromCSV(Customer::customerFile);
    for (int i = 0; i < customerData.size(); ++i) {
        if (customerData[i][0] == userID) {
            if (customerData[i][2] == password) {
                recordIndex = i;
                break;
            }
            else {
                cout << "Invalid Password\n";
                flag = 1;
                break;
            }
        }
    }
    if (flag) return;


    if (recordIndex == -1) {
        cout << "UserID not found" << endl;
        return;
    }

    cout << "Hello " << customerData[recordIndex][1] << "!\n";
    Customer currentCustomer(customerData[recordIndex][0], customerData[recordIndex][1], customerData[recordIndex][2], stoi(customerData[recordIndex][3]), stoi(customerData[recordIndex][4]), stoi(customerData[recordIndex][5]), stoi(customerData[recordIndex][6]));

    while (!loginFinish) {
        cout << "What do you want to do?\n1. Show available cars\n2. Show rented cars\n3. Rent a car\n4. Return a car\n5. Show fine\n6. Clear fine\n7. View profile\n8. Logout\n";
        cout << "Enter your choice: ";
        int loginChoice;
        cin >> loginChoice;

        switch (loginChoice) {
            case 1:
                currentCustomer.showAvailableCars();
                break;

            case 2:
                currentCustomer.showRentedCars();
                break;

            case 3:
                currentCustomer.rentCar();
                break;

            case 4:
                currentCustomer.returnCar();
                break;

            case 5:
                cout << "Your fine is " << currentCustomer.userFine << endl;
                break;

            case 6:
                currentCustomer.clearFine();
                break;

            case 7:
                currentCustomer.viewProfile();
                break;

            case 8:
                cout << "You are successfully logged out" << endl;
                loginFinish = 1;
                break;

            default:
                cout << "Invalid choice" << endl << endl;
                break;
        }
    }
}

void employeeLogin() {
    std::string userID, password;
    cout << "Enter your UserID: ";
    cin >> userID;
    cout << "Enter your Password: ";
    cin >> password;
    cout << endl;

    int flag = 0, recordIndex = -1, loginFinish = 0;

    vector<vector<std::string> > employeeData = readDataFromCSV(Employee::employeeFile);
    for (int i = 0; i < employeeData.size(); ++i) {
        if (employeeData[i][0] == userID) {
            if (employeeData[i][2] == password) {
                recordIndex = i;
                break;
            }
            else {
                cout << "Invalid Password" << endl;
                flag = 1;
                break;
            }
        }
    }
    if (flag) return;

    if (recordIndex == -1) {
        cout << "UserID not found" << endl;
        return;
    }

    cout << "Hello " << employeeData[recordIndex][1] << "!\n";
    Customer currentEmployee(employeeData[recordIndex][0], employeeData[recordIndex][1], employeeData[recordIndex][2], stoi(employeeData[recordIndex][3]), stoi(employeeData[recordIndex][4]), stoi(employeeData[recordIndex][5]), stoi(employeeData[recordIndex][6]));
    while (!loginFinish) {
        cout << "What do you want to do?\n1. Show available cars\n2. Show rented cars\n3. Rent a car\n4. Return a car\n5. Show fine\n6. Clear fine\n7. View profile\n8. Logout\n";
        cout << "Enter your choice: ";
        int loginChoice;
        cin >> loginChoice;

        switch (loginChoice) {
            case 1:
                currentEmployee.showAvailableCars(); break;

            case 2:
                currentEmployee.showRentedCars(); break;

            case 3:
                currentEmployee.rentCar(); break;

            case 4:
                currentEmployee.returnCar(); break;

            case 5:
                cout << "Your fine is " << currentEmployee.userFine << endl; break;

            case 6:
                currentEmployee.clearFine(); break;

            case 7:
                currentEmployee.viewProfile(); break;

            case 8:
                cout << "Successfully logged out" << endl;
                loginFinish = 1;
                break;

            default:
                cout << "Invalid choice" << endl << endl;
                break;
        }
    }
    return;
}

void managerLogin(vector<vector<std::string> > &managers) {
    std::string userID, password;
    cout << "Enter your UserID: ";
    cin >> userID;
    cout << "Enter your Password: ";
    cin >> password;
    cout << endl;

    int flag = 0, recordIndex = -1, loginFinish = 0;

    for (int i = 0; i < managers.size(); i++) {
        if (managers[i][0] == userID) {
            if (managers[i][2] == password) {
                recordIndex = i;
                break;
            } else {
                cout << "Invalid Password" << endl;
                flag = 1;
                break;
            }
        }
    }

    if (flag) return;

    if (recordIndex == -1) {
        cout << "UserID not found" << endl << endl;
        return;
    }

    cout << "Hello " << managers[recordIndex][1] << "!\n";
    Manager currentManager(managers[recordIndex][0], managers[recordIndex][1], managers[recordIndex][2]);

    while (!loginFinish) {
        cout << "What do you want to do?\n1. Show all cars\n2. Show all customers\n3. Show all employees\n4. Add a car\n5. Remove a car\n6. Update a car\n7. Add a customer\n8. Remove a customer\n9. Update a customer\n10. Add an employee\n11. Remove an employee\n12. Update an employee\n13. Add a manager\n14. Remove a manager\n15. Update a manager\n16. Search for a customer\n17. Search for an employee\n18. Search for a manager\n19. Search for a car\n20. Show rented cars\n21. Logout\n";
        cout << "Enter your choice: ";
        int loginChoice;
        cin >> loginChoice;
        int searchChoice, goBack = 0, flg;
        std::string licensePlate, brand, model, color, status, carID;
        vector<vector<std::string> > data;
        CarRental currentCar("", "", "", "", "", 0, 0, 0, "", "", "");

        switch (loginChoice) {
            case 1:
                currentManager.displayAllCars();
                break;
            case 2:
                currentManager.displayAllCustomers();
                break;
            case 3:
                currentManager.displayAllEmployees();
                break;
            case 4:
                cout << "Enter the licensePlate of the car: ";
                cin >> licensePlate;
                cout << "Enter the brand of the car: ";
                cin >> brand;
                cout << "Enter the model of the car: ";
                cin >> model;
                cout << "Enter the color of the car: ";
                cin >> color;
                cout << "Enter the condition of the car: ";
                cin >> status;
                cout << endl;

                carID = "car";
                carID += to_string(CarRental::vehicleCount);
                currentCar.setVal(carID, brand, model, color, status, 0, 0, 0, "0", "0", licensePlate);
                currentCar.addCar();
                break;
            case 5:
                cout << "Enter the ID of the car you want to remove: ";
                cin >> carID;
                cout << endl;

                data = readDataFromCSV(CarRental::file);
                flg = 0;
                for (int i = 0; i < data.size(); ++i) {
                    if (data[i][0] == carID) {
                        currentCar.setVal(data[i][0], data[i][1], data[i][2], data[i][3], data[i][4], stoi(data[i][5]), stoi(data[i][6]), stoi(data[i][7]), data[i][8], data[i][9], data[i][10]);
                        currentCar.removeCar();
                        flg = 1;
                        break;
                    }
                }
                if (!flg) cout << "Car not found" << endl;
                break;
            case 6:
                cout << "Enter the ID of the car you want to update: ";
                cin >> carID;
                cout << endl;

                data = readDataFromCSV(CarRental::file);
                flg = 0;
                for (int i = 0; i < data.size(); ++i) {
                    if (data[i][0] == carID) {
                        currentCar.setVal(data[i][0], data[i][1], data[i][2], data[i][3], data[i][4], stoi(data[i][5]), stoi(data[i][6]), stoi(data[i][7]), data[i][8], data[i][9], data[i][10]);
                        currentCar.updateCar();
                        flg = 1;
                        break;
                    }
                }
                if (!flg) cout << "Car not found" << endl;
                break;
            case 7:
                currentManager.addCustomer();
                break;
            case 8:
                currentManager.removeCustomer();
                break;
            case 9:
                currentManager.updateCustomer();
                break;
            case 10:
                currentManager.addEmployee();
                break;
            case 11:
                currentManager.removeEmployee();
                break;
            case 12:
                currentManager.updateEmployee();
                break;
            case 13:
                currentManager.addManager(managers);
                break;
            case 14:
                currentManager.removeManager(managers);
                break;
            case 15:
                currentManager.updateManager(managers);
                break;
            case 16:
                goBack = 0;
                while (!goBack) {
                    cout << "1. Search by customer ID\n2. Search by customer name\n3. Go Back\n";
                    cout << "Enter your choice: ";
                    cin >> searchChoice;
                    switch (searchChoice) {
                        case 1:
                            currentManager.searchCustomerById();
                            break;
                        case 2:
                            currentManager.searchCustomerByName();
                            break;
                        case 3:
                            goBack = 1;
                            break;
                        default:
                            cout << "Invalid choice. Please enter a valid choice" << endl;
                            break;
                    }
                }
                break;
            case 17:
                goBack = 0;
                while (!goBack) {
                    std::cout << "1. Search by employee ID\n2. Search by employee name\n3. Go Back\n";
                    std::cout << "Enter your choice: ";
                    cin >> searchChoice;
                    switch (searchChoice) {
                        case 1:
                            currentManager.searchEmployeeById();
                            break;
                        case 2:
                            currentManager.searchEmployeeByName();
                            break;
                        case 3:
                            goBack = 1;
                            break;
                        default:
                            cout << "Invalid choice. Please enter a valid choice" << endl;
                            break;
                    }
                }
                break;
            case 18:
                goBack = 0;
                while (!goBack) {
                    cout << "1. Search by manager ID\n2. Search by manager name\n3. Go Back\n";
                    cout << "Enter your choice: ";
                    cin >> searchChoice;
                    switch (searchChoice) {
                        case 1:
                            currentManager.searchManagerById(managers);
                            break;
                        case 2:
                            currentManager.searchManagerByName(managers);
                            break;
                        case 3:
                            goBack = 1;
                            break;
                        default:
                            cout << "Invalid choice. Please enter a valid choice" << endl;
                            break;
                    }
                }
                break;
            case 19:
                goBack = 0;
                while (!goBack) {
                    cout << "1. Search by car ID\n2. Search by car name\n3. Search by car model\n4. Search by car color\n5. Search by car condition\n6. Search by renter ID\n7. Search by renter name\n8. Go Back\n";
                    cout << "Enter your choice: ";
                    cin >> searchChoice;
                    switch (searchChoice) {
                        case 1:
                            currentManager.searchCarById(); break;
                        case 2:
                            currentManager.searchCarByName(); break;
                        case 3:
                            currentManager.searchCarByModel(); break;
                        case 4:
                            currentManager.searchCarByColor(); break;
                        case 5:
                            currentManager.searchCarByCondition(); break;
                        case 6:
                            currentManager.searchCarByRenterID(); break;
                        case 7:
                            currentManager.searchCarByRenterName(); break;
                        case 8:
                            goBack = 1; break;
                        default:
                            cout << "Invalid choice. Please enter a valid choice" << endl; break;
                    }
                }
                break;
            case 20:
                currentManager.displayRentedCars();
                break;
            case 21:
                cout << "You are successfully logged out" << endl;
                loginFinish = 1;
                break;
            default:
                cout << "Invalid choice. Please enter a valid choice" << endl << endl;
                break;
        }
    }
    return;
}

void registerNewCustomer() {
    std::string username, password;
    cout << "Enter your desired username: ";
    cin >> username;
    cout << "Enter your desired password: ";
    cin >> password;

    vector<vector<std::string> > data = readDataFromCSV(Customer::customerFile);
    std::string id = "C";
    id += to_string(Customer::customerIdCount);
    appendRowToCSV(Customer::customerFile, {id, username, password, "0", to_string(Customer::avgCustomerRecord), "0", "0"});
    Customer::numCustomers++;
    Customer::customerIdCount++;
    cout << "Congratulations! You have successfully registered as a customer." << endl;
    cout << "Your UserID is: " << id << endl;
    return;
}

void registerNewEmployee() {
    std::string username, password;
    cout << "Enter your desired username: ";
    cin >> username;
    cout << "Enter your desired password: ";
    cin >> password;

    vector<vector<std::string> > data = readDataFromCSV(Employee::employeeFile);
    std::string id = "E";
    id += to_string(Employee::employeeIdCount);
    appendRowToCSV(Employee::employeeFile, {id, username, password, "0", to_string(Employee::avgEmployeeRecord), "15", "0"});
    Employee::numEmployees++;
    Employee::employeeIdCount++;
    cout << "Congratulations! You have successfully registered as an employee." << endl;
    cout << "Your UserID is: " << id << endl;
    return;
}

std::string Customer::customerFile = "customers.csv";
std::string Employee::employeeFile = "employees.csv";
std::string CarRental::file = "cars.csv"; 

int Customer::avgCustomerRecord = 4;
int Customer::numCustomers = 0;
int Customer::customerIdCount = 0;

int Employee::avgEmployeeRecord = 4;
int Employee::numEmployees = 0;
int Employee::employeeIdCount = 0;

int main() {
    if (!isFileExisting(Customer::customerFile)) {
        ofstream file(Customer::customerFile);
    }
    if (!isFileExisting(Employee::employeeFile)) {
        ofstream file(Employee::employeeFile);
    }
    if (!isFileExisting(CarRental::file)) {
        ofstream file(CarRental::file);
    }

    try
    {
        vector<vector<std::string> > init_data = readDataFromCSV(Customer::customerFile);

        if (init_data.size()!=0) Customer::avgCustomerRecord = 0;
        for (int i = 0; i < init_data.size(); i++) {
            std::string id = init_data[i][0];
            for (int j=0;j<id.length()-1;j++) id[j] = id[j+1];
            id.pop_back();
            Customer::customerIdCount = max(Customer::customerIdCount, stoi(id));
            Customer::avgCustomerRecord += stoi(init_data[i][4]);
            Customer::numCustomers++;
        }

        if (Customer::numCustomers != 0)
        {
            Customer::customerIdCount++;
            Customer::avgCustomerRecord /= Customer::numCustomers;
        }

        init_data = readDataFromCSV(Employee::employeeFile);
        if (init_data.size()!=0) Employee::avgEmployeeRecord = 0;
        for (int i = 0; i < init_data.size(); i++) {
            std::string id = init_data[i][0];
            for (int j=0;j<id.length()-1;j++) id[j] = id[j+1];
            id.pop_back();
            Employee::employeeIdCount = max(Employee::employeeIdCount, stoi(id));
            Employee::avgEmployeeRecord += stoi(init_data[i][4]);
            Employee::numEmployees++;
        }
        if (Employee::numEmployees != 0)
        {
            Employee::employeeIdCount++;
            Employee::avgEmployeeRecord /= Employee::numEmployees;
        }

        init_data = readDataFromCSV(CarRental::file);
        for (int i = 0; i < init_data.size(); i++) {
            std::string id = init_data[i][0];
            for (int j=0;j<id.length()-3;j++) id[j] = id[j+3];
            id.pop_back();
            CarRental::vehicleCount = max(CarRental::vehicleCount, stoi(id));
        }
        if (init_data.size()!=0) CarRental::vehicleCount++;
    }
    catch(const std::exception& e)
    {
        // std::cerr
    }

    vector<vector<std::string> > managers;
    managers.push_back({"m0","manager", "123"});
    Manager::managerIdCount++;

    cout<<endl<<"Welcome to Car Rental System"<<endl<<endl;

    int finish = 0;
    int signUpFinish = 0;
    int loginFinish = 0;

    while (!finish)
    {
        cout<<"1. Login\n2. Sign up\n3. Exit\nEnter your choice: ";
        int choice;
        cin>>choice;

        switch (choice)
        {
        case 1: // Login
            loginFinish = 0;
            while (!loginFinish)
            {
                cout<<"1. Login as customer\n2. Login as employee\n3. Login as manager\n4. Return back\n";
                cout<<"Please enter your choice: ";
                int subChoice;
                cin>>subChoice;

                switch (subChoice)
                {
                case 1: // Login as a customer
                    customerLogin();
                    break;

                case 2:
                    employeeLogin();
                    break;

                case 3:
                    managerLogin(managers);
                    break;

                case 4:
                    loginFinish = 1;
                    break;

                default:
                    cout<<"Invalid choice. Re-enter a valid choice\n"<<endl;
                    break;
                }
            }
            break;

        case 2: // Sign up
            signUpFinish = 0;
            while (!signUpFinish)
            {
                cout<<"1. Signup as a customer\n2. Signup as an employee\n3. Go back\n";
                cout<<"Please enter your choice: ";
                int subChoice;
                cin>>subChoice;

                switch (subChoice)
                {
                case 1: // Signup as a customer
                    registerNewCustomer();
                    break;

                case 2:  // Signup as an employee
                    registerNewEmployee();
                    break;

                case 3:
                    signUpFinish = 1;
                    break;

                default:
                    cout<<"Invalid choice. Please enter a valid choice\n";
                    break;
                }
            }

            break;

        case 3:
            finish = 1;
            std::cout<<"Thank you\n";
            break;

        default:
            std::cout<<"Invalid choice. Re-enter a valid choice\n";
            break;
        }
    }
    return 0;
}
