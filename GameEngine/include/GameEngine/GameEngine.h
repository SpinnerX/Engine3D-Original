#pragma once

/**
 * 
 * 
 * Only intended to be used and called by client applications
 * 
 * For use by GameEngine application
 * 
*/

#include <GameEngine/Application.h>
#include <GameEngine/Layer.h>

// ------------- Engine Logger ---------------
#include <GameEngine/EngineLogger.h>
// -------------------------------------------

#include <GameEngine/InputPoll.h>
#include <GameEngine/KeyCodes.h>
#include <GameEngine/MouseButtonCodes.h>

#include <GameEngine/Imgui/ImGuiLayer.h>

// Renderer-related stuff (virtual interfaces, impl's, etc)
#include <GameEngine/Renderer/Buffer.h>
#include <GameEngine/Renderer/Shader.h>
#include <GameEngine/Renderer/VertexArray.h>

#include <GameEngine/Renderer/RenderCommand.h>


#include <GameEngine/Renderer/Renderer.h>
#include <GameEngine/Renderer/OrthographicCamera.h>
#include <GameEngine/platforms/OpenGL/OpenGLVertexArray.h>
#include <GameEngine/platforms/OpenGL/OpenGLBuffer.h>

// --------------- Entry Point ---------------
#include <GameEngine/EntryPoint.h>
// -------------------------------------------
