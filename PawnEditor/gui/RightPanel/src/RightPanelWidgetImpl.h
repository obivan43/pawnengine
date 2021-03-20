#pragma once

#include "RightPanelWidget.h"

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

		private slots:
			void OnTagLineEditPress();

		signals:
			void EntityModified();

		private:
			QTreeWidget* m_InspectorPanel;

			QLineEdit* m_TagLineEdit;
			QTreeWidgetItem* m_TagItem;
			QTreeWidgetItem* m_TagWidgetWrapper;

			pawn::Entity m_SelectedEntity;
	};

}