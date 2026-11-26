typedef struct S_02025FF0 {
    u8 _0x000[0x18C4];
    u8 flushFlag;
} S_02025FF0;
extern S_02025FF0 gMainWorkspace;

/* If no work pointer is queued at +0x30, push the staged graphics data out and
 * clear the flush flag. */
void sub_08007B18(void *arg0) {
    s32 work;

    work = *(s32 *)((u8 *)arg0 + 0x30);
    if (work == 0) {
        sub_080064C4();
        gMainWorkspace.flushFlag = (u8)work;
    }
}
