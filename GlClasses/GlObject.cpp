#include "GlClasses/GlObject.h"
#include "Game.h"

#include <glm/ext.hpp>

GlObject::GlObject(NormalShader *s, int nVerts, GLfloat *vetPos, GLfloat *vetColor, int nNormals, GLfloat *vetNormals)
{
	shader = s;
	numVerts = nVerts;
	numNormals = nNormals;
	modelMatrix = glm::mat4(1.f);

	glBindBuffer(GL_ARRAY_BUFFER, vboPos);
	glBufferData(GL_ARRAY_BUFFER, 3*numVerts*sizeof(GLfloat), vetPos, GL_STATIC_DRAW);
	checkGlErrors();

	glBindBuffer(GL_ARRAY_BUFFER, vboColor);
	glBufferData(GL_ARRAY_BUFFER, 3*numVerts*sizeof(GLfloat), vetColor, GL_STATIC_DRAW);
	checkGlErrors();

	glBindBuffer(GL_ARRAY_BUFFER, vboNormals);
	glBufferData(GL_ARRAY_BUFFER, 3*numNormals*sizeof(GLfloat), vetNormals, GL_STATIC_DRAW);
	checkGlErrors();
}

GlObject::~GlObject()
{
	//for(GlObject *childUiObj : childList)
	//	delete childUiObj;
}


void GlObject::setModelMatrix(glm::mat4 m)
{
	modelMatrix = m;
}

// ----- Render ----- //

void GlObject::render(glm::mat4 projMatrix, glm::mat4 viewMatrix)
{
	glUseProgram(shader->program);

	safe_glUniformMatrix4fv(shader->h_uModelMatrix, &modelMatrix[0][0]);
	safe_glUniformMatrix4fv(shader->h_uViewMatrix, &viewMatrix[0][0]);
	safe_glUniformMatrix4fv(shader->h_uProjMatrix, &projMatrix[0][0]);
	safe_glUniform3f(shader->h_uLightPosition, Game::Instance().lightPos.x, Game::Instance().lightPos.y, Game::Instance().lightPos.z);
	safe_glUniform3f(shader->h_uLightIntensity, Game::Instance().lightIntensity.x, Game::Instance().lightIntensity.y, Game::Instance().lightIntensity.z);

	glEnableVertexAttribArray(shader->h_aPosition);
	glEnableVertexAttribArray(shader->h_aColor);
	glEnableVertexAttribArray(shader->h_aNormal);

	glBindBuffer(GL_ARRAY_BUFFER, vboPos);
	glVertexAttribPointer(shader->h_aPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vboColor);
	glVertexAttribPointer(shader->h_aColor, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vboNormals);
	glVertexAttribPointer(shader->h_aNormal, 3, GL_FLOAT, GL_TRUE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, numVerts);

	glDisableVertexAttribArray(shader->h_aPosition);
	glDisableVertexAttribArray(shader->h_aColor);
	glDisableVertexAttribArray(shader->h_aNormal);
}
