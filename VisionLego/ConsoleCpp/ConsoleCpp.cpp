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

    std::string current_path = "C://Github//VisionLego//VisionLego//x64//Release//";
    std::cout << "current execution path = " << current_path << std::endl;



    try {
        vl::vscript script;
        script.setAddonPath(current_path);
        script.loadLibrary();


        auto node1 = script.addNode("test1", vl::to_integer(vl::objectType::VL_BOOL));
        auto node2 = script.addNode("test2", vl::to_integer(vl::objectType::VL_BOOL));
        auto node3 = script.addNode("test3", vl::to_integer(vl::objectType::VL_BOOL));
        auto node4 = script.addNode("test4", vl::to_integer(vl::objectType::VL_BOOL));
        auto node5 = script.addNode("test5", vl::to_integer(vl::objectType::VL_BOOL));
        auto node6 = script.addNode("test6", vl::to_integer(vl::objectType::VL_BOOL));
        auto node7 = script.addNode("test7", vl::to_integer(vl::objectType::VL_BOOL));
        auto node8 = script.addNode("test8", vl::to_integer(vl::objectType::VL_BOOL));
        auto node9 = script.addNode("test9", vl::to_integer(vl::objectType::VL_BOOL));
        auto node10 = script.addNode("test10", vl::to_integer(vl::objectType::VL_BOOL));
        auto node11 = script.addNode("test11", vl::to_integer(vl::objectType::VL_BOOL));
        auto node12 = script.addNode("test12", vl::to_integer(vl::objectType::VL_BOOL));
        auto node13 = script.addNode("test13", vl::to_integer(vl::objectType::VL_BOOL));
        auto node14 = script.addNode("test14", vl::to_integer(vl::objectType::VL_BOOL));
        auto node15 = script.addNode("test15", vl::to_integer(vl::objectType::VL_BOOL));
        auto node16 = script.addNode("test16", vl::to_integer(vl::objectType::VL_BOOL));
        auto node17 = script.addNode("test17", vl::to_integer(vl::objectType::VL_BOOL));
        auto node18 = script.addNode("test18", vl::to_integer(vl::objectType::VL_BOOL));
        auto node19 = script.addNode("test19", vl::to_integer(vl::objectType::VL_BOOL));
        auto node20 = script.addNode("test20", vl::to_integer(vl::objectType::VL_BOOL));



        script.connect(node1->uid(), "output", node2->uid(), "input");
        script.connect(node2->uid(), "output", node3->uid(), "input");
        script.connect(node3->uid(), "output", node4->uid(), "input");
        script.connect(node4->uid(), "output", node5->uid(), "input");
        script.connect(node5->uid(), "output", node6->uid(), "input");
        script.connect(node6->uid(), "output", node7->uid(), "input");
        script.connect(node7->uid(), "output", node8->uid(), "input");
        script.connect(node8->uid(), "output", node9->uid(), "input");
        script.connect(node9->uid(), "output", node10->uid(), "input");
        script.connect(node10->uid(), "output", node11->uid(), "input");
        script.connect(node11->uid(), "output", node12->uid(), "input");
        script.connect(node12->uid(), "output", node13->uid(), "input");
        script.connect(node13->uid(), "output", node14->uid(), "input");
        script.connect(node14->uid(), "output", node15->uid(), "input");
        script.connect(node15->uid(), "output", node16->uid(), "input");
        script.connect(node16->uid(), "output", node17->uid(), "input");
        script.connect(node17->uid(), "output", node18->uid(), "input");
        script.connect(node18->uid(), "output", node19->uid(), "input");
        script.connect(node19->uid(), "output", node20->uid(), "input");
      
        script.verification();

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
