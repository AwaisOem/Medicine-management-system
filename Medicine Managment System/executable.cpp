#include<bits/stdc++.h>
using namespace std;
template<typename T>
class Node{
    public:
    T data;
    Node* next;
    Node(T data){
        this->data = data;
        this->next = NULL;
    }
};
/// Data Structure to Implement
template<typename T>
class LinkList{
    Node<T> * head;
    public:
    LinkList(){
        head = NULL;
    }
    void insert(T data){
        Node<T> * temp = new Node(data);
        if(head == NULL){
            head = temp;
        }else{
            Node<T> * temp1 = head;
            while(temp1->next != NULL){
                temp1 = temp1->next;
            }
            temp1->next = temp;
        }
    }
    int size(){
        Node<T> * temp = head;
        int i = 0;
        while(temp != NULL){
            i++;
            temp = temp->next;
        }
        return i;
    }
    void print(){
        Node<T> * temp = head;
        while(temp != NULL){
            cout<<temp->data<<" ";
            temp = temp->next;
        }
        cout<<endl;
    }
    T& operator [](int n){
        Node<T> * temp = head;
        int i = 0;
        while(temp != NULL){
            if(i == n){
                return temp->data;
            }
            i++;
            temp = temp->next;
        }
        cout<<"Index out of bound"<<endl;
        exit(1);
    }
    void erase(int n){
        Node<T> * temp = head;
        int i = 0;
        if(n == 0){
            head = head->next;
            delete temp;
            return;
        }
        while(temp != NULL){
            if(i == n-1){
                Node<T> * temp1 = temp->next;
                temp->next = temp1->next;
                delete temp1;
                return;
            }
            i++;
            temp = temp->next;
        }
    }
};
/// User Classes
class Users;
class User{
    string name , password;
    int age;
    bool isadmin;
    friend class Users;
    public:
    User(string name="", int age=0, string password="" , bool isadmin=false){
        this->name = name;
        this->age = age;
        this->password = password;
        this->isadmin = isadmin;
    }
    void setAdmin(){
        isadmin = true;
    }
    void print(){
        cout<<endl;
        cout<<"Name: "<<name<<endl;
        cout<<"Age: "<<age<<endl;
        if(isadmin)cout<<name<<" is an Admin"<<endl;
        cout<<endl;
    }
    bool isThisUser(string name, string password){
        return (this->name == name && this->password == password);
    }
};
class Users{
    LinkList<User> * users;
    public:
    Users(){
        users = new LinkList<User>();
        ifstream file("users.dat");
        string name, password;
        int age;
        bool isUseradmin;
        while(file>>name>>age>>password>>isUseradmin){
            User * temp = new User(name, age, password , isUseradmin);
            users->insert(*temp);
        }
    }
    bool Login(string name, string password){
        
        for(int i = 0; i < users->size(); i++){
            User  temp = (*users)[i];
            if(temp.isThisUser(name, password)){
                temp.print();
                return true;
            }
        }
        return false;
    }
    bool isAdmin(string name, string password){
        for(int i = 0; i < users->size(); i++){
            User temp = (*users)[i];
            if(temp.isThisUser(name, password)){
                return temp.isadmin;
            }
        }
        return false;
    }
    void setToFile(){
        ofstream file("users.dat");
        for(int i = 0; i < users->size(); i++){
            User temp = (*users)[i];
            file<<temp.name<<" "<<temp.age<<" "<<temp.password<<" "<<temp.isadmin<<endl;
        }   
    }
    bool userExistAlready(string name , string password){
        for(int i = 0; i < users->size(); i++){
            User  temp = (*users)[i];
            if(temp.isThisUser(name, password)){
                return true;
            }
        }
        return false;
    }
    bool SignUp(){
        string name, password , cpassword;
        int age;
        cout<<"Enter User name(no space): ";
        cin>>name;
        cout<<"Enter age: ";
        cin>>age;
        cout<<"Enter password(Choose Strong Password): ";
        cin>>password;
        cout<<"Confirm password: ";
        cin>>cpassword;
        if(password != cpassword){
            cout<<"Password not matched"<<endl;
            return false;
        }
        if(userExistAlready(name , password)){
            cout<<"User Exist Already"<<endl;
            return false;
        }
        User * temp = new User(name, age, password, false);
        users->insert(*temp);
        return true;
    }
    void PrintList(){
        if(users->size()!=0){
            for(int i = 0; i < users->size(); i++){
                User temp = (*users)[i];
                temp.print();
            }
            return;
        }
        cout<<"Nothing to show..."<<endl;
    }
    bool setAdmin(){
        string name, password;
        cout<<"Enter name: ";
        cin>>name;
        cout<<"Enter password: ";
        cin>>password;
        for(int i = 0; i < users->size(); i++){
            if((*users)[i].isThisUser(name, password)){
                (*users)[i].setAdmin();
                return true;
            }
        }
        return false;
    }
    bool DeleteUser(){
        string name, password;
        cout<<"Enter name: ";
        cin>>name;
        cout<<"Enter password: ";
        cin>>password;
        for(int i = 0; i < users->size(); i++){
            User temp = (*users)[i];
            if(temp.isThisUser(name, password)){
                users->erase(i);
                return true;
            }
        }
        return false;
    }
};
/// Users Classes End
/// Date Function
string getDateOfToday(){
    time_t now = time(0);
    tm *ltm = localtime(&now);
    string date = to_string(ltm->tm_mday) + "/" + to_string(1 + ltm->tm_mon) + "/" + to_string(1900 + ltm->tm_year);
    return date;
}
/// Date Function End
/// Sales Functions
void addSales(int quantity , int price , string name , string customerName){
    string date = getDateOfToday();
    ofstream fout("sales.dat", ios::app);
    fout<<name<<" "<<price<<" "<<quantity<<" "<<customerName<<" "<<date<<endl;
    fout.close();
}
void SalesPrint(){
    string name , customerName, date;
    int price , quantity;
    ifstream fin("sales.dat");
    if(!fin.is_open()){
        cout<<"Nothing to show..."<<endl;
        return;
    }
    cout<<setiosflags(ios::left)<<setw(20)<<"Name"<<setw(20)<<"Price"<<setw(20)<<"Quantity"<<setw(20)<<"Customer Name"<<setw(20)<<"Date"<<endl;
    while(fin>>name>>price>>quantity>>customerName>>date)
        cout<<setiosflags(ios::left)<<setw(20)<<name<<setw(20)<<price<<setw(20)<<quantity<<setw(20)<<customerName<<setw(20)<<date<<endl;
    fin.close();
}
/// Sales Functions End
/// Medicine Classes
class Medicines;
class Medicine{
    string name;
    int price , quantity;
    friend class Medicines;
    public:
    Medicine(string name ="", int price =0, int quantity=0){
        this->name = name;
        this->price = price;
        this->quantity = quantity;
    }
    void print(){
        cout<<endl;
        cout<<"Name: "<<name<<endl;
        cout<<"Price: "<<price<<endl;
        cout<<"Quantity: "<<quantity<<endl;
        cout<<endl;
    }
    bool isThisMedicine(string name){
        return (this->name == name);
    }
    void setQuantity(int quantity){
        this->quantity = quantity;
    }
    int getQuantity(){
        return quantity;
    }
    int getPrice(){
        return price;
    }
    void setPrice(int price){
        this->price = price;
    }
    void printInTable(){
        cout<<setiosflags(ios::left)<<setw(20)<<name<<setw(20)<<price<<setw(20)<<quantity<<endl;
    }
};
class Medicines{
    LinkList<Medicine> * medicines;
    public:
    Medicines(){
        medicines = new LinkList<Medicine>();
        ifstream file("medicines.dat");
        string name;
        int price, quantity;
        while(file>>name>>price>>quantity){
            Medicine * temp = new Medicine(name, price, quantity);
            medicines->insert(*temp);
        }
    }
    void PrintList(){
        if(medicines->size()!=0){
            for(int i = 0; i < medicines->size(); i++){
                Medicine temp = (*medicines)[i];
                temp.print();
            }
        }else{
            cout<<"Nothing to show...."<<endl;
        }
    }
    void PrintListInTable(){
        if(medicines->size()!=0){
            cout<<setiosflags(ios::left)<<setw(20)<<"Name"<<setw(20)<<"Price"<<setw(20)<<"Quantity"<<endl;
            for(int i = 0; i < medicines->size(); i++){
                Medicine  temp = (*medicines)[i];
                temp.printInTable();
            }
        }else{
            cout<<"Nothing to show...."<<endl;
        }
    }
    void setToFile(){
        ofstream file("medicines.dat");
        for(int i = 0; i < medicines->size(); i++){
            Medicine temp = (*medicines)[i];
            file<<temp.name<<" "<<temp.price<<" "<<temp.getQuantity()<<endl;
        }   
    }
    bool MedicineAlreadyExist(string name){
        for(int i = 0; i < medicines->size(); i++){
            Medicine temp = (*medicines)[i];
            if(temp.isThisMedicine(name)){
                return true;
            }
        }
        return false;
    }
    bool AddMedicine(){
        string name;
        int price, quantity;
        cout<<"Enter Medicine name: ";
        cin>>name;
        if(MedicineAlreadyExist(name))
        {
            cout<<"Medicine Already Exist"<<endl;
            return false;
        }
        cout<<"Enter price: ";
        cin>>price;
        cout<<"Enter quantity: ";
        cin>>quantity;
        Medicine * temp = new Medicine(name, price, quantity);
        medicines->insert(*temp);
        return true;
    }
    bool DeleteMedicine(){
        string name;
        cout<<"Enter Medicine name: ";
        cin>>name;
        for(int i = 0; i < medicines->size(); i++){
            Medicine temp = (*medicines)[i];
            if(temp.isThisMedicine(name)){
                medicines->erase(i);
                return true;
            }
        }
        return false;
    }
    bool UpdateQuantity(){
        string name;
        cout<<"Enter Medicine name: ";
        cin>>name;
        int flag =-1;
        for(int i = 0; i < medicines->size(); i++){
            Medicine temp = (*medicines)[i];
            if(temp.isThisMedicine(name)){
                flag=i;
                break;
            }
        }
        if(flag!=-1){
            cout<<"Enter New quantity: ";
            int quantity;
            cin>>quantity;
            (*medicines)[flag].setQuantity(quantity);
            return true;
        }else{
            cout<<"Medicine Not Found So"<<endl;
        }
        return false;
    }
    void SearchMedicine(string CustomerName){
        string name;
        cout<<"Enter Medicine name: ";
        cin>>name;
        for(int i = 0; i < medicines->size(); i++){
            Medicine temp = (*medicines)[i];
            if(temp.isThisMedicine(name)){
                temp.print();
                cout<<"Do you wanna Buy this medicine? (y/n): ";
                char ch;
                cin>>ch;
                if(ch == 'y' || ch == 'Y'){
                    cout<<"Enter quantity: ";
                    int quantity;
                    cin>>quantity;
                    if(BuyMedicine(i , quantity , name , CustomerName))
                        cout<<"Medicine Bought SuccessFully"<<endl;
                    else
                        cout<<"Medicine not Bought"<<endl;
                }
                return;
            }
        }
        cout<<"Medicine not found"<<endl;
    }
    bool BuyMedicine(int index, int quantity , string name , string CustomerName){
        Medicine temp = (*medicines)[index];
        if(temp.getQuantity() < quantity || quantity<1){
            cout<<"Not enough quantity"<<endl;
            return false;
        }
        (*medicines)[index].setQuantity(temp.getQuantity() - quantity);
        displayInvoice(quantity, temp.getPrice(), name);
        addSales(quantity, temp.getPrice(), name , CustomerName);
        return true;
    }
    void displayInvoice(int quantity , int price , string name){
        cout<<setiosflags(ios::left)<<setw(20)<<"Name"<<setw(20)<<"Price"<<setw(20)<<"Quantity"<<endl;
        cout<<setiosflags(ios::left)<<setw(20)<<name<<setw(20)<<price<<setw(20)<<quantity<<endl;
        cout<<"Total Price: "<<price * quantity<<endl;
    }
    bool BuyMedicine(string CustomerName){
        string name;
        int flag = -1;
        cout<<"Enter Medicine name: ";
        cin>>name;
         for(int i = 0; i < medicines->size(); i++){
            Medicine temp = (*medicines)[i];
            if(temp.isThisMedicine(name)){
               flag = i;break;
            }
        }
        if(flag==-1){
            cout<<"Medicine Not Found.."<<endl;
            return false;
        }
        cout<<"Enter quantity: ";
        int quantity;
        cin>>quantity;
        Medicine &temp2 = (*medicines)[flag];
        if(temp2.getQuantity() < quantity || quantity<1){

            cout<<"Not enough quantity"<<endl;
            return false;
        }
        temp2.setQuantity(temp2.getQuantity() - quantity);
        displayInvoice(quantity, temp2.getPrice(), name);
        addSales(quantity, temp2.getPrice(), name , CustomerName);
        return true;
    }
    bool UpdatePrice(){
        string name;
        cout<<"Enter Medicine name: ";
        cin>>name;
        int flag = -1;
        for(int i = 0; i < medicines->size(); i++){
            Medicine temp = (*medicines)[i];
            if(temp.isThisMedicine(name)){
                flag = i;
            }
        }
        if(flag!=-1){
            int price;
            cout<<"Enter New price: ";
            cin>>price;
            (*medicines)[flag].setPrice(price);
            return true;
        }else{
            cout<<"Medicine Not Found So"<<endl;
        }
        return false;
    }
};
///---------------------End of Medicnie Classes---------------------
///---------------------Customer Panel---------------------
void CustomerPanel(string name){
    Medicines * medicines = new Medicines();
    char choice;
    while(true){
        system("clear");
        cout<<"Welcome "<<name<<endl;
        cout<<"1. View Medicines"<<endl;
        cout<<"2. Search Medicine"<<endl;
        cout<<"3. Buy Medicine"<<endl;
        cout<<"4. Logout"<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;
        if(choice == '1'){
            medicines->PrintListInTable();
        }else if(choice == '2'){
            medicines->SearchMedicine(name);
            medicines->setToFile();
        }else if(choice == '3'){
            medicines->BuyMedicine(name);
            medicines->setToFile();
        }else if(choice == '4'){
            return;
        }
        cout<<"Press any key to continue...";
        cin.ignore();
        cin.get();
    }
}
///---------------------End of Customer Panel---------------------
///---------------------Admin Panel---------------------
void AdminPanel(Users * u){
    Medicines * medicines = new Medicines();
    char choice;
    while(true){
        system("clear");
        cout<<"1. View Medicines"<<endl;
        cout<<"2. Add Medicine"<<endl;
        cout<<"3. Delete Medicine"<<endl;
        cout<<"4. Update Medicine Quantity"<<endl;
        cout<<"5. Update Medicine Price"<<endl;
        cout<<"6. Show Sales"<<endl;
        cout<<"7. View Users"<<endl;
        cout<<"8. Delete User"<<endl;
        cout<<"9. Make User Admin"<<endl;
        cout<<"0. Save Changes without logout"<<endl;
        cout<<"L. Logout"<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;
        if(choice == '1'){
            medicines->PrintListInTable();
        }else if(choice == '2'){
            if(medicines->AddMedicine()){
                cout<<"Medicine added successfully"<<endl;
                // medicines->setToFile();
            }else{
                cout<<"Medicine not added"<<endl;
            }
        }else if(choice == '3'){
            if(medicines->DeleteMedicine()){
                cout<<"Medicine deleted successfully"<<endl;
                // medicines->setToFile();
            }else{
                cout<<"Medicine not deleted"<<endl;
            }
        }else if(choice == '4'){
            if(medicines->UpdateQuantity()){
                cout<<"Medicine quantity updated successfully"<<endl;
                // medicines->setToFile();
            }else{
                cout<<"Medicine quantity not updated"<<endl;
            }
        }else if(choice == '5'){
            if(medicines->UpdatePrice()){
                cout<<"Medicine price updated successfully"<<endl;
                // medicines->setToFile();
            }else{
                cout<<"Medicine price not updated"<<endl;
            }
        }else if(choice == '6'){
                SalesPrint();
        }else if(choice == '7'){
                u->PrintList();
        }else if(choice == '8'){
            if(u->DeleteUser()){
                cout<<"User deleted successfully"<<endl;
                // u->setToFile();
            }else{
                cout<<"User not deleted"<<endl;
            }
        }else if(choice == '9'){
            if(u->setAdmin()){
                cout<<"User made admin successfully"<<endl;
                // u->setToFile();
            }else{
                cout<<"User not made admin bcz of some error"<<endl;
            }
        }else if(choice == '0'){
            medicines->setToFile();
            u->setToFile();
        }else if(choice == 'l' || choice == 'L'){
            medicines->setToFile();
            u->setToFile();
            break;
        }else{
            cout<<"Invalid choice"<<endl;
        }
        cout<<"Press enter to continue"<<endl;
        cin.ignore();
        cin.get();
    }
}
///---------------------End of Admin Panel---------------------
///---------------------Main---------------------
void Run(){
    Users * users = new Users();
    Medicines * medicines = new Medicines();
    string name, password;
    char choice;
    while(true){
        system("clear");
        cout<<"1. View Medicines"<<endl;
        cout<<"2. Login"<<endl;
        cout<<"3. Sign Up"<<endl;
        cout<<"4. Exit"<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;
        if(choice == '1'){
            medicines->PrintListInTable();
        }else if(choice == '2'){
            cout<<"Enter name: ";
            cin>>name;
            cout<<"Enter password: ";
            cin>>password;
            if(users->Login(name, password)){
                if(users->isAdmin(name, password)){
                    AdminPanel(users);
                }else{
                    CustomerPanel(name);
                }
            }else{
                cout<<"Invalid name or password"<<endl;
            }
        }else if(choice == '3'){
            if(users->SignUp()){
                cout<<"Sign Up Successfull"<<endl;
                users->setToFile();
            }else{
                cout<<"Sign Up Failed"<<endl;
            }
        }else if(choice == '4'){
            break;
        }else{
            cout<<"Invalid choice"<<endl;   
        }
        cout<<"Press Enter to continue..."<<endl;
        cin.ignore();
        cin.get();
    }
}main(){Run();}
///---------------------End of Main---------------------