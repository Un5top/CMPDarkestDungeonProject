//
// Created by Kaan on 22.04.2020.
//

#ifndef CMPDARKESTDUNGEONPROJECT_SKILL_H
#define CMPDARKESTDUNGEONPROJECT_SKILL_H


//Skill Classes

#include <utility>
#include <vector>
#include "Unit.h"
#include <deque>

class skill{
public:
    //Hello There
};

class stun{
protected:
    static int stunBase;
public:
    static void stunSkillH(monster *defender, bool crit);
    static void stunSkillM(hero *defender, bool crit);
};

class attackSkill:public skill,public stun{
protected:
    static int dmgMod,baseAcc;
    static double critMod;
    static bool stunEffect;
public:
    static bool attackSkillH(unit *attacker,monster *defender,int dmgMod,int baseAcc,double critMod,bool stunEffect);

    static bool attackSkillM(unit *attacker, hero *defender, int dmgMod, int baseAcc, double critMod, bool stunEffect);
};

class smite:public attackSkill{
public:
    static bool smiteAttack(unit *attacker, monster *defender);
};

class maceBash:public attackSkill{
public:
    static bool maceBashAttack(unit *attacker, monster *defender);
};

class holyLance:public attackSkill{
public:
    static bool holyLanceAttack(unit *attacker, monster *defender);
};

class stunningBlow:public attackSkill{
public:
    static bool stunningBlowAttack(unit *attacker, monster *defender);
};

class dazzlingLight:public attackSkill{
public:
    static bool dazzlingLightAttack(unit *attacker, monster *defender);
};

class graveyardSlash:public  attackSkill{
public:
    static bool graveyardSlashAttack(unit *attacker, hero *defender);
};

class graveyardStumble:public  attackSkill{
public:
    static bool graveyardStumbleAttack(unit *attacker, hero *defender);
};

class axeblade:public  attackSkill{
public:
    static bool axebladeAttack(unit *attacker, hero *defender);
};

class deadWeight:public  attackSkill{
public:
    static bool deadWeightAttack(unit *attacker, hero *defender);
};

class utilitySkill:public skill{
};

class bulwarkOfFaith:utilitySkill{
public:
    static void bulwarkOfFaithSkill(unit * user);
};

class divineGrace:utilitySkill{
public:
    static void divineGraceSkill(unit *user, hero* receiver);
};

class divineComfort:utilitySkill{
public:
    static void divineComfortSkill(unit *user, vector<pair<hero*, int>> heroes, int heroCount);
};

class knittingBones:utilitySkill{
public:
    static void knittingBonesSkill(unit *user, monster* receiver);
};

class move:public skill{
public:
    static void moveSkillH(hero *user, int p);
    static void moveSkillM(monster *user, int p);
};


#endif //CMPDARKESTDUNGEONPROJECT_SKILL_H
