extern void startEffectTimer(void *, s32, const void *);
extern void stepDelayTimer(void *, void *);
extern void sub_0806D588(void *, void *);
extern void sub_080C31E4(void *, void *, u32);

extern u32 gMainWorkspace[];
extern const void D_084FEC0C;
extern u32 gMainObjTimerCallbacks[];

/* Tick a mover's attached animation: when the global mode word (+0x1C) is 1,
 * start the sub-script stored at mover+0x20 on its frame data and advance the
 * outer script; then step that sub-script and copy the mover's world position
 * into the sprite's screen position. */
void sub_08088AEC(void *self)
{
    u8 *a = (u8 *)self;
    u8 *mover = *(u8 **)(a + 0x6C);
    u8 *pos = mover + 4;
    u8 *sprite = *(u8 **)(a + 0x38);

    if (gMainWorkspace[7] == 1) {
        u32 *scriptTable;
        startEffectTimer(mover + 0x20, 0, &D_084FEC0C);
        gMainWorkspace[7] = 2;
        *(u8 *)(a + (*(s16 *)(a + 0x22) * 2) + 0x19) = 0;
        scriptTable = gMainObjTimerCallbacks;
        sub_080C31E4(a + 0x18, a + 0x22, scriptTable[0]);
    }

    stepDelayTimer(mover + 0x20, sprite);
    sub_0806D588(sprite, pos);
}
