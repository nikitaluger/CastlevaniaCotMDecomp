extern void setAnimationFrame(s32, void *, s32, s32);
extern void sub_080C31E8(void *, void *, s32, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_080C31E0(void *, s32);
extern void sub_080161F0(void *);
extern void clearObjectSlot(void *);
extern s32 D_08671BD8[];
extern s32 gMainObjTimerCallback[];

void sub_0801F838(void *arg0) {
    u8 *self = (u8 *)arg0;
    s32 a0 = *(s32 *)(self + 0x38);
    u8 *r1 = *(u8 **)(self + 0x3C);
    u8 *r4 = r1 + 0x34;
    u8 *r6 = r1 + 0x48;
    s32 *lit;

    setAnimationFrame(a0, r4, 8, 0);
    if (*(u8 *)r4 & 2) {
        s16 idx = *(s16 *)(self + 0x22);
        *(u8 *)(self + idx * 2 + 0x17) = 0;
        *(u16 *)(r6 + 6) = 0x78;
        lit = D_08671BD8;
        sub_080C31E8(self + 0x18, self + 0x22, 3, *lit);
    }
}

/* Tear down an object: unregister it (clearObjectSlot), free the two objects it
 * owns (data+0x28 and script+4) and pass data+0x24 to sub_080C31E0. */
void destroyObject(void *obj) {
    u8 *self = (u8 *)obj;
    u8 *data = *(u8 **)(self + 0x3C);
    u8 *script = data + 0x48;

    clearObjectSlot(obj);
    if (*(u32 *)(data + 0x28) != 0) {
        sub_080161F0(*(void **)(data + 0x28));
    }
    if (*(u32 *)(script + 4) != 0) {
        sub_080161F0(*(void **)(script + 4));
    }
    sub_080C31E0(obj, *(s32 *)(data + 0x24));
}

void clearObjectSlot(void *arg0)
{
    if (!(2 & *(u16 *)((u8 *)arg0 + 0x6C)))
    {
        u32 *base = *(u32 **)(*(u8 **)((u8 *)arg0 + 0x8C) + 0x3C);
        u32 zero = 0;
        u32 *p = base + 0x1C;
        s32 i = 9;
        do
        {
            if (*p == (u32)arg0)
                *p = zero;
            p++;
        } while (--i >= 0);
    }
}

void sub_0802459C(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *r2 = *(u8 **)(self + 0x3C);
    u8 *r1 = r2 + 0x34;
    u8 *r5 = r2 + 0x48;
    s32 *lit;

    setAnimationFrame(*(s32 *)(self + 0x38), r1, 3, 0);
    *(u16 *)r5 = *(u16 *)r5 - 1;
    if ((s16)*(u16 *)r5 < 0) {
        s16 idx;
        *(u16 *)r5 = 0;
        idx = *(s16 *)(self + 0x22);
        *(u8 *)(self + idx * 2 + 0x19) = 0;
        lit = gMainObjTimerCallback;
        sub_080C31E4(self + 0x18, self + 0x22, *lit);
    }
}
