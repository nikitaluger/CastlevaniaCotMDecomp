extern s32 scaleByRandom(s32 a);
extern void sub_08007E24(s32 a);
extern void sub_0808BB54(void);
extern void sub_080AAB74(u8 a);
extern void sub_080C31E4(void *a, void *b, void *c);
extern u8 gMainWorkspace[];
extern u8 gMainObjTimerCallbacks[];

/* Per-frame update for a two-part entity: mirror two input flags onto its child
 * objects, count down a random timer that toggles the active phase (firing a
 * phase effect via sub_080AAB74), and when both flags are set fire the shared
 * effect and reset the acting child's flag. */
void sub_080A59C4(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *state = *(u8 **)(self + 0x3C) + 0x48;
    u8 *flagAPtr = self + 0x4C;
    u8 *p = self;
    s32 countdown;
    if (*(u8 *)flagAPtr != 0) { *(u8 *)(*(u8 **)(state + 0x08) + 0x7C) = 1; }
    p = p + 0x50;
    { u8 flagB = *p; u8 *flagBPtr = p;
      if (flagB != 0) { *(u8 *)(*(u8 **)(state + 0x04) + 0x7C) = 1; }
      countdown = *(u16 *)(state + 0x02);
      if (countdown == 0) { *(u16 *)(state + 0x02) = scaleByRandom(0x3C) + 0xB4; }
      else { countdown = countdown - 1; *(u16 *)(state + 0x02) = countdown;
        if ((countdown << 16) != 0) goto skip_tail;
        if (*(vu8 *)state == 0) { if (*(u8 *)flagAPtr == 0) sub_080AAB74(*(vu8 *)state); else goto else_if; }
        else {
        else_if:
          if (*(vu8 *)state == 1) { if (*(u8 *)flagBPtr == 0) sub_080AAB74(*(vu8 *)state); } }
        *(u8 *)state = (*(vu8 *)state + 1) & 1; }
      if (*(u8 *)(self + 0x4C) != 0 && *(u8 *)flagBPtr != 0) {
        u8 *world;
        sub_08007E24(0xB7);
        world = gMainWorkspace;
        { s32 zero = 0;
          *(u16 *)(world + 0x3C) = 2;
          sub_0808BB54();
          *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = zero;
          { u8 *effectTable = gMainObjTimerCallbacks;
            sub_080C31E4(self + 0x18, self + 0x22, (void *)*(u32 *)effectTable); } }
      }
      skip_tail: ; }
}
