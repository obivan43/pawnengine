#pragma once

#include <QtWidgets/QDockWidget>
#include <QCloseEvent>

#include "MainWindow.h"
#include "gui/BottomPanel/include/bottompanelwidget.h"
#include "gui/LeftPanel/include/leftpanelwidget.h"
#include "gui/RightPanel/include/rightpanelwidget.h"
#include "gui/CentralWidget/include/centralwidget.h"

namespace impl {

	class MainWindowImpl : public MainWindow {
		Q_OBJECT

		public:
			MainWindowImpl(QWidget* parent = Q_NULLPTR);

			uint32_t GetDefaultWidth() const { return DefaultWidth; }
			uint32_t GetDefaultHeight() const { return DefaultHeight; }

			void closeEvent(QCloseEvent* event);

		private:
			void InitEngine();
			void InitConnections();

		signals:
			void ActiveSceneChanged(std::shared_ptr<pawn::Scene>);

		private:
			BottomPanelWidget* m_BottomPanel;
			LeftPanelWidget* m_LeftPanel;
			RightPanelWidget* m_RightPanel;
			CentralWidget* m_CentralWidget;

			const uint32_t DefaultWidth = 1280;
			const uint32_t DefaultHeight = 720;
	};

}