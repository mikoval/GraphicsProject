#include <Shaders/ShaderManager.h>
#include <Shaders/Phong/PhongShader.h>
#include <Shaders/Phong/BlinnPhongShader.h>
#include <Shaders/Phong/PhongInstanceShader.h>
#include <Shaders/Color/ColorShader.h>
#include <Shaders/CubeMap/CubeMapShader.h>
#include <Shaders/TextureShaders/DisplayImageShader.h>
#include <Shaders/TextureShaders/BlurImageShader.h>
#include <Shaders/Shadows/ShadowShader.h>
#include <Shaders/Text/TextShader.h>


#include <string>
#include <fstream>
#include <streambuf>
#include <regex>

ShaderManager shaders = ShaderManager();

static GLuint PhongShader = 0;
static GLuint BlinnPhongShader = 0;
static GLuint PhongInstanceShader = 0;
static GLuint ColorShader = 0;
static GLuint CubeMapShader = 0;
static GLuint DisplayImageShader = 0;
static GLuint BlurImageShader = 0;
static GLuint ShadowShader = 0;
static GLuint TextShader = 0;


ShaderManager::ShaderManager(){
	cout << "CONSTRUCITNG SHADER MANAGER" << endl;

}

GLuint* ShaderManager::LoadShader(string shader) {
	if(shader == "PhongShader") {
		if(!PhongShader){
			PhongShader = CreatePhongShader();
		}
		return &PhongShader;
	} else if(shader == "BlinnPhongShader") {
		if(!BlinnPhongShader){
			BlinnPhongShader = CreateBlinnPhongShader();
		}
		return &BlinnPhongShader;
	} else if(shader == "ColorShader") {
		if(!ColorShader){
			ColorShader = CreateColorShader();
		}
		return &ColorShader;
	}
	else if(shader == "CubeMapShader") {
		if(!CubeMapShader){
			CubeMapShader = CreateCubeMapShader();
		}
		return &CubeMapShader;
	}
	else if(shader == "PhongInstanceShader") {
		if(!PhongInstanceShader){
			PhongInstanceShader = CreatePhongInstanceShader();
		}
		return &PhongInstanceShader;
	}
	else if(shader == "DisplayImageShader") {
		if(!DisplayImageShader){
			DisplayImageShader = CreateDisplayImageShader();
		}
		return &DisplayImageShader;
	}
	else if(shader == "BlurImageShader") {
		if(!BlurImageShader){
			BlurImageShader = CreateBlurImageShader();
		}
		return &BlurImageShader;
	}
	else if(shader == "ShadowShader") {
		if(!ShadowShader){
			ShadowShader = CreateShadowShader();
		}
		return &ShadowShader;
	}
	else if(shader == "TextShader") {
		if(!TextShader){
			TextShader = CreateTextShader();
		}
		return &TextShader;
	}
	else {
		assert(false);
	}

	return 0;
}

string loadShader(string path) {
	cout << path << endl;
	path = "include/Rasterizer/Shaders/" + path;
	ifstream t(path);
	string str((std::istreambuf_iterator<char>(t)),
                 std::istreambuf_iterator<char>());

    regex r("#include\\(\"([a-z]|[A-Z])*.shx\"\\)"); 
    smatch m;

    while(std::regex_search(str, m, r)){
	    string s = m[0];
	    int first = s.find("\"");
	    int second = s.find("\"", first + 1);
	    string part_path = s.substr(first + 1, second - first - 1);
	    
	    string part_path_full = "include/Rasterizer/Shaders/ShaderParts/" + part_path;
		ifstream t2(part_path_full);
		string str2((std::istreambuf_iterator<char>(t2)),
	                 std::istreambuf_iterator<char>());


		int pos = str.find(s);

		str.replace(pos, s.size(), str2);
	   	
    }




	return str;
}