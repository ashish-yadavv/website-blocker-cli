#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

//Remember: Before running this code you must take the backup of your hosts files

int addSite(int argc, char *argv[]) {
    if (argc < 3) {
        cout<<"Enter the Domain to be blocked!";
        return 1;
    }

    string domain=argv[2];
    string t1="127.0.0.1 " + domain + " #BLOCKED_BY_BLOCKER"; //using these tags to identify what I added
    string t2="127.0.0.1 www." + domain + " #BLOCKED_BY_BLOCKER";

    fstream file;
    file.open("/etc/hosts", ios::in);
    if (!file.is_open()) { //Opening a file may fail to open due to any reasons that's why we are checking like this
        cout<<"Failed to block the Site because Could not access hosts file.";
        return 1;
    }

    string line;
    while (getline(file, line)) {
        if (line == t1 || line == t2) {
            cout<<"Already Blocked!";
            file.close();
            return 1; //Returning 1 because this is not what user wanted
        }
    }
    file.close();

    file.open("/etc/hosts", ios::app);
    if (!file.is_open()) {
        cout<<"Failed to block the site becuase Could not access hosts file.";
        return 1;
    }

    file<< "\n" <<t1<< "\n";
    file<<t2<< "\n";
    cout<<"Site Added to Block List...";
    file.close();

    system("dscacheutil -flushcache"); //Clears saved website address memory so Mac checks the updated hosts file again
    system("killall -HUP mDNSResponder"); //Restarts the Mac’s DNS service so the new blocking changes start working immediately

    return 0;
}

int removeSite(int argc, char *argv[]) {
    if(argc < 3) {
        cout<<"Enter the Domain to be blocked!";
        return 1;
    }

    string domain=argv[2];
    string t1="127.0.0.1 " + domain + " #BLOCKED_BY_BLOCKER";
    string t2 = "127.0.0.1 www." + domain + " #BLOCKED_BY_BLOCKER";
    bool contains=false;

    fstream file;
    file.open("/etc/hosts", ios::in);
    if (!file.is_open()) {
        cout<<"Error: Could not access hosts file.";
        return 1;
    }

    string line;
    while (getline(file, line)) {
        if (line == t1 || line == t2) {
            contains=true;
            break;
        }
    }
    file.close();

    if (!contains) {
        cout<<"Domain not found!";
        return 1;
    }

    vector<string> fileLines; //Vector Buffer it is
    file.open("/etc/hosts", ios::in);
    if (!file.is_open()) {
        cout<<"Error: Could not access hosts file.";
        return 1;
    }

    while (getline(file, line)) {
        if (line != t1 && line != t2){
            fileLines.push_back(line);
        }
    }
    file.close();

    file.open("/etc/hosts", ios::out);
    if (!file.is_open()) {
        cout << "Error: Could not access hosts files";
        return 1;
    }

    for (const string &i : fileLines) //faster than normal loop
        file << i << endl;

    cout<<"Site Removed Successfully!";
    file.close();

    system("dscacheutil -flushcache");
    system("killall -HUP mDNSResponder");

    return 0;
}

int listSites() {
    fstream file;
    file.open("/etc/hosts", ios::in);
    if (!file.is_open()) {
        cout<<"Error: Could not access hosts file.";
        return 1;
    }

    string line;
    while (getline(file, line))
        cout << line << endl;

    file.close();
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cout<<"Complete the Command...";
        return 1;
    }

    string command = argv[1];

    if (command == "add")
        return addSite(argc, argv);
    else if (command == "remove")
        return removeSite(argc, argv);
    else if (command == "list")
        return listSites();
    else {
        cout<<"Incorrect Command!";
        return 1;
    }

    return 0; 
}