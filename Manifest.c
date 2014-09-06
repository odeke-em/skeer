#include <stdlib.h>
#include <pthread.h>

#include "Manifest.h"
#include "rodats/hashset/errors.h"

static pthread_mutex_t _MANIFEST_MUTEX_ = PTHREAD_MUTEX_INITIALIZER;

inline Manifest *allocManifest(void) {
    return (Manifest *)malloc(sizeof(Manifest));
}

void noRetrManifestFree(void *d) {
    Manifest *mf = (Manifest *)d;
    mf = destroyManifest(mf);
}

Manifest *newManifest(const unsigned int id, void **start, void **end) {
    Manifest *mf = allocManifest();
    assert(mf != NULL);

    mf->id = id;
    mf->isHeapd = True;
    mf->isFreed = False;

    mf->start = start;
    mf->end = end;

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
