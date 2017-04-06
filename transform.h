#pragma once

#include <QVector3D>
#include <QMatrix4x4>


class Transformation
{
private:
    QVector3D position     = {0, 0, 0};
    QVector3D rotation     = {0, 0, 0};
    QVector3D scale        = {1, 1, 1};

    QQuaternion rotation_chain;

public:
    Transformation() = default;
    Transformation(const QVector3D& _position, const QVector3D& _rotation, const QVector3D& _scale)
        : position{ _position }, rotation{ _rotation }, scale{ _scale }
    {	}

    virtual ~Transformation() = default;

public:
    const QVector3D& GetPos()       const           { return position;	}
    const QVector3D& GetRot()       const           { return rotation;	}
    const QVector3D& GetScale()     const           { return scale;     }

    void SetPosition(const QVector3D& _position)    { position = _position; }
    void SetRotation(const QVector3D& _rotation)    { rotation = _rotation; }
    void SetScale   (const QVector3D& _scale)       { scale    = _scale;    }

    void IncPosition(const QVector3D& _position)    { position += _position; }
    void IncRotation(const QVector3D& _rotation)    { rotation += _rotation; }
    void IncScale   (const QVector3D& _scale)       { scale    += _scale;    }

    void AddRotation(const QVector3D& _rotation)    { rotation_chain = QQuaternion::fromEulerAngles(_rotation) * rotation_chain; }


    QVector3D& Position()                           { return position;	}
    QVector3D& Rotation()                           { return rotation;	}
    QVector3D& Scale()                              { return scale;     }

    QMatrix4x4 Model()              const
    {
        QMatrix4x4 modelMatrix;
        modelMatrix.setToIdentity();
        modelMatrix.translate(position);
        modelMatrix.rotate(rotation.x(), QVector3D(1, 0, 0));
        modelMatrix.rotate(rotation.y(), QVector3D(0, 1, 0));
        modelMatrix.rotate(rotation.z(), QVector3D(0, 0, 1));
        modelMatrix = modelMatrix * QMatrix4x4(rotation_chain.toRotationMatrix());
        modelMatrix.scale(scale);

        return modelMatrix;
    }
};
