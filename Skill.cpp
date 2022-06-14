//
// Created by Kaan on 22.04.2020.
//

#include <cstdlib>
#include <cmath>
#include "Skill.h"
#include "Unit.h"
using namespace std;

//Skill Classes

int attackSkill::dmgMod=0;
int attackSkill::baseAcc=0;
double attackSkill::critMod=0;
bool attackSkill::stunEffect=false;
int stun::stunBase=100;

bool attackSkill::attackSkillH(unit *attacker,monster *defender,int dmgMod,int baseAcc,double critMod,bool stunEffect){
    int hitChance=baseAcc + attacker->returnAccuracyModifier() - defender->returnDodge();
    int dmg,rawDmg,actualDmg,critChance=0;
    double actualDmgT=0,temp=0;
    if(hitChance>=rand() % 100 + 1){
        cout << " attack hits;";
        if(critChance>=rand() % 100 + 1){
            actualDmgT= 1.5 * attacker->returnMaxDmg();
            actualDmg= round(actualDmgT);
            cout << " critical hit; " << actualDmg << " damage;";
            defender->dealDamage(actualDmg);
            if(stunEffect){
                stunSkillH(defender,true);
            }
            return defender->returnHP() == 0;
        }
        else{
            dmg = rand()%(attacker->returnMaxDmg()-attacker->returnMinDmg()+1)+attacker->returnMinDmg();
            rawDmg = dmg*(double)((100 + dmgMod)/(double)100);
            temp=defender->returnProtectionModifier()/(double)100;
            actualDmgT = rawDmg - rawDmg*(double)temp;
            actualDmg=round(actualDmgT);
            cout << actualDmg << " damage;";
            defender->dealDamage(actualDmg);
            if(stunEffect){
                stunSkillH(defender,false);
            }
            return defender->returnHP() == 0;
        }
    }
    else{
        cout << " attack misses;";
        return false;
    }
}




bool attackSkill::attackSkillM(unit *attacker,hero *defender,int dmgMod,int baseAcc,double critMod,bool stunEffect){
    double temp;
    int actualDmg,critChance=0;
    double dmg,rawDmg,actualDmgT;
    int hitChance=baseAcc + attacker->returnAccuracyModifier() - defender->returnDodge();
    if(hitChance>=rand() % 100 + 1){
        cout << " attack hits;";
        if(critChance>=rand() % 100 + 1){
            actualDmgT= 1.5 * attacker->returnMaxDmg();
            actualDmg = round(actualDmgT);
            cout << " critical hit; " << actualDmgT << " damage;";
            if(!defender->returnDeathsDoor()){
                defender->dealDamage(actualDmg);
                if(stunEffect){
                    stunSkillM(defender,true);
                }
                return false;
            }
            else if(defender->returnDeathsDoor() && actualDmg!=0){
                return true;
            }
        }
        else{
            dmg = rand()%(attacker->returnMaxDmg()-attacker->returnMinDmg()+1)+attacker->returnMinDmg();
            rawDmg = dmg*(double)((100 + dmgMod)/(double)100);
            temp=defender->returnProtectionModifier()/(double)100;
            actualDmgT = rawDmg - rawDmg*(double)temp;
            actualDmg=round(actualDmgT);
            cout << actualDmg << " damage;";
            if(!defender->returnDeathsDoor()){
                defender->dealDamage(actualDmg);
                if(stunEffect){
                    stunSkillM(defender,false);
                }
                return false;
            }
            else if(defender->returnDeathsDoor() && actualDmg!=0){
                return true;
            }
        }
    }
    else{
        cout << " attack misses;";
        return false;
    }
    return false;
}

bool smite::smiteAttack(unit *attacker, monster *defender){
    dmgMod=0;
    baseAcc=85;
    critMod=0;
    stunEffect=false;
    cout << attacker->returnName() << " #" << attacker->returnNumber() << " uses Smite on " << defender->returnName() << " #" << defender->returnNumber() << ";";
    return attackSkill::attackSkillH(attacker, defender,dmgMod,baseAcc,critMod,stunEffect);
}

bool maceBash::maceBashAttack(unit * attacker, monster *defender){
    dmgMod=0;
    baseAcc=85;
    critMod=0;
    stunEffect=false;
    cout << attacker->returnName() << " #" << attacker->returnNumber() << " uses Mace Bash on " << defender->returnName() << " #" << defender->returnNumber() << ";";
    return attackSkill::attackSkillH(attacker, defender,dmgMod,baseAcc,critMod,stunEffect);
}

bool dazzlingLight::dazzlingLightAttack(unit * attacker, monster *defender){
    dmgMod=-75;
    baseAcc=90;
    critMod=5;
    stunEffect=true;
    cout << attacker->returnName() << " #" << attacker->returnNumber() << " uses Dazzling Light on " << defender->returnName() << " #" << defender->returnNumber() << ";";
    return attackSkill::attackSkillH(attacker, defender,dmgMod,baseAcc,critMod,stunEffect);
}

bool holyLance::holyLanceAttack(unit * attacker, monster *defender){
    dmgMod=0;
    baseAcc=85;
    critMod=6.5;
    stunEffect=false;
    cout << attacker->returnName() << " #" << attacker->returnNumber() << " uses Holy Lance on " << defender->returnName() << " #" << defender->returnNumber() << ";";
    return attackSkill::attackSkillH(attacker, defender,dmgMod,baseAcc,critMod,stunEffect);
}

bool stunningBlow::stunningBlowAttack(unit * attacker, monster *defender){
    dmgMod=-50;
    baseAcc=90;
    critMod=0;
    stunEffect=true;
    cout << attacker->returnName() << " #" << attacker->returnNumber() << " uses Stunning Blow on " << defender->returnName() << " #" << defender->returnNumber() << ";";
    return attackSkill::attackSkillH(attacker, defender,dmgMod,baseAcc,critMod,stunEffect);
}

bool graveyardSlash::graveyardSlashAttack(unit *attacker, hero *defender){
    dmgMod=0;
    baseAcc=85;
    critMod=6;
    stunEffect=false;
    cout << attacker->returnName() << " #" << attacker->returnNumber() << " uses Graveyard Slash on " << defender->returnName() << " #" << defender->returnNumber() << ";";
    return attackSkill::attackSkillM(attacker, defender,dmgMod,baseAcc,critMod,stunEffect);
}

bool graveyardStumble::graveyardStumbleAttack(unit *attacker, hero *defender){
    dmgMod=-50;
    baseAcc=45;
    critMod=0;
    stunEffect=false;
    cout << attacker->returnName() << " #" << attacker->returnNumber() << " uses Graveyard Stumble on " << defender->returnName() << " #" << defender->returnNumber() << ";";
    return attackSkill::attackSkillM(attacker, defender,dmgMod,baseAcc,critMod,stunEffect);
}

bool axeblade::axebladeAttack(unit *attacker, hero *defender){
    dmgMod=0;
    baseAcc=72;
    critMod=6;
    stunEffect=false;
    cout << attacker->returnName() << " #" << attacker->returnNumber() << " uses Axeblade on " << defender->returnName() << " #" << defender->returnNumber() << ";";
    return attackSkill::attackSkillM(attacker, defender,dmgMod,baseAcc,critMod,stunEffect);
}

bool deadWeight::deadWeightAttack(unit *attacker, hero *defender){
    dmgMod=-25;
    baseAcc=82;
    critMod=6;
    stunEffect=true;
    cout << attacker->returnName() << " #" << attacker->returnNumber() << " uses Dead Weight on " << defender->returnName() << " #" << defender->returnNumber() << ";";
    return attackSkill::attackSkillM(attacker, defender,dmgMod,baseAcc,critMod,stunEffect);
}

void bulwarkOfFaith::bulwarkOfFaithSkill(unit * user){
    cout << user->returnName() << " #" << user->returnNumber() << " uses Bulwark of Faith; protection increased by 20 for 3 rounds;" << endl;
    user->updateProtection();
    _sleep(1500);
}

void divineGrace::divineGraceSkill(unit * user, hero *receiver){
    //Heal function
    int healAmount=rand() % 2 + 4;
    cout << user->returnName() << " #" << user->returnNumber() << " uses Divine Grace;" << endl;
    receiver->heal(healAmount);
    cout << endl;
}

void divineComfort::divineComfortSkill(unit * user, vector<pair<hero*, int>> heroes, int heroCount) {
    //Heal all function target all=0
    cout << user->returnName() << " #" << user->returnNumber() << " uses Divine Comfort;" << endl;
    for(int i=0;i<heroCount;i++){
        int healAmount=rand() % 3 + 1;
        heroes[i].first->heal(healAmount);
    }
    cout << endl;
}

void knittingBones::knittingBonesSkill(unit *user, monster* receiver){
    //Heal function
    int healAmount=rand() % 2 + 4;
    cout << user->returnName() << " #" << user->returnNumber() << " uses Knitting Bones;" << endl;
    receiver->heal(healAmount);
    cout << endl;
}

void stun::stunSkillH(monster *defender, bool crit) {
    int stunChance=0;
    stunBase=100;
    if(!crit){
        stunChance=stunBase - defender->returnStunResist();
    }
    else{
        stunChance= 20 + stunBase - defender->returnStunResist();
    }
    if((rand() % 100)>=stunChance){
        cout << " got stunned;";
        defender->setStun();
    }
}

void stun::stunSkillM(hero *defender, bool crit) {
    int stunChance=0;
    stunBase=100;
    if(!crit){
        stunChance=stunBase - defender->returnStunResist();
    }
    else{
        stunChance= 20 + stunBase - defender->returnStunResist();
    }
    if((rand() % 100)>=stunChance){
        cout << " got stunned;";
        defender->setStun();
    }
}

void move::moveSkillH(hero *user,int p) {
    user->updatePositionS(p);
}

void move::moveSkillM(monster *user,int p) {
    user->updatePositionS(p);
}
