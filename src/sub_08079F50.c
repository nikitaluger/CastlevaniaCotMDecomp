struct GameState_79F50 {
    u8 _0[0x10];
    u32 f10;
    u8 _1[0x14ED - 0x14];
    u8 f14ED;
    u8 _2[0x173A - 0x14EE];
    u8 f173A;
    u8 _3[0x18C2 - 0x173B];
    u16 w;
};
extern struct GameState_79F50 D_02025FF0;
extern s32 sub_08003740(void *, s32);
extern s32 sub_0806D2F8(void *, void *);
extern s32 sub_0806D518();
extern void sub_0806D588(void *, void *);
extern void _call_via_r1(void *, s32);

/* Moving-object update: gate on global flags, integrate velocity into the
 * position, copy global sprite flags, tick a delayed script, align the
 * sprite, then bail via the state-change handler or the bounds check. */
void sub_08079F50(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *mover;
    u8 *pos;
    u8 *sprite;
    struct GameState_79F50 *gs;
    mover = *(u8 **)(self + 0x6C);
    pos = mover + 4;
    sprite = *(u8 **)(self + 0x38);
    if (sub_0806D518(self, sprite, pos) == 0) {
        *(s32 *)(mover + 4) = *(s32 *)(mover + 4) + *(s32 *)(pos + 8);
        *(s32 *)(pos + 4) = *(s32 *)(pos + 4) + *(s32 *)(pos + 0x0C);
        gs = &D_02025FF0;
        {
            u16 w = D_02025FF0.w;
            *(u16 *)sprite = w;
        }
        sub_08003740((void *)(mover + 0x20), (s32)sprite);
        sub_0806D588(sprite, pos);
        if (gs->f173A == 0x1C || (gs->f14ED == 0 && gs->f10 != 0)) {
            _call_via_r1(self, *(s32 *)(self + 0x24));
            return;
        }
        sub_0806D2F8(self, sprite);
    }
}
