void sub_0808D7BC(s32, s32, s32, s32);

/* Move the actor's counter at +0x18 toward the entity's target at +0x8C by at
 * most the limit stored at entity+0x28->0x5C, then spawn a kind-2 effect at
 * the actor's position carrying the applied step. */
void sub_080A8B44(void *self, void *actor) {
    s32 step = *(s32 *)((u8 *)self + 0x8C) - *(s32 *)((u8 *)actor + 0x18);
    s32 limit = *(s32 *)(*(void **)((u8 *)self + 0x28) + 0x5C);
    if (step > limit) step = limit;
    *(s32 *)((u8 *)actor + 0x18) = *(s32 *)((u8 *)actor + 0x18) + step;
    sub_0808D7BC(*(s32 *)((u8 *)actor + 8), *(s32 *)((u8 *)actor + 0xC), step, 2);
}
