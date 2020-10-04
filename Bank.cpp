#include<iostream>  //For Turbo C++, write iostream.h
#include<fstream>    //For Turbo C++, write fstream.h
#include<cctype>      //For Turbo C++, write cctype.h
#include<iomanip>
#include<cstdlib> //For Turbo C++, write iomanip.h
using namespace std; //Not required for Turbo C++, So you can safely remove in that

class acc     //Class definition starts
{
    int ano;
    char name[100];
    int dep;
    char type;
public:
    void create_acc();    //function to create a new account
    void show_acc() const;    //function to show account details
    void modify();    //function to modify account details
    void adep(int);    //function to accept deposit amount
    void draw(int);    //function to subtract withdrawal amount
    void report() const;    //function to show data in tabular format
    int retano() const;    //For returning account number
    int retbal() const;    //For returning balance amount
    char qtype() const;    //For returning type of account
};         //Class definition ends



void acc::create_acc()
{
    cout<<"\nEnter The Account Number :";
    cin>>ano;
    cout<<"\n\nEnter, Name of The Account Holder : ";
    cin.ignore();
    cin.getline(name,100);
    cout<<"\nEnter Type of Account(Current/Savings) : ";
    cin>>type;
    cout<<"\nEnter The Initial amount(>=500 for Saving and >=1000 for current ) : ";
    cin>>dep;     //We have set the minimum initial amount for savings be 500 & for current be 1000
    cout<<"\n\n\nCongrats Account Has Been Created..";
}

void acc::show_acc() const
{
    cout<<"\nAccount Number : "<<ano;
    cout<<"\nAccount Holder Name : ";
    cout<<name;
    cout<<"\nType of Account : "<<type;
    cout<<"\nBalance amount : "<<dep;
}


void acc::modify()
{
    cout<<"\nAccount Number : "<<ano;
    cout<<"\nModify Account Holder Name : ";
    cin.ignore();
    cin.getline(name,100);
    cout<<"\nModify Type of Account : ";
    cin>>type;
    cout<<"\nModify Balance amount : ";
    cin>>dep;
}

void acc::adep(int x)
{
    dep+=x;
}

void acc::draw(int x)
{
    dep-=x;
}

void acc::report() const
{
    cout<<ano<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(6)<<dep<<endl;
}

int acc::retano() const
{
    return ano;
}

int acc::retbal() const
{
    return dep;
}

char acc::qtype() const
{
    return type;
}

void write_acc();    //function to write record in binary file
void display_sp(int);    //function to display account details given by user
void modify_acc(int);    //function to modify record of file
void delete_acc(int);    //function to delete record of file
void display_all();        //function to display all account details
void dep_withdraw(int, int); // function to desposit/withdraw amount for given account
void intro();    //introductory screen function





int main()
{
    char ch;
    int num;
    intro();
    do
    {
        system("CLS");   //Clear The Screen
        cout<<"\n\n\n\tACTION MENU";
        cout<<"\n\n\t01. NEW ACCOUNT";
        cout<<"\n\n\t02. DEPOSIT";
        cout<<"\n\n\t03. WITHDRAW";
        cout<<"\n\n\t04. BALANCE ENQUIRY";
        cout<<"\n\n\t05. COMPLETE ACCOUNT HOLDERS LIST";
        cout<<"\n\n\t06. CLOSE AN ACCOUNT";
        cout<<"\n\n\t07. MODIFY AN ACCOUNT";
        cout<<"\n\n\t08. EXIT";
        cout<<"\n\n\tSelect Your Option (1-8) ";
        cin>>ch;
        system("CLS");   //Clear The Screen
        switch(ch)
        {
        case '1':
            write_acc();
            break;
        case '2':
            cout<<"\n\n\tEnter The Account Number : "; cin>>num;
            dep_withdraw(num, 1);
            break;
        case '3':
            cout<<"\n\n\tEnter The Account Number : "; cin>>num;
            dep_withdraw(num, 2);
            break;
        case '4':
            cout<<"\n\n\tEnter The Account Number : "; cin>>num;
            display_sp(num);
            break;
        case '5':
            display_all();
            break;
        case '6':
            cout<<"\n\n\tEnter The Account Number : "; cin>>num;
            delete_acc(num);
            break;
         case '7':
            cout<<"\n\n\tEnter The Account Number : "; cin>>num;
            modify_acc(num);
            break;
         case '8':
            cout<<"\n\n\tThanks For Visiting Our Bank!";
            break;
         default :cout<<"\a";
        }
        cin.ignore();
        cin.get();
    }while(ch!='8');
    return 0;
}// Function To write the account data to .dat file
void write_acc()
{
    acc ac;
    ofstream x;
    x.open("info.dat",ios::binary|ios::app);
    ac.create_acc();
    x.write(reinterpret_cast<char *> (&ac), sizeof(acc));
    x.close();
}


void display_sp(int n)      //function to retrive a record from file stored
{
    acc ac;
    bool flag=false;
    ifstream x;
    x.open("info.dat",ios::binary);
    if(!x)
    {
        cout<<"File could not be opened!! Press any Key to exit...";
        return;
    }
    cout<<"\nBALANCE DETAILS\n";

        while(x.read(reinterpret_cast<char *> (&ac), sizeof(acc)))
    {
        if(ac.retano()==n)
        {
            ac.show_acc();
            flag=true;
        }
    }
    x.close();
    if(flag==false)
        cout<<"\n\nAccount number does not exist";
}//function to modify record of an account which is stored in file
void modify_acc(int n)
{
    bool found=false;
    acc ac;
    fstream x;
    x.open("info.dat",ios::binary|ios::in|ios::out);
    if(!x)
    {
        cout<<"File could not be open !! Press any Key...";
        return;
    }
    while(!x.eof() && found==false)
    {
        x.read(reinterpret_cast<char *> (&ac), sizeof(acc));
        if(ac.retano()==n)
        {
            ac.show_acc();
            cout<<"\n\nEnter The New Details of account"<<endl;
            ac.modify();
            int pos=(-1)*static_cast<int>(sizeof(acc));
            x.seekp(pos,ios::cur);
            x.write(reinterpret_cast<char *> (&ac), sizeof(acc));
            cout<<"\n\n\t Record Updated";
            found=true;
          }
    }
    x.close();
    if(found==false)
        cout<<"\n\n Record Not Found ";
}//function to delete a record from file
void delete_acc(int n)
{
    acc ac;
    ifstream x;
    ofstream y;
    x.open("info.dat",ios::binary);
    if(!x)
    {
        cout<<"File could not be open !! Press any Key...";
        return;
    }
    y.open("Temp.dat",ios::binary);
    x.seekg(0,ios::beg);
    while(x.read(reinterpret_cast<char *> (&ac), sizeof(acc)))
    {
        if(ac.retano()!=n)
        {
            y.write(reinterpret_cast<char *> (&ac), sizeof(acc));
        }
    }
    x.close();
    y.close();
    remove("info.dat");
    rename("Temp.dat","info.dat");
    cout<<"\n\n\tRecord Deleted ..";
}// function to display account details from the stored file
void display_all()
{
    acc ac;
    ifstream x;
    x.open("info.dat",ios::binary);
    if(!x)
    {
        cout<<"File could not be open !! Press any Key...";
        return;
    }
    cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
    cout<<"====================================================\n";
    cout<<"A/c no.      NAME           Type  Balance\n";
    cout<<"====================================================\n";
    while(x.read(reinterpret_cast<char *> (&ac), sizeof(acc)))
    {
        ac.report();
    }
    x.close();
}// function to withdraw amout from the account
void dep_withdraw(int n, int option)
{
    int amt;
    bool found=false;
    acc ac;
    fstream x;
    x.open("info.dat", ios::binary|ios::in|ios::out);
    if(!x)
    {
        cout<<"File could not be open !! Press any Key...";
        return;
    }
    while(!x.eof() && found==false)
    {
        x.read(reinterpret_cast<char *> (&ac), sizeof(acc));
        if(ac.retano()==n)
        {
            ac.show_acc();
            if(option==1)
            {
                cout<<"\n\n\tTO DEPOSITE AMOUNT ";
                cout<<"\n\nEnter The amount to be deposited";
                cin>>amt;
                ac.adep(amt);
            }
            if(option==2)
            {
                cout<<"\n\n\tTO WITHDRAW AMOUNT ";
                cout<<"\n\nEnter The amount to be withdraw";
                cin>>amt;
                int bal=ac.retbal()-amt;
                if((bal<500 && ac.qtype()=='S') || (bal<1000 && ac.qtype()=='C'))
                    cout<<"Insufficience balance";
                else
                    ac.draw(amt);
            }
            int pos=(-1)*static_cast<int>(sizeof(ac));
            x.seekp(pos,ios::cur);
            x.write(reinterpret_cast<char *> (&ac), sizeof(acc));
            cout<<"\n\n\t Record Updated";
            found=true;
           }
         }
    x.close();
    if(found==false)
        cout<<"\n\n Record Not Found ";
}//The Entry/Welcome Screen
void intro()
{
     cout<<"\n\n\n\n";
    cout<<"\t\t\t\t\t  *********      *******    ****     ***  ***       *        ********    *********** "<<endl;
    cout<<"\t\t\t\t\t  ***********   *********   *****    ***  ***     ***       **********   *********** "<<endl;
    cout<<"\t\t\t\t\t  ***     ***  ***     ***  ******   ***  ***   *****      ****    ****  ***         "<<endl;
    cout<<"\t\t\t\t\t  **********   ***     ***  *** ***  ***  *********        ****    ****  *********   "<<endl;
    cout<<"\t\t\t\t\t  **********   ***********  ***  *** ***  ********         ****    ****  *********   "<<endl;
    cout<<"\t\t\t\t\t  ***     ***  ***********  ***   ******  ***  ****        ****    ****  ***         "<<endl;
    cout<<"\t\t\t\t\t  ***********  ***     ***  ***    *****  ***   ****        **********   ***         "<<endl;
    cout<<"\t\t\t\t\t  *********    ***     ***  ***     ****  ***    ****        ********    ***         "<<endl;
    cout<<"\n\n\n";
    cout<<"\t\t\t\t\t         *********      ********    ****     ****    *******     ***                   "<<endl;
    cout<<"\t\t\t\t\t         ***********   **********    ****   ****    *********    ***                   "<<endl;
    cout<<"\t\t\t\t\t         ***     ***  ****    ****    *********    ***     ***   ***                   "<<endl;
    cout<<"\t\t\t\t\t         **********   ****    ****     *******     ***     ***   ***                   "<<endl;
    cout<<"\t\t\t\t\t         ********     ****    ****      *****      ***********   ***                   "<<endl;
    cout<<"\t\t\t\t\t         ***  ****    ****    ****      ****       ***********   ***                   "<<endl;
    cout<<"\t\t\t\t\t         ***   ****    **********      ****        ***     ***   ***********           "<<endl;
    cout<<"\t\t\t\t\t         ***    ****    ********      ****         ***     ***   ***********           "<<endl;


    //Note: All the data of the new account entered will be stored in the disk
    //So Please use with Admin Privilage for the compiled .exe, so that it could access the disk space
    cout<<"\nPress Enter To Continue........";
    cin.get();
}
