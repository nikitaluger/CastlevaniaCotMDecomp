struct S_02025FF0_9D34 { u8 _0[0x18C2]; u16 f18C2; };
extern struct S_02025FF0_9D34 D_02025FF0;
extern s32 sub_0800168C(void *, s32, s32, s32);
extern void *sub_0800355C(void);
extern void sub_0806D2D0(void *);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);

/* Initialize a scripted effect: allocate its body and animation controller, set
 * sprite attributes from a position offset, then start its script callbacks. */
void sub_08079D34(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *animCtrl;
    u32 delta;
    if (sub_0800168C((void *)self, 0, 0x68, 3) == 0) {
        sub_080C31E0((void *)self, *(void **)(self + 0x24));
        return;
    }
    animCtrl = sub_0800355C();
    if (animCtrl == 0) {
        sub_0806D2D0((void *)self);
        return;
    }
    *(u8 **)(self + 0x38) = animCtrl;
    *(u32 *)(animCtrl + 0x1C) = 0x80000004;
    *(u16 *)animCtrl = D_02025FF0.f18C2;
    delta = *(u32 *)(self + 0x9C) - 0x40;
    *(u16 *)(animCtrl + 2) = delta > 0x80 ? (0xFFEF & *(u16 *)(animCtrl + 2)) : (*(u16 *)(animCtrl + 2) | 0x10);
    self[*(s16 *)(self + 0x22) * 2 + 0x19] = 0;
    {
        s32 *lit = (s32 *)0x08671BB0;
        u8 *scriptPos = self + 0x18;
        sub_080C31E4(scriptPos, self + 0x22, *lit);
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
        scriptPos = scriptPos + *(s16 *)(self + 0x22) * 2;
        sub_080C31E0((void *)self, *(void **)(*(u32 *)(self + 0x14) + *(u8 *)scriptPos * 4));
    }
}
