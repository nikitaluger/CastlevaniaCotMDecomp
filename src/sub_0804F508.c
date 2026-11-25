s32 sub_08014A6C(void *, s32, s32, s32);
s32 sub_080C31E4(void *, void *, s32);
extern u32 D_08671BB4[];

/* A word-first zero pair keeps agbcc from merging the two distinct #0 stores. */
struct ZeroPair { u32 w; u8 b; };

/* When the work object's distance check (sub_08014A6C, range 0x2000) reports
 * arrival, reset the timer at +0x54 and the state word at +0x48, clear this
 * step's action byte at +0x17 and run the handler at D_08671BB4[0]. */
void sub_0804F508(u8 *arg0)
{
    u8 *work = *(u8 **)(arg0 + 0x3C);
    u8 *moveState = work + 0x48;
    if (sub_08014A6C(work, *(s32 *)(moveState + 8), 0x2000, 0) == 1) {
        u32 *handlerTable;
        struct ZeroPair zeros = {0, 0};
        register u8 byteZero = zeros.b;
        register u32 wordZero = zeros.w;
        *(u16 *)(moveState + 0xC) = 0x3C;
        *(s32 *)(moveState + 4) = wordZero;
        *(s32 *)(work + 0x48) = *(s32 *)(work + 0xC);
        *(u8 *)(arg0 + *(s16 *)(arg0 + 0x22) * 2 + 0x17) = byteZero;
        handlerTable = D_08671BB4;
        sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *handlerTable);
    }
}
