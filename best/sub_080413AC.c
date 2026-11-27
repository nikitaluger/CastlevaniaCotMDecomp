struct S_02025FF0 { u8 _0[0x18C2]; u16 field18C2; };
extern struct S_02025FF0 gMainWorkspace;
extern void allocWorkSlot(void *, s32, s32, s32);
extern void *allocSpriteObject(void);
extern s16 findKindIndex(s16);
extern void sub_080C31E0(void *, void *);
extern void sub_08041458(void);
extern s16 gPairedEffectKindTable[];

void sub_080413AC(void *self)
{
    void *animCtrl;
    s32 tableIndex;
    u16 index16;
    u32 flags;

    allocWorkSlot(self, 0, 0x14, 0);
    if (*(u32 *)((u8 *)self + 0x3C) == 0) {
        sub_080C31E0(self, *(void **)((u8 *)self + 0x24));
        return;
    }
    animCtrl = allocSpriteObject();
    if (animCtrl == 0) {
        sub_080C31E0(self, *(void **)((u8 *)self + 0x24));
        return;
    }
    *(void **)((u8 *)self + 0x38) = animCtrl;
    { s16 *table = gPairedEffectKindTable; tableIndex = findKindIndex(table[((u8 *)self)[0x74] * 2]); index16 = (u16)tableIndex; }
    if ((tableIndex << 16) < 0) {
        sub_080C31E0(self, *(void **)((u8 *)self + 0x24));
        return;
    }
    {
        s32 idx = (s16)index16;
        u32 attrib = *(u16 *)animCtrl;
        attrib |= (idx << 6) + 0x200;
        attrib |= (idx + 8) << 12;
        *(u16 *)animCtrl = attrib;
        *(u16 *)animCtrl = attrib | gMainWorkspace.field18C2;
    }
    *(void **)((u8 *)animCtrl + 0x24) = (void *)0x083B6974;
    *(s32 *)((u8 *)animCtrl + 0x1C) = 0x8000000B;
    flags = (u16)(0x800U) | *(u16 *)((u8 *)self + 0x02);
    *(u16 *)((u8 *)self + 0x02) = (u16)flags;
    {
        void *fp = sub_08041458;
        *(void **)((u8 *)self + 0x14) = fp;
        *(u16 *)((u8 *)self + 0x22) = 1;
        sub_080C31E0(self, fp);
    }
}
