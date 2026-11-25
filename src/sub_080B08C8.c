struct S_02025FF0 { u8 _0[0x1870]; u32 p; };
extern struct S_02025FF0 D_02025FF0;
extern void *sub_0805FAEC(void *, s32);
void sub_080B089C(s32 arg0, s32 arg1) {
    void *r = sub_0805FAEC((void *)D_02025FF0.p, 0xD6 << 1);
    if (r != NULL) {
        *(s32 *)((u8 *)r + 0x4C) = arg0;
        *(s32 *)((u8 *)r + 0x5C) = arg1;
    }
}

extern void sub_080C31E0(void *, void *);
/* Invoke the stored callback on every type-0x1AC (0xD6 << 1) child of the root object. */
void sub_080B08C8(void) {
    void *mgr = (void *)D_02025FF0.p;
    void *child = *(void **)((u8 *)mgr + 0x30);
    if (child != NULL) {
        s32 typeId = 0xD6 << 1;
        do {
            if (*(s16 *)child == typeId) {
                sub_080C31E0(child, *(void **)((u8 *)child + 0x24));
            }
            child = *(void **)((u8 *)child + 0x2C);
        } while (child != NULL);
    }
}

struct S_70 { u8 pad[0x70]; u8 b; };
void *sub_080B0934(s32 arg0, s32 arg1) {
    void *r = sub_0805FAEC((void *)D_02025FF0.p, 0x1AF);
    if (r == NULL) return NULL;
    *(s32 *)((u8 *)r + 0x4C) = arg0;
    *(s32 *)((u8 *)r + 0x5C) = arg1;
    ((struct S_70 *)r)->b = 0;
    return r;
}

extern void sub_08097F70(s32, s32);
extern void sub_080C31E4(void *, void *, s32);
struct S_40 { u8 pad[0x40]; u32 v; };
extern struct S_40 D_02025FF0_x;
void sub_080B0DE8(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *p3C = *(u8 **)(self + 0x3C);
    u8 *p4C = *(u8 **)(self + 0x4C);
    if (D_02025FF0_x.v == 2) {
        s32 z = 0;
        *(u8 *)(p4C + 0x34) = z;
        sub_08097F70(0x0840ABCC, 0);
        *(u8 *)(*(u8 **)(p3C + 0x28) + 1) = 5;
        *(u8 *)(*(u8 **)(p3C + 0x48) + 1) = 1;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = z;
        {
            s32 *lit = (s32 *)0x08671BB0;
            sub_080C31E4(self + 0x18, self + 0x22, *lit);
        }
    }
}
