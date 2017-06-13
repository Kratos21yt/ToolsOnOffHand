#include <jni.h>
#include <dlfcn.h>
#include <android/log.h>
#include <stdlib.h>
#include <Substrate.h>

#include "ItemInstance.h"

bool (*_isOffhandItem)(ItemInstance*);
bool isOffhandItem(ItemInstance* item){
	const int TOOLS_SIZE = 27;
	int tools[TOOLS_SIZE] = {256, 257, 258, 259, 261, 267, 268, 269, 270, 271, 272, 273, 274, 275, 276, 277, 278, 279, 283, 284, 285, 286, 290, 291, 292, 293};
	
	for(int i = 0; i < TOOLS_SIZE; i++){
		if(item->getId() == tools[i]){
			return true;
		}
	}
	return _isOffhandItem(item);
}

#define hook(a,b,c) MSHookFunction((void*)&a,(void*)&b,(void**)&c);

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved) {
	hook(ItemInstance::isOffhandItem,isOffhandItem,_isOffhandItem);
	return JNI_VERSION_1_2;
}
