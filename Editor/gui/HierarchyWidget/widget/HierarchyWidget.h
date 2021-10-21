#pragma once

#include "PawnEngine/engine/GameEntity.h"

#include "Editor/editor/impl/EngineManager.h"

#include <QtWidgets/QWidget>
#include <memory>

namespace editor {

	class HierarchyWidget : public QWidget {
			Q_OBJECT

		public:
			static HierarchyWidget* CreateImpl(QWidget* parent = Q_NULLPTR);

			virtual void RefreshPanel() = 0;

			void SetEngineManager(std::shared_ptr<impl::EngineManager>& engineManager);

			std::shared_ptr<impl::EngineManager> GetEngineManager();

		signals:
			void SelectedEntityChanged(pawn::engine::GameEntity entity);

		protected:
			HierarchyWidget(QWidget* parent);

		protected:
			std::shared_ptr<impl::EngineManager> m_EngineManager;
	};

}
