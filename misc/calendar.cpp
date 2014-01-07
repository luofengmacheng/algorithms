/*
 * author:	luo feng
 * date:	2013/11/1
 * source:	Programming Pearls
 * title:	calendar
 * language:	C++
 */

#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

const int NO_CHOOSE = -1;
const int QUIT = 0;
const int DAY_DATE = 1;
const int DATE_DAY = 2;
const int CURRENT_DATE = 3;

class Calendar {
private:
    vector<unsigned int> *days;

public:
    Calendar()
    {
        unsigned int days_arr[24] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31,
                            31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        days = new vector<unsigned int>(days_arr, days_arr+24);
    }

    ~Calendar()
    {
        delete days;
    }

    bool leap_year(unsigned int year)
    {
        if(!(year % 4) && (year % 100) || !(year % 400))
            return true;
        else
            return false;
    }

    void day_to_date(unsigned int year, unsigned int day)
    {
        unsigned long i = 0;
        unsigned int day_temp = day;

        if(leap_year(year)) {
            i = 0;
            if(day > 366)
                day %= 366;
        }
        else {
            i = 12;
            if(day > 365)
                day %= 365;
        }

        unsigned long j = 0;
        unsigned int  month = 0, cur_day = 0;
        for(j = i; j < i + 12; ++j) {
            if(day > (*days)[j]) {
                day -= (*days)[j];
            }
            else {
                month = (j > 11) ? (j % 12 + 1) : j + 1;
                cur_day = day;
                break;
            }
        }

        cout<<"the "<<day_temp<<" of "<<year<<":"<<endl;
        cout<<year<<"年"<<month<<"月"<<cur_day<<"日"<<endl;
    }

    void date_to_day(unsigned int year, unsigned int month, unsigned int daytime)
    {
        unsigned long i = 0;
        unsigned int month_temp = month;
        unsigned int daytime_temp = daytime;

        if(leap_year(year)) {
            i = 0;
        }
        else {
            i = 12;
        }

        unsigned long j = 0;
        unsigned int day = 0;
        for(j = i; j < i + month_temp - 1; ++j) {
            day += (*days)[j];
        }
        day += daytime;

        cout<<year<<"年"<<month<<"月"<<daytime<<"日:"<<endl;
        cout<<day<<" of "<<year<<endl;
    }

    void show_current_date()
    {
        time_t now_time;

        time(&now_time);
        struct tm time_struct = *localtime(&now_time);
        cout<<"current time:";
        cout<<1900+time_struct.tm_year<<"年"<<1+time_struct.tm_mon<<"月"<<time_struct.tm_mday<<"日 ";
        cout<<"星期"<<time_struct.tm_wday<<" ";
        cout<<time_struct.tm_hour<<":"<<time_struct.tm_min<<":"<<time_struct.tm_sec<<endl;
    }

    void show_menu()
    {
        int op = NO_CHOOSE;
        unsigned int year = 0, month = 0, day = 0;

        cout<<"Welcome to Calendar!"<<endl;
        while(true) {
            cout<<"select operation you want:"<<endl;
            cout<<"0: quit"<<endl;
            cout<<"1: give year and day, print year, date"<<endl;
            cout<<"2: give year and date, print year day"<<endl;
            cout<<"3: show current date and time"<<endl;
            cin>>op;
            switch(op) {
            case QUIT:
                break;
            case DAY_DATE:
                cout<<"year:";
                cin>>year;
                cout<<"day:";
                cin>>day;
                day_to_date(year, day);
                cout<<endl;
                break;
            case DATE_DAY:
                cout<<"year:";
                cin>>year;
                cout<<"month:";
                cin>>month;
                cout<<"daytime:";
                cin>>day;
                date_to_day(year, month, day);
                cout<<endl;
                break;
            case CURRENT_DATE:
                show_current_date();
                cout<<endl;
                break;
            default:
                cout<<"invalid operation"<<endl;
                cout<<endl;
                break;
            }
            if(op == QUIT)
                break;
        }

        cout<<"Bye bye!"<<endl;
    }
};

int main(int argc, char *argv[])
{
    Calendar cal;
    cal.show_menu();

    return 0;
}
