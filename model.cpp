#include "model.h"


IModel::IModel(const std::vector<QVector3D>& positions)
    : mesh{ new Mesh(positions) },
      vertexArrayObject{ new QOpenGLVertexArrayObject }
{
    mesh->InitializeMesh();
}

IModel::IModel(const std::vector<QVector3D>& positions, const std::vector<uint>& indices)
    : mesh{ new IndexedMesh(positions, indices) },
      vertexArrayObject{ new QOpenGLVertexArrayObject }
{
    mesh->InitializeMesh();
}

IModel::IModel(const IModel& model)
    : mesh{ model.mesh->Clone() },
      vertexArrayObject{ new QOpenGLVertexArrayObject }
{

}

IModel::IModel(const Mesh& mesh)
    : mesh{ mesh.Clone() },
      vertexArrayObject{ new QOpenGLVertexArrayObject }
{
}


void IModel::BindShaderProgram(QOpenGLShaderProgram& program)
{
    BindBaseShaderProgram(program);
}


void IModel::BindBaseShaderProgram(QOpenGLShaderProgram& program)
{
    vertexArrayObject->bind();

    vertexBufferObjects[0].bind();
    program.enableAttributeArray("position");
    program.setAttributeArray("position", GL_FLOAT, 0, 3);

    vertexBufferObjects[1].bind();
    program.enableAttributeArray("normal");
    program.setAttributeArray("normal", GL_FLOAT, 0, 3);

    vertexArrayObject->release();
}

void IModel::InitializeModel()
{
    InitializeBaseModel();
    is_initialized = true;
}

void IModel::DrawBase(QOpenGLFunctions_4_3_Core* glFunctions)
{
    vertexArrayObject->bind();

    if(auto indexed_mesh = dynamic_cast<IndexedMesh*>(mesh.get())) {
        glFunctions->glDrawElements(GL_TRIANGLES, indexed_mesh->VertexCount(), GL_UNSIGNED_INT, nullptr);
    }
    else {
        glFunctions->glDrawArrays(GL_TRIANGLES, 0, mesh->VertexCount());
    }

    vertexArrayObject->release();
}



void IModel::DrawBase(QOpenGLFunctions* glFunctions)
{
    vertexArrayObject->bind();

    if(auto indexed_mesh = dynamic_cast<IndexedMesh*>(mesh.get())) {
        glFunctions->glDrawElements(GL_POINTS, indexed_mesh->VertexCount(), GL_UNSIGNED_INT, nullptr);
    }
    else {
        glFunctions->glDrawArrays(GL_TRIANGLES, 0, mesh->VertexCount());
    }

    vertexArrayObject->release();
}

void IModel::Draw(QOpenGLFunctions* glFunctions)
{
    DrawBase(glFunctions);
}

void IModel::Draw(QOpenGLFunctions_4_3_Core* glFunctions)
{
    DrawBase(glFunctions);
}

void IModel::InitializeBaseModel()
{
    GenerateObjects();
    InitializeBuffers();
}

void IModel::GenerateObjects()
{
    vertexArrayObject->create();
    vertexArrayObject->bind();

    vertexBufferObjects.emplace_back(QOpenGLBuffer::VertexBuffer);
    vertexBufferObjects.emplace_back(QOpenGLBuffer::VertexBuffer);
    vertexBufferObjects.emplace_back(QOpenGLBuffer::IndexBuffer);

    for(auto& vbo : vertexBufferObjects) { vbo.create(); }
}

void IModel::InitializeBuffers()
{
    vertexArrayObject->bind();

    vertexBufferObjects[0].bind();
    vertexBufferObjects[0].allocate(mesh->Positions(), (int)mesh->SizeOfPositions());
    vertexBufferObjects[0].setUsagePattern(QOpenGLBuffer::StreamDraw);

    vertexBufferObjects[1].bind();
    vertexBufferObjects[1].allocate(mesh->Normals(), (int)mesh->SizeOfNormals());
    vertexBufferObjects[1].setUsagePattern(QOpenGLBuffer::StreamDraw);

    if(auto indexed_mesh = dynamic_cast<IndexedMesh*>(mesh.get()))
    {
        vertexBufferObjects[2].bind();
        vertexBufferObjects[2].allocate(indexed_mesh->Indices(), (int)indexed_mesh->SizeOfIndices());
        vertexBufferObjects[2].setUsagePattern(QOpenGLBuffer::StaticDraw);
    }

    vertexArrayObject->release();
}
