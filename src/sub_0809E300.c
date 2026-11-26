void setObjectAnimation(void *scene, void *anim, s32 animId, s32 flags);

struct AnimFrame {
    u8 pad[2];
    u16 value;
};

/* Switches the actor to animation 0xC with flag 1, then copies a u16 value
 * from the current frame entry into the work state's field at +0x3E. */
void sub_0809E300(void *scene, void *anim, void *state) {
    s32 *frameTable;
    s32 idx;

    setObjectAnimation(scene, anim, 0xC, 1);
    frameTable = *(s32 **)((u8 *)anim + 8);
    idx = *(s16 *)((u8 *)anim + 0xE) + *(u8 *)((u8 *)anim + 1);
    *(u16 *)((u8 *)state + 0x3E) = ((struct AnimFrame *)((u8 *)*frameTable + idx * 4 - 4))->value;
}
