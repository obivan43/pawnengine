#pragma once

#include "PawnEditor/gui/BottomPanel/widget/BottomPanelWidget.h"
#include "OutputStream.h"

#include <QtWidgets/QTextEdit>

namespace impl {

	class BottomPanelWidgetImpl : public BottomPanelWidget {
		Q_OBJECT

		public:
			BottomPanelWidgetImpl(QWidget* parent);

		private:
			QTextEdit* m_OutputTextEdit;
			OutputStream* m_OutputStream;
	};

}
