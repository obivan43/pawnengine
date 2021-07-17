#pragma once

#include "PawnEngine/engine/Engine.h"

#include <QObject>

namespace impl {

	class EngineManager : public QObject {
		Q_OBJECT

		public:
			EngineManager(pawn::engine::Engine* engine);

		public slots:
			void OnEntityMeshModified(pawn::engine::GameEntity entity);

		private:
			pawn::engine::Engine* m_Engine;

	};

}