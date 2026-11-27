struct S_02025FF0 { u8 _0[0x18C2]; u16 field18C2; };
extern struct S_02025FF0 gMainWorkspace;
extern void allocWorkSlot(void *, s32, s32, s32);
extern void *allocSpriteObject(void);
extern s16 findKindIndex(s16);
extern void sub_080C31E0(void *, void *);
extern s16 gPairedEffectKindTable[];

void sub_080413AC(void *self)
{
    void *animCtrl;
    s32 tableIndex;
    u16 index16;
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
    {
        s16 *table = gPairedEffectKindTable;
        tableIndex = findKindIndex(table[((u8 *)self)[0x74] * 2]);
        index16 = (u16)tableIndex;
    }
    if ((tableIndex << 16) < 0) {
        sub_080C31E0(self, *(void **)((u8 *)self + 0x24));
        return;
    }
    return;
}
