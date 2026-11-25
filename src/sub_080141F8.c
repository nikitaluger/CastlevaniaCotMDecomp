extern s32 sub_08013C2C(s32);
extern void sub_080C31E0(void *, s32);
struct KindRow_141F8 { u8 pad[2]; s16 val; u8 rest[0x10]; };
extern struct KindRow_141F8 D_080CB2B8[];
struct GameState_141F8 { u8 _0[0x18C2]; u16 w; };
extern struct GameState_141F8 D_02025FF0;

/* Initialize a work struct for the given kind: copy the kind's base value
 * and table position, look up its attribute index, and write the resulting
 * sprite attribute; bail through the state handler if the kind is unknown. */
void sub_080141F8(void *self, s16 *attrOut, void *work, void *source, s32 kind) {
    u16 kind16 = (u16)kind;
    u32 zero;
    s16 idx;
    s16 *posTable;
    s32 kindIndex;
    s16 idxCopy;
    s32 attr;
    s32 offset;

    zero = 0;
    *(u16 *)((u8 *)work + 0x1C) = kind16;
    idx = (s16)kind16;
    *(s32 *)((u8 *)work + 0x18) = D_080CB2B8[idx].val;
    posTable = *(s16 **)((u8 *)source + 4);
    *(s32 *)((u8 *)work + 0x08) = (s32)posTable[0] << 16;
    *(s32 *)((u8 *)work + 0x0C) = (s32)posTable[1] << 16;
    *(s32 *)((u8 *)work + 0x10) = zero;
    *(s32 *)((u8 *)work + 0x14) = zero;
    *(s32 *)((u8 *)work + 0x2C) = zero;
    *(s16 *)((u8 *)work + 0x04) = zero;
    kindIndex = sub_08013C2C(*(s16 *)((u8 *)work + 0x1C));
    *(s16 *)((u8 *)work + 0x22) = kindIndex;
    if ((s32)(kindIndex << 16) < 0) {
        sub_080C31E0(self, *(s32 *)((u8 *)self + 0x24));
        return;
    }
    idxCopy = *(s16 *)((u8 *)work + 0x22);
    attr = (idxCopy << 6) + 0x200;
    offset = kindIndex + 8;
    offset <<= 12;
    attr = attr | offset;
    *attrOut = attr;
    *attrOut = attr | D_02025FF0.w;
}
