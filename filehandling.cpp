//code for maintaining records of patients(for doctors)//
#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
#include<cstring>
#include<cstdio>
using namespace std;

class patient
 {
     int srno;
     char name[20];
     int appdate;
     int month;
     int year;
     char symptoms[60];
     char medications[60];

 public:

    void create();
    void updatesymp();
    void updateapp();
    void updatemeds();
    void show();
    int patientno();
    void report();
 };
 void patient::create()
 {
     cout<< "\n Enter the Patient number:";
     cin>>srno;
     cout<< "\n Enter the Patient name: ";
     cin.ignore();
	cin.getline(name,20);
     cout<<" \n Enter the next appointment date DD MM YY: ";
     cin>>appdate>>month>>year;

     cout<< "\n Enter symptoms of patient: ";
     cin.ignore();
        cin.getline(symptoms,60);

     cout<< "\n Enter medications suggested: ";

     cin.getline(medications,60);
     cout<< "\n Entry created";
}

void patient::updatesymp()
{
    cout<<"Symptoms to be updated:";
    cin>>symptoms;

}

void patient::updateapp()
{

    cout<<"Enter next appointment date:";
    cin>>appdate>>month>>year;
}

void patient::updatemeds()
{
    cout<<"Enter medicine details:";
    cin>>medications;
}
void patient::show()
{
    cout<<"Enter the patient number:"<<srno<<endl;
    cout<<"Patient Name:"<<name<<endl;
    cout<<"Symptoms:"<<symptoms<<endl;
    cout<<"medications:"<<medications<<endl;
    cout<<"Last appointment date:"<<appdate<<"/"<<month<<"/"<<year<<endl;

}
void patient::report()
{
    cout<<srno<<setw(6)<<" "<<name<<setw(6)<<" "<<appdate<<"/"<<month<<"/"<<year<<setw(10)<<" "<<symptoms<<setw(10)<<" "<<medications ;
    cout<<"\n";
}

int patient::patientno()
{
    return srno;
}

//function declarations//
void write_record();
void display_record(int);
void modify_record(int);
void delete_record(int);
void display_all();


int main()
{
	char ch;
	int num;

	do
	{
		cout<<"\n\n\n\t MAIN MENU";
		cout<<"\n\n\t01. CREATE NEW RECORD";
		cout<<"\n\n\t02. UPDATE EXISTING";
		cout<<"\n\n\t03. DELETE RECORD";
		cout<<"\n\n\t04. DISPLAY A RECORD";
		cout<<"\n\n\t05. DISPLAY ALL";
		cout<<"\n\n\t06. EXIT";
		cout<<"\n\n\tSelect Your Option (1-6) ";
		cin>>ch;

		switch(ch)
		{
		case '1':
			write_record();
			break;
		case '2':
		    cout<<"\n\n\tEnter Patient Number:";
		    cin>>num;
			modify_record(num);
			break;
		case '3':
			cout<<"\n\n\tEnter patient Number:"; cin>>num;
			delete_record(num);
			break;
		case '4':
			cout<<"\n\n\tEnter Patient Number:"; cin>>num;
			display_record(num);
			break;
		case '5':
			display_all();
			break;
        case '6':
			cout<<"\n\n\t Successfully Exited ";
			break;
		default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
	}while(ch!='6');
	return 0;
}



void write_record()
{
	patient p;
	ofstream outFile;
	outFile.open("patient.txt",ios::binary|ios::app);
	p.create();
	outFile.write(reinterpret_cast<char *> (&p), sizeof(patient));
	outFile.close();
}

void display_record(int n)
{
	patient p;
	bool flag=false;
	ifstream inFile;
	inFile.open("patient.txt",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be opened.Press any Key";
		return;
	}
	cout<<"\n RECORDS\n";

    	while(inFile.read(reinterpret_cast<char *> (&p), sizeof(patient)))
	{
		if(p.patientno()==n)
		{
			p.show();
			flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\n Patient number does not exist";

}


void modify_record(int n)
{
 char a;
    do{
       cout<<"\n\n\t01.Modify Symptoms:";
       cout<<"\n\n\t02.Modify Medicines:";
       cout<<"\n\n\t03.Modify appointment date:";
       cout<<"\n\n\t   Enter the number (1-3)";
       cin>>a;
    //switch cases//
     switch(a)
		{
		case '1':
			{bool found=false;
	        patient p;
            fstream File;
	         File.open("patient.txt",ios::binary|ios::in|ios::out);
	         if(!File)
	         {
		      cout<<"File could not be opened.Press any Key...";
		      return;
	          }
	        while(!File.eof() && found==false)
	       {
		    File.read(reinterpret_cast<char *> (&p), sizeof(patient));
            if(p.patientno()==n)
		    {
			p.show();
			cout<<"\n\nEnter The New symptoms in record"<<endl;
			p.updatesymp();
			int pos=(-1)*static_cast<int>(sizeof(patient));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&p), sizeof(patient));
			cout<<"\n\n\t Record Updated";
			found=true;
		    }
	       }
	      File.close();
	      if(found==false)
		  cout<<"\n\n Record Not Found ";
            }
          break;

		case '2':
		    {bool found=false;
	        patient p;
            fstream File;
	         File.open("patient.txt",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be opened.Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&p), sizeof(patient));
		if(p.patientno()==n)
		{
			p.show();
			cout<<"\n\nEnter The New Medicines prescribed:"<<endl;
			p.updatemeds();
			int pos=(-1)*static_cast<int>(sizeof(patient));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&p), sizeof(patient));
			cout<<"\n\n\t Record Updated";
			found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
         }
        break;
		case '3':
		   {

            bool found=false;
	        patient p;
            fstream File;
	         File.open("patient.txt",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be opened.Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&p), sizeof(patient));
		if(p.patientno()==n)
		{
			p.show();
			cout<<"\n\nEnter The New symptoms in record"<<endl;
			p.updateapp();
			int pos=(-1)*static_cast<int>(sizeof(patient));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&p), sizeof(patient));
			cout<<"\n\n\t Record Updated";
			found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
       }
            break;
     default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
		}while (a!='3');

	}

void delete_record(int n)
{
	patient p;
	ifstream inFile;
	ofstream outFile;
	inFile.open("patient.txt",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.txt",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&p), sizeof(patient)))
	{
		if(p.patientno()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&p), sizeof(patient));
		}
	}
	inFile.close();
	outFile.close();
	remove("patient.txt");
	rename("Temp.txt","patient.txt");
	cout<<"\n\n\tRecord Deleted ..";
}

void display_all()
{
	patient p;
	ifstream inFile;
	inFile.open("patient.txt",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\tPATIENT RECORDS\n\n";
	cout<<"================================================================================\n";
	cout<<"SrNo.      NAME        Next Appointment Date       Symptoms        medications  \n";
	cout<<"================================================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&p), sizeof(patient)))
	{
		p.report();
	}
	inFile.close();
}
