/* The actor's position lives at +0x4C (x) and +0x5C (y); the motion block
 * pointed to by +0x3C mirrors it at +8 and +0xC. */
struct Motion {
    u8 pad[8];
    s32 x;
    s32 y;
};

/* Copy the actor's position into its motion block. */
void sub_080A9EBC(void *actor) {
    struct Motion *motion;

    motion = *(struct Motion **)((u8 *)actor + 0x3C);
    motion->x = *(s32 *)((u8 *)actor + 0x4C);
    motion->y = *(s32 *)((u8 *)actor + 0x5C);
}
