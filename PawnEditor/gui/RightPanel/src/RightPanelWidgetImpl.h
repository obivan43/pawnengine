#pragma once

#include "RightPanelWidget.h"
#include "TagComponentWidgetItem.h"

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
			void InitConnections();

		public slots:
			void OnSelectedEntityChanged(pawn::Entity);

		signals:
			void EntityModified();

		private:
			QTreeWidget* m_InspectorPanel;
			TagComponentWidgetItem* m_TagComponentInspectorWidget;

			pawn::Entity m_SelectedEntity;
	};

}