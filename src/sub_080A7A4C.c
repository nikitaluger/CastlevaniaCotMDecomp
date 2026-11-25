extern void sub_08005E80(s32);
extern void sub_0808D0A4(s32);
extern void sub_080AAA30(void);
extern void sub_080AAACC(void);
extern void sub_080AACA0(void *);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);

struct Body {
    u8 pad[0xEC];
    u16 flags;
    u8 pad2;
    u8 step;
    u8 pad3[0x24];
    s32 value;
};

/* Entity cleanup: configures the body, removes related child objects and plays
 * the appropriate sounds, then advances to the next script step. */
void sub_080A7A4C(void *self)
{
    u8 *gfx;
    struct Body *body;
    u8 *parent;
    void *child;
    s16 stepIdx;
    s32 *pStepCounter;

    gfx = *(u8 **)((u8 *)self + 0x38);
    body = *(struct Body **)((u8 *)self + 0x3C);

    body->step = 2;
    body->flags = 0x10 & *(u16 *)(gfx + 2);
    body->value = 0x200;

    if (*(u8 *)((u8 *)self + 0x4C) == 0) {
        sub_080AAACC();
        child = *(void **)((u8 *)body + 0x180);
        sub_080C31E0(child, (s32)*(void **)((u8 *)child + 0x24));
    } else {
        sub_080AAA30();
    }

    sub_080AACA0(self);

    parent = *(u8 **)((u8 *)self + 0x28);
    if ((*(u8 *)(parent + 0x4C) | *(u8 *)(parent + 0x50)) != 0) {
        sub_08005E80(0x82);
        sub_08005E80(0x186);
        sub_0808D0A4(0xF);
    } else {
        sub_08005E80(0x188);
    }

    stepIdx = *(s16 *)((u8 *)self + 0x22);
    *(u8 *)((u8 *)self + stepIdx * 2 + 0x19) = 0;

    pStepCounter = (s32 *)0x08671BB0;
    {
        u8 *stepBase = (u8 *)self + 0x18;
        sub_080C31E4(stepBase, (u8 *)self + 0x22, *pStepCounter);
    }

    stepIdx = *(s16 *)((u8 *)self + 0x22);
    *(u8 *)((u8 *)self + stepIdx * 2 + 0x19) += 1;

    stepIdx = *(s16 *)((u8 *)self + 0x22);
    {
        u8 *stepBase = (u8 *)self + 0x18;
        stepBase += stepIdx * 2;
        {
            u8 v = *stepBase;
            s32 *arr = *(s32 **)((u8 *)self + 0x14);
            sub_080C31E0(self, arr[v]);
        }
    }
}
