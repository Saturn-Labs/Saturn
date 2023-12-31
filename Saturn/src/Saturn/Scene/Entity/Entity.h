#pragma once
#include <entt.hpp>
#include "../Scene.h"
#include "Saturn/Core/Core.h"
#include "../Components/Transform.h"
#include "../Components/Tag.h"
#include "../Components/CameraComponent.h"
#include "../Components/SpriteRenderer.h"

namespace Saturn
{
	class Entity
	{
		friend class Scene;
	public:
		Entity(entt::entity handle, Scene* scene);
		Entity() = default;
		Entity(const Entity&) = default;

		template<typename Component>
		bool HasComponent() const
		{
			if (!m_SceneReference)
				return false;
			return m_SceneReference->m_Registry.all_of<Component>(m_EntityHandle);
		}

		template<typename Component, typename... Args>
		Component& AddComponent(Args&&... args)
		{
			ST_CORE_ASSERT(!HasComponent<Component>(), "Entity already has component!");
			auto& c = m_SceneReference->m_Registry.emplace<Component>(m_EntityHandle, std::forward<Args>(args)...);
			m_SceneReference->OnComponentAdded<Component>(*this, (Component&)c);
			return (Component&)c;
		}

		template<typename S>
		S& AddScript()
		{
			ST_CORE_ASSERT(!HasComponent<Component::NativeScript>(), "Entity already has script component!");
			Component::NativeScript& component = m_SceneReference->m_Registry.emplace<Component::NativeScript>(m_EntityHandle);
			S& scriptBeh = component.Bind<S>(*this);
			return scriptBeh;
		}

		template<typename Component, typename... CArgs>
		Component& GetOrAddComponent(CArgs&&... args)
		{
			if (HasComponent<Component>())
				return GetComponent<Component>();
			else
				return AddComponent<Component>(std::forward<CArgs>(args)...);
		}

		template<typename Component>
		Component& GetComponent()
		{
			ST_CORE_ASSERT(HasComponent<Component>(), "Entity doesn't have the component!");
			return m_SceneReference->m_Registry.get<Component>(m_EntityHandle);
		}

		template<typename Component>
		void RemoveComponent()
		{
			ST_CORE_ASSERT(HasComponent<Component>(), "Entity doesn't have the component!");
			m_SceneReference->m_Registry.remove<Component>(m_EntityHandle);
		}

		operator bool() const
		{
			return m_EntityHandle != entt::null;
		}

		operator UInt32() const
		{
			return (UInt32)m_EntityHandle;
		}

		operator entt::entity() const
		{
			return m_EntityHandle;
		}

		bool operator==(const Entity& other) const
		{
			return m_EntityHandle == other.m_EntityHandle && m_SceneReference == other.m_SceneReference;
		}

		bool operator!=(const Entity& other) const
		{
			return !((*this) == other);
		}

		Component::Transform& GetTransform()
		{
			if (!m_Transform)
			{
				if (HasComponent<Component::Transform>())
					m_Transform = &GetComponent<Component::Transform>();
				else
					m_Transform = &AddComponent<Component::Transform>();
			}
			return *m_Transform;
		}
		Component::Tag& GetTag()
		{
			if (!m_Tag)
			{
				if (HasComponent<Component::Tag>())
					m_Tag = &GetComponent<Component::Tag>();
				else
					m_Tag = &AddComponent<Component::Tag>();
			}
			return *m_Tag;
		}

	private:
		entt::entity m_EntityHandle = entt::null;
		Scene* m_SceneReference = nullptr;

		Component::Transform* m_Transform = nullptr;
		Component::Tag* m_Tag = nullptr;
	};
}