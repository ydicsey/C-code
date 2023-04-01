#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

class Entity {
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

    //最大血量
    int max_health;
    bool operator<(const Entity& other) const {
        return id < other.id;
    }
};

//int find_mindist(vector spider)
//{
   //int min_d;
    //for(auto i : spider)
    //{

    //}
//}
int main() {
    int base_x, base_y;
    cin >> base_x >> base_y;

    int heroes_per_player; // Always 3
    cin >> heroes_per_player;

    int round = 1;
    while (true) {
        int my_health, my_mana;
        cin >> my_health >> my_mana;

        int enemy_health, enemy_mana;
        cin >> enemy_health >> enemy_mana;

        int entity_count; // Amount of heros and monsters you can see
        cin >> entity_count;

        vector<Entity> spider;
        vector<Entity> my_heros;
        vector<Entity> enemy_heros;

        for (int i = 0; i < entity_count; i++) {
            Entity entity;
            cin >> entity.id >> entity.type >> entity.x >> entity.y >> entity.shield_life >>
                entity.is_controlled >> entity.health >> entity.vx >> entity.vy >>
                entity.near_base >> entity.threat_for;


            entity.max_health = entity.health;
            if (entity.type == 0) {
                spider.push_back(entity);
            } else if (entity.type == 1) {
                my_heros.push_back(entity);
            } else if (entity.type == 2) {
                enemy_heros.push_back(entity);
            } else {
                assert(false);
            }
        }
        
        int emergency = 0;
        int min_dist_spider_id;
        int min_dist = 10000;
        vector<pair<int, Entity>> spiders_rank;
        for (auto i : spider) {
            int threat_level = 0;
            if (i.near_base == 1 && i.threat_for == 1) {
                threat_level = 1000;
            } else if (i.near_base == 1) {
                threat_level = 500;
            }

            double dist = hypot(base_x - i.x, base_y - i.y);
            if(min_dist <= 1000)
                emergency = 1;
         
            if(dist<min_dist)
            {
                min_dist = dist;
                min_dist_spider_id = i.id;
            }
                

            //殘血加權
            threat_level += 9999999999 * (1 / (dist + 1)) + (i.max_health - i.health);
            
            spiders_rank.push_back(make_pair(threat_level, i));
            cerr << "Debug: "<< threat_level << " " << endl;
        }

        sort(spiders_rank.rbegin(), spiders_rank.rend());
    
        if(round < 160)
        {
            for (int i = 0; i < heroes_per_player; i++) {
            if(spiders_rank.size() > i && (i == 0 || i==1 || i==2))
            {   
                if(emergency == 1)
                {
                    if(base_x == 0 && base_y == 0)
                    {
                        cout << "SPELL WIND 16241 7025" << endl;
                    }
                    else
                    {
                        cout << "SPELL WIND 0 0" << endl;
                    }
                    emergency = 0;
                }
                else
                cout << "MOVE " << spiders_rank[i].second.x << " " << spiders_rank[i].second.y << endl;
            }
            else if (spiders_rank.size() > i && hypot(base_x - spiders_rank[0].second.x, base_y - spiders_rank[0].second.y) < 5000 ) {
                 cout << "MOVE " << spiders_rank[0].second.x << " " << spiders_rank[0].second.y << endl;
            }
            
            else {

                if(base_x == 0 && base_y == 0)
                {
                    if(i==0)
                        cout << "MOVE 9300 1398" << endl;
                    else if(i==1)
                        cout << "MOVE 8188 4297" << endl;
                    else if(i==2)
                        cout << "MOVE 2000 7403" << endl;
                }
                else
                {
                    if(i==0)
                        cout << "MOVE 16000 1600" << endl;
                    else if(i==1)
                        cout << "MOVE 12300 3400" << endl;
                    else if(i==2)
                        cout << "MOVE 9500 6703" << endl;
                }
                
            }
            }
        }
        else
        {
            for (int i = 0; i < heroes_per_player; i++) {
            if (spiders_rank.size() > 0 && hypot(base_x - spiders_rank[0].second.x, base_y - spiders_rank[0].second.y) < 5000 ) {
                if(emergency == 1)
                {
                    if(base_x == 0 && base_y == 0)
                    {
                        cout << "SPELL WIND 16241 7025" << endl;
                    }
                    else
                    {
                        cout << "SPELL WIND 0 0" << endl;
                    }
                    emergency = 0;
                }
                else
                    cout << "MOVE " << spiders_rank[0].second.x << " " << spiders_rank[0].second.y << endl;
            }
            else //no enemy detect
            {
                if(base_x == 0 && base_y == 0)
                {
                    cout << "MOVE 1800 2096" << endl;
                }
                else
                {
                    cout << "MOVE 16241 7025" << endl;
                }
                
            } 
            //else {
                //cout << "WAIT" << endl;
            //}
            }
        }
        

        round++;
    }

    return 0;
}