#pragma once

#include "TagComponentWidgetItem.h"
#include "TransformationComponentWidgetItem.h"
#include "MeshComponentWidgetItem.h"
#include "CameraComponentWidgetItem.h"
#include "ScriptComponentWidgetItem.h"

#include "Editor/gui/InspectorWidget/widget/InspectorWidget.h"

#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QLineEdit>
#include <memory>

namespace editor {

	namespace impl {

		class InspectorWidgetImpl : public InspectorWidget {
				Q_OBJECT

			public:
				InspectorWidgetImpl(QWidget* parent);

				void RefreshPanel();

			private:
				void InitTagComponent();
				void InitTransformationComponent();
				void InitMeshComponent();
				void InitCameraComponent();
				void InitConnections();
				void InitScriptComponent();

			public slots:
				void OnSelectedEntityChanged(pawn::engine::GameEntity);

			signals:
				void EntityTagModified();
				void EntityMeshModfied(pawn::engine::GameEntity);

			private:
				QTreeWidget* m_InspectorPanel;
				TagComponentWidgetItem* m_TagComponentInspectorWidgetItem;
				TransformationComponentWidgetItem* m_TransformationComponentInspectorWidgetItem;
				MeshComponentWidgetItem* m_MeshComponentWidgetItem;
				CameraComponentWidgetItem* m_CameraComponentWidgetItem;
				ScriptComponentWidgetItem* m_ScriptComponentInspectorWidgetItem;

				pawn::engine::GameEntity m_SelectedEntity;
		};

	}

}
