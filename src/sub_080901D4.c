extern void sub_08007E24(u16);
extern void sub_08005E80(s32);
extern void sub_080C31E4(void *, void *, s32);

struct S_02025FF0_1848 { u8 _0x000[0x1848]; u32 v; };
extern struct S_02025FF0_1848 gMainWorkspace;

/* When the work object's trigger flag (bit 2 at +0x20) is set, unlock the
 * ability named by its linked data, clear its timer, set the global progress
 * bits and a work field, play a sound, then clear and advance the script step. */
void sub_080901D4(void *arg0) {
    u8 *entity = (u8 *)arg0;
    u8 *work = *(u8 **)(entity + 0x3C);
    u8 *triggerFlag;
    u8 zero = 0;
    triggerFlag = work;
    triggerFlag += 0x20;
    if (*triggerFlag & 2) {
        sub_08007E24(*(u16 *)(*(u8 **)(work + 0x1C) + 2));
        *(u16 *)(work + 0x14) = 0;
        gMainWorkspace.v |= 0x4D7E0000;
        *(u16 *)(work + 0x18) = *(u16 *)*(u8 **)(work + 0x1C);
        sub_08005E80(0x1BE);
        *(u8 *)(entity + *(s16 *)(entity + 0x22) * 2 + 0x19) = zero;
        {
            s32 *scriptCb = (s32 *)0x08671BB0;
            sub_080C31E4(entity + 0x18, entity + 0x22, *scriptCb);
        }
    }
}
