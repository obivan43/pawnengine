#pragma once

#include "PawnEngine/engine/GameEntity.h"

#include <QtWidgets/QWidget>
#include <memory>

namespace editor {

	class HierarchyWidget : public QWidget {
			Q_OBJECT

		public:
			static HierarchyWidget* CreateImpl(QWidget* parent = Q_NULLPTR);

		signals:
			void SelectedEntityChanged(pawn::engine::GameEntity entity);

		protected:
			HierarchyWidget(QWidget* parent);
	};

}
