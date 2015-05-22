//
//  score.c
//  Warships
//
//  Created by Natalia Zagan on 22/05/2015.
//  Copyright (c) 2015 Natalia Zagan. All rights reserved.
//

#include "score.h"

void socres_db_close() {
    fclose(fw);
    fclose(fr);
}

void scores_db_create(const char* filename) {
    if ( (fw = fopen(filename, "wb+")) == NULL ) {
        print_error(ERROR_FILE_CREATION);
    }
    if ( (fr = fopen(filename, "rb")) == NULL )  {
        print_error(ERROR_FILE_NOT_FOUND);
    }
}

void scores_db_open(const char* filename) {
    if ( (fw = fopen(filename, "ab+")) == NULL ) {
        print_error(ERROR_FILE_CREATION);
    }
    if ( (fr = fopen(filename, "rb")) == NULL )  {
        print_error(ERROR_FILE_NOT_FOUND);
    }
}

void scores_db_save(battleships_score_item item) {
    fwrite(&item, sizeof(battleships_score_item), 1, fw);
}

battleships_score_item scores_db_recall_scores(uint8_t id) {
    battleships_score_item temp;
    
    fseek( fr, sizeof(battleships_score_item)*id, SEEK_SET );
    fread( &temp, sizeof(battleships_score_item), 1, fr);
    
    return temp;
}
