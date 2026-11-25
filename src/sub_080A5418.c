void sub_080C31E0(void *, void *);
void sub_080A543C(void *);

/* Waiting state: once the transition-request flag at entity+0x6C is set,
 * switch the entity's handler to sub_080A543C, reset its command step to 1 and
 * run that handler immediately. */
void sub_080A5418(void *entity) {
    u8 *self = entity;
    if (*(u8 *)(self + 0x6C) != 0) {
        *(void **)(self + 0x14) = (void *)sub_080A543C;
        *(u16 *)(self + 0x22) = 1;
        sub_080C31E0(entity, (void *)sub_080A543C);
    }
}
