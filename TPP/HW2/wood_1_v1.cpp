#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unistd.h>
#include <unordered_map>
#include <cmath>

using namespace std;

class BaseEntity
{
    public:
        BaseEntity(int id, int type, int x, int y, int shield_life, int is_controlled, int health);
        const pair<int, int> get_position() const;
        const int& getID() const { return id_; };
        const int& getType() const { return type_; };
        const int& getShieldLife() const { return shield_life_; };
        const int& getIsControlled() const { return is_controlled_; };
        const int& getHealth() const { return health_; };
    private:
        int id_;                // Unique identifier
        int type_;              // 0=monster, 1=your hero, 2=opponent hero
        int x_;                 // Position of this entity
        int y_;
        int shield_life_;       // Ignore for this league; Count down until shield spell fades
        int is_controlled_;     // Ignore for this league; Equals 1 when this entity is under a control spell
        int health_;            // Remaining health of this monster
};

BaseEntity::BaseEntity(int id, int type, int x, int y, int shield_life, int is_controlled, int health)
{
    id_ = id;
    type_ = type;
    x_ = x;
    y_ = y;
    shield_life_ = shield_life;
    is_controlled_ = is_controlled;
    health_ = health;
}

const pair<int, int> BaseEntity::get_position() const
{
    return make_pair(x_, y_);
}

class HeroEntity
{
    public:
        HeroEntity();
        HeroEntity(int id, int type, int x, int y, int shield_life, int is_controlled, int health, int start_x, int start_y);
        const pair<int, int> get_position() const;
        const int& getID() const { return id_; };
        const int& getType() const { return type_; };
        const int& getShieldLife() const { return shield_life_; };
        const int& getIsControlled() const { return is_controlled_; };
        const int& getHealth() const { return health_; }; 
    private:
        int id_;                // Unique identifier
        int type_;              // 0=monster, 1=your hero, 2=opponent hero
        int x_;                 // Position of this entity
        int y_;
        int shield_life_;       // Ignore for this league; Count down until shield spell fades
        int is_controlled_;     // Ignore for this league; Equals 1 when this entity is under a control spell
        int health_;            // Remaining health of this monster
        int start_x_;
        int start_y_;
};

HeroEntity::HeroEntity()
{
    id_ = -1;
}
HeroEntity::HeroEntity(int id, int type, int x, int y, int shield_life, int is_controlled, int health, int start_x, int start_y)
{
    id_ = id;
    type_ = type;
    x_ = x;
    y_ = y;
    shield_life_ = shield_life;
    is_controlled_ = is_controlled;
    health_ = health;
    start_x_ = start_x;
    start_y_= start_y;
}

const pair<int, int> HeroEntity::get_position() const
{
    return make_pair(x_, y_);
}

class MonsterEntity
{
    public:
        MonsterEntity();
        MonsterEntity(int id, int type, int x, int y, int shield_life, int is_controlled, int health, int vx, int vy, int near_base, int threat_for);
        const pair<int, int> get_position() const;
        const int& getID() const { return id_; };
        const int& getType() const { return type_; };
        const int& getShieldLife() const { return shield_life_; };
        const int& getIsControlled() const { return is_controlled_; };
        const int& getHealth() const { return health_; };  
        const int& getVx() const { return vx_; };
        const int& getVy() const { return vy_; };
        const int& isNearBase() const { return near_base_; };
        const int& getThreat() const { return threat_for_; };
        const int& getRankofMonster() const { return rank_; };
        void setRankofMonster(int r) { rank_ = r; };
    private:
        int id_;                // Unique identifier
        int type_;              // 0=monster, 1=your hero, 2=opponent hero
        int x_;                 // Position of this entity
        int y_;
        int shield_life_;       // Ignore for this league; Count down until shield spell fades
        int is_controlled_;     // Ignore for this league; Equals 1 when this entity is under a control spell
        int health_;            // Remaining health of this monster
        int vx_;                // Trajectory of this monster
        int vy_;
        int near_base_;         // 0=monster with no target yet, 1=monster targeting a base
        int threat_for_;        // Given this monster's trajectory, is it a threat to 1=your base, 2=your opponent's base, 0=neither
        int rank_;              // rank for sort to determind what is threat level
};
MonsterEntity::MonsterEntity()
{
    id_ = -1;
}
MonsterEntity::MonsterEntity(int id, int type, int x, int y, int shield_life, int is_controlled, int health, int vx, int vy, int near_base, int threat_for)
{
    id_ = id;
    type_ = type;
    x_ = x;
    y_ = y;
    shield_life_ = shield_life;
    is_controlled_ = is_controlled;
    health_ = health;
    vx_ = vx;
    vy_ = vy;
    near_base_ = near_base;
    threat_for_ = threat_for;
}

const pair<int, int> MonsterEntity::get_position() const
{
    return make_pair(vx_, vy_);
}

// https://www.geeksforgeeks.org/sort-vector-of-pairs-in-ascending-order-in-c/#:~:text=Space%3A%20O(1)-,Case%202,-%3A%20Sorting%20the%20vector
// Driver function to sort the vector elements
// by second element of pairs
bool sortbysec(const pair<MonsterEntity,int> &a, const pair<MonsterEntity,int> &b)
{
    return (a.second < b.second);
}

int main()
{
    int base_x; // The corner of the map representing your base
    int base_y;
    cin >> base_x >> base_y; cin.ignore();

    int heroes_per_player; // Always 3
    cin >> heroes_per_player; cin.ignore();

    // game loop
    while (1) {
        unordered_map<int, MonsterEntity>spiders;
        // unordered_map<int, HeroEntity>myHeros;
        vector< HeroEntity >myHeros(heroes_per_player);
        // unordered_map<int, HeroEntity>enemyHeros;

        int my_health, enemy_health;
        int my_mana, enemy_mana; 

        cin >> my_health >> my_mana; cin.ignore();
        cin >> enemy_health >> enemy_mana; cin.ignore();

        int entity_count; // Amount of heros and monsters you can see
        cin >> entity_count; cin.ignore();

        // set start loction to set defence pattern
        vector<pair<int, int>>init_loc = {
            make_pair(600, 600),
            make_pair(1500, 4500),
            make_pair(4500, 1500)
        };

        // monster, threat_level
        vector< pair< MonsterEntity, int > >spiders_rank;

        for (int i = 0; i < entity_count; i++) 
        {
            // ignore for this league
            // shield_life + is_controlled
            int id;                // Unique identifier
            int type;              // 0=monster, 1=your hero, 2=opponent hero
            int x;                 // Position of this entity
            int y;
            int shield_life;       // Ignore for this league; Count down until shield spell fades
            int is_controlled;     // Ignore for this league; Equals 1 when this entity is under a control spell
            int health;            // Remaining health of this monster
            int vx;                // Trajectory of this monster
            int vy;
            int near_base;         // 0=monster with no target yet, 1=monster targeting a base
            int threat_for;        // Given this monster's trajectory, is it a threat to 1=your base, 2=your opponent's base, 0=neither

            cin >> id >> type >> x >> y >> shield_life >> is_controlled >> health >> vx >> vy >> near_base >> threat_for; cin.ignore();
            // memoized count of my heros
            int myHerosCNT = 0;
            // 1: one of your heroes
            if (type == 1)
            {
                HeroEntity tmp(id, type, x, y, shield_life, is_controlled, health, init_loc[myHerosCNT].first, init_loc[myHerosCNT].second);
                myHeros[myHerosCNT++] = tmp;
                // myHeros[id] = tmp;
                // myHerosCNT++;
            }

            // 0: a monster
            if (type == 0)
            {
                MonsterEntity tmp(id, type, x, y, shield_life, is_controlled, health, vx, vy, near_base, threat_for);
                spiders[id] = tmp;
                int threat_level = 0;
                // monster is targeting my base
                if(near_base == 1 && threat_for == 1)
                {
                    threat_level = 1000;
                }
                else if(near_base == 1)
                {
                    threat_level = 500;
                }

                int dist = hypot(base_x - x, base_y - y);
                threat_level += 3000*(1/(dist+1));
                if(dist < 7000)
                {
                    spiders_rank.emplace_back(tmp, threat_level);
                }
            }
        }

        cerr << spiders_rank.size() << endl;

        sort(spiders_rank.rbegin(), spiders_rank.rend(), sortbysec);

        if( spiders_rank.size() == 0 )
        {
            for (int i = 0; i < heroes_per_player; i++) 
            {
                cout << "MOVE " << init_loc[i].first << " " << init_loc[i].second << endl; 
            }
        }
        else
        {
            cerr << spiders[spiders_rank[0].first.getID()].get_position().first << endl;
            // can call wind here
            if(my_mana > 10)
            {
                double dist = hypot(myHeros[0].get_position().first - spiders_rank[0].first.get_position().first, myHeros[0].get_position().second - spiders_rank[0].first.get_position().second);
                if(dist < 1280)
                {
                    cout << "SPELL WIND 17630 9000" << endl;
                    my_mana -= 10; 
                }
                else
                {
                    cout << "MOVE " << spiders_rank[0].first.get_position().first << " " << spiders_rank[0].first.get_position().second << endl;
                }
            }
            cout << "MOVE " << spiders_rank[0].first.get_position().first << " " << spiders_rank[0].first.get_position().second << endl;
        }
    }
}