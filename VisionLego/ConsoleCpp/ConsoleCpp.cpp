// ConsoleCpp.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>


#include <vscript.h>
#include <filesystem>
#include <vlexception.h>

int main()
{

    std::string current_path = "C://Github//VisionLego//VisionLego//x64//Debug//";
    std::cout << "current execution path = " << current_path << std::endl;


    try {
        vl::vscript script;
        script.setAddonPath(current_path);
        script.loadLibrary();
        script.unloadLibrary();
    }
    catch (vl::exception e) {
        std::cout << e.what() << std::endl;
    }

}
