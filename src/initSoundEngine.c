extern void sub_080BFBB8(void *);
extern void sub_080C2F1C(s32 *, void *, u32);
extern void sub_080C14E8(void);
extern void sub_080C02D8(void);
extern void sub_080C02EC(void);
extern void sub_080C1640(void);
extern void sub_080C0270(void);
extern void sub_080C082C(void);
extern void sub_080C0020(void);
extern void sub_080C0BB0(void);
extern void sub_080C0C30(void);
extern void sub_080C0E58(void);
extern void sub_080C0DA0(void);
extern void sub_080C0CF8(void);
extern u8 D_00000000[];

/* Initialize the sound engine: program the GBA sound registers, verify the
 * engine magic at [0x03007FF0], build the callback table in its IWRAM work
 * area at 0x03004040, set up the player through sub_080C2F1C, and seed its
 * per-player state bytes. */
void initSoundEngine(void *player)
{
    volatile u32 *engine;
    u32 magic;
    u8 *work;
    u8 *table;
    s32 setupResult;
    volatile u8 *reg;
    u32 zeroAddr;
    s32 zero;

    *(volatile u16 *)0x04000084 = 0x8F;
    *(volatile u16 *)0x04000080 = 0x77;

    reg = (volatile u8 *)0x04000063;
    *reg = 8;
    reg += 6;
    *reg = 8;
    reg += 0x10;
    *reg = 8;
    reg -= 0x14;
    *reg = 0x80;
    reg += 8;
    *reg = 0x80;
    reg += 0x10;
    *reg = 0x80;
    *(volatile u8 *)0x04000070 = 0;
    *(volatile u16 *)0x04000080 = 0xFF77;

    engine = *(volatile u32 **)0x03007FF0;
    magic = *engine;
    if (magic == 0x68736D53) {
        *engine = magic + 1;
        work = (u8 *)0x03004040;
        sub_080BFBB8(work);
        table = work;
        *(u32 *)(table + 0x20) = (u32)sub_080C14E8;
        *(u32 *)(table + 0x44) = (u32)sub_080C02D8;
        *(u32 *)(table + 0x4C) = (u32)sub_080C02EC;
        *(u32 *)(table + 0x70) = (u32)sub_080C1640;
        *(u32 *)(table + 0x74) = (u32)sub_080C0270;
        *(u32 *)(table + 0x78) = (u32)sub_080C082C;
        *(u32 *)(table + 0x7C) = (u32)sub_080C0020;
        *(u32 *)(table + 0x80) = (u32)sub_080C0BB0;
        *(u32 *)(table + 0x84) = (u32)sub_080C0C30;

        engine[0x1C/4] = (u32)player;
        engine[0x28/4] = (u32)sub_080C0E58;
        engine[0x2C/4] = (u32)sub_080C0DA0;
        engine[0x30/4] = (u32)sub_080C0CF8;
        engine[0x34/4] = (u32)work;

        zeroAddr = (u32)D_00000000;
        zero = 0;
        ((volatile u8 *)engine)[0x0C] = zeroAddr;
        setupResult = zero;
        sub_080C2F1C(&setupResult, player, 0x05000040);

        ((u8 *)player)[1] = 1;
        ((u8 *)player)[0x1C] = 0x11;
        ((u8 *)player)[0x41] = 2;
        ((u8 *)player)[0x5C] = 0x22;
        ((u8 *)player)[0x81] = 3;
        ((u8 *)player)[0x9C] = 0x44;
        {
            u8 *q = (u8 *)player + 0xC0;
            q[1] = 4;
            q[0x1C] = 0x88;
        }

        *engine = magic;
    }
}
