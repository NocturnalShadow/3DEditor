#include "model.h"


Model::Model(const std::vector<QVector3D> &positions, std::vector<QVector4D> colors)
    : mesh{ new Mesh(positions) }, colors{ colors }
{
    mesh->InitializeMesh();
}

Model::Model(const std::vector<QVector3D> &positions, std::vector<QVector4D> colors, const std::vector<uint> &indices)
    : mesh{ new IndexedMesh(positions, indices) }, colors{ colors }
{
    mesh->InitializeMesh();
}

Model::Model(const Model &model)
    : mesh{ model.mesh->clone() }, colors{ model.colors }
{
}

Model::Model(Model &&model)
    : mesh{ std::move(model.mesh) }, colors{ std::move(model.colors) }
{
}

void Model::BindShaderProgram(QOpenGLShaderProgram& program)
{
    vertexArrayObject.bind();

    vertexBufferObjects[0].bind();
    program.enableAttributeArray("position");
    program.setAttributeArray("position", GL_FLOAT, 0, 3);

    vertexBufferObjects[1].bind();
    program.enableAttributeArray("normal");
    program.setAttributeArray("normal", GL_FLOAT, 0, 3);

    vertexBufferObjects[2].bind();
    program.enableAttributeArray("color");
    program.setAttributeArray("color", GL_FLOAT, 0, 4);

    vertexArrayObject.release();
}

void Model::InitializeModel()
{
    InitializeBaseModel();
    is_initialized = true;
}

void Model::Draw(QOpenGLFunctions_4_3_Core* glFunctions)
{
    vertexArrayObject.bind();

    if(auto indexed_mesh = dynamic_cast<IndexedMesh*>(mesh.get())) {
        glFunctions->glDrawElements(GL_TRIANGLES, indexed_mesh->VertexCount(), GL_UNSIGNED_INT, nullptr);
    }
    else {
        glFunctions->glDrawArrays(GL_TRIANGLES, 0, mesh->VertexCount());
    }

    vertexArrayObject.release();
}

void Model::Draw(QOpenGLFunctions* glFunctions)
{
    vertexArrayObject.bind();

    if(auto indexed_mesh = dynamic_cast<IndexedMesh*>(mesh.get())) {
        glFunctions->glDrawElements(GL_TRIANGLES, indexed_mesh->VertexCount(), GL_UNSIGNED_INT, nullptr);
    }
    else {
        glFunctions->glDrawArrays(GL_TRIANGLES, 0, mesh->VertexCount());
    }

    vertexArrayObject.release();
}


void Model::InitializeBaseModel()
{
    GenerateObjects();
    InitializeBuffers();
}

void Model::GenerateObjects()
{
    vertexArrayObject.create();
    vertexArrayObject.bind();

    vertexBufferObjects.emplace_back(QOpenGLBuffer::VertexBuffer);
    vertexBufferObjects.emplace_back(QOpenGLBuffer::VertexBuffer);
    vertexBufferObjects.emplace_back(QOpenGLBuffer::VertexBuffer);
    vertexBufferObjects.emplace_back(QOpenGLBuffer::IndexBuffer);

    for(auto& vbo : vertexBufferObjects) { vbo.create(); }
}

void Model::InitializeBuffers()
{
    vertexArrayObject.bind();

    vertexBufferObjects[0].bind();
    vertexBufferObjects[0].allocate(mesh->Positions(), (int)mesh->SizeOfPositions());
    vertexBufferObjects[0].setUsagePattern(QOpenGLBuffer::StreamDraw);

    vertexBufferObjects[1].bind();
    vertexBufferObjects[1].allocate(mesh->Normals(), (int)mesh->SizeOfNormals());
    vertexBufferObjects[1].setUsagePattern(QOpenGLBuffer::StreamDraw);

    vertexBufferObjects[2].bind();
    vertexBufferObjects[2].allocate(colors.data(), (int)colors.size() * sizeof(colors[0]));
    vertexBufferObjects[2].setUsagePattern(QOpenGLBuffer::StreamDraw);

    if(auto indexed_mesh = dynamic_cast<IndexedMesh*>(mesh.get()))
    {
        vertexBufferObjects[3].bind();
        vertexBufferObjects[3].allocate(indexed_mesh->Indices(), (int)indexed_mesh->SizeOfIndices());
        vertexBufferObjects[3].setUsagePattern(QOpenGLBuffer::StaticDraw);
    }

    vertexArrayObject.release();
}
