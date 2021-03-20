#pragma once

#include "RightPanelWidget.h"

#include <QtWidgets/QTreeWidget>
#include <memory>

namespace impl {

	class RightPanelWidgetImpl : public RightPanelWidget {
		Q_OBJECT

		public:
			RightPanelWidgetImpl(QWidget* parent);

		private:
			QTreeWidget* m_HierarchyPanel;
	};

}