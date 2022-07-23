// ConsoleCpp.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <filesystem>
#include <chrono>
#include <vscript.h>
#include <vlexception.h>
#include <varBoolNode.h>
#include <constBoolNode.h>
#include <condIfNode.h>


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




        auto node9 = script.addNode("test8", vl::to_integer(vl::objectType::VL_BOOL));
        auto node10 = script.addNode("test8", vl::to_integer(vl::objectType::VL_BOOL));
        auto node11 = script.addNode("test8", vl::to_integer(vl::objectType::VL_BOOL));


        auto node12 = script.addNode("test8", vl::to_integer(vl::objectType::VL_BOOL));
        auto node13 = script.addNode("test8", vl::to_integer(vl::objectType::VL_BOOL));
        auto node14 = script.addNode("test8", vl::to_integer(vl::objectType::VL_BOOL));


        auto node15 = script.addNode("test8", vl::to_integer(vl::objectType::VL_BOOL));
        auto node16 = script.addNode("test8", vl::to_integer(vl::objectType::VL_BOOL));
        auto node17 = script.addNode("test8", vl::to_integer(vl::objectType::VL_BOOL));


        auto node19 = script.addNode("test8", vl::to_integer(vl::objectType::VL_BOOL));
        auto node20 = script.addNode("test8", vl::to_integer(vl::objectType::VL_BOOL));
        auto node21 = script.addNode("test8", vl::to_integer(vl::objectType::VL_BOOL));



        auto node30 = script.addNode("test8", vl::to_integer(vl::objectType::VL_IF));
        node30->addInCondition("if", node21);


       

        script.connect(node1, "output", node9, "input");
        script.connect(node1, "output", node10, "input");
        script.connect(node1, "output", node11, "input");





        script.connect(node2, "output", node12, "input");
        script.connect(node2, "output", node13, "input");
        script.connect(node2, "output", node14, "input");



        script.connect(node3, "output", node4, "input");
        script.connect(node3, "output", node15, "input");
        script.connect(node3, "output", node16, "input");
        script.connect(node3, "output", node17, "input");


        script.connect(node3, "output", node19, "input");
        script.connect(node3, "output", node20, "input");
        script.connect(node3, "output", node21, "input");


        script.printNodeInfo();
        script.setMaxTaskCount(4);


        


        script.save("C://Github//test//test.txt");
        script.load(script.serialization(), vl::contextType::json);
        script.save("C://Github//test//test2.txt");



        script.printNodeInfo();


        std::chrono::steady_clock::time_point begin;
        std::chrono::steady_clock::time_point end;

        begin = std::chrono::steady_clock::now();
        script.run(vl::syncType::serial);
        end = std::chrono::steady_clock::now();
        auto elapseTime = std::chrono::duration_cast<std::chrono::seconds>(end - begin).count();
        std::cout << "serial processing time = " << elapseTime << std::endl;



        begin = std::chrono::steady_clock::now();
        script.run(vl::syncType::parallel);
        end = std::chrono::steady_clock::now();
        elapseTime = std::chrono::duration_cast<std::chrono::seconds>(end - begin).count();
        std::cout << "parallel processing time = " << elapseTime << std::endl;


       


    }
    catch (vl::exception e) {
        std::cout << e.what() << std::endl;
    }

}
