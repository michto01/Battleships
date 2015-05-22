//
//  map.c
//  Warships
//
//  Created by Natalia Zagan on 21/05/2015.
//  Copyright (c) 2015 Natalia Zagan. All rights reserved.
//

#include "map.h"

// Comment line bellow to suppress the debugging messages
//#define N_DEBUG 1


point * map_get_point_xy( MapRef map, position pos ) {
        return &map[pos.y][pos.x];  
}

uint8_t map_is_valid_position( uint8_t size_w, uint8_t size_h, position point ) {
    if ( 0 <= point.x && point.x < size_h ) {
        if ( 0 <= point.y && point.y < size_w) {
            return TRUE;
        }
    }
    return FALSE;
}

MapRef map_create( uint8_t size_w, uint8_t size_h ) {
    /* size_h is the number of rows  */
    /* note: c is char** */
    MapRef c;
    
    if (( c = (MapRef) malloc( size_h * sizeof( point* ))) == NULL ) {
        /* error */
        print_error(ERROR_NOMEM);
    }
    
    for ( int i = 0; i < size_h; i++) {
        
        /* size_w here is the size of given row, no need to
         * multiply by sizeof( char ), it's always 1
         */
        if (( c[i] = malloc( size_w )) == NULL ) {
            /* error */
            print_error(ERROR_NOMEM);
        }
        
        for ( int col = 0; col < size_w; col++ ) {
            
            c[i][col].isHidden     = TRUE;
            c[i][col].isBlocked    = FALSE;
            c[i][col].isPlayed     = FALSE;
            c[i][col].isShip       = FALSE;
            c[i][col].isShipSinked = FALSE;
        }
    }
    
    return c;
}

void map_free(MapRef map, uint8_t size_w, uint8_t size_h ) {
    for (int i = 0; i < size_h; i++)
        free(map[i]);
    free(map);
}

void map_generate_ships_simple( MapRef map, uint8_t size_w, uint8_t size_h, uint8_t ship_count ) {
    
    while ( ship_count > 0 ) {
        
        position current_point = random_point(size_w, size_h);
        
        while (!map_is_valid_position(size_w, size_h, current_point)) {
            current_point = random_point(size_w, size_h);
        }
        
        point * ptr = map_get_point_xy(map, current_point);
        
#ifndef N_DEBUG
        printf("[%d,%d][%db%ds]\n", current_point.y, current_point.x, ptr->isBlocked, ptr->isShip);
#endif
        // Place ship and block surranding areas
        if ( !ptr->isShip && !ptr->isBlocked ) {
            ship_set_new(ptr);
            
            // Auxiliary points => points to be blocked
            position N = current_point; if(N.y) N.y--;
            position S = current_point; S.y++;
            position E = current_point; E.x++;
            position W = current_point; if(N.x) W.x--;
            
            position NE = current_point; NE.x++; if(NE.y) NE.y--;
            position NW = current_point; if(NW.x) NW.x--; if(NW.y) NW.y--;
            position SE = current_point; SE.x++; SE.y++;
            position SW = current_point; if(SW.x) SW.x--; SW.y++;

#ifndef N_DEBUG
            printf(KRED "[%d,%d]\n" RESET, N.y, N.x);
            printf(KYEL "[%d,%d]\n" RESET, S.y, S.x);
            printf(KGRN "[%d,%d]\n" RESET, E.y, E.x);
            printf(KBLU "[%d,%d]\n" RESET, W.y, W.x);
#endif
            
            if ( map_is_valid_position(size_w, size_h, N) ) {
                #ifndef N_DEBUG
                printf(KRED "YES [%d,%d]\n" RESET, N.y, N.x);
                #endif
                ship_set_blocked(map_get_point_xy(map, N));
            }
            
            if ( map_is_valid_position(size_w, size_h, S) ) {
                #ifndef N_DEBUG
                printf(KYEL "YES [%d,%d]\n" RESET, S.y, S.x);
                #endif
                ship_set_blocked(map_get_point_xy(map, S));
            }
            
            if ( map_is_valid_position(size_w, size_h, E) ) {
                #ifndef N_DEBUG
                printf(KGRN "YES [%d,%d]\n" RESET, E.y, E.x);
                #endif
                ship_set_blocked(map_get_point_xy(map, E));
            }
            
            if ( map_is_valid_position(size_w, size_h, W) ) {
                #ifndef N_DEBUG
                printf(KBLU "YES [%d,%d]\n" RESET, W.y, W.x);
                #endif
                ship_set_blocked(map_get_point_xy(map, W));
                
            }
            
            if ( map_is_valid_position(size_w, size_h, NE) ) {
                #ifndef N_DEBUG
                #endif
                ship_set_blocked(map_get_point_xy(map, NE));
                
            }
            
            if ( map_is_valid_position(size_w, size_h, NW) ) {
                #ifndef N_DEBUG
                #endif
                ship_set_blocked(map_get_point_xy(map, NW));
            }
            
            if ( map_is_valid_position(size_w, size_h, SW) ) {
                #ifndef N_DEBUG
                #endif
                ship_set_blocked(map_get_point_xy(map, SW));
            }
            
            if ( map_is_valid_position(size_w, size_h, SE) ) {
                #ifndef N_DEBUG
                #endif
                ship_set_blocked(map_get_point_xy(map, SE));
            }
            
            ship_count--;
        }
    }
}

point_type map_perform_action(MapRef map, position pos) {
    point *p;
    if ( ( p = map_get_point_xy(map, pos) ) ) {
        printf("\nDBG: %d %d %d %d %d\n", p->isShip, p->isBlocked, p->isPlayed, p->isHidden, p->isShipSinked);
        if ( p->isPlayed ) {
            return PointPlayed;
        } else {
            p->isPlayed = TRUE;
            p->isHidden = FALSE;
            
            if ( p->isShip ) {
                return PointIsShip;
            }
        }
    }
    return PointUnknown;
}

void map_print_cheat ( MapRef map, uint8_t size_w, uint8_t size_h) {
    // Size_H is number of rows whereas Size_W is number of collumns
    
    for (int i = 0; i < size_h; i++) {
        for (int j = 0; j < size_w; j++) {
            
            position current_point;
            current_point.x = i;
            current_point.y = j;
            
            if (map_get_point_xy(map, current_point)->isShip) {
                printf("[" KBLU "%2c" RESET " ]", ((char)ship_print(map_get_point_xy(map, current_point), PointIsShip)) == 0 ? ' ':((char)ship_print(map_get_point_xy(map, current_point), PointIsShip)));
            }
            else if (map_get_point_xy(map, current_point)->isBlocked) {
                printf("[" KRED "%2c" RESET " ]", ((char)ship_print(map_get_point_xy(map, current_point), PointBlocked)) == 0 ? ' ':((char)ship_print(map_get_point_xy(map, current_point), PointBlocked)));
            }
            else {
                printf("[" KYEL "%2c" RESET " ]", ((char)ship_print(map_get_point_xy(map, current_point), PointHidden)) == 0 ? ' ':((char)ship_print(map_get_point_xy(map, current_point), PointHidden)));
            }
            
            
        }
        
        printf("\n");
    }

}

void map_print ( MapRef map, uint8_t size_w, uint8_t size_h, point_type type) {
    
    // Size_H is number of rows whereas Size_W is number of collumns
    
    for (int i = 0; i < size_h; i++) {
        for (int j = 0; j < size_w; j++) {
            
            position current_point;
            current_point.x = i;
            current_point.y = j;
            
            if ( type == PointHidden ) {
                if ( !map_get_point_xy(map, current_point)->isHidden ) {
                    if ( map_get_point_xy(map, current_point)->isPlayed && !map_get_point_xy(map, current_point)->isShip) {
                        printf("[" KBLU "%2c" RESET " ]", '~');
                        continue;
                    }
                    if ( map_get_point_xy(map, current_point)->isShip ) {
                        printf("[" KRED "%2c" RESET " ]", ((char)ship_print(map_get_point_xy(map, current_point), PointIsShip)) == 0 ? ' ':((char)ship_print(map_get_point_xy(map, current_point), PointIsShip)));
                        continue;
                    }
                }
                printf("[" KGRN "%2c" RESET " ]", ' ');
                continue;
            }
            
            if (type == PointBlocked) {
                printf("[" KBLU "%2c" RESET " ]", ((char)ship_print(map_get_point_xy(map, current_point), type)) == 0 ? ' ':((char)ship_print(map_get_point_xy(map, current_point), type)));
            }
            /*else {
                printf("[" KRED "%2c" RESET " ]", ((char)ship_print(map_get_point_xy(map, current_point), type)) == 0 ? ' ':((char)ship_print(map_get_point_xy(map, current_point), type)));
            }*/
            
            
        }
        
        printf("\n");
    }
}

position map_take_user_input(const char* message) {
    int x,y;
    position rifle;
    printf("%s", message);
    scanf("%d %d", &y, &x);
    rifle.x = x;
    rifle.y = y;
    return rifle;
}