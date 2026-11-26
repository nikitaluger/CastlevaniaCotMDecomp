void sub_080C31E0(void *obj, void *callback);

/* Global game state: the script/sequence phase word at +0x18C0. */
struct GameState {
    u8 pad[0x18C0];
    u16 phase;
};
extern struct GameState gMainWorkspace;

/* Cleanup callback installed by sub_08097AB0: clear the script phase word and
 * hand control back to the update callback saved in the object's component
 * at +0x3C+4. */
void sub_08097CD4(void *obj) {
    void *component = *(void **)((u8 *)obj + 0x3C);
    gMainWorkspace.phase = 0;
    sub_080C31E0(obj, *(void **)((u8 *)component + 4));
}
