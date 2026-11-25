void sub_080A2E74(void *arg0)
{
    if (arg0 != 0) {
        *(u8 *)((u8 *)arg0 + 0x54) = 1;
    }
}

void sub_080A2E84(void *arg0, s32 arg1)
{
    if (arg0 != 0) {
        *(u8 *)((u8 *)arg0 + 0x4C) = 1;
        *(s32 *)((u8 *)arg0 + 0x5C) = arg1;
    }
}

extern void sub_080C31E4(void *, void *, s32);
extern void sub_080C31E0(void *, s32);

/* Reset the work's two state words at +0x48/+0x4C to 2, advance the entity's
 * script, then call the handler selected by the current script byte. */
void sub_080A3560(void *arg0)
{
    u32 *callback;
    void *script;
    void *work = *(void **)((u8 *)arg0 + 0x3C);
    *(s32 *)((u8 *)work + 0x48) = 2;
    *(s32 *)((u8 *)work + 0x4C) = 2;
    *(u8 *)((u8 *)arg0 + ((s32)*(s16 *)((u8 *)arg0 + 0x22) * 2) + 0x19) = 0;
    callback = (u32 *)0x08671BB0;
    script = (u8 *)arg0 + 0x18;
    sub_080C31E4(script, (u8 *)arg0 + 0x22, *callback);
    *(u8 *)((u8 *)arg0 + ((s32)*(s16 *)((u8 *)arg0 + 0x22) * 2) + 0x19) += 1;
    script = (u8 *)script + ((s32)*(s16 *)((u8 *)arg0 + 0x22) * 2);
    sub_080C31E0(arg0, *(u32 *)((u8 *)*(u32 *)((u8 *)arg0 + 0x14) + *(u8 *)script * 4));
}

extern void sub_080161F0(void);

void sub_080A25D4(void *arg0)
{
    s32 *r4;
    s32 r5;
    void *r6;

    r6 = *(void **)((u8 *)arg0 + 0x3C);
    r5 = 0;
    r4 = (s32 *)((u8 *)r6 + 0x48);
    do {
        if (*r4 != 0) {
            sub_080161F0();
        }
        r4++;
        r5++;
    } while (r5 == 0);
    sub_080C31E0(arg0, *(s32 *)((u8 *)r6 + 0x24));
}
