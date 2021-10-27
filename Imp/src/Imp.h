#pragma once

//This needs to be included by the applications using Imp
//Core engine classes
#include "Imp/Application.h"
#include "Imp/Log.h"
#include "Imp/Layer.h"
#include "Imp/Time.h"

//Input
#include "Imp/Input.h"
#include "Imp/KeyCodes.h"
#include "Imp/MouseCodes.h"

//Events
#include "Imp/Events/KeyEvent.h"
#include "Imp/Events/WindowEvent.h"
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
#include "Imp/EntryPoint.h"