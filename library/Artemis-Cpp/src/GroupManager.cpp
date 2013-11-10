#include "GroupManager.h"
#include "Entity.h"

namespace artemis {
	GroupManager::GroupManager() : empty_bag(1) {
		empty_string.clear();
	}

	ImmutableBag<Entity*> * GroupManager::getEntities(std::string group) {
		auto bag = entitiesByGroup[group];
		if(bag == NULL) {
			// create a new empty group
			bag = new Bag<Entity*>(32);
			entitiesByGroup[group] = bag;
		}
		return bag;
	}

	std::string GroupManager::getGroupOf(Entity& e) {
		if(e.getId() < groupByEntity.getCapacity()){
			auto group = groupByEntity.get(e.getId());
			if(group == NULL) 
				return empty_string;
			return  *group;
		}
		return empty_string;
	}

	bool GroupManager::isGrouped(Entity& e) {
		return !getGroupOf(e).empty();
	}

	bool GroupManager::isInGroup(std::string group, Entity& e) {
		//TODO ignore case
		//return strncasecmp(group, getGroupOf(e)) == 0;
		return group.compare(getGroupOf(e)) == 0;
	}

	void GroupManager::remove(Entity& e) {
		if(e.getId() < groupByEntity.getCapacity()){
			
			auto groupId = groupByEntity.get(e.getId());
			if(groupId != NULL){
				groupByEntity.set(e.getId(), NULL);
				
				auto entities = entitiesByGroup[*groupId];
				if(entities != NULL){
					entities->remove(&e);
				}
				entities = NULL;
				delete groupId;
				groupId = NULL;
			}
			groupId = NULL;
			
		}
	}

	void GroupManager::set(std::string group, Entity& e) {
		remove(e);
		
		Bag<Entity*> * entities = entitiesByGroup[group];
		if(entities == NULL){
			entities = new Bag<Entity*>(32);
			entitiesByGroup[group] = entities;
		}
		entities->add(&e);
		entities = NULL;

		delete groupByEntity.get(e.getId());
		groupByEntity.set(e.getId(), new std::string(group));
		
	}
	
	GroupManager::~GroupManager(){
		
		groupByEntity.deleteData();
		
		//groupByEntity.clear();
	
		for(auto it : entitiesByGroup)
		{
			delete it.second;
		}

		entitiesByGroup.clear();
	}

};
