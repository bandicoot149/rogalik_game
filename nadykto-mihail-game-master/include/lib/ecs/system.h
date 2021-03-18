#ifndef INCLUDE_LIB_ECS_SYSTEM_H_
#define INCLUDE_LIB_ECS_SYSTEM_H_

class SystemManager;
class EntityManager;

class ISystem {
  friend class SystemManager;
  bool is_enabled_ = true;
  EntityManager *const entity_manager_;
  SystemManager *const system_manager_;

 protected:
  virtual void OnPreUpdate() {}
  virtual void OnUpdate() {}
  virtual void OnPostUpdate() {}

 public:
  ISystem(EntityManager *entity_manager, SystemManager *system_manager)
      : entity_manager_(entity_manager), system_manager_(system_manager) {}
  virtual ~ISystem() = default;

  EntityManager *GetEntityManagerPtr() const {
    return entity_manager_;
  }
  EntityManager &GetEntityManager() const {
    return *GetEntityManagerPtr();
  }
  SystemManager *GetSystemManagerPtr() const {
    return system_manager_;
  }
  SystemManager &GetSystemManager() const {
    return *GetSystemManagerPtr();
  }
};

#endif  // INCLUDE_LIB_ECS_SYSTEM_H_
