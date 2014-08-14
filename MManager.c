#include <math.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include "MManager.h"
#include "rodats/hashmap/errors.h"
#include "rodats/hashmap/HashMap.h"

inline MManager *allocMManager(void) {
    return (MManager *)malloc(sizeof(MManager));
}

MManager *newMManager(const char *path) {
    if (path == NULL)
        return NULL;
    else {
        struct stat stSav;
        int fd = open(path, O_RDONLY); // For starters we are doing ReadOnly ops
        if (fd < 0 || fstat(fd, &stSav)) {
            raiseWarning("While opening: %s encountered: %s\n", path, strerror(errno));
            return NULL;
        } else if (stSav.st_size <= 0) {
            raiseWarning("Trying to map an empty file: %s\n", path);
            return NULL;
        } else {
            // Memory Mapping time
            long pageSize = sysconf(_SC_PAGESIZE);
            unsigned long long int mapLength = ALIGN_BOUNDARY(stSav.st_size, pageSize);
            
            void **buf = (void **)mmap(NULL, mapLength, PROT_READ, MAP_SHARED, fd, 0);
            if (buf == MAP_FAILED) {
                raiseWarning("Could not mmap fd: %d from %s. Err encountered: %s\n",
                    fd, path, strerror(errno)
                );
                return NULL;
            }

            MManager *mmgr = allocMManager();
            assert(mmgr != NULL);

            mmgr->fd = fd;
            mmgr->buf = buf;
            mmgr->pageSize = pageSize;
            mmgr->mapLength = mapLength;
            mmgr->origSize = stSav.st_size;
            mmgr->chunkMap = newHashMap(10); // TODO: Drop chunks into chunkmap
            mmgr->chunkCount = (unsigned long int)ceil(mapLength/((float)pageSize)) || 1; 

            return mmgr;
        }
    }
}

MManager *destroyMManager(MManager *mmgr) {
    if (mmgr != NULL) {
        if (mmgr->buf != NULL) {
            if (munmap(mmgr->buf, mmgr->mapLength)) {
                raiseWarning("Failed to munmap %ld bytes of buf: %p\n", mmgr->mapLength, mmgr->buf);
            }

            mmgr->fd = -1;
            mmgr->buf = NULL;
            mmgr->chunkMap = destroyHashMap(mmgr->chunkMap);
            free(mmgr);
            mmgr = NULL;
        }
    }

    return mmgr;
}
