#ifndef _STREAMER_H
#define _STREAMER_H
    #include "rodats/list/list.h"
    #include "rodats/hashmap/HashMap.h"

    typedef struct {
        int fd;
        void *bufSrc;
        unsigned long int bufLen; // Buffer length
        HashMap *subscriberMap; // Map of subscriber to handler 
    } Streamer;

    inline Streamer *allocStreamer(void);
    Streamer *newStreamer(void);
    Streamer *destroyStreamer(Streamer *);
#endif // _STREAMER_H
