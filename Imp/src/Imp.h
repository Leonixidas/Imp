#pragma once
#define GLM_ENABLE_EXPERIMENTAL
//This needs to be included by the applications using Imp
//Core engine classes
#include "Imp/Core/Application.h"
#include "Imp/Core/Log.h"
#include "Imp/Core/Layer.h"
#include "Imp/Utils/PlatformUtils.h"

//Input
#include "Imp/Core/Input.h"
#include "Imp/Core/KeyCodes.h"
#include "Imp/Core/MouseCodes.h"

//Events
#include "Imp/Events/KeyEvent.h"
#include "Imp/Events/ApplicationEvent.h"
#include "Imp/Events/MouseEvent.h"

//Rendering
#include "Imp/Renderer/Buffer.h"
#include "Imp/Renderer/Texture.h"
#include "Imp/Renderer/Renderer.h"
#include "Imp/Renderer/RenderCommand.h"
#include "Imp/Renderer/Camera.h"
#include "Imp/Renderer/Shader.h"
#include "Imp/Renderer/VertexArray.h"

//Entry Point
#include "Imp/Core/EntryPoint.h"