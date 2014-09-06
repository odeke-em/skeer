#ifndef _MANIFEST_H
#define _MANIFEST_H

#ifndef _BOOL_T
#define _BOOL_T
    typedef enum {
        False=0, True=1
    } Bool;
#endif // _BOOL_T

    typedef struct {
        void *metaInfo;
        unsigned int id;
        void **start, **end; // Not owned by us, just referral from provider
        Bool isFreed, isHeapd;
    } Manifest;

    inline Manifest *allocManifest(void);

    Manifest *newManifest(const unsigned int id, void **start, void **end);
    Manifest *destroyManifest(Manifest *m);

    void noRetrManifestFree(void *d);

#endif // _MANIFEST_H
