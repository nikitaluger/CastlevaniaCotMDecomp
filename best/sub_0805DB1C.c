extern s32 sub_08007DD8(s32, s32, s32);
extern s32 sub_0805DC5C(s32, s32, s32, s32, s32 *, s32 *, s32);
struct S_02025FF0b { u8 _0[0x18A8]; u8 v; };
extern struct S_02025FF0b gMainWorkspace;
extern u8 gTilemapPages[];
extern u16 D_080D0054[];
struct Res { u16 f0; u16 _2; s32 f4; s32 f8; };

void sub_0805DB1C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, struct Res *arg5) {
    s32 spC, sp10;
    u16 mask = (u16)arg4;
    s32 ret;
    arg5->f0 = 0;
    ret = sub_0805DC5C(arg0, arg1, arg2, arg3, &spC, &sp10, mask);
    do {
if (ret != 0) {
        u16 t;
        u16 t_b1;
        s32 v;
        u8 *table;
        v = sub_08007DD8(0x02023130 + gMainWorkspace.v * 0x40, spC, sp10 + 0x10000);
        table = (u8 *)0x080D0054;
        t = *(u16 *)(table + ((u32)(v << 16) >> 15));
        if (t & mask) arg5->f0 |= 4;
        if (arg3 < 0) {
            v = sub_08007DD8(0x02023130 + gMainWorkspace.v * 0x40, spC, sp10 - 0x10000);
            table = (u8 *)0x080D0054;
            t_b1 = *(u16 *)(table + ((u32)(v << 16) >> 15));
            if (t_b1 & mask) arg5->f0 |= 8;
        }
        if (arg2 > 0) {
            u16 t;
            v = sub_08007DD8(0x02023130 + gMainWorkspace.v * 0x40, spC + 0x10000, sp10);
            table = (u8 *)0x080D0054;
            t = *(u16 *)(table + ((u32)(v << 16) >> 15));
            if ((t & ~8) & mask) arg5->f0 |= 1;
        } else {
            u16 t;
            if (arg2 < 0) {
                v = sub_08007DD8(0x02023130 + gMainWorkspace.v * 0x40, spC - 0x10000, sp10);
                table = (u8 *)0x080D0054;
                t = *(u16 *)(table + ((u32)(v << 16) >> 15));
                if ((t & ~8) & mask) arg5->f0 |= 1;
            }
        }
        {
            u16 v2 = arg5->f0;
            if (!(v2 & 9)) arg5->f0 = v2 | 4;
        }
    }
    } while (0);
    arg5->f4 = spC;
    arg5->f8 = sp10;
}
