extern u8 D_020278D0[];

struct S_03000830 { u8 _[4]; u16 flags; u16 params; };

typedef void (*ScriptFunc2)(void *, void *);
typedef void (*ScriptFunc1)(void *);

/* Advance a fade/transition counter by two each tick, programming the effect
 * registers at 0x03000830. Once the counter reaches 16, clear them and step
 * the entity's script to its next callback. */
void sub_0800CF98(u8 *entity) {
    struct S_03000830 *fx = (struct S_03000830 *)0x03000830;
    u16 mask = 0x3F53;
    u8 *base;
    u8 *counter;
    s8 level;
    u8 maxLevel;
    u8 val;
    u8 *script;
    s32 *callback;
    u8 opcode;
    s32 next;

    fx->flags = mask;
    base = D_020278D0;
    counter = base + 0x67;
    level = *(s8 *)counter;
    maxLevel = 0x10;
    fx->params = level | ((maxLevel - level) << 8);
    val = *counter;
    if (*(s8 *)counter == 0x10) {
        fx->flags = 0;
        *(u8 *)(entity + *(s16 *)(entity + 0x22) * 2 + 0x19) = 0;
        callback = (s32 *)0x08671BB0;
        script = entity + 0x18;
        ((ScriptFunc2)*callback)(script, entity + 0x22);
        *(u8 *)(entity + *(s16 *)(entity + 0x22) * 2 + 0x19) += 1;
        script = script + *(s16 *)(entity + 0x22) * 2;
        opcode = *script;
        ((ScriptFunc1)(*(u32 *)(opcode * 4 + *(u32 *)(entity + 0x14))))(entity);
    } else {
        next = val + 2;
        *counter = (u8)next;
        if ((s8)next > 0x10)
            *counter = maxLevel;
    }
}
