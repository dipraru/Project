#include <bits/stdc++.h>
#include<conio.h>
using namespace std;
typedef long long ll;
#define cls system("cls");
#define pause system("pause");

// Class to manage security interface for username and password setting and sign-in
class securityInterphase
{
    string username, password;
    int cnt;

    // Private function to set username and password
    bool setSecurity()
    {
        cout << "===============================================\n";
        cout << "------------Set Username & Password------------\n";
        int n;
        cout << "Please Set Your Username and Password.\n";
        cout << "Enter Your Username: ";
        cin >> username;
    take_pw:
        cout << "Enter Your Password: ";
        cin >> password;
        cls if (password.size() < 8)
        {
            cout << "Your password must be at least 8 characters long. Please try another.\n";
            cout << "(1) Try again\n(2) Exit Program\nChoice: ";
            cin >> n;
            cls if (n == 1) goto take_pw;
            else return 0;
        }
        ofstream security("SecurityFile.txt");
        security << 1 << endl
                 << username << endl
                 << password;
        security.close();
        cout << "Your password was set successfully. You are now signed in.\n";
        return 1;
    }

    // Private function for user sign-in    
    bool sign_in()
    {
        ifstream security("SecurityFile.txt");
        int s;
        string un, pw;
        security >> s >> un >> pw;
        security.close();
        if (s != 1)
            return setSecurity();
    sign_in:
        password.clear();
        cout << "===============================================\n";
        cout << "--------------------SIGN IN--------------------\n";
        cnt++;
        cout << "Enter Your Username: ";
        cin >> username;
        cout << "Enter Your Password: ";
        char ch;
        do {
            ch = _getch();
            if (ch != '\r') {
                if (ch == '\b' && !password.empty()) { // Handle backspace
                    cout << "\b \b";
                    password.pop_back();
                }
                else if (ch != '\b') { // Ignore backspace when password is empty
                    password.push_back(ch);
                    cout << '*';
                }
            }
        } while (ch != '\r');
        cls if (username == un && password == pw)
        {
            cout << "You are successfully signed in.\n";
            return 1;
        }
        cout << "Please check your username and password.\n";
        cout << "If you forgot the username or password, please contact to the Authority.\n";
        if (cnt % 5 == 0)
        {
            cout << "You have tried " << cnt << " times wrong attempt.\n";
            pause
                cls for (int i = cnt * 6 - 1; i >= 0; i--)
            {
                cout << "Try again in " << i << " seconds\n";
                this_thread::sleep_for(chrono::seconds(1));
                cls
            }
        }
        cout << "(1) Try again\n(2) Exit Program\nChoice: ";
        cin >> s;
        cls if (s == 1) goto sign_in;
        else return 0;
    }

    // Friend function to access the private member function sign_in    
    friend bool SignIn(securityInterphase);

public:
    securityInterphase()
    {
        username = password = "";
        cnt = 0;
    }
};

// Friend function to access the private member function sign_in
bool SignIn(securityInterphase s)
{
    return s.sign_in();
}

// Class to manage customer details
class customer
{
    string name, address, mob;
    int iday, imn, iyr, oday, omn, oyr, advance, id;

public:
    customer() {}

    // Parameterized constructor for customer details
    customer(string nm, string ad, string mo, int ida, int im, int iy, int od, int om, int oy, int adv, int id)
    {
        name = nm, address = ad, mob = mo, iday = ida, imn = im, iyr = iy;
        oday = od, omn = om, oyr = oy, advance = adv, this->id = id;
    }
    
    // Function to read customer details from user input and store them in a file
    void read_customer()
    {
        ofstream cm;
        cm.open("customers.txt", ios::app);
        cout << "Customer Details: "
             << "\n";
        cout << "Name: ";
        cin >> name;
        cout << "Address: ";
        cin >> address;
        cout << "Phone: ";
        cin >> mob;
        cout << "\nCheck-In Date: \nEnter day: ";
        cin >> iday;
        cout << "Enter Month: ";
        cin >> imn;
        cout << "Enter Year: ";
        cin >> iyr;
        cout << "\nCheck-Out Date: \nEnter day: ";
        cin >> oday;
        cout << "Enter Month: ";
        cin >> omn;
        cout << "Enter Year: ";
        cin >> oyr;
        cout << "\nAdvance Payment: ";
        cin >> advance;
        cout << "Booking ID: ";
        cin >> id;
        cm << name << "\n"
           << address << "\n"
           << mob << "\n";
        cm << iday << "\n"
           << imn << "\n"
           << iyr << "\n";
        cm << oday << "\n"
           << omn << "\n"
           << oyr << "\n";
        cm << advance << "\n"
           << id << "\n";
        cm.close();
    }
    
    // Function to display customer details
    void show_customer()
    {
        cout << "Name: " << name << "\n";
        cout << "Address: " << address << "\n";
        cout << "Mobile No: " << mob << "\n";
        cout << "Check-In Date: " << iday << '/' << imn << '/' << iyr << "\n";
        cout << "Check-Out Date: " << oday << '/' << omn << '/' << oyr << "\n";
        cout << "Advance Payement: " << advance << "\n";
        cout << "Booking ID: " << id << "\n";
    }
};

// Class to manage room details
class room
{
    int rent, room_no, type, status;

    // Friend classes and functions to access private members
    friend class roomMng;
    friend void show_room(room r);

public:
    room() {}

    // Parameterized constructor for room details
    room(int room_no, int type, int status, int rent)
    {
        this->room_no = room_no;
        this->type = type;
        this->status = status;
        this->rent = rent;
    }
    
    // Function to read room details from user input and store them in a file
    void read_room()
    {
        ifstream room;
    again:
        room.open("rooms.txt");
        cout << "Enter Room No: ";
        cin >> room_no;
        int rnt, no, t, st;
        while (room >> no >> t >> st >> rnt)
        {
            if (no == room_no)
            {
                cout << "The room already exists.\nPlease try again........\n";
                room.close();
                goto again;
            }
        }
        cout << "Room Type (Single Room = 1, Double Room = 2, Family Room = 3): ";
        cin >> type;
        cout << "Room Status (Empty Room = 0, Occupied Room = 1): ";
        cin >> status;
        cout << "Room Rent: ";
        cin >> rent;
        ofstream rooms;
        rooms.open("rooms.txt", ios::app);
        rooms << room_no << "\n"
              << type << "\n"
              << status << "\n"
              << rent << "\n";
        rooms.close();
    }
};

// Function to display room details
void show_room(room r)
{
    cout << "\nRoom No: " << r.room_no << "\n";
    cout << "Type: " << (r.type == 1 ? "Single" : (r.type == 2 ? "Double" : "Family")) << " room"
         << "\n";
    cout << "Status: " << (r.status == 0 ? "Available" : "Occupied") << "\n";
    cout << "Rent: " << r.rent << "\n";
}

// Class to manage room operations
class roomMng
{
    string name, address, mob, cs;
    int iday, imn, iyr, oday, omn, oyr, advance, id, rm_no, rnt, no, t, st, c, x, cnt;
    char ch;
    bool flag;

public:
    roomMng()
    {
        cnt = 0;
    }
    
    // Function to display details of all rooms
    void AllRoom()
    {
        cout << "===============================================\n";
        cout << "---------------LIST OF ALL ROOMS---------------\n";
        ifstream rooms, cm;
        rooms.open("rooms.txt");
        while (rooms >> no >> t >> st >> rnt)
        {
            room r(no, t, st, rnt);
            show_room(r);
            if (st)
            {
                cout << "Customer Info: "
                     << "\n";
                cm.open("customers.txt");
                while (cm >> rm_no >> name >> address >> mob >> iday >> imn >> iyr >> oday >> omn >> oyr >> advance >> id)
                {
                    if (rm_no == no)
                    {
                        customer cc(name, address, mob, iday, imn, iyr, oday, omn, oyr, advance, id);
                        cc.show_customer();
                        break;
                    }
                }
                cm.close();
            }
        }
        rooms.close();
        cout << "\n----------------END OF THE LIST----------------\n";
        cout << "===============================================\n";
    }
    
    // Function to display details of available rooms
    void AvailableRoom()
    {
        cout << "===============================================\n";
        cout << "----------LIST OF THE AVAILABLE ROOMS----------\n";
        ifstream rooms;
        rooms.open("rooms.txt");
        while (rooms >> no >> t >> st >> rnt)
        {
            if (st)
                continue;
            room r(no, t, st, rnt);
            show_room(r);
        }
        rooms.close();
        cout << "\n----------------END OF THE LIST----------------\n";
        cout << "===============================================\n";
    }
    
    // Function to add a new room and related customer details
    void Addroom()
    {
        cout << "===============================================\n";
        cout << "--------------------ADD ROOM-------------------\n";
        room r;
        r.read_room();
        if (r.status)
        {
            ofstream cm;
            cm.open("customers.txt", ios::app);
            cm << r.room_no << "\n";
            cm.close();
            customer c;
            c.read_customer();
        }
        cout << "---------THE ROOM IS ADDED SUCCESSFULLY--------\n";
        cout << "===============================================\n";
    }
    
    // Function to find a specific room and perform check-in or check-out
    void findRoom()
    {
        cout << "===============================================\n";
        cout << "------------------FIND A ROOM------------------\n";
        cout << "Enter Room No: ";
        cin >> rm_no;
        ifstream rms("rooms.txt");
        while (rms >> no >> t >> st >> rnt)
        {
            if (rm_no == no)
            {
                cout << "The room has been found.\n";
                cout << "Here the details of the room:" << endl;
                room r(no, t, st, rnt);
                show_room(r);
                rms.close();
                if (st)
                {
                    ifstream cm;
                    cout << "Customer Info: "
                         << "\n";
                    cm.open("customers.txt");
                    while (cm >> rm_no >> name >> address >> mob >> iday >> imn >> iyr >> oday >> omn >> oyr >> advance >> id)
                    {
                        if (rm_no == no)
                        {
                            customer cc(name, address, mob, iday, imn, iyr, oday, omn, oyr, advance, id);
                            cc.show_customer();
                            break;
                        }
                    }
                    cm.close();
                }
                cout << "===============================================\n";
                cout << "\nDo you want to " << (st ? "check it out" : "occupy it") << "? (y/n): ";
                cin >> cs;
                if (cs != "y")
                    cout << "Okay!!Let's go to previous page.\n";
                else
                    st ? check_out() : check_in();
                return;
            }
        }
        cout << "----------THE ROOM HAS NOT BEEN FOUND----------\n";
        cout << "===============================================\n";
    }
    
    // Function to update room details
    void UpdateRoom()
    {
        cout << "===============================================\n";
        cout << "----------------Update Room Info---------------\n";
        vector<int> info;
        vector<string> cminfo;
        ifstream rms;
    update_again:
        cout << "Enter Room No: ";
        cin >> rm_no;
        rms.open("rooms.txt");
        flag = true;
        bool mark = false;
        info.clear();
        cminfo.clear();
        while (rms >> no >> t >> st >> rnt)
        {
            if (no == rm_no)
            {
                flag = false;
                cout << "(1) Room Number\n(2) Room Type\n(3) Room Rent\nChoice: ";
                cin >> c;
                cout << "Enter New Room " << (c == 1 ? "Number" : c == 2 ? "Type (Single Room = 1, Double Room = 2, Family Room = 3)"
                                                                         : "Rent")
                     << ": ";
                cin >> x;
                if (c == 1)
                {
                    ifstream cm("customers.txt");
                    while (cm >> rm_no >> name >> address >> mob >> iday >> imn >> iyr >> oday >> omn >> oyr >> advance >> id)
                    {
                        if (rm_no == no)
                            rm_no = x, mark = true;
                        cminfo.insert(cminfo.end(), {to_string(rm_no), name, address, mob, to_string(iday), to_string(imn),
                         to_string(iyr), to_string(oday), to_string(omn), to_string(oyr), to_string(advance), to_string(id)});
                    }
                    cm.close();
                }
                c == 1 ? no = x : c == 2 ? t = x
                                         : rnt = x;
            }
            info.insert(info.end(), {no, t, st, rnt});
        }
        rms.close();
        if (flag)
        {
            cout << "The Room Doesn't Exist.\n(1) Back\n(2) Continue\nChoice: ";
            cin >> c;
            if (c == 1)
                return;
            cout << "Please Try again........\n";
            goto update_again;
        }
        ofstream rmo("rooms.txt");
        for (int i = 0; i < info.size(); i++)
            rmo << info[i] << "\n";
        rmo.close();
        if (mark)
        {
            ofstream cmm("customers.txt");
            for (int i = 0; i < cminfo.size(); i++)
                cmm << cminfo[i] << "\n";
            cmm.close();
        }
        cout << " THE INFORMATION HAS BEEN SUCCESSFULLY UPDATED.\n";
        cout << "===============================================\n";
    }
    
    // Function to remove a room and related customer details
    void RemoveRoom()
    {
        cout << "===============================================\n";
        cout << "-----------------REMOVE A ROOM-----------------\n";
        vector<int> info;
        ifstream rms;
    update_again:
        cout << "Enter Room No: ";
        cin >> rm_no;
        rms.open("rooms.txt");
        flag = true;
        info.clear();
        while (rms >> no >> t >> st >> rnt)
        {
            if (no == rm_no)
            {
                if (flag = st)
                    break;
                else
                    continue;
            }
            info.insert(info.end(), {no, t, st, rnt});
        }
        rms.close();
        if (flag)
        {
            cout << "The Room Doesn't Exist Or Already Occupied.\n(1) Back\n(2) Continue\nChoice: ";
            cin >> c;
            if (c == 1)
                return;
            cout << "Please Try again........\n";
            goto update_again;
        }
        ofstream rmo("rooms.txt");
        for (int i = 0; i < info.size(); i++)
            rmo << info[i] << "\n";
        rmo.close();
        cout << "----THE ROOM HAS BEEN SUCCESSFULLY REMOVED-----\n";
        cout << "===============================================\n";
    }
    
    // Function to perform check-in for a room
    void check_in()
    {
        cout << "===============================================\n";
        cout << "\t\tALL AVAILABLE ROOMS\n";
        ifstream rooms;
        rooms.open("rooms.txt");
        while (rooms >> no >> t >> st >> rnt)
            if (!st)
                cout << "\tRoom No: " << no << "\n", cnt++;
        rooms.close();
        if (cnt == 0)
            cout << "Sorry!! There is no available room.\n";
        cout << "===============================================\n";
        if (cnt == 0)
        {
            pause return;
        }
        vector<int> info;
    again:
        cout << "(1) Show Details\n(2) Continue....\nChoice: ";
        cin >> c;
        if (c == 1)
        {
            AvailableRoom();
            cout << "===============================================\n";
            goto again;
        }
        cout << "===============================================\n";
        cout << "--------------------CHECK IN-------------------\n";
        rooms.open("rooms.txt");
        info.clear();
        cout << "Enter the Room No: ";
        cin >> rm_no;

        flag = true;
        while (rooms >> no >> t >> st >> rnt)
        {
            if (no == rm_no)
            {
                if (flag = st)
                    break;
                cout << "\nRoom to be Checked In: ";
                room r(no, t, st, rnt);
                show_room(r);
                st = 1;
            }
            info.insert(info.end(), {no, t, st, rnt});
        }
        rooms.close();
        if (flag)
        {
            cout << "The room does not found or the room is already occupied.\n";
            rooms.close();
            cout << "(1) Back\n(2) Continue\nChoice: ";
            cin >> c;
            if (c == 1)
                return;
            cout << "Please Try again....\n";
            goto again;
        }
        ofstream rm;
        rm.open("rooms.txt");
        for (ll i = 0; i < info.size(); i++)
            rm << info[i] << "\n";
        ofstream cm;
        cm.open("customers.txt", ios::app);
        cm << rm_no << "\n";
        cm.close();
        customer cmm;
        cmm.read_customer();
        cout << "-----------------CHECK IN DONE-----------------\n";
        cout << "===============================================\n";
    }
    
    // Function to perform check-out for a room
    void check_out()
    {
        vector<string> cminfo;
        vector<int> rminfo;
        ifstream rooms;
        cout << "===============================================\n";
        cout << "-------------------CHECK OUT-------------------\n";
    chk_out:
        cminfo.clear();
        rminfo.clear();
        cout << "Enter Room No: ";
        cin >> rm_no;
        rooms.open("rooms.txt");
        flag = true;
        while (rooms >> no >> t >> st >> rnt)
        {
            if (rm_no == no)
            {
                if (flag = (st == 0))
                    break;
                cout << "\nRoom to be Checked Out:";
                room r(no, t, st, rnt);
                show_room(r);
                cout << "Customer Info: "
                     << "\n";
                ifstream cm("customers.txt");
                while (cm >> rm_no >> name >> address >> mob >> iday >> imn >> iyr >> oday >> omn >> oyr >> advance >> id)
                {
                    if (rm_no == no)
                    {
                        customer cc(name, address, mob, iday, imn, iyr, oday, omn, oyr, advance, id);
                        cc.show_customer();
                    }
                    else
                        cminfo.insert(cminfo.end(), {to_string(rm_no), name, address, mob, to_string(iday), to_string(imn),
                        to_string(iyr), to_string(oday), to_string(omn), to_string(oyr), to_string(advance), to_string(id)});
                }
                cm.close();
                st = 0;
            }
            rminfo.insert(rminfo.end(), {no, t, st, rnt});
        }
        rooms.close();
        if (flag)
        {
            cout << "The Room does not Exist or Unoccupied\n";
            cout << "(1) Back\n(2) Continue\nChoice: ";
            cin >> c;
            if (c == 1)
                return;
            cout << "Please Try again....\n";
            goto chk_out;
        }
        cout << "Are you confirm to check out (y/n): ";
        cin >> ch;
        if (ch == 'n')
        {
            cout << "Okay\n(1) Back to previous page\n(2) Continue\nChoice: ";
            cin >> c;
            if (c == 1)
                return;
            else
                goto chk_out;
        }
        ofstream cmr("customers.txt");
        for (ll i = 0; i < cminfo.size(); i++)
            cmr << cminfo[i] << "\n";
        cmr.close();
        ofstream rms("rooms.txt");
        for (ll i = 0; i < rminfo.size(); i++)
            rms << rminfo[i] << "\n";
        rms.close();
        cout << "Please take the bill from the guest before his/her leaving.\n\n";
        cout << "-----------------CHECK OUT DONE----------------\n";
        cout << "===============================================\n";
    }
    
    //Destructor to show the exit message
    ~roomMng()
    {
        cout << "\t\t  Have a Nice Day.\n";
        cout << "------------------Thanks for Using---------------\n";
        cout << "=================================================\n\n";
        pause
    }
};

// Function to display menu choices
int choices()
{
    char c = 3;
    cout << "============" << c << " Welcome to U&Me Hotel " << c << "============\n|\t\t\t\t\t\t|\n";
    cout << "|\t\t(1) Show all rooms\t\t|\n";
    cout << "|\t\t(2) Show available rooms\t|\n";
    cout << "|\t\t(3) Add a room\t\t\t|\n";
    cout << "|\t\t(4) Update room information\t|\n";
    cout << "|\t\t(5) Remove a room\t\t|\n";
    cout << "|\t\t(6) Find a room\t\t\t|\n";
    cout << "|\t\t(7) Check-in\t\t\t|\n";
    cout << "|\t\t(8) Check-out\t\t\t|\n";
    cout << "|\t\t(9) Exit\t\t\t|\n|\t\t\t\t\t\t|\n";
    cout << "=================================================\n";   
    int a;
    cout << "\t\tCHOICE: ";
    cin >> a;
    cls return a;
}

int main()
{
    cout << "\033[45m";
    cls;
    cout << "Make sure that the files named \"SecurityFile.txt\", ";
    cout << "\"customers.txt\" and \"rooms.txt\" are in your folder.\n";
    pause cls

    securityInterphase s;
    if (!SignIn(s))
    {
        cout << "Your attempts are expired. Contact Authority.\n";
        pause return 0;
    }
    pause

    roomMng r;
main_menu:
    cls switch (choices())
    {
    case 1:
        r.AllRoom();
        pause goto main_menu;
        break;
    case 2:
        r.AvailableRoom();
        pause goto main_menu;
        break;
    case 3:
        r.Addroom();
        system("pause");
        goto main_menu;
        break;
    case 4:
        r.UpdateRoom();
        pause;
        goto main_menu;
        break;
    case 5:
        r.RemoveRoom();
        pause;
        goto main_menu;
        break;
    case 6:
        r.findRoom();
        pause;
        goto main_menu;
        break;
    case 7:
        r.check_in();
        pause goto main_menu;
        break;
    case 8:
        r.check_out();
        pause goto main_menu;
        break;
    default:
        return 0;
        break;
    };
}