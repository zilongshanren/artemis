#ifndef __CC_RESOURCEINFO_CACHE_H__
#define __CC_RESOURCEINFO_CACHE_H__

#include <map>
#include <vector>
#include <string>

#include "ccTypes.h" 
#include "cocoa/CCString.h"
#include "cocoa/CCDictionary.h"
#include "cocoa/CCArray.h"
#include "cocoa/CCString.h"
#include "platform/CCPlatformMacros.h"
#include <memory>

NS_CC_BEGIN

class CC_DLL ResourceInfo
{
public:
    ResourceInfo();
    virtual ~ResourceInfo();
    ResourceInfo(const std::string& strFormater);    
    ResourceInfo(int type, const char* fileName);

    std::string toString() const;
    
public:
    int  _type;
    std::string _fileName;
    bool _isCached;
    int _usedCount;
};

typedef std::shared_ptr<ResourceInfo> ResourceInfoPtr;
typedef std::vector<ResourceInfoPtr> ResourceInfoVector;
typedef std::map<std::string, ResourceInfoPtr> ResourceInfoMap;

/** 
 * @brief a Delegate about how the ResourceInfo load and cache.
 * @date 2012年12月14日 15:08:56
 */
class ResourceInfoCacheDelegate : public cocos2d::Object
{
public:

    virtual void cache(std::string& strResFileName, std::string& strExtension, ResourceInfo& targetInfo) = 0;
    virtual void load(ResourceInfo* pInfo) = 0;
    virtual void removeUnusedResourceInfo() = 0;
};

/** 
 * @brief cache the game ResourceInfo list.
 * 
 * @author zwb
 * @date 2012年12月7日 11:29:02
 */
class CC_DLL ResourceInfoCache 
{
private:

    ResourceInfoCache();

public:
    virtual ~ResourceInfoCache();

    static ResourceInfoCache* getInstance();
    void initialize(bool bDisableCache);
   const ResourceInfoMap& getResourceInfoMap() const;
   void setDelegate(ResourceInfoCacheDelegate* pDelegate);
   void cache(std::string& strResFileName, std::string& strExtension, ResourceInfo& targetInfo);
    void save();
    void load();    

private:

    void doSave(const char* pszFileName, const ResourceInfoMap& setResourceInfo);
    void doLoad(const char* pszFileName, ResourceInfoMap& setResourceInfo);
    CC_SYNTHESIZE(bool, m_bIsCacheEnable, IsCacheEnable);

private:

    bool m_bIsDirty;
    ResourceInfoMap m_mapResourceInfo;
    ResourceInfoCacheDelegate* m_pDelegate;
    std::string m_strFileName;
    bool m_bDisableCache;
};

NS_CC_END
#endif