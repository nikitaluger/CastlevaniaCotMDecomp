s32 sub_080C31E0(void *, s32);   /* run an object's handler */

/* Detach the two auxiliary objects held in the actor's sub-object at +0x48:
 * run each object's handler and clear its reference. */
void sub_080BB05C(void *entity) {
    void *childA;
    void *childB;
    u8 *aux;

    aux = (u8 *)(*(s32 *)((u8 *)entity + 0x3C) + 0x48);
    childA = *(void **)(aux + 0x2C);
    if (childA != NULL) {
        sub_080C31E0(childA, *(s32 *)((u8 *)childA + 0x24));
        *(void **)(aux + 0x2C) = NULL;
    }
    childB = *(void **)(aux + 0x30);
    if (childB != NULL) {
        sub_080C31E0(childB, *(s32 *)((u8 *)childB + 0x24));
        *(void **)(aux + 0x30) = NULL;
    }
}
