#pragma once

#include <QObject>

namespace impl {

	class EngineManager : public QObject {
		Q_OBJECT

		public:
			EngineManager(pawn::Engine* engine);

		public slots:
			void OnEntityMeshModified(pawn::Entity entity);

		private:
			pawn::Engine* m_Engine;

	};

}