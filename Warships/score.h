//
//  score.h
//  Warships
//
//  Created by Natalia Zagan on 22/05/2015.
//  Copyright (c) 2015 Natalia Zagan. All rights reserved.
//

#ifndef __Warships__score__
#define __Warships__score__

#include <stdio.h>
#include "common.h"

static FILE *fr, *fw;

struct _battleships_score_item {
    size    battleground;
    char    player[20];
    uint8_t turns;
    double  time;
};

typedef struct _battleships_score_item battleships_score_item;

void scores_db_close();
void scores_db_create(const char* filename);
void scores_db_open(const char* filename);

void scores_db_save(battleships_score_item item);

battleships_score_item scores_db_recall_scores(uint8_t id);



/*

int counter;
FILE *ptr_myfile;
struct rec my_record;

ptr_myfile=fopen("test.bin","wb");
if (!ptr_myfile)
{
    printf("Unable to open file!");
    return 1;
}
for ( counter=1; counter <= 10; counter++)
{
    my_record.x= counter;
    fwrite(&my_record, sizeof(struct rec), 1, ptr_myfile);
}
fclose(ptr_myfile);
return 0;
*/

#endif /* defined(__Warships__score__) */
