#include <stdlib.h>
#include <pthread.h>

#include "Manifest.h"
#include "rodats/hashmap/errors.h"

static pthread_mutex_t _MANIFEST_MUTEX_ = PTHREAD_MUTEX_INITIALIZER;

inline Manifest *allocManifest(void) {
    return (Manifest *)malloc(sizeof(Manifest));
}

Manifest *newManifest(void) {
    Manifest *mf = allocManifest();
    assert(mf != NULL);

    mf->id = 0;
    mf->buf = NULL;
    mf->start = mf->end = 0;
    mf->isFreed = False;
    mf->isHeapd = True;

    return mf;
}

Manifest *destroyManifest(Manifest *mf) {
    if (mf != NULL && mf->isFreed == False && mf->isHeapd == True) {
        pthread_mutex_lock(&_MANIFEST_MUTEX_);
        *(&mf->isHeapd) = False;
        *(&mf->isFreed) = True;
        free(mf);

        mf = NULL;
        pthread_mutex_unlock(&_MANIFEST_MUTEX_);
    }

    return mf;
}
