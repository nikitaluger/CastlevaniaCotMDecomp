void sub_08002D7C(void);
void sub_080C31E0(void *, void *);
void sub_080C31E4(void *, void *, u32);

struct S_02025FF0 { u8 _0[0x18C0]; u16 w; };
extern struct S_02025FF0 gMainWorkspace;
struct S_020213DC { s16 v; };
extern struct S_020213DC D_020213DC;

s32 sub_08097DF8(s32 arg0) {
    vu32 *dma = (vu32 *)0x040000D4;
    u32 r2;
    u32 r3;
    dma[0] = (u32)arg0;
    dma[1] = 0x05000180;
    dma[2] = 0x80000040;
    (void)dma[2];
    dma[0] = (u32)arg0;
    r2 = 0x020214E0;
    dma[1] = r2;
    r3 = 0x84000020;
    dma[2] = r3;
    (void)dma[2];
    dma[0] = (u32)arg0;
    r2 += 0x80;
    dma[1] = r2;
    dma[2] = r3;
    return (s32)dma[2];
}

void sub_08097CF4(void) {
    u16 a;
    u16 b;
    a = *(u16 *)0x020279E0;
    a += 1;
    *(u16 *)0x020279E0 = a;
    b = *(u16 *)0x020213DC;
    b -= 1;
    *(u16 *)0x020213DC = b;
    sub_08002D7C();
}

void sub_08097CD4(void *arg0) {
    void *r3 = *(void **)((u8 *)arg0 + 0x3C);
    gMainWorkspace.w = 0;
    sub_080C31E0(arg0, *(void **)((u8 *)r3 + 4));
}

/* When the countdown timer at D_020213DC expires, switch the script state to
 * 2, reset the current command slot's step counter, and restart the command
 * script from the token table at 0x08671BB0. */
void sub_08097C88(void *obj) {
    if (D_020213DC.v <= 0) {
        gMainWorkspace.w = 2;
        *(u8 *)((u8 *)((u32)(*(s16 *)((u8 *)obj + 0x22)) * 2 + (u32)obj) + 0x19) = 0;
        {
            u32 *tokenTable;
            tokenTable = (u32 *)0x08671BB0;
            sub_080C31E4((u8 *)obj + 0x18, (u8 *)obj + 0x22, *tokenTable);
        }
    }
}
