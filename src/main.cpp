#include  <jni.h>
#include <cstdlib>
#include <stdio.h>
#include <windows.h>
#include "../includes/QuickUnionModel.hpp"

/*typedef struct JavaVMInitArgs{
    jint version; //version cannot be less than JNI_VERSION_1_2
    jint nOptions;  // number of options passed to JVM
    JavaVMOption *options; //pointer to an array of JavaVMOption structure
    jboolean ignoreUnrecognized;
} JavaVMInitArgs;

typedef struct JavaVMOption{
    char* optionString; //indicate the default platform encoding for JVM
    void *extraInfo; //represent function hook for redirecting JVM message, a JVM abort hook or a JVM exit hook
} JavaVMOption;
*/

#ifdef _WIN32
#define PATH_SEPARATOR ';'
#else
#define PATH_SEPARATOR ':'
#endif

void loadJVM(){
    JavaVMOption jvmopt[1];
    jvmopt[0].optionString = const_cast<char*>("Djava.class.path=C:\\Users\\Hebronace\\Desktop\\c++\\alogrithms\\network\\java\\MyTest.class");
    JavaVMInitArgs vmArgs;
    vmArgs.version = JNI_VERSION_1_2;
    vmArgs.nOptions = 1; 
    vmArgs.options = jvmopt;
    vmArgs.ignoreUnrecognized = JNI_TRUE;

    
    JavaVM *jvm;
    JNIEnv *env;
    long flag = JNI_CreateJavaVM(&jvm,(void**)&env,&vmArgs);
    if(flag == JNI_ERR){
        std::cout  << "Error creating VM. exiting....." << std::endl;
        exit(EXIT_FAILURE);
    }

    printf("JVM loaded succesfully : version %d", env->GetVersion());
    std::cout << ((env->GetVersion() >> 16) & 0x0f) << "." << (env->GetVersion() & 0x0f) << std::endl;
     /**
     *  =============================================================
     *                  C++ CODE USING JVM 
     * ==============================================================
     */
    
    jclass cls = env->FindClass("MyTest");
    if (cls == nullptr)
    {
        std::cerr << "Error: class not found" << std::endl;
        goto destroy;
    }
    else
    {
        std::cout << "Class MyTest found" << std::endl;
        jmethodID mid = env->GetStaticMethodID(cls, "hello", "()V"); // find method
        if (mid == nullptr)
            std::cerr << "ERROR: method void hello() not found !" << std::endl;
        else
        {
            env->CallStaticVoidMethod(cls, mid); // call method
            if(env->ExceptionCheck()){
                env->ExceptionDescribe();
                env->ExceptionClear();
            }
            std::cout << std::endl;
            goto destroy;
        }
    }

    destroy:
        env->ExceptionDescribe();
        jvm->DestroyJavaVM();

}

int main(int argc, char const *argv[])
{
    // std::string file = "C:\\Users\\Hebronace\\Desktop\\c++\\alogrithms\\network\\src\\data.txt";
    // reader(file);
    loadJVM();
    return 0;
}
