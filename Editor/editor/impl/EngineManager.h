#pragma once

#include "PawnEngine/engine/Engine.h"

#include <QObject>

namespace editor::impl {

	class EngineManager : public QObject {
			Q_OBJECT

		public:
			EngineManager(pawn::engine::Engine* engine);

			pawn::engine::Engine* GetEngine();

		public slots:
			void OnEntityMeshModified(pawn::engine::GameEntity entity);
			void OnEntityTexture2DModified(pawn::engine::GameEntity entity);

		private:
			pawn::engine::Engine* m_Engine;
	};

}
