void sub_080144D8(void *, void *);
void sub_080144FC(void *, void *);
void sub_080C31E0(void *, void *);
void unlinkAndFreeObject(void);
void freeMotionTracker(void);
void sub_08016678(void *);
void _call_via_r1(void *, void *);

/* Release any live objects held in the actor's work block, run its cleanup
 * callback, then switch to the state handler stored at work+0x24. */
void sub_08035D6C(void *actor) {
    u8 *work = *(u8 **)((u8 *)actor + 0x3C);
    u8 *effect = work + 0x48;
    if (*(s32 *)(work + 0x28) != 0) unlinkAndFreeObject();
    if (*(s32 *)(work + 0x48) != 0) unlinkAndFreeObject();
    if (*(s32 *)(effect + 4) != 0) unlinkAndFreeObject();
    if (*(s32 *)(work + 0x2C) != 0) freeMotionTracker();
    sub_08016678(actor);
    _call_via_r1(actor, *(void **)(work + 0x24));
}

/* Script command: prepare the actor's sprite, install a new command-handler
 * table at +0x14, advance one step and dispatch its handler, then restore the
 * step counter and reposition/highlight the sprite on screen. */
void sub_0803617C(void *actor) {
    void *sprite = *(void **)((u8 *)actor + 0x38);
    sub_080144D8(actor, sprite);
    *(void **)((u8 *)actor + 0x14) = (void *)0x0866DDF0;
    *(u16 *)((u8 *)actor + 0x22) = (u16)(*(u16 *)((u8 *)actor + 0x22) + 1);
    {
        u8 *stepSlot = (u8 *)((u32)(*(s16 *)((u8 *)actor + 0x22)) * 2 + (u32)actor);
        stepSlot[0x19] = (u8)(stepSlot[0x19] + 1);
        {
            s32 stepOffset = (*(s16 *)((u8 *)actor + 0x22)) * 2;
            u8 *commandSlot = (u8 *)actor + 0x18;
            u8 commandId = *(commandSlot + stepOffset);
            u8 **commandTable = *(u8 **)((u8 *)actor + 0x14);
            void *handler = commandTable[commandId];
            sub_080C31E0(actor, handler);
        }
    }
    *(u16 *)((u8 *)actor + 0x22) = (u16)(*(u16 *)((u8 *)actor + 0x22) - 1);
    sub_080144FC(actor, sprite);
}

/* Script command: prepare the actor's sprite, install a new command-handler
 * table at +0x14, advance one step and dispatch its handler, then restore the
 * step counter and reposition/highlight the sprite on screen. */
void sub_0803569C(void *actor) {
    void *sprite = *(void **)((u8 *)actor + 0x38);
    sub_080144D8(actor, sprite);
    *(void **)((u8 *)actor + 0x14) = (void *)0x0866DDC4;
    *(u16 *)((u8 *)actor + 0x22) = (u16)(*(u16 *)((u8 *)actor + 0x22) + 1);
    {
        u8 *stepSlot = (u8 *)((u32)(*(s16 *)((u8 *)actor + 0x22)) * 2 + (u32)actor);
        stepSlot[0x19] = (u8)(stepSlot[0x19] + 1);
        {
            s32 stepOffset = (*(s16 *)((u8 *)actor + 0x22)) * 2;
            u8 *commandSlot = (u8 *)actor + 0x18;
            u8 commandId = *(commandSlot + stepOffset);
            u8 **commandTable = *(u8 **)((u8 *)actor + 0x14);
            void *handler = commandTable[commandId];
            sub_080C31E0(actor, handler);
        }
    }
    *(u16 *)((u8 *)actor + 0x22) = (u16)(*(u16 *)((u8 *)actor + 0x22) - 1);
    sub_080144FC(actor, sprite);
}

/* Script command: prepare the actor's sprite, install a new command-handler
 * table at +0x14, advance one step and dispatch its handler, then restore the
 * step counter and reposition/highlight the sprite on screen. */
void sub_08036E60(void *actor) {
    void *sprite = *(void **)((u8 *)actor + 0x38);
    sub_080144D8(actor, sprite);
    *(void **)((u8 *)actor + 0x14) = (void *)0x0866DE34;
    *(u16 *)((u8 *)actor + 0x22) = (u16)(*(u16 *)((u8 *)actor + 0x22) + 1);
    {
        u8 *stepSlot = (u8 *)((u32)(*(s16 *)((u8 *)actor + 0x22)) * 2 + (u32)actor);
        stepSlot[0x19] = (u8)(stepSlot[0x19] + 1);
        {
            s32 stepOffset = (*(s16 *)((u8 *)actor + 0x22)) * 2;
            u8 *commandSlot = (u8 *)actor + 0x18;
            u8 commandId = *(commandSlot + stepOffset);
            u8 **commandTable = *(u8 **)((u8 *)actor + 0x14);
            void *handler = commandTable[commandId];
            sub_080C31E0(actor, handler);
        }
    }
    *(u16 *)((u8 *)actor + 0x22) = (u16)(*(u16 *)((u8 *)actor + 0x22) - 1);
    sub_080144FC(actor, sprite);
}
