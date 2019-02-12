#pragma once

#include "common.h"

class Shader;
typedef std::shared_ptr<Shader> ShaderPtr;

class Shader {
public:
	static ShaderPtr create(const std::string& vertex, const std::string& fragment);

	// Devuelve el identificador de OpenGL del programa
	uint32_t getId() const;

	// Obtiene el mensaje de error generado al compilar o enlazar
	static const std::string& getError();

	// Activa el uso de este programa
	void use() const;

	// Activa la escritura de las variables attribute,
	// y especifica su formato
	void setupAttribs() const;

	// Obtiene la localización de una variable uniform
	int getLocation(const std::string& name) const;

	// Da valor a una variable uniform
	static void setInt(int loc, int val);
	static void setIntArrayIndex(int loc, int index, const int& val);
	static void setFloat(int loc, float val);
	static void setFloatArrayIndex(int loc, int index, const float& val);
	static void setVec3(int loc, const glm::vec3& vec);
	static void setVec3ArrayIndex(int loc, int index, const glm::vec3& vec);
	static void setVec4(int loc, const glm::vec4& vec);
	static void setMatrix(int loc, const glm::mat4& matrix);
protected:
	Shader(const std::string& vertex, const std::string& fragment);
	~Shader();
private:
	static std::string m_error;
	uint32_t	m_id;
	int			m_vposLoc;
	int			m_vcolorLoc;
	int			m_vtexLoc;
	int			m_vnormalLoc;
	glm::vec3   m_diffuseContrib;
	glm::vec3   m_specularContrib;
};