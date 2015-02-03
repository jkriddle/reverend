#include <iostream>
#include <sstream>
#include <noise\noise.h>
#include "..\noise\noiseutils.h"
#include <SDL\SDL.h>

class MapRenderer {

public:

	void renderToFile(noise::utils::NoiseMap noiseMap, std::string fileName) {
		noise::utils::RendererImage renderer;
		noise::utils::Image image;
		renderer.SetSourceNoiseMap(noiseMap);
		renderer.SetDestImage(image);
		renderer.ClearGradient();
		
		/*
		renderer.AddGradientPoint (-1.0000, utils::Color (  0,   0, 128, 255)); // deeps
		renderer.AddGradientPoint (-0.2500, utils::Color (  0,   0, 255, 255)); // shallow
		renderer.AddGradientPoint ( 0.0000, utils::Color (  0, 128, 255, 255)); // shore
		renderer.AddGradientPoint ( 0.0625, utils::Color (240, 240,  64, 255)); // sand
		renderer.AddGradientPoint ( 0.1250, utils::Color ( 32, 160,   0, 255)); // grass
		renderer.AddGradientPoint ( 0.3750, utils::Color (224, 224,   0, 255)); // dirt
		renderer.AddGradientPoint ( 0.7500, utils::Color (128, 128, 128, 255)); // rock
		renderer.AddGradientPoint ( 1.0000, utils::Color (255, 255, 255, 255)); // snow
		*/

		renderer.AddGradientPoint( -1.0, utils::Color (  0,   0, 0, 255));
		renderer.AddGradientPoint( 1.0, utils::Color (255, 255, 255, 255));
		
		renderer.Render();
		utils::WriterBMP writer;
		writer.SetSourceImage(image);
		writer.SetDestFilename(fileName.c_str());
		writer.WriteDestFile();
	}
	
	void renderToMemory(noise::utils::NoiseMap noiseMap, std::ostringstream &mem) {
		noise::utils::RendererImage renderer;
		noise::utils::Image image;
		renderer.SetSourceNoiseMap(noiseMap);
		renderer.SetDestImage(image);
		renderer.ClearGradient();
		
		/*
		renderer.AddGradientPoint (-1.0000, utils::Color (  0,   0, 128, 255)); // deeps
		renderer.AddGradientPoint (-0.2500, utils::Color (  0,   0, 255, 255)); // shallow
		renderer.AddGradientPoint ( 0.0000, utils::Color (  0, 128, 255, 255)); // shore
		renderer.AddGradientPoint ( 0.0625, utils::Color (240, 240,  64, 255)); // sand
		renderer.AddGradientPoint ( 0.1250, utils::Color ( 32, 160,   0, 255)); // grass
		renderer.AddGradientPoint ( 0.3750, utils::Color (224, 224,   0, 255)); // dirt
		renderer.AddGradientPoint ( 0.7500, utils::Color (128, 128, 128, 255)); // rock
		renderer.AddGradientPoint ( 1.0000, utils::Color (255, 255, 255, 255)); // snow
		*/

		renderer.AddGradientPoint( -1.0, utils::Color (  0,   0, 0, 255));
		renderer.AddGradientPoint( 1.0, utils::Color (255, 255, 255, 255));
		
		renderer.Render();
		utils::WriterBMP writer;
		writer.SetSourceImage(image);
		writer.WriteToMemory(mem);
	}

private:

};