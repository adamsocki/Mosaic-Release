
enum CameraType : uint8 {
    CameraType_Perspective,
    CameraType_Orthographic,
};

struct CameraFocusPoint
{


};

struct Camera {
    CameraType type;
    
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


};

void UpdateCamera(Camera *camera, vec3 position, quaternion rotation ) {
     //rotation = AxisAngle(V3(1, 0, 0), DegToRad(camera->pitch));
    
   mat4 camWorld = TRS(position, rotation, V3(1));
   camera->view = OrthogonalInverse(camWorld);
    
   camera->viewProjection = camera->projection * camera->view;
}
