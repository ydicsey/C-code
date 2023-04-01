#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unistd.h>
#include <unordered_map>
#include <cmath>

using namespace std;

class entity
{
    public:
        int id;
        int type;
        int x;
        int y;
        int shield_life;
        int is_controlled;
        int health;
        int vx;
        int vy;
        int near_base;
        int threat_for;
        entity() { id = -1; };
};

// https://www.geeksforgeeks.org/sort-vector-of-pairs-in-ascending-order-in-c/#:~:text=Space%3A%20O(1)-,Case%202,-%3A%20Sorting%20the%20vector
// Driver function to sort the vector elements
// by second element of pairs
bool sortbysec(const pair<entity, double> &a, const pair<entity, double> &b)
{
    return (a.second < b.second);
}

int main()
{
    // The corner of the map representing your base
    int base_x, enemy_x; 
    int base_y, enemy_y;
    cin >> base_x >> base_y; cin.ignore();

    if(base_x == 0)
    {
        enemy_x = 17630;
        enemy_y = 9000;
    }
    else
    {
        enemy_x = 0;
        enemy_y = 0;
    }

    // Always 3
    int heroes_per_player; 
    cin >> heroes_per_player; cin.ignore();

    // use unordered map for target a monster
    // unordered_map<int ,entity> my_monsters;
    vector<entity> my_monsters;
    vector<entity> my_heros;
    vector<entity> enemy_heros;
    // vector<entity> enemy_monsters;
    // vector<entity> neutral_monsters;

    // set first step
    vector<pair<int, int>>init_loc(3);
    if(base_x == 0)
    {
        init_loc[0].first = 15400;
        init_loc[0].second = 6200;
        init_loc[1].first = 4500;
        init_loc[1].second = 2000;
        init_loc[2].first = 2000;
        init_loc[2].second = 4500;
    }
    else
    {
        init_loc[0].first = 17630 - 15400;
        init_loc[0].second = 9000 - 6200;
        init_loc[1].first = 17630 - 4500;
        init_loc[1].second = 9000 - 2000;
        init_loc[2].first = 17630 - 2000;
        init_loc[2].second = 9000 - 4500;
    }

    // game loop
    while(1)
    {
        int my_health, my_mana;
        int enemy_health, enemy_mana;
        cin >> my_health >> my_mana; cin.ignore();
        cin >> enemy_health >> enemy_mana; cin.ignore();

        // Amount of heros and monsters you can see
        int entity_count;
        cin >> entity_count; cin.ignore();

        // < spider, dist_from_base >
        // and sort it to find the most threat monster
        vector< pair<entity, double> > spiders_near_mybase_rank;
        vector< pair<entity, double> > spiders_near_enemybase_rank;
        vector< pair<entity, double> > spiders_aim_enemybase_rank;

        for(int i = 0; i < entity_count; i++)
        {
            entity e;
            cin >> e.id >> e.type >> e.x >> e.y >> e.shield_life >> e.is_controlled >> e.health >> e.vx >> e.vy >> e.near_base >> e.threat_for; cin.ignore();
            if (e.type == 1)
            {
                my_heros.emplace_back(e);
            }
            else if (e.type == 2)
            {
                enemy_heros.emplace_back(e);
            }
            else if (e.type == 0)
            {
                double dist_to_mybase = hypot(base_x - e.x, base_y - e.y);
                // double dist_to_attackhero = hypot(my_heros[0].x - e.x, my_heros[0].y - e.y);

                if(dist_to_mybase < 6500)
                {
                    spiders_near_mybase_rank.emplace_back(make_pair(e, dist_to_mybase));
                }
                my_monsters.emplace_back(e);
            }
        }
        // 按distance由小到大排序
        sort(spiders_near_mybase_rank.begin(), spiders_near_mybase_rank.end(), sortbysec);
        // sort(spiders_near_enemybase_rank.begin(), spiders_near_enemybase_rank.end(), sortbysec);
        // sort(spiders_aim_enemybase_rank.begin(), spiders_aim_enemybase_rank.end(), sortbysec);

        // attack hero => hero[0]
        int monster_near_attack = 0;
        for(auto it = my_monsters.begin(); it != my_monsters.end(); it++)
        {
            if(it->shield_life > 0)
            {
                continue;
            }
            int atk_x = my_heros[0].x;
            int atk_y = my_heros[0].y;
            double dist = hypot(it->x - atk_x, it->y - atk_y);
            if(dist <= 1000)
            {
                monster_near_attack = 1;
            }
        }
        if(my_mana > 10 && monster_near_attack)
        {
            cerr << "1" << endl;
            cout << "SPELL WIND " << enemy_x << " " << enemy_y << endl;
        }
        else
        {
            int move_x = init_loc[0].first;
            int move_y = init_loc[0].second;
            for(auto it = my_monsters.begin(); it != my_monsters.end(); it++)
            {
                double dist = hypot(it->x - enemy_x, it->y - enemy_y);
                if(dist < 5500)
                {
                    move_x = it->x;
                    move_y = it->y;
                }
            }
            cerr << "2" << endl;
            cout << "MOVE " << move_x << " " << move_y << endl;
        }

        // deffense heros => hero[1,2]
        if(spiders_near_mybase_rank.size())
        {
            vector<pair<int, int>> first_two_target(2);
            if(spiders_near_mybase_rank.size() == 1)
            {
                int threat_x = spiders_near_mybase_rank[0].first.x;
                int threat_y = spiders_near_mybase_rank[0].first.y;
                int dist1 = hypot(my_heros[1].x - threat_x, my_heros[1].y - threat_y);
                int dist2 = hypot(my_heros[2].x - threat_x, my_heros[2].y - threat_y);
                if(dist1 < dist2)
                {
                    first_two_target[0] = make_pair(threat_x, threat_y);
                    first_two_target[1] = make_pair(-1, -1);
                }
                else
                {
                    first_two_target[1] = make_pair(threat_x, threat_y);
                    first_two_target[0] = make_pair(-1, -1);
                }
            }
            else
            {
                int threat_x = spiders_near_mybase_rank[0].first.x;
                int threat_y = spiders_near_mybase_rank[0].first.y;
                int dist1 = hypot(my_heros[1].x - threat_x, my_heros[1].y - threat_y);
                int dist2 = hypot(my_heros[2].x - threat_x, my_heros[2].y - threat_y);
                if(dist1 < dist2)
                {
                    first_two_target[0] = make_pair(spiders_near_mybase_rank[0].first.x, spiders_near_mybase_rank[0].first.y);
                    first_two_target[1] = make_pair(spiders_near_mybase_rank[1].first.x, spiders_near_mybase_rank[1].first.y);
                }
                else
                {
                    first_two_target[1] = make_pair(spiders_near_mybase_rank[0].first.x, spiders_near_mybase_rank[0].first.y);
                    first_two_target[0] = make_pair(spiders_near_mybase_rank[1].first.x, spiders_near_mybase_rank[1].first.y);
                }
            }

            int spelled_ = 0;
            for(int i = 1; i < heroes_per_player; i++)
            {
                if(spiders_near_mybase_rank.size() > i)
                {
                    if(my_mana > 10 && spiders_near_mybase_rank[0].second < 1000 && !spelled_)
                    {
                        cerr << "3" << endl;
                        cout << "SPELL WIND " << enemy_x << " " << enemy_y << endl;
                        spelled_ = 1;
                    }
                    else if(first_two_target[i-1].first != -1)
                    {
                        cerr << "4" << endl;
                        cout << "MOVE " << first_two_target[i-1].first << " " << first_two_target[i-1].second << endl;
                    }
                    else
                    {
                        cerr << "5" << endl;
                        cout << "MOVE " << init_loc[i].first << " " << init_loc[i].second << endl; 
                    }
                }
                else
                {
                    cerr << "6" << endl;
                    cout << "MOVE " << init_loc[i].first << " " << init_loc[i].second << endl; 
                }
            }
        }
        else
        {
            for(int i = 1; i < heroes_per_player; i++)
            {
                cerr << "7" << endl;
                cout << "MOVE " << init_loc[i].first << " " << init_loc[i].second << endl;
            }
        }
    }
}