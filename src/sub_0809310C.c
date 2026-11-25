/* Returns 0 when the global mode word at 0x020279E8 is 0xE, -1 otherwise. */
s32 sub_0809295C(void)
{
    if (*(s16 *)0x020279E8 == 0xE)
        return 0;
    return -1;
}

extern void sub_080C31E4(void *, void *, s32);

/* When the entity's group has state 1 at +0xE, latch it into +0xC, clear the
 * entity's current script slot flag and re-dispatch its command script. */
void sub_080922A4(void *arg0)
{
    u8 *group = *(u8 **)((u8 *)arg0 + 0x3C);
    s16 state = *(s16 *)(group + 0xE);
    if (state == 1) {
        void **pp;
        *(s16 *)(group + 0xC) = state;
        *(u8 *)((u8 *)arg0 + *(s16 *)((u8 *)arg0 + 0x22) * 2 + 0x19) = 0;
        pp = (void **)0x08671BB0;
        sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, (s32)*pp);
    }
}

/* If the group's flag byte at +0x1C has bit 2 set, clear a byte in the group's
 * +4 child, clear the entity's script slot flag and re-dispatch its script. */
void sub_0809310C(void *arg0)
{
    u8 *group = *(u8 **)((u8 *)arg0 + 0x3C);
    if (*(u8 *)(group + 0x1C) & 2) {
        void **pp;
        *(u8 *)(*(u8 **)(group + 4) + 1) = 0;
        *(u8 *)((u8 *)arg0 + *(s16 *)((u8 *)arg0 + 0x22) * 2 + 0x19) = 0;
        pp = (void **)0x08671BB0;
        sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, (s32)*pp);
    }
}

extern void sub_08015974(void);
extern void sub_080C31E0(void *, s32);

struct S_02025FF0_9324C {
    u8 pad[0x3C];
    u16 h3C;
};
extern struct S_02025FF0_9324C D_02025FF0;

/* Unlink the group's +4 child when present, clear the scene header at +0x3C
 * and dispatch the entity's +8 handler. */
void sub_0809324C(void *arg0)
{
    u8 *group = *(u8 **)((u8 *)arg0 + 0x3C);
    if (*(s32 *)(group + 4) != 0)
        sub_08015974();
    D_02025FF0.h3C = 0;
    sub_080C31E0(arg0, *(s32 *)(group + 8));
}
