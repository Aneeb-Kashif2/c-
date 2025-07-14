
#include <iostream>
#include <string>
using namespace std;

const int MAX_PRODUCTS = 100;
const int MAX_SALES = 100;

struct Product {
    int id;
    string name;
    float price;
    float discount;
};

struct Sale {
    int id;
    string name;
    int quantity;
    float totalPrice;
};

Product products[MAX_PRODUCTS];
int productCount = 0;

Sale salesLog[MAX_SALES];
int salesCount = 0;

string salesmanPassword = "admin123";
// INITILIZING THE PRODUCTS IN PRODUCT OPTION
void initializeProducts() {
    products[productCount++] = { 1, "Apple", 1.5, 10.0 };
    products[productCount++] = { 2, "Banana", 0.5, 5.0 };
    products[productCount++] = { 3, "Orange", 2.0, 15.0 };
}

// Function to find a product index by ID
int findProductIndex(int id) {
    for (int i = 0; i < productCount; i++) {
        if (products[i].id == id) {
            return i;
        }
    }
    return -1;
}

// Salesman functions
void addProduct() {
    if (productCount >= MAX_PRODUCTS) {
        cout << "Product list is full!" << endl;
        return;
    }
    Product newProduct;
    cout << "Enter product ID: ";
    cin >> newProduct.id;
    cin.ignore();
    cout << "Enter product name: ";
    getline(cin, newProduct.name);
    cout << "Enter product price: ";
    cin >> newProduct.price;
    cout << "Enter product discount (%): ";
    cin >> newProduct.discount;

    products[productCount++] = newProduct;
    cout << "Product added successfully!" << endl;
}

void updateProduct() {
    int id;
    cout << "Enter product ID to update: ";
    cin >> id;
    int index = findProductIndex(id);

    if (index == -1) {
        cout << "Product not found!" << endl;
        return;
    }

    cout << "Updating product: " << products[index].name << endl;
    cout << "Enter new price: ";
    cin >> products[index].price;
    cout << "Enter new discount (%): ";
    cin >> products[index].discount;

    cout << "Product updated successfully!" << endl;
}

void displayProducts() {
    if (productCount == 0) {
        cout << "No products available!" << endl;
        return;
    }
    cout << "ID\tName\t\tPrice\tDiscount (%)" << endl;
    for (int i = 0; i < productCount; i++) {
        cout << products[i].id << "\t" << products[i].name << "\t\t"
            << products[i].price << "\t" << products[i].discount << endl;
    }
}

// Customer functions
void buyProducts() {
    int id, quantity;
    float totalBill = 0;

    cout << "Available products:" << endl;
    displayProducts();

    while (true) {
        cout << "Enter product ID to buy (0 to finish): ";
        cin >> id;
        if (id == 0) break;

        int index = findProductIndex(id);
        if (index == -1) {
            cout << "Product not found!" << endl;
            continue;
        }

        cout << "Enter quantity: ";
        cin >> quantity;
        if (quantity <= 0) {
            cout << "Invalid quantity!" << endl;
            continue;
        }

        float price = products[index].price;
        float discount = (products[index].discount / 100) * price;
        float finalPrice = price - discount;
        totalBill += finalPrice * quantity;

        // Log the sale
        if (salesCount < MAX_SALES) {
            salesLog[salesCount].id = products[index].id;
            salesLog[salesCount].name = products[index].name;
            salesLog[salesCount].quantity = quantity;
            salesLog[salesCount].totalPrice = finalPrice * quantity;
            salesCount++;
        }
        else {
            cout << "Sales log is full! Cannot log more sales." << endl;
        }

        cout << "Added " << quantity << " of " << products[index].name
            << " to cart. Subtotal: " << finalPrice * quantity << endl;
    }

    cout << "Total Bill: " << totalBill << endl;
}

// Function to display sales log
void displaySales() {
    if (salesCount == 0) {
        cout << "No sales recorded yet!" << endl;
        return;
    }
    cout << "Sales Summary:" << endl;
    cout << "ID\tName\t\tQuantity\tTotal Price" << endl;
    for (int i = 0; i < salesCount; i++) {
        cout << salesLog[i].id << "\t" << salesLog[i].name << "\t\t"
            << salesLog[i].quantity << "\t\t" << salesLog[i].totalPrice << endl;
    }
}

// Salesman authentication
bool authenticateSalesman() {
    string password;
    cout << "Enter salesman password: ";
    cin >> password;
    if (password == salesmanPassword) {
        return true;
    }
    else {
        cout << "Incorrect password!" << endl;
        return false;
    }
}

// Main menu
void salesmanMenu() {
    while (true) {
        cout << "\n--- Salesman Menu ---" << endl;
        cout << "1. Add Product" << endl;
        cout << "2. Update Product" << endl;
        cout << "3. Display Products" << endl;
        cout << "4. Display Sales" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            addProduct();
            break;
        case 2:
            updateProduct();
            break;
        case 3:
            displayProducts();
            break;
        case 4:
            displaySales();
            break;
        case 5:
            return;
        default:
            cout << "Invalid choice. Try again!" << endl;
        }
    }
}

void customerMenu() {
    while (true) {
        cout << "\n--- Customer Menu ---" << endl;
        cout << "1. Buy Products" << endl;
        cout << "2. Exit" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            buyProducts();
            break;
        case 2:
            return;
        default:
            cout << "Invalid choice. Try again!" << endl;
        }
    }
}

int main() {
    cout << "  SUPER MARKET BILLING SYSTEM \n";
    initializeProducts();
    while (true) {
        cout << "\n--- Main Menu ---" << endl;
        cout << "1. Salesman" << endl;
        cout << "2. Customer" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            if (authenticateSalesman()) {
                salesmanMenu();
            }
            break;
        case 2:
            customerMenu();
            break;
        case 3:
            cout << "Thank you for using the Supermarket Billing System!" << endl;
            return 0;
        default:
            cout << "Invalid choice. Try again!" << endl;
        }
    }
}



