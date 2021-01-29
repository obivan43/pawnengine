#pragma once

#include <string>

namespace pawn {

	class Rtti {
        public:
		
            Rtti() = default;
            Rtti(const Rtti& other) = default;
            Rtti(Rtti&& other) = default;

            Rtti& operator=(const Rtti& other) = default;
            Rtti& operator=(Rtti&& other) = default;

            virtual ~Rtti() = default;
		
            virtual size_t TypeIdInstance() const = 0;

            virtual Rtti* QueryInterface(const size_t) {
                return nullptr;
            }

            virtual const Rtti* QueryInterface(const size_t) const {
                return nullptr;
            }

            virtual bool Is(const size_t id) const {
                return false;
            }

            virtual bool Is(const std::string& name) const {
                return false;
            }

            template <typename Type> Type* As() {
                if (Is(Type::TypeIdClass())) {
                    return reinterpret_cast<Type*>(this);
                }

                return nullptr;
            }

            template <typename Type> const Type* As() const {
                if (Is(Type::TypeIdClass()))
                {
                    return reinterpret_cast<Type*>(this);
                }

                return nullptr;
            }
	};

}

#define RTTI_DECLARATIONS(Type, ParentType)                            \
    public:                                                            \
        static const std::string& TypeName()                           \
        { static std::string name(#Type); return name; }               \
        virtual size_t TypeIdInstance() const                          \
        { return Type::TypeIdClass(); }                                \
        static const size_t TypeIdClass()                              \
        { static size_t id = 0; return reinterpret_cast<size_t>(&id); }\
        virtual pawn::Rtti* QueryInterface(const size_t id)            \
        {                                                              \
            if (id == TypeIdClass())                                   \
                { return (Rtti*)this; }                                \
            else                                                       \
                { return ParentType::QueryInterface(id); }             \
        }                                                              \
        virtual const pawn::Rtti* QueryInterface(const size_t id) const\
        {                                                              \
            if (id == TypeIdClass())                                   \
                { return (Rtti*)this; }                                \
            else                                                       \
                { return ParentType::QueryInterface(id); }             \
        }                                                              \
        virtual bool Is(const size_t id) const                         \
        {                                                              \
            if (id == TypeIdClass())                                   \
                { return true; }                                       \
            else                                                       \
                { return ParentType::Is(id); }                         \
        }                                                              \
        virtual bool Is(const std::string& name) const                 \
        {                                                              \
            if (name == TypeName())                                    \
                { return true; }                                       \
            else                                                       \
                { return ParentType::Is(name); }                       \
        }                                                              

