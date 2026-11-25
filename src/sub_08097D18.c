extern s32 sub_08013C2C(s16);
extern void sub_080C31E0(void *, void *);

/* Global state: sprite flags word ORed into new objects. */
struct GameGlobals { u8 _0[0x18C2]; u16 objFlags; };
extern struct GameGlobals D_02025FF0;

/* 20-byte per-object definition record; +2 is a per-object type/param word. */
struct ObjDefRecord { u8 _0[2]; s16 kind; u8 _rest[16]; };
extern struct ObjDefRecord D_080CB2B8[];

/* Initialize a spawned object from its definition: set its id and per-id
 * record, copy its spawn coordinates (definition +4 points at an s16 x/y
 * pair) as 16.16, zero its motion/timer fields, register its active slot and
 * hand the global sprite flags back to the caller; if no slot is free,
 * switch the owner's script state instead. */
void sub_08097D18(void *arg0, u16 *outFlags, u8 *obj, void *def, s32 defIndex) {
    u16 id;
    s32 zero;
    struct ObjDefRecord *defs;
    s16 *coords;
    s32 slot;

    id = (u16)defIndex;
    zero = 0;
    *(u16 *)(obj + 0x1C) = id;
    defs = D_080CB2B8;
    *(s32 *)(obj + 0x18) = defs[(s16)id].kind;
    coords = *(s16 **)((u8 *)def + 4);
    *(s32 *)(obj + 8) = (s32)coords[0] << 16;
    *(s32 *)(obj + 0xC) = (s32)coords[1] << 16;
    *(s32 *)(obj + 0x10) = zero;
    *(s32 *)(obj + 0x14) = zero;
    *(s32 *)(obj + 0x2C) = zero;
    *(u16 *)(obj + 4) = zero;
    slot = sub_08013C2C(*(s16 *)(obj + 0x1C));
    *(u16 *)(obj + 0x22) = slot;
    if ((s32)((u16)slot << 16) < 0) {
        sub_080C31E0(arg0, *(void **)((u8 *)arg0 + 0x24));
        return;
    }
    *outFlags = D_02025FF0.objFlags;
}
