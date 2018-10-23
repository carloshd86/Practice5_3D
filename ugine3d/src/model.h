#pragma once

#include "entity.h"
#include "mesh.h"

class Model;
typedef std::shared_ptr<Model> ModelPtr;

class Model : public Entity {
public:
	static ModelPtr create(const MeshPtr& mesh);
	virtual void draw() override;
protected:
	Model(const MeshPtr& mesh) : m_mesh(mesh) {}
private:
	MeshPtr m_mesh;
};