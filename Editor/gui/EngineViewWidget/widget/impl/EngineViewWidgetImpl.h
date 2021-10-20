#pragma once

#include "Editor/gui/EngineViewWidget/widget/EngineViewWidget.h"

#include <QFrame>
#include <QPushButton>

namespace editor::impl {

	class EngineViewWidgetImpl : public EngineViewWidget {
			Q_OBJECT

		public:
			EngineViewWidgetImpl(QWidget* parent);

			HWND GetWindowsHandle() override { return reinterpret_cast<HWND>(m_EngineFrame->winId()); }

		private:
			QFrame* m_EngineFrame;
	};

}
