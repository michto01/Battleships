//
//  map.h
//  Warships
//
//  Created by Natalia Zagan on 21/05/2015.
//  Copyright (c) 2015 Natalia Zagan. All rights reserved.
//

#ifndef __Warships__map__
#define __Warships__map__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "common.h"
#include "ship.h"

static inline void set_randomizer_seed () {
    srand((unsigned int)time(NULL)); // Random seed
}

static inline position random_point( uint8_t size_w, uint8_t size_h ) {
    
    position point;
    point.x = rand() % size_w;
    point.y = rand() % size_h;
    
    return point;
}

uint8_t map_is_valid_position( uint8_t size_w, uint8_t size_h, position point );

point * map_get_point_xy( MapRef map, position pos );

MapRef  map_create( uint8_t size_w, uint8_t size_h);              // Ship size in simple = 1 point
void    map_free  ( MapRef map, uint8_t size_w, uint8_t size_h ); // free the map

void    map_generate_ships_simple( MapRef map, uint8_t size_w, uint8_t size_h, uint8_t ship_count );

void    map_print ( MapRef map, uint8_t size_w, uint8_t size_h, point_type type);
void    map_print_cheat ( MapRef map, uint8_t size_w, uint8_t size_h);

point_type map_perform_action(MapRef map, position pos);

position map_take_user_input( const char* message );
#endif /* defined(__Warships__map__) */
