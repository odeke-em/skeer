#include <stdlib.h>
#include "Streamer.h"

Streamer *destroyStreamer(Streamer *s) {
    if (s != NULL) {
        if (! isEmptyTrie(s->map)) {
            // Inform all the users in the map that time is up
        }
    }

    return s;
}
