s32 sub_080141AC(void *, void *);
s32 sub_08016238(void *);
s32 sub_08013B5C(void *, void *);
void sub_08013C8C(void *, void *);
s32 sub_080C31E0(s32, s32);
void sub_080C31E8(void *, void *, u32, u32);

/* Runs one tick of a scripted entity: flag the actor on contact/state changes,
 * perform a one-time step action, then dispatch the current script step. */
void sub_08048FC8(void *self) {
    void *sprite;
    void *actor;
    u32 *fnaddr;

    sprite = *(void **)((u8 *)self + 0x38);
    actor = *(void **)((u8 *)self + 0x3C);
    if (sub_080141AC(sprite, actor) == 1) {
        sub_080C31E0((s32)self, *(s32 *)((u8 *)self + 0x24));
        return;
    }
    if (sub_08016238(*(void **)((u8 *)actor + 0x28)) != 0) {
        s32 tmp = 1 | *(u16 *)actor;
        *(u16 *)actor = tmp;
    }
    if (1 & *(u16 *)((u8 *)*(void **)((u8 *)actor + 0x28) + 0x14)) {
        s32 tmp = 1 | *(u16 *)actor;
        *(u16 *)actor = tmp;
    }
    if (1 & *(u16 *)actor) {
        if (*(u8 *)((u32)(*(s16 *)((u8 *)self + 0x22)) * 2 + (u32)self + 0x1A) != 1) {
            *(u8 *)((u32)(*(s16 *)((u8 *)self + 0x22)) * 2 + (u32)self + 0x1B) = 0;
            fnaddr = (u32 *)0x08671BDC;
            sub_080C31E8((u8 *)self + 0x18, (u8 *)self + 0x22, 1, *fnaddr);
        }
    }
    if (*(u8 *)((u8 *)self + 0x8C) != 0 || sub_08013B5C(sprite, actor) == 0) {
        u8 *stepPtr;
        u8 stepByte;
        s32 stepOffset;
        *(u32 *)((u8 *)self + 0x14) = 0x0866E380;
        *(u16 *)((u8 *)self + 0x22) = *(u16 *)((u8 *)self + 0x22) + 1;
        ((u8 *)self + *(s16 *)((u8 *)self + 0x22) * 2)[0x19]++;
        stepOffset = (s32)(s16)(*(s16 *)((u8 *)self + 0x22)) * 2;
        stepPtr = (u8 *)self;
        stepPtr += 0x18;
        stepPtr += stepOffset;
        stepByte = *stepPtr;
        sub_080C31E0((s32)self, *(s32 *)((u32)(stepByte * 4) + *(u32 *)((u8 *)self + 0x14)));
        *(u16 *)((u8 *)self + 0x22) = *(u16 *)((u8 *)self + 0x22) - 1;
    }
    sub_08013C8C(self, sprite);
}
