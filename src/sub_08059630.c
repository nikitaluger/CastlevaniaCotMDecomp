extern void sub_08013C5C(void *, s32);
extern s32 sub_080141AC(s32, void *);
extern s32 sub_08013558(s32, void *, void *);
extern void sub_08013978(void *, void *);
extern void sub_080142C0(void *, void *);
extern void sub_08013AC4(void *);
extern s32 sub_08013B5C(s32, void *);
extern void sub_080113A8(s32, void *);
extern void sub_08011EE8(void *, s32, s32);
extern void sub_08013C8C(void *, s32);
extern void sub_08059AD8(s32, void *);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E8(void *, void *, s32, void *);
extern void *D_08671BDC;
extern u8 D_02021E90[];
extern struct { u8 _0[0x18A8]; u8 f18A8; } D_02025FF0;

/* Entity script update: refresh contact/combat state, run one script command
 * from the command table, then apply the camera-relative Y correction. */
void sub_08059630(u8 *self) {
    s32 parent = *(s32 *)(self + 0x38);
    u8 *comp = *(u8 **)(self + 0x3C);
    u8 *body = comp + 0x34;
    u8 *fx = comp + 0x48;
    u32 coordBase;
    u32 coordOff;
    s32 worldY;
    u32 coordVal;

    if (sub_080141AC(parent, comp) == 1) return;

    sub_08013C5C(self, parent);
    if (sub_08013558(parent, comp, *(void **)(comp + 0x28)) != 0) {
        sub_08013978(self, *(void **)(comp + 0x28));
    }
    sub_080142C0(self, *(void **)(comp + 0x28));
    if (*(u16 *)comp & 1) {
        u8 *script = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
        if (*(u8 *)(script + 0x1A) != 3) {
            sub_08013AC4(self);
            {
                u8 *scriptPtr = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
                *(u8 *)(scriptPtr + 0x1B) = 0;
                { void **sound = &D_08671BDC;
                  sub_080C31E8(self + 0x18, self + 0x22, 3, *sound); }
            }
        }
    }
    if (sub_08013B5C(parent, comp) != 0) goto cdc;
    *(u32 *)(self + 0x14) = 0x0866E854;
    *(u16 *)(self + 0x22) = (u16)(*(u16 *)(self + 0x22) + 1);
    {
        u8 *scriptPtr = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
        scriptPtr[0x19] = (u8)(scriptPtr[0x19] + 1);
    }
    {
        s32 scriptIdx = (*(s16 *)(self + 0x22)) * 2;
        u8 *scriptBase = self + 0x18;
        u8 cmd = *(scriptBase + scriptIdx);
        void **table = *(void **)(self + 0x14);
        void *func = table[cmd];
        sub_080C31E0(self, func);
    }
    *(u16 *)(self + 0x22) = (u16)(*(u16 *)(self + 0x22) - 1);
    if ((*(u16 *)(self + 2) & 0x8000) != 0) goto done;
    sub_080113A8(parent, body);
    sub_08011EE8(comp, *(s32 *)(fx + 8), 0);
cdc:
    sub_08059AD8(parent, comp);
    sub_08013C8C(self, parent);
    worldY = *(s32 *)(comp + 0xC) + *(s32 *)(fx + 0xC);
    coordBase = (u32)D_02021E90;
    coordOff = 0x127C;
    coordVal = *(u32 *)(coordBase + coordOff + ((D_02025FF0.f18A8 + 1) << 6));
    coordVal = (coordVal + 0xFFFF8000) & 0xFFFF0000;
    *(s32 *)((u8 *)parent + 0x18) = worldY - coordVal;
done:
    ;
}
