// OOP_UAS3_TitaNoviana_24120500011.cpp
#include <iostream>
#include <vector>
using namespace std;

// Base Class
class Person {
protected:
    string name;
    int age;
public:
    Person(string name, int age) : name(name), age(age) {}
    virtual void display() = 0;
};

// Player Class
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

// Coach Class
class Coach : public Person {
private:
    string role;
    string licenseLevel;
public:
    Coach(string name, int age, string role, string licenseLevel)
        : Person(name, age), role(role), licenseLevel(licenseLevel) {}
    void display() override {
        cout << role << ": " << name << ", Age: " << age << ", License: " << licenseLevel << endl;
    }
};

// Abstract Factory
class PersonFactory {
public:
    virtual Person* create() = 0;
};

// Player Factory
class PlayerFactory : public PersonFactory {
private:
    string name;
    int age;
    string position;
    int jerseyNumber;
public:
    PlayerFactory(string name, int age, string position, int jerseyNumber)
        : name(name), age(age), position(position), jerseyNumber(jerseyNumber) {}
    Person* create() override {
        return new Player(name, age, position, jerseyNumber);
    }
};

// Coach Factory
class CoachFactory : public PersonFactory {
private:
    string name;
    int age;
    string role;
    string licenseLevel;
public:
    CoachFactory(string name, int age, string role, string licenseLevel)
        : name(name), age(age), role(role), licenseLevel(licenseLevel) {}
    Person* create() override {
        return new Coach(name, age, role, licenseLevel);
    }
};

// Team and Club classes
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

    CoachFactory headFactory("Pak Budi", 45, "Head Coach", "A");
    CoachFactory assistantFactory("Pak Ali", 40, "Assistant Coach", "B");

    Coach* headCoach = dynamic_cast<Coach*>(headFactory.create());
    Coach* assistantCoach = dynamic_cast<Coach*>(assistantFactory.create());

    team->setHeadCoach(headCoach);
    team->setAssistantCoach(assistantCoach);

    PlayerFactory player1("Andi", 20, "Striker", 9);
    PlayerFactory player2("Budi", 21, "Goalkeeper", 1);

    team->addPlayer(dynamic_cast<Player*>(player1.create()));
    team->addPlayer(dynamic_cast<Player*>(player2.create()));

    club.addTeam(team);

    club.display();

    return 0;
}
