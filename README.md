# OpenGL FrameWork 
---
This framework simulates the rendering process of the **Unity Engine**.

This version is currently adapted to versions after OpenGL 3.3. If you need to adapt to previous versions, please overwrite all files in inside GL30.

### Current features included
- MemoryPool
  - TLSF algorithm is used for memory management. Please refer to **MemoryLabel.h** for different memory allocation.
- ThreadPool
  -  Pleas refer to the content under folder **ThreadPool**
- Builtin program
  - skybox, ground, and quad for debug FBO content.
- Debugg and Log
  - Pleas refer to the content under folder **Debugger**
- The rendering process is material-based
- If you create program based on this project, you should initialize and render in **Scene.cpp / Scene.h***
----
An object contains a material, and a material has two rendering passes, namely the main pass and the sub-pass. Key lights and shadows should be done in the master pass. I have encapsulated Attribute and Uniform. These two components should be managed by rendering channels, not Shader. Shader should only be responsible for passing messages from the CPU to the GPU, it does not need to know the specific content of the message
![img](https://cdn.jsdelivr.net/gh/YosefQiuImg/Img@master/uPic/process.png)
a typical example
```c++
void Init()
{
Model model;
	model.Init("Res/Sphere.obj");
	vao = new VAO;
	vao->Init();
	vbo = new VBO();
	vbo->SetSize(model.mVertexCount);
	vbo->SubmitData(model.mData, sizeof(VertexDataFull) * model.mVertexCount);
	
	m = glm::translate(m, glm::vec3(0.0f, 0.0f, -3.0f));

	camera = new Camera;
	camera->Init(cameraPos, targetPos, cameraUp);

	Light* light = new Light;
	Light::mMainLight = light;
	light->SetDiffuseColor(0.0f, 1.0f, 0.0f, 1.0f);

	material = new Material;
	material->mBaseRenderPass = new RenderPass;
	material->mBaseRenderPass->SetShader(Shader::LoadShader("Res/deffer_light", "Res/test_light.vs", "Res/DefferedPosition.fs"));
	material->mBaseRenderPass->SetMatrix4(ModelMatrix.c_str(), glm::value_ptr(m));

	dc.mVAO = vao;
	dc.mVBO = vbo;
	dc.mMaterial = material;
}
void Render()
{
    camera->SwitchTo3D(1280.0f, 720.0f);
	camera->Update(GetFrameTime());
	// render 3D obj
	dc.Draw(camera);

    camera->SwitchTo2D(1280.0f, 720.0f);
    // render UI
}
```

### Third library
- Math
  - GLM
    - version 0.9.9.8
  - Eigen
- GLAD
  - version 4.6
- GLFW
  - version 3.3.8
- UI
  - Imgui
  - FileDialog
  - Imguizmo
- Loader Models
  - Assimp
    - version 5.0.1
  - tiny_loader
- Picture
  - stb_image
    - almost all format picture
  - svpng.inc
    - png
  - EasyBMP
    - bmp
