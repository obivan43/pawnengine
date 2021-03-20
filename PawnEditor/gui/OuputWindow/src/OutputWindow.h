#pragma once

#include <QtWidgets/QDockWidget>

class OutputWindow : public QDockWidget {

	public:
		static OutputWindow* createImpl(QWidget* parent = Q_NULLPTR);

	protected:
		OutputWindow(QWidget* parent);
};
