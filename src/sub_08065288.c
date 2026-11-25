extern s32 D_08671BD8;
extern s32 sub_0806C4B4(void *, void *);
extern void sub_0806C5EC(void *, void *, void *, void *);
extern void sub_0806A884(void *, void *);
extern s32 sub_08003740(void *, void *);
extern u16 sub_08065CC8(void *, void *, void *, void *);
extern u16 sub_0806BCD8(void *, void *, void *, void *);
extern void sub_0806C6B0(void *, void *, void *, void *);
extern void sub_080C31E8(void *, void *, s32, s32);

/* Behaviour callback: wait for the game mode to supply a target point, then run the
 * movement/collision steps and dispatch the resulting script commands. */
void sub_08065288(u8 *behav) {
    u8 *params;
    u8 *point;
    u8 *target;
    s32 camMode;
    u8 *script;
    u8 *idxPtr;
    s32 *cmdTable;
    params = *(u8 **)(behav + 0x6C);
    point = params + 4;
    target = *(u8 **)(behav + 0x38);
    camMode = sub_0806C4B4(point, point);
    if (camMode == 0) {
        s32 sp0;
        sub_0806C5EC(behav, target, point, point);
        sub_0806A884(target, point);
        sp0 = (s32)params + 0x2C;
        if (sub_08003740(sp0, target) == 0) {
            *(u8 *)(behav + (*(s16 *)(behav + 0x22)) * 2 + 0x17) = camMode;
            {
                u8 *p18 = behav;
                u8 *p22 = behav;
                s32 *lit = &D_08671BD8;
                u16 rv;
                p18 += 0x18;
                p22 += 0x22;
                rv = sub_08065CC8(behav, target, point, point);
                sub_080C31E8(p18, p22, rv, *lit);
            }
        }
        {
            s32 code;
            code = sub_0806BCD8(behav, target, point, point);
            *(u32 *)(params + 0xC8) = (u16)code;
            if ((u16)code != 0) {
                sub_08003740(sp0, target);
                *(u8 *)(behav + (*(s16 *)(behav + 0x22)) * 2 + 0x17) = camMode;
                {
                    u8 *p18 = behav;
                    u8 *p22 = behav;
                    s32 *lit = &D_08671BD8;
                    p18 += 0x18;
                    p22 += 0x22;
                    sub_080C31E8(p18, p22, *(u32 *)(params + 0xC8), *lit);
                }
            }
        }
        sub_0806C6B0(behav, target, point, point);
    }
}
