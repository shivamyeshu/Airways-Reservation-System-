#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>  // Include this for std::find_if

using namespace std;

class Passenger {
public:
    Passenger(const string& name, const string& passportNumber)
        : name(name), passportNumber(passportNumber) {}

    string getName() const { return name; }
    string getPassportNumber() const { return passportNumber; }

private:
    string name;
    string passportNumber;
};

class Flight {
public:
    Flight() : totalSeats(0), availableSeats(0) {}

    Flight(const string& flightNumber, const string& origin, const string& destination, int totalSeats)
        : flightNumber(flightNumber), origin(origin), destination(destination), totalSeats(totalSeats), availableSeats(totalSeats) {}

    string getFlightNumber() const { return flightNumber; }

    bool bookSeat(const Passenger& passenger) {
        if (availableSeats > 0) {
            passengers.push_back(passenger);
            availableSeats--;
            return true;
        } else {
            return false;
        }
    }

    void showFlightInfo() const {
        cout << "Flight Number: " << flightNumber << "\n"
             << "Origin: " << origin << "\n"
             << "Destination: " << destination << "\n"
             << "Total Seats: " << totalSeats << "\n"
             << "Available Seats: " << availableSeats << "\n";
    }

    void showPassengerList() const {
        cout << "Passenger List for Flight " << flightNumber << ":\n";
        for (const auto& passenger : passengers) {
            cout << "Name: " << passenger.getName() << ", Passport Number: " << passenger.getPassportNumber() << "\n";
        }
    }

private:
    string flightNumber;
    string origin;
    string destination;
    int totalSeats;
    int availableSeats;
    vector<Passenger> passengers;
};

class ReservationSystem {
public:
    void addFlight(const Flight& flight) {
        flights[flight.getFlightNumber()] = flight;
    }

    bool makeReservation(const string& flightNumber, const Passenger& passenger) {
        if (flights.find(flightNumber) != flights.end()) {
            return flights[flightNumber].bookSeat(passenger);
        } else {
            cout << "Flight " << flightNumber << " not found.\n";
            return false;
        }
    }

    void showFlightDetails(const string& flightNumber) const {
        if (flights.find(flightNumber) != flights.end()) {
            flights.at(flightNumber).showFlightInfo();
        } else {
            cout << "Flight " << flightNumber << " not found.\n";
        }
    }

    void showPassengerList(const string& flightNumber) const {
        if (flights.find(flightNumber) != flights.end()) {
            flights.at(flightNumber).showPassengerList();
        } else {
            cout << "Flight " << flightNumber << " not found.\n";
        }
    }

    map<string, Flight> getFlights() const { // Added this method to access flights
        return flights;
    }

private:
    map<string, Flight> flights;
};

int main() {
    ReservationSystem system;

    int numFlights;
    cout << "Enter the number of flights: ";
    cin >> numFlights;

    for (int i = 0; i < numFlights; ++i) {
        string flightNumber, origin, destination;
        int totalSeats;
        cout << "Enter details for flight " << i + 1 << " (FlightNumber Origin Destination TotalSeats): ";
        cin >> flightNumber >> origin >> destination >> totalSeats;

        Flight flight(flightNumber, origin, destination, totalSeats);
        system.addFlight(flight);
    }

    int numPassengers;
    cout << "Enter the number of passengers: ";
    cin >> numPassengers;

   vector<Passenger> passengers;
for (int i = 0; i < numPassengers; ++i) {
    string name, passportNumber;  // Add the missing semicolon here
    cout << "Enter details for passenger " << i + 1 << " (Name PassportNumber): ";
    cin >> name >> passportNumber;

    Passenger passenger(name, passportNumber);
    passengers.push_back(passenger);
}

    int numReservations;
    cout << "Enter the number of reservations: ";
    cin >> numReservations;

    for (int i = 0; i < numReservations; ++i) {
        string flightNumber, passengerName;
        cout << "Enter reservation details " << i + 1 << " (FlightNumber PassengerName): ";
        cin >> flightNumber >> passengerName;

        auto it = find_if(passengers.begin(), passengers.end(), [&passengerName](const Passenger& p) {
            return p.getName() == passengerName;
        });

        if (it != passengers.end()) {
            if (system.makeReservation(flightNumber, *it)) {
                cout << "Reservation successful for " << passengerName << " on flight " << flightNumber << "\n";
            } else {
                cout << "Reservation failed for " << passengerName << " on flight " << flightNumber << "\n";
            }
        } else {
            cout << "Passenger " << passengerName << " not found.\n";
        }
    }

    cout << "Showing flight details and passenger lists:\n";

    for (const auto& flight : system.getFlights()) {
        system.showFlightDetails(flight.first);
        system.showPassengerList(flight.first);
    }

    return 0;
}
