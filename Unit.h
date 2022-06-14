//
// Created by Kaan on 22.04.2020.
//

#ifndef CMPDARKESTDUNGEONPROJECT_UNIT_H
#define CMPDARKESTDUNGEONPROJECT_UNIT_H

#include <iostream>
using namespace std;

class unit{
protected:
    int maxHP,dodge,protection,speed,accuracyModifier,baseCritical,minDmg,maxDmg,stunResist,position,number,hp,ProtectionTurn=0;
    string name;
    bool stunned;
public:
    unit(int maxHPI, int dodgeI, int protectionI, int speedI, int accuracyModifierI, int baseCriticalI, int minDmgI,int maxDmgI, int stunResistI, int positionI, int numberI,string nameI);
    unit();
    unit(unit *pUnit);
    void declarePosition();
    virtual int returnStunResist();
    virtual bool death();
    void updateProtection();
    virtual bool returnStun();
    virtual void heal(int healAmount);
    virtual void speedRand();
    virtual int returnHP();
    virtual int returnSpeed();
    virtual std::pair<std::basic_string<char>, int> turn();
    virtual int returnPosition();
    virtual int returnAccuracyModifier();
    virtual int returnDodge();
    virtual int returnBaseCritical();
    virtual void dealDamage(int i);
    virtual int returnMaxDmg();
    virtual int returnMinDmg();
    virtual int returnProtectionModifier();
    virtual int returnNumber();
    string returnName();
    void updateStun();
    void updatePosition(int deadPosition);

    void updateProtectionMain();

    void setStun();

    void updatePositionS(int p);
};

class hero:public unit{
protected:
    bool deathsDoor;
    int deathBlowResist;
public:
    hero();
    hero(int maxHPI,int dodgeI, int protectionI,int speedI, int accuracyModifierI,int baseCriticalI,int minDmgI,int maxDmgI,int stunResistI, int positionI, int deathBlowResistI,int numberI,string nameI);
    void speedRand();
    int returnSpeed();
    int returnHP();
    virtual std::pair<std::basic_string<char>, int> turn();
    hero(unit *pUnit);
    void dealDamage(int dmg);
    bool returnDeathsDoor();
    virtual bool death();
    virtual pair<string, int> turn(vector<pair<struct monster *, int>> monsters,int monsterCount);
};

class monster:public unit{
public:
    monster(int maxHPI,int dodgeI, int protectionI,int speedI, int accuracyModifierI,int baseCriticalI,int minDmgI,int maxDmgI,int stunResistI,int positionI,int numberI,string nameI);
    void speedRand();
    int returnSpeed();
    virtual std::pair<std::basic_string<char>, int> turn();

    void dealDamage(int dmg);

    bool death();
};

//Hero Classes

class Crusader:public hero{
public:
    Crusader(int p,int numberI);
    pair<string, int> turn(vector<pair<monster*, int>> monsters,int monsterCount);
};

class Vestal:public hero{
public:
    Vestal(int p,int numberI);
    std::pair<std::string, int> turn();
};

//Monster Classes

class BoneSoldier:public monster{
public:
    BoneSoldier(int p,int numberI);
    std::pair<std::basic_string<char>, int> turn();
};

class BoneDefender:public monster{
public:
    BoneDefender(int p,int numberI);
    std::pair<std::basic_string<char>, int> turn();
};


#endif //CMPDARKESTDUNGEONPROJECT_UNIT_H
