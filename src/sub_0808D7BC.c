extern u32 D_02025FF0;
extern u8 D_080F3E7C[];       /* 5-byte parameter records, indexed by definition ID */
void *sub_080014D0(s32, s32);

/* Creates a scripted object (kind 0x205) from the definition table for the
 * given ID, copying its five parameter bytes and the caller's extra values
 * into the new object; returns 1 on success, 0 if the ID or allocation fails. */
s32 sub_0808D7BC(s32 arg0, s32 arg1, u32 arg2, u8 arg3) {
    u8 *obj;
    u32 *globalBase;
    s32 parent;
    u32 entryIndex;
    s32 fieldByte;
    s32 fieldByte2;
    if (arg2 <= 0x270F) {
        globalBase = (u32 *)&D_02025FF0;
        parent = *(s32 *)((u8 *)globalBase + 0x1878);
        obj = sub_080014D0(parent, 0x205);
        if (obj != NULL) {
            *(s32 *)(obj + 0x4C) = arg0;
            *(s32 *)(obj + 0x5C) = arg1;
            obj[0x6C] = arg3;
            *(s32 *)(obj + 0x7C) = arg2;
            fieldByte = D_080F3E7C[arg2 * 5];       *(obj + 0x74) = fieldByte;
            entryIndex = arg2 * 5;
            fieldByte = (D_080F3E7C + 4)[entryIndex];     *(obj + 0x8C) = fieldByte;
            fieldByte = (D_080F3E7C + 3)[entryIndex];     *(obj + 0x90) = fieldByte;
            fieldByte = (D_080F3E7C + 2)[entryIndex];     *(obj + 0x94) = fieldByte;
            fieldByte2 = (D_080F3E7C + 1)[entryIndex];    *(obj + 0x98) = fieldByte2;
            return 1;
        }
    }
    return 0;
}
