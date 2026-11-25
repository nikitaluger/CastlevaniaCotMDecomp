/* Handle of the single active floating-damage-number effect (0 when none). */
extern s32 D_020213D8;

/* Release the floating damage-number effect slot once it has finished. */
void sub_0808D84C(void) {
    D_020213D8 = 0;
}
