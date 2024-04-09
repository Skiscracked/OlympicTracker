// implementation
#include "olympic.h"

athlete::athlete(string n, int a, string c, int i) { // constructor for athlete
    name = n;
    age = a;
    country = c;
    id = i; //added a data member called id, to store the identification number for that speecific athlete
}           //eliminates issues considering duplicates

void athlete::read(istream& in) { // read athletes info
    cout << "Enter athlete's name: ";
    in >> name;
    cout << "Enter athlete's age: ";
    in >> age;
    cout << "Enter athlete's country: ";
    in >> country;
    cout << "Enter an id (integars only!):";
    in >> id;
}


sprinter::sprinter(string n, int a, string c, int i, int d, float r) : athlete(n, a, c, i) { // constructor afor sprinter
    dist = d;
    record_time = r;
}

void sprinter::read(istream& in) { // read sprinters info
    athlete::read(in);
    cout << "Enter the distance in meters: ";
    in >> dist;
    cout << "Enter the record time in seconds: ";
    in >> record_time;
}

soccer_player::soccer_player(string n, int a, string c, int i, int g, int p) : athlete(n, a, c, i) { // constructor for soccer player
    goals = g;
    penalties = p;
}

void soccer_player::read(istream& in) { // read soccer players info
    athlete::read(in);
    cout << "Enter the number of goals: ";
    in >> goals;
    cout << "Enter the number of penalties: ";
    in >> penalties;
}

node::node(athlete* a) { // data = x, next = NULL
    data = a;
    next = NULL;
}

olympics::olympics(void) { // constructor of an empty olympics
    start = NULL;
    count = 0;
}


void olympics::push_back(athlete* item) {
    //olympics::duplicate(item);
    node* ptr = new node(item);
    if (start == NULL) { // if the olympics is empty
        start = ptr;
    }
    else { // otherwise, traverse the olympics to the end
        node* tail = start;
        while (tail->next != NULL) {
            tail = tail->next;
        }
        tail->next = ptr; // add the new node to the end
    }
    count++; // increment the node count
}

void olympics::pop_front(void) { // used to clear the olympics
    node* ptr = start;
    start = start->next;
    count--;
    delete ptr;
}

int olympics::size(void) const { // returns count
    return count;
}

bool olympics::empty(void) const { // check if olympics is empty
    return (start == NULL);
}

void olympics::sprinter_write(ostream& out) const { // write sprinters info
    for (node* ptr = start; ptr != NULL; ptr = ptr->next) {
        athlete* a = ptr->data;
        out << "Name: " << a->name << ", Age: " << a->age << ", Country: " << a->country << ", id: " << a->id; //print out the id as well
        sprinter* s = static_cast<sprinter*>(ptr->data);
        out << ", Distance (m): " << s->dist << ", Record Time (s): " << s->record_time << endl;
    }
}
void olympics::soccer_write(ostream& out) const { // write soccer players info
    for (node* ptr = start; ptr != NULL; ptr = ptr->next) {
        athlete* a = ptr->data;
        out << "Name: " << a->name << ", Age: " << a->age << ", Country: " << a->country << ", id: " << a->id; //print out the id as well
        soccer_player* sp = static_cast<soccer_player*>(ptr->data);
        out << ", Goals: " << sp->goals << ", Penalties: " << sp->penalties << endl;
    }
}

bool olympics::remove(const int& x) { // remove a specific athlete
    node* temp = start;
    node* prev = NULL;
    bool found = false;
    while (temp != NULL) {
        if (temp->data->id == x) { // athlete found in olympics
            if (prev == NULL) {
                start = temp->next;
            }
            else {
                prev->next = temp->next;
            }
            delete temp->data;
            delete temp;
            count--;
            found = true;
            break;
        }
        prev = temp;
        temp = temp->next;
    }
    return found;
}

bool olympics::sprinter_retrieve(int x) { // retrieve from sprinter list
    node* temp = start;
    bool found = false;
    while (temp != NULL) {
        if (temp->data->id == x) {
            cout << "Athlete Found" << endl;
            cout << "Name: " << temp->data->name << ", Age: " << temp->data->age << ", Country: " << temp->data->country;
            sprinter* s = static_cast<sprinter*>(temp->data);
            cout << ", Distance (m): " << s->dist << ", Record Time (s): " << s->record_time << endl;
            return found = true;
            break;
        }
        temp = temp->next;
    }
    return found = false;
}

bool olympics::soccer_player_retrieve(int x) { // retrieve from soccer player list
    node* temp = start;
    bool found = false;
    while (temp != NULL) {
        if (temp->data->id == x) {
            cout << "Athlete Found" << endl;
            cout << "Name: " << temp->data->name << ", Age: " << temp->data->age << ", Country: " << temp->data->country;
            soccer_player* sp = static_cast<soccer_player*>(temp->data);
            cout << ", Goals: " << sp->goals << ", Penalties: " << sp->penalties << endl;
            return found = true;
            break;
        }
        temp = temp->next;
    }
    return found = false;
}

/*---------------------SORTING FUNCTIONS------------------*/
void olympics::sort_distance() { //sorts sprinter distance
    vector<sprinter*> sprinters;
    node* ptr = start;
    while (ptr != NULL) {
        sprinter* s = static_cast<sprinter*>(ptr->data);
        sprinters.push_back(s);
        ptr = ptr->next;
    }
    // sort the sprinters based on distance using bubble sort
    for (int i = 0; i < sprinters.size() - 1; i++) {
        for (int j = 0; j < sprinters.size() - i - 1; j++) {
            if (sprinters.at(j)->dist < sprinters.at(j + 1)->dist) {
                sprinter* temp = sprinters.at(j);
                sprinters.at(j) = sprinters.at(j + 1);
                sprinters.at(j + 1) = temp;
            }
        }
    }
    // print the sorted olympics of sprinters
    cout << endl << "Standings based on distance: " << endl;
    for (int i = 0; i < sprinters.size(); i++) {
        cout << "Name: " << sprinters.at(i)->name << ", Age: " << sprinters.at(i)->age << ", Country: " << sprinters.at(i)->country << ", Distance (m): " << sprinters.at(i)->dist << endl;
    }
}

void olympics::sort_time() { //sorts sprinters record times
    vector<sprinter*> sprinters;
    node* ptr = start;
    while (ptr != NULL) {
        sprinter* s = static_cast<sprinter*>(ptr->data);
        sprinters.push_back(s);
        ptr = ptr->next;
    }
    // sort the sprinters based on time using bubble sort
    for (int i = 0; i < sprinters.size() - 1; i++) {
        for (int j = 0; j < sprinters.size() - i - 1; j++) {
            if (sprinters.at(j)->record_time > sprinters.at(j + 1)->record_time) {
                sprinter* temp = sprinters.at(j);
                sprinters.at(j) = sprinters.at(j + 1);
                sprinters.at(j + 1) = temp;
            }
        }
    }
    // print the sorted olympics of sprinters
    cout << endl << "Standings based on record time: " << endl;
    for (int i = 0; i < sprinters.size(); i++) {
        cout << "Name: " << sprinters.at(i)->name << ", Age: " << sprinters.at(i)->age << ", Country: " << sprinters.at(i)->country << ", Record Time (s): " << sprinters.at(i)->record_time << endl;
    }
}

void olympics::sort_goals() { //sorts soccer players goals
    vector<soccer_player*> players;
    node* ptr = start;
    while (ptr != NULL) {
        soccer_player* p = static_cast<soccer_player*>(ptr->data);
        players.push_back(p);
        ptr = ptr->next;
    }
    // sort the players based on goals using bubble sort
    for (int i = 0; i < players.size() - 1; i++) {
        for (int j = 0; j < players.size() - i - 1; j++) {
            if (players.at(j)->goals < players.at(j + 1)->goals) {
                soccer_player* temp = players.at(j);
                players.at(j) = players.at(j + 1);
                players.at(j + 1) = temp;
            }
        }
    }
    // print the sorted olympics of soccer players
    cout << endl << "Standings based on number of goals: " << endl;
    for (int i = 0; i < players.size(); i++) {
        int y = i + 1;
        cout << y << ". Name: " << players.at(i)->name << ", Age: " << players.at(i)->age << ", Country: " << players.at(i)->country << ", Goals: " << players.at(i)->goals << endl;
    }
}

void olympics::sort_penalties() { //sorts soccer player penalties
    vector<soccer_player*> soccer_players;
    node* ptr = start;
    while (ptr != NULL) {
        soccer_player* sp = static_cast<soccer_player*>(ptr->data);
        soccer_players.push_back(sp);
        ptr = ptr->next;
    }
    // sort the soccer players based on number of penalties using bubble sort
    for (int i = 0; i < soccer_players.size() - 1; i++) {
        for (int j = 0; j < soccer_players.size() - i - 1; j++) {
            if (soccer_players.at(j)->penalties > soccer_players.at(j + 1)->penalties) {
                soccer_player* temp = soccer_players.at(j);
                soccer_players.at(j) = soccer_players.at(j + 1);
                soccer_players.at(j + 1) = temp;
            }
        }
    }
    // print the sorted olympics of soccer players
    cout << endl << "Standings based on number of penalties: " << endl;
    for (int i = 0; i < soccer_players.size(); i++) {
        cout << "Name: " << soccer_players.at(i)->name << ", Age: " << soccer_players.at(i)->age << ", Country: " << soccer_players.at(i)->country << ", Number of Penalties: " << soccer_players.at(i)->penalties << endl;
    }
}
/*
void athlete::athlete_id(istream& in) { //scanning the input from the user into id in a seperate function.
    in >> id;                           //now this function can be called in the duplicate function
}

//duplicate function definition
void olympics::duplicate(athlete* item) {

    for (node* ptr = start; ptr != NULL; ptr = ptr->next) {
        if (item->id == ptr->data->id) {
            cout << "That ID has been choosen, please enter a new id:" << endl;
            item->athlete_id(cin);
        }
        else {
            item->athlete_id(cin);
        }
        }

   }
*/
//We attempted to implement the unique id idea Prof Naghibi suggested, due to the amount of time we had we were unsuccessful.
//the code stops working once a second type of that specific athlete is inputted.

char getAthleteType() {
    char type;
    cout << endl << "Enter the type of athlete you would like to add: " << endl;
    cout << "p - sprinter" << endl;
    cout << "k - soccer player" << endl;
    cout << "e - previous menu" << endl;
    cin >> type;
    return type;
}

char sortSprinter() {
    char sort;
    cout << endl << "Enter how you would like to sort: " << endl;
    cout << "d - distance" << endl;
    cout << "t - record time" << endl;
    cin >> sort;
    return sort;
}

char sortSoccer() {
    char sort;
    cout << endl << "Enter how you would like to sort: " << endl;
    cout << "g - goals" << endl;
    cout << "p - penalties" << endl;
    cin >> sort;
    return sort;
}

char athleteclearType() {
    char confirm;
    cout << endl << "Enter the records you would like to clear?" << endl;
    cout << "a - all records" << endl;
    cout << "p - sprinter records" << endl;
    cout << "k - soccer player records" << endl;
    cin >> confirm;
    return confirm;
}

