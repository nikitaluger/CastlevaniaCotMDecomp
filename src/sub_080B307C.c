/* Destroy one child object: the harness calls the callback stored at +0x24. */
extern void sub_080C31E0(void *, s32);
extern void sub_08011528(s32, void *);
extern void sub_080C31E8(void *, void *, s32, s32);
extern void setObjectAnimation(s32, void *, s32, s32);
extern void startScriptOnce(s32, s32, s32);

/* Shared child-object list: gMainWorkspace+0x1870 points at the owner object; its
 * +0x30 is the first live child. Each child starts with an s16 type id, keeps a
 * destroy argument at +0x24 and links to the next child at +0x2C. */
struct ObjectRoot { u8 _0[0x1870]; u32 owner; };
extern struct ObjectRoot gMainWorkspace;

/* Kill every live child of type 0x1BA (0xDD << 1) in the shared list. */
void sub_080B307C(void) {
    void *owner = (void *)gMainWorkspace.owner;
    void *child = *(void **)((u8 *)owner + 0x30);
    if (child != NULL) {
        s32 typeId = 0xDD << 1;
        do {
            if (*(s16 *)child == typeId) {
                sub_080C31E0(child, *(s32 *)((u8 *)child + 0x24));
            }
            child = *(void **)((u8 *)child + 0x2C);
        } while (child != NULL);
    }
}

/* Run one step of the entity's command script; the 0x78 command clears the
 * previous-command byte and restarts the handler table at command 3. */
void sub_080B4504(void *arg0) {
    u8 *obj = (u8 *)arg0;
    sub_08011528(*(s32 *)(obj + 0x38), (u8 *)*(void **)(obj + 0x3C) + 0x34);
    if (*(u8 *)(obj + *(s16 *)(obj + 0x22) * 2 + 0x19) == 0x78) {
        s32 *lit;
        *(u8 *)(obj + *(s16 *)(obj + 0x22) * 2 + 0x17) = 0;
        lit = (s32 *)0x08671BD8;
        sub_080C31E8(obj + 0x18, obj + 0x22, 3, *lit);
    }
}

/* Animation script step: play animation 0x68 on the actor's sprite; when the
 * current step's action byte is 6, set the work byte at +0x69, clear the
 * linked sprite flag and the step's paired byte at +0x17, then advance the
 * script through the table at 0x08671BD8 with command 3. */
void sub_080B489C(void *arg0)
{
  u8 *self = (u8 *) arg0;
  s32 sprite = *((s32 *) (self + 0x38));
  u8 *work = *((u8 **) (self + 0x3C));
  u8 *animState = work + 0x34;
  u8 *spriteData = work + 0x48;

  setObjectAnimation(sprite, animState, 0x68, 0);
  if ((*((u8 *) ((self + ((*((s16 *) (self + 0x22))) * 2)) + 0x19))) == 6)
  {
    u8 *workFlag = work + 0x69;
    s32 zero = 0;
    s32 *scriptTable;
    *workFlag = 1;
    *(spriteData + 0x1F) = (u8)zero;
    *((u8 *) ((self + ((*((s16 *) (self + 0x22))) * 2)) + 0x17)) = (u8)zero;
    scriptTable = (s32 *) 0x08671BD8;
    sub_080C31E8(self + 0x18, self + 0x22, 3, *scriptTable);
  }
}

/* When the object's current script step reaches 0x1E, run startScriptOnce on its
 * id, clear the step's paired byte and advance the script through table
 * 0x08671BD8 with command 2. */
void sub_080B12C0(void *arg0) {
    u8 *obj = (u8 *)arg0;
    s32 id4C = *(s32 *)(obj + 0x4C);
    if (*(u8 *)(obj + *(s16 *)(obj + 0x22) * 2 + 0x19) == 0x1E) {
        s32 *table;
        startScriptOnce(id4C, 1, 1);
        *(u8 *)(obj + *(s16 *)(obj + 0x22) * 2 + 0x17) = 0;
        table = (s32 *)0x08671BD8;
        sub_080C31E8(obj + 0x18, obj + 0x22, 2, *table);
    }
}
