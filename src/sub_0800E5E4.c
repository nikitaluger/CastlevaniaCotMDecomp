extern s32 sub_080C31E0(void *, s32);

/* Call the callback at object+0x24 of the object held in the workspace's
 * 0x48 slot, when that slot is non-null. */
void sub_0800E5E4(void)
{
    void *obj;
    u8 *workspace;
    workspace = (u8 *)0x020278D0;
    obj = *(void **)(workspace + 0x48);
    if (obj != NULL) {
        sub_080C31E0(obj, *(s32 *)((u8 *)obj + 0x24));
    }
}
