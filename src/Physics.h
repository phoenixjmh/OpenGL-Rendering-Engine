#pragma once
#include "PhysicsObject.h"
#include <random>

class Physics
{
  public:
    static bool IsSimulating;

    static void OnWake();

    static void Update(double deltaTime);

    static std::vector<PhysicsObject> ObjectsInScene;

    static void ResolveCollision(PhysicsObject &a, PhysicsObject &b, float magnitude, float deltaTime);

    static void ResolveBorderCollision(PhysicsObject &s, float ground_level, float left_border, float right_border,
                                       float deltaTime);
    static void previousToCurrent();

    static bool GetObjectVectorAccess()
    {
        return m_CanAccessObjects;
    }

    static void SetObjectVectorAccessibility(bool b)
    {
        m_CanAccessObjects = b;
    }

    static float getDistance(float ax, float bx, float ay, float by);

    static float border_resolution_force;

    static float object_resolution_force;

    static unsigned int UUID_DISPENSER;

    static void ClearAll();

  private:
    static bool m_CanAccessObjects;

    static bool first_update;
};
