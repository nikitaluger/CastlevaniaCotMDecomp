extern void sub_080AA8A0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_08011898(void *, s32);
extern void sub_08011368(s32, void *, s32, s32);
extern void sub_080C31E0(void *, s32);
extern void *sub_0805FAEC(void *, s32);

struct S_02025FF0_1870 { u8 _0[0x1870]; u32 p; };
extern struct S_02025FF0_1870 D_02025FF0;

void sub_080AA828(void *arg0) {
    u8 *self = (u8 *)arg0;
    void *r0 = *(void **)(self + 0x3C);
    sub_080AA8A0(arg0, r0);
    if (*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) == 0xC) {
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        {
            s32 *nv = (s32 *)0x08671BB0;
            sub_080C31E4(self + 0x18, self + 0x22, *nv);
        }
    }
}

void sub_080AA860(void *arg0) {
    u8 *self = (u8 *)arg0;
    s32 r7 = *(s32 *)(self + 0x38);
    u8 *r4 = *(u8 **)(self + 0x3C);
    u8 *r6 = r4 + 0x34;
    sub_08011898(r4, *(s32 *)(self + 0x4C));
    if (*(s32 *)(r4 + 0x14) > (0x80 << 10)) {
        sub_08011368(r7, r6, 0xC, 0);
    }
    if (*(u16 *)(r4 + 2) != 0) {
        sub_080C31E0(arg0, *(s32 *)(self + 0x24));
    }
}

void *sub_080AA9F0(s32 arg0, s32 arg1, s32 arg2, u8 arg3) {
    void *r = sub_0805FAEC((void *)D_02025FF0.p, 0xCE << 1);
    if (r == NULL) return NULL;
    {
        u8 *p = r;
        *(s32 *)(p + 0x4C) = arg0;
        *(s32 *)(p + 0x5C) = arg1;
        *(s32 *)(p + 0x6C) = arg2;
        p += 0x7C;
        *(u8 *)p = arg3;
    }
    return r;
}

/* Invoke the stored callback on every type-0x19C (0xCE << 1) child of the root object. */
void sub_080AAA30(void) {
    void *mgr = (void *)D_02025FF0.p;
    void *child = *(void **)((u8 *)mgr + 0x30);
    if (child != NULL) {
        s32 typeId = 0xCE << 1;
        do {
            if (*(s16 *)child == typeId) {
                sub_080C31E0(child, *(s32 *)((u8 *)child + 0x24));
            }
            child = *(void **)((u8 *)child + 0x2C);
        } while (child != NULL);
    }
}
