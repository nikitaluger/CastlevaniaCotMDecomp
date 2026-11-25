extern u32 D_02025FF0[];

void sub_08003740(void *, void *);
void sub_080C31E0(void *, void *);

/* Per-frame idle update: while the scene is active (workspace word at +0x10 is
 * non-zero) tick the actor's delay timer at state+0x20; otherwise hand control
 * to the update handler saved at entity+0x24. */
void sub_08089324(void *arg0)
{
    u8 *entity = arg0;
    void *state = *(void **)(entity + 0x6C);
    void *sprite = *(void **)(entity + 0x38);

    if (D_02025FF0[4] == 0)
        sub_080C31E0(entity, *(void **)(entity + 0x24));
    else
        sub_08003740((u8 *)state + 0x20, sprite);
}
