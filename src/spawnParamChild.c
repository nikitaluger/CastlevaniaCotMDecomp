extern void *sub_0805FAEC(s32, s32);

/* Spawn a kind-0x1C0 object under `parent`, store `param` at +0x5C and clear
 * its +0x4C flag; returns NULL if the spawn budget is exhausted. */
void *spawnParamChild(s32 parent, s32 param)
{
    void *obj = sub_0805FAEC(parent, 0x1C0);
    if (obj == 0) {
        return 0;
    }
    *(s32 *)((u8 *)obj + 0x5C) = param;
    *(u8 *)((u8 *)obj + 0x4C) = 0;
    return obj;
}
