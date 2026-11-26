extern void sub_080C31E0(void *, s32);
extern void *sub_0805FAEC(void *, s32);
struct S_02025FF0_1870 { u8 _0[0x1870]; u32 p; };
extern struct S_02025FF0_1870 gMainWorkspace;

void sub_080AAACC(void) {
    void *p = (void *)gMainWorkspace.p;
    void *e = *(void **)((u8 *)p + 0x30);
    if (e != NULL) {
        s32 v = 0xCF << 1;
        do {
            if (*(s16 *)e == v) {
                sub_080C31E0(e, *(s32 *)((u8 *)e + 0x24));
            }
            e = *(void **)((u8 *)e + 0x2C);
        } while (e != NULL);
    }
}

/* Spawn a type-0x1A0 child and fill its +0x4C/+0x5C/+0x6C parameter slots. */
void sub_080AAB04(void *parent, s32 value1, s32 value2) {
    void *obj = sub_0805FAEC((void *)gMainWorkspace.p, 0xD0 << 1);
    if (obj != 0) {
        *(s32 *)((u8 *)obj + 0x4C) = value1;
        *(s32 *)((u8 *)obj + 0x5C) = value2;
        *(s32 *)((u8 *)obj + 0x6C) = *(s32 *)((u8 *)*(void **)((u8 *)parent + 0x38) + 0x24);
    }
}

void sub_080AAB3C(s32 arg0, s32 arg1, u8 arg2) {
    void *r = sub_0805FAEC((void *)gMainWorkspace.p, 0x1A1);
    if (r != 0) {
        u8 *p;
        *(s32 *)((u8 *)r + 0x4C) = arg0;
        *(s32 *)((u8 *)r + 0x5C) = arg1;
        p = (u8 *)r + 0x6C;
        *p = arg2;
    }
}

void sub_080AAC20(u8 arg0, s32 arg1, s32 arg2) {
    void *r = sub_0805FAEC((void *)gMainWorkspace.p, 0xD2 << 1);
    if (r != 0) {
        u8 *p = (u8 *)r + 0x7C;
        *p = arg0;
        *(s32 *)((u8 *)r + 0x4C) = arg1;
        *(s32 *)((u8 *)r + 0x5C) = arg2;
    }
}
