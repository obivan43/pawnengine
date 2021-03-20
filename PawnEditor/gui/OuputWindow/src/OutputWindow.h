#pragma once

#include <QtWidgets/QDockWidget>

class OutputWindow : public QDockWidget {

	public:
		static OutputWindow* CreateImpl(QWidget* parent = Q_NULLPTR);

	protected:
		OutputWindow(QWidget* parent);
};
