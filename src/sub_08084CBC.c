extern u8 gMainWorkspace[]; /* memory base; byte 0x14ED holds the current room id */
extern void *spawnEntity(s32, s32, s32, s32); /* spawn object of a given type */
extern void sub_08086E28(void); /* notify the room engine of the spawn */

/* Room 0x34 handler: scale the entity's +0x90 field by four, spawn object type
 * 0x34, clear the spawned object's +0x7C field, notify the room engine, then
 * copy the scaled field into +0x8C. */
void sub_08084CBC(s32 arg0, void *arg1) {
    u8 *room = (u8 *)arg1;
    if (gMainWorkspace[0x14ED] == 0x34) {
        *(s32 *)(room + 0x90) = *(s32 *)(room + 0x90) << 2;
        {
            void *spawn = spawnEntity(arg0, 0x34, 0x0A, 0x12);
            if (spawn != NULL) {
                *(u16 *)((u8 *)spawn + 0x7C) = 0;
            }
        }
        sub_08086E28();
    }
    *(s32 *)(room + 0x8C) = *(s32 *)(room + 0x90);
}
