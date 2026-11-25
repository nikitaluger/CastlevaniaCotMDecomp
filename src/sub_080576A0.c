struct S_02025FF0 { u8 _0[0x18C2]; u16 field18C2; };
extern struct S_02025FF0 D_02025FF0;
extern void sub_0800168C(void *, s32, s32, s32);
extern void *sub_0800355C(void);
extern s16 sub_08013C2C(s16);
extern void sub_080C31E0(void *, void *);
extern void sub_0805775C(void);
extern s16 D_080CFC98[];

/* Initialize a scripted effect: allocate its body and animation controller,
 * resolve a table index for its sprite attribute, then install the first script callback. */
void sub_080576A0(void *self)
{
    void *animCtrl;
    s32 tableIndex;
    u16 index16;
    u32 flags;
    sub_0800168C(self, 0, 0x2C, 0);
    if (*(u32 *)((u8 *)self + 0x3C) == 0) {
        sub_080C31E0(self, *(void **)((u8 *)self + 0x24));
        return;
    }
    animCtrl = sub_0800355C();
    if (animCtrl == 0) {
        sub_080C31E0(self, *(void **)((u8 *)self + 0x24));
        return;
    }
    *(void **)((u8 *)self + 0x38) = animCtrl;
    { s16 *table = D_080CFC98; tableIndex = sub_08013C2C(table[((u8 *)self)[0x4C] * 2]); index16 = (u16)tableIndex; }
    if ((tableIndex << 16) < 0) {
        sub_080C31E0(self, *(void **)((u8 *)self + 0x24));
        return;
    }
    {
        u32 attrib = (*(u16 *)animCtrl & 0x0FFF) | 0xD000;
        s32 idx = (s16)index16;
        s32 attrBits1 = (idx << 6) + 0x200;
        s32 attrBits2 = (idx + 8) << 12;
        attrib |= attrBits1 | attrBits2;
        *(u16 *)animCtrl = attrib;
        *(u16 *)animCtrl = attrib | D_02025FF0.field18C2;
    }
    *(void **)((u8 *)animCtrl + 0x24) = (void *)0x083C3B60;
    *(s32 *)((u8 *)animCtrl + 0x1C) = 0x8000000B;
    flags = (u16)(0x800U) | *(u16 *)((u8 *)self + 0x02);
    *(u16 *)((u8 *)self + 0x02) = (u16)flags;
    {
        void *fp = sub_0805775C;
        *(void **)((u8 *)self + 0x14) = fp;
        *(u16 *)((u8 *)self + 0x22) = 1;
        sub_080C31E0(self, fp);
    }
}
