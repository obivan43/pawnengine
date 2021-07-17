#pragma once

#include "MainWindow.h"
#include "EngineManager.h"

#include "gui/BottomPanel/widget/BottomPanelWidget.h"
#include "gui/LeftPanel/widget/LeftPanelWidget.h"
#include "gui/RightPanel/widget/RightPanelWidget.h"
#include "gui/CentralWidget/widget/CentralWidget.h"

#include <QtWidgets/QDockWidget>
#include <QCloseEvent>

namespace editor {

	namespace impl {

		class MainWindowImpl : public MainWindow {
				Q_OBJECT

			public:
				MainWindowImpl(QWidget* parent = Q_NULLPTR);

				uint32_t GetDefaultWidth() const { return EngineViewWidth; }
				uint32_t GetDefaultHeight() const { return EngineViewHeight; }

				void RestoreSettings();

				void closeEvent(QCloseEvent* event) override;

			private:
				void InitEngine();
				void InitConnections();

			signals:
				void ActiveSceneChanged(std::shared_ptr<pawn::engine::GameScene>);

			private:
				BottomPanelWidget* m_BottomPanel;
				LeftPanelWidget* m_LeftPanel;
				RightPanelWidget* m_RightPanel;
				CentralWidget* m_CentralWidget;
				EngineManager* m_EngineManager;

				const uint32_t EngineViewWidth{ 1280 };
				const uint32_t EngineViewHeight{ 720 };

				const uint32_t EditorDefaultWidth{ 1920 };
				const uint32_t EditorDefaultHeight{ 1080 };
		};

	}

}