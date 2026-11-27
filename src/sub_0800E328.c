/*
 * Actor-state sync: invoke the update callback on the two tracked objects,
 * start a screen transition when the scene id changes, then snapshot the
 * 0x48-byte work block into the state buffer and rebuild its derived stats.
 */
struct S_020278D0 {
    u8 _0x000[0x40];
    u16 sceneId;
    u8 _0x042[0x6];
    void *objects[5];
};
extern struct S_020278D0 gMenuState;
extern u8 gGameStatus[];
void _call_via_r1(void *, void *);
void sub_0806DD94(void);
void copyBytes(void *, void *, u32);
void sub_0806D930(void *);

void sub_0800E328(void) {
    u8 *state = gGameStatus;
    u32 i = 0;
    void *obj;
    u8 *sync = (u8 *)&gMenuState;
    void **slot = (void **)(sync + 0x48);
    do {
        obj = *slot;
        if (obj != 0)
            _call_via_r1(obj, *(void **)((u8 *)obj + 0x24));
        slot++;
        i++;
    } while (i <= 1);
    if (gMenuState.sceneId != *(u16 *)(state + 0x304))
        sub_0806DD94();
    copyBytes(state + 0x2C4, &gMenuState, 0x48);
    sub_0806D930(state + 0x2C4);
}
