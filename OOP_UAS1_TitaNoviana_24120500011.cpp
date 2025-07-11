// OOP_UAS1_TitaNoviana_24120500011.cpp
#include <iostream>
#include <vector>
using namespace std;

class Person {
protected:
    string name;
    int age;
public:
    Person(string name, int age) : name(name), age(age) {}
    virtual void display() = 0;
};

class Staff : public Person {
protected:
    string role;
public:
    Staff(string name, int age, string role) : Person(name, age), role(role) {}
    void display() override {
        cout << "Staff: " << name << " (" << role << "), Age: " << age << endl;
    }
};

class Coach : public Staff {
private:
    string licenseLevel;
public:
    Coach(string name, int age, string role, string licenseLevel)
        : Staff(name, age, role), licenseLevel(licenseLevel) {}
    void display() override {
        cout << role << ": " << name << ", Age: " << age << ", License: " << licenseLevel << endl;
    }
};

class Player : public Person {
private:
    string position;
    int jerseyNumber;
public:
    Player(string name, int age, string position, int jerseyNumber)
        : Person(name, age), position(position), jerseyNumber(jerseyNumber) {}
    void display() override {
        cout << "Player: " << name << ", #" << jerseyNumber << ", Position: " << position << ", Age: " << age << endl;
    }
};

class Team {
private:
    string name;
    Coach* headCoach;
    Coach* assistantCoach;
    vector<Player*> players;
public:
    Team(string name) : name(name), headCoach(nullptr), assistantCoach(nullptr) {}

    void setHeadCoach(Coach* coach) {
        headCoach = coach;
    }

    void setAssistantCoach(Coach* coach) {
        assistantCoach = coach;
    }

    void addPlayer(Player* player) {
        if (players.size() < 15)
            players.push_back(player);
    }

    void display() {
        cout << "Team: " << name << endl;
        if (headCoach) headCoach->display();
        if (assistantCoach) assistantCoach->display();
        for (auto p : players)
            p->display();
    }
};

class Club {
private:
    string name;
    vector<Team*> teams;
public:
    Club(string name) : name(name) {}

    void addTeam(Team* team) {
        teams.push_back(team);
    }

    void display() {
        cout << "Club: " << name << endl;
        for (auto t : teams)
            t->display();
    }
};

// ======= Contoh Main =========
int main() {
    Club club("FC Cakrawala");

    Team* team = new Team("FC Cakrawala Muda");

    Coach* head = new Coach("Pak Budi", 45, "Head Coach", "A");
    Coach* assistant = new Coach("Pak Ali", 40, "Assistant Coach", "B");

    team->setHeadCoach(head);
    team->setAssistantCoach(assistant);

    team->addPlayer(new Player("Andi", 20, "Striker", 9));
    team->addPlayer(new Player("Budi", 21, "Goalkeeper", 1));

    club.addTeam(team);

    club.display();

    return 0;
}
