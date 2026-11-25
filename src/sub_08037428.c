extern void sub_080C31E4(void *, void *, s32);
extern void sub_080C31E0(void *, s32);

/* Start callback for a scripted projectile: aim it with the angle stored at
 * +0x7C, give it a fresh speed budget, advance the entity's script, then call
 * the handler selected by the current script byte. */
void sub_08037428(void *arg0)
{
    u32 *callback;
    void *script;
    void *work = *(void **)((u8 *)arg0 + 0x3C);
    *(s32 *)((u8 *)work + 0x4C) = *(s32 *)((u8 *)arg0 + 0x7C);
    *(s32 *)((u8 *)work + 0x48) = 0x40000;
    *(u8 *)((u8 *)arg0 + ((s32)*(s16 *)((u8 *)arg0 + 0x22) * 2) + 0x19) = 0;
    callback = (u32 *)0x08671BB0;
    script = (u8 *)arg0 + 0x18;
    sub_080C31E4(script, (u8 *)arg0 + 0x22, *callback);
    *(u8 *)((u8 *)arg0 + ((s32)*(s16 *)((u8 *)arg0 + 0x22) * 2) + 0x19) += 1;
    script = (u8 *)script + ((s32)*(s16 *)((u8 *)arg0 + 0x22) * 2);
    sub_080C31E0(arg0, *(u32 *)((u8 *)*(u32 *)((u8 *)arg0 + 0x14) + *(u8 *)script * 4));
}
