#pragma once

#include <QtWidgets/QWidget>

namespace editor {

	class InspectorWidget : public QWidget {
			Q_OBJECT

		public:
			static InspectorWidget* CreateImpl(QWidget* parent = Q_NULLPTR);

		protected:
			InspectorWidget(QWidget* parent);
	};

}
