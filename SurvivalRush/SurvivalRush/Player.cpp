#include "include/Player.h"
#include "include/CustomTime.h"
#include "include/Debug.h"

Player::Player(float health,float speed, float damping, float maxForce, float rotationSpeed,Collider collider) 
    : SimpleCharacter(SimpleGeo(TRIANGLE, green)), health(health), maxHealth(health), speed(speed), damping(damping),
    maxForce(maxForce), rotationSpeed(rotationSpeed),collider(collider)
{
    weapon[0] = new Weapon(Bullet(SimpleGeo(CIRCLE, yellow, 0.5f), 30, 10, 20,Collider(0.25f)), 1);
    weapon[1] = new Weapon(Bullet(SimpleGeo(SQUARE, red, 0.3f), 25, 25, 100,Collider(0.15f)), 1.5f);
    weapon[2] = new WeaponShotgun(Bullet(SimpleGeo(TRIANGLE, magenta, 0.5f), 15, 15, 15,Collider(0.25f)), 1.25f, 2, 30);
}

void Player::PlayerMotionUpdate(const Input& input,const Camera& camera)
{
    //Rotate Towards Mouse
    Vector3 hitPos;
    input.GetHitOnXZ(camera, hitPos);
    Vector3 playerDir = (hitPos - transform.position).Normalized();
    float angleToRotate = SignedAngleBetween(transform.Forward(), playerDir, up);

    float deltaTime = CustomTime::Instance().deltaTime;

    float maxTurnPerFrame = 180.0f * deltaTime * rotationSpeed; // degrees per second
    angleToRotate = Clamp(angleToRotate, -maxTurnPerFrame, maxTurnPerFrame);

    transform.RotateOnY(angleToRotate);

    //Movement
    float horizontalInput = input.GetKeyboardDirectionHorizontal();
    float verticalInput = input.GetKeyboardDirectionVertical();
    Vector3 forwardInput = transform.Forward() * verticalInput;
    Vector3 rightInput = transform.Right() * horizontalInput;
    Vector3 dir = (forwardInput + rightInput).Normalized();

    Vector3 desiredVelocity = dir * (speed * deltaTime);
    Vector3 force = desiredVelocity - velocity;
    Vector3 dampingForce = -velocity* damping;

    force = force - dampingForce;
    
    velocity = velocity + force.ClampMagnitude(maxForce) * deltaTime;

    velocity = velocity.ClampMagnitude(speed);
    transform.Move(velocity);
    Update();

    SimpleCharacter* playerForwardDebug = new SimpleCharacter(SimpleGeo(SQUARE, blue));
    SimpleCharacter* playerRightDebug = new SimpleCharacter(SimpleGeo(SQUARE, red));
    SimpleCharacter* inputDebug = new SimpleCharacter(SimpleGeo(CIRCLE, white));

    playerForwardDebug->transform.SetPosition(transform.position + transform.Forward() * 3);
    playerRightDebug->transform.SetPosition(transform.position + transform.Right() * 3);
    inputDebug->transform.SetPosition(hitPos);

    Debug::Instance().AddDebug(inputDebug);
    Debug::Instance().AddDebug(playerForwardDebug);
    Debug::Instance().AddDebug(playerRightDebug);

    collider.DrawDebug(transform.position,transform.scale);
}

void Player::PlayerActionUpdate(const Input& input)
{
    Weapon* currentWeapon = weapon[input.selectedSlot];
    if (input.leftMouseDown)
    {
        currentWeapon->Fire(transform.Forward(),transform.position);
    }

    for (size_t i = 0; i < 3; i++)
    {
        weapon[i]->Update();
    }
}

void Player::Reset()
{
    health = maxHealth;
    velocity = Vector3();

    transform.SetPosition(Vector3());
    transform.SetRotation(Vector3());

    Update();
}
