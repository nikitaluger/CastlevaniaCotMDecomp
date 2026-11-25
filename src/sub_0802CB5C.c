extern u16 D_080CEA28[];
extern u16 D_080CEA30[];
extern u16 D_080CEA38[];

/*
 * Pick a sprite-frame parameter table from the object's animation index and
 * write its four u16 values into the actor's sprite attributes, clearing the
 * relevant animation flag bits along the way.
 */
void sub_0802CB5C(void *self, void *actor)
{
    u8 *selfBytes = (u8 *)self;
    u8 *actorBytes = (u8 *)actor;
    u16 *frameTable = D_080CEA28;
    u32 animIndex;
    u32 relIndex = *(u16 *)(selfBytes + 0x28) - 0x1E;
    if (relIndex <= 4) {
        switch (relIndex) {
        case 0:
        case 1: {
            u8 *animState = *(u8 **)(actorBytes + 0x28);
            u8 flags = *(u8 *)(animState + 1) & 0xFA;
            *(u8 *)(animState + 1) = flags;
            break;
        }
        case 2:
            frameTable = D_080CEA28;
            break;
        case 3:
            frameTable = D_080CEA30;
            break;
        case 4:
            frameTable = D_080CEA38;
            break;
        }
    }
    animIndex = *(u16 *)(selfBytes + 0x28);
    if ((u16)(animIndex - 0x2C) <= 8) frameTable = D_080CEA30;
    if ((u16)(animIndex - 0x38) <= 9) frameTable = D_080CEA38;
    if ((u16)(animIndex - 0x45) <= 7) {
        u8 *animState = *(u8 **)(actorBytes + 0x28);
        u8 flags = *(u8 *)(animState + 1) & 0xFE;
        *(u8 *)(animState + 1) = flags;
    }
    {
        void * volatile *ppAnim = (void * volatile *)(actorBytes + 0x28);
        *(u16 *)((u8 *)*ppAnim + 6) = frameTable[0];
        *(u16 *)((u8 *)*ppAnim + 8) = frameTable[1];
        *(u16 *)((u8 *)*ppAnim + 10) = frameTable[2];
        *(u16 *)((u8 *)*ppAnim + 12) = frameTable[3];
    }
}
