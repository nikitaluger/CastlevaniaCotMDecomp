extern void sub_080C31E8(void *, void *, s32, s32);

struct S_081017CC { u32 a, b, c; };
extern struct S_081017CC D_081017CC;

// Propagates a mode value (1, or 5 when the slot byte is 0x5A) to the child and
// neighbour objects linked through +0x28/+0x48, clears a companion slot byte,
// and in the 0x5A case dispatches an indirect callback with a value looked up
// from the D_081017CC table.
void sub_0809A588(u8 *self) {
    u8 *child = *(u8 **)(self + 0x3C);
    u8 *neighbor = child + 0x48;
    u8 *target;
    struct S_081017CC valueTable;
    s32 *callbackSlot;
    s32 zero;

    valueTable = D_081017CC;
    target = *(u8 **)(child + 0x28);
    zero = 0;
    *(target + 1) = 1;
    *(*(u8 **)(child + 0x48) + 1) = 1;
    *(*(u8 **)(neighbor + 0x04) + 1) = 1;
    *(*(u8 **)(*(u8 **)(*(u8 **)(neighbor + 0x08) + 0x3C) + 0x28) + 1) = zero;
    if (*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) == 0x5A) {
        *(*(u8 **)(child + 0x28) + 1) = 5;
        *(*(u8 **)(child + 0x48) + 1) = 5;
        *(*(u8 **)(neighbor + 0x04) + 1) = 5;
        *(*(u8 **)(*(u8 **)(*(u8 **)(neighbor + 0x08) + 0x3C) + 0x28) + 1) = 5;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x17) = zero;
        callbackSlot = (s32 *)0x08671BD8;
        sub_080C31E8(self + 0x18, self + 0x22, ((u32 *)&valueTable)[*(u8 *)(child + 0x68)], *callbackSlot);
    }
}
