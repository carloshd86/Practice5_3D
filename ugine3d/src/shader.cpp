#include "shader.h"
#include "vertex.h"

std::string Shader::m_error = "";

ShaderPtr Shader::create(const std::string& vertex, const std::string& fragment) {
	std::shared_ptr<Shader> p(new Shader(vertex, fragment), [](Shader* p) {
		delete p;
	});
	if (p->m_id == 0) p = nullptr;
	return p;
}

Shader::Shader(const std::string& vertex, const std::string& fragment) : m_id(0) {
	m_error = "";

	// create vertex shader
	int retCode;
	const char* cVertexShaderSource = vertex.c_str();
	uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &cVertexShaderSource, nullptr);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &retCode);
	if (retCode == GL_FALSE) {
		char errorLog[1024];
		glGetShaderInfoLog(vertexShader, sizeof(errorLog), nullptr, errorLog);
		m_error = errorLog;
		glDeleteShader(vertexShader);
		return;
	}

	// create fragment shader
	const char* cFragmentShaderSource = fragment.c_str();
	uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &cFragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &retCode);
	if (retCode == GL_FALSE) {
		char errorLog[2048];
		glGetShaderInfoLog(fragmentShader, sizeof(errorLog), nullptr, errorLog);
		m_error = errorLog;
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		return;
	}

	// create and link program
	m_id = glCreateProgram();
	glAttachShader(m_id, vertexShader);
	glAttachShader(m_id, fragmentShader);
	glLinkProgram(m_id);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glGetProgramiv(m_id, GL_LINK_STATUS, &retCode);
	if (retCode == GL_FALSE) {
		char errorLog[1024];
		glGetProgramInfoLog(m_id, sizeof(errorLog), nullptr, errorLog);
		m_error = errorLog;
		glDeleteProgram(m_id);
		m_id = 0;
		return;
	}

	// use program and get locations
	m_vposLoc    = glGetAttribLocation(m_id, "vpos");
	m_vcolorLoc  = glGetAttribLocation(m_id, "vcolor");
	m_vtexLoc    = glGetAttribLocation(m_id, "vtex");
	m_vnormalLoc = glGetAttribLocation(m_id, "vnormal");
}

Shader::~Shader() {
	if (m_id) glDeleteProgram(m_id);
}

uint32_t Shader::getId() const {
	return m_id;
}

const std::string& Shader::getError() {
	return m_error;
}

void Shader::use() const {
	glUseProgram(m_id);
}

void Shader::setupAttribs() const {
	if (-1 != m_vposLoc) {
		glEnableVertexAttribArray(m_vposLoc);
		glVertexAttribPointer(m_vposLoc, 3, GL_FLOAT, false, sizeof(Vertex), reinterpret_cast<const void*>(offsetof(Vertex, position)));
	}
	if (-1 != m_vcolorLoc) {
		glEnableVertexAttribArray(m_vcolorLoc);
		glVertexAttribPointer(m_vcolorLoc, 3, GL_FLOAT, false, sizeof(Vertex), reinterpret_cast<const void*>(offsetof(Vertex, color)));
	}
	if (-1 != m_vtexLoc) {
		glEnableVertexAttribArray(m_vtexLoc);
		glVertexAttribPointer(m_vtexLoc, 2, GL_FLOAT, false, sizeof(Vertex), reinterpret_cast<const void*>(offsetof(Vertex, textCoords)));
	}
	if (-1 != m_vnormalLoc) {
		glEnableVertexAttribArray(m_vnormalLoc);
		glVertexAttribPointer(m_vnormalLoc, 3, GL_FLOAT, false, sizeof(Vertex), reinterpret_cast<const void*>(offsetof(Vertex, normals)));
	}
}

int Shader::getLocation(const std::string& name) const {
	return glGetUniformLocation(m_id, name.c_str());
}

void Shader::setInt(int loc, int val) {
	if (loc != -1) glUniform1i(loc, val);
}

void Shader::setFloat(int loc, float val) {
	if (loc != -1) glUniform1f(loc, val);
}

void Shader::setVec3(int loc, const glm::vec3& vec) {
	if (loc != -1) glUniform3fv(loc, 1, glm::value_ptr(vec));
}

void Shader::setVec4(int loc, const glm::vec4& vec) {
	if (loc != -1) glUniform4fv(loc, 1, glm::value_ptr(vec));
}

void Shader::setMatrix(int loc, const glm::mat4& matrix) {
	if (loc != -1) glUniformMatrix4fv(loc, 1, false, glm::value_ptr(matrix));
}
