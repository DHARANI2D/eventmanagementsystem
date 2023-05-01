#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Vendor {
public:
    Vendor(string name, string category) : name(name), category(category) {}
    string getName() const { return name; }
    string getCategory() const { return category; }
private:
    string name;
    string category;
};

class Event {
public:
    Event(string name, string location, string date, double budget) : name(name), location(location), date(date), budget(budget) {}
    string getName() const { return name; }
    string getLocation() const { return location; }
    string getDate() const { return date; }
    double getBudget() const { return budget; }
    void addVendor(Vendor vendor) { vendors.push_back(vendor); }
    void listVendors() const {
        for (const auto& vendor : vendors) {
            cout << vendor.getName() << " (" << vendor.getCategory() << ")" << endl;
        }
    }
private:
    string name;
    string location;
    string date;
    double budget;
    vector<Vendor> vendors;
};

int main() {
    vector<Event> events;

    bool running = true;
    while (running) {
        cout << "Enter a command (add, list, exit): ";
        string command;
        cin >> command;

        if (command == "add") {
            cout << "Enter the event name: ";
            string name;
            cin >> name;

            cout << "Enter the event location: ";
            string location;
            cin >> location;

            cout << "Enter the event date (DD/MM/YYYY): ";
            string date;
            cin >> date;

            cout << "Enter the event budget: ";
            double budget;
            cin >> budget;

            Event event(name, location, date, budget);

            bool addingVendors = true;
            while (addingVendors) {
                cout << "Enter a vendor name or type 'done' to finish adding vendors: ";
                string vendorName;
                cin >> vendorName;

                if (vendorName == "done") {
                    addingVendors = false;
                } else {
                    cout << "Enter the vendor category: ";
                    string vendorCategory;
                    cin >> vendorCategory;

                    Vendor vendor(vendorName, vendorCategory);
                    event.addVendor(vendor);
                }
            }

            events.push_back(event);

            cout << "Event added!" << endl;
        } else if (command == "list") {
            cout << "Events:" << endl;
            for (const auto& event : events) {
                cout << event.getName() << endl;
            }

            cout << "Enter an event name to see the vendors or type 'back' to go back: ";
            string eventName;
            cin >> eventName;

            if (eventName != "back") {
                auto it = find_if(events.begin(), events.end(), [&](const Event& event) {
                    return event.getName() == eventName;
                });

                if (it != events.end()) {
                    cout << "Vendors for " << it->getName() << ":" << endl;
                    it->listVendors();
                } else {
                    cout << "Event not found." << endl;
                }
            }
        } else if (command == "exit") {
            running = false;
        } else {
            cout << "Invalid command." << endl;
        }
    }

    return 0;
}
