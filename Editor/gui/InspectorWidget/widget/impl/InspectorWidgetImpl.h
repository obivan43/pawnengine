#pragma once

#include "TagComponentWidgetItem.h"
#include "TransformationComponentWidgetItem.h"
#include "MeshComponentWidgetItem.h"
#include "CameraComponentWidgetItem.h"
#include "ScriptComponentWidgetItem.h"
#include "NewComponentWidget.h"
#include "SelectComponentWidget.h"
#include "Texture2DComponentWidgetItem.h"

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

				void ForceUpdate();
				void RefreshPanel();

			private:
				void InitNewComponent();
				void InitTagComponent();
				void InitTransformationComponent();
				void InitMeshComponent();
				void InitCameraComponent();
				void InitConnections();
				void InitScriptComponent();
				void InitTexture2DComponent();

			public slots:
				void Update();
				void UpdateTransformation();
				void OnSelectedEntityChanged(pawn::engine::GameEntity);
				void OnNewComponentAdded(ComponentsEnum id);

			signals:
				void EntityTagModified();
				void EntityMeshModfied(pawn::engine::GameEntity);
				void EntityTexture2DModified(pawn::engine::GameEntity);

			private:
				QTreeWidget* m_InspectorPanel;
				NewComponentWidget* m_NewComponentWidget;
				TagComponentWidgetItem* m_TagComponentInspectorWidgetItem;
				TransformationComponentWidgetItem* m_TransformationComponentInspectorWidgetItem;
				MeshComponentWidgetItem* m_MeshComponentWidgetItem;
				CameraComponentWidgetItem* m_CameraComponentWidgetItem;
				ScriptComponentWidgetItem* m_ScriptComponentInspectorWidgetItem;
				Texture2DComponentWidgetItem* m_Texture2DComponentWidgetItem;

				pawn::engine::GameEntity m_SelectedEntity;
		};

	}

}
