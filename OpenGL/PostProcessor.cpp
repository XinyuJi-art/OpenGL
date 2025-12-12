#include "PostProcessor.h"
#include "WindowController.h"
#include "GameController.h"
#include "Shader.h"
#include "Time.h"

PostProcessor::~PostProcessor()
{
	glDeleteFramebuffers(1, &framebuffer);
	glDeleteTextures(1, &textureColorbuffer);
	glDeleteRenderbuffers(1, &renderBufferObject);
}

void PostProcessor::Create(json::JSON& jsonData)
{
	M_ASSERT(jsonData.hasKey("Shader"), "Shader is required");
	//shader = GameController::Instance().GetShader(jsonData["Shader"].ToString().c_str());
	CreateBuffer();
	CreateVertices();
}

void PostProcessor::Start()
{
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
}

void PostProcessor::End()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST);

	glUseProgram(shader->GetProgramID());
	shader->SetTextureSampler("screenTexture", GL_TEXTURE0, 0, textureColorbuffer);
	shader->SetTextureSampler("depthSampler", GL_TEXTURE1, 1, textureDepthBuffer);
	//shader->SetFloat("Frequency", GameController::Instance().frequency);
	//shader->SetFloat("Time", Time::Instance().TotalTime());
	//shader->SetFloat("Amplitude", GameController::Instance().amplitude);
	//shader->SetInt("TintBlue", (int)GameController::Instance().TintBlue);

	//BindVertices();
	//if (GameController::Instance().wireFrame)
	//{
	//	glLineWidth(5.0f);
	//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//}
	//else
	//{
	//	glLineWidth(1.0f);
	//	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//}

	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(shader->GetAttrVertices());
	glDisableVertexAttribArray(shader->GetAttrTexCoords());
}

void PostProcessor::CreateVertices()
{
	float vertexData[] = {
		-1.0f,	1.0f,	0.0f,	1.0f,
		-1.0f,	-1.0f,	0.0f,	0.0f,
		1.0f,	-1.0f,	1.0f,	0.0f,

		-1.0f,	1.0f,	0.0f,	1.0f,
		1.0f,	-1.0f,	1.0f,	0.0f,
		1.0f,	1.0f,	1.0f,	1.0f
	};

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), &vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void PostProcessor::CreateBuffer()
{
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	glGenTextures(1, &textureColorbuffer);
	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
	//Resolution r = WindowController::Instance().GetResolution();
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, r.width, r.height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);

	glGenTextures(1, &textureDepthBuffer);
	glBindTexture(GL_TEXTURE_2D, textureDepthBuffer);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, r.width, r.height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, textureDepthBuffer, 0);

	M_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is not complete!");
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void PostProcessor::BindVertices()
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	glEnableVertexAttribArray(shader->GetAttrVertices());
	glVertexAttribPointer(shader->GetAttrVertices(),
		2,
		GL_FLOAT,
		GL_FALSE,
		4 * sizeof(float),
		(void*)0);

	glEnableVertexAttribArray(shader->GetAttrTexCoords());
	glVertexAttribPointer(shader->GetAttrTexCoords(),
		2,
		GL_FLOAT,
		GL_FALSE,
		4 * sizeof(float),
		(void*)(2 * sizeof(float)));
}
