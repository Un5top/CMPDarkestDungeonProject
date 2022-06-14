//
// Created by Kaan on 22.04.2020.
//

#include <iostream>
#include <vector>
#include "Unit.h"
using namespace std;


unit::unit(int maxHPI,int dodgeI, int protectionI,int speedI, int accuracyModifierI,int baseCriticalI,int minDmgI,int maxDmgI,int stunResistI,int positionI,int numberI,string nameI){
        maxHP = maxHPI;
        hp=maxHP;
        stunned=false;
        dodge = dodgeI;
        protection = protectionI;
        speed = speedI;
        accuracyModifier = accuracyModifierI;
        baseCritical = baseCriticalI;
        minDmg = minDmgI;
        maxDmg = maxDmgI;
        stunResist = stunResistI;
        position=positionI;
        number=numberI;
        name=nameI;
    }

void unit::updatePosition(int deadPosition){
    if(deadPosition==1){
        position--;
    }
    else if(deadPosition==2){
        if(position!=1){
            position--;
        }
    }
    else if(deadPosition==3){
        if(position!=1 || position!=2){
            position--;
        }
    }
}

void unit::updatePositionS(int positionI){
    unit::position=positionI + 1;
}

bool hero::death(){
    if((rand() % 100) >deathBlowResist){
        cout << "resisted" << endl;
        return false;
    }
    else return true;
}



void unit::heal(int healAmount){
    if(hp==maxHP){
        cout << unit::returnName() << " #" << unit::returnNumber() << " is already at maximum hp, couldn't heal;" << endl;
        _sleep(1000);
    }
    else if (hp+healAmount>maxHP){
        cout << "Healed " << unit::returnName() << " #" << unit::returnNumber() << " for " << maxHP-hp << " hp;" << endl;
        hp=maxHP;
        _sleep(1000);
    }
    else if(hp+healAmount<=maxHP){
        cout << "Healed " << unit::returnName() << " #" << unit::returnNumber() << " for " << healAmount << " hp;" << endl;
        hp=hp+healAmount;
        _sleep(1000);
    }
}

void unit::speedRand(){
    speed = speed + rand() % 8 + 1;
}

int unit::returnHP() {
    return hp;
}

int unit::returnBaseCritical() {
    return baseCritical;
}

int unit::returnAccuracyModifier() {
    return accuracyModifier;
}

int unit::returnDodge() {
    return dodge;
}

int unit::returnSpeed() {
    return speed;
}

int unit::returnPosition() {
    return position;
}

int unit::returnMaxDmg() {
    return maxDmg;
}

int unit::returnMinDmg() {
    return minDmg;
}

int unit::returnNumber() {
    return number;
}

int unit::returnProtectionModifier(){
    return protection;
}

string unit::returnName(){
    return name;
}

void unit::dealDamage(int dmg) {}

pair<string, int> unit::turn() {
    return make_pair("unit",0);
}

unit::unit() {}

bool unit::death() {
    return false;
}

int unit::returnStunResist() {

    return stunResist;
}

bool unit::returnStun() {
    return stunned;
}

void unit::updateStun() {
    stunned=!stunned;
}

void unit::setStun() {
    stunned=true;
}

void unit::updateProtection() {
    protection = protection + 20;
    ProtectionTurn = 1;
}
void unit::updateProtectionMain() {
    if(ProtectionTurn!=0){
        ProtectionTurn++;
    }
    else if(ProtectionTurn==4){
        cout << unit::returnName() << " #" << unit::returnNumber() << "'s protection boost has worn off;" << endl;
        ProtectionTurn = 0;
        protection = protection - 20;
    }
}

void unit::declarePosition() {
    cout << name << " #" << number << " is in the";
    if(position==1){
        cout << " 1st position;" << endl;
    }
    else if(position==2){
        cout << " 2nd position;" << endl;
    }
    else if(position==3){
        cout << " 3rd position;" << endl;
    }
    else if(position==4){
        cout << " 4th position;" << endl;
    }
    _sleep(1500);
}

hero::hero(int maxHPI,int dodgeI, int protectionI,int speedI, int accuracyModifierI,int baseCriticalI,int minDmgI,int maxDmgI,int stunResistI, int positionI, int deathBlowResistI,int numberI,string nameI):unit(maxHPI, dodgeI, protectionI, speedI, accuracyModifierI, baseCriticalI, minDmgI, maxDmgI, stunResistI, positionI,numberI,nameI){
    deathBlowResist = deathBlowResistI;
    deathsDoor=false;
}

hero::hero() {}

void hero::speedRand(){
    speed = speed + rand() % 8 + 1;
}

int hero::returnSpeed(){
    return speed;
}

int hero::returnHP() {
    return maxHP;
}

void hero::dealDamage(int dmg) {
    if(dmg>=hp){
        hp=0;
        deathsDoor=true;
        cout << endl << unit::returnName() << " #" << unit::returnNumber() << " is at Death's Door;" << endl;
    }
    else if(dmg<hp){
        hp=hp-dmg;
    }
}

pair<basic_string<char>, int> hero::turn(){
    return make_pair("unit",0);
}

monster::monster(int maxHPI,int dodgeI, int protectionI,int speedI, int accuracyModifierI,int baseCriticalI,int minDmgI,int maxDmgI,int stunResistI,int positionI,int numberI,string nameI):unit(maxHPI, dodgeI, protectionI, speedI, accuracyModifierI, baseCriticalI, minDmgI, maxDmgI, stunResistI, positionI,numberI,nameI){}

void monster::speedRand(){
    speed = speed + rand() % 8 + 1;
}

int monster::returnSpeed(){
    return speed;
}

void monster::dealDamage(int dmg) {
    if(dmg>=hp){
        hp=0;
    }
    else if(dmg<hp){
        hp=hp-dmg;
    }
}

pair<basic_string<char>, int> monster::turn(){
    return make_pair("monster",0);
}

//Hero Classes

//Crusader functions
Crusader::Crusader(int p,int numberI): hero(1,5,0,1,0,3,6,12,40,p,67,numberI,"Crusader") {}

pair<basic_string<char>, int> Crusader::turn(vector<pair<monster*, int>> monsters, int monsterCount){
    cout << "It is Crusader #" << number << "'s turn" << endl;
    cout << "Choose skill" << endl;
    int holyLanceGuide=0;
    if(position==1 || position==2){
        cout << 1 << ") Smite (Attack)" << endl;
        cout << 2 << ") Stunning Blow (Attack)" << endl;
        cout << 4 << ") Bulwark of Faith (Utility)" << endl;
        cout << 5 << ") Move" << endl;
    }
    else if((position==4 || position==3)){
        for(int i=0;i<monsterCount;i++){
            if(monsters[i].first->returnPosition()==2 || monsters[i].first->returnPosition()==3 || monsters[i].first->returnPosition()==4){
                holyLanceGuide++;
            }
        }
        if(holyLanceGuide==0){
            cout << 5 << ") Move" << endl;
        }
        if(holyLanceGuide!=0){
            cout << 3 << ") Holy Lance (Attack)" << endl;
            cout << 5 << ") Move" << endl;
        }
    }
    int input=0;
    cin >> input;
    if((input==1 || input==2 || input==4) && (position==1 || position==2)){
        return make_pair("Crusader",input);
    }
    if(input==3 && (position==3 || position==4) && !holyLanceGuide==0){
        return make_pair("Crusader",input);
    }
    else if(input==5){
        return make_pair("Crusader",input);
    }
    else{
        cout << "Wrong Input, game terminated" << endl;
        exit(0);
    }
}

//Vestal functions
Vestal::Vestal(int p,int numberI) : hero(24,0,0,4,0,1,4,8,30,p,77,numberI,"Vestal") {}

pair<string,int> Vestal::turn(){
    cout << "It is Vestal #" << number << "'s turn" << endl;
    cout << "Choose skill (Only the ones you can use are visible)" << endl;
    if(position==1){
        cout << 1 << ") Mace Bash (Attack)" << endl;
        cout << 5 << ") Move" << endl;
    }
    else if(position==2){
        cout << 1 << ") Mace Bash (Attack)" << endl;
        cout << 2 << ") Dazzling Light (Attack)" << endl;
        cout << 4 << ") Divine Comfort (Utility)" << endl;
        cout << 5 << ") Move" << endl;
    }
    else if(position==4 || position==3){
        cout << 2 << ") Dazzling Light (Attack)" << endl;
        cout << 3 << ") Divine Grace (Utility)" << endl;
        cout << 4 << ") Divine Comfort (Utility)" << endl;
        cout << 5 << ") Move" << endl;
    }
    int input=0;
    cin >> input;
    if(input==1 && (position==1 || position==2)){
        return make_pair("Vestal",input);
    }
    else if((input==2 || input==4) && (position==2 || position==3 || position==4)){
        return make_pair("Vestal",input);
    }
    else if(input==3 && (position==3 || position==4)){
        return make_pair("Vestal",input);
    }
    else if(input==5){
        return make_pair("Vestal",input);
    }
    else {
        cout << "Wrong Input, game terminated" << endl;
        exit(0);
    }
}

//Monster Classes

//Bone Soldier functions
BoneSoldier::BoneSoldier(int p,int numberI) : monster(10,10,15,2,0,0,3,8,25,p,numberI,"Bone Soldier") {}

pair<basic_string<char>, int> BoneSoldier::turn(){
    int roll,choice;
    roll=rand() % 100 +1;
    if(roll<10 && roll>=0){
        return make_pair("Bone Soldier", 3);
    }
    else if(roll>=10 && roll<100){
        if(position==1 || position==2 || position==3){
            choice=1;
        }
        else if(position==4){
            choice=2;
        }
        return  make_pair("Bone Soldier", choice);
    }
    return make_pair(" ",0);
}

//Bone Defender functions
BoneDefender::BoneDefender(int p,int numberI) : monster(22,8,45,1,0,0,2,4,45,p,numberI,"Bone Defender") {}

pair<basic_string<char>, int> BoneDefender::turn(){
    int roll,choice;
    roll=rand() % 100 +1;
    if(roll<10 && roll>=0){
        return make_pair("Bone Defender", 4);
    }
    else if(roll>=10 && roll<100){
        if(position==4){
            choice=3;
        }
        else if(position==3){
            choice=rand() % 2 + 2;
        }
        else if(position==1 || position==2){
            choice=rand() % 2 + 1;
        }
        return  make_pair("Bone Defender", choice);
    }
    return make_pair("0",0);
}

bool hero::returnDeathsDoor() {
    return deathsDoor;
}

pair<string, int> hero::turn(vector<pair<struct monster *, int>> monsters,int monsterCount) {
    return pair<string, int>();
}

bool monster::death() {
    return false;
}
