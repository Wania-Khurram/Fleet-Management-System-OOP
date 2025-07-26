#include <iostream>
#include <vector>      // vector is like a growable array — it can add/remove items easily
#include <algorithm>   // for find() — helps us search in vector
using namespace std;

// ---------------- BASE CLASS ----------------
class vehicle {
protected:
    string make, model;
    int year;
    double fuel_level;

public:
    vehicle() {}
    vehicle(string m, string mo, int y, double f) : make(m), model(mo), year(y), fuel_level(f) {}

    virtual void start_engine() = 0;
    virtual void stop_engine() = 0;
    virtual double fuel_efficiency() = 0;

    virtual void refuel(double amount) {
        fuel_level += amount;
        cout << "Added " << amount << " liters. Now fuel is: " << fuel_level << endl;
    }

    virtual void display() = 0;

    virtual ~vehicle() {}  // destructor for deleting object safely
};

// ---------------- CAR CLASS ----------------
class car : public vehicle {
    int num_doors;
    string engine_type;

public:
    car(string m, string mo, int y, double f, int nd, string et)
        : vehicle(m, mo, y, f), num_doors(nd), engine_type(et) {}

    void start_engine() override {
        cout << "Car engine started." << endl;
    }
    void stop_engine() override {
        cout << "Car engine stopped." << endl;
    }
    double fuel_efficiency() override {
        return 25.0; // just a fixed value
    }
    void refuel(double amount) override {
        cout << "Refueling car...\n";
        vehicle::refuel(amount);
    }
    void display() override {
        cout << "\n--- Car ---\nMake: " << make << "\nModel: " << model << "\nYear: " << year
             << "\nFuel: " << fuel_level << "L\nDoors: " << num_doors
             << "\nEngine: " << engine_type << endl;
    }
};

// ---------------- TRUCK CLASS ----------------
class truck : public vehicle {
    double cargo_capacity;
    string engine_type;

public:
    truck(string m, string mo, int y, double f, double cc, string et)
        : vehicle(m, mo, y, f), cargo_capacity(cc), engine_type(et) {}

    void start_engine() override {
        cout << "Truck engine started." << endl;
    }
    void stop_engine() override {
        cout << "Truck engine stopped." << endl;
    }
    double fuel_efficiency() override {
        return 15.0;
    }
    void refuel(double amount) override {
        cout << "Refueling truck...\n";
        vehicle::refuel(amount);
    }
    void display() override {
        cout << "\n--- Truck ---\nMake: " << make << "\nModel: " << model << "\nYear: " << year
             << "\nFuel: " << fuel_level << "L\nCargo: " << cargo_capacity << " tons\nEngine: "
             << engine_type << endl;
    }
};

// ---------------- BIKE CLASS ----------------
class bike : public vehicle {
    string type;
    int engine_capacity;

public:
    bike(string m, string mo, int y, double f, string t, int ec)
        : vehicle(m, mo, y, f), type(t), engine_capacity(ec) {}

    void start_engine() override {
        cout << "Bike engine started." << endl;
    }
    void stop_engine() override {
        cout << "Bike engine stopped." << endl;
    }
    double fuel_efficiency() override {
        return 40.0;
    }
    void refuel(double amount) override {
        cout << "Refueling bike...\n";
        vehicle::refuel(amount);
    }
    void display() override {
        cout << "\n--- Bike ---\nMake: " << make << "\nModel: " << model << "\nYear: " << year
             << "\nFuel: " << fuel_level << "L\nType: " << type
             << "\nEngine CC: " << engine_capacity << endl;
    }
};

// ---------------- ELECTRIC VEHICLE CLASS ----------------
class electricvehicle : public vehicle {
    int battery_capacity;
    double charge_level;

public:
    electricvehicle(string m, string mo, int y, double f, int bc, double cl)
        : vehicle(m, mo, y, f), battery_capacity(bc), charge_level(cl) {}

    void start_engine() override {
        cout << "Electric vehicle started." << endl;
    }
    void stop_engine() override {
        cout << "Electric vehicle stopped." << endl;
    }
    double fuel_efficiency() override {
        return 100.0;
    }
    void refuel(double amount) override {
        cout << "Charging electric vehicle...\n";
        charge_level += amount;
        if (charge_level > battery_capacity)
            charge_level = battery_capacity;
        cout << "Charged to: " << charge_level << " kWh\n";
    }
    void display() override {
        cout << "\n--- Electric Vehicle ---\nMake: " << make << "\nModel: " << model
             << "\nYear: " << year << "\nBattery: " << battery_capacity << " kWh\nCharge: "
             << charge_level << " kWh" << endl;
    }
};

// ---------------- FLEET MANAGER ----------------
class fleet_management_system {
    // This is like a magical array that can grow or shrink
    vector<vehicle*> vehicles;

public:
    // This adds a new vehicle to the fleet (pushes to end of vector)
    void add_vehicle(vehicle* v) {
        vehicles.push_back(v);
    }

    // Removes a vehicle from the vector and deletes its memory
    void remove_vehicle(vehicle* v) {
        auto it = find(vehicles.begin(), vehicles.end(), v); // search vehicle in vector
        if (it != vehicles.end()) {
            delete *it;                 // free memory
            vehicles.erase(it);        // remove from vector
            cout << "Vehicle removed from fleet.\n";
        } else {
            cout << "Vehicle not found.\n";
        }
    }

    void display_fleet() {
        cout << "\n--- Fleet ---" << endl;
        for (auto v : vehicles) {
            v->display(); // show each vehicle
        }
    }

    void start_engine() {
        for (auto v : vehicles)
            v->start_engine();
    }

    void stop_engine() {
        for (auto v : vehicles)
            v->stop_engine();
    }

    void refuel_all(double amount) {
        for (auto v : vehicles)
            v->refuel(amount);
    }

    // Get pointer of a vehicle by its position (index)
    vehicle* get_vehicle(int index) {
        if (index >= 0 && index < vehicles.size())
            return vehicles[index];
        return nullptr;
    }

    // destructor deletes all vehicles when fleet ends
    ~fleet_management_system() {
        for (auto v : vehicles)
            delete v;
        vehicles.clear();  // empty the vector
    }
};

// ---------------- MAIN FUNCTION ----------------
int main() {
    fleet_management_system fms;

    // Add some vehicles to the fleet (dynamic memory used)
    fms.add_vehicle(new car("Honda", "Civic", 2021, 40.0, 4, "Petrol"));
    fms.add_vehicle(new truck("Volvo", "FH16", 2020, 100.0, 20.0, "Diesel"));
    fms.add_vehicle(new bike("Suzuki", "GS150", 2022, 15.0, "Standard", 150));
    fms.add_vehicle(new electricvehicle("Tesla", "Model X", 2023, 0.0, 100, 60.0));

    // Start all engines
    fms.start_engine();

    // Refuel everything
    fms.refuel_all(10.0);

    // Stop all engines
    fms.stop_engine();

    // Display all vehicles
    fms.display_fleet();

    // Remove first vehicle
    vehicle* v = fms.get_vehicle(0);
    if (v)
        fms.remove_vehicle(v);

    // Show remaining vehicles
    fms.display_fleet();
    system("pause"); 
    return 0;
}
