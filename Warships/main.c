//
//  main.c
//  Warships
//
//  Created by Natalia Zagan on 21/05/2015.
//  Copyright (c) 2015 Natalia Zagan. All rights reserved.
//

#include <stdio.h>
#include <time.h>

#include "map.h"
#include "common.h"


int main(int argc, const char * argv[]) {
    set_randomizer_seed();
    
    time_t start, stop;
    
    // Start time measure
    time(&start);
    
    size s;
    s.width  = 5;
    s.height = 6;
    
    uint8_t ship_count = 2;
    
    MapRef map = map_create(s.width, s.height);
    //map_print(map, s.width, s.height, PointHidden); // Print test clean map
    
    
    // The Game
    map_generate_ships_simple(map, s.width, s.height, ship_count);

    clear_screen();
    map_print_cheat(map, s.width, s.height);
    
    for (int z = 0; z < 10; z++) {
        position rifle = map_take_user_input("[x,y]:");
        point_type   p = map_perform_action(map, rifle);
        // total awesome comment
        clear_screen();
        map_print(map, s.width, s.height, PointHidden);
    }
    map_free( map, s.width, s.height ); // Garbage collector -> free the array
 
    // Stop time measure
    time(&stop);
    printf("Finished in about %.2f seconds. \n", difftime(stop, start));
    
    gc_pause();
    return 0;
}
