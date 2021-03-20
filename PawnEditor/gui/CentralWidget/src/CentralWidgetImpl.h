#pragma once

#include "CentralWidget.h"

namespace impl {

	class CentralWidgetImpl : public CentralWidget {
		Q_OBJECT

		public:
			CentralWidgetImpl(QWidget* parent);
	};

}