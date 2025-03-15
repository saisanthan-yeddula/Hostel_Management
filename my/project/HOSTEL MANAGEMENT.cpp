#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>

using namespace std;

struct Tenant {
    string name;
    int roomNo;
    int rent;
    int payment;
    string complaint;

    Tenant() : name(""), roomNo(0), rent(5500), payment(0), complaint("") {}
    Tenant(string name, int roomNo) : name(name), roomNo(roomNo), rent(5500), payment(0), complaint("") {}
};

class Hostel {
public:
    vector<Tenant> tenants;
    map<int, pair<int, int>> roomAvailability;  // room number -> (total beds, available beds)
    map<string, vector<string>> weeklyMenu;  // {day, [menu items]}

    Hostel() {
        // Initialize room availability for each room type (total beds, available beds)
        roomAvailability[101] = {3, 3};  // 3-sharing room (3 beds)
        roomAvailability[102] = {3, 3};
        roomAvailability[103] = {3, 3};

        roomAvailability[201] = {2, 2};  // 2-sharing room (2 beds)
        roomAvailability[202] = {2, 2};
        roomAvailability[203] = {2, 2};

        roomAvailability[301] = {4, 4};  // 4-sharing room (4 beds)
        roomAvailability[302] = {4, 4};
        roomAvailability[303] = {4, 4};

        roomAvailability[304] = {1, 1};  // 1-sharing room (1 bed)
        roomAvailability[305] = {1, 1};

        // Initialize weekly menu
        weeklyMenu["Monday"] = {"Idly & Sambar", "Dal/Rice", "Roti/Rice/Sabji"};
        weeklyMenu["Tuesday"] = {"Lemon Rice", "Ladies Finger", "Chapati/Alu Curry"};
        weeklyMenu["Wednesday"] = {"Dosa & Chutney", "Dal & Rice", "Egg Rice"};
        weeklyMenu["Thursday"] = {"Upma & Chutney", "Alu Curry & Rice", "Chapathi & Dal"};
        weeklyMenu["Friday"] = {"Tomato Rice", "Brijal Curry & Rice", "Egg Curry & Roti & Rice"};
        weeklyMenu["Saturday"] = {"Puri & Sabji", "Sambar Rice", "Special Veg Biriyani"};
        weeklyMenu["Sunday"] = {"Pongal & Chutney", "Rice & Chicken/Paneer", "Dal & Rice"};
    }

    bool allocateRoom(string name, int roomNo) {
        if (roomAvailability[roomNo].second > 0) {
            tenants.push_back(Tenant(name, roomNo));
            roomAvailability[roomNo].second--;  // Decrease available beds
            saveTenantData();
            return true;
        }
        return false;
    }

    Tenant* tenantLogin(string name, int roomNo) {
        for (auto &tenant : tenants) {
            if (tenant.name == name && tenant.roomNo == roomNo) {
                return &tenant;  // Return pointer to the tenant if login successful
            }
        }
        return nullptr;  // Return nullptr if login fails
    }

    void printRoomAvailability(int sharingType) {
        cout << "\nAvailable Rooms:\n";
        for (auto &room : roomAvailability) {
            if ((sharingType == 3 && room.first >= 101 && room.first <= 103) ||
                (sharingType == 2 && room.first >= 201 && room.first <= 203) ||
                (sharingType == 4 && room.first >= 301 && room.first <= 303) ||
                (sharingType == 1 && (room.first == 304 || room.first == 305))) {
                cout << "Room " << room.first << " (" << roomAvailability[room.first].second
                     << " beds available)\n";
            }
        }
    }

    void printTotalPayments() {
        int totalPayments = 0;
        for (auto &tenant : tenants) {
            totalPayments += tenant.payment;
        }
        cout << "Total Payments: " << totalPayments << endl;
    }

    void printPendingPayments() {
        cout << "\nPending Payments List:\n";
        cout << "Name\tRoom No\tAmount Due\n";
        for (auto &tenant : tenants) {
            int balance = tenant.rent - tenant.payment;
            if (balance > 0) {
                cout << tenant.name << "\t" << tenant.roomNo << "\t" << balance << endl;
            }
        }
    }

    void updateMenu() {
        cout << "\nUpdating Weekly Menu:\n";
        for (auto &day : weeklyMenu) {
            cout << day.first << " Menu: \n";
            for (int i = 0; i < day.second.size(); i++) {
                cout << i + 1 << ". " << day.second[i] << endl;
            }
            cout << "Enter new menu for " << day.first << " (or press Enter to keep current):\n";
            for (int i = 0; i < day.second.size(); i++) {
                string newMenuItem;
                cout << "Enter new item for course " << i + 1 << ": ";
                getline(cin, newMenuItem);
                if (!newMenuItem.empty()) {
                    day.second[i] = newMenuItem;  // Update if the user enters a new item
                }
            }
        }
        saveWeeklyMenu();
    }

    void showWeeklyMenu() {
        cout << "\nWeekly Menu:\n";
        for (auto &day : weeklyMenu) {
            cout << day.first << ": ";
            for (auto &item : day.second) {
                cout << item << ", ";
            }
            cout << endl;
        }
    }

    void saveTenantData() {
        ofstream file("tenants.txt");
        for (auto &tenant : tenants) {
            file << tenant.name << " " << tenant.roomNo << " " << tenant.rent << " " << tenant.payment << " " << tenant.complaint << "\n";
        }
    }

    void loadTenantData() {
        ifstream file("tenants.txt");
        string name;
        int roomNo, rent, payment;
        string complaint;
        while (file >> name >> roomNo >> rent >> payment) {
            getline(file, complaint);  // To read the complaint
            tenants.push_back(Tenant(name, roomNo));
            tenants.back().payment = payment;
            tenants.back().complaint = complaint;
        }
    }

    void saveWeeklyMenu() {
        ofstream file("weekly_menu.txt");
        for (auto &day : weeklyMenu) {
            file << day.first << "\n";
            for (auto &item : day.second) {
                file << item << "\n";
            }
        }
    }

    void loadWeeklyMenu() {
        ifstream file("weekly_menu.txt");
        string day, item;
        while (getline(file, day)) {
            vector<string> items;
            while (getline(file, item) && !item.empty()) {
                items.push_back(item);
            }
            weeklyMenu[day] = items;
        }
    }

    void removeTenant(string name, int roomNo) {
        for (auto it = tenants.begin(); it != tenants.end(); ++it) {
            if (it->name == name && it->roomNo == roomNo) {
                tenants.erase(it);
                roomAvailability[roomNo].second++;  // Increase available beds
                saveTenantData();
                break;
            }
        }
    }

    void viewTenantList() {
        cout << "\nTenant List:\n";
        for (auto &tenant : tenants) {
            cout << "Name: " << tenant.name << ", Room No: " << tenant.roomNo << endl;
        }
    }

    void addComplaint(string name, string complaint) {
        for (auto &tenant : tenants) {
            if (tenant.name == name) {
                tenant.complaint = complaint;
                cout << "Complaint added successfully.\n";
                saveTenantData();
                break;
            }
        }
    }
};

class OwnerLogin {
public:
    bool login() {
        string password;
        cout << "Enter Owner Password: ";
        cin >> password;
        return password == "995986";  // Correct password
    }
};

class TenantLogin {
public:
    bool login(Hostel &hostel, string name, int roomNo) {
        Tenant* tenant = hostel.tenantLogin(name, roomNo);
        if (tenant) {
            cout << "Tenant login successful! Welcome, " << tenant->name << ".\n";
            return true;
        }
        cout << "Invalid credentials. Login failed.\n";
        return false;
    }
};

void ownerMenu(Hostel &hostel) {
    int choice;
    while (true) {
        cout << "\nOwner Menu:\n";
        cout << "1. Allocate Room\n";
        cout << "2. View Payments\n";
        cout << "3. View Pending Payments\n";
        cout << "4. Update Weekly Menu\n";
        cout << "5. View Tenant List\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();  // Clear the input buffer

        switch (choice) {
           case 1: {
    int sharingType;
    cout << "\nSelect the type of sharing:\n";
    cout << " 3-sharing\n";
    cout << " 2-sharing\n";
    cout << " 4-sharing\n";
    cout << " 1-sharing\n";
    cout << "Enter your choice: ";
    cin >> sharingType;

    // Display available rooms based on the selected sharing type
    hostel.printRoomAvailability(sharingType);

    int roomNo;
    cout << "Enter room number to allocate: ";
    cin >> roomNo;

    // Check if room exists and has available beds
    if (hostel.roomAvailability.find(roomNo) != hostel.roomAvailability.end()) {
        if (hostel.roomAvailability[roomNo].second > 0) {
            string name;
            cout << "Enter tenant name: ";
            cin >> name;

            // Allocate room to the tenant
            if (hostel.allocateRoom(name, roomNo)) {
                cout << "Room allocated successfully!\n";
            } else {
                cout << "Room allocation failed. No beds available.\n";
            }
        } else {
            cout << "No available beds in room " << roomNo << ". Please select another room.\n";
        }
    } else {
        cout << "Invalid room number. Please try again.\n";
    }
    break;
}
            case 2:
                hostel.printTotalPayments();
                break;
            case 3:
                hostel.printPendingPayments();
                break;
            case 4:
                hostel.updateMenu();
                break;
            case 5:
                hostel.viewTenantList();
                break;
            case 6:
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}

void tenantMenu(Hostel &hostel) {
    int choice;
    while (true) {
        cout << "\nTenant Menu:\n";
        cout << "1. View Weekly Menu\n";
        cout << "2. Make Complaint\n";
        cout << "3. Pay Rent\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();  // Clear the input buffer

        switch (choice) {
            case 1:
                hostel.showWeeklyMenu();
                break;
            case 2: {
                string name, complaint;
                cout << "Enter your name: ";
                getline(cin, name);
                cout << "Enter your complaint: ";
                getline(cin, complaint);
                hostel.addComplaint(name, complaint);
                break;
            }
            case 3: {
                string name;
                int amount;
                cout << "Enter your name: ";
                getline(cin, name);
                cout << "Enter rent payment amount: ";
                cin >> amount;
                cin.ignore();
                for (auto &tenant : hostel.tenants) {
                    if (tenant.name == name) {
                        tenant.payment += amount;
                        cout << "Payment successful! Total payment: " << tenant.payment << endl;
                        hostel.saveTenantData();
                        break;
                    }
                }
                break;
            }
            case 4:
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}

int main() {
    Hostel hostel;
    OwnerLogin ownerLogin;
    TenantLogin tenantLogin;

    hostel.loadTenantData();
    hostel.loadWeeklyMenu();

    cout << "Welcome to Hostel Management System!\n";

    int choice;
    while (true) {
        cout << "\n1. Owner Login\n";
        cout << "2. Tenant Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                if (ownerLogin.login()) {
                    ownerMenu(hostel);
                } else {
                    cout << "Invalid password.\n";
                }
                break;
            }
            case 2: {
                string name;
                int roomNo;
                cout << "Enter your name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter room number: ";
                cin >> roomNo;
                if (tenantLogin.login(hostel, name, roomNo)) {
                    tenantMenu(hostel);
                }
                break;
            }
            case 3:
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}
