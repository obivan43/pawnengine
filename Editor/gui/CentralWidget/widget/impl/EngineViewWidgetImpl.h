#pragma once

#include "Editor/gui/CentralWidget/widget/EngineViewWidget.h"

namespace editor {

	namespace impl {

		class EngineViewWidgetImpl : public EngineViewWidget {
				Q_OBJECT

			public:
				EngineViewWidgetImpl(QWidget* parent);
		};

	}

}
