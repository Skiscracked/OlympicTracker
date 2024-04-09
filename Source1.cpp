// main
#include "olympic.h"

int main(void) {
    // linked olympic lists
    olympics sprinters_olympics;
    olympics soccer_players_olympics;

    cout << "Welcome to the Olympic Athlete Tracker!" << endl;

    while (true) {
        char menu;
        // print menu
        cout << endl << "-------------------MENU-------------------" << endl;
        cout << "Select from the following options:" << endl;
        cout << "a - add athletes" << endl;
        cout << "r - retrieve an athlete's information" << endl;
        cout << "b - display all athletes" << endl;
        cout << "s - sort athletes" << endl;
        cout << "d - remove a specific athlete" << endl;
        cout << "c - count the number of athletes" << endl;
        cout << "o - clear records" << endl;
        cout << "e - exit" << endl;
        cout << "------------------------------------------" << endl;
        cin >> menu;

        /*------------------------ADD-----------------------*/
        if (menu == 'a' || menu == 'A') { // if menu selection is to add athlete
            while (1) {
                char kind = getAthleteType();
                if (kind == 'p' || kind == 'P') { // if athlete to add is a sprinter
                    sprinter* new_sprinter = new sprinter; //****not sure**** 
                    new_sprinter->read(cin);
                    sprinters_olympics.push_back(new_sprinter); // store pointer to object in linked olympics
                    break;
                }
                else if (kind == 'k' || kind == 'K') { // if athlete to add is a soccer player
                    soccer_player* new_soccer_player = new soccer_player;
                    new_soccer_player->read(cin);
                    soccer_players_olympics.push_back(new_soccer_player); // store pointer to object in linked olympics
                    break;
                }
                else if (kind == 'e') {
                    break;
                }
                else {
                    cout << "Invalid selection" << endl;
                }
            }
        }
        /*------------------------RETRIEVE-----------------------*/
        else if (menu == 'r' || menu == 'R') { // if menu selection is to retrieve an athlete
            if (sprinters_olympics.empty() && soccer_players_olympics.empty()) {
                cout << "There are no athletes in the olympics" << endl;
            }
            else {
                int x;
                athlete* start = nullptr;
                cout << endl << "Enter the ID of the athlete you would like to retrieve: ";
                cin >> x;
                if (sprinters_olympics.sprinter_retrieve(x)) {
                    continue;
                }
                else if (soccer_players_olympics.soccer_player_retrieve(x)) {
                    continue;
                }
                else {
                    cout << "Athlete not found" << endl;
                }
            }
        }
        /*------------------------DISPLAY-----------------------*/
        else if (menu == 'b' || menu == 'B') { // if menu selection is to display Olympics
            if (sprinters_olympics.empty() && soccer_players_olympics.empty()) {
                cout << "There are no athletes in the Olympics" << endl;
            }
            else {
                cout << endl << "Sprinters: " << endl;
                if (sprinters_olympics.empty()) {
                    cout << "There are no sprinters in the Olympics" << endl;
                }
                else {
                    sprinters_olympics.sprinter_write(cout);
                }
                cout << endl << "Soccer Players: " << endl;
                if (soccer_players_olympics.empty()) {
                    cout << "There are no soccer players in the Olympics" << endl;
                }
                else {
                    soccer_players_olympics.soccer_write(cout);
                }
            }
        }

        /*------------------------SORT-----------------------*/
        else if (menu == 's' || menu == 'S') { // if menu selection is to sort
            if (sprinters_olympics.empty() && soccer_players_olympics.empty()) {
                cout << "There are no athletes in the olympics" << endl;
            }
            else {
                char type = getAthleteType();

                if (type == 'p' || type == 'P') { // if type of athletes to sort is sprinters
                    if (sprinters_olympics.empty()) {
                        cout << endl << "There are no sprinters in the olympics" << endl;
                    }
                    else {
                        char sort = sortSprinter();
                        if (sort == 'd') { // if sorting sprinters by distance
                            sprinters_olympics.sort_distance();
                        }
                        else if (sort == 't') { // if sorting sprinters by record time
                            sprinters_olympics.sort_time();
                        }
                        else {
                            cout << "Invalid selection" << endl;
                        }
                    }
                }
                else if (type == 'k' || type == 'K') { // if type of athletes to sort is soccer players
                    if (soccer_players_olympics.empty()) {
                        cout << endl << "There are no soccer players in the olympics" << endl;
                    }
                    else {
                        char sort = sortSoccer();
                        if (sort == 'g' || sort == 'G') { // if sorting soccer players by goals
                            soccer_players_olympics.sort_goals();
                        }
                        else if (sort == 'p' || sort == 'P') { // if sorting soccer players by penalties
                            soccer_players_olympics.sort_penalties();
                        }
                        else {
                            cout << "Invalid selection" << endl;
                        }
                    }
                }
                else {
                    cout << "Invalid selection" << endl;
                }
            }
        }
        /*------------------------DELETE-----------------------*/
        else if (menu == 'd' || menu == 'D') { // if menu selection is to remove an athlete
            if (sprinters_olympics.empty() && soccer_players_olympics.empty()) {
                cout << "There are no athletes in the olympics" << endl;
            }
            else {
                int x;
                cout << endl << "Enter the ID of the athlete you would like to remove: ";
                cin >> x;
                if (sprinters_olympics.remove(x)) {
                    cout << "Athlete removed" << endl;
                }
                else if (soccer_players_olympics.remove(x)) {
                    cout << "Athlete removed" << endl;
                }
                else {
                    cout << "Athlete not found" << endl;
                }
            }
        }
        /*------------------------COUNT-----------------------*/
        else if (menu == 'c' || menu == 'C') { // if menu selection is to count
            int totalAthletes = sprinters_olympics.size() + soccer_players_olympics.size();
            cout << endl << "There are " << totalAthletes << " total athletes in the Olympics." << endl;

            if (sprinters_olympics.size() == 1 && soccer_players_olympics.size() == 0) {
                cout << "There is " << sprinters_olympics.size() << " sprinter." << endl;
            }
            else if (sprinters_olympics.size() == 0 && soccer_players_olympics.size() == 1) {
                cout << "There is " << soccer_players_olympics.size() << " soccer player." << endl;
            }
            else if (sprinters_olympics.size() == 1 && soccer_players_olympics.size() == 1) {
                cout << "There is " << sprinters_olympics.size() << " sprinter and " << soccer_players_olympics.size() << " soccer player." << endl;
            }
            else if (sprinters_olympics.size() > 1 && soccer_players_olympics.size() == 0) {
                cout << "There are " << sprinters_olympics.size() << " sprinters." << endl;
            }
            else if (sprinters_olympics.size() == 0 && soccer_players_olympics.size() > 1) {
                cout << "There are " << soccer_players_olympics.size() << " soccer players." << endl;
            }
            else {
                cout << "There are " << sprinters_olympics.size() << " sprinters and " << soccer_players_olympics.size() << " soccer players." << endl;
            }
        }

        /*------------------------CLEAR-----------------------*/
        else if (menu == 'o' || menu == 'O') { // if menu selection is to clear records
            if (sprinters_olympics.empty() && soccer_players_olympics.empty()) {
                cout << "There are no athletes in the olympics" << endl;
            }
            else {
                char confirm = athleteclearType();

                if (confirm == 'a' || confirm == 'A') { // if clearing all records
                    //extra step to make sure the input wasn't a mistake
                    cout << endl << "Are you sure you want to clear all records? (y/n): ";
                    cin >> confirm;
                    if (confirm == 'y' || confirm == 'Y') { // if user confirms yes to clearing records
                        while (!sprinters_olympics.empty()) {
                            sprinters_olympics.pop_front();
                        }
                        while (!soccer_players_olympics.empty()) {
                            soccer_players_olympics.pop_front();
                        }
                        cout << "All records have been cleared." << endl;
                    }
                }
                else if (confirm == 'p' || confirm == 'P') { // if clearing only sprinter records
                    //extra step to make sure the input wasn't a mistake
                    cout << endl << "Are you sure you want to clear all sprinter records? (y/n): ";
                    cin >> confirm;
                    if (confirm == 'y' || confirm == 'Y') { // if user confirms yes to clearing records
                        while (!sprinters_olympics.empty()) {
                            sprinters_olympics.pop_front();
                        }
                        cout << "All sprinter records have been cleared." << endl;
                    }
                }
                else if (confirm == 'k' || confirm == 'K') { // if clearing only soccer player records
                    //extra step to make sure the input wasn't a mistake
                    cout << endl << "Are you sure you want to clear all soccer player records? (y/n): ";
                    cin >> confirm;
                    if (confirm == 'y' || confirm == 'Y') { // if user confirms yes to clearing records
                        while (!soccer_players_olympics.empty()) {
                            soccer_players_olympics.pop_front();
                        }
                        cout << "All soccer player records have been cleared." << endl;
                    }
                }
                else {
                    cout << "Invalid selection" << endl;
                }
            }
        }
        /*------------------------EXIT-----------------------*/
        else if (menu == 'e' || menu == 'E') { // if menu selection is to exit
            cout << "Thank you for using the Olympic Athlete Tracker!" << endl;
            break;
        }
        /*------------------------INVALID-----------------------*/
        else { // if user inputs something that is not a menu option
            cout << "Invalid selection" << endl;
        }
    }
    return 0;
}
