#pragma once

#include <QVector3D>
#include <QMatrix4x4>
#include <QQuaternion>

class ICamera
{
protected:
    QVector3D position;

    float fov;
    float aspect;

    QMatrix4x4 view;
    QMatrix4x4 projection;

public:
    ICamera(const QVector3D& _position, float _fov = 45.0f, float _aspect = 4.0f/3.0f)
         : position{ _position }, fov{ _fov }, aspect { _aspect }
    {
        projection.perspective(_fov, _aspect, 0.1f, 100.f);
    }

public:
    virtual void MoveTo(const QVector3D& _position) = 0;

public:
    QMatrix4x4 View()            const      { return view;               }
    QMatrix4x4 Projection()      const      { return projection;         }
    QMatrix4x4 ViewProjection()  const      { return projection * view;  }
    QVector3D  Position()        const      { return position;           }

    void ChangeAspect(int width, int height)
    {
        aspect = (float) width / (float) height;
        projection.setToIdentity();
        projection.perspective(fov, aspect, 0.1f, 100.f);
    }
    void ChangeFieldOfView(float _fov)
    {
        fov = _fov;
        projection.setToIdentity();
        projection.perspective(fov, aspect, 0.1f, 100.f);
    }

};

class FirstPersonCamera : public ICamera
{
private:
    QVector3D forward   = { 0.0f, 0.0f, 1.0f };
    QVector3D up        = { 0.0f, 1.0f, 0.0f };

public:
    FirstPersonCamera(float _fov = 45.0f, float _aspect = 4.0f/3.0f)
        : ICamera{ {0.0f, 0.0f, 0.0f}, _fov, _aspect }
    {
        view.lookAt(position, position + forward, up);
    }

public:
    void MoveTo(const QVector3D& _position) override
    {
        position = _position;
        view.setToIdentity();
        view.lookAt(position, position + forward, up);
    }
    void LookTo(const QVector3D& direction)
    {
        forward = direction;
        view.setToIdentity();
        view.lookAt(position, position + forward, up);
    }
    void LookAt(const QVector3D& point)
    {
        forward = point - position;
        view.setToIdentity();
        view.lookAt(position, position + forward, up);
    }

    void ResetPosition()
    {
        position  = { 0.0f, 0.0f, 0.0f };
        forward   = { 0.0f, 0.0f, 1.0f };
        up        = { 0.0f, 1.0f, 0.0f };

        fov           = 45.0f;
        aspect        = 4.0f/3.0f;

        view.setToIdentity();
        view.lookAt(position, position + forward, up);

        projection.setToIdentity();
        projection.perspective(fov, aspect, 0.1f, 100.f);
    }
};


class SceneViewCamera : public ICamera
{
private:
    QVector3D center    = { 0.0f, 0.0f, 0.0f };
    QVector3D up        = { 0.0f, 1.0f, 0.0f };
    QVector3D right     = { 1.0f, 0.0f, 0.0f };

    QQuaternion centered_rotation;

    float xRot = 0;
    float yRot = 0;

    bool xReverse    = false;

public:
    SceneViewCamera(QVector3D _position = {3.0f, 3.0f, -3.0f}, float _fov = 45.0f, float _aspect = 4.0f/3.0f)
         : ICamera{ _position, _fov, _aspect }
    {
        view.lookAt(position, center, up);
        centered_rotation = QQuaternion();
    }

public:
    void MoveTo(const QVector3D& _position) override
    {
        position = _position;
        view.setToIdentity();
        centered_rotation = QQuaternion();
        view.lookAt(position, center, up);
    }
    void LookAt(const QVector3D& _center)
    {
        center = _center;
        view.setToIdentity();
        centered_rotation = QQuaternion();
        view.lookAt(centered_rotation * position, center, up);
    }

   void Rotate(float deg_xRot, float deg_yRot)
   {
       view.setToIdentity();
       if(!xReverse) {
           xRot += deg_xRot;
       } else {
           xRot -= deg_xRot;
       }
       yRot += deg_yRot;
       centered_rotation = QQuaternion::fromAxisAndAngle(up, xRot) * QQuaternion::fromAxisAndAngle(right, yRot);
       view.lookAt(centered_rotation * position, center, centered_rotation * up);
   }

   void Rotate(QPoint p) {
        Rotate((float) -p.rx() / 2.3f, (float) -p.ry() / 2.3f);
   }

   void Zoom(float units)
   {
        position += (center - position) * units;
        view.setToIdentity();
        view.lookAt(centered_rotation * position, center, up);
   }

   void Reset()
   {
       centered_rotation = QQuaternion();
       view.setToIdentity();
       view.lookAt(centered_rotation*position, center, up);
       xRot = yRot = 0;
   }

   void ReverseIfNeeded()
   {
       if((centered_rotation * up).y() > 0 && xReverse)
           xReverse = false;
       if((centered_rotation * up).y() < 0 && !xReverse)
           xReverse = true;
   }
};

