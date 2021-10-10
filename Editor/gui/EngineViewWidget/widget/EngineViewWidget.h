#pragma once

#include <QWidget>

namespace editor {

	class EngineViewWidget : public QWidget {
			Q_OBJECT

		public:
			static EngineViewWidget* CreateImpl(QWidget* parent = Q_NULLPTR);

			virtual HWND GetWindowsHandle() = 0;

		protected:
			EngineViewWidget(QWidget* parent);
	};

}
