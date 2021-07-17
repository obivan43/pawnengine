#pragma once

#include "TagComponentWidgetItem.h"
#include "TransformationComponentWidgetItem.h"
#include "MeshComponentWidgetItem.h"

#include "Editor/gui/RightPanel/widget/RightPanelWidget.h"

#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QLineEdit>
#include <memory>

namespace impl {

	class RightPanelWidgetImpl : public RightPanelWidget {
		Q_OBJECT

		public:
			RightPanelWidgetImpl(QWidget* parent);

			void RefreshPanel();

		private:
			void InitTagComponent();
			void InitTransformationComponent();
			void InitMeshComponent();
			void InitConnections();

		public slots:
			void OnSelectedEntityChanged(pawn::engine::GameEntity);

		signals:
			void EntityTagModified();
			void EntityMeshModfied(pawn::engine::GameEntity);

		private:
			QTreeWidget* m_InspectorPanel;
			TagComponentWidgetItem* m_TagComponentInspectorWidget;
			TransformationComponentWidgetItem* m_TransformationComponentInspectorWidget;
			MeshComponentWidgetItem* m_MeshComponentWidgetItem;

			pawn::engine::GameEntity m_SelectedEntity;
	};

}
