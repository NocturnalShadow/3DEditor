#pragma once

#include <QVector3D>
#include <QMatrix4x4>


class Transform
{
private:
    QVector3D position     = {0, 0, 0};
    QVector3D rotation     = {0, 0, 0};
    QVector3D scale        = {1, 1, 1};

public:
    Transform() = default;
    Transform(const QVector3D& _position, const QVector3D& _rotation, const QVector3D& _scale)
        : position{ _position }, rotation{ _rotation }, scale{ _scale }
    {	}

    virtual ~Transform() = default;

public:
    const QVector3D& GetPos()		const	{ return position;	}
    const QVector3D& GetRot()		const	{ return rotation;	}
    const QVector3D& GetScale()		const	{ return scale; }

    void SetPos(const QVector3D& _position)		{ position = _position; }
    void SetRot(const QVector3D& _rotation)		{ rotation = _rotation; }
    void SetScale(const QVector3D& _scale)      { scale = _scale; }

    QVector3D& Position()					{ return position;	}
    QVector3D& Rotation()					{ return rotation;	}
    QVector3D& Scale()						{ return scale;     }

    QMatrix4x4 Model() const
    {
        QMatrix4x4 posMatrix;
        QMatrix4x4 rotXMatrix;
        QMatrix4x4 rotYMatrix;
        QMatrix4x4 rotZMatrix;
        QMatrix4x4 scaleMatrix;

        posMatrix.translate(position);
        rotXMatrix.rotate(rotation.x(), QVector3D(1, 0, 0));
        rotYMatrix.rotate(rotation.y(), QVector3D(0, 1, 0));
        rotZMatrix.rotate(rotation.z(), QVector3D(0, 0, 1));
        scaleMatrix.scale(scale);

        QMatrix4x4 rotMatrix = rotZMatrix * rotYMatrix * rotXMatrix;

        return posMatrix * rotMatrix * scaleMatrix;
    }
};
