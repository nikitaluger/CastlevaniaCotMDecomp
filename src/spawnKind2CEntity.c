extern void sub_080C31E0(void *, void *);
extern void *sub_0806D24C(void *, s32, s32, s32);
extern void sub_08005E80(void);
extern s32 sub_080C36E4(s32, s32);

extern u8 gMainWorkspace[];
extern u8 gGameStatus[];

/* Release the entity's global slot and run its handler number 7. */
void sub_0806E154(void *entity) {
    void **handlers = *(void ***)((u8*)entity + 0x6C);
    u32 idx = *(u32*)((u8*)entity + 0xAC);
    *(u32*)(gMainWorkspace + 0x1780 + idx * 4) = 0;
    sub_080C31E0(entity, handlers[7]);
}

/* Spawn a kind-0x2C entity from definition `def`: its low 16 bits index the
 * spawn table at 0x080E01A0 (entry[0] = first slot, entry[1] = slot count).
 * The full definition word and the two coordinates are kept on the entity. */
void *spawnKind2CEntity(void *entity, u32 def, s32 x, s32 y) {
    u32 temp = (def & 0xFFFF) << 5;
    u32 *entry = (u32*)(0x080E01A0 + temp);
    void *spawned = sub_0806D24C(entity, 0x2C, entry[0], entry[1]);
    if (spawned == NULL) {
        return NULL;
    }
    *(u32*)((u8*)spawned + 0x7C) = def;
    *(s32*)((u8*)spawned + 0x8C) = x;
    *(s32*)((u8*)spawned + 0x9C) = y;
    return spawned;
}

/* Play the alternating footstep sound for the current walk phase. */
void sub_0806DE38(void) {
    s32 v = *(s32*)(gGameStatus + 0x90);
    s32 idx = v - ((v + ((u32)v >> 31)) >> 1) * 2;
    if (*(u16*)(0x080E0ADA + idx * 2) != 0) {
        sub_08005E80();
    }
}

/* Play the footstep sound for the current walk phase modulo 9. */
void sub_0806DE0C(void) {
    s32 v = *(s32*)(gGameStatus + 0x90);
    s32 idx = sub_080C36E4(v, 9);
    if (*(u16*)(0x080E0AC8 + idx * 2) != 0) {
        sub_08005E80();
    }
}
