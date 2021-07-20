#pragma once

#include <QtWidgets/QWidget>

namespace editor {

	class OutputWidget : public QWidget {

		public:
			static OutputWidget* CreateImpl(QWidget* parent = Q_NULLPTR);

		protected:
			OutputWidget(QWidget* parent);
	};

}
