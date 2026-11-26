extern void sub_08003A6C(void *, s32, void *);
extern s32 sub_08003740(void *, void *);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_0808449C(void);
extern u8 gMainWorkspace[];
extern u32 D_084E2568;
extern u32 D_084E25C0;
extern s32 gMainObjTimerCallback;

/* Initialize an actor: clear its motion state, install its update callback
 * and graphics data, seed its position from globals, then dispatch its
 * first animation step. */
void sub_0807BCA4(u8 *self) {
    u32 zero;
    u8 *object = *(u8 **)(self + 0x6C);
    u8 *state = object + 4;
    u8 *sprite = *(u8 **)(self + 0x38);
    zero = 0;

    *(u32 *)(state + 0x2C) = zero;
    *(u32 *)(state + 0x30) = zero;
    *(u32 *)(state + 0x34) = zero;
    *(u32 *)(state + 0x38) = zero;
    *(u32 *)(state + 0x3C) = zero;
    *(u32 *)(state + 0x18) = *(u32 *)(self + 0x24);
    *(u32 *)(self + 0x24) = (u32)&sub_0808449C;
    *(u32 *)(sprite + 0x24) = (u32)&D_084E2568;
    {
        u8 *pos = object;
        pos += 0x20;
        sub_08003A6C(pos, 0, &D_084E25C0);
        sub_08003740(pos, sprite);
    }
    {
        u8 *gGame = gMainWorkspace;
        *(s32 *)(object + 4) = *(s32 *)(gGame + 0x1728);
        *(s32 *)(state + 4) = *(s32 *)(gGame + 0x172C) + 0xFF800000;
    }
    *(u32 *)(state + 0x10) = zero;
    *(u32 *)(state + 0x54) = zero;
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = zero;
    {
        s32 *animCmd = &gMainObjTimerCallback;
        u8 *sequence = self;
        sequence += 0x18;
        sub_080C31E4(sequence, self + 0x22, *animCmd);
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) + 1;
        sequence += *(s16 *)(self + 0x22) * 2;
        {
            u8 animState = *sequence;
            sub_080C31E0(self, *(s32 *)(animState * 4 + *(u32 *)(self + 0x14)));
        }
    }
}
