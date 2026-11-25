s32 sub_08013B5C(void *, void *);
void sub_08013C8C(void *, s32);
s32 sub_080141AC(void *, void *);
void sub_080C31E0(void *, void *);

/* Run one step of an actor's bytecode script using this area's command table,
 * then refresh its sprite position. If a display/state override claims the
 * frame, switch the actor to its default handler instead. */
void sub_080373B0(void *actor)
{
    u8 *actorBytes = actor;
    s32 sprite = *(s32 *)(actorBytes + 0x38);
    s32 work = *(s32 *)(actorBytes + 0x3C);

    if (sub_080141AC(sprite, work) == 1) {
        sub_080C31E0(actor, *(void **)(actorBytes + 0x24));
        return;
    }
    if (sub_08013B5C(sprite, work) == 0) {
        int scriptOffset = 0x18;
        s32 scriptIndex;
        s32 indexOffset;

        *(u32 *)(actorBytes + 0x14) = 0x0866DE40;
        *(u16 *)(actorBytes + 0x22) += 1;
        ((u8 *)(actorBytes + (*(s16 *)(actorBytes + 0x22)) * 2))[0x19]++;
        scriptIndex = *(s16 *)(actorBytes + 0x22);
        indexOffset = scriptIndex << 1;
        sub_080C31E0(actor, *(void **)(*(u32 *)(actorBytes + 0x14) + *(u8 *)(actorBytes + scriptOffset + indexOffset) * 4));
        *(u16 *)(actorBytes + 0x22) -= 1;
    }
    sub_08013C8C(actor, sprite);
}
