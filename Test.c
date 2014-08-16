#include <math.h>
#include <stdio.h>
#include "Streamer.h"
#include "MManager.h"

int main() {
    MManager *mmgr = newMManager(__FILE__);
    if (mmgr != NULL) {
        printf("%s", (char *)mmgr->buf);
    }

    printf("ml: %ld ps: %ld cc: %ld\n", ml, ps, cc); 
    mmgr = destroyMManager(mmgr);

    // Test out the streamer
    Streamer *s = newStreamer();
    s = destroyStreamer(s);

    return 0;
}
