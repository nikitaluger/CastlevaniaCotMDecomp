extern u32 gScriptStepCallbackTable;
extern void *D_0201E8A0;
s32 sub_08014990(s32);
void sub_0801843C(void);
void sub_080C31E4(void *, void *, u32);
void sub_080008A0(void *, s32);

void sub_080172DC(void *arg0) {
    u8 *p = (u8 *)arg0;
    s32 v38 = *(s32 *)(p + 0x38);
    u8 *field = *(u8 **)(p + 0x3C);
    u8 *r7 = field + 0x48;
    void **pp;
    u8 zero;

    sub_0801843C();
    if (sub_08014990(v38) > 0) {
        *(s32 *)(field + 0x10) = 0x60000;
    } else {
        *(s32 *)(field + 0x10) = (s32)0xFFFA0000;
    }
    zero = 0;
    *(u16 *)(r7 + 0x16) = 5;
    *(u8 *)(p + *(s16 *)(p + 0x22) * 2 + 0x19) = zero;
    pp = (void **)0x08671BB0;
    sub_080C31E4(p + 0x18, p + 0x22, (s32)*pp);
}

void sub_08016160(void) {
    *(s32 *)0x020202A8 = 0;
    *(s32 *)0x020202AC = 0;
    *(s32 *)0x020202B0 = 0;
    sub_080008A0((void *)0x0201E8A8, 0xD0 << 5);
}

void sub_0801604C(void *arg0) {
    u8 *p = (u8 *)arg0;
    u8 *dst = *(u8 **)(p + 0x1C);
    u16 flags = *(u16 *)(p + 2);
    s32 v;

    *(u16 *)dst = flags;
    flags = *(u16 *)(p + 2);
    if (!(flags & 0xF0)) {
        *(s32 *)(dst + 4) = *(s32 *)(p + 0xC) - (*(s32 *)(p + 4) + *(s32 *)(p + 0x14));
        *(s32 *)(dst + 8) = *(s32 *)(p + 0x10) - (*(s32 *)(p + 8) + *(s32 *)(p + 0x18));
    } else if (!(flags & 0x60)) {
        *(s32 *)(dst + 4) = 0;
        *(s32 *)(dst + 8) = *(s32 *)(p + 0x10) - (*(s32 *)(p + 8) + *(s32 *)(p + 0x18));
    } else {
        *(s32 *)(dst + 4) = *(s32 *)(p + 0xC) - (*(s32 *)(p + 4) + *(s32 *)(p + 0x14));
        *(s32 *)(dst + 8) = 0;
    }
    *(s32 *)(dst + 0x10) = 0;
    *(s32 *)(dst + 0xC) = 0;
}

/* Unlink the given object from the global object list and free it. */
void freeMotionTracker(void *arg0) {
    void *entry = arg0;
    void *cur = D_0201E8A0;
    void *prev = NULL;

    if (cur != NULL) {
        do {
            if (cur == entry) goto found;
            prev = cur;
            cur = *(void **)((u8 *)cur + 0x10);
        } while (cur != NULL);
    }
    return;
found:
    *(u8 *)cur &= 0x7F;
    if (prev == NULL) {
        D_0201E8A0 = *(void **)((u8 *)cur + 0x10);
    } else {
        *(void **)((u8 *)prev + 0x10) = *(void **)((u8 *)cur + 0x10);
    }
    sub_080008A0(cur, 0x14);
}
