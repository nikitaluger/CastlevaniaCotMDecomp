extern s32 sub_0800168C(u8 *, s32, s32, s32);
extern void *sub_0805FAEC(s32, s32);
extern s32 sub_080C31E0(s32, s32);
extern void sub_080AFE80(void *);

struct S_02025FF0 { u8 _0[0x1870]; u32 v; };
extern struct S_02025FF0 D_02025FF0;

/* Init an entity that drives two linked child objects: allocate the 0x50-byte
 * work state at self+0x3C, spawn a pair of children (indexes 0 and 1) and keep
 * them in the work state and self+0x7C/+0x6C, set flag bits 0x1000/0x0800 on
 * self, install sub_080AFE80 as its update handler at +0x14, reset the step
 * index at +0x22 and switch to that handler. */
void sub_080AFDF0(u8 *self) {
    u8 *work;
    u8 *childSlots;
    void *child;
    u8 index;

    sub_0800168C(self, 0, 0x50, 0);
    work = *(u8 **)(self + 0x3C);
    if (work == NULL) {
        sub_080C31E0((s32)self, *(s32 *)(self + 0x24));
        return;
    }
    childSlots = work + 0x48;
    child = sub_0805FAEC(D_02025FF0.v, 0x1B0);
    *(void **)childSlots = child;
    *(void **)(self + 0x7C) = child;
    *(u8 *)(*(void **)childSlots + 0x4C) = 0;
    child = sub_0805FAEC(D_02025FF0.v, 0x1B0);
    *(void **)(childSlots + 4) = child;
    *(void **)(self + 0x6C) = child;
    {
        u8 *childIndex = (u8 *)(*(void **)(childSlots + 4) + 0x4C);
        index = 1;
        *childIndex = index;
    }
    {
        u16 flags = 0x1000 | *(u16 *)(self + 0x02);
        flags |= 0x0800;
        *(u16 *)(self + 0x02) = flags;
    }
    *(u32 *)(self + 0x14) = (u32)sub_080AFE80;
    *(u16 *)(self + 0x22) = index;
    sub_080C31E0((s32)self, (s32)sub_080AFE80);
}
