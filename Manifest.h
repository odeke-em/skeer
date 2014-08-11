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
        Bool isFreed, isHeapd;
        unsigned long int start, end;
        const void *buf; // Not owned by us, just referral from provider
    } Manifest;

    inline Manifest *allocManifest(void);

    Manifest *newManifest(void);
    Manifest *destroyManifest(Manifest *m);

#endif // _MANIFEST_H
