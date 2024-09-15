#pragma once
#include "Common/Types.hpp"

namespace Saturn {
    template<typename TName, TName TNameInvalid>
    class GraphicsResource {
    public:
        inline static TName NameDefault = TNameInvalid;
    protected:
        TName mName = NameDefault;
    public:
        GraphicsResource() = default;
        GraphicsResource(const GraphicsResource&) = delete;
        GraphicsResource(GraphicsResource&&) = delete;
        GraphicsResource& operator=(const GraphicsResource&) = delete;
        GraphicsResource& operator=(GraphicsResource&&) = delete;
        virtual ~GraphicsResource() = default;

        virtual bool IsValid() const {
            return mName != NameDefault;
        }

        const TName& GetName() const {
            return mName;
        }
    };
}