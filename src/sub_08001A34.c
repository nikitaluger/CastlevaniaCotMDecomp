extern void sub_08001978(void *);

/* Current step's flag byte: actor+0x19 + step*2, with step = s16 at actor+0x22. */
inline u8 currentStepFlag(void *actor, void *base)
{
  return *((u8 *) (((s8 *) (((*((s16 *) (((s8 *) actor) + 0x22))) * 2) + base)) + 0x19));
}

/* Script command: when the current step's flag byte has none of its low two
 * bits set, run the "wait 16 frames" handler. */
void sub_08001A34(void *actor)
{
  if (!(currentStepFlag(actor, actor) & 3))
  {
    sub_08001978(actor);
  }
}
