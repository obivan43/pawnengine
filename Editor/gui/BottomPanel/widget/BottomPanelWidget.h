#pragma once

#include <QtWidgets/QDockWidget>

class BottomPanelWidget : public QDockWidget {

	public:
		static BottomPanelWidget* CreateImpl(QWidget* parent = Q_NULLPTR);

	protected:
		BottomPanelWidget(QWidget* parent);
};
