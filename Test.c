#include <stdio.h>
#include "MManager.h"

int main() {
    MManager *mmgr = newMManager(__FILE__);
    if (mmgr != NULL) {
        printf("%s", (char *)mmgr->buf);
    }
    mmgr = destroyMManager(mmgr);

    return 0;
}
