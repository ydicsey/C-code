import sys
import math

# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.

# base_x: The corner of the map representing your base
base_x, base_y = [int(i) for i in input().split()]
base_is_top = base_x == 0
enemy_x = 17630 - base_x
enemy_y = 9000 - base_y
heroes_per_player = int(input())  # Always 3

if base_is_top:
    default_pos = [(15199, 6225), (4706, 2033), (2033, 4706)]
else:
    default_pos = [(17630 - 15199, 9000 - 6225), (17630 - 4706, 9000 - 2033), (17630 - 2033, 9000 - 4706)]

# game loop
while True:
    my_health, my_mana = [int(j) for j in input().split()]
    enemy_health, enemy_mana = [int(j) for j in input().split()]
    entity_count = int(input())  # Amount of heros and monsters you can see
    
    spider = []
    my_heros = []
    enemy_heros = []
    for i in range(entity_count):
        # _id: Unique identifier
        # _type: 0=monster, 1=your hero, 2=opponent hero
        # x: Position of this entity
        # shield_life: Ignore for this league; Count down until shield spell fades
        # is_controlled: Ignore for this league; Equals 1 when this entity is under a control spell
        # health: Remaining health of this monster
        # vx: Trajectory of this monster
        # near_base: 0=monster with no target yet, 1=monster targeting a base
        # threat_for: Given this monster's trajectory, is it a threat to 1=your base, 2=your opponent's base, 0=neither
        _id, _type, x, y, shield_life, is_controlled, health, vx, vy, near_base, threat_for = [int(j) for j in input().split()]
        entity = {
            'id' :_id,
            'type' :_type,
            'x': x,
            'y' :y,
            'shield_life' :shield_life,
            'is_controlled': is_controlled,
            'health': health,
            'vx': vx,
            'vy': vy,
            'near_base': near_base,
            'threat_for' : threat_for
        }
        if _type == 0:
            spider.append(entity)
        elif _type == 1:
            my_heros.append(entity)
        elif _type == 2:
            enemy_heros.append(entity)
        else:
            assert False
    # attack
    spider_near_attack = False
    for it in spider:
        if it['shield_life'] > 0:
            continue
        atk_x = my_heros[0]['x']
        atk_y = my_heros[0]['y']
        spider_x = it['x']
        spider_y = it['y']
        dist = math.hypot(spider_x-atk_x, spider_y - atk_y)
        if dist <= 1280:
            spider_near_attack = True
    if my_mana >= 10 and spider_near_attack:
        print('SPELL WIND', enemy_x, enemy_y)
    else:
        target_x = default_pos[0][0]
        target_y = default_pos[0][1]
        for it in spider:
            spider_x = it['x']
            spider_y = it['y']
            dist = math.hypot(spider_x - enemy_x, spider_y - enemy_y)
            if dist <= 6000:
                target_x = spider_x
                target_y = spider_y
        print('MOVE', target_x, target_y)

    #deffence
    if spider:
        spiders_rank = []
        for i in spider:
            threat_level = 0
            if i['near_base'] == 1 and i['threat_for'] == 1:
                threat_level = 1000
            elif i['near_base'] == 1:
                threat_level = 500

            dist = math.hypot(base_x - i['x'], base_y - i['y'])
            threat_level += 500*(1/(dist+1))
            if dist <= 6500:
                spiders_rank.append((threat_level, i))

        spiders_rank.sort(reverse = True)

        target = [None, None]
        if spiders_rank:
            thraet_x = spiders_rank[0][1]['x']
            thraet_y = spiders_rank[0][1]['y']
            dist1 = math.hypot(my_heros[1]['x'] - thraet_x, my_heros[1]['y'] - thraet_y)
            dist2 = math.hypot(my_heros[2]['x'] - thraet_x, my_heros[2]['y'] - thraet_y)
            if dist1 < dist2:
                target[0] = (thraet_x, thraet_y)
            else:
                target[1] = (thraet_x, target_y)

        if len(spiders_rank) > 1:
            thraet_x = spiders_rank[1][1]['x']
            thraet_y = spiders_rank[1][1]['y']
            target[target.index(None)] = (thraet_x, thraet_y)
        
        spelled = False
        for i in range(2):

            # Write an action using print
            # To debug: print("Debug messages...", file=sys.stderr, flush=True)


            # In the first league: MOVE <x> <y> | WAIT; In later leagues: | SPELL <spellParams>;
            if len(spiders_rank) > i:
                dist = math.hypot(base_x - spiders_rank[0][1]['x'], base_y - spiders_rank[0][1]['y'])
                if dist < 1000 and not spelled:
                    print('SPELL WIND', enemy_x, enemy_y)
                    spelled = True
                elif target[i] is not None:
                    print('MOVE', target[i][0], target[i][1])
                else:
                    print('MOVE', default_pos[i+1][0], default_pos[i+1][1])
            else:
                print('MOVE', default_pos[i+1][0], default_pos[i+1][1])
    else:
        for x,y in default_pos[1:]:
            print("MOVE", x,y)