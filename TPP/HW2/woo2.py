import sys
import math

# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.

# base_x: The corner of the map representing your base
base_x, base_y = [int(i) for i in input().split()]
heroes_per_player = int(input())  # Always 3

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
    
    spiders_rank = []
    for i in spider:
        threat_level = 0
        if i['near_base'] == 1 and i['threat_for'] == 1:
            threat_level = 1000
        elif i['near_base'] == 1:
            threat_level = 500

        dist = math.hypot(base_x - i['x'], base_y - i['y'])
        threat_level += 500*(1/(dist+1))
        spiders_rank.append((threat_level, i))

    spiders_rank.sort(reverse = True)


    for i in range(heroes_per_player):

        # Write an action using print
        # To debug: print("Debug messages...", file=sys.stderr, flush=True)


        # In the first league: MOVE <x> <y> | WAIT; In later leagues: | SPELL <spellParams>;
        if len(spiders_rank) > i:
            print('MOVE', spiders_rank[i][1]['x'], spiders_rank[i][1]['y'])
        else:
            print('WAIT')