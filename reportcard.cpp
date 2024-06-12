 #include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;
class student
{
    int rollno;
    char name[50];
    int english_marks, hindi_marks, math_marks, social_marks, science_marks;
    double per;
    char grade;
    void calculate();
    public:
    void getdata();
    void showdata()const;
    void show_tabular()const;
    int retrollno() const;
};


void student ::calculate()

{

    per=(english_marks+hindi_marks+math_marks+social_marks+science_marks)/5.0;
    if(per>=60)
    grade='A';
    else if(per>=50)
    grade='B';  
    else if(per>=33)
    grade='C';
    else
    grade='Fail';
}     
void student::getdata()
{

    cout<<"\n enter the roll number of student ";
    cin>>rollno;
    cout<<"\n\n enter the name of student";
    cin.ignore();
    cin.getline(name,50);
    cout<<"\n Enter the marks in english out of 100:";
    cin>>english_marks;
    cout<<"\n Enter the marks in hindi out of 100:";
    cin>>hindi_marks;
    cout<<"\n Enter the marks in math out of 100:";
    cin>>math_marks;
    cout<<"\n Enter the marks in social out of 100:";
    cin>>social_marks;
    cout<<"\n Enter the marks in science out of 100:";
    cin>>science_marks;
    calculate();            
}

void student::showdata() const

{

    cout<<"\nRoll number of student:"<<rollno;
    cout<<"\nName of student:"<<name;
    cout<<"\nMarks in english:"<<english_marks;
    cout<<"\nMarks in hindi:"<<hindi_marks;
    cout<<"\nMarks in math:"<<math_marks;
    cout<<"\nMarks in social:"<<social_marks;
    cout<<"\nMarks in science:"<<science_marks;
    cout<<"\npercentage of student is :"<<per;
    cout<<"\nGrade of student is :"<<grade;            
}

void student::show_tabular() const

{

    cout<<rollno<<setw(6)<<" "<<name<<setw(10)<<english_marks<<setw(4)<<hindi_marks<<setw(4)
    <<math_marks<<setw(4)<<social_marks<<setw(4)<<science_marks<<setw(4)<<per<<setw(6)<<grade<<endl;               
}

int student::retrollno()const

{
    return rollno;


}
        
// **************************************************************************
// function declaration
// **************************************************************************


void write_student();

void display_all();
void display_sp(int);
void modify_sttudent(int);
void delete_student(int);
void class_result();
void result();
void intro();
void entry_menu();

// **************************************************************************
//      THE MAIN FUNCTION OF PROGRAM
// **************************************************************************

int main()
{

    char ch;

    cout.setf(ios::fixed|ios::showpoint);
    cout<<setprecision(2);
    intro();

    do


         
    {
        system("cls");
        cout<<"\n\n\n\tMAIN MENU";
        cout<<"\n\n\t01. RESULT MENU";
        cout<<"\n\n\t02. ENTRY/EDIT MENU";
        cout<<"\n\n\t03.EXIT";
        cout<<"\n\n\tplease select your option(1-3)";
        cin>>ch;
        switch(ch)
        {
            case '1' : result();
            break;
            case '2' : entry_menu();
            break;
            case '3':
            break;  
            default :cout<<"\a";
                
        }



    }

    while(ch!= '3');
    return 0;
}

// **********************************************************************
//                   FUNCTION TO WRITE IN FILE
// **********************************************************************


void write_student()

{

    student st;
    ofstream outfile;
    outfile.open("student.dat",ios::binary|ios::app);
    st.getdata();
    outfile.write(reinterpret_cast<char *>(&st),sizeof(student));
    outfile.close();
    cout<<"\n\nstudent record has been created";
    cin.ignore();
    cin.get();
}  


// *********************************************************************************
//             FUNCTION TO READ ALL RECORD FROM FILE
// *********************************************************************************

void dispay_all()
{
    student st;
    ifstream infile;
    infile.open("student.dat",ios ::binary);
    if(!infile)

    {
        cout<<"file could not be open !! press any key...";
        cin.ignore();
        cin.get();
        return;

    }

    cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
    while(infile.read(reinterpret_cast<char *>(&st),sizeof(student)))
    {
        st.showdata();
        cout<<"\n\n===========================================\n";
    }


    infile.close();
    cin.ignore();
    cin.get();
}            
        

// **************************************************************************
//           FUNCTION TO READ SPECIFIC RECORD FROM FILE
// **************************************************************************


void display_sp(int n)  
{
    student st;
    ifstream infile;
    infile.open("student.dat",ios::binary);
    if(!infile)
    {
        cout<<"file could not be open !! press any key...";
        cin.ignore();
        cin. get();
        return;

    }
    bool flag=false;
    while(infile.read(reinterpret_cast<char *>(&st), sizeof(student)))
    {
        if(st.retrollno()==n)
        {
            st.showdata();
            flag=true;
        }

    }
    infile.close();
    if(flag==false)
    cout<<"\n\nrecord not exist";
    cin.ignore();
    cin.get();
}

// ************************************************************************************
//               FUNCTION TO MODIFY RECORD OF FILE
// ************************************************************************************

void modify_student(int n)
{
    bool found=false;
    student st;
    fstream file;
    file.open("student.dat",ios::binary|ios::in|ios::out);
    if(!file)
    {
        cout<<"file could not be open || press any key...";
        cin.ignore();
        cin.get();
        return;

    }

    while(!file.eof() && found==false)
    {
        file.read(reinterpret_cast<char *> (&st), sizeof(student));
        if(st.retrollno()==n)
        {
            st.showdata();
            cout<<"\n\nplease enter the new datails of student"<<endl;
            st.getdata();
            int pos=(-1)*static_cast<int>(sizeof(st));
            file.seekp(pos,ios::cur);
            file.write(reinterpret_cast<char *> (&st), sizeof(student));
            cout<<"\n\n\t record updated";
            found=true;
        }
    }
    file.close();
    if(found==false)
    cout<<"\n\n record not found";
    cin.ignore();
    cin.get();
                
}


// ************************************************************************
//        FUNCTION TO DELETE RECORD OF FILE
// ************************************************************************

void delete_student(int n)
{
    student st;
    ifstream infile;
    infile.open("student.dat",ios::binary);
    if(!infile)
    {
        cout<<"file could not be open !! press any key...";
        cin.ignore();
        cin.get();
        return;
    }
    ofstream outfile;
    outfile.open("temp.dat",ios::out);
    infile.seekg(0,ios::beg);
    while(infile.read(reinterpret_cast<char *>(&st),sizeof(student)))
    {
        if(st.retrollno()!=n)
        {
            outfile.write(reinterpret_cast<char *> (&st), sizeof(student));
        }
    }
    outfile.close();
    infile.close();
    remove("student .dat");
    rename("temp.dat","student.dat");
    cout<<"\n\n\trecoad deleted..";
    cin.ignore();
    cin.get();

}

// *****************************************************************
//     FUNCTION TO DISPLAY ALL STUDENT GRADE REPORT
// *****************************************************************

void class_result()
{
    student st;
    ifstream infile;
    infile.open("student.dat",ios::binary);
    if(!infile)
    {
        cout<<"File could not be open !! press any key...";
        cin.ignore();
        cin.get();
        return;
    }
    cout<<"\n\n\t\tALL STUDENT RESULT \n\n";
    cout<<"=======================================================================================\n";
    cout<<"R.NO    name     english     hindi     math     social     math    percentage   grade "<<endl;
    cout<<"=======================================================================================\n"; 
    while(infile.read(reinterpret_cast<char *> (&st),sizeof(student)))
    {
        st.show_tabular();

    }
    cin.ignore();
    cin.get();
    infile.close();

}

// ****************************************************************************************************
//       FUNCTION TO DISPLAY RESULT MENU
// ******************************************************************************************************

void result()
{
    char ch;
    int rno;
    system("cls");
    cout<<"\n\n\n\tRESULT MENU";
    cout<<"\n\n\n\t1. class result";
    cout<<"\n\n\t2. student report card";
    cout<<"\n\n\t3. back to main menu";
    cout<<"\n\n\n\t Enter choice (1/2/3)?";
    cin>>ch;
    system("cls");
    switch(ch)
    {
        case '1' : class_result(); break;
        case '2' : cout<<"\n\n\tEnter Roll Number Of Student  :"; cin>>rno;
        display_sp(rno); break;
        case '3' : break;
        default:     cout<<"\a";
    }
}
void intro()
{
    cout<<"\n\n\n\t\t STUDENT";
    cout<<"\n\n\t\t REPORT CARD";
    cin.get();
}

// ***************************************************************************
//      ENTRY / EDIT MENU FUNCTION
// ***************************************************************************

void entry_menu()
{
    char ch;
    int num;
    system("cls");
    cout<<"\n\n\n\tENTRY MENU";
    cout<<"\n\n\t1.CREATE STUDENT RECORD";
    cout<<"\n\n\t2.DISPLAY ALL STUDENT RECORD";
    cout<<"\n\n\t3.SEARCH STUDENT RECORD";
    cout<<"\n\n\t4.MODIFY STUDENT RECORD";
    cout<<"\n\n\t5.DELETE STUDENT RECORD";
    cout<<"\n\n\t6.BACK TO MAIN MENU";
    cout<<"\n\n\tplease enter your choice(1-6)";
    cin>>ch;
    system("cls");
    switch(ch)
    {
        case '1' :  write_student(); break;
        case '2' :  dispay_all();break;
        case '3' :  cout<<"\n\n\tplease enter the roll number"; cin>>num;
        display_sp(num);break;
        case '4' :  cout<<"\n\n\tplease enter the roll number"; cin>>num;
        modify_student(num);break;
        case '5' :  cout<<"\n\n\tplease enter the roll number"; cin>>num;
        delete_student(num);break;
        case '6' :  break;
        default:   cout<<"\a"; entry_menu();                                    
    }
}
