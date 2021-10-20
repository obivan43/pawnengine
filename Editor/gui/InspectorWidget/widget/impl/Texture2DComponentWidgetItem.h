#pragma once

#include "PawnEngine/engine/GameEntity.h"

#include "Texture2DComponentWidget.h"

#include <QtWidgets/QTreeWidgetItem>

namespace editor::impl {

	class Texture2DComponentWidgetItem : public QObject, public QTreeWidgetItem {
		Q_OBJECT

		public:
			Texture2DComponentWidgetItem(QTreeWidget* parent);

			void SetEntity(pawn::engine::GameEntity* entity);

			Texture2DComponentWidget* GetWidget() { return m_Texturee2DComponentWidget; }
			QTreeWidgetItem* GetWrapper() { return m_WidgetWrapper; }

		private:
			void InitConnections();

		signals:
			void EntityTexture2DModified(pawn::engine::GameEntity entity);

		private:
			Texture2DComponentWidget* m_Texturee2DComponentWidget;
			QTreeWidgetItem* m_WidgetWrapper;
			pawn::engine::GameEntity* m_Entity;
	};

}
