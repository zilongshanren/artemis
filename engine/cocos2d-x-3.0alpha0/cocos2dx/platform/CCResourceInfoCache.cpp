#include "CCResourceInfoCache.h"

#include <vector>
#include <string> 

#include "cocoa/CCArray.h"
#include "cocoa/CCString.h"
#include "platform/CCFileUtils.h"
#include "textures/CCTexture2D.h"
#include "textures/CCTextureCache.h"

NS_CC_BEGIN

ResourceInfo::ResourceInfo()
: _type(0)
, _fileName("")
, _isCached(false)
{

}

// dtor
ResourceInfo::~ResourceInfo()
{

}


ResourceInfo::ResourceInfo( int nType, const char* pszFileName)
    : _type(nType)
    , _fileName(pszFileName)
    , _isCached(false)
{
}


ResourceInfo::ResourceInfo( const std::string& strFormater )
{
    // format: "type(int);fileName(string);bLanguageRelative(bool)"
    std::vector<std::string> vecValue;
    size_t start = 0;
    size_t pos = 0;

    // get the ResourceInfo's data vector
    for(unsigned int i = 0; ; ++i)
    {
        if( pos == strFormater.npos )
        {
            break;
        }

        pos = strFormater.find_first_of(';', start);
        vecValue.push_back(strFormater.substr(start, pos - start ));
        start = pos + 1;
    }
    CCAssert(vecValue.size() == 4, "data format error.");

    // convert to variables
    this->_type = atoi(vecValue[0].c_str());
    this->_fileName = vecValue[1];
}

// ctor
ResourceInfoCache::ResourceInfoCache() 
    : m_bIsDirty(false)
    , m_bIsCacheEnable(false)
    , m_pDelegate(NULL)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    this->m_strFileName = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("resourceCache.xml");
#else
    this->m_strFileName = "resourceCache.xml";
#endif
}


// dtor
ResourceInfoCache::~ResourceInfoCache()
{ 
}


// a singleton
ResourceInfoCache* ResourceInfoCache::getInstance()
{
    static ResourceInfoCache s_cache;
    return &s_cache;
}


// initialize the CCResourceInfoCache
void ResourceInfoCache::initialize( bool bDisableCache )
{
    static bool s_bIsInited = false;
    if ( false == s_bIsInited )
    {
        CCLOG("disable CCResourceInfoCache: %d", bDisableCache);
        this->m_bDisableCache = bDisableCache;
        this->load();
        s_bIsInited = true;
    }
}


const ResourceInfoMap& ResourceInfoCache::getResourceInfoMap() const
{
    return m_mapResourceInfo;
}


// set a delegate to do cache and load.
void ResourceInfoCache::setDelegate( ResourceInfoCacheDelegate* pDelegate )
{
    m_pDelegate = pDelegate;
}


// insert the new ResourceInfo to list 
void ResourceInfoCache::cache( std::string& strResFileName, std::string& strExtension, ResourceInfo& info )
{
    if (m_bIsCacheEnable && m_pDelegate && false == m_bDisableCache)
    {
        CCLOG("%s(%d)", __FUNCTION__, __LINE__);
        m_pDelegate->cache(strResFileName, strExtension, info);
        if (0 != info._type)
        {
            ResourceInfoPtr info_old = m_mapResourceInfo[info._fileName];
            if (0 != info_old->_type)
            {
                // add the old info's weight to the new info.
            //    info.addWeight(*info_old);
            }
       //     m_mapResourceInfo[info.m_resFileName] = info;
            m_bIsDirty = true;
        }
    }
    else
    {
        info._isCached = true;
    }
}

// save the list
void ResourceInfoCache::save()
{ 
    // save the ResourceInfo
    if (m_bIsDirty && false == m_bDisableCache)
    {
        this->doSave(m_strFileName.c_str(), m_mapResourceInfo);
    }
    m_bIsDirty = false;
}


// load the list
void ResourceInfoCache::load()
{
    this->doLoad(m_strFileName.c_str(), m_mapResourceInfo);
}


//  do Save the xml file. 
void ResourceInfoCache::doSave( const char* pszFileName, const ResourceInfoMap& mapResourceInfo )
{
}


// do Load the xml file.
void ResourceInfoCache::doLoad( const char* pszFileName, ResourceInfoMap& mapResourceInfo)
{
    bool bOldNotify = FileUtils::getInstance()->isPopupNotify();
    FileUtils::getInstance()->setPopupNotify(false);

	// 测试用的假数据 
	m_mapResourceInfo["effect_1"] = ResourceInfoPtr(new ResourceInfo(3, "resource_cache_test/music/effect_1.ogg"));
	m_mapResourceInfo["effect_2"] = ResourceInfoPtr(new ResourceInfo(3, "resource_cache_test/music/effect_2.ogg"));
	m_mapResourceInfo["effect_3"] = ResourceInfoPtr(new ResourceInfo(3, "resource_cache_test/music/effect_3.ogg"));
	m_mapResourceInfo["effect_4"] = ResourceInfoPtr(new ResourceInfo(3, "resource_cache_test/music/effect_4.ogg"));
	m_mapResourceInfo["effect_5"] = ResourceInfoPtr(new ResourceInfo(3, "resource_cache_test/music/effect_5.ogg"));

	m_mapResourceInfo["bgm_1"] = ResourceInfoPtr(new ResourceInfo(4, "resource_cache_test/music/bgm_1.ogg"));
	m_mapResourceInfo["bgm_2"] = ResourceInfoPtr(new ResourceInfo(4, "resource_cache_test/music/bgm_2.ogg"));
	m_mapResourceInfo["bgm_3"] = ResourceInfoPtr(new ResourceInfo(4, "resource_cache_test/music/bgm_3.ogg"));

    FileUtils::getInstance()->setPopupNotify(bOldNotify);
}

NS_CC_END