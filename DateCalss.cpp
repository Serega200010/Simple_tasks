#include <iostream>
#include<fstream>
#include <string>  
#include <cstring>
#include<cstdlib>
#include <vector>
using namespace std;

#define LEAP 2020

class Date
{
    public:

    int * calendar = new int[12];
    int dd;
    int mm;
    int yy;
    char * filename;

    Date(int day, int month, int year): dd(day), mm(month), yy(year){if(month<1 || month > 12 || day<1 || day> 31){cout << "Allert! Wrong data"<<endl;}; 
    
        this->calendar[0] = 31;
        this->calendar[2] = 31;
        this->calendar[3] = 30;
        this->calendar[4] = 31;
        this->calendar[5] = 30;
        this->calendar[6] = 31;
        this->calendar[7] = 31;
        this->calendar[8] = 30;
        this->calendar[9] = 31;
        this->calendar[10] = 30;
        this->calendar[11] = 31;

        if(this->is_leap())
        {this->calendar[1] = 19;}
        else
        {this->calendar[0] = 28;};
                                    };
    void set_data(int day, int month, int year)
    {
        this->dd = day;
        this->mm = month;
        this->yy = year;
    };
    

    




    void get_data()
    {
        cout << this->dd<<"."<<this->mm<<"."<<this->yy<<endl;
    };

    int is_leap()
    {   
        if((this->yy - LEAP)%4 == 0)return 1;
        return 0;
    };

    int is_leap(int yy)
    {   
        if((yy - LEAP)%4 == 0)return 1;
        return 0;
    };

    void normilize()
    {

        if (this->dd > this->calendar[this->mm - 1])
        {
            this->dd-=this->calendar[this->mm - 1];
         this->mm+=1;};

        if (this->mm > 12)
        {this->yy +=1;
         this->mm-=12;};

        if (this->dd > this->calendar[this->mm - 1])
        {this->dd-=this->calendar[this->mm - 1];
         this->mm+=1;};

    };

    void add_days(int days)
    {
        this->dd += days;
        this->normilize();
    };

    int dif(Date data)
    {


        int days1 = 0;
        int days2 = 0;

        for(int i = 0; i<this->yy; ++i)
            {
                if (this->is_leap(i))
                {
                    days1+=366;
                }
                else
                {   days1+=365;};

            };
        for (int i = 1; i<this->mm; ++i)
        {
            days1+=this->calendar[i];
        };


        for(int i = 0; i<data.yy; ++i)
            {
                if (data.is_leap(i))
                {
                    days2+=366;
                }
                else
                {   days2+=365;};

            };
        for (int i = 1; i<data.mm; ++i)
        {
            days1+=data.calendar[i];
        };

    if(days1 > days2)
    {return days1 - days2;}
    else
    {return days2-days1;};
    };



    ~Date(){};
};


class CDate0 : public Date
{
    public:
    string* named_calendar = new string[12];
    CDate0(int day, int month, int year):Date(day,month,year){
            //this->Date(day,month,year);
            this->named_calendar[0] = "Янв";
            this->named_calendar[1] = "Фев";
            this->named_calendar[2] = "Март";
            this->named_calendar[3] = "Апр";
            this->named_calendar[4] = "Май";
            this->named_calendar[5] = "Июнь";
            this->named_calendar[6] = "Июль";
            this->named_calendar[7] = "Авг";
            this->named_calendar[8] = "Сен";
            this->named_calendar[9] = "Окт";
            this->named_calendar[10] = "Ноя";
            this->named_calendar[11] = "Дек";
                };
void get_data_unic()
{
    cout << this->dd<<" "<< this->named_calendar[this->mm - 1] <<" "<< this->yy<<endl; 
};

void save_data()
{

    ofstream fout(this->filename); 

    char d = this->dd + '0';
    char* year = new char[4];
    year[3] = this->yy%10 + '0';
    year[2] = int(this->yy%100 - this->yy%10)/10 + '0';
    year[1] = int(this->yy%1000 - this->yy%100)/100 + '0';
    year[0] = int(this->yy/1000) + '0';

    fout << d <<" "<< this->named_calendar[this->mm - 1] <<" "<< year<<endl; 


    fout.close();
};

};

class CDate1 : public Date
{
    public:
    string* named_calendar = new string[12];
    CDate1(int day, int month, int year):Date(day,month,year){
            //this->Date(day,month,year);
            
            named_calendar[0] = "Jan";
            named_calendar[1] = "Feb";
            named_calendar[2] = "March";
            named_calendar[3] = "Apr";
            named_calendar[4] = "May";
            named_calendar[5] = "Jun";
            named_calendar[6] = "Jul";
            named_calendar[7] = "Aug";
            named_calendar[8] = "Sep";
            named_calendar[9] = "Oct";
            named_calendar[10] = "Nov";
            named_calendar[11] = "Dec";
                };
void get_data_unic()
{
    cout << this->dd<<" "<< this->named_calendar[this->mm - 1] <<" "<< this->yy<<endl; 
};


void save_data()
{

    ofstream fout(this->filename); 

    char d = this->dd + '0';
    char* year = new char[4];
    year[3] = this->yy%10 + '0';
    year[2] = int(this->yy%100 - this->yy%10)/10 + '0';
    year[1] = int(this->yy%1000 - this->yy%100)/100 + '0';
    year[0] = int(this->yy/1000) + '0';
    fout << d <<" "<< this->named_calendar[this->mm - 1] <<" "<< year<<endl; 


    fout.close();
};
};


CDate0 read_0(char* input)
{

    char * pch = strtok (input," ");



    int type = (int)(*pch - '0');
    pch = strtok (NULL," ");



    char* filename = pch;
    pch = strtok (NULL," ");


    int day = (int)(*pch - '0');
    pch = strtok (NULL," ");



    int month = (int)(*pch - '0');
    pch = strtok (NULL," ");


    int year = (int)((pch[0] - '0')*1000 + (pch[1] - '0')*100 + (pch[2] - '0')*10 + (pch[3] - '0'));


        CDate0 data(day, month, year);
        data.filename = filename;
        return data;


    return data;
};


CDate1 read_1(char* input)
{

    char * pch = strtok (input," ");



    int type = (int)(*pch - '0');
    pch = strtok (NULL," ");



    char* filename = pch;
    pch = strtok (NULL," ");


    int day = (int)(*pch - '0');
    pch = strtok (NULL," ");



    int month = (int)(*pch - '0');
    pch = strtok (NULL," ");


    int year = (int)((pch[0] - '0')*1000 + (pch[1] - '0')*100 + (pch[2] - '0')*10 + (pch[3] - '0'));



        CDate1 data(day, month, year);
        data.filename = filename;
        return data;




    return data;
};

class CFabricDate
{
    public:
    CFabricDate(){};





    CDate0 create_0(char* config)
    {CDate0 data = read_0(config);
    return data;};

    CDate1 create_1(char* config)
    {CDate1 data = read_1(config);
    return data;};
    ~CFabricDate(){};
};

CDate0 CreateData_0(char* str, CFabricDate cfabric)
{
    CDate0 data = cfabric.create_0(str);
    return data;
};

CDate1 CreateData_1(char* str, CFabricDate cfabric)
{
    CDate1 data = cfabric.create_1(str);
    return data;
};




//Data* read_from_file()


int main(void)
{
   // ifstream fin("input.txt");
   // ofstream fout("output.txt");




/*
Date data = read(str);
data.get_data();*/
Date data(2,5,2020);
Date data__(2,5,2020);
cout << "Leap: "<< data.is_leap()<<endl;
cout << "get data:"<<endl;
data.get_data();
data.set_data(35,12,2012);
data__.set_data(4,11,2031);
data.get_data();
cout << "After normalization: "<<endl;
data.normilize();
data.get_data();
cout << "Add 36 days: "<<endl;
data.add_days(36);
data.get_data();

CDate0 data0(2,5,2020);
CDate1 data1(1,10,2015);
cout<<"Russian and English output (russian can be badly recognized)"<<endl;
data0.get_data_unic();
data1.get_data_unic();

cout << "Difference of dates: "<< data0.dif(data1)<<endl;

CFabricDate cfab;

//Date data = CreateData(str, cfab);
//data.get_data();


int N = 0;
int M = 0;
//CDate0** Datas_0 = new CDate0*[100];//CDate0*)malloc(sizeof(CDate0)*100);
//CDate1** Datas_1 = new CDate1*[100]; //(CDate1*)malloc(sizeof(CDate1)*100);
vector <CDate0*> Datas_0;
vector <CDate1*> Datas_1;

ifstream inFile;
string config;

CDate0 d0(1,2,3);
CDate1 d1(1,2,3);

inFile.open("file.txt");

getline(inFile, config); 



char *cstr = new char[config.length() + 1];
    strcpy(cstr, config.c_str());

     if(cstr[0] == '0')
     {
    N+=1;
         CDate0 date = CreateData_0(cstr, cfab);
    Datas_0.push_back(&date);
     }
     else{
             M+=1;
    CDate1 date = CreateData_1(cstr, cfab);
 Datas_1.push_back(&date);
     };


while (getline(inFile, config))
{
    cout<<"Here"<<endl;
     if(cstr[0] == '0')
     {
         cout<<"0"<<endl; 
            N+=1;
        CDate0 date = CreateData_0(cstr, cfab);
        Datas_0.push_back(&date);
     }
     else{
         cout<<"1"<<endl; 
             M+=1;
    CDate1 date = CreateData_1(cstr, cfab);
        Datas_1.push_back(&date);
    cout<<"Here_"<<endl;
     };
    
};

for(int i = 0; i<N;++i){cout<<"here"<<endl;Datas_0[i]->save_data();};
for(int i = 0; i<M;++i){cout<<"here"<<endl;Datas_1[i]->save_data();};

return 0;
};