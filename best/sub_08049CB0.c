extern u32 nextRandomWord(void);
extern void sub_0804A4D0(void *, void *, void *, s32);
extern void copyPoseAttrs(void *, void *);
extern void sub_080C31E8(void *, void *, s32, void *);
extern void sub_080C31E4(void *, void *, void *);
extern void *gScriptStepCallbacks;
extern void *gMainObjTimerCallbacks;

struct S_02025FF0 { u8 _0[0x174C]; s32 f174C; s32 f1750; };
extern struct S_02025FF0 gMainWorkspace;

void sub_08049CB0(u8 *arg0)
{
    u8 *self;
    u16 *sprite;
    u8 *work;
    u8 *animTrack;
    u8 *state;
    s32 flagY;
    s32 flagX;
    u8 *p_1;
    u8 *p_2;
    u8 *p_b1;

    self = arg0;
    flagY = 0;
    flagX = 0;
    sprite = *(u16 **)(self + 0x38);
    work = *(u8 **)(self + 0x3c);
    animTrack = (void *) ((0x34) + (s32) work);
    state = (void *) ((0x48) + (s32) work);

    if (*(u8 *)(self + 0x6c) != 0) {
        s32 z = 0;
        void *cb;
        *(u32 *)state = *(u32 *)(work + 0xc);
        *(u16 *)(state + 4) = (u16)nextRandomWord();
        p_1 = (void *) (((*(s16 *)(self + 0x22) * 2)) + (s32) self);
        *(u8 *)(p_1 + 0x19) = z;
        cb = &gScriptStepCallbacks;
        sub_080C31E8(self + 0x18, self + 0x22, 2, *(void **)cb);
        return;
    }
    {
        s32 camY = gMainWorkspace.f1750;
        s32 y = *(s32 *)(work + 0xc);
        if (camY > y - 0x280000 && camY < y + 0x100000)
            flagY = 1;
    }
    if (sprite[1] & 0x10) {
        s32 camX = gMainWorkspace.f174C;
        s32 x = *(s32 *)(work + 8);
        if (camX > x && camX < x + 0x600000)
            flagX = 1;
    } else {
        s32 camX = gMainWorkspace.f174C;
        s32 x = *(s32 *)(work + 8);
        if (camX < x && camX > x - 0x600000)
            flagX = 1;
    }
    if (flagY == 0 || flagX == 0)
        return;
    {
        s32 z = 0;
        void *cb;
        *(u8 *)(state + 0xa) = 1;
        *(u32 *)(work + 0xc) = *(u32 *)(work + 0xc) - 0x100000;
        sub_0804A4D0((void *)sprite, (void *)animTrack, (void *)state, 2);
        copyPoseAttrs(*(void **)(work + 0x28), (void *)0x080CF93C);
        p_2 = *(u8 **)(work + 0x28);
        *(u8 *)(p_2 + 2) = 8;
        *(u32 *)(work + 0x10) = (u32)(s8)(*(s8 *)(self + 0x70)) * 0x6000;
        *(u32 *)(work + 0x14) = (u32)-0xC000;
        p_b1 = (void *) (((*(s16 *)(self + 0x22) * 2)) + (s32) self);
        *(u8 *)(p_b1 + 0x19) = z;
        cb = &gMainObjTimerCallbacks;
        sub_080C31E4(self + 0x18, self + 0x22, *(void **)cb);
    }
}
