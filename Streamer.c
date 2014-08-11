#include <stdlib.h>

#include "Streamer.h"
#include "rodats/hashmap/errors.h"

static UInt Base = 10;

inline Streamer *allocStreamer(void) {
    return (Streamer *)malloc(sizeof(Streamer));
}

Streamer *newStreamer(void) {
    Streamer *s = allocStreamer();
    assert((s != NULL));

    s->fd = -1;
    s->bufLen = 0;
    s->bufSrc = NULL;
    s->bufDestroyer = NULL;
    s->subscriberMap = newHashMap(Base);

    return s;
}

void closeDownUsers(void *v) {
    raiseWarning("Not yet implemented for: %p", v);
}

Streamer *destroyStreamer(Streamer *s) {
    if (s != NULL) {
        if (s->subscriberMap != NULL) {
            // Inform all the users in the map that time is up
            mapOntoHashMap(s->subscriberMap, closeDownUsers);
        }

        s->subscriberMap = destroyHashMap(s->subscriberMap);
        if (s->bufSrc != NULL) {
            if (s->bufDestroyer != NULL) {
                s->bufSrc = s->bufDestroyer(s->bufSrc);
            } else {
                free(s->bufSrc);
                s->bufSrc = NULL;
            }
        }
    }

    return s;
}
