extern void sub_0801165C(void *motion, s32 gravity);

/* Advance the motion held in the entity's +0x3C slot by one step with no
 * gravity (the object does not fall this frame). */
void sub_080A96BC(void *entity) {
    sub_0801165C(*(void **)((u8 *)entity + 0x3C), 0);
}
