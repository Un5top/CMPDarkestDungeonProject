#include <iostream>
#include <vector>
#include <algorithm>
#include "Unit.h"
#include "Skill.h"
#include <ctime>
using namespace std;

int main() {
    srand(time(nullptr));
    Crusader *crusader1,*crusader2;
    Vestal *vestal1,*vestal2;
    crusader1 = new Crusader(1,1);
    crusader2 = new Crusader(2,2);
    vestal1 = new Vestal(3,1);
    vestal2 = new Vestal(4,2);
    BoneDefender *boneDefender1,*boneDefender2;
    boneDefender1 = new BoneDefender(2,1);
    boneDefender2 = new BoneDefender(4,2);
    BoneSoldier *boneSoldier1,*boneSoldier2;
    boneSoldier1 = new BoneSoldier(1,1);
    boneSoldier2 = new BoneSoldier(3,2);
    vector<pair< int , unit* >> Units;
    vector<pair<hero*,int>> Heroes;
    vector<pair<monster*,int>> Monsters;
    Heroes.push_back(make_pair(crusader1,1));
    Heroes.push_back(make_pair(crusader2,2));
    Heroes.push_back(make_pair(vestal1,3));
    Heroes.push_back(make_pair(vestal2,4));
    Monsters.push_back(make_pair(boneSoldier1,1));
    Monsters.push_back(make_pair(boneDefender1,2));
    Monsters.push_back(make_pair(boneSoldier2,3));
    Monsters.push_back(make_pair(boneDefender2,4));
    Units.push_back(make_pair(0, Heroes[0].first));
    Units.push_back(make_pair(0, Heroes[1].first));
    Units.push_back(make_pair(0, Heroes[2].first));
    Units.push_back(make_pair(0, Heroes[3].first));
    Units.push_back(make_pair(0, Monsters[0].first));
    Units.push_back(make_pair(0, Monsters[1].first));
    Units.push_back(make_pair(0, Monsters[2].first));
    Units.push_back(make_pair(0, Monsters[3].first));
    int heroCount=4,monsterCount=4,unitCount=8;
    for(int round=1;round>0;round++){

        for(int d=0;d<heroCount;d++){
            Heroes[d].first->declarePosition();
        }
        for(int d=0;d<monsterCount;d++){
            Monsters[d].first->declarePosition();
        }

        cout << endl;

        for(int p=0;p<heroCount;p++){
            if(Heroes[p].first->returnName()=="Crusader"){
                Heroes[p].first->updateProtectionMain();
            }
        }
        //Sort units in descending order
        for(int i=0; i < unitCount; i++){
            Units[i].second->speedRand();
            Units[i].first = Units[i].second->returnSpeed();
        }
        sort(Units.begin(), Units.end());
        reverse(Units.begin(), Units.end());

        pair<string,int> userChoice;

        //turns
        for(int turn=0; turn < unitCount; turn++){
            //get unit type and chosen skill
            if(Units[turn].second->returnName()=="Vestal" || Units[turn].second->returnName()=="Bone Defender" || Units[turn].second->returnName()=="Bone Soldier"){
                if(!Units[turn].second->returnStun()){
                    userChoice = (Units[turn].second->turn());
                }
                else if(Units[turn].second->returnStun()){
                    Units[turn].second->updateStun();
                }
            }
            else if(Units[turn].second->returnName()=="Crusader"){
                int crusaderTurn=0;
                for(int x=0;x<heroCount;x++){
                    if (Units[turn].second->returnName()==Heroes[x].first->returnName() && Units[turn].second->returnNumber()==Heroes[x].first->returnNumber()){
                        crusaderTurn=x;
                    }
                }
                if(!Units[turn].second->returnStun()){
                    userChoice = (Heroes[crusaderTurn].first->turn(Monsters,monsterCount));
                }
                else if(Units[turn].second->returnStun()){
                    Units[turn].second->updateStun();
                }
            }

            int targetChoice=0;

            if(userChoice.first == "Crusader") {
                if (userChoice.second == 1) {
                    cout << "Choose a target" << endl;
                    for (int k = 0; k < monsterCount; k++) {
                        if (Monsters[k].first->returnPosition() == 1 || Monsters[k].first->returnPosition() == 2) {
                            cout << Monsters[k].first->returnPosition() << ") " << Monsters[k].first->returnName() << " #" << Monsters[k].first->returnNumber() << endl;
                        }
                    }
                    cin >> targetChoice;
                    if((monsterCount==1 && targetChoice!=1) || (monsterCount>1 && !(targetChoice==1 || targetChoice==2))){
                        cout << "Wrong Input, game terminated" << endl;
                        exit(0);
                    }
                    bool death = smite::smiteAttack(Units[turn].second, Monsters[targetChoice - 1].first);
                    cout << endl << endl;
                    _sleep(1500);
                    if (death) {
                        cout << Monsters[targetChoice-1].first->returnName() << " #" << Monsters[targetChoice-1].first->returnNumber() << " has died;" << endl;
                        for (int x = 0; x < unitCount; x++) {
                            if (Units[x].second->returnName()==Monsters[targetChoice-1].first->returnName() && Units[x].second->returnNumber()==Monsters[targetChoice-1].first->returnNumber()) {
                                Units.erase(Units.begin() + x);
                            }
                        }
                        Monsters.erase(Monsters.begin() + targetChoice - 1);
                        unitCount--;
                        monsterCount--;
                        for(int i=0;i<monsterCount;i++){
                            Monsters[i].first->updatePosition(targetChoice);
                            Monsters[i].second = Monsters[i].first->returnPosition();
                        }
                    }
                    if(monsterCount==0){
                        //need to output surviving heroes (use same system pull protected data) - ez
                        cout << "The Monsters have Fallen. You Win!" << endl;
                        return 0;
                    }
                }
                else if(userChoice.second == 2){
                    cout << "Choose a target" << endl;
                    for(int k=0;k<monsterCount;k++) {
                        if (Monsters[k].first->returnPosition() == 1 || Monsters[k].first->returnPosition() == 2) {
                            cout << Monsters[k].first->returnPosition() << ") " << Monsters[k].first->returnName() << " #" << Monsters[k].first->returnNumber() << endl;
                        }
                    }
                    cin >> targetChoice;
                    if((monsterCount==1 && targetChoice!=1) || (monsterCount>1 && !(targetChoice==1 || targetChoice==2))){
                        cout << "Wrong Input, game terminated" << endl;
                        exit(0);
                    }
                    bool death = stunningBlow::stunningBlowAttack(Units[turn].second, Monsters[targetChoice - 1].first);
                    cout << endl << endl;
                    _sleep(1500);
                    if(death){
                        cout << Monsters[targetChoice-1].first->returnName() << " #" << Monsters[targetChoice-1].first->returnNumber() << " has died;" << endl;
                        for (int x = 0; x < unitCount; x++) {
                            if (Units[x].second->returnName()==Monsters[targetChoice-1].first->returnName() && Units[x].second->returnNumber()==Monsters[targetChoice-1].first->returnNumber()) {
                                Units.erase(Units.begin() + x);

                            }
                        }
                        Monsters.erase(Monsters.begin() + targetChoice-1);
                        unitCount--;
                        monsterCount--;
                        for(int i=0;i<monsterCount;i++){
                            Monsters[i].first->updatePosition(targetChoice);
                            Monsters[i].second = Monsters[i].first->returnPosition();
                        }

                    }
                    if(monsterCount==0){
                        //need to output surviving heroes (use same system pull protected data) - ez
                        cout << "The Monsters have Fallen. You Win!" << endl;
                        return 0;
                    }
                }
                else if(userChoice.second == 3){
                    cout << "Choose a target" << endl;
                    for(int k=0;k<monsterCount;k++) {
                        if (Monsters[k].first->returnPosition() == 2 || Monsters[k].first->returnPosition() == 3 || Monsters[k].first->returnPosition() == 4) {
                            cout << Monsters[k].first->returnPosition() << ") " << Monsters[k].first->returnName() << " #" << Monsters[k].first->returnNumber() << endl;

                        }
                    }
                    cin >> targetChoice;
                    if((monsterCount==2 && targetChoice!=2) || (monsterCount==3 && !(targetChoice==2 || targetChoice==3)) || (monsterCount==4 && !(targetChoice==2 || targetChoice==3 || targetChoice==4))){
                        cout << "Wrong Input, game terminated" << endl;
                        exit(0);
                    }
                    bool death = holyLance::holyLanceAttack(Units[turn].second, Monsters[targetChoice - 1].first);
                    for(int x=0;x<heroCount;x++){
                        if (Units[turn].second->returnName()==Heroes[x].first->returnName() && Units[turn].second->returnNumber()==Heroes[x].first->returnNumber()){
                            Heroes[x].first->updatePositionS(x-1);
                            Heroes[x-1].first->updatePositionS(x);
                            swap(Heroes[x],Heroes[x-1]);
                        }
                    }
                    cout << " moves forward;" << endl << endl;
                    if(death){
                        cout << Monsters[targetChoice-1].first->returnName() << " #" << Monsters[targetChoice-1].first->returnNumber() << " has died;" << endl;
                        for (int x = 0; x < unitCount; x++) {
                            if (Units[x].second->returnName()==Monsters[targetChoice-1].first->returnName() && Units[x].second->returnNumber()==Monsters[targetChoice-1].first->returnNumber()) {
                                Units.erase(Units.begin() + x);

                            }
                        }
                        Monsters.erase(Monsters.begin() + targetChoice-1);
                        unitCount--;
                        monsterCount--;
                        for(int i=0;i<monsterCount;i++){
                            Monsters[i].first->updatePosition(targetChoice);
                            Monsters[i].second = Monsters[i].first->returnPosition();
                        }

                    }
                    if(monsterCount==0){
                        //need to output surviving heroes (use same system pull protected data) - ez
                        cout << "The Monsters have Fallen. You Win!" << endl;
                        return 0;
                    }
                }
                else if(userChoice.second == 4){
                    bulwarkOfFaith::bulwarkOfFaithSkill(Units[turn].second);
                }
                else if(userChoice.second == 5){
                    if(Units[turn].second->returnPosition()==1){
                        for(int x=heroCount-1;x<heroCount && x>=0;x--){
                            if (Units[turn].second->returnName()==Heroes[x].first->returnName() && Units[turn].second->returnNumber()==Heroes[x].first->returnNumber()){
                                move::moveSkillH(Heroes[x+1].first,x);
                                move::moveSkillH(Heroes[x].first,x+1);
                                swap(Heroes[x],Heroes[x+1]);
                            }
                        }
                        cout << Units[turn].second->returnName() << " #" << Units[turn].second->returnNumber() << " moved backwards;" << endl << endl;
                    }
                    else if(Units[turn].second->returnPosition()==2 ||Units[turn].second->returnPosition()==3){
                        int moveChoice=0;
                        cout << "Front or Back?" << endl << "1) Front" << endl << "2) Back" << endl;
                        cin >> moveChoice;
                        if(moveChoice==1){
                            for(int x=0;x<heroCount;x++){
                                if (Units[turn].second->returnName()==Heroes[x].first->returnName() && Units[turn].second->returnNumber()==Heroes[x].first->returnNumber()){
                                    move::moveSkillH(Heroes[x].first,x-1);
                                    move::moveSkillH(Heroes[x-1].first,x);
                                    swap(Heroes[x],Heroes[x-1]);
                                }
                            }
                            cout << Units[turn].second->returnName() << " #" << Units[turn].second->returnNumber() << " moved forward;" << endl << endl;
                        }
                        else if(moveChoice==2){
                            for(int x=heroCount-1;x<heroCount && x>=0;x--){
                                if (Units[turn].second->returnName()==Heroes[x].first->returnName() && Units[turn].second->returnNumber()==Heroes[x].first->returnNumber()){
                                    move::moveSkillH(Heroes[x+1].first,x);
                                    move::moveSkillH(Heroes[x].first,x+1);
                                    swap(Heroes[x],Heroes[x+1]);
                                }
                            }
                            cout << Units[turn].second->returnName() << " #" << Units[turn].second->returnNumber() << " moved backwards;" << endl << endl;
                        }
                        else{
                            cout << "Wrong Input, game terminated" << endl;
                            exit(0);
                        }

                    }
                    else if(Units[turn].second->returnPosition()==4){
                        for(int x=0;x<heroCount;x++){
                            if (Units[turn].second->returnName()==Heroes[x].first->returnName() && Units[turn].second->returnNumber()==Heroes[x].first->returnNumber()){
                                move::moveSkillH(Heroes[x].first,x-1);
                                move::moveSkillH(Heroes[x-1].first,x);
                                swap(Heroes[x],Heroes[x-1]);
                            }
                        }
                        cout << Units[turn].second->returnName() << " #" << Units[turn].second->returnNumber() << " moved forward;" << endl << endl;
                        }
                    }
            }
            else if(userChoice.first == "Vestal"){
                if(userChoice.second == 1){
                    cout << "Choose a target" << endl;
                    for(int k=0;k<monsterCount;k++) {
                        if (Monsters[k].first->returnPosition() == 1 || Monsters[k].first->returnPosition() == 2) {
                            cout << Monsters[k].first->returnPosition() << ") " << Monsters[k].first->returnName() << " #" << Monsters[k].first->returnNumber() << endl;
                        }
                    }
                    cin >> targetChoice;
                    if((monsterCount==1 && targetChoice!=1) || (monsterCount>1 && !(targetChoice==1 || targetChoice==2))){
                        cout << "Wrong Input, game terminated" << endl;
                        exit(0);
                    }
                    bool death = maceBash::maceBashAttack(Units[turn].second, Monsters[targetChoice - 1].first);
                    cout << endl << endl;
                    _sleep(1500);
                    if(death){
                        cout << Monsters[targetChoice-1].first->returnName() << " #" << Monsters[targetChoice-1].first->returnNumber() << " has died;" << endl;
                        for (int x = 0; x < unitCount; x++) {
                            if (Units[x].second->returnName()==Monsters[targetChoice-1].first->returnName() && Units[x].second->returnNumber()==Monsters[targetChoice-1].first->returnNumber()) {
                                Units.erase(Units.begin() + x);

                            }
                        }
                        Monsters.erase(Monsters.begin() + targetChoice-1);
                        unitCount--;
                        monsterCount--;
                        for(int i=0;i<monsterCount;i++){
                            Monsters[i].first->updatePosition(targetChoice);
                            Monsters[i].second = Monsters[i].first->returnPosition();
                        }

                    }
                    if(monsterCount==0){
                        //need to output surviving heroes (use same system pull protected data) - ez
                        cout << "The Monsters have Fallen. You Win!" << endl;
                        return 0;
                    }
                }
                else if(userChoice.second == 2){
                    cout << "Choose a target" << endl;
                    for(int k=0;k<monsterCount;k++) {
                        if (Monsters[k].first->returnPosition() == 1 || Monsters[k].first->returnPosition() == 2 || Monsters[k].first->returnPosition() == 3) {
                            cout << Monsters[k].first->returnPosition() << ") " << Monsters[k].first->returnName() << " #" << Monsters[k].first->returnNumber() << endl;
                        }
                    }
                    cin >> targetChoice;
                    if((monsterCount==1 && targetChoice!=1) || (monsterCount==2 && !(targetChoice==1 || targetChoice==2)) || ((monsterCount==4 || monsterCount==3) && !(targetChoice==1 || targetChoice==2 || targetChoice==3))){
                        cout << "Wrong Input, game terminated" << endl;
                        exit(0);
                    }
                    bool death = dazzlingLight::dazzlingLightAttack(Units[turn].second, Monsters[targetChoice - 1].first);
                    cout << endl << endl;
                    _sleep(1500);
                    if(death){
                        cout << Monsters[targetChoice-1].first->returnName() << " #" << Monsters[targetChoice-1].first->returnNumber() << " has died;" << endl;
                        for (int x = 0; x < unitCount; x++) {
                            if (Units[x].second->returnName()==Monsters[targetChoice-1].first->returnName() && Units[x].second->returnNumber()==Monsters[targetChoice-1].first->returnNumber()) {
                                Units.erase(Units.begin() + x);

                            }
                        }
                        Monsters.erase(Monsters.begin() + targetChoice-1);
                        unitCount--;
                        monsterCount--;
                        for(int i=0;i<monsterCount;i++){
                            Monsters[i].first->updatePosition(targetChoice);
                            Monsters[i].second = Monsters[i].first->returnPosition();
                        }

                    }
                    if(monsterCount==0){
                        //need to output surviving heroes (use same system pull protected data) - ez
                        cout << "The Monsters have Fallen. You Win!" << endl;
                        return 0;
                    }
                }
                else if(userChoice.second == 3){
                    //Divine Grace
                    cout << "Choose a target" << endl;
                    for(int k=0;k<heroCount;k++) {
                        if (Heroes[k].second == 1 || Heroes[k].second == 2 || Heroes[k].second == 3 || Heroes[k].second == 4) {
                            cout << Heroes[k].second << ") " << Heroes[k].first->returnName() << " #" << Heroes[k].first->returnNumber() << endl;
                        }
                    }
                    cin >> targetChoice;
                    if(targetChoice<=0 || targetChoice>heroCount){
                        cout << "Wrong Input, game terminated" << endl;
                        exit(0);
                    }
                    divineGrace::divineGraceSkill(Units[turn].second,Heroes[targetChoice-1].first);
                }
                else if(userChoice.second == 4){
                    divineComfort::divineComfortSkill(Units[turn].second,Heroes,heroCount);
                }
                else if(userChoice.second == 5){
                    if(Units[turn].second->returnPosition()==1){
                        for(int x=heroCount-1;x<heroCount && x>=0;x--){
                            if (Units[turn].second->returnName()==Heroes[x].first->returnName() && Units[turn].second->returnNumber()==Heroes[x].first->returnNumber()){
                                move::moveSkillH(Heroes[x+1].first,x);
                                move::moveSkillH(Heroes[x].first,x+1);
                                swap(Heroes[x],Heroes[x+1]);
                            }
                        }
                        cout << Units[turn].second->returnName() << " #" << Units[turn].second->returnNumber() << " moved backwards;" << endl << endl;
                    }
                    else if(Units[turn].second->returnPosition()==2 ||Units[turn].second->returnPosition()==3){
                        int moveChoice=0;
                        cout << "Front or Back?" << endl << "1) Front" << endl << "2) Back" << endl;
                        cin >> moveChoice;
                        if(moveChoice==1){
                            for(int x=0;x<heroCount;x++){
                                if (Units[turn].second->returnName()==Heroes[x].first->returnName() && Units[turn].second->returnNumber()==Heroes[x].first->returnNumber()){
                                    move::moveSkillH(Heroes[x].first,x-1);
                                    move::moveSkillH(Heroes[x-1].first,x);
                                    swap(Heroes[x],Heroes[x-1]);
                                }
                            }
                            cout << Units[turn].second->returnName() << " #" << Units[turn].second->returnNumber() << " moved forward;" << endl << endl;
                        }
                        else if(moveChoice==2){
                            for(int x=heroCount-1;x<heroCount && x>=0;x--){
                                if (Units[turn].second->returnName()==Heroes[x].first->returnName() && Units[turn].second->returnNumber()==Heroes[x].first->returnNumber()){
                                    move::moveSkillH(Heroes[x+1].first,x);
                                    move::moveSkillH(Heroes[x].first,x+1);
                                    swap(Heroes[x],Heroes[x+1]);
                                }
                            }
                            cout << Units[turn].second->returnName() << " #" << Units[turn].second->returnNumber() << " moved backwards;" << endl << endl;
                        }
                        else{
                            cout << "Wrong Input, game terminated" << endl;
                            exit(0);
                        }

                    }
                    else if(Units[turn].second->returnPosition()==4){
                        for(int x=0;x<heroCount;x++){
                            if (Units[turn].second->returnName()==Heroes[x].first->returnName() && Units[turn].second->returnNumber()==Heroes[x].first->returnNumber()){
                                move::moveSkillH(Heroes[x].first,x-1);
                                move::moveSkillH(Heroes[x-1].first,x);
                                swap(Heroes[x],Heroes[x-1]);
                            }
                        }
                        cout << Units[turn].second->returnName() << " #" << Units[turn].second->returnNumber() << " moved forward;" << endl << endl;
                    }
                }
            }
            else if(userChoice.first == "Bone Soldier"){
                int defender=0;
                if(userChoice.second == 1){
                    if(heroCount==4 || heroCount==3){
                        defender=rand() % 3;
                    }
                    else if(heroCount==2){
                        defender=rand() % 2;
                    }
                    else if(heroCount==1){
                        defender=0;
                    }
                    bool death=false;
                    bool deathsDoorMain = graveyardSlash::graveyardSlashAttack(Units[turn].second, Heroes[defender].first);
                    cout << endl << endl;
                    if(deathsDoorMain){
                        death = Heroes[defender].first->death();
                    }
                    if(death){
                        cout << Heroes[defender].first->returnName() << " #" << Heroes[defender].first->returnNumber() << " has died;";
                        for(int x=0;x<unitCount;x++){
                            if (Units[x].second->returnName()==Heroes[defender].first->returnName() && Units[x].second->returnNumber()==Heroes[defender].first->returnNumber()){
                                Units.erase(Units.begin() + x);

                            }
                        }
                        Heroes.erase(Heroes.begin() + defender);
                        unitCount--;
                        heroCount--;
                        for(int i=0;i<heroCount;i++){
                            Heroes[i].first->updatePosition(defender+1);
                            Heroes[i].second = Heroes[i].first->returnPosition();
                        }
                    }
                    if(heroCount==0){
                        //need to output surviving monsters (use same system pull protected data) - ez
                        cout << "The Heroes have Fallen. Game Over!" << endl;
                        return 0;
                    }
                }
                else if(userChoice.second == 2){
                    if(heroCount==1){
                        defender=0;
                    }
                    else{
                        defender=rand() % 2;
                    }
                    bool death=false;
                    bool deathsDoorMain = graveyardStumble::graveyardStumbleAttack(Units[turn].second, Heroes[defender].first);
                    cout << endl << endl;
                    if(deathsDoorMain){
                        death = Heroes[defender].first->death();
                    }
                    if(death){
                        cout << Heroes[defender].first->returnName() << " #" << Heroes[defender].first->returnNumber() << " has died;";
                        for(int x=0;x<unitCount;x++){
                            if (Units[x].second->returnName()==Heroes[defender].first->returnName() && Units[x].second->returnNumber()==Heroes[defender].first->returnNumber()){
                                Units.erase(Units.begin() + x);

                            }
                        }
                        Heroes.erase(Heroes.begin() + defender);
                        unitCount--;
                        heroCount--;
                        for(int i=0;i<heroCount;i++){
                            Heroes[i].first->updatePosition(defender+1);
                            Heroes[i].second = Heroes[i].first->returnPosition();
                        }

                    }
                    if(heroCount==0){
                        //need to output surviving monsters (use same system pull protected data) - ez
                        cout << "The Heroes have Fallen. Game Over!" << endl;
                        return 0;
                    }
                }
                else if(userChoice.second == 3){
                    //move
                    if(Units[turn].second->returnPosition()==1){
                        for(int x=monsterCount-1;x<monsterCount && x>=0;x--){
                            if (Units[turn].second->returnName()==Monsters[x].first->returnName() && Units[turn].second->returnNumber()==Monsters[x].first->returnNumber()){
                                move::moveSkillM(Monsters[x+1].first,x);
                                move::moveSkillM(Monsters[x].first,x+1);
                                swap(Monsters[x],Monsters[x+1]);
                            }
                        }
                        cout << Units[turn].second->returnName() << " #" << Units[turn].second->returnNumber() << " moved backwards;" << endl << endl;
                    }
                    else if(Units[turn].second->returnPosition()==2 ||Units[turn].second->returnPosition()==3){
                        int moveChoice=rand() % 2 + 1;
                        if(moveChoice==1){
                            for(int x=0;x<monsterCount;x++){
                                if (Units[turn].second->returnName()==Monsters[x].first->returnName() && Units[turn].second->returnNumber()==Monsters[x].first->returnNumber()){
                                    move::moveSkillM(Monsters[x].first,x-1);
                                    move::moveSkillM(Monsters[x-1].first,x);
                                    swap(Monsters[x],Monsters[x-1]);
                                }
                            }
                            cout << Units[turn].second->returnName() << " #" << Units[turn].second->returnNumber() << " moved forward;" << endl << endl;
                        }
                        else if(moveChoice==2){
                            for(int x=monsterCount-1;x<monsterCount && x>=0;x--){
                                if (Units[turn].second->returnName()==Monsters[x].first->returnName() && Units[turn].second->returnNumber()==Monsters[x].first->returnNumber()){
                                    move::moveSkillM(Monsters[x+1].first,x);
                                    move::moveSkillM(Monsters[x].first,x+1);
                                    swap(Monsters[x],Monsters[x+1]);
                                }
                            }
                            cout << Units[turn].second->returnName() << " #" << Units[turn].second->returnNumber() << " moved backwards;" << endl << endl;
                        }
                    }
                    else if(Units[turn].second->returnPosition()==4){
                        for(int x=0;x<monsterCount;x++){
                            if (Units[turn].second->returnName()==Monsters[x].first->returnName() && Units[turn].second->returnNumber()==Monsters[x].first->returnNumber()){
                                move::moveSkillM(Monsters[x].first,x+1);
                                move::moveSkillM(Monsters[x+1].first,x);
                                swap(Monsters[x],Monsters[x-1]);
                            }
                        }
                        cout << Units[turn].second->returnName() << " #" << Units[turn].second->returnNumber() << " moved forward;" << endl << endl;
                    }
                }
            }
            else if(userChoice.first == "Bone Defender"){
                int defender=0;
                if(userChoice.second == 1){
                    if(heroCount==1){
                        defender=0;
                    }
                    else{
                        defender=rand() % 2;
                    }
                    bool death=false;
                    bool deathsDoorMain = axeblade::axebladeAttack(Units[turn].second, Heroes[defender].first);
                    cout << endl << endl;
                    if(deathsDoorMain){
                        death = Heroes[defender].first->death();
                    }
                    if(death){
                        cout << Heroes[defender].first->returnName() << " #" << Heroes[defender].first->returnNumber() << " has died;";
                        for(int x=0;x<unitCount;x++){
                            if (Units[x].second->returnName()==Heroes[defender].first->returnName() && Units[x].second->returnNumber()==Heroes[defender].first->returnNumber()){
                                Units.erase(Units.begin() + x);

                            }
                        }
                        Heroes.erase(Heroes.begin() + defender);
                        unitCount--;
                        heroCount--;
                        for(int i=0;i<heroCount;i++){
                            Heroes[i].first->updatePosition(defender+1);
                            Heroes[i].second = Heroes[i].first->returnPosition();
                        }

                    }
                    if(heroCount==0){
                        //need to output surviving monsters (use same system pull protected data) - ez
                        cout << "The Heroes have Fallen. Game Over!" << endl;
                        return 0;
                    }
                }
                else if(userChoice.second == 2){
                    if(heroCount==1){
                        defender=0;
                    }
                    else{
                        defender=rand() % 2;
                    }
                    bool death=false;
                    bool deathsDoorMain = deadWeight::deadWeightAttack(Units[turn].second, Heroes[defender].first);
                    cout << endl << endl;
                    if(deathsDoorMain){
                        death = Heroes[defender].first->death();
                    }
                    if(death){
                        cout << Heroes[defender].first->returnName() << " #" << Heroes[defender].first->returnNumber() << " has died;";
                        for(int x=0;x<unitCount;x++){
                            if (Units[x].second->returnName()==Heroes[defender].first->returnName() && Units[x].second->returnNumber()==Heroes[defender].first->returnNumber()){
                                Units.erase(Units.begin() + x);

                            }
                        }
                        Heroes.erase(Heroes.begin() + defender);
                        unitCount--;
                        heroCount--;
                        for(int i=0;i<heroCount;i++){
                            Heroes[i].first->updatePosition(defender+1);
                            Heroes[i].second = Heroes[i].first->returnPosition();
                        }

                    }
                    if(heroCount==0){
                        //need to output surviving monsters (use same system pull protected data) - ez
                        cout << "The Heroes have Fallen. Game Over!" << endl;
                        return 0;
                    }
                }
                else if(userChoice.second == 3){
                    defender=rand() % monsterCount;
                    knittingBones::knittingBonesSkill(Units[turn].second,Monsters[defender].first);
                }
                else if(userChoice.second == 4){
                    //move
                    if(Units[turn].second->returnPosition()==1){
                        for(int x=monsterCount-1;x<monsterCount && x>=0;x--){
                            if (Units[turn].second->returnName()==Monsters[x].first->returnName() && Units[turn].second->returnNumber()==Monsters[x].first->returnNumber()){
                                move::moveSkillM(Monsters[x+1].first,x);
                                move::moveSkillM(Monsters[x].first,x+1);
                                swap(Monsters[x],Monsters[x+1]);
                            }
                        }
                        cout << Units[turn].second->returnName() << " #" << Units[turn].second->returnNumber() << " moved backwards;" << endl << endl;
                    }
                    else if(Units[turn].second->returnPosition()==2 ||Units[turn].second->returnPosition()==3){
                        int moveChoice=rand() % 2 + 1;
                        if(moveChoice==1){
                            for(int x=0;x<monsterCount;x++){
                                if (Units[turn].second->returnName()==Monsters[x].first->returnName() && Units[turn].second->returnNumber()==Monsters[x].first->returnNumber()){
                                    move::moveSkillM(Monsters[x].first,x-1);
                                    move::moveSkillM(Monsters[x-1].first,x);
                                    swap(Monsters[x],Monsters[x-1]);
                                }
                            }
                            cout << Units[turn].second->returnName() << " #" << Units[turn].second->returnNumber() << " moved forward;" << endl << endl;
                        }
                        else if(moveChoice==2){
                            for(int x=monsterCount-1;x<monsterCount && x>=0;x--){
                                if (Units[turn].second->returnName()==Monsters[x].first->returnName() && Units[turn].second->returnNumber()==Monsters[x].first->returnNumber()){
                                    move::moveSkillM(Monsters[x+1].first,x);
                                    move::moveSkillM(Monsters[x].first,x+1);
                                    swap(Monsters[x],Monsters[x+1]);
                                }
                            }
                            cout << Units[turn].second->returnName() << " #" << Units[turn].second->returnNumber() << " moved backwards;" << endl << endl;
                        }
                    }
                    else if(Units[turn].second->returnPosition()==4){
                        for(int x=0;x<monsterCount;x++){
                            if (Units[turn].second->returnName()==Monsters[x].first->returnName() && Units[turn].second->returnNumber()==Monsters[x].first->returnNumber()){
                                move::moveSkillM(Monsters[x].first,x-1);
                                move::moveSkillM(Monsters[x-1].first,x);
                                swap(Monsters[x],Monsters[x-1]);
                            }
                        }
                        cout << Units[turn].second->returnName() << " #" << Units[turn].second->returnNumber() << " moved forward;" << endl << endl;
                    }
                }
            }

        userChoice.first.clear();
        }
        cout << "End of Round " << round << endl << endl;
    }
    return 0;
}