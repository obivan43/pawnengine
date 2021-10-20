#pragma once

#include "TransformationComponentWidget.h"

#include "PawnEngine/engine/GameEntity.h"

#include <QtWidgets/QTreeWidgetItem>
#include <QtWidgets/QLabel>

namespace editor::impl {

	class TransformationComponentWidgetItem : public QObject, public QTreeWidgetItem {
			Q_OBJECT

		public:
			TransformationComponentWidgetItem(QTreeWidget* parent);

			void SetEntity(pawn::engine::GameEntity* entity);

			TransformationComponentWidget* GetWidget() { return m_TransformationComponentWidget; }
			QTreeWidgetItem* GetWrapper() { return m_WidgetWrapper; }

		private:
			TransformationComponentWidget* m_TransformationComponentWidget;
			QTreeWidgetItem* m_WidgetWrapper;
			pawn::engine::GameEntity* m_Entity;
	};

}
