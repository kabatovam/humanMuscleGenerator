#include "GLManipulator.h"
#include <IL/il.h>
#include <IL/ilut.h>
#include <FreeImage.h>
#include <libtiff/tiffio.h>

GLManipulator::GLManipulator()
{
	cm = new CameraManipulator();
	texture = 0;
	dispMap = 1;
	animationStopped = true;
}


GLManipulator::~GLManipulator()
{
	//delete scene; --
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void GLManipulator::loadMesh(const std::string path){
	Assimp::Importer importer;
	scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || !scene->mRootNode || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE){
		std::cout << "Assimp error: " << importer.GetErrorString();
		
	}	
	//scene = importer.GetOrphanedScene();
	processNode(scene->mRootNode);
	globalInverseTransform;// = scene->mRootNode->mTransformation; //global trasformation
	//globalInverseTransform.Inverse();
	std::cout << "I have " << scene->mNumAnimations << "animations.\n";
	if (scene->HasAnimations())
	{
		std::cout << "Mam" << scene->mNumAnimations << "animacii!\n\n";
		m->startAnimation(scene->mAnimations[0]);
	}
	
}

void GLManipulator::processNode(aiNode *node){
	if (node->mNumMeshes > 0){
		std::cout << "I have " << node->mNumMeshes << "meshes.\n";
		setupModel(scene->mMeshes[node->mMeshes[0]]); //setupModel()
		
	}
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		if (m != NULL){
			m->findChildren(node->mName.data, (node->mChildren[i])->mName.data);
			
		}
		this->processNode(node->mChildren[i]);				
	}
	if (m != NULL){
		m->setTransform(node->mName.data, node->mTransformation);
	}
}

void GLManipulator::setupModel(aiMesh *mesh){
	m = new MeshManipulator(mesh);
	//loadshaders
	//indices_size = m->getNumIndices();
	bindVAO();
	
}

void GLManipulator::setupShaders(){
	ShaderManipulator shm;
	shm.createShader("", &shaderProgram);
}

void GLManipulator::initialize(){
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_TEXTURE_2D);
	setupShaders();
	loadMesh("C:/martinka/cone_bone_anim.dae");
	m->setupBindPose(globalInverseTransform);
	setupTexture();
	m->writeBones();
	m->bindInfluencers();
	//m->RotateBone("Bone002", 20, 1, 0, 0, 0, globalInverseTransform);
	//std::cout << "T3sting number: " <<scene->mNumMeshes << std::endl;
	//m->tick(globalInverseTransform, scene->mAnimations[0]);
	
}

void GLManipulator::paint(){
	
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glUseProgram(shaderProgram);
	
	if (!animationStopped)
		m->tick(globalInverseTransform, scene->mAnimations[0]);

	cm->bindCamera(&shaderProgram);
	m->bindBones(&shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(shaderProgram, "tex"), 0);
	

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, dispMap);
	glUniform1i(glGetUniformLocation(shaderProgram, "dispMap"), 1);
	

	glBindVertexArray(VAO);
	glPatchParameteri(GL_PATCH_VERTICES, 3);
	glDrawElements(GL_PATCHES, indices_size, GL_UNSIGNED_INT, 0);


	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

	
}

void GLManipulator::bindVAO(){
		
	glGenVertexArrays(1, &VAO);
	
	
	
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, m->getNumvertices() * sizeof(glm::vec3), m->getVertices() , GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glBindAttribLocation(shaderProgram, 0, "position");
	
	glGenBuffers(1, &texCoordVBO);
	glBindBuffer(GL_ARRAY_BUFFER, texCoordVBO);
	glBufferData(GL_ARRAY_BUFFER, m->getNumTexCoords() * sizeof(glm::vec2), m->getTexCoords(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
	glBindAttribLocation(shaderProgram, 1, "texCoord");

	GLuint boneIDVBO, boneWeightVBO;
	glGenBuffers(1, &boneIDVBO);
	glBindBuffer(GL_ARRAY_BUFFER, boneIDVBO);
	glBufferData(GL_ARRAY_BUFFER, m->getNumVertexBoneIDs() * sizeof(GLuint), m->getVertexBoneIDs(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribIPointer(2, 4, GL_INT, (4 * sizeof(GLuint)), (GLvoid*)0);
	glBindAttribLocation(shaderProgram, 2, "boneIDs");

	glGenBuffers(1, &boneWeightVBO);
	glBindBuffer(GL_ARRAY_BUFFER, boneWeightVBO);
	glBufferData(GL_ARRAY_BUFFER, m->getNumVertexBoneWeights() * sizeof(GLfloat), m->getVertexBoneWeights(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glBindAttribLocation(shaderProgram, 3, "boneWeights");
	
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m->getNumIndices() * sizeof(GLuint) , m->getIndices(), GL_STATIC_DRAW);
	
	
	
	indices_size = m->getNumIndices();
	//glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	//glBindVertexArray(0);
}

void GLManipulator::rotateCamera(GLfloat angle, bool xaxis, bool yaxis){
	cm->changeCameraRotation(angle, xaxis, yaxis);
}

void GLManipulator::moveCamera(std::string direction){
	cm->changeCameraMovement(direction);
}

void GLManipulator::setupTexture(){
	
	glGenTextures(1, &texture);
	
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	int width, height;
	unsigned char* image = SOIL_load_image("C:/martinka/libs/textura.png", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	
	glGenTextures(1, &dispMap);

	glBindTexture(GL_TEXTURE_2D, dispMap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	
	TIFF* tif = TIFFOpen("C:/martinka/libs/cone_vdm.tif", "r");
	TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &width);
	TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &height);
	unsigned char* data;
	data = (unsigned char*)_TIFFmalloc((tsize_t)(TIFFNumberOfStrips(tif) * TIFFStripSize(tif)));

	for (tstrip_t strip = 0; strip < TIFFNumberOfStrips(tif); strip++)
		TIFFReadEncodedStrip(tif, strip, data + strip * TIFFStripSize(tif), (tsize_t)-1);
	GLuint ndata = width*height;
	for (GLuint i = 0; i < ndata; i++) {
		register unsigned char *cp = (unsigned char *)&data[i];
		int t;

		t = cp[3];
		cp[3] = cp[0];
		cp[0] = t;
		t = cp[2];
		cp[2] = cp[1];
		cp[1] = t;
	}
	/*
	TIFF* tif = TIFFOpen("C:/martinka/libs/16bit_texture_vdm.tif", "r");
	if (tif) {
		uint32 w, h;
		size_t npixels;
		uint32* raster;

		TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &w);
		TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &h);
		npixels = w * h;
		raster = (uint32*)_TIFFmalloc(npixels * sizeof (uint32));
		if (raster != NULL) {
			if (TIFFReadRGBAImage(tif, w, h, raster, 0)) {
				
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, raster);
			}
			_TIFFfree(raster);
		}
		TIFFClose(tif);
	
	}*/
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data); //tiff to cita dajako naopak skontrolovat!
	//glGenerateMipmap(GL_TEXTURE_2D);

	
	TIFFClose(tif);

	
	
	glBindTexture(GL_TEXTURE_2D, 0);
}

void GLManipulator::stopAnimation(){
	if (animationStopped == true){
		animationStopped = false;
	}
	else
		animationStopped = true;
			
}