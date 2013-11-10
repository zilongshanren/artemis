LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := artemis_static

LOCAL_MODULE_FILENAME := libartemis

LOCAL_SRC_FILES := \
src/Component.cpp \
src/ComponentType.cpp \
src/ComponentTypeManager.cpp \
src/DelayedEntityProcessingSystem.cpp \
src/DelayedEntitySystem.cpp \
src/Entity.cpp \
src/EntityManager.cpp \
src/EntityProcessingSystem.cpp \
src/EntitySystem.cpp \
src/GroupManager.cpp \
src/SystemBitManager.cpp \
src/SystemManager.cpp \
src/TagManager.cpp \
src/World.cpp

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH) \
                    $(LOCAL_PATH)/include

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
                    $(LOCAL_PATH)/include

include $(BUILD_STATIC_LIBRARY)