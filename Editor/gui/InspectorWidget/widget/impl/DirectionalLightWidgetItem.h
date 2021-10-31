#pragma once

#include "PawnEngine/engine/GameEntity.h"

#include "DirectionalLightWidget.h"

#include <QtWidgets/QTreeWidgetItem>

namespace editor::impl {

	class DirectionalLightWidgetItem : public QObject, public QTreeWidgetItem {
		Q_OBJECT

		public:
			DirectionalLightWidgetItem(QTreeWidget* parent);

			void SetEntity(pawn::engine::GameEntity* entity);

			DirectionalLightWidget* GetWidget() { return m_DirectionalLightWidget; }
			QTreeWidgetItem* GetWrapper() { return m_WidgetWrapper; }

		private:
			DirectionalLightWidget* m_DirectionalLightWidget;
			QTreeWidgetItem* m_WidgetWrapper;
			pawn::engine::GameEntity* m_Entity;
	};

}
