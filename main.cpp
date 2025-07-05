#include <iostream>
#include <vector>
using namespace std;



class Product{
private:
    string name;
    double price;
    int quantity;

public:
//    Product(){}
    Product(string Pname, double Pprice, int Pquantity ){
        name=Pname;
        price=Pprice;
        quantity=Pquantity;
    };

    string getName(){
        return name;
    }
    double getPrice(){
        return price;
    }
    int getQuantity(){
        return quantity;
    }
    void setQuantity(int qun){
     quantity-=qun;
    }
};


class Shippable{
private:
    double weight;
public:
    Shippable(double Pweight=0): weight(Pweight){};

    double getWeight(){
        return weight;
    }

};

class Expirable{
private:
    string expireDate;
    string currentDate;
public:
    Expirable(string PexpireDate ="", string PcurrentDate=""): expireDate(PexpireDate),  currentDate(PcurrentDate){};

    bool isExpired() {
        return expireDate < currentDate;
    }
};


class FinalProduct : public Product{
private:
    Shippable* ship;
    Expirable* expire;
public:
    FinalProduct(string Pname= "", double Pprice=0, int Pquantity=0, Shippable* Pship= nullptr, Expirable* Pexpire= nullptr):
    Product (Pname,Pprice,Pquantity){
        ship =Pship;
        expire=Pexpire;
    }

    bool isExpired(){
        return (expire != nullptr && expire->isExpired());
    }

    bool isShippable() {
       return ship!= nullptr;
    }
    double getWeight(){
            return ship->getWeight();
    }

};


class Cart{
private:
    vector<pair<FinalProduct*,int>> cartItems; // item and qunatity

public:
    void addItem(FinalProduct* product, int quantity , double currentbalance){
        double totalPrice = quantity * product->getPrice();
        if (totalPrice > currentbalance) {
            cout << "Error, You can't afford that product.\n";
            return;
        }
        if (quantity <= 0) {
            cout << "Quantity must be at least 1.\n";
            return;
        }
        if (quantity > product->getQuantity()) {
            cout << product->getName()<<"isnt available.\n";
            return;
        }
        if ( ((product->isExpired()))){ // handling quantity>0 ,a
           cout<<product->getName()<<"is expired\n";
            return;
        }
        cartItems.push_back({product,quantity});
        product->setQuantity(quantity); // updating the product quantity
        cout<<"Item has being added successfully!\n";
    }

    vector<pair<FinalProduct*,int>> getItems() {
        if (cartItems.empty()) {
            cout << "Your cart is empty.\n";
        }else{
            return cartItems;
        }

    }

};


class Customer{
private:
    string name;
    double balance;
    Cart cart;
public:

    Customer(string Pname="",double Pbalance=0): name(Pname), balance(Pbalance), cart(){
    };
    string getName(){
        return name;
    }
    double getBalance(){
        return balance;
    }
    void setBalance(double bal){
        balance-=bal;
    }
    Cart& getCart(){
        return cart;
    }
};


void shippingService(vector<pair<FinalProduct*,int>> shippingItems ){
    double totalWeight=0;
    cout<<"**     Shipment notice     **\n";
    for(auto& item: shippingItems){
        cout<<item.second<<"x"<<" "<<item.first->getName()<<"     "<<item.first->getWeight()*item.second<<"gram."<<endl;
        totalWeight+=item.first->getWeight()*item.second;
    }
    cout<<"Total package weight "<<totalWeight/1000<<" Kg.\n\n";

}

void checkout(Customer& customer){
    int shippingFee=20;
    double subTotal=0;
    double shipping=0;
    double totalWeight=0;
    double total=0;
    double balance=customer.getBalance();
    vector<pair<FinalProduct*,int>> shippingItems;
    Cart& cart = customer.getCart();
    if (cart.getItems().empty()){
        cout<<"Cart is empty.\n";
    }else{
        for( auto& item: cart.getItems()){

            if (item.first->isShippable()){
                shipping+= shippingFee;
                totalWeight+= item.first->getWeight() *item.second;
                shippingItems.push_back({item.first,item.second});
            }
            subTotal+= item.second * item.first->getPrice();
            total=subTotal+shipping;
            if (total>balance){
                cout<<"Error,your balance is insufficient.\n"
                << "Available: " << customer.getBalance()<< endl;
                return;
            }
        }
        customer.setBalance(total);
        shippingService(shippingItems);
        cout<<"**     Checkout receipt     **\n";
        for(auto& item: cart.getItems()){
            cout<<item.second<<"x"<<" "<<item.first->getName()<<"     $"<<item.first->getPrice()<<endl;
        }
        cout<<"- - - - - - - - - - - - -\n"
              <<"Subtotal"<<"       $"<<subTotal<<endl
              <<"Shipping"<<"       $"<<shipping<<endl
              <<"Amount"<<"         $"<<total<<endl
              <<"Current balance:   $"<<customer.getBalance()<<endl;

    }


}


void showProd(string arr[], int n){
    cout<<"Our Product!\n";
    for (int i = 0; i < n; ++i) {
        cout<<i+1<<"-"<<arr[i]<<endl;
    }
}

int main(){
FinalProduct products[5];
 string prodArr[5];
    for (int i = 0; i < 5; i++) {
        string name;
        double price;
        int quantity;
        double weight;
        string expireDate;
        string currentDate;

    cout<<"Enetr the name price and stock quantity of the product.\n";
        cin>>name>>price>>quantity;
        prodArr[i]=name;

        cout<<"Is that product shippable?(y/n)\n";
        char ans;
        cin>>ans;

        Shippable* ship = nullptr;
        if (ans=='y'){
            cout<<"enter the Weight.\n";
            cin>>weight;
            ship= new Shippable(weight);
        }
        cout<<"Can that product expire?(y/n)\n";
        char ans2;
        cin>>ans2;

        Expirable* expire = nullptr;
        if (ans2=='y'){
            cout<<"Enter the  expire date and the current date\n";
            cin>>expireDate>>currentDate;
            expire= new Expirable(expireDate,currentDate);
        }
         products[i]= FinalProduct(name,price,quantity,ship,expire);
    }


string name;
int balance;
cout<<"Enter you Name!\n";
cin>>name;
cout<<"Enter your Balance.\n";
cin>>balance;
Customer customer= Customer(name, balance);

bool flag= true;
    while (flag){
        showProd(prodArr,5);
        int pNumber, quantity;
        cout << "Enter product number and quantity.\nEnter -1 to checkout.\n";
        cin >> pNumber;
        if (pNumber == -1){
            checkout(customer );
            flag= false;
        }
        cin >> quantity;

        customer.getCart().addItem(&products[pNumber - 1], quantity, customer.getBalance());

    }


    return 0;
}