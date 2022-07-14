// ConsoleCpp.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>


#include <vscript.h>
#include <filesystem>
#include <vlexception.h>


#include <varBoolNode.h>


int main()
{

    std::string current_path = "C://Github//VisionLego//VisionLego//x64//Debug//";
    std::cout << "current execution path = " << current_path << std::endl;


    try {
        vl::vscript script;
        script.setAddonPath(current_path);
        script.loadLibrary();


        auto node1 = script.addNode("test1", vl::to_integer(vl::objectType::VL_BOOL));
        auto node2 = script.addNode("test2", vl::to_integer(vl::objectType::VL_BOOL));

        auto convertedNode1 = std::dynamic_pointer_cast<vl::varBoolNode>(node1);
        auto convertedNode2 = std::dynamic_pointer_cast<vl::varBoolNode>(node2);

        script.printNodeInfo();
        script.connect(convertedNode1->uid(), "output", convertedNode2->uid(), "input");
        script.printNodeInfo();
        //script.unloadLibrary();
    }
    catch (vl::exception e) {
        std::cout << e.what() << std::endl;
    }

}
