#include "Engine.h"
#include "Scene1.h"
#include "Scene3.h"
#include "imgui/imgui.h"
#include "imgui-sfml/imgui-SFML.h"

#include <tinyxml/tinyxml.h>

int main()
{
    Engine game;
    //base conf init

    CORE_Config conf;

    //conf init from file
    std::string filename = "Config.xml";
    TiXmlDocument config_file;
    if (!config_file.LoadFile(filename.c_str()))
    {
        TiXmlDeclaration* decl = new TiXmlDeclaration("1.0", "utf-8", "");
        config_file.LinkEndChild(decl);

        TiXmlElement* root = new TiXmlElement("config");
        config_file.LinkEndChild(root);
        root->SetAttribute("app", "SF");

        TiXmlElement* param = new TiXmlElement("param");
        root->LinkEndChild(param);
        param->SetAttribute("width", 1366);

        param = new TiXmlElement("param");
        root->LinkEndChild(param);
        param->SetAttribute("height", 768);

        param = new TiXmlElement("param");
        root->LinkEndChild(param);
        param->SetAttribute("v_sync", 0);

        param = new TiXmlElement("param");
        root->LinkEndChild(param);
        param->SetAttribute("frame_limit", 30);

        param = new TiXmlElement("param");
        root->LinkEndChild(param);
        param->SetAttribute("full_screen", 0);

        config_file.SaveFile(filename.c_str());
    }

        TiXmlElement* root;
        root = config_file.FirstChildElement("config");
        conf.app_name = root->Attribute("app");

        TiXmlElement* param;

        param = root->FirstChildElement("param");
        conf.width = atoi(param->Attribute("width"));

        param = param->NextSiblingElement("param");
        conf.height = atoi(param->Attribute("height"));

        param = param->NextSiblingElement("param");
        conf.v_sync = atoi(param->Attribute("v_sync"));

        param = param->NextSiblingElement("param");
        conf.frame_limit = atoi(param->Attribute("frame_limit"));

        param = param->NextSiblingElement("param");
        conf.full_screen = atoi(param->Attribute("full_screen"));

    //init
    game.init(&conf);

    //load scene
    game._push(new SceneOne(&game));
    //game._push(new SceneThree(&game));

    //core
    game.core();

    //cleanup
    game.cleanup();

    system("Pause");
    return EXIT_SUCCESS;
}