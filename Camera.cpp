#include "Camera.hpp"

namespace gps {

    //Camera constructor
    Camera::Camera(glm::vec3 cameraPosition, glm::vec3 cameraTarget, glm::vec3 cameraUp) {
        this->cameraPosition = cameraPosition;
        this->cameraTarget = cameraTarget;
        this->cameraUpDirection = glm::normalize(cameraUp);
        this->cameraFrontDirection = glm::normalize(cameraTarget - cameraPosition);
        this->cameraRightDirection = glm::normalize(glm::cross(this->cameraFrontDirection, this->cameraUpDirection));
    }

    //return the view matrix, using the glm::lookAt() function
    glm::mat4 Camera::getViewMatrix() {
        return glm::mat4(glm::lookAt(this->cameraPosition, this->cameraTarget, this->cameraUpDirection));
    }

    //update the camera internal parameters following a camera move event
    void Camera::move(MOVE_DIRECTION direction, float speed) {
        switch (direction)
        {

        case gps::MOVE_FORWARD:
            this->cameraPosition += speed * this->cameraFrontDirection;
            break;
        case gps::MOVE_BACKWARD:
            this->cameraPosition -= speed * this->cameraFrontDirection;
            break;
        case gps::MOVE_RIGHT:
            this->cameraPosition += speed * this->cameraRightDirection;
            break;
        case gps::MOVE_LEFT:
            this->cameraPosition -= speed * this->cameraRightDirection;
            break;
        default:
            break;
        }

        this->cameraTarget = this->cameraPosition + this->cameraFrontDirection;
    }

    //update the camera internal parameters following a camera rotate event
    //yaw - camera rotation around the y axis
    //pitch - camera rotation around the x axis
    void Camera::rotate(float pitch, float yaw) {

        glm::mat4 transformation_camera = glm::mat4(1.0f);
        transformation_camera = glm::translate(transformation_camera, -this->cameraPosition);
        transformation_camera = glm::rotate(transformation_camera, glm::radians(pitch), this->cameraRightDirection);
        transformation_camera = glm::rotate(transformation_camera, glm::radians(yaw), this->cameraUpDirection);
        transformation_camera = glm::translate(transformation_camera, this->cameraPosition);

        //this->cameraUpDirection = glm::normalize(glm::vec3(transformation_camera * glm::vec4(this->cameraUpDirection, 0)));
        this->cameraFrontDirection = glm::normalize(glm::vec3(transformation_camera * glm::vec4(this->cameraFrontDirection, 0)));
        this->cameraRightDirection = glm::normalize(glm::cross(this->cameraFrontDirection, this->cameraUpDirection));

        this->cameraTarget = this->cameraPosition + this->cameraFrontDirection;

        //TODO
    }

    glm::vec3 Camera::getPosition() {
        return this->cameraPosition;
    }

    glm::vec3 Camera::getDirection(){
        return this->cameraFrontDirection;
    }
}
