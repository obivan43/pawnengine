#pragma once

#include "Editor/gui/CentralWidget/widget/CentralWidget.h"

namespace editor {

	namespace impl {

		class CentralWidgetImpl : public CentralWidget {
				Q_OBJECT

			public:
				CentralWidgetImpl(QWidget* parent);
		};

	}

}
