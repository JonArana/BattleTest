#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

using namespace std;

//initialize functions
float total_damage(int[], int, float);
void load_dva(float&, float);
void load_dva(int&, float);

//template for missile power
template <typename T>
T missile_power(T botsAtk){
    return botsAtk * 3;
}

int main() {

    //open combat.txt and check if combat.txt opened
    string combatFileName = "combat.txt";

    ifstream combatFile(combatFileName);

    if (!combatFile.is_open()) {
        cout << "File fail to open." << endl;
        return 0;
    }
    //initiate values for combat information
    int botsCount;
    float bossHP;
    int microMissiles;
    float defenseMatrix;

    //get values from combat.txt
    combatFile >> botsCount;

    //initialize array and insert values from combat.txt
    int botsPower[botsCount];
    for (int i = 0; i < botsCount; i++) {
        combatFile >> botsPower[i];
    }
    combatFile >> bossHP >> microMissiles >> defenseMatrix;

    //close combat.txt
    combatFile.close();

    //use functions to calculate
    float botsAtk = total_damage(botsPower, botsCount, bossHP);
    load_dva(defenseMatrix, botsAtk);
    load_dva(microMissiles, missile_power(botsAtk));


    //open report text and check if report is open
    string reportFileName = "report.txt";

    ofstream report(reportFileName);
    if (!report.is_open()) {
        cout << "File fail to open." << endl;
        return 0;
    }

    //write to report.txt
    report << "D.Va's Combat Report" << endl;
    report << "Combat with " << botsCount << " enemy bots and one enemy boss with power " << bossHP << "." << endl;
    report << "Loaded mech with " << microMissiles << " micro missiles and the defense matrix with power " << defenseMatrix << "." << endl;
    report << "Ready for combat!";

    //close file report.txt
    report.close();
    return 0;
}

//function to calculate the total damage of all bots and boss
float total_damage(int botsPower[], int botsCount, float bossHP){
    float botsAtk;
    for (int i = 0; i < botsCount; i++){
        botsAtk += botsPower[i];
    }
    botsAtk += bossHP;
    return botsAtk;
}

//function to calculate how much power defense matrix needs
void load_dva(float& defenseMatrix, float botsAtk){
    if (defenseMatrix < botsAtk){
    defenseMatrix = botsAtk;
    }
}

//function to determine if more micro missiles are needed
void load_dva(int& microMissiles, float missilePower){
    if (microMissiles < ceil(missilePower / 100)){
        microMissiles = ceil(missilePower/100);
    }
}
