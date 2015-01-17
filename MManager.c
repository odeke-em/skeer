#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include "rodats/hashset/errors.h"
#include "rodats/hashset/HashMap.h"
#include "MManager.h"
#include "Manifest.h"

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

            // Chunking here
            unsigned long int i=0;
            void **s=mmgr->buf, **e, **extreme = mmgr->buf + mmgr->origSize;
            while (s < extreme) {
                e = s + mmgr->pageSize;
                mmgr->chunkMap = putWithFreer(
                    mmgr->chunkMap, i, (void *)newManifest(i, s, e), noRetrManifestFree, 1
                );
                s = e;
                ++i;
            }

            mmgr->chunkCount = i;

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
            if (mmgr->fd >= 0 && close(mmgr->fd)) {
                raiseWarning("Failed to close file descriptor: %d due to error: %s\n",
                    mmgr->fd, strerror(errno)
                );
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
