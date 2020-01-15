#ifndef META_DATA_H
#define META_DATA_H

#include "datastream.h"

typedef struct {
    unsigned int nodeid;
    char filename[50];
    unsigned int size;
    // unsigned int type;
    // unsigned int parentNodeId;
    // time_t creationTime;
    // time_t accessTime;
    // time_t modificationTime;
    Datastream data;
} MetaData;

#endif
