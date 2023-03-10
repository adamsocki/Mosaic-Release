#define TINYOBJLOADER_IMPLEMENTATION
//#include <iostream> 
#include "tiny_obj_loader.h"



void TinyObject()
{
    std::string inputfile = "cornell_box.obj";
    tinyobj::ObjReaderConfig reader_config;
    reader_config.mtl_search_path = "./"; // Path to material files

    tinyobj::ObjReader reader;

    if (!reader.ParseFromFile(inputfile, reader_config)) 
    {
        if (!reader.Error().empty()) 
        {
          std::cerr << "TinyObjReader: " << reader.Error();
        }
            exit(1);
    }

    if (!reader.Warning().empty()) 
    {
        std::cout << "TinyObjReader: " << reader.Warning();
    }


    auto& attrib = reader.GetAttrib();
    auto& shapes = reader.GetShapes();
    auto& materials = reader.GetMaterials();
}