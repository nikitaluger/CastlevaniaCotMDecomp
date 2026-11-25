extern void *D_08671BB0;
extern void *D_08671BD8;
struct S_02021E90 { u8 _0[0x146C]; u16 f146C; };
extern struct S_02021E90 D_02021E90;
extern void sub_08005E80(s32);
extern void sub_0800B824(s32, s32, s32);
extern s32 sub_0800B8C4(void *, s32);
extern s32 sub_080103F0(u8);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_080C31E8(void *, void *, s32, s32);

/* Confirms a menu-style selection for an entity when available (playing a
 * feedback sound/effect and advancing its script), or clears the selection
 * state when the owning entity is idle. */
void sub_0800B288(u8 *self) {
    u8 *parent;
    s32 state;
    s16 scriptIndex;
    parent = *(u8 **)(self + 0x3C);
    state = *(parent + 0x638);
    if (state != 0) {
        state = sub_0800B8C4(self, 0);
        if (state == 0) {
            if (D_02021E90.f146C & 1) {
                if (sub_080103F0(*(self + 0x50)) != 0) {
                    sub_08005E80(0x157);
                    sub_0800B824(0x81DB, 0x270, 0x600);
                    scriptIndex = *(s16 *)(self + 0x22);
                    *(self + scriptIndex * 2 + 0x19) = state;
                    { void **fnaddr = &D_08671BB0; sub_080C31E4(self + 0x18, self + 0x22, (s32)*fnaddr); }
                }
            }
        }
    } else if (D_02021E90.f146C & 3) {
        sub_08005E80(0x159);
        *(parent + 0x635) = state;
        scriptIndex = *(s16 *)(self + 0x22);
        *(self + scriptIndex * 2 + 0x17) = state;
        { void **fnaddr = &D_08671BD8; sub_080C31E8(self + 0x18, self + 0x22, 0x10, (s32)*fnaddr); }
    }
}
