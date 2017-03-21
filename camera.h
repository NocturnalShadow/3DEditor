#pragma once

#include <QVector3D>
#include <QMatrix4x4>


class Camera
{
private:
    QVector3D position  = { 0.0f, 0.0f, 0.0f };
    QVector3D forward   = { 0.0f, 0.0f, 1.0f };
    QVector3D up        = { 0.0f, 1.0f, 0.0f };

    QMatrix4x4 projection;
    QMatrix4x4 view;

    float fov           = 60.0f;
    float aspect        = 4.0f/3.0f;

public:
    Camera(float _fov = 60.0f, float _aspect = 4.0f/3.0f)
         : fov{ _fov }
    {
        projection.perspective(_fov, _aspect, 0.1f, 100.f);
        view.lookAt(position, position + forward, up);
    }

public:
    QMatrix4x4 Projection()      const { return projection;         }
    QMatrix4x4 View()            const { return view;               }
    QMatrix4x4 ViewProjection()  const { return projection * view;  }

    QVector3D  GetPosition()     const { return position;           }

    void MoveTo(const QVector3D& _position)
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

    void ChangeAspect(int width, int height)
    {
        aspect = (float) width / (float) height;
        projection.perspective(fov, aspect, 0.1f, 30.f);
    }
    void ChangeFieldOfView(float _fov)
    {
        fov = _fov;
        projection.perspective(fov, aspect, 0.1f, 30.f);
    }
};
