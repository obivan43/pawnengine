#pragma once

#include <QtWidgets/QDockWidget>
#include <memory>

class LeftPanelWidget : public QDockWidget {
	Q_OBJECT

	public:
		static LeftPanelWidget* CreateImpl(QWidget* parent = Q_NULLPTR);

	signals:
		void SelectedEntityChanged(pawn::Entity entity);

	protected:
		LeftPanelWidget(QWidget* parent);
};
