#pragma once

#include <QtWidgets/QFrame>

namespace editor {

	class EngineViewWidget : public QFrame {
			Q_OBJECT

		public:
			static EngineViewWidget* CreateImpl(QWidget* parent = Q_NULLPTR);

			HWND GetWindowsHandle() { return reinterpret_cast<HWND>(winId()); }

		protected:
			EngineViewWidget(QWidget* parent);
	};

}
