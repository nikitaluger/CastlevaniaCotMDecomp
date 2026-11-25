s32 sub_08003740(u8 *, u8 *);
s32 sub_0806D518(u8 *, u8 *, u8 *);
void sub_0806D588(u8 *, u8 *);
void sub_080722E0(u8 *, u32);
void sub_080C31E0(u8 *, void *);
s16 sub_080C364C(s32, s32);

/* Advance one entity's motion while it is active: clamp and propagate a large
 * coordinate to its child nodes, integrate position from the physics body's
 * velocity, and despawn when the velocity expires or global state ends it. */
void sub_0807599C(u8 *entity)
{
  u8 *owner;
  u8 *body;
  u8 *childNode;
  u8 *component;
  owner = *((u8 **) (entity + 0x6C));
  body = owner + 4;
  component = *((u8 **) (entity + 0x38));
  if (sub_0806D518(entity, component, body) == 0)
  {
    u8 *global;
    if ((*((s16 *) (component + 4))) > 0x100)
    {
      int coordValue;
      u8 *node;
      *((u16 *) (component + 4)) = (*((u16 *) (component + 4))) - 0x40;
      *((u16 *) (component + 6)) = (*((u16 *) (component + 6))) - 0x40;
      childNode = *((u8 **) (body + 0x2C));
      node = childNode;
      do
      {
        coordValue = *((s16 *) (component + 4));
        *((s16 *) (node + 6)) = sub_080C364C(0x1C00, coordValue);
      }
      while (0);
      node = *((u8 **) (body + 0x2C));
      *((s16 *) (node + 8)) = sub_080C364C(0x1C00, *((s16 *) (component + 6)));
    }
    global = (u8 *) 0x02025FF0;
    *((u16 *) (component + 0)) = *((u16 *) (global + 0x18C2));
    sub_08003740(owner + 0x20, component);
    sub_080722E0(body, ((*((u32 *) (body + 0x54))) << 24) >> 24);
    {
      s32 xStep;
      xStep = (*((s32 *) (body + 8))) * ((*((s32 *) (body + 0x58))) >> 0x0C);
      if (xStep < 0)
      {
        xStep += 0x0F;
      }
      *((s32 *) (owner + 4)) += xStep >> 4;
    }
    {
      s32 speed;
      s32 yStep;
      s32 newSpeed;
      speed = *((s32 *) (body + 0x58));
      yStep = (*((s32 *) (body + 0x0C))) * (speed >> 0x0C);
      if (yStep <= (0 - 1))
      {
        yStep += 0x0F;
      }
      *((s32 *) (body + 4)) += yStep >> 4;
      newSpeed = speed - 0x1000;
      *((s32 *) (body + 0x58)) = newSpeed;
      if (newSpeed <= 0)
      {
        sub_080C31E0(entity, *((void **) (entity + 0x24)));
        return;
      }
    }
    sub_0806D588(component, body);
    if ((*((u8 *) (global + 0x14ED))) != 0x36)
    {
      sub_080C31E0(entity, *((void **) (entity + 0x24)));
    }
  }
}
