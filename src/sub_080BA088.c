void sub_080BB940(s32, s32);
void sub_080BB898(void *);
void sub_080BE644(void *);
void sub_080BE7D4(void);
void sub_080BE87C(void);
void sub_080BE8D0(s32, s32);
void sub_080C31E4(void *, void *, s32);

/* Fade-in step: step the attached mover, ramp the fade group's level from 0 to
 * 1.0 (0x10000) by 0x300 per frame and apply it to the group's fade target;
 * when the ramp completes, enable the group's five sprites, run the fade
 * completion hooks and advance the script. */
void sub_080BA088(void *entity)
{
  s32 work;
  s32 level;
  void *fade;
  s32 *scriptTable;

  work = *((s32 *) (((s8 *) entity) + 0x3C));
  fade = work + 0x48;
  sub_080BB940(work, *((s32 *) (((s8 *) entity) + 0x4C)));
  level = (*((s32 *) (((s8 *) fade) + 0x40))) + 0x300;
  *((s32 *) (((s8 *) fade) + 0x40)) = level;
  if (level > 0x10000)
  {
    *((s32 *) (((s8 *) fade) + 0x40)) = 0x10000;
  }
  sub_080BE8D0(*((s32 *) (((s8 *) fade) + 0x34)), *((s32 *) (((s8 *) fade) + 0x40)));
  if ((*((s32 *) (((s8 *) fade) + 0x40))) == 0x10000)
  {
    sub_080BB898(fade);
    sub_080BE7D4();
    sub_080BE87C();
    sub_080BE644(entity);
    *((s8 *) (((s8 *) (((*((s16 *) (((s8 *) entity) + 0x22))) * 2) + entity)) + 0x19)) = 0;
    scriptTable = (s32 *) 0x08671BB0;
    sub_080C31E4(entity + 0x18, entity + 0x22, *scriptTable);
  }
}
