#include "include/Player.h"
#include "include/CustomTime.h"
#include "include/Debug.h"

Player::Player(float speed,float damping,float maxForce,float rotationSpeed) 
	: SimpleCharacter(SimpleGeo(TRIANGLE, green)),speed(speed),damping(damping),maxForce(maxForce), rotationSpeed(rotationSpeed)
{

}

Vector3 up = Vector3(0.0f, 1.0f, 0.0f);
Vector3 forward = Vector3(0.0f, 0.0f, 1.0f);

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
}