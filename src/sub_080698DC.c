struct S_02025FF0_698DC {
    u8 _0[0x14AC];
    u32 f14AC;
    u32 f14B0;
    u8 _14B4[0x18C5 - 0x14B4];
    u8 f18C5;
    u8 f18C6;
};
extern struct S_02025FF0_698DC gMainWorkspace;
extern void *gMainObjTimerCallback;
extern void sub_0806C5EC(void *, void *, void *, void *);
extern void sub_0806C6B0(void *, void *, void *, void *);
extern void *sub_08001480(void *, s32);
extern void sub_0806D894(void);
extern void sub_0806D8C0(void);
extern void sub_08005E80(s32);
extern void sub_080C31E4(void *, void *, void *);

/*
 * Initialises a spawned entity group: resets its state, spawns three child
 * objects with successive ids, sets the global flags, restarts the related
 * timers, plays a sound and fires the entity's effect callback.
 */
void sub_080698DC(u8 *arg0) {
    void *subObj = *((void **)(arg0 + 0x6C));
    u8 *obj = (u8 *)subObj + 4;
    u8 *ctx = *((u8 **)(arg0 + 0x38));
    void *spawned;
    s32 index;
    sub_0806C5EC(arg0, ctx, obj, obj);
    sub_0806C6B0(arg0, ctx, obj, obj);
    spawned = sub_08001480(arg0, 0x30);
    if (spawned != 0) *(s32 *)((u8 *)spawned + 0x7C) = 0;
    spawned = sub_08001480(arg0, 0x30);
    if (spawned != 0) *(s32 *)((u8 *)spawned + 0x7C) = 1;
    spawned = sub_08001480(arg0, 0x30);
    if (spawned != 0) *(s32 *)((u8 *)spawned + 0x7C) = 2;
    gMainWorkspace.f14B0 = 1;
    gMainWorkspace.f14AC = 1;
    *(s32 *)((u8 *)subObj + (0x8A << 1)) = 0x64;
    *(s32 *)((u8 *)subObj + (0x8C << 1)) = 0x64;
    sub_0806D894();
    sub_0806D8C0();
    sub_08005E80(0x7C);
    gMainWorkspace.f18C6 = 1;
    gMainWorkspace.f18C5 = 1;
    index = *(s16 *)(arg0 + 0x22);
    (arg0 + index * 2)[0x19] = 0;
    {
        void **effectIds = &gMainObjTimerCallback;
        sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *effectIds);
    }
}
