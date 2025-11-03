// COMSC 210 | Lab 28 | Annie Morales
// IDE used: Visual Studio Code

// Eight additional STL algorithms

#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include "Goat.h"
#include <algorithm>
#include <numeric>
#include <random>
#include <cstdlib>
#include <ctime>
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
int main_menu();
//void unique_goats(list<Goat> &trip);
void sorting_goats(list<Goat> &trip); // 1st addition
void reverse_goats(list<Goat> &trip); // 2nd addition
void clear_goats(list<Goat> trip); // 3rd addition
void shuffle_goats(list<Goat> &trip); // 4th addition
void find_goat(list<Goat> &trip); // 5th addition

int main() {
    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    // create & populate a trip of Goats using std::list of random size 8-15
    int tripSize = rand() % 8 + 8;
    list<Goat> trip; // List of goats on the trip.
    int age;
    string name, color;
    for (int i = 0; i < tripSize; i++) {
        age = rand() % MAX_AGE;  // defined in Goat.h
        name = names[rand() % SZ_NAMES];
        color = colors[rand() % SZ_COLORS];
        Goat tmp(name, age, color);
        trip.push_back(tmp);
    }
    
    // Goat Manager 3001 Engine
    int sel = main_menu();
    while (sel != 8) {
        switch (sel) {
            case 1:
                cout << "Adding a goat...\n";
                add_goat(trip, names, colors);
                break;
            case 2:    
                cout << "Removing a goat...\n";
                delete_goat(trip);
                break;
            case 3:    
                cout << "Displaying goat data...\n";
                display_trip(trip);
                break;
            case 4:
                cout << "Sorting goats by name...\n";
                sorting_goats(trip);
                break;
            case 5:
                cout << "Reversing order of goats...\n";
                reverse_goats(trip);
                break;
            case 6:
                cout << "Clearing list of goats...\n";
                clear_goats(trip);
                break;
            case 7:
                cout << "Shuffling goats...\n";
                shuffle_goats(trip);
                break;
            case 8:
                cout << "Finding a goat...\n";
                find_goat(trip);
                break;
            default:
                cout << "Invalid selection.\n";
                break;
        }
        sel = main_menu();
    }
    return 0;
}

int main_menu() {
    cout << endl << "*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] Sort goats by name\n"; // Addition 1
    cout << "[5] Reverse order of goats\n"; // Addition 2 
    cout << "[6] Clear list of goats.\n"; // Addition 3
    cout << "[7] Shuffle goats.\n"; // Addition 4
    cout << "[8] Find a goat.\n"; // Addition 5
    cout << "[8] Quit\n";
    cout << "Choice --> ";
    int choice;
    cin >> choice; cout << endl;
    while (choice < 1 || choice > 8) {
        cout << "Invalid, again --> ";
        cin >> choice;
    }
    return choice;
}

// sorting_goats sorts the names of goats alphabetically.
// arguments: list of goats on the trip.
// returns: nothing.
void sorting_goats(list<Goat> &trip){ // Milestone 1
    list<Goat> goats_sorted(trip);
    // sort the copy by goat name
    goats_sorted.sort([](const Goat &a, const Goat &b){
        return a.get_name() < b.get_name();
    });
    int i = 1;
    cout << "Goats have been sorted alphabetically by name." << endl;
    for (const Goat &g : goats_sorted)
        cout << "\t" << "[" << i++ << "] " << g.get_name() << " (" << g.get_age() << ", " << g.get_color() << ")\n";
}

// reverse_goats reverses the order of goats in the list.
// arguments: list of goats on the trip.
// returns: nothing.
void reverse_goats(list<Goat> &trip){ // Milestone 2
    list<Goat> goats_reversed(trip);
    // reversing list of goats
    reverse(trip.begin(), trip.end());
    cout << "Goats in reverse order:\n";
    display_trip(trip);
}

// clear_goats removes all the goats from the list.
// arguments: list of goats.
// returns: nothing.
void clear_goats(list<Goat> trip){ // Milestone 3
    cout << "Size before clearing list of goats: " << trip.size() << endl;
    trip.clear();
    cout << "Goats have been cleared from the list. Size now: " << trip.size() << endl;
}

// shuffle_goat shuffles the goats in the list.
// arguments: list of goats.
// returns: nothing.
void shuffle_goats(list<Goat> &trip){ // Milestone 4
    vector<Goat> vec_goats(trip.begin(), trip.end());
    shuffle(vec_goats.begin(), vec_goats.end(), default_random_engine(time(0)));
    trip.assign(vec_goats.begin(), vec_goats.end());
    cout << "Goats have been shuffled." << endl;
    display_trip(trip);
}

// find_ goat will find a goat.
// arguments: list of goats.
// returns: nothing.
void find_goat(list<Goat> &trip){
    string name;
    cout << "Enter the name of the goat you're looking for: "; cin >> name; 
    cout << "Finding" << name << "...";
    auto it = find(trip.begin(), trip.end(), [&](const Goat& g){ return g.get_name() == name; });
    if (it != trip.end())
        cout << it->get_name() << "has been found." << endl;
    else
        cout << it->get_name() << " has not been found.";
}

/*
void unique_goats(list<Goat> &trip){
    trip.unique();
}
*/

void delete_goat(list<Goat> &trip) {
    cout << "DELETE A GOAT\n";
    int index = select_goat(trip);
    auto it = trip.begin();
    advance(it, index-1);
    trip.erase(it);
    cout << "Goat deleted. New trip size: " << trip.size() << endl;
}

void add_goat(list<Goat> &trip, string nms[], string cls[]) {
    cout << "ADD A GOAT\n";
    int age = rand() % MAX_AGE;
    string nm = nms[rand() % SZ_NAMES];
    string cl = cls[rand() % SZ_COLORS];
    Goat tmp(nm, age, cl);
    trip.push_back(tmp);
    cout << "Goat added. New trip size: " << trip.size() << endl;
}

void display_trip(list<Goat> trp) {
    int i = 1;
    for (auto gt: trp)
        cout << "\t" 
             << "[" << i++ << "] "
             << gt.get_name() 
             << " (" << gt.get_age() 
             << ", " << gt.get_color() << ")\n";
}

int select_goat(list<Goat> trp) {
    int input;
    cout << "Make a selection:\n";
    display_trip(trp);
    cout << "Choice --> ";
    cin >> input;
    while (input < 1 || input > trp.size()) {
        cout << "Invalid choice, again --> ";
        cin >> input;
    }
    return input;
}