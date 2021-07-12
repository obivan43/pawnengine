#pragma once

#include "TransformationComponentWidget.h"

#include <QtWidgets/QTreeWidgetItem>
#include <QtWidgets/QLabel>

namespace impl {

	class TransformationComponentWidgetItem : public QObject, public QTreeWidgetItem {
		Q_OBJECT

		public:
			TransformationComponentWidgetItem(QTreeWidget* parent);

			void SetEntity(pawn::GameEntity* entity);

			TransformationComponentWidget* GetWidget() { return m_TransformationComponentWidget; }
			QTreeWidgetItem* GetWrapper() { return m_WidgetWrapper; }

		private:
			TransformationComponentWidget* m_TransformationComponentWidget;
			QTreeWidgetItem* m_WidgetWrapper;
			pawn::GameEntity* m_Entity;
	};

}