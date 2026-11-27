extern void drawDecimalNumber(s32, s32, s32, s32);
extern void sub_0800EBDC(s32, s32, s32);
struct Record { s16 lo; s16 hi; };
extern struct Record gGameStatus[];

/* Draw the record panel: three decimal figures from the record table followed
 * by four comparison markers, each on its own row of tilemap VRAM. */
void sub_0800ECF8(void) {
    s32 record;
    s16 value;
    record = 0xB1;
    drawDecimalNumber(gGameStatus[record].hi, 4, 0x511C, 0x0600706E);
    record = 0xB3;
    drawDecimalNumber(gGameStatus[record].hi, 4, 0x511C, 0x060070AE);
    record = 0xB5;
    drawDecimalNumber(gGameStatus[record].lo, 3, 0x511C, 0x060070EE);
    record = 0xB8;
    value = gGameStatus[record].lo;
    sub_0800EBDC(value, value, 0x0600716E);
    record = 0xBA;
    value = gGameStatus[record].lo;
    sub_0800EBDC(value, value, 0x060071AE);
    record = 0xBC;
    value = gGameStatus[record].lo;
    sub_0800EBDC(value, value, 0x060071EE);
    record = 0xBE;
    value = gGameStatus[record].lo;
    sub_0800EBDC(value, value, 0x0600722E);
}
