#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <raylib.h>
#include <raymath.h>

class SwagCam
{
public:
    Camera camera{};
    float pitch = 0.0f;
    float yaw = -90.0f;
    float speed = 5.0f;
    float sensitivity = 0.1f;

    // construct
    SwagCam(const Vector3 &startPos = {0.0f, 2.0f, 5.0f})
    {
        camera.position = startPos;
        camera.up = {0.0f, 1.0f, 0.0f};
        camera.fovy = 60.0f;
    }

    // update the camera
    void Update(float deltaTime)
    {
        // look around
        Vector2 mouseDelta = GetMouseDelta();
        yaw += mouseDelta.x * sensitivity;
        pitch -= mouseDelta.y * sensitivity;

        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        Vector3 front;
        front.x = cosf(DEG2RAD * yaw) * cosf(DEG2RAD * pitch);
        front.y = sinf(DEG2RAD * pitch);
        front.z = sinf(DEG2RAD * yaw) * cosf(DEG2RAD * pitch);
        front = Vector3Normalize(front);

        Vector3 right = Vector3Normalize(Vector3CrossProduct(front, camera.up));

        // move
        if (IsKeyDown(KEY_W))
            camera.position = Vector3Add(camera.position, Vector3Scale(front, speed * deltaTime));
        if (IsKeyDown(KEY_S))
            camera.position = Vector3Subtract(camera.position, Vector3Scale(front, speed * deltaTime));
        if (IsKeyDown(KEY_D))
            camera.position = Vector3Add(camera.position, Vector3Scale(right, speed * deltaTime));
        if (IsKeyDown(KEY_A))
            camera.position = Vector3Subtract(camera.position, Vector3Scale(right, speed * deltaTime));
        if (IsKeyDown(KEY_SPACE))
            camera.position.y += speed * deltaTime;
        if (IsKeyDown(KEY_LEFT_CONTROL))
            camera.position.y -= speed * deltaTime;

        camera.target = Vector3Add(camera.position, front);
    }
};

#endif // CAMERA_HPP
