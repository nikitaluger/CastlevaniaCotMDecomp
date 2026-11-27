void *spawnBudgetedEffect(u32, u32);

struct S_02025FF0 { u8 _0x000[0x1870]; u32 v; };
extern struct S_02025FF0 gMainWorkspace;

/* Spawn a type-0x182 object under the global actor list, clear its +0x6C
 * parameter byte and return it (NULL when no slot is available). */
void *sub_080A0210(void) {
    void *obj = spawnBudgetedEffect(gMainWorkspace.v, 0x182);
    if (obj == NULL) {
        return NULL;
    }
    ((u8 *)obj)[0x6C] = 0;
    return obj;
}
