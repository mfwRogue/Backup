#include <string>
#include <chrono>
#include <iostream>
#include <fstream>
#include <filesystem>
using namespace std;

ofstream root;
string backupdir = R"(C:\Games\BACKUP\)";
string rootdir = backupdir + "gamelocations.txt";
string backuploc;


string searchGames(string name){
    ifstream root;
    root.open(rootdir);
    size_t pos;
    string line;
    int count = 1;
    if(root.is_open()){
        while(getline(root, line)){
            pos = line.find(name);
            if(pos!=string::npos){
                return line; 
            }
            count++;
        }
    }
    root.close();
    return "";
}

void addGame(){
    string input;
    string game;
    cout << "Enter the name of the game: ";
    cin >> input;
    cout << searchGames(input).size();
    if(searchGames(input).size() < 1){
        game = input + "{";
        cout << "Enter game save folder you want backed up: ";
        cin.ignore();
        getline(cin, input);
        game += input + "}\n";
        root << game;
    } else { 
        cout << "Game already exists with path: ";
    }

}
void editGame(){  
}


void zipUp(string saveloc){
    time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now());
    tm utc_tm = *gmtime(&tt);

    string date = to_string(utc_tm.tm_mon + 1) + "-" + to_string(utc_tm.tm_mday) + "-" + to_string(utc_tm.tm_year + 1900) 
                + "-" + to_string(utc_tm.tm_hour-5) + "h" + to_string(utc_tm.tm_min) + "m" + to_string(utc_tm.tm_sec) + "s";
    

    //change to use tar command
    string cmd = "cd " + saveloc + " & 7z a " + date + ".zip";
    cmd += " & move \"" + date + ".zip\" " + backuploc;
    system(cmd.c_str());
}

int main(){
    cout << searchGames("Wonderlands") << endl;
    
    string appRoot = R"()";
    
    if(!filesystem::exists(backupdir + "gamelocations.txt")) {
        root.open(backupdir + "gamelocations.txt");
    } else {
        root.open(backupdir + "gamelocations.txt", ios::app);
    }
    
    char userOption;
    cout << "0. Add/Edit Game" << endl << "-. Go to previous page" << endl << "+. Go to next page" << endl << "Select an option: ";
    cin >> userOption;
    switch(userOption){
        case '0':
            addGame();
        break;

        case '-':

        break;

        case '+':

        break;
    }

    // zipUp(backupdir);
    root.close();
}



