extern s32 sub_08011408(s32, void *, s32, s32, s32);
extern s32 getSpriteFacingSign(s32);
extern void sub_080C31E4(void *, void *, void *);
extern void *gMainObjTimerCallbacks;

void sub_0802E698(u8 *entity) {
    void *sprite = *(void **)(entity + 0x38);
    u8 *work = *(u8 **)(entity + 0x3C);
    u8 *actionData = work + 0x34;
    extern u8 gMainWorkspace[];
    s32 offset = 0x1728;
    s32 r7;
    r7 = *(s32 *)(gMainWorkspace + offset) - *(s32 *)(work + 8);
    sub_08011408((s32)sprite, actionData, 2, *(s32 *)(work + 0x48), 1);
    if (getSpriteFacingSign((s32)sprite) < 0) {
        s32 offset = *(s32 *)(work + 0x10) + (s32)0xFFFFF800;
        *(s32 *)(work + 0x10) = offset;
        *(s32 *)(work + 0x48) = -offset;
        if (offset < (s32)0xFFFC0000) {
            *(s32 *)(work + 0x10) = (s32)0xFFFC0000;
        }
        if (r7 > 0x100000) {
            *(u8 *)(entity + *(s16 *)(entity + 0x22) * 2 + 0x19) = 0;
            {
                void **scriptTable = &gMainObjTimerCallbacks;
                sub_080C31E4(entity + 0x18, entity + 0x22, *scriptTable);
            }
        }
    } else {
        s32 offset = *(s32 *)(work + 0x10) + 0x800;
        *(s32 *)(work + 0x10) = offset;
        if (offset > 0x40000) {
            *(s32 *)(work + 0x10) = 0x40000;
        }
        *(s32 *)(work + 0x48) = *(s32 *)(work + 0x10);
        if (r7 < (s32)0xFFF00000) {
            *(u8 *)(entity + *(s16 *)(entity + 0x22) * 2 + 0x19) = 0;
            {
                void **scriptTable = &gMainObjTimerCallbacks;
                sub_080C31E4(entity + 0x18, entity + 0x22, *scriptTable);
            }
        }
    }
}
