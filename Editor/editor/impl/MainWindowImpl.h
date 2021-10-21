#pragma once

#include "MainWindow.h"
#include "EngineManager.h"

#include "gui/OutputWidget/widget/OutputWidget.h"
#include "gui/HierarchyWidget/widget/HierarchyWidget.h"
#include "gui/InspectorWidget/widget/InspectorWidget.h"
#include "gui/EngineViewWidget/widget/EngineViewWidget.h"
#include "gui/EnvironmentWidget/widget/EnvironmentWidget.h"

#include "gui/QtAdvancedDocking/docking/DockManager.h"

#include <QCloseEvent>
#include <QMenu>
#include <QApplication>

namespace editor::impl {

	class MainWindowImpl : public MainWindow {
			Q_OBJECT

		public:
			MainWindowImpl(QApplication* application, QWidget* parent = Q_NULLPTR);

			uint32_t GetDefaultWidth() const { return EngineViewWidth; }
			uint32_t GetDefaultHeight() const { return EngineViewHeight; }

			void RestoreSettings();

			void closeEvent(QCloseEvent* event) override;

		private:
			void InitEngine();
			void InitConnections();

		signals:
			void ActiveSceneChanged(std::shared_ptr<pawn::engine::GameScene>);

		private slots:
			void Start();
			void Pause();
			void Reset();
			void Open();
			void Save();
			void ShowHideCursor();

		private:
			QApplication* m_Application;
			ads::CDockManager* m_DockManager;
			OutputWidget* m_Output;
			HierarchyWidget* m_Hierarchy;
			InspectorWidget* m_Inspector;
			EngineViewWidget* m_EngineView;
			EnvironmentWidget* m_Environment;
			QMenu* m_FileMenu;
			QMenu* m_ViewMenu;
			QMenu* m_EngineMenu;

			std::shared_ptr<EngineManager> m_EngineManager;

			bool m_IsFreshStart;
			bool m_IsCursorHidden;

			const uint32_t EngineViewWidth{ 1280 };
			const uint32_t EngineViewHeight{ 720 };

			const uint32_t EditorDefaultWidth{ 1920 };
			const uint32_t EditorDefaultHeight{ 1080 };
	};

}
