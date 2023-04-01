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
    vector<entity> enemy_monsters;
    vector<entity> neutral_monsters;

    // set first step
    vector<pair<int, int>>init_loc(3);
    if(base_x == 0)
    {
        init_loc[0].first = 4000;
        init_loc[0].second = 1500;
        init_loc[1].first = 3500;
        init_loc[1].second = 3500;
        init_loc[2].first = 1500;
        init_loc[2].second = 4000;
    }
    else
    {
        init_loc[0].first = 16200;
        init_loc[0].second = 5000;
        init_loc[1].first = 14000;
        init_loc[1].second = 6000;
        init_loc[2].first = 13000;
        init_loc[2].second = 7500;
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
        vector< pair<entity, double> > spiders_rank;

        for(int i = 0; i < entity_count; i++)
        {
            entity e;
            cin >> e.id >> e.type >> e.x >> e.y >> e.shield_life >> e.is_controlled >> e.health >> e.vx >> e.vy >> e.near_base >> e.threat_for; cin.ignore();
            if (e.type == 1)
            {
                my_heros.emplace_back(e);
            }
            if (e.type == 2)
            {
                enemy_heros.emplace_back(e);
            }
            if (e.type == 0 && e.threat_for == 0)
            {
                neutral_monsters.emplace_back(e);
            }
            if (e.type == 0 && e.threat_for == 1)
            {
                double dist = hypot(base_x - e.x, base_y - e.y);
                spiders_rank.emplace_back(make_pair(e, dist));
                my_monsters.emplace_back(e);
            }
            if (e.type == 0 && e.threat_for == 2)
            {
                enemy_monsters.emplace_back(e);
            } 
        }
        // 按distance由小到大排序
        sort(spiders_rank.begin(), spiders_rank.end(), sortbysec);

        int spelled_ = 0;

        for(int i = 0; i < heroes_per_player; i++)
        {
            if(spiders_rank.size() > 0)
            {
                if(my_mana > 10)
                {
                    double dist_hero_spider = hypot(my_heros[i].x - spiders_rank[0].first.x, my_heros[i].y - spiders_rank[0].first.y);
                    if(!spelled_ && spiders_rank[0].second < 1000 && dist_hero_spider < 1250)
                    {
                        spelled_ = 1;
                        my_mana -= 10;
                        cout << "SPELL WIND " << enemy_x << " " << enemy_y << endl;
                    }
                    else
                    {
                        if(spiders_rank[0].second < 2500)
                        {
                            cout << "MOVE " << spiders_rank[0].first.x << " " << spiders_rank[0].first.y << endl;
                        }
                        else
                        {
                            cout << "MOVE " << spiders_rank[i].first.x << " " << spiders_rank[i].first.y << endl;
                        }
                    }
                }
                else
                {
                    if(spiders_rank[0].second < 2500)
                    {
                        cout << "MOVE " << spiders_rank[0].first.x << " " << spiders_rank[0].first.y << endl;
                    }
                    else
                    {
                        cout << "MOVE " << spiders_rank[i].first.x << " " << spiders_rank[i].first.y << endl;
                    }
                }
            }
            else
            {
                cout << "MOVE " <<  init_loc[i].first << " " << init_loc[i] .second << endl;
            }
        }
    }
}