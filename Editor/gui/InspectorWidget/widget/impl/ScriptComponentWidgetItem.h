#pragma once

#include "PawnEngine/engine/GameEntity.h"

#include "ScriptComponentWidget.h"

#include <QtWidgets/QTreeWidgetItem>
#include <QtWidgets/QLineEdit>

namespace editor {

	namespace impl {

		class ScriptComponentWidgetItem : public QObject, public QTreeWidgetItem {
			Q_OBJECT

			public:
				ScriptComponentWidgetItem(QTreeWidget* parent);

				void SetEntity(pawn::engine::GameEntity* entity);

				ScriptComponentWidget* GetWidget() { return m_ScriptComponentWidget; }
				QTreeWidgetItem* GetWrapper() { return m_WidgetWrapper; }

			private:
				void InitConnections();

			signals:
				void EntityScriptModified();

			private:
				ScriptComponentWidget* m_ScriptComponentWidget;
				QTreeWidgetItem* m_WidgetWrapper;
				pawn::engine::GameEntity* m_Entity;
		};

	}

}
