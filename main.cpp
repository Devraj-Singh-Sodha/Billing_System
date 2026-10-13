#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

string filename = "product.txt";
ofstream data_product (filename, ios::app);

class Card{
    public:
    void proceed_card(double amount){

        double value;
        string card_no;
        int pin;
        
        cout << "Enter Card Number: ";
        cin >> card_no;
        cout << "Enter The Amount: ";
        cin >> value;
        
        
        while (amount != value)
        {
            cout << "Amount Is Not Correct "<< endl
                 << "Try Again " << endl;
            cin >> value;
        }
        
        
        cout << "Enter The Pin: " ;
        cin >> pin;
        
        cout << "Payment Was Recieved ...." << endl
             << "Visit Again....."<< endl; 
        
    }
};


class Upi{
    public:

    void proceed_upi(double amount){

        double value;
        string upi_id;
        int pin;
        
        cout << "Enter Upi Id: ";
        cin >> upi_id;
        cout << "Enter The Amount: ";
        cin >> value;
        
        
        while (amount != value)
        {
            cout << "Amount Is Not Correct "<< endl
                 << "Try Again " << endl;
            cin >> value;
        }
        
        
        cout << "Enter The Pin: " ;
        cin >> pin;
        
        cout << "Payment Was Recieved ...." << endl
             << "Visit Again....."<< endl; 
        
    }
};

class Payment : public Upi , Card{
    public:
    double amount;
        void getMethod(double amount){
            int choice;
            double value;
            this->amount = amount;
            cout << "1. CASH: " << endl
                 << "2. UPI:  " << endl
                 << "3. CARD: " << endl;

            cin >> choice;

            if (choice == 1)
            {
                cout << "Enter The amount: ";
                cin >> value;

                 while (amount != value)
                {
                    cout << "Amount Is Not Correct "<< endl
                         << "Try Again " << endl;
                    cin >> value;
                }
        
                cout << "Payment Was Recieved ...." << endl
                    << "Visit Again....."<< endl; 
        
            }

            else if (choice == 2)
            {
                proceed_upi( amount);
            }
            else if (choice == 3)
            {
                proceed_card( amount);
            }
            else{
                cout << "Invalid choice : " << endl;
            }
        }
        

    };
class Product{    
    public:
        string name;
        double price;
        int Id;
        int quantity;
        Product(int Id, string name, double price, int quantity){
            this->Id = Id;
            this->name = name;  
            this->price = price;
            this->quantity = quantity;

            data_product << Id << " | " << name << " | $" << price << endl;
        }
        void display(){
            cout << Id << "    " << name
                << "    $" << price
                << "      " << quantity << endl;
        }
        void update(string name, double price){
            this->name = name;
            this->price = price;
        }

};
class Customer{
    private:
    bool isCustomer = false;
    public:
        string name;
        int Id;
        int age;
        vector<string> cart;
        double total_price;

        void add_customer(){
            string name;
            int age;
            int id;

            cout << "Enter Your Name: ";
            cin >> name;
            cout << "Enter Your Id";
            cin >> id;
            cout << "Enter Your Age: ";
            cin >> age;
            this->name = name;
            this->Id = id;
            this->age = age;
            isCustomer = true;
        }


    };
class Billing{
    private:
        int Id;
        string name;


    public:
        void generate_bill(vector<Product> &Products, bool is_Customer, string name){
            vector<pair<int, int>> arr;
            int quantity;
            int id;
            this->name = name;

            ofstream order("Ordeer.txt");
            if (!is_Customer)
            {
                cout <<"Enter Youir Name: ";
                cin >> name;
            }
            
            while (true)
            {
                int ans;
                cout << "Enter product id : ";
                cin >> ans;
                
                if (ans == 00)
                {
                    break;
                }
                
                else{
                    cout << "Enter Quantity: " ;
                    cin >> quantity;
                    for(auto &it : Products){
                        if (ans == it.Id)
                        {
                            if (quantity > it.quantity)
                            {
                                cout << "We Dont Have This Much Quantity" << endl;
                            }
                            else{
                                it.quantity -= quantity;
                                arr.push_back({ans, quantity});
                            }
                        }
    
                    }
                }
                cout << "For Exit (00)"<<endl;


            }

            double total = 0;

            for (auto item : arr) {
                for (auto& product : Products) {
                    if (item.first == product.Id) {
                        total += product.price * item.second;
                        break;
                    }
                }
            }
            
            if (is_Customer)
            {
                total = total * 0.20;
            }
            
            if (total > 50)
            {
                total = total * 0.70;
            }

            cout << "Your Total Is :" << total << endl;
            cout << "Thank You For Purchasing...." << endl;
            
            order << "Name = " << name << endl;

            for (int i = 0; i < arr.size(); i++)
            {
                order << "Product = " << (i + 1)<< endl;
            }
                  
            order<< "Total Price = " << total;

            Payment payment;
            payment.getMethod(total);
            

        }

};


    int main(){
    vector<Product> Products;
    vector<Customer> Customers;
    int count = 1;

    int choice;
    while (true){
        cout << "_______Dev Billing System_______" << endl;
        cout << "1. Product Manegement :" << endl
             << "2. Customer Manegement :" << endl
             << "3. Purchase Product : " << endl
             << "4. Exit:" << endl;
             
             cin >> choice;
             
        if (choice == 1)
        {
            int choice;
            while (true)
            {
                cout << "_______Product Management_______" << endl;
                cout << "1. Add Product: " << endl
                     << "2. Update Product: " << endl
                     << "3. Delete Prodeuct: " << endl
                     << "4. Display All Product: " << endl
                     << "5. Search Product: " << endl
                     << "6. Back:" << endl;
                cin >> choice;

                if (choice == 1)
                {
                    string name;
                    double price;
                    int quantity;

                    cout << "Enter Product Name ";
                    cin >> name;
                    cout << "Enter Product Price: ";
                    cin >> price;
                    cout << "Enter Product quantity: ";
                    cin >> quantity;

                    Products.push_back(Product(count++, name, price, quantity));
                    cout << endl;
                }
                else if (choice == 2){
                    string name;
                    double price;
                    int id;
                    cout << "Enter Product Id: ";
                    cin >> id;

                    for (auto &it : Products){
                        if (it.Id == id){
                            cout << "Enter Product Name ";
                            cin >> name;
                            cout << "Enter Product Price: ";
                            cin >> price;
                            it.update(name, price);
                            cout << "Updated Successfully...." << endl;
                            break;
                        }
                        else{
                            cout << "Product Not Found:" << endl;
                        }
                    }
                    cout << endl;
                }                
                else if (choice == 3){
                        int id;

                        cout << "Enter Product Id: ";
                        cin >> id;

                        bool found = false;

                        for (auto it = Products.begin(); it != Products.end(); ++it){
                            if (it->Id == id){
                                Products.erase(it);

                                found = true;
                                cout << "Product Deleted Successfully!\n";
                                break;
                            }
                        }
                        cout << endl;

                        if (!found){
                            cout << "Product Not Found!\n";
                        }
                    }
                else if (choice == 5){
                    int id;
                    cout << "Enter Product Id: ";
                    cin >> id;

                    for(auto &it : Products){
                        if (it.Id == id)
                        {
                            cout << it.Id << " | " << it.name
                                 << " | $" << it.price << endl;
                        }
                        else{
                            cout << "Product not Found: " << endl;
                        }
                        
                    }
                    cout << endl;
                }
                else if (choice == 4){
                    cout << "\nID   Name   Price   Quantity" << endl;

                    for (auto &it : Products){
                        it.display();
                    }
                    cout << endl;
                }
                else if (choice == 6)
                {
                    break;
                }
                
            }
        }

        else if (choice == 2)
        {
            while (true)
            {
                int choice;

                cout << "1. Add Customer: " << endl
                     << "2. Search Customer: " << endl
                     << "3. Back:" << endl;
                cin >> choice;

                if (choice == 1)
                {
                    Customer customer;
                    customer.add_customer();
                    Customers.push_back(customer);
                }

                else if (choice == 2)
                {
                    int id;
                    cout << "Enter Product Id: ";
                    cin >> id;

                    for(auto &it : Customers){
                        if (it.Id == id)
                        {
                            cout << "Name : " << it.name
                                 << "Age : " << it.age
                                 << "Id : " << it.Id;
                        }
                        else{
                            cout << "Customer not Found: " << endl;
                        }
                        
                    }
                    cout << endl;
                }
                else if (choice == 3)
                {
                    break;
                }
                          
            }
            
        }
        else if (choice == 3){
            string choice;
            bool is_Customer = false;
            cout << "_______Billing Menu_______" << endl;
            cout << "Are You a Regular Cuctomer(y/n)" << endl;
            cin >> choice;
            string name;
            if (choice == "y")
            {
                int id;
                cout << "Enter Your Customer Id: " ;
                cin >> id;

                for(auto it : Customers){
                    if (it.Id == id)
                    {
                        is_Customer = true;
                        name = it.name;
                        cout << "welcome: " <<it.name<<  endl;
                        for (auto &it : Products){
                            it.display();
                            break;
                    }
                    }
                    
                }
                if (!is_Customer) {
                    cout << "Customer Not Found!" << endl;
                    continue;
                }

                
            }
            else
            {
                cout << "\nID   Name   Price   Quantity" << endl;
                for (auto &it : Products){
                        it.display();
                }
            }

            
            Billing Bill;
            Bill.generate_bill(Products, is_Customer, name);
            
            
        }
        else if (choice == 4){
            break;
        }

    }
}