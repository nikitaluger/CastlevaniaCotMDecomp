extern void sub_08003A6C(void *, s32, void *);
extern void sub_0806D588(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_080C31E0(void *, s32);
extern void sub_0808C9BC(void *);

/* Initialize the actor's script/callback state, snap its position to the grid, then advance the script slot and invoke the resulting callback. */
void sub_0808C3C4(void *arg0)
{
    u8 *self = (u8 *)arg0;
    void *actor = *(void **)(self + 0x6C);
    void *pos = (u8 *)actor + 4;
    void *result = *(void **)(self + 0x38);

    *(u32 *)((u8 *)pos + 0x18) = *(u32 *)(self + 0x24);
    *(u32 *)(self + 0x24) = (u32)sub_0808C9BC;
    *(u32 *)((u8 *)result + 0x24) = 0x0862ECE4;
    sub_08003A6C((u8 *)actor + 0x20, 0, (void *)0x0862ED1C);
    *(u32 *)((u8 *)actor + 4) = 0x780000;
    *(u32 *)((u8 *)pos + 4) = 0x480000;
    sub_0806D588(result, pos);

    *(u8 *)(self + (s32)*(s16 *)(self + 0x22) * 2 + 0x19) = 0;
    {
        const u32 *scriptTable = (const u32 *)0x08671BB0;
        void *entry = self + 0x18;
        sub_080C31E4(entry, self + 0x22, *scriptTable);
        *(u8 *)(self + (s32)*(s16 *)(self + 0x22) * 2 + 0x19) += 1;
        entry = (u8 *)entry + (s32)*(s16 *)(self + 0x22) * 2;
        sub_080C31E0(arg0, *(u32 *)(*(u32 *)(self + 0x14) + *(u8 *)entry * 4));
    }
}
