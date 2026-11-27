extern s8 spawnSceneObjectTableEntries(void *p);

void sub_08098644(void *arg0, s8 arg1, s32 arg2, s32 arg3) {
    ((u8 *)arg0)[0x1C] = (u8)arg1;
    *(s32 *)arg0 = arg2;
    *(s32 *)((u8 *)arg0 + 0x0C) = arg3;
    ((u8 *)arg0)[0x35] = 0xFF;
}

void sub_08098684(void *arg0, u8 arg1, s8 arg2) {
    u8 r1 = (u8)(arg1 << 24 >> 24);
    u8 *p = (u8 *)arg0 + 0x24;
    *p = r1; p++;
    *p = 0; p++;
    *p = 0; p++;
    *p = (u8)arg2;
    *(s32 *)((u8 *)arg0 + 0x20) = *(s32 *)(*(s32 *)arg0 + r1 * 4);
    ((u8 *)arg0)[0x29] = 0;
    ((u8 *)arg0)[0x28] = (u8)spawnSceneObjectTableEntries(arg0);
}

s32 sub_08098754(void *arg0) {
    if (((u8 *)arg0)[0x27] == 2) return 1;
    return 0;
}

s32 sub_08097234(void) {
    extern s16 D_020279E8;
    if (D_020279E8 != 0x10) return -1;
    return 0;
}
