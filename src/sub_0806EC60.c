extern s16 sub_0806D62C(u16, s32);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);

struct S_02025368 { u8 _pad[0x2DE]; u16 v; };
extern struct S_02025368 gGameStatus;

struct A_6EC60 {
    u8 _0;
    u8 f1;
    u8 f2;
    u8 f3;
    u16 f4;
    u16 f6;
    u16 f8;
    u16 fA;
    u16 fC;
    u16 fE;
    s32 f10;
    u16 _14;
    u16 f16;
    u16 f18;
};
struct B_6EC60 { u8 _0[0x3C]; struct A_6EC60 *p; };

/* Initialize a scripted effect's attribute block from a percentage of a global
 * gauge, clear its state byte, then advance and dispatch its script callbacks. */
void sub_0806EC60(void *arg0) {
    u8 *self;
    u8 *stateBlock;
    s32 animCtrl;
    s32 zero;
    u16 gauge;
    u8 *scriptPos;
    s32 *lit;
    struct S_02025368 *base;

    self = (u8 *)arg0;
    stateBlock = *(u8 **)(self + 0x6C) + 4;
    animCtrl = *(s32 *)(self + 0x38);
    base = &gGameStatus;
    ((struct B_6EC60 *)stateBlock)->p->f1 = 0;
    ((struct B_6EC60 *)stateBlock)->p->f2 = 2;
    ((struct B_6EC60 *)stateBlock)->p->f3 = 8;
    zero = 0;
    ((struct B_6EC60 *)stateBlock)->p->f4 = 0;
    ((struct B_6EC60 *)stateBlock)->p->f6 = 2;
    ((struct B_6EC60 *)stateBlock)->p->f8 = 2;
    ((struct B_6EC60 *)stateBlock)->p->fA = 0;
    ((struct B_6EC60 *)stateBlock)->p->fC = 0;
    gauge = base->v;
    ((struct B_6EC60 *)stateBlock)->p->fE = sub_0806D62C(gauge, 0x7E);
    ((struct B_6EC60 *)stateBlock)->p->f10 = animCtrl;
    ((struct B_6EC60 *)stateBlock)->p->f16 = 0xF;
    ((struct B_6EC60 *)stateBlock)->p->f18 = 0x10;
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = zero;
    lit = (s32 *)0x08671BB0;
    scriptPos = self + 0x18;
    sub_080C31E4(scriptPos, self + 0x22, *lit);
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
    scriptPos += *(s16 *)(self + 0x22) * 2;
    sub_080C31E0(arg0, *(s32 *)(*(s32 *)(self + 0x14) + *(u8 *)scriptPos * 4));
}
