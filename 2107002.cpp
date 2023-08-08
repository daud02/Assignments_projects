#include <ctime>
#include <iostream>
using namespace std;

bool isLeapYear(int year);     //these four function is working for showing calender. These functions don't depend on class.
int getDayOfWeek(int year, int month, int day);
int getNumberOfDaysInMonth(int year, int month);
void printCalendar(int year, int month, int startDay);

class to_do;       // These four class are used in this project;
class date;
class event;
class target;

void show_calender(to_do);         //these five functions are used as friend function in class.
void show_event(date A,event events[]);
void show_task(date A,to_do task[]);
void show_target(int year, target targets[]);
void add_target(int year,string name,target targets[] );

int task_co=0;       // these int variables are used to count objects of any class stored.
int event_co=0;
int target_co=0;
class date
{
    int day;
    int month;
    int year;
public:
    date() {}
    date (int day, int month, int year)
    {
        this->day=day;
        this->month=month;
        this->year=year;
    }
    friend  to_do;
    friend event;
    friend void show_task(date A,to_do task[]);
    friend void printCalendar(int year, int month, int startDay,to_do task[],event events[]);
    bool operator == (date A)
    {
        return (A.day==day&&A.month==month&&A.year==year);
    }
    void display(void)
    {
        cout<<day<<"/"<<month<<"/"<<year<<" ";
    }
};

class to_do
{
    date tdate;
    bool status;
    string work;
public:
    to_do()
    {
        status=0;
    }
    to_do(date A,string s)
    {
        status=1;
        tdate=A;
        work=s;
    }
    friend void show_task(date A,to_do task[]);
    friend void printCalendar(int year, int month, int startDay,to_do task[],event events[]);
    void display(void)
    {
        tdate.display();
        cout<<work<<"\n";
    }
};

class event
{
    date tdate;
    string s;
public:
    event() {}
    event(date A,string s)
    {
        tdate=A;
        this->s=s;
    }
    friend void show_event(date A,event events[]);
    friend void printCalendar(int year, int month, int startDay,to_do task[],event events[]);
};

class target
{
    int year;
    string name;
public:
    target() {}
    target(int year, string name)
    {
        this->year=year;
        this->name=name;
    }
    void show_target(void)
    {
        cout<<year <<"-> "<<name<<"\n";
    }
    friend void show_target(int year, target targets[]);
};


void add_event(date A,string s,event events[])
{
    event_co++;
    event tem(A,s);
    events[event_co]=tem;
}

void add_task(date A, string s,to_do task[])
{
    task_co++;
    to_do tem(A,s);
    task[task_co]=tem;
}

bool isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int getDayOfWeek(int year, int month, int day)
{
    if (month < 3)
    {
        month += 12;
        year--;
    }
    int century = year / 100;
    int yearInCentury = year % 100;
    int dayOfWeek = (day + 13 * (month + 1) / 5 + yearInCentury + yearInCentury / 4 + century / 4 - 2 * century) % 7;
    return (dayOfWeek + 5) % 7; // To convert 0 (Saturday) to 6 (Friday)
}

int getNumberOfDaysInMonth(int year, int month)
{
    if (month == 2)
    {
        return isLeapYear(year) ? 29 : 28;
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        return 30;
    }
    else
    {
        return 31;
    }
}

void printCalendar(int year, int month, int startDay,to_do task[],event events[])
{
    const string weekdays[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    int daysInMonth = getNumberOfDaysInMonth(year, month);

    // Print the header
    cout << "----------------------------------------------------\n";
    cout << "                   " << month << "/" << year << "\n";
    cout << "-----------------------------------------------------\n";
    for (const string& day : weekdays)
    {
        cout << day << "   ";
    }
    cout << "\n-----------------------------------------------------\n";

    // Print the days
    int currentDay = 1;
    for (int i = 0; i < startDay; ++i)
    {
        cout << "      ";
    }
    for (int i = startDay; i < 7; ++i)
    {
        if (currentDay <= daysInMonth)
        {
            int co=0;
            bool coo=0;
            date A(currentDay,month,year);
            for(int i=1; i<=event_co; i++)
            {
                if(events[i].tdate==A)coo=1;
            }
            for(int i=1; i<=task_co; i++)
            {
                if(task[i].tdate==A)co++;
            }
            printf("%3d", currentDay);
            if(coo)cout<<"*";
            else cout<<" ";
            if(co)cout<<"<"<<co;
            else cout<<"  ";
        }
        else
        {
            cout << "        ";
        }
        currentDay++;
    }
    cout << endl;
    while (currentDay <= daysInMonth)
    {
        for (int i = 0; i < 7; ++i)
        {
            if (currentDay <= daysInMonth)
            {
                int co=0;
                bool coo=0;
                date A(currentDay,month,year);
                for(int i=1; i<=event_co; i++)
                {
                    if(events[i].tdate==A)coo=1;
                }
                for(int i=1; i<=task_co; i++)
                {
                    if(task[i].tdate==A)co++;
                }
                printf("%3d", currentDay);
                if(coo)cout<<"*";
                else cout<<" ";
                if(co)cout<<"<"<<co;
                else cout<<"  ";
            }
            else
            {
                cout << "        ";
            }
            currentDay++;
        }
        cout << endl;
    }
}

void show_calender(to_do task[],event events[])
{
    int year, month;

    cout << "Enter the month (1-12): ";
    cin >> month;

    cout << "Enter the year: ";
    cin >> year;

    if (month < 1 || month > 12)
    {
        cout << "Invalid month! Please enter a month between 1 and 12.\n";
        return ;
    }

    if (year < 1)
    {
        cout << "Invalid year! Please enter a valid year.\n";
        return ;
    }

    int startDay = getDayOfWeek(year, month, 1);
    printCalendar(year, month, startDay,task,events);
    cout<<"Here * for events and < for number of tasks.\n";
    return ;
}

void show_event(date A,event events[])
{
    for(int i=1; i<=event_co; i++)
    {
        if(A==events[i].tdate)
        {
            cout<<events[i].s<<"\n";
            return ;
        }
    }
    cout<<"NO event.\n";
}

void show_task(date A,to_do task[])
{
    int ans=0;
    for(int i=1; i<=task_co; i++)
    {
        if(A.month==task[i].tdate.month&&A.year==task[i].tdate.year&&(A.day<=task[i].tdate.day))   ///////
        {
            ans++;
            task[i].tdate.display();
            cout<<"->"<<task[i].work<<"\n";
        }
    }
    if(!ans)cout<<"No task.\n";
}
void show_target(int year, target targets[])
{
    int co=0;
    for(int i=1; i<=target_co; i++)
    {
        if(year>=targets[i].year)
        {
            co++;
            targets[i].show_target();
        }
    }
    if(!co)
    {
        cout<<"You have no goal within "<<year<<"\n";
    }
}
void add_target(int year,string name,target targets[] )
{
    target_co++;
    target tem(year,name);
    targets[target_co]=tem;
}

int main()
{
    to_do task[1000];
    event events[1000];
    target targets[1000];
    /*date a(5, 8, 2023);
     add_task(a,"do it",task);
    add_event(a,"jatiyo shok dibosh",events);
    task[task_co].display();
    show_event(a,events);
    show_task(a,task);
    */
    cout<<"Select any option(1-6)\n";
    cout<<"1-> show calender\n";
    cout<<"2-> add event\n";
    cout<<"3-> add task\n";
    cout<<"4-> show event\n";
    cout<<"5-> show task\n";
    cout<<"6-> set goad\n";
    cout<<"7-> show goal\n";
    cout<<"8-> exit\n";
    int k;
    while(cin>>k,k!=8)
    {
        if(k==1)
        {
            show_calender(task,events);
        }
        else if (k==2)
        {
            string ss="yes";
            while(ss=="yes")
            {
                int day,month,year;
                cout<<"enter day month year(space separated)\n";
                cin>>day>>month>>year;
                date tem(day,month,year);
                cout<<"enter the name of the event(in one line)\n";
                string s;
                fflush(stdin);
                getline(cin,s);
                add_event(tem,s,events);
                cout<<"Do you want to add more event? (yes/no)\n";
                fflush(stdin);
                cin>>ss;
            }
        }
        else if (k==3)
        {
            string ss="yes";
            while(ss=="yes")
            {
                int day,month,year;
                cout<<"enter(deadline of the task) day month year(space separated)\n";
                cin>>day>>month>>year;
                date tem(day,month,year);
                fflush(stdin);
                cout<<"enter details of the task(in one line)\n";
                string s;
                getline(cin,s);
                add_task(tem,s,task);
                cout<<"Do you want to add more task? (yes/no)\n";
                fflush(stdin);
                cin>>ss;
            }
        }
        else if (k==4)
        {
            string ss="yes";
            while(ss=="yes")
            {
                int day,month,year;
                cout<<"enter day month year(space separated)\n";
                cin>>day>>month>>year;
                date tem(day,month,year);
                show_event(tem,events);
                cout<<"Do you want to see more event? (yes/no)\n";
                fflush(stdin);
                cin>>ss;
            }
        }
        else if (k==5)
        {
            string ss="yes";
            while(ss=="yes")
            {
                int day,month,year;
                cout<<"enter day month year(space separated)\n";
                cin>>day>>month>>year;
                date tem(day,month,year);
                show_task(tem,task);
                cout<<"Do you want to see more task? (yes/no)\n";
                fflush(stdin);
                cin>>ss;
            }
        }
        else if (k==6)
        {
            string ss="yes";
            while(ss=="yes")
            {
                cout<<"enter year \n";
                int year;
                cin>>year;
                cout<<"what is your goal in "<<year<<"?\n";
                fflush(stdin);
                string s;
                getline(cin,s);
                add_target(year,s,targets);
                cout<<"Do you want to set more goal? (yes/no)\n";
                fflush(stdin);
                cin>>ss;
            }
        }
        else if (k==7)
        {
            string ss="yes";
            while(ss=="yes")
            {
                cout<<"enter a year\n";
                int year;
                cin>>year;
                show_target(year,targets);
                cout<<"Do you want to see more goal? (yes/no)\n";
                fflush(stdin);
                cin>>ss;
            }
        }
        else
        {
            cout<<"wrong input\n";
        }
        cout<<"Select any option(1-6)\n";
        cout<<"1-> show calender\n";
        cout<<"2-> add event\n";
        cout<<"3-> add task\n";
        cout<<"4-> show event\n";
        cout<<"5-> show task\n";
        cout<<"6-> set goad\n";
        cout<<"7-> show goal\n";
        cout<<"8-> exit\n";
    }
    cout<<"Thank you!\n";
    return 0;
}
