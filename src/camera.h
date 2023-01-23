
enum CameraType : uint8 {
    CameraType_Perspective,
    CameraType_Orthographic,
};

enum CameraControllerType
{
    ControllerType_FirstPerson,
    ControllerType_ThirdPerson,

    // Level Editor Camera Types,

    ControllerType_TopDown,

};

struct CameraFocusPoint
{


};

struct Camera {
    CameraType type;
    CameraControllerType controllerType;

    mat4 view;
    mat4 rot;
    mat4 projection;
    mat4 viewProjection;

    // Orthographic
    real32 width;
    real32 height;

    real32 size;

    vec3 CFP;                // cameraFocusPoint
    real32 distanceToCFP;
    real32 angleAroundCFP;

    real32 pitch;
    real32 yaw;
    real32 roll;

    vec3 pos;
    vec3 front;
    vec3 up;
    
    vec3 direction;

    real32 cameraSpeed;
    real32 cameraSpeedThirdPerson;
    real32 rotationSpeed;
    
    real32 rotationValue;

    real32 speed;

    bool isWalkingMod;
    vec3 walkingModDisplacement;
    real32 walkingModTime;

    bool resetWalk;
    real32 resetWalkTimer;
    real32 resetWalkTimerDeltaTimer;
    
    bool posValWalking;
    vec3 targetPos;
    real32 targetRotY;
    bool isWalkingForwardOrBackward;
    real32 targetSpeed;
    real32 targetTurnSpeed;
    real32 currentSpeed;
    real32 currentTurnSpeed;
    //real32 targetSpeed;
};

void UpdateCamera(Camera *camera, vec3 position, quaternion rotation ) {
     //rotation = AxisAngle(V3(1, 0, 0), DegToRad(camera->pitch));
    
    mat4 camWorld = Identity4();
   camWorld = TRS(position, rotation, V3(0,1,0));
  // camera->view= TRS(position, rotation, V3(0,1,0));
   //camera->view = OrthogonalInverse(camWorld);
  // camera->view = camWorld;
  // camera->viewProjection = camera->projection * camera->view;
}
