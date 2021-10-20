#pragma once

#include "CameraComponentWidget.h"

#include "PawnEngine/engine/GameEntity.h"

#include <QTreeWidgetItem>

namespace editor::impl {

	class CameraComponentWidgetItem : public QObject, public QTreeWidgetItem {
		Q_OBJECT

		public:
			CameraComponentWidgetItem(QTreeWidget* parent);

			void SetEntity(pawn::engine::GameEntity* entity);

			CameraComponentWidget* GetWidget() { return m_CameraComponentWidget; }
			QTreeWidgetItem* GetWrapper() { return m_WidgetWrapper; }

		private:
			CameraComponentWidget* m_CameraComponentWidget;
			QTreeWidgetItem* m_WidgetWrapper;
			pawn::engine::GameEntity* m_Entity;
	};

}
