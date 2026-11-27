void startEffectTimer(void *, s32, s32);

struct S_02025FF0 { u8 _0x000[0x1804]; u32 v; };
extern struct S_02025FF0 gMainWorkspace;

/* Set an entity's form from the 0x14-byte table at 0x080DEA88: record the
 * form index, install its graphics pointer, load the sprite data, and
 * remember the current form in the global state. */
void sub_0806A7C4(void *obj, void *sprite, s32 form)
{
    u32 *entry;
    *(u32 *)((u8 *)sprite + 0x1C) = form;
    entry = (u32 *)((u8 *)0x080DEA88 + form * 0x14);
    *(u32 *)((u8 *)obj + 0x24) = entry[3];
    startEffectTimer((u8 *)sprite + 0x28, 0, entry[4]);
    gMainWorkspace.v = form;
}
