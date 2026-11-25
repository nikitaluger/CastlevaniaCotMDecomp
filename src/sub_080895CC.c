struct S_D { u8 _0[0x10]; u32 f10; u32 f14; u8 _1[0x1824]; };
extern struct S_D D_02025FF0;
extern void sub_080C31E4(void *, void *, s32);
extern void sub_08003A6C(void *, s32, s32);
extern void sub_08003740(void *, void *);
extern void sub_0806D588(void *, void *);
extern void sub_0806D6B4(void *);

/* Move a physics body with collision, start a scripted reaction while the game
 * is outside mode 0x11, then advance the body's timer and screen position. */
void sub_080895CC(void *actor) {
    u8 *self = (u8 *)actor;
    u8 *body = *(u8 **)(self + 0x6C);
    u8 *bodyDyn = body + 4;
    u8 *owner = *(u8 **)(self + 0x38);
    s32 *scriptData;
    sub_0806D6B4(bodyDyn);
    if (D_02025FF0.f14 != 0x11) {
        sub_08003A6C(body + 0x20, 0, 0x08506444);
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        scriptData = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *scriptData);
    }
    sub_08003740(body + 0x20, owner);
    sub_0806D588(owner, bodyDyn);
}
