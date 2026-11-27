extern void sub_080C31E0(void *, s32);
extern void advanceAnimTrack(s32, void *);
extern void sub_080C31E8(void *, void *, s32, s32);
extern void setObjectAnimation(s32, void *, s32, s32);
extern void startScriptOnce(s32, s32, s32);
struct S_02025FF0_1870 { u8 _0[0x1870]; u32 p; };
extern struct S_02025FF0_1870 gMainWorkspace;

void sub_080B307C(void) {
    void *p = (void *)gMainWorkspace.p;
    void *e = *(void **)((u8 *)p + 0x30);
    if (e != NULL) {
        s32 v = 0xDD << 1;
        do {
            if (*(s16 *)e == v) {
                sub_080C31E0(e, *(s32 *)((u8 *)e + 0x24));
            }
            e = *(void **)((u8 *)e + 0x2C);
        } while (e != NULL);
    }
}

/* Run one step of the entity's command script; the 0x78 command clears the
 * previous-command byte and restarts the handler table at command 3. */
void sub_080B4504(void *arg0) {
    u8 *obj = (u8 *)arg0;
    advanceAnimTrack(*(s32 *)(obj + 0x38), (u8 *)*(void **)(obj + 0x3C) + 0x34);
    if (*(u8 *)(obj + *(s16 *)(obj + 0x22) * 2 + 0x19) == 0x78) {
        s32 *lit;
        *(u8 *)(obj + *(s16 *)(obj + 0x22) * 2 + 0x17) = 0;
        lit = (s32 *)0x08671BD8;
        sub_080C31E8(obj + 0x18, obj + 0x22, 3, *lit);
    }
}

void sub_080B489C(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *p5 = *(u8 **)(self + 0x3C);
    u8 *r6 = p5 + 0x48;
    setObjectAnimation(*(s32 *)(self + 0x38), p5 + 0x34, 0x68, 0);
    if (*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) == 6) {
        u8 z = 0;
        s32 *lit;
        *(u8 *)(p5 + 0x69) = 1;
        *(u8 *)(r6 + 0x1F) = z;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x17) = z;
        lit = (s32 *)0x08671BD8;
        sub_080C31E8(self + 0x18, self + 0x22, 3, *lit);
    }
}

void sub_080B12C0(void *arg0) {
    u8 *self = (u8 *)arg0;
    if (*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) == 0x1E) {
        s32 *lit;
        startScriptOnce(*(s32 *)(self + 0x4C), 1, 1);
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x17) = 0;
        lit = (s32 *)0x08671BD8;
        sub_080C31E8(self + 0x18, self + 0x22, 2, *lit);
    }
}
