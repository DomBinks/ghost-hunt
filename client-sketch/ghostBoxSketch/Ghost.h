#pragma once

#define GHOST_TYPE_LEN 32
#define GHOST_NAME_LEN 32

typedef struct Ghost {
    char type[GHOST_TYPE_LEN];
    char name[GHOST_NAME_LEN];
    char location; //the room the ghost is in
    uint8_t activeness;
} Ghost;