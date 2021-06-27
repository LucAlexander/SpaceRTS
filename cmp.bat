cls
g++ -std=c++17 generator.cpp generator.h rnd.cpp rnd.h utils.cpp utils.h entity.cpp entity.h entityHandler.cpp entityHandler.h textureTable.cpp textureTable.h point.cpp point.h planet.cpp planet.h unit.cpp unit.h partition.cpp partition.h triangulation.cpp triangulation.h regionMapping.cpp regionMapping.h -o run -IC:\codeProjects\nationGenerator\SFML-2.5.1\include -LC:\codeProjects\nationGenerator\SFML-2.5.1\lib -DSFML_STATIC -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32

