// ConsoleCpp.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>



#include <filesystem>
#include <chrono>

#include <vscript.h>
#include <vlexception.h>
#include <varBoolNode.h>
#include <constBoolNode.h>


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
        auto node3 = script.addNode("test3", vl::to_integer(vl::objectType::VL_BOOL));
        auto node4 = script.addNode("test4", vl::to_integer(vl::objectType::VL_BOOL));

        script.printNodeInfo();

        script.connect(node1, "output", node2, "input");
        script.connect(node2, "output", node3, "input");
        script.connect(node3, "flowOut", node4, "flowIn");


        script.printNodeInfo();

      
        script.verification();


        auto node5 = script.addNode("test5", vl::to_integer(vl::objectType::VL_BOOL));
        script.connect(node4, "flowOut", node5, "flowIn");



        script.printNodeInfo();

        script.run();



        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        int fps = 0;
        while(true) {
            script.run();
            fps++;
            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

            auto elapseTime =  std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

            if (elapseTime > 1000) {
                std::cout << "fps = " << fps << std::endl;
                begin = std::chrono::steady_clock::now();
                fps = 0;
            }

        }





    }
    catch (vl::exception e) {
        std::cout << e.what() << std::endl;
    }

}
