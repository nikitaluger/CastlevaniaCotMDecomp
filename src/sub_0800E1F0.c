/* Resolve a graphics entry from the current state byte; on success set up the
 * graphics state, upload two attribute blocks selected by the globals, clear the
 * entity's pose byte and run its behaviour script. */
extern s32 sub_0805FEC8(u16);
extern void sub_0805FDF0(void);
extern void sub_0805FEB4(s32);
extern void sub_08000E54(s32, s32, s32, s32, s32);
extern void sub_080C31E4(void *, void *, s32);
extern u16 D_080CB062[];
extern u8 D_020278D0[];
extern u8 D_02021E90[];

void sub_0800E1F0(u8 *self)
{
    s32 result;
    result = sub_0805FEC8(D_080CB062[(s8)D_020278D0[0xF7]]);
    if (result == 0) {
        u16 *attrPtr;
        s32 attrSize;
        u32 gfxBase, attrOffset;
        sub_0805FDF0();
        sub_0805FEB4(0);

        gfxBase = (u32)D_02021E90;
        attrOffset = 0x1262;
        attrPtr = (u16 *)(gfxBase + attrOffset);
        sub_08000E54(1, 0, ((*attrPtr & 0xC) << 12) + 0x06000040, 0xFC0, (attrSize = 0x10));
        sub_08000E54(1, 0, ((*attrPtr & 0xC) << 12) + 0x06000020, 0x20, attrSize);

        {
            s16 scriptIndex = *(s16 *)(self + 0x22);
            *(u8 *)(self + scriptIndex * 2 + 0x19) = result;
            {
                s32 *fnaddr = (s32 *)0x08671BC0;
                sub_080C31E4(self + 0x18, self + 0x22, *fnaddr);
            }
        }
    }
}
