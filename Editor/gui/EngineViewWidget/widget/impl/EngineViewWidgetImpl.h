#pragma once

#include "Editor/gui/EngineViewWidget/widget/EngineViewWidget.h"

namespace editor {

	namespace impl {

		class EngineViewWidgetImpl : public EngineViewWidget {
				Q_OBJECT

			public:
				EngineViewWidgetImpl(QWidget* parent);
		};

	}

}
