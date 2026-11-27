s32 sub_0806D24C(void);

struct D02025FF0_S {
    u8 _p0[0x14ED];
    u8 spawnFlagSrc;     /* byte propagated to spawnFlagDst on a successful spawn */
    u8 _p1[0x14F0 - 0x14EE];
    u8 spawnFlagDst;     /* receives spawnFlagSrc when an entity is spawned */
    u8 _p2[0x1780 - 0x14F1];
    u32 slotTable[1];    /* global entity slot table at +0x1780 */
};
extern struct D02025FF0_S gMainWorkspace;

/* Try to allocate an entity through the slot allocator (the caller's arguments
 * are forwarded in registers). On success propagate the spawn flag byte and
 * return the entity; otherwise return 0. */
s32 spawnEntity(void) {
    s32 spawned = sub_0806D24C();
    s32 result;
    if (spawned != 0) {
        gMainWorkspace.spawnFlagDst = gMainWorkspace.spawnFlagSrc;
        result = spawned;
    } else {
        result = 0;
    }
    return result;
}
