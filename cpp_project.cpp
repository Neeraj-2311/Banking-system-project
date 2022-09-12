#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;
const int MAX_VALID_YR = 2022; // max year value
const int MIN_VALID_YR = 1900; // min year value
// function to check validity of name
int validname(string s)
{
    for (int i = 0; i < s.length(); i++)
    {
        if (!isalpha(s[i]))
        {
            return -1;
        }
    }
    return 1;
}
// function to check leap year
bool isLeap(int year)
{
    return (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
}
// function to check valid date
bool isValidDate(int d, int m, int y)
{
    if (y > MAX_VALID_YR || y < MIN_VALID_YR)
        return false;
    if (m < 1 || m > 12)
        return false;
    if (d < 1 || d > 31)
        return false;

    if (m == 2)
    {
        if (isLeap(y))
            return (d <= 29);
        else
            return (d <= 28);
    }
    if (m == 4 || m == 6 || m == 9 || m == 11)
        return (d <= 30);
    return true;
}
// function to check valid password
int validpass(string s)
{
    int len = 0, lower = 0, upper = 0, special = 0, numeric = 0;
    if (s.length() > 7)
        len++;
    for (int i = 0; i < s.length(); i++)
    {
        if (isupper(s[i]))
            upper++;
        if (islower(s[i]))
            lower++;
        if (s[i] == '1' || s[i] == '2' || s[i] == '3' || s[i] == '4' || s[i] == '5' || s[i] == '6' || s[i] == '7' || s[i] == '8' || s[i] == '9' || s[i] == '0')
            numeric++;
        if (s[i] == '!' || s[i] == '@' || s[i] == '#' || s[i] == '$' || s[i] == '%' || s[i] == '&')
            special++;
    }
    if (upper > 0 && lower > 0 && special > 0 && len > 0 && numeric > 0)
        return 1;
    else
        return 0;
}
// function to check valid mobile number
int validnum(string s)
{
    if (s.length() != 10)
        return -1;
    for (int i = 0; i < s.length(); i++)
    {
        if (!isdigit(s[i]))
            return -1;
    }
    return 1;
}
// class "account" declaration
class account
{
private:
    int account_no[10]; 
    string password[10];
    string name[10];
    string mobile[10];   
    int balance[10];     
    int dob[10];         
    int checkacc(int numb, int pos);
    string adminp = "ADMIN@123"; // admin password to login into admin

public:
    void createaccount(int &pos, int &acc); 
    void delete_account(int &pos);          
    void showdata(int pos);                 
    void exportdata(int pos, int acc);      
    void importdata(int pos, int acc);      
    void debit(int pos);                    
    void credit(int pos);                   
    void transfer(int pos);                 
    void login(int pos);                    
    void exporttransaction(int pos);        
    void importtransaction(int pos);
    bool adminlogin(string s)
    {
        if (s == adminp)
            return true;
        return false;
    }
};
int account::checkacc(int numb, int pos)
{
    for (int i = 0; i < pos; i++)
    {
        if (numb == account_no[i])
            return i;
    }
    return -1;
}
void account::createaccount(int &pos, int &acc) // create_account function
{
    string var;
    account_no[pos] = acc;
    cout << "Enter your first name : ";
    cin >> var;
    while (validname(var) != 1)
    {
        cout << "Name is not valid\nEnter a valid Name : ";
        cin >> var;
    }
    char cvar[var.length() + 1];
    strcpy(cvar, var.c_str());
    name[pos] = strlwr(cvar);
    cout << "Create password---------- " << endl;
    cout << "Enter password : ";
    cin >> var;
    while (validpass(var) != 1)
    {
        cout << "password must contain : " << endl;
        cout << "    ~ One lower-case letter" << endl;
        cout << "    ~ One upper-case letter" << endl;
        cout << "    ~ One special character(!, @, #, $, %, &)" << endl;
        cout << "    ~ One numeric value(0-9)" << endl;
        cout << "    ~ password length should be atleast 7" << endl;
        cout << "Enter password : ";
        cin >> var;
    }
    password[pos] = var;
    int dobsample;
    cout << "Enter your DOB (ddmmyyyy) : ";
    cin >> dobsample;
    while (isValidDate(dobsample / 1000000, (dobsample / 10000) % 100, dobsample % 10000) != true)
    {
        cout << "Invalid DOB " << endl;
        cout << "Enter your DOB (ddmmyyyy): ";
        cin >> dobsample;
    }
    dob[pos] = dobsample;
    cout << "Enter your mobile number : ";
    cin >> var;
    while (validnum(var) != 1)
    {
        cout << "Invalid number !" << endl;
        cout << "Enter a valid mobile number : ";
        cin >> var;
    }
    mobile[pos] = var;
    balance[pos] = 0;
    cout << "Account created successfully !" << endl;
    cout<<"Your account are ------ "<<endl;
    cout<<"     Account no       : "<<account_no[pos]<<endl;
    cout<<"     Your name        : "<<name[pos]<<endl;
    cout<<"     Mobile number    : "<<mobile[pos]<<endl;
    cout<<"     Balance (in Rs.) : "<<balance[pos]<<endl;
    cout<<"     DOB (dd/mm/yyyy) : "<<dob[pos]<<endl;
    pos++;
    acc++;
}
void account::delete_account(int &pos) // delete_account function
{
    if (pos == 0)
    {
        cout << "No accounts !!" << endl;
        return;
    }
    int x;
    string pass;
    string decision;
    cout << "Enter account number : ";
    cin >> x;
    int index = checkacc(x, pos);
    if (index != -1)
    {
        cout << "Enter password : ";
        cin >> pass;
        while (true)
        {
            if (pass == password[index])
            {
                cout << "Do you want to delete your account? (y/n) : ";
                cin >> decision;
                if (decision == "y" || decision == "Y")
                {
                    while (index < pos)
                    {
                        account_no[index] = account_no[index + 1];
                        password[index] = password[index + 1];
                        name[index] = name[index + 1];
                        mobile[index] = mobile[index + 1];
                        balance[index] = balance[index + 1];
                        dob[index] = dob[index + 1];
                        index++;
                    }
                    cout << "Account deleted successfully" << endl;
                    pos--;
                    return;
                }
                else if (decision == "n" || decision == "N")
                {
                    cout << "Deletion cancelled !!" << endl;
                    return;
                }
                else
                    cout << "Wrong input" << endl;
            }
            else
            {
                int f;
                cout << "Password is incorrect !!" << endl;
                cout << "Password can be reset only from \"login to your account\" section" << endl;
                ;
                cout << "    ~ press -> 1 : continue to login with password" << endl;
                cout << "    ~ press -> 2 : previous menu" << endl;
                cin >> f;
                if (f == 1)
                {
                    cout << "Enter password : ";
                    cin >> pass;
                }
                else if (f == 2)
                {
                    break;
                }
                else
                {
                    cout << "Wrong input !!" << endl;
                    cout << "Enter password : ";
                    cin >> pass;
                }
            }
        }
    }
    else
    {
        cout << "Account not found !!" << endl;
        return;
    }
}
void account::showdata(int pos) // showdata funtion to show all account's data to admin
{
    int i = 0;
    if (pos == 0)
    {
        cout << "No accounts !" << endl;
    }
    else
    {
        while (i < pos)
        {
            cout << "----------" << i + 1 << "----------" << endl;
            cout << "->  Account number : " << account_no[i] << endl;
            cout << "->  Customer name  : " << name[i] << endl;
            cout << "->  DOB (ddmmyyyy) : " << dob[i] << endl;
            cout << "->  Mobile number  : " << mobile[i] << endl;
            cout << "->  Balance(in INR): " << balance[i] << endl;
            i++;
        }
    }
}
void account::exportdata(int pos, int acc)
{
    fstream obj("database.txt", ios::out);
    obj << pos << " ";
    obj << acc << " " << endl;
    for (int index = 0; index < pos; index++)
    {
        obj << account_no[index] << " ";
        obj << password[index] << " ";
        obj << dob[index] << " ";
        obj << mobile[index] << " ";
        obj << name[index] << " ";
        obj << balance[index] << " ";
        obj << endl;
    }
}
void account::importdata(int pos, int acc)
{
    string pass, naming, mob;
    int date, ac_no, bal;
    fstream file("database.txt");
    file >> pass;
    file >> pass;
    for (int i = 0; i < pos; i++)
    {
        file >> ac_no;
        account_no[i] = ac_no;
        file >> pass;
        password[i] = pass;
        file >> date;
        dob[i] = date;
        file >> mob;
        mobile[i] = mob;
        file >> naming;
        name[i] = naming;
        file >> bal;
        balance[i] = bal;
    }
}
void account::debit(int pos)
{
    if (pos == 0)
    {
        cout << "No accounts !!" << endl;
        cout<<"~ create an account first !"<<endl;
        return;
    }
    int numb;
    string pass;
    cout << "Enter your account number : ";
    cin >> numb;
    int index = checkacc(numb, pos);
    if (index != -1)
    {
        cout << "Enter password : ";
        cin >> pass;
        while (true)
        {
            if (pass == password[index])
            {
                if (balance[index] == 0)
                {
                    cout << "Account balance is 0 !!" << endl;
                    return;
                }
                int value;
                cout << "Enter a valid amount(in Rs) you want to debit from your account : ";
                cin >> value;
                while (true)
                {
                    if (value < 0)
                    {
                        cout << "Debit amount can't be less than 0" << endl;
                        break;
                    }
                    else if (value == 0)
                    {
                        cout << "Debit amount can't be 0." << endl;
                        break;
                    }
                    else if (balance[index] >= value && value != 0)
                    {
                        balance[index] = balance[index] - value;
                        cout << value << " has been Debitted from your account successfully\nupdated balance is " << balance[index] << endl;
                        cout << "Have a nice day :)" << endl;
                        fstream obj("transaction_database.txt", ios::app);
                        time_t tnow;
                        tnow = time(NULL);
                        struct tm t = *localtime(&tnow);
                        obj << account_no[index] << name[index] << " "
                            << "-" << value << "                   "
                            << "self"
                            << "                      " << balance[index] << "                " << t.tm_mday << "/" << t.tm_mon + 1 << "/" << t.tm_year + 1900 << endl;
                        obj.close();
                        return;
                    }
                    else if (value > balance[index] && value != 0)
                    {
                        cout << "Not enough amount!!" << endl;
                        break;
                    }
                    else
                    {
                        cout << "wrong input !" << endl;
                        break;
                    }
                }
            }
            else
            {
                string f;
                cout << "Password is incorrect !!" << endl;
                cout << "Password can be reset only from \"login to your account\" section" << endl;
                ;
                cout << "    ~ press -> 1 : continue to login with password" << endl;
                cout << "    ~ press -> 2 : previous menu" << endl;
                cin >> f;
                if (f == "1")
                {
                    cout << "Enter password : ";
                    cin >> pass;
                }
                else if (f == "2")
                {
                    break;
                }
                else
                {
                    cout << "Wrong input !!" << endl;
                    cout << "Enter password : ";
                    cin >> pass;
                }
            }
        }
    }
    else
        cout << "Account not found" << endl;
}
void account::credit(int pos)
{
    if (pos == 0)
    {
        cout << "No accounts !!" << endl;
        cout<<"~ create an account first !"<<endl;
        return;
    }
    int numb;
    string pass;
    cout << "Enter your account number : ";
    cin >> numb;
    int index = checkacc(numb, pos);
    if (index != -1)
    {
        cout << "Enter password : ";
        cin >> pass;
        while (true)
        {
            if (pass == password[index])
            {
                int value;
                cout << "Enter a valid amount(in Rs) you want to credit to your account : ";
                cin >> value;
                while (true)
                {
                    if (value < 0)
                    {
                        cout << "Credit amount can't be less than 0" << endl;
                        break;
                    }
                    else if (value == 0)
                    {
                        cout << "Credit amount can't be 0." << endl;
                        break;
                    }
                    else if (value != 0)
                    {
                        balance[index] = balance[index] + value;
                        cout << value << " has been creditted to your account successfully\nupdated balance is " << balance[index] << endl;
                        cout << "Have a nice day :)" << endl;
                        fstream obj("transaction_database.txt", ios::app);
                        time_t tnow;
                        tnow = time(NULL);
                        struct tm t = *localtime(&tnow);
                        obj << account_no[index] << name[index] << " "
                            << "+" << value << "                   "
                            << "self"
                            << "                      " << balance[index] << "                " << t.tm_mday << "/" << t.tm_mon + 1 << "/" << t.tm_year + 1900 << endl;
                        obj.close();
                        return;
                    }
                    else
                    {
                        cout << "wrong input !" << endl;
                        break;
                    }
                }
            }
            else
            {
                string f;
                cout << "Password is incorrect !!" << endl;
                cout << "Password can be reset only from \"login to your account\" section" << endl;
                ;
                cout << "    ~ press -> 1 : continue to login with password" << endl;
                cout << "    ~ press -> 2 : previous menu" << endl;
                cin >> f;
                if (f == "1")
                {
                    cout << "Enter password : ";
                    cin >> pass;
                }
                else if (f == "2")
                {
                    break;
                }
                else
                {
                    cout << "Wrong input !!" << endl;
                    cout << "Enter password : ";
                    cin >> pass;
                }
            }
        }
    }
    else
        cout << "Account not found" << endl;
}
void account::transfer(int pos)
{
    if (pos == 0)
    {
        cout << "No accounts !!" << endl;
        cout<<"~ create an account first !"<<endl;
        return;
    }
    int numb;
    string pass;
    cout << "Enter your account number : ";
    cin >> numb;
    int index = checkacc(numb, pos);
    if (index != -1)
    {
        cout << "Enter password : ";
        cin >> pass;
        while (true)
        {
            int secondacc;
            if (pass == password[index])
            {
                if (balance[index] == 0)
                {
                    cout << "Account balance is 0 !!" << endl;
                    return;
                }
                cout << "Enter an account in which you want to transfer : ";
                cin >> secondacc;
                int secindex = checkacc(secondacc, pos);
                if (secindex == index)
                {
                    cout << "Amount can't be transferred to your own account !" << endl;
                    break;
                }
                if (secindex != -1)
                {
                    int value;
                    string yn;
                    cout << "This account's details are ; \naccount number -> " << secondacc << "\nAccount owner -> " << name[secindex] << endl;
                    cout << "Do you want to continue ?(y/n) :";
                    cin >> yn;
                    if (yn == "y" || yn == "Y")
                    {
                        cout << "Enter an amount you want to transfer (in Rs): ";
                        cin >> value;
                        while (true)
                        {
                            if (value < 0)
                            {
                                cout << "Transfer amount can't be less than 0" << endl;
                                cout << "Enter an amount you want to transfer (in Rs): ";
                                cin >> value;
                            }
                            else if (value == 0)
                            {
                                cout << "Transfer amount can't be 0." << endl;
                                cout << "Enter an amount you want to transfer (in Rs): ";
                                cin >> value;
                            }
                            else if (value != 0 && value <= balance[index])
                            {
                                balance[index] -= value;
                                balance[secindex] += value;
                                cout << value << " has been transferred to " << name[secindex] << " successfully\nyour updated balance is " << balance[index] << endl;
                                cout << "Have a nice day :)" << endl;
                                fstream obj("transaction_database.txt", ios::app);
                                time_t tnow;
                                tnow = time(NULL);
                                struct tm t = *localtime(&tnow);
                                obj << account_no[index] << name[index] << " "
                                    << "-" << value << "                " << account_no[secindex] << "(" << name[secindex] << ")"
                                    << "                  " << balance[index] << "                " << t.tm_mday << "/" << t.tm_mon + 1 << "/" << t.tm_year + 1900 << endl;
                                obj << account_no[secindex] << name[secindex] << " "
                                    << "+" << value << "                " << account_no[index] << "(" << name[index] << ")"
                                    << "                  " << balance[secindex] << "                " << t.tm_mday << "/" << t.tm_mon + 1 << "/" << t.tm_year + 1900 << endl;
                                obj.close();
                                return;
                            }
                            else
                            {
                                cout << "Your account have insufficient balance !" << endl;
                                cout << "Enter an amount you want to transfer (in Rs): ";
                                cin >> value;
                            }
                        }
                    }
                    else if (yn == "n" || yn == "N")
                    {
                        cout << "Transfer cancelled !!" << endl;
                        return;
                    }
                    else
                    {
                        cout << "Wrong input !!" << endl;
                        break;
                    }
                }
                else
                    cout << "this account not found !" << endl;
            }
            else
            {
                string f;
                cout << "Password is incorrect !!" << endl;
                cout << "Password can be reset only from \"login to your account\" section" << endl;
                ;
                cout << "    ~ press -> 1 : continue to login with password" << endl;
                cout << "    ~ press -> 2 : previous menu" << endl;
                cin >> f;
                if (f == "1")
                {
                    cout << "Enter password : ";
                    cin >> pass;
                }
                else if (f == "2")
                {
                    break;
                }
                else
                {
                    cout << "Wrong input !!" << endl;
                    cout << "Enter password : ";
                    cin >> pass;
                }
            }
        }
    }
    else
        cout << "Account not found" << endl;
}
void account::login(int pos)
{
    if (pos == 0)
    {
        cout << "No accounts found !" << endl;
        cout << " ~~ Create an account first. " << endl;
        return;
    }
    int accountsample;
    string pass;
    char decision;
    cout << "Enter your account number : ";
    cin >> accountsample;
    int index = checkacc(accountsample, pos);
    if (index != -1)
    {
        cout << "Enter password : ";
        cin >> pass;
        while (true)
        {
            if (pass == password[index])
            {
                string option;
                cout << "*****Your account details are ;" << endl;
                cout << "  ~  Your name        -> " << name[index] << endl;
                cout << "  ~  account number   -> " << account_no[index] << endl;
                cout << "  ~  Reg. mobile no.  -> " << mobile[index] << endl;
                cout << "  ~  Your password    -> " << password[index] << endl;
                cout << "  ~  DOB (dd mm yyyy) -> " << dob[index] << endl;
                cout << "  ~  Balance (in Rs.) -> " << balance[index] << endl;
                cout << "Select option if you want to change any details ----" << endl;
                cout << "Press -> 1 : change mobile number\nPress -> 2 : change password" << endl;
                cout << "Press -> 3 : transaction history\nPress -> 4 : previous menu" << endl;
                cin >> option;
                if (option == "4")
                    break;
                else
                {
                    while (option != "4")
                    {
                        if (option == "1")
                        {
                            string newmob;
                            cout << "Enter your new mobile number : ";
                            cin >> newmob;
                            if (newmob == mobile[index])
                            {
                                cout << "Number is same as before." << endl;
                                break;
                            }
                            while (validnum(newmob) != 1)
                            {
                                cout << "Invalid number !" << endl;
                                cout << "Enter a valid mobile number : ";
                                cin >> newmob;
                            }
                            mobile[index] = newmob;
                            cout << "Your mobile number has been updated successsfully." << endl;
                        }
                        else if (option == "2")
                        {
                            string var;
                            cout << "Create new password---------- " << endl;
                            cout << "Enter password : ";
                            cin >> var;
                            if (var == password[index])
                            {
                                cout << "Password is same as before !" << endl;
                                break;
                            }
                            while (validpass(var) != 1)
                            {
                                cout << "password must contain : " << endl;
                                cout << "    ~ One lower-case letter" << endl;
                                cout << "    ~ One upper-case letter" << endl;
                                cout << "    ~ One special character(!, @, #, $, %, &)" << endl;
                                cout << "    ~ One numeric value(0-9)" << endl;
                                cout << "    ~ password length should be atleast 7" << endl;
                                cout << "Enter password : ";
                                cin >> var;
                            }
                            password[index] = var;
                            cout << "Your password has been updated successfully." << endl;
                        }
                        else if (option == "3")
                        {
                            string linestr;
                            string namepass = to_string(account_no[index]) + name[index];
                            int out = 0;
                            ifstream obj("transaction_database.txt");
                            while (!obj.eof())
                            {
                                getline(obj, linestr);
                                if (linestr.find(namepass) != string::npos)
                                {
                                    out++;
                                    if (out == 1)
                                        cout << "debit/credit         from/to account             upd. balance        date(dd/mm/yyyy)" << endl;
                                    cout << "   ";
                                    for (int i = namepass.size() + 1; i < linestr.size(); i++)
                                    {
                                        cout << linestr[i];
                                    }
                                    cout << endl;
                                }
                            }
                            if (out == 0)
                                cout << "NO TRANSACTIONS FOUND !!" << endl;
                            else
                                cout << "Completed !!" << endl;
                            obj.close();
                        }
                        else
                        {
                            cout << "Wrong option" << endl;
                        }
                        cout << "Select option if you want to change any details ----" << endl;
                        cout << "Press -> 1 : change mobile number\nPress -> 2 : change password" << endl;
                        cout << "Press -> 3 : transaction history\nPress -> 4 : previous menu" << endl;
                        cin >> option;
                    }
                }
            }
            else
            {
                string f;
                cout << "Password is incorrect !!" << endl;
                cout << "Password can be reset using DOB & Reg. mobile number only." << endl;
                cout << "    ~ press -> 1 : continue to login with password" << endl;
                cout << "    ~ press -> 2 : previous menu" << endl;
                cout << "    ~ press -> 3 : Forget password" << endl;
                cin >> f;
                if (f == "1")
                {
                    cout << "Enter password : ";
                    cin >> pass;
                }
                else if (f == "2")
                {
                    break;
                }
                else if (f == "3")
                {
                    int birth;
                    cout << "Enter your Date of Birth in (ddmmyyyy) format : ";
                    cin >> birth;
                    if (birth == dob[index])
                    {
                        string mob;
                        cout << "Enter your Mobile number : ";
                        cin >> mob;
                        if (mob == mobile[index])
                        {
                            string newpass;
                            cout << "Enter your new password :";
                            cin >> newpass;
                            password[index] = newpass;
                            cout << "Congratulations !! New password has been updated." << endl;
                            return;
                        }
                        else
                        {
                            cout << "Sorry :( \nAccount credentials do not match with this account's data." << endl;
                            cout << "You should contact \"ADMIN\" to reset your password." << endl;
                            break;
                        }
                    }
                    else
                    {
                        cout << "Sorry :( \nAccount credentials do not match with this account's data." << endl;
                        cout << "You should contact \"ADMIN\" to reset your password." << endl;
                        break;
                    }
                }
                else
                {
                    cout << "Wrong input !!" << endl;
                    cout << "Enter password : ";
                    cin >> pass;
                }
            }
        }
    }
    else
    {
        cout << "Account not found !!" << endl;
        return;
    }
}
int main() // driver function
{
    int pos, acc;
    string set;
    fstream n;
    n.open("database.txt");
    n >> set;
    if (set == "")
    {
        pos = 0;
        acc = 10001;
    }
    else
    {
        pos = stoi(set);
        n >> set;
        acc = stoi(set);
    }
    n.close();
    account o;
    o.importdata(pos, acc);
    string choice1, choice2, choice3;
    cout << "-------------WELCOME TO SAFE BANKING---------------" << endl;
    cout << "press -> 1 : Admin login" << endl;
    cout << "press -> 2 : Customer login" << endl;
    cout << "press -> 3 : Exit" << endl;
    cin >> choice1;
    if (choice1 == "3")
    {
        cout << "Exiting...." << endl;
        return 0;
    }
    else
    {
        while (choice1 != "3")
        {
            if (choice1 == "1")
            {
                string pass;
                cout << "Enter password : ";
                cin >> pass;
                if (!o.adminlogin(pass))
                {
                    cout << "Password is incorrect !!" << endl;
                }
                else
                {
                    cout << "--------------ADMIN---------------" << endl;
                    cout << "press -> 1 : to Show all data" << endl;
                    cout << "press -> 2 : for previous menu" << endl;
                    cin >> choice2;
                    while (choice2 != "2")
                    {
                        if (choice2 == "1")
                        {
                            o.showdata(pos);
                            break;
                        }
                        else
                        {
                            cout << "Wrong input" << endl;
                            cout << "--------------ADMIN---------------" << endl;
                            cout << "press -> 1 : to Show all data" << endl;
                            cout << "press -> 2 : for previous menu" << endl;
                            cin >> choice2;
                        }
                    }
                }
            }
            else if (choice1 == "2")
            {
                cout << "---------------CUSTOMER---------------" << endl;
                cout << "press -> 1 : to create an account" << endl;
                cout << "press -> 2 : to delete an account" << endl;
                cout << "press -> 3 : to debit" << endl;
                cout << "press -> 4 : to credit" << endl;
                cout << "press -> 5 : for money transfer" << endl;
                cout << "press -> 6 : login to your account" << endl;
                cout << "press -> 7 : for previous menu" << endl;
                cin >> choice3;
                while (choice3 != "7")
                {
                    if (choice3 == "1")
                    {
                        o.createaccount(pos, acc);
                        o.exportdata(pos, acc);
                        break;
                    }
                    else if (choice3 == "2")
                    {
                        o.delete_account(pos);
                        o.exportdata(pos, acc);
                        break;
                    }
                    else if (choice3 == "3")
                    {
                        o.debit(pos);
                        o.exportdata(pos, acc);
                        break;
                    }
                    else if (choice3 == "4")
                    {
                        o.credit(pos);
                        o.exportdata(pos, acc);
                        break;
                    }
                    else if (choice3 == "5")
                    {
                        o.transfer(pos);
                        o.exportdata(pos, acc);
                        break;
                    }
                    else if (choice3 == "6")
                    {
                        o.login(pos);
                        o.exportdata(pos, acc);
                        break;
                    }
                    else
                    {
                        if (choice3 != "7")
                            cout << "Wrong input!!" << endl;
                    }
                    cout << "---------------CUSTOMER---------------" << endl;
                    cout << "press -> 1 : to create an account" << endl;
                    cout << "press -> 2 : to delete an account" << endl;
                    cout << "press -> 3 : to debit" << endl;
                    cout << "press -> 4 : to credit" << endl;
                    cout << "press -> 5 : for money transfer" << endl;
                    cout << "press -> 6 : login to your account" << endl;
                    cout << "press -> 7 : for previous menu" << endl;
                    cin >> choice3;
                }
            }
            else
                cout << "Wrong input!!" << endl;
            cout << "-------------MAIN MENU---------------" << endl;
            cout << "press -> 1 : Admin login" << endl;
            cout << "press -> 2 : Customer login" << endl;
            cout << "press -> 3 : Exit" << endl;
            cin >> choice1;
        }
        cout << "Exiting...";
    }
    return 0;
}
