#pragma once

#include "PawnEngine/engine/GameEntity.h"

#include <QObject>
#include <QMenu>

namespace editor {

	namespace impl {

		class HierarchyWidgetImpl;

		class HierarchyWidgetContextMenu : public QObject {
			Q_OBJECT

			public:

				HierarchyWidgetContextMenu(QWidget* parent = Q_NULLPTR);

				void ShowMenu(
					HierarchyWidgetImpl* widget,
					const QPoint& position
				);

			private:
				pawn::engine::GameEntity Create3DObject(const QString& name);

				void InitConnections();

			public slots:
				void CreateEmptyEntity();
				void CreateCube();
				void CreateSphere();
				void CreateCone();
				void CreateTorus();
				void CreateCylinder();

				void DeleteEntity();

			private:
				HierarchyWidgetImpl* m_HierarchyWidget;

				QMenu* m_ContextMenu;
				QAction* m_CreateEmptyEntity;
				QAction* m_DeleteEntity;

				QMenu* m_Create3DObject;
				QAction* m_CreateCube;
				QAction* m_CreateSphere;
				QAction* m_CreateCone;
				QAction* m_CreateTorus;
				QAction* m_CreateCylinder;
		};

	}

}

