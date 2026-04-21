#include<iostream>
#include<windows.h>
#include<vector>
#include<iomanip>
#include<conio.h>
#include<fstream>

using namespace std;
//-----------------constant speed limits---------------
const int city_road=60;
const int highway=100;
const int motoway=180;

//-----------------class for records data------------
class Vehicle
{
    public:
    string vehicle_number;
    string road_type;
    float speed;
    float speed_limit;
    int fine=0;
    string fine_status="null";

};
vector<Vehicle>vehicles;// to store all violations

//---------------------to save all records to file------------------
void save_records()
{
    ofstream outfile("vehicle records.txt");
    if(!outfile) return;
    for(auto v: vehicles)
    {
        outfile<<v.vehicle_number<<","<<v.road_type<<","<<v.speed<<","<<v.speed_limit<<","<<v.fine<<","<<v.fine_status<<endl;
    }
}

//----------------to load all records from file to vehicle vector--------------
void load_records()
{
    ifstream infile("vehicle records.txt");
    if(!infile) return;
    string line;
    while(getline(infile,line)){
        Vehicle v;
        stringstream ss(line);
        string temp;
        getline(ss,temp,','); v.vehicle_number=temp;
        getline(ss,temp,','); v.road_type=temp;
        getline(ss,temp,','); v.speed=stof(temp);
        getline(ss,temp,','); v.speed_limit=stof(temp);
        getline(ss,temp,','); v.fine=stoi(temp);
        getline(ss,temp,','); v.fine_status=temp;
        vehicles.push_back(v);
        
    }
}

//--------------------display vehicle record--------------
void display(Vehicle v)
{
    cout<<left<<setw(20)<< "vehicle number"<<setw(20)<< v.vehicle_number<<endl;
    cout<<left<<setw(20)<< "vehivle speed"<<v.speed<<"km/h"<<endl;
    cout<<left<<setw(20)<< "vehivle road_type"<<setw(20)<<v.road_type<<endl;
    cout<<left<<setw(20)<< "road speed_limit"<<v.speed_limit<<"km/h"<<endl;
    if(v.fine > 0){
    cout<<left<<setw(20)<< "fine"<<setw(20)<<v.fine<<endl;
    cout<<left<<setw(20)<< "fine status"<<setw(20)<<v.fine_status<<endl;
    }
    else{
        cout<<"------------safe travels-------------"<<endl;
    }
    getch();

}

//---------------------to add a violation record----------------
void add_record()
{
    Vehicle v;
    cout<<"enter vehicle number"<<endl;
    getline(cin,v.vehicle_number);
    cout<<"enter speed of the vehicle(km/h)"<<endl;
    cin>>v.speed;
    cin.ignore();
    cout<<"enter roadtype traveled by vehicle(city/ highway/ motorway)"<<endl;
    start:
    getline(cin,v.road_type);

    if(v.road_type=="city")
    v.speed_limit=city_road;
    else if(v.road_type=="highway")
    v.speed_limit=highway;
    else if(v.road_type=="motorway")
    v.speed_limit=motoway;
    else{
    cout<<"invalid roadtype. \n enter again"<<endl;
    goto start;
    }
    float exceeded_speed=v.speed - v.speed_limit;
    if(exceeded_speed > 0){
        if(exceeded_speed<=10)
        v.fine=1000;
        else if(exceeded_speed<=30)
        v.fine=3000;
        else
        v.fine=5000;
        char choice;
        cout<<"you are fined Rs. "<<v.fine<<". Do you want to pay (y/n)"<<endl;
        cin>>choice;
        if(choice== 'y' || choice== 'Y'){
            v.fine_status="paid";
        }
        else{
            v.fine_status="unpaid";
        }
        vehicles.push_back(v);
        save_records();
    }
    display(v);

}

//--------------------to search a specific record-----------------
void search_record()
{
    string v_no;
    cout<<"enter vehicle number"<<endl;
    getline(cin,v_no);
    bool found=false;
    for(int i=0;i<vehicles.size();i++)
    {
        if(v_no==vehicles[i].vehicle_number){
            found=true;
            cout<<left<<setw(20)<< "vehicle number"<<setw(20)<< vehicles[i].vehicle_number<<endl;
            cout<<left<<setw(20)<< "vehivle speed"<<vehicles[i].speed<<"km/h"<<endl;
            cout<<left<<setw(20)<< "vehivle road_type"<<setw(20)<<vehicles[i].road_type<<endl;
            cout<<left<<setw(20)<< "road speed_limit"<<vehicles[i].speed_limit<<"km/h"<<endl;
            cout<<left<<setw(20)<< "fine"<<setw(20)<<vehicles[i].fine<<endl;
            cout<<left<<setw(20)<< "fine status"<<setw(20)<<vehicles[i].fine_status<<endl;
            break;
        }
    }
    if(!found)
    {
        cout<<"no record found for this vehicle"<<endl;
    }
    getch();
}

//----------------------to view all violation records----------------------
void view__all_records()
{
    for(int i=0;i<vehicles.size();i++)
    {
        cout<<"\n\n************vehicle "<<i+1<<" record************"<<endl;
        cout<<left<<setw(20)<< "vehicle number"<<setw(20)<< vehicles[i].vehicle_number<<endl;
        cout<<left<<setw(20)<< "vehivle speed"<<vehicles[i].speed<<"km/h"<<endl;
        cout<<left<<setw(20)<< "vehivle road_type"<<setw(20)<<vehicles[i].road_type<<endl;
        cout<<left<<setw(20)<< "road speed_limit"<<vehicles[i].speed_limit<<"km/h"<<endl;
        cout<<left<<setw(20)<< "fine"<<setw(20)<<vehicles[i].fine<<endl;
        cout<<left<<setw(20)<< "fine status"<<setw(20)<<vehicles[i].fine_status<<endl;
        cout<<"\n*****#*****#******#*****#******#*****#*****"<<endl;

    }
    getch();
}

//-------------------for paying fine later-----------------
void pay_fine()
{
    string v_no;
    cout<<"enter vehicle number"<<endl;
    getline(cin,v_no);
    bool found=false;
    for(int i=0;i<vehicles.size();i++)
    {
        if(v_no==vehicles[i].vehicle_number)
        {
            found=true;
            if(vehicles[i].fine_status=="unpaid"){
                cout<<"you have been fined Rs."<<vehicles[i].fine<<endl;
                cout<<"do you want to pay it (y/n)"<<endl;
                char choice;
                cin>>choice;
                cin.ignore();
                if(choice== 'y' || choice== 'Y'){
                vehicles[i].fine_status="paid";
                cout<<"fine payed successfully"<<endl;
                save_records();
                }
                else{
                    vehicles[i].fine_status="unpaid";
                    cout<<"you didn't pay the fine"<<endl;
                }
            }
            else{
                cout<<"you have payed the fine"<<endl;
            }
            break;
        }
    }
    if(!found)
    {
        cout<<"no record found for such a vehicle"<<endl;
    }
    getch();
}

//--------------------to calculate total unpaid fine---------------
void Calculate_unpaid_fine()
{
    int total=0;
    for(int i=0;i<vehicles.size();i++)
    {
        total+=vehicles[i].fine;
    }
    cout<<"the total unpaid fine is: "<<total<<endl;
    getch();
}
int main()
{
    load_records();
    int choice=0;
    while(choice != 6){
        Sleep(1000);
        system("cls");
        cout << "===================================" << endl;
        cout << "SIMULATION OF SPEED CAMERA SYSTEM" << endl;
        cout << "===================================" << endl;

        cout << "\nMenu:" << endl;
        cout << "1. Enter vehicle record" << endl;
        cout << "2. View all violation records" << endl;
        cout << "3. Search a record" << endl;
        cout << "4. Show total unpaid fine" << endl;
        cout << "5. Pay unpaid fine" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        switch(choice)
        {
            case 1:
            add_record();
            break;
            case 2:
            view__all_records();
            break;
            case 3:
            search_record();
            break;
            case 4:
            Calculate_unpaid_fine();
            break;
            case 5:
            pay_fine();
            break;
            case 6:
            cout<<"exiting the program";
            for(int i=0;i<4;i++){
                cout<<". ";
                Sleep(1000);
            }
            break;
            default:
            cout<<"invalid choice"<<endl;
        }
    }
}