#pragma once

#include "PawnEngine/engine/Engine.h"

#include <QObject>

namespace impl {

	class EngineManager : public QObject {
		Q_OBJECT

		public:
			EngineManager(pawn::Engine* engine);

		public slots:
			void OnEntityMeshModified(pawn::GameEntity entity);

		private:
			pawn::Engine* m_Engine;

	};

}