#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <map>

using namespace std;

char delim = ':';
const int hoursPerDay = 24;
const int minutesPerHour = 60;
//enum DaysInMonth{JAN=31,FEB=28,MAR=31,APR=30,MAY=31,JUN=30,JUL=31,AUG=31,SEP=30,OCT=31,NOV=30,DEC=31};
//enum MonthNumber{JAN=1,FEB=2,MAR=3,APR=4,MAY=5,JUN=6,JUL=7,AUG=8,SEP=9,OCT=10,NOV=11,DEC=12};
//typedef MonthNumber monthNumber;
//typedef DaysInMonth daysInMonth;

map<int,int> daysInMonth;


class Date
{
private:

    string date;

public:
    int day;
    int month;
    int year;
    Date(string date) {

        stringstream ss;
        ss.str(date);
        char c = '/';
        ss>>day>>c >> month >> c >> year;

    }
    Date(int day, int month, int year) {

        this->day = day;
        this->month = month;
        this->year = year;
        toString();
    }

    Date operator + (int numberOfDays) {

        if(month==2)
        {

            if(this->year%4==0 || this->year%100==0)
            {
                if(this->day+numberOfDays<=29)
                {
                    this->day+=numberOfDays;

                }else{
                    this->day=01;
                    this->month +=1;
                }

            }else{
                if(this->day+numberOfDays<=28)
                {
                    this->day+=numberOfDays;

                }else{
                    this->day=01;
                    this->month +=1;
                }

            }


        }else if(daysInMonth[month]== 30)
        {
            if(this->day-numberOfDays<1)
            {
                this->day+=numberOfDays;

            }else{
                this->day=01;
                this->month +=1;
            }


        }else
        {
            if(this->day+numberOfDays<=31)
            {
                this->day+=numberOfDays;

            }else{
                this->day = 01;
                if(this->month==12)
                {
                    this->month = 01;
                    this->year++;
                }else
                {
                    this->month +=1;

                }
            }
        }
        toString();
        return *this;
    }
    Date operator - (int numberOfDays) {
        if(month==3)
        {

            if(this->year%4==0 || this->year%100==0)
            {
                if(this->day-numberOfDays<1)
                {
                    this->day =29;
                    this->month -= 1;

                }else{
                    this->day -= numberOfDays;

                }

            }else{
                if(this->day-numberOfDays<1)
                {
                    this->day =28;
                    this->month -= 1;

                }else{
                    this->day -= numberOfDays;

                }


            }


        }else if(this->day-numberOfDays>=1)
        {

            this->day-=numberOfDays;
        }else
        {
            if(daysInMonth[month]==30)
            {
                this->day= 31;
                this->month -=1;

            }else{
                if(this->month==1)
                {
                    this->day=31;
                    this->month=12;
                    this->year-=1;
                }else{
                    this->day= daysInMonth[month-1];
                    this->month= month-1;
                }
            }
        }
        toString();
        return *this;

    }
    string toString() {
        date.clear();
        char c='/';
        stringstream ss;

        ss<<to_string(day)<<c<<to_string(month)<<c<<to_string(year);
        date = ss.str();
        return date;
    }
};

class CityDetails
{
public:
    //string name;
    int gmtOffsetHH;
    int gmtOffsetMM;
    int dstOffsetHH;
    int dstOffsetMM;

    int dstStartMonth;
    int dstStartDate;
    int dstEndMonth;
    int dstEndDate;
    CityDetails(int gmtOffsetHH,int gmtOffsetMM,int dstOffsetHH,int dstOffsetMM,int dstStartMonth,int dstStartDate,int dstEndMonth,int dstEndDate)
    {
        this->dstEndDate = dstEndDate;
        this->dstStartDate = dstStartDate;
        this->dstStartMonth = dstStartMonth;
        this->dstEndMonth = dstEndMonth;
        this->gmtOffsetHH = gmtOffsetHH;
        this->gmtOffsetMM = gmtOffsetMM;
        this->dstOffsetHH = dstOffsetHH;
        this->dstOffsetMM = dstOffsetMM;
    }
    CityDetails()
    {
        this->dstEndDate = 0;
        this->dstStartDate = 0;
        this->dstStartMonth = 0;
        this->dstEndMonth = 0;
        this->gmtOffsetHH = 0;
        this->dstOffsetHH = 0;
        this->gmtOffsetMM = 0;
        this->dstOffsetMM = 0;
    }

};

class TimeConvertion
{
    map<string,CityDetails*> data;

private:
    string in;
    stringstream ss;
    int hours, minutes;
    char c;
    int date,month,year;
    string source,destination;


    bool checkTimeValidity(int hour, int min)
    {
        return (hour >= 0) && (hour < hoursPerDay) && (min >= 0) && (min < minutesPerHour);
    }
    bool checkCountryValidity(string cName)
    {
        if(_stricmp(cName.c_str(),"New Delhi")==0 || _strcmpi(cName.c_str(),"Jakarta")==0 ||_strcmpi(cName.c_str(),"London")==0 ||_strcmpi(cName.c_str(),"Brussels")==0 || _strcmpi(cName.c_str(),"Montreal")==0 ||_strcmpi(cName.c_str(),"Kabul")==0 || _strcmpi(cName.c_str(),"Buenos Aires")==0 || _strcmpi(cName.c_str(),"Brisbane")==0 || _strcmpi(cName.c_str(),"Vienna")==0)
        {
            return true;
        }
        return false;
    }
    ~TimeConvertion() {
        //iterate map and delete data
    }


public:
    TimeConvertion()
    {
        data.clear();

        data.insert(pair<string,CityDetails*>("Kabul",new CityDetails(4,30,4,30,0,0,0,0)));
        //c.init(-3,0,-3,0,0,0,0,0);
        data.insert(pair<string,CityDetails*>("Buenos Aires",new CityDetails(-3,0,-3,0,0,0,0,0)));
        //c.init(10,0,10,0,0,0,0,0);
        data.insert(pair<string,CityDetails*>("Brisbane",new CityDetails(10,0,10,0,0,0,0,0)));

        //c.init(1,0,2,0,3,31,10,27);
        data.insert(pair<string,CityDetails*>("Vienna",new CityDetails(1,0,2,0,3,31,10,27) ));
        //c.init(1,0,2,0,3,31,10,27);
        data.insert(pair<string,CityDetails*>("Brussels",new CityDetails(1,0,2,0,3,31,10,27)));
        //c.init(-5,0,-4,0,3,10,11,3);
        data.insert(pair<string,CityDetails*>("Montreal",new CityDetails(-5,0,-4,0,3,10,11,3)));

        //c.init(5,5,5,5,0,0,0,0);
        data.insert(pair<string,CityDetails*>("New Delhi",new CityDetails(5,30,5,30,0,0,0,0)));
       // c.init(7,0,7,0,0,0,0,0);
        data.insert(pair<string,CityDetails*>("Jakarta",new CityDetails(7,0,7,0,0,0,0,0)));
        //c.init(0,0,1,0,3,31,10,27);
        data.insert(pair<string,CityDetails*>("London",new CityDetails(0,0,1,0,3,31,10,27)));

        daysInMonth.insert(pair<int,int>(1,31));
        daysInMonth.insert(pair<int,int>(2,28));
        daysInMonth.insert(pair<int,int>(3,31));
        daysInMonth.insert(pair<int,int>(4,30));
        daysInMonth.insert(pair<int,int>(5,31));
        daysInMonth.insert(pair<int,int>(6,30));
        daysInMonth.insert(pair<int,int>(7,31));
        daysInMonth.insert(pair<int,int>(8,31));
        daysInMonth.insert(pair<int,int>(9,30));
        daysInMonth.insert(pair<int,int>(10,31));
        daysInMonth.insert(pair<int,int>(11,30));
        daysInMonth.insert(pair<int,int>(12,31));




    }
    int calculateSourceTime(CityDetails source)
    {
        int sTime = hours*60+minutes;

        if(source.dstStartMonth !=0){//if source has dst

            if(source.dstStartMonth<=month<=source.dstEndMonth)
            {
                bool validDst = false;
                if(source.dstStartMonth == month)
                {
                  if(date>= source.dstStartDate)
                  {
                      validDst =true;

                  }

                }else if(source.dstEndMonth == month)
                {
                    if(date<= source.dstEndDate)
                    {
                        validDst =true;

                    }

                }else{
                     validDst =true;
                }


                 if(validDst)
                 {
                    int dsTime = -1*(source.dstOffsetHH*60+source.dstOffsetMM);

                    sTime= sTime+dsTime;
                 }else{
                     int dsTime = -1*(source.gmtOffsetHH*60+source.gmtOffsetMM);

                     sTime= sTime+dsTime;

                 }



            }
        }else{
            int dsTime = -1*(source.gmtOffsetHH*60+source.gmtOffsetMM);

            sTime= sTime+dsTime;

        }

        Date currentDate(date,month,year);
        if(sTime < 0) {
            sTime = 1440+sTime;
            currentDate = currentDate-1;
        }else if(sTime>1440)
        {
            sTime = sTime-1440;
            currentDate =currentDate+1;
        }
        date = currentDate.day;
        month = currentDate.month;
        year = currentDate.year;


        return sTime;

    }
    int calculateDestTime(CityDetails dest, int sTime)
    {
        int desTime = sTime;

        if(dest.dstStartMonth !=0){//if source has dst

            if(dest.dstStartMonth<=month<=dest.dstEndMonth)
            {
                bool validDst = false;
                if(dest.dstStartMonth == month)
                {
                  if(date>= dest.dstStartDate)
                  {
                      validDst =true;

                  }

                }else if(dest.dstEndMonth == month)
                {
                    if(date<= dest.dstEndDate)
                    {
                        validDst =true;

                    }

                }else
                {
                    validDst =true;
                }


                 if(validDst)
                 {
                    int dsTime = (dest.dstOffsetHH*60+dest.dstOffsetMM);

                    desTime= desTime+dsTime;
                 }else{
                     int dsTime = (dest.gmtOffsetHH*60+dest.gmtOffsetMM);

                     desTime= desTime+dsTime;

                 }



            }
        }else{
            int dsTime = dest.gmtOffsetHH*60+dest.gmtOffsetMM;

            desTime= desTime+dsTime;

        }

        Date currentDate(date,month,year);
        if(desTime < 0) {
            desTime = 1440+desTime;
            currentDate = currentDate-1;
        }else if(desTime>1440)
        {
            desTime = desTime-1440;
            currentDate =currentDate+1;
        }
        date = currentDate.day;
        month = currentDate.month;
        year = currentDate.year;
        return desTime;
    }

    void convert()
    {
        CityDetails *sourceCity = data.find(source)->second;
        CityDetails *destCity = data.find(destination)->second;
        int sourceTime = calculateSourceTime(*sourceCity);
        int destTime = calculateDestTime(*destCity, sourceTime);
        Date currentDate(date, month, year);
        cout <<endl;
        cout << "***** " <<destination<< " *****"<< endl<<endl;
        cout << "Date : " << currentDate.toString() << ", Time: " << destTime/60 <<":" << destTime%60 << endl<<endl;
        cout << "***************"<< endl;
    }

    bool readInput()
    {

        while (true) {
            cout << "Enter time (HH:MM ) : ";
            getline(cin,in);
            ss.clear(); ss.str(in);
            if ((ss >> hours >> c >> minutes ) &&
                    (c == delim) &&
                    (checkTimeValidity(hours, minutes) == true)){
                delim = '/';
                cout << "Enter Date (DD/MM/YY ) : ";
                getline(cin,in);
                ss.clear(); ss.str(in);
                ss >> date >> c >> month >> c >> year;
                cout /*<<endl*/<< "Enter source city      : ";
                getline(cin,source);
                cout /*<<endl*/<< "Enter destination city : ";
                getline(cin,destination);
                if(!checkCountryValidity(source))
                {
                    cout<<"Invalid source city"<<endl;
                    return false;
                }
                if(!checkCountryValidity(destination))
                {
                    cout<<"Invalid destination city"<<endl;
                    return false;

                }
                return true;
                //process();
              //cout<<hours<<" "<<minutes<<" "<<date<<" "<<month<<" "<<year<<" "<<source<<" "<<destination<<endl;

            }
        }
        return false;
    }

};




int main(int argc, char* argv[])
{
    TimeConvertion t;
    if(t.readInput())
    {
        t.convert();
    } else {
        cout << "Invalid Input" << endl;
    }
    return 0;
}
