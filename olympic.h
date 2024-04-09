// declaration
#ifndef OLYMPIC_H
#define OLYMPIC_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class athlete { // base class
	friend class olympics;
protected:   // protected so that soccer_player::write can access easier
	string name, country;
	int age, id;
public:
	athlete(string n, int a, string c, int i);
	virtual void read(istream& in);
	void athlete_id(istream& in);
};

class node {
	friend class olympics;    // olympics can access node's private members
	friend class sprinter;
	friend class soccer_player;
private:
	athlete* data;   // this is the data stored in a node
	node* next;      // pointer to the next node in the olympics
public:
	node(athlete* ath);
};

class olympics { // composite class
private:
	node* start;       // pointer to node at the start of the olympics
	int count;         // number of nodes in the olympics
public:
	olympics(void);                            // constructor of an empty olympics
	void pop_front(void);                      // remove the node at the start
	void duplicate(athlete* item);
	void push_back(athlete* item);             // push the item at the end of the olympics
	int size(void) const;                      // return count
	bool empty(void) const;                    // check for an empty olympics
	void sprinter_write(ostream& out) const;  // write sprinters info
	void soccer_write(ostream& out) const;    // write soccer players info
	bool remove(const int& x);              // remove a specific athlete
	bool soccer_player_retrieve(int x);     // retrieve from soccer player list
	bool sprinter_retrieve(int x);          // retrieve from sprinter list
	void sort_distance();                      // sort sprinters by distance
	void sort_time();                          // sort sprinters by record time
	void sort_goals();                         // sort soccer players by goals
	void sort_penalties();                     // sort soccer players by penalties
};

class sprinter : public athlete { //derived class
	friend class olympics;
	friend class node;
private:
	int dist;
	float record_time;
public:
	sprinter(string n = "none", int a = 0, string c = "none", int i = 0, int d = 0, float r = 0);
	void read(istream& in);
};

class soccer_player : public athlete { //derived class
	friend class node;
	friend class olympics;
private:
	int goals, penalties;
public:
	soccer_player(string n = "none", int a = 0, string c = "none", int i = 0, int g = 0, int p = 0);
	void read(istream& in);
};


char getAthleteType();
char sortSprinter();
char sortSoccer();
char athleteclearType();
#endif