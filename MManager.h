#ifndef _MMANAGER_H
#define _MMANAGER_H
    #include "rodats/hashset/HashMap.h"

    #ifdef ALIGN_BOUNDARY
        #undef ALIGN_BOUNDARY
    #endif // ALIGN_BOUNDARY

    #define ALIGN_BOUNDARY(x, b) ((b) < 0 ? x: (((x) + (b) -1)/(b)) * (b))

    typedef struct {
        int fd;
        void **buf;
        unsigned long int
            pageSize,
            mapLength,
            chunkCount,
            origSize;
        HashMap *chunkMap;
    } MManager;

    inline MManager *allocMManager(void);
    MManager *newMManager(const char *path);
    MManager *destroyMManager(MManager *mmgr);

#endif // _MMANAGER_H
