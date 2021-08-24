#include<iostream>
#include<fstream>
#include<cstring>

using namespace std;
const char*datafile="Hostel.csv";
class student
{
	private:
		char name[50];
		float ioe_marks;
		char district[30];
		int add;

	public:
		void read_data();
		void show_data();
		void write_rec();
		void readone_rec();
		void readall_rec();
		void edit_rec();
		void delete_rec();
		void calc_reasult();
		void show_reasult();
};
void student::read_data()
{
	cout<<"Enter Name of Student:"<<endl;
	cin>>name;
	cout<<"Enter IOE Marks:"<<endl;
	cin>>ioe_marks;
	cout<<"Enter your district:"<<endl;
	cin>>district;
	cout<<"Enter: \n1)VDC \n2)Municipality:"<<endl;
	cin>>add;
	cout<<endl;
}
void student::show_data()
{
	cout<<"Student Name: "<<name<<endl;
	cout<<"Student IOE Marks:"<<ioe_marks<<endl;
	cout<<"Student Home District:"<<district<<endl;
	cout<<"----------------------------------"<<endl;
}
void student::write_rec()
{ 	
	
	ofstream outfile(datafile,ios::out|ios::app);
	read_data();
	outfile.write(reinterpret_cast<char*>(this),sizeof(*this));
}
void student::readall_rec()
	{
	ifstream infile(datafile,ios::binary| ios::out|ios::in);
	if(!infile)
	{
		cout<<"File not found :store record first"<<endl;
		return;
	}
	cout<<"\n****Data from file****"<<endl;
	while(!infile.eof())
	{
		if (infile.read(reinterpret_cast<char*>(this),sizeof(*this))>0)
		show_data();
	}
	}
void student::readone_rec()
{
	int n;
	ifstream infile(datafile,ios::binary);
	if(!infile)
	{
		cout<<"File not found:store record first"<<endl;
		return;
	}
	infile.seekg(0,ios::end);
	int count=infile.tellg()/sizeof (*this);
	cout<<"\n There are"<<count<<"records in the file";
	cout<<"\n Enter Record Number:";
	cin>>n;
	infile.seekg((n-1)*sizeof(*this));
	infile.read(reinterpret_cast <char*>(this),sizeof (*this));
	show_data();
}
void student::edit_rec()
{
	int n;
	fstream iofile(datafile,ios::in|ios::binary);
	if(!iofile)
	{
		cout<<"file not found :store record first"<<endl;
		return;
	}
	iofile.seekg(0,ios::end);
	int count=iofile.tellg()/sizeof(*this);
	cout<<"\n There are "<<count<<"records in the file";
	cout<<"\n Enter Record Number to be edited: ";
	cin>>n;
	iofile.seekg((n-1)*sizeof(*this));
	iofile.read(reinterpret_cast<char*>(this),sizeof(*this));
	cout<<"Record"<<n<<"has following data"<<endl;
	read_data();
	iofile.close();
	iofile.open ("record.dat",ios::out|ios::in|ios::binary);
	iofile.seekp((n-1)*sizeof(*this));
	cout<<"\n Enter data to modify"<<endl;
	read_data();
	iofile.write(reinterpret_cast<char*>(this),sizeof(*this) );
}
void student::delete_rec()
{
	int n;
	char tempfile[]="temp.data";
	ifstream infile(datafile,ios::binary);
	if(!infile)
	{
		cout<<"File not found:store record first "<<endl;
		return;
	}
	infile.seekg(0,ios::end);
	int count=infile.tellg()/sizeof(*this);
	cout<<"\n There are"<<count<<"records in the file";
	cout<<"\n Enter Record Number to be delete:";
	cin>>n;
	fstream tmpfile(tempfile,ios::out|ios::binary);
	infile.seekg(0);
	for(int i=0;i<count;++i)
	{
		infile.read(reinterpret_cast<char*>(this),sizeof(*this));
		if (i==(n-1))
		continue;
		tmpfile.write(reinterpret_cast<char*>(this),sizeof(*this));
	}
	infile.close();
	ofstream outfile(datafile,ios::binary);
	tmpfile.close();
	tmpfile.open(tempfile,ios::in|ios::binary);
	for(int i=0;i<count-1;++i)
	{
		tmpfile.read(reinterpret_cast<char*>(this),sizeof(*this));
		outfile.write(reinterpret_cast<char*>(this),sizeof(*this));

	}
	tmpfile.close();
	remove(tempfile);
}
void student::calc_reasult()
{
	float total;
	int location_marks;
	int MUN_OR_VDC;
	int VDC_Point;
	if (district=="Sindhupalchowk"|| district=="Manang"|| district=="Mustang"|| district=="Darchula"|| district=="Dhading")
	{
		location_marks=80;
	}
	else
	location_marks=60;
	if (MUN_OR_VDC==1)
	VDC_Point=25;
	else if(MUN_OR_VDC==2)
	VDC_Point=20;
	else
	VDC_Point=15;
	total=ioe_marks+location_marks+VDC_Point;
	cout<<"Name:"<<name<<"\t\t\t\t"<<"Total Point:"<<total<<endl;
}
int main()
{
	student stu[100];
	student st;
	int i;
	int choice,n;
	cout<<"\n\t\t\t***************************************\t\t\t"<<endl;
	cout<<"\t\t\t***Pulchowk Hostel Management System***\t\t\t"<<endl;
	cout<<"\t\t\t***************************************\t\t\t"<<endl;
	cout<<"\t\t\t\t\t\t\t\t\t\t\t\t prepared by:";
	cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t Manoj Joshi";
	cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t Min Nidal"<<endl;
	while(true)
	{
	cout<<"\n select one option below";
	cout<<"\n\t1--->Write Records to file";
	cout<<"\n\t2--->Show all records from file";
	cout<<"\n\t3--->Show one Record";
	cout<<"\n\t4--->Edit a Record";
	cout<<"\n\t5--->Delete a Record";
	cout<<"\n\t6--->Calculate a Reasult";
	cout<<"\n\t7--->Show Reasult";
	cout<<"\n Enter your choice:"<<endl;
	cin>>choice;
	switch(choice)
	{
		case 1:
			cout<<"Enter the number of student:"<<endl;
			cin>>n;
			for(i=0;i<n;i++)
			{
				stu[i].write_rec();
			}
			break;
		case 2:
			st.readall_rec();
			break;
		case 3:
			st.readone_rec();
			break;
		case 4:
			st.edit_rec();
			break;
		case 5:
			st.delete_rec();
			break;
		case 6:
			cout<<"enter the number of record"<<endl;
			cin>>n;
			cout<<"total marks obtained by student:"<<endl;
			for(i=0;i<n;i++)
			{
				stu[i].calc_reasult();
			}
			break;
	//	case 7:
	//		for(i=0;i<n;i++)
	//		{
	//			stu[i].show_reasult();
	//		}
	//		break;		
		default:
			cout<<"choice not available"<<endl;
			exit(0);
			
	}
	
   
   }return 0;
	
}
	
	

