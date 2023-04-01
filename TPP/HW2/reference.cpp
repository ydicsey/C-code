#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include<climits>
#include<utility>
#include<math.h>
using namespace std;


class baseEntity
{
public:
    baseEntity(int i, int t, int xx, int yy, int sl, int ic, int h);
    baseEntity();
    ~baseEntity();
    int getX();
    int getY();
    int getID();
    int getType();
    int getShieldLife();
    int getHealth();
    int getControlled();
protected:
    int id; // Unique identifier
    int type; // 0=monster, 1=your hero, 2=opponent hero
    int x; // Position of this entity
    int y;
    int shield_life; //  Count down until shield spell fades
    int is_controlled; // Equals 1 when this entity is under a control spell
    int health; // Remaining health of this monster
};

baseEntity::baseEntity(int i, int t, int xx, int yy, int sl, int ic, int h)
{
    id = i;
    type = t;
    x = xx;
    y = yy;
    shield_life = sl;
    is_controlled = ic;
    health = h;
}

baseEntity::baseEntity()
{
}

baseEntity::~baseEntity()
{
}
int baseEntity::getX()
{
    return x;
}
int baseEntity::getY()
{
    return y;
}
int baseEntity::getID()
{
    return id;
}
int baseEntity::getType()
{
    return type;
}
int baseEntity::getShieldLife()
{
    return shield_life;
}
int baseEntity::getHealth()
{
    return health;
}

int baseEntity::getControlled()
{
    return is_controlled;
}
class Hero : public baseEntity
{
public:
    Hero(int i, int t, int xx, int yy, int sl, int ic, int h, int dx, int dy);
    Hero();
    ~Hero();

private:
    int default_x;
    int default_y;
};

Hero::Hero(int i, int t, int xx, int yy, int sl, int ic, int h, int dx, int dy) : baseEntity(i, t, xx, yy, sl, ic, h)
{
    default_x = dx;
    default_y = dy;
}

Hero::Hero() :baseEntity()
{
}

Hero::~Hero()
{
}
class Monster : public baseEntity
{
public:
    Monster(int i, int t, int xx, int yy, int sl, int ic, int h, int vxx, int vyy, int nb, int tf, bool iA);
    Monster();
    ~Monster();
    int get_near_base();
    int get_threadFor();
    int getVX();
    int getVY();
    void set_rank(int r);
    int get_rank();
    
private:
    int vx; // Trajectory of this monster
    int vy;
    int near_base; // 0=monster with no target yet, 1=monster targeting a base
    int threat_for; // Given this monster's trajectory, is it a threat to 1=your base, 2=your 
    int rank;//spider rank inicates the level of danger
    bool isAttacked;//to check if it's attacked ??
};

Monster::Monster(int i, int t, int xx, int yy, int sl, int ic, int h, int vxx, int vyy, int nb, int tf, bool iA) : baseEntity(i, t, xx, yy, sl, ic, h)
{
    rank = 0;
    isAttacked = iA;
    near_base = nb;
    threat_for = tf;
}

Monster::Monster() :baseEntity()
{
    id = -1;//to know that monster is without initialization
}


Monster::~Monster()
{
}

int Monster::get_near_base()
{
    return near_base;
}

int Monster::get_threadFor()
{
    return threat_for;
}

int Monster::getVX()
{
    return vx;
}
int Monster::getVY()
{
    return vy;
}
void Monster::set_rank(int r)
{
    rank = r;
}
int Monster::get_rank()
{
    return rank;
}



//sorting method
bool sortbysec(const pair<Monster, int>& a, const pair<Monster, int>& b)
{
    return (a.second < b.second);
}

int main()
{
    int base_x, enemy_x; // The corner of the map representing your base
    int base_y, enemy_y;
    cin >> base_x >> base_y; cin.ignore();

    vector<pair<int, int>>default_positions(3);//default positions for  my heros
    if (base_x == 0 && base_y == 0)
    {
        default_positions[0].first = 13630;
        default_positions[0].second = 6000;
        default_positions[1].first = 5000;
        default_positions[1].second = 1500;
        default_positions[2].first = 2500;
        default_positions[2].second = 4500;
        enemy_x = 17630;
        enemy_y = 9000;
    }
    else {
        default_positions[0].first = 4000;
        default_positions[0].second = 3000;
        default_positions[1].first = 12500;
        default_positions[1].second = 7000;
        default_positions[2].first = 15500;
        default_positions[2].second = 4000;
        enemy_x = enemy_y = 0;
    }

    int heroes_per_player; // Always 3
    cin >> heroes_per_player; cin.ignore();

    int controlCount = 0;
    // game loop
    while (1)
    {
        int my_health, enemy_health; // Each player's base health
        int my_mana, enemy_mana; // Ignore in the first league; Spend ten mana to cast a spell
        //Taking base inputs from the user 
        cin >> my_health >> my_mana; cin.ignore();
        cin >> enemy_health >> enemy_mana; cin.ignore();

        int entity_count; // Amount of heros and monsters you can see
        cin >> entity_count; cin.ignore();

        //maps to store the data we initialize it every iteration in order to have updated values
        unordered_map<int, Monster>Spiders;
        unordered_map<int, Hero>myHeros;
        unordered_map<int, Hero>enemyHeros;

        vector<pair<Monster, int>>spider_ranked;//vector to rank the spiders in
        vector<Hero>ordered_heros;
        int dcount1 = 0, dcount2 = 0;
        //loop of taking input for each entity
        for (int i = 0; i < entity_count; i++) {
            int id; // Unique identifier
            int type; // 0=monster, 1=your hero, 2=opponent hero
            int x; // Position of this entity
            int y;
            int shield_life; // Ignore for this league; Count down until shield spell fades
            int is_controlled; // Ignore for this league; Equals 1 when this entity is under a control spell
            int health; // Remaining health of this monster
            int vx; // Trajectory of this monster
            int vy;
            int near_base; // 0=monster with no target yet, 1=monster targeting a base
            int threat_for; // Given this monster's trajectory, is it a threat to 1=your base, 2=your opponent's base, 0=neither
            cin >> id >> type >> x >> y >> shield_life >> is_controlled >> health >> vx >> vy >> near_base >> threat_for; cin.ignore();

            if (type == 0)//monster
            {
                Monster m(id, type, x, y, shield_life, is_controlled, health, vx, vy, near_base, threat_for, false);
                Spiders[id] = m;
                int thread_level = 0;
                if (near_base == 1 && threat_for == 1)
                {
                    thread_level = 1000;
                }
                else if (threat_for == 1) {
                    thread_level = 500;
                }
                double dist = sqrt(pow(base_x - x - vx, 2) + pow(base_y - y - vy, 2));
                thread_level += 3000 * (1 / (dist + 1));//the thread level is inverse propotion to the dist
                //less distance means higher thread
                if (dist <= 6500)
                {
                    spider_ranked.push_back(make_pair(m, thread_level));//this list for deffence only
                }
            }
            else if (type == 1) {//my hero
                Hero myH(id, type, x, y, shield_life, is_controlled, health, default_positions[dcount1].first, default_positions[dcount1].second);
                myHeros[id] = myH;
                ordered_heros.push_back(myH);
                dcount1++;
            }
            else {//enemy hero
                Hero enemyH(id, type, x, y, shield_life, is_controlled, health, -1, -1);
                enemyHeros[id] = enemyH;
                dcount2++;
            }
        }

        sort(spider_ranked.rbegin(), spider_ranked.rend(), sortbysec);//sort desc

        if (/*my_health < 3 || */my_mana < 100)
        {
            if (base_x == 0 && base_y == 0)//deffence mode
            {
                default_positions[0].first = 4000;
                default_positions[0].second = 3000;
            }
            else {
                default_positions[0].first = 14000;
                default_positions[0].second = 5500;
            }
        }
        //inital position for the heros
        if (spider_ranked.size() == 0)//if there is no spiders move to the initail position
        {
            int i = 0;
            for (auto myHero = myHeros.begin(); myHero !=myHeros.end(); myHero++)
            {
                bool hitHero = false;//attack the opponent hero

                if (my_mana>=10)
                {
                    for (auto enemyHero = enemyHeros.begin(); enemyHero != enemyHeros.end(); enemyHero++)
                    {
                        double enemyHero_to_myBase = sqrt(pow(base_x - enemyHero->second.getX(), 2) + pow(base_y - enemyHero->second.getY(), 2));
                        double heroTohero = sqrt(pow(myHero->second.getX() - enemyHero->second.getX(), 2) + pow(myHero->second.getY() - enemyHero->second.getY(), 2));
                        if (heroTohero <= 2200 && enemyHero->second.getShieldLife() == 0 && enemyHero_to_myBase <= 6000)
                        {//if the distance between enemy hero and the base less than 6000 control the hero to perevent it to reac
                            cout << "SPELL CONTROL " << enemyHero->second.getID() << " " << enemy_x << " " << enemy_y << endl;
                            //if there is a near hero control it to my base 
                            my_mana -= 10;
                            hitHero = true;
                            break;
                        }
                    }
                }
                if(!hitHero) {

                    cout << "MOVE " << default_positions[i].first << " " << default_positions[i].second << endl;
                }
                i++;
            }

        }
        // if spider_rank.size != 0
        else
        {
            //ATTACKER CODE
            bool spellSpider = false;//spell a spider
            bool hitHero = false;//attack the opponent hero

            if (/*my_health < 3 || */my_mana < 100)//DEFENCE MODE
            {//if my health decreasd or my mana is not enough to attack
                controlCount = 0;//re-initialize the conrolCount so that when I enter the attacking mode I count 3 controls
                if (my_mana >= 10)
                {
                    for (auto it = enemyHeros.begin(); it != enemyHeros.end(); it++)
                    {
                        double enemyHero_to_enemyBase = sqrt(pow(enemy_x - it->second.getX(), 2) + pow(enemy_y - it->second.getY(), 2));
                        double heroTohero = sqrt(pow(ordered_heros[0].getX() - it->second.getX(), 2) + pow(ordered_heros[0].getY() - it->second.getY(), 2));
                        if (heroTohero <= 2200 && it->second.getShieldLife() == 0 && enemyHero_to_enemyBase <= 5000)
                        {//if the distance between enemy hero and the base less than 6000 control the hero to perevent it to reac
                            cout << "SPELL CONTROL " << it->second.getID() << " " << base_x << " " << base_y << endl;
                            //if there is a near hero control it to my base 
                            my_mana -= 10;
                            hitHero = true;
                            break;
                        }
                    }
                    if (!hitHero) {
                        double myDist = sqrt(pow(ordered_heros[0].getX() - (spider_ranked[0].first.getX()), 2) + pow(ordered_heros[0].getY() - (spider_ranked[0].first.getY()), 2));
                        if (spider_ranked[0].first.getShieldLife() == 0)
                        {
                            if (myDist <= 1280) {
                                cout << "SPELL WIND " << enemy_x << " " << enemy_y << endl;
                                spellSpider = true;
                                my_mana -= 10;
                            }
                        }
                    }
                }
                if (!spellSpider&&!hitHero)//if you won't spell move to the most dangerous spider to spell it the next round
                {
                    cout << "MOVE " << spider_ranked[0].first.getX() << " " << spider_ranked[0].first.getY() << endl;
                }
            }
            //deffense code
            vector<Monster>first_targets(2);
            int thread_x = spider_ranked[0].first.getX();
            int thread_y = spider_ranked[0].first.getY();
            double dist1 = sqrt(pow(ordered_heros[1].getX() - thread_x, 2) + pow(ordered_heros[1].getY() - thread_y, 2));
            double dist2 = sqrt(pow(ordered_heros[2].getX() - thread_x, 2) + pow(ordered_heros[2].getY() - thread_y, 2));
            if (dist1 < dist2)
            {
                first_targets[0] = spider_ranked[0].first;
            }
            else {
                first_targets[1] = spider_ranked[0].first;
            }
            if (spider_ranked.size() > 1)//second most threating
            {
                for (int k = 0; k < 2; k++)
                {
                    if (first_targets[k].getID() == -1)
                    {
                        first_targets[k] = spider_ranked[1].first;
                        break;
                    }
                }
            }
            for (int i = 0; i < 2; i++)
            {
                /*double spiderToMybase = sqrt(pow(base_x - first_targets[i].getX(), 2) + pow(base_y - first_targets[i].getY(), 2));*/
                spellSpider = false;
                hitHero = false;
                if (first_targets[i].getID() != -1)//if there is a spider to attack
                {
                    if (my_mana >= 10)
                    {
                        double myDist = sqrt(pow(ordered_heros[i + 1].getX() - (first_targets[i].getX()), 2) + pow(ordered_heros[i + 1].getY() - (first_targets[i].getY()), 2));
                        if (first_targets[i].getShieldLife() == 0)//distance to make control or shield
                        {
                            if (myDist <= 1280) {

                                cout << "SPELL WIND " << enemy_x << " " << enemy_y << endl;
                                spellSpider = true;
                                if(i==0)
                                    my_mana -= 10;
                                continue;
                            }

                        }
                    }
                    if (!spellSpider)//if you won't spell move to the most dangerous spider
                    {
                        cout << "MOVE " << first_targets[i].getX() << " " << first_targets[i].getY() << endl;

                    }
                }
                else {
                    for (auto it = enemyHeros.begin(); it != enemyHeros.end(); it++)
                    {
                        double enemyHero_to_myBase = sqrt(pow(base_x - it->second.getX(), 2) + pow(base_y - it->second.getY(), 2));
                        double heroTohero = sqrt(pow(ordered_heros[i + 1].getX() - it->second.getX(), 2) + pow(ordered_heros[i + 1].getY() - it->second.getY(), 2));
                        if (it->second.getShieldLife() == 0 && enemyHero_to_myBase <= 7000)
                        {//if the distance between enemy hero and the base less than 6000 control the hero to perevent it 
                            if (heroTohero <= 1280)
                            {
                                cout << "SPELL WIND " << enemy_x << " " << enemy_y << endl;
                                if (i == 0)
                                    my_mana -= 10;
                                hitHero = true;
                                break;
                            }
                            else if (heroTohero <= 2200) {
                                cout << "SPELL CONTROL " << it->second.getID() << " " << enemy_x << " " << enemy_y << endl;
                                //if there is a near hero control it to my base 
                                if (i == 0)
                                    my_mana -= 10;
                                hitHero = true;
                                break;
                            }
                        }
                    }
                    if (!hitHero) {
                        cout << "MOVE " << spider_ranked[0].first.getX() << " " << spider_ranked[0].first.getY() << endl;
                    }
                }

            }
        }

    }
}