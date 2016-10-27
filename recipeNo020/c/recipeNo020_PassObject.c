#include <stdio.h>
#include "jni.h"
#include "recipeNo020_PassObject.h"

JNIEXPORT void JNICALL Java_recipeNo020_PassObject_displayObject
  (JNIEnv *env, jclass obj, jobject objarg) {
	
	/* Get objarg's class - objarg is the one we pass from
           Java */
	jclass cls = (*env)->GetObjectClass(env, objarg);

	/* For accessing primitive types from class use
           following field descriptors

           +---+---------+
           | Z | boolean |
           | B | byte    |
           | C | char    |
           | S | short   |
           | I | int     |
           | J | long    |
           | F | float   |
           | D | double  |
           +-------------+
	*/

	/* Get int field 

	   Take a look here, we are passing char* with 
           field descriptor - e.g. "I" => int 
        */
	jfieldID fidInt = (*env)->GetFieldID(env, cls, "iVal", "I");
	jint iVal = (*env)->GetIntField(env, objarg, fidInt);
	printf("iVal: %d\n", iVal);

	/* Get double field */
	jfieldID fidDouble = (*env)->GetFieldID(env, cls, "dVal", "D");
        jdouble dVal = (*env)->GetIntField(env, objarg, fidDouble);
        printf("dVal: %f\n", dVal);

	/* Get boolean field */
        jfieldID fidBoolean = (*env)->GetFieldID(env, cls, "bVal", "Z");
        jboolean bVal = (*env)->GetIntField(env, objarg, fidBoolean);
        printf("bVal: %d\n", bVal);	

	/* Get character field */
	jfieldID fidChar = (*env)->GetFieldID(env, cls, "cVal", "C");
        jboolean cVal = (*env)->GetIntField(env, objarg, fidChar);
        printf("cVal: %c\n", cVal);

	/* Get String field */
        jfieldID fidString = (*env)->GetFieldID(env, cls, "sVal", "Ljava/lang/String;");
        jobject sVal = (*env)->GetObjectField(env, objarg, fidString);

        // we have to get string bytes into C string
        const char *c_str;
        c_str = (*env)->GetStringUTFChars(env, sVal, NULL);
  	if(c_str == NULL) {
    		return;
  	}
 
  	printf("sVal: %s\n", c_str);
 
  	// after using it, remember to release the memory
  	(*env)->ReleaseStringUTFChars(env, sVal, c_str);

	/* Get OtherClass */
	jfieldID fidOtherClass = (*env)->GetFieldID(env, cls, "oVal", "LrecipeNo020/OtherClass;");
        jobject oVal = (*env)->GetObjectField(env, objarg, fidOtherClass);

	jclass clsOtherClass = (*env)->GetObjectClass(env, oVal);

	/* Once we have OtherClass class and OtherClass object
	   we can access OtherClass'es components
        */

	/* Get String field from OtherClass */
        jfieldID fidStringOtherClass = (*env)->GetFieldID(env, clsOtherClass, "sVal", "Ljava/lang/String;");
        jobject sValOtherClass = (*env)->GetObjectField(env, oVal, fidStringOtherClass);

        // we have to get string bytes into C string
        const char *c_str_oc;
        c_str_oc = (*env)->GetStringUTFChars(env, sValOtherClass, NULL);
        if(c_str_oc == NULL) {
                return;
        }

        printf("OtherClass.sVal: %s\n", c_str_oc);

        // after using it, remember to release the memory
        (*env)->ReleaseStringUTFChars(env, sValOtherClass, c_str_oc);	
}