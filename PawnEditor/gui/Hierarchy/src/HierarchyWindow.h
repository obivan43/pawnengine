#pragma once

#include <QtWidgets/QDockWidget>
#include <memory>

class HierarchyWindow : public QDockWidget {
	Q_OBJECT

	public:
		static HierarchyWindow* CreateImpl(std::shared_ptr<pawn::Scene>& scene, QWidget* parent = Q_NULLPTR);

	signals:
		void SelectedEntityChanged(pawn::Entity entity);

	protected:
		HierarchyWindow(QWidget* parent);
};
