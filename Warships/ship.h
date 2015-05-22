//
//  ship.h
//  Warships
//
//  Created by Natalia Zagan on 21/05/2015.
//  Copyright (c) 2015 Natalia Zagan. All rights reserved.
//

#ifndef __Warships__ship__
#define __Warships__ship__

#include <stdio.h>
#include <stdlib.h>

#include "common.h"

#define PLAYED   '#'
#define SHIP     '$'
#define HIDDEN   '%'
#define SINKED   '*'
#define BLOCKED  '&'


static inline void ship_set_new ( point * map_point ) {
    map_point->isShip       = TRUE;
    map_point->isBlocked    = TRUE;
}

static inline void ship_set_blocked ( point * map_point ) {
    map_point->isBlocked    = TRUE;
}



static inline uint8_t ship_print( point * map_point, point_type type) {
    
    if (map_point == NULL) {
        return 0;
    }
    
    switch (type) {
        case PointPlayed:
            if ( map_point->isPlayed ) {
                return PLAYED;
            } else {
                return 0;
            }
            break;
        
        case PointIsShip:
            if ( map_point->isShip ) {
                return SHIP;
            } else {
                return 0;
            }
            break;
        
        case PointHidden:
            if ( map_point->isHidden ) {
                return HIDDEN;
            } else {
                return 0;
            }
            break;
            
        case PointBlocked:
            if ( map_point->isBlocked ) {
                return BLOCKED;
            } else {
                return 0;
            }
            break;
            
        case PointIsSinkedShip:
            if ( map_point->isShipSinked ) {
                return BLOCKED;
            }  else {
                return 0;
            }
            break;

    
        default:
            return 0;
    }
    
    return 0;
}

#endif /* defined(__Warships__ship__) */
