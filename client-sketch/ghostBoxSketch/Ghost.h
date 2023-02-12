#pragma once

#define GHOST_TYPE_LEN 32
#define GHOST_NAME_LEN 32

typedef struct Ghost {
    String type;
    String name;
    char location; //the room the ghost is in
    uint8_t activeness;
    uint8_t foundCode;
} Ghost;

