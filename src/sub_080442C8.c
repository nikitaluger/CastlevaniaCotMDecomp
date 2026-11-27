extern void advanceMotion(void *motion, s32 gravity);

/* Advance the motion held in the entity's +0x3C slot by one step with no
 * gravity (the object does not fall this frame). */
void sub_080442C8(void *entity) {
    advanceMotion(*(void **)((u8 *)entity + 0x3C), 0);
}
