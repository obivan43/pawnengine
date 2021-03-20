#pragma once

#include <QtWidgets/QDockWidget>

class RightPanelWidget : public QDockWidget {
	Q_OBJECT

	public:
		static RightPanelWidget* CreateImpl(QWidget* parent = Q_NULLPTR);

	protected:
		RightPanelWidget(QWidget* parent);
};