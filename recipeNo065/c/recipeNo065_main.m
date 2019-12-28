#include <stdio.h>
#include "jni.h"
#import <Foundation/Foundation.h>

int main(int argc, const char * argv[]) {
  @autoreleasepool {
  
    JNIEnv *env;
    JavaVM *jvm;
    JavaVMInitArgs vm_args;
    JavaVMOption options[3];         // Make sure to prepare array of arguments
                                     // for as many arguments as you want to pass
  
    // This one (java.class.path) is hardcoded, but I guess we could 
    // make something better here. I simply assume that in sample codes
    // main function will be called either from lib or from root directory
    // of given sample code. It's possible to use some env variables here
    // or to pass this value to main, but I don't care.
    // This is just a sample.
      
    NSString *home = [[[NSProcessInfo processInfo]environment]objectForKey:@"HOME"];
    options[0].optionString = (char *)[[NSString stringWithFormat: @"-Djava.class.path=%@/workspace/jnicookbook/recipeNo065/target", home] UTF8String];
  
    // if you want, you can pass additional parameters for JVM following way
    //options[1].optionString = "-verbose:jni";
  
    // checking JNI related issues
    //options[2].optionString = "-Xcheck:jni";
  
    vm_args.options = options;
    vm_args.ignoreUnrecognized = 0;
    vm_args.version = JNI_VERSION_1_8;
    vm_args.nOptions = 1;           // in case you are passing additional
                                    // arguments for JVM, make sure to update
                                    // the number of arguments here
  
    // I don't care about supper duper error handling here
    // in case we can't make it to create JVM. If JVM fails, just boil down.
    int status = JNI_CreateJavaVM (&jvm, (void **) &env, &vm_args);
    if (status < 0 || !env) {
      printf ("Error - JVM creation failed\n");
      return 1;
    }
  
    // This is the place where we are looking for class
    // and it's method - "displayMessage".
    jclass cls_Main = (*env)->FindClass (env, "recipeNo065/Main");
    
    // This is the place where we call the method "displayMessage"
    jmethodID method_displayMessage = (*env)->GetStaticMethodID (env, cls_Main, "displayMessage", "()V");
    (*env)->CallStaticVoidMethod(env, cls_Main, method_displayMessage);
  
    // and we are done
    (*jvm)->DestroyJavaVM( jvm );
  }
  
}

