void setObjectAnimation(void *scene, void *anim, s32 animId, s32 flags);

struct AnimFrame {
    u8 pad[2];
    u16 value;
};

/* Switches the actor to animation 0x18 (no flags), then copies a u16 value
 * from the current frame entry into the work state's field at +0x14. */
void sub_080A17B0(void *scene, void *anim, void *state) {
    s32 *frameTable;
    s32 idx;

    setObjectAnimation(scene, anim, 0x18, 0);
    frameTable = *(s32 **)((u8 *)anim + 8);
    idx = *(s16 *)((u8 *)anim + 0xE) + *(u8 *)((u8 *)anim + 1);
    *(u16 *)((u8 *)state + 0x14) = ((struct AnimFrame *)((u8 *)*frameTable + idx * 4 - 4))->value;
}
