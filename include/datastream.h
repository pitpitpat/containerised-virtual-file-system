#ifndef DATASTREAM_H
#define DATASTREAM_H

#define DATABLOCK_NUM 1000

typedef struct {
    unsigned int datablocks[DATABLOCK_NUM];
} Datastream;

#endif
