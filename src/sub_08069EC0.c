s32 sub_08005E80(s32);
s32 setEntityForm(void *, void *, s32);
s32 sub_0808BBAC(s32, s32, s32);
void sub_080C31E0(void *, s32);
void sub_080C31E4(void *, void *, s32);
extern u8 gMainWorkspace[];
extern void *gScriptStepCallbackTable;

/*
 * Sets up the entity's effect (id 0x57), copies its position, applies the
 * palette, plays a sound for certain global states, then advances the entity's
 * effect callback index and invokes the corresponding callback.
 */
void sub_08069EC0(void *arg0) {
  void *subObj = *((void **) (((char *) arg0) + 0x6C));
  void *obj = ((char *) subObj) + 4;
  void *ctx = *((void **) (((char *) arg0) + 0x38));
  setEntityForm(ctx, obj, 0x57);
  *((s32 *) (((char *) subObj) + 0x108)) = *((s32 *) (((char *) obj) + 4));
  if (*((s32 *) (((char *) obj) + 0x40)) == 0) {
    *((s32 *) (((char *) subObj) + 0x110)) = *((s32 *) (((char *) obj) + 4));
  } else {
    s32 coordOffset = 0xC0;
    coordOffset <<= 15;
    *((s32 *) (((char *) subObj) + 0x110)) = *((s32 *) (((char *) obj) + 4)) + coordOffset - *((s32 *) (((char *) ctx) + 0x18));
  }
  *((volatile u16 *) 0x05000000) = 0x4210;
  sub_0808BBAC(1, 2, 2);
  {
    int state = gMainWorkspace[0x14EE];
    switch (state) {
    case 0x91: case 0x92: case 0x93: case 0x94: case 0x95:
    case 0x96: case 0x97: case 0x98: case 0x99: case 0x9A:
      sub_08005E80(0x15D);
      break;
    }
  }
  *((u8 *) (((char *) arg0) + (*((s16 *) (((char *) arg0) + 0x22))) * 2 + 0x19)) = 0;
  {
    void **effectIds = &gScriptStepCallbackTable;
    u8 *paramPtr = ((char *) arg0) + 0x18;
    sub_080C31E4(paramPtr, ((char *) arg0) + 0x22, (s32) *effectIds);
    *((u8 *) (((char *) arg0) + (*((s16 *) (((char *) arg0) + 0x22))) * 2 + 0x19)) += 1;
    {
      s16 index = *((s16 *) (((char *) arg0) + 0x22));
      u8 paramIndex;
      void **callbackTable;
      paramPtr = (u8 *) (((char *) paramPtr) + index * 2);
      paramIndex = *paramPtr;
      callbackTable = *((void ***) (((char *) arg0) + 0x14));
      sub_080C31E0(arg0, (s32) callbackTable[paramIndex]);
    }
  }
}
