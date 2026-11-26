struct Obj84 { u8 _0[0x7C]; u16 spriteId; u8 _7E[0x6]; u16 kind; };

extern u8 gGameStatus[];
extern u8 gMainWorkspace[];

void *sub_0806D2A0(void *a0, s32 a1, s32 a2, s32 a3);
void sub_08086E28(void);

/* Spawns a companion object according to the global game mode: modes 0xA2 and
 * 0xA4 spawn it with the graphic index held in global state and tag it as kind
 * 1 or 2, while mode 0xA6 spawns a different graphic with no tag. Each spawn is
 * also recorded in the global spawn table by sub_08086E28. */
void sub_08084AD0(void *spawner)
{
    u8 *gameState = gGameStatus;
    struct Obj84 *spawned;

    switch (gMainWorkspace[0x14ED]) {
    case 0xA2:
        spawned = sub_0806D2A0(spawner, 0x25, 0x0A, 0x12);
        sub_08086E28();
        if (spawned != NULL) {
            spawned->spriteId = gameState[0x2D8];
            spawned->kind = 1;
        }
        break;
    case 0xA4:
        spawned = sub_0806D2A0(spawner, 0x25, 0x0A, 0x12);
        if (spawned != NULL) {
            spawned->spriteId = gameState[0x2D8];
            spawned->kind = 2;
        }
        break;
    case 0xA6:
        spawned = sub_0806D2A0(spawner, 0x34, 0x0A, 0x12);
        if (spawned != NULL) {
            spawned->spriteId = 0;
        }
        sub_08086E28();
        break;
    default:
        break;
    }
}
