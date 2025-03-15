# Hostel Management System

This project is a **C++-based Hostel Management System** designed to manage hostel room allocations, tenant details, rent payments, complaints, and weekly menus. It supports both **owner** and **tenant** functionalities.

## Features

### 🏠 Room & Tenant Management
- Allocate rooms based on **sharing types** (1, 2, 3, or 4 sharing).
- Track **room availability** and **tenant details**.
- **Tenant login** to manage rent payments and complaints.

### 💰 Rent & Payments
- Owners can **view total and pending payments**.
- Tenants can **make rent payments**.
- Rent is **fixed at ₹5500** per month.

### 🍽️ Weekly Menu Management
- Owners can **update the weekly menu** for hostel meals.
- Tenants can **view the weekly menu** anytime.

### 📢 Complaint Management
- Tenants can **submit complaints** to the management.
- Complaints are stored and can be viewed later.

### 📋 Data Persistence
- **Tenant data** is stored in `tenants.txt`.
- **Weekly menu** is stored in `weekly_menu.txt`.
- Data is **automatically saved and loaded** on startup.

## User Roles

### 🛠️ Owner Functionalities
- Allocate rooms to new tenants.
- View total and pending rent payments.
- Update and manage the weekly menu.
- View tenant details.
- **Owner Password:** `995986`

### 🏠 Tenant Functionalities
- Log in using **name and room number**.
- View weekly menu.
- Make rent payments.
- File complaints about hostel facilities.

## Installation & Compilation

1. **Compile the program** using g++:
   ```bash
   g++ hostel_management.cpp -o hostel_management
   ```
2. **Run the executable**:
   ```bash
   ./hostel_management
   ```

## Usage

1. **Choose Owner or Tenant login** at startup.
2. Owners can **allocate rooms, manage payments, update menus, and view tenant lists**.
3. Tenants can **view menus, make payments, and file complaints**.
4. Data is automatically **saved and loaded** from files.

## Future Improvements
- **Add authentication system** for tenants.
- **Improve room assignment logic**.
- **Enhance complaint management system** with resolution tracking.

## License
This project is open-source and can be freely modified.

---
👨‍💻 Developed using **C++** | 🏠 Hostel Management | 💰 Payment Tracking | 🍽️ Weekly Menu System

