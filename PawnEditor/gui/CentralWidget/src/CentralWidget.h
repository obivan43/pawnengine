#pragma once

#include <QtWidgets/QFrame>

class CentralWidget : public QFrame {
	Q_OBJECT

	public:
		static CentralWidget* CreateImpl(QWidget* parent = Q_NULLPTR);

		HWND GetWindowsHandle() { return reinterpret_cast<HWND>(winId()); }

	protected:
		CentralWidget(QWidget* parent);
};
