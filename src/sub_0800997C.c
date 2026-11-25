void sub_080C31E8(void *, void *, s32, s32);

struct S_03000830 { u8 pad[8]; u16 field; };
extern struct S_03000830 D_03000830;

/* Count the shared frame-delay counter down by one per frame; when it reaches
 * zero, clear the actor's wait flag at +4, clear the current step's flag byte
 * and advance the script with step-table call 4. */
void sub_0800997C(void *actor) {
    u8 *self = (u8 *)actor;
    struct S_03000830 *g = (struct S_03000830 *)0x03000830;
    s32 framesLeft = g->field;
    framesLeft = framesLeft - 1;
    g->field = (u16)framesLeft;
    if ((u16)framesLeft != 0) return;
    *(s32 *)(self + 4) = 0;
    {
        s16 step = *(s16 *)(self + 0x22);
        *(u8 *)(self + step * 2 + 0x19) = 0;
    }
    {
        s32 *stepTable = (s32 *)0x08671BD0;
        sub_080C31E8(self + 0x18, self + 0x22, 4, *stepTable);
    }
}
