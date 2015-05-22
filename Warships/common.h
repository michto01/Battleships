//
//  common.h
//  Warships
//
//  Created by Natalia Zagan on 21/05/2015.
//  Copyright (c) 2015 Natalia Zagan. All rights reserved.
//

#ifndef Warships_common_h
#define Warships_common_h


// Cross compile on Linux, MacOS X and Windows
#ifdef __linux__
    #include <unistd.h>
#elif __APPLE__
    #include <unistd.h>
#elif _WIN32
    #include <stdlib.h>
#endif

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define RESET "\033[0m"


#define TRUE  1
#define FALSE 0

#define ERROR_NOMEM          "MEMORY ALLOCATION ERROR"
#define ERROR_OUT_OF_BOUNDS  "DIRECTION IS NOT ON MAP"
#define ERROR_FILE_NOT_FOUND "FILE NOT FOUND"
#define ERROR_FILE_CREATION  "FILE NOT CREATED"



static inline void clear_screen() {
#ifdef __linux__
    write(STDOUT_FILENO,"\e[1;1H\e[2J",12);
#elif __APPLE__
    write(STDOUT_FILENO,"\e[1;1H\e[2J",12);
#elif _WIN32
    system("cls");
#endif
}

/*
 *  Convinience structure to denote state of ship in place on map
 */
struct _map_point {
  uint8_t   isPlayed       : 1, // This point was already checked
            isShip         : 1, // This point contains ship
            isBlocked      : 1, // This point is blocked because proximity of another ship
            isHidden       : 1, // Allows to debug the single point on the map
            isShipSinked   : 1, // Allows for future extension to multipoint ships
            padding        : 3; // Rest of the byte to be used by expansions
};

enum _point_types {
    PointUnknown,
    PointPlayed,
    PointIsShip,
    PointHidden,
    PointBlocked,
    PointIsSinkedShip
};


struct _size {
    uint8_t width;
    uint8_t height;
};


// Cell is exact opposite of the position X -> Col, Y -> ROW
struct _position {
    uint8_t x;
    uint8_t y;
};

struct _cell {
    uint8_t row;
    uint8_t col;
};

typedef enum   _point_types  point_type;
typedef struct _map_point    point;
typedef        point      ** MapRef; // define 2-dimensional array as the map

typedef struct _size         size;
typedef struct _position     position;
typedef struct _cell         cell;

static inline void print_error ( const char* message ) {
    printf(KRED "[ERROR]: %s" RESET, message);
}

static inline void gc_pause() {
    //flush(stdin);
    //flush(stdout);
    getchar();
}

#endif
